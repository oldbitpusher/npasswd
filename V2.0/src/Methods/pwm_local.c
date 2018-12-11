/*
 * pwm_local.c
 *	Method routines for local password files
 *
 * Exported routines
 *	get_local_user()
 *	put_local_user()
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
 */
#include "npasswd.h"
#include "pwm_defs.h"
#include "passwdtab.h"

#ifndef lint
static char sccsid[] = "@(#)pwm_local.c	1.33 01/17/00 (cc.utexas.edu)";
#endif

/*
 * Size difference tolerated between new and old passwd files
 * Can be set in the configuration file
 */
Config_Value int	PasswdTolerance = PASSWD_DIFF_OK;

#ifdef	USE_NIS
extern struct ypinfo	ypinfo;		/* YP configuration (from pwm_nis.c) */
#endif

/*
 * get_local_user
 *	Look for user in local password files
 * Usage
 *	found = get_local_user(char *user, struct mpasswd *where);
 * Returns
 *	1 if <user> was found if any of the password files listed
 *		in the etc_passwd table (in passwdtab.h).
 *		The user's passwd & shadow entries are stored in meta-passwd
 *		structure pointed to by <where>.
 *	0 if <user> not found
 */
public int
get_local_user(name, mp)
	char	*name;
	struct mpasswd	*mp;
{
	struct passwd_files *whichpw;
	struct passwd	*pwinfo = NULL;
	char	localhost[MAXHOSTNAMLEN];
	struct pw_opaque	*opdata = (struct pw_opaque *)mp->opaque;

	/*
	 * Look in the local flat password file(s)
	 */
	for (whichpw = etc_passwd; whichpw->pwfile; whichpw++) {
		struct stat	pwfstat;

		debug(DB_LOOKUP, "get_local_user: looking for '%s' in \"%s\"\n",
			name, whichpw->pwfile);
		if (lstat(whichpw->pwfile, &pwfstat) < 0)
			continue;
		/*
		 * Sanity check - disallow symlinks (who knows what
		 * they might really point to)
		 */
		if ((pwfstat.st_mode & S_IFLNK) == S_IFLNK) {
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
		if (pwinfo = fgetpwnam(name, whichpw->pwfile)) {
			debug(DB_LOOKUP, "get_local_user: found '%s' in \"%s\"\n",
				name, whichpw->pwfile);
			break;
		}
	}
	if (pwinfo == NULL)		/* Did not find user */
		return(0);
#if	defined(USE_NIS) || defined(USE_NISPLUS)
	if (*pwinfo->pw_name == '+')	/* Ignore YP stub entry */
		return(0);
#endif
	/*
	 * If this machine is a NIS client, the local entry
	 * is ignored unless the -l flag was given (SunOS 4 only).
	 */
#ifdef	USE_NIS
# ifdef	OS_SUNOS_4
	if (ypinfo.status == is_yp_client && !Switches['l'])
		return(0);
# endif
#endif	/* USE_NIS */
	(void) gethostname(localhost, sizeof(localhost));
	mp->pws_loc = strdup(localhost);
	mp->pws_name = "Local";
	opdata->sourcePW = srv_local;
	opdata->whichPW = whichpw;
#ifdef	USE_NIS
	opdata->dbinfo.ypinfo = &ypinfo;
#endif
#ifdef	USE_NISPLUS
	opdata->dbinfo.nisinfo = &nisinfo;
#endif
	(void) copypwent(pwinfo, &mp->pw);
	get_shadow(mp);
#ifdef	PWAGE
# ifdef	OS_HPUX
	/* Sys5 aging HP-UX style */
	if (mp->mpw_age && *mp->mpw_age) {	/*MRS 10/97*/
		extern long a64l();
		char	temp[10],
			*tmpAge;

		temp[0] = mp->mpw_age[0];	/* QUICK and dirty */
		temp[1] = '\0';
		mp->pwage.must_change = a64l(temp);
		temp[0] = mp->mpw_age[1];
		mp->pwage.can_change = a64l(temp);
		tmpAge = &mp->mpw_age[2];	/* The portable way */
		mp->pwage.last_change = a64l(tmpAge);
        }
# else 		/* OS_HPUX */
	/* Generic Sys5 aging */
	if (mp->mpw_age && *mp->mpw_age) {
		time_t pwage = 0;
		extern long	a64l();

		pwage = a64l(mp->mpw_age);
		mp->pwage.must_change = (pwage & 077) * SEC_WEEK;
		mp->pwage.can_change = ((pwage >> 6) & 077) * SEC_WEEK;
		mp->pwage.last_change = (pwage >> 12) * SEC_WEEK;
	}
# endif		/* OS_HPUX */
	debug(DB_LOOKUP,
		"Password aging:\n\tMust change: %ld\n\tCan Change: %ld\n\tLast Change: %ld\n",
		mp->pwage.must_change,
		mp->pwage.can_change,
		mp->pwage.last_change);

#endif 	/* PWAGE */
	return(1);
}

#ifdef	DBM_PASSWD
#include <ndbm.h>
/*
 * update_dbm_passwd
 *	Update the hashed password data base
 * Usage
 *	update_dbm_passwd(struct mpaswd *old, struct mpaswd *new)
 * Errors
 *	Error exit on failure of dbm write
 */
private void
update_dbm_passwd(theUser, newUser)
	struct mpasswd	*theUser;
	struct mpasswd	*newUser;
{
#define	SCOPY(S) xp = (S); if (xp) { while (*cp++ = *xp++); } else { *cp++ = 0; }
#define	ICOPY(B) bcopy((char *)&(B), cp, sizeof(int)); cp += sizeof(int)

	DBM	*pwd;		/* DBM data base passwd */
	char	*cp,		/* Data storage pointer */
		*xp;		/* String copy pointer */
	datum	key,		/* DBM key datum */
		data;		/* DBM data store datum */
	char	buf[512];	/* Data buffer */

	if (theUser == NULL || newUser == NULL)
		/* Post error */
		return;
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
#ifdef	PWQUOTA
	ICOPY(newUser->mpw_quota);
#endif
#ifdef	PWCOMMENT
	SCOPY(newUser->mpw_comment);
#endif
	SCOPY(newUser->mpw_gecos);
	SCOPY(newUser->mpw_dir);
	SCOPY(newUser->mpw_shell);

	data.dptr = buf;
	data.dsize = cp - buf;
	key.dptr = newUser->mpw_name;
	key.dsize = strlen(newUser->mpw_name);
	if (dbm_store(pwd, key, data, DBM_REPLACE) < 0) {
		perror("dbm_store (name)");
		logdie("Can't store passwd entry (name key)\n");
	}
	key.dptr = (char *)&newUser->mpw_uid;
	key.dsize = sizeof (int);
	if (dbm_store(pwd, key, data, DBM_REPLACE) < 0) {
		perror("dbm_store (uid)");
		logdie("Can't store passwd entry (uid key)\n");
	}
	dbm_close(pwd);
#	undef	SCOPY
#	undef	ICOPY
}
#endif	/* DBM_PASSWD */

/*
 * put_local_user
 *	Update local passwd/shadow files
 *
 * Usage
 *	put_local_user(struct mpasswd *old, struct mpasswd *new, int changes);
 * Effects
 *	Updates the appropriate local password file if needed
 *	Updates the appropriate local shadow file if needed
 *	Syncs auxillary databases (DBM hash files, NIS maps)
 * Errors
 *	Failure in file manipulation (creation or renaming)
 *	New password file appears truncated
 */
public void
put_local_user(theUser, newUser, changes)
	struct mpasswd	*theUser;
	struct mpasswd	*newUser;
	int		changes;
{
	FILE	*tf,		/* New password file output */
		*pf;		/* Current password file input */
	int	fd;		/* Temp file create fd */
	int	repdone = 0;	/* Entry was replaced */
	int	mytempfile = 0;	/* Does PASSWD_TEMP belong to me? */
	int	sizediff;	/* Size difference in old & new files */
	struct passwd	*px;	/* Password file traversal */
	struct pw_opaque *aux = (struct pw_opaque *)theUser->opaque;
	struct sigblk	blocked;
	if (changes == 0)
		logdie("Error: put_local_user called with null changes\n");

#ifdef	PWAGE
	/*
	 * Update password aging information
	 */

	debug(DB_DETAIL,"Updating age\nChanges: %d\nAge: %ld\n",
		changes & CHG_PWAGE,newUser->pwage.must_change);

	if (changes & CHG_PWAGE) {
		if ((changes & CHG_PW) &&
		    (newUser->pwage.must_change == 0) &&
		    (newUser->pwage.can_change == 0)) {
			newUser->mpw_age = "";
		}
		else {
			extern char *l64a();
			time_t	now = newUser->pwage.last_change / SEC_WEEK,
				pwage;
#ifdef OS_HPUX
			char	pwtemp[STRINGLEN];
#endif

			if (changes & CHG_PW)
				now = time((time_t *)0) / SEC_WEEK;
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
			pwage = (newUser->pwage.must_change / SEC_WEEK)
				+ ((newUser->pwage.can_change / SEC_WEEK) << 6)
				+ (now << 12);
			if (pwage)
				newUser->mpw_age = l64a(pwage);
			else
				newUser->mpw_age = ".";
#endif
		}
	}
#endif	/* PWAGE */
	/*
	 * The shadow file holds the encrypted password
	 * and password aging information.
	 */
	if ((changes & (CHG_PW | CHG_PWAGE)) &&
	     aux->sourceSH == srv_local) {
		update_shadow(theUser, newUser);
		return;		/* Our work is done */
	}
	/*
	 * Update the local passwd file.
	 */
	if ((pf = fopen(aux->whichPW->pwfile, "r")) == NULL)
		logdie("Cannot open password file \"%s\".\n",
			aux->whichPW->pwfile);
	/*
	 * This deals with the SunOS yppasswdd which creates temp files
	 * named "passwd-file.ptmp", rather than the traditional "/etc/ptmp".
	 *
	 * But there are still a lot of applications which use /etc/ptmp,
	 * so is it used as the passwd temp file and the 'auxlockfile' is
	 * also made.
	 */
#ifdef	USE_NIS
	if (ypinfo.status == is_yp_master && aux->whichPW->lockfile) {
#else
	if (aux->whichPW->lockfile) {
#endif
		mytempfile = 1;
		(void) close(MakeLockTemp(aux->whichPW->lockfile));
	}
	fd = MakeLockTemp(aux->whichPW->tempfile);

#if	defined(HAS_FCHOWN) && defined(HAS_FCHMOD)
	if (fchown(fd, PASSWD_UID, PASSWD_GID) < 0)
# if	(CDEBUG < CDEBUG_SYSTEM)
		logdie("Passwd temp fchown error %d\n", errno);
# else
		warn("Passwd temp fchown error %d\n", errno);
# endif
	if (fchmod(fd, PASSWD_MODE) < 0)
# if	(CDEBUG < CDEBUG_SYSTEM)
		logdie("Passwd temp fchmod error %d\n", errno);
# else
		warn("Passwd temp fchmod error %d\n", errno);
# endif
#else
	FixPwFileMode(aux->whichPW->tempfile, "passwd");
#endif

	if ((tf = fdopen(fd, "w")) == NULL) {
		if (mytempfile)
			(void) unlink(aux->whichPW->lockfile);
		logdie("Cannot fdopen temp file \"%s\".\n",
			aux->whichPW->tempfile);
	}
	debug(DB_UPDATE, "put_local_user: replace %s in \"%s\"\n",
		newUser->mpw_name, aux->whichPW->pwfile);
	zeromem(&blocked, sizeof blocked);
#if	(CDEBUG < CDEBUG_SYSTEM)
	block_signals(&blocked, SIGHUP, SIGINT, SIGQUIT, SIGTSTP, 0);
#endif

	while ((px = fgetpwent(pf)) != NULL) {
		if (px->pw_name == 0 || px->pw_name[0] == 0) /* Sanity check */
			continue;
		if (!repdone && strcmp(px->pw_name, theUser->mpw_name) == 0) {
			/*
			 * The password and aging fields changes
			 * won't make it here if a shadow file exists
			 */
#ifdef	PWAGE
			if (changes & CHG_PWAGE)
				px->pw_age = newUser->mpw_age;
			else
				px->pw_age = "";
#endif
			if (changes & CHG_PW)
				px->pw_passwd = newUser->mpw_passwd;
			if (changes & CHG_GECOS)
				px->pw_gecos = newUser->mpw_gecos;
			if (changes & CHG_SHELL)
				px->pw_shell = newUser->mpw_shell;
			repdone++;
		}
		(void) putpwent(px, tf);
	}
	(void) fflush(tf);
	(void) fclose(tf);
	(void) fclose(pf);

	if (mytempfile) {		/* Need to discard lock? */
		(void) unlink(aux->whichPW->lockfile);
		mytempfile = 0;
	}
	if (repdone == 0) {		/* Nothing changed? */
		(void) unlink(aux->whichPW->tempfile);
		unblock_signals(&blocked);
		return;
	}
	/*
	 * Check if the new password file is complete.
	 * There is an assumption here that changing one passwd entry should
	 * not change the total size of the file more than <PasswdTolerance>
	 * bytes.  In order to accomodate GECOS changes, this threshold has to
	 * be generous, maybe too generous.  But if the disk really did fill up,
	 * then we will proabably lose big enough to notice.
	 *
	 * If the new file is longer, don't worry.  If shorter, that's 
	 * alright if the difference is less than <PasswdTolerance>, otherwise
	 * assume that the new file got truncated and bail.
	 *
	 * The alternative is to not use stdio for the temp file I/O, or
	 * force a fflush() after each putpwent() and rely upon fflush to
	 * return the right error code.  Not something to bet /etc/passwd on.
	 * I'm not about to reach behind stdio's back and manipulate
	 * buffer pointers and counters.  There Lie Dragons...
	 *
	 * Check the sizes and assume that will catch most errors.
	 */
	sizediff = ( FileSize(aux->whichPW->tempfile) -
		     FileSize(aux->whichPW->pwfile)) + PasswdTolerance;
	if (sizediff < 0) {
#ifdef	SHORT_FILE_WARN
		logerr("Password temp is %d bytes short\n", abs(sizediff));
#else
		logdie("Passwd temp is %d bytes short\n", abs(sizediff));
#endif
	}
	debug(DB_UPDATE,
		"put_local_user: Install passwd '%s', temp '%s', save '%s'\n",
		aux->whichPW->pwfile, aux->whichPW->tempfile,
		aux->whichPW->savefile);

	(void) unlink(aux->whichPW->savefile);
	if (link(aux->whichPW->pwfile, aux->whichPW->savefile) < 0) {
		perror("Password file save");
		(void) unlink(aux->whichPW->tempfile);
		logdie("Cannot save password file");
	}
	if (rename(aux->whichPW->tempfile, aux->whichPW->pwfile) < 0) {
		perror("Password file replace");
		(void) unlink(aux->whichPW->tempfile);
		(void) link(aux->whichPW->savefile, aux->whichPW->pwfile);
		(void) unlink(aux->whichPW->savefile);
		logdie("Cannot replace password file");
	}
#ifdef	DBM_PASSWD
	update_dbm_passwd(theUser, newUser);
#endif	/* DBM_PASSWD */
#ifdef	USE_NIS
	/*
	 * If on the YP master, try to update the DBM map files
	 */
	if (ypinfo.status == is_yp_master) {
		char	pwline[PW_LINELEN],
			uidx[16];

		(void) sputpwent(&newUser->pw, pwline);
		update_yp_map(newUser->mpw_name, pwline, PASSWD_BYNAME,
			ypinfo.data, 0);
#ifdef  UIDS_ARE_SIGNED
		(void) sprintf(uidx, "%d", newUser->mpw_uid);
#else	/* UIDS_ARE_SIGNED */
		(void) sprintf(uidx, "%u", newUser->mpw_uid);
#endif	/* UIDS_ARE_SIGNED */
		update_yp_map(uidx, pwline, PASSWD_BYUID, ypinfo.data, 0);
	}
#endif	/* USE_NIS */
	unblock_signals(&blocked);
}
/* End pwm_local.c */
