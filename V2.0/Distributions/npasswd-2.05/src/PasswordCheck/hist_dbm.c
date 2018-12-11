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

#include "pwck_defines.h"
#include "options.h"
#include "pwck_history.h"

#ifndef lint
static char utid[] = "@(#)hist_dbm.c	1.4 10/13/98 (cc.utexas.edu)";
#endif

/*
 * hist_dbm.c - Password history database method 'DBM'
 */

#ifdef	I_NDBM
/*
 * pwh_get_dbm - Fetch password history from DBM database.
 *
 * Usage:
 *	history-line = pwh_get_dbm(char *who);
 *
 * Returns:
 *	Password history database entry for <who> or NULL if not found.
 */
#include <sys/types.h>		/* Maybe not */
#include <ndbm.h>

/*
 * xdbm_open
 *	DBM open wrapper 
 * Usage
 *	dbp = xdbm_open(db-name, o_flags, o_mode)
 * Returns
 * 	DBM file pointer or NULL
 */
private DBM *
xdbm_open(path, flags, mode)
	char	*path;		/* DBM path */
	int	flags,		/* File open paths */
		mode;		/* File mode (for creating dbs) */
{
	DBM	*hdb;			/* DBM pointer */
	char	dbtemp[MAXPATHLEN];	/* Temp file path */
	struct stat	statbuf;	/* DBM stat buffer */
	uid_t	oldeuid = geteuid();	/* Saved effective uid */

	if (hdb = dbm_open(path, flags, mode))
		return(hdb);

	/*
	 * If cannot open the file as self, change the effective uid
	 * to the owner of the .dir file and try again.
	 * This is for when the history is on an NFS mounted filesystem
	 * that this host does not have root permission.
	 */
	debug(DB_UPDATE, "xdbm_open: first open failure %d\n", errno);

	(void) strcpy(dbtemp, path);
	(void) strcat(dbtemp, ".dir");
	if (stat(dbtemp, &statbuf) < 0)
		return(0);

	(void) setreuid(-1, statbuf.st_uid);
	if ((hdb = dbm_open(HistoryDB, O_RDWR, 0)) == 0) {
		debug(DB_UPDATE,
			"xdbm_open: second open failure %d\n", errno);
	}
	(void) setreuid(-1, oldeuid);
	return(hdb);
}

/*
 * pwh_get_dbm
 *	Fetch history entry from DBM history
 * Usage:
 *	pwh_get_dbm(char *name)
 * 
 *  0 = user not found or history entry
 */
public char *
pwh_get_dbm(who)
	char	*who;		/* Username to get */
{
	DBM	*hdb;		/* DBM pointer */
	datum	hkey,		/* Lookup key */
		hdata;		/* Return data key */
	static char	rdata[HISTORY_RECLEN];	/* Return data */

	if (HistoryDB == 0 || !*HistoryDB) {
		debug(DB_PWCHECK, "pwh_get_dbm: No history database\n");
		return(0);
	}

	if ((hdb = xdbm_open(HistoryDB, O_RDONLY, 0)) == 0) {
		debug(DB_PWCHECK, "pwh_get_dbm: Cannot open '%s'\n", HistoryDB);
		return(0);
	}

	/*
	 * Lookup history entry
	 */
	hkey.dptr = who;
	hkey.dsize = strlen(who);
	hdata = dbm_fetch(hdb, hkey);
	(void) dbm_close(hdb);
	if (hdata.dptr) {
		/*
		 * If the data is bigger than sizeof(rdata), toss items
		 * from the end.  These will be older items anyway,
		 * so discarding them will matter less.
		 */
		if (hdata.dsize >= sizeof(rdata)) {
			char	*fc;

			debug(DB_PWCHECK,
				"pwh_get_dbm: Overflow len=%d max=%d\n",
				hdata.dsize, sizeof(rdata));
			(void) strncpy(rdata, hdata.dptr, sizeof(rdata)-1);
			rdata[sizeof(rdata)] = 0;
			fc = strrchr(rdata, ENTRY_SEP);
			*fc = 0;	/* Truncate at item boundary */
		} else {
			(void) strncpy(rdata, hdata.dptr, hdata.dsize);
			rdata[hdata.dsize] = 0;
		}
		debug(DB_PWCHECK, "pwh_get_dbm: found <%s>\n", rdata);
		return(rdata);
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
public int
pwh_put_dbm(name, cryptedpassword, epoch)
	char	*name;			/* User name */
	char	*cryptedpassword;	/* Encrypted password to store */
	time_t	epoch;			/* Item timestamp */
{
	DBM	*hdb;			/* Database pointer */
	datum	hkey,			/* DBM lookup datum */
		hdata;			/* DBM return datum */
	int	rc = 1;			/* Return code */
	char	new[HISTORY_RECLEN];	/* New entry temp */

	if (HistoryDB == 0 || !*HistoryDB) {
		debug(DB_PWCHECK, "pwh_put_dbm: disabled\n");
		return(0);
	}
	debug(DB_UPDATE, "pwh_put_dbm: update '%s'\n", HistoryDB);

	/*
	 * Open database read-only to verify existence and fetch history entry.
	 */
	if ((hdb = xdbm_open(HistoryDB, O_RDONLY, 0)) == 0) {
		debug(DB_PWCHECK, "pwh_put_dbm: Cannot read '%s'\n", HistoryDB);
		return(0);
	}
	hkey.dptr = name;
	hkey.dsize = strlen(name);
	hdata = dbm_fetch(hdb, hkey);
	dbm_close(hdb);

	/*
	 * Make new history item
	 */
	(void) sprintf(new, "%s,%lu", cryptedpassword,
		epoch ? epoch : time((time_t *)0));
	/*
	 * Put new item at front of existing history.
	 */
	if (hdata.dptr) {
		char	*temp = malloc(hdata.dsize + 1);

		(void) strncpy(temp, hdata.dptr, hdata.dsize);
		temp[hdata.dsize] = 0;
		(void) strcat(new, ":");
		(void) strcat(new, 
			clean_history(temp, HistoryDepth, HistoryAge, 0,
				HISTORY_RECLEN - strlen(new) - 4));
		free(temp);
	}
	hdata.dptr = new;
	hdata.dsize = strlen(new);
	debug(DB_PWCHECK, "pwh_dbm_put: new <%s>\n", hdata.dptr);

	/*
	 * Open database read-write to put the data
	 */
	hdb = xdbm_open(HistoryDB, O_RDWR, 0);
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
#else	/* I_DBM */

public char *
pwh_get_dbm(who)
	char	*who;
{
	return(NULL);
}

public int
pwh_put_dbm(name, cryptedpassword, epoch)
	char	*name;
	char	*cryptedpassword;
	time_t	epoch;
{
	return(-1);
}

#endif	/* I_NDBM */

/* End hist_dbm.c */
