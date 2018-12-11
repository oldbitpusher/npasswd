
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

pwck_dictionary(password, userid, mesgbuf)
char	*password;	/* Password to check */
int	userid;		/* NOTUSED */
char	*mesgbuf;	/* Message buffer */
{
	int	rcode;		/* Return code temp */
	char	*p;		/* Scratch */
	dictionary *d;		/* Current dictionary */

	/*
	 * If there are any non-alphanumeric characters 
	 * don't bother with the dictionary checks.
	 * note that we still want to check strings like
	 * "colby0" to see if they might be in the dictionary.
	 */
	for (p = password; *p; p++) {
		if (!isalnum(*p))
			return(PWCK_OK);
	}
	for (d = dictionaries; d; d = d->dict_next) {
#ifdef	DEBUG
		printf("pwck_dictionary: searching %s for %s\n", 
			d->dict_path,password);
#endif
		if ((rcode = InDictionary(d->dict_path, password)) != PWCK_OK) {
			(void) sprintf(mesgbuf,
			"Password or reversed password found in dictionary '%s'",
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
 *	else use npasswd's internal search mechanism.
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

/*	Using the 4.3BSD 'ndbm' routines for dictionaries */
#ifdef  NDBM
#include <ndbm.h>
#endif

static
InDictionary(which_dictionary, password)
char	*which_dictionary,	/* Pathname of dictionary */
	*password;		/* Plaintext of password */
{
        char	*xp;
	int	rc;

#ifdef	NDBM
	/* dbm database search method */
	if((rc = dbm_search(which_dictionary, password)) != PWCK_FAIL)
		return(rc);
#endif
	/* npasswd internal search method */
        /* "password" and "Password" */
	rc = pwck_search(which_dictionary, password);
        if(rc == PWCK_INDICT || rc == PWCK_FAIL) return(rc);

        /* reversed passwords: "drowssap" and "Drowssap" */
	xp = _flipstring(password,1);
#ifdef DEBUG
        printf("reversed password = %s\n",xp);
#endif
	rc = pwck_search(which_dictionary, xp);
        return(rc);
}

/*
 * dbm_search: Look in dbm version of dictionary for the password.
 */

#ifdef	NDBM
dbm_search(which_dictionary, password)
char	*which_dictionary,	/* Pathname of dictionary */
	*password;		/* Plaintext of password */
{
	DBM	*dbp;		/* DBM database pointer */
	char	pwtemp[BUFSIZ];	/* Scratch buffer */
	char	*xp;		/* Scratch */
	datum	k,		/* DBM lookup key */
		d;		/* DBM lookup datum */
	int	found = 0;	/* Was word found in DBM dict? */

	if ((dbp = dbm_open(which_dictionary, 0, 0)) != (DBM *)0) {
#ifdef	DEBUG
	        printf("pwck_dictionary: using dbm version of %s\n",
			which_dictionary);
#endif
		(void) strcpy(pwtemp, password);
		k.dptr = pwtemp;
		k.dsize = strlen(pwtemp);

		pwtemp[0] = toupper(password[0]);;
		d = dbm_fetch(dbp, k);
		if (d.dptr) found++;

		pwtemp[0] = tolower(password[0]);;
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
	return(PWCK_FAIL);
}
#endif
/*	End pwck_dict.c 	*/
