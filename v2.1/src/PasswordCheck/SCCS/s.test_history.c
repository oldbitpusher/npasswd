h05429
s 00016/00013/00207
d D 1.8 98/09/30 15:13:37 clyde 8 7
c Add get/put of non-existant user
e
s 00005/00005/00215
d D 1.7 98/07/09 14:23:52 clyde 7 6
c Use set_debug_tag() and init_debug() instead of global vars
e
s 00000/00005/00220
d D 1.6 98/07/09 11:07:46 clyde 6 5
c Remove pw_svc stuff
e
s 00001/00001/00224
d D 1.5 98/06/26 14:26:09 clyde 5 4
c Change checkpasswd.h to checkpassword.h
e
s 00045/00028/00180
d D 1.4 98/06/23 10:44:45 clyde 4 3
c Change command line arguments (be more like history_admin)
e
s 00008/00007/00200
d D 1.3 98/06/08 14:08:49 clyde 3 2
c Change variable names
e
s 00001/00001/00206
d D 1.2 98/06/04 09:51:42 clyde 2 1
c Change first arg to password_history_update()
e
s 00207/00000/00000
d D 1.1 98/06/04 08:15:43 clyde 1 0
c date and time created 98/06/04 08:15:43 by clyde
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
 *	Standalone program to test the password history mechanism
 */

#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu) %P%";
#endif

#include <stdio.h>
#include "defines.h"
#include "compatibility.h"
#include "options.h"
D 5
#include "checkpasswd.h"
E 5
I 5
#include "checkpassword.h"
E 5
D 6
#include "pw_svc.h"
E 6
#include "pwck_defines.h"
#include "pwck_history.h"

D 6
struct pw_svc	svc;

E 6
D 7
int	DebugLevel = DB_ALL;
char	*ProgramName = "test_history";

E 7
char *Usage = "Usage: %s\n\
	[-A N]		Set password age to N\n\
D 4
	[-c \"directive_1; directive_2; ... \"] Configuration directives\n\
E 4
	[-d data]	Data string (used for some functions)\n\
D 4
	[-D N]		Set password depth to N\n\
E 4
I 4
	[-M N]		Set password depth to N\n\
E 4
	[-f function]	Select test function\n\
I 4
	[-F file]	Set database name\n\
	[-M method]	Select database method\n\
E 4
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
D 4
		*function = "get",
E 4
I 4
		*function = 0,
E 4
		*alt_user = 0,
		*alt_data = 0,
D 4
		*directives = 0;
	char	*rc;
E 4
I 4
		*dbfile = 0,
		*method = DEFAULT_METHOD,
I 8
		*uname,
E 8
		*rc;
E 4
	struct passwd *pw;
	extern char	*optarg;	/* From getopt() */
I 4
	extern int	optind;		/* From getopt() */
E 4

I 7
	init_debug(DB_ALL);
	set_debug_tag("test_history");

E 7
	/*
	 * Process command line arguments
	 */
D 4
	while ((opt = getopt(argc, argv, "A:d:D:c:f:p:su:")) != EOF) {
E 4
I 4
	while ((opt = getopt(argc, argv, "a:d:D:f:m:p:su:")) != EOF) {
E 4
		switch (opt) {
D 4
		case 'A':	/* -a password-age */
E 4
I 4
		case 'a':	/* -a password-age */
E 4
D 3
			PasswordHistoryAge = atoi(optarg);
E 3
I 3
			HistoryAge = atoi(optarg);
E 3
			break;
D 4
		case 'c':	/* -c config-directives */
			directives = optarg;
			break;
		case 'd':	/* -d misc-data */
E 4
I 4
		case 'D':	/* -D misc-data */
E 4
			alt_data = optarg;
			break;
D 4
		case 'D':	/* -D password-depth */
E 4
I 4
		case 'd':	/* -d password-depth */
E 4
D 3
			PasswordHistoryDepth = atoi(optarg);
E 3
I 3
			HistoryDepth = atoi(optarg);
E 3
			break;
D 4
		case 'f':	/* -f function */
			function = optarg;
E 4
I 4
		case 'f':	/* -f file */
			dbfile = optarg;
E 4
			break;
I 4
		case 'm':	/* -m method */
			method = optarg;
			break;
E 4
		case 'p':	/* -p password */
			password = optarg;
			break;
		case 's':	/* -s (silent) */
D 7
			DebugLevel = 0;
E 7
I 7
			init_debug(DB_NONE);
E 7
			break;
		case 'u':	/* -u username */
			alt_user = optarg;
			break;
		}
	}
I 4
	/*
	 * Get & verify function argument
	 */
	if (function == 0)
		function = argv[optind++];
	if (function == 0)
		die(Usage, argv[0]);

E 4
D 6
	(void) get_pwsvc(argc, argv, envp, &svc);       /* Get service order */
D 4
	if (directives) {
		char	**dl = split(directives, ';', 0, 0);
		char	*error;
E 4

E 6
D 4
		for (; *dl; dl++) {
			char	**dw = split(*dl, 0, 0, 0);
			if (error = pwck_history_configure(dw))
				die("Directive error (%s) %s\n", *dl, error);
E 4
I 4
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
E 4
		}
	}
D 7
	if (DebugLevel) {
E 7
I 7
	if (get_debug()) {
E 7
D 3
		printf("History database = \"%s\"\n", PasswordHistoryDB);
		printf("History method = %s\n", PasswordHistoryMethod);
		printf("History depth = %d\n", PasswordHistoryDepth);
		printf("History age = %d days\n", PasswordHistoryAge / SEC_DAY);
E 3
I 3
		printf("History database = \"%s\"\n", HistoryDB);
		printf("History method = %s\n", HistoryMethod);
		printf("History depth = %d\n", HistoryDepth);
		printf("History age = %d days\n", HistoryAge / SEC_DAY);
E 3
	}
D 8
	if (alt_user) {
		if ((pw = getpwnam(alt_user)) == 0)
			die("Cannot get password info for %s\n", alt_user);
	} else {
		if ((pw = getpwuid(getuid())) == 0)
			die("Cannot get password info for you\n");
	}
E 8
I 8
	if ((pw = getpwuid(getuid())) == 0)
		die("Cannot get password info for you\n");
	uname = pw->pw_name;
	if (alt_user)
		uname = alt_user;
E 8

	if (instringcase(function, "clean")) {
		if (alt_data) {
			char	*nhist;

			printf("Original history: <%s>\n", alt_data);
D 3
			nhist = clean_history(alt_data);
E 3
I 3
			nhist = clean_history(alt_data, HistoryDepth,
				HistoryAge, 0, 0);
I 8
			if (nhist == NULL)
				nhist = "";
E 8
E 3
			printf("Cleaned history:  <%s>\n", nhist);
		} else {
D 4
			printf("No history data (use -d)\n");
			exit(1);
E 4
I 4
			printf("No history data (use -D)\n");
			return(1);
E 4
		}
	}
	if (instringcase(function, "put")) {
		char	*ct = crypt(password, "pw");
D 2
		int	rv = password_history_update(pw, ct);
E 2
I 2
D 4
		int	rv = password_history_update(pw->pw_name, ct);
E 4
I 4
D 8
		int	rv = password_history_update(pw->pw_name, ct, 0);
E 8
I 8
		int	rv = password_history_update(uname, ct, 0);
E 8
E 4
E 2
		switch (rv) {
			case 0:
				printf("No history database\n");
				return(2);
				/*NOTREACHED*/
			case 1:
D 8
				printf("Put %s ok for %s\n", ct, pw->pw_name);
E 8
I 8
				printf("Put %s ok for %s\n", ct, uname);
E 8
				return(0);
				/*NOTREACHED*/
			default:
D 8
				printf("Put failed %s\n", pw->pw_name);
E 8
I 8
				printf("Put failed %s\n", uname);
E 8
				return(1);
				/*NOTREACHED*/
		}
I 4
		return(3);
E 4
	}
	if (instringcase(function, "get")) {
D 8
		if (rc = (char *)pwck_get_history(pw->pw_name)) {
			printf("History for %s: %s\n", pw->pw_name, rc);
E 8
I 8
		if (rc = (char *)pwck_get_history(uname)) {
			printf("History for %s: %s\n", uname, rc);
E 8
D 4
			exit(0);
E 4
I 4
			return(0);
E 4
		} else {
D 8
			printf("No history for %s\n", pw->pw_name);
E 8
I 8
			printf("No history for %s\n", uname);
E 8
D 4
			exit(1);
E 4
I 4
			return(1);
E 4
		}
	}
	if (instringcase(function, "find")) {
I 8
		if (alt_user && (pw = getpwnam(alt_user)) == 0)
			die("Cannot get password info for %s\n", alt_user);
E 8
		if (rc = pwck_history(password, pw)) {
			printf("<%s> FOUND %s\n", password, rc);
D 4
			exit(0);
E 4
I 4
			return(0);
E 4
		} else {
			printf("<%s> NOT FOUND\n", password);
D 4
			exit(1); }
E 4
I 4
			return(1);
		}
E 4
	}
	return(0);
}
/* End %M% */
E 1
