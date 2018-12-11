h42879
s 00063/00013/00041
d D 1.10 98/04/07 09:53:38 clyde 10 9
c 1. Add UT copyright notice
c 2. Use Cracklib/GTry for testing
c 3. Change return type to (char *)
e
s 00002/00002/00052
d D 1.9 98/03/26 11:08:41 clyde 9 8
c 1. Cosmetic changes
c 2. Use 'mtry' instead of 'try'
e
s 00002/00002/00052
d D 1.8 96/08/29 12:59:33 clyde 8 7
c Remove 'const' declarations (too much compiler trouble)
e
s 00002/00002/00052
d D 1.7 96/08/13 13:05:32 clyde 7 6
c Add const where useful
e
s 00002/00004/00052
d D 1.6 96/08/06 14:13:53 clyde 6 5
c beta 3 cycle 1 checkin
e
s 00000/00000/00056
d D 1.5 95/04/05 16:20:01 clyde 5 4
c Beta 3 development checkin
e
s 00003/00006/00053
d D 1.4 94/03/15 18:52:55 clyde 4 3
c Use new include files
e
s 00005/00001/00054
d D 1.3 94/01/06 14:43:25 clyde 3 2
c Use MAXHOSTNAMLEN for hostname buffer
e
s 00038/00014/00017
d D 1.2 94/01/05 15:48:21 clyde 2 1
c Check against aliases for host, users .rhosts file
e
s 00031/00000/00000
d D 1.1 89/05/18 10:05:54 clyde 1 0
c date and time created 89/05/18 10:05:54 by clyde
e
u
U
t
T
I 1
/*
D 10
 *	pwck_local - Perform 'local' password checks.
E 10
I 10
 * Copyright 1998, The University of Texas at Austin ("U. T. Austin").
 * All rights reserved.
E 10
 *
D 2
 *	Returns:
 *		PWCK_OBVIOUS if <password> == hostname
 *		PWCK_OK if otherwise
E 2
I 2
D 10
 *	Returns PWCK_OBVIOUS if password flunks, else PWCK_OK
E 10
I 10
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
E 10
E 2
 */
I 10
/*
 * pwck_local - Perform 'local' password checks.
 *
 * Usage
 *	error = pwck_local(char *, struct passwd *);
 *
 * Return
 *	PWCK_OBVIOUS if password flunks
 * 	PWCK_OK if password ok
 */
E 10
#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu)";
#endif

D 2
#include "checkpasswd.h"
E 2
I 2
D 4
#include "compat.h"
#include "lib.h"
E 4
I 4
D 6
#include "compatibility.h"
E 4
#include "checkpassword.h"
I 4
#include "pwck_lib.h"
E 6
I 6
#include "pwck_defines.h"
E 6
E 4
#include <sys/socket.h>
#include <sys/param.h>
#include <netdb.h>
E 2

I 3
D 4
#ifndef MAXHOSTNAMLEN
# define MAXHOSTNAMLEN 64
#endif

E 4
I 4
D 10
public int
E 4
E 3
D 2
pwck_local(password, userid, mesg)
char	*password;	/* Password to check */
int	userid;		/* NOTUSED */
char	*mesg;		/* Message buffer */
E 2
I 2
pwck_local(password, user, mesg)
E 10
I 10
public char *
pwck_local(password, user)
E 10
D 7
	char	*password;	/* Password to check */
	struct passwd *user;	/* Passwd info for user */ /* NOTUSED */
E 7
I 7
D 8
	const char	*password;	/* Password to check */
	const struct passwd *user;	/* Passwd info for user */ /* NOTUSED */
E 8
I 8
	char	*password;	/* Password to check */
D 9
	struct passwd *user;	/* Passwd info for user */ /* NOTUSED */
E 9
I 9
	struct passwd *user;	/* Passwd info for user */
E 9
E 8
E 7
D 10
	char	*mesg;		/* Message buffer */
E 10
E 2
{
D 2
	char	myname[32];		/* Scratch */
E 2
I 2
D 10
	FILE	*rh;
D 3
	char	myname[64],		/* Scratch */
E 3
I 3
	char	myname[MAXHOSTNAMLEN],		/* Scratch */
E 3
		temp[MAXPATHLEN];	/* Scratch */
E 10
I 10
	char	myname[MAXHOSTNAMLEN],
		temp[MAXPATHLEN];
E 10
	struct hostent	*h;
I 10
	FILE	*rh;
E 10
E 2

D 10
	(void) gethostname(myname, sizeof(myname));
	try(password, myname, PWCK_OBVIOUS);
E 10
I 10
	(void) gethostname(myname, sizeof myname);
	if (GTry(myname, password))
		return(PWCK_OBVIOUS);
E 10
	/*
D 2
	 * Could try full canoncalized hostname here in case gethostname
	 * didn't get that for us.
	 *
	 * Then look in users' .rhosts and try those strings (maybe)
E 2
I 2
	 * Check against the full hostname and aliases
E 2
	 */
I 2
	if (h = gethostbyname(myname)) {
		char	**hh;

D 10
		try(password, h->h_name, PWCK_OBVIOUS);
E 10
I 10
		if (GTry(h->h_name, password))
			return(PWCK_OBVIOUS);
E 10
		for (hh = h->h_aliases; *hh; hh++) {
D 9
			try(password, *hh, PWCK_OBVIOUS);
E 9
I 9
D 10
			mtry(password, *hh, PWCK_OBVIOUS);
E 10
I 10
			if (GTry(*hh, password))
				return(PWCK_OBVIOUS);
E 10
E 9
		}
	}
	/*
	 * Check against the users' .rhosts file
	 */
	(void) sprintf(temp, "%s/.rhosts", user->pw_dir);
	if (rh = fopen(temp, "r")) {
		while (fgets(temp, sizeof(temp), rh)) {
D 6
			if (_instring(password, temp, PWCK_OBVIOUS) == PWCK_OBVIOUS) {
E 6
I 6
D 10
			if (instring(password, temp)) {
E 10
I 10
			if (GTry(temp, password)) {
E 10
E 6
				(void) fclose(rh);
				return(PWCK_OBVIOUS);
			}
		}
		(void) fclose(rh);
	}
E 2
	return(PWCK_OK);
}
D 2
/*	End %M% */
E 2
I 2
/* End %M% */
E 2
E 1
