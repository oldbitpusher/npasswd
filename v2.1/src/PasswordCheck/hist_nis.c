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
static char utid[] = "@(#)hist_nis.c	1.1 06/04/98 (cc.utexas.edu)";
#endif

/*
 * hist_nis.c - Password history database method 'NIS' (not fully implimented)
 */

#ifdef	USE_NIS_UNSUPPORTED
/*
 * Support for storing password history in a NIS map
 *
 * This somewhat duplicates code in the NIS method module.
 */
#define PORTMAP
#include <ndbm.h>
#include <netdb.h>
#include <sys/socket.h>
#include <rpc/rpc.h>
#include <rpcsvc/yppasswd.h>
#include <rpcsvc/ypclnt.h>
#define DATUM                   /* Prevent error in next include */
#include <rpcsvc/yp_prot.h>
#undef  DATUM

/*
 * pwh_put_nis
 *	Add password to history file.
 * Usage:
 *	pwh_put_nis(char *name,  char *crypt_passwd)
 */
public char
*pwh_get_nis(who)
	char	*who;
{
	char	*domain,
		*master,
		*data;
	int	dlen;

	if (yp_get_default_domain(&domain)) {
		debug(DB_PWCHECK, "NIS domain not set\n");
                return(0);
	}

	if (yp_master(domain, PasswordHistoryDB, &master)) {
		debug(DB_PWCHECK, "NIS map %s not found\n", PasswordHistoryDB);
                return(0);
	}
	if (yp_match(domain, PasswordHistoryDB, who, strlen(who), &data, &dlen)) {
		debug(DB_PWCHECK, "No history found for %s\n", who);
                return(0);
	}
	return(data);
}

/*
 * pwh_put_nis
 *	Add password to NIS history map
 * Usage:
 *	pwh_put_nis(char *name,  char *crypt_passwd)
 */
public int
pwh_put_nis(name, cryptedpassword)
	char	*name,			/* User name */
		*cryptedpassword;	/* Encrypted password */
{
	char	*domain,
		*master,
		*data;
	int	dlen,
		rc;
	time_t	now = time((time_t *)0);
	char	temp[YPMAXRECORD];

	if (yp_get_default_domain(&domain)) {
		debug(DB_UPDATE, "NIS domain not set\n");
                return;		/* Not a fatal error */
	}

	if (yp_master(domain, PasswordHistoryDB, &master)) {
		debug(DB_UPDATE, "NIS map %s not found\n", PasswordHistoryDB);
                return;		/* Not a fatal error */
	}
	(void) sprintf(temp, "%s:%s,%u", name, cryptedpassword, now);

	/* Get existing password history */
	rc = yp_match(domain, PasswordHistoryDB, name, strlen(name), &data, &dlen);
	if (rc == 0) {		/* Append new item to entry */
		char	**v;
		int	count;

		v = (char **)split(data, ENTRY_SEP, 0, 0, 0);
		/*
		 * Skip v[0] (user name)
		 */
		for (count = 1; v[count]; count++) {
			if (PasswordHistoryDepth && count > PasswordHistoryDepth)
				break;
			if ((strlen(temp) + strlen(v[count]) + 2) > YPMAXRECORD)
				break;
			(void) strcat(temp, ":");
			(void) strcat(temp, v[count]);
		}
	} else {
		if (rc != YPERR_KEY) {
			logerr("pwh_put_nis: lookup error %d\n", rc);
		}
	}
	debug(DB_UPDATE, "pwh_put_nis: put '%s'\n", temp);

#ifdef	SECURE_RPC
	rc = yp_update(domain, PasswordHistoryDB, YPOP_STORE,
		name, strlen(name), temp, strlen(temp));
	if (rc) {
		logerr("pwh_put_nis: store failed- map '%s' error %d\n",
			PasswordHistoryDB, rc);
		warn("Could not store password in NIS history database.\n");
	}
#endif
}

#else	/* USE_NIS_UNSUPPORTED */

public char *
pwh_get_nis(who)
	char	*who;
{
	return(NULL);
}

public int
pwh_put_nis(name, cryptedpassword)
	char	*name;
	char	*cryptedpassword;
{
	return(-1);
}

#endif	/* USE_NIS_UNSUPPORTED */
/* End hist_nis.c */
