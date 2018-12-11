
/* --------------------------------------------------------------------  */
/*                                                                       */
/*                         Author: Clyde Hoover                          */
/*                          Computation Center                           */
/*                   The University of Texas at Austin                   */
/*                          Austin, Texas 78712                          */
/*                         clyde@emx.utexas.edu                          */
/*                   uunet!cs.utexas.edu!ut-emx!clyde                    */
/*                                                                       */
/*This code may be distributed freely, provided this notice is retained. */
/*                                                                       */
/* --------------------------------------------------------------------  */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
/*
 *	pwck_dictionary - Look in the forbidden password dictionaries.
 *	Returns:
 *		PWCK_INDICT if <password> was in any dictionary
 *		PWCK_OK if not
 */

#ifndef lint
static char sccsid[] = "@(#)pwck_dict.c	1.4 1/27/92 (cc.utexas.edu)";
#endif

#include "checkpasswd.h"

dictionary	*dictionaries = 0;	/* List of dictionaries */
static char	*grep = "\
	IFS=' \t'; export IFS;\
	PATH=/bin:/usr/bin:/usr/ucb; export PATH;\
	fgrep -s"; 				/* fgrep command */

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
	  printf("\tdictionary '%s'\n", d->dict_path);
#endif
		if ((rcode = InDictionary(d->dict_path, password)) != PWCK_OK) {
			(void) sprintf(mesgbuf,
				"Password found in dictionary '%s'",
				d->dict_path);
			return(rcode);
		}
	}
	return(PWCK_OK);
}

/*
 *	InDictionary - look for <password> in <dictionary>
 *
 *	Look in a DBM version of the dictionary if present, 
 *	else use fgrep to search the flat file.
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

static
InDictionary(which_dictionary, password)
char	*which_dictionary,	/* Pathname of dictionary */
	*password;		/* Plaintext of password */
{
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

#ifdef	NDBM
	{
	DBM	*dbp;		/* DBM database pointer */

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
		(void) close(rc);
		return(PWCK_INDICT);   /* fopen failed, bail out */
	}
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
}

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
/*	End pwck_dict.c 	*/
