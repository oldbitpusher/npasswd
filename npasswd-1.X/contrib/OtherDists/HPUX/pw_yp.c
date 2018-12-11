
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
 *	pw_yp - Routines for dealing with SUN Yellow Pages password files
 *
 *	This code can update local password file, can cause rebuilding of
 *	local YP maps and can use yppasswdd(8) to change YP passwords.
 *
 *	Must be linked with -lrpcsvc
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
#include <pwd.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef lint
static char sccsid[] = "@(#)pw_yp.c	1.6 11/14/89 (cc.utexas.edu)";
#endif

#define	NONE	-1	/* YP not active */
#define	NOT	0	/* YP active - we are not master */
#define	IS	1	/* YP active - we have the password file */

#define	SLOP	128	/* Size difference tolerated old <> new passwd file */

typedef struct passwd	passwd;
typedef	struct passwd	*passwdp;

static passwd	theUser,	/* User being changed */
		Me;		/* User invoking passwd */
static int	myuid,		/* Uid of invoker */
		mytempfile = 0;	/* Does PASSWD_TEMP belong to me? */
static char	ypmaster[BUFSIZ];	/* Name of the YP master */

/*
 *	File names
 */
#ifndef	PASSWD_FILE
#define	PASSWD_FILE	"/etc/passwd"
#endif
 
#ifndef	PASSWD_SAVE
#define	PASSWD_SAVE	"/etc/opasswd"
#endif

#ifndef	PASSWD_TEMP
#define	PASSWD_TEMP	"/etc/ptmp"
#endif

#define	PASSWD_MODE	0644
 
#ifdef	DEBUG
static char	*passwdtemp = "./etc_ptmp",		/* Temp file */
		*passwdfile = "./etc_passwd",		/* Password file */
		*savefile = "./etc_opasswd";		/* Save file */
#else
static char	*passwdtemp = PASSWD_TEMP,
		*passwdfile = PASSWD_FILE,
		*savefile = PASSWD_SAVE;
#endif

extern int	errno;

char	*getlogin(),
	*crypt();

/*
 *	pw_initialize - set up
 */
pw_initialize()
{
	passwdp	me;			/* Passwd for invoker */
	char	*myname = getlogin();	/* Invoker login name */

#ifdef	DEBUG
	setpwfile(passwdfile);
#endif
	myuid = getuid();
	if (myname == NULL || *myname == NULL)
		quit(1, "Cannot get user name.\n");

	if ((me = getpwnam(myname)) == NULL)
		quit(1, "Cannot get user identification.\n");

	_cppasswd(me, &Me);
	return(1);
}

/*
 *	pw_getuserbyname - get password
 *
 *	Returns 1 if passwd found for <name>
 *		0 otherwise
 */
pw_getuserbyname(name, passwdb)
char	*name,		/* User name */
	*passwdb;	/* Where to stuff password */
{
	passwdp	p;	/* Temp */

	if ((p = getpwnam(name)) == NULL)
		return(0);
	_cppasswd(p, &theUser);
	(void) strcpy(passwdb, p->pw_passwd);
	return(1);
}

/*
 *	pw_permission - check password change permission
 *
 *	Returns 1 if password can be changed
 *		0 if not
 */
pw_permission()
{
	/*
	 * Is this my password or someone elses?
	 */
	if (strcmp(Me.pw_name, theUser.pw_name) && myuid)
		return(0);

	/*
	 * If on a YP client, root cannot change another
	 * users' password via yppasswd(), since we can't
	 * get a plain text password to pass to ypasswd().
	 */
	if (myuid == 0 && is_yp_master() == NOT) {
		FILE	*pf;
		passwdp px,		/* Password file traversal */
			fgetpwent();
		int	rc = 0;

		if ((pf = fopen(passwdfile, "r")) == NULL)
			quit(1, "Cannot open password file.");
		/*
		 * Scan local password file, looking for user
		 * Cannot use getpwnam() because it will use YP - I want to know
		 * if the user's password file entry is >>local<<
		 */
		while ((px = fgetpwent(pf)) != NULL) {
			if (strcmp(px->pw_name, theUser.pw_name) == 0)
				rc = 1;
		}
		fclose(pf);
		if (rc)
			return(1);
		else
			quit(0, "Password for %s can only be changed on YP server %s.\n",
				theUser.pw_name, ypmaster);
	}

	/*
	 * Other checks can be put here to determine if the invoker should
	 * be allowed to change this password.
	 */
	return(1);
}

/*
 *      pw_compare - compare old and new passwords
 *
 *      Returns 1 if check = new, 0 if not
 */
pw_compare(current, new)
char	*current,		/* Current pw (encrypted) */
	*new;			/* check pw (plain) */
{
	/* Put other administrative checks here */
	return(!strcmp(current, crypt(new, current)));
}

/*
 *      pw_check - sanity check password.  Right now just calls
 *              the password check program
 *
 *      Returns 1 if password is ok to use, 0 otherwise
 */
pw_check(pwd)
char	*pwd;
{
	return(checkpasswd(theUser.pw_uid, pwd));
}

static char *yperr =
"YP password change failed.\n\
YP server %s may not be running ypassswdd.\n";

/*
 *      pw_replace - replace password in passwd file 
 */
pw_replace(newpwd, curpwd)
char	*newpwd,		/* New password (plain) */
	*curpwd;		/* Old password (plain) */
{
	passwdp px,		/* Password file traversal */
		fgetpwent();
	long    oldsigs,	/* Old signal mask */
		blocksigs = sigmask(SIGINT) |	/* Sigs to block */
			    sigmask(SIGQUIT) |
			    sigmask(SIGTSTP);
	FILE	*tf,		/* New password file output */
		*pf;		/* Current password file input */
	int	fd,		/* Temp file create fd */
		islocal = 0;	/* Is user in local password file */
	struct stat	oldstat,	/* Old password file stat */
			newstat;	/* New password file stat */

	if ((pf = fopen(passwdfile, "r")) == NULL)
		quit(1, "Cannot open password file.");
	/*
	 * Scan local password file, looking for user
	 * Cannot use getpwnam() because it will use YP - I want to know
	 * if I have to change a >>local<< password file.
	 */
	while ((px = fgetpwent(pf)) != NULL) {
		if (strcmp(px->pw_name, theUser.pw_name) == 0) {
			islocal++;
			break;
		}
	}
	rewind(pf);

	/*
	 * If the user was not in the local password file, use RPC
	 * to update the Yellow Pages password file.
	 */
	if (islocal == 0) {
		if (is_yp_master() == NOT) {
			int	tries,		/* Count of yppasswd tries */
				rc;		/* yppasswd() return code */

			if (curpwd[0] == 0)
				quit(0, "Cannot change YP password without old password.\n");
			/*
			 * MUST crypt using old password salt so that
			 * yppasswdd can verify the current password.
			 */
			theUser.pw_passwd = crypt(newpwd, theUser.pw_passwd);
#ifdef	DEBUG
			printf("yppasswd(%s, %s)\n", curpwd, theUser.pw_passwd);
#else
#define	NTRIES	3
			for (tries = 0; tries < NTRIES; tries++) {
				if ((rc = yppasswd(curpwd, &theUser)) == 0)
					break;
			}
#undef	NTRIES
			if (rc)
				quit(1, yperr, ypmaster);
#endif
				return;
		}
		else	/* User not in local passwd, and not in YP passwd */
			quit(1, "User %s missing from password file.\n",
				theUser.pw_name);
	}

	/*
	 * There is a local password file to change
	 */
	(void) umask(0);
	(void) fstat(fileno(pf), &oldstat);
	fd = open(passwdtemp, O_WRONLY|O_CREAT|O_EXCL, PASSWD_MODE);
	if (fd < 0) {
		if (errno == EEXIST)
			quit(0, "Password file busy - try again.\n");
		perror("Tempfile create");
		quit(1, "Cannot create temp file.\n");
	}
	mytempfile = 1;
	if ((tf = fdopen(fd, "w")) == NULL)
		quit(1, "Cannot fdopen temp file.");

	oldsigs = sigblock(blocksigs);
	while ((px = fgetpwent(pf)) != NULL) {
		if (px->pw_name == 0 || px->pw_name[0] == 0) /* Sanity check */
			continue;
		if (strcmp(px->pw_name, theUser.pw_name) == 0) {
			char	salt[4];	/* Password encryption salt */

			randomstring(salt, sizeof(salt));
			theUser.pw_passwd = crypt(newpwd, salt);
			px = &theUser;
		}
		(void) putpwent(px, tf);
	}
	(void) fflush(tf);			/* Force buffers empty */
	(void) fstat(fileno(tf), &newstat);	/* Get size */
	(void) fclose(tf);
	(void) fclose(pf);

	/*
	 * Check if the new password file is complete.  Since the encrypted
	 * password is of a fixed length, the new file should be roughly
	 * the same size as the old one.
	 */
	if (newstat.st_size < (oldstat.st_size - SLOP))
		quit(1,
		"New password file appears to be incomplete - aborting.\n");

	if (rename(passwdfile, savefile) < 0) {
		perror("Password file save");
		(void) unlink(passwdtemp);
		quit(1, "Can't save password file");
	}
	if (rename(passwdtemp, passwdfile) < 0) {
		perror("Password file replace");
		(void) unlink(passwdtemp);
		(void) link(savefile, passwdfile);
		quit(1, "Can't replace password file");
	}
	if (is_yp_master() == IS)
		updateyp();
	(void) sigsetmask(oldsigs);
}

/*
 *      pw_cleanup - clean up after myself
 */
pw_cleanup(code)
int	code;		/* 0 for normal, 1 for abort */ /*NOTUSED*/
{
	if (mytempfile)
		(void) unlink(passwdtemp);
}

/*
 *      _newstr - copy string into new storage
 */
static char *
_newstr(s)
char	*s;		/* String to copy */
{
	register char	*t;	/* Temp */
	char	*malloc();

	if (s == NULL)
		return(0);
	t = malloc(strlen(s) + 1);
	if (t == NULL)
		quit(1, "No memory.\n");
	(void) strcpy(t, s);
	return(t);
}

/*
 *	 _cppasswd - copy a passwd structure
 */
static
_cppasswd(f,t)
passwdp	f,		/* From */
	t;		/* To */
{
	*t = *f;
	t->pw_name = _newstr(f->pw_name);
	t->pw_passwd = _newstr(f->pw_passwd);
	t->pw_comment = _newstr(f->pw_comment);
	t->pw_gecos = _newstr(f->pw_gecos);
	t->pw_dir = _newstr(f->pw_dir);
	t->pw_shell = _newstr(f->pw_shell);
}

/*
 *	is_yp_master - Figure out whether we are running on the Yellow Pages
 *		master for the password file maps.
 *
 *	Returns:
 *		IS if we are the master
 *		NOT if we are not the master
 *		NONE if there is no master
 */
	/* Put your local version of PATH in the next line */
char	*ypwhich = 
	"PATH=/bin:/usr/bin; export PATH; ypwhich -m passwd 2>/dev/null";
	
is_yp_master()
{
	static char	known = 0,	/* We've been here */
			answer = NOT;	/* ...and this is the answer */
	char	hostname[32];		/* Our host name */
	char	*p;			/* Scratch */
	FILE	*ypx,			/* Pipe reader */
		*popen();
	char	*index();
	if (known)
		return(answer);
	(void) gethostname(hostname, sizeof(hostname));
	ypx = popen(ypwhich, "r");
	if (ypx == NULL)
		return(NONE);
	ypmaster[0] = 0;
	(void) fgets(ypmaster, sizeof(ypmaster), ypx);
	(void) pclose(ypx);
/*#ifdef HPUX*/
	/*Aif (p = strchr(ypmaster, '\n')) *p = 0;*/
	if (p = index(ypmaster, '\n')) *p = 0;
	known++;
	if (ypmaster[0] == 0) 	/* Null response - assume YP not running */
		return(answer = NONE);
	/* Compare the first component of hostname & yp master */
/*#ifdef HPUX*/
	/*if (p = strchr(ypmaster, '.')) *p = 0;*/
	/*if (p = strchr(hostname, '.')) *p = 0;*/
	if (p = index(ypmaster, '.')) *p = 0;
	if (p = index(hostname, '.')) *p = 0;
	if (strcmp(ypmaster, hostname) == 0)
		return(answer = IS);
	return(answer);
}

/*
 *	An example sh(1) script to update YP password map
 */
char	*ypcmd =
	"(ypdirs='/var/yp /etc/yp'\n\
	for d in $ypdirs; do\n\
		if [ -d $d ]; then\n\
			cd $d; exec make passwd\n\
		fi\n\
	done\n\
	echo 'passwd: Cannot rebuild YP maps!' 1>&2\n\
	false) >/dev/null &\n";

/*
 *	updateyp - update local YP maps
 */
updateyp()
{
	/*
	 * This machine is the YP master for passwd - invoke something
	 * to update the YP maps
	 */

setuid(geteuid());

#ifdef	DEBUG
	printf("updateyp: %s", ypcmd);
#endif
	(void) system(ypcmd);
}
