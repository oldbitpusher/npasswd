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
 * Routines to fetch the "service order" list for "passwd".
 * There is a "init_pwsvc()" routine for each service
 * variant (nsswitch, svc.conf, etc).
 *
 * Exported routines:
 *	init_pwsvc()
 *	get_pwsvc()
 */

#ifndef lint
static char sccsid[] = "@(#)pw_svc.c	1.14 11/17/98 (cc.utexas.edu) /usr/share/src/private/ut/share/bin/passwd/V2.0/src/Common/SCCS/s.pw_svc.c";
#endif

#include "npasswd.h"
#include "pw_svc.h"

extern char	*crypt();	/* Standard encryptor */

static struct pw_svc _svcinfo = { 
	0,			/* Not initialized */
	crypt,			/* Password encryptor */
	sec_std,		/* System security level */
	{ 			/* Passwd lookup services */
#ifdef  USE_NIS
		srv_local, srv_yp, srv_last
#else
		srv_local, srv_last
#endif
	}
};

#ifdef	HAS_SVCCONF		/* Ultrix and Digital UNIX (OSF/1) */
#define	_SETUP	1		/* A setup method has been selected */
/*
 * init_pwsvc (Ultrix/OSF1)
 *	Get service order for Digital UNIX (using /etc/svc.conf)
 * Usage
 *	init_pwsvc(int argc, char **argv, char **);
 * Error exits
 *	Error return from getsvc()
 */
#include <sys/svcinfo.h>

void
init_pwsvc(argc, argv, cmdsw)
	int	argc;			/* Used in OSF/1 */
	char	**argv;			/* Used in OSF/1 */
	char	**cmdsw;		/* NOTUSED*/
{
	extern char 	*crypt16();	/* Extended encryptor */
#ifdef	OSF1_AUTH
	extern char 	*bigcrypt();	/* Really extended encryptor */
#endif
	struct svcinfo	*svc;	/* Service info */
	int	i,		/* Temp */
		j,		/* Temp */
		s;		/* Temp */

	_svcinfo.SecurityLevel = sec_std;
	_svcinfo.PasswdCrypt = crypt;

	if ((svc = getsvc()) == 0)
		logdie("Cannot get service configuration.\n");

	debug(DB_LOOKUP, "init_pwsvc (svc.conf): "):
	for (s = i = 0; (j = svc->svcpath[SVC_PASSWD][i]) != SVC_LAST; i++) {
		switch(j) {
		case SVC_LOCAL:
			_svcinfo.ServiceOrder[s++] = srv_local;
			debug(DB_LOOKUP, "local "):
			break;
		case SVC_YP:
			_svcinfo.ServiceOrder[s++] = srv_yp;
			debug(DB_LOOKUP, "nis "):
			break;
		case SVC_BIND:
			_svcinfo.ServiceOrder[s++] = srv_hesiod;
			debug(DB_LOOKUP, "bind "):
			break;
		}
	}
	_svcinfo.ServiceOrder[s++] = srv_last;

	switch (svc->svcauth.seclevel) {
	case SEC_BSD:
		_svcinfo.SecurityLevel = sec_std;
		debug(DB_LOOKUP, "(security_std) "):
		break;
	case SEC_UPGRADE:
		_svcinfo.SecurityLevel = sec_u4upgrade;
		debug(DB_LOOKUP, "(security_upgrade) "):
		break;
	case SEC_ENHANCED:
		_svcinfo.SecurityLevel = sec_u4enhanced;
		debug(DB_LOOKUP, "(security_enhanced) "):
#ifdef	ULTRIX_AUTH
		_svcinfo.PasswdCrypt = crypt16;
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
				_svcinfo.SecurityLevel = sec_OSFenhanced;
				_svcinfo.PasswdCrypt = bigcrypt;
				debug(DB_LOOKUP, "(security_C2) "):
		}
	}
#endif
	debug(DB_LOOKUP, "\n"):
	_svcinfo.init = 1;
}
#endif	/* HAS_GETSVC_CONF */


#if	defined(HAS_NSSWITCH) && defined(OS_SUNOS_5)
#define	_SETUP	1
/*
 * get_nsswitch
 *	Process the Solaris 2 name service switch 
 * Usage
 *	service_list = get_nsswitch(char *database-name);
 */
#undef	private			/* Avoid use of 'private' in includes below */
#include <nsswitch.h>
#include <nss_dbdefs.h>

static char **
get_nsswitch(what)
	char	*what;
{
	struct __nsw_switchconfig *config;
	struct __nsw_lookup     *p;
	enum __nsw_parse_err    error;
	static char	*srvlist[N_SVC];
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
		warn("Warning: \"%s\" not found.\n", __NSW_CONFIG_FILE);
		return(0);
#if	(OS_MINOR_VERSION >= 3)
	case __NSW_CONF_PARSE_NOPOLICY:
#else
	case __NSW_PARSE_NOPOLICY:
#endif
		return(0);
#if	(OS_MINOR_VERSION >= 3)
	case __NSW_CONF_PARSE_SYSERR:
#else
	case __NSW_PARSE_SYSERR:
#endif
		warn("Warning: Syntax error in \"%s\".\n", __NSW_CONFIG_FILE);
		return(0);
	}
	for (p = config->lookups; p; p = p->next) {
		srvlist[svcno++] = strdup(p->service_name);
	}
	srvlist[svcno] = 0;
	return(srvlist);
}

void
init_pwsvc(argc, argv, cmdsw)
	int	argc;		/*NOTUSED*/
	char	**argv;		/*NOTUSED*/
	char	**cmdsw;	/* Command line switches */
{
/*
 *	Having a list of defines for service names is not really the
 *	right way to go, but since source changes are needed to add
 *	a method module, forcing changes here also is not the most
 *	terrible thing.
 */
#define	SV_NIS		"nis"
#define	SV_NISPLUS	"nisplus"
#define	SV_COMPAT	"compat"
#define	SV_FILES	"files"
	int	svo = 0;
	char	**svlist;

	_svcinfo.SecurityLevel = sec_std;
	debug(DB_LOOKUP, "init_pwsvc nsswitch: ");

	/*
	 * TODO: Figure out what security level needed for RPC 
	 * i.e. might a key need resetting.
	 */

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
	for (svlist = get_nsswitch(NSS_DBNAM_PASSWD); *svlist; *svlist++) {
		if (strcmp(*svlist, SV_FILES) == 0) {
			_svcinfo.ServiceOrder[svo++] = srv_local;
			debug(DB_LOOKUP, "local ");
		}
#if	defined(USE_NIS) || defined(USE_NISPLUS)
		if (strcmp(*svlist, SV_NIS) == 0) {
			_svcinfo.ServiceOrder[svo++] = srv_yp;
			debug(DB_LOOKUP, "nis ");
		}
		if (strcmp(*svlist, SV_COMPAT) == 0) {
			char	**pwsv = get_nsswitch(NSS_DBNAM_PASSWD_COMPAT);
			enum	svc_services sv_compat = srv_yp;
			char	*what = "nis";

			/* Check for service passwd_compat: */
			if (pwsv) {
				for (; *pwsv; pwsv++) {
					if (strcmp(*pwsv, SV_NISPLUS) == 0) {
						sv_compat = srv_nisplus;
						what = "nisplus";
					}
				}
				_svcinfo.ServiceOrder[svo++] = sv_compat;
				debug(DB_LOOKUP, "compat/%s ", what);
			} else {
				_svcinfo.ServiceOrder[svo++] = srv_local;
				_svcinfo.ServiceOrder[svo++] = sv_compat;
				debug(DB_LOOKUP, "compat/%s ", what);
			}
		}
#endif
#ifdef	USE_NISPLUS
		if (strcmp(*svlist, SV_NISPLUS) == 0) {
			die("NIS+ not supported\n");
			_svcinfo.ServiceOrder[svo++] = srv_nisplus;
			debug(DB_LOOKUP, "nisplus ");
		}
#endif
	}
	_svcinfo.ServiceOrder[svo] = srv_last;
	_svcinfo.init = 1;
	debug(DB_LOOKUP, "\n");

#undef	SV_NIS
#undef	SV_NISPLUS
#undef	SV_COMPAT
#undef	SV_FILES
#undef	SV_PWCOMPAT
}
#endif	/* defined(HAS_NSSWITCH) && defined(OS_SUNOS_5) */

#ifndef	_SETUP
/*
 * The default init_pwsvc() routine
 */
void
init_pwsvc(argc, argv, cmdsw)
	int	argc;	/*NOTUSED*/
	char	**argv;	/*NOTUSED*/
	char	**cmdsw; /*NOTUSED*/
{
	_svcinfo.SecurityLevel = sec_std;
#ifdef	SUNOS4_SECURITY
	if (issecure()) {
		_svcinfo.SecurityLevel = sec_sunC2;
		debug(DB_LOOKUP, "init_pwsvc: SUN C2\n");
	}
#endif	/* OS_SUNOS_4 */
#ifdef	HPUX_AUTH
	_svcinfo.SecurityLevel = sec_HPUXtrusted;
	debug(DB_LOOKUP, "init_pwsvc: HPUX auth\n");
#endif
	_svcinfo.init = 1;
}
#endif	/* _SETUP */

/*
 * get_pwsvc
 *	Return the password service info block
 * Usage:
 *	ptr = get_pwsvc();
 */
struct pw_svc *
get_pwsvc()
{
	if (_svcinfo.init == 0)
		init_pwsvc(0, 0, 0);
	return(&_svcinfo);
}

/* End pw_svc.c */
