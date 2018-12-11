h40085
s 00014/00004/00301
d D 1.15 98/10/13 15:38:51 clyde 15 14
c 1. A bit more debugging in put_shadow()
c 2. Fix shadow temp size check 
c 3. Add SHORT_FILE_WARN define to control short temp file behavior
e
s 00015/00000/00290
d D 1.14 98/07/20 15:20:42 clyde 14 13
c Add no-nop check_auth()
e
s 00012/00012/00278
d D 1.13 98/06/23 10:59:06 clyde 13 12
c Change compile-time debug include trigger
e
s 00001/00005/00289
d D 1.12 98/04/28 16:49:02 clyde 12 11
c Use zeromem() macro
e
s 00001/00001/00293
d D 1.11 98/03/31 14:35:41 clyde 11 10
c Fix unintialized var in get_shadow()
e
s 00015/00002/00279
d D 1.10 97/05/05 11:24:30 clyde 10 9
c Retry lckpwdf() LockTries times
e
s 00061/00030/00220
d D 1.9 96/08/13 16:49:09 clyde 9 8
c 1. Add lots of comments
c 2. Change size check test
c 3. Better error checks
e
s 00064/00011/00186
d D 1.8 96/08/06 14:13:54 clyde 8 7
c beta 3 cycle 1 checkin
e
s 00006/00006/00191
d D 1.7 96/04/03 14:35:04 clyde 7 6
c Reflect new mpasswd structure element names
e
s 00029/00023/00168
d D 1.6 96/03/29 11:36:43 clyde 6 5
c 1. Add more comments
c 2. Deal with NIS stubs in shadow files
c 3. More debugging hooks
c 4. Deal better with non-local shadow entries
e
s 00030/00024/00161
d D 1.5 96/03/27 09:32:41 clyde 5 4
c 1. se debug() routine for messages
c 2. Traverse list of shadow files looking for user
c 3. Remove debris
e
s 00005/00025/00180
d D 1.4 95/04/05 16:20:06 clyde 4 3
c Beta 3 development checkin
e
s 00001/00001/00204
d D 1.3 94/11/03 15:19:09 clyde 3 2
c Use link instead of rename to save shadow file
e
s 00001/00001/00204
d D 1.2 94/09/28 16:26:29 clyde 2 1
c Fix routine name
e
s 00205/00000/00000
d D 1.1 94/09/28 16:16:32 clyde 1 0
c date and time created 94/09/28 16:16:32 by clyde
e
u
U
f e 0
t
T
I 1
/*
D 9
 *	%M% - Support for System 5-style shadow files
E 9
I 9
 * %M%
 *	Support for System 5 shadow files
E 9
 *
D 9
 *	Two routines need to advertised from this module:
E 9
I 9
 * Exported routines
 *	get_shadow();
 *	update_shadow()
E 9
 *
D 9
 *	void get_shadow(struct mpasswd *theUser)
 *		This routine checks if the password is in a shadow database
 *		and fetches it if so.  Information is stashed in the 
 *		"method" data about where the shadow password was found.
E 9
I 9
 * Exported variables
 *	ShadowTolerance
E 9
 *
D 9
 *	void update_shadow(struct mpasswd *theUser, struct mpasswd *newUser)
 *		Updates the shadow password for "newUser".
 *		
D 6
 *
E 6
 *	Neither routine returns a value, but changes the meta-passwd record
D 6
 *	passed in, and aborts on serious error.
E 6
I 6
 *	passed in and aborts on serious error.
E 9
E 6
 */
#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu)";
#endif

#include "npasswd.h"
#include "pwm_defs.h"
I 4
#include "shadowtab.h"
E 4

D 4
#ifdef	S5_SHADOW

E 4
#include <shadow.h>

D 8
#define	SHADOW_SIZE_SLOP	32
E 8
I 8
D 9
Config_Value int	shadow_tolerance = 32;
E 9
I 9
/*
 * Size difference tolerated between new and old shadow files
 * Can be set in the configuration file
 */
D 13
Config_Value int	ShadowTolerance = SHDAOW_DIFF_OK;
E 13
I 13
Config_Value int	ShadowTolerance = SHADOW_DIFF_OK;
E 13
E 9
E 8

D 4
#ifndef	OS_SOLARIS_2
E 4
I 4
#ifndef	HAS_LCKPWDF
E 4
# define	ulckpwdf()	(1)
# define	lckpwdf()	(1)
#endif

D 4
#ifdef	OS_AIX
# define	SHADOW_MARKER	"!"
#else
# define	SHADOW_MARKER	"x"
#endif

E 4
/*
D 4
 * Table of possible places for the shadow file to live
 */
private struct passwd_files shadowfiles[]  = {
#ifdef	DEBUG_FILES
	{ "./etc_shadow", "./etc_stmp", "./etc_oshadow", 0 },
#endif
	{ SHADOW, SHADTEMP, OSHADOW,  0 },
	{ 0 }
};

/*
E 4
D 9
 * Check if the password is in the shadow datbase
E 9
I 9
 * get_shadow
 *	Look for a user is in the shadow files.
 *	The user's shadow information is stored in <user>
 *
 * Usage
 *	get_shadow(struct mpasswd *user);
 * Error exits
 *	Failure to find any shadow information for <user> if the passwd
 *	entry indicates that shadow entry should exist
E 9
 */
public void
get_shadow(userm)
	struct mpasswd *userm;
{
D 6
	struct passwd_files *shp;
	struct spwd	*si;
	struct pw_opaque *po = userm->opaque;
E 6
I 6
	struct passwd_files *shp;	/* Pointer in shadow file list */
D 11
	struct spwd	*si;		/* Shadow passwd entry */
E 11
I 11
	struct spwd	*si = NULL;	/* Shadow passwd entry */
E 11
	struct pw_opaque *po = userm->opaque;	/* Metadata */
E 6

D 6
	if (strcmp(userm->mpw_passwd, "x"))
		return;
E 6
I 6
D 8
	if (strcmp(userm->mpw_passwd, "x"))	/* Is this the right */
		return;				/* cookie for all systems? */
E 8
I 8
	switch (*userm->mpw_passwd) {
		case 'x':	break;	/* System 5 */
		case '!':	break;	/* AIX */
		default:	return;
	}
E 8
E 6

D 5
	if ((si = getspnam(userm->mpw_name)) == NULL)
E 5
I 5
D 6
#ifdef	DEBUGXXX
	/* Maybe not ... */
	if ((si = getspnam(userm->mpw_name)) == NULL) {
E 5
		logdie("Cannot get password for %s from shadow",
I 5
		userm->mpw_name);
	}
#endif
E 6
I 6
	/*
	 * Look for the user in the list of shadow files
	 */
E 6
	for (shp = etc_shadow; shp->pwfile; shp++) {
		FILE	*spf;

		if ((spf = fopen(shp->pwfile, "r")) == NULL)
			continue;
		debug(DB_LOOKUP, "get_shadow: look for for %s in \"%s\"\n",
			userm->mpw_name, shp->pwfile);
		while (si = fgetspent(spf)) {
D 6
			if (strcmp(userm->mpw_name, si->sp_namp) == 0) {
				debug(DB_LOOKUP,"get_shadow: found shadow for %s in \"%s\"\n",
					userm->mpw_name, shp->pwfile);
E 6
I 6
			char	*shm = si->sp_namp;

			if (*shm == '+') continue;	/* Ignore NIS stubs */
			if (strcmp(userm->mpw_name, shm) == 0) {
				debug(DB_LOOKUP,
					"get_shadow: found shadow for %s\n",
					userm->mpw_name);
				po->whichSH = shp;
				po->sourceSH = srv_local;
E 6
				break;
			}
		}
		(void) fclose(spf);
		if (si != NULL)
			break;
	}
D 6
	if (si == NULL) {
		logdie("Cannot get password for %s from shadow",
E 5
			userm->mpw_name);
E 6
I 6
	if (si == NULL) {		/* No local shadow entry */
		if ((si = getspnam(userm->mpw_name)) == NULL) {
			/* No shadow entry found anywhere */
			logdie("Cannot get password for %s from shadow",
				userm->mpw_name);
		}
E 6
I 5
	}
D 6
	po->whichSH = shp;
E 6
I 6
	/*
	 * Copy shadow data to user metadata
	 */
E 6
E 5
D 8
	userm->mpw_passwd = copystr(si->sp_pwdp);
E 8
I 8
	userm->mpw_passwd = strdup(si->sp_pwdp);
E 8
D 6
	po->sourceSH = srv_local;
E 6
	userm->pwage.last_change = si->sp_lstchg;
D 7
	userm->pwage.min_time = si->sp_min;
	userm->pwage.max_time = si->sp_max;
E 7
I 7
	userm->pwage.can_change = si->sp_min;
	userm->pwage.must_change = si->sp_max;
E 7
D 5
	/*
	 * Find the adjunct password file
	 */
D 4
	for (shp = shadowfiles; shp->pwfile; shp++) {
E 4
I 4
	for (shp = etc_shadow; shp->pwfile; shp++) {
E 4
		if (access(shp->pwfile, 0) == 0)
			break;
	}
	if (DebugLevel >= DB_LOOKUP) {
		printf("get_shadow: shadow pw for %s in \"%s\"\n",
			userm->mpw_name, shp->pwfile);
		fflush(stdout);
	}
	/*
	 * I assume that the first shadow file found
	 * is the correct one - they don't tend to move around
	 * like /etc/passwd does.
	 */
	po->whichSH = shp;
E 5
}

I 9
/*
 * update_shadow
 *	Update local shadow file
 *
 * Usage
 *	update_shadow(struct mpasswd *old-data, struct mpasswd *new-data);
 * Error exits
 *	Failure to find any shadow information for <user> if the passwd
 *	entry indicates that shadow entry should exist
 */
E 9
public void
D 2
update_local_shadow(theUser, newUser)
E 2
I 2
update_shadow(theUser, newUser)
E 2
	struct mpasswd	*theUser;
	struct mpasswd	*newUser;
{
	FILE	*tf,		/* New password file output */
		*pf;		/* Current password file input */
D 5
	char	adjline[BUFSIZ];	/* Adjunct line to stuff in YP map */
E 5
	int	fd;		/* Temp file create fd */
I 10
	int	cnt;		/* Lock retry counter */
E 10
	int	repdone = 0;	/* Entry was replaced */
D 9
	time_t	now;
	size_t	sizediff;
	struct pw_opaque *aux = (struct pw_opaque *)theUser->opaque;
E 9
I 9
	time_t	now;		/* Current time */
D 15
	size_t	sizediff;	/* Temp/shadow file size difference */
E 15
I 15
	int	sizediff;	/* Temp/shadow file size difference */
E 15
	struct pw_opaque *aux = (struct pw_opaque *)theUser->opaque; /* Metadata */
E 9
	struct spwd	*px;	/* Shadow file traversal */
D 9
	struct sigblk	blocked;
E 9
I 9
	struct sigblk	blocked;	/* Signal blocker */
E 9

D 8
	fd = mklocktemp(aux->whichSH->tempfile);
E 8
I 8
	fd = MakeLockTemp(aux->whichSH->tempfile);

#if     defined(HAS_FCHOWN) && defined(HAS_FCHMOD)
D 9
	(void) fchown(fd, SHADOW_UID, SHADOW_GID);
	(void) fchmod(fd, SHADOW_MODE);
E 9
I 9
	if (fchown(fd, SHADOW_UID, SHADOW_GID) < 0)
D 13
# ifdef	DEBUG
		warn("Shadow temp fchown error %d\n", errno);
# else
E 13
I 13
# if	(CDEBUG < CDEBUG_SYSTEM)
E 13
		logdie("Shadow temp fchown error %d\n", errno);
D 13
#endif
	if (fchmod(fd, SHADOW_MODE) < 0)
# ifdef	DEBUG
		warn("Shadow temp fchmod error %d\n", errno);
E 13
# else
I 13
		warn("Shadow temp fchown error %d\n", errno);
# endif
	if (fchmod(fd, SHADOW_MODE) < 0)
# if	(CDEBUG < CDEBUG_SYSTEM)
E 13
		logdie("Shadow temp fchmod error %d\n", errno);
D 13
#endif
E 13
I 13
# else
		warn("Shadow temp fchmod error %d\n", errno);
# endif
E 13
E 9
#else
	FixPwFileMode(aux->whichSH->tempfile, "shadow");
#endif
I 9

E 9
E 8
	if ((tf = fdopen(fd, "w")) == NULL) {
I 10
		(void) unlink(aux->whichSH->tempfile);
E 10
		logdie("Cannot fdopen shadow temp file \"%s\".\n",
			aux->whichSH->tempfile);
	}
	if ((pf = fopen(aux->whichSH->pwfile, "r")) == NULL) {
I 10
		(void) unlink(aux->whichSH->tempfile);
E 10
		logdie("Cannot open shadow file \"%s\".\n",
			aux->whichSH->pwfile);
	}
D 5
	if (DebugLevel >= DB_UPDATE) {
		printf("Modifying shadow file \"%s\"\n", aux->whichSH->pwfile);
		fflush(stdout);
	}
E 5
I 5
	debug(DB_UPDATE, "update_shadow: shadow file \"%s\"\n",
		aux->whichSH->pwfile);
E 5
D 9

#ifndef	DEBUG
E 9
I 9
D 12
#ifdef HAS_MEMSET
	(void) memset((void *)&blocked, 0, sizeof blocked);
#else
E 9
D 4
	BZERO((char *)&blocked, sizeof blocked);
E 4
I 4
	bzero((char *)&blocked, sizeof blocked);
I 9
#endif
E 12
I 12
	zeromem((char *)&blocked, sizeof blocked);
E 12
D 13
#ifndef	DEBUG
E 13
I 13
#if	(CDEBUG < CDEBUG_SYSTEM)
E 13
E 9
E 4
	block_signals(&blocked, SIGHUP, SIGINT, SIGQUIT, SIGTSTP, 0);
#endif
D 10
	if (lckpwdf() < 0)
		logdie("Cannot lock shadow/password file\n");
E 10
I 10
	for (cnt = 0; cnt <= LockTries; cnt++) {
		if (lckpwdf() < 0) {
			if (cnt == LockTries) {
				(void) unlink(aux->whichSH->tempfile);
				logdie("Cannot lock shadow/password file\n");
			}
			debug(DB_DETAIL, "update_shadow: Lock cycle %d\n", cnt);
			(void) sleep(LockCycle);
		} else {
			break;
		}
	}
E 10
	now = time((time_t *)0);
	while ((px = fgetspent(pf)) != NULL) {
		if (px->sp_namp == 0 || px->sp_namp[0] == 0)
			continue;
		if (repdone) {
			(void) putspent(px, tf);
			continue;
		}
		if (strcmp(px->sp_namp, theUser->mpw_name) == 0) {
			px->sp_pwdp = newUser->mpw_passwd;
D 8
			px->sp_lstchg = now / SEC_PER_DAY;
E 8
I 8
			px->sp_lstchg = now / SEC_DAY;
E 8
D 7
			if (newUser->pwage.min_time)
				px->sp_min = newUser->pwage.min_time;
			if (newUser->pwage.max_time)
				px->sp_max = newUser->pwage.max_time;
E 7
I 7
			if (newUser->pwage.can_change)
				px->sp_min = newUser->pwage.can_change;
			if (newUser->pwage.must_change)
				px->sp_max = newUser->pwage.must_change;
E 7
D 4
			(void) putspent(px, tf);
E 4
			repdone++;
I 6
			debug(DB_UPDATE, "update_shadow: replaced entry for %s\n",
				theUser->mpw_name);
E 6
		}
		(void) putspent(px, tf);
	}
	(void) fclose(tf);
	(void) fclose(pf);

	if (repdone == 0) {
		(void) unlink(aux->whichSH->tempfile);
		(void) ulckpwdf();
D 13
#ifndef	DEBUG
E 13
I 13
#if	(CDEBUG < CDEBUG_SYSTEM)
E 13
		unblock_signals(&blocked);
#endif
		return;
	}
	/*
	 * Check if the new shadow file is complete.
	 * There is an assumption here that changing one passwd entry should
D 8
	 * not change the total size of the file more than SHADOW_SIZE_SLOP
E 8
I 8
D 9
	 * not change the total size of the file more than shadow_tolerance
E 9
I 9
	 * not change the total size of the file more than <ShadowTolerance>
E 9
E 8
	 * bytes.
	 *
	 * If the new file is longer, don't worry.  If shorter, that's 
D 8
	 * alright if the difference is less than SHADOW_SIZE_SLOP, otherwise
E 8
I 8
D 9
	 * alright if the difference is less than shadow_tolerance, otherwise
E 9
I 9
	 * alright if the difference is less than <ShadowTolerance>, otherwise
E 9
E 8
	 * assume that the new file got truncated and bail.
	 *
	 * The alternative is to not use stdio for the temp file I/O, or
	 * force a fflush() after each putspent() and rely upon fflush to
	 * return the right error code.  Either way, we take a performance hit.
	 *
	 * So check the sizes and assume that will catch most errors.
	 */
D 8
	sizediff = cmp_file_size(aux->whichSH->tempfile, aux->whichSH->pwfile);
	if (sizediff < 0 && abs(sizediff) > SHADOW_SIZE_SLOP) {
E 8
I 8
D 15
	sizediff = FileSizeDiff(aux->whichSH->tempfile, aux->whichSH->pwfile);
D 9
	if (sizediff < 0 && abs(sizediff) > shadow_tolerance) {
E 8
		logdie("New shadow file is too short by %lu bytes\n",
			sizediff);
	}
E 9
I 9
	sizediff += ShadowTolerance;
	if (sizediff < 0)
E 15
I 15
	sizediff = ( FileSize(aux->whichSH->tempfile) -
		     FileSize(aux->whichSH->pwfile)) + ShadowTolerance;
	if (sizediff < 0) {
#ifdef	SHORT_FILE_WARN
		logerr("Shadow temp is %d bytes short\n", abs(sizediff));
#else
E 15
		logdie("Shadow temp is %d bytes short\n", abs(sizediff));
I 15
#endif
	}
E 15

I 15
	debug(DB_UPDATE,
		"update_shadow: Install shadow '%s', temp '%s', save '%s'\n",
		aux->whichSH->pwfile, aux->whichSH->tempfile,
		aux->whichSH->savefile);

E 15
E 9
D 8
	set_protection(aux->whichSH->tempfile, "shadow");
E 8
I 4
	(void) unlink(aux->whichSH->savefile);
E 4
D 3
	if (rename(aux->whichSH->pwfile, aux->whichSH->savefile) < 0) {
E 3
I 3
	if (link(aux->whichSH->pwfile, aux->whichSH->savefile) < 0) {
E 3
		perror("shadow file save");
		(void) unlink(aux->whichSH->tempfile);
		(void) ulckpwdf();
		logdie("Failed to save shadow file.\n");
	}
	if (rename(aux->whichSH->tempfile, aux->whichSH->pwfile) < 0) {
		perror("shadow file replace");
		(void) unlink(aux->whichSH->tempfile);
		(void) link(aux->whichSH->savefile, aux->whichSH->pwfile);
		(void) ulckpwdf();
		logdie("Failed to replace shadow file.\n");
	}
D 13
#ifndef	DEBUG
E 13
I 13
#if	(CDEBUG < CDEBUG_SYSTEM)
E 13
	unblock_signals(&blocked);
#endif
	(void) ulckpwdf();
D 4
	newUser->mpw_passwd = SHADOW_MARKER;
E 4
}
I 14
/*
 * check_auth
 *	Check the password change bits in auth database (no-op)
 * Usage:
 *	check_auth(struct mpasswd *)
 * Returns:
 *	allow = always
 */
public enum chg_perm
check_auth(theUser)
        struct mpasswd *theUser;
{
	return(allow);
}
E 14
I 8

I 14

E 14
#if	0
I 9
/* These routines aren't ready  yet */
E 9
public void
unpack_pwage(theUser, shinfo)
	struct mpasswd	*theUser;
	char		*shinfo;
{
D 9
	char	*p = shinfo;
#define skipc while (*p && *p != ':' && *p != '\n') ++p; if (*p) *p++ = 0
E 9
I 9
	char	**shl = split(shinfo, ':', 0,0,0);
E 9

        theUser->pwage.last_change = ( *p != ':' ? atol(p) : -1); skipc;
        theUser->pwage.can_change = ( *p != ':' ? atol(p) : -1); skipc;
        theUser->pwage.must_change = ( *p != ':' ? atol(p) : -1); skipc;
        theUser->pwage.warn_user = ( *p != ':' ? atol(p) : -1); skipc;
D 9
#undef	skipc
E 9
}

char *
pack_pwage(theUser, oshadow)
	struct mpasswd	*theUser;
	char	*oshadow;
{
	char	newshadow[64];
	char	nb[16];

#define shadd(_I_, _V_,_F_) nb[0] = 0; \
	if (_I_ != _V_) sprintf(nb, _F_, _I_); \
	strcat(newshadow, nb); strcat(newshadow, ":");

	newshadow[0] = 0;
	shadd(theUser->pwage.last_change, -1, "%ld");
	shadd(theUser->pwage.can_change, -1, "%ld");
	shadd(theUser->pwage.must_change, -1, "%ld");
	shadd(theUser->pwage.warn_user, -1, "%ld");
	shadd(shp->sp_inact, -1, "%ld");
	shadd(shp->sp_expire, -1, "%ld");
	shadd(shp->sp_flag, 0, "%lu");
	p = strrchr(newshadow, ':');
	*p = 0;
#undef  shadd
	return(newshadow);
}
#endif

E 8
D 4
#endif	/* S5_SHADOW */
E 4
D 6

E 6
/* End %M% */
E 1
