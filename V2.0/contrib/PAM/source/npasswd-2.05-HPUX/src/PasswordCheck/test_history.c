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
 * test_history.c
 *	Standalone program to test the password history mechanism
 */

#ifndef lint
static char sccsid[] = "@(#)test_history.c	1.8 09/30/98 (cc.utexas.edu) /usr/share/src/private/ut/share/bin/passwd/V2.0/src/PasswordCheck/SCCS/s.test_history.c";
#endif

#include <stdio.h>
#include "defines.h"
#include "compatibility.h"
#include "options.h"
#include "checkpassword.h"
#include "pwck_defines.h"
#include "pwck_history.h"

char *Usage = "Usage: %s\n\
	[-a N]		Set password age to N\n\
	[-D data]	Data string (used for some functions)\n\
	[-d N]		Set password depth to N\n\
	[-f function]	Select test function\n\
	[-F file]	Set database name\n\
	[-m method]	Select database method\n\
	[-p password]	Password to enter or search for (plaintext)\n\
	[-s]		Supress output\n\
	[-u username]	Alternate user name\n\
";

/*
 * main
 *	Main program
 *
 * Exit codes
 *	0 if test ok
 *	1 if not
 */
main(argc, argv, envp)
	int	argc;
	char	**argv;
	char	**envp;
{
	int	opt;
	int	tmp;
	char	*password = 0,
		*function = 0,
		*alt_user = 0,
		*alt_data = 0,
		*dbfile = 0,
		*method = DEFAULT_METHOD,
		*uname,
		*rc;
	struct passwd *pw;
	extern char	*optarg;	/* From getopt() */
	extern int	optind;		/* From getopt() */

	init_debug(DB_ALL);
	set_debug_tag("test_history");

	/*
	 * Process command line arguments
	 */
	while ((opt = getopt(argc, argv, "a:d:D:f:m:p:su:")) != EOF) {
		switch (opt) {
		case 'a':	/* -a password-age */
			HistoryAge = atoi(optarg);
			break;
		case 'D':	/* -D misc-data */
			alt_data = optarg;
			break;
		case 'd':	/* -d password-depth */
			HistoryDepth = atoi(optarg);
			break;
		case 'F':	/* -f file */
			dbfile = optarg;
			break;
		case 'm':	/* -m method */
			method = optarg;
			break;
		case 'p':	/* -p password */
			password = optarg;
			break;
		case 's':	/* -s (silent) */
			init_debug(DB_NONE);
			break;
		case 'u':	/* -u username */
			alt_user = optarg;
			break;
		}
	}
	/*
	 * Get & verify function argument
	 */
	if (function == 0)
		function = argv[optind++];
	if (function == 0)
		die(Usage, argv[0]);

	if (dbfile) {
		char    *tmp[4];
		char    *error;

		tmp[0] = "database";
		tmp[1] = method;
		tmp[2] = dbfile;
		tmp[3] = 0;
		if (error = pwck_history_configure(tmp)) {
			die("error: file '%s' method '%s' error '%s'\n",
				dbfile, method, error);
		}
	}
	if (get_debug()) {
		printf("History database = \"%s\"\n", HistoryDB);
		printf("History method = %s\n", HistoryMethod);
		printf("History depth = %d\n", HistoryDepth);
		printf("History age = %d days\n", HistoryAge / SEC_DAY);
	}
	if ((pw = getpwuid(getuid())) == 0)
		die("Cannot get password info for you\n");
	uname = pw->pw_name;
	if (alt_user)
		uname = alt_user;

	if (instringcase(function, "clean")) {
		if (alt_data) {
			char	*nhist;

			printf("Original history: <%s>\n", alt_data);
			nhist = clean_history(alt_data, HistoryDepth,
				HistoryAge, 0, 0);
			if (nhist == NULL)
				nhist = "";
			printf("Cleaned history:  <%s>\n", nhist);
		} else {
			printf("No history data (use -D)\n");
			return(1);
		}
	}
	if (instringcase(function, "put")) {
		char	*ct = crypt(password, "pw");
		int	rv = password_history_update(uname, ct, 0);
		switch (rv) {
			case 0:
				printf("No history database\n");
				return(2);
				/*NOTREACHED*/
			case 1:
				printf("Put %s ok for %s\n", ct, uname);
				return(0);
				/*NOTREACHED*/
			default:
				printf("Put failed %s\n", uname);
				return(1);
				/*NOTREACHED*/
		}
		return(3);
	}
	if (instringcase(function, "get")) {
		if (rc = (char *)pwck_get_history(uname)) {
			printf("History for %s: %s\n", uname, rc);
			return(0);
		} else {
			printf("No history for %s\n", uname);
			return(1);
		}
	}
	if (instringcase(function, "find")) {
		if (alt_user && (pw = getpwnam(alt_user)) == 0)
			die("Cannot get password info for %s\n", alt_user);
		if (rc = pwck_history(password, pw)) {
			printf("<%s> FOUND %s\n", password, rc);
			return(0);
		} else {
			printf("<%s> NOT FOUND\n", password);
			return(1);
		}
	}
	return(0);
}
/* End test_history.c */
