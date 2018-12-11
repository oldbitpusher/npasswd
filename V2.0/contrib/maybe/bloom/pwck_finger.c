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
 *	pwck_finger - Look for match to "dotfile" items
 *	Returns:
 *		PWCK_FINGER_C if match
 *		PWCK_OK otherwise
 */

#include "checkpasswd.h"
#include "CCStr.h"
#include "Blf.h"
#include "Finger.h"

pwck_finger(password, userid, mesgbuf)
char	*password;	/* Password to check */
int	userid;		/* NOTUSED */
char	*mesgbuf;	/* Message buffer NOTUSED */
{
    char* s;
    char buf[11];
    int any;

#ifdef	DEBUG
    printf("pwck_finger: \"%s\"\n", password);
#endif

    mesgbuf[0] = '\0';

    CCStr(password);
    any = 0;
    while (s = CCStr(0)) {
	strcpy(buf, s);
	strcat(buf, FINGER_SUFFIX);
	if (BlfProbe(buf)) {
#ifdef DEBUG
	    printf("Found \"%s\"\n", buf);
#endif DEBUG
	    any = 1;
	}
    }

    if (any) 
	return PWCK_FINGER_C;
    else
	return PWCK_OK;
}

/*	End pwck_finger.c */
