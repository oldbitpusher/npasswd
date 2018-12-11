h63008
s 00007/00003/00787
d D 1.36 00/03/09 10:40:43 clyde 36 35
c 1. Add more debug statement in ypwhich
c 2. Use case-insensitive string match for hostname compare
e
s 00007/00006/00783
d D 1.35 98/08/17 16:57:31 clyde 35 34
c Change use of zncrypt()
e
s 00013/00005/00776
d D 1.34 98/07/21 09:33:53 clyde 34 33
c 1. Add explict notice about why password needed for RPC 
c 2. Use zdcrypt() and zncrypt() around theUser->password
c 3. Fix Secure RPC support code typo
e
s 00002/00001/00779
d D 1.33 98/07/16 09:19:39 clyde 33 32
c Change get_pwsvc() usage
e
s 00001/00001/00779
d D 1.32 98/06/23 10:58:24 clyde 32 31
c Change compile-time debug include trigger
e
s 00002/00004/00778
d D 1.31 98/04/28 16:49:19 clyde 31 30
c 1. Remove DEBUG_NOEXEC
c 2. Change LOCAL_FILES to DEBUG_LOCAL_FILES
e
s 00037/00018/00745
d D 1.30 98/04/21 11:03:08 clyde 30 29
c 1. Fix some debug messages
c 2. Add HP-UX password aging support contrib
e
s 00006/00001/00757
d D 1.29 97/09/23 12:28:38 clyde 29 28
c 1. Fix bzero/memset typo
c 2. Use xdr_int() if xdr_uid_t() not available
e
s 00001/00001/00757
d D 1.28 97/06/18 13:30:52 clyde 28 27
c Change getpass() to np_getpass()
e
s 00004/00000/00754
d D 1.27 97/05/27 09:28:43 clyde 27 26
c Use memset(0) instead of bzero() where available
e
s 00034/00008/00720
d D 1.26 97/05/05 10:36:54 clyde 26 25
c Rewrite YP activity probe in ypwhich()
e
s 00040/00016/00688
d D 1.25 96/12/17 11:04:07 clyde 25 24
c 1. Change public routine names 
c 2. Set timeout on YP interaction to prevent hanging
e
s 00001/00001/00703
d D 1.24 96/09/13 15:40:26 clyde 24 23
c Don't trigger NO_STRINGS if SunOS version >= 5.5
e
s 00009/00009/00695
d D 1.23 96/08/29 13:04:47 clyde 23 22
c 1. Remove 'const' declarations (too much compiler pain)
c 2. Don't bomb if RPC password is null
e
s 00004/00000/00700
d D 1.22 96/08/27 16:33:09 clyde 22 21
c Use memcpy if available
e
s 00001/00001/00699
d D 1.21 96/08/14 17:23:25 clyde 21 20
c Change LOCAL_TEST_FILES to LOCAL_FILES
e
s 00196/00083/00504
d D 1.20 96/08/13 16:33:58 clyde 20 19
c 1, Add lots of comments
c 2. Remove arguments from yp_init()
c 3. Move some routines around
e
s 00061/00021/00526
d D 1.19 96/08/06 14:14:04 clyde 19 18
c beta 3 cycle 1 checkin
e
s 00007/00006/00540
d D 1.18 96/04/03 14:35:37 clyde 18 17
c Reflect new mpasswd structure element names
e
s 00002/00002/00544
d D 1.17 96/04/01 14:10:19 clyde 17 16
c Change a #ifdef DEBUG to #ifdef DEBUG_NOEXEC
e
s 00002/00000/00544
d D 1.16 96/03/29 11:38:45 clyde 16 15
c Add debug hooks
e
s 00006/00012/00538
d D 1.15 96/03/27 09:28:03 clyde 15 14
c Use debug() routine for messages
e
s 00033/00025/00517
d D 1.14 95/04/05 16:19:54 clyde 14 13
c Beta 3 development checkin
e
s 00039/00000/00503
d D 1.13 94/10/24 10:30:03 clyde 13 12
c Add check_rpc_key() routine
e
s 00107/00044/00396
d D 1.12 94/09/28 16:11:13 clyde 12 11
c Development checkin 
e
s 00033/00021/00407
d D 1.11 94/06/20 13:48:53 clyde 11 10
c 1 Cleanup debugging statements
c 2 Cleanup RPC call retry loop
e
s 00003/00003/00425
d D 1.10 94/05/17 15:26:11 clyde 10 9
c Change SUN_SHADOW to SUN_SECURITY
e
s 00015/00003/00413
d D 1.9 94/03/31 17:42:52 clyde 9 8
c Retry RPC call a few times
e
s 00003/00001/00413
d D 1.8 94/03/17 13:35:53 clyde 8 7
c Wrap entire module in #ifdef YP_PASSWD
e
s 00009/00002/00405
d D 1.7 94/03/01 15:59:19 clyde 7 6
c Devlopment checkin:
c 1. Fix Sun shadow passwd setting
c 
e
s 00030/00032/00377
d D 1.6 93/12/20 09:19:10 clyde 6 5
c Finish support for changing secret RPC keys
e
s 00156/00039/00253
d D 1.5 93/12/17 17:09:24 clyde 5 4
c Add code to update users' secret key
e
s 00029/00113/00263
d D 1.4 93/12/16 13:35:18 clyde 4 3
c Compress yp_sync routine
e
s 00188/00145/00188
d D 1.3 93/12/16 11:04:46 clyde 3 2
c Development checkin
e
s 00070/00081/00263
d D 1.2 93/07/12 15:07:19 clyde 2 1
c 1. Cleanup logdie() calls.
c 2. Move ypwhich() and change to return pointer to structure.
e
s 00344/00000/00000
d D 1.1 93/07/12 09:18:20 clyde 1 0
c date and time created 93/07/12 09:18:20 by clyde
e
u
U
f e 0
t
T
I 1
/*
D 5
 *	yp_backend - Routines for dealing with NIS
E 5
I 5
D 20
 *	pw_nis.c - Network Information Service (NIS, nee YP) support routines
E 20
I 20
 * %M%
 *	Network Information Service (NIS/YP) method routines
 *	Needs -lrpcsvc on many systems
E 20
E 5
 *
D 9
 *	Must be linked with -lrpcsvc
E 9
I 9
D 20
 *	Needs library routines from -lrpcsvc on many systems
E 20
I 20
 * Exported routines
 *	init_yp()
 *	ypwhich()
D 25
 *	update_yp_pw()
E 25
I 25
 *	put_yp_user()
E 25
 *	update_yp_map()
D 25
 *	get_yp_pw()
E 25
I 25
 *	get_yp_user()
E 25
 *	ypsync()
 *	update_rpc_key()
 *	check_rpc_key()
 *	yp_password()
 *
 * Exported variables
 *	ypinfo
 *
 * Compilation flags
 *	cc -I.. ... -lrpcsvc
E 20
E 9
 */
I 14
D 24
#if	defined(OS_SUNOS_5)
E 24
I 24
#if	defined(OS_SUNOS_5) && (OS_MINOR_VERSION < 5)
E 24
D 20
#define	NO_STRINGS
E 20
I 20
# define	NO_STRINGS		/* Work around <strings.h> bug */
E 20
#endif
I 20

E 20
E 14
D 5

E 5
#include "npasswd.h"
I 12
#include "pwm_defs.h"
E 12
I 9

E 9
I 8
D 12
#ifdef	YP_PASSWD
E 12
I 12
#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu)";
#endif
E 12

E 8
D 12
#include "pw_defs.h"
#include "pw_nis.h"

E 12
I 12
D 14
#ifdef	YP_SUPPORT
E 14
I 14
D 20
#ifdef	USE_NIS
E 20
I 20
#ifdef	USE_NIS			/* Wraps entire module */

E 20
E 14
#define	PORTMAP
E 12
D 2
#if	YP_PASSWD
E 2
#include <ndbm.h>
#include <netdb.h>
I 26
#include <setjmp.h>
E 26
I 5
D 7
#include <des_crypt.h>
E 7
#include <sys/socket.h>
E 5
#include <rpc/rpc.h>
D 5
#include <rpcsvc/ypclnt.h>
E 5
I 5
D 7
#include <rpc/key_prot.h>
E 7
E 5
#include <rpcsvc/yppasswd.h>
I 3
D 5
#define	DATUM
E 5
I 5
#include <rpcsvc/ypclnt.h>
#define	DATUM			/* Prevent error in next include */
E 5
#include <rpcsvc/yp_prot.h>
D 5
#include <rpcsvc/ypv1_prot.h>
E 3
#include <sys/socket.h>
E 5
I 5
#undef	DATUM
E 5

D 10
#if	SUN_SHADOW
E 10
I 10
D 14
#if	SUN_SECURITY
E 14
I 14
D 20
#ifdef	SECURE_RPC
E 20
I 20
#ifdef	SECURE_RPC		/* SunOS Secure RPC available */
E 20
E 14
E 10
# include <sys/label.h>
# include <sys/audit.h>
I 7
# include <rpc/key_prot.h>
# include <des_crypt.h>
E 7
# include <pwdadj.h>
D 12
#endif
E 12
I 12
# define PKEY_MAP	"publickey.byname"	/* YP publickey map */
# define ROOT_KEY	"/etc/.rootkey"		/* root key is stashed here */
D 14
#endif	/* SUN_SECURITY */
E 14
I 14
#endif	/* SECURE_RPC */
E 14
E 12

I 5
D 12
/*
 *	Constants for doing YP stuff
 */
#define	PKEY_MAP	"publickey.byname"	/* YP publickey map */
#define	ROOT_KEY	"/etc/.rootkey"		/* root key is stashed here */
E 12
#define	MOD_TOKEN	"YP_LAST_MODIFIED"	/* YP map timestamp */
I 11
#define	YPPASSWD_TRIES	3			/* RPC call retries */
#define	YPPASSWD_WAIT	2			/* Retry cycle */
E 11
#ifndef	YP_TIMEOUT
D 12
#define	YP_TIMEOUT	30			/* Timeout for YP interaction */
E 12
I 12
D 26
# define YP_TIMEOUT	30			/* Timeout for YP interaction */
E 26
I 26
# define YP_TIMEOUT	20			/* Timeout for YP interaction */
E 26
E 12
#endif
I 26
#ifndef YP_PROBE_TIMEOUT
# define YP_PROBE_TIMEOUT 2			/* Timeout for YP probing */
#endif
I 30
#ifndef	NIS_PASSWD_MAX_LEN
# define	NIS_PASSWD_MAX_LEN 8		/* Size of YP password buffer */
#endif
E 30
E 26

E 5
D 2

E 2
D 12
#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu)";
#endif

E 12
I 3
D 5
static char *ypdirs[] = {
E 5
I 5
D 20
private char *ypdirs[] = {	/* Possible locations for YP data directories */
E 20
I 20
/*
 * Possible locations for YP data directory
 */
private char *ypdirs[] = {
E 20
E 5
D 19
#ifdef	DEBUG_FILES
E 19
I 19
D 21
#ifdef	LOCAL_TEST_FILES
E 21
I 21
D 31
#ifdef	LOCAL_FILES
E 31
I 31
D 32
#ifdef	DEBUG_LOCAL_FILES
E 32
I 32
#if	(CDEBUG >= CDEBUG_FILES)
E 32
E 31
E 21
E 19
	"./yp",
#endif
I 20
#ifdef	SYSTEM_YP_DIR
	SYSTEM_YP_DIR ,
#endif
E 20
	"/var/yp",
	"/etc/yp",
	0
};

I 20
/*
 * YP configuration block.  Exported for use in other modules.
 */
E 20
I 12
public struct ypinfo   ypinfo = { 0 };

I 20
/*
I 26
 *
 */
private jmp_buf	ypxwait;

/*
E 26
 * init_yp
 *	Fetches YP configuration information and stashes in the <ypinfo>
 *	structure declared in this module
 * Usage
 *	init_yp()	Usually called from pw_initialize()
 */
E 20
public void
D 20
init_yp(argc, argv)
	int	argc;	/*NOTUSED*/
	char	**argv;	/*NOTUSED*/
E 20
I 20
init_yp()
E 20
{
	static int	inited = 0;

D 19
	if (inited) return;
E 19
I 19
	if (ypinfo.inited) return;
E 19
	ypinfo.status = yp_not_running;
	ypwhich(PASSWD_BYNAME, &ypinfo);
D 19
	inited++;
E 19
I 19
	ypinfo.inited = 1;
E 19
}

E 12
E 3
I 2
/*
I 25
 * yp_sig_catch
 *	Called if yp_master() takes too long.  This will happen
 *	if there is no NIS server available.
 */
D 26
private void
E 26
I 26
private Signal_t
E 26
yp_sig_catch()
{
D 26
	logdie("System error - no NIS server\n");
E 26
I 26
D 30
	debug(DB_LOOKUP, "Cannot talk to NIS server\n");
E 30
I 30
	debug(DB_LOOKUP, "ypwhich: Cannot talk to NIS server\n");
E 30
	longjmp(ypxwait,1);
E 26
}

/*
E 25
D 20
 *	ypwhich - Find YP configuration.
E 20
I 20
 * ypwhich
 *	Get YP configuration.
 * Usage
 *	ypwhich(char *yp-name-name, struct ypinfo *ypinfo);
E 20
D 3
 *
 *	Returns:
 *		is_yp_master if we are the master
 *		is_yp_client if we are not the master
 *		yp_not_running if there is no master
E 3
 */
D 3
public struct ypinfo *
ypwhich(map)
E 3
I 3
public void
ypwhich(map, yp)
E 3
D 5
char	*map;		/* Name of YP map to find master of */
I 3
struct ypinfo	*yp;	/* Where to stash configuration */
E 5
I 5
D 20
	char	*map;		/* Name of YP map to find master of */
E 20
I 20
D 23
	const char	*map;	/* Name of YP map to find master of */
E 23
I 23
	char	*map;	/* Name of YP map to find master of */
E 23
E 20
	struct ypinfo	*yp;	/* Where to stash configuration */
E 5
E 3
{
D 8
	
E 8
D 25
	struct hostent	*hinfo;
E 25
I 25
	struct hostent	*hinfo;			/* Hostname lookup */
E 25
	char	hostname[MAXHOSTNAMLEN];	/* Our host name */
D 3
	struct ypinfo	yp;
E 3
D 25
	char	*t;			/* ACME Temporary Variables, Inc. */
E 25
I 25
	int	ti; 				/* ACME Temporaries */
	char	*t;				/* ACME Temporaries */
	Signal_t	(*oldalarm)();		/* SIGALARM save */
E 25

I 20
D 30
#ifdef	HAS_MEMSET
	memset((void *)yp, 0, sizeof(*yp));
#else
E 20
D 3
	BZERO((char *)&yp, sizeof(yp));
	yp.status = yp_not_running;	/* Assume no YP running */
E 3
I 3
D 14
	BZERO((char *)yp, sizeof(*yp));
E 14
I 14
	bzero((char *)yp, sizeof(*yp));
I 20
#endif
E 30
I 30
	zeromem(yp, sizeof *yp);
E 30
I 25
D 26
	(void) alarm(YP_TIMEOUT);
	oldalarm = signal(SIGALRM, yp_sig_catch);

E 26
E 25
E 20
E 14
	yp->status = yp_not_running;	/* Assume no YP running */
E 3
D 26
	if (yp_get_default_domain(&t))
E 26
I 26

	/*
	 * If we already know that YP isn't working, bail.
	 */
	if (ypinfo.inited && ypinfo.status == yp_not_running) {
E 26
D 3
		return(&yp);
	yp.domain = copystr(t);
E 3
I 3
		return;
I 26
	}

	/*
	 * Get NIS domain name
	 */
	if (yp_get_default_domain(&t))
		return;		/* Domain not set */
E 26
D 19
	yp->domain = copystr(t);
E 19
I 19
	yp->domain = strdup(t);
I 25
D 30
	debug(DB_LOOKUP, "YP domain is \"%s\"\n", yp->domain);
E 30
I 30
	debug(DB_LOOKUP, "ypwhich: YP domain is \"%s\"\n", yp->domain);
E 30
E 25
E 19
E 3

I 26
	/*
	 * Set non-local jump for YP probe timeout
	 */
	if (setjmp(ypxwait))
		return;		/* Return if probe timed out */

	(void) alarm(YP_PROBE_TIMEOUT);
	oldalarm = signal(SIGALRM, yp_sig_catch);
E 26
D 3
	if (yp_master(yp.domain, map, &t))
		return(&yp);		/* Assume no YP running */
E 3
I 3
D 25
	if (yp_master(yp->domain, map, &t))
D 20
		return;		/* Assume no YP running */
E 20
I 20
		return;			/* Assume no YP running */
E 25
I 25
	ti = yp_master(yp->domain, map, &t);
	(void) alarm(0);
	(void) signal(SIGALRM, oldalarm);
D 26

E 26
	if (ti)			/* Assume no YP running */
		return;
D 30
	debug(DB_LOOKUP, "YP master is \"%s\"\n", t);
E 30
I 30
D 36
	debug(DB_LOOKUP, "ypwhich: YP master is \"%s\"\n", t);
E 36
I 36
	debug(DB_LOOKUP, "ypwhich: YP master \"%s\"\n", t);
E 36
E 30
I 26

E 26
E 25
E 20
E 3
	/*
	 * Compare my host name and the YP master's host name.
	 * Use gethostbyname() to return the fully qualified form so that
	 * a string compare can be done.
	 */
D 14
	if (INDEX(t, '.') == 0) {
E 14
I 14
D 19
	if (index(t, '.') == 0) {
E 19
I 19
	if (strchr(t, '.') == 0) {
E 19
E 14
		static char	ypmaster_f[MAXHOSTNAMLEN];

		if ((hinfo = gethostbyname(t)) == 0)
			logdie("gethostbyname failed for ypmaster");
		(void) strcpy(ypmaster_f, hinfo->h_name);
I 36
		debug(DB_LOOKUP,
			"ypwhich: canonical YP master \"%s\"\n", hinfo->h_name);
E 36
		t = ypmaster_f;
	}
	(void) gethostname(hostname, sizeof(hostname));
D 14
	if (INDEX(hostname, '.') == 0) {
E 14
I 14
D 19
	if (index(hostname, '.') == 0) {
E 19
I 19
	if (strchr(hostname, '.') == 0) {
I 36

E 36
E 19
E 14
		if ((hinfo = gethostbyname(hostname)) == 0)
			logdie("gethostbyname failed for self");
		(void) strcpy(hostname, hinfo->h_name);
I 36
		debug(DB_LOOKUP, "ypwhich: Hostname \"%s\"\n", hinfo->h_name);
E 36
	}
D 3
	if (strcmp(t, hostname) == 0)
		yp.status = is_yp_master;
	else
		yp.status = is_yp_client;
	yp.master = copystr(t);
	return(&yp);
E 3
I 3
D 19
	yp->master = copystr(t);
E 19
I 19
	yp->master = strdup(t);
E 19
D 36
	if (strcmp(t, hostname) == 0) {
E 36
I 36
	if (strcasecmp(yp->master, hostname) == 0) {
E 36
D 20
		char	**dir,			/* temp */
			path[MAXPATHLEN];	/* temp */
E 20
I 20
D 25
		char	**dir,			/* ACME Scratch Storage */
			path[MAXPATHLEN];	/* ACME Scratch Storage */
E 25
I 25
		char	**dir,			/* ACME Temporaries */
			path[MAXPATHLEN];	/* ACME Temporaries */
E 25
E 20

I 20
		/*
		 * Find the YP data directory
		 */
E 20
		yp->status = is_yp_master;
D 20
		/* Find the data directory */
E 20
		for (dir = ypdirs; *dir; dir++) {
			(void) sprintf(path, "%s/%s", *dir, yp->domain);
			if (access(path, 0) == 0) {
D 19
				yp->data = copystr(path);
E 19
I 19
				yp->data = strdup(path);
I 25
D 30
				debug(DB_LOOKUP,
					"YP directory is \"%s\"\n", path);
E 30
I 30
D 36
				ypwhich: debug(DB_LOOKUP,
E 36
I 36
				debug(DB_LOOKUP,
E 36
					"ypwhich: YP directory is \"%s\"\n", path);
E 30
E 25
E 19
				return;
			}
		}
		logdie("Cannot find YP data directory");
	}
	yp->status = is_yp_client;
E 3
}

I 12

E 12
E 2
D 20
/*	Error message for when yppasswdd fails with error code 1.  */
E 20
I 20
/*
 * Error message for when yppasswdd fails with error code 1.
 */
E 20
static char *yperrmsg =
D 2

E 2
"Password change failed: Problem with yppasswdd.\n\n\
D 2
This is probably because the YP maps are out of sync\n\
with the YP passwd file for %s on %s.\n\n\
E 2
I 2
This is probably because the NIS maps are out of sync\n\
with the NIS passwd file for %s on %s.\n\n\
E 2
Please try again later.\n";

I 20
/*
D 25
 * update_yp_pw
E 25
I 25
 * put_yp_user
E 25
 *	Update NIS passwd database
 * Usage
D 25
 *	update_yp_pw(struct mpasswd *old, struct mpasswd *new, int changes);
E 25
I 25
 *	put_yp_user(struct mpasswd *old, struct mpasswd *new, int changes);
E 25
 * Side effects
 *	Update secure RPC credentials if applicable
 * Error exits
 *	Failure to set up RPC connection to yppasswdd service
 *	Timeout in sending RPC request (after YPPASSWD_TRIES retries)
 *	Failure in sending RPC request
 *	Error returned from remote yppasswdd server
 */
E 20
D 2
void update_yp_passwd(theUser, NewUser, ypdomain, ypmaster)
E 2
I 2
D 5
void update_yp_passwd(theUser, NewUser, ypinfo, changes)
E 2
struct mpasswd	*theUser;
struct passwd	*NewUser;
D 2
char		*ypdomain,
		*ypmaster;
E 2
I 2
struct ypinfo	*ypinfo;
int		changes;
E 5
I 5
public void
D 12
update_yp_passwd(theUser, NewUser, ypinfo, changes)
E 12
I 12
D 25
update_yp_pw(theUser, newUser, changes)
E 25
I 25
put_yp_user(theUser, newUser, changes)
E 25
E 12
	struct mpasswd	*theUser;	/* Original user information */
D 12
	struct passwd	*NewUser;	/* New user information */
	struct ypinfo	*ypinfo;	/* YP information */
E 12
I 12
	struct mpasswd	*newUser;	/* New user information */
E 12
D 20
	int		changes;	/* What was changed */
E 20
I 20
	int		changes;	/* What was changed (CHG_X flags) */
E 20
E 5
E 2
{
	int	rc;		/* Return code from ypasswdd */
I 9
	int	tries;		/* How many tries to call yppasswdd */
E 9
	int	why;		/* RPC call return code */
	int	ypport;		/* Port for RPC call */
D 30
	char	cpw[8];		/* Buffer for current password (cleartext) */
E 30
I 30
	char	cpw[NIS_PASSWD_MAX_LEN + 1];	
				/* Buffer for current password (cleartext) */
E 30
	struct yppasswd yppasswd; /* YP passwd change block */
	struct pw_opaque *aux = (struct pw_opaque *)theUser->opaque;
I 34
	struct	pw_svc *svc = get_pwsvc();
E 34

D 2
#ifdef	ALWAYS_USE_YPPASSWD
	/*
	 * %%POLICY - Using rpc.ypassswdd for all changes.
	 *
	 * This option forces all changes through rpc.yppasswdd.
	 *
	 * I do not recommend this option because of the buggy behavior
	 * I have seen by various versions of rpc.yppasswdd.  I also prefer
	 * that when I change a password on the YP master, that change will
	 * happen and I will get immediate feedback to that effect. 
	 *
	 */
	ypstatus = is_yp_client;
#endif	/* USE_YPPASSWD_ALWAYS */
	if (theUser->password[0] == 0 && theUser->mpw_passwd[0])
		die("Cannot change NIS password without old password.\n");

E 2
I 2
D 34
	if (theUser->password[0] == 0 && theUser->mpw_passwd[0]) /* XXX */
E 34
I 34
	/*
	 * Passwd info cannot be updated via the RPC interface
	 * without having the current password in the clear.
	 * This is a basic limitation of the RPC mechanism (at least for SunOS
	 * 4) and there is no way around it.
	 */
	if (theUser->password[0] == 0 && theUser->mpw_passwd[0])
E 34
		die("Cannot change passwd info via NIS without old password.\n");
I 12
D 14
#ifdef	HAS_PW_AGE
E 14
I 14
#ifdef	PWAGE
E 14
	/*
	 * Update password aging information
	 */
D 18
	if (newUser->pwage.doit) {
		if (newUser->pwage.max_time == 0) {
E 18
I 18
D 19
	if (newUser->pwage.do_aging) {
E 19
I 19
	if (changes & CHG_PWAGE) {
I 30

E 30
E 19
		if (newUser->pwage.must_change == 0) {
E 18
			newUser->mpw_age = '\0';
		}
		else {
			extern char *l64a();
D 19
			time_t	now = newUser->pwage.last_change / SEC_PER_WEEK,
E 19
I 19
			time_t	now = newUser->pwage.last_change / SEC_WEEK,
E 19
				pwage;

			if (changes & CHG_PW)
D 19
				now = time((time_t *)0) / SEC_PER_WEEK;
E 19
I 19
				now = time((time_t *)0) / SEC_WEEK;
I 30
#ifdef	OS_HPUX
			{
			char	agetmp[STRINGLEN];

			(void) strcpy(agetmp, l64a(newUser->pwage.must_change));
			if (newUser->pwage.can_change)
				(void) strcat(agetmp,
					l64a(newUser->pwage.can_change));
			else
				(void) strcat(agetmp, ".");
			(void) strcat(agetmp, l64a(now));
			if (strlen(agetmp))
				(void) strcpy(newUser->mpw_age, agetmp);
			else
				newUser->mpw_age = ".";
			}
#else	/* OS_HPUX */
E 30
E 19
D 18
			pwage = newUser->pwage.max_time
				+ (newUser->pwage.min_time << 6)
E 18
I 18
			pwage = newUser->pwage.must_change
				+ (newUser->pwage.can_change << 6)
E 18
				+ (now << 12);
			if (pwage)
				newUser->mpw_age = l64a(pwage);
			else
				newUser->mpw_age = ".";
I 30
#endif	/* OS_HPUX */
E 30
		}
	}
D 30
#endif
E 30
I 30
#endif	/* PWAGE */
E 30
E 12
E 2
D 34
	(void) strncpy(cpw, theUser->password, sizeof(cpw));
E 34
I 34
	(void) strncpy(cpw, zdcrypt(theUser->password), sizeof(cpw));
E 34
D 30
	cpw[8] = 0;
E 30
I 30
	cpw[NIS_PASSWD_MAX_LEN] = 0;
E 30
	yppasswd.oldpass = cpw;
D 12
	copypwent(NewUser, &yppasswd.newpw);
E 12
I 12
	copypwent(&newUser->pw, &yppasswd.newpw);
E 12

D 11
	if (DebugLevel)		/* XXX */
E 11
I 11
D 15
	if (DebugLevel >= DB_UPDATE) {
E 11
		printf("yppasswd(%s, %s)\n", cpw, yppasswd.newpw.pw_passwd);
I 11
		fflush(stdout);
	}
E 15
I 15
D 25
	debug(DB_UPDATE, "update_yp_pw: yppasswd(%s, %s)\n",
E 25
I 25
	debug(DB_UPDATE, "put_yp_user: yppasswd(%s, %s)\n",
E 25
		cpw, yppasswd.newpw.pw_passwd);
E 15
E 11
D 17
#ifndef	DEBUG
E 17
I 17
D 31
#ifndef	DEBUG_NOEXEC
E 31
I 31

E 31
E 17
D 2
	if ((ypport = getrpcport(ypmaster, YPPASSWDPROG,
E 2
I 2
D 12
	if ((ypport = getrpcport(ypinfo->master, YPPASSWDPROG,
E 12
I 12
D 14
#ifndef	OS_SOLARIS_2
E 14
I 14
#ifndef	OS_SUNOS_5
E 14
	if ((ypport = getrpcport(ypinfo.master, YPPASSWDPROG,
E 12
E 2
	     YPPASSWDPROC_UPDATE, IPPROTO_UDP)) == 0)
D 2
		logdie("ypassswdd on %s is not running.\n", master);
E 2
I 2
D 12
		logdie("ypassswdd on %s is not running", ypinfo->master);
E 12
I 12
		logdie("ypassswdd on %s is not running", ypinfo.master);
E 12
E 2

	if (ypport >= IPPORT_RESERVED)
D 2
		logdie("yppasswdd on %s is not privleged.\n", master);
	rc = callrpc(ypmaster, YPPASSWDPROG, YPPASSWDVERS,
E 2
I 2
D 12
		logdie("yppasswdd on %s is not privleged", ypinfo->master);
E 12
I 12
		logdie("yppasswdd on %s is not privleged", ypinfo.master);
E 12
I 9

I 12
D 19
#endif
E 19
I 19
#endif	/* OS_SUNOS_5 */
E 19
E 12
D 11
	tries = 0;
retry:
E 9
	rc = callrpc(ypinfo->master, YPPASSWDPROG, YPPASSWDVERS,
E 2
		YPPASSWDPROC_UPDATE, xdr_yppasswd, &yppasswd, xdr_int, &why);
E 11
I 11
	for (tries = 0; tries <= YPPASSWD_TRIES; tries++) {
D 12
		rc = callrpc(ypinfo->master, YPPASSWDPROG, YPPASSWDVERS,
			YPPASSWDPROC_UPDATE, xdr_yppasswd, &yppasswd,
			xdr_int, &why);
E 12
I 12
		rc = callrpc(ypinfo.master, YPPASSWDPROG, YPPASSWDVERS,
			YPPASSWDPROC_UPDATE, xdr_yppasswd, (char *)&yppasswd,
			xdr_int, (char *)&why);
E 12
E 11

D 5
	/* RPC call error */
	if (rc) {
E 5
I 5
D 9
	if (rc) {		/* RPC error */
E 9
I 9
D 11
	/*
	 * If the call timed out, retry because the NIS master might be slow
	 */
	if (rc == RPC_TIMEDOUT) {
		printf("Timeout talking to password change server - trying again\n");
		if (++tries < 3) goto retry;	/* XXX */
	}
	if (rc != RPC_SUCCESS) {		/* RPC error */
E 11
I 11
		if (rc == RPC_SUCCESS)
			break;
		/*
		 * If the call timed out, retry because the NIS master
		 * might be slow
		 */
		if (rc != RPC_TIMEDOUT) {
E 11
E 9
E 5
D 14
#if	NO_CLNT_SPERRNO
D 11
		clnt_perrno(rc);
D 2
		logdie("Password change failed on %s\n", ypmaster);
E 2
I 2
		logdie("Password change failed on %s", ypinfo->master);
E 11
I 11
			clnt_perrno(rc);
D 12
			logdie("Password change failed on %s", ypinfo->master);
E 12
I 12
			logdie("Password change failed on %s", ypinfo.master);
E 12
E 11
E 2
#else
E 14
I 14
#ifdef	HAS_CLNT_SPERRNO
E 14
D 2
		logdie("Password change failed on %s: %s\n", ypmaster,
E 2
I 2
D 11
		logdie("Password change failed on %s: %s", ypinfo->master,
E 2
			clnt_sperrno(rc));
E 11
I 11
			logdie("Password change failed on %s: %s",
D 12
				ypinfo->master, clnt_sperrno(rc));
E 12
I 12
				ypinfo.master, clnt_sperrno(rc));
I 14
#else
			clnt_perrno(rc);
			logdie("Password change failed on %s", ypinfo.master);
E 14
E 12
E 11
#endif
I 11
			/*NOTREACHED*/
		}
		printf("Timeout talking to NIS master - retrying\n");
		sleep(YPPASSWD_WAIT);
E 11
	}
	/*
D 11
	 * An error was returned from yppasswdd
E 11
I 11
	 * The RPC call suceeded but yppasswdd returned an error code
E 11
	 */
	if (why) {
		logerr("yppasswdd error %d on %s for %s",
D 2
			why, ypmaster, theUser->mpw_name);
E 2
I 2
D 12
			why, ypinfo->master, theUser->mpw_name);
E 12
I 12
			why, ypinfo.master, theUser->mpw_name);
E 12
E 2
		if (why == 1)
D 2
			die(yperrmsg,  ypdomain, ypmaster);
E 2
I 2
D 12
			die(yperrmsg,  ypinfo->domain, ypinfo->master);
E 12
I 12
			die(yperrmsg,  ypinfo.domain, ypinfo.master);
E 12
E 2
		else
D 2
			logdie("Password change failed.");
E 2
I 2
			logdie("Password change failed");
E 2
	}
I 19
#ifdef  HAS_SECURE_RPC
D 34
	if (SecurityLevel == sec_sunC2)
		update_rpc_key(theUser, theUser->password);
E 34
I 34
	if (svc->SecurityLevel == sec_sunC2)
		update_rpc_key(theUser, zdecrypt(theUser->password));
E 34
#endif
D 31

E 19
D 17
#endif	/* DEBUG */
E 17
I 17
#endif	/* DEBUG_NOEXEC */
E 31
E 17
}

D 3
/*
D 2
 *	ypwhich - Find YP configuration.
 *
 *	Returns:
 *		is_yp_master if we are the master
 *		is_yp_client if we are not the master
 *		yp_not_running if there is no master
 */

enum ypstatus
ypwhich(map, domain, master)
char	*map,		/* Name of YP map to find master of */
	**domain,	/* Where to stash pointer to yp domainname */
	**master;	/* Where to stash pointer to yp master name */
{
	struct hostent	*hinfo;
	char	hostname[MAXHOSTNAMLEN];	/* Our host name */

	if (yp_get_default_domain(domain))
		return(yp_not_running);		/* Assume no YP running */

	if (yp_master(*domain, map, master))
		return(yp_not_running);		/* Assume no YP running */
	/*
	 * Compare my host name and the YP master's host name.
	 * Use gethostbyname() to return the fully qualified form so that
	 * a string compare can be done.
	 */
	(void) gethostname(hostname, sizeof(hostname));
	if (INDEX(hostname, '.') == 0) {
		if ((hinfo = gethostbyname(hostname)) == 0)
			logdie("Cannot get gethostbyname for self.\n");
		(void) strcpy(hostname, hinfo->h_name);
	}
	if (INDEX(*master, '.') == 0) {
		static char	ypmaster_f[MAXHOSTNAMLEN];

		if ((hinfo = gethostbyname(*master)) == 0)
			logdie("Cannot gethostbyname for ypmaster.\n");
		(void) strcpy(ypmaster_f, hinfo->h_name);
		*master = ypmaster_f;
	}
	return ((strcmp(*master, hostname) == 0) ? is_yp_master : is_yp_client);
}

/*
E 2
 *	An example sh(1) script to update YP password map
 */
static char	*ypcmd =
	"(PATH=/bin:/usr/bin; export PATH; ypdirs='/var/yp /etc/yp'\n\
	for d in $ypdirs; do\n\
		if [ -d $d ]; then\n\
			cd $d; exec /bin/make passwd\n\
		fi\n\
	done\n\
	echo 'passwd: Cannot rebuild YP maps!' 1>&2\n\
	false) >/dev/null &\n";

ypmake()
{
#ifdef	DEBUG
	printf("updateyp: %s", ypcmd);
#else
	if (fork() == 0) {
		(void) setuid(geteuid()); 	/* Get all privs */
		(void) execl("/bin/sh", "sh", "-c", ypcmd, 0);
		_exit(0);
	}
	(void) wait((int *)0);	/* "Wrong" for BSD, right for SYS V */
#endif
}

E 3
D 5
#define	MOD_TOKEN	"YP_LAST_MODIFIED"

E 5
I 5
/*
D 20
 * update_yp_map - Twiddle the DBM files of a YP map
E 20
I 20
D 25
 * get_yp_pw
E 25
I 25
 * get_yp_user
E 25
 *	Look for user in YP passwd map
 * Usage
 *	found = get_pw_yp(char *user, struct mpasswd *where);
 * Returns
 *	1 if <user> found in YP map "passwd.byname"
 *		The user's passwd entry are stored in meta-passwd structure
 *		pointed to by <where>
 *	0 if <user> not found
E 20
 */
public int
I 20
D 25
get_yp_pw(name, mp)
E 25
I 25
get_yp_user(name, mp)
E 25
D 23
	const char	*name;	/* Name of user to lookup */
E 23
I 23
	char	*name;	/* Name of user to lookup */
E 23
	struct mpasswd	*mp;	/* Where to stash the data */
{
	struct passwd	*pwy;		/* ACME Scratch Storage */
	int	len;			/* ACME Scratch Storage */
	char	*val,			/* ACME Scratch Storage */
		*db;			/* ACME Scratch Storage */
	struct pw_opaque	*opdata = mp->opaque;

I 30
	if (ypinfo.status == yp_not_running) {
		debug(DB_LOOKUP, "get_yp_user: NIS not active\n");
		return(0);
	}
E 30
D 25
	debug(DB_LOOKUP, "get_yp_pw: look in NIS map '%s'\n", PASSWD_BYNAME);
E 25
I 25
	debug(DB_LOOKUP, "get_yp_user: look in NIS map '%s'\n", PASSWD_BYNAME);
E 25
	if (yp_match(ypinfo.domain, PASSWD_BYNAME, name, strlen(name), &val, &len))
		return(0);
D 25
	debug(DB_LOOKUP, "get_yp_pw: found %s\n", name);
E 25
I 25
	debug(DB_LOOKUP, "get_yp_user: found %s\n", name);
E 25

	if ((db = malloc(len + 2)) == 0)
		logdie("No memory for NIS passwd info.\n");
I 22
#ifdef	HAS_MEMCPY
	(void) memcpy(db, val, len);
#else
E 22
	bcopy(val, db, len);
I 22
#endif
E 22
	db[len] = 0;
	if ((pwy = sgetpwent(db)) == NULL) {
		logerr("Syntax error in NIS pwent (%s)\n", db);
		free(db);
		return(0);
	}
	(void) copypwent(pwy, &mp->pw);
	free(db);
	opdata->sourcePW = srv_yp;
	mp->pws_remote = 1;
	mp->pws_name = "NIS";
	mp->pws_loc = ypinfo.master;
	return(1);
}

/*
 * update_yp_map
 *	Modify the DBM files of a YP map
 * Usage:
 *	result = update_yp_map(char *key-to-change, char *data-to-change,
 *		char *yp-map-name, char *yp-data-directory, int do-push);
 * Returns
 *	1 if DBM database was successfully modified
 *	0 if not
 */
public int
E 20
E 5
D 3
static char *ypdirs[] = {
#ifdef	DEBUG
	"./yp",
#endif
	"/var/yp",
	"/etc/yp",
	0
};

/*
 *	yp_update - update local YP maps
 *
 *	We had better be the master for passwd.by(name/uid)
 */
update_yp_maps(theUser, NewUser, ypdomain)
struct mpasswd	*theUser;
struct passwd	*NewUser;
char		*ypdomain;
E 3
I 3
update_yp_map(mapkey, mapdata, mapname, datadir, push)
D 20
char	*mapkey,
	*mapdata,
	*mapname,
	*datadir;
int	push;
E 20
I 20
D 23
	const char	*mapkey,
E 23
I 23
	char	*mapkey,
E 23
			*mapdata,
			*mapname,
			*datadir;
D 23
	const int	push;
E 23
I 23
	int	push;
E 23
E 20
E 3
{
	DBM	*pwd;		/* DBM data base passwd */
	datum	key,		/* DBM key datum */
		data;		/* DBM data store datum */
D 3
	char	**ypdir;	/* YP data directory */
	char	pwline[512],	/* Password line */
		temp[512],	/* Temp */
		tod[32],	/* Time of day string */
		mapname[MAXPATHLEN]; /* YP map DBM database name */
E 3
I 3
	char	tod[32],	/* Time of day string */
		path[MAXPATHLEN]; /* YP map DBM database name */
E 3
	time_t	now;		/* Right now */

D 3
	/*
	 * Find where the YP maps live
	 */
	for (ypdir = ypdirs; *ypdir; ypdir++) {
		(void) sprintf(mapname, "%s/%s", *ypdir, ypdomain);
		if (access(mapname, 0) == 0) 
			break;
	}
	if (access(mapname, 0) < 0) {
		if (DebugLevel)		/* XXX */
			printf("Cannot find any YP directories\n");
		logerr("Cannot find any YP directory");
		return(0);
	}
E 3
	now = time((time_t *)0);	/* Make the YP timestamp cookie */
	(void) sprintf(tod, "%lu", (u_long )now);

D 3
	(void) sputpwent(NewUser, pwline);	/* Make the password file line */
E 3
I 3
D 4
printf("key <%s> data <%s> map <%s> dir <%s> push %d\n",	/* XXX */
mapkey, mapdata, mapname, datadir, push);			/* XXX */
E 4
E 3
	/*
D 3
	 * Open the paswd.byname map
E 3
I 3
	 * Open the map DBM file
E 3
	 */
D 3
	(void) sprintf(mapname, "%s/%s/%s", *ypdir, ypdomain, PASSWD_BYNAME);
	if ((pwd = dbm_open(mapname, O_RDWR, 0)) == 0) {
		logerr("Cannot open YP map \"%s\"", mapname);
E 3
I 3
	(void) sprintf(path, "%s/%s", datadir, mapname);
	if ((pwd = dbm_open(path, O_RDWR, 0)) == 0) {
D 5
		logerr("Cannot open YP map \"%s\"", path);
E 5
I 5
		logerr("(update_yp_map) Cannot open YP map \"%s\"", path);
E 5
E 3
		return(0);
	}
D 3
#ifdef	DEBUG
	printf("Modifying YP map %s\n", mapname);
#endif
	data.dptr = pwline;
	data.dsize = strlen(pwline);
	key.dptr = NewUser->pw_name;
	key.dsize = strlen(NewUser->pw_name);
E 3
I 3
D 11
	if (DebugLevel) printf("Modifying YP map %s\n", path);
E 11
I 11
D 15
	if (DebugLevel >= DB_UPDATE) {
		printf("Modifying NIS map file \"%s\"\n", path);
		fflush(stdout);
	}
E 15
I 15
	debug(DB_UPDATE, "update_yp_map: Modifying map file \"%s\"\n", path);

E 15
E 11
	data.dptr = mapdata;
	data.dsize = strlen(mapdata);
	key.dptr = mapkey;
	key.dsize = strlen(mapkey);
E 3

D 3
	/* Stash the passwd line */
E 3
I 3
	/* Stash the data */
E 3
	if (dbm_store(pwd, key, data, DBM_REPLACE) < 0) {
		perror("dbm_store (name data)");
D 5
		logerr("dbm_store (name data): %m");
E 5
I 5
D 20
		logerr("(update_yp_map) dbm_store (name data): %m");
E 20
I 20
		logerr("(update_yp_map) dbm_store (name data): %m\n");
E 20
E 5
		dbm_close(pwd);
		return(0);
	}

D 5
	/* Twiddle the YP_LAST_MODIFIED token */
E 5
I 5
	/* Update the YP_LAST_MODIFIED token */
E 5
	key.dptr = MOD_TOKEN;
	key.dsize = strlen(MOD_TOKEN);
	data.dptr = tod;
	data.dsize = strlen(tod);
	if (dbm_store(pwd, key, data, DBM_REPLACE) < 0) {
D 3
		perror("dbm_store (name timestamp)");
		logerr("dbm_store (name timestamp): %m");
E 3
I 3
		perror("dbm_store (timestamp)");
D 5
		logerr("dbm_store (timestamp): %m");
E 5
I 5
D 20
		logerr("(update_yp_map) dbm_store (timestamp): %m");
E 20
I 20
		logerr("(update_yp_map) dbm_store (timestamp): %m\n");
E 20
E 5
E 3
		dbm_close(pwd);
		return(0);
	}
	dbm_close(pwd);
I 19
	ypsync();
E 19
D 3

	/*
	 * Open the passwd.byuid map
	 */
	(void) sprintf(mapname, "%s/%s/%s", *ypdir, ypdomain, PASSWD_BYUID);
	if ((pwd = dbm_open(mapname, O_RDWR, 0)) == 0) {
		logerr("Cannot open YP map \"%s\"", mapname);
		return(0);
E 3
I 3
	if (push) {
I 12
D 20
		/* Could do something to invoke yppush */
E 20
I 20
		/* Could invoke yppush */
E 20
E 12
E 3
	}
I 5
	return(1);
E 5
D 3
#ifdef	DEBUG
	printf("Modifying YP map %s\n", mapname);
#endif
	data.dptr = pwline;
	data.dsize = strlen(pwline);
#ifdef	UIDS_ARE_SIGNED
	(void) sprintf(temp, "%d", NewUser->pw_uid);
#else
	(void) sprintf(temp, "%u", NewUser->pw_uid);
#endif
	key.dptr = temp;
	key.dsize = strlen(temp);

	/* Stash the passwd line */
	if (dbm_store(pwd, key, data, DBM_REPLACE) < 0) {
		perror("dbm_store (uid data)");
		logerr("dbm_store (uid data): %m");
		dbm_close(pwd);
		return(0);
	}

	/* Twiddle the YP_LAST_MODIFIED token */
	key.dptr = MOD_TOKEN;
	key.dsize = strlen(MOD_TOKEN);
	data.dptr = tod;
	data.dsize = strlen(tod);
	if (dbm_store(pwd, key, data, DBM_REPLACE) < 0) {
		perror("dbm_store (uid timestamp)");
		logerr("dbm_store (uid timestamp): %m");
		dbm_close(pwd);
		return(0);
	}
	dbm_close(pwd);

	/*
	 * Now cause a yppush() to be done (or the eqivilant thereof)
	 */
	return(1);
E 3
}
I 3
 
E 3
D 5

struct passwd *
E 5
I 5
D 20
/*
 * ypgetpwnam - Lookup passwd entry in "yppasswd.byname" YP map
 */
D 12
public struct passwd *
E 5
ypgetpwnam(name, ypdomain)
E 12
I 12
public int
get_yp_pw(name, mp)
E 12
D 5
char	*name;
char	*ypdomain;
E 5
I 5
	char	*name;		/* Name of user to lookup */
D 12
	char	*ypdomain;	/* YP domain to look in */
E 12
I 12
	struct mpasswd *mp;	/* */
E 12
E 5
{
D 5
	struct passwd	*pwy;
	static struct passwd	rval;
	int	len;
	char	*val,
		*db;
E 5
I 5
D 12
	static struct passwd	rval;	/* Return data */
E 12
	struct passwd	*pwy;		/* Temp */
	int	len;			/* Temp */
	char	*val,			/* Temp */
		*db;			/* Temp */
I 12
	struct pw_opaque	*opdata = mp->opaque;
E 12
E 5

I 16
	debug(DB_LOOKUP, "get_yp_pw: look in NIS map '%s'\n", PASSWD_BYNAME);
E 16
D 12
	if (yp_match(ypdomain, PASSWD_BYNAME, name, strlen(name), &val, &len))
		return(NULL);
E 12
I 12
	if (yp_match(ypinfo.domain, PASSWD_BYNAME, name, strlen(name), &val, &len))
		return(0);
I 16
	debug(DB_LOOKUP, "get_yp_pw: found %s\n", name);
E 16
E 12

	if ((db = malloc(len + 2)) == 0)
		logdie("No memory for NIS passwd info.\n");
D 12
	bcopy(val, db, len);
E 12
I 12
D 14
	BCOPY(val, db, len);
E 14
I 14
	bcopy(val, db, len);
E 14
E 12
	db[len] = 0;
D 12
	pwy = sgetpwent(db);
	if (pwy == NULL) {
		fprintf(stderr, "Syntax error in NIS pwent (%s)\n", db);
E 12
I 12
	if ((pwy = sgetpwent(db)) == NULL) {
		logerr("Syntax error in NIS pwent (%s)\n", db);
E 12
		free(db);
D 12
		return(NULL);
E 12
I 12
		return(0);
E 12
	}
D 12
	copypwent(pwy, &rval);
E 12
I 12
	(void) copypwent(pwy, &mp->pw);
E 12
	free(db);
D 12
	return(&rval);
E 12
I 12
	opdata->sourcePW = srv_yp;
D 18
	mp->remote = 1;
	mp->where = ypinfo.master;
E 18
I 18
	mp->pws_remote = 1;
	mp->pws_name = "NIS";
	mp->pws_loc = ypinfo.master;
E 18
	return(1);
E 12
I 3
}

E 20
I 12
D 14
#ifndef	OS_SOLARIS_2
E 14
I 14
#ifdef	OS_SUNOS_5
D 19
public void yp_sync()
E 19
I 19
D 20
public void ypsync()
E 20
I 20
public void
ypsync()
E 20
E 19
{
I 20
	/* This code will probably look pretty much the same */
E 20
}
#else
E 14
E 12
D 4
#define	YPTIMEOUT	30
static	struct timeval		udp_timeout = { YPTIMEOUT, 0 };

E 4
I 4
/*
D 5
 *	yp_sync - command local ypserv to flush its caches
E 5
I 5
D 19
 *	yp_sync - command local ypserv to flush its cache
E 19
I 19
D 20
 *	ypsync - command local ypserv to flush its cache
E 19
E 5
 *		so it will pick up the map modifications we've done.
E 20
I 20
 * ypsync 
 *	Command local ypserv to flush its cache so it will pick up
 *	map modifications that have been done.
 * Usage
 *	ypsync();
E 20
 */
E 4
D 19
public void yp_sync()
E 19
I 19
D 20
public void ypsync()
E 20
I 20
public void
ypsync()
E 20
E 19
{
D 5
	struct sockaddr_in	myaddr;
	struct dom_binding	dom;
D 4
	char			localhost[64];
E 4
I 4
	char			localhost[MAXHOSTNAMELEN];
E 4
	enum clnt_stat		rc;
D 4
	int			junk0, junk1;
E 4
I 4
#ifndef	YP_TIMEOUT
#define	YP_TIMEOUT	30
#endif
E 5
I 5
	struct sockaddr_in	myaddr;		/* Local machine address */
	struct dom_binding	dom;		/* */
	char			localhost[MAXHOSTNAMELEN];	/* Local host */
	enum clnt_stat		rc;		/* Call return code */
E 5
	static	struct timeval	yp_timeout = { YP_TIMEOUT, 0 };
E 4

	if (gethostname(localhost, sizeof(localhost))) {
D 4
		logerr("yp_sync cannot get hostname: %m");
E 4
I 4
D 19
		logerr("(yp_sync) cannot get hostname: %m");
E 19
I 19
		logerr("(ypsync) cannot get hostname: %m");
E 19
E 4
		return;
	}
	get_myaddress(&myaddr);
I 27
D 30
#ifdef	HAS_MEMSET
D 29
	bzero((void *)&dom, 0, sizeof(dom));
E 29
I 29
	memset((void *)&dom, 0, sizeof(dom));
E 29
#else
E 27
I 7
D 14
	BZERO((void *)&dom, sizeof(dom));
E 14
I 14
	bzero((void *)&dom, sizeof(dom));
I 27
#endif
E 30
I 30
	zeromem(&dom, sizeof dom);
E 30
E 27
E 14
E 7
D 4
	if (!bind_to_server(localhost, myaddr.sin_addr, &dom, &junk0, &junk1))
E 4
I 4
	dom.dom_server_addr.sin_addr = myaddr.sin_addr;
	dom.dom_server_addr.sin_family = AF_INET;
	dom.dom_server_addr.sin_port = htons((u_short)0);
	dom.dom_server_port = htons((u_short)0);
	dom.dom_socket = RPC_ANYSOCK;
	dom.dom_client = clntudp_create(&dom.dom_server_addr, YPPROG, YPVERS,
		yp_timeout, &dom.dom_socket);
I 7
	/*
	 * Need to suppress this message when client create failed because
	 * there is no local ypserv running
	 */
E 7
	if (dom.dom_client == 0) {
D 19
		logerr("(yp_sync) cannot talk to ypserv, error %s",
E 19
I 19
		logerr("(ypsync) cannot talk to ypserv, error %s",
E 19
			clnt_spcreateerror(""));
		(void) close(dom.dom_socket);
E 4
		return;
D 4
/*
	timeout.tv_sec = YPTIMEOUT;
	timeout.tv_usec = 0;
 */
	rc = clnt_call(dom.dom_client, YPPROC_CLEAR,
		xdr_void, 0, xdr_void, 0, udp_timeout);
	if (rc != RPC_SUCCESS)
		logerr("yp_sync clear local ypserv error %d", rc);
}
#undef	YPTIMEOUT
/*
 *	THIS IS LIFTED STRAIGHT OUT OF 4.1.1 ypxfr and MUST be rewritten
 *	before this code goes anywhere
 */

/*
 * This sets up a udp connection to speak the correct program and version
 * to a NIS server.  vers is set to one of YPVERS or YPOLDVERS to reflect which
 * language the server speaks.
 */
bind_to_server(host, host_addr, pdomb, vers, status)
	char *host;
	struct in_addr host_addr;
	struct dom_binding *pdomb;
	unsigned int *vers;
	int *status;
{
	if (ping_server(host, host_addr, pdomb, YPVERS, status)) {
		*vers = YPVERS;
		return (TRUE);
	} else if (*status == YPPUSH_YPERR) {
		return (FALSE);
	} else {
		if (ping_server(host, host_addr, pdomb, YPOLDVERS, status)) {
			*vers = YPOLDVERS;
			return (TRUE);
		} else {
			return (FALSE);
		}
E 4
	}
D 4
}

/*
 * This sets up a UDP channel to a server which is assumed to speak an input
 * version of YPPROG.  The channel is tested by pinging the server.  In all
 * error cases except "Program Version Number Mismatch", the error is
 * reported, and in all error cases, the client handle is destroyed and the
 * socket associated with the channel is closed.
 */
ping_server(host, host_addr, pdomb, vers, status)
	char *host;
	struct in_addr host_addr;
	struct dom_binding *pdomb;
	unsigned int vers;
	int *status;
{
	enum clnt_stat rpc_stat;
	bool issecure();
	
	pdomb->dom_server_addr.sin_addr = host_addr;
	pdomb->dom_server_addr.sin_family = AF_INET;
	pdomb->dom_server_addr.sin_port = htons((u_short) 0);
	pdomb->dom_server_port = htons((u_short) 0);
	pdomb->dom_socket = RPC_ANYSOCK;

	if (pdomb->dom_client = clntudp_create(&(pdomb->dom_server_addr),
	    YPPROG, vers, /* udp_intertry, */ udp_timeout, &(pdomb->dom_socket )) ) {
		    
		/*
		 * if we are on a c2 system, we should only accept data
		 * from a server which is on a reserved port.
		 */
		if (issecure() &&
		    (pdomb->dom_server_addr.sin_family != AF_INET ||
		    pdomb->dom_server_addr.sin_port >= IPPORT_RESERVED) ) {
			clnt_destroy(pdomb->dom_client);
			close(pdomb->dom_socket);
			(void) logerr("bind_to_server: server is not using a privileged port\n");
			*status = YPPUSH_YPERR;
			return (FALSE);
		}

		rpc_stat = clnt_call(pdomb->dom_client, YPBINDPROC_NULL,
		    xdr_void, 0, xdr_void, 0, udp_timeout);

		if (rpc_stat == RPC_SUCCESS) {
			return (TRUE);
		} else {
			clnt_destroy(pdomb->dom_client);
			close(pdomb->dom_socket);
			
			if (rpc_stat != RPC_PROGVERSMISMATCH) {
				(void) clnt_perror(pdomb->dom_client,
				     "ypxfr: bind_to_server clnt_call error");
			}
			
			*status = YPPUSH_RPC;
			return (FALSE);
		}
	} else {
		logerr("bind_to_server clntudp_create error");
		(void) clnt_pcreateerror("");
		fflush(stderr);
		*status = YPPUSH_RPC;
		return (FALSE);
E 4
I 4
	rc = clnt_call(dom.dom_client, YPBINDPROC_NULL,
D 14
		xdr_void, 0, xdr_void, 0, yp_timeout);
E 14
I 14
		(xdrproc_t )xdr_void, 0, (xdrproc_t )xdr_void, 0, yp_timeout);
E 14
	if (rc == RPC_SUCCESS) {
		rc = clnt_call(dom.dom_client, YPPROC_CLEAR,
D 14
			xdr_void, 0, xdr_void, 0, yp_timeout);
E 14
I 14
			(xdrproc_t )xdr_void, 0, (xdrproc_t )xdr_void,
			0, yp_timeout);
E 14
		if (rc != RPC_SUCCESS)
D 19
			logerr("yp_sync clear local ypserv error %d", rc);
E 19
I 19
			logerr("ypsync clear local ypserv error %d", rc);
E 19
E 4
	}
I 4
	clnt_destroy(dom.dom_client);
I 5
}
I 12
#endif
E 12

I 12
D 14
#if	defined(SUN_SECURITY)
E 14
I 14
#ifdef	SECURE_RPC
E 14
E 12
/*
D 20
 * update_rpc_key - Update the Secure RPC secret key for the user
E 20
I 20
 * Support for SunOS 4.X Secure RPC (used with C2 security)
E 20
 */
D 6
public void update_rpc_keys(theUser, newpw)
E 6
I 6
D 20
public void update_rpc_key(theUser, newpw)
E 6
	struct mpasswd	*theUser;		/* User to change key for */
	char		*newpw;			/* New password for key */
E 20
I 20

/*
 * update_rpc_key
 *	Update the user's Secure RPC secret key
 * Usage
 *	update_rpc_key(struct mpasswd *new-user, char *new-password);
 * Side effects
 *	Changes the private/public key pair in the NIS public key map
 *	or /etc/.rootkey if target user is root.
 * Errors
 *	Returns without changing RPC key on error.
 *	This might not the optimal thing to do.
 */
public void
update_rpc_key(theUser, newpw)
D 23
	const struct mpasswd	*theUser;	/* User to change key for */
	const char		*newpw;		/* New password for key */
E 23
I 23
	struct mpasswd	*theUser;	/* User to change key for */
	char		*newpw;		/* New password for key */
E 23
E 20
{
I 7
D 10
#ifdef	SUN_SHADOW
E 10
I 10
D 12
#ifdef	SUN_SECURITY
E 12
E 10
E 7
D 6
	char	*dom;			/* YP domain */
E 6
	char	sysid[MAXNETNAMELEN+1],	/* Entity netname */
		skey[HEXKEYBYTES + 1],	/* Secret key */
		pkey[HEXKEYBYTES + 1],	/* Public key */
		cdat[HEXKEYBYTES + KEYCHECKSUMSIZE + 1], /* New secret key */
		pdat[(HEXKEYBYTES*2) + KEYCHECKSUMSIZE + 4];
					/* New publickey table entry */
	int	rc;		/* Temp */
	struct pw_opaque	*xp = theUser->opaque;	/* Other stuff */

D 6
	if (yp_get_default_domain(&dom))
		return;

E 6
	if (theUser->mpw_uid) {		/* Changing a user's secret key */
D 20
		char	*kdata, *p;
E 20
I 20
		char	*kdata,
			*p;
E 20
		int	len;

D 6
		user2netname(sysid, theUser->mpw_uid, dom);
		if (yp_match(dom, PKEY_MAP, sysid, strlen(sysid), &kdata, &len))
			return;		/* No key for this user */
E 6
I 6
		user2netname(sysid, theUser->mpw_uid, xp->dbinfo.ypinfo->domain);
		if (yp_match(xp->dbinfo.ypinfo->domain, PKEY_MAP,
			sysid, strlen(sysid), &kdata, &len))
				return;		/* No key for this user */
E 6
		kdata[len] = 0;
D 6
/*		printf("secret key <%s> = <%s>\n", sysid, kdata);/* XXX */
E 6
D 14
		if (!(p = INDEX(kdata, ':'))) {
E 14
I 14
D 19
		if (!(p = index(kdata, ':'))) {
E 19
I 19
		if (!(p = strchr(kdata, ':'))) {
E 19
E 14
D 6
			logerr("(update_rpc_keys) Malformed key entry %s <%s>",
				sysid, kdata);
E 6
I 6
			logerr("Malformed publickey %s <%s>", sysid, kdata);
E 6
			free(kdata);
			return;
		}
		bcopy(kdata, pkey, HEXKEYBYTES);
		pkey[HEXKEYBYTES] = 0;
		bcopy(++p, skey, HEXKEYBYTES);
		skey[HEXKEYBYTES] = 0;
		free(kdata);
D 34
		if (xdecrypt(skey, theUser->password) == 0) {
E 34
I 34
		if (xdecrypt(skey, zdecrypt(theUser->password)) == 0) {
E 34
			/* Probable that (network password != login password) */
			printf("Use \"chkey\" to change your RPC password.\n");
			return;
		}
	} else {			/* Changing the root's secret key */
D 20
		char	*kdata, *p;
		int	len, fd;
E 20
I 20
		char	*kdata,
			*p;
		int	len,
			fd;
E 20

D 20
		/* Changing the root's secret key */
E 20
		getnetname(sysid);
D 6
		if (yp_match(dom, PKEY_MAP, sysid, strlen(sysid), &kdata, &len)) 
			return;
E 6
I 6
		if (yp_match(xp->dbinfo.ypinfo->domain, PKEY_MAP,
			sysid, strlen(sysid), &kdata, &len)) 
				return;
E 6
		kdata[len] = 0;
D 6
/*		printf("root secret key <%s> = <%s>\n", sysid, kdata);/* XXX */
E 6
D 14
		if (!(p = INDEX(kdata, ':'))) {
E 14
I 14
D 19
		if (!(p = index(kdata, ':'))) {
E 19
I 19
		if (!(p = strchr(kdata, ':'))) {
E 19
E 14
D 6
			logerr("(update_rpc_keys) Malformed key entry %s <%s>",
				sysid, kdata);
E 6
I 6
			logerr("Malformed publickey %s <%s>", sysid, kdata);
E 6
			free(kdata);
			return;	
		}
		bcopy(kdata, pkey, HEXKEYBYTES);
		pkey[HEXKEYBYTES] = 0;
		free(kdata);
		if ((fd = open(ROOT_KEY, 0)) < 0) {
D 6
			logerr("(update_rpc_keys) Cannot get root key: %m");
E 6
I 6
			logerr("Cannot get root key: %m");
E 6
			return;
		}
		if (read(fd, skey, HEXKEYBYTES) != HEXKEYBYTES) {
			(void) close(fd);
			return;
		}
		(void) close(fd);
		skey[HEXKEYBYTES] = 0;
	}
	/*
	 * Make a new secret key and stuff the whole thing back into the
	 * publickey YP map.
	 */
	bcopy(skey, cdat, HEXKEYBYTES);
	bcopy(skey, cdat + HEXKEYBYTES, KEYCHECKSUMSIZE);
	cdat[HEXKEYBYTES + KEYCHECKSUMSIZE] = 0;
	xencrypt(cdat, newpw);
	(void) sprintf(pdat, "%s:%s", pkey, cdat);
D 6
	printf("New key for <%s> is <%s>\n", sysid, pdat);	/* XXX */
E 6
I 6
D 11
	if (DebugLevel)
		printf("New key for <%s> is <%s>\n", sysid, pdat);
E 11
E 6

I 11
D 15
	if (DebugLevel >= DB_UPDATE) {
		printf("New key for <%s> is <%s>\n", sysid, pdat);
		fflush(stdout);
	}
E 15
I 15
	debug(DB_UPDATE, "update_rpc_key: New key for <%s> is <%s>\n",
		sysid, pdat);
E 15
E 11
D 6
	switch (xp->dbinfo.ypinfo->status) {
	case is_yp_master:
		update_yp_map(sysid, pdat, PKMAP, xp->dbinfo.ypinfo->data, 0);
		break;

	case is_yp_client:
		if (rc = yp_update(dom, PKMAP, YPOP_STORE,
			sysid, strlen(sysid), pdat, strlen(pdat))) {
/*				printf("(update_rpc_keys) cannot store secret key: error %d\n", rc);	/* XXX */
				logerr("(update_rpc_keys) cannot store secret key: error %d", rc);
				return;
E 6
I 6
	/*
	 * Use the YP interface to update the publickey database.
	 * Must do this as the real user, not root.
	 */
	if (fork() == 0) {
		(void) setuid(getuid());
		if (rc = yp_update(xp->dbinfo.ypinfo->domain,
			PKEY_MAP, YPOP_STORE, sysid, strlen(sysid),
			pdat, strlen(pdat))) {
				printf("Error %d updating secret key\n", rc);
				logerr("Error %d updating secret key for %s",
					rc, sysid);
		} else {
			printf("Updated secret key for %s on %s\n",
				theUser->mpw_name, xp->dbinfo.ypinfo->master);
E 6
		}
D 6
		break;
E 6
I 6
		exit(0);
E 6
	}
D 6
	printf("Set new secret key for %s on %s\n",
		theUser->mpw_name, xp->dbinfo.ypinfo->master);
E 6
I 6
	(void) wait((int *)0);
I 12
}
I 20

E 20
I 13
/*
D 20
 *	check_rpc_key -
 *		Lookup Secure RPC key for user and check against password
E 20
I 20
 * check_rpc_key -
 *	Lookup Secure RPC key for user and check against password
E 20
 *
D 20
 *	Returns:
 *		1 if key found and password matches
 *		0 if key found and password does not match
 *		-1 if no key found
E 20
I 20
 * Usage
 *	match = check_rpc_key(struct mpasswd *user, char *password);
 * Returns
 *	1 if key found and password matches
 *	0 if key found and password does not match
 *	-1 if no key found
E 20
 */
public int
check_rpc_key(theUser, password)
D 20
	struct mpasswd	*theUser;		/* User to check RPC key */
	char	*password;			/* Password (plain) */
E 20
I 20
D 23
	const struct mpasswd	*theUser;	/* User to check RPC key */
	const char	*password;		/* Password (plain) */
E 23
I 23
	struct mpasswd	*theUser;	/* User to check RPC key */
	char	*password;		/* Password (plain) */
E 23
E 20
{
	char	sysid[MAXNETNAMELEN+1],	/* Entity netname */
		skey[HEXKEYBYTES + 1];	/* Secret key */
	struct pw_opaque	*xp = theUser->opaque;	/* Other stuff */
	char	*kdata, *p;
	int	len;

	if (theUser->mpw_uid)
		user2netname(sysid, theUser->mpw_uid,
			xp->dbinfo.ypinfo->domain);
	else
		getnetname(sysid);
	if (yp_match(xp->dbinfo.ypinfo->domain, PKEY_MAP,
		sysid, strlen(sysid), &kdata, &len))
			return(-1);		/* No key for this user */
	kdata[len] = 0;
D 14
	if (!(p = INDEX(kdata, ':'))) {
E 14
I 14
D 19
	if (!(p = index(kdata, ':'))) {
E 19
I 19
	if (!(p = strchr(kdata, ':'))) {
E 19
E 14
		logerr("Malformed publickey %s <%s>", sysid, kdata);
		free(kdata);
		return(-1);
	}
	bcopy(++p, skey, HEXKEYBYTES);
	skey[HEXKEYBYTES] = 0;
	free(kdata);
	return (xdecrypt(skey, password) != 0);
}
E 13
E 12
I 7
D 9
#endif
E 9
I 9
D 10
#endif	/* SUN_SHADOW */
E 10
I 10
D 14
#endif	/* SUN_SECURITY */
E 14
I 14
#endif	/* SECURE_RPC */
E 14
I 12

D 14
#ifdef	OS_SOLARIS_2
E 14
I 14
#ifndef	HAS_XDR_PASSWD
I 20
/*
 * xdr_yppasswd
 *	RPC passwd XDR encoding routine for those systems which
 *	don't have this in libc or librpcsvc.
 *	Called by YP internal routines only.
 * Usage
 *	xdr_yppasswd(XDR *xdr-data, struct yppasswd *yp);
 */
E 20
E 14
private bool_t
xdr_yppasswd(xdrp, pw)
	XDR	*xdrp;
	struct yppasswd *pw;
{
	if (	xdr_wrapstring(xdrp, &pw->oldpass)  &&
		xdr_wrapstring(xdrp, &pw->newpw.pw_name) &&
		xdr_wrapstring(xdrp, &pw->newpw.pw_passwd) &&
I 29
#ifdef	HAS_XDR_UID
E 29
		xdr_uid_t(xdrp, &pw->newpw.pw_uid) &&
		xdr_gid_t(xdrp, &pw->newpw.pw_gid) &&
I 29
#else
		xdr_int(xdrp, &pw->newpw.pw_uid) &&
		xdr_int(xdrp, &pw->newpw.pw_gid) &&
#endif
E 29
		xdr_wrapstring(xdrp, &pw->newpw.pw_gecos) &&
		xdr_wrapstring(xdrp, &pw->newpw.pw_dir) &&
		xdr_wrapstring(xdrp, &pw->newpw.pw_shell))
			return(TRUE);
	return(FALSE);
E 12
E 10
E 9
E 7
E 6
E 5
E 4
E 3
}
I 8
D 12
#endif
E 12
I 12
D 14
#endif	/* OS_SOLARIS_2 */
E 14
I 14
#endif
E 14

I 20
/*
 * yp_password
 *	Get the password for YP use
 *	This routine is called from chfn() and chsh() in order to obtain
 *	the password(s) needed for remote YP updates later on.
 * Usage
 *	yp_password(struct mpasswd *user);
 */
E 20
I 19
public void
yp_password(theUser)
	struct mpasswd	*theUser;
{
	/*
	 * In order to use the RPC interface to replace a passwd entry,
	 * the plaintext of the current password is required.
	 */
	init_yp();

	if (ypinfo.status != is_yp_client) return;	/* Not a YP client */
	if (theUser->pws_remote == 0) return;		/* PW is local */

	if (theUser->mpw_passwd[0]) {
D 35
		char	prompt[TMPBUFSIZ];
E 35
I 35
		char	prompt[TMPBUFSIZ],
			ptmp[TMPBUFSIZ];
E 35
I 33
		struct	pw_svc *svc = get_pwsvc();
E 33

		(void) sprintf(prompt,
			"Password for %s: ", theUser->mpw_name);
D 35
		get_password(prompt, theUser->mpw_passwd,
			theUser->password, sizeof(theUser->password));
E 35
I 35
		get_password(prompt, theUser->mpw_passwd, ptmp, sizeof(ptmp));
E 35
#ifdef	HAS_SECURE_RPC
D 33
		if (svc_SecurityLevel == sec_sunC2) {
E 33
I 33
		if (svc->SecurityLevel == sec_sunC2) {
E 33
			char	*rpcpw;

D 35
			rpcpw = theUser->password;
E 35
I 35
			rpcpw = ptmp
E 35
			while (!check_rpc_key(theUser, rpcpw)) {
D 28
				rpcpw = getpass("Secure RPC password: ");
E 28
I 28
				rpcpw = np_getpass("Secure RPC password: ");
E 28
			}
D 23
			(void) strcpy(theUser->key, rpcpw);
E 23
I 23
D 35
			if (rpcpw) (void) strcpy(theUser->key, rpcpw);
E 35
I 35
			if (rpcpw)
				(void) strcpy(theUser->key, rpcpw);
E 35
E 23
		}
#endif
I 34
D 35
		zncrypt(theUser->password);
E 35
I 35
		strcpy(theUser->password, zncrypt(ptmp));
E 35
E 34
	}
}

E 19
D 14
#endif	/* YP_SUPPORT */
E 14
I 14
#endif	/* USE_NIS */
E 14

E 12
E 8
D 2

#endif	/* YP_PASSWD */
E 2
I 2
/* End %M% */
E 2
E 1
