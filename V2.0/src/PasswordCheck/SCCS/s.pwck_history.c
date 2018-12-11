h62228
s 00044/00000/00545
d D 1.31 99/07/23 16:35:33 clyde 31 30
c Add in_history() to search history for encrypted password
e
s 00026/00016/00519
d D 1.30 98/10/14 09:26:11 clyde 30 29
c 1. Fix history clean fencepost error better 
c 2. Add comments
e
s 00084/00059/00451
d D 1.29 98/10/13 17:38:23 clyde 29 28
c 1. Fix fencepost error in pwck_get_history()
c 2. Make comments prettier
c 3. Make some variable names more descriptive
e
s 00038/00028/00472
d D 1.28 98/09/30 15:15:24 clyde 28 27
c 1. Allow "-" in "history datbase" directives as shortcut for default DB
c 2. Deal with null return data from clean_history()
c 3. Deal with null arguments to clean_history()
e
s 00020/00000/00480
d D 1.27 98/07/17 11:14:28 clyde 27 26
c Add pwck_history_probe()
e
s 00002/00002/00478
d D 1.26 98/07/09 15:25:39 clyde 26 25
c Fix debug ifdef typo
e
s 00005/00002/00475
d D 1.25 98/07/09 14:29:00 clyde 25 24
c Use new pwsvc() routine
e
s 00003/00002/00474
d D 1.24 98/06/23 10:44:02 clyde 24 23
c Add timestamp argument to password_history_update(), pass to method routine
e
s 00005/00001/00471
d D 1.23 98/06/16 16:56:13 clyde 23 22
c 1. Add CDEBUG hook 
c 2. Use ENTRY_SEP_STR define
e
s 00053/00036/00419
d D 1.22 98/06/08 14:08:14 clyde 22 21
c 1. Fix possible history entry buffer overflows 
c 2. Change some variable names
e
s 00003/00003/00452
d D 1.21 98/06/04 09:50:31 clyde 21 20
c Change type of first param to password_history_update()
e
s 00140/00660/00315
d D 1.20 98/06/04 08:49:39 clyde 20 19
c 1. Move all method code into seperate files
c 2. Move common definitions to pwck_passwd.h
e
s 00085/00070/00890
d D 1.19 98/04/16 16:54:21 clyde 19 18
c Passed verification suite
c 1. Flat file functions
c 2. DBM database functions
c 3. History entry aging
c 4. History entry depth (on read side)
e
s 00478/00139/00482
d D 1.18 98/04/16 09:42:37 clyde 18 17
c First really working version
e
s 00001/00001/00620
d D 1.17 98/04/07 16:45:01 clyde 17 16
c Fix call of split
e
s 00071/00029/00550
d D 1.16 98/04/07 09:59:46 clyde 16 15
c 1. Add UT copyright
c 2. Change pwck_history() return type to (char *)
c 3. Change debug level to DB_PWCHECK
c 4. Disable NIS and NISPLUS history code (not verified)
e
s 00003/00004/00576
d D 1.15 98/03/26 10:57:19 clyde 15 14
c Fix buffer handling
e
s 00002/00002/00578
d D 1.14 97/09/23 12:22:53 clyde 14 13
c Use setreuid() rather than seteuid()
e
s 00005/00005/00575
d D 1.13 97/05/23 13:20:47 clyde 13 12
c 1. Fix configuration code 
c 2. Fix bugs in password compare code
e
s 00001/00001/00579
d D 1.12 97/04/14 10:47:25 clyde 12 11
c Change min age to 30 days
e
s 00002/00002/00578
d D 1.11 96/09/13 16:45:18 clyde 11 10
c Fix syntax errors in OSF code
e
s 00486/00140/00094
d D 1.10 96/09/12 16:26:55 clyde 10 9
c 1. Eliminate 'struct hpasswd'
c 2. Add NIS history lookup & modify routine
c 3. Add stub for NIS+ history routines
c 4. Add PasswordHistoryAge and PasswordHistoryDepth parameters
c 5. Add pwck_history_configure() 
c 6. Change debug tracing
c 7. Split out OSF history lookup code
c 8. Split out history file code
c 9. Cleanup comments & lots of misc
e
s 00002/00002/00232
d D 1.9 96/08/29 12:59:30 clyde 9 8
c Remove 'const' declarations (too much compiler trouble)
e
s 00002/00002/00232
d D 1.8 96/08/13 13:06:28 clyde 8 7
c Add const where useful
e
s 00008/00006/00226
d D 1.7 96/08/09 16:17:54 clyde 7 6
c Beta 3 development checkin 2
e
s 00068/00085/00164
d D 1.6 96/08/06 14:10:27 clyde 6 5
c Development checkin
e
s 00008/00008/00241
d D 1.5 95/04/05 16:20:05 clyde 5 4
c Beta 3 development checkin
e
s 00001/00001/00248
d D 1.4 94/05/19 10:34:26 clyde 4 3
c Check if OSF/1 security is enabled
e
s 00040/00002/00209
d D 1.3 94/05/17 14:26:48 clyde 3 2
c Add support for OSF1 security password history mechanism
e
s 00023/00007/00188
d D 1.2 94/03/16 11:10:19 clyde 2 1
c Generate good diagnostics
e
s 00195/00000/00000
d D 1.1 94/03/15 18:53:54 clyde 1 0
c date and time created 94/03/15 18:53:54 by clyde
e
u
U
t
T
I 1
D 16

E 16
I 16
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
E 16
/*  --------------------------------------------------------------------  */
/*                                                                        */
D 10
/*                        Author: Tomasz Surmacz                          */
E 10
I 10
/*                    Original Author: Tomasz Surmacz                     */
E 10
/*                   Institute of Technical Cybernetics                   */
/*                    Technical University of Wroclaw                     */
/*                                 Poland                                 */
/*                         tsurmacz@ict.pwr.wroc.pl                       */
/*                                                                        */
/* This code may be distributed freely, provided this notice is retained. */
/*                                                                        */
/*  --------------------------------------------------------------------  */
D 10
/* noreusal.c, v1.0, 15.11.1993
E 10
I 10
/* 
E 10
 *
D 10
 * This program is copyright Tomasz Surmacz 1993 (tsurmacz@ict.pwr.wroc.pl).
 * The author disclaims all responsibility or liability with respect to it's
 * usage or its effect upon hardware or computer systems, and maintains
 * copyright on this source.
E 10
I 10
 * This code 
E 10
 *
D 10
 * Permission is granted to copy and use this source in unmodified version
 * as part of the CRACKLIB package by Alec Muffet or any other package
 * improving password security on your system.
E 10
I 10
 * Form of password history entries:
E 10
 *
D 10
 * Form of the password history file:
 *  name:passwd:timestamp
E 10
I 10
 * name:passwd,timestamp:passwd,timestamp: ...
 * e.g.
 * joe:XFDJFDJFKDsf,1234450:xadierercx/,13344432
E 10
 */

D 3

E 3
#ifndef lint
D 30
static char sccsid[] = "@(#)pwck_history.c 1.0 12/11/93 (asic.ict.pwr.wroc.pl)";
E 30
static char vers_id[] = "noreusal.c : v1.0 Tomasz Surmacz 15 Nov 1993";
D 30
static char utid[] = "%W% %G% (cc.utexas.edu)";
E 30
I 30
static char sccsid[] = "%W% %G% (cc.utexas.edu)";
E 30
#endif

D 6
#include "compatibility.h"
#include "checkpassword.h"
#include "pwck_lib.h"
E 6
I 6
D 25
#include "pwck_defines.h"
E 25
E 6
#include "options.h"
I 25
#include "pwck_defines.h"
E 25
I 20
#include "pwck_history.h"
I 25
#include "pw_svc.h"
E 25
E 20

D 10
struct hpasswd {
	char	*name,		/* User name */
		*passwd;	/* Encrypted password */
D 5
	uid_t	uid;		/* User id */
E 5
I 5
	Uid_t	uid;		/* User id */
E 5
	char	*ts;		/* Timestamp */
};
E 10
I 10
D 20
private char *pwh_get_file _((char *));
D 18
private void  pwh_put_file _((char *, char *));
E 18
I 18
private int   pwh_put_file _((char *, char *));
E 18
E 10
D 6
#ifdef	__STDC__
private struct hpasswd *fgetSpwent(FILE *);
#else
private struct hpasswd *fgetSpwent();
#endif
E 6

D 6
#ifndef PASSWD_HISTORY_FILE
D 5
# define PASSWD_HISTORY_FILE "/etc/passwd.hist"
E 5
I 5
# define PASSWD_HISTORY_FILE "/usr/lib/passwd/passwd.hist"
E 5
#endif
E 6
I 6
D 7
private struct hpasswd *pwhist_file _((FILE *));
E 7
I 7
D 10
/* private struct hpasswd *pwhist_file _((FILE *)); */
private struct hpasswd *pwhist_file _((char *));
E 10
I 10
D 16
#ifdef	USE_NIS
E 16
I 16
D 18
#ifdef	USE_NIS_NOTYET
E 18
I 18
#ifdef	USE_NIS_UNSUPPORTED
E 18
E 16
private char *pwh_get_nis _((char *));
D 18
private void  pwh_put_nis _((char *, char *));
E 18
I 18
private int   pwh_put_nis _((char *, char *));
E 18
#endif
E 10
E 7
E 6

I 6
D 10
/* XXX this becomes a mechanism string:
E 10
I 10
D 16
#ifdef	USE_NISPLUS
E 16
I 16
D 18
#ifdef	USE_NISPLUS_NOTYET
E 18
I 18
#ifdef	USE_NISPLUS_UNSUPPORTED
E 18
E 16
private char *pwh_get_nisplus _((char *));
D 18
private char *pwh_put_nisplus _((char *, char *));
E 18
I 18
private int  *pwh_put_nisplus _((char *, char *));
E 18
#endif

D 18
private char *(*get)() = pwh_get_file;
private void (*put)() = pwh_put_file;
E 18
I 18
/* #ifdef	I_NDBM */
#if	1
/*
 * If NDBM is available, make it the default history database method
 */
private char *pwh_get_dbm _((char *));
private int   pwh_put_dbm _((char *, char *));
E 18

I 18
#define	DEFAULT_PUT	pwh_put_dbm
#define	DEFAULT_GET	pwh_get_dbm
#define	DEFAULT_METHOD	"dbm"

#else
/*
 * Default history database method is flat file
 */
#define	DEFAULT_PUT	pwh_put_file
#define	DEFAULT_GET	pwh_get_file
#define	DEFAULT_METHOD	"file"

#endif

E 20
private char *(*get)() = DEFAULT_GET;
private int   (*put)() = DEFAULT_PUT;

/*
D 20
 * Prototypes for functions
 */
private char *clean_hist _((char *, time_t));


I 19
#define	HIST_SEP	':'
E 19
E 18
#define	MIN_HISTORY_DEPTH	1
D 12
#define	MIN_HISTORY_AGE		7
E 12
I 12
#define	MIN_HISTORY_AGE		30
E 12

/*
E 20
 * Password history system parameters
E 10
 *
D 10
 *	file /foo/var
 *	nis map-name
 *	nisplus map-name
E 10
I 10
D 22
 * PasswordHistoryDB - Location of history database.
E 22
I 22
 * HistoryDB - Location of history database.
E 22
 *	This can be a file name, NIS map name or NIS+ table name.
I 20
 *
E 20
D 22
 * PasswordHistoryAge - Age limitation on history
E 22
I 22
 * HistoryAge - Age limitation on history
E 22
 * 	History entries older than this are ignored (does not work
 *	with OSF/1 password history).
I 20
 *	Setting to 0 disables password age checks.
 *
E 20
D 22
 * PasswordHistoryDepth - How many passwords are kept per user
E 22
I 22
 * HistoryDepth - How many passwords are kept per user
E 22
I 20
 *	Setting to 0 keeps all passwords.
E 20
 *
 * Default vaules are defined in ../options.h
I 20
 *
 * These vars are not static so that test_history.c can access them.
E 20
E 10
 */
E 6
D 10
public char	PasswordHistoryFile[MAXPATHLEN] = { PASSWD_HISTORY_FILE };
E 10
I 10
D 20
private char	*PasswordHistoryDB = PASSWORD_HISTORY_DB;
D 13
private time_t	PasswordHistoryAge = PASSWORD_HISTORY_AGE;
E 13
I 13
private time_t	PasswordHistoryAge = (PASSWORD_HISTORY_AGE * 86400);
E 13
private int	PasswordHistoryDepth = PASSWORD_HISTORY_DEPTH;
E 20
I 20
D 22
char	*PasswordHistoryDB = PASSWORD_HISTORY_DB;
time_t	PasswordHistoryAge = (PASSWORD_HISTORY_AGE * 86400);
int	PasswordHistoryDepth = PASSWORD_HISTORY_DEPTH;
char	*PasswordHistoryMethod = DEFAULT_METHOD;
E 22
I 22
char	*HistoryDB = PASSWORD_HISTORY_DB;
char	*HistoryMethod = DEFAULT_METHOD;
time_t	HistoryAge = (PASSWORD_HISTORY_AGE * 86400);
int	HistoryDepth = PASSWORD_HISTORY_DEPTH;
E 22
E 20
E 10

D 2
#define	MSG_SAMEAGAIN	"it has been used recently"
E 2
I 2
#define	MSG_REUSE	"it is not old enough (last used %s)"
I 3
#define	MSG_REUSE_NODATE "it is not old enough"
E 3
E 2
D 6
#define	ERR_NOHISTUPDATE	"Cannot update password history file\n"
E 6
I 6
D 18
#define	ERR_NOHISTUPDATE "Cannot update password history file\n"
E 6
D 2
#define	ERR_NOHISTFILE	"Password history file not found\n"
E 2
I 2
#define	ERR_NOHISTFILE	"Password history file \"%s\" not found\n"
E 18
I 18
D 20
#define	HISTORYDB_MODE	0600
E 20
E 18
E 2

/*
I 27
 * pwck_history_probe
 *	Print the state of the history mechanism to stdout
 * Usage:
 *	pwck_history_probe(char *message-prefix)
 */
public void
pwck_history_probe(prefix)
	char	*prefix;
{
	printf("%sdatabase ", prefix);
	if (HistoryDB == 0)
		printf("none\n");
	else
		printf("%s %s\n", HistoryMethod, HistoryDB);

	printf("%sage %d\n", prefix, (int )(HistoryAge / SEC_DAY));
	printf("%sdepth %d\n", prefix, HistoryDepth);
}

/*
E 27
D 10
 *	pw_cracklib - Wrapper for password history checking function
E 10
I 10
D 18
 * history_configure
E 18
I 18
 * pwck_history_configure
E 18
 *	Configure the history mechanism
 * Usage: 
D 18
 *	pwck_history_configure(char **configline, char *errormsg);
E 18
I 18
 *	pwck_history_configure(char **configline);
E 18
 * Returns:
D 18
 *	1 if configuration line was good
 *	0 if not
E 18
I 18
 *	(char *)0 if configuration line was good
 *	error message if not
E 18
 */
D 18
public int
pwck_history_configure(cfitem, cfargs, errmsg)
	char	*cfitem,
		**cfargs,
		*errmsg;
E 18
I 18
public char *
pwck_history_configure(args)
	char **args;
E 18
{
D 18
#define	cf_error(_w_) { (void) strcpy(errmsg, _w_); return(0); }
E 18
I 18
	char	*cfitem;
E 18

I 18
	if (args == 0)
		return("Missing argument list");
	cfitem = *args++;

E 18
	debug(DB_CONFIG,
D 18
		"pwck_history_configure: item '%s'\n", cfitem);
E 18
I 18
		"pwck_history_configure: [%s]\n", cfitem);
E 18
	
	if (instringcase(cfitem, "database")) {		/* Database selection */
		debug(DB_CONFIG,
D 18
			"pwck_history_configure: database '%s'\n", *cfargs);
		if (strcasecmp(*cfargs, "none") == 0) {
E 18
I 18
			"pwck_history_configure: database '%s'\n", *args);
		if (strcasecmp(*args, "none") == 0) {
E 18
D 22
			PasswordHistoryDB = 0;		/* History disabled */
E 22
I 22
			HistoryDB = 0;		/* History disabled */
E 22
			debug(DB_CONFIG, "pwck_history_configure: disable history\n");
D 18
			return(1);
E 18
I 18
			return(0);
E 18
		}
D 16
#ifdef	USE_NISPLUS
E 16
I 16
D 18
#ifdef	USE_NISPLUS_NOTYET
E 18
I 18
D 20
#ifdef	USE_NISPLUS_UNSUPPORTED
E 20
I 20

E 20
E 18
E 16
		/*
		 * History in a NIS+ table
		 */
D 18
		if (strcasecmp(*cfargs, "nisplus") == 0) {
			cfargs++;
			if (!*cfargs)
				cf_error("Missing NIS+ table name");
			PasswordHistoryDB = strdup(*cfargs);
E 18
I 18
		if (strcasecmp(*args, "nisplus") == 0) {
I 20
#ifdef	USE_NISPLUS_UNSUPPORTED
E 20
			args++;
			if (!*args)
				return("Missing NIS+ table name");
D 22
			PasswordHistoryDB = strdup(*args);
I 20
			PasswordHistoryMethod = "nisplus";
E 22
I 22
D 28
			HistoryDB = strdup(*args);
E 28
I 28
			if (strcmp(*args, HISTORYDB_DEFAULT))
				HistoryDB = strdup(*args);
E 28
			HistoryMethod = "nisplus";
E 22
E 20
E 18
			debug(DB_CONFIG,
				"pwck_history_configure: NIS+ table '%s'\n",
D 22
				PasswordHistoryDB);
E 22
I 22
				HistoryDB);
E 22
			get = pwh_get_nisplus;
			put = pwh_put_nisplus;
D 18
			return(1);
E 18
I 18
			return(0);
E 18
D 20
		}
E 20
I 20
#else
			return("NIS+ support not available");
E 20
#endif
D 16
#ifdef	USE_NIS
E 16
I 16
D 18
#ifdef	USE_NIS_NOTYET
E 18
I 18
D 20
#ifdef	USE_NIS_UNSUPPORTED
E 20
I 20
		}

E 20
E 18
E 16
		/*
		 * History in a NIS (YP) map
		 */
D 18
		if (strcasecmp(*cfargs, "nis") == 0) {
E 18
I 18
		if (strcasecmp(*args, "nis") == 0) {
E 18
D 20
#ifndef	SECURE_RPC
			die("NIS cannot be used for password history without secure RPC support.\n");
#endif
E 20
I 20
#ifdef	USE_NIS_UNSUPPORTED
# ifdef	SECURE_RPC
E 20
D 18
			cfargs++;
			if (!*cfargs)
				cf_error("Missing NIS map name");
			PasswordHistoryDB = strdup(*cfargs);
E 18
I 18
			args++;
			if (!*args)
				return("Missing NIS map name");
D 22
			PasswordHistoryDB = strdup(*args);
I 20
			PasswordHistoryMethod = "nis";
E 22
I 22
D 28
			HistoryDB = strdup(*args);
E 28
I 28
			if (strcmp(*args, HISTORYDB_DEFAULT))
				HistoryDB = strdup(*args);
E 28
			HistoryMethod = "nis";
E 22
E 20
E 18
			debug(DB_CONFIG,
				"pwck_history_configure: NIS map '%s'\n",
D 22
				PasswordHistoryDB);
E 22
I 22
				HistoryDB);
E 22
			get = pwh_get_nis;
			put = pwh_put_nis;
D 18
			return(1);
E 18
I 18
			return(0);
I 20
# else	/* SECURE_RPC */
			return("Secure RPC support not available");
# endif	/* SECURE_RPC */
#else	/* USE_NIS_UNSUPPORTED */
			return("NIS support not available");
#endif	/* USE_NIS_UNSUPPORTED */
E 20
E 18
		}
D 20
#endif
I 18
/* #ifdef	I_DBM */
#if	1
E 20
I 20

E 20
E 18
		/*
D 18
		 * History in a local file
E 18
I 18
		 * History in a local DBM database
E 18
		 */
D 18
		if (strcasecmp(*cfargs, "file") == 0)	/* "file" is optional */
			cfargs++;
		if (**cfargs != '/') 		/* Naked file name */
			cf_error("Bad history database specification");
E 18
I 18
		if (strcasecmp(*args, "dbm") == 0) {
I 20
#ifdef	I_NDBM
E 20
			args++;
			if (!*args)
				return("Missing DBM name");
I 28
			if (strcmp(*args, HISTORYDB_DEFAULT)) {
E 28
I 23
D 26
#if	(CDEBUG < DB_VERBOSE)
E 26
I 26
#if	(CDEBUG < CDEBUG_FILES)
E 26
E 23
D 19
			if (**args != '/') 		/* Naked file name */
				return("Bad history database specification");
E 19
I 19
D 20
#ifdef REMOVE_BEFORE_FLIGHT
E 20
D 28
			if (**args != '/')
				return("Bad file name");
E 28
I 28
				if (**args != '/')
					return("Bad file name");
E 28
I 23
#endif
E 23
D 20
#endif
E 20
E 19
D 22
			PasswordHistoryDB = strdup(*args);
I 20
			PasswordHistoryMethod = "dbm";
E 22
I 22
D 28
			HistoryDB = strdup(*args);
E 28
I 28
				HistoryDB = strdup(*args);
			}
E 28
			HistoryMethod = "dbm";
E 22
E 20
			debug(DB_CONFIG,
				"pwck_history_configure: DBM database '%s'\n",
D 22
				PasswordHistoryDB);
E 22
I 22
				HistoryDB);
E 22
			get = pwh_get_dbm;
			put = pwh_put_dbm;
			return(0);
D 20
		}
E 20
I 20
#else
			return("DBM support not available");
E 20
#endif
I 20
		}

E 20
		/*
		 * History in a flat file
		 */
D 19
		if (strcasecmp(*args, "file") == 0)	/* "file" is optional */
E 19
I 19
		if (strcasecmp(*args, "file") == 0) {
E 19
			args++;
E 18
D 19

E 19
I 19
			if (!*args)
				return("Missing file name");
I 28
			if (strcmp(*args, HISTORYDB_DEFAULT)) {
E 28
I 23
D 26
#if	(CDEBUG < DB_VERBOSE)
E 26
I 26
#if	(CDEBUG < CDEBUG_FILES)
E 26
E 23
D 20
#ifdef REMOVE_BEFORE_FLIGHT
E 20
D 28
			if (**args != '/')
				return("Bad file name");
E 28
I 28
				if (**args != '/')
					return("Bad file name");
E 28
I 23
#endif
E 23
D 20
#endif
E 20
E 19
D 18
		PasswordHistoryDB = strdup(*cfargs);
		debug(DB_CONFIG,
			"pwck_history_configure: file '%s'\n",
			PasswordHistoryDB);
		get = pwh_get_file;
		put = pwh_put_file;
		return(1);
E 18
I 18
D 22
			PasswordHistoryDB = strdup(*args);
I 20
			PasswordHistoryMethod = "file";
E 22
I 22
D 28
			HistoryDB = strdup(*args);
E 28
I 28
				HistoryDB = strdup(*args);
			}
E 28
			HistoryMethod = "file";
E 22
E 20
			debug(DB_CONFIG,
				"pwck_history_configure: file '%s'\n",
D 22
				PasswordHistoryDB);
E 22
I 22
				HistoryDB);
E 22
			get = pwh_get_file;
			put = pwh_put_file;
			return(0);
		}
		/*
		 * Fallthrough - use the default method
		 */
D 19
		if (**args != '/') 		/* Naked file name */
			return("Bad history database specification");

		PasswordHistoryDB = strdup(*args);
		get = DEFAULT_GET;
		put = DEFAULT_PUT;
		debug(DB_CONFIG, "pwck_history_configure: default %s '%s'\n",
			DEFAULT_METHOD, PasswordHistoryDB);
		return(0);
E 19
I 19
		if (**args == '/') {		/* Naked file name */
D 22
			PasswordHistoryDB = strdup(*args);
E 22
I 22
			HistoryDB = strdup(*args);
E 22
			get = DEFAULT_GET;
			put = DEFAULT_PUT;
			debug(DB_CONFIG, "pwck_history_configure: default %s '%s'\n",
D 22
				DEFAULT_METHOD, PasswordHistoryDB);
E 22
I 22
				DEFAULT_METHOD, HistoryDB);
E 22
			return(0);
		}
		return("Bad history database specification");
E 19
E 18
	}

	if (instringcase(cfitem, "age")) {	/* Active history age */
D 13
		int	t = decode_int(*++cfargs);
E 13
I 13
D 18
		int	t = decode_int(*cfargs);
E 18
I 18
		int	t;
E 18
E 13

D 18
		if (t < 0)
			cf_error("Bad history age specification");
E 18
I 18
D 19
		if (xatoi(*args, (char *)0, &t) == 0)
E 19
I 19
		if (xatoi(*args, (char **)0, &t) == 0)
E 19
			return("Bad history age specification");
E 18
D 20
		if (t < MIN_HISTORY_AGE)
E 20
I 20
		if (t < MIN_HISTORY_TIMEOUT)
E 20
D 18
			cf_error("History age too short");
		PasswordHistoryAge = (t * 86400);
E 18
I 18
			return("History age too short");
D 22
		PasswordHistoryAge = (time_t )(t * SEC_DAY);
E 22
I 22
		HistoryAge = (time_t )(t * SEC_DAY);
E 22
E 18
		debug(DB_CONFIG,
			"pwck_history_configure: age %d days\n", t);
D 18
		return(1);
E 18
I 18
		return(0);
E 18
	}

	if (instringcase(cfitem, "depth")) {	/* Active history depth */
D 13
		int	t = decode_int(*++cfargs);
E 13
I 13
D 18
		int	t = decode_int(*cfargs);
E 18
I 18
		int	t = decode_int(*args);
E 18
E 13

		if (t < 0)
D 18
			cf_error("Bad history depth specification");
E 18
I 18
			return("Bad history depth specification");
E 18
		if (t < MIN_HISTORY_DEPTH)
D 18
			cf_error("History depth too small");
E 18
I 18
			return("History depth too small");
E 18
D 22
		PasswordHistoryDepth = t;
E 22
I 22
		HistoryDepth = t;
E 22
		debug(DB_CONFIG,
			"pwck_history_configure: depth %d\n", t);
D 18
		return(1);
E 18
I 18
		return(0);
E 18
	}
D 18
	return(0);
#undef	cf_error
E 18
I 18
	return("Unknown history directive");
E 18
}

I 20
D 30
private int bytime(a1, a2)
	void *a1, *a2;
E 30
I 30
/*
 * bytime
 *	Sort function to compare history items by timestamp
 *
 * Returns:
 *	 0 if items are the same age
 *	 1 if item1 younger than item2
 *	-1 if item1 older than item2
 */
private int
bytime(a1, a2)
	void	*a1,		/* Pointer to item 1 */
		*a2;		/* Pointer to item 2 */
E 30
{
D 30
	char	*t;
	time_t	t1 = 0,
		t2 = 0;
	char **c1 = (char **)a1;
	char **c2 = (char **)a2;
E 30
I 30
	char	*t;		/* Temp */
	time_t	t1 = 0,		/* Item 1 time */
		t2 = 0;		/* Item 2 time */
	char **c1 = (char **)a1; /* Char pointer to item 1 */
	char **c2 = (char **)a2; /* Char pointer to item 2 */
E 30

	if (*c1 && (t = strchr(*c1, FIELD_SEP)))
		t1 = (time_t )atol(++t);
	if (*c2 && (t = strchr(*c2, FIELD_SEP)))
		t2 = (time_t )atol(++t);
I 30
	/* time_t is unsigned - cannot do "return(t1 - t2)" */
E 30
	if (t1 > t2) return(-1);
	if (t1 < t2) return(1);
	return(0);
}

E 20
I 18
/*
I 20
 * clean_history
 *	Filter a history line, remove old and extra passwords
 *
D 29
 * Usage
 *	new-history = clean_history(old-history);
E 29
I 29
 * Returns:
 *	Address of buffer containing the cleaned entry or
 *	NULL on error
 *
 * Effects:
 *	The cleaned entry is copied back into the <data> argument buffer
E 29
 */
public char *
D 22
clean_history(data)
E 22
I 22
clean_history(data, depth, age, epoch, maxlen)
E 22
	char	*data;		/* History entry */
I 22
	int	depth;		/* How many passwords to keep */
	time_t	age,		/* Password retention limit */
		epoch;		/* Current time */
D 29
	size_t	maxlen;		/* Maximum line length */
E 29
I 29
	size_t	maxlen;		/* Sizeof <data> */
E 29
E 22
{
D 28
	char	*nd = calloc((strlen(data) + 2), sizeof(char));
	char	**hv = split(data, ENTRY_SEP, 0, 0),
E 28
I 28
D 29
	char	*nd;
	char	**hv,
E 28
		**hp;
	int	seen = 0;
	int	i;
E 29
I 29
	char	*newdata;	/* New version of <data> */
	char	**hvec,		/* Split version of <data> */
		**hptr;		/* List traversal temp */
	int	seen = 0;	/* How many passwords in this entry */
	int	i;		/* Temp */
E 29
D 22
	time_t	now = time((time_t *)0);
E 22
I 22
	time_t	now = epoch ? epoch : time((time_t *)0);
I 29
				/* Epoch for time comparisons */
E 29
E 22

I 28
D 29
	if (data == 0)
		return(0);
	nd = calloc((strlen(data) + 2), sizeof(char));
E 28
	if (nd == 0)
		logdie("(clean_history) Cannot allocate memory");
I 22
	if (maxlen == 0)
		maxlen = HISTORY_RECLEN;
E 29
I 29
	if (data == NULL)
		return(NULL);
E 29
E 22

I 29
	if ((newdata = calloc((strlen(data) + 2), sizeof(char))) == NULL)
		logdie("(clean_history) No memory for history copy");

	if (maxlen == 0)			/* Assume buffer length */
		maxlen = HISTORY_RECLEN;	/* if not given by caller */

E 29
	/*
	 * Sort the entries by time - youngest first
	 */
I 28
D 29
	hv = split(data, ENTRY_SEP, 0, 0);
E 28
	for (hp = hv, i = 0; *hp; hp++, i++);
	if (i > 1)
		qsort((void *)hv, i, sizeof(char *), bytime);
E 29
I 29
	if ((hvec = split(data, ENTRY_SEP, 0, 0)) == 0)
		logdie("(clean_history) History split failed");
E 29

D 29
	for (hp = hv; *hp; hp++) {
E 29
I 29
	for (hptr = hvec, i = 0; *hptr; hptr++, i++);	/* Get size of list */
	if (i > 1)				/* Sort in time order */
		qsort((void *)hvec, i, sizeof(char *), bytime);

	for (hptr = hvec; *hptr; hptr++) {		/* Traverse the list */
E 29
		char	*t;
		time_t	pwtime;

D 29
		if (t = strchr(*hp, FIELD_SEP)) {
E 29
I 29
		if (t = strchr(*hptr, FIELD_SEP)) {
E 29
 			*t = 0;
			pwtime = (time_t )atol(t+1);
 			*t = FIELD_SEP;
		} else {
D 22
			logerr("Malformed history entry '%s'", data);
E 22
I 22
			logerr("(clean_history) Bad entry '%s'", data);
E 22
			continue;
		}
D 22
		if (PasswordHistoryAge &&
		   (now - pwtime) > PasswordHistoryAge) {
E 22
I 22
		if (age && (now - pwtime) > age) {
E 22
			debug(DB_PWCHECK,
				"clean_history: old '%s' age = %lu limit = %lu\n",
D 22
				*hp, (now - pwtime), PasswordHistoryAge);
E 22
I 22
D 29
				*hp, (now - pwtime), age);
E 29
I 29
				*hptr, (now - pwtime), age);
E 29
E 22
			continue;
		}
		/*
D 22
		 * Ignore if more than <PasswordHistoryDepth>
E 22
I 22
D 30
		 * Ignore if more than <HistoryDepth>
E 22
		 * have already been seen
E 30
I 30
		 * Ignore if more than <HistoryDepth> have already been seen
		 *
		 * "HistoryDepth" means "how many old passwords matter"
		 * (hence use "seen++")
E 30
		 */
D 22
		if (PasswordHistoryDepth && ++seen > PasswordHistoryDepth) {
E 22
I 22
D 30
		if (depth && ++seen > depth) {
E 30
I 30
		if (depth && seen++ > depth) {
E 30
E 22
			debug(DB_PWCHECK,
				"clean_history: Depth limit %d reached, discard '%s'\n",
D 22
				PasswordHistoryDepth, *hp);
E 22
I 22
D 29
				depth, *hp);
E 29
I 29
				depth, *hptr);
E 29
E 22
			continue;
		}
I 22
		/*
		 * Length check - don't go over HISTORY_RECLEN chars
		 * Old items will be discarded.
		 */
D 29
		if ((strlen(nd) + strlen(*hp) + 1) > maxlen) {
E 29
I 29
		if ((strlen(newdata) + strlen(*hptr) + 1) > maxlen) {
E 29
			debug(DB_PWCHECK,
				"clean_history: length limit %d reached, discard '%s'\n",
D 29
				maxlen, *hp);
E 29
I 29
				maxlen, *hptr);
E 29
			continue;
		}
I 25
D 29
	/* Always want to save the *most recent* password */ /* XXX */
E 25
E 22
		if (*nd) {
D 23
			(void) strcat(nd, ":");
E 23
I 23
			(void) strcat(nd, ENTRY_SEP_STR);
E 23
			(void) strcat(nd, *hp);
E 29
I 29
		if (*newdata) {
			(void) strcat(newdata, ENTRY_SEP_STR);
			(void) strcat(newdata, *hptr);
E 29
		}
		else {
D 29
			(void) strcpy(nd, *hp);
E 29
I 29
			(void) strcpy(newdata, *hptr);
E 29
		}
	}
D 29
	free((char *)hv);
	(void) strcpy(data, nd);
	free(nd);
E 29
I 29
	/*
	 * Try to return the youngest password (first in the sorted
	 * list), even if it is too old.
	 */
	if (*newdata == 0 && *hvec) {
		(void) strcpy(newdata, *hvec);
		debug(DB_PWCHECK,
			"clean_history: Null list backoff '%s'\n", *hvec);
	}

	free((char *)hvec);
	(void) strcpy(data, newdata);
	free(newdata);
E 29
	debug(DB_PWCHECK, "clean_history: Return <%s>\n", data);
	return(data);
}

/*
E 20
D 29
 * pwck_get_history - Fetch history entry
E 29
I 29
 * pwck_get_history
 *	Fetch history entry for user
E 29
 *
D 29
 * Returns
 *	History for <user->pw_name> if found
 *	(char *)0 if not
 *
 * A routine seperate from pwck_history() is needed for the test
D 19
 * suite to verify the history database lookup functions
E 19
I 19
 * suite to verify the raw history database lookup
E 29
I 29
 * Returns:
 *	Value from db method get() routine
 *	NULL if history not found or error
E 29
E 19
 */
public char *
D 19
pwck_get_history(password, user)
	char	*password;	/* Password to check (plaintext) */
	struct passwd	*user;	/* Passwd info for user */
E 19
I 19
pwck_get_history(user)
	char *user;	/* Name of user */
E 19
{
D 29
	char	*rc;
E 29
I 29
	char	*rc;	/* Return code */
E 29
E 18

I 18
D 22
	if (PasswordHistoryDB == 0 || *PasswordHistoryDB == 0)
E 22
I 22
D 28
	if (HistoryDB == 0 || *HistoryDB == 0)
E 28
I 28
D 29
	if (HistoryDB == 0 || *HistoryDB == 0 || user == 0)
E 28
E 22
		return(0);		/* No history */
E 29
I 29
	if (user == 0)			/* Null user? */
		return(NULL);
	if (HistoryDB == NULL || *HistoryDB == 0)
		return(NULL);		/* No history */
E 29

D 19
	if (rc = (*get)(user->pw_name)) {
E 19
I 19
	if (rc = (*get)(user))
E 19
		return(rc);
D 19
	debug(DB_PWCHECK, "pwck_history: no history for %s\n", user->pw_name);
E 19
I 19
	debug(DB_PWCHECK, "pwck_history: no history for %s\n", user);
E 19
D 29
	return(0);
E 29
I 29
	return(NULL);
E 29
}

E 18
/*
D 18
 *	pwck_history - Wrapper for password history checking function
E 18
I 18
 * pwck_history - Wrapper for password history checking function
E 18
E 10
 *
D 18
 *	Returns:
D 6
 *		PWCK_INDICT if password exists in the history file
E 6
I 6
D 16
 *		PWCK_REUSE if password exists in the history file
E 6
 *		PWCK_OK if otherwise
E 16
I 16
 *		Message if password exists in the history database
 *		(char *)0 if not
E 18
I 18
 * Returns:
 *	Message if password exists in the history database
D 29
 *	(char *)0 if not
E 29
I 29
 *	'PWCK_OK' if not
E 29
E 18
E 16
 */
D 16
public int
pwck_history(password, user, mesg)
E 16
I 16
public char *
pwck_history(password, user)
E 16
D 8
	char	*password;	/* Password to check (plaintext) */
	struct passwd	*user;	/* Passwd info for user */
E 8
I 8
D 9
	const char	*password;	/* Password to check (plaintext) */
	const struct passwd	*user;	/* Passwd info for user */
E 9
I 9
	char	*password;	/* Password to check (plaintext) */
	struct passwd	*user;	/* Passwd info for user */
E 9
E 8
D 16
	char	*mesg;		/* Message buffer */
E 16
{
I 19
D 20
	int	seen = 0;
E 20
E 19
D 6
	char *reason;
	FILE *f;
	struct hpasswd *pwdata;
	int m;
E 6
I 6
D 10
	struct hpasswd *pwdata = 0;
E 10
I 10
D 18
	char	*histent;
	char	**hv,
		**plist;
	int	rc;
E 18
I 18
D 29
	char	*histent,
		**hv,
		**plist,
I 19
D 20
		**pend,
E 20
E 19
		*rval = PWCK_OK;
I 25
	struct pw_svc *svc = get_pwsvc();
E 25
E 18
D 20
	time_t	now = time((time_t *)0);
E 20
I 16
	static char mesg[STRINGLEN];
E 29
I 29
	char	*histent,		/* History data */
		**hv,			/* Split history data */
		**plist,		/* History entry traversal */
		*rval = PWCK_OK;	/* Return value */
	static char mesg[STRINGLEN];	/* Error message buffer */
	struct pw_svc *svc = get_pwsvc(); /* Password service */
E 29
E 16
E 10
E 6

D 7
#ifndef	PASSWORD_HISTORY
	return(PWCK_OK);
#endif
E 7
I 7
D 10
#ifdef	PASSWORD_HISTORY
E 7
#ifdef	DEBUG
	printf("pwck_history: \"%s\"\n", password);
#endif
E 10
I 10
D 13
	debug(DB_NONE, "pwck_history: %s \"%s\"\n", user->pw_name, password);
E 13
I 13
D 18
	debug(DB_VERBOSE, "pwck_history: %s \"%s\"\n", user->pw_name, password);
E 18
I 18
	debug(DB_VERBOSE, "pwck_history: %s '%s'\n", user->pw_name, password);
E 18
E 13

E 10
I 3
D 5
#ifdef	OSF1_SECURITY
E 5
I 5
D 18
#ifdef	OSF1_AUTH
E 18
I 18
#ifdef	OSF1_AUTH	/* And maybe HPUX_AUTH also */
	{
	char	*rc;

E 18
E 5
D 10
	/*
	 * Look up the auth record for this user and check this password
	 * against the passwords there.
	 */
D 4
	{
E 4
I 4
	if (access(OSF1_TCB, 0) == 0) {
E 4
		struct pr_passwd *pw;
E 10
I 10
D 11
	if (rc = osf_history_check(password, user, mesg)) != PWCK_OK)
E 11
I 11
D 16
	if ((rc = osf_history_check(password, user, mesg)) != PWCK_OK)
E 16
I 16
	if ((rc = osf_history_check(password, user)) != PWCK_OK)
E 16
E 11
		return(rc);
I 18
	}
E 18
#endif
D 18
	if (PasswordHistoryDB == 0 || *PasswordHistoryDB == 0)
E 18
I 18
D 19
	if ((histent = pwck_get_history(password, user)) == 0)
E 19
I 19
	if ((histent = pwck_get_history(user->pw_name)) == 0)
E 19
E 18
		return(PWCK_OK);		/* No history */
E 10

D 10
		if ((pw = getprpwnam(user->pw_name)) != NULL &&
		     pw->uflg.fg_pwdict && pw->ufld.fd_pwdict[0]) {
D 6
			char *ts, *te, *xc;
E 6
I 6
			char **ts, **tl;
E 10
I 10
D 18
	if ((histent = (*get)(user->pw_name)) == 0) {
D 16
		debug(DB_LOOKUP, "pwck_history: no history for %s\n", user->pw_name);
E 16
I 16
		debug(DB_PWCHECK, "pwck_history: no history for %s\n", user->pw_name);
E 16
		return(PWCK_OK);		/* No history */
	}
E 10
E 6

E 18
I 18
D 20
	/*
D 19
	 * Traverse the history, comparing the candidate password
	 * to that in each recent (younger than PasswordHistoryAge) entry.
E 19
I 19
	 * Traverse the history from end to front
	 * (to enforce PasswordHistoryDepth)
E 19
	 */
E 18
D 6
			ts = te = pw->ufld.fd_pwdict;	
			while (*ts) {
				while (*te && *te != ',') *te++; 
				if (*te)
					*te++ = '\0';
				xc = crypt(password, ts);
				if (strlen(ts) > strlen(xc))
E 6
I 6
D 10
			for (ts = tl = split(pw->ufld.fd_pwdict, ',', 0,0,0);
			     *ts; ts++)) {
				char	*xc;
E 10
I 10
D 17
	hv = (char **)split(histent, ':', 0, 0, 0);
E 17
I 17
D 19
	hv = (char **)split(histent, ':', 0, 0);
E 17
D 18
	for (plist = &hv[1]; *plist; plist++) {	/* hv[0] == username */
		char	*pwtext,
			*pwtm;
		char	*t;
		time_t	pwtime;
E 18
I 18
	for (plist = hv; *plist; plist++) {
		char	*t;			/* Temp */
		time_t	pwtime;			/* History entry time */
E 19
I 19
	hv = split(histent, HIST_SEP, 0, 0);
	for (pend = hv; *pend; pend++);		/* Find end */
E 19
E 18
E 10

I 19
	for (plist = --pend; plist >= hv; plist--) {
E 20
I 20
D 22
	hv = split(clean_history(histent), ENTRY_SEP, 0, 0);
E 22
I 22
D 28
	hv = split(
		clean_history(histent, HistoryDepth, HistoryAge, 0, 0),
			ENTRY_SEP, 0, 0);
E 22
	for (plist = hv; *plist; plist++) {
E 20
		char	*t;
E 28
I 28
D 29
	if (hv = split(clean_history(histent, HistoryDepth, HistoryAge, 0, 0),
E 29
I 29
D 30
	/*
	 * Use "HistoryDepth" as "the number of old passwords which matter"
	 */
	if (hv = split(clean_history(histent, HistoryDepth+1, HistoryAge, 0, 0),
E 30
I 30
	if (hv = split(clean_history(histent, HistoryDepth, HistoryAge, 0, 0),
E 30
E 29
			ENTRY_SEP, 0, 0)) {
		for (plist = hv; *plist; plist++) {
D 29
			char	*t;
E 29
I 29
			char	*t;	/* Temp */
E 29
E 28
D 20
		time_t	pwtime;
E 20

D 20
		/*
		 * Reject if too old
		 */
E 19
D 10
				xc = crypt(password, *ts);
				if (strlen(*ts) > strlen(xc))
E 6
					xc = bigcrypt(password, ts);
D 6
				if (strcmp(xc, ts) == 0) {
E 6
I 6
				if (strcmp(xc, *ts) == 0) {
E 6
					(void) strcpy(mesg, MSG_REUSE_NODATE);
I 6
					free((char *)tl);
E 6
					return(PWCK_REUSE);
				}
D 6
				ts = te;
E 6
			}
I 6
			free((char *)tl);
E 10
I 10
D 18
		pwtext = *plist;
		if (pwtm = strchr(pwtext, ',')) {
 			*pwtm++ = 0;
			pwtime = (time_t )atol(pwtm);
E 18
I 18
		if (t = strchr(*plist, ',')) {
 			*t++ = 0;
E 20
I 20
D 28
		if (t = strchr(*plist, FIELD_SEP)) {
			time_t	pwtime;
E 28
I 28
			if (t = strchr(*plist, FIELD_SEP)) {
D 29
				time_t	pwtime;
E 29
I 29
				time_t	pwtime;		/* Current time */
E 29
E 28

D 28
			*t++ = 0;
E 20
			pwtime = (time_t )atol(t);
I 19
D 20
			if (PasswordHistoryAge &&
			   (now - pwtime) > PasswordHistoryAge) {
				debug(DB_PWCHECK,
				"pwck_history: Too old age = %u limit = %u\n",
				(now - pwtime), PasswordHistoryAge);
				continue;
E 20
I 20
D 25
			t = (*svc.PasswdCrypt)(password, *plist);
E 25
I 25
			t = (*svc->PasswdCrypt)(password, *plist);
E 25
			if (strcmp(t, *plist) == 0) {	/* Found <password> */
				char	*ct = ctime(&pwtime);
E 28
I 28
				*t++ = 0;
				pwtime = (time_t )atol(t);
				t = (*svc->PasswdCrypt)(password, *plist);
				if (strcmp(t, *plist) == 0) {	/* Found <password> */
					char	*ct = ctime(&pwtime);
E 28

D 28
				chop_nl(ct);
				(void) sprintf(mesg, MSG_REUSE, &ct[4]);
				rval = mesg;
				break;
E 28
I 28
					chop_nl(ct);
					(void) sprintf(mesg, MSG_REUSE, &ct[4]);
					rval = mesg;
					break;
				}
E 28
E 20
			}
E 19
E 18
D 20
		} else {
D 19
			(void) time(&pwtime);	/* Malformed entry */
E 19
I 19
			logerr("Malformed history entry '%s'", histent);
E 20
E 19
E 10
E 6
		}
I 28
		free((char *)hv);
E 28
I 6
D 10
		return(PWCK_OK);
E 10
I 10
D 19
		if (PasswordHistoryAge &&
		   (now - pwtime) > PasswordHistoryAge) {
E 19
I 19
D 20
		/*
		 * Ignore if more than <PasswordHistoryDepth> 
		 * have already been seen
		 */
		if (PasswordHistoryDepth && ++seen > PasswordHistoryDepth) {
E 19
D 15
#ifdef	DEBUG
E 15
D 16
			debug(DB_LOOKUP,
E 16
I 16
			debug(DB_PWCHECK,
E 16
D 15
				"pwck_history: Too old age=%u limit=%u\n",
E 15
I 15
D 19
				"pwck_history: Too old age = %u limit = %u\n",
E 15
				(now - pwtime), PasswordHistoryAge);
D 15
#endif
E 15
			continue;
E 19
I 19
				"pwck_history: Depth limit %d reached\n",
				PasswordHistoryDepth);
			break;
E 19
		}
D 18
		t = (*svc.PasswdCrypt)(password, pwtext);
D 13
		if (strcmp(t, user->pw_passwd) == 0) {
E 13
I 13
		if (strcmp(t, pwtext) == 0) {
E 13
			char	*ct;
E 18
I 18
		t = (*svc.PasswdCrypt)(password, *plist);
		if (strcmp(t, *plist) == 0) {		/* Found <password> */
			char	*ct = ctime(&pwtime);
E 18

D 16
			debug(DB_LOOKUP, "pwck_history: found\n");
E 16
I 16
D 18
			debug(DB_PWCHECK, "pwck_history: found\n");
E 16
			free((char *)hv);
			ct = ctime(&pwtime);
E 18
			chop_nl(ct);
D 18
			(void) sprintf(mesg, MSG_REUSE, ct);
D 16
			return(PWCK_REUSE);
E 16
I 16
			return(mesg);
E 18
I 18
			(void) sprintf(mesg, MSG_REUSE, &ct[4]);
			rval = mesg;
			break;
E 18
E 16
		}
E 20
E 10
E 6
	}
I 10
D 28
	free((char *)hv);
E 28
D 16
	debug(DB_LOOKUP, "pwck_history: not found\n");
E 16
I 16
D 18
	debug(DB_PWCHECK, "pwck_history: not found\n");
E 16
	return(PWCK_OK);
E 18
I 18
D 19
	debug(DB_PWCHECK, "pwck_history: %s found\n", rval ? "" : "not");
E 19
I 19
	debug(DB_PWCHECK, "pwck_history: %s\n", rval ? rval : "not found");
E 19
	return(rval);
E 18
}

/*
I 31
 * in_history
 *	Look for an encrypted password in the history
 *
 * Returns:
 *	1 if password exists in the history database
 *	0 if now
 */
public
in_history(user, crypt_text)
	char *user;		/* User name */
	char *crypt_text;	/* Password to search for (encrytped) */
{
	char	*histent,		/* History data */
		**hv,			/* Split history data */
		**plist;		/* History entry traversal */
	int	rval = 0;
	struct pw_svc *svc = get_pwsvc(); /* Password service */

	debug(DB_VERBOSE, "in_history: %s '%s'\n", user, crypt_text);

	if ((histent = pwck_get_history(user)) == 0)
		return(0);		/* No history */

	if (hv = split(
		clean_history(histent, HistoryDepth, HistoryAge, 0, 0),
			ENTRY_SEP, 0, 0)) {
		for (plist = hv; *plist; plist++) {
			char	*t;	/* Temp */

			if (t = strchr(*plist, FIELD_SEP)) {
				*t++ = 0;
				if (strcmp(*plist, crypt_text) == 0) {
					rval = 1;
					break;
				}
			}
		}
		free((char *)hv);
	}
	debug(DB_PWCHECK, "in_history: %s\n", rval ? "found" : "not found");
	return(rval);
}

/*
E 31
 * password_history_update()
D 29
 *	Store password in history database.
E 29
I 29
 *	Store password in history database
E 29
 * Usage
 *	pwck_history_update(struct passwd *user, char *crypted_password);
I 29
 * Returns:
 *	Value from db method put() routine or
 *	0 if history disabled or null argument
E 29
 */
D 18
public void
E 18
I 18
public int
E 18
D 24
password_history_update(user, crypted_password)
E 24
I 24
password_history_update(user, crypted_password, epoch)
E 24
D 21
	struct passwd	*user;
	char *crypted_password;
E 21
I 21
D 29
	char	*user,
		*crypted_password;
I 24
	time_t	epoch;
E 29
I 29
	char	*user,			/* User name */
		*crypted_password;	/* Encrypted password */
	time_t	epoch;			/* Timestamp */
E 29
E 24
E 21
{
D 18
#ifdef	OSF1_AUTH
	if (osf_history_update(user, crypted_password))
E 18
I 18
#ifdef	OSF1_AUTH	/* And maybe HPUX_AUTH also */
D 19
	if (osf_history_update(user, crypted_password))	/* XXX */
E 19
I 19
	if (osf_history_update(user, crypted_password))
E 19
E 18
		return;
E 10
#endif
I 29
	if (user == 0)			/* Null user? */
		return(0);
E 29
E 3
D 2

E 2
D 6
	if ((f = fopen(PasswordHistoryFile, "rt")) == NULL) {
D 2
		fprintf(stderr, ERR_NOHISTFILE);
E 2
I 2
		fprintf(stderr, ERR_NOHISTFILE, PasswordHistoryFile);
E 2
		return(PWCK_OK);  /* print warning and accept password */
E 6
I 6
D 10
#ifdef	USE_NISPLUS
	pwdata = pwhist_nisplus(user->pw_name);
#endif
	if (pwdata == 0)
		pwdata = pwhist_file(user->pw_name);
E 10
I 10
D 22
	if (PasswordHistoryDB == 0 || *PasswordHistoryDB == 0)
E 22
I 22
	if (HistoryDB == 0 || *HistoryDB == 0)
E 22
D 18
		return;			/* No history */
	(*put)(user->pw_name, crypted_password);
E 18
I 18
D 29
		return(0);	/* No history */
E 29
I 29
		return(0);		/* No history */
E 29
D 21
	return((*put)(user->pw_name, crypted_password));
E 21
I 21
D 24
	return((*put)(user, crypted_password));
E 24
I 24
	return((*put)(user, crypted_password, epoch));
E 24
E 21
E 18
}
E 10
D 20

D 10
	if (pwdata == 0) {		/* User has no password history */
E 10
I 10
/*
 * Password history "method" modules
 */

D 18
#ifdef	OSF1_AUTH
E 18
I 18
#ifdef	OSF1_AUTH	/* And maybe HPUX_AUTH also */
E 18
/*
 * osf_history_check
 *	Check OSF/1 password history database
 * Usage:
 *	return-code = osf_history_check(char *password,
 *			struct passwd *user, char *mesg);
 * Returns:
D 18
 *	PWCK_OK if <password> not found in history list
 *	PWCK_REUSE if <password> was found in history list
E 18
I 18
 *	Message if <password> was found in history list
 *	0 if not
E 18
 */
D 16
private int
osf_history_check(password, user, mesg)
E 16
I 16
private char *
osf_history_check(password, user)
E 16
	char	*password;		/* Password to check (plaintext) */
	struct passwd	*user;		/* Who to check for */
D 16
	char	*mesg;			/* Where to stash messages */
E 16
{
	struct pr_passwd *pw;

	if (access(OSF1_TCB, 0) < 0)	/* AuthDB not in use */
E 10
		return(PWCK_OK);
E 6
D 10
	}
D 6
	while (pwdata = fgetSpwent(f)) {
E 6
I 6
D 7
	if (strcmp(pwdata->passwd,	/* XXX Depend on npasswd main.c */
	           (*PasswdCrypt)(password, pwdata->passwd)) == 0) {
E 7
I 7
	if (strcmp(pwdata->passwd,
	           (*svc.PasswdCrypt)(password, pwdata->passwd)) == 0) {
E 7
		time_t	then;
		char	*ct;
E 10
E 6
I 2

E 2
D 6
		if (!pwdata->passwd)
E 6
I 6
D 10
		then = (time_t )atol(pwdata->ts);
		ct = ctime(&then);
		chop_nl(ct);
		(void) sprintf(mesg, MSG_REUSE, ct);
		return(PWCK_REUSE);
E 10
I 10
	if ((pw = getprpwnam(user->pw_name)) != NULL &&
	     pw->uflg.fg_pwdict && pw->ufld.fd_pwdict[0]) {
		char **ts, **tl;

		for (ts = tl = split(pw->ufld.fd_pwdict, ',', 0,0,0);
D 11
		     *ts; ts++)) {
E 11
I 11
		     *ts; ts++) {
E 11
			char	*xc;

			xc = crypt(password, *ts);
			if (strlen(*ts) > strlen(xc))
				xc = bigcrypt(password, ts);
			if (strcmp(xc, *ts) == 0) {
D 16
				(void) strcpy(mesg, MSG_REUSE_NODATE);
E 16
				free((char *)tl);
D 16
				return(PWCK_REUSE);
E 16
I 16
				return(MSG_REUSE_NODATE);
E 16
			}
		}
		free((char *)tl);
E 10
	}
I 7
D 10
#endif
E 10
E 7
	return(PWCK_OK);
}

I 7
D 10
#ifdef	PASSWORD_HISTORY
E 7
private struct hpasswd *
pwhist_file(name)
	char	*name;
E 10
I 10
/*
D 18
 * osf_history_update
 *	Update OSF/1 password history
E 18
I 18
 * osf_history_update -	Update OSF/1 password history
 *
 * If user has auth database entry, password history has already been
 * modfied by the OSF/1 shadow support module.
E 18
 */
private int
osf_history_update(user, password)
	struct passwd	*user;		/* Who to check for */
	char	*password;		/* Password to check (plaintext) */
E 10
{
D 10
	struct hpasswd *pwd;
	FILE *f;
E 10
I 10
	struct pr_passwd *pw;
E 10

D 10
	if ((f = fopen(PasswordHistoryFile, "rt")) == NULL)
E 10
I 10
	if (access(OSF1_TCB, 0) < 0)		/* AuthDB not in use */
E 10
		return(0);
D 10
	while (pwd = fgetpwhist(f)) {
		if (!pwd->passwd)
E 6
			continue;
		/*
		 * if the username is '*' or matches the given user name
		 * or uid - check if the password matches.
		 * If yes return 1 in case of 'system-wide' match
		 * 2 if user matches too.
		 */
I 2
D 6
/*
 * POLICY - match password history entry by uid not login name.
 * 	    Login names change much more often than uids, so ignore
 *	    the login name and rely upon the uid.
 */
E 2
		if (pwdata->name[0]=='*' ||
I 2
#if	PASSWORD_HISTORY_BYNAME 
E 2
		    strcmp(pwdata->name, user->pw_name) == 0 ||
D 2
		    pwdata->uid == user->pw_uid)  {
			if (!strcmp(pwdata->passwd, crypt(password, pwdata->passwd))) {
E 2
I 2
#endif
		    pwdata->uid == user->pw_uid) {
D 3
			char	*xc = crypt(password, pwdata->passwd);
E 3
I 3
			char	*xc;
E 3

I 3
			xc = crypt(password, pwdata->passwd);
D 5
#ifdef	ULTRIX_SECURITY
E 5
I 5
#ifdef	ULTRIX_AUTH
E 5
			if (strlen(pwdata->passwd) > strlen(xc))
				xc = crypt16(password, pwdata->passwd);
#endif
D 5
#ifdef	OSF1_SECURITY
E 5
I 5
#ifdef	OSF1_AUTH
E 5
			if (strlen(pwdata->passwd) > strlen(xc))
				xc = bigcrypt(password, pwdata->passwd);
#endif
E 3
			if (strcmp(pwdata->passwd, xc) == 0) {
				time_t	then;
				char	*ct;

E 2
				(void) fclose(f);
D 2
				strncpy(mesg, MSG_SAMEAGAIN, BUFSIZ-1);
E 2
I 2
				then = (time_t )atol(pwdata->ts);
				ct = ctime(&then);
D 5
				*(INDEX(ct, '\n')) = 0;
E 5
I 5
				*(index(ct, '\n')) = 0;
E 5
				(void) sprintf(mesg, MSG_REUSE, ct);
E 2
				return(PWCK_REUSE);
			}
		}
E 6
I 6
		if (pwd->name[0] == '*' || strcmp(pwd->name, name) == 0)
			break;
E 6
	}
	(void) fclose(f);
D 6
	return(PWCK_OK);
E 6
I 6
	return(pwd);
E 10
I 10
	if (getprpwnam(user->pw_name) == 0)	/* No auth for user */
		return(0);
	/*
	 * User has auth database entry - password history has already been
D 18
	 * modfiied by the OSF/1 shadow support module.
E 18
I 18
	 * modfied by the OSF/1 shadow support module.
E 18
	 */
	return(1);
E 10
E 6
}
I 10
#endif	/* OSF1_AUTH */
E 10

/*
D 6
 *	fgetSpwent() - read simple/incomplete passwd(5) entry from a file.
E 6
I 6
D 10
 *	fgetpwhist() - read simple/incomplete passwd(5) entry from a file.
E 6
 *      Only 'user:passwd:' part is required, the rest is ignored. (It may be
 *	used for comments).
 *      user field may be a real user or '*' in which case it will match any
 *	user when making comparisons.
 *	Standalone comments can be put in this file in form of '#:*: Comment'
E 10
I 10
D 18
 * pwh_get_file
 *	Read password history from file
 * Usage:
 *	history-line = pwh_get_file(char *who);
 * Returns:
 *	Password history database entry for <who> or NULL if not found
E 18
I 18
 * pwh_get_file - Read password history from flat file
 *
 *	Multiple lines for a user may exist in the history file,
 *	these are merged into one, discarding those which are older
 *	than <PasswordHistoryAge>.
 *
 * Usage
 *	history_line = pwh_get_file(char *who);
 *
 * Returns
 *	Password history database entry for <who> or NULL if not found.
E 18
E 10
 */
D 10
private struct hpasswd *
D 6
fgetSpwent(f)
E 6
I 6
fgetpwhist(f)
E 6
	FILE	*f;		/* Pointer to open password history file */
E 10
I 10
private char *
pwh_get_file(who)
	char	*who;
E 10
{
D 10
	static struct hpasswd pwdata;	/* Return data */
	static char ibuf[BUFSIZ];	/* Input and return data buffer */
E 10
I 10
	FILE	*histfp;		/* History file fp */
	char	ibuf[BUFSIZ];		/* Input buffer */
D 18
	static char	rdata[BUFSIZ];	/* Return data */
E 18
I 18
	static char	rdata[BUFSIZ * 2];	/* Return data */
	time_t	now = time((time_t *)0);
E 18
E 10

D 10
	pwdata.name = pwdata.passwd = pwdata.ts = "";
	pwdata.uid = 0;
D 6
	while (1) {
		char	*p;
E 6
I 6
	while (fgets(ibuf, sizeof(ibuf), f) != NULL) {
		char	**pv;
E 10
I 10
	if (PasswordHistoryDB == 0 || !*PasswordHistoryDB) {
D 16
		debug(DB_LOOKUP, "pwh_get_file: disabled\n");
E 16
I 16
		debug(DB_PWCHECK, "pwh_get_file: disabled\n");
E 16
		return(0);
	}
	if ((histfp = fopen(PasswordHistoryDB, "r")) == NULL) {
D 16
		debug(DB_LOOKUP, "pwh_get_file: No file \"%s\"\n",
E 16
I 16
D 18
		debug(DB_PWCHECK, "pwh_get_file: No file \"%s\"\n",
E 18
I 18
		debug(DB_PWCHECK, "pwh_get_file: No file '%s'\n",
E 18
E 16
			PasswordHistoryDB);
		return(0);
	}
	/*
	 * There may be multiple lines for a user in the history file.
	 * Return the concatenation of them.
	 */
	rdata[0] = 0;
	while (fgets(ibuf, sizeof(ibuf), histfp)) {
		char	*colon;
E 10
E 6

D 6
		if (fgets(ibuf, sizeof(ibuf), f) == NULL)
			return(0);
E 6
D 10
		if (ibuf[0] == '#')	/* Ignore comment lines */
			continue;
E 10
D 5
		if ((p = INDEX(ibuf, '\n')) == NULL) {	/* Zap newline */
E 5
I 5
D 6
		if ((p = index(ibuf, '\n')) == NULL) {	/* Zap newline */
E 5
			fprintf(stderr, "Ill-formed old-passwd entry \"%s\".\n", ibuf);
			continue;
		}
		else
			*p = 0;
#define	skipc while (*p && *p != ':') ++p; if (*p) *p++ = 0
		p = ibuf;
		pwdata.name = p;	skipc;
		pwdata.passwd = p;	skipc;
D 5
		pwdata.uid = (uid_t )atol(p);	skipc;
E 5
I 5
		pwdata.uid = (Uid_t )atol(p);	skipc;
E 5
I 2
		pwdata.ts = p;
E 6
I 6
		chop_nl(ibuf);
D 10
		pv = split(ibuf, ':', 0,0,0);
		pwdata.name = pv[0];
		pwdata.passwd = pv[1];
		pwdata.uid = (Uid_t )atol(pv[2]);
		pwdata.ts = pv[3];
		free((char *)pv);
E 6
E 2
		return(&pwdata);
E 10
I 10
		if (*ibuf == 0 || *ibuf == '#')		/* Empty or comment */
			continue;
D 19
		if ((colon = strchr(ibuf, ':')) == 0)	/* Bad history line */
E 19
I 19
		if ((colon = strchr(ibuf, HIST_SEP)) == 0)	/* Bad history line */
E 19
			continue;
D 19
		*colon = 0;
E 19
I 19
		*colon++ = 0;
E 19
		if (strcmp(who, ibuf) == 0) {
I 18
D 19
			char	*t;
			time_t	pwtime;
E 19
I 19
			if (rdata[0]) {
				int	rsz = strlen(rdata);
E 19

D 19
			/*
			 * Filter out those password history entries
			 * which are older than the age limit.
			 * This will also be done by pwck_history(),
			 * but also doing it here helps keep the return
			 * data buffer from overflowing.
			 */
			if (t = strchr(colon + 1, ',')) {
				*t = 0;
				pwtime = (time_t )atol(t + 1);
				*t = ',';
			} else {
				pwtime = time((time_t *)0);
E 19
I 19
				/*
				 * If the buffer would overflow
				 * discard first entry, which should be old
				 */
				while ((rsz + strlen(colon)) > sizeof(rdata)) {
					char	*nc = strchr(rdata, HIST_SEP);

					if (nc == 0) /* Really busted */
						logdie("(pwh_get_file) History compress error");
					(void) strcpy(rdata, ++nc);
				}
				(void) strncat(rdata, colon,
						sizeof(rdata) - rsz);
E 19
			}
D 19
			if (PasswordHistoryAge &&
			   (now - pwtime) > PasswordHistoryAge) {
				debug(DB_PWCHECK,
					"pwh_get_file: Too old <%s> age = %u limit = %u\n",
					colon, (now - pwtime),
					PasswordHistoryAge);
				continue;
E 19
I 19
			else {
				(void) strcpy(rdata, colon);
E 19
			}
E 18
D 19
			*colon = ':';
			if (rdata[0])
D 15
				(void) strcat(rdata, colon);
E 15
I 15
				(void) strncat(rdata, colon,
					sizeof(rdata) - strlen(rdata));
E 15
			else
D 18
				(void) strcpy(rdata, ibuf);
E 18
I 18
				(void) strcpy(rdata, colon + 1);
E 19
E 18
		}
E 10
	}
I 10
	(void) fclose(histfp);
D 16
	debug(DB_LOOKUP, "pwh_get_file: found <%s>\n", rdata);
E 16
I 16
D 19
	debug(DB_PWCHECK, "pwh_get_file: found <%s>\n", rdata);
E 19
I 19
	debug(DB_PWCHECK, "pwh_get_file: return <%s>\n", rdata);
E 19
E 16
	return(rdata[0] ? rdata : 0);
E 10
D 6
#undef	skipc
E 6
}

/*
D 10
 * update_password_history() - Stash password in history file.
 * It should be called from the password changing program just after
 * the password has been changed.  It adds given (encrypted) password to the
 * 'old passwords' database so it cannot be used again.
E 10
I 10
 * pwh_put_file
 *	Add password to history file.
D 18
 * Usage:
E 18
I 18
 *
 * Usage
E 18
 *	pwh_put_file(char *name,  char *crypt_passwd)
I 18
 * 
 * Returns
 * 	 0 = no history file
 *	 1 = history put OK
 *	-1 = history put failed
E 18
E 10
 */
D 10
public int
update_password_history(user, cryptedpassword)
	struct passwd	*user;
	char *cryptedpassword;
E 10
I 10
D 18
private void
E 18
I 18
private int
E 18
pwh_put_file(name, cryptedpassword)
	char	*name;
	char	*cryptedpassword;
E 10
{
D 10
	FILE *f;
	struct passwd *pwdata;
E 10
I 10
	int	f,
		nw;
E 10
	struct stat statbuf;
I 10
	char	histent[BUFSIZ];
I 18
	int	xerrno;
E 18
E 10
	time_t	now;

I 18
	if (stat(PasswordHistoryDB, &statbuf) < 0)	/* No history file */
		return(0);

	debug(DB_UPDATE, "pwh_put_file: update '%s'\n", PasswordHistoryDB);
E 18
D 10
#ifndef	PASSWORD_HISTORY
	return(0);
#endif
E 10
	/*
	 * Update history only if file has write permission for owner.
D 18
	 * The passwd changing program runs as suid to root,
	 * 'access()' would check if the user has write permission which
	 * would be 'no', so we must check stat() instead.
E 18
I 18
	 * access(2) uses the *real* uid for checking not the *effective*,
	 * making it not useful when running setuid, so this check must be
	 * done via stat(2).
E 18
	 */
I 10
D 18
	debug(DB_UPDATE, "pwh_put_file: update '%s'\n", PasswordHistoryDB);

	if (stat(PasswordHistoryDB, &statbuf) < 0)	/* No history file */
		return;
E 18
E 10
#ifndef	DEBUG
D 10
	if (stat(PasswordHistoryFile, &statbuf) < 0)
		return(-1);
	if (!(statbuf.st_mode & S_IWUSR))
		return(1);	
E 10
I 10
	if (!(statbuf.st_mode & S_IWUSR)) {
D 18
		logerr("Password history \"%s\" bad mode 0%o\n",
E 18
I 18
		logerr("Password history '%s' bad mode 0%o\n",
E 18
			PasswordHistoryDB, statbuf.st_mode);
D 18
		return;	
E 18
I 18
		return(-1);	
E 18
	}
E 10
#endif
D 10
	if ((f = fopen(PasswordHistoryFile, "at")) == NULL) {
		fprintf(stderr, ERR_NOHISTUPDATE);
		return(2);
E 10
I 10
	(void) time(&now);
D 19
	(void) sprintf(histent, "%s:%s,%lu\n", name, cryptedpassword, now);
E 19
I 19
	(void) sprintf(histent, "%s:%s,%lu:\n", name, cryptedpassword, now);
E 19

	/*
	 * Dirty trick - if the process cannot append to the
	 * history file, then try setting the effective uid to the
D 18
	 * owner of the file and try again.  This should take care of most
	 * NFS root access problems.
E 18
I 18
	 * owner of the file and try again.
	 * This should take care of most NFS root access problems, provided
	 * the history file ownership is non-root.
E 18
	 */
	if ((f = open(PasswordHistoryDB, O_WRONLY|O_APPEND)) < 0) {
D 18
		uid_t	oldeuid = geteuid();
E 18
I 18
		uid_t	oldeuid;
E 18

		debug(DB_UPDATE,
			"pwh_put_file: first open failure %d\n", errno);
I 18
		oldeuid = geteuid();
		if (oldeuid == statbuf.st_uid) {
			debug(DB_UPDATE,
				"pwh_put_file: file is owned by my euid\n");
			xerrno = EPIPE;
		}
E 18
D 14
		(void) seteuid(statbuf.st_uid);
E 14
I 14
		(void) setreuid(-1, statbuf.st_uid);
E 14
D 18
		if ((f = open(PasswordHistoryDB, O_WRONLY|O_APPEND)) < 0)
E 18
I 18
		if ((f = open(PasswordHistoryDB, O_WRONLY|O_APPEND)) < 0) {
			xerrno = errno;
E 18
			debug(DB_UPDATE,
D 18
				"pwh_put_file: second open failure %d\n", errno);
E 18
I 18
				"pwh_put_file: second open failure %d\n",
				xerrno);
		}
E 18
D 14
		(void) seteuid(oldeuid);
E 14
I 14
		(void) setreuid(-1, oldeuid);
E 14
E 10
	}
D 10
	now = time((time_t *)0);
	(void) fprintf(f, "%s:%s:%u:%lu\n",
			user->pw_name, cryptedpassword, user->pw_uid, now);
	(void) fclose (f);
	return(0);
E 10
I 10
	/*
	 * File exists but cannot be opened - this is bad
	 */
	if (f < 0) {
D 18
		logerr("Append to password history \"%s\" failed, error %d",
			PasswordHistoryDB, errno);
		return;
E 18
I 18
		logerr("Password history '%s' append open failure %d",
			PasswordHistoryDB, xerrno);
		return(-1);
E 18
	}
I 18
	/*
	 * Write the new history entry at EOF.
	 *
	 * This is a cheap & dirty update.  Doing a "proper" merge would require
	 * a temporary file with all the appropriate checking.
	 * History entries that are too old are ignored during the lookup,
	 * but the history file should be periodically purged lest it
	 * become unweildly for a linear serach.
	 */
E 18
	nw = write(f, histent, strlen(histent));
I 18
	xerrno = errno;
E 18
	(void) close(f);
I 18
	if (nw != strlen(histent)) {
		logerr("Password history '%s' append failure %d",
			PasswordHistoryDB, xerrno);
		return(-1);
	}
	return(1);
E 18
E 10
}
I 10

D 16
#ifdef	USE_NIS
E 16
I 16
D 18
#ifdef	USE_NIS_NOTYET
E 18
E 16
/*
I 18
 * Filter out those password history entries
 * which are older than the age limit.
 * This will also be done by pwck_history(),
 */
private char *
clean_hist(data, when)
	char	*data;
	time_t	when;
{
	char	*nd = calloc((strlen(data) + 2), sizeof(char));
D 19
	char	**hv = split(data, ':', 0, 0),
E 19
I 19
	char	**hv = split(data, HIST_SEP, 0, 0),
E 19
		**hd;

	if (nd == 0)
		logdie("clean_hist: Cannot allocate memory");
	for (hd = hv; *hd; hd++) {
		char	*t;			/* Temp */
		time_t	pwtime;			/* History entry time */

		if (t = strchr(*hd, ',')) {
 			*t = 0;
			pwtime = (time_t )atol(t+1);
 			*t = ',';
		} else {
			pwtime = when;
		}
		if (PasswordHistoryAge &&
		   (when - pwtime) > PasswordHistoryAge) {
			debug(DB_PWCHECK,
				"clean_hist: Too old <%s> age = %u limit = %u\n",
					*hd, (when - pwtime), PasswordHistoryAge);
			continue;
		}
		if (*nd)
			(void) strcat(nd, ":");
		(void) strcat(nd, *hd);
	}
	free((char *)hv);
	if (*nd)
		(void) strcpy(data, nd);
	free(nd);
	return(data);
}

/* #ifdef	I_NDBM */
/*
 * pwh_get_dbm - Fetch password history from DBM database.
 *
 * Usage:
 *	history-line = pwh_get_dbm(char *who);
 *
 * Returns:
 *	Password history database entry for <who> or NULL if not found.
 */
I 19
#include <sys/types.h>		/* Maybe not */
E 19
#include <ndbm.h>

private char *
pwh_get_dbm(who)
	char	*who;
{
	DBM	*hdb;
	datum	hkey,
		hdata;
	static char	etemp[BUFSIZ];

	if (PasswordHistoryDB == 0 || !*PasswordHistoryDB) {
		debug(DB_PWCHECK, "pwh_get_dbm: disabled\n");
		return(0);
	}
	if ((hdb = dbm_open(PasswordHistoryDB, O_RDONLY, 0)) == 0) {
		debug(DB_PWCHECK, "pwh_get_dbm: No DBM '%s'\n",
			PasswordHistoryDB);
		return(0);
	}
	hkey.dptr = who;
	hkey.dsize = strlen(who);
	hdata = dbm_fetch(hdb, hkey);
	(void) dbm_close(hdb);
	if (hdata.dptr) {
		(void) strncpy(etemp, hdata.dptr, hdata.dsize);
		etemp[hdata.dsize] = 0;
		debug(DB_PWCHECK, "pwh_dbm_put: found <%s>\n", etemp);
		return(etemp);
	}
	debug(DB_PWCHECK, "pwh_get_dbm: not found\n");
	return(0);
}

/*
 * pwh_put_dbm - Stash password in history database.
 *
 * Usage:
 *	pwh_put_dbm(char *name, char *crypt_passwd)
 * 
 *  0 = no history file
 *  1 = history put OK
 * -1 = history put failed
 */
private int
pwh_put_dbm(name, cryptedpassword)
	char	*name;
	char	*cryptedpassword;
{
	DBM	*hdb;			/* Database pointer */
	datum	hkey,			/* DBM key */
		hdata;			/* DBM data */
	int	rc = 1;			/* Return code */
	char	nentry[BUFSIZ];		/* New entry temp */
	time_t	now = time((time_t *)0);	/* Current time */

	if (PasswordHistoryDB == 0 || !*PasswordHistoryDB) {
		debug(DB_PWCHECK, "pwh_put_dbm: disabled\n");
		return(0);
	}
	debug(DB_UPDATE, "pwh_put_dbm: update '%s'\n", PasswordHistoryDB);

	/*
	 * Open database read-only to verify existence and fetch history entry.
	 */
	if ((hdb = dbm_open(PasswordHistoryDB, O_RDONLY, 0)) == 0) {
		debug(DB_PWCHECK, "pwh_put_dbm: No DB '%s'\n",
			PasswordHistoryDB);
		return(0);
	}
	hkey.dptr = name;
	hkey.dsize = strlen(name);
	hdata = dbm_fetch(hdb, hkey);
	dbm_close(hdb);

	if (hdata.dptr) {
		/*
		 * History entry found - merge in new data
		 */
		char	etemp[BUFSIZ];

		(void) strncpy(etemp, hdata.dptr, hdata.dsize);
		etemp[hdata.dsize] = 0;
		debug(DB_PWCHECK, "pwh_dbm_put: found <%s>\n", etemp);
		(void) clean_hist(etemp, now);
D 19
		(void) sprintf(nentry, "%s:%s,%lu", etemp, cryptedpassword, now);
E 19
I 19
		(void) sprintf(nentry, "%s:%s,%lu",
			etemp, cryptedpassword, now);
E 19
	} else {
		/*
		 * Make new history entry
		 */
		(void) sprintf(nentry, "%s,%lu", cryptedpassword, now);
	}
	hdata.dptr = nentry;
	hdata.dsize = strlen(nentry);

	/*
	 * Open database read-write to put the data
	 */
	if ((hdb = dbm_open(PasswordHistoryDB, O_RDWR, 0)) == 0) {
		/*
		 * Dirty trick - if the process cannot dbm_open the
		 * history database, then try setting the effective uid to the
		 * owner of the file and try again.  This should take
		 * care of most NFS root access problems.
		 */
		uid_t	oldeuid = geteuid();
		char	dbtemp[MAXPATHLEN];
		struct stat	statbuf;

		debug(DB_UPDATE,
			"pwh_put_dbm: first open failure %d\n", errno);
		(void) strcpy(dbtemp, PasswordHistoryDB);
		(void) strcat(dbtemp, ".dir");
		if (stat(dbtemp, &statbuf) < 0)
			logdie("pwh_put_dbm: History DB vanished!");

		(void) setreuid(-1, statbuf.st_uid);
		if ((hdb = dbm_open(PasswordHistoryDB, O_RDWR, 0)) == 0)
			debug(DB_UPDATE,
				"pwh_put_dbm: second open failure %d\n", errno);
		(void) setreuid(-1, oldeuid);
	}
	if (hdb) {
		if (dbm_store(hdb, hkey, hdata, DBM_REPLACE) < 0) {
			logerr("pwh_put_dbm: Store failed");
			rc = -1;
		}
	}
	else {
		debug(DB_UPDATE,
			"pwh_put_dbm: cannot update history\n");
		rc = -1;
	}
	return(rc);
}

#ifdef	USE_NIS_UNSUPPORTED
/*
E 18
 * Support for storing password history in a NIS map
I 16
 *
 * This somewhat duplicates code in the NIS method module.
E 16
 */
#define PORTMAP
#include <ndbm.h>
#include <netdb.h>
#include <sys/socket.h>
#include <rpc/rpc.h>
#include <rpcsvc/yppasswd.h>
#include <rpcsvc/ypclnt.h>
#define DATUM                   /* Prevent error in next include */
#include <rpcsvc/yp_prot.h>
#undef  DATUM

/*
 * pwh_put_nis
 *	Add password to history file.
 * Usage:
D 18
 *	pwh_put_file(char *name,  char *crypt_passwd)
E 18
I 18
 *	pwh_put_nis(char *name,  char *crypt_passwd)
E 18
 */
private char
*pwh_get_nis(who)
	char	*who;
{
	char	*domain,
		*master,
		*data;
	int	dlen;

	if (yp_get_default_domain(&domain)) {
D 16
		debug(DB_LOOKUP, "NIS domain not set\n");
E 16
I 16
		debug(DB_PWCHECK, "NIS domain not set\n");
E 16
                return(0);
	}

	if (yp_master(domain, PasswordHistoryDB, &master)) {
D 16
		debug(DB_LOOKUP, "NIS map %s not found\n", PasswordHistoryDB);
E 16
I 16
		debug(DB_PWCHECK, "NIS map %s not found\n", PasswordHistoryDB);
E 16
                return(0);
	}
	if (yp_match(domain, PasswordHistoryDB, who, strlen(who), &data, &dlen)) {
D 16
		debug(DB_LOOKUP, "No history found for %s\n", who);
E 16
I 16
		debug(DB_PWCHECK, "No history found for %s\n", who);
E 16
                return(0);
	}
	return(data);
}

/*
 * pwh_put_nis
 *	Add password to NIS history map
 * Usage:
D 18
 *	pwh_put_file(char *name,  char *crypt_passwd)
E 18
I 18
 *	pwh_put_nis(char *name,  char *crypt_passwd)
E 18
 */
private void
pwh_put_nis(name, cryptedpassword)
	char	*name,			/* User name */
		*cryptedpassword;	/* Encrypted password */
{
	char	*domain,
		*master,
		*data;
	int	dlen,
		rc;
	time_t	now = time((time_t *)0);
	char	temp[YPMAXRECORD];

	if (yp_get_default_domain(&domain)) {
		debug(DB_UPDATE, "NIS domain not set\n");
                return;		/* Not a fatal error */
	}

	if (yp_master(domain, PasswordHistoryDB, &master)) {
		debug(DB_UPDATE, "NIS map %s not found\n", PasswordHistoryDB);
                return;		/* Not a fatal error */
	}
	(void) sprintf(temp, "%s:%s,%lu", name, cryptedpassword, now);

	/* Get existing password history */
	rc = yp_match(domain, PasswordHistoryDB, name, strlen(name), &data, &dlen);
	if (rc == 0) {		/* Append new item to entry */
		char	**v;
		int	count;

D 19
		v = (char **)split(data, ':', 0, 0, 0);
E 19
I 19
		v = (char **)split(data, HIST_SEP, 0, 0, 0);
E 19
		/*
		 * Skip v[0] (user name)
		 */
		for (count = 1; v[count]; count++) {
			if (count > PasswordHistoryDepth)
				break;
			if ((strlen(temp) + strlen(v[count]) + 2) > YPMAXRECORD)
				break;
			(void) strcat(temp, ":");
			(void) strcat(temp, v[count]);
		}
	} else {
		if (rc != YPERR_KEY) {
			logerr("pwh_put_nis: lookup error %d\n", rc);
		}
	}
	debug(DB_UPDATE, "pwh_put_nis: put '%s'\n", temp);

#ifdef	SECURE_RPC
	rc = yp_update(domain, PasswordHistoryDB, YPOP_STORE,
		name, strlen(name), temp, strlen(temp));
	if (rc) {
		logerr("pwh_put_nis: store failed- map '%s' error %d\n",
			PasswordHistoryDB, rc);
		warn("Could not store password in NIS history database.\n");
	}
E 10
I 7
#endif
I 10
}
D 16
#endif	/* USE_NIS */
E 16
I 16
D 18
#endif	/* USE_NIS_NOTYET */
E 18
I 18
#endif	/* USE_NIS_UNSUPPORTED */
E 18
E 16

E 20
E 10
E 7
/* End %M% */
E 1
