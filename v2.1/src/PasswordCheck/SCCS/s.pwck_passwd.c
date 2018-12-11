h10727
s 00057/00029/00017
d D 1.12 98/04/07 09:54:29 clyde 12 11
c 1. Add UT copyright 
c 2. Change return type to (char *)
c 3. Punt to Cracklib/FascistGecos()
e
s 00003/00005/00043
d D 1.11 98/03/26 11:08:56 clyde 11 10
c Cosmetic changes
e
s 00002/00002/00046
d D 1.10 96/08/29 12:59:37 clyde 10 9
c Remove 'const' declarations (too much compiler trouble)
e
s 00002/00002/00046
d D 1.9 96/08/13 13:05:41 clyde 9 8
c Add const where useful
e
s 00006/00011/00042
d D 1.8 96/08/06 14:14:10 clyde 8 7
c beta 3 cycle 1 checkin
e
s 00000/00000/00053
d D 1.7 95/04/05 16:20:04 clyde 7 6
c Beta 3 development checkin
e
s 00003/00034/00050
d D 1.6 94/03/15 18:53:40 clyde 6 5
c 1. Use new include files
c 2. Rip out UT userinfo stuff
e
s 00031/00042/00053
d D 1.5 94/01/05 15:49:30 clyde 5 4
c Development checkin
e
s 00003/00000/00092
d D 1.4 92/02/18 16:33:07 clyde 4 3
c Check contents of "PWCK_auxpwline" if non-empty
e
s 00001/00001/00091
d D 1.3 92/01/27 16:45:20 clyde 3 2
c Use new calling sequence for _flipstring()
e
s 00001/00001/00091
d D 1.2 89/06/05 11:00:00 clyde 2 1
c Rename some internal routines to avoid name collisions
e
s 00092/00000/00000
d D 1.1 89/05/18 10:05:55 clyde 1 0
c date and time created 89/05/18 10:05:55 by clyde
e
u
U
t
T
I 1
/*
D 12
 *	pwck_password - Check password candidate against the users' password
 *		file information, or any other information that is publicly
 *		available about this user that a bandit could use as
 *		password guesses.
E 12
I 12
 * Copyright 1998, The University of Texas at Austin ("U. T. Austin").
 * All rights reserved.
E 12
 *
D 8
 *	This code has an option for the User Information Data Base used
 *	at the UT Computation Center.  Here is the place to search 
 *	any local 'finger' database.
I 5
 *
E 8
D 12
 *	Returns:
D 8
 *
E 8
 *		PWCK_OBVIOUS if password is part of the users' passwd info
 *		PWCK_FINGER if password is part of the user's finger info
 *		PWCK_OK if password is ok
E 12
I 12
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
E 12
E 5
 */
I 12
/*
 * pwck_password - Check password candidate against the users' password
 *	file information, or any other information that is publicly
 *	available about this user that a bandit could use as password guesses.
 *
 * Usage
 *	error = pwck_passwd(char *, struct passwd *);
 *
 * Returns
 *	Error message from Cracklib/FascistGecos if password flunks
 *	PWCK_OK if password is ok
 */
E 12
#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu)";
#endif

D 5
#include "checkpasswd.h"
E 5
I 5
D 6
#include "compat.h"
#include "lib.h"
E 6
I 6
D 8
#include "compatibility.h"
E 6
#include "checkpassword.h"
I 6
#include "pwck_lib.h"
E 8
I 8
#include "pwck_defines.h"
E 8
E 6
E 5

D 5
#ifdef	UTEXAS_CC
/*
 *	For UTCC systems
 */
E 5
I 5
D 6
#ifdef	UT_USERINFO
E 5
#include <local/userinfo.h>
D 5
#define	cname	pwp->ui_name
typedef	userptr	pwptr;
#define	setpwent	setuserent
#define	getpwuid	getuserbyuid
E 5
I 5
#endif
E 5

E 6
I 6
D 12
public int
E 6
D 5
#else	/* UTEXAS_CC */

#include	<pwd.h>
#define	cname	pwp->pw_name
typedef	struct passwd *pwptr;

#endif	/* UTEXAS_CC */

pwck_passwd(password, userid, mesg)
char	*password;
int	userid;
char	*mesg;
E 5
I 5
pwck_passwd(password, user, mesg)
E 12
I 12
public char *
pwck_passwd(password, user)
E 12
D 9
	char	*password;		/* Candidate password */
	struct passwd	*user;	/* Passwd info */
E 9
I 9
D 10
	const char	*password;		/* Candidate password */
	const struct passwd	*user;	/* Passwd info */
E 10
I 10
	char	*password;		/* Candidate password */
D 11
	struct passwd	*user;	/* Passwd info */
E 11
I 11
	struct passwd	*user;		/* Passwd info */
E 11
E 10
E 9
D 12
	char	*mesg;			/* Where to stash message */
E 12
E 5
{
D 11
	char	temp[BUFSIZ];	/* Scratch */
E 11
I 11
D 12
	char	temp[BUFSIZ];
E 11
I 8
	char	*tp;
E 12
I 12
	char	*error;
E 12
E 8
D 5
	pwptr	pwp;		/* Pointer to user information */
I 4
	extern char	PWCK_auxpwline[];
E 5
E 4

D 5
	mesg[0] = 0;
E 5
D 11
#ifdef	DEBUG
	printf("pwck_passwd: \"%s\"\n", password);
#endif
E 11
I 11
	debug(DB_PWCHECK, "pwck_passwd: \"%s\"\n", password);
E 11
D 5
	if (userid < 0)			/* Can't do user checks */
		return(PWCK_FAIL);
E 5
I 5
D 8
	strcpy(mesg, "it is part of your passwd information");
E 8
I 8
D 12
	(void) strcpy(mesg, "it is part of your passwd information");
E 8
	try(password, user->pw_name, PWCK_OBVIOUS);
			/* Checks 'name' and 'Name' */
E 5

D 5
	pwp = getpwuid(userid);
	if (pwp == (pwptr )0)
		return(PWCK_FAIL);

	strcpy(mesg, "Password is part of your passwd information");
	try(password, cname, PWCK_OBVIOUS);	/* Checks 'name' and 'Name' */

	(void) strcpy(temp, cname);
	(void) strcat(temp, cname);
E 5
I 5
	(void) strcpy(temp, user->pw_name);
	(void) strcat(temp, user->pw_name);
E 5
	try(password, temp, PWCK_OBVIOUS);	/* Check 'namename' */

D 5
	(void) strcpy(temp, cname);
E 5
I 5
	(void) strcpy(temp, user->pw_name);
E 5
D 2
	flipstring(temp);
E 2
I 2
D 3
	_flipstring(temp);
E 3
I 3
D 8
	(void) _flipstring(temp, 0);
E 3
E 2
	try(password, temp, PWCK_OBVIOUS);	/* 'eman' */
E 8
I 8
	tp = _flipstring(user->pw_name, temp);
	try(password, tp, PWCK_OBVIOUS);	/* 'eman' */

E 8
D 6

D 5
#ifdef	UTEXAS_CC
E 5
I 5
#ifdef	UT_USERINFO
E 6
E 5
	/*
D 6
	 * Try the rest of the stuff in this userinfo record
	 */
I 5
	{
	userptr	pwp;

	pwp = getuserbyuid(user->pw_uid, (userptr *)0);
	if (pwp == NULL)
		return(PWCK_FAIL);

E 5
	try(password, pwp->ui_rje_cc, PWCK_OBVIOUS);
	try(password, pwp->ui_bill_cc, PWCK_OBVIOUS);

	mesg[0] = 0;
	/* Try all 'finger' information */
	mtry(password, pwp->ui_personal_name, PWCK_FINGER);
	mtry(password, pwp->ui_nick_name, PWCK_FINGER);	
	mtry(password, pwp->ui_home_address, PWCK_FINGER);
	mtry(password, pwp->ui_work_address, PWCK_FINGER);
	mtry(password, pwp->ui_home_phone, PWCK_FINGER);
	mtry(password, pwp->ui_work_phone, PWCK_FINGER);
	mtry(password, pwp->ui_birthday, PWCK_FINGER);
	mtry(password, pwp->ui_project, PWCK_FINGER);
	mtry(password, pwp->ui_fellows, PWCK_FINGER);
#else
	/*
E 6
	 * Try every word in user's GECOS entry
	 */
D 5
	mesg[0] = 0;
	mtry(password, pwp->pw_gecos, PWCK_FINGER);
E 5
I 5
	mtry(password, user->pw_gecos, PWCK_FINGER);
E 12
I 12
	if (error = FascistGecos(password, 0, user))
		return(error);
E 12
E 5
D 6
#endif
E 6
I 4
D 5
	if (PWCK_auxpwline[0])
		mtry(password, PWCK_auxpwline, PWCK_FINGER);
E 5
E 4
	return(PWCK_OK);
}
D 5
/*	End %M% */
E 5
I 5
/* End %M% */
E 5
E 1
