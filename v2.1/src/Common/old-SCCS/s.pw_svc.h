h00000
s 00046/00002/00050
d D 1.8 98/11/17 16:08:30 clyde 8 7
c Add copyright notice
e
s 00001/00001/00051
d D 1.7 98/09/29 14:20:19 clyde 7 6
c Add third arg to init_pwsvc()
e
s 00003/00001/00049
d D 1.6 98/07/09 13:49:07 clyde 6 5
c Change structure of struct pw_svc & routine names
e
s 00002/00004/00048
d D 1.5 98/04/30 16:30:52 clyde 5 4
c 1. Add HP security mode
c 2. Remove Netinfo and Hesiod services
e
s 00002/00002/00050
d D 1.4 96/08/14 17:03:11 clyde 4 3
c Change routine name again
e
s 00005/00005/00047
d D 1.3 96/08/14 16:49:29 clyde 3 2
c Change routine name to avoid OSF name collision
e
s 00002/00002/00050
d D 1.2 96/08/09 16:19:03 clyde 2 1
c Beta 3 development checkin 2
e
s 00052/00000/00000
d D 1.1 96/08/07 09:59:57 clyde 1 0
c date and time created 96/08/07 09:59:57 by clyde
e
u
U
f e 0
t
T
I 1
/*
D 3
 *	Defines for using svc_get() module
E 3
I 3
D 8
 *	Defines for using get_svc_conf()
E 8
I 8
 * Copyright 1998, The University of Texas at Austin ("U. T. Austin").
 * All rights reserved.
E 8
E 3
 *
D 8
 *	%W% %G% (cc.utexas.edu)
E 8
I 8
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
E 8
 */
I 8

/*
 * Defines for using get_svc_conf()
 *
 * %W% %G% (cc.utexas.edu)
 */
E 8
I 3
#ifndef	pw_svc_h
#define	pw_svc_h 1
E 3

#define	N_SVC	32		/* How many services in list */

/*
 * Security level names
 */
enum svc_security {		/* System security level */
	sec_std = 0,
	sec_u4upgrade,		/* Ultrix 4 'upgrade' */
	sec_u4enhanced,		/* Ultrix 4 'enhanced' */
	sec_sunC2,		/* SunOS 4 C2 security */
D 5
	sec_OSFenhanced		/* Digital UNIX (OSF/1) enhanced */
E 5
I 5
	sec_OSFenhanced,	/* Digital UNIX (OSF/1) enhanced */
	sec_HPtrusted		/* HP/UX trusted system */
E 5
};

/*
 * Database service names
 */
enum svc_services {
	srv_local,		/* Local file */
	srv_yp,			/* NIS map */
	srv_nisplus,		/* NIS+ table */
D 5
	srv_nidot,		/* Netinfo local */
	srv_niroot,		/* Netinfo root */
E 5
	srv_kerb,		/* Kerberos */
D 5
	srv_hesiod,		/* Hesiod */
E 5
	srv_unknown,		/* Whatever's left */
	srv_last = 99		/* List end marker */
};

/*
D 3
 * Data returned by svc_info()
E 3
I 3
 * Data returned
E 3
 */
D 2
struct svcinfo {	
E 2
I 2
D 4
struct pwsvc {	
E 4
I 4
struct pw_svc {	
I 6
	int  init;				/* Initialized? */
E 6
E 4
E 2
	char *(*PasswdCrypt)();			/* Password encryptor */
	enum svc_security SecurityLevel;	/* Security level */
	enum svc_services ServiceOrder[N_SVC];	/* Passwd lookup services */
};

/*
 * Function declaration
 */
D 2
struct svcinfo svc_get _((int, char *, char *));
E 2
I 2
D 3
struct pwsvc *svc_info _((int, char **, char **, struct pwsvc *));
E 3
I 3
D 4
struct pwsvc *get_svc_conf _((int, char **, char **, struct pwsvc *));
E 4
I 4
D 6
struct pw_svc *get_pwsvc _((int, char **, char **, struct pw_svc *));
E 6
I 6
D 7
void init_pwsvc _((int, char **));
E 7
I 7
void init_pwsvc _((int, char **, char **));
E 7
struct pw_svc *get_pwsvc();
E 6
E 4
E 3
E 2

#endif
/* End %M% */
E 1
