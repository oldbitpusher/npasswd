/*
 * shm_shadow.c
 *	Support for System 5 shadow files
 *
 * Exported routines
 *	get_shadow();
 *	update_shadow()
 *
 * Exported variables
 *	ShadowTolerance
 *
 */
#ifndef lint
static char sccsid[] = "@(#)shm_shadow.c	1.15 10/13/98 (cc.utexas.edu)";
#endif

#include "npasswd.h"
#include "pwm_defs.h"
#include "shadowtab.h"

#include <shadow.h>

/*
 * Size difference tolerated between new and old shadow files
 * Can be set in the configuration file
 */
Config_Value int	ShadowTolerance = SHADOW_DIFF_OK;

#ifndef	HAS_LCKPWDF
# define	ulckpwdf()	(1)
# define	lckpwdf()	(1)
#endif

/*
 * get_shadow
 *	Look for a user is in the shadow files.
 *	The user's shadow information is stored in <user>
 *
 * Usage
 *	get_shadow(struct mpasswd *user);
 * Error exits
 *	Failure to find any shadow information for <user> if the passwd
 *	entry indicates that shadow entry should exist
 */
public void
get_shadow(userm)
	struct mpasswd *userm;
{
	struct passwd_files *shp;	/* Pointer in shadow file list */
	struct spwd	*si = NULL;	/* Shadow passwd entry */
	struct pw_opaque *po = userm->opaque;	/* Metadata */

	switch (*userm->mpw_passwd) {
		case 'x':	break;	/* System 5 */
		case '!':	break;	/* AIX */
		default:	return;
	}

	/*
	 * Look for the user in the list of shadow files
	 */
	for (shp = etc_shadow; shp->pwfile; shp++) {
		FILE	*spf;

		if ((spf = fopen(shp->pwfile, "r")) == NULL)
			continue;
		debug(DB_LOOKUP, "get_shadow: look for for %s in \"%s\"\n",
			userm->mpw_name, shp->pwfile);
		while (si = fgetspent(spf)) {
			char	*shm = si->sp_namp;

			if (*shm == '+') continue;	/* Ignore NIS stubs */
			if (strcmp(userm->mpw_name, shm) == 0) {
				debug(DB_LOOKUP,
					"get_shadow: found shadow for %s\n",
					userm->mpw_name);
				po->whichSH = shp;
				po->sourceSH = srv_local;
				break;
			}
		}
		(void) fclose(spf);
		if (si != NULL)
			break;
	}
	if (si == NULL) {		/* No local shadow entry */
		if ((si = getspnam(userm->mpw_name)) == NULL) {
			/* No shadow entry found anywhere */
			logdie("Cannot get password for %s from shadow",
				userm->mpw_name);
		}
	}
	/*
	 * Copy shadow data to user metadata
	 */
	userm->mpw_passwd = strdup(si->sp_pwdp);
	userm->pwage.last_change = si->sp_lstchg;
	userm->pwage.can_change = si->sp_min;
	userm->pwage.must_change = si->sp_max;
}

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
public void
update_shadow(theUser, newUser)
	struct mpasswd	*theUser;
	struct mpasswd	*newUser;
{
	FILE	*tf,		/* New password file output */
		*pf;		/* Current password file input */
	int	fd;		/* Temp file create fd */
	int	cnt;		/* Lock retry counter */
	int	repdone = 0;	/* Entry was replaced */
	time_t	now;		/* Current time */
	int	sizediff;	/* Temp/shadow file size difference */
	struct pw_opaque *aux = (struct pw_opaque *)theUser->opaque; /* Metadata */
	struct spwd	*px;	/* Shadow file traversal */
	struct sigblk	blocked;	/* Signal blocker */

	fd = MakeLockTemp(aux->whichSH->tempfile);

#if     defined(HAS_FCHOWN) && defined(HAS_FCHMOD)
	if (fchown(fd, SHADOW_UID, SHADOW_GID) < 0)
# if	(CDEBUG < CDEBUG_SYSTEM)
		logdie("Shadow temp fchown error %d\n", errno);
# else
		warn("Shadow temp fchown error %d\n", errno);
# endif
	if (fchmod(fd, SHADOW_MODE) < 0)
# if	(CDEBUG < CDEBUG_SYSTEM)
		logdie("Shadow temp fchmod error %d\n", errno);
# else
		warn("Shadow temp fchmod error %d\n", errno);
# endif
#else
	FixPwFileMode(aux->whichSH->tempfile, "shadow");
#endif

	if ((tf = fdopen(fd, "w")) == NULL) {
		(void) unlink(aux->whichSH->tempfile);
		logdie("Cannot fdopen shadow temp file \"%s\".\n",
			aux->whichSH->tempfile);
	}
	if ((pf = fopen(aux->whichSH->pwfile, "r")) == NULL) {
		(void) unlink(aux->whichSH->tempfile);
		logdie("Cannot open shadow file \"%s\".\n",
			aux->whichSH->pwfile);
	}
	debug(DB_UPDATE, "update_shadow: shadow file \"%s\"\n",
		aux->whichSH->pwfile);
	zeromem((char *)&blocked, sizeof blocked);
#if	(CDEBUG < CDEBUG_SYSTEM)
	block_signals(&blocked, SIGHUP, SIGINT, SIGQUIT, SIGTSTP, 0);
#endif
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
			px->sp_lstchg = now / SEC_DAY;
			if (newUser->pwage.can_change)
				px->sp_min = newUser->pwage.can_change;
			if (newUser->pwage.must_change)
				px->sp_max = newUser->pwage.must_change;
			repdone++;
			debug(DB_UPDATE, "update_shadow: replaced entry for %s\n",
				theUser->mpw_name);
		}
		(void) putspent(px, tf);
	}
	(void) fclose(tf);
	(void) fclose(pf);

	if (repdone == 0) {
		(void) unlink(aux->whichSH->tempfile);
		(void) ulckpwdf();
#if	(CDEBUG < CDEBUG_SYSTEM)
		unblock_signals(&blocked);
#endif
		return;
	}
	/*
	 * Check if the new shadow file is complete.
	 * There is an assumption here that changing one passwd entry should
	 * not change the total size of the file more than <ShadowTolerance>
	 * bytes.
	 *
	 * If the new file is longer, don't worry.  If shorter, that's 
	 * alright if the difference is less than <ShadowTolerance>, otherwise
	 * assume that the new file got truncated and bail.
	 *
	 * The alternative is to not use stdio for the temp file I/O, or
	 * force a fflush() after each putspent() and rely upon fflush to
	 * return the right error code.  Either way, we take a performance hit.
	 *
	 * So check the sizes and assume that will catch most errors.
	 */
	sizediff = ( FileSize(aux->whichSH->tempfile) -
		     FileSize(aux->whichSH->pwfile)) + ShadowTolerance;
	if (sizediff < 0) {
#ifdef	SHORT_FILE_WARN
		logerr("Shadow temp is %d bytes short\n", abs(sizediff));
#else
		logdie("Shadow temp is %d bytes short\n", abs(sizediff));
#endif
	}

	debug(DB_UPDATE,
		"update_shadow: Install shadow '%s', temp '%s', save '%s'\n",
		aux->whichSH->pwfile, aux->whichSH->tempfile,
		aux->whichSH->savefile);

	(void) unlink(aux->whichSH->savefile);
	if (link(aux->whichSH->pwfile, aux->whichSH->savefile) < 0) {
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
#if	(CDEBUG < CDEBUG_SYSTEM)
	unblock_signals(&blocked);
#endif
	(void) ulckpwdf();
}
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


#if	0
/* These routines aren't ready  yet */
public void
unpack_pwage(theUser, shinfo)
	struct mpasswd	*theUser;
	char		*shinfo;
{
	char	**shl = split(shinfo, ':', 0,0,0);

        theUser->pwage.last_change = ( *p != ':' ? atol(p) : -1); skipc;
        theUser->pwage.can_change = ( *p != ':' ? atol(p) : -1); skipc;
        theUser->pwage.must_change = ( *p != ':' ? atol(p) : -1); skipc;
        theUser->pwage.warn_user = ( *p != ':' ? atol(p) : -1); skipc;
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

/* End shm_shadow.c */
