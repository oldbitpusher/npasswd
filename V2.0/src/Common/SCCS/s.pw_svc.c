h19921
s 00001/00001/00379
d D 1.15 99/07/26 12:44:57 clyde 15 14
c Fix typo in HPUX security code
e
s 00050/00006/00330
d D 1.14 98/11/17 16:49:07 clyde 14 13
c 1. Add copyright notice
c 2. Reformat function comments
e
s 00055/00013/00281
d D 1.13 98/09/29 14:20:52 clyde 13 12
c 1. Add command line switch vector arg to init_pwsvc()
c 2. Impliment -r option for SunOS 5
e
s 00002/00000/00292
d D 1.12 98/09/23 14:24:56 clyde 12 11
c Add  _svcinfo.init = 1 in more places
e
s 00031/00036/00261
d D 1.11 98/07/09 14:15:13 clyde 11 10
c 1. Change get_pwsvc() to init_pwsvc(), eliminate some args
c 2. Add new get_pwsvc()
e
s 00012/00009/00285
d D 1.10 98/04/30 16:32:54 clyde 10 9
c 1. Move crypt16() and bigcrypt() decls
c 2. Add HP-UX support
c 3. Little cleanup
e
s 00004/00000/00290
d D 1.9 97/09/19 10:58:07 clyde 9 8
c Establish a default service order for "passwd_compat" on Solaris 2
e
s 00009/00007/00281
d D 1.8 97/05/23 12:56:25 clyde 8 7
c Fix NIS+ service order lookup
e
s 00006/00006/00282
d D 1.7 96/08/14 17:59:16 clyde 7 6
c More structure name changes
e
s 00035/00026/00253
d D 1.6 96/08/14 17:02:26 clyde 6 5
c Rename routines
e
s 00002/00011/00277
d D 1.5 96/08/13 18:00:03 clyde 5 4
c Fix memory allocation bug
e
s 00035/00013/00253
d D 1.4 96/08/09 16:19:01 clyde 4 3
c Beta 3 development checkin 2
e
s 00046/00034/00220
d D 1.3 96/08/07 15:20:27 clyde 3 2
c Beta 3 devlopment checkin
e
s 00032/00021/00222
d D 1.2 96/08/06 14:48:44 clyde 2 1
c beta 3 development checkin
e
s 00243/00000/00000
d D 1.1 96/04/01 16:15:12 clyde 1 0
c date and time created 96/04/01 16:15:12 by clyde
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
D 14
 * %M%
 *	Routines to fetch the "service order" list for "passwd".
D 11
 *	There is a "get_pwsvc()" routine for each service
E 11
I 11
 *	There is a "init_pwsvc()" routine for each service
E 11
 *	variant (nsswitch, svc.conf, etc).
E 14
I 14
 * Copyright 1998, The University of Texas at Austin ("U. T. Austin").
 * All rights reserved.
E 14
E 6
 *
D 6
 * This module contains routines to fetch the "service order" list
 * for this system.  There is a "svc_get()"  routine for each service
 * variant (nsswitch, svc.conf, etc).
 *
 * Compilation: cc -c %M%
D 3
 * Includes:		npasswd.h
E 3
 *
E 6
I 6
D 14
 * Exported routines
E 14
I 14
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
 * Routines to fetch the "service order" list for "passwd".
 * There is a "init_pwsvc()" routine for each service
 * variant (nsswitch, svc.conf, etc).
 *
 * Exported routines:
E 14
I 11
 *	init_pwsvc()
E 11
 *	get_pwsvc()
E 6
 */
I 14

E 14
D 3

#include "npasswd.h"

E 3
#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu) %P%";
#endif

I 3
D 13
#include "defines.h"
#include "constants.h"
#include "compatibility.h"
E 13
I 13
#include "npasswd.h"
E 13
D 6
#include "svc_info.h"
E 6
I 6
#include "pw_svc.h"
E 6

E 3
I 2
D 6
extern char	*crypt();
E 6
I 6
extern char	*crypt();	/* Standard encryptor */
E 6
I 4
D 10
#ifdef	ULTRIX_AUTH
D 6
extern char 	*crypt16();
E 6
I 6
extern char 	*crypt16();	/* Extended encryptor */
E 6
#endif
#ifdef	OSF1_AUTH
D 6
extern char 	*bigcrypt();
E 6
I 6
extern char 	*crypt16();	/* Extended encryptor */
extern char 	*bigcrypt();	/* Really extended encryptor */
E 6
#endif
E 10
E 4
D 3
public char	(*svc_PasswdCrypt)() = crypt;	/* Password encryptor */
public enum sec_order svc_SecurityLevel;	/* OS security level */
public enum svc_order svc_ServiceOrder[32] = {	/* Passwd lookup services */
E 3
I 3

D 4
static struct svcinfo _svcinfo = { 
E 4
I 4
D 6
static struct pwsvc _svcinfo = { 
E 6
I 6
static struct pw_svc _svcinfo = { 
I 11
	0,			/* Not initialized */
E 11
E 6
E 4
	crypt,			/* Password encryptor */
	sec_std,		/* System security level */
	{ 			/* Passwd lookup services */
E 3
#ifdef  USE_NIS
D 3
	srv_local, srv_yp, srv_last
E 3
I 3
		srv_local, srv_yp, srv_last
E 3
#else
D 3
	srv_local, srv_last
E 3
I 3
		srv_local, srv_last
E 3
#endif
I 3
D 4
	{
E 4
I 4
	}
E 4
E 3
};

E 2
D 6
#ifdef	HAS_SVC_CONF		/* Ultrix and Digital UNIX (OSF/1) */
E 6
I 6
#ifdef	HAS_SVCCONF		/* Ultrix and Digital UNIX (OSF/1) */
E 6
#define	_SETUP	1		/* A setup method has been selected */
/*
D 6
 * svc_get - Process the service configuration for Ultrix 4.X and OSF/1
E 6
I 6
D 11
 * get_pwsvc (Ultrix/OSF1)
E 11
I 11
 * init_pwsvc (Ultrix/OSF1)
E 11
 *	Get service order for Digital UNIX (using /etc/svc.conf)
 * Usage
D 11
 *	svcblk = get_pwsvc(int argc, char **argv,
 *		char **envp, struct pwsvc *return);
E 11
I 11
D 13
 *	init_pwsvc(int argc, char **argv);
E 13
I 13
 *	init_pwsvc(int argc, char **argv, char **);
E 13
E 11
 * Error exits
 *	Error return from getsvc()
E 6
 */
#include <sys/svcinfo.h>

D 3
public void
svc_get(argc, argv, envp)
E 3
I 3
D 7
public struct svcinfo
E 7
I 7
D 11
public struct pw_svc
E 7
D 4
svc_info(argc, argv, envp)
E 4
I 4
D 6
svc_info(argc, argv, envp, svp)
E 4
E 3
	int	argc;
	char	**argv;
	char	**envp;	/*NOTUSED*/
I 4
	struct pwsvc	*svp;
E 6
I 6
get_pwsvc(argc, argv, envp, svp)
E 11
I 11
void
D 13
init_pwsvc(argc, argv)
E 13
I 13
init_pwsvc(argc, argv, cmdsw)
E 13
E 11
	int	argc;			/* Used in OSF/1 */
	char	**argv;			/* Used in OSF/1 */
I 13
	char	**cmdsw;		/* NOTUSED*/
E 13
D 11
	char	**envp;			/*NOTUSED*/
D 7
	struct pwsvc	*svp;		/* Return value (if present */
E 7
I 7
	struct pw_svc	*svp;		/* Return value (if present */
E 11
E 7
E 6
E 4
{
I 10
	extern char 	*crypt16();	/* Extended encryptor */
#ifdef	OSF1_AUTH
	extern char 	*bigcrypt();	/* Really extended encryptor */
#endif
E 10
	struct svcinfo	*svc;	/* Service info */
	int	i,		/* Temp */
		j,		/* Temp */
		s;		/* Temp */

D 2
	SecurityLevel = sec_std;
E 2
I 2
D 3
	svc_SecurityLevel = sec_std;
E 3
I 3
	_svcinfo.SecurityLevel = sec_std;
	_svcinfo.PasswdCrypt = crypt;
E 3
E 2

	if ((svc = getsvc()) == 0)
		logdie("Cannot get service configuration.\n");

D 3
	debug(DB_LOOKUP, "svc_get (svc.conf): "):
E 3
I 3
D 6
	debug(DB_LOOKUP, "svc_info (svc.conf): "):
E 6
I 6
D 11
	debug(DB_LOOKUP, "get_pwsvc (svc.conf): "):
E 11
I 11
	debug(DB_LOOKUP, "init_pwsvc (svc.conf): "):
E 11
E 6
E 3
	for (s = i = 0; (j = svc->svcpath[SVC_PASSWD][i]) != SVC_LAST; i++) {
		switch(j) {
		case SVC_LOCAL:
D 2
			ServiceOrder[s++] = srv_local;
E 2
I 2
D 3
			svc_ServiceOrder[s++] = srv_local;
E 3
I 3
			_svcinfo.ServiceOrder[s++] = srv_local;
E 3
E 2
			debug(DB_LOOKUP, "local "):
			break;
		case SVC_YP:
D 2
			ServiceOrder[s++] = srv_yp;
E 2
I 2
D 3
			svc_ServiceOrder[s++] = srv_yp;
E 3
I 3
			_svcinfo.ServiceOrder[s++] = srv_yp;
E 3
E 2
			debug(DB_LOOKUP, "nis "):
			break;
		case SVC_BIND:
D 2
			ServiceOrder[s++] = srv_hesiod;
E 2
I 2
D 3
			svc_ServiceOrder[s++] = srv_hesiod;
E 3
I 3
			_svcinfo.ServiceOrder[s++] = srv_hesiod;
E 3
E 2
			debug(DB_LOOKUP, "bind "):
			break;
		}
	}
D 2
	ServiceOrder[s++] = srv_last;
E 2
I 2
D 3
	svc_ServiceOrder[s++] = srv_last;
E 3
I 3
	_svcinfo.ServiceOrder[s++] = srv_last;
E 3
E 2

	switch (svc->svcauth.seclevel) {
	case SEC_BSD:
D 2
		SecurityLevel = sec_std;
E 2
I 2
D 3
		svc_SecurityLevel = sec_std;
E 3
I 3
		_svcinfo.SecurityLevel = sec_std;
E 3
E 2
		debug(DB_LOOKUP, "(security_std) "):
		break;
	case SEC_UPGRADE:
D 2
		SecurityLevel = sec_u4upgrade;
E 2
I 2
D 3
		svc_SecurityLevel = sec_u4upgrade;
E 3
I 3
		_svcinfo.SecurityLevel = sec_u4upgrade;
E 3
E 2
		debug(DB_LOOKUP, "(security_upgrade) "):
		break;
	case SEC_ENHANCED:
D 2
		SecurityLevel = sec_u4enhanced;
E 2
I 2
D 3
		svc_SecurityLevel = sec_u4enhanced;
E 3
I 3
		_svcinfo.SecurityLevel = sec_u4enhanced;
E 3
E 2
		debug(DB_LOOKUP, "(security_enhanced) "):
#ifdef	ULTRIX_AUTH
D 3
		PasswdCrypt = crypt16;
E 3
I 3
		_svcinfo.PasswdCrypt = crypt16;
E 3
#endif
		break;
	}
#ifdef	OSF1_AUTH
	/*
	 * If there is a Trusted Computing Base directory, then
	 * we are running enhanced security.
	 * On OSF/1, the "security level" returned by getsvc() is wrong.
	 */
	if (access(OSF1_TCB, 0) == 0) {
		SIAENTITY *who;

		if (sia_ses_init(&who, argc, argv, NULL, NULL, NULL, 0, NULL)
			== SIASUCCESS) {
D 2
				SecurityLevel = sec_OSFenhanced;
E 2
I 2
D 3
				svc_SecurityLevel = sec_OSFenhanced;
E 2
				PasswdCrypt = bigcrypt;
E 3
I 3
				_svcinfo.SecurityLevel = sec_OSFenhanced;
				_svcinfo.PasswdCrypt = bigcrypt;
E 3
				debug(DB_LOOKUP, "(security_C2) "):
		}
	}
#endif
	debug(DB_LOOKUP, "\n"):
I 4
D 11
	if (svp) {
		*svp = _svcinfo;
		return(svp);
	}
E 4
I 3
	return(&_svcinfo);
E 11
I 11
	_svcinfo.init = 1;
E 11
E 3
}
#endif	/* HAS_GETSVC_CONF */


D 13
#ifdef	HAS_NSSWITCH
E 13
I 13
#if	defined(HAS_NSSWITCH) && defined(OS_SUNOS_5)
E 13
#define	_SETUP	1
/*
D 6
 * svc_get - Process the 'name service' configuration of Solaris 2
E 6
I 6
 * get_nsswitch
 *	Process the Solaris 2 name service switch 
 * Usage
 *	service_list = get_nsswitch(char *database-name);
E 6
 */
I 4
D 6
#undef	private
E 6
I 6
#undef	private			/* Avoid use of 'private' in includes below */
E 6
E 4
#include <nsswitch.h>
I 2
#include <nss_dbdefs.h>
E 2

D 4
private char **
E 4
I 4
static char **
E 4
get_nsswitch(what)
	char	*what;
{
	struct __nsw_switchconfig *config;
	struct __nsw_lookup     *p;
	enum __nsw_parse_err    error;
D 3
	char	*srvlist[32];	/* LIMIT */
E 3
I 3
D 5
	char	*srvlist[N_SVC];
E 3
	char	**rv;
E 5
I 5
	static char	*srvlist[N_SVC];
E 5
	int	svcno = 0;

	config = __nsw_getconfig(what, &error);
	switch (error) {
#if	(OS_MINOR_VERSION >= 3)
	case __NSW_CONF_PARSE_SUCCESS:
#else
	case __NSW_PARSE_SUCCESS:
#endif
		break;
#if	(OS_MINOR_VERSION >= 3)
	case __NSW_CONF_PARSE_NOFILE:
#else
	case __NSW_PARSE_NOFILE:
#endif
D 6
		printf("Warning: \"%s\" not found.\n", __NSW_CONFIG_FILE);
E 6
I 6
		warn("Warning: \"%s\" not found.\n", __NSW_CONFIG_FILE);
E 6
D 4
		return;
E 4
I 4
		return(0);
E 4
#if	(OS_MINOR_VERSION >= 3)
	case __NSW_CONF_PARSE_NOPOLICY:
#else
	case __NSW_PARSE_NOPOLICY:
#endif
D 4
		return;
E 4
I 4
		return(0);
E 4
#if	(OS_MINOR_VERSION >= 3)
	case __NSW_CONF_PARSE_SYSERR:
#else
	case __NSW_PARSE_SYSERR:
#endif
D 6
		printf("Warning: Syntax error in \"%s\".\n", __NSW_CONFIG_FILE);
E 6
I 6
		warn("Warning: Syntax error in \"%s\".\n", __NSW_CONFIG_FILE);
E 6
D 4
		return;
E 4
I 4
		return(0);
E 4
	}
	for (p = config->lookups; p; p = p->next) {
D 4
		srvlist[svcno++] = copystr(p->service_name);
E 4
I 4
		srvlist[svcno++] = strdup(p->service_name);
E 4
	}
	srvlist[svcno] = 0;
D 5
	rv = (char **)calloc(sizeof(char *), svcno);
	if (rv == 0)
		logdie("Cannot allocate memory for service list\n");
I 3
#ifdef	HAS_MEMCPY
	memcpy((void *)rv, (void *)&srvlist, (svcno * sizeof(char *)));
#else
E 3
	bcopy((void *)&srvlist, (void *)rv, (svcno * sizeof(char *)));
I 3
#endif
E 3
	return(rv);
E 5
I 5
	return(srvlist);
E 5
}

D 3
public void
svc_get(argc, argv, envp)
E 3
I 3
D 4
public struct svcinfo *
svc_info(argc, argv, envp)
E 4
I 4
D 7
public struct pwsvc *
E 7
I 7
D 11
public struct pw_svc *
E 7
D 6
svc_info(argc, argv, envp, svp)
E 6
I 6
get_pwsvc(argc, argv, envp, svp)
E 11
I 11
void
D 13
init_pwsvc(argc, argv)
E 11
E 6
E 4
E 3
	int	argc;	/*NOTUSED*/
	char	**argv;	/*NOTUSED*/
E 13
I 13
init_pwsvc(argc, argv, cmdsw)
	int	argc;		/*NOTUSED*/
	char	**argv;		/*NOTUSED*/
	char	**cmdsw;	/* Command line switches */
E 13
D 11
	char	**envp;	/*NOTUSED*/
I 4
D 7
	struct pwsvc	*svp;
E 7
I 7
	struct pw_svc	*svp;
E 11
E 7
E 4
{
I 13
/*
 *	Having a list of defines for service names is not really the
 *	right way to go, but since source changes are needed to add
 *	a method module, forcing changes here also is not the most
 *	terrible thing.
 */
E 13
#define	SV_NIS		"nis"
#define	SV_NISPLUS	"nisplus"
#define	SV_COMPAT	"compat"
#define	SV_FILES	"files"
D 2
#define	SV_PWCOMPAT	"passwd_compat"
E 2
D 13

E 13
	int	svo = 0;
	char	**svlist;

D 2
	SecurityLevel = sec_std;
E 2
I 2
D 3
	svc_SecurityLevel = sec_std;
E 3
I 3
	_svcinfo.SecurityLevel = sec_std;
E 3
E 2
D 10
	debug(DB_LOOKUP, "svc_get nsswitch: ");
E 10
I 10
D 11
	debug(DB_LOOKUP, "get_pwsvc nsswitch: ");
E 11
I 11
	debug(DB_LOOKUP, "init_pwsvc nsswitch: ");
E 11
E 10

	/*
	 * TODO: Figure out what security level needed for RPC 
	 * i.e. might a key need resetting.
	 */
I 13

	/*
	 * The -r command line option short-circuits nsswitch.conf processing
	 */
	if (cmdsw && cmdsw['r']) {
		if (strcmp(cmdsw['r'], SV_FILES) == 0) {
			_svcinfo.ServiceOrder[svo++] = srv_local;
			debug(DB_LOOKUP, "-r local ");
		}
		if (strcmp(cmdsw['r'], SV_NIS) == 0) {
#ifdef	USE_NIS
			_svcinfo.ServiceOrder[svo++] = srv_yp;
			debug(DB_LOOKUP, "-r nis ");
#else
			die("NIS support not enabled\n");
			/*NOTREACHED*/
#endif
		}
		if (strcmp(cmdsw['r'], SV_NISPLUS) == 0) {
#ifdef	USE_NISPLUS_NOPE
			_svcinfo.ServiceOrder[svo++] = srv_nis;
			debug(DB_LOOKUP, "-r nisplus ");
#else
			die("NIS+ not supported\n");
			/*NOTREACHED*/
#endif
		}
		if (svo) {
			_svcinfo.ServiceOrder[svo] = srv_last;
			_svcinfo.init = 1;
			debug(DB_LOOKUP, "\n");
			return;
		}
		die("Unknown service selector '%s'\n", cmdsw['r']);
		/*NOTREACHED*/
	}
E 13
D 2
	for (svlist = get_nsswitch(__NSW_PASSWD_DB); *svlist; *svlist++) {
E 2
I 2
	for (svlist = get_nsswitch(NSS_DBNAM_PASSWD); *svlist; *svlist++) {
E 2
		if (strcmp(*svlist, SV_FILES) == 0) {
D 2
			ServiceOrder[svo++] = srv_local;
E 2
I 2
D 3
			svc_ServiceOrder[svo++] = srv_local;
E 3
I 3
			_svcinfo.ServiceOrder[svo++] = srv_local;
E 3
E 2
			debug(DB_LOOKUP, "local ");
		}
#if	defined(USE_NIS) || defined(USE_NISPLUS)
		if (strcmp(*svlist, SV_NIS) == 0) {
D 2
			ServiceOrder[svo++] = srv_yp;
E 2
I 2
D 3
			svc_ServiceOrder[svo++] = srv_yp;
E 3
I 3
			_svcinfo.ServiceOrder[svo++] = srv_yp;
E 3
E 2
			debug(DB_LOOKUP, "nis ");
		}
D 2
		if (strcmp(*svlist, SV_COMPAT) == 0) {
			char	**pwsv = get_nsswitch(SV_PWCOMPAT);
E 2
I 2
D 8
		if (strcmp(*svlist, NSS_DBNAM_PASSWD_COMPAT) == 0) {
E 8
I 8
		if (strcmp(*svlist, SV_COMPAT) == 0) {
E 8
			char	**pwsv = get_nsswitch(NSS_DBNAM_PASSWD_COMPAT);
E 2
D 4
			enum	svc_order sv_compat = srv_yp;
E 4
I 4
			enum	svc_services sv_compat = srv_yp;
E 4
			char	*what = "nis";

			/* Check for service passwd_compat: */
D 8
			for (; *pwsv; pwsv++) {
				if (strcmp(*pwsv, SV_NISPLUS) == 0) {
					sv_compat = srv_nisplus;
					what = "nisplus";
E 8
I 8
			if (pwsv) {
				for (; *pwsv; pwsv++) {
					if (strcmp(*pwsv, SV_NISPLUS) == 0) {
						sv_compat = srv_nisplus;
						what = "nisplus";
					}
E 8
				}
I 8
				_svcinfo.ServiceOrder[svo++] = sv_compat;
				debug(DB_LOOKUP, "compat/%s ", what);
I 9
			} else {
				_svcinfo.ServiceOrder[svo++] = srv_local;
				_svcinfo.ServiceOrder[svo++] = sv_compat;
				debug(DB_LOOKUP, "compat/%s ", what);
E 9
E 8
			}
D 2
			ServiceOrder[svo++] = sv_compat;
E 2
I 2
D 3
			svc_ServiceOrder[svo++] = sv_compat;
E 3
I 3
D 8
			_svcinfo.ServiceOrder[svo++] = sv_compat;
E 3
E 2
			debug(DB_LOOKUP, "compat/%s ", what);
E 8
		}
#endif
#ifdef	USE_NISPLUS
		if (strcmp(*svlist, SV_NISPLUS) == 0) {
			die("NIS+ not supported\n");
D 2
			ServiceOrder[svo++] = srv_nisplus;
E 2
I 2
D 3
			svc_ServiceOrder[svo++] = srv_nisplus;
E 3
I 3
			_svcinfo.ServiceOrder[svo++] = srv_nisplus;
E 3
E 2
			debug(DB_LOOKUP, "nisplus ");
		}
#endif
	}
D 2
	ServiceOrder[svo] = srv_last;
E 2
I 2
D 3
	svc_ServiceOrder[svo] = srv_last;
E 3
I 3
	_svcinfo.ServiceOrder[svo] = srv_last;
I 12
	_svcinfo.init = 1;
E 12
E 3
E 2
	debug(DB_LOOKUP, "\n");
I 4
D 11
	if (svp) {
		*svp = _svcinfo;
		return(svp);
	} 
E 4
I 3
	return(&_svcinfo);
E 11
E 3

#undef	SV_NIS
#undef	SV_NISPLUS
#undef	SV_COMPAT
#undef	SV_FILES
#undef	SV_PWCOMPAT
}
D 13
#endif	/* OS_SUNOS_5 */
E 13
I 13
#endif	/* defined(HAS_NSSWITCH) && defined(OS_SUNOS_5) */
E 13

#ifndef	_SETUP
/*
D 11
 * The default svc_get() routine
E 11
I 11
 * The default init_pwsvc() routine
E 11
 */
D 4
private void
svc_get(argc, argv, envp)
E 4
I 4
D 7
public struct pwsvc *
E 7
I 7
D 11
public struct pw_svc *
E 7
D 6
svc_info(argc, argv, envp, svp)
E 6
I 6
get_pwsvc(argc, argv, envp, svp)
E 11
I 11
void
D 13
init_pwsvc(argc, argv)
E 13
I 13
init_pwsvc(argc, argv, cmdsw)
E 13
E 11
E 6
E 4
	int	argc;	/*NOTUSED*/
	char	**argv;	/*NOTUSED*/
I 13
	char	**cmdsw; /*NOTUSED*/
E 13
D 11
	char	**envp; /*NOTUSED*/
I 4
D 7
	struct pwsvc	*svp;
E 7
I 7
	struct pw_svc	*svp;
E 11
E 7
E 4
{
D 2
	SecurityLevel = sec_std;
E 2
I 2
D 3
	svc_SecurityLevel = sec_std;
E 3
I 3
	_svcinfo.SecurityLevel = sec_std;
E 3
E 2
#ifdef	SUNOS4_SECURITY
D 10
	if (issecure())
E 10
I 10
	if (issecure()) {
E 10
D 2
		SecurityLevel = sec_sunC2;
E 2
I 2
D 3
		svc_SecurityLevel = sec_sunC2;
E 3
I 3
		_svcinfo.SecurityLevel = sec_sunC2;
I 10
D 11
		debug(DB_LOOKUP, "get_pwsvc: SUN C2\n");
E 11
I 11
		debug(DB_LOOKUP, "init_pwsvc: SUN C2\n");
E 11
	}
E 10
E 3
E 2
#endif	/* OS_SUNOS_4 */
I 10
#ifdef	HPUX_AUTH
D 15
	_svcinfo.SecurityLevel = sec_HPUXtrusted;
E 15
I 15
	_svcinfo.SecurityLevel = sec_HPtrusted;
E 15
D 11
	debug(DB_LOOKUP, "get_pwsvc: HPUX auth\n");
E 11
I 11
	debug(DB_LOOKUP, "init_pwsvc: HPUX auth\n");
E 11
#endif
I 12
	_svcinfo.init = 1;
E 12
E 10
I 4
D 11
	if (svp) {
		*svp = _svcinfo;
		return(svp);
	}
E 4
I 3
	return(&_svcinfo);
E 11
E 3
}
#endif	/* _SETUP */

I 11
/*
 * get_pwsvc
 *	Return the password service info block
 * Usage:
D 14
 *	ptr = get_pwsvc()
E 14
I 14
 *	ptr = get_pwsvc();
E 14
 */
struct pw_svc *
get_pwsvc()
{
	if (_svcinfo.init == 0)
D 13
		init_pwsvc(0, 0);
E 13
I 13
		init_pwsvc(0, 0, 0);
E 13
	return(&_svcinfo);
}

E 11
/* End %M% */
E 1
