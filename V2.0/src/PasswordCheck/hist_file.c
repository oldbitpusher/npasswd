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
static char utid[] = "@(#)hist_file.c	1.4 07/23/99 (cc.utexas.edu)";
#endif

/*
 * hist_file.c - Password history database method 'file'
 */


/*
 * pwh_open_file
 *	Open the password history file
 *
 * Usage
 *	pwh_open_file(int mode)
 * 
 * Returns
 * 	 open file descriptor or -1 on error
 */
private
pwh_file_open(mode)
	int	mode;			/* File open mode */
{
	int	fd;			/* File descriptor */

	if ((fd = open(HistoryDB, mode)) < 0) {
		struct stat statbuf;		/* History file stat buffer */
		Uid_t	olduid;			/* Saved real uid */

		debug(DB_PWCHECK,
			"pwh_file_open: first open failure %d\n", errno);

		if (stat(HistoryDB, &statbuf) < 0) {	/* No history file */
			debug(DB_PWCHECK, "pwh_file_open: Stat error %d\n",
				errno);
			return(-1);
		}
		/*
		 * If the process cannot open the history file,
		 * set process real uid to the file owner and try again.
		 * This should take care of most NFS root access problems,
		 * provided the history file ownership is non-root.
		 */
		olduid = getuid();
		if (setreuid(statbuf.st_uid, -1) < 0) {
			debug(DB_PWCHECK,
				"pwh_file_open: setuid failure %d\n", errno);
			return(-1);
		}
		debug(DB_PWCHECK, "pwh_file_open: setuid to %d\n", getuid());
		if ((fd = open(HistoryDB, mode)) < 0) {
			debug(DB_PWCHECK,
				"pwh_file_open: second open failure %d\n",
				errno);
		}
		if (setreuid(olduid, -1) < 0) {
			debug(DB_PWCHECK,
				"pwh_file_open: uid reset failure %d\n", errno);
		}
		debug(DB_PWCHECK, "pwh_file_open: reset uid to %d\n", getuid());
	}
	return(fd);
}

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
	char	ibuf[HISTORY_RECLEN];	/* Input buffer */
	struct stat statbuf;		/* History file stat buffer */
	static char	rdata[HISTORY_RECLEN];	/* Return data */

	if (HistoryDB == 0 || !*HistoryDB) {
		debug(DB_PWCHECK, "pwh_get_file: No history database\n");
		return(0);
	}
	/*
	 * File exists but cannot be opened - this is bad
	 */
	if ((in_fd = pwh_file_open(O_RDONLY)) < 0)
		return(0);
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
		written;		/* Write count */
	char	new[HISTORY_RECLEN],	/* Entry build buffer */
		*current;		/* Lookup pointer */

	debug(DB_UPDATE, "pwh_put_file: update '%s'\n", HistoryDB);
	/*
	 * Open the history file
	 */
	if ((out_fd = pwh_file_open(O_WRONLY|O_APPEND)) < 0)
		return(-1);
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
	 * Write the new entry at EOF.
	 * This is a quick & dirty way to update, but makes the
	 * history database purge more painful.
	 */
	written = write(out_fd, new, strlen(new));
	(void) close(out_fd);
	if (written != strlen(new)) {
		logerr("Password history '%s' append failure %d",
			HistoryDB, errno);
		return(-1);
	}
	return(1);
}
/* End hist_file.c */
