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

#include "pwck_defines.h"
#include "options.h"
#include "pwck_history.h"

#ifndef lint
static char utid[] = "@(#)hist_osf.c	1.2 06/30/98 (cc.utexas.edu)";
#endif

/*
 * hist_osf.c - Password history method for OSF/1 and HP-UX enhanced security
 */

#ifdef	OSF1_AUTH	/* And maybe HPUX_AUTH also */
/*
 * osf_history_check
 *	Check OSF/1 password history database
 * Usage:
 *	return-code = osf_history_check(char *password,
 *			struct passwd *user, char *mesg);
 * Returns:
 *	Message if <password> was found in history list
 *	0 if not
 */
public char *
osf_history_check(password, user)
	char	*password;		/* Password to check (plaintext) */
	struct passwd	*user;		/* Who to check for */
{
	struct pr_passwd *pw;

	if (access(OSF1_TCB, 0) < 0)	/* AuthDB not in use */
		return(PWCK_OK);

	if ((pw = getprpwnam(user->pw_name)) != NULL &&
	     pw->uflg.fg_pwdict && pw->ufld.fd_pwdict[0]) {
		char **ts, **tl;

		for (ts = tl = split(pw->ufld.fd_pwdict, FIELD_SEP, 0,0);
		     *ts; ts++) {
			char	*xc;

			xc = crypt(password, *ts);
			if (strlen(*ts) > strlen(xc))
				xc = bigcrypt(password, ts);
			if (strcmp(xc, *ts) == 0) {
				free((char *)tl);
				return(PWCK_REUSE);
			}
		}
		free((char *)tl);
	}
	return(PWCK_OK);
}

/*
 * osf_history_update -	Update OSF/1 password history
 *
 * If user has auth database entry, password history has already been
 * modfied by the OSF/1 shadow support module.
 */
public int
osf_history_update(user, password)
	struct passwd	*user;		/* Who to check for */
	char	*password;		/* Password to check (plaintext) */
{
	struct pr_passwd *pw;

	if (access(OSF1_TCB, 0) < 0)		/* AuthDB not in use */
		return(0);
	if (getprpwnam(user->pw_name) == 0)	/* No auth for user */
		return(0);
	/*
	 * User has auth database entry - password history has already been
	 * modfied by the OSF/1 shadow support module.
	 */
	return(1);
}
#endif	/* OSF1_AUTH */
/* End hist_osf.c */
