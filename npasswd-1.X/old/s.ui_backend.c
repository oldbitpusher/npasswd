h18801
s 00002/00002/00255
d D 1.6 93/06/28 22:19:49 clyde 6 5
c 1. Make pw_initialize consistent with the documentation.
c 2. Change checkpasswd() to checkpassword().
e
s 00004/00003/00253
d D 1.5 93/06/25 10:09:58 clyde 5 4
c Add message buffer to pw_check() and pass to checkpasswd()
e
s 00008/00002/00248
d D 1.4 90/08/07 15:56:31 mic 4 3
c Use getpwuid() to get user id if getlogin() fails.  This can happen if run
c from an rsh or by /bin/login before you are really logged in.
e
s 00002/00000/00248
d D 1.3 90/06/22 10:39:19 clyde 3 2
c Make password compare rtn deal with null password
e
s 00172/00105/00076
d D 1.2 89/06/05 13:48:30 clyde 2 1
c First working version
e
s 00181/00000/00000
d D 1.1 89/05/18 10:25:56 clyde 1 0
c date and time created 89/05/18 10:25:56 by clyde
e
u
U
t
T
I 2
/*
 *	pw_userinfo.c - UTEXAS CC UNIX User Information Data Base
 *		backend for npasswd
 */
#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu) %P%";
#endif
E 2
I 1

#include <stdio.h>
#include <errno.h>
D 2
#include <sys/signal.h>
E 2
I 2
#include <syslog.h>
E 2
#include <strings.h>
I 2
#include <signal.h>
I 4
#include <pwd.h>
E 4
E 2
#include <local/userinfo.h>

D 2
#include "passwd.h"
E 2
I 2
static userdata	theUser,	/* User having password changed */
		Me;		/* User doing password change */
E 2

D 2
LOCAL userdata	theUser,
		Me;
E 2
I 2
#define	P_USER	1
#define	P_PRIV	2
#define	P_SU	3
E 2

D 2
IMPORT char	*getlogin();
E 2
I 2
static short	priv = P_USER;	/* Privlege level of <Me> */
E 2

D 2
EXPORT
E 2
I 2
#define	QUOTEC	'"'		/* Character to start plaintext pwd */
#define	XPWLEN	3		/* Length of 'original CDC password' */

extern char	*getlogin(),
		*crypt(),
		*index(),
		*rindex();

/*
 *	pw_initialize - set up
 */
E 2
pw_initialize()
{
D 2
	userptr	u;
	char	*me = getlogin();
E 2
I 2
	char	*myname = getlogin();		/* Login name */
I 4
	struct passwd *pw;			/* If getlogin() fails... */
E 4
	userptr	u;			/* Temp */
E 2

I 2
D 4
	if (myname == NULL || *myname == '\0')
		quit(1, "Cannot get user name.\n");
E 4
I 4
	if (myname == NULL || *myname == '\0') {
		if ((pw = getpwuid(getuid())) == ((struct passwd *)NULL))
			quit(1, "Cannot get user name.\n");
		else
			myname = pw->pw_name;
	}
E 4
E 2
	bzero((char *)&theUser, sizeof(theUser));
	bzero((char *)&Me, sizeof(Me));
D 2
	if (me == NULL || *me == '\0')
		quit("Cannot get user information for invoker");
	u = getuserbyname(me);
E 2
I 2
	if ((u = getuserbyname(myname)) == NULL)
		quit(1, "Cannot get user identification.\n");
E 2
	Me = *u;
I 2
	if (Me.ui_priv.p_acct_maint)	/* Account maintenance priv? */
		priv = P_PRIV;
	if (getuid() == 0)		/* SuperUser? */
		priv = P_SU;
E 2
}

D 2
EXPORT
pw_getuserbyname(name)
int	name;
E 2
I 2
/*
 *	pw_getuserbyname - Get userinfo data by name
 *
 *	Returns 1 if passwd info found for <name>
 *		0 otherwise
 */
pw_getuserbyname(name, passwdb)
char	*name,			/* Login name */
	*passwdb;		/* Where to stash password */
E 2
{
D 2
	userptr	u;
E 2
I 2
	userptr	u;			/* Temp */
E 2

D 2
	u = getuserbyname(name);
	if (u == (userptr )NULL)
E 2
I 2
	if ((u = getuserbyname(name)) == NULL)
E 2
		return(0);
	theUser = *u;
D 2
	(void) strcpy(CurrentUser, u->ui_name);
	(void) strcpy(CurrentPasswd, u->ui_password);
E 2
I 2
	(void) strcpy(passwdb, theUser.ui_password);
E 2
	return(1);
}

/*
 *	pw_permission - check if this user can change this password
 */
D 2
EXPORT
E 2
pw_permission()
{
D 2
	int	mypasswd = (theUser.ui_uid == Me.ui_uid);
E 2
I 2
	int	mypasswd		/* Wanting to change own password? */
		= (theUser.ui_uid == Me.ui_uid);
E 2

	/*
D 2
	 * Must be su to change root password
E 2
I 2
	 * Must be su to change root password.
E 2
	 */
D 2
	if (theUser.ui_uid == 0 && Me.ui_uid)
		quit("Permission denied.");
E 2
I 2
	if (theUser.ui_uid == 0 && priv != P_SU) {
		fprintf(stderr, "Permission denied.\n");
		return(0);
	}
E 2

	/*
	 * Must be su or have 'account maintenace' capability to change
	 * someone else's password.
	 */
D 2
	if (!mypasswd && Me.ui_uid && !Me.ui_priv.p_acct_maint)
		quit("Permission denied.");
E 2
I 2
	if (!mypasswd && priv < P_PRIV) {
		fprintf(stderr, "Permission denied.\n");
		return(0);
	}
E 2

	/*
	 * If 'password change' capability denied, then user cannot
D 2
	 * change their own password.  We know at this point that the
E 2
I 2
	 * change their own password.
	 */
	if (theUser.ui_priv.p_nopwchange && mypasswd) {
		fprintf(stderr, "Permission denied.\n");
		return(0);
	}
	/*
	 * We know at this point that the
E 2
	 * invoker does have permission to change the password.
	 */
D 2
	if (theUser.ui_priv.p_nopwchange && mypasswd)
		quit("Permission denied.\n");
E 2
I 2
	return(1);
E 2
}

D 2
EXPORT
pw_compare(old, new)
char	*old, *new;
E 2
I 2
/*
 *	pw_compare - compare old and new passwords
 *
 *	Returns 1 if check = new, 0 if not
 */
pw_compare(current, check)
char	*current,
	*check;
E 2
{
I 3
	if (!*current)
		return(1);
E 3
D 2
	char	buf[SIZEPW];
	IMPORT char *crypt();

	(void) strcpy(buf, crypt(new, old));
	return(!strcmp(buf, old));
E 2
I 2
	return(strcmp(current, crypt(check, current)) == 0);
E 2
}

D 2
EXPORT
pw_verify(pwd)
char	*pwd;
E 2
I 2
/*
 *	pw_check - sanity check password.  Performs some site-specific
D 6
 *		checks, then calls the checkpasswd() code.
E 6
I 6
 *		checks, then calls the checkpassword() code.
E 6
 *
 *	Returns 1 if password is ok to use, 0 otherwise
 */
D 5
pw_check(new)
char	*new;		/* New password (plaintext) */
E 5
I 5
pw_check(new, mesgbuf)
char	*new,		/* New password (plaintext) */
	*mesgbuf;	/* Error message buffer */
E 5
E 2
{
D 2
	int	pwlen = strlen(pwd);
	extern int	PwdMin;		/* Minimum pwd length */
E 2
I 2
	/* Setting null password? */
	if (strcmp(new, "@") == 0) {
		if (theUser.ui_priv.p_null_pass == 0 || priv < P_PRIV) {
			fprintf(stderr, "Cannot set null password.\n");
			return(0);
		}
		else
			return(1);
	}
E 2

D 2
	if (pwlen == 0 || strcmp(pwd, "@") == 0) {
		if (theUser.ui_priv.p_null_pass == 0 || theUser.ui_uid) /*XXX*/
			return(PWCK_NULL);
E 2
I 2
	/* A plain text password (enclosed in ""s)? */
	if (*new == QUOTEC) {
		char	*p = &new[1];

		while (*p) p++;
		if (p[-1] == QUOTEC) {
			if (priv == P_SU)	/* Reserved for superuser */
				return(1);
			else {
				fprintf(stderr,
					"Cannot set plaintext password.\n");
				return(0);
			}
		}
E 2
	}
D 2
	if (pwlen < (Me.ui_uid ? PwdMin : 3))		/* XXX */
		return(PWCK_SHORT);
	return(checkpassword(pwd, theUser.ui_uid));
E 2
I 2

	/* Special password (reserved for superuser) */
	if (strlen(new) == XPWLEN && priv == P_SU)
		return(1); 

	/* Dispatch to general password checker */
D 5
	return(checkpasswd(theUser.ui_uid, new));
E 5
I 5
D 6
	return(checkpasswd(theUser.ui_uid, new, mesgbuf));
E 6
I 6
	return(checkpassword(theUser.ui_uid, new, mesgbuf));
E 6
E 5
E 2
}

D 2
EXPORT
pw_replace(pwd)
char	*pwd;
E 2
I 2
/*
 *	pw_replace - Replace password in Userinfo database
 */
pw_replace(new, current)
char	*new,		/* New password (plaintext) */
	*current;	/* Current password (plaintext) [unused] */
E 2
{
D 2
	long	oldsigs,
		blockedsigs = sigmask(SIGINT) |
			      sigmask(SIGQUIT) |
			      sigmask(SIGTSTP);
	userptr	new;
	IMPORT int	errno;
E 2
I 2
	userptr	newu;			/* Temp */
	int	rc;			/* Temp */
	long	oldsigs,		/* Saved signal mask */
		blockedsigs = sigmask(SIGINT) |		/* Signals to block */
			      sigmask(SIGQUIT) |	/* while updating */
			      sigmask(SIGTSTP);		/* the database */
	extern int	errno;
E 2

	/*
D 2
	 * Password has already been validated by pw_verify()
E 2
I 2
	 * Password has already been validated by pw_check()
E 2
	 */
D 2
	if (strcmp(pwd, "@") == 0) {
E 2
I 2
	if ((newu = getuserbyuid(theUser.ui_uid)) == NULL)
		quit(1, "pw_replace: Cannot refetch user information.\n");

	if (strcmp(new, "@") == 0) {
E 2
		printf("Password removed from %s\n", theUser.ui_name);
D 2
		theUser.ui_password[0] = 0;
E 2
I 2
#ifndef	DEBUG
		syslog(LOG_INFO, "Password removed from %s\n", theUser.ui_name);
#endif
		newu->ui_password[0] = 0;
E 2
	}
	else {
D 2
		crypt_passwd(pwd, theUser.ui_password);
		theUser.ui_status.a_pwchanged = time((time_t *)0);
E 2
I 2
		char	salt[2];

		randomstring(salt, sizeof(salt));
		(void) strcpy(newu->ui_password, crypt(new, salt));
		if (*new == QUOTEC && priv == P_SU) {
			char	*p = new;

			while (*p) p++;
			if (*--p == QUOTEC) {
				*p = 0;
				(void) strcpy(newu->ui_password, &new[1]);
				printf("Setting plain text password.\n");
			}
		}
E 2
	}
D 2
	new = getuserbyuid(theUser.ui_uid);
	if (new == (userptr )NULL)
		quit("pw_replace: ?Cannot reget user");
E 2
I 2
	ui_acct(newu)->a_pwchanged = time((time_t *)0);
E 2

D 2
	(void) strcpy(new->ui_password, theUser.ui_password);
/*
 *	if (UIRecordChanged (U))
 *		quit("?Record synchronization error\n");
 */
E 2
I 2
#if	0
	if (UIRecordChanged(newu))
		quit(1, "Record synchronization error\n");
#endif
#ifdef	DEBUG
	printf("replace %s %s\n", theUser.ui_password, newu->ui_password);
#else
E 2
	errno = 0;
	oldsigs = sigblock(blockedsigs);
	if (lockuser(theUser.ui_uid) < 0) {
		if (errno == ETXTBSY)
D 2
			fprintf(stderr,
				"pw_replace: ?User record for %s locked out.\n",
E 2
I 2
			quit(1,
				"pw_replace: Data for %s locked out.\n",
E 2
				theUser.ui_name);
		else
D 2
			fprintf(stderr,
				"pw_replace: ?Can't lock record for user %s\n",
E 2
I 2
			quit(1,
				"pw_replace: Data lock failure for user %s\n",
E 2
				theUser.ui_name);
D 2
		quit((char *)0);
E 2
	}
D 2
	if (UIReplaceEntry (new) < 0) {
		unlockuser(theUser.ui_uid);
		(void) sigsetmask(oldsigs);
		quit("?Userinfo update failed: %s\n", UIErrorMessage);/* XXX */
		quit((char *)0);/* XXX */
	}
	unlockuser(theUser.ui_uid);
E 2
I 2
	rc = UIReplaceEntry(newu);
E 2
	(void) sigsetmask(oldsigs);
I 2
	unlockuser(theUser.ui_uid);
	if (rc < 0)
		quit(1, "Userinfo update failure %s\n", UIErrorMessage);
#endif
E 2
}

D 2

#define	PASSWD_QUOTE	'"'
E 2
/*
D 2
 *	crypt_passwd -- check and configure password. If privledged, a plain
 *		text password can be entered but surrounding it with
 *		quote marks e.g. "PlainText".
E 2
I 2
 *	pw_cleanup - cleanup routine
E 2
 */
D 2
LOCAL
crypt_passwd(plain, cryptloc)
register char	*plain,		/* Plain text of password */
		*cryptloc;	/* Where to store cryptext */
E 2
I 2
pw_cleanup()
E 2
{
D 2
	char salt[2];		/* Temp */

	if (*plain == PASSWD_QUOTE && Me.ui_uid == 0) {
		char	*p;

		if ((p = rindex(++plain, PASSWD_QUOTE))) {
			*p = 0;
			(void) strcpy(cryptloc, plain);
			return;
		}
		else plain--;
	}
	MakeRandomString(salt, sizeof(salt));
	(void) strcpy(cryptloc, crypt(plain, salt));
E 2
I 2
	/* Do nothing */
E 2
}
I 2
/*	End %M%		*/
E 2
E 1
