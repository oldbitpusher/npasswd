
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
/*
 *	pwck_dictionary - Look in the forbidden password dictionaries.
 *	Returns:
 *		PWCK_INDICT if exact match
 *		PWCK_INDICT_C if construct match
 *		PWCK_OK otherwise
 */

#include "checkpasswd.h"
#include "CCStr.h"
#include "Blf.h"
#include "Finger.h"

pwck_dictionary(password, userid, mesgbuf)
char	*password;	/* Password to check */
int	userid;		/* NOTUSED */
char	*mesgbuf;	/* Message buffer */
{
    char* s;
    char buf[33];
    int any;
    int construct;

#ifdef	DEBUG
	printf("pwck_dict: \"%s\"\n", password);
#endif

    CCStr(password);
    any = construct = 0;
    while (s = CCStr(0)) {
	if (!any && strncmp(s, password, max_length))
	    construct = 1;
	if (BlfProbe(s)) {
#ifdef DEBUG
	    printf("Found \"%s\"\n", s);
#endif DEBUG
	    any = 1;
	}
    }

    if (any) 
	if (construct)
	    return PWCK_INDICT_C;
	else
	    return PWCK_INDICT;

    return(PWCK_OK);
}

/*	End pwck_dict.c 	*/
