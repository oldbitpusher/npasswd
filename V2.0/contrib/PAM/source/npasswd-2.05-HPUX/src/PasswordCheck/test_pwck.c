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
 * test_pwck.c
 *	Standalone program to test the password check modules
 */

#ifndef lint
static char sccsid[] = "@(#)test_pwck.c	1.5 07/09/98 (cc.utexas.edu) /usr/share/src/private/ut/share/bin/passwd/V2.0/src/PasswordCheck/SCCS/s.test_pwck.c";
#endif

#include <stdio.h>
#include "defines.h"
#include "compatibility.h"
#include "options.h"
#include "checkpassword.h"
#include "pwck_defines.h"

char *Usage = "Usage: %s\n\
	[-c config-file] Use alternate configuration file\n";
/*
 * main
 *	Main program
 *
 * Exit codes
 *	0 if password is acceptable 
 *	1 on error
 */
main(argc, argv, envp)
	int	argc;
	char	**argv;
	char	**envp;
{
	int	opt;
	char	*config = 0,
		*password = 0,
		*checks = 0,
		*directives = 0;
	int	silent = 0,
		onetime = 0;
	FILE	*pf;
	char	*rc;
	int	cfline = 0;		/* Configuration file line number */
	struct passwd *pw;
	extern char	*optarg;	/* From getopt() */

	set_debug_tag("test_pwck");
	init_debug(DB_PWCHECK);
	/*
	 * Process command line arguments
	 */
	while ((opt = getopt(argc, argv, "c:D:o:p:s:P:")) != EOF) {
		switch (opt) {
		case 'c':	/* -c config-file */
			config = optarg;
			break;
		case 'D':	/* -D config-directives */
			directives = optarg;
			break;
		case 'P':	/* -P password */
			password = optarg;
			onetime = 1;
			break;
		case 'p':	/* -p checks */
			checks = optarg;
			break;
		case 'o':	/* -o (once-only) */
			onetime = 1;
			break;
		case 's':	/* -s (silent) */
			init_debug(DB_NONE);
			silent++;
			break;
		}	
	}
	if (config == 0 && !silent)
		warn("No configuration file - using built-in settings\n");

	checkpassword_init();
	/*
	 * Read the configuration file
	 */
	if (config && (pf = fopen(config, "r"))) {
		char	ibuf[BUFSIZ];
		char	*error;

		while (fgets(ibuf, BUFSIZ, pf)) {
			cfline++;
			if (error = checkpassword_configure(ibuf, 0))
				die("File \"%s\"; line %d; %s\n",
					config, cfline, error);
		}
		(void) fclose(pf);
	}
	if (directives) {
		char	**dl = split(directives, ';', 0, 0);
		char	*error;

		for (; *dl; dl++) {
			if (error = checkpassword_configure(*dl, 0))
				die("Directive error (%s) %s\n", *dl, error);
		}
	}
	if ((pw = getpwuid(getuid())) == 0)
		die("Cannot get password info for you\n");

#define	CHECK	\
	if (rc) { \
		printf("<%s> BAD %s\n", password, rc);\
		if (onetime) exit(1);\
	} else { \
		printf("<%s> OK\n", password); \
		if (onetime) exit(0);\
	}

	if (checks == 0)
		die("No check selected\n");
	for (;;) {
		char	ibuf[BUFSIZ];

		if (!onetime) {
			if (!silent) {
				printf("\nPassword to check: ");
				fflush(stdout);
			}
			if (fgets(ibuf, sizeof(ibuf), stdin) == NULL)
				break;
			if (ibuf[0] == '#') {
				fputs(ibuf, stdout);
			continue;
			}
			chop_nl(ibuf);
			if (ibuf[0] == 0)
				continue;
			password = ibuf;
		}
		if (instringcase(checks, "lexical")) {
			rc = pwck_lexical(password, pw);
			CHECK
			continue;
		}
		if (instringcase(checks, "local")) {
			rc = pwck_local(password, pw);
			CHECK
			continue;
		}
		if (instringcase(checks, "passwd")) {
			rc = pwck_passwd(password, pw);
			CHECK
			continue;
		}
		if (instringcase(checks, "strong")) {
			rc = pwck_vicb(password, pw);
			CHECK
			continue;
		}
		if (instringcase(checks, "dictionary")) {
			if (!Config.dictionaries[0])
				die("No dictionaries configured");
			rc = pwck_crack(password, pw);
			CHECK
			continue;
		}
	/* Test history with different driver */
		if (instringcase(checks, "history")) {
			rc = pwck_history(password, pw);
			CHECK
			continue;
		}
		die("No check selected\n");
	}
	exit(0);
}
/* End test_pwck.c */
