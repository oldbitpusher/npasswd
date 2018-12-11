h13717
s 00003/00000/00296
d D 1.11 00/01/17 18:16:49 clyde 11 10
c Make sure the save file is removed
e
s 00015/00005/00281
d D 1.10 98/10/13 15:38:43 clyde 10 9
c 1. A bit more debugging in put_shadow()
c 2. Fix shadow temp size check
c 3. Add SHORT_FILE_WARN define to control short temp file behavior
e
s 00017/00000/00269
d D 1.9 98/07/20 15:21:02 clyde 9 8
c Add no-op check_auth()
e
s 00002/00003/00267
d D 1.8 98/06/23 10:58:35 clyde 8 7
c 1. Change compile-time debug include trigger
c 2. Fix define typo
e
s 00002/00011/00268
d D 1.7 98/03/31 14:43:38 clyde 7 6
c Use zeromem() to clear memory
e
s 00008/00000/00271
d D 1.6 97/05/27 09:28:45 clyde 6 5
c Use memset(0) instead of bzero() where available
e
s 00007/00007/00264
d D 1.5 96/08/27 16:33:39 clyde 5 4
c Use ShadowTolerance for temp file size check
e
s 00014/00011/00257
d D 1.4 96/08/06 14:14:13 clyde 4 3
c beta 3 cycle 1 checkin
e
s 00011/00013/00257
d D 1.3 96/03/27 09:29:18 clyde 3 2
c Use debug() routine for messages
e
s 00007/00025/00263
d D 1.2 95/04/05 16:19:52 clyde 2 1
c Beta 3 development checkin
e
s 00288/00000/00000
d D 1.1 94/09/28 16:16:29 clyde 1 0
c date and time created 94/09/28 16:16:29 by clyde
e
u
U
f e 0
t
T
I 1
/*
 *	%M% - Support for Sun adjunct password files
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
D 2

E 2
#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu)";
#endif

#include "npasswd.h"
#include "pwm_defs.h"
I 2
#include "shadowtab.h"
E 2

D 2
#define	SHADOW_FILE_MODE	0400

#ifdef	SUN_SECURITY

E 2
D 5
#define	SHADOW_SIZE_SLOP	32
E 5
I 5
D 8
Config_Value	int	ShadowTolerance = SHDAOW_DIFF_OK;
E 8
I 8
Config_Value	int	ShadowTolerance = SHADOW_DIFF_OK;
E 8
E 5

/*
D 2
 * Table of possible places for the shadow file to live
 */
private struct passwd_files shadowfiles[]  = {
#ifdef	DEBUG_FILES
	{ "./etc_shadow", "./etc_stmp", "./etc_oshadow", 0 },
#endif
	{ "/etc/security/passwd.adjunct", "/etc/security/ptmpa",
	  "/etc/security/opadjunct", 0 },
	{ 0 }
};

/*
E 2
 * Support for Solaris 1 (SunOS 4.X) adjunct passwords
 */
D 2
# define ADJUNCT_BYNAME  "passwd.adjunct.byname"
# define	SHADOW_METHOD_SET
E 2
I 2
#define ADJUNCT_BYNAME  "passwd.adjunct.byname"
E 2

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
D 2
	if ((p = INDEX(ibuf, '\n')) == 0)               /* Zap newline */
E 2
I 2
D 4
	if ((p = index(ibuf, '\n')) == 0)               /* Zap newline */
E 2
                logdie("Ill-formed adjunct entry \"%s\".\n", ibuf);
        else
                *p = 0;
E 4
I 4
	chop_nl(ibuf);
I 6
D 7
#ifdef	HAS_MEMSET
        memset((char *)&pwadata, 0, sizeof(pwadata));
#else
E 6
E 4
D 2
        BZERO((char *)&pwadata, sizeof(pwadata));
E 2
I 2
        bzero((char *)&pwadata, sizeof(pwadata));
I 6
#endif
E 7
I 7
        zeromem(&pwadata, sizeof pwadata);
E 7
E 6
E 2
#define skipc while (*p && *p != ':' && *p != '\n') ++p; if (*p) *p++ = 0
        p = ibuf;
        pwadata.pwa_name = p;     skipc;
        pwadata.pwa_passwd = p;   skipc;
D 2
        if (pp = INDEX(pwadata.pwa_passwd, ',')) {
E 2
I 2
D 4
        if (pp = index(pwadata.pwa_passwd, ',')) {
E 4
I 4
        if (pp = strchr(pwadata.pwa_passwd, ',')) {
E 4
E 2
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

I 3
D 8
/* #ifndef	DEBUG */
E 8
E 3
	/*
	 * We are running as root, so we can get the
	 * encrypted password from the adjunct file/NIS map
	 */
	if ((ap = getpwanam(userm->mpw_name)) == NULL)
		logdie("Cannot get password for %s from adjunct",
			userm->mpw_name);
I 3
D 8
/* #endif */
E 8
I 8

E 8
E 3
	aux->sourceSH = srv_local;	/* Assume its in YP map for now */
D 3
	if (DebugLevel >= DB_LOOKUP) {
		printf("get_shadow: %s has adjunct pw\n", userm->mpw_name);
		fflush(stdout);
	}
E 3
I 3

	debug(DB_LOOKUP, "get_shadow: found adjunct pw for %s\n",
		userm->mpw_name);

E 3
D 4
	userm->mpw_passwd = copystr(ap->pwa_passwd);
E 4
I 4
	userm->mpw_passwd = strdup(ap->pwa_passwd);
E 4
	if (ap->pwa_age && *ap->pwa_age)
D 4
		userm->mpw_age = copystr(ap->pwa_age);
E 4
I 4
		userm->mpw_age = strdup(ap->pwa_age);
E 4

	/*
	 * Look for the local adjunct file
	 * There should always be an adjunct file
	 * unless this is an NIS client
	 */
D 2
	for (adj = shadowfiles; adj->pwfile; adj++) {
E 2
I 2
	for (adj = etc_shadow; adj->pwfile; adj++) {
E 2
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
D 4
				userm->mpw_passwd = copystr(xp->pwa_passwd);
E 4
I 4
				userm->mpw_passwd = strdup(xp->pwa_passwd);
E 4
D 3
				if (DebugLevel >= DB_LOOKUP) {
					printf("get_shadow: found adjunct pw for %s in %s\n",
						userm->mpw_name, adj->pwfile);
					fflush(stdout);
				}
E 3
I 3
				debug(DB_LOOKUP,
					"get_shadow: found adjunct pw for %s in %s\n",
					userm->mpw_name, adj->pwfile);
E 3
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
D 10
	size_t	sizediff;		/* Size difference in old & new files */
E 10
I 10
	int	sizediff;		/* Size difference in old & new files */
E 10
	struct passwd_Xadjunct	*px;	/* Password file traversal */
	struct sigblk	blocked;	/* Signals blocked during disk copy */
	struct pw_opaque *aux = (struct pw_opaque *)theUser->opaque;
					/* Method block */

D 4
	fd = mklocktemp(aux->whichSH->tempfile);
E 4
I 4
	fd = MakeLockTemp(aux->whichSH->tempfile);

#if     defined(HAS_FCHOWN) && defined(HAS_FCHMOD)
	(void) fchown(fd, SHADOW_UID, SHADOW_GID);
	(void) fchmod(fd, SHADOW_MODE);
#else
	FixPwFileMode(aux->whichSH->tempfile, "shadow");
#endif
E 4
	if ((tf = fdopen(fd, "w")) == NULL) {
		logdie("Cannot fdopen shadow temp file \"%s\".\n",
			aux->whichSH->tempfile);
	}
	if ((pf = fopen(aux->whichSH->pwfile, "r")) == NULL) {
		logdie("Cannot open shadow file \"%s\".\n",
			aux->whichSH->pwfile);
	}
D 3
	if (DebugLevel >= DB_UPDATE) {
		printf("Modifying adjunct file \"%s\"\n", aux->whichSH->pwfile);
		fflush(stdout);
	}
E 3
I 3
	debug(DB_UPDATE, "Modifying adjunct file \"%s\"\n",
		aux->whichSH->pwfile);
E 3
D 7

I 6
#ifdef	HAS_MEMSET
	memset((char *)&blocked, 0, sizeof blocked);
#else
E 6
D 2
	BZERO((char *)&blocked, sizeof blocked);
E 2
I 2
	bzero((char *)&blocked, sizeof blocked);
I 6
#endif
E 7
I 7
	zeromem(&blocked, sizeof blocked);
E 7
E 6
E 2
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
D 5
	 * not change the total size of the file more than SHADOW_SIZE_SLOP
E 5
I 5
	 * not change the total size of the file more than ShadowTolerance
E 5
	 * bytes.
	 *
	 * If the new file is longer, don't worry.  If shorter, that's 
D 5
	 * alright if the difference is less than SHADOW_SIZE_SLOP, otherwise
E 5
I 5
	 * alright if the difference is less than ShadowTolerance, otherwise
E 5
	 * assume that the new file got truncated and bail.
	 *
	 * The alternative is to not use stdio for the temp file I/O, or
	 * force a fflush() after each putspent() and rely upon fflush to
	 * return the right error code.  Either way, we take a performance hit.
	 *
	 * So check the sizes and assume that will catch most errors.
	 */
D 4
	sizediff = cmp_file_size(aux->whichSH->tempfile, aux->whichSH->pwfile);
E 4
I 4
D 10
	sizediff = FileSizeDiff(aux->whichSH->tempfile, aux->whichSH->pwfile);
E 4
D 5
	if (sizediff < 0 && abs(sizediff) > SHADOW_SIZE_SLOP) {
		logdie("New shadow file is too short by %lu bytes\n",
			sizediff);
	}
E 5
I 5
	sizediff += ShadowTolerance;
	if (sizediff < 0)
E 10
I 10
	sizediff = ( FileSize(aux->whichSH->tempfile) -
		     FileSize(aux->whichSH->pwfile)) + ShadowTolerance;
	if (sizediff < 0) {
#ifdef	SHORT_FILE_WARN
		logerr("Shadow temp is %d bytes short\n", abs(sizediff));
#else
E 10
		logdie("Shadow temp is %d bytes short\n", abs(sizediff));
I 10
#endif
	}
E 10

E 5
D 10
	if (rename(aux->whichSH->pwfile, aux->whichSH->savefile) < 0) {
E 10
I 10
	debug(DB_UPDATE,
		"update_shadow: Install shadow '%s', temp '%s', save '%s'\n",
		aux->whichSH->pwfile, aux->whichSH->tempfile,
		aux->whichSH->savefile);

I 11
	(void) unlink(aux->whichSH->savefile);
E 11
	if (link(aux->whichSH->pwfile, aux->whichSH->savefile) < 0) {
E 10
		perror("adjunct file save");
		(void) unlink(aux->whichSH->tempfile);
		logdie("Failed to save adjunct file.\n");
	}
D 4
	set_protection(aux->whichSH->tempfile, "shadow");
E 4
	if (rename(aux->whichSH->tempfile, aux->whichSH->pwfile) < 0) {
		perror("adjunct file replace");
		(void) unlink(aux->whichSH->tempfile);
		(void) link(aux->whichSH->savefile, aux->whichSH->pwfile);
		logdie("Failed to replace adjunct file.\n");
	}
I 11
#ifdef	USE_NIS
E 11
	update_yp_map(theUser->mpw_name, adjline, ADJUNCT_BYNAME,
			aux->dbinfo.ypinfo->data, 0);
I 11
#endif
E 11
	unblock_signals(&blocked);
}
I 9

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

E 9
D 2
#endif	/* SUN_SECURITY */
E 2
/* End %M% */
E 1
