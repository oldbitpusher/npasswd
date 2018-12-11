h19448
s 00061/00092/00176
d D 1.4 99/07/23 16:34:47 clyde 4 3
c 1. Move history file opens into one routine
c 2. Use real uid for history file access (don't change effective uid)
e
s 00048/00003/00220
d D 1.3 98/07/20 17:00:32 clyde 3 2
c Use seteuid() trick to open history db file
e
s 00056/00050/00167
d D 1.2 98/06/08 14:07:15 clyde 2 1
c Bring code up to release condition
e
s 00217/00000/00000
d D 1.1 98/06/04 08:47:06 clyde 1 0
c date and time created 98/06/04 08:47:06 by clyde
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
 * %M% - Password history database method 'file'
 */

I 4

E 4
/*
I 4
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
E 4
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
D 2
	char	ibuf[BUFSIZ];		/* Input buffer */
	static char	rdata[BUFSIZ];	/* Return data */
E 2
I 2
D 3
	char	ibuf[HISTORY_RECLEN];		/* Input buffer */
E 3
I 3
	int	in_fd;			/* History file descriptor temp */
D 4
	int	xerrno;			/* Errno temp */
E 4
	char	ibuf[HISTORY_RECLEN];	/* Input buffer */
	struct stat statbuf;		/* History file stat buffer */
E 3
	static char	rdata[HISTORY_RECLEN];	/* Return data */
E 2

D 2
	if (PasswordHistoryDB == 0 || !*PasswordHistoryDB) {
		debug(DB_PWCHECK, "pwh_get_file: disabled\n");
E 2
I 2
	if (HistoryDB == 0 || !*HistoryDB) {
		debug(DB_PWCHECK, "pwh_get_file: No history database\n");
E 2
		return(0);
	}
D 2
	if ((histfp = fopen(PasswordHistoryDB, "r")) == NULL) {
		debug(DB_PWCHECK, "pwh_get_file: No file '%s'\n",
			PasswordHistoryDB);
E 2
I 2
D 3
	if ((histfp = fopen(HistoryDB, "r")) == NULL) {
		debug(DB_PWCHECK, "pwh_get_file: Cannot open '%s'\n", HistoryDB);
E 3
I 3
D 4
	if (stat(HistoryDB, &statbuf) < 0) {	/* No history file */
		debug(DB_PWCHECK, "pwh_get_dbm: History database missing\n");
E 3
E 2
		return(0);
	}
E 4
	/*
I 3
D 4
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
E 4
	 * File exists but cannot be opened - this is bad
	 */
D 4
	if (in_fd < 0) {
		logerr("Password history '%s' append open failure %d",
			HistoryDB, xerrno);
E 4
I 4
	if ((in_fd = pwh_file_open(O_RDONLY)) < 0)
E 4
		return(0);
D 4
	}
E 4
	if ((histfp = fdopen(in_fd, "r")) == NULL) {
		debug(DB_PWCHECK, "pwh_get_file: Cannot open '%s'\n",
			HistoryDB);
		return(0);
	}

	/*
E 3
D 2
	 * Return the history entry for the user.
E 2
I 2
	 * Return the last line for the user in the history file.
	 * If an entry line is longer than HISTORY_RECLEN, then it will not
	 * have the newline at the end, and so will be ignored.  Not the
	 * best of solutions, but the history file should not be in
	 * such a condition.
E 2
	 */
	rdata[0] = 0;
	while (fgets(ibuf, sizeof(ibuf), histfp)) {
		char	*colon;

D 2
		if (strchr(ibuf, '\n') == 0)		/* Malformed line */
E 2
I 2
		if (strchr(ibuf, '\n') == 0)	/* Malformed line - overflow? */
E 2
			continue;
I 2
			
E 2
		chop_nl(ibuf);
		if (*ibuf == 0 || *ibuf == '#')		/* Empty or comment */
			continue;
		if ((colon = strchr(ibuf, ENTRY_SEP)) == 0)
D 2
			continue;			/* Bad history line */
E 2
I 2
			continue;			/* Bad line */
E 2
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
D 2
 *	pwh_put_file(char *name,  char *crypt_passwd)
E 2
I 2
 *	pwh_put_file(char *name,  char *crypt_passwd, time_t timestamp)
E 2
 * 
 * Returns
 * 	 0 = no history file
 *	 1 = history put OK
 *	-1 = history put failed
 */
public int
D 2
pwh_put_file(name, cryptedpassword)
	char	*name;
	char	*cryptedpassword;
E 2
I 2
pwh_put_file(name, cryptedpassword, epoch)
	char	*name;			/* User name */
	char	*cryptedpassword;	/* Encrypted password to store */
	time_t	epoch;			/* Item timestamp */
E 2
{
D 2
	int	f,
		nw;
	struct stat statbuf;
	char	histent[BUFSIZ],
		out[BUFSIZ];
	int	xerrno;
	time_t	now = time((time_t *)0);
	char	*current;
E 2
I 2
	int	out_fd,			/* Output file descriptor */
D 4
		written,		/* Write count */
		xerrno;			/* Errno copy */
E 4
I 4
		written;		/* Write count */
E 4
	char	new[HISTORY_RECLEN],	/* Entry build buffer */
		*current;		/* Lookup pointer */
D 4
	struct stat statbuf;		/* File status */
E 4
E 2

D 2
	if (stat(PasswordHistoryDB, &statbuf) < 0)	/* No history file */
E 2
I 2
D 4
	if (stat(HistoryDB, &statbuf) < 0) {	/* No history file */
		debug(DB_PWCHECK, "pwh_put_dbm: No history database\n");
E 2
		return(0);
I 2
	}
E 2

E 4
D 2
	debug(DB_UPDATE, "pwh_put_file: update '%s'\n", PasswordHistoryDB);
E 2
I 2
	debug(DB_UPDATE, "pwh_put_file: update '%s'\n", HistoryDB);
E 2
	/*
D 4
	 * Update history only if file has write permission for owner.
	 * access(2) uses the *real* uid for checking not the *effective*,
	 * making it not useful when running setuid, so this check must be
	 * done via stat(2).
E 4
I 4
	 * Open the history file
E 4
	 */
D 4
#if	(CDEBUG <= CDEBUG_SYSTEM)
	if (!(statbuf.st_mode & S_IWUSR)) {
		logerr("Password history '%s' bad mode 0%o\n",
D 2
			PasswordHistoryDB, statbuf.st_mode);
		return(-1);	
E 2
I 2
			HistoryDB, statbuf.st_mode);
E 4
I 4
	if ((out_fd = pwh_file_open(O_WRONLY|O_APPEND)) < 0)
E 4
		return(-1);
E 2
D 4
	}
#endif
E 4
	/*
D 2
	 * Fetch the current history from the file (since we are putting
	 * it into a flat file, assume it came from a flat file.
E 2
I 2
	 * Make new history item
E 2
	 */
I 2
	(void) sprintf(new, "%s:%s,%lu", name, cryptedpassword,
			epoch ? epoch : time((time_t *)0) );
	/*
	 * Put new item at front of existing history.
	 */
E 2
	if (current = pwh_get_file(name)) {
D 2
		/* Prepend new component to entry */
		(void) sprintf(histent, "%s,%lu:%s",
			cryptedpassword, now, current);
		/* Purge undesired components */
		(void) clean_history(histent); 
E 2
I 2
		char	*t = clean_history(current,
			 	HistoryDepth, HistoryAge, 0,
				HISTORY_RECLEN - strlen(new) - 4);

		(void) strcat(new, ":");
		(void) strcat(new, t);
E 2
	}
D 2
	else {
		(void) sprintf(histent, "%s,%lu", cryptedpassword, now);
	}
	/* Make string ready to be appended to file */
	(void) sprintf(out, "%s:%s\n", name, histent);
E 2
I 2
	debug(DB_PWCHECK, "pwh_file_put: new entry <%s>\n", new);
	(void) strcat(new, "\n");
E 2

	/*
D 4
	 * Dirty trick - if the process cannot append to the
	 * history file, then try setting the effective uid to the
	 * owner of the file and try again.
	 * This should take care of most NFS root access problems, provided
	 * the history file ownership is non-root.
	 */
D 2
	if ((f = open(PasswordHistoryDB, O_WRONLY|O_APPEND)) < 0) {
E 2
I 2
	if ((out_fd = open(HistoryDB, O_WRONLY|O_APPEND)) < 0) {
E 2
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
D 2
		if ((f = open(PasswordHistoryDB, O_WRONLY|O_APPEND)) < 0) {
E 2
I 2
		if ((out_fd = open(HistoryDB, O_WRONLY|O_APPEND)) < 0) {
E 2
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
D 2
	if (f < 0) {
E 2
I 2
	if (out_fd < 0) {
E 2
		logerr("Password history '%s' append open failure %d",
D 2
			PasswordHistoryDB, xerrno);
E 2
I 2
			HistoryDB, xerrno);
E 2
		return(-1);
	}
	/*
E 4
D 2
	 * Write the new entry at EOF
	 * This is a cheap & dirty way to update.
	 * The history file should be periodically purged of dead entries.
E 2
I 2
	 * Write the new entry at EOF.
	 * This is a quick & dirty way to update, but makes the
	 * history database purge more painful.
E 2
	 */
D 2
	nw = write(f, out, strlen(out));
E 2
I 2
	written = write(out_fd, new, strlen(new));
E 2
D 4
	xerrno = errno;
E 4
D 2
	(void) close(f);
	if (nw != strlen(out)) {
E 2
I 2
	(void) close(out_fd);
	if (written != strlen(new)) {
E 2
		logerr("Password history '%s' append failure %d",
D 2
			PasswordHistoryDB, xerrno);
E 2
I 2
D 4
			HistoryDB, xerrno);
E 4
I 4
			HistoryDB, errno);
E 4
E 2
		return(-1);
	}
	return(1);
}
D 2

E 2
/* End %M% */
E 1
