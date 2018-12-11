h45142
s 00047/00004/00065
d D 1.6 98/11/17 16:06:03 clyde 6 5
c Add copyright, clean up function comments
e
s 00000/00001/00069
d D 1.5 98/04/30 16:30:23 clyde 5 4
c Remove duplicate output from printmpwent
e
s 00003/00003/00067
d D 1.4 96/08/29 13:02:33 clyde 4 3
c Remove 'const' declarations (too much compiler pain)
e
s 00009/00007/00061
d D 1.3 96/08/13 18:00:22 clyde 3 2
c Add second argument to copympwent()
e
s 00002/00002/00066
d D 1.2 96/08/09 16:19:06 clyde 2 1
c Beta 3 development checkin 2
e
s 00068/00000/00000
d D 1.1 96/08/07 15:19:19 clyde 1 0
c date and time created 96/08/07 15:19:19 by clyde
e
u
U
f e 0
t
T
I 1
/*
D 6
 * npasswd module %M%
E 6
I 6
 * Copyright 1998, The University of Texas at Austin ("U. T. Austin").
 * All rights reserved.
E 6
 *
D 6
 * Compliation: cc -c %M%
 * Includes: npasswd.h
E 6
I 6
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
E 6
 */

I 6
/*
 * Npasswd 'meta-passwd' routines
 */

E 6
#include "npasswd.h"

#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu) %P%";
#endif

/*
 * copympwent - Make a copy of a meta-passwd structure
 *
 * Usage:
 *	new_mpw = copy_mpwent(struct mpassswd *original);
 * Returns:
 *	Pointer to a unique copy of <original> 
I 6
 *	Will allocate memory for copy if <new> is NULL
E 6
 */
struct mpasswd *
D 2
copympwent(donor);
E 2
I 2
D 3
copympwent(donor)
E 2
	struct mpasswd	*donor;
E 3
I 3
copympwent(donor, new)
D 4
	const struct mpasswd	*donor;
	struct mpasswd		*new;
E 4
I 4
	struct mpasswd	*donor;
	struct mpasswd	*new;
E 4
E 3
{
D 3
	struct mpasswd	*new = calloc(sizeof(struct mpasswd), 1);

	if (new == 0)
		logdie("Cannot allocate memory to clone user\n");
E 3
I 3
	if (new == 0) {
		new = calloc(sizeof(struct mpasswd), 1);
		if (new == 0)
			logdie("Cannot allocate memory to clone user\n");
	}
E 3
	*new = *donor;
	(void) copypwent(&donor->pw, &new->pw);
	new->pws_name = strdup(donor->pws_name);
	new->pws_loc = strdup(donor->pws_loc);
D 2
	return(copy);
E 2
I 2
	return(new);
E 2
}

/*
D 6
 * 	printmpwent - Dump contents of mpasswd structure
E 6
I 6
 * printmpwent
 *	Dump contents of mpasswd structure to stdout
E 6
 */
public void
printmpwent(theUser)
D 3
	struct mpasswd *theUser;
E 3
I 3
D 4
	const struct mpasswd *theUser;
E 4
I 4
	struct mpasswd *theUser;
E 4
E 3
{
#define	STRX(_Z_) (_Z_ ? _Z_ : "(null)")
	printf("mpw_name = %s\n", STRX(theUser->mpw_name));
	printf("mpw_passwd = %s\n", STRX(theUser->mpw_passwd));
	printf("mpw_uid = %u\n", theUser->mpw_uid);
	printf("mpw_gid = %u\n", theUser->mpw_gid);
D 5
	printf("mpw_shell = %s\n", STRX(theUser->mpw_shell));
E 5
	printf("mpw_gecos = %s\n", STRX(theUser->mpw_gecos));
	printf("mpw_shell = %s\n", STRX(theUser->mpw_shell));
	printf("mpw_dir = %s\n", STRX(theUser->mpw_dir));
#ifdef	PWAGE
	printf("mpw_age = %s\n", STRX(theUser->mpw_age));
#endif
	printf("last_change = %u\n", theUser->pwage.last_change);
	printf("min_time = %u\n", theUser->pwage.can_change);
	printf("max_time = %u\n", theUser->pwage.must_change);
	printf("key = %s\n", STRX(theUser->key));
	printf("password = %s\n", STRX(theUser->password));
	printf("where = %s\n", STRX(theUser->pws_loc));
	printf("what = %s\n", STRX(theUser->pws_name));
	printf("remote = %u\n", theUser->pws_remote);
	printf("opaque = %x\n", theUser->opaque);
#undef	STRZ
}

/* End %M% */
E 1
