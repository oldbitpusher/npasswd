h15088
s 00001/00000/00284
d D 1.8 00/01/17 18:18:50 clyde 8 7
c Plug file descriptor leak in hist_dbm()
e
s 00008/00015/00276
d D 1.7 99/07/23 16:35:02 clyde 7 6
c Use real uid for history file access (don't change effective uid)
e
s 00014/00008/00277
d D 1.6 99/07/23 13:47:11 clyde 6 5
c More twiddling of dbm_xopen()
e
s 00011/00001/00274
d D 1.5 99/07/23 11:33:06 clyde 5 4
c More error checking in dbm_xopen()
e
s 00002/00002/00273
d D 1.4 98/10/13 17:37:16 clyde 4 3
c Fix some debug messages
e
s 00057/00026/00218
d D 1.3 98/07/20 17:00:58 clyde 3 2
c Use seteuid() trick to always open history dbm
e
s 00069/00048/00175
d D 1.2 98/06/08 14:07:34 clyde 2 1
c Bring code up to release condition
e
s 00223/00000/00000
d D 1.1 98/06/04 08:47:05 clyde 1 0
c date and time created 98/06/04 08:47:05 by clyde
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

#include "pwck_defines.h"
#include "options.h"
#include "pwck_history.h"

#ifndef lint
static char utid[] = "%W% %G% (cc.utexas.edu)";
#endif

/*
 * %M% - Password history database method 'DBM'
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

I 3
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
D 6
	uid_t	oldeuid = geteuid();	/* Saved effective uid */
E 6
I 6
D 7
	Uid_t	oldeuid = geteuid();	/* Saved effective uid */
E 7
I 7
	Uid_t	olduid = getuid();	/* Saved real uid */
E 7
E 6

	if (hdb = dbm_open(path, flags, mode))
		return(hdb);

	/*
	 * If cannot open the file as self, change the effective uid
	 * to the owner of the .dir file and try again.
D 6
	 * This is for when the history is on an NFS mounted filesystem
	 * that this host does not have root permission.
E 6
I 6
	 *
	 * This is for when the history is on an NFS filesystem
	 * for which this host does not have root permission.
E 6
	 */
	debug(DB_UPDATE, "xdbm_open: first open failure %d\n", errno);

	(void) strcpy(dbtemp, path);
	(void) strcat(dbtemp, ".dir");
D 6
	if (stat(dbtemp, &statbuf) < 0)
E 6
I 6
	if (stat(dbtemp, &statbuf) < 0) {
D 7
		debug(DB_PWCHECK,
			"xdbm_open: stat failure %d\n", errno);
E 7
I 7
		debug(DB_PWCHECK, "xdbm_open: stat failure %d\n", errno);
E 7
E 6
		return(0);
I 6
	}
E 6
D 7

D 5
	(void) setreuid(-1, statbuf.st_uid);
E 5
I 5
	if (oldeuid == statbuf.st_uid) {
E 7
I 7
	if (setreuid(statbuf.st_uid, -1) < 0) {
E 7
		debug(DB_PWCHECK,
D 6
			"xdbm_open: file is owned by my euid\n");
E 6
I 6
D 7
			"xdbm_open: file is owned by euid (%d) - cannot open\n",
			oldeuid);
E 7
I 7
			"xdbm_open: setuid failure %d\n", errno);
E 7
		return(0);
E 6
	}
D 7
	if (setreuid(-1, statbuf.st_uid) < 0) {
D 6
		debug(DB_UPDATE,
E 6
I 6
		debug(DB_PWCHECK,
E 6
			"xdbm_open: setreuid failure %d\n", errno);
D 6
		return(NULL);
E 6
I 6
		return(0);
E 6
	}
E 7
	debug(DB_PWCHECK, "xdbm_open: seteuid to %d\n", statbuf.st_uid);
E 5
	if ((hdb = dbm_open(HistoryDB, O_RDWR, 0)) == 0) {
D 6
		debug(DB_UPDATE,
E 6
I 6
		debug(DB_PWCHECK,
E 6
D 4
			"pwh_put_dbm: second open failure %d\n", errno);
E 4
I 4
			"xdbm_open: second open failure %d\n", errno);
E 4
	}
D 7
	(void) setreuid(-1, oldeuid);
I 5
	debug(DB_PWCHECK, "xdbm_open: reset euid to %d\n", oldeuid);
E 7
I 7
	if (setreuid(olduid, -1) < 0) {
		debug(DB_PWCHECK, "xdbm_open: uid reset failure %d\n", errno);
	}
	debug(DB_PWCHECK, "xdbm_open: reset euid to %d\n", olduid);
E 7
E 5
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
E 3
public char *
pwh_get_dbm(who)
D 2
	char	*who;
E 2
I 2
	char	*who;		/* Username to get */
E 2
{
D 2
	DBM	*hdb;
	datum	hkey,
		hdata;
	static char	etemp[BUFSIZ];
E 2
I 2
	DBM	*hdb;		/* DBM pointer */
	datum	hkey,		/* Lookup key */
		hdata;		/* Return data key */
	static char	rdata[HISTORY_RECLEN];	/* Return data */
E 2

D 2
	if (PasswordHistoryDB == 0 || !*PasswordHistoryDB) {
		debug(DB_PWCHECK, "pwh_get_dbm: disabled\n");
E 2
I 2
	if (HistoryDB == 0 || !*HistoryDB) {
		debug(DB_PWCHECK, "pwh_get_dbm: No history database\n");
E 2
		return(0);
	}
D 2
	if ((hdb = dbm_open(PasswordHistoryDB, O_RDONLY, 0)) == 0) {
		debug(DB_PWCHECK, "pwh_get_dbm: No DBM '%s'\n",
			PasswordHistoryDB);
E 2
I 2
D 3
	if ((hdb = dbm_open(HistoryDB, O_RDONLY, 0)) == 0) {
E 3
I 3

	if ((hdb = xdbm_open(HistoryDB, O_RDONLY, 0)) == 0) {
E 3
		debug(DB_PWCHECK, "pwh_get_dbm: Cannot open '%s'\n", HistoryDB);
E 2
		return(0);
	}
I 3

E 3
I 2
	/*
	 * Lookup history entry
	 */
E 2
	hkey.dptr = who;
	hkey.dsize = strlen(who);
	hdata = dbm_fetch(hdb, hkey);
	(void) dbm_close(hdb);
	if (hdata.dptr) {
D 2
		(void) strncpy(etemp, hdata.dptr, hdata.dsize);
		etemp[hdata.dsize] = 0;
		debug(DB_PWCHECK, "pwh_dbm_put: found <%s>\n", etemp);
		return(etemp);
E 2
I 2
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
D 4
		debug(DB_PWCHECK, "pwh_dbm_put: found <%s>\n", rdata);
E 4
I 4
		debug(DB_PWCHECK, "pwh_get_dbm: found <%s>\n", rdata);
E 4
		return(rdata);
E 2
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
D 2
pwh_put_dbm(name, cryptedpassword)
	char	*name;
	char	*cryptedpassword;
E 2
I 2
pwh_put_dbm(name, cryptedpassword, epoch)
	char	*name;			/* User name */
	char	*cryptedpassword;	/* Encrypted password to store */
	time_t	epoch;			/* Item timestamp */
E 2
{
	DBM	*hdb;			/* Database pointer */
D 2
	datum	hkey,			/* DBM key */
		hdata;			/* DBM data */
E 2
I 2
	datum	hkey,			/* DBM lookup datum */
		hdata;			/* DBM return datum */
E 2
	int	rc = 1;			/* Return code */
D 2
	char	nentry[BUFSIZ];		/* New entry temp */
	time_t	now = time((time_t *)0);	/* Current time */
E 2
I 2
	char	new[HISTORY_RECLEN];	/* New entry temp */
E 2

D 2
	if (PasswordHistoryDB == 0 || !*PasswordHistoryDB) {
E 2
I 2
	if (HistoryDB == 0 || !*HistoryDB) {
E 2
		debug(DB_PWCHECK, "pwh_put_dbm: disabled\n");
		return(0);
	}
D 2
	debug(DB_UPDATE, "pwh_put_dbm: update '%s'\n", PasswordHistoryDB);
E 2
I 2
	debug(DB_UPDATE, "pwh_put_dbm: update '%s'\n", HistoryDB);
E 2
D 7

E 7
	/*
	 * Open database read-only to verify existence and fetch history entry.
	 */
D 2
	if ((hdb = dbm_open(PasswordHistoryDB, O_RDONLY, 0)) == 0) {
		debug(DB_PWCHECK, "pwh_put_dbm: No DB '%s'\n",
			PasswordHistoryDB);
E 2
I 2
D 3
	if ((hdb = dbm_open(HistoryDB, O_RDONLY, 0)) == 0) {
E 3
I 3
	if ((hdb = xdbm_open(HistoryDB, O_RDONLY, 0)) == 0) {
E 3
		debug(DB_PWCHECK, "pwh_put_dbm: Cannot read '%s'\n", HistoryDB);
E 2
		return(0);
	}
	hkey.dptr = name;
	hkey.dsize = strlen(name);
	hdata = dbm_fetch(hdb, hkey);
	dbm_close(hdb);

D 2
	if (hdata.dptr) { /* History entry found - merge in new data */
		char	*etemp = malloc(hdata.dsize + 1);
E 2
I 2
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
E 2

D 2
		if (etemp == 0)
			logdie("(pwh_dbm_put) new entry alloc failed");
		(void) strncpy(etemp, hdata.dptr, hdata.dsize);
		etemp[hdata.dsize] = 0;
		debug(DB_PWCHECK, "pwh_dbm_put: found <%s>\n", etemp);
		(void) sprintf(nentry, "%s:%s,%lu",
			clean_history(etemp), cryptedpassword, now);
		free(etemp);
	} else {
		/*
		 * Make new history entry
		 */
		(void) sprintf(nentry, "%s,%lu", cryptedpassword, now);
E 2
I 2
		(void) strncpy(temp, hdata.dptr, hdata.dsize);
		temp[hdata.dsize] = 0;
		(void) strcat(new, ":");
		(void) strcat(new, 
			clean_history(temp, HistoryDepth, HistoryAge, 0,
				HISTORY_RECLEN - strlen(new) - 4));
		free(temp);
E 2
	}
D 2
	hdata.dptr = nentry;
	hdata.dsize = strlen(nentry);
	debug(DB_PWCHECK, "pwh_dbm_put: new <%s>\n", nentry);
E 2
I 2
	hdata.dptr = new;
	hdata.dsize = strlen(new);
	debug(DB_PWCHECK, "pwh_dbm_put: new <%s>\n", hdata.dptr);
E 2

	/*
	 * Open database read-write to put the data
	 */
D 2
	if ((hdb = dbm_open(PasswordHistoryDB, O_RDWR, 0)) == 0) {
E 2
I 2
D 3
	if ((hdb = dbm_open(HistoryDB, O_RDWR, 0)) == 0) {
E 2
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
D 2
		(void) strcpy(dbtemp, PasswordHistoryDB);
E 2
I 2
		(void) strcpy(dbtemp, HistoryDB);
E 2
		(void) strcat(dbtemp, ".dir");
		if (stat(dbtemp, &statbuf) < 0)
			logdie("pwh_put_dbm: History DB vanished!");

		(void) setreuid(-1, statbuf.st_uid);
D 2
		if ((hdb = dbm_open(PasswordHistoryDB, O_RDWR, 0)) == 0)
E 2
I 2
		if ((hdb = dbm_open(HistoryDB, O_RDWR, 0)) == 0)
E 2
			debug(DB_UPDATE,
				"pwh_put_dbm: second open failure %d\n", errno);
		(void) setreuid(-1, oldeuid);
	}
E 3
I 3
	hdb = xdbm_open(HistoryDB, O_RDWR, 0);
E 3
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
I 8
	(void) dbm_close(hdb);
E 8
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
D 2
pwh_put_dbm(name, cryptedpassword)
E 2
I 2
pwh_put_dbm(name, cryptedpassword, epoch)
E 2
	char	*name;
	char	*cryptedpassword;
I 2
	time_t	epoch;
E 2
{
	return(-1);
}

#endif	/* I_NDBM */

/* End %M% */
E 1
