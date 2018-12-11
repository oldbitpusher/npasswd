/*
 * pw_ultrix  - update password files for Ultrix UPGRADE or ENHANCED
 *		security levels.  Handles local password files only.
 *
 *	Original author: Paul Leyland (pcl@oxford.ac.uk)
 */

#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu) %P%";
#endif

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
#include <pwd.h>
#include <fcntl.h>
#include <auth.h>
#include <time.h>
#include <ndbm.h>

#define	STD_PW_LEN 13	/* Length of encrypted strings from standard crypt */
			/* crypt16() makes a longer string */

#define	SLOP	128	/* Size difference tolerated old <> new passwd file */

static struct passwd theUser,		/* The user to change */
		     Me;		/* The user who invoked command */
static uid_t myuid;			/* Uid of program */
static int mytempfile = 0;		/* Does PASSWD_TEMP belong to me? */
static AUTHORIZATION theAuth;		/* Authorization info */

#define	PASSWD_MODE	0644

/*
 *	File names
 */
#ifndef	PASSWD_FILE
#define	PASSWD_FILE	"/etc/passwd"
#endif

#ifndef	PASSWD_SAVE
#define	PASSWD_SAVE	"/etc/opasswd"
#endif

#ifndef	PASSWD_TEMP
#define	PASSWD_TEMP	"/etc/ptmp"
#endif

#define	PASSWD_MODE	0644

struct passwdinfo {
	char	*pwfile,	/* Name of password file */
		*tempfile,	/* Name of password temp file */
		*savefile;	/* Name of password save file */
};

/*
 * List of possible locations for the password file
 */
static struct passwdinfo pwfiles[] = {
#ifdef	DEBUG
	{
		"./etc_passwd", "./etc_ptmp", "./etc_opasswd",
	},
#endif
	{
		PASSWD_FILE, PASSWD_TEMP, PASSWD_SAVE,
	},
	{
		"/etc/passwd", "/etc/ptmp", "/etc/opasswd",
	},
	{
		0
	}
};

static struct passwdinfo	*whichpw;	/* While files to use */

extern int errno;

char	*getlogin(),
	*crypt(),
	*crypt16();
uid_t	getuid();
size_t	strlen();

int	checkpassword();
extern void	quit(),
		randomstring();

/*
 * pw_initialize - set up
 */
pw_initialize ()
{
	struct passwd *metmp;		       /* Temp */
	AUTHORIZATION *a;		       /* Another temp. */
	char *myname = getlogin();	       /* Name of invoker */

	/*
	 * Find the password file.
	 */
	for (whichpw = pwfiles; whichpw->pwfile; whichpw++) {
		if (access(whichpw->pwfile, 0) == 0)
			break;
	}
	if (access(whichpw->pwfile, 0) < 0)
		quit(1, "Cannot find a password file!\n");

#ifdef	DEBUG
	printf("Using password file \"%s\"\n", whichpw->pwfile);
	setpwfile(whichpw->pwfile);
#endif
	myuid = getuid();
	if (myname && *myname) {
		if ((metmp = getpwnam(myname)) == NULL)
			quit (1, "Cannot get user identification from name.\n");
	}
	else {
		if ((metmp = getpwuid(myuid)) == NULL)
			quit (1, "Cannot get user identification from uid.\n");
	}

	if ((a = getauthuid(myuid)) == 0)
		quit(1, "Cannot get auth record.\n");
	_cpauth(a, &theAuth);
	copypwent(metmp, &Me);
	if (!strcmp(Me.pw_passwd, "*"))
		Me.pw_passwd = theAuth.a_password;
	/*   strcpy (Me.pw_passwd, theAuth.a_password); */
	return (1);
}

/*
 *	pw_getuserbyname - get password
 *
 *	Returns 1 if passwd info found for <name> 0 otherwise
 */
pw_getuserbyname (name, passwdb)
char	*name,			/* User name */
	*passwdb;		/* Where to stuff password */
{
	struct passwd *p;	/* Temp */
	AUTHORIZATION *a;	/* Temp */

	if ((p = getpwnam(name)) == NULL)
		return(0);
	copypwent(p, &theUser);

	if ((a = getauthuid(p->pw_uid)) == 0)
		return(0);
	_cpauth (a, &theAuth);

	/*
	 * Is the encrypted password in p, (UPGRADE) or do we have
	 * to get the Auth record (ENHANCED) ?
	 */
	if (strcmp ("*", p->pw_passwd))
		(void) strcpy(passwdb, p->pw_passwd);
	else
		(void) strcpy(passwdb, a->a_password);
	return (1);
}

/*
 * pw_permission - check password change permission
 *
 * Returns 1 if password can be changed 0 if not
 */
pw_permission ()
{
	/* First off, am I root? */
	if (myuid == 0)
		return(1);

	/* Am I trying to change someone else's password? */
	if (strcmp(Me.pw_name, theUser.pw_name))
		return (0);

	/* Fine.  Now, have I been allowed to change my own password at all? */
	if (!(theAuth.a_authmask & A_CHANGE_PASSWORD))
		return(0);

	/* Now, what to do if forced to use generated passwords.
	   Punt to original passwd?  Let's ignore for the moment. */

	/* Changed too recently? */
	if (time ((time_t *)0) - theAuth.a_pass_mod < theAuth.a_pw_minexp)
		quit(1, "Password changed too recently.\n");

	return(1);
}

/*
 * pw_compare - compare old and new passwords
 *
 * Returns 1 if check = new, 0 if not
 */
pw_compare (current, check)
char	*current,		/* Current pw (encrypted) */
	*check;			/* check pw (plain) */
{
	if (!*current)
		return (0);

	if (strlen(current) == (size_t) STD_PW_LEN)
		return (!strcmp(current, crypt(check, current)));
	else		/* ENHANCED */
		return (!strcmp(current, crypt16(check, current)));
}

/*
 * pw_check - sanity check password. 
 *	Right now just calls the password check program
 *
 * Returns 1 if password is ok to use, 0 otherwise
 */
pw_check (newpw, mesgbuf)
char	*newpw,		/* New password (plain) */
	*mesgbuf;	/* Error message buffer */
{
	/* Put other administrative checks here */
	return (checkpassword (newpw, theUser.pw_uid, mesgbuf));
}

/*
 * pw_replace - replace password in passwd file
 */
pw_replace (newpwd, curpwd)
char	*newpwd,			       /* New password (plain) */
	*curpwd/*NOTUSED*/;		       /* Old password (plain) */
{
	int	oldsigs,		       /* Signal mask save */
		blocksigs = sigmask (SIGINT) | /* Signals to block */
			sigmask (SIGQUIT) |    /* while updating */
			sigmask (SIGTSTP);     /* password file */
	struct passwd * px;		       /* Temp */
	char salt[4];		       /* Encryption salt */
	FILE *tf;		       /* File ptr to new passwd file */
	int fd;			       /* File desc. to new passwd file */
	struct stat oldstat,	       /* Stat of current passwd file */
		newstat;	       /* Stat of new passwd file */

	/* Prepare password entry 'theUser' for replacement */
	randomstring (salt, sizeof (salt));
	theUser.pw_passwd = "*";	       /* Always '*' in /etc/passwd */
	(void) strcpy (theAuth.a_password, crypt16 (newpwd, salt));
	(void) umask (0);
	(void) stat (whichpw->pwfile, &oldstat);
	fd = open (whichpw->tempfile, O_WRONLY | O_CREAT | O_EXCL, PASSWD_MODE);
	if (fd < 0) {
		if (errno == EEXIST)
			quit (0, "Password file busy - try again.\n");
		perror ("Tempfile create");
		quit (1, "Cannot create temp file.\n");
	}
	mytempfile = 1;
	if ((tf = fdopen (fd, "w")) == NULL)
		quit (1, "Cannot fdopen temp file.");
	oldsigs = sigblock (blocksigs);
	setpwent();
	while ((px = getpwent ()) != NULL) {
		if (px->pw_name == 0 || px->pw_name[0] == 0)	/* Sanity check */
			continue;
		if (strcmp (px->pw_name, theUser.pw_name) == 0)
			px = &theUser;
		(void) putpwent (px, tf);
	}
	endpwent ();
	(void) fflush (tf);
	(void) fstat (fileno (tf), &newstat);
	(void) fclose (tf);

	/*
	 * Check if the new password file is complete.
	 * Since the encrypted password is of a fixed length,
	 * the new file should be roughly the same size as the old one.
	 */
	if (newstat.st_size < (oldstat.st_size - SLOP))
		quit (1, "New password file appears to be incomplete - aborting.\n");

	if (rename (whichpw->pwfile, whichpw->savefile) < 0) {
		perror("Password file save");
		(void) unlink(whichpw->tempfile);
		quit(1, "Can't save password file");
	}
	if (rename (whichpw->tempfile, whichpw->pwfile) < 0) {
		perror("Password file replace");
		(void) unlink(whichpw->tempfile);
		(void) link(whichpw->savefile, whichpw->pwfile);
		quit(1, "Can't replace password file");
	}
	updatedbm();

	/* Ok, /etc/passwd in good shape -- update auth DB */
	theAuth.a_pass_mod = time((time_t *)0);
#ifdef DEBUG
	fprintf (stderr, "About to storeauthent()\n");
#else
	if (storeauthent(&theAuth))
		quit(1, "Can't update auth database.\n");
#endif
	(void) sigsetmask (oldsigs);
}

/*
 * pw_cleanup - clean up after myself
 */
pw_cleanup (code)
	int code;	 	/* 0 for normal, 1 for abort */
{
	if (mytempfile)
		(void) unlink (whichpw->tempfile);
}

/*
 * _cpauth - copy a authentication structure
 */
static _cpauth (from, to)
AUTHORIZATION	*from,
		*to;
{
	to->a_uid = from->a_uid;
	(void) strcpy(to->a_password, from->a_password);
	to->a_pass_mod = from->a_pass_mod;
	to->a_pw_minexp = from->a_pw_minexp;
	to->a_pw_maxexp = from->a_pw_maxexp;
	to->a_authmask = from->a_authmask;
	to->a_fail_count = from->a_fail_count;
	(to->a_audit).audit_id = (from->a_audit).audit_id;
	(to->a_audit).audit_control = (from->a_audit).audit_control;
	bcopy((char *)(to->a_audit).audit_mask,
		(char *)(from->a_audit).audit_mask,
		sizeof (AUDIT_MASK));
	bcopy((char *)to->a_privs,
		(char *)from->a_privs,
		sizeof (PRIVILEGE_MASK));
}

/* Update the hashed password data base */
#define	SCOPY(S) xp = (S); while (*cp++ = *xp++)
#define	BCOPY(B) bcopy((char *)&(B), cp, sizeof(int)); cp += sizeof(int)

updatedbm ()
{
	DBM	*pwd;		       /* DBM data base passwd */
	char	*cp,		       /* Data storage pointer */
		*xp;		       /* String copy pointer */
	datum	key,		       /* DBM key datum */
		data;		       /* DBM data store datum */
	char	buf[512];	       /* Data buffer */

	if ((pwd = dbm_open (whichpw->pwfile, O_RDWR, 0)) == 0)
		return;
	cp = buf;
	/* Pack passwd entry in the form expected by the getpw* routines */
	SCOPY (theUser.pw_name);
	SCOPY (theUser.pw_passwd);
	BCOPY (theUser.pw_uid);
	BCOPY (theUser.pw_gid);
	BCOPY (theUser.pw_quota);
	SCOPY (theUser.pw_comment);
	SCOPY (theUser.pw_gecos);
	SCOPY (theUser.pw_dir);
	SCOPY (theUser.pw_shell);

	data.dptr = buf;
	data.dsize = cp - buf;
	key.dptr = theUser.pw_name;
	key.dsize = strlen (theUser.pw_name);
	if (dbm_store (pwd, key, data, DBM_REPLACE) < 0) {
		perror ("dbm_store (name)");
		quit (1, "Can't store passwd entry (name key).\n");
	}
	key.dptr = (char *) &theUser.pw_uid;
	key.dsize = sizeof (int);
	if (dbm_store (pwd, key, data, DBM_REPLACE) < 0) {
		perror ("dbm_store (uid)");
		quit (1, "Can't store passwd entry (uid key).\n");
	}
	dbm_close (pwd);
}
/* End %M% */
