/*
 *	shm_adjunct.c - Support for Sun adjunct password files
 *
 *	Two routines need to advertised from this module:
 *
 *	void get_shadow(struct mpasswd *theUser)
 *		This routine checks if the password is in a shadow database
 *		and fetches it if so.  Information is stashed in the 
 *		"method" data about where the shadow password was found.
 *
 *	void update_shadow(struct mpasswd *theUser, struct mpasswd *newUser)
 *		Updates the shadow password for "newUser".
 *		
 *
 *	Neither routine returns a value, but changes the meta-passwd record
 *	passed in, and aborts on serious error.
 */
#ifndef lint
static char sccsid[] = "@(#)shm_adjunct.c	1.11 01/17/00 (cc.utexas.edu)";
#endif

#include "npasswd.h"
#include "pwm_defs.h"
#include "shadowtab.h"

Config_Value	int	ShadowTolerance = SHADOW_DIFF_OK;

/*
 * Support for Solaris 1 (SunOS 4.X) adjunct passwords
 */
#define ADJUNCT_BYNAME  "passwd.adjunct.byname"

#include <sys/label.h>
#include <sys/audit.h>
#include <pwdadj.h>

/* Simple subsitute for the Sun adjunct password structure */
struct passwd_Xadjunct { 
	char	*pwa_name;
	char	*pwa_passwd;
	char	*pwa_minimum;
	char	*pwa_maximum;
	char	*pwa_def;
	char	*pwa_au_always;
	char	*pwa_au_never;
	char	*pwa_version;
	char	*pwa_age;
};

/*
 * fgetapwent - Fetch adjunct password record from a file
 */
private struct passwd_Xadjunct	*
fgetapwent(af)
	FILE	*af;	/* Pointer to open adjunct file */
{
	char	*p,
		*pp;	/* ACME Pointer Works, Inc */
	static char     ibuf[BUFSIZ];	/* Input and return data buffer */
	static struct passwd_Xadjunct	pwadata;	/* Return data */

	if (fgets(ibuf, sizeof(ibuf), af) == NULL)
		return(NULL);
	chop_nl(ibuf);
        zeromem(&pwadata, sizeof pwadata);
#define skipc while (*p && *p != ':' && *p != '\n') ++p; if (*p) *p++ = 0
        p = ibuf;
        pwadata.pwa_name = p;     skipc;
        pwadata.pwa_passwd = p;   skipc;
        if (pp = strchr(pwadata.pwa_passwd, ',')) {
                *pp++ = 0;
                pwadata.pwa_age = pp;
        }
        pwadata.pwa_minimum = p; skipc;
        pwadata.pwa_maximum = p; skipc;
        pwadata.pwa_def = p; skipc;
        pwadata.pwa_au_always = p; skipc;
        pwadata.pwa_au_never = p; skipc;
        pwadata.pwa_version = p; skipc;
#undef	skipc
	return(&pwadata);
}

/*
 * sputpwaent - Write an adjunct password file entry
 */
private char *
sputpwaent(ap, lp)
	struct passwd_Xadjunct	*ap;	/* Entry to format */
	char	*lp;			/* Buffer to use */
{
	char	pwb[48];

	(void) strcpy(pwb, ap->pwa_passwd);
	if (ap->pwa_age && *ap->pwa_age) {
		(void) strcat(pwb, ",");
		(void) strcat(pwb, ap->pwa_age);
	}
	(void) sprintf(lp, "%s:%s:%s:%s:%s:%s:%s",
		ap->pwa_name, pwb,
		ap->pwa_minimum, ap->pwa_maximum,
		ap->pwa_def, ap->pwa_au_always, ap->pwa_au_never);
	return(lp);
}

/*
 * get_shadow - Fetch encrypted password from adjunct password database
 */
public void
get_shadow(userm)
	struct mpasswd *userm;		/* User to get shadow password for */
{
	struct passwd_adjunct *ap;	/* Adjunct lookup ptr */
	struct passwd_Xadjunct *xp;	/* Adjunct file lookup ptr */
	struct passwd_files *adj;	/* Shadow file finder */
	struct pw_opaque *aux = userm->opaque;	/* Ptr to method data */
	FILE	*af;			/* Shadow file I/O ptr */

	/*
	 * If the password isn't "##username", then it's not a shadow password
	 */
	if (strncmp(userm->mpw_passwd, "##", 2) ||
	    strcmp(&userm->mpw_passwd[2], userm->mpw_name))
			return;

	/*
	 * We are running as root, so we can get the
	 * encrypted password from the adjunct file/NIS map
	 */
	if ((ap = getpwanam(userm->mpw_name)) == NULL)
		logdie("Cannot get password for %s from adjunct",
			userm->mpw_name);

	aux->sourceSH = srv_local;	/* Assume its in YP map for now */

	debug(DB_LOOKUP, "get_shadow: found adjunct pw for %s\n",
		userm->mpw_name);

	userm->mpw_passwd = strdup(ap->pwa_passwd);
	if (ap->pwa_age && *ap->pwa_age)
		userm->mpw_age = strdup(ap->pwa_age);

	/*
	 * Look for the local adjunct file
	 * There should always be an adjunct file
	 * unless this is an NIS client
	 */
	for (adj = etc_shadow; adj->pwfile; adj++) {
		if (access(adj->pwfile, 0) < 0)
			continue;
		if ((af = fopen(adj->pwfile, "r")) == NULL)
			logdie("Cannot open adjunct file \"%s\"",
				adj->pwfile);

		while ((xp = fgetapwent(af)) != NULL) {
			if (strcmp(xp->pwa_name, userm->mpw_name) == 0 &&
			    xp->pwa_passwd && *xp->pwa_passwd) {
				aux->sourceSH = srv_local;
				aux->whichSH = adj;
				userm->mpw_passwd = strdup(xp->pwa_passwd);
				debug(DB_LOOKUP,
					"get_shadow: found adjunct pw for %s in %s\n",
					userm->mpw_name, adj->pwfile);
				(void) fclose(af);
				return;
			}
		}
	}
	(void) fclose(af);
}

/*
 * update_shadow - Change data in the adjunct password file
 */
public int
update_shadow(theUser, newUser)
	struct mpasswd	*theUser;	/* Original user */
	struct mpasswd	*newUser;	/* Modified user */
{
	FILE	*tf,			/* New password file output */
		*pf;			/* Current password file input */
	int	fd;			/* Temp file create fd */
	int	repdone = 0;		/* Has the entry been found? */
	char	adjline[BUFSIZ];	/* Adjunct line to stuff in YP map */
	int	sizediff;		/* Size difference in old & new files */
	struct passwd_Xadjunct	*px;	/* Password file traversal */
	struct sigblk	blocked;	/* Signals blocked during disk copy */
	struct pw_opaque *aux = (struct pw_opaque *)theUser->opaque;
					/* Method block */

	fd = MakeLockTemp(aux->whichSH->tempfile);

#if     defined(HAS_FCHOWN) && defined(HAS_FCHMOD)
	(void) fchown(fd, SHADOW_UID, SHADOW_GID);
	(void) fchmod(fd, SHADOW_MODE);
#else
	FixPwFileMode(aux->whichSH->tempfile, "shadow");
#endif
	if ((tf = fdopen(fd, "w")) == NULL) {
		logdie("Cannot fdopen shadow temp file \"%s\".\n",
			aux->whichSH->tempfile);
	}
	if ((pf = fopen(aux->whichSH->pwfile, "r")) == NULL) {
		logdie("Cannot open shadow file \"%s\".\n",
			aux->whichSH->pwfile);
	}
	debug(DB_UPDATE, "Modifying adjunct file \"%s\"\n",
		aux->whichSH->pwfile);
	zeromem(&blocked, sizeof blocked);
	block_signals(&blocked, SIGHUP, SIGINT, SIGQUIT, SIGTSTP, 0);
	while ((px = fgetapwent(pf)) != NULL) {
		char	pwaline[BUFSIZ];

		if (px->pwa_name == 0 || px->pwa_name[0] == 0)
			continue;
		if (!repdone && strcmp(px->pwa_name, theUser->mpw_name) == 0) {
			px->pwa_passwd = newUser->mpw_passwd;
			if (newUser->mpw_age)
				px->pwa_age = newUser->mpw_age;
			(void) sputpwaent(px, adjline);
			repdone++;
		}
		(void) fprintf(tf, "%s\n", sputpwaent(px, pwaline));
	}
	(void) fclose(tf);
	(void) fclose(pf);

	if (repdone == 0) {
		(void) unlink(aux->whichSH->tempfile);
		unblock_signals(&blocked);
		return(1);
	}
	/*
	 * Check if the new shadow file is complete.
	 * There is an assumption here that changing one passwd entry should
	 * not change the total size of the file more than ShadowTolerance
	 * bytes.
	 *
	 * If the new file is longer, don't worry.  If shorter, that's 
	 * alright if the difference is less than ShadowTolerance, otherwise
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
		perror("adjunct file save");
		(void) unlink(aux->whichSH->tempfile);
		logdie("Failed to save adjunct file.\n");
	}
	if (rename(aux->whichSH->tempfile, aux->whichSH->pwfile) < 0) {
		perror("adjunct file replace");
		(void) unlink(aux->whichSH->tempfile);
		(void) link(aux->whichSH->savefile, aux->whichSH->pwfile);
		logdie("Failed to replace adjunct file.\n");
	}
#ifdef	USE_NIS
	update_yp_map(theUser->mpw_name, adjline, ADJUNCT_BYNAME,
			aux->dbinfo.ypinfo->data, 0);
#endif
	unblock_signals(&blocked);
}

/*
 * check_auth
 *	Check the password change bits in auth database
 * Usage:
 *	check_auth(struct mpasswd *)
 * Returns:
 *	deny = auth says no
 *	allow = no deny
 */
public enum chg_perm
check_auth(theUser)
	struct mpasswd *theUser;
{
	return(allow);
}

/* End shm_adjunct.c */
