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
static char utid[] = "@(#)hist_file.c	1.3 07/20/98 (cc.utexas.edu)";
#endif

/*
 * hist_file.c - Password history database method 'file'
 */

/*
 * pwh_get_file - Read password history from flat file
 *
 * Usage
 *	history_line = pwh_get_file(char *who);
 *
 * Returns
 *	Password history database entry for <who> or NULL if not found.
 */
public char *
pwh_get_file(who)
	char	*who;
{
	FILE	*histfp;		/* History file fp */
	int	in_fd;			/* History file descriptor temp */
	int	xerrno;			/* Errno temp */
	char	ibuf[HISTORY_RECLEN];	/* Input buffer */
	struct stat statbuf;		/* History file stat buffer */
	static char	rdata[HISTORY_RECLEN];	/* Return data */

	if (HistoryDB == 0 || !*HistoryDB) {
		debug(DB_PWCHECK, "pwh_get_file: No history database\n");
		return(0);
	}
	if (stat(HistoryDB, &statbuf) < 0) {	/* No history file */
		debug(DB_PWCHECK, "pwh_get_dbm: History database missing\n");
		return(0);
	}
	/*
	 * If cannot open the file as self, change the effective uid
	 * to the owner of the file and try again.
	 * This is for when the history is on an NFS mounted filesystem
	 * that this host does not have root permission.
	 */
	if ((in_fd = open(HistoryDB, O_RDONLY)) < 0) {
		Uid_t	oldeuid;

		debug(DB_PWCHECK,
			"pwh_get_file: first open failure %d\n", errno);
		oldeuid = geteuid();
		if (oldeuid == statbuf.st_uid) {
			debug(DB_PWCHECK,
				"pwh_get_file: file is owned by my euid\n");
			xerrno = EPIPE;
		}
		(void) setreuid(-1, statbuf.st_uid);
		debug(DB_PWCHECK,
			"pwh_get_file: seteuid to %d\n", statbuf.st_uid);
		if ((in_fd = open(HistoryDB, O_RDONLY)) < 0) {
			xerrno = errno;
			debug(DB_PWCHECK,
				"pwh_get_file: second open failure %d\n",
				xerrno);
		}
		(void) setreuid(-1, oldeuid);
	}
	/*
	 * File exists but cannot be opened - this is bad
	 */
	if (in_fd < 0) {
		logerr("Password history '%s' append open failure %d",
			HistoryDB, xerrno);
		return(0);
	}
	if ((histfp = fdopen(in_fd, "r")) == NULL) {
		debug(DB_PWCHECK, "pwh_get_file: Cannot open '%s'\n",
			HistoryDB);
		return(0);
	}

	/*
	 * Return the last line for the user in the history file.
	 * If an entry line is longer than HISTORY_RECLEN, then it will not
	 * have the newline at the end, and so will be ignored.  Not the
	 * best of solutions, but the history file should not be in
	 * such a condition.
	 */
	rdata[0] = 0;
	while (fgets(ibuf, sizeof(ibuf), histfp)) {
		char	*colon;

		if (strchr(ibuf, '\n') == 0)	/* Malformed line - overflow? */
			continue;
			
		chop_nl(ibuf);
		if (*ibuf == 0 || *ibuf == '#')		/* Empty or comment */
			continue;
		if ((colon = strchr(ibuf, ENTRY_SEP)) == 0)
			continue;			/* Bad line */
		*colon++ = 0;
		if (strcmp(who, ibuf) == 0)
			(void) strcpy(rdata, colon);
	}
	(void) fclose(histfp);
	debug(DB_PWCHECK, "pwh_get_file: return <%s>\n", rdata);
	return(rdata[0] ? rdata : 0);
}

/*
 * pwh_put_file
 *	Add password to history file.
 *
 * Usage
 *	pwh_put_file(char *name,  char *crypt_passwd, time_t timestamp)
 * 
 * Returns
 * 	 0 = no history file
 *	 1 = history put OK
 *	-1 = history put failed
 */
public int
pwh_put_file(name, cryptedpassword, epoch)
	char	*name;			/* User name */
	char	*cryptedpassword;	/* Encrypted password to store */
	time_t	epoch;			/* Item timestamp */
{
	int	out_fd,			/* Output file descriptor */
		written,		/* Write count */
		xerrno;			/* Errno copy */
	char	new[HISTORY_RECLEN],	/* Entry build buffer */
		*current;		/* Lookup pointer */
	struct stat statbuf;		/* File status */

	if (stat(HistoryDB, &statbuf) < 0) {	/* No history file */
		debug(DB_PWCHECK, "pwh_put_dbm: No history database\n");
		return(0);
	}

	debug(DB_UPDATE, "pwh_put_file: update '%s'\n", HistoryDB);
	/*
	 * Update history only if file has write permission for owner.
	 * access(2) uses the *real* uid for checking not the *effective*,
	 * making it not useful when running setuid, so this check must be
	 * done via stat(2).
	 */
#if	(CDEBUG <= CDEBUG_SYSTEM)
	if (!(statbuf.st_mode & S_IWUSR)) {
		logerr("Password history '%s' bad mode 0%o\n",
			HistoryDB, statbuf.st_mode);
		return(-1);
	}
#endif
	/*
	 * Make new history item
	 */
	(void) sprintf(new, "%s:%s,%lu", name, cryptedpassword,
			epoch ? epoch : time((time_t *)0) );
	/*
	 * Put new item at front of existing history.
	 */
	if (current = pwh_get_file(name)) {
		char	*t = clean_history(current,
			 	HistoryDepth, HistoryAge, 0,
				HISTORY_RECLEN - strlen(new) - 4);

		(void) strcat(new, ":");
		(void) strcat(new, t);
	}
	debug(DB_PWCHECK, "pwh_file_put: new entry <%s>\n", new);
	(void) strcat(new, "\n");

	/*
	 * Dirty trick - if the process cannot append to the
	 * history file, then try setting the effective uid to the
	 * owner of the file and try again.
	 * This should take care of most NFS root access problems, provided
	 * the history file ownership is non-root.
	 */
	if ((out_fd = open(HistoryDB, O_WRONLY|O_APPEND)) < 0) {
		uid_t	oldeuid;

		debug(DB_UPDATE,
			"pwh_put_file: first open failure %d\n", errno);
		oldeuid = geteuid();
		if (oldeuid == statbuf.st_uid) {
			debug(DB_UPDATE,
				"pwh_put_file: file is owned by my euid\n");
			xerrno = EPIPE;
		}
		(void) setreuid(-1, statbuf.st_uid);
		if ((out_fd = open(HistoryDB, O_WRONLY|O_APPEND)) < 0) {
			xerrno = errno;
			debug(DB_UPDATE,
				"pwh_put_file: second open failure %d\n",
				xerrno);
		}
		(void) setreuid(-1, oldeuid);
	}
	/*
	 * File exists but cannot be opened - this is bad
	 */
	if (out_fd < 0) {
		logerr("Password history '%s' append open failure %d",
			HistoryDB, xerrno);
		return(-1);
	}
	/*
	 * Write the new entry at EOF.
	 * This is a quick & dirty way to update, but makes the
	 * history database purge more painful.
	 */
	written = write(out_fd, new, strlen(new));
	xerrno = errno;
	(void) close(out_fd);
	if (written != strlen(new)) {
		logerr("Password history '%s' append failure %d",
			HistoryDB, xerrno);
		return(-1);
	}
	return(1);
}
/* End hist_file.c */
