/*
 * Copyright (C) 2002  The University of Texas at Austin ("U. T. Austin").
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  Contact: npasswd-support@www.utexas.edu
 *
 */

/*
 *	This program duplicates the manual page behavior of the 4.XBSD
 *	passwd(1) command.  It can be configured for use with a variety
 *	of passwd systems (/etc/passwd, /etc/shadow, databases).
 */
#include "npasswd.h"
#include "pw_svc.h"

#ifndef lint
static char sccsid[] = "$Id: main.c,v 1.49 2002/10/02 15:53:18 clyde Exp $ (cc.utexas.edu) %P%";
#endif

/*
 * Global variables
 */
public char	*ConfigFile = CONFIG_FILE;	/* Configuration file */
public char	*Switches[256];			/* Command line switch values */
public char	*XSwitches[256];		/* 'X' Command switches */
private	struct mpasswd	*TargetPW,		/* Target of change */
			*CallerPW;		/* Who wants to make change */
public Uid_t	CallerUid;			/* Cached getuid() value */

private enum { PASSWD, CHFN, CHSH } what_to_do;	/* What to do */

private char	*ProgramName;			/* Program name */
private char	*Usage = "Usage: %s\n\
	Generic options:\n\
	[-Xc]		Show configuration settings\n\
	[-XC config-file] Use alternate configuration file\n\
	[-XD level]	Set debug level\n\
	[-Xf]		Change finger name\n\
	[-XF]		Suppress new password checking (root only)\n\
	[-Xh]		Help\n\
	[-XA]		Always ask for current password (root only)\n\
	[-XO]		Allow one attempt to set new password (root only)\n\
	[-XI]		Read passwords from standard input (root only)\n\
	[-Xs]		Change login shell\n\
	[-XS]		Change login shell without verfication (root only)\n\
	[-XV]		Print version and patch information\n";

/*
 * Program debug level table
 */
private debug_table npasswd_debug[] = {
	{ "none",	DB_NONE,	"Debugging off" },
	{ "verbose",	DB_VERBOSE,	"Verbose" },
	{ "lookup",	DB_LOOKUP,	"User lookup" },
	{ "update",	DB_UPDATE,	"User update" },
	{ "config",	DB_CONFIG,	"Configuration processing" },
	{ "pwcheck",	DB_PWCHECK,	"Password checking" },
	{ "detail",	DB_DETAIL,	"Detailed debugging" },
	{ "all",	DB_ALL,		"All debugging" },
	{ 0 },
};

private Signal_t catchit _((int));		/* Signal catcher */
private void	checktty();
private void	os_init _((int, char **, char **));
private void	print_os_env();
private void	process_arguments _((int, char **, char **));

/*
 *	main program - passwd/chfn/chsh
 */
main(argc, argv, envp)
	int	argc;
	char	**argv;
	char	**envp;		/* Not ANSI? */
{
	char	*temp;			/* ACME Scratch Variables */
	char	CallerLogin[STRINGLEN];	/* User name temp */
	struct passwd	*pwtemp;	/* Lookup temp */
	extern int	optind;

#ifdef	DEBUG_DEFAULT
	init_debug(DEBUG_DEFAULT);
#else
	init_debug(DB_NONE);
#endif
	CallerUid = getuid();		/* Get uid of invoker */
	set_die_callback(pw_cleanup);
	process_arguments(argc, argv, envp); /* Process command line */

	init_pwsvc(argc, argv, Switches);
	checktty();
	term_save();
	temp = getlogin();
	if (temp == 0 || *temp == '\0') {	/* Can't get login name */
		static char savedname[STRINGLEN];

		if ((pwtemp = getpwuid(CallerUid)) == ((struct passwd *)NULL))
			logdie("Cannot get your login name.\n");
		(void) strncpy(savedname, pwtemp->pw_name, sizeof(savedname));
		temp = savedname;
	}
	(void) strncpy(CallerLogin, temp, sizeof(CallerLogin));
	if ((pwtemp = getpwnam(CallerLogin)) == NULL)
		logdie("Cannot get user identification from name.\n");
	if (pwtemp->pw_uid != CallerUid && CallerUid) {
#if	(CDEBUG >= CDEBUG_SYSTEM)
		warn("Login name \"%s\" does not belong to uid %d\n",
			pwtemp, CallerUid);
#endif
#ifdef	PARANOID_UIDCHECK
		logdie("Login name \"%s\" does not belong to uid %d\n",
			pwtemp, CallerUid);
#endif
	}
	CallerPW = (struct mpasswd *)calloc(sizeof(struct mpasswd), 1);
	if (!CallerPW)
		logdie("Cannot allocate memory to store caller information\n");
	(void) copypwent(pwtemp, &CallerPW->pw);

	/*
	 * Set up signal handling
	 */
#if	(CDEBUG < CDEBUG_SYSTEM)
	(void) signal(SIGHUP, catchit);
	(void) signal(SIGINT, catchit);
	(void) signal(SIGQUIT, catchit);
	(void) signal(SIGTERM, catchit);
#endif
#ifdef	LOG_AUTH
	openlog(ProgramName, LOG_PID, LOG_AUTH);
#else
	openlog(ProgramName, LOG_PID);
#endif
	configure(ConfigFile, 0);
	pw_initialize(argc, argv);

	if (argv[optind]) {
		if ((TargetPW = pw_getuserbyname(argv[optind])) == NULL)
			die("No such user %s\n", argv[optind]);
	}
	else {
		if ((TargetPW = pw_getuserbyname(CallerLogin)) == NULL)
			logdie("Cannot get your user information.\n");
	}

#if	(CDEBUG <= CDEBUG_SYSTEM)
	if (geteuid())
		die("Permission denied.\n");
#endif
#ifdef	NICE_LEVEL
	(void) nice(NICE_LEVEL);
#endif
	switch (what_to_do) {
	case PASSWD:
		passwd(TargetPW, CallerPW);
		break;
	case CHSH:
#ifdef	DENY_CHSH
		die("Chsh not available.\n");
#else
		chsh(TargetPW, CallerPW);
#endif
		break;
	case CHFN:
#ifdef	DENY_CHFN
		die("Chfn not available.\n");
#else
		chfn(TargetPW, CallerPW);
#endif
		break;
	}
	pw_cleanup(0);
	exit(0);
	return(0);		/* Make ANSI C happy */
}

/*
 * motd
 *	Issue 'message of the day'
 * Usage
 *	(void) motd(file, error-message);
 */
public void
motd(fn, complaint)
	char	*fn,		/* File to present */
		*complaint;	/* Complaint if missing */
{
	char	inbuf[TMPBUFSIZ];	/* ACME Scratch Storage */
	FILE	*in;			/* ACME Scratch Storage */

	if ((in = fopen(fn, "r")) == NULL) {
		if (complaint)
			printf("%s\n", complaint);
		return;
	}
	pager(in);
	(void) fclose(in);
}

/*
 * checktty
 *	Check if standard input has been redirected. This is considered bad.
 * Usage
 * 	(void) checktty();
 * Errors
 *	Aborts upon error or ttyname(stdin) != ttyname(stdout)
 */
private void
checktty()
{
	char	*stdin_tty,	/* ttyname(0) */
		*t;		/* Temp */

	if (!isatty(fileno(stdin))) {
		if (!XSwitches[Xsw_UseStdin])
			die("Input not a tty.\n");
		return;
	}
	XSwitches[Xsw_UseStdin] = 0;	/* Stdin is a tty - behave normal */
	t = ttyname(fileno(stdin));
	if (t == NULL || *t == 0)
		die("Cannot get name for input.\n");
	stdin_tty = strdup(t);

	t = ttyname(fileno(stdout));
	if (t == NULL || *t == 0)
		die("Cannot get name for output.\n");
	if (strcmp(stdin_tty, t))
		die("Input and output are not the same tty.\n");
	free(stdin_tty);
}

/*
 * Command line option defines.  These are used only in this module.
 */
#define	OPTIONS_GENERIC "X:"		/* Baseline command line options */

#ifdef	OS_SUNOS_4
# define	OPTIONS_DEFER	"a"		/* SunOS 4 options punted */
# define	OPTIONS_OS 	"fsden:x:"	/* SunOS 4 options supported */
# define	OPTIONS_IGNORE 	"F:ly"		/* SunOS 4 options to ignore */
#endif

#ifdef	OS_SUNOS_5
# define	OPTIONS_DEFER	"adfhln:w:x:s:"	/* SunOS 5 options punted */
# define	OPTIONS_OS 	"egr:"		/* SunOS 5 options supported */
# define	OPTIONS_IGNORE 	"D:"		/* SunOS 5 options to ignore */
#endif

#ifdef OS_HPUX
# define	OPTIONS_OS "den:x:"		/* HP-UX options supported */
#endif

#ifdef OS_DEC_OSF
# define	OPTIONS_OS "fs"			/* OSF options supported */
#endif

#ifdef OS_AIX
# define	OPTIONS_OS "fs"			/* AIX options supported */
#endif

/*
 * process_arguments
 *	Process command line arguments
 * Usage
 *	(void) process_arguments(argc, argv, envp);
 * Effects
 *	Sets lots of global variables
 *
 * Notes
 *	Npasswd can't do everything, so some command line options are
 *	deferred to the vendor program (stashed in SAVE_DIR).
 *	The encounter of any deferred option (in DEFER_OPTIONS), causes
 *	invocation of the vendor program.
 */
private void
process_arguments(argc, argv, envp)
	int	argc;
	char	**argv;
	char	**envp;
{
	char	opts[STRINGLEN];	/* Options string for getopt */
	int	opt;			/* Option processing temp */
	char	*pn;			/* Program name from argv[0] */
#ifdef	OPTIONS_DEFER
	char	*d_argv[256];		/* Arguments for deferred program */
	int	d_argc = 0;		/* Argument counter */
#endif
	extern char	*optarg;	/* From getopt() */
	extern int	optind;		/* From getopt() */

	/*
	 * Build option string for getopt()
	 */
	(void) strcpy(opts, OPTIONS_GENERIC);	/* Start with generic options */
#ifdef	OPTIONS_OS
	(void) strcat(opts, OPTIONS_OS);	/* Add platform options we do */
#endif
#ifdef	OPTIONS_DEFER
	zeromem(d_argv, sizeof(d_argv));
	(void) strcat(opts, OPTIONS_DEFER);	/* Add platform options we punt */
#endif
#ifdef	OPTIONS_IGNORE
	(void) strcat(opts, OPTIONS_IGNORE);	/* Add platform options we ignore */
#endif
	what_to_do = PASSWD;
	ProgramName = "passwd";

	if (pn = strrchr(argv[0], '/'))		/* Invoked with what name? */
		pn++;
	else
		pn = argv[0];

	if (instring(pn, "chsh")) {
		what_to_do = CHSH;
		ProgramName = "chsh";
	}
	if (instring(pn, "chfn")) {
		what_to_do = CHFN;
		ProgramName = "chfn";
	}
	set_debug_tag(ProgramName);

	os_init(argc, argv, envp);		/* Call platform init code */

	zeromem(Switches, sizeof Switches);
	zeromem(XSwitches, sizeof XSwitches);

	while ((opt = getopt(argc, argv, opts)) != EOF) {
		switch (opt) {
#ifdef	OS_SUNOS_4
		/*
		 * SunOS 4 options
		 */
		case 'a':
			Switches[(char)opt] = "on";
			break;
		case 'f':		/* Change finger */
			what_to_do = CHFN;
			break;
		case 's':		/* Change shell */
			what_to_do = CHSH;
			break;
		case 'l':
			Switches[(char)opt] = "on";
			break;
		case 'y':
			Switches[(char)opt] = "on";
			break;
		case 'd':
			Switches[(char)opt] = "on";
			break;
		case 'e':
			Switches[(char)opt] = "on";
			break;
		case 'n':
			Switches[(char)opt] = strdup(optarg);
			break;
		case 'x':
			Switches[(char)opt] = strdup(optarg);
			break;
		case 'F':
			printf("Option \"-F\" not supported.\n");
			exit(1);
#endif	/* OS_SUNOS_4 */
#ifdef	OS_SUNOS_5
		/*
		 * SunOS 5 options
		 */
		case 'e':		/* Change shell */
			what_to_do = CHSH;
			break;
		case 'g':		/* Change finger info */
			what_to_do = CHFN;
			break;
		case 'r':		/* Select service */
			Switches[(char)opt] = strdup(optarg);
			break;

#endif	/* OS_SUNOS_5 */
#ifdef OS_HPUX
		/*
		 * HP-UX code from mstute@compucom.com (Mike Stute)
		 */
		case 'n':
			Switches[(char)opt] = strdup(optarg);
			break;
		case 'x':
			Switches[(char)opt] = strdup(optarg);
			break;
		case 'd':
			Switches[(char)opt] = "on";
			break;
		case 'e':
			Switches[(char)opt] = "on";
			break;
#endif	/* OS_HPUX */
		case 'X': {		/* -X [Extended options] */
			char	*op = optarg;
		
			switch (*op) {
			case Xsw_Chfn:
				what_to_do = CHFN;	/* chfn mode */
				break;

			case Xsw_Chsh:			/* chsh mode */
				what_to_do = CHSH;
				break;

			case Xsw_ChshSpecial:		/* chsh (no check) */
				if (CallerUid)
					die("Option \"-X%s\" reserved for super-user.\n", Xsw_ChshSpecial);
				XSwitches[Xsw_ChshSpecial] = "on";
				what_to_do = CHSH;
				break;

			case Xsw_AskOnce:	/* Try once to read password */
				XSwitches[Xsw_AskOnce] = "on";
				break;

			case Xsw_AskAlways:		/* Always ask for pw */
				XSwitches[Xsw_AskAlways] = "on";
				break;

			case Xsw_ShowConfig:		/* Show config */
				XSwitches[Xsw_ShowConfig] = "on";
				break;

			case Xsw_CheckConfig:		/* Check config file */
				(void) setgid(getgid()); /* Give away */
				(void) setuid(getuid()); /* privs */
				configure(++op, 1);
				printf("Configuration file \"%s\" OK\n", op);
				exit(0);
				break;

			case Xsw_SetDebug:		/* Debug level */
				set_debug(++op, npasswd_debug);
				printf("Debug level = %d\n", get_debug());
				printf("Version: %s\nPatch: %s\n%s",
					npasswd_version,
					npasswd_patchlevel,
					build_info);
				print_os_env();
				break;

			case Xsw_ForcePWChange:		/* Force change */
				if (CallerUid)
					die("Option \"-X%s\" reserved for super-user.\n", Xsw_ForcePWChange);
				XSwitches[Xsw_ForcePWChange] = "on";
				break;

			case Xsw_UseStdin:		/* Read from stdin */
				if (CallerUid)
					die("Option \"-X%s\" reserved for super-user.\n", Xsw_UseStdin);
				XSwitches[Xsw_UseStdin] = "on";
				break;

			case Xsw_ShowVersion:
				printf("Version: %s\nPatch level: %s\n%s\n",
					npasswd_version, npasswd_patchlevel,
					build_info);
				exit(0);

			case Xsw_Help:
				{
				debug_table *dt = npasswd_debug;

				printf(Usage, ProgramName);
				printf("Debug levels (-XD...):\n");
				for (; dt->name; dt++)
					printf("\t%s\t%s\n", dt->name, dt->help);
				exit(0);
				}
				/*NOTREACHED*/
				break;
			}	/* switch */
		} /* case 'X' */
		break;

		/* Switches of OPTIONS_IGNORE are quietly not dealt with */

#ifdef	OPTIONS_DEFER
		default: {
			/*
			 * If this option should be deferred, add the switch
			 * and possbily the next argument to the argument list
			 */
			char *xopt;
			if (xopt = strchr(OPTIONS_DEFER, (char )opt)) {
				char	temp[STRINGLEN];

				(void) sprintf(temp, "-%c", (char )opt);
				if (d_argc == 0) d_argc++; /* leave space */
				d_argv[d_argc++] = strdup(temp);
				if (*++xopt == ':')
					d_argv[d_argc++] = strdup(optarg);
			}
			break;
		}
#endif
		} /* switch */
	} /* for */

#ifdef	OPTIONS_DEFER
	if (d_argc) {
		/*
		 * Punt to external program
		 */
		while (argv[optind])	/* Copy remaining arguments */
			d_argv[d_argc++] = argv[optind++];
		punt(d_argv, envp);
		/*NOTREACHED*/
	}
#endif
}

/*
 * punt
 *	Execute vendor program to do something that we don't do.
 * Usage
 *	punt(arg-list, environmnet-list)
 */
private
punt(argv, envp)
	char	**argv;		/* Arguments */
	char	**envp;		/* Environment */
{
	char	xpath[MAXPATHLEN];

	if (access(SAVED_BIN, 0) < 0)
		logdie("Cannot find saved '%s'\n", ProgramName);
	
	(void) sprintf(xpath, "%s/%s", SAVED_BIN, ProgramName);
	if (access(xpath, 0) < 0)
		logdie("Cannot find '%s'\n", xpath);

	(void) setgid(getgid());
	(void) setuid(CallerUid);
	argv[0] = ProgramName;
	if (get_debug() >= DB_UPDATE) {
		char	**v = argv;

		printf("punt: %s ", xpath);
		for (; *v; v++) {
			printf("'%s' ", *v);
		}
		printf("\n");
	}
#if	(CDEBUG < CDEBUG_SYSTEM)
	(void) execve(xpath, argv, envp);
	/*NOTREACHED*/
	logdie("(punt) Exec of '%s' failed\n", xpath);
	/*NOTREACHED*/
#else
	printf("punt exec\n");
	exit(0);
#endif
}

/*
 * catchit
 *	Generic signal handler
 * Usage
 *	catchit(signal-number)
 * Effects
 #	Aborts with error message
 */
private Signal_t
catchit(signo)
	int	signo;
{
	term_restore();
	pw_cleanup(signo);
	die("\nInterrupted; changes discarded.\n");
}

#ifdef	I_SYS_RESOURCE
#include <sys/resource.h>
#endif
/*
 * os_init
 *	Operating system specific initialization
 * Effects
 *	Clears out environment (from envp) for safety and removes system
 *	resource limits, to prevent hitting our head.
 */
private void
os_init(argc, argv, envp)
	int	argc;
	char	**argv;
	char	**envp;
{
	(void) umask((mode_t)0);	/* Full control over file modes */
#ifdef	I_SYS_RESOURCE
	{
	/*
	 * Remove BSD resource limits
	 */
	struct rlimit no_limit;

	no_limit.rlim_cur = no_limit.rlim_max = RLIM_INFINITY;
	(void) setrlimit(RLIMIT_CPU, &no_limit);
	(void) setrlimit(RLIMIT_DATA, &no_limit);
	(void) setrlimit(RLIMIT_STACK, &no_limit);
	(void) setrlimit(RLIMIT_FSIZE, &no_limit);
#ifdef	RLIMIT_RSS
	(void) setrlimit(RLIMIT_RSS, &no_limit);
#endif
#ifdef	RLIMIT_AS
	(void) setrlimit(RLIMIT_AS, &no_limit);
#endif
	}
#endif
#if	(CDEBUG < CDEBUG_SYSTEM)
	/*
	 * Sanitize the environment, which is all changable by the user and
	 * therefore not trustable.  This avoids *some* strange overflows
	 * and bad assumptions by shared libraries and dyanmic loaders.
	 *
	 * This is usually a pointer to the "real" environment vector, so 
	 * the changes made here will be effective throughout the program.
 	 */
	while (*envp) *envp++ = "";
#endif
}

/*
 * print_os_env
 *	Printer runtime environment
 * Effects
 *	Calls uname(2) to get environment information and prints it.
 */
#ifdef	HAS_UTSNAME_H
#include <sys/utsname.h>

private void
print_os_env()
{
	struct utsname	un;

	if (uname(&un) >= 0)
		printf("Operating system: %s %s %s\nPlatform: %s\nNode: %s\n",
			un.sysname, un.release, un.version,
			un.machine, un.nodename);
}
#else
private void
print_os_env()
{
	/* Use something else here instead of uname(2) */
}
#endif	/* HAS_UTSNAME_H */

/* End $RCSfile: main.c,v $ */
