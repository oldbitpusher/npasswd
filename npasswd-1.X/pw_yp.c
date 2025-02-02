
/* --------------------------------------------------------------------  */
/*                                                                       */
/*                         Author: Clyde Hoover                          */
/*                          Computation Center                           */
/*                   The University of Texas at Austin                   */
/*                          Austin, Texas 78712                          */
/*                         clyde@emx.utexas.edu                          */
/*                   uunet!cs.utexas.edu!ut-emx!clyde                    */
/*                                                                       */
/*This code may be distributed freely, provided this notice is retained. */
/*                                                                       */
/* --------------------------------------------------------------------  */
/*
 *	pw_yp - Routines for dealing with SUN Yellow Pages password files
 *
 *	This code can update local password file, can cause rebuilding of
 *	local YP maps and can use yppasswdd(8) to change YP passwords.
 *
 *	Must be linked with -lrpcsvc
 */
#include <stdio.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
#include <pwd.h>
#include <fcntl.h>
#include <rpc/rpc.h>
#include <rpcsvc/ypclnt.h>
#include <rpcsvc/yppasswd.h>
#include <sys/socket.h>

#ifdef	SECURE_RPC
#include <rpc/key_prot.h>
#endif

#ifdef	SYSV
#define	index	strchr
#endif

#ifdef	SYSLOG
#include <syslog.h>
#endif

#ifndef lint
static char sccsid[] = "@(#)pw_yp.c	1.20 4/27/92 (cc.utexas.edu)";
#endif

#define	NONE	-1	/* YP not active */
#define	NOT	0	/* YP active - we are not master */
#define	IS	1	/* YP active - we have the password file */

#define	SLOP	128	/* Size difference tolerated old <> new passwd file */

typedef struct passwd	passwd;
typedef	struct passwd	*passwdp;

static passwd	theUser,	/* User being changed */
		Me;		/* User invoking passwd */
static int	myuid,		/* Uid of invoker */
		mytempfile = 0;	/* Does PASSWD_TEMP belong to me? */
static char	*ypmaster,	/* Name of the YP master */
		*ypdomain;	/* YP domain name */

#define	PASSWD_MAP	"passwd.byname"		/* Name of YP passwd map */

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
static char	auxlockfile[MAXPATHLEN];	/* Aux lock file */

extern int	errno;

char	*getlogin(),
	*crypt();

/*
 *	pw_initialize - set up
 */
pw_initialize()
{
	passwdp	me;			/* Passwd for invoker */
	char	*myname;		/* Invoker login name */

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
	myname = getlogin();
	me = NULL;
	if (myname && *myname) {
		if ((me = getpwnam(myname)) == NULL)
			quit(1, "Cannot get user identification from name.\n");
		if (me->pw_uid != myuid) {
			me = NULL;
#ifdef	DEBUG
			printf("Login name \"%s\" does not belong to uid %d\n",
				myname, myuid);
#endif
#ifdef	PARANOID
			quit(1, "Login name \"%s\" does not belong to uid %d\n",
				myname, myuid);
#endif
		}
	}
	if (me == 0) {
		if ((me = getpwuid(myuid)) == NULL)
			quit(1, "Cannot get user identification from uid.\n");
	}
	_cppasswd(me, &Me);
	return(1);
}

/*
 *	pw_getuserbyname - get password
 *
 *	Returns 1 if passwd found for <name>
 *		0 otherwise
 */
pw_getuserbyname(name, passwdb)
char	*name,		/* User name */
	*passwdb;	/* Where to stuff password */
{
	passwdp	p;	/* Temp */

	if ((p = getpwnam(name)) == NULL)
		return(0);
	_cppasswd(p, &theUser);
	(void) strcpy(passwdb, p->pw_passwd);
	return(1);
}

/*
 *	pw_permission - check password change permission
 *
 *	Returns 1 if password can be changed
 *		0 if not
 */
pw_permission()
{
	extern char	ppbuf[];

	/*
	 * Is this my password or someone elses?
	 */
	if (strcmp(Me.pw_name, theUser.pw_name) && myuid)
		return(0);

	/*
	 * If on a YP client, root cannot change another
	 * users' password via yppasswd(), since we can't
	 * get a plain text password to pass to yppasswdd().
	 */
	if (myuid == 0 && is_yp_master() == NOT) {
		FILE	*pf;
		passwdp px,		/* Password file traversal */
			fgetpwent();
		int	rc = 0;

		if ((pf = fopen(whichpw->pwfile, "r")) == NULL) {
			quit(1, "Cannot open password file \"%s\".\n",
				whichpw->pwfile);
		}
		/*
		 * Scan local password file, looking for user
		 * Cannot use getpwnam() because it will use YP - I want to know
		 * if the user's password file entry is >>local<<
		 */
		while ((px = fgetpwent(pf)) != NULL) {
			if (strcmp(px->pw_name, theUser.pw_name) == 0) {
				rc = 1;
				break;
			}
		}
		fclose(pf);
		if (rc) {
			if (strncmp(px->pw_passwd, "##", 2) == 0)
			    quit(0,
				"Changing of adjunct passwords not supported.\n");
			return(1);
		}
		else
			if (!ppbuf[0])
				quit(0,
				"Password for %s can only be changed on YP server %s.\n",
				theUser.pw_name, ypmaster);
	}
	/* Check if passwd is '##username' - can't do that yet */

	/*
	 * Other checks can be put here to determine if the invoker should
	 * be allowed to change this password.
	 */
	return(1);
}

/*
 *      pw_compare - compare old and new passwords
 *
 *      Returns 1 if check = new, 0 if not
 */
pw_compare(current, new)
char	*current,		/* Current pw (encrypted) */
	*new;			/* check pw (plain) */
{
	if (!*current)		/* Is current password null? */
		return(0);
	/* Put other administrative checks here */
	return(!strcmp(current, crypt(new, current)));
}

/*
 *      pw_check - sanity check password.  Right now just calls
 *              the password check code
 *
 *      Returns 1 if password is ok to use, 0 otherwise
 */
pw_check(pwd)
char	*pwd;
{
	int	rc = checkpasswd(theUser.pw_uid, pwd);

#ifdef	PASSWORD_HISTORY
	if (rc)
		return(rc);
	/* Call password history checker to prevent password reuse */
	rc = passwd_history(theUser.pw_uid, pwd);
#endif
	return(rc);
}

/*	Error message for when yppasswdd fails with error code 1.  */
static char *yperrmsg =
"Password change failed: Problem with yppasswdd.\n\n\
This is probably because the YP maps are out of sync\n\
with the YP passwd file for %s on %s.\n\n\
Please try again later.\n";

/*
 *      pw_replace - replace password in passwd file 
 */
pw_replace(newpwd, curpwd)
char	*newpwd,		/* New password (plain) */
	*curpwd;		/* Old password (plain) */
{
	passwdp px,		/* Password file traversal */
		fgetpwent();
	long    oldsigs,	/* Old signal mask */
		blocksigs = sigmask(SIGINT) |	/* Sigs to block */
			    sigmask(SIGQUIT) |
			    sigmask(SIGTSTP);
	FILE	*tf,		/* New password file output */
		*pf;		/* Current password file input */
	int	fd,		/* Temp file create fd */
		islocal = 0,	/* Is user in local password file */
		onpwmaster = NOT; /* Is this the master for the passwd map? */
	struct stat	oldstat,	/* Old password file stat */
			newstat;	/* New password file stat */

	if ((pf = fopen(whichpw->pwfile, "r")) == NULL)
		quit(1, "Cannot open password file \"%s\".\n", whichpw->pwfile);

#ifndef	FORCE_YP_CHANGE
	onpwmaster = is_yp_master();
	/*
	 * Scan local password file, looking for user
	 * Cannot use getpwnam() because it will use YP - I want to know
	 * if I have to change a >>local<< password file.
	 */
	while ((px = fgetpwent(pf)) != NULL) {
		if (*px->pw_name == '+' || *px->pw_name == '-')
			continue;
		if (strcmp(px->pw_name, theUser.pw_name) == 0) {
			if (strncmp(px->pw_passwd, "##", 2) == 0)
			    quit(0,
				"Changing of adjunct passwords not supported.\n");
			islocal++;
			break;
		}
	}
	fclose(pf);
#else
	(void) is_yp_master();
	onpwmaster = NOT;
#endif

	/*
	 * If the user was not in the local password file, use RPC
	 * to update the Yellow Pages (NIS) password file.
	 */
	if (islocal == 0) {
		if (onpwmaster == NOT) {
			int	rc;		/* Return code from ypasswdd */
			int	why;		/* RPC call return code */
			int	ypport;		/* Port for RPC call */
			struct yppasswd yppasswd; /* YP passwd change block */
			char	salt[4];	/* Password encryption salt */
			char	cpw[8];

			if (curpwd[0] == 0)
				quit(0, "Cannot change YP password without old password.\n");
			randomstring(salt, sizeof(salt));
			theUser.pw_passwd = crypt(newpwd, salt);
			(void) strncpy(cpw, curpwd, sizeof(cpw));
			cpw[8] = 0;
			yppasswd.oldpass = cpw;
			_cppasswd(&theUser, &yppasswd.newpw);
#ifdef	DEBUG
			printf("yppasswd(%s, %s)\n", curpwd, theUser.pw_passwd);
#else
			if ((ypport = getrpcport(ypmaster, YPPASSWDPROG,
			     YPPASSWDPROC_UPDATE, IPPROTO_UDP)) == 0)
				quit(1, "%s is not running ypassswdd.\n",
				     ypmaster);

			if (ypport >= IPPORT_RESERVED)
				quit(1, "yppasswdd on %s not privleged.\n",
					ypmaster);
			rc = callrpc(ypmaster, YPPASSWDPROG, YPPASSWDVERS,
				YPPASSWDPROC_UPDATE, xdr_yppasswd, &yppasswd,
				xdr_int, &why);

			/* RPC call error */
			if (rc) {
#if	NO_CLNT_SPERRNO
				clnt_perrno(rc);
				quit(1, "Password change failed (%s)\n",
					ypmaster);
#else
				quit(1, "Password change failed (%s): %s\n",
					ypmaster, clnt_sperrno(rc));
#endif
			}
			/* Error returned from yppasswdd */
			if (why) {
#ifdef	SYSLOG
				syslog(LOG_ERR,
					"yppasswdd error %d on %s for %s",
					why, ypmaster, theUser.pw_name);
#endif
				if (why == 1)
				   quit(0, yperrmsg,  ypdomain, ypmaster);
				else
				   quit(1, "Password change failed.\n");
			}
# ifdef	SECURE_RPC
			reset_secret_key(curpwd);
# endif /* SECURE_RPC */
#endif	/* DEBUG */
			return;
		}
		else	/* User not in local passwd, and not in YP passwd */
			quit(1, "User %s missing from password file.\n",
				theUser.pw_name);
	}

	/*
	 * There is a local password file to change
	 */
	if ((pf = fopen(whichpw->pwfile, "r")) == NULL)
		quit(1, "Cannot open password file \"%s\".\n", whichpw->pwfile);
	(void) umask(0);
	(void) fstat(fileno(pf), &oldstat);
	/*
	 * Use different temp file if on YP master.
	 * This deals with the SunOS 4.0.3 yppasswdd which creates temp files
	 * named "passwd-file.ptmp", rather than the traditional "/etc/ptmp".
	 * But there are still a lot of applications which use /etc/ptmp,
	 * so is it used as the passwd temp file and the 'auxlockfile' is
	 * also made --- >>>GROAN<<<.
	 */
	auxlockfile[0] = 0;
	if (onpwmaster == IS) {
		(void) sprintf(auxlockfile, "%s.ptmp", whichpw->pwfile);
		close(mklocktemp(auxlockfile));
	}
	mytempfile = 1;
	fd = mklocktemp(whichpw->tempfile);
	if ((tf = fdopen(fd, "w")) == NULL)
		quit(1, "Cannot fdopen temp file.\n");

	oldsigs = sigblock(blocksigs);
	while ((px = fgetpwent(pf)) != NULL) {
		if (px->pw_name == 0 || px->pw_name[0] == 0) /* Sanity check */
			continue;
		if (strcmp(px->pw_name, theUser.pw_name) == 0) {
			char	salt[4];	/* Password encryption salt */

			randomstring(salt, sizeof(salt));
			theUser.pw_passwd = crypt(newpwd, salt);
			px = &theUser;
		}
		(void) putpwent(px, tf);
	}
	(void) fflush(tf);			/* Force buffers empty */
	(void) fstat(fileno(tf), &newstat);	/* Get size */
	(void) fclose(tf);
	(void) fclose(pf);

	/*
	 * Check if the new password file is complete.  Since the encrypted
	 * password is of a fixed length, the new file should be roughly
	 * the same size as the old one.
	 *
	 * This assumption will FAIL when this program does chfn and chsh!!! -
	 * use line counts.
	 */
	if (newstat.st_size < (oldstat.st_size - SLOP))
		quit(1,
		"New password file appears to be incomplete - aborting.\n");

	if (rename(whichpw->pwfile, whichpw->savefile) < 0) {
		perror("Password file save");
		(void) unlink(whichpw->tempfile);
		quit(1, "Can't save password file.\n");
	}
	if (rename(whichpw->tempfile, whichpw->pwfile) < 0) {
		perror("Password file replace");
		(void) unlink(whichpw->tempfile);
		(void) link(whichpw->savefile, whichpw->pwfile);
		quit(1, "Can't replace password file.\n");
	}
	if (onpwmaster == IS)
		updateyp();
	(void) sigsetmask(oldsigs);
}

/*
 *      pw_cleanup - clean up after myself
 */
pw_cleanup(code)
int	code;		/* 0 for normal, 1 for abort */ /*NOTUSED*/
{
	if (mytempfile) {
		(void) unlink(whichpw->tempfile);
		if (auxlockfile[0])
			(void) unlink(auxlockfile);
	}
}

/*
 *      _newstr - copy string into new storage
 */
static char *
_newstr(s)
char	*s;		/* String to copy */
{
	register char	*t;	/* Temp */
	char	*malloc();

	if (s == NULL)
		return(0);
	t = malloc(strlen(s) + 1);
	if (t == NULL)
		quit(1, "No memory.\n");
	(void) strcpy(t, s);
	return(t);
}

/*
 *	mklocktemp - Make temp file with exclusive use checking
 *
 *	Returns file descriptor of created file, else exits with error
 */
static int
mklocktemp(name)
char	*name;
{
	int	fd;

	fd = open(name, O_WRONLY|O_CREAT|O_EXCL, PASSWD_MODE);
	if (fd < 0) {
		if (errno == EEXIST)
			quit(0, "Password file busy - try again.\n");
		perror("Tempfile create");
		quit(1, "Cannot create temp file.\n");
	}
	return(fd);
}

/*
 *	 _cppasswd - copy a passwd structure
 */
static
_cppasswd(f,t)
passwdp	f,		/* From */
	t;		/* To */
{
	*t = *f;
	t->pw_name = _newstr(f->pw_name);
	t->pw_passwd = _newstr(f->pw_passwd);
	t->pw_comment = _newstr(f->pw_comment);
	t->pw_gecos = _newstr(f->pw_gecos);
	t->pw_dir = _newstr(f->pw_dir);
	t->pw_shell = _newstr(f->pw_shell);
}

/*
 *	is_yp_master - Figure out whether we are running on the Yellow Pages
 *		master for the password file maps.
 *
 *	Returns:
 *		IS if we are the master
 *		NOT if we are not the master
 *		NONE if there is no master
 */
#include <netdb.h>
#ifndef	MAXHOSTNAMLEN
#define	MAXHOSTNAMLEN 32
#endif

is_yp_master()
{
	static char	known = 0,	/* We've been here */
			answer = NOT;	/* ...and this is the answer */
	char	hostname[MAXHOSTNAMLEN];	/* Our host name */
	char	*index();
	struct hostent	*hinfo;

	if (known)
		return(answer);
	(void) gethostname(hostname, sizeof(hostname));
	if (yp_get_default_domain(&ypdomain)) {
/* 		quit(1, "Cannot get YP domain.\n"); */
		known++;
		return(answer = NONE);		/* Assume no YP running */
	}

	if (yp_master(ypdomain, PASSWD_MAP, &ypmaster)) {
		known++;
		return(answer = NONE);		/* Assume no YP running */
	}

	known++;
#ifdef	FASTCHECK
	/*
	 * Stupid (but fast) hostname check (first component only)
	 */
	{
		char	*p;			/* Scratch */

		if (p = index(ypmaster, '.')) *p = 0;
		if (p = index(hostname, '.')) *p = 0;
	}
#else
	/*
	 * Compare my host name and the YP master's host name.
	 * Use gethostbyname() to return the fully qualified form so that
	 * a string compare can be done.
	 */
	if (index(hostname, '.') == 0) {
		if ((hinfo = gethostbyname(hostname)) == 0)
			quit(1, "Cannot get hostinfo for self.\n");
		(void) strcpy(hostname, hinfo->h_name);
	}
	if (index(ypmaster, '.') == 0) {
		static char	ypmaster_f[MAXHOSTNAMLEN];

		if ((hinfo = gethostbyname(ypmaster)) == 0)
			quit(1, "Cannot get hostinfo for ypmaster.\n");
		(void) strcpy(ypmaster_f, hinfo->h_name);
		ypmaster = ypmaster_f;
	}
#endif
	if (strcmp(ypmaster, hostname) == 0)
		return(answer = IS);
	return(answer);
}

/*
 *	An example sh(1) script to update YP password map
 */
char	*ypcmd =
	"(PATH=/bin:/usr/bin; export PATH; ypdirs='/var/yp /etc/yp'\n\
	for d in $ypdirs; do\n\
		if [ -d $d ]; then\n\
			cd $d; exec make passwd\n\
		fi\n\
	done\n\
	echo 'passwd: Cannot rebuild YP maps!' 1>&2\n\
	false) >/dev/null &\n";

/*
 *	updateyp - update local YP maps
 */
updateyp()
{
	(void) setuid(geteuid()); 	/* Get all privs */
			/* (This assumes that we are setuid root) */
	/*
	 * This machine is the YP master for passwd - invoke something
	 * to update the YP maps.
	 * Super-user can override the default YP updater by setting
	 * env "YP_UPDATE_PROC" to a command to be run instead.
	 * The name of the user being changed is piped to stdin of the command.
	 */
	if (myuid == 0) {
		char	*getenv();
		char	*proc = getenv("YP_UPDATE_PROC");

		if (proc && *proc) {
			char	cmdbuf[BUFSIZ];

			(void) sprintf(cmdbuf, "/bin/echo '%s' | ( %s )",
				theUser.pw_name, proc);
#ifdef	DEBUG
			printf("updateyp (proc): %s", cmdbuf);
#endif
			(void) system(cmdbuf);
			return;
		}
	}
#ifdef	DEBUG
	printf("updateyp: %s", ypcmd);
#endif
	(void) system(ypcmd);
}

#ifdef	SECURE_RPC
/*
 *	reset_secret_key - Reset secret key for secure RPC
 */
reset_secret_key(curpwd)
char	*curpwd;
{
	char	mynet[MAXNETNAMELEN+1],
		key[HEXKEYBYTES+1];

	getnetname(mynet);
	if (!getsecretkey(mynet, key, curpwd))
		return;		/* Secure RPC not running */
	if (key[0] = 0)
		return;		/* No secret key */
	fprintf(stderr, "Cannot change secure RPC key\n");
	/*
	 * Actually I could, but I'd have to steal from Sun source
	 * code to do it.  Sun wouldn't like that very much, so I won't.
	 */
}
#endif
/*		End pw_yp.c 		*/
