
/* --------------------------------------------------------------------  */
/*                                                                       */
/*                         Author: Clyde Hoover                          */
/*                          Computation Center                           */
/*                   The University of Texas at Austin                   */
/*                          Austin, Texas 78712                          */
/*                         clyde@emx.utexas.edu                          */
/*                   uunet!cs.utexas.edu!ut-emx!clyde                    */
/*                                                                       */
/*This code may be distributed freely, provided this notice is retained. */
/*                                                                       */
/* --------------------------------------------------------------------  */
/*
 *      This program duplicates the manual page behavior of the 4.XBSD
 *      passwd(1) command.  It can be configured for use with a variety
 *      of passwd systems (/etc/passwd, /etc/shadow, databases).
 *
 *      The System V support is untested (by the author - other sites
 *      tell me it works).
 *
 *      Here we have only the most abstract data needed (login name,
 *      user id, current password, new password).
 *      All other information needed (the full password line, etc),
 *      is kept down in the 'method' routines.
 *
 *      The 'method' routines are:
 *
 *      pw_initalize()          Do initializations
 *      pw_getuserbyname()      Get user information by name
 *      pw_permission()         Check if user has permission
 *                               to change this users' password
 *      pw_compare()            Compare passwords
 *      pw_check()              Check password
 *                               Returns 1 if ok, 0 otherwise
 *      pw_replace()            Replace the password
 *      pw_cleanup()            Cleanup
 */
#ifdef  SYSLOG
#include <syslog.h>
# ifndef        LOG_AUTH
#  define       LOG_AUTH        0
# endif
# ifndef        LOG_CONS
#  define       LOG_CONS        0
# endif
#endif

#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <pwd.h>
#include <errno.h>

#ifdef __STDC__
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#endif

#ifdef AUTH_SECURITY
# include <auth.h>
#endif

#include "npasswd.h"

char *version = VERSION;
char *patchlevel = PATCHLEVEL;

#ifndef lint
static char sccsid[] = "@(#)npasswd.c   1.16 9/24/90 (cc.utexas.edu) /usr/share/src/private/ut/share/bin/passwd/SCCS/s.npasswd.c";
#endif

#ifndef CONFIG_FILE
#define CONFIG_FILE     "/usr/adm/passwd.conf"
#endif
#ifndef HELP_FILE
#define HELP_FILE       "/usr/adm/passwd.help"
#endif
#ifndef MOTD_FILE
#define MOTD_FILE       "/usr/adm/passwd.motd"
#endif
#ifndef SHELL_FILE
#define SHELL_FILE      "/etc/shells"
#endif

extern int      errno;                  /* System error code */

#ifdef  sun
static char     *options = "alyd:e:F:n:fPsVx:"; /* Command line options */
#else
static char     *options = "afPsV";      /* Command line options */
#endif
static int      retries = 3;            /* Retry limit */
static int      from_prog = 0;          /* Data source is a program */

static char     username[USERNAMESIZE+1],/* Name of user changing password */
                password[PBUFSIZE];     /* Current password (encrypted) */

char    pbuf[PBUFSIZE],                 /* Password read buffer 1 */
        pbuf2[PBUFSIZE],                /* Password read buffer 2 */
        ppbuf[PBUFSIZE],                /* Current password */
        mylogin[PBUFSIZE];              /* My login name (saved) */

static	passwdp UserPasswd;             /* Password info about user */
static	authp   UserAuth;               /* Authorization info */

/*
 *      passwd - change the password for a user.
 *
 *      This program implements the 'passwd' command.
 */
int main(argc, argv)
int     argc;
char    *argv[];
{
        char    *myname, mysavedname[USERNAMESIZE];/* My login name */
        struct  passwd *pw;             /* My passwd entry */
        int     opt;                    /* Option processing temp */
        extern  char     *optarg;       /* From getopt() */
        extern  int      optind;        /* From getopt() */
	int	DoPasswd;		/* Get the user to change their password */
	int	DoFinger;		/* Get the user to change their finger info */
	int	DoShell;		/* Get the user to change their shell */
	char	*ProgName;		/* The name of this program */

	ProgName = strrchr(argv[0], '/');
	if (ProgName == NULL)
		ProgName = argv[0];
	else
		ProgName++;
	DoPasswd = 0;
	DoFinger = strcmp(ProgName, "chfn") == 0; /* pretend to be chfn */
	DoShell = strcmp(ProgName, "chsh") == 0;  /* pretend to be chsh */

        /*
         * Handle the 4.3BSD & SunOS 4.0 command line options.
         * Defer everything except password change to other programs.
         */
        while ((opt = getopt(argc, argv, options)) != EOF) {
                switch (opt) {
#ifdef  sun
                /*
                 * Recognized the SunOS 4.1 switches
                 * but just say that we don't handle them.
                 */
                case 'l':
                case 'y':
                case 'd':
                case 'e':
                case 'n':
                case 'x':
                case 'F':
                        fprintf(from_prog ? stdout : stderr,
                                "Option \"-%c\" not supported.\n", opt);
                        exit(1);
#endif
                case 'a':
			DoFinger = 1;
			DoShell = 1;
			DoPasswd = 1;
			break;
                case 'f':
                        DoFinger = 1;
                        break;
                case 's':
                        DoShell = 1;
                        break;
                case 'P':               /* Data source is a program */
                        if (getuid())
                                quit(0, "Option \"-P\" reserved for super-user.\n");
                        from_prog = 1;
                        break;
                case 'V':
                        printf("%s; patch level %s\n", version, patchlevel);
                        exit(0);
                }
        }

	/* make sure that at least a password change is selected */
	if (!DoPasswd && !DoFinger && !DoShell)
		DoPasswd = 1;

        bzero(ppbuf, sizeof(ppbuf));
#ifndef DEBUG
        if (geteuid())
                quit(0,"Permission denied.\n");
#endif
        checktty();
        savetty();
        myname = getlogin();
        if (myname == 0 || *myname == '\0') {
                if ((pw = getpwuid(getuid())) == ((struct passwd *)NULL))
                        quit(1, "Cannot get your login name.\n");
                strncpy(mysavedname, pw->pw_name, sizeof(mysavedname));
                myname = mysavedname;
        }
        (void) strcpy(mylogin, myname);
        (void) signal(SIGINT, catchit);
        (void) signal(SIGQUIT, catchit);

#ifdef  SYSLOG
        openlog("passwd", LOG_PID | LOG_CONS, LOG_AUTH);
#endif
        setcheckpasswd("-c", CONFIG_FILE, 0);
        pw_initialize();

        if (argv[optind])
                (void) strcpy(username, argv[optind]);
        else
                (void) strcpy(username, mylogin);

        if (strcmp(username, mylogin) == 0 && getuid()) {
                if ((UserPasswd = pw_getuserbyname(username, password)) == NULL)
                        quit(1, "Cannot get your password information.\n");
#ifdef AUTH_SECURITY
                if ((UserAuth = pw_getauth(UserPasswd->pw_uid, password)) == NULL)
                        quit(1, "Cannot get your password information.\n");
#endif
        }
        else {
                if ((UserPasswd = pw_getuserbyname(username, password)) == 0)
                        quit(0, "No such user %s\n", argv[optind]);
#ifdef AUTH_SECURITY
                if ((UserAuth = pw_getauth(UserPasswd->pw_uid, password)) == NULL)
                        quit(0, "Cannot get password information for %s.\n", argv[optind]);
#endif
                if ((pw_permission() & 1) == 0)
                        quit(0, "Permission denied.\n");
        }

        motd(MOTD_FILE, (char *)0);

	if (DoShell)
		ChangeShell();

	if (DoFinger)
		ChangeFinger();

	if (DoPasswd)
		ChangePasswd();

#ifdef AUTH_SECURITY
        pw_replace(pbuf, ppbuf, UserPasswd, UserAuth, DoPasswd);
#else
        pw_replace(pbuf, ppbuf, UserPasswd);
#endif
        pw_cleanup(0);
        exit(0);
}


void ChangePasswd()
{
	if ((pw_permission() & 4) == 0)
		quit(0, "You're not allowed to change your password yet.\n");

        if (strcmp(username, mylogin) == 0 && getuid()) {
                if (password[0])
                        getpassword(password, ppbuf, sizeof(ppbuf));
	} else
                printf("Changing password for %s\n", username);

        for (;;) {
                char    *px;            /* Temp */
                int     ntries = 0;     /* Password match counter */

                px = getpass(from_prog ? "" : "New password (? for help): ");
                if (px == NULL)
                        quit(0, "EOF during new password read.\n");
                (void) strcpy(pbuf, px);
                if (pbuf[0] == '?') {
                        motd(HELP_FILE, "Missing help file");
                        continue;
                }
                /* Sanity check the new password */
                if (pw_check(pbuf) == 0)
                        continue;

                /* Get confirmation */
                px = getpass(from_prog ? "" : "New password (again): ");
                if (px == NULL)
                        quit(0, "EOF during new password read.\n");
                (void) strcpy(pbuf2, px);
                if (strcmp(pbuf, pbuf2)) {
                        if (ntries++ >= retries)
                                quit(0, "Too many attempts.\n");
                        else
                                printf("They don't match; try again.\n");
                        if (from_prog)
                                quit(0, (char *)0);
                        else
                                continue;
                }
                /* Disallow new password == old password */
                if (pw_compare(password, pbuf)) {
                        printf("New password must be different than old; try again.\n");
                        if (from_prog)
                                quit(0, (char *)0);
                        else
                                continue;
                }
                else
                        break;
        }
#ifdef AUTH_SECURITY
	/* update the password time */
	UserAuth->a_pass_mod = time(NULL);
#endif
#ifdef  SYSLOG
        syslog(LOG_INFO, "Password changed for %s by %s\n",
                username, mylogin);
#endif
        printf("Password changed for %s\n", username);
}


int checkinput(InString)
char *InString;
{
	int Count;
	for (Count = 0; *(InString + Count) != 0; Count++) {
		if (!isprint(*(InString + Count))) {
			printf("Control codes are not allowed.\n\n");
			return 0;
		}
		if (*(InString + Count) == ':') {
			printf("Colons are not allowed.\n\n");
			return 0;
		}
		if (*(InString + Count) == ',') {
			printf("Commas are not allowed.\n\n");
			return 0;
		}
	}

	/* strip trailing spaces */
	for (Count--; Count >= 0 && *(InString + Count) == ' '; Count--)
		*(InString + Count) = 0;

	return 1;
}


void ChangeFinger()
{
	char Gecos[BUFMAX*5];	/* a copy of the gecos info */
	char NewName[BUFMAX];	/* the new real name string */
	char NewOfficeNo[BUFMAX]; /* the new office number */
	char NewOfficePh[BUFMAX]; /* the new office phone number */
	char NewHomePh[BUFMAX];	/* the new home phone number */
	char *OfficeNo, *OfficePh, *HomePh;	/* separate fields */

	/* separate out the fields */
	strcpy(Gecos, UserPasswd->pw_gecos);
	OfficeNo = strchr(Gecos, ',');
	OfficePh = NULL;
	HomePh = NULL;

	if (OfficeNo != NULL) {
		*OfficeNo++ = 0; /* null-term real name and advance */
		OfficePh = strchr(OfficeNo, ',');
		if (OfficePh != NULL) {
			*OfficePh++ = 0;
			HomePh = strchr(OfficePh, ',');
			if (HomePh != NULL)
				*HomePh++ = 0;
		}
	}

	if ((pw_permission() & 2) == 2) {
		/* get the real name */
		do {
			if (Gecos[0] == 0)
				printf("Real name ? ");
			else
				printf("Real name [default '%s'] ? ", Gecos);
			getinput(NewName, BUFMAX, Gecos);
		} while (!checkinput(NewName) && NewName[0] != 0);
	} else
		strcpy(NewName, Gecos);

	/* get the office number */
	do {
		if (OfficeNo != NULL && *OfficeNo != 0) {
			printf("Office number [default '%s', space for none] ? ", OfficeNo);
			getinput(NewOfficeNo, BUFMAX, OfficeNo);
		} else {
			printf("Office number [default none] ? ");
			getinput(NewOfficeNo, BUFMAX, "");
		}
	} while (!checkinput(NewOfficeNo));

	/* get the office phone number */
	do {
		if (OfficePh != NULL && *OfficePh != 0) {
			printf("Office phone number [default '%s', space for none] ? ", OfficePh);
			getinput(NewOfficePh, BUFMAX, OfficePh);
		} else {
			printf("Office phone number [default none] ? ");
			getinput(NewOfficePh, BUFMAX, "");
		}
	} while (!checkinput(NewOfficePh));

	/* get the home phone number */
	do {
		if (HomePh != NULL && *HomePh != 0) {
			printf("Home phone number [default '%s', space for none] ? ", HomePh);
			getinput(NewHomePh, BUFMAX, HomePh);
		} else {
			printf("Home phone number [default none] ? ");
			getinput(NewHomePh, BUFMAX, "");
		}
	} while (!checkinput(NewHomePh));

	/* construct the new gecos string */
	if (NewHomePh[0] != 0)
		sprintf(Gecos, "%s,%s,%s,%s", NewName, NewOfficeNo, NewOfficePh, NewHomePh);
	else if (NewOfficePh[0] != 0) 
		sprintf(Gecos, "%s,%s,%s", NewName, NewOfficeNo, NewOfficePh);
	else if (NewOfficeNo[0] != 0)
		sprintf(Gecos, "%s,%s", NewName, NewOfficeNo);
	else
		strcpy(Gecos, NewName);
	Gecos[BUFMAX-1] = 0; /* cruelly null-terminate */

	/* copy back to the gecos field */
	free(UserPasswd->pw_gecos);
	UserPasswd->pw_gecos = _newstr(Gecos);
}


void ChangeShell()
{
	char WantShell[BUFMAX];
	char ShellBuf[BUFMAX];
	FILE *ShellFile;
	int Found;

	do {
		printf("Shell [Default %s] ? ", UserPasswd->pw_shell);
		getinput(WantShell, BUFMAX, UserPasswd->pw_shell);

		/* check if the chosen shell is in /etc/shells */
		ShellFile = fopen(SHELL_FILE, "r");
		if (ShellFile == NULL)
			quit(1, "Can't open list of valid shells\n");
		Found = 0;
		while (!feof(ShellFile)) {
			if (fgets(ShellBuf, BUFMAX-1, ShellFile) != NULL) {
				ShellBuf[BUFMAX-1] = 0; /* null-term */
				if (ShellBuf[0] != 0 && ShellBuf[strlen(ShellBuf)-1] == '\n')
					ShellBuf[strlen(ShellBuf)-1] = 0; /* strip lf */
				if (strcmp(ShellBuf, WantShell) == 0)
					Found = 1;
			}
		}
		if (!Found && getuid() != 0) {
			printf("\nYou must choose one of:\n\n");
			fseek(ShellFile, 0, SEEK_SET); /* rewind */
			while (!feof(ShellFile)) {
				if (fgets(ShellBuf, BUFMAX-1, ShellFile) != NULL) {
					ShellBuf[BUFMAX-1] = 0; /* null-term */
					printf("%s", ShellBuf);
				}
			}
			printf("\n");
		}
		fclose(ShellFile);
	} while (!Found && getuid() != 0);

	/* assign the new shell */
	free(UserPasswd->pw_shell);
	UserPasswd->pw_shell = _newstr(WantShell);
}


/*
 *      getpassword -- read password and check against current.
 */
void getpassword(pwd_crypt, pwd_plain, pwlen)
char    *pwd_crypt,             /* Present password (encrypted) */
        *pwd_plain;             /* Present password (plain)  */
int     pwlen;                  /* Length of present password buffer */
{
        int     ntries = 0;     /* Match attempt counter */
        char    *px;            /* Temp */

        for (;;) {
                px = getpass(from_prog ? "" : "Current password: ");
                if (px == 0)
                        quit(0, "EOF during password read.\n");
                if (*px == '\0')
                        continue;
                if (!pw_compare(pwd_crypt, px)) {
                        printf("Password incorrect.\n");
                        if (ntries++ == retries)
                                quit(0, "Password not matched.\n");
                }
                else
                        break;
        }
        if (pwd_plain)
                (void) strncpy(pwd_plain, px, pwlen);
}


#define MAXRANDSTRING 128       /* the maximum length of random strings */
/*
 *      randomstring - create a string of random characters
 */
void randomstring(buf, len)
char    buf[];          /* String buffer */
int     len;            /* Length of buf */
{
        register int    i,              /* Temp */
                        n;              /* Temp */
        time_t          tv;             /* Current time */
        char            proto[MAXRANDSTRING];   /* Build buffer */

        (void) time (&tv);
        /*
         * Assumes (implicitly) that sizeof(int) == sizeof(long)
         */
        (void) srand ( (tv & 0x38d9fcff) ^ getpid ());
        for (i = 0; i < sizeof(proto); i++) {   /* fill proto vector */
                int     c;              /* Temp */

                for (;;) {
                        c = rand () % 0x7f;     /* turn into ASCII */
                        if (isalnum (c))
                                break;
                }
                proto[i] = (char )c;
        }
        (void) srand(((unsigned )tv & 0x1a90fefc) ^ getpid());
        for (i = 0; i < len; i++) {
                n = rand() % sizeof(proto);
                buf[i] = proto[n];
        }
        buf[len] = 0;
}

/*
 *      quit - print/log error message and exit
 */
quit(logit, message, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10)
int     logit;          /* 0 = don't log, <> 0 = log message */
char    *message;       /* Message */
int	*a1, *a2, *a3, *a4, *a5, *a6, *a7, *a8, *a9, *a10;
{
        if (message) {
                /*
                 * If used from program, direct failure messages to stdout,
                 * else send to stderr.
                 */
                fprintf(from_prog ? stdout : stderr,  message, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
#ifdef  SYSLOG
                if (logit)
                        syslog(LOG_ERR,  message, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
#endif
        }
        pw_cleanup(1);
        exit(1);
}

/*
 *      motd - issue 'message of the day'
 */
void motd(fn, complaint)
char    *fn,                    /* Name of file to present */
        *complaint;             /* Complaint if missing */
{
        char    cmdbuf[BUFSIZ];         /* Buffer to build command in */

        if (access(fn, 0) < 0) {
                if (complaint)
                        printf("%s\n", complaint);
                return;
        }
        if (isatty(0))
#ifdef  SYSV
                (void) sprintf(cmdbuf, "pg -n -s %s", fn);
#else
                (void) sprintf(cmdbuf, "more -d %s", fn);
#endif
        else
                (void) sprintf(cmdbuf, "cat %s", fn);

        if (fork() == 0) {
                (void) setgid(getgid());
                (void) setuid(getuid());
                (void) system(cmdbuf);
                exit(0);
        }
        (void) wait((int *)0);          /* "Wrong" for BSD, right for SYS V */
}

/*
 *      checktty - Attempt to check against being pipe-fed
 */
void checktty()
{
        char    *stdin_tty,     /* ttyname(0) */
                *stdout_tty,    /* ttyname(1) */
                *t;             /* Temp */

        if (!isatty(0)) {
                if (from_prog == 0)
                        quit(0, "Input not a tty.\n");
                if (lseek(0, 0L, 1) < 0) {
                        if (errno != ESPIPE)
                                quit(0, "Input not a tty or pipe.\n");
                        else
                                return;
                }
        }
        from_prog = 0;          /* Stdin is a tty - behave normal */
        stdin_tty = ttyname(0);
        if (stdin_tty == NULL || *stdin_tty == 0)
                quit(0, "Cannot get name (stdin).\n");
        t = malloc(strlen(stdin_tty) + 1);
        if (t == NULL)
                quit(1, "Cannot allocate temp memory.\n");
        (void) strcpy(t, stdin_tty);
        stdin_tty = t;

        stdout_tty = ttyname(1);
        if (stdout_tty == NULL || *stdout_tty == 0)
                quit(0, "Cannot get name (stdout).\n");
        if (strcmp(stdin_tty, stdout_tty))
                quit(0, "Input and output are not the same tty.\n");
        free(stdin_tty);
}

/*
 *      catchit - tty interrupt catcher
 */
void catchit()
{
        fixtty();
        pw_cleanup(1);
        quit(0, "\nInterrupted; changes discarded.\n");
}


#if     defined(SYSV)
#       include <termio.h>              /* Vanilla SV termio */
        struct termio saved_tty_mode;
#endif

#if     defined(SUNOS4)
#       include <sys/termios.h>         /* SUN OS 4.0 termio */
#define TCGETA  TCGETS
#define TCSETA  TCSETS
        struct termios saved_tty_mode;
#endif

#if     !defined(SUNOS4) && !defined(SYSV)
#       include <sgtty.h>               /* BSD tty */
        struct sgttyb saved_tty_mode;
        int     saved_local_flags;
#endif
char    saves_valid  = 0;               /* Are the saved values valid? */

/*
 *      savetty - save current terminal settings
 */
void savetty()
{
#if     defined(SYSV) || defined(SUNOS4)
        (void) ioctl(0, TCGETA, &saved_tty_mode);
#else
        (void) ioctl(0, TIOCGETP, &saved_tty_mode);
        (void) ioctl(0, TIOCLGET, &saved_local_flags);
#endif
        saves_valid++;
}

/*
 *      fixtty - restore saved terminal settings
 */
void fixtty()
{
        if (saves_valid) {
#if     defined(SYSV) || defined(SUNOS4)
                (void) ioctl(0, TCSETA, &saved_tty_mode);
#else
                (void) ioctl(0, TIOCSETP, &saved_tty_mode);
                (void) ioctl(0, TIOCLSET, &saved_local_flags);
#endif
        }
}


/*
 * getinput - get input safely from the keyboard with default
 */
void getinput(Buf, Size, Default)
char 	*Buf;	/* input buffer */
int	Size;	/* size of the the buffer */
char 	*Default;	/* default string to use if no input */
{
	fflush(stdout);	/* just in case... */
        if (fgets(Buf, Size-1, stdin) != NULL) {
        	Buf[Size-1] = 0;           /* make sure buffer is null-term */
		if (Buf[0] != 0 && Buf[strlen(Buf) - 1] == '\n')
			Buf[strlen(Buf) - 1] = 0;	/* strip lf */
		if (Buf[0] == 0) {	/* use default */
			strncpy(Buf, Default, Size-1);
			Buf[Size-1] = 0;	/* null-term */
		}
	} else 
		quit(0, "Got end of input - aborting\n");
}


#ifdef  XGETPASS
/*
 *      The system getpass() throws away all but the first 8 characters
 *      of a password string.  If this isn't enough for you, use this
 *      routine instead.  This code assumes that stdin is the terminal.
 */
char    *
getpass(prompt)
char    *prompt;
{
#if     defined(SYSV)
        struct termio   saved,          /* Saved tty characteristics */
                        noecho;         /* No-echo tty characteristics */
        char    *strchr();
#endif
#if     defined(SUNOS4)
        struct termios  saved,          /* Saved tty characteristics */
                        noecho;         /* No-echo tty characteristics */
#else
        struct sgttyb   saved,          /* Saved tty characteristics */
                        noecho;         /* No-echo tty characteristics */
#endif
        static char     ib[BUFMAX];     /* Input buffer */
        char    *rc;                    /* Temp */

#if     defined(SYSV) || defined(SUNOS4)
        (void) ioctl(0, TCGETA, &saved);
        noecho = saved;
        noecho.c_lflag &= ~ECHO;
        (void) ioctl(0, TCSETA, &noecho);
#else
        (void) ioctl(0, TIOCGETP, &saved);
        noecho = saved;
        noecho.sg_flags &= ~ECHO;
        (void) ioctl(0, TIOCSETP, &noecho);
#endif
        fprintf(stderr, "%s", prompt);
        fflush(stderr);
	getinput(ib, sizeof(ib), "");
        putc('\n', stderr);
        fflush(stderr);

#if     defined(SYSV) || defined(SUNOS4)
        (void) ioctl(0, TCSETA, &saved);
#else
        (void) ioctl(0, TIOCSETP, &saved);
#endif
        return(ib);
}
#endif

#ifdef  XPUTPWENT
/*
 *      putpwent - replacement for the System V routine
 *              This writes the "standard" passwd file format.
 */
void putpwent(p, f)
struct passwd   *p;     /* Passwd entry to put */
FILE    *f;             /* File pointer */
{
#ifdef  UNSIGNED_UID
        fprintf(f, "%s:%s:%u:%u:%s:%s:%s\n",
#else
        fprintf(f, "%s:%s:%d:%d:%s:%s:%s\n",
#endif
                p->pw_name, p->pw_passwd, p->pw_uid, p->pw_gid,
                p->pw_gecos, p->pw_dir, p->pw_shell);
}
#endif

#ifdef  XFGETPWENT
/*
 *      fgetpwent() - read passwd(5) entry from a file
 *              This reads the "standard" passwd file format.
 */
struct passwd *
fgetpwent(f)
FILE    *f;                     /* Pointer to open passwd format file */
{
        static struct passwd    pwdata; /* Return data */
        static char     ibuf[BUFSIZ];   /* Input and return data buffer */
        char            *p;             /* ACME Pointer Works, Inc */

        bzero((char *)&pwdata, sizeof(pwdata));
        pwdata.pw_name = pwdata.pw_passwd = pwdata.pw_comment =
        pwdata.pw_gecos = pwdata.pw_dir = pwdata.pw_shell = "";

        if (fgets(ibuf, sizeof(ibuf), f) == NULL)
                return(0);
        if ((p = index(ibuf, '\n')) == 0)               /* Zap newline */
                quit(1, "Ill-formed passwd entry \"%s\".\n", ibuf);
        else
                *p = 0;
#define skipc while (*p && *p != ':' && *p != '\n') ++p; if (*p) *p++ = 0
        p = ibuf;
        pwdata.pw_name = p;     skipc;
        pwdata.pw_passwd = p;   skipc;
        pwdata.pw_uid = atoi(p); skipc;
        pwdata.pw_gid = atoi(p); skipc;
        pwdata.pw_gecos = p;    skipc;
        pwdata.pw_dir = p;      skipc;
        pwdata.pw_shell = p;
        return(&pwdata);
#undef  skipc
}
#endif

#ifdef  SYSV
/*
 *      rename - replacement for the 4.2/4.3 BSD rename system call
 */
int rename(src, dst)
char    *src,           /* Source path */
        *dst;           /* Destination path */
{
        if (unlink(dst) < 0) {
                if (errno != ENOENT)
                        return(-1);
        }
        if (link(src, dst) < 0)
                return(-1);
        return(unlink(src));
}
#endif

/*
 *      punt() - run another program to do what we don't do
 */
void punt(prog)
char    *prog;          /* Program to run */
{
        (void) setgid(getgid());
        (void) setuid(getuid());
        (void) execlp(prog, prog, 0);
        perror(prog);
        exit(1);
}
/*              End npasswd.c           */
