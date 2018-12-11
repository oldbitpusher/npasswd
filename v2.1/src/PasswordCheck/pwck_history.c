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
/*  --------------------------------------------------------------------  */
/*                                                                        */
/*                    Original Author: Tomasz Surmacz                     */
/*                   Institute of Technical Cybernetics                   */
/*                    Technical University of Wroclaw                     */
/*                                 Poland                                 */
/*                         tsurmacz@ict.pwr.wroc.pl                       */
/*                                                                        */
/* This code may be distributed freely, provided this notice is retained. */
/*                                                                        */
/*  --------------------------------------------------------------------  */
/* 
 *
 * This code 
 *
 * Form of password history entries:
 *
 * name:passwd,timestamp:passwd,timestamp: ...
 * e.g.
 * joe:XFDJFDJFKDsf,1234450:xadierercx/,13344432
 */

#ifndef lint
static char vers_id[] = "noreusal.c : v1.0 Tomasz Surmacz 15 Nov 1993";
static char sccsid[] = "@(#)pwck_history.c	1.31 07/23/99 (cc.utexas.edu)";
#endif

#include "options.h"
#include "pwck_defines.h"
#include "pwck_history.h"
#include "pw_svc.h"

private char *(*get)() = DEFAULT_GET;
private int   (*put)() = DEFAULT_PUT;

/*
 * Password history system parameters
 *
 * HistoryDB - Location of history database.
 *	This can be a file name, NIS map name or NIS+ table name.
 *
 * HistoryAge - Age limitation on history
 * 	History entries older than this are ignored (does not work
 *	with OSF/1 password history).
 *	Setting to 0 disables password age checks.
 *
 * HistoryDepth - How many passwords are kept per user
 *	Setting to 0 keeps all passwords.
 *
 * Default vaules are defined in ../options.h
 *
 * These vars are not static so that test_history.c can access them.
 */
char	*HistoryDB = PASSWORD_HISTORY_DB;
char	*HistoryMethod = DEFAULT_METHOD;
time_t	HistoryAge = (PASSWORD_HISTORY_AGE * 86400);
int	HistoryDepth = PASSWORD_HISTORY_DEPTH;

#define	MSG_REUSE	"it is not old enough (last used %s)"
#define	MSG_REUSE_NODATE "it is not old enough"

/*
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
 * pwck_history_configure
 *	Configure the history mechanism
 * Usage: 
 *	pwck_history_configure(char **configline);
 * Returns:
 *	(char *)0 if configuration line was good
 *	error message if not
 */
public char *
pwck_history_configure(args)
	char **args;
{
	char	*cfitem;

	if (args == 0)
		return("Missing argument list");
	cfitem = *args++;

	debug(DB_CONFIG,
		"pwck_history_configure: [%s]\n", cfitem);
	
	if (instringcase(cfitem, "database")) {		/* Database selection */
		debug(DB_CONFIG,
			"pwck_history_configure: database '%s'\n", *args);
		if (strcasecmp(*args, "none") == 0) {
			HistoryDB = 0;		/* History disabled */
			debug(DB_CONFIG, "pwck_history_configure: disable history\n");
			return(0);
		}

		/*
		 * History in a NIS+ table
		 */
		if (strcasecmp(*args, "nisplus") == 0) {
#ifdef	USE_NISPLUS_UNSUPPORTED
			args++;
			if (!*args)
				return("Missing NIS+ table name");
			if (strcmp(*args, HISTORYDB_DEFAULT))
				HistoryDB = strdup(*args);
			HistoryMethod = "nisplus";
			debug(DB_CONFIG,
				"pwck_history_configure: NIS+ table '%s'\n",
				HistoryDB);
			get = pwh_get_nisplus;
			put = pwh_put_nisplus;
			return(0);
#else
			return("NIS+ support not available");
#endif
		}

		/*
		 * History in a NIS (YP) map
		 */
		if (strcasecmp(*args, "nis") == 0) {
#ifdef	USE_NIS_UNSUPPORTED
# ifdef	SECURE_RPC
			args++;
			if (!*args)
				return("Missing NIS map name");
			if (strcmp(*args, HISTORYDB_DEFAULT))
				HistoryDB = strdup(*args);
			HistoryMethod = "nis";
			debug(DB_CONFIG,
				"pwck_history_configure: NIS map '%s'\n",
				HistoryDB);
			get = pwh_get_nis;
			put = pwh_put_nis;
			return(0);
# else	/* SECURE_RPC */
			return("Secure RPC support not available");
# endif	/* SECURE_RPC */
#else	/* USE_NIS_UNSUPPORTED */
			return("NIS support not available");
#endif	/* USE_NIS_UNSUPPORTED */
		}

		/*
		 * History in a local DBM database
		 */
		if (strcasecmp(*args, "dbm") == 0) {
#ifdef	I_NDBM
			args++;
			if (!*args)
				return("Missing DBM name");
			if (strcmp(*args, HISTORYDB_DEFAULT)) {
#if	(CDEBUG < CDEBUG_FILES)
				if (**args != '/')
					return("Bad file name");
#endif
				HistoryDB = strdup(*args);
			}
			HistoryMethod = "dbm";
			debug(DB_CONFIG,
				"pwck_history_configure: DBM database '%s'\n",
				HistoryDB);
			get = pwh_get_dbm;
			put = pwh_put_dbm;
			return(0);
#else
			return("DBM support not available");
#endif
		}

		/*
		 * History in a flat file
		 */
		if (strcasecmp(*args, "file") == 0) {
			args++;
			if (!*args)
				return("Missing file name");
			if (strcmp(*args, HISTORYDB_DEFAULT)) {
#if	(CDEBUG < CDEBUG_FILES)
				if (**args != '/')
					return("Bad file name");
#endif
				HistoryDB = strdup(*args);
			}
			HistoryMethod = "file";
			debug(DB_CONFIG,
				"pwck_history_configure: file '%s'\n",
				HistoryDB);
			get = pwh_get_file;
			put = pwh_put_file;
			return(0);
		}
		/*
		 * Fallthrough - use the default method
		 */
		if (**args == '/') {		/* Naked file name */
			HistoryDB = strdup(*args);
			get = DEFAULT_GET;
			put = DEFAULT_PUT;
			debug(DB_CONFIG, "pwck_history_configure: default %s '%s'\n",
				DEFAULT_METHOD, HistoryDB);
			return(0);
		}
		return("Bad history database specification");
	}

	if (instringcase(cfitem, "age")) {	/* Active history age */
		int	t;

		if (xatoi(*args, (char **)0, &t) == 0)
			return("Bad history age specification");
		if (t < MIN_HISTORY_TIMEOUT)
			return("History age too short");
		HistoryAge = (time_t )(t * SEC_DAY);
		debug(DB_CONFIG,
			"pwck_history_configure: age %d days\n", t);
		return(0);
	}

	if (instringcase(cfitem, "depth")) {	/* Active history depth */
		int	t = decode_int(*args);

		if (t < 0)
			return("Bad history depth specification");
		if (t < MIN_HISTORY_DEPTH)
			return("History depth too small");
		HistoryDepth = t;
		debug(DB_CONFIG,
			"pwck_history_configure: depth %d\n", t);
		return(0);
	}
	return("Unknown history directive");
}

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
{
	char	*t;		/* Temp */
	time_t	t1 = 0,		/* Item 1 time */
		t2 = 0;		/* Item 2 time */
	char **c1 = (char **)a1; /* Char pointer to item 1 */
	char **c2 = (char **)a2; /* Char pointer to item 2 */

	if (*c1 && (t = strchr(*c1, FIELD_SEP)))
		t1 = (time_t )atol(++t);
	if (*c2 && (t = strchr(*c2, FIELD_SEP)))
		t2 = (time_t )atol(++t);
	/* time_t is unsigned - cannot do "return(t1 - t2)" */
	if (t1 > t2) return(-1);
	if (t1 < t2) return(1);
	return(0);
}

/*
 * clean_history
 *	Filter a history line, remove old and extra passwords
 *
 * Returns:
 *	Address of buffer containing the cleaned entry or
 *	NULL on error
 *
 * Effects:
 *	The cleaned entry is copied back into the <data> argument buffer
 */
public char *
clean_history(data, depth, age, epoch, maxlen)
	char	*data;		/* History entry */
	int	depth;		/* How many passwords to keep */
	time_t	age,		/* Password retention limit */
		epoch;		/* Current time */
	size_t	maxlen;		/* Sizeof <data> */
{
	char	*newdata;	/* New version of <data> */
	char	**hvec,		/* Split version of <data> */
		**hptr;		/* List traversal temp */
	int	seen = 0;	/* How many passwords in this entry */
	int	i;		/* Temp */
	time_t	now = epoch ? epoch : time((time_t *)0);
				/* Epoch for time comparisons */

	if (data == NULL)
		return(NULL);

	if ((newdata = calloc((strlen(data) + 2), sizeof(char))) == NULL)
		logdie("(clean_history) No memory for history copy");

	if (maxlen == 0)			/* Assume buffer length */
		maxlen = HISTORY_RECLEN;	/* if not given by caller */

	/*
	 * Sort the entries by time - youngest first
	 */
	if ((hvec = split(data, ENTRY_SEP, 0, 0)) == 0)
		logdie("(clean_history) History split failed");

	for (hptr = hvec, i = 0; *hptr; hptr++, i++);	/* Get size of list */
	if (i > 1)				/* Sort in time order */
		qsort((void *)hvec, i, sizeof(char *), bytime);

	for (hptr = hvec; *hptr; hptr++) {		/* Traverse the list */
		char	*t;
		time_t	pwtime;

		if (t = strchr(*hptr, FIELD_SEP)) {
 			*t = 0;
			pwtime = (time_t )atol(t+1);
 			*t = FIELD_SEP;
		} else {
			logerr("(clean_history) Bad entry '%s'", data);
			continue;
		}
		if (age && (now - pwtime) > age) {
			debug(DB_PWCHECK,
				"clean_history: old '%s' age = %lu limit = %lu\n",
				*hptr, (now - pwtime), age);
			continue;
		}
		/*
		 * Ignore if more than <HistoryDepth> have already been seen
		 *
		 * "HistoryDepth" means "how many old passwords matter"
		 * (hence use "seen++")
		 */
		if (depth && seen++ > depth) {
			debug(DB_PWCHECK,
				"clean_history: Depth limit %d reached, discard '%s'\n",
				depth, *hptr);
			continue;
		}
		/*
		 * Length check - don't go over HISTORY_RECLEN chars
		 * Old items will be discarded.
		 */
		if ((strlen(newdata) + strlen(*hptr) + 1) > maxlen) {
			debug(DB_PWCHECK,
				"clean_history: length limit %d reached, discard '%s'\n",
				maxlen, *hptr);
			continue;
		}
		if (*newdata) {
			(void) strcat(newdata, ENTRY_SEP_STR);
			(void) strcat(newdata, *hptr);
		}
		else {
			(void) strcpy(newdata, *hptr);
		}
	}
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
	debug(DB_PWCHECK, "clean_history: Return <%s>\n", data);
	return(data);
}

/*
 * pwck_get_history
 *	Fetch history entry for user
 *
 * Returns:
 *	Value from db method get() routine
 *	NULL if history not found or error
 */
public char *
pwck_get_history(user)
	char *user;	/* Name of user */
{
	char	*rc;	/* Return code */

	if (user == 0)			/* Null user? */
		return(NULL);
	if (HistoryDB == NULL || *HistoryDB == 0)
		return(NULL);		/* No history */

	if (rc = (*get)(user))
		return(rc);
	debug(DB_PWCHECK, "pwck_history: no history for %s\n", user);
	return(NULL);
}

/*
 * pwck_history - Wrapper for password history checking function
 *
 * Returns:
 *	Message if password exists in the history database
 *	'PWCK_OK' if not
 */
public char *
pwck_history(password, user)
	char	*password;	/* Password to check (plaintext) */
	struct passwd	*user;	/* Passwd info for user */
{
	char	*histent,		/* History data */
		**hv,			/* Split history data */
		**plist,		/* History entry traversal */
		*rval = PWCK_OK;	/* Return value */
	static char mesg[STRINGLEN];	/* Error message buffer */
	struct pw_svc *svc = get_pwsvc(); /* Password service */

	debug(DB_VERBOSE, "pwck_history: %s '%s'\n", user->pw_name, password);

#ifdef	OSF1_AUTH	/* And maybe HPUX_AUTH also */
	{
	char	*rc;

	if ((rc = osf_history_check(password, user)) != PWCK_OK)
		return(rc);
	}
#endif
	if ((histent = pwck_get_history(user->pw_name)) == 0)
		return(PWCK_OK);		/* No history */

	if (hv = split(clean_history(histent, HistoryDepth, HistoryAge, 0, 0),
			ENTRY_SEP, 0, 0)) {
		for (plist = hv; *plist; plist++) {
			char	*t;	/* Temp */

			if (t = strchr(*plist, FIELD_SEP)) {
				time_t	pwtime;		/* Current time */

				*t++ = 0;
				pwtime = (time_t )atol(t);
				t = (*svc->PasswdCrypt)(password, *plist);
				if (strcmp(t, *plist) == 0) {	/* Found <password> */
					char	*ct = ctime(&pwtime);

					chop_nl(ct);
					(void) sprintf(mesg, MSG_REUSE, &ct[4]);
					rval = mesg;
					break;
				}
			}
		}
		free((char *)hv);
	}
	debug(DB_PWCHECK, "pwck_history: %s\n", rval ? rval : "not found");
	return(rval);
}

/*
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
 * password_history_update()
 *	Store password in history database
 * Usage
 *	pwck_history_update(struct passwd *user, char *crypted_password);
 * Returns:
 *	Value from db method put() routine or
 *	0 if history disabled or null argument
 */
public int
password_history_update(user, crypted_password, epoch)
	char	*user,			/* User name */
		*crypted_password;	/* Encrypted password */
	time_t	epoch;			/* Timestamp */
{
#ifdef	OSF1_AUTH	/* And maybe HPUX_AUTH also */
	if (osf_history_update(user, crypted_password))
		return;
#endif
	if (user == 0)			/* Null user? */
		return(0);
	if (HistoryDB == 0 || *HistoryDB == 0)
		return(0);		/* No history */
	return((*put)(user, crypted_password, epoch));
}
/* End pwck_history.c */
