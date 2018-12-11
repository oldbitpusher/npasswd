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
 * pwck_local - Perform 'local' password checks.
 *
 * Usage
 *	error = pwck_local(char *, struct passwd *);
 *
 * Return
 *	PWCK_OBVIOUS if password flunks
 * 	PWCK_OK if password ok
 */
#ifndef lint
static char sccsid[] = "@(#)pwck_local.c	1.10 04/07/98 (cc.utexas.edu)";
#endif

#include "pwck_defines.h"
#include <sys/socket.h>
#include <sys/param.h>
#include <netdb.h>

public char *
pwck_local(password, user)
	char	*password;	/* Password to check */
	struct passwd *user;	/* Passwd info for user */
{
	char	myname[MAXHOSTNAMLEN],
		temp[MAXPATHLEN];
	struct hostent	*h;
	FILE	*rh;

	debug(DB_PWCHECK, "pwck_local: \"%s\"\n", password);

	(void) gethostname(myname, sizeof myname);
	if (GTry(myname, password))
		return(PWCK_OBVIOUS);

	/*
	 * Check against the full hostname and aliases
	 */
	if (h = gethostbyname(myname)) {
		char	**hh;

		if (GTry(h->h_name, password))
			return(PWCK_OBVIOUS);
		for (hh = h->h_aliases; *hh; hh++) {
			if (GTry(*hh, password))
				return(PWCK_OBVIOUS);
		}
	}

	/*
	 * Check if password is a hostname
	 */
	if (h = gethostbyname(password)) {
		return(PWCK_OBVIOUS);
	}

	/*
	 * Check against the users' .rhosts file
	 */
	(void) sprintf(temp, "%s/.rhosts", user->pw_dir);
	if (rh = fopen(temp, "r")) {
		while (fgets(temp, sizeof(temp), rh)) {
			if (GTry(temp, password)) {
				(void) fclose(rh);
				return(PWCK_OBVIOUS);
			}
		}
		(void) fclose(rh);
	}

	/*
	 * Check against the roots /.rhosts file
	 */
	if (rh = fopen("/.rhosts", "r")) {
		while (fgets(temp, sizeof(temp), rh)) {
			if (GTry(temp, password)) {
				(void) fclose(rh);
				return(PWCK_OBVIOUS);
			}
		}
		(void) fclose(rh);
	}
	return(PWCK_OK);
}
/* End pwck_local.c */
