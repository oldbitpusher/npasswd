/*
 * Copyright 1998, The University of Texas at Austin ("U. T. Austin").
 * All rights reserved.
 *
 * By using this software the USER indicates that he or she has read,
 * understood and will comply with the following:
 *
 * U. T. Austin hereby grants USER permission to use, copy, modify, and
 * distribute this software and its documentation for any purpose and
 * without fee, provided that:
 *
 * 1. the above copyright notice appears in all copies of the software
 *    and its documentation, or portions thereof, and 
 * 2. a full copy of this notice is included with the software and its
 *    documentation, or portions thereof, and 
 * 3. neither the software nor its documentation, nor portions thereof,
 *    is sold for profit. Any commercial sale or license of this software,
 *    copies of the software, its associated documentation and/or
 *    modifications of either is strictly prohibited without the prior
 *    consent of U. T. Austin. 
 * 
 * Title to copyright to this software and its associated documentation
 * shall at all times remain with U. T. Austin. No right is granted to
 * use in advertising, publicity or otherwise any trademark, service
 * mark, or the name of U. T. Austin.
 * 
 * This software and any associated documentation are provided "as is,"
 * and U. T. AUSTIN MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESSED OR
 * IMPLIED, INCLUDING THOSE OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR
 * PURPOSE, OR THAT USE OF THE SOFTWARE, MODIFICATIONS, OR ASSOCIATED
 * DOCUMENTATION WILL NOT INFRINGE ANY PATENTS, COPYRIGHTS, TRADEMARKS OR
 * OTHER INTELLECTUAL PROPERTY RIGHTS OF A THIRD PARTY. U. T. Austin, The
 * University of Texas System, its Regents, officers, and employees shall
 * not be liable under any circumstances for any direct, indirect, special,
 * incidental, or consequential damages with respect to any claim by USER
 * or any third party on account of or arising from the use, or inability
 * to use, this software or its associated documentation, even if U. T.
 * Austin has been advised of the possibility of those damages.
 * 
 * Submit commercialization requests to: Office of the Executive Vice
 * President and Provost, U. T. Austin, 201 Main Bldg., Austin, Texas,
 * 78712, ATTN: Technology Licensing Specialist.
 */

/*
 *	This program duplicates the manual page behavior of the 4.XBSD
 *	passwd(1) command.  It can be configured for use with a variety
 *	of passwd systems (/etc/passwd, /etc/shadow, databases).
 */

#include "npasswd.h"
#include "pw_svc.h"
#include "pwm_defs.h"
#include "checkpassword.h"

#if	defined(OS_HPUX)
/*
 * HP-UX code from Mike Stute <mstute@compucom.com>
 */
# include <hpsecurity.h>
# include <prot.h>
#endif

#ifdef	AIX_AUTH
# include <userpw.h>
# include <usersec.h>
#endif

#ifndef lint
static char sccsid[] = "@(#)passwd.c	1.42 11/12/98 (cc.utexas.edu) /usr/share/src/private/ut/share/bin/passwd/V2.0/src/SCCS/s.passwd.c";
#endif

/* Local routines */
private char	*random_string _((char *, int));
private enum chg_perm	can_change_pw _((struct mpasswd *, struct mpasswd *));

/*
 * Configuration settings
 */
Config_Value char	*Passwd_Help = PASSWD_HELP,
			*Passwd_Motd = PASSWD_MOTD;

private	struct	pw_svc		*svc;	/* Service config */

/*
 * passwd - The password change command
 *
 * Usage:
 *	passwd(user, caller)
 */
public void
passwd(theUser, theCaller)
	struct mpasswd	*theUser,
			*theCaller;
{
#if	(CDEBUG >= CDEBUG_NOEXEC)
	Uid_t	myuid = 0;
#else
	Uid_t	myuid = CallerUid;	/* Userid of invoker */
#endif
	enum	chg_perm	perm;	/* Change permission */
	int	changes = CHG_NONE;	/* What was changed */
	char	newpw1[STRINGLEN],	/* New password 1 */
		newpw2[STRINGLEN];	/* New password 2 */
	
	struct pw_opaque *aux = theUser->opaque;
	struct mpasswd	*newUser;
 
	newUser = copympwent(theUser, (struct mpasswd *)0);
	svc = get_pwsvc();
	/*
	 * This section replicates some of the options
	 * for vendor-specific passwd programs.
	 */
#if	defined(OS_SUNOS_4)
	if (Switches['d']) {	/* Print aging information */
		struct tm	*lt;

		lt = gmtime(&theUser->pwage.last_change);
		if (theUser->pwage.last_change == 0) {
			lt->tm_mon = -1;
			lt->tm_mday = lt->tm_year = 0;
		}
		printf("%-10s %02d/%02d/%02d %3d %3d\n", theUser->mpw_name,
			lt->tm_mon + 1, lt->tm_mday, lt->tm_year,
			theUser->pwage.can_change / SEC_DAY,
			theUser->pwage.must_change / SEC_DAY);
		return;
	}
	if (Switches['e']) {	/* Expire this password */
		if (myuid)
			die("Permission denied.\n");
		if (!theUser->mpw_age)
			die("Must set password age using the -x option first.\n");
		newUser->pwage.last_change = 0;
		changes |= CHG_PWAGE;
		goto updatepw;
	}
	if (Switches['n']) {	/* Set maturity */
		int	days;

		if (myuid)
			die("Permission denied.\n");
		if (!theUser->mpw_age)
			die("Must set password age using the -x option first.\n");
		if (xatoi(Switches['n'], 0, &days) == 0)
			die("Invalid argument to option -n\n");
		newUser->pwage.can_change =
			((days + DAYS_WEEK - 1) / DAYS_WEEK) * SEC_WEEK;
		changes |= CHG_PWAGE;
		goto updatepw;
	}
	if (Switches['x']) {	/* Set expiration time */
		int	days;

		if (myuid)
			die("Permission denied.\n");
		if (xatoi(Switches['x'], 0, &days) == 0)
			die("Invalid argument to option -x\n");
		newUser->pwage.must_change = 
                       ((days + DAYS_WEEK - 1) / DAYS_WEEK) * SEC_WEEK;
		changes |= CHG_PWAGE;
		goto updatepw;
	}
#endif /* OS_SUNOS_4 */
#ifdef OS_HPUX
	if (Switches['d']) { /* Print aging information */
		struct tm *lt;
		time_t timen = theUser->pwage.last_change * SEC_WEEK;
		
		lt = (struct tm *)gmtime(&timen);
		if (theUser->pwage.last_change == 0) {
			lt->tm_mon = -1;
			lt->tm_mday = lt->tm_year = 0;
		}
		printf("%-10s %02d/%02d/%02d %3d %3d\n", theUser->mpw_name,
			lt->tm_mon+1, lt->tm_mday, lt->tm_year,
			theUser->pwage.can_change,
			theUser->pwage.must_change);
		return;
	}
	if(Switches['e']) { /* Expire password */
		if(myuid)
			die("Permission denied.\n");
		if (!theUser->mpw_age)
			die("Must set password age using the -x option first.\n");
		newUser->pwage.last_change = 0;
		changes |= CHG_PWAGE;
		goto updatepw;
	}
	if (Switches['n']) { /* Set maturity */
		int days;
		
		if(myuid)
			die("Permission denied.\n");
		if(theUser->mpw_age)
			die("Must set password age using the -x option first.\n");
		if (xatoi(Switches['n'], 0, &days) == 0)
			die("Invalid argument to option -n\n");
		newUser->pwage.can_change =
		((days + DAYS_WEEK -1 ) / DAYS_WEEK);
		changes |= CHG_PWAGE;
		goto updatepw;
	}
	if(Switches['x']) { /* Set expiration time */
		int days;

		if (myuid)
			die("Permission denied\n");
		if (xatoi(Switches['x'],0,&days)==0)
			die("Invalid argument to option -n\n");
		newUser->pwage.can_change=
			((days + DAYS_WEEK - 1) / DAYS_WEEK);
		changes |= CHG_PWAGE;
		goto updatepw;
	}
#endif /* OS_HPUX */
	if ((perm = can_change_pw(theUser, theCaller)) == deny)
		die("Permission denied.\n");

	if (perm == self || XSwitches[Xsw_AskAll]) {
		if (theUser->mpw_passwd[0]) {
			char	cpw[STRINGLEN];

			get_password("Current password: ", theUser->mpw_passwd,
				cpw, sizeof(cpw));
#ifdef	HAS_SECURE_RPC
			if (svc->SecurityLevel == sec_sunC2) {
				char	*rpcpw;

				rpcpw = cpw;
				while (!check_rpc_key(theUser, rpcpw)) {
					rpcpw = np_getpass("Secure RPC password: ");
				}
				if (rpcpw)
					(void) strcpy(theUser->key, rpcpw);
			}
#endif
			/* Obsfugate and stash current password */
			(void) strcpy(theUser->password, zncrypt(cpw));
		}
	}
	motd(Passwd_Motd, 0);

	printf("Changing password for %s on %s\n",
		theUser->mpw_name, theUser->pws_loc);

	for (;;) {
		char	*px;		/* Temp */
		int	tries = 0;	/* Password match counter */
		char	salt[8];
		extern int PasswdMatchTries;

		if ((px = np_getpass("New password (? for help): ")) == NULL)
			die("Password unchanged.\n");
		if (!*px)
			continue;
		(void) strcpy(newpw1, px);
		if (strcmp(newpw1, "?") == 0) {
			motd(Passwd_Help, "Sorry, there is no help.\n");
			continue;
		}
#if	0
		if (strcmp(newpw1, "^") == 0) {
			px = generate_password();
			/* Print and request them to type it in twice */
			/* Skip the checks and break the loop */
		}
#endif
		/*
		 * See if its the current password
		 */
		if (theUser->mpw_passwd &&
		    *theUser->mpw_passwd &&
		     password_cmp(theUser->mpw_passwd, newpw1)) {
			printf("That is your current password.\n");
			return;
		}
		/*
		 * Sanity check the new password
		 */
		if (XSwitches[Xsw_ForcePWChange] == 0) {
			char	*checkmsg;

			if (checkmsg = checkpassword(newpw1, &theUser->pw)) {
				printf("\nThat password cannot be used because %s.\n",
					checkmsg);
				printf("Try a different password.\n\n");
				continue;
			}
		}
		/*
		 * Get confirmation
		 */
		if ((px = np_getpass("New password (again): ")) == NULL)
			die("Password unchanged.\n");
		(void) strcpy(newpw2, px);
		if (strcmp(newpw1, newpw2)) {
			if (tries++ > PasswdMatchTries) 
				die("Too many attempts.\n");
			else
				printf("They don't match; try again.\n\n");
			if (XSwitches[Xsw_UseStdin])
				die("");
			else
				continue;
		}
		/* Obsfugate and stash current password */
		(void) strcpy(newUser->password, zncrypt(newpw1));

		(void) random_string(salt, sizeof(salt));
		newUser->mpw_passwd = strdup((*svc->PasswdCrypt)(newpw1, salt));
		changes |= (CHG_PW | CHG_PWAGE);
		break;
	}

updatepw:
	/*
	 * Stuff the bits back into the password file
	 */
	debug(DB_UPDATE, "pw_replace(%s, %s)\n",
		theUser->mpw_name,
		newUser->mpw_passwd ? newUser->mpw_passwd : "<null>");
	pw_replace(theUser, newUser, changes);

	/* If pw_replace() failed, this code will not be reached */
	if (changes & CHG_PW) {
		printf("%s password changed for %s on %s\n",
			theUser->pws_name, theUser->mpw_name, theUser->pws_loc);
		syslog(LOG_INFO,
			"Password changed on %s for %s by %s\n",
			theUser->pws_loc, theUser->mpw_name, theCaller->mpw_name);
		password_history_update(theUser->mpw_name, newUser->mpw_passwd, 0);
	}
	if (changes & CHG_PWAGE) {
		printf("%s password aging changed for %s on %s\n",
			 theUser->pws_name, theUser->mpw_name, theUser->pws_loc);
		syslog(LOG_INFO,
			"Password aging changed on %s for %s by %s\n",
			theUser->pws_loc, theUser->mpw_name, theCaller->mpw_name);
	}
}

/*
 *	can_change - check password change permission
 *
 *	Returns 1 if password can be changed
 *		0 if not
 */
private enum chg_perm
can_change_pw(theUser, theCaller)
	struct mpasswd	*theUser,
			*theCaller;
{
#ifdef	USE_NIS
	/*
	 * %%POLICY - Changing other users' passwd info via NIS.
	 *
	 * In order to use the RPC interface to replace a passwd entry,
	 * the plaintext of the current password is required.
	 *
	 * This is ok for the user but not the system administrator.
	 * I assume that because the super-user is changing someone else's
	 * password, the current password is not available.  This assumption
	 * is implicitly extended to chsh and chfn also.
	 *
	 * So disallow the change if the caller is root and not changing
	 * their own password.
	 */
	{
		struct ypinfo ypinfo;

		ypwhich(PASSWD_BYNAME, &ypinfo);
		if (CallerUid == 0 &&
		    ypinfo.status == is_yp_client &&
		    XSwitches[Xsw_AskAll] == 0 &&
		    theUser->pws_remote) {
			printf("Information can only be changed on NIS master %s.\n",
				ypinfo.master);
			return(deny);
		}
	}
#endif	/* USE_NIS */

	if (CallerUid == 0)		/* Su can change any passwd */
		return(other);

	if (strcmp(theCaller->mpw_name, theUser->mpw_name))
		return(deny);		/* I'm not root and target isn't me */

	/*
 	 * Check password age
	 */
	if (theUser->mpw_age) {
		time_t	now;

		(void) time(&now);
		if (theUser->pwage.last_change <= now && CallerUid) {
			if (now < (theUser->pwage.last_change + theUser->pwage.can_change)) {
				printf("You may not change your password for %d more days.\n",
				(theUser->pwage.last_change +
				 theUser->pwage.can_change - now) / SEC_DAY);
				return(deny);
			}
			if (theUser->pwage.can_change > theUser->pwage.must_change) {
				printf("You may not change your password.\n");
				return(deny);
			}
		}
	}
	/*
	 * Call the method auth check routine
	 */
	if (check_auth(theUser) == deny)
		return(deny);

	/*
	 * Other checks can be put here to determine if the invoker should
	 * be allowed to change this password.
	 */
	return(pw_permission(theUser, theCaller));
}

/* 
 *	random_string - create a string of random characters
 */
private char *
random_string(buf, buflen)
	char	*buf;		/* String buffer */
	int	buflen;		/* Length of buf */
{
	int	i,		/* Temp */
		n;		/* Temp */
	unsigned int	tv;	/* Srand seed */
	char	proto[128];	/* Build buffer */

	buflen--;		/* Avoid overflowing <buf> */
	tv = (unsigned int) time((time_t *)0);
	(void) srand ( (tv & 0x07201969) ^ getpid ());
	for (i = 0; i < sizeof(proto); i++) {	/* fill proto vector */
		int	c;		/* Temp */

		for (;;) {
			c = rand() % 0x7f;	/* turn into ASCII */
			if (isalnum(c))
				break;
		}
		proto[i] = (char )c;
	}
	(void) srand((tv & 0x11201972) ^ getpid());
	for (i = 0; i < buflen; i++) {
		n = rand() % sizeof proto;
		buf[i] = proto[n];
	}
	buf[buflen] = 0;
	return(buf);
}

/* End passwd.c */
