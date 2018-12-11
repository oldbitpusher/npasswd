h34271
s 00004/00000/00236
d D 1.25 98/11/13 16:26:37 clyde 25 24
c Call checkpassword_probe() if debug level > DB_DETAIL
e
s 00002/00000/00234
d D 1.24 98/07/16 14:53:51 clyde 24 23
c Release any setuid/setgid privs if -c option given
e
s 00001/00001/00233
d D 1.23 98/07/16 09:43:47 clyde 23 22
c Change logdie() to die()
e
s 00004/00006/00230
d D 1.22 98/07/10 15:02:14 clyde 22 21
c Change patch level var names
e
s 00018/00019/00218
d D 1.21 98/07/09 14:23:05 clyde 21 20
c 1. Change pwcheck_debug table\
c 2. Make usage message include debug settings
c 3. Eliminate DebugLevel and ProgramName globals
e
s 00000/00004/00237
d D 1.20 98/07/09 11:05:17 clyde 20 19
c Remove call to get_pwsvc()
e
s 00002/00001/00239
d D 1.19 98/07/09 08:52:18 clyde 19 18
c Change usage of checkpassword_verify()
e
s 00014/00020/00226
d D 1.18 98/07/02 16:57:14 clyde 18 17
c Change processing of -X option
e
s 00015/00005/00231
d D 1.17 98/07/02 16:49:09 clyde 17 16
c 1. Allow everyone to use -XD
c 2. Use set_debug() to set debug level
e
s 00001/00000/00235
d D 1.16 98/06/30 15:42:49 clyde 16 15
c Add call to checkpassword_verify() after processing config file
e
s 00001/00001/00234
d D 1.15 98/06/26 14:24:46 clyde 15 14
c Change checkpasswd.h to checkpassword.h
e
s 00060/00029/00175
d D 1.14 98/06/26 14:23:29 clyde 14 13
c Bring up to date with other programs
e
s 00002/00002/00202
d D 1.13 98/06/04 08:43:29 clyde 13 12
c Update debug compile conditional
e
s 00004/00004/00200
d D 1.12 98/04/16 17:02:10 clyde 12 11
c Change use of checkpassword_configure()
e
s 00047/00005/00157
d D 1.11 98/04/07 09:50:24 clyde 11 10
c 1. Add UT copyright notice 
c 2. Change use of checkpassword()
e
s 00001/00001/00161
d D 1.10 98/03/26 11:10:05 clyde 10 9
c Change call of checkpassword()
e
s 00089/00042/00073
d D 1.9 96/08/15 14:25:52 clyde 9 8
c Compile & links Solaris 2.5 & OSF/1 3.2
e
s 00004/00000/00111
d D 1.8 96/08/09 16:17:39 clyde 8 7
c Beta 3 development checkin 2
e
s 00004/00004/00107
d D 1.7 96/08/06 14:14:19 clyde 7 6
c beta 3 cycle 1 checkin
e
s 00006/00005/00105
d D 1.6 95/04/05 16:20:08 clyde 6 5
c Beta 3 development checkin
e
s 00005/00003/00105
d D 1.5 94/01/07 18:19:07 clyde 5 4
c Fix use of checkpassword_configure
e
s 00052/00058/00056
d D 1.4 94/01/05 15:47:38 clyde 4 3
c Massive rewrite
e
s 00006/00002/00108
d D 1.3 92/02/18 16:34:40 clyde 3 2
c 1.  Add the option "-P passwd-entry.
c 2. Rename var "standalone" to "PWCK_standalone".
c 3. Add var "PWCK_auxpwline" to impliment #1.
e
s 00001/00000/00109
d D 1.2 89/11/14 17:35:23 clyde 2 1
c Add hook to differentiate between running as library and as standalone application
e
s 00109/00000/00000
d D 1.1 89/05/18 10:05:50 clyde 1 0
c date and time created 89/05/18 10:05:50 by clyde
e
u
U
t
T
I 1
/*
I 11
 * Copyright 1998, The University of Texas at Austin ("U. T. Austin").
 * All rights reserved.
 *
 * By using this software the USER indicates that he or she has read,
 * understood and will comply with the following:
 *
 * U. T. Austin hereby grants USER permission to use, copy, modify, and
 * distribute this software and its documentation for any purpose and
 * without fee, provided that:
 *
 * 1. the above copyright notice appears in all copies of the software
 *    and its documentation, or portions thereof, and 
 * 2. a full copy of this notice is included with the software and its
 *    documentation, or portions thereof, and 
 * 3. neither the software nor its documentation, nor portions thereof,
 *    is sold for profit. Any commercial sale or license of this software,
 *    copies of the software, its associated documentation and/or
 *    modifications of either is strictly prohibited without the prior
 *    consent of U. T. Austin. 
 * 
 * Title to copyright to this software and its associated documentation
 * shall at all times remain with U. T. Austin. No right is granted to
 * use in advertising, publicity or otherwise any trademark, service
 * mark, or the name of U. T. Austin.
 * 
 * This software and any associated documentation are provided "as is,"
 * and U. T. AUSTIN MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESSED OR
 * IMPLIED, INCLUDING THOSE OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR
 * PURPOSE, OR THAT USE OF THE SOFTWARE, MODIFICATIONS, OR ASSOCIATED
 * DOCUMENTATION WILL NOT INFRINGE ANY PATENTS, COPYRIGHTS, TRADEMARKS OR
 * OTHER INTELLECTUAL PROPERTY RIGHTS OF A THIRD PARTY. U. T. Austin, The
 * University of Texas System, its Regents, officers, and employees shall
 * not be liable under any circumstances for any direct, indirect, special,
 * incidental, or consequential damages with respect to any claim by USER
 * or any third party on account of or arising from the use, or inability
 * to use, this software or its associated documentation, even if U. T.
 * Austin has been advised of the possibility of those damages.
 * 
 * Submit commercialization requests to: Office of the Executive Vice
 * President and Provost, U. T. Austin, 201 Main Bldg., Austin, Texas,
 * 78712, ATTN: Technology Licensing Specialist.
 */
/*
E 11
D 4
 *	checkpasswd - Main program for standalone version
E 4
I 4
D 9
 *	checkpassword - Main program for standalone version
E 4
 *		libmain.c is the driver for the library version
E 9
I 9
 * %M%
 *	Standalone program to use the npasswd password checker
E 9
 *
D 4
 *	Compilation:	cc -o checkpasswd checkpasswd.c main.c pwck_dict.c
 *			pwck_passwd.c pwck_lexical.c pwck_local.c util.c 
E 4
I 4
D 7
 *	Compilation:	cc -o checkpassword checkpassword.c libcheckpassword.a
E 7
I 7
D 9
 *	Compilation: cc -o checkpassword checkpassword.c
			libcheckpassword.a lib/libutil.a
E 9
I 9
 * Compilation
D 14
 *	cc -o checkpasswd checkpasswd.c libpwcheck.a ../common/libcomobj.a
E 14
I 14
 *	cc -o checkpassword checkpassword.c libpwcheck.a ../common/libcomobj.a
E 14
E 9
E 7
E 4
 */

#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu) %P%";
#endif

D 4
#include "checkpasswd.h"
E 4
I 4
#include <stdio.h>
#include <pwd.h>
I 14
#include "defines.h"
E 14
D 7
#include "compat.h"
E 7
I 7
#include "compatibility.h"
E 7
D 9
#include "checkpassword.h"
E 4
#include "version.h"
I 8
#include "svc_info.h"
E 9
I 9
D 15
#include "checkpasswd.h"
E 15
I 15
#include "checkpassword.h"
E 15
D 20
#include "pw_svc.h"
E 20
#include "options.h"
I 17
#include "common.h"
E 17
E 9
E 8

D 4
char *replies[] = {
	"This password is ok for use",		/* PWCK_OK */
	"Empty password",			/* PWCK_NULL */
	"This password is too easy to guess",	/* PWCK_OBVIOUS */
	"This password is part of your 'finger' information", /* PWCK_FINGER */
	"This password was found in a dictionary",	/* PWCK_INDICT */
	"This password has an illegal character in it",	/* PWCK_ILLCHAR */
	"This password is too short",			/* PWCK_SHORT */
	0
};
#define	NREPLIES	7	/* Number of messages in replies */
E 4
I 4
D 21
#ifndef	CONFIG_FILE
E 21
D 9
			/* Set configuration file name */
E 9
I 9
/*
 * This program can use the npasswd configuration file.
D 14
 * Define this if you want to use a different configuration file
 * for the checkpasswd program.
E 14
I 14
D 21
 * Define this in the Makefile to change the default configuration file.
E 14
 * 
D 14
 * The configuration file is usally set in ../options.h
E 14
I 14
 * The npasswd configuration file is defined in ../options.h
E 21
I 21
 * The npasswd configuration file is defined in ../options.h.
 * Redefine CONFIG_FILE in the Makefile to change the default.
E 21
E 14
 */
E 9
D 13
# ifdef	DEBUG
E 13
I 13
D 21
# ifdef	CDEBUG
E 13
D 9
#	define	CONFIG_FILE	"checkpasswd.cf" 
# else
#	define	CONFIG_FILE	"/usr/adm/checkpasswd.cf"
E 9
I 9
D 14
# define	CONFIG_FILE	"checkpasswd.cf" 
E 14
I 14
# define	CONFIG_FILE	"checkpassword.cf" 
E 14
E 9
D 13
# endif	/* DEBUG */
E 13
I 13
# endif	/* CDEBUG */
E 13
#endif	/* CONFIG_FILE */
E 21
E 4

I 8
D 9
struct pwsvc	svc;
E 9
I 9
D 14
struct pw_svc	svc;
E 14
I 14
D 20
struct pw_svc	svc;				/* Needed by library */
E 14
E 9

E 20
E 8
D 4
char	elucidate[BUFSIZ];	/* Expanded error message */

int	silent = 0,		/* Silent mode switch */
	oneshot = 0,		/* Check only one password switch */
	errornum = 0;		/* Print error number with message */
I 2
D 3
int	standalone = 1;		/* Running as standalone application */
E 3
I 3
int	PWCK_standalone = 1;	/* Running as standalone application */
char	PWCK_auxpwline[BUFSIZ] = { 0 };
E 3
E 2

E 4
D 9
main(argc, argv)
int	argc;
char	**argv;
E 9
I 9
D 14
extern char	*checkpasswd_version,
		*checkpasswd_patchlevel,
		*build_info;
E 14
I 14
D 22
extern char	*checkpasswd_version,		/* Version string */
		*checkpasswd_patchlevel,	/* Patch level string */
		*build_info;			/* Build info string */
E 22
I 22
extern char	*version,	/* Version string */
		*patchlevel,	/* Patch level string */
		*build_info;	/* Build info string */
E 22
E 14

D 14
int	DebugLevel = 0;				/* For messages module */
char	*ProgramName = "checkpasswd";		/* For messages module */
E 14
I 14
D 21
int	DebugLevel = DB_NONE;			/* For messages module */
char	*ProgramName = "checkpassword";		/* For messages module */
E 14

E 21
I 17
/*
 * Program debug level table
 */
D 21
private debug_levels pwcheck_debug[] = {
	"none",		DB_NONE,
	"verbose",	DB_VERBOSE,
	"config",	DB_CONFIG,
	"pwcheck",	DB_PWCHECK,
	"detail",	DB_DETAIL,
	"all",		DB_ALL,
	0,		-1,
E 21
I 21
debug_table pwcheck_debug[] = {
	{ "none",	DB_NONE,	"Debugging off" },
	{ "verbose",	DB_VERBOSE,	"Verbose" },
	{ "config",	DB_CONFIG,	"Configuration processing" },
	{ "pwcheck",	DB_PWCHECK,	"Password checking" },
	{ "detail",	DB_DETAIL,	"Detailed debugging" },
	{ "all",	DB_ALL,		"All debugging" },
	{ 0 },
E 21
};

E 17
char *Usage = "Usage: %s\n\
	[-c config-file] Use alternate configuration file\n\
	[-o]		Check one password and exit\n\
D 14
	[-u user-id]	Alternate uid to use for check\n\
	[-X]		Extended options\n\
E 14
I 14
	[-u user-id]	Alternate name or uid for check\n\
E 14
	[-Xh]		Print usage message\n\
I 14
	[-XDn]		Set debug level to N\n\
E 14
	[-XV]		Print version information\n\
";

/*
 * main
 *	Main program
 *
 * Exit codes
 *	0 if password is acceptable (-o only)
 *	1 if password is not acceptable (-o only)
 *	1 on error
 */
main(argc, argv, envp)
	int	argc;
	char	**argv;
	char	**envp;
E 9
{
D 6
	int	uid = getuid(),		/* Invoker's uid */
		opt,			/* Argument parser */
E 6
I 6
D 9
	Uid_t	uid = getuid(),		/* Invoker's uid */
E 9
I 9
	Uid_t	uid = getuid();		/* Invoker's uid */
E 9
	int	opt,			/* Argument parser */
E 6
		interactive = 0;	/* In interactive mode? */
D 4
	char	*configfile = CONFIG_FILE;	/* Configuration file */
E 4
I 4
D 14
	char	*config = CONFIG_FILE;
	FILE	*pf;
I 11
	char	*rc;
E 14
I 14
	char	*config = CONFIG_FILE;	/* Configuration file */
	FILE	*pf;			/* Config file I/O */
	char	*rc;			/* Temp */
E 14
E 11
D 12
	char	elucidate[BUFSIZ];	/* Expanded error message */
E 12
	int	oneshot = 0;		/* Check only one password switch */
D 9
	struct passwd *pwinfo;
E 9
I 9
	int	cfline = 0;		/* Configuration file line number */
D 11
	int	rc;			/* Return code from checkpassword() */
E 11
	struct passwd *pwinfo;		/* Passwd info to check with */
E 9
E 4
	extern char	*optarg;	/* From getopt() */

I 21
	set_debug_tag("checkpassword");
E 21
D 9
	/* Process argument list */
D 3
	while ((opt = getopt(argc, argv, "c:eosu:V?")) != EOF) {
E 3
I 3
D 4
	while ((opt = getopt(argc, argv, "c:eP:osu:V?")) != EOF) {
E 4
I 4
	while ((opt = getopt(argc, argv, "c:P:ou:V?")) != EOF) {
E 9
I 9
	set_die_callback((void *)0);
I 14

	if ((pwinfo = getpwuid(uid)) == 0)
		die("Cannot get password info for you\n");

E 14
	/*
	 * Process command line arguments
	 */
	while ((opt = getopt(argc, argv, "c:ou:X:")) != EOF) {
E 9
E 4
E 3
		switch (opt) {
		case 'c':	/* -c config-file */
I 24
			(void) setuid(getuid());	/* Release privs */
			(void) setgid(getgid());	/* Release privs */
E 24
D 4
			configfile = optarg;
E 4
I 4
			config = optarg;
D 9
			if (access(config, 1) < 0) {
				printf("configuration file error %s\n", config);
				exit(1);
			}
E 9
I 9
			if (access(config, 1) < 0)
				die("Cannot read configuration file %s\n", config);
E 9
E 4
			break;
D 4
		case 'e':	/* -e [print status number] */
			errornum++;
			break;
E 4
		case 'o':	/* -o [check one password & quit] */
			oneshot++;
			break;
D 4
		case 's':	/* -s [silent mode] */
			silent++;
I 3
			break;
		case 'P':	/* -P passwd-line */
			(void) strcpy(PWCK_auxpwline, optarg);
E 3
			break;
E 4
		case 'u':	/* -u [user id] */
D 14
			if (uid == 0 && isdigit(*optarg))
D 12
				uid = atoi(optarg);
E 12
I 12
				uid = decode_int(optarg);
E 14
I 14
#if	(CDEBUG < CDEBUG_DBX)
			if (uid)
				die("Option -u reserved for root.\n");
#endif
			if (isdigit(*optarg)) {
				Uid_t	xuid = decode_int(optarg);

				if ((pwinfo = getpwuid(xuid)) == 0) {
					die("Cannot get password for uid %d\n",
						xuid);
				}
			} else {
				pwinfo = getpwnam(optarg);
				if (pwinfo == 0)
					die("No such user '%s'\n", optarg);
			}
E 14
E 12
			break;
D 9
		case 'V':	/* -V [print version information] */
D 6
			printf("Version %s\nPatch level %s\n",
				version, patchlevel);
E 6
I 6
			printf("Version: %s\nPatch level: %s\n%s\n",
				checkpasswd_version, checkpasswd_patchlevel,
				build_info);
E 9
I 9
D 18
		case 'X': {	/* -X [Extended options] */
			char	*op;

			for (op = optarg; *op; op++) {
				switch (*op) {
I 14
				case 'D':		/* Set debug level */
D 17
#if	(CDEBUG < CDEBUG_DBX)
					if (uid)
						die("Option -XD reserved for root.\n");
#endif
					DebugLevel = decode_int(++optarg);
E 17
I 17
					set_debug(++optarg, pwcheck_debug);
E 17
					break;
E 14
				case 'h':		/* Help message */
					printf(Usage, argv[0]);
D 14
					exit(0);
					/*NOTREACHED*/
E 14
I 14
					return(0);
E 14
				case 'V':		/* Print version info */
					printf("Version: %s\nPatch level: %s\n%s\n",
						checkpasswd_version,
						checkpasswd_patchlevel,
						build_info);
D 14
					exit(0);
					/*NOTREACHED*/
E 14
I 14
					return(0);
E 14
				}
E 18
I 18
		case 'X':	/* -X [Extended options] */
			switch (*optarg) {
			case 'D':		/* Set debug level */
				set_debug(++optarg, pwcheck_debug);
				break;
			case 'h':		/* Help message */
I 21
				{
				debug_table *dt = pwcheck_debug;

E 21
				printf(Usage, argv[0]);
I 21
				printf("Debug levels (-XD...):\n");
				for (; dt->name; dt++)
					printf("\t%s\t%s\n", dt->name, dt->help);
E 21
				return(0);
I 21
				}
E 21
			case 'V':		/* Print version info */
				printf("Version: %s\nPatch level: %s\n%s\n",
D 22
					checkpasswd_version,
					checkpasswd_patchlevel,
					build_info);
E 22
I 22
					version, patchlevel, build_info);
E 22
				return(0);
E 18
			}
E 9
E 6
D 18
			break;
D 9
		case '?':
D 4
			printf("Usage: checkpasswd [-c config] [-e] [-o] [-s] [-V] [-u uid]\n");
E 4
I 4
			printf("Usage: checkpassword [-c config] [-o] [-V] [-u uid]\n");
E 4
			exit(0);
E 9
I 9
			}
E 18
E 9
		}
	}
I 8
D 9
	(void) svc_info(argc, argv, envp, &svc);       /* Get service order */
E 9
I 9
D 20
	(void) get_pwsvc(argc, argv, envp, &svc);       /* Get service order */
E 20
E 9
E 8
D 4
	(void) readconfig(configfile);
E 4
I 4
	checkpassword_init();
I 9
	/*
	 * Read the configuration file
	 */
E 9
	if (pf = fopen(config, "r")) {
		char	ibuf[BUFSIZ];
I 12
D 14
		char	*error;
E 14
E 12

D 5
		while (fgets(ibuf, BUFSIZ, pf))
			checkpassword_configure(ibuf, 1);
		close(pf);
E 5
I 5
		while (fgets(ibuf, BUFSIZ, pf)) {
I 14
			char	*error;

			chop_nl(ibuf);
E 14
I 9
			cfline++;
E 9
D 12
			if (checkpassword_configure(ibuf, elucidate) == 0)
E 12
I 12
D 14
			if (error = checkpassword_configure(ibuf))
E 12
D 9
				printf("CFERROR %s\n", elucidate);
E 9
I 9
				die("File \"%s\"; line %d; %s\n",
E 14
I 14
			if (*ibuf == 0 || *ibuf == '#')
				continue;
			if (instringcase(ibuf, "passwd.") == 0)
				continue;

			/*
			 * Feed config line to checklib configure.
			 * Error flag is 0 so that unknown stuff is ignored
			 */
			if (error = checkpassword_configure(ibuf, 0))
				die("File '%s;; line %d; %s\n",
E 14
D 12
					config, cfline, elucidate);
E 12
I 12
					config, cfline, error);
E 12
E 9
		}
D 9
		fclose(pf);
E 9
I 9
		(void) fclose(pf);
E 9
E 5
	}
I 25
	if (get_debug() >= DB_DETAIL)
		checkpassword_probe("checkpassword.");

E 25
I 16
D 19
	checkpassword_verify();
E 19
I 19
	if (rc = checkpassword_verify())
D 23
		logdie(rc);
E 23
I 23
		die(rc);
I 25

E 25
E 23
E 19
E 16
D 9
	if ((pwinfo = getpwuid(uid)) == 0) {
		printf("Cannot get password info for uid %d\n", uid);
		exit(1);
	}
E 9
I 9
D 14
	if ((pwinfo = getpwuid(uid)) == 0)
		die("Cannot get password info for uid %d\n", uid);

E 14
E 9
E 4
	interactive = isatty(fileno(stdin));
	for (;;) {
D 4
		int	rc;	/* Return code from checkpasswd() */
E 4
I 4
D 9
		int	rc;	/* Return code from checkpassword() */
E 9
E 4
		char	ibuf[BUFSIZ];		/* Input buffer */
		char	*nl;	/* Newline postition */

		if (interactive) {
D 4
			printf("Password to check: ");
E 4
I 4
			printf("\nPassword to check: ");
E 4
			fflush(stdout);
		}
D 4
		if (fgets(ibuf, sizeof(ibuf), stdin) == NULL)
E 4
I 4
		if (fgets(ibuf, sizeof(ibuf), stdin) == NULL) {
			if (interactive) printf("\n");
E 4
			break;
D 4
		if (nl = index(ibuf, '\n'))
E 4
I 4
		}
D 6
		if (nl = INDEX(ibuf, '\n'))
E 6
I 6
D 7
		if (nl = index(ibuf, '\n'))
E 6
E 4
			*nl = 0;
E 7
I 7
		chop_nl(ibuf);
E 7
		if (ibuf[0] == 0)
			continue;
D 4
		rc = checkpassword(ibuf, uid, elucidate);
		if (!silent) {
			if (errornum)
				printf("%d ", rc);
			if (rc <= NREPLIES) {
				if (elucidate[0])
					printf("%s.\n", elucidate);
				else if (replies[rc])
					printf("%s.\n", replies[rc]);
				else
					putchar('\n');
			}
			else
				printf("Error %d\n", rc);
		}
E 4
I 4
D 10
		rc = checkpassword(ibuf, pwinfo, elucidate);
E 10
I 10
D 11
		rc = checkpassword(ibuf, pwinfo, elucidate, sizeof elucidate);
E 10
		if (*elucidate)
D 9
			printf("Password cannot be used because %s.\n",
				elucidate);
E 9
I 9
			printf("Password bad: %s.\n", elucidate);
E 11
I 11
		if (rc = checkpassword(ibuf, pwinfo))
			printf("Password bad: %s.\n", rc);
E 11
E 9
		else
			printf("Password ok.\n");
E 4
		if (oneshot)
D 4
			exit(rc);
E 4
I 4
D 9
			exit(rc == 0);
E 9
I 9
			break;
E 9
E 4
	}
D 9
	exit(0);
E 9
I 9
D 11
	exit(rc);
E 11
I 11
D 14
	exit(rc == 0);
E 14
I 14
	return(rc != 0);
E 14
E 11
E 9
}
D 4
/*	End %M% */
E 4
I 4
/* End %M% */
E 4
E 1
