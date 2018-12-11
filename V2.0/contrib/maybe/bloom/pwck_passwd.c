/*----------------------------------------------------------------------------*
|                                                                             |
|                           Author: Donald Olivier                            |
|                      Instructional Computing Facility                       |
|                      Harvard School of Public Health                        |
|                            677 Huntington Ave.                              |
|                             Boston, MA 02115                                |
|                           don@hsph.harvard.edu                              |
|                                                                             |
|    This code may be distributed freely, provided this notice is retained.   |
|                                                                             |
*----------------------------------------------------------------------------*/

/*
 *	pwck_passwd - Look for match to password file items
 *	Returns:
 *		PWCK_PASSWD if exact match
 *		PWCK_PASSWD_C if construct match
 *		PWCK_OK otherwise
 */

#include "checkpasswd.h"
#include "CCStr.h"
#include "Blf.h"
#include "Finger.h"

pwck_passwd(password, userid, mesgbuf)
char	*password;	/* Password to check */
int	userid;		/* NOTUSED */
char	*mesgbuf;	/* Message buffer NOTUSED */
{
    char* s;
    char buf[11];
    int any;

#ifdef	DEBUG
	printf("pwck_passwd: \"%s\"\n", password);
#endif

    mesgbuf[0] = '\0';

    CCStr(password);
    any = 0;
    while (s = CCStr(0)) {
	strcpy(buf, s);
	strcat(buf, PASSWD_SUFFIX);
	if (BlfProbe(buf)) {
#ifdef DEBUG
	    printf("Found \"%s\"\n", buf);
#endif DEBUG
	    any = 1;
	}
    }

    if (any) 
	return PWCK_PASSWD_C;
    else
	return PWCK_OK;
}

/*	End pwck_passwd.c */
