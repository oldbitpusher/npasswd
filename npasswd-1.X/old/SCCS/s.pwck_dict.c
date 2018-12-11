h58410
s 00004/00001/00211
d D 1.4 92/01/27 17:14:23 clyde 4 3
c Make sure that IFS are set to safe values
e
s 00137/00078/00075
d D 1.3 92/01/27 16:48:54 clyde 3 2
c Rewrite of InDictionary(): 
c 1. Remove all "MDBM" hooks.
c 2. Reorder code to make DBM code contigious.
c 3. Use fgrep and a pattern file for flat file searches.
e
s 00008/00008/00145
d D 1.2 90/11/26 09:44:10 clyde 2 1
c Rename one variable to avoid brain-damaged Ultrix compiler
e
s 00153/00000/00000
d D 1.1 89/05/18 10:05:51 clyde 1 0
c date and time created 89/05/18 10:05:51 by clyde
e
u
U
t
T
I 3
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
E 3
I 1
/*
 *	pwck_dictionary - Look in the forbidden password dictionaries.
 *	Returns:
 *		PWCK_INDICT if <password> was in any dictionary
 *		PWCK_OK if not
 */

#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu)";
#endif

#include "checkpasswd.h"

dictionary	*dictionaries = 0;	/* List of dictionaries */
D 3
static char	*egrep = "PATH=/bin:/usr/bin:/usr/ucb; egrep -s"; /* egrep */
E 3
I 3
D 4
static char	*grep = "PATH=/bin:/usr/bin:/usr/ucb; fgrep -s"; /* fgrep */
E 4
I 4
static char	*grep = "\
	IFS=' \t'; export IFS;\
	PATH=/bin:/usr/bin:/usr/ucb; export PATH;\
	fgrep -s"; 				/* fgrep command */
E 4
E 3

pwck_dictionary(password, userid, mesgbuf)
char	*password;	/* Password to check */
int	userid;		/* NOTUSED */
char	*mesgbuf;	/* Message buffer */
{
	int	rcode;		/* Return code temp */
	char	*p;		/* Scratch */
	dictionary *d;		/* Current dictionary */

	/*
	 * If there are any non-alpha characters 
	 * don't bother with the dictionary checks.
	 */
	for (p = password; *p; p++) {
		if (!isalpha(*p))
			return(PWCK_OK);
	}
#ifdef	DEBUG
	printf("pwck_dictionary: \"%s\"\n", password);
#endif
	for (d = dictionaries; d; d = d->dict_next) {
#ifdef	DEBUG
D 3
		printf("\tdictionary '%s'\n", d->dict_path);
E 3
I 3
	  printf("\tdictionary '%s'\n", d->dict_path);
E 3
#endif
D 3
		if ((rcode = InDictionary(d->dict_path, password)) != PWCK_OK){
E 3
I 3
		if ((rcode = InDictionary(d->dict_path, password)) != PWCK_OK) {
E 3
			(void) sprintf(mesgbuf,
				"Password found in dictionary '%s'",
				d->dict_path);
			return(rcode);
		}
	}
	return(PWCK_OK);
}

D 3
#ifdef  MDBM
E 3
/*
D 3
 *	Use the 'mdbm' package by Chris Torek and others
 */
#include "mdbm.h"
#define	DBM		struct mdbm
#define	DBM_FETCH	mdbm_fetch
#define	DBM_CLOSE	mdbm_close
#endif

/*
 *	Using the 4.3BSD 'ndbm' routines
 */
#ifdef  NDBM
#include <ndbm.h>
#define DBM_FETCH	dbm_fetch
#define DBM_CLOSE	dbm_close
#endif

/*
E 3
D 2
 *	IsInDictionary - look for <password> in <dictionary>
E 2
I 2
 *	InDictionary - look for <password> in <dictionary>
E 2
 *
 *	Look in a DBM version of the dictionary if present, 
D 3
 *	else use egrep to search the flat file.
E 3
I 3
 *	else use fgrep to search the flat file.
E 3
 *
 *	Look for <password>, then if the first letter
 *	is capitalized, force to lower and look again.  I don't care
 *	if <password> is in the dictionary but has mixed case letters.
 *	BUT if the first letter has been capitalized, I care because
 *	that's not a sufficent permutation to be secure.
 *
 *	If more than the first letter is capitalized, then the dictionary
 *	lookup will fail.
 *
 *	Returns:
 *		PWCK_INDICT if <password> was found in <dictionary>
 *		PWCK_OK if not
 */
I 3
/*
 * (minar@reed.edu) changed the grep to store things in a temporary file,
 * so that you can't see it on the command line. Note if there are any
 * errors (couldn't open the file, etc) we just return that the password
 * is bad. Not good failure handling. I'm pretty careful about the security
 * of the temp file, I think.
 */

/*	Using the 4.3BSD 'ndbm' routines for dictionaries */
#ifdef  NDBM
#include <ndbm.h>
#endif

E 3
static
D 2
InDictionary(dictionary, password)
char	*dictionary,		/* Pathname of dictionary */
E 2
I 2
InDictionary(which_dictionary, password)
D 3
char	*which_dictionary,		/* Pathname of dictionary */
E 3
I 3
char	*which_dictionary,	/* Pathname of dictionary */
E 3
E 2
	*password;		/* Plaintext of password */
{
D 3
#if	defined(NDBM) || defined(MDBM)
	DBM	*dbp;		/* DBM database pointer */
	datum	k,		/* DBM lookup key */
		d;		/* DBM lookup datum */
#endif
	int	uc = isupper(password[0]);	/* Is first char UC? */
	char	pwtemp[BUFSIZ];			/* Scratch buffer */
#ifdef	MDBM
D 2
	if ((dbp = mdbm_open(dictionary, 0, 0,
E 2
I 2
	if ((dbp = mdbm_open(which_dictionary, 0, 0,
E 2
	    (int *)0, (int *)0, (char *)0)) == (DBM *)0)
#endif
E 3
I 3
	char	command[BUFSIZ],/* Command build buffer */
		pwtemp[BUFSIZ];	/* Scratch buffer */
	int	rc;		/* Return code from sytem(3) */
	char	*grepfile;	/* filename for pw */
	char	*xp;		/* Scratch */
	char	fcu,		/* First char of password (upper case) */
		fcl;		/* First char of password (lower case) */
	FILE	*fp;		/* FP for pw */
	struct stat	statGrepfile;	/* stat of password file */
	extern char	*mktemp();

	fcu = fcl = password[0];
	if (islower(password[0]))
		fcu = toupper(password[0]);
	if (isupper(password[0]))
		fcl = tolower(password[0]);

E 3
#ifdef	NDBM
D 2
	if ((dbp = dbm_open(dictionary, 0, 0)) == (DBM *)0)
E 2
I 2
D 3
	if ((dbp = dbm_open(which_dictionary, 0, 0)) == (DBM *)0)
E 2
#endif
E 3
	{
D 3
		char	command[BUFSIZ];	/* Command build buffer */
		int	rc;			/* Return code from sytem(3) */
E 3
I 3
	DBM	*dbp;		/* DBM database pointer */
E 3

D 2
		if ((rc = open(dictionary, 0)) < 0)
E 2
I 2
D 3
		if ((rc = open(which_dictionary, 0)) < 0)
E 2
			return(PWCK_OK);
E 3
I 3
	if ((dbp = dbm_open(which_dictionary, 0, 0)) != (DBM *)0) {
		/* Look in the DBM version of the dictionary.  */
		datum	k,		/* DBM lookup key */
			d;		/* DBM lookup datum */
		int	found = 0;	/* Was word found in DBM dict? */

		(void) strcpy(pwtemp, password);
		k.dptr = pwtemp;
		k.dsize = strlen(pwtemp);

		pwtemp[0] = fcu;
		d = dbm_fetch(dbp, k);
		if (d.dptr) found++;

		pwtemp[0] = fcl;
		d = dbm_fetch(dbp, k);
		if (d.dptr) found++;

		xp = _flipstring(password, 1);
		(void) strcpy(pwtemp, xp);
		(void) free(xp);
		d = dbm_fetch(dbp, k);
		if (d.dptr) found++;

		dbm_close(dbp);
		return(found ? PWCK_INDICT : PWCK_OK);
	}
	}
#endif
	/* Use grep to look in the flat dictionary file */
	if ((rc = open(which_dictionary, 0)) < 0)
		return(PWCK_OK);
	(void) close(rc);

	(void) strcpy(pwtemp, "/tmp/.XXXXXX");
	grepfile = mktemp(pwtemp);
#ifdef	O_CREAT
	if ((rc = open(grepfile, O_RDWR|O_CREAT, 0400)) < 0)
		return(PWCK_INDICT);   /* file create failed, bail out */
	if ((fp = fdopen(rc, "w")) == NULL) {
E 3
		(void) close(rc);
D 3
		/*
		 * If the first letter is capitalized, look for
		 * "[wW]ord" else look for "word"
		 */
		if (uc) 
			(void) sprintf(command,
				"%s '^[%c%c]%s$' %s > /dev/null",
				egrep, password[0], password[0] | 040,
D 2
				&password[1], dictionary);
E 2
I 2
				&password[1], which_dictionary);
E 2
		else
			(void) sprintf(command, "%s '^%s$' %s > /dev/null",
D 2
				egrep, password, dictionary);
E 2
I 2
				egrep, password, which_dictionary);
E 2
		rc = system(command);
		if (rc == 0) 
			return(PWCK_INDICT);
		else
			return(PWCK_OK);
	} 
#if	defined(NDBM) || defined(MDBM)
#define	returnwith(code) { DBM_CLOSE(dbp); return(code); }
	/*
	 * Look in the DBM version of the dictionary.
	 */
	(void) strcpy(pwtemp, password);
	k.dptr = pwtemp;
	k.dsize = strlen(pwtemp);
	d = DBM_FETCH(dbp, k);
	if (d.dptr)
		returnwith(PWCK_INDICT);
	if (uc) {
		pwtemp[0] |= 040;
		d = DBM_FETCH(dbp, k);
		if (d.dptr)
			returnwith(PWCK_INDICT);
E 3
I 3
		return(PWCK_INDICT);   /* fopen failed, bail out */
E 3
	}
D 3
	returnwith(PWCK_OK);
#endif	/* defined(NDBM) || defined(MDBM) */
E 3
I 3
#else
	if ((fp = fopen(grepfile, "w")) == NULL)
		return(PWCK_INDICT);   		/* fopen failed */
	if (chmod(grepfile, 0400) == -1) {
		closePWFile(fp, grepfile);	/* chmod failed */
		return(PWCK_INDICT);
	}
#endif
	if (stat(grepfile, &statGrepfile) == -1) {
		closePWFile(fp, grepfile);
		return(PWCK_INDICT);		/* Couldn't stat file */
	}
	if (statGrepfile.st_nlink > 1) {    	/* Someone else has a link! */
		closePWFile(fp, grepfile);
		return(PWCK_INDICT);		/* so don't use it */
	}
	(void) fprintf(fp, "%c%s\n", fcu, &password[1]); /* "Password" */
	(void) fprintf(fp, "%c%s\n", fcl, &password[1]); /* "password" */
	xp = _flipstring(password, 1);
	(void) fprintf(fp, "%s\n", xp);		/* "drowssap" */
	(void) free(xp);
	(void) fflush(fp);

	(void) sprintf(command, "%s -f %s %s > /dev/null",
		grep, grepfile, which_dictionary);

	rc = system(command);
	closePWFile(fp, grepfile);

	if (rc == 0) 
		return(PWCK_INDICT);
	else
		return(PWCK_OK);
E 3
}
D 3
/*	End %M% */
E 3
I 3

/*
 * closePWFile - Carefully close the plaintext password file.
 *
 * We first scribble over the file, in case something weird has happened.
 * This isn't perfect, but neither is UNIX. Remember to make the string
 * long enough to overwrite whatever is in the file.
 * Currently, its just 3 plaintexts.
 */
char	*foomsg =
"This file used to contain interesting stuff, but we have now overwritten it.\n\
Try something more interesting.\n\tLove and kisses, The Management\n";

closePWFile(fp, filename)
FILE	*fp;
char	*filename;
{
	(void) rewind(fp);
	(void) fprintf(fp, "%s", foomsg);
	(void) fclose(fp);
	(void) unlink(filename);
}
/*	End %M% 	*/
E 3
E 1
