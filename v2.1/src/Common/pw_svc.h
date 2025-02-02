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
 * Defines for using get_svc_conf()
 *
 * $Id: pw_svc.h,v 1.8 1998/11/17 00:00:00 clyde Exp $ (cc.utexas.edu)
 */
#ifndef	pw_svc_h
#define	pw_svc_h 1

#define	N_SVC	32		/* How many services in list */

/*
 * Security level names
 */
enum svc_security {		/* System security level */
	sec_std = 0,
	sec_u4upgrade,		/* Ultrix 4 'upgrade' */
	sec_u4enhanced,		/* Ultrix 4 'enhanced' */
	sec_sunC2,		/* SunOS 4 C2 security */
	sec_OSFenhanced,	/* Digital UNIX (OSF/1) enhanced */
	sec_HPtrusted		/* HP/UX trusted system */
};

/*
 * Database service names
 */
enum svc_services {
	srv_local,		/* Local file */
	srv_yp,			/* NIS map */
	srv_nisplus,		/* NIS+ table */
	srv_kerb,		/* Kerberos */
	srv_unknown,		/* Whatever's left */
	srv_last = 99		/* List end marker */
};

/*
 * Data returned
 */
struct pw_svc {	
	int  init;				/* Initialized? */
	char *(*PasswdCrypt)();			/* Password encryptor */
	enum svc_security SecurityLevel;	/* Security level */
	enum svc_services ServiceOrder[N_SVC];	/* Passwd lookup services */
};

/*
 * Function declaration
 */
void init_pwsvc _((int, char **, char **));
struct pw_svc *get_pwsvc();

#endif
/* End $RCSfile: pw_svc.h,v $ */
