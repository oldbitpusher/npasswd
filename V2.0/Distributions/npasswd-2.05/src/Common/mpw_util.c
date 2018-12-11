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
 * Npasswd 'meta-passwd' routines
 */

#include "npasswd.h"

#ifndef lint
static char sccsid[] = "@(#)mpw_util.c	1.6 11/17/98 (cc.utexas.edu) /usr/share/src/private/ut/share/bin/passwd/V2.0/src/Common/SCCS/s.mpw_util.c";
#endif

/*
 * copympwent - Make a copy of a meta-passwd structure
 *
 * Usage:
 *	new_mpw = copy_mpwent(struct mpassswd *original);
 * Returns:
 *	Pointer to a unique copy of <original> 
 *	Will allocate memory for copy if <new> is NULL
 */
struct mpasswd *
copympwent(donor, new)
	struct mpasswd	*donor;
	struct mpasswd	*new;
{
	if (new == 0) {
		new = calloc(sizeof(struct mpasswd), 1);
		if (new == 0)
			logdie("Cannot allocate memory to clone user\n");
	}
	*new = *donor;
	(void) copypwent(&donor->pw, &new->pw);
	new->pws_name = strdup(donor->pws_name);
	new->pws_loc = strdup(donor->pws_loc);
	return(new);
}

/*
 * printmpwent
 *	Dump contents of mpasswd structure to stdout
 */
public void
printmpwent(theUser)
	struct mpasswd *theUser;
{
#define	STRX(_Z_) (_Z_ ? _Z_ : "(null)")
	printf("mpw_name = %s\n", STRX(theUser->mpw_name));
	printf("mpw_passwd = %s\n", STRX(theUser->mpw_passwd));
	printf("mpw_uid = %u\n", theUser->mpw_uid);
	printf("mpw_gid = %u\n", theUser->mpw_gid);
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

/* End mpw_util.c */
