h50487
s 00003/00004/00209
d D 1.5 98/07/09 14:23:38 clyde 5 4
c Use set_debug_tag() and init_debug() instead of global vars
e
s 00000/00004/00213
d D 1.4 98/07/09 11:07:54 clyde 4 3
c  Remove pw_svc stuff
e
s 00001/00001/00216
d D 1.3 98/06/26 14:26:08 clyde 3 2
c Change checkpasswd.h to checkpassword.h
e
s 00002/00002/00215
d D 1.2 98/06/26 13:31:32 clyde 2 1
c Add flag argument to checkpassword_configure()
e
s 00217/00000/00000
d D 1.1 98/04/14 15:40:43 clyde 1 0
c date and time created 98/04/14 15:40:43 by clyde
e
u
U
f e 0
t
T
I 1
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
 * %M%
 *	Standalone program to test the password check modules
 */

#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu) %P%";
#endif

#include <stdio.h>
#include "defines.h"
#include "compatibility.h"
#include "options.h"
D 3
#include "checkpasswd.h"
E 3
I 3
#include "checkpassword.h"
E 3
D 4
#include "pw_svc.h"
E 4
#include "pwck_defines.h"

D 4
struct pw_svc	svc;

E 4
D 5
int	DebugLevel = DB_PWCHECK;
char	*ProgramName = "test_chkpw";

E 5
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

I 5
	set_debug_tag("test_pwck");
	init_debug(DB_PWCHECK);
E 5
	/*
	 * Process command line arguments
	 */
	while ((opt = getopt(argc, argv, "c:D:op:sP:")) != EOF) {
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
D 5
			DebugLevel = 0;
E 5
I 5
			init_debug(DB_NONE);
E 5
			silent++;
			break;
		}	
	}
	if (config == 0 && !silent)
		warn("No configuration file - using built-in settings\n");

D 4
	(void) get_pwsvc(argc, argv, envp, &svc);       /* Get service order */
E 4
	checkpassword_init();
	/*
	 * Read the configuration file
	 */
	if (config && (pf = fopen(config, "r"))) {
		char	ibuf[BUFSIZ];
		char	*error;

		while (fgets(ibuf, BUFSIZ, pf)) {
			cfline++;
D 2
			if (error = checkpassword_configure(ibuf))
E 2
I 2
			if (error = checkpassword_configure(ibuf, 0))
E 2
				die("File \"%s\"; line %d; %s\n",
					config, cfline, error);
		}
		(void) fclose(pf);
	}
	if (directives) {
		char	**dl = split(directives, ';', 0, 0);
		char	*error;

		for (; *dl; dl++) {
D 2
			if (error = checkpassword_configure(*dl))
E 2
I 2
			if (error = checkpassword_configure(*dl, 0))
E 2
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

		if (!password) {
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
		if (instringcase(checks, "dictionary")) {
			if (!Config.dictionaries[0])
				die("No dictionaries configured");
			rc = pwck_crack(password, pw);
			CHECK
			continue;
		}
#if	0
	/* Test history with different driver */
		if (instringcase(checks, "history")) {
			rc = pwck_history(password, pw);
			CHECK
			continue;
		}
#endif
		die("No check selected\n");
	}
	exit(0);
}
/* End %M% */
E 1
