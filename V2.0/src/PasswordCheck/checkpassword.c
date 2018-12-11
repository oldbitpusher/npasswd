/*
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
 * checkpassword.c
 *	Standalone program to use the npasswd password checker
 *
 * Compilation
 *	cc -o checkpassword checkpassword.c libpwcheck.a ../common/libcomobj.a
 */

#ifndef lint
static char sccsid[] = "@(#)checkpassword.c	1.25 11/13/98 (cc.utexas.edu) /usr/share/src/private/ut/share/bin/passwd/V2.0/src/PasswordCheck/SCCS/s.checkpassword.c";
#endif

#include <stdio.h>
#include <pwd.h>
#include "defines.h"
#include "compatibility.h"
#include "checkpassword.h"
#include "options.h"
#include "common.h"

/*
 * This program can use the npasswd configuration file.
 * The npasswd configuration file is defined in ../options.h.
 * Redefine CONFIG_FILE in the Makefile to change the default.
 */

extern char	*version,	/* Version string */
		*patchlevel,	/* Patch level string */
		*build_info;	/* Build info string */

/*
 * Program debug level table
 */
debug_table pwcheck_debug[] = {
	{ "none",	DB_NONE,	"Debugging off" },
	{ "verbose",	DB_VERBOSE,	"Verbose" },
	{ "config",	DB_CONFIG,	"Configuration processing" },
	{ "pwcheck",	DB_PWCHECK,	"Password checking" },
	{ "detail",	DB_DETAIL,	"Detailed debugging" },
	{ "all",	DB_ALL,		"All debugging" },
	{ 0 },
};

char *Usage = "Usage: %s\n\
	[-c config-file] Use alternate configuration file\n\
	[-o]		Check one password and exit\n\
	[-u user-id]	Alternate name or uid for check\n\
	[-Xh]		Print usage message\n\
	[-XDn]		Set debug level to N\n\
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
{
	Uid_t	uid = getuid();		/* Invoker's uid */
	int	opt,			/* Argument parser */
		interactive = 0;	/* In interactive mode? */
	char	*config = CONFIG_FILE;	/* Configuration file */
	FILE	*pf;			/* Config file I/O */
	char	*rc;			/* Temp */
	int	oneshot = 0;		/* Check only one password switch */
	int	cfline = 0;		/* Configuration file line number */
	struct passwd *pwinfo;		/* Passwd info to check with */
	extern char	*optarg;	/* From getopt() */

	set_debug_tag("checkpassword");
	set_die_callback((void *)0);

	if ((pwinfo = getpwuid(uid)) == 0)
		die("Cannot get password info for you\n");

	/*
	 * Process command line arguments
	 */
	while ((opt = getopt(argc, argv, "c:ou:X:")) != EOF) {
		switch (opt) {
		case 'c':	/* -c config-file */
			(void) setuid(getuid());	/* Release privs */
			(void) setgid(getgid());	/* Release privs */
			config = optarg;
			if (access(config, 1) < 0)
				die("Cannot read configuration file %s\n", config);
			break;
		case 'o':	/* -o [check one password & quit] */
			oneshot++;
			break;
		case 'u':	/* -u [user id] */
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
			break;
		case 'X':	/* -X [Extended options] */
			switch (*optarg) {
			case 'D':		/* Set debug level */
				set_debug(++optarg, pwcheck_debug);
				break;
			case 'h':		/* Help message */
				{
				debug_table *dt = pwcheck_debug;

				printf(Usage, argv[0]);
				printf("Debug levels (-XD...):\n");
				for (; dt->name; dt++)
					printf("\t%s\t%s\n", dt->name, dt->help);
				return(0);
				}
			case 'V':		/* Print version info */
				printf("Version: %s\nPatch level: %s\n%s\n",
					version, patchlevel, build_info);
				return(0);
			}
		}
	}
	checkpassword_init();
	/*
	 * Read the configuration file
	 */
	if (pf = fopen(config, "r")) {
		char	ibuf[BUFSIZ];

		while (fgets(ibuf, BUFSIZ, pf)) {
			char	*error;

			chop_nl(ibuf);
			cfline++;
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
					config, cfline, error);
		}
		(void) fclose(pf);
	}
	if (get_debug() >= DB_DETAIL)
		checkpassword_probe("checkpassword.");

	if (rc = checkpassword_verify())
		die(rc);

	interactive = isatty(fileno(stdin));
	for (;;) {
		char	ibuf[BUFSIZ];		/* Input buffer */
		char	*nl;	/* Newline postition */

		if (interactive) {
			printf("\nPassword to check: ");
			fflush(stdout);
		}
		if (fgets(ibuf, sizeof(ibuf), stdin) == NULL) {
			if (interactive) printf("\n");
			break;
		}
		chop_nl(ibuf);
		if (ibuf[0] == 0)
			continue;
		if (rc = checkpassword(ibuf, pwinfo))
			printf("Password bad: %s.\n", rc);
		else
			printf("Password ok.\n");
		if (oneshot)
			break;
	}
	return(rc != 0);
}
/* End checkpassword.c */
