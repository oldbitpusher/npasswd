h41940
s 00013/00008/00473
d D 1.33 00/01/17 18:18:17 clyde 33 32
c 1. Fix SCOPY() macro
c 2. Don't mess with password aging if not changing password
e
s 00017/00011/00464
d D 1.32 98/10/13 15:40:16 clyde 32 31
c 1. Allow local changes on non-YP master (unless SunOS 4 system)
c 2. Fix passwd temp size check
c 3. Cleanup some error messages
c 4. Add SHORT_FILE_WARN define to control short temp file behavior
e
s 00002/00000/00473
d D 1.31 98/07/20 14:07:37 clyde 31 30
c Fix problem with pw_age element
e
s 00001/00001/00472
d D 1.30 98/06/30 15:17:49 clyde 30 29
c Change pws_name
e
s 00001/00001/00472
d D 1.29 98/06/30 15:13:25 clyde 29 28
c Fix symlink check
e
s 00017/00015/00456
d D 1.28 98/06/23 10:59:15 clyde 28 27
c Change compile-time debug include trigger
e
s 00075/00010/00396
d D 1.27 98/04/21 11:02:26 clyde 27 26
c 1. Add HP-UX password aging contrib code
c 2. Be more paranoid about mode & ownership of passwd files
e
s 00002/00000/00404
d D 1.26 97/09/23 12:27:15 clyde 26 25
c Wrap use of mpw_comment in #ifdef PWCOMMENT
e
s 00002/00000/00402
d D 1.25 97/05/23 11:13:20 clyde 25 24
c Ifdef PWQUOTA use of pw_quota
e
s 00012/00012/00390
d D 1.24 96/12/17 11:02:36 clyde 24 23
c get_local_pw -> get_local_user; update_local_pw -> put_local_user
e
s 00009/00008/00393
d D 1.23 96/08/29 13:04:03 clyde 23 22
c 1. Remove 'const' declarations (too much compiler pain)
c 2. Honor -l switch on SunOS4
e
s 00122/00042/00279
d D 1.22 96/08/13 15:44:31 clyde 22 21
c 1. Change declaration of passwd slop tolerance
c 2. Change how passwd slop tolerance is used
c 3. Use change flags for selective field updates
c 4. Add lots of comments
c 5. Fix many bugs
e
s 00032/00023/00289
d D 1.21 96/08/06 14:14:08 clyde 21 20
c beta 3 cycle 1 checkin
e
s 00014/00013/00298
d D 1.20 96/04/03 14:38:13 clyde 20 19
c Reflect new mpasswd structure element names
e
s 00006/00015/00305
d D 1.19 96/03/27 09:28:58 clyde 19 18
c Use debug() routine for messages
e
s 00020/00034/00300
d D 1.18 95/04/05 16:20:12 clyde 18 17
c Beta 3 development checkin
e
s 00002/00002/00332
d D 1.17 94/11/03 15:18:36 clyde 17 16
c Use link instead of rename to save password file
e
s 00003/00000/00331
d D 1.16 94/10/24 10:31:49 clyde 16 15
c Bug fix
e
s 00128/00320/00203
d D 1.15 94/09/28 16:13:47 clyde 15 14
c Development checkin - lots of changes
e
s 00002/00002/00521
d D 1.14 94/06/20 14:01:30 clyde 14 13
c Fix typos 
e
s 00006/00003/00517
d D 1.13 94/06/20 13:49:46 clyde 13 12
c Cleanup debugging statements
e
s 00037/00000/00483
d D 1.12 94/05/17 15:31:17 clyde 12 11
c 1. Put password aging information into returned mpasswd structure
c 2. Update password aging information when rewriting files
e
s 00274/00510/00209
d D 1.11 94/03/31 17:44:48 clyde 11 10
c Development checkin:
c 	Process service order when doing lookups
c 	Move lots of stuff around
e
s 00043/00032/00676
d D 1.10 94/03/17 15:48:27 clyde 10 9
c Rewrite signal handling
e
s 00004/00001/00704
d D 1.9 94/03/15 18:51:29 clyde 9 8
c Add default extra password file location for Ultrix and OSF/1
e
s 00015/00006/00690
d D 1.8 94/03/15 11:09:03 clyde 8 7
c Fix ifdef DBM_PASSWD use
e
s 00067/00026/00629
d D 1.7 94/03/01 15:26:06 clyde 7 6
c Development checkin:
c 1. Fix update code
c 2. Fix dbm file update code
e
s 00002/00000/00653
d D 1.6 93/12/20 09:20:27 clyde 6 5
c Development checkin
e
s 00029/00016/00624
d D 1.5 93/12/16 11:04:10 clyde 5 4
c Development checkin
e
s 00037/00030/00603
d D 1.4 93/12/13 12:56:46 clyde 4 3
c Make adjunct password file handling work
e
s 00076/00101/00557
d D 1.3 93/07/12 15:05:51 clyde 3 2
c 1. Gut pw_permission().
c 2. Clean up all logdie() calls.
c 3. Change YP configuration processing.
e
s 00040/00055/00618
d D 1.2 93/07/12 11:08:19 clyde 2 1
c 1. Remove password checking routine
c 2. Add field change flags
c 3. Treat password arg to pw_replace() as already encrypted
e
s 00673/00000/00000
d D 1.1 93/07/12 09:18:16 clyde 1 0
c date and time created 93/07/12 09:18:16 by clyde
e
u
U
f e 0
t
T
I 1
/*
D 15
 *	pw_yp - Routines for dealing with SUN Yellow Pages password files
 *
 *	This code can update local password file, can cause rebuilding of
 *	local YP maps and can use yppasswdd(8) to change YP passwords.
 *
 *	Must be linked with -lrpcsvc
E 15
I 15
D 18
 * pw_passwd.c - Backend routines for local password files.
E 18
I 18
D 22
 *	pwm_local.c - Backend routines for local password files.
E 22
I 22
 * %M%
 *	Method routines for local password files
 *
 * Exported routines
D 24
 *	get_local_pw()
 *	update_local_pw()
E 24
I 24
 *	get_local_user()
 *	put_local_user()
E 24
 *
 * Exported variables
 *	PasswdTolerance
 *
 * Imported variables
 *	ypinfo (from pwm_nis.c)
 *
 * Private routines
 *	update_dbm_passwd()
 *
 * Compilation flags
 *	cc -I.. -I../Common ...
E 22
E 18
E 15
 */
D 15

E 15
#include "npasswd.h"
D 15
#include "pw_defs.h"
#include "pw_nis.h"
E 15
I 15
#include "pwm_defs.h"
I 18
#include "passwdtab.h"
E 18
E 15

D 11
#if	SUN_SHADOW
# include <sys/label.h>
# include <sys/audit.h>
# include <pwdadj.h>
#endif

D 10
#if	S5_SHADOW
E 10
I 10
#ifdef	S5_SHADOW
E 10
# include <shadow.h>
#endif

#if	ULTRIX_SHADOW
# include <auth.h>
D 7
# include <time.h>
E 7
I 7
D 8
# include <ndbm.h>
E 8
E 7
#endif

E 11
I 7
D 15
#ifndef	PASSWD_FILE
# define	PASSWD_FILE	"/etc/passwd"
#endif
 
#ifndef	PASSWD_SAVE
# define	PASSWD_SAVE	"/etc/opasswd"
#endif

#ifndef	PASSWD_TEMP
# define	PASSWD_TEMP	"/etc/ptmp"
#endif

#ifndef	PASSWD_LOCK
# define	PASSWD_LOCK	"/etc/passwd.ptmp"
#endif

#ifndef	PASSWD_CONFIG
# define	PASSWD_CONFIG	"/usr/adm/passwd.conf"
#endif

#define	PASSWD_MODE	0444
I 11
#define	PASSWD_SIZE_SLOP	128	/* Move to npasswd.h */
E 11

E 15
D 11
/*
 * Names of NIS maps where passwd information is stored
 */
#define	PASSWD_BYNAME	"passwd.byname"
#define	PASSWD_BYUID	"passwd.byuid"
#define	ADJUNCT_BYNAME	"passwd.adjunct.byname"

#define	PASSWD_SIZE_SLOP	128

E 11
E 7
#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu)";
#endif

I 15
D 21
#define	PASSWD_FILE_MODE	0444
#define	PASSWD_SIZE_SLOP	128
E 21
I 21
D 22
public int	passwd_tolerance = 128;
E 22
I 22
/*
 * Size difference tolerated between new and old passwd files
 * Can be set in the configuration file
 */
Config_Value int	PasswdTolerance = PASSWD_DIFF_OK;
E 22
E 21

E 15
D 3
static int	ypstatus;	/* YP status */
static char	*ypmaster,	/* Name of the YP master */
		*ypdomain;	/* YP domain name */

E 3
D 18
/*
 * List of possible locations for the password file
 */
static struct passwd_files pwfiles[] = {
D 5
#ifdef	DEBUG
E 5
I 5
#ifdef	DEBUG_FILES
E 5
D 15
	{ "./etc_passwd", "./etc_ptmp", "./etc_opasswd", "./passwd_lock", },
E 15
I 15
	{ "./etc_passwd", "./etc_ptmp", "./etc_opasswd", "./passwd_lock" },
E 15
#endif
D 15
	{ PASSWD_FILE, PASSWD_TEMP, PASSWD_SAVE, PASSWD_LOCK, },
E 15
I 15
#ifdef	XPASSWD_FILE
	{ XPASSWD_FILE, XPASSWD_TEMP, XPASSWD_SAVE, XPASSWD_LOCK },
#endif
E 15
I 9
#if	defined(OS_ULTRIX_4) || defined(OS_DEC_OSF_1)
D 15
	{ "/var/yp/src/passwd", "/var/yp/src/ptmp", "/var/yp/src/opasswd",  0 },
E 15
I 15
	{ "/var/yp/src/passwd", "/var/yp/src/ptmp", "/var/yp/src/opasswd", 0 },
E 15
#endif
I 15
#if	defined(OS_SUNOS_4)
	{ "/etc/passwd", "/etc/ptmp", "/etc/opasswd", "/etc/passwd.ptmp" },
#else
E 15
E 9
	{ "/etc/passwd", "/etc/ptmp", "/etc/opasswd",  0 },
I 15
#endif
E 15
	{ 0 }
};
E 18
D 11

/*
 * List of possible places for the shadow file
 */
struct passwd_files shadowfiles[]  = {
D 5
#ifdef	DEBUG
	{ "./etc_shadow", "./etc_stmp", "./etc_oshadow", },
E 5
I 5
#ifdef	DEBUG_FILES
	{ "./etc_shadow", "./etc_stmp", "./etc_oshadow", 0 },
E 5
#endif
#if	S5_SHADOW
	{ "/etc/shadow", "/etc/stmp", "/etc/oshadow",  0 },
#endif
#if	SUN_SHADOW
	{ "/etc/security/passwd.adjunct", "/etc/security/ptmpa",
	  "/etc/security/opadjunct", 0 },
#endif
	{ 0 }
};

E 11
I 3
D 15
private struct ypinfo	ypinfo;
E 15
D 21

E 21
I 15
D 18
#ifdef	YP_SUPPORT
E 18
I 18
#ifdef	USE_NIS
E 18
D 22
extern struct ypinfo	ypinfo;
E 22
I 22
extern struct ypinfo	ypinfo;		/* YP configuration (from pwm_nis.c) */
E 22
#endif
E 15
D 5

E 5
E 3
D 11
/*
 *	pw_initialize - set up
 */
D 5
void pw_initialize(argc, argv)
E 5
I 5
public void pw_initialize(argc, argv)
E 5
int	argc;			/* NOTUSED */
char	**argv;			/* NOTUSED */
{
D 3
	struct	passwd_files *whichpw;
E 3
I 3
	struct passwd_files *whichpw;
E 11
D 5
	struct ypinfo *ypi;
E 5
E 3

I 22
/*
D 24
 * get_local_pw
E 24
I 24
 * get_local_user
E 24
 *	Look for user in local password files
 * Usage
D 24
 *	found = get_local_pw(char *user, struct mpasswd *where);
E 24
I 24
 *	found = get_local_user(char *user, struct mpasswd *where);
E 24
 * Returns
 *	1 if <user> was found if any of the password files listed
 *		in the etc_passwd table (in passwdtab.h).
 *		The user's passwd & shadow entries are stored in meta-passwd
 *		structure pointed to by <where>.
 *	0 if <user> not found
 */
E 22
I 7
D 11
#if	0
E 7
D 3
	ypstatus = ypwhich(PASSWD_BYNAME, &ypdomain, &ypmaster);
E 3
	/*
	 * Find the password file.
	 */
	for (whichpw = pwfiles; whichpw->pwfile; whichpw++) {
		if (access(whichpw->pwfile, 0) == 0)
			break;
	}
	/*
	 * There should always be a local /etc/passwd, even if it is
	 * not being used.  I consider that to be a fundamental constant
	 * of UNIX, like "root" having uid 0.
	 */
	if (access(whichpw->pwfile, 0) < 0)
D 3
		logdie( "Cannot find any password file.\n");
E 3
I 3
		logdie("Cannot find any password file");
D 7

E 7
I 7
#endif
E 7
	BZERO((char *)&ypinfo, sizeof(ypinfo));
	ypinfo.status = yp_not_running;
#ifdef	YP_PASSWD
D 5
	/* Get NIS configuration information */
	ypi = ypwhich(PASSWD_BYNAME);
	ypinfo.status = ypi->status;
	ypinfo.domain = copystr(ypi->domain);
	ypinfo.master = copystr(ypi->master);
E 5
I 5
	ypwhich(PASSWD_BYNAME, &ypinfo);
E 5
#endif
E 3
}

/*
 *	pw_getuserbyname - get paswd information by user name.
 *
 *	Returns: Pointer to mpasswd sturcture if <name> found
 *		 NULL otherwise
 */
struct mpasswd *
pw_getuserbyname(name)
char	*name;		/* User name */
E 11
I 11
D 15
private struct passwd_files *
getpwlocal(name, pwptr)
	char		*name;
	struct passwd	**pwptr;
E 15
I 15
public int
D 24
get_local_pw(name, mp)
E 24
I 24
get_local_user(name, mp)
E 24
D 22
	char	*name;
E 22
I 22
D 23
	const char	*name;
E 23
I 23
	char	*name;
E 23
E 22
	struct mpasswd	*mp;
E 15
E 11
{
D 11
	struct passwd	*userp,		/* Info from getpwnam() */
			*localpw,	/* Info from local pw file */
			*yppw;		/* Info from YP map */
	static struct passwd	userd,		/* Info from getpwnam() */
			locald,		/* Info from local pw file */
			ypd;		/* Info from YP map */
E 11
I 11
D 15
	struct passwd *pwinfo = NULL;
E 11
	struct passwd_files *whichpw;	/* Passwd file search */
E 15
I 15
	struct passwd_files *whichpw;
	struct passwd	*pwinfo = NULL;
	char	localhost[MAXHOSTNAMLEN];
	struct pw_opaque	*opdata = (struct pw_opaque *)mp->opaque;
E 15
D 11
	struct mpasswd	*rval;		/* Return mpasswd record */
	struct pw_opaque *xv;		/* Method opaque data block */
	static char	localhost[MAXHOSTNAMLEN];
E 11

D 11
	if ((userp = getpwnam(name)) == NULL)
		return(NULL);

	rval = (struct mpasswd *)calloc(sizeof(*rval), 1);
	if (rval == NULL)
D 3
		logdie( "Cannot allocate memory for mpasswd data\n");
E 3
I 3
		logdie("Cannot allocate memory for mpasswd data");
E 3

	xv = (struct pw_opaque *)calloc(sizeof(*xv), 1);
	if (xv == NULL)
D 3
		logdie( "Cannot allocate memory for opaque data\n");
E 3
I 3
		logdie("Cannot allocate memory for opaque data");
E 3
	rval->opaque = (void *)xv;

	xv->magic = OPAQUE_MAGIC;
	xv->shadow = sl_none;
	xv->source = pl_local;
I 5
	xv->dbinfo.ypinfo = &ypinfo;
E 5

	(void) gethostname(localhost, MAXHOSTNAMLEN);
	userp = copypwent(userp, &userd);
#ifdef	SUN_SHADOW
E 11
	/*
D 11
	 * If the password is "##username", then its in the adjunct file
	 */
	if (strncmp(userp->pw_passwd, "##", 2) == 0 &&
	    strcmp(&userp->pw_passwd[2], name) == 0) {
		struct passwd_adjunct *ap;
I 4
		struct passwd_files *adj;
		struct passwd_Xadjunct *xp;
		FILE *af;
E 4
D 2
		extern struct passwd_adjunct *fgetapwent();
E 2

		/*
		 * We are running as root, so we can get the
		 * encrypted password from the adjunct file.
		 */
		if ((ap = getpwanam(name)) == NULL)
D 3
			logdie( "Cannot get password for %s from adjunct.\n",
E 3
I 3
			logdie("Cannot get password for %s from adjunct",
E 3
				name);
		if (DebugLevel)		/* XXX */
			printf("pw_getuserbyname: adjunct pw for %s\n", name);

D 5
		userp->pw_passwd = copystr(ap->pwa_passwd);
E 5
I 5
		xv->shadowpw = userp->pw_passwd = copystr(ap->pwa_passwd);
E 5
I 2
		if (ap->pwa_age && *ap->pwa_age)
			userp->pw_age = copystr(ap->pwa_age);
E 2
D 4
		xv->shadow = sl_yp;
E 4

D 4
		/*
		 * If on a YP client and the -l option given, look in the
		 * the local adjunct file for an override or YP stub.
		 */
D 3
		if (ypstatus == is_yp_client && CommandLineOption['l']) {
E 3
I 3
		if (ypinfo.status == is_yp_client && CommandLineOption['l']) {
E 3
			struct passwd_files *adj;
I 2
			struct passwd_Xadjunct *xp;
E 2
			FILE *af;
E 4
I 4
		if (ypinfo.status == is_yp_client)
			xv->shadow = sl_yp;
E 4

D 4
			for (adj = shadowfiles; adj->pwfile; adj++) {
				if (access(adj->pwfile, 0) == 0)
					break;
			}
			/* There should always be an adjunct file */
			if (access(adj->pwfile, 0) < 0)
E 4
I 4
		/* Look for the local adjunct file */

		for (adj = shadowfiles; adj->pwfile; adj++) {
			if (access(adj->pwfile, 0) == 0)
				break;
		}
		/* There should always be an adjunct file
		 * unless this is an NIS client
		 */
		if (access(adj->pwfile, 0) < 0) {
			if (ypinfo.status != is_yp_client)
E 4
D 2
				logdie( "Cannot find any adjunct file.\n");
E 2
I 2
D 3
				logdie("Cannot find any adjunct file.\n");
E 3
I 3
				logdie("Cannot find any adjunct file");
I 4
			else
				goto adjunct_done;
		}
		if ((af = fopen(adj->pwfile, "r")) == NULL)
			logdie("Cannot open adjunct file \"%s\"",
				adj->pwfile);
E 4
E 3
E 2

D 4
			if ((af = fopen(adj->pwfile, "r")) == NULL)
D 3
				logdie("Cannot open adjunct file \"%s\".\n",
E 3
I 3
				logdie("Cannot open adjunct file \"%s\"",
E 3
					adj->pwfile);

D 2
			while ((ap = fgetapwent(af)) != NULL) {
				if (strcmp(ap->pwa_name, name) == 0 &&
				    ap->pwa_passwd && *ap->pwa_passwd) {
E 2
I 2
			while ((xp = fgetapwent(af)) != NULL) {
				if (strcmp(xp->pwa_name, name) == 0 &&
				    xp->pwa_passwd && *xp->pwa_passwd) {
E 2
					xv->shadow = sl_local;
					xv->whichSH = adj;
					if (DebugLevel)		/* XXX */
						printf("pw_getuserbyname: adjunct pw for %s in %s\n",
							name, adj->pwfile);
					break;
				}
E 4
I 4
		while ((xp = fgetapwent(af)) != NULL) {
			if (strcmp(xp->pwa_name, name) == 0 &&
			    xp->pwa_passwd && *xp->pwa_passwd) {
				xv->shadow = sl_local;
				xv->whichSH = adj;
I 5
				xv->shadowpw = copystr(xp->pwa_passwd);
E 5
				if (DebugLevel)		/* XXX */
					printf("pw_getuserbyname: adjunct pw for %s in %s\n",
						name, adj->pwfile);
				break;
E 4
			}
D 4
			(void) fclose(af);
E 4
		}
I 4
		(void) fclose(af);
adjunct_done:	;
E 4
	}
#endif
#ifdef	ULTRIX_SHADOW
	/*
	 * Check if the password is in the auth datbase (Ultrix 4.X)
	 */
D 3
	if (strcmp(userp->pw_passwd, "*") == 0 &&
	    (SecurityLevel == sec_u4upgrade || SecurityLevel == sec_u4enhanced)) {
E 3
I 3
	if ((SecurityLevel == sec_u4enhanced) ||
	    (SecurityLevel == sec_u4upgrade &&
	     strcmp(userp->pw_passwd, "*") == 0)) {
E 3
		AUTHORIZATION	*a;

		if ((a = getauthuid(userp->pw_uid)) == 0)
D 3
			logdie( "Cannot get password for %s from auth db\n",
E 3
I 3
D 7
			logdie("Cannot get password for %s from auth db",
E 3
				user);
E 7
I 7
			logdie("Cannot get password for uid %d from auth db",
				userp->pw_uid);
E 7
		userp->pw_passwd = copystr(a->a_password);
		xv->shadow = sl_local;
		if (DebugLevel)
D 7
			printf("pw_getuserbyname: found auth pw for %s\n", name);
E 7
I 7
			printf("pw_getuserbyname: found auth pw for %s\n",
				userp->pw_name);
E 7
	}
#endif
#ifdef	S5_SHADOW
	/*
	 * Check if the password is in the shadow datbase (System 5)
	 */
	if (strcmp(userp->pw_passwd, "x") == 0) {
D 10
		struct spwd	*si = getspnam(user);
E 10
I 10
		struct spwd	*si = getspnam(userp->pw_name);
E 10
		struct passwd_files *shp;

		if (si == NULL)
D 3
			logdie( "Cannot get password for %s from shadow\n",
E 3
I 3
			logdie("Cannot get password for %s from shadow",
E 3
D 10
				user);
E 10
I 10
				userp->pw_name);
E 10
		userp->pw_passwd = copystr(si->sp_pwdp);
		xv->shadow = sl_local;

		/*
		 * Find the adjunct password file
		 */
		for (shp = shadowfiles; shp->pwfile; shp++) {
			if (access(shp->pwfile, 0) == 0)
				break;
		}
		if (DebugLevel)		/* XXX */
			printf("pw_getuserbyname: shadow pw for %s in %s\n",
				name, shp->pwfile);
		/*
		 * I assume that the first shadow file found
		 * is the correct one - they don't tend to move around
		 * like /etc/passwd does.
		 */
		xv->whichSH = shp;
	}
#endif
	/*
E 11
	 * Look in the local flat password file(s)
	 */
D 11
	localpw = NULL;
E 11
D 18
	for (whichpw = pwfiles; whichpw->pwfile; whichpw++) {
E 18
I 18
	for (whichpw = etc_passwd; whichpw->pwfile; whichpw++) {
E 18
D 13
		if (DebugLevel)
E 13
I 13
D 19
		if (DebugLevel >= DB_LOOKUP) {
E 13
			printf("pw_getuserbyname: looking for %s in pw %s\n",
				name, whichpw->pwfile);
I 13
			fflush(stdout);
		}
E 19
I 19
D 24
		debug(DB_LOOKUP, "get_local_pw: looking for %s in \"%s\"\n",
E 24
I 24
D 27
		debug(DB_LOOKUP, "get_local_user: looking for %s in \"%s\"\n",
E 27
I 27
		struct stat	pwfstat;

		debug(DB_LOOKUP, "get_local_user: looking for '%s' in \"%s\"\n",
E 27
E 24
			name, whichpw->pwfile);
E 19
E 13
D 27
		if (access(whichpw->pwfile, 0) < 0)
E 27
I 27
		if (lstat(whichpw->pwfile, &pwfstat) < 0)
E 27
			continue;
I 27
		/*
		 * Sanity check - disallow symlinks (who knows what
		 * they might really point to)
		 */
D 29
		if (pwfstat.st_mode & S_IFLNK) {
E 29
I 29
		if ((pwfstat.st_mode & S_IFLNK) == S_IFLNK) {
E 29
			warn("Ignoring passwd file \"%s\" symlink\n",
				whichpw->pwfile);
			continue;
		}
		/*
		 * Sanity check - disallow world-writable files
		 * (just a really bad idea)
		 */
#ifdef	S_IWOTH
		if (pwfstat.st_mode & S_IWOTH) {
#else
		if (pwfstat.st_mode & 02) {
#endif
			warn("Ignoring passwd file \"%s\" world-writable\n",
				whichpw->pwfile);
			continue;
		}
E 27
D 11
		if (localpw = fgetpwnam(name, whichpw->pwfile)) {
			xv->whichPW = whichpw;
			xv->source = pl_local;
E 11
I 11
		if (pwinfo = fgetpwnam(name, whichpw->pwfile)) {
E 11
D 13
			if (DebugLevel)
E 13
I 13
D 19
			if (DebugLevel >= DB_LOOKUP) {
E 13
D 15
				printf("pw_getuserbyname: found user %s in pw %s\n",
E 15
I 15
				printf("getpwlocal: found user %s in pw %s\n",
E 15
					name, whichpw->pwfile);
D 11
			localpw = copypwent(localpw, &locald);
			break;
		}
	}
#ifndef	YP_PASSWD
	if (localpw == NULL)
D 3
		logdie( "User %s not found in any password file.\n", name);
E 3
I 3
		logdie("User %s not found in any password file", name);
E 3
	/*NOTREACHED*/
	return(NULL);
E 11
D 13

E 13
I 13
				fflush(stdout);
			}
E 19
I 19
D 24
			debug(DB_LOOKUP, "get_local_pw: found %s in \"%s\"\n",
E 24
I 24
D 27
			debug(DB_LOOKUP, "get_local_user: found %s in \"%s\"\n",
E 27
I 27
			debug(DB_LOOKUP, "get_local_user: found '%s' in \"%s\"\n",
E 27
E 24
				name, whichpw->pwfile);
E 19
E 13
D 11
#else	/* YP_PASSWD */
	/*
	 * %%POLICY - Password entry use precedence rules.
	 *
	 *	If no local entry, return <userp> (= YP map entry).
	 *
	 *	If local stub entry and option 'l' set, use <userp>,
	 *	(overlay of local stub and YP map), else <yppw> (YP map entry).
	 *
	 *	If local non-stub entry and option 'l' set, use <localpw>.
	 */
	if (localpw == NULL) {
D 3
		switch (ypstatus) {
E 3
I 3
		switch (ypinfo.status) {
E 3
		case is_yp_client:
			rval->remote = 1;
D 3
			rval->where = ypmaster;
E 3
I 3
			rval->where = ypinfo.master;
E 3
			xv->source = pl_local;
			(void) copypwent(userp, &rval->pw);
			return(rval);
		default:
D 3
			logdie("User %s not found in any password file.\n",
E 3
I 3
			logdie("User %s not found in any password file",
E 3
				name);
			/*NOTREACHED*/
			break;
E 11
I 11
D 15
			*pwptr = pwinfo;
			return(whichpw);
E 15
I 15
			break;
E 15
E 11
		}
	}
D 11
	/*
	 * There is a local passwd file entry for the user
	 *
	 * %%POLICY - Don't change local YP stub entries.
	 */
#ifdef	OS_SUNOS_4
	if (*localpw->pw_name != '+' && CommandLineOption['l']) {
#else
	if (*localpw->pw_name != '+') {
#endif
		rval->remote = 0;
		rval->where = localhost;
		xv->source = pl_local;
I 4
		(void) copypwent(localpw, &rval->pw);
I 5
		if (xv->shadow == sl_local)
			rval->mpw_passwd = xv->shadowpw;
E 5
		return(rval);
	}
	if (ypinfo.status != is_yp_client) {
I 5
		if (xv->shadowpw)
			localpw->pw_passwd = xv->shadowpw;
E 5
E 4
		(void) copypwent(localpw, &rval->pw);
I 5
		rval->where = localhost;
E 5
		return(rval);
	}
	/*
	 * Aren't going to replace the local entry, so return data
	 * from the YP map.
	 */
D 3
	if ((yppw = ypgetpwnam(name, ypdomain)) == NULL)
		logdie( "Cannot get YP passwd for %s.\n", name);
E 3
I 3
	if ((yppw = ypgetpwnam(name, ypinfo.domain)) == NULL)
		logdie("Cannot get YP passwd for %s", name);
E 3
	rval->remote = 1;
D 3
	rval->where = ypmaster;
E 3
I 3
	rval->where = ypinfo.master;
E 3
	xv->source = pl_yp;
	(void) copypwent(yppw, &rval->pw);
	return(rval);
#endif	/* YP_PASSWD */
E 11
I 11
D 15
	return(NULL);
E 15
I 15
	if (pwinfo == NULL)		/* Did not find user */
		return(0);
I 21
D 22
#ifdef	USE_NIS
E 22
I 22
#if	defined(USE_NIS) || defined(USE_NISPLUS)
E 22
E 21
	if (*pwinfo->pw_name == '+')	/* Ignore YP stub entry */
		return(0);
I 21
#endif
E 21
	/*
	 * If this machine is a NIS client, the local entry
	 * is ignored unless the -l flag was given (SunOS 4 only).
	 */
D 22
#if	defined(OS_SUNOS_4)
E 22
I 22
D 23
#ifdef	OS_SUNOS_4
E 23
I 23
#ifdef	USE_NIS
# ifdef	OS_SUNOS_4
E 23
E 22
D 21
	if (ypinfo.status == is_yp_client && !CommandLineOption['l'])
E 21
I 21
	if (ypinfo.status == is_yp_client && !Switches['l'])
E 21
		return(0);
D 22
#else
E 22
I 22
D 23
#endif
E 22
D 18
#ifdef	YP_SUPPORT
E 18
I 18
#ifdef	USE_NIS
E 23
I 23
D 28
#else	/* OS_SUNOS_4 */
E 28
I 28
D 32
# else		/* OS_SUNOS_4 */
E 28
E 23
E 18
	if (ypinfo.status == is_yp_client)
		return(0);
D 21
#endif
#endif
E 21
I 21
D 22
#endif	/* USE_NIS */
#endif	/* OS_SUNOS_4 */
E 22
I 22
D 23
#endif
E 23
I 23
D 28
# endif	/* OS_SUNOS_4 */
E 28
I 28
# endif		/* OS_SUNOS_4 */
E 32
I 32
# endif
E 32
E 28
#endif	/* USE_NIS */
E 23
E 22
E 21
D 18
	(void) gethostname(localhost, MAXHOSTNAMLEN);
E 18
I 18
	(void) gethostname(localhost, sizeof(localhost));
E 18
D 20
	mp->where = copystr(localhost);
E 20
I 20
D 21
	mp->pws_loc = copystr(localhost);
E 21
I 21
	mp->pws_loc = strdup(localhost);
E 21
D 30
	mp->pws_name = "local";
E 30
I 30
	mp->pws_name = "Local";
E 30
E 20
	opdata->sourcePW = srv_local;
	opdata->whichPW = whichpw;
I 16
D 18
#ifdef	YP_SUPPORT
E 18
I 18
#ifdef	USE_NIS
E 18
	opdata->dbinfo.ypinfo = &ypinfo;
#endif
I 22
#ifdef	USE_NISPLUS
	opdata->dbinfo.nisinfo = &nisinfo;
#endif
E 22
E 16
	(void) copypwent(pwinfo, &mp->pw);
	get_shadow(mp);
D 18
#if	HAS_PW_AGE
E 18
I 18
#ifdef	PWAGE
I 27
D 28
#ifdef	OS_HPUX
E 28
I 28
# ifdef	OS_HPUX
	/* Sys5 aging HP-UX style */
E 28
	if (mp->mpw_age && *mp->mpw_age) {	/*MRS 10/97*/
		extern long a64l();
		char	temp[10],
D 28
			*tmpAge;	/*ACME*/
E 28
I 28
			*tmpAge;
E 28

		temp[0] = mp->mpw_age[0];	/* QUICK and dirty */
		temp[1] = '\0';
		mp->pwage.must_change = a64l(temp);
		temp[0] = mp->mpw_age[1];
		mp->pwage.can_change = a64l(temp);
D 28
/* ??? */	tmpAge = &mp->mpw_age[2];	/* The portable way */
E 28
I 28
		tmpAge = &mp->mpw_age[2];	/* The portable way */
E 28
		mp->pwage.last_change = a64l(tmpAge);
        }
D 28
#else /* end of HPUX*/
E 28
I 28
# else 		/* OS_HPUX */
	/* Generic Sys5 aging */
E 28
E 27
E 18
	if (mp->mpw_age && *mp->mpw_age) {
		time_t pwage = 0;
		extern long	a64l();

		pwage = a64l(mp->mpw_age);
D 20
		mp->pwage.doit = 1;
		mp->pwage.max_time = (pwage & 077) * SEC_PER_WEEK;
		mp->pwage.min_time = ((pwage >> 6) & 077) * SEC_PER_WEEK;
E 20
I 20
D 21
		mp->pwage.do_aging = 1;
		mp->pwage.must_change = (pwage & 077) * SEC_PER_WEEK;
		mp->pwage.can_change = ((pwage >> 6) & 077) * SEC_PER_WEEK;
E 20
		mp->pwage.last_change = (pwage >> 12) * SEC_PER_WEEK;
E 21
I 21
		mp->pwage.must_change = (pwage & 077) * SEC_WEEK;
		mp->pwage.can_change = ((pwage >> 6) & 077) * SEC_WEEK;
		mp->pwage.last_change = (pwage >> 12) * SEC_WEEK;
E 21
	}
D 27
#endif
E 27
I 27
D 28
#endif /* Generic age code */
E 28
I 28
# endif		/* OS_HPUX */
E 28
	debug(DB_LOOKUP,
		"Password aging:\n\tMust change: %ld\n\tCan Change: %ld\n\tLast Change: %ld\n",
		mp->pwage.must_change,
		mp->pwage.can_change,
		mp->pwage.last_change);

D 28
#endif /* if PWAGE */
E 28
I 28
#endif 	/* PWAGE */
E 28
E 27
	return(1);
E 15
E 11
}

D 11
/*
D 3
 *	pw_permission - check password change permission
E 3
I 3
 *	pw_permission - check information change permission
E 3
 *
D 3
 *	Returns 1 if password can be changed
E 3
I 3
 *	Returns 1 if information can be changed
E 3
 *		0 if not
I 3
 *
 *	This routine does method-dependant permissions checking for updating
 *	passwd information.
E 3
 */
D 5
pw_permission(theUser, theCaller)
E 5
I 5
enum chg_perm pw_permission(theUser, theCaller)
E 5
struct mpasswd	*theUser,
		*theCaller;
{
D 3
	uid_t	calluid = getuid();

	/* Is this my password? */
	if (strcmp(theCaller->mpw_name, theUser->mpw_name) && calluid)
		return(1);

	/*
	 * %%POLICY - Changing other passwords via NIS.
	 *
	 * If on a YP client, root cannot change another
	 * users' password via yppasswd().  Doing it that way
	 * requires plain text of the current password, and for me as a
	 * sys admin, If I had that password, I wouldn't need to be trying
	 * to change it.
	 *
	 * The "ALWAYS_USE_YPPASSWDD" option runs smack into this same
	 * problem, which is one of the reasons that I don't recommend it.
	 */
	if (calluid == 0 && ypstatus == is_yp_client && theUser->remote) {
		printf("Information can only be changed on NIS master %s.\n",
			ypmaster);
		return(0);
	}
#ifdef	S5_PWAGING
	if (theUser->mpw_age) {
		time_t	pwage = 0,
			maxpwtime = 0,
			minpwtime = 0,
			now;
		extern long a64l();

		pwage = a64l(theUser->mpw_age);
		maxpwtime = pwage & 077;
		minpwtime = (pwage >> 6) & 077;
		pwage >>= 12;
		(void) time(&now);
		now /= SEC_PER_WEEK;
		if (pwage <= now) {
			if (calluid && (now < (pwage + minpwtime))) {
				printf("Less than %ld weeks since last change.\n",
				     minpwtime);
				return(0);
			}
			if ((minpwtime > maxpwtime) && calluid) {
				printf("You may not change this password.\n");
				return(0);
			}
		}
	}
#endif
	/*
	 * Other checks can be put here to determine if the invoker should
	 * be allowed to change this password.
	 */
	return(1);
E 3
I 3
D 5
	return(1);		/* Always say yes right now */
E 5
I 5
	return(self);		/* Always say yes right now */
E 5
E 3
}
E 11
I 11
#ifdef	DBM_PASSWD
E 11
D 15

E 15
I 11
#include <ndbm.h>
E 11
/*
I 22
 * update_dbm_passwd
E 22
D 2
 *      pw_check - sanity check password.  Right now just calls
 *              the password check code
 *
 *      Returns 1 if password is ok to use, 0 otherwise
 */
pw_check(theUser, newpwd, mesgbuf)
struct mpasswd	*theUser;
char		*newpwd,		/* New password (plaintext) */
		*mesgbuf;		/* Error message buffer */
{
	int	rc = checkpassword(&theUser->pw, newpwd, mesgbuf);

#ifdef	PASSWORD_HISTORY
	if (rc)
		return(rc);
	/* Call password history checker to prevent password reuse */
	rc = passwd_history(&theUser->pw, newpwd, mesgbuf);
#endif
	return(rc);
}

/*
E 2
D 11
 *      pw_replace - replace password in passwd file 
E 11
I 11
 *	Update the hashed password data base
I 22
 * Usage
D 23
 *	update_dbm_passwd(const struct mpaswd *old, struct mpaswd *new)
E 23
I 23
 *	update_dbm_passwd(struct mpaswd *old, struct mpaswd *new)
E 23
 * Errors
 *	Error exit on failure of dbm write
E 22
E 11
 */
D 8
void pw_replace(theUser, newpw, newfn, newsh)
E 8
I 8
D 11
public void
pw_replace(theUser, newpw, newfn, newsh)
E 8
struct mpasswd	*theUser;	/* User block */
D 2
char	*newpw,		/* New password (plain) */
E 2
I 2
char	*newpw,			/* New password (encrypted) */
E 2
	*newfn,			/* New full name */
	*newsh;			/* New shell */
E 11
I 11
private void
update_dbm_passwd(theUser, newUser)
D 22
	struct mpasswd	*theUser;
	struct mpasswd	*newUser;
E 22
I 22
D 23
	const struct mpasswd	*theUser;
	      struct mpasswd	*newUser;
E 23
I 23
	struct mpasswd	*theUser;
	struct mpasswd	*newUser;
E 23
E 22
E 11
{
D 11
	struct pw_opaque *aux = (struct pw_opaque *)theUser->opaque;
	struct passwd	NewUser;
I 2
D 3
	int	chflg = 0;
E 3
I 3
	int	changes = 0;
E 11
I 11
D 33
#	define	SCOPY(S) xp = (S); while (*cp++ = *xp++)
D 18
#	define	ICOPY(B) BCOPY((char *)&(B), cp, sizeof(int)); cp += sizeof(int)
E 18
I 18
#	define	ICOPY(B) bcopy((char *)&(B), cp, sizeof(int)); cp += sizeof(int)
E 33
I 33
#define	SCOPY(S) xp = (S); if (xp) { while (*cp++ = *xp++); } else { *cp++ = 0; }
#define	ICOPY(B) bcopy((char *)&(B), cp, sizeof(int)); cp += sizeof(int)
E 33
E 18
E 11
E 3
E 2

D 11
	(void) copypwent(&theUser->pw, &NewUser);
	if (newfn)
D 2
		NewUser.pw_gecos = newfn;
E 2
I 2
D 3
		NewUser.pw_gecos = newfn, chflg |= CHG_FN;
E 3
I 3
D 7
		NewUser.pw_gecos = newfn, changes |= CHG_FN;
E 7
I 7
		NewUser.pw_gecos = copystr(newfn), changes |= CHG_FN;
E 7
E 3
E 2
	if (newsh)
D 2
		NewUser.pw_shell = newsh;
	if (newpw) {
		char salt[8];
E 2
I 2
D 3
		NewUser.pw_shell = newsh, chflg |= CHG_SH;
E 3
I 3
D 7
		NewUser.pw_shell = newsh, changes |= CHG_SH;
E 7
I 7
		NewUser.pw_shell = copystr(newsh), changes |= CHG_SH;
E 7
E 3
	if (newpw)
D 3
		NewUser.pw_passwd = newpw, chflg |= CHG_PW;
E 3
I 3
D 7
		NewUser.pw_passwd = newpw, changes |= CHG_PW;
E 7
I 7
		NewUser.pw_passwd = copystr(newpw), changes |= CHG_PW;
E 11
I 11
	DBM	*pwd;		/* DBM data base passwd */
D 33
	register char	*cp,	/* Data storage pointer */
			*xp;	/* String copy pointer */
E 33
I 33
	char	*cp,		/* Data storage pointer */
		*xp;		/* String copy pointer */
E 33
	datum	key,		/* DBM key datum */
		data;		/* DBM data store datum */
	char	buf[512];	/* Data buffer */
E 11
E 7
E 3
E 2

I 33
	if (theUser == NULL || newUser == NULL)
		/* Post error */
		return;
E 33
I 3
D 11
#if	defined(YP_PASSWD) && defined(ALWAYS_USE_YPPASSWD)
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
	aux->source = pl_yp;
	ypinfo.status = is_yp_client;
#endif
E 11
I 11
	pwd = dbm_open(((struct pw_opaque *)theUser->opaque)->whichPW->pwfile,
		O_RDWR, 0);
	if (pwd == NULL)
		return;
	cp = buf;
	/* Pack passwd entry in the form expected by the getpw* routines */
	SCOPY(newUser->mpw_name);
	SCOPY(newUser->mpw_passwd);
	ICOPY(newUser->mpw_uid);
	ICOPY(newUser->mpw_gid);
I 25
#ifdef	PWQUOTA
E 25
	ICOPY(newUser->mpw_quota);
I 25
#endif
I 26
#ifdef	PWCOMMENT
E 26
E 25
	SCOPY(newUser->mpw_comment);
I 26
#endif
E 26
	SCOPY(newUser->mpw_gecos);
	SCOPY(newUser->mpw_dir);
	SCOPY(newUser->mpw_shell);
E 11

E 3
D 2
		(void) random_string(salt, sizeof(salt));
		NewUser.pw_passwd = crypt(newpw, salt);
#if	ULTRIX_SHADOW
		/* Check for high security levels */
		if (aux->shadow != sl_none)
			NewUser.pw_password = crypt16(newpw, salt);
#endif
	}
E 2
D 11
	switch (aux->source) {
I 10
#ifdef	YP_PASSWD
E 10
	case pl_yp:
D 2
		update_yp_passwd(theUser, NewUser, ypdomain, ypmaster);
E 2
I 2
D 3
		update_yp_passwd(theUser, NewUser, chflg, ypdomain, ypmaster);
E 3
I 3
D 7
		update_yp_passwd(theUser, NewUser, &ypinfo, changes);
E 7
I 7
		update_yp_passwd(theUser, &NewUser, &ypinfo, changes);
E 7
E 3
E 2
		break;
I 10
#endif
E 10
	case pl_local:
D 2
		update_local_passwd(theUser, NewUser);
E 2
I 2
D 3
		update_local_passwd(theUser, NewUser, chflg);
E 3
I 3
D 7
		update_local_passwd(theUser, NewUser, changes);
E 7
I 7
		update_local_passwd(theUser, &NewUser, changes);
E 7
E 3
E 2
		break;
	default:
D 3
		logdie( "Unknown passwd source %d\n", aux->source);
E 3
I 3
		logdie("Unknown passwd source %d", aux->source);
E 3
		/*NOTREACHED*/
E 11
I 11
	data.dptr = buf;
	data.dsize = cp - buf;
	key.dptr = newUser->mpw_name;
	key.dsize = strlen(newUser->mpw_name);
	if (dbm_store(pwd, key, data, DBM_REPLACE) < 0) {
		perror("dbm_store (name)");
D 22
		logdie("Can't store passwd entry (name key)");
E 22
I 22
		logdie("Can't store passwd entry (name key)\n");
E 22
E 11
	}
I 11
	key.dptr = (char *)&newUser->mpw_uid;
	key.dsize = sizeof (int);
	if (dbm_store(pwd, key, data, DBM_REPLACE) < 0) {
		perror("dbm_store (uid)");
D 22
		logdie("Can't store passwd entry (uid key)");
E 22
I 22
		logdie("Can't store passwd entry (uid key)\n");
E 22
	}
	dbm_close(pwd);
I 15
#	undef	SCOPY
#	undef	ICOPY
E 15
E 11
}
I 11
D 15
#undef	SCOPY
#undef	ICOPY
#else	/* DBM_PASSWD */
public void
update_dbm_passwd(theUser, newUser)
	struct mpasswd	*theUser,
			*newUser;
{
}
E 15
#endif	/* DBM_PASSWD */
E 11

I 22
/*
D 24
 * update_local_pw
E 24
I 24
 * put_local_user
E 24
 *	Update local passwd/shadow files
 *
 * Usage
D 24
 *	update_local_pw(struct mpasswd *old, struct mpasswd *new, int changes);
E 24
I 24
 *	put_local_user(struct mpasswd *old, struct mpasswd *new, int changes);
E 24
 * Effects
 *	Updates the appropriate local password file if needed
 *	Updates the appropriate local shadow file if needed
 *	Syncs auxillary databases (DBM hash files, NIS maps)
 * Errors
 *	Failure in file manipulation (creation or renaming)
 *	New password file appears truncated
 */
E 22
I 10
D 11
private int sigs_to_block[] = { SIGHUP, SIGINT, SIGQUIT, SIGTSTP, 0 };

E 10
D 2
update_local_passwd(theUser, NewUser)
E 2
I 2
update_local_passwd(theUser, NewUser, flags)
E 2
struct mpasswd	*theUser;
struct passwd	*NewUser;
I 2
int		flags;
E 11
I 11
D 15
private void
update_local_passwd(theUser, newUser, flags)
E 15
I 15
public void
D 22
update_local_pw(theUser, newUser, flags)
E 22
I 22
D 24
update_local_pw(theUser, newUser, changes)
E 24
I 24
put_local_user(theUser, newUser, changes)
E 24
E 22
E 15
	struct mpasswd	*theUser;
	struct mpasswd	*newUser;
D 22
	int		flags;
E 22
I 22
	int		changes;
E 22
E 11
E 2
{
D 8
#if	BSD_SIGNALS
E 8
I 8
D 10
#if	HAS_SIGMASK
E 8
	int	oldsigs,	/* Old signal mask */
		blocksigs = sigmask(SIGINT) |	/* Sigs to block */
			    sigmask(SIGQUIT) |
			    sigmask(SIGHUP) |
			    sigmask(SIGTSTP);
I 8
#elif	POSIX_SIGNALS
	/* Use sig*set and sigprocmask */
E 8
#else
	SIGTYPE	(*saveint)(),
		(*savequit)(),
		(*savehup)();
#endif
E 10
	FILE	*tf,		/* New password file output */
		*pf;		/* Current password file input */
	int	fd;		/* Temp file create fd */
	int	repdone = 0;	/* Entry was replaced */
	int	mytempfile = 0;	/* Does PASSWD_TEMP belong to me? */
I 15
D 32
	size_t	sizediff;	/* Size difference in old & new files */
E 32
I 32
	int	sizediff;	/* Size difference in old & new files */
E 32
E 15
	struct passwd	*px;	/* Password file traversal */
	struct pw_opaque *aux = (struct pw_opaque *)theUser->opaque;
I 11
	struct sigblk	blocked;
E 11
D 27

E 27
I 21
D 22
	if ((flags & (CHG_PW | CHG_PWAGE)) == 0) {
		/* DEBUG complain about nothing to do */
		return; 
	}
E 22
I 22
	if (changes == 0)
D 24
		logdie("Error: update_local_pw called with null changes\n");
E 24
I 24
		logdie("Error: put_local_user called with null changes\n");
E 24

E 22
E 21
I 15
D 18
#ifdef	HAS_PW_AGE
E 18
I 18
#ifdef	PWAGE
E 18
E 15
I 10
D 11
#if	(SIG_TYPE == SIG_TYPE_POSIX)
	sigset_t	blocksigs,
			savesigs;

	{ int i; for (i = 0; sigs_to_block[i]; i++)
		sigaddset(&blocksigs, sigs_to_block[fd]);
	}

# define	HOLD_SIGNALS	sigprocmask(SIG_BLOCK, &blocksigs, &savesigs)
# define	RELEASE_SIGNALS	sigprocmask(SIG_UNBLOCK, &blocksigs, &savesigs)
#endif
#if	(SIG_TYPE == SIG_TYPE_BSD)
	unsigned long	blocksigs,
			savesigs;

	{ int i; for (i = 0; sigs_to_block[i]; i++)
		blocksigs |= sigmask(sigs_to_block[fd]);
	}

# define	HOLD_SIGNALS	savesigs = sigblock(blocksigs)
# define	RELEASE_SIGNALS	setsigmask(savesigs)
#endif
#if	(SIG_TYPE == SIG_TYPE_UNIX)
	signal_t savesigs[sizeof(sigs_to_block) / sizeof(sigs_to_block[0])];

# define HOLD_SIGNALS { int i; for (i = 0; sigs_to_block[i]; i++)\
		savesigs[i] = (void *)signal(sigs_to_block[i], SIG_IGN); }
# define RELEASE_SIGNALS { int i; for (i = 0; sigs_to_block[i]; i++)\
		signal(sigs_to_block[i], (signal_t )savesigs[i]); }
#endif

E 11
E 10
	/*
I 15
	 * Update password aging information
	 */
I 27

	debug(DB_DETAIL,"Updating age\nChanges: %d\nAge: %ld\n",
		changes & CHG_PWAGE,newUser->pwage.must_change);

E 27
D 20
	if (newUser->pwage.doit) {
		if (newUser->pwage.max_time == 0) {
E 20
I 20
D 21
	if (newUser->pwage.do_aging) {
E 21
I 21
D 22
	if (flags & CHG_PWAGE) {
E 22
I 22
	if (changes & CHG_PWAGE) {
E 22
E 21
D 33
		if (newUser->pwage.must_change == 0) {
E 20
			newUser->mpw_age = '\0';
E 33
I 33
		if ((changes & CHG_PW) &&
		    (newUser->pwage.must_change == 0) &&
		    (newUser->pwage.can_change == 0)) {
			newUser->mpw_age = "";
E 33
		}
		else {
			extern char *l64a();
D 21
			time_t	now = newUser->pwage.last_change / SEC_PER_WEEK,
E 21
I 21
			time_t	now = newUser->pwage.last_change / SEC_WEEK,
E 21
				pwage;
I 27
#ifdef OS_HPUX
			char	pwtemp[STRINGLEN];
#endif
E 27

D 22
			if (flags & CHG_PW)
E 22
I 22
			if (changes & CHG_PW)
E 22
D 21
				now = time((time_t *)0) / SEC_PER_WEEK;
E 21
I 21
				now = time((time_t *)0) / SEC_WEEK;
I 27
#ifdef OS_HPUX		
			(void) strcpy(pwtemp, l64a(newUser->pwage.must_change));
			if (newUser->pwage.can_change)
				(void) strcat(pwtemp,
					l64a(newUser->pwage.can_change));
			else
				(void) strcat(pwtemp, ".");
			(void) strcat(pwtemp, l64a(now));
			debug(DB_DETAIL, "HPUX Age=%s\n", pwtemp);
			if (strlen(pwtemp))
			 	(void) strcpy(newUser->mpw_age, pwtemp);
			else
				newUser->mpw_age = ".";
#else
E 27
E 21
D 20
			pwage = newUser->pwage.max_time
				+ (newUser->pwage.min_time << 6)
E 20
I 20
D 33
			pwage = newUser->pwage.must_change
				+ (newUser->pwage.can_change << 6)
E 33
I 33
			pwage = (newUser->pwage.must_change / SEC_WEEK)
				+ ((newUser->pwage.can_change / SEC_WEEK) << 6)
E 33
E 20
				+ (now << 12);
			if (pwage)
				newUser->mpw_age = l64a(pwage);
			else
				newUser->mpw_age = ".";
I 27
#endif
E 27
		}
	}
D 20
#endif
E 20
I 20
#endif	/* PWAGE */
E 20
	/*
E 15
D 2
	 * Update the shadow file first
E 2
I 2
D 22
	 * Update shadow password files.  For all the shadow passwd file
	 * formats supported, only the shadow file is altered to change
	 * the password.
E 22
I 22
	 * The shadow file holds the encrypted password
	 * and password aging information.
E 22
E 2
	 */
D 11
#ifdef	ULTRIX_SHADOW
D 2
	if (aux->shadow == sl_local &&
	    (SecurityLevel == sec_u4upgrade || SecurityLevel == sec_u4enhanced)) {
E 2
I 2
	if ((flags & CHG_PW) &&
	    aux->shadow == sl_local &&
	    (SecurityLevel == sec_u4upgrade ||
	     SecurityLevel == sec_u4enhanced)) {
E 2
		AUTHORIZATION	*a = getauthuid(theUser->mpw_uid);

D 2
		if (a == NULL)
			break;
E 2
I 2
		if (a == NULL) 
			logdie("Could not read auth database for update.");
E 2
		(void) strcpy(a->a_password, NewUser->pw_passwd);
D 2
		NewUser->pw_passwd = "*";
E 2
		a->a_pass_mod = time((time_t *)0);
D 7
		if (storeauth(a))
E 7
I 7
		if (storeauthent(a))
E 7
D 2
			logdie( "Could not update auth database\n");
E 2
I 2
			logdie("Could not update auth database.");
		if (flags == CHG_PW)	/* Nothing else to do */
			return;
		NewUser->pw_passwd = "*";
E 2
	}
#endif
#ifdef	SUN_SHADOW
E 11
D 2
	if (aux->shadow == sl_local) {
E 2
I 2
D 15
	if ((flags & CHG_PW) && aux->shadow == sl_local) {
E 15
I 15
D 18
	if ((flags == CHG_PW) && aux->sourceSH == srv_local) {
E 18
I 18
D 21
	if (flags == CHG_PW && aux->sourceSH == srv_local) {
E 21
I 21
D 22
	if (aux->sourceSH == srv_local) {
E 22
I 22
	if ((changes & (CHG_PW | CHG_PWAGE)) &&
	     aux->sourceSH == srv_local) {
E 22
E 21
E 18
E 15
E 2
D 11
		update_adjunct(theUser, NewUser);
I 2
		if (flags == CHG_PW)	/* That does it */
			return;
E 2
		(void) strcpy(NewUser->pw_passwd, "##");
D 2
		(void) strcat(NewUser->pw_passwd, NewUser->pw_name);
E 2
I 2
		(void) strcat(NewUser->pw_passwd, theUser->mpw_name);
E 11
I 11
		update_shadow(theUser, newUser);
D 22
		return;
E 22
I 22
		return;		/* Our work is done */
E 22
E 11
E 2
	}
D 11
#endif
#ifdef	S5_SHADOW
D 2
	if (aux->shadow == sl_none) {
E 2
I 2
	if ((flags & CHG_PW) && aux->shadow == sl_local) {
E 2
		update_local_shadow(theUser, NewUser);
I 2
		if (flags == CHG_PW)	/* That's all folks */
			return;
		NewUser->pw_passwd = "x";
E 2
	}
#endif
E 11
	/*
	 * Update the local passwd file.
	 */
	if ((pf = fopen(aux->whichPW->pwfile, "r")) == NULL)
D 2
		logdie( "Cannot open password file \"%s\".\n",
E 2
I 2
		logdie("Cannot open password file \"%s\".\n",
E 2
			aux->whichPW->pwfile);
	/*
	 * This deals with the SunOS yppasswdd which creates temp files
	 * named "passwd-file.ptmp", rather than the traditional "/etc/ptmp".
	 *
	 * But there are still a lot of applications which use /etc/ptmp,
	 * so is it used as the passwd temp file and the 'auxlockfile' is
	 * also made.
	 */
I 15
D 18
#ifdef	YP_SUPPORT
E 18
I 18
#ifdef	USE_NIS
E 18
E 15
D 3
	if (ypstatus == is_yp_master && aux->whichPW->lockfile) {
E 3
I 3
	if (ypinfo.status == is_yp_master && aux->whichPW->lockfile) {
I 15
#else
	if (aux->whichPW->lockfile) {
#endif
E 15
E 3
		mytempfile = 1;
D 21
		(void) close(mklocktemp(aux->whichPW->lockfile));
E 21
I 21
		(void) close(MakeLockTemp(aux->whichPW->lockfile));
E 21
	}
D 21
	fd = mklocktemp(aux->whichPW->tempfile);
E 21
I 21
	fd = MakeLockTemp(aux->whichPW->tempfile);

#if	defined(HAS_FCHOWN) && defined(HAS_FCHMOD)
D 22
	(void) fchown(fd, PASSWD_UID, PASSWD_GID);
	(void) fchmod(fd, PASSWD_MODE);
E 22
I 22
	if (fchown(fd, PASSWD_UID, PASSWD_GID) < 0)
D 28
# ifdef	DEBUG
		warn("Passwd temp fchown error %d\n", errno);
# else
E 28
I 28
# if	(CDEBUG < CDEBUG_SYSTEM)
E 28
		logdie("Passwd temp fchown error %d\n", errno);
I 28
# else
		warn("Passwd temp fchown error %d\n", errno);
E 28
# endif
	if (fchmod(fd, PASSWD_MODE) < 0)
D 28
# ifdef	DEBUG
		warn("Passwd temp fchmod error %d\n", errno);
# else
E 28
I 28
# if	(CDEBUG < CDEBUG_SYSTEM)
E 28
		logdie("Passwd temp fchmod error %d\n", errno);
I 28
# else
		warn("Passwd temp fchmod error %d\n", errno);
E 28
# endif
E 22
#else
	FixPwFileMode(aux->whichPW->tempfile, "passwd");
#endif
I 27

E 27
E 21
	if ((tf = fdopen(fd, "w")) == NULL) {
		if (mytempfile)
			(void) unlink(aux->whichPW->lockfile);
D 2
		logdie( "Cannot fdopen temp file \"%s\".\n",
E 2
I 2
		logdie("Cannot fdopen temp file \"%s\".\n",
E 2
			aux->whichPW->tempfile);
	}
D 8
#if	BSD_SIGNALS
E 8
I 8
D 10
#if	HAS_SIGMASK
E 8
	oldsigs = sigblock(blocksigs);
#else
	saveint = signal(SIGINT, SIG_IGN);
	savequit = signal(SIGQUIT, SIG_IGN);
	savehup = signal(SIGHUP, SIG_IGN);
#endif
E 10
I 10
D 11
	HOLD_SIGNALS;
E 11
I 11
D 18

	BZERO((char *)&blocked, sizeof blocked);
E 18
I 18
D 19
	if (DebugLevel >= DB_UPDATE) {
		printf("update_local_pw: replace user %s in pw %s\n",
			newUser->mpw_name, aux->whichPW->pwfile);
		fflush(stdout);
	}
E 19
I 19
D 24
	debug(DB_UPDATE, "update_local_pw: replace %s in \"%s\"\n",
E 24
I 24
	debug(DB_UPDATE, "put_local_user: replace %s in \"%s\"\n",
E 24
		newUser->mpw_name, aux->whichPW->pwfile);
I 22
D 27
#ifdef	HAS_MEMSET
	memset((void *)&blocked, 0, sizeof blocked);
#else
E 22
E 19
	bzero((char *)&blocked, sizeof blocked);
I 22
#endif
E 27
I 27
	zeromem(&blocked, sizeof blocked);
E 27
D 28
#ifndef	DEBUG
E 28
I 28
#if	(CDEBUG < CDEBUG_SYSTEM)
E 28
E 22
E 18
	block_signals(&blocked, SIGHUP, SIGINT, SIGQUIT, SIGTSTP, 0);
I 22
#endif
I 27

E 27
E 22
E 11
E 10
	while ((px = fgetpwent(pf)) != NULL) {
		if (px->pw_name == 0 || px->pw_name[0] == 0) /* Sanity check */
			continue;
D 22
		if (repdone) {
			(void) putpwent(px, tf);
			continue;
		}
I 7
D 11
#if	0
printf("pw_name <%s> theUser_name <%s>\n",		/* XXX */
	px->pw_name, theUser->mpw_name);		/* XXX */
#endif
E 11
E 7
		if (strcmp(px->pw_name, theUser->mpw_name) == 0) {
I 7
D 11
#if	0
printf("replace NewUser_name <%s>\n",		/* XXX */
	NewUser->pw_name);		/* XXX */
#endif
E 7
			(void) putpwent(NewUser, tf);
E 11
I 11
D 15
			(void) putpwent(&newUser->pw, tf);
E 15
I 15
			px = &newUser->pw;
E 22
I 22
		if (!repdone && strcmp(px->pw_name, theUser->mpw_name) == 0) {
			/*
			 * The password and aging fields changes
			 * won't make it here if a shadow file exists
			 */
#ifdef	PWAGE
			if (changes & CHG_PWAGE)
				px->pw_age = newUser->mpw_age;
I 31
			else
				px->pw_age = "";
E 31
#endif
			if (changes & CHG_PW)
				px->pw_passwd = newUser->mpw_passwd;
			if (changes & CHG_GECOS)
				px->pw_gecos = newUser->mpw_gecos;
			if (changes & CHG_SHELL)
				px->pw_shell = newUser->mpw_shell;
E 22
E 15
E 11
			repdone++;
D 15
			continue;
E 15
		}
		(void) putpwent(px, tf);
	}
D 3
	(void) fflush(tf);			/* Force buffers empty */
E 3
I 3
	(void) fflush(tf);
E 3
	(void) fclose(tf);
	(void) fclose(pf);

D 3
	if (mytempfile) {
E 3
I 3
	if (mytempfile) {		/* Need to discard lock? */
E 3
		(void) unlink(aux->whichPW->lockfile);
		mytempfile = 0;
	}
D 3

	if (repdone == 0) {		/* Nothing changed */
E 3
I 3
	if (repdone == 0) {		/* Nothing changed? */
E 3
		(void) unlink(aux->whichPW->tempfile);
D 10
		(void) sigsetmask(oldsigs);
E 10
I 10
D 11
		RELEASE_SIGNALS;
E 11
I 11
		unblock_signals(&blocked);
E 11
E 10
		return;
	}
	/*
	 * Check if the new password file is complete.
I 15
	 * There is an assumption here that changing one passwd entry should
D 21
	 * not change the total size of the file more than PASSWD_SIZE_SLOP
E 21
I 21
D 22
	 * not change the total size of the file more than passwd_tolerance
E 22
I 22
	 * not change the total size of the file more than <PasswdTolerance>
E 22
E 21
	 * bytes.  In order to accomodate GECOS changes, this threshold has to
	 * be generous, maybe too generous.  But if the disk really did fill up,
	 * then we will proabably lose big enough to notice.
	 *
	 * If the new file is longer, don't worry.  If shorter, that's 
D 21
	 * alright if the difference is less than PASSWD_SIZE_SLOP, otherwise
E 21
I 21
D 22
	 * alright if the difference is less than passwd_tolerance, otherwise
E 22
I 22
	 * alright if the difference is less than <PasswdTolerance>, otherwise
E 22
E 21
	 * assume that the new file got truncated and bail.
	 *
	 * The alternative is to not use stdio for the temp file I/O, or
	 * force a fflush() after each putpwent() and rely upon fflush to
D 22
	 * return the right error code.  Either way, we take a performance hit.
E 22
I 22
	 * return the right error code.  Not something to bet /etc/passwd on.
	 * I'm not about to reach behind stdio's back and manipulate
	 * buffer pointers and counters.  There Lie Dragons...
E 22
	 *
D 22
	 * So check the sizes and assume that will catch most errors.
E 22
I 22
	 * Check the sizes and assume that will catch most errors.
E 22
E 15
	 */
D 15
/*	sizecheck(aux->whichPW->tempfile, aux->whichPW->pwfile);	/* XX */

E 15
I 15
D 21
	sizediff = cmp_file_size(aux->whichPW->tempfile, aux->whichPW->pwfile);
	if (sizediff < 0 && abs(sizediff) > PASSWD_SIZE_SLOP) {
E 21
I 21
D 32
	sizediff = FileSizeDiff(aux->whichPW->tempfile, aux->whichPW->pwfile);
D 22
	if (sizediff < 0 && abs(sizediff) > passwd_tolerance) {
E 21
		logdie("New passwd file is too short by %lu bytes\n",
			sizediff);
	}
E 22
I 22
	sizediff += PasswdTolerance;
	if (sizediff < 0)
E 32
I 32
	sizediff = ( FileSize(aux->whichPW->tempfile) -
		     FileSize(aux->whichPW->pwfile)) + PasswdTolerance;
	if (sizediff < 0) {
#ifdef	SHORT_FILE_WARN
		logerr("Password temp is %d bytes short\n", abs(sizediff));
#else
E 32
		logdie("Passwd temp is %d bytes short\n", abs(sizediff));
I 32
#endif
	}
	debug(DB_UPDATE,
		"put_local_user: Install passwd '%s', temp '%s', save '%s'\n",
		aux->whichPW->pwfile, aux->whichPW->tempfile,
		aux->whichPW->savefile);
E 32

E 22
E 15
D 17
	if (rename(aux->whichPW->pwfile, aux->whichPW->savefile) < 0) {
E 17
I 17
D 21
	set_protection(aux->whichPW->tempfile, "passwd");
E 21
I 18
	(void) unlink(aux->whichPW->savefile);
E 18
	if (link(aux->whichPW->pwfile, aux->whichPW->savefile) < 0) {
E 17
		perror("Password file save");
		(void) unlink(aux->whichPW->tempfile);
D 3
		logdie( "Can't save password file.\n");
E 3
I 3
D 32
		logdie("Can't save password file");
E 32
I 32
		logdie("Cannot save password file");
E 32
E 3
	}
I 15
D 17
	set_protection(aux->whichPW->tempfile, "passwd");
E 17
E 15
	if (rename(aux->whichPW->tempfile, aux->whichPW->pwfile) < 0) {
		perror("Password file replace");
		(void) unlink(aux->whichPW->tempfile);
		(void) link(aux->whichPW->savefile, aux->whichPW->pwfile);
D 3
		logdie( "Can't replace password file.\n");
E 3
I 3
D 32
		logdie("Can't replace password file");
E 32
I 32
		(void) unlink(aux->whichPW->savefile);
		logdie("Cannot replace password file");
E 32
E 3
	}
I 15
D 21
	(void) chmod(aux->whichPW->pwfile, PASSWD_FILE_MODE);
E 21
I 21
D 32
/* 	(void) chmod(aux->whichPW->pwfile, PASSWD_MODE); */
E 32
E 21
#ifdef	DBM_PASSWD
E 15
D 11
	update_dbm_passwd(theUser, NewUser);
E 11
I 11
	update_dbm_passwd(theUser, newUser);
E 11
I 6
D 15
#ifdef	YP_PASSWD
E 15
I 15
D 20
#endif
E 20
I 20
#endif	/* DBM_PASSWD */
E 20
D 18
#ifdef	YP_SUPPORT
E 18
I 18
#ifdef	USE_NIS
E 18
	/*
	 * If on the YP master, try to update the DBM map files
	 */
E 15
E 6
D 3
	if (ypstatus == is_yp_master)
		update_yp_maps(theUser, NewUser, ypdomain);
E 3
I 3
D 5
	if (ypinfo.status == is_yp_master)
		update_yp_maps(theUser, NewUser, &ypinfo);
E 5
I 5
	if (ypinfo.status == is_yp_master) {
D 15
		char	pwline[BUFSIZ],
E 15
I 15
		char	pwline[PW_LINELEN],
E 15
			uidx[16];

D 11
		(void) sputpwent(NewUser, pwline);
		update_yp_map(NewUser->pw_name, pwline, PASSWD_BYNAME,
E 11
I 11
		(void) sputpwent(&newUser->pw, pwline);
		update_yp_map(newUser->mpw_name, pwline, PASSWD_BYNAME,
E 11
			ypinfo.data, 0);
#ifdef  UIDS_ARE_SIGNED
D 11
		(void) sprintf(uidx, "%d", NewUser->pw_uid);
E 11
I 11
		(void) sprintf(uidx, "%d", newUser->mpw_uid);
E 11
D 20
#else
E 20
I 20
#else	/* UIDS_ARE_SIGNED */
E 20
D 11
		(void) sprintf(uidx, "%u", NewUser->pw_uid);
E 11
I 11
		(void) sprintf(uidx, "%u", newUser->mpw_uid);
E 11
D 20
#endif
E 20
I 20
#endif	/* UIDS_ARE_SIGNED */
E 20
		update_yp_map(uidx, pwline, PASSWD_BYUID, ypinfo.data, 0);
	}
I 6
D 20
#endif
E 20
I 20
#endif	/* USE_NIS */
E 20
E 6
E 5
E 3
D 10

D 8
#if	BSD_SIGNALS
E 8
I 8
#if	HAS_SIGMASK
E 8
	(void) sigsetmask(oldsigs);
#else
	(void) signal(SIGINT, saveint);
	(void) signal(SIGQUIT, savequit);
	(void) signal(SIGHUP, savehup);
#endif
E 10
I 10
D 11
	RELEASE_SIGNALS;
E 11
I 11
	unblock_signals(&blocked);
E 11
E 10
D 15
}
I 10
D 11
#undef	HOLD_SIGNALS
#undef	RELEASE_SIGNALS
E 11
E 10

I 11

E 11
/*
I 11
 *	pw_initialize - set up
 */
public void pw_initialize(argc, argv)
	int	argc;		/* NOTUSED */
	char	**argv;		/* NOTUSED */
{
	BZERO((char *)&ypinfo, sizeof(ypinfo));
	ypinfo.status = yp_not_running;
#ifdef	YP_PASSWD
	ypwhich(PASSWD_BYNAME, &ypinfo);
#endif
}

/*
 *	pw_getuserbyname - get paswd information by user name.
 *
 *	Returns: Pointer to mpasswd sturcture if <name> found
 *		 NULL otherwise
 */
struct mpasswd *
pw_getuserbyname(name)
	char	*name;		/* User name */
{
	struct passwd	*pwinfo;	/* Info from getpwnam() */
	struct mpasswd	*rval;		/* Return mpasswd record */
	struct pw_opaque *xv;		/* Method opaque data block */
	int	i;

	rval = (struct mpasswd *)calloc(sizeof(struct mpasswd), 1);
	if (rval == NULL)
		logdie("Cannot allocate memory for mpasswd data");

	xv = (struct pw_opaque *)calloc(sizeof(struct pw_opaque), 1);
	if (xv == NULL)
		logdie("Cannot allocate memory for opaque data");

	rval->opaque = (void *)xv;
	xv->magic = OPAQUE_MAGIC;
	xv->shadow = sl_none;
	xv->source = pl_local;
	xv->dbinfo.ypinfo = &ypinfo;

	pwinfo = NULL;
	for (i = 0; ServiceOrder[i] != srv_last && pwinfo == NULL; i++) {
		struct passwd_files *whichpw;
		char	localhost[MAXHOSTNAMLEN];

		switch (ServiceOrder[i]) {
		case srv_ypcompat:
		case srv_local:
			if ((whichpw = getpwlocal(name, &pwinfo)) == NULL)
				break;

			if (*pwinfo->pw_name == '+') /* Ignore YP stub entry */
				pwinfo = NULL;
			/*
			 * If this machine is a NIS client, the local entry
			 * is ignored unless the -l flag was given
			 * (SunOS only).
			 */
#if	defined(OS_SUNOS_4) || defined(OS_SUNOS_5)
			if (ypinfo.status == is_yp_client
				&& !CommandLineOption['l']) {
#else
			if (ypinfo.status == is_yp_client) {
#endif
				pwinfo = NULL;
				break;
			}
			(void) gethostname(localhost, MAXHOSTNAMLEN);
			rval->where = copystr(localhost);
			xv->source = pl_local;
			xv->whichPW = whichpw;
			break;

		case srv_yp:
#ifdef	YP_PASSWD
			if (pwinfo = ypgetpwnam(name, ypinfo.domain)) {
				xv->source = pl_yp;
				rval->remote = 1;
				rval->where = ypinfo.master;
			}
#endif
			break;	/* switch case */

		case srv_nisplus:
			logdie("NIS+ not supported\n");
			break;

		case srv_niroot:
		case srv_nidot:
			logdie("Netinfo not supported\n");
			break;

		case srv_kerb:
			logdie("Kerebos not supported\n");
			break;

		case srv_hesiod:
			logdie("Hesiod not supported\n");
			break;
		}
	}

	if (!pwinfo) {
		/* Sanity check? */
		return(NULL);
	}
	(void) copypwent(pwinfo, &rval->pw);
	get_shadow(rval);
I 12
#if	S5_PWAGING
	if (rval->mpw_age && *rval->mpw_age) {
		time_t pwage = 0;
		extern long	a64l();

		pwage = a64l(rval->mpw_age);
		rval->age_password = 1;
		rval->expire = (pwage & 077) * SEC_PER_WEEK;
		rval->min_change_time = ((pwage >> 6) & 077) * SEC_PER_WEEK;
		rval->last_change = (pwage >> 12) * SEC_PER_WEEK;
	}
#endif
E 12
	return(rval);
}

/*
 *	pw_permission - check information change permission
 *
 *	Returns 1 if information can be changed
 *		0 if not
 *
 *	This routine does method-dependant permissions checking for updating
 *	passwd information.
 */
enum chg_perm
pw_permission(theUser, theCaller)
	struct mpasswd	*theUser,
			*theCaller;
{
	return(self);		/* Always say yes right now */
}

/*
 *      pw_replace - replace password in passwd file 
 */
public void
pw_replace(theUser, newpw, newfn, newsh)
	struct mpasswd	*theUser;	/* User block */
	char	*newpw,			/* New password (encrypted) */
		*newfn,			/* New full name */
		*newsh;			/* New shell */
{
	struct pw_opaque *aux = (struct pw_opaque *)theUser->opaque;
	struct mpasswd	newUser;
	int	changes = 0;

	newUser = *theUser;
	(void) copypwent(&theUser->pw, &newUser.pw);
	if (newfn)
		newUser.mpw_gecos = copystr(newfn), changes |= CHG_FN;
	if (newsh)
		newUser.mpw_shell = copystr(newsh), changes |= CHG_SH;
	if (newpw)
		newUser.mpw_passwd = copystr(newpw), changes |= CHG_PW;

I 12
#ifdef	S5_PWAGING
	/*
	 * Update password aging information
	 */
	if (newUser.age_password) {
		if (newUser.expire == 0) {
D 14
			newUser->mpw_age = '\0';
E 14
I 14
			newUser.mpw_age = '\0';
E 14
		}
		else {
			extern char *l64a();
D 14
			time_t	now = newUser.last_change_time / SEC_PER_WEEK,
E 14
I 14
			time_t	now = newUser.last_change / SEC_PER_WEEK,
E 14
				pwage;

			if (newpw)
				now = time((time_t *)0) / SEC_PER_WEEK;
			pwage = newUser.expire
				+ (newUser.min_change_time << 6)
				+ (now << 12);
			if (pwage)
				newUser.mpw_age = l64a(pwage);
			else
				newUser.mpw_age = ".";
		}
	}
#endif
E 12
#if	defined(YP_PASSWD) && defined(ALWAYS_USE_YPPASSWD)
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
	aux->source = pl_yp;
	ypinfo.status = is_yp_client;
#endif

	switch (aux->source) {
#ifdef	YP_PASSWD
	case pl_yp:
		update_yp_passwd(theUser, &newUser, &ypinfo, changes);
		break;
#endif
	case pl_local:
		update_local_passwd(theUser, &newUser, changes);
		break;
	default:
		logdie("Unknown passwd source %d", aux->source);
		/*NOTREACHED*/
	}
}

/*
E 11
 *      pw_cleanup - clean up after myself
 */
D 11
void pw_cleanup(code)
int	code;		/* 0 for normal, 1 for abort */ /*NOTUSED*/
E 11
I 11
public void
pw_cleanup(code)
	int	code;		/* 0 for normal, 1 for abort */ /*NOTUSED*/
E 11
{
	/* do nothing */
}

/*
 *	mklocktemp - Make temp file with exclusive use checking
 *
 *	Returns file descriptor of created file, else exits with error
 */
D 11
int
E 11
I 11
public int
E 11
mklocktemp(name)
D 11
char	*name;
E 11
I 11
	char	*name;
E 11
{
	int	fd;

	fd = open(name, O_WRONLY|O_CREAT|O_EXCL, PASSWD_MODE);
I 3
	/* Need to loop here  */
E 3
	if (fd < 0) {
		if (errno == EEXIST)
D 3
			die("Password file busy - try again.\n");
E 3
I 3
			die("Password file busy - try again");
E 3
		perror("Tempfile create");
D 3
		logdie( "Cannot create temp file.\n");
E 3
I 3
		logdie("Cannot create temp file");
E 3
	}
	return(fd);
E 15
}
D 11

I 8
#ifdef	DBM_PASSWD
#include <ndbm.h>
E 8
/*
 *	Update the hashed password data base
 */
update_dbm_passwd(theUser, newUser)
struct mpasswd	*theUser;
struct passwd	*newUser;
{
D 8
#ifdef	DBM_PASSWD
E 8
#	define	SCOPY(S) xp = (S); while (*cp++ = *xp++)
D 7
#	define	BCOPY(B) bcopy((char *)&(B), cp, sizeof(int)); cp += sizeof(int)
E 7
I 7
#	define	ICOPY(B) BCOPY((char *)&(B), cp, sizeof(int)); cp += sizeof(int)
E 7

	DBM	*pwd;		/* DBM data base passwd */
	register char	*cp,	/* Data storage pointer */
			*xp;	/* String copy pointer */
	datum	key,		/* DBM key datum */
		data;		/* DBM data store datum */
	char	buf[512];	/* Data buffer */

D 7
	pwd = dbm_open((struct pw_opaque *)theUser->opaque->whichPW->pwfile,
E 7
I 7
	pwd = dbm_open(((struct pw_opaque *)theUser->opaque)->whichPW->pwfile,
E 7
		O_RDWR, 0);
	if (pwd == NULL)
		return;
	cp = buf;
	/* Pack passwd entry in the form expected by the getpw* routines */
D 7
	SCOPY(NewUser->pw_name);
	SCOPY(NewUser->pw_passwd);
	BCOPY(NewUser->pw_uid);
	BCOPY(NewUser->pw_gid);
	BCOPY(NewUser->pw_quota);
	SCOPY(NewUser->pw_comment);
	SCOPY(NewUser->pw_gecos);
	SCOPY(NewUser->pw_dir);
	SCOPY(NewUser->pw_shell);
E 7
I 7
	SCOPY(newUser->pw_name);
	SCOPY(newUser->pw_passwd);
	ICOPY(newUser->pw_uid);
	ICOPY(newUser->pw_gid);
	ICOPY(newUser->pw_quota);
	SCOPY(newUser->pw_comment);
	SCOPY(newUser->pw_gecos);
	SCOPY(newUser->pw_dir);
	SCOPY(newUser->pw_shell);
E 7

	data.dptr = buf;
	data.dsize = cp - buf;
D 7
	key.dptr = theUser.pw_name;
	key.dsize = strlen(NewUser->pw_name);
E 7
I 7
	key.dptr = newUser->pw_name;
	key.dsize = strlen(newUser->pw_name);
E 7
	if (dbm_store(pwd, key, data, DBM_REPLACE) < 0) {
		perror("dbm_store (name)");
D 3
		logdie( "Can't store passwd entry (name key).\n");
E 3
I 3
		logdie("Can't store passwd entry (name key)");
E 3
	}
D 7
	key.dptr = (char *)&NewUser->pw_uid;
E 7
I 7
	key.dptr = (char *)&newUser->pw_uid;
E 7
	key.dsize = sizeof (int);
	if (dbm_store(pwd, key, data, DBM_REPLACE) < 0) {
		perror("dbm_store (uid)");
D 3
		logdie( "Can't store passwd entry (uid key).\n");
E 3
I 3
		logdie("Can't store passwd entry (uid key)");
E 3
	}
	dbm_close(pwd);
I 9
}
E 9
#undef	SCOPY
D 7
#undef	BCOPY
E 7
I 7
#undef	ICOPY
I 8
#else
update_dbm_passwd(theUser, newUser)
struct mpasswd	*theUser;
struct passwd	*newUser;
{
}
E 8
E 7
#endif	/* DBM_PASSWD */
E 11
D 9
}
E 9
/* End %M% */
E 1
