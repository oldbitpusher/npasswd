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

/*
 *	This program duplicates the manual page behavior of the 4.XBSD
 *	chfn(1) command.
 */
#include "npasswd.h"
#include "Methods/pwm_defs.h"

#ifndef lint
static char sccsid[] = "@(#)chfn.c	1.14 08/11/00 (cc.utexas.edu) /usr/share/src/private/ut/share/packages/npasswd/V2.0/src/SCCS/s.chfn.c";
#endif

Config_Value char	*Chfn_Help = CHFN_HELP,
			*Chfn_Motd = CHFN_MOTD;

#define	GECOS_SIZE	128

private int	check_name _((char *));
private int	check_roomnum _((char *));
private int	check_phone _((char *));

struct gecosFields {
	char	*label;
	int	(*check)();
	char	*oldvalue;
};

/* These must be in the right order */
private struct gecosFields Fields[] = {
	{ "Name",		check_name },
	{ "Office number",	check_roomnum },
	{ "Office phone",	check_phone },
	{ "Home phone",		check_phone },
	{ 0 },
};

public void chfn(theUser, theCaller)
struct mpasswd	*theUser,
		*theCaller;
{
	char	newGecos[GECOS_SIZE];
	char	*t;
	char	**oldGecos;
	char	**x;
	int	field;
	int	ismore = 1;
	struct gecosFields *gptr;
	struct mpasswd	*newUser;

#ifdef	USE_NIS
	yp_password(theUser);	/* If a NIS client get user password */
#endif
	if (theCaller->mpw_uid &&
	    strcmp(theCaller->mpw_name, theUser->mpw_name))
		die("Permission denied.\n");

	motd(Chfn_Motd, 0);
	newGecos[0] = 0;

	if (!XSwitches[Xsw_UseStdin]) {
		printf("Changing finger information for %s on %s\n",
			theUser->mpw_name, theUser->pws_loc);
		printf("Default values are printed inside of '[]'\n");
		printf("To accept the default, type <return>\n");
		printf("To have a blank entry, type the word 'none'\n");
		printf("For more information, type '?'\n");
		fflush(stdout);
	}
	oldGecos = split(theUser->mpw_gecos, ',', 0, 0);

	for (gptr = Fields, x = oldGecos; gptr->label; gptr++) {
		if (x && *x) gptr->oldvalue = *x++;
		else gptr->oldvalue = "";
	}

	for (field = 0; (&Fields[field])->label; field++) {
		char	inbuf[GECOS_SIZE];

		gptr = &Fields[field];
		if (!XSwitches[Xsw_UseStdin])
			printf("%s [%s]: ", gptr->label, gptr->oldvalue);

		if (fgets(inbuf, GECOS_SIZE, stdin) == NULL) {
			if (feof(stdin)) {
				printf("\nFinger information unchanged\n");
				return;
			}
			else {
				die("Error while reading stdin.\n");
			}
		}
		chop_nl(inbuf);
		if (strcmp(inbuf, "?") == 0) {
			motd(Chfn_Help, "Sorry, there is no help.\n");
			field--;
			continue;
		} else if (*inbuf == '\0') {
			(void) strncpy(inbuf, gptr->oldvalue, sizeof inbuf);
		} else if (strcasecmp(inbuf, "none") == 0) {
			inbuf[0] = 0;
		} else {
			if (!(gptr->check)(inbuf)) {
				printf("Invalid %s: %s\n", gptr->label, inbuf);
				fflush(stdout);
				field--;
				continue;
			}
		}
		(void) strcat(newGecos, inbuf);
		(void) strcat(newGecos, ",");
	}
	t = strrchr(newGecos, ',');
	*t = 0;

	newUser = copympwent(theUser, (struct mpasswd *)0);
	newUser->mpw_gecos = newGecos;

	pw_replace(theUser, newUser, CHG_GECOS);
	syslog(LOG_INFO,
	       "Finger information changed on %s for %s by %s\n",
	       theUser->pws_loc, theUser->mpw_name, theCaller->mpw_name);
}

/*
 *	check_name	- check for valid user name
 *	check_roomnum	- check for valid room number
 *	check_phone	- check for valid phone number
 *
 *	These three routines can be used to provide sanity checks for 
 *	 values to be stored in the password file gecos fields.
 *
 *	Return 1 if field is OK
 *	       0 if not.
 */

private int
check_name (name)
	char	*name;
{
	for ( ; *name; name++ ) {
		if (*name == ':' || *name == ',' || !isprint(*name)) {
			return(0);
		}
	}
	return(1);
}

private int
check_roomnum (num)
char	*num;
{
	for ( ; *num != '\0' ; num++ ) {
		if (*num == ':' || *num == ',' || !isprint(*num)) {
			return 0;
		}
	}
	return 1;
}

private int
check_phone (phonenum)
char	*phonenum;
{
	for ( ; *phonenum != '\0' ; phonenum++ ) {
		if (!isdigit (*phonenum) && *phonenum != '-' &&
		    *phonenum != '(' && *phonenum != ')') {
			return 0;
		}
		/* Space is ok */
	}
	return 1;
}
/*
 * End chfn.c
 */
