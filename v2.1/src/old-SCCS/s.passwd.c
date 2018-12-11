h41392
s 00055/00024/00442
d D 1.44 00/01/17 18:15:17 clyde 44 43
c 1. Add option -XA (always ask for old password)
c 2. Add option -XO (ask for new password only once)
c 3. Don't print password aging message if aging not active
e
s 00009/00002/00457
d D 1.43 99/07/23 16:36:20 clyde 43 42
c Add the current password to history if not present
e
s 00002/00001/00457
d D 1.42 98/11/12 17:08:25 clyde 42 41
c Add -XA (always ask for current password)
e
s 00019/00007/00439
d D 1.41 98/08/17 16:58:01 clyde 41 40
c 1. Change use of zncrypt() and zdcrypt()
c 2. Add stub for password generator
e
s 00002/00003/00444
d D 1.40 98/07/21 09:31:18 clyde 40 39
c Obsfugate copy of plaintext password
e
s 00005/00080/00442
d D 1.39 98/07/20 15:19:26 clyde 39 38
c Move method change permission code to Method routines
e
s 00014/00010/00508
d D 1.38 98/07/09 14:19:29 clyde 38 37
c Changes for new pwsvc() routines
e
s 00002/00002/00516
d D 1.37 98/06/30 15:30:22 clyde 37 36
c Tweak password change user messages
e
s 00001/00001/00517
d D 1.36 98/06/30 10:34:17 clyde 36 35
c Change checkpasswd.h to checkpassword.h
e
s 00001/00001/00517
d D 1.35 98/06/23 13:52:09 clyde 35 34
c Fix call for password_history_update()
e
s 00068/00060/00450
d D 1.34 98/06/23 11:07:24 clyde 34 33
c 1. Add copyright notice
c 2. Change name of some config variable
c 3. Eliminate password_ok() routine
c 4. Remove 'punt' code
c 5. Change debugging ifdef trigger
e
s 00028/00241/00482
d D 1.33 98/04/21 10:58:45 clyde 33 32
c Move getpass() and related routines to seperate file in comobj lib
e
s 00094/00016/00629
d D 1.32 98/03/26 11:22:18 clyde 32 31
c 1. Add HP-UX auth support
c 2. Change password_ok() call sequence
c 3. Delay after user enters invalid password
e
s 00027/00002/00618
d D 1.31 97/09/23 12:21:29 clyde 31 30
c 1. Fix SunOS 4 adjunct password check
c 2. Add AIX auth support
e
s 00007/00007/00613
d D 1.30 97/06/18 13:36:04 clyde 30 29
c Change getpass() to np_getpass()
e
s 00001/00004/00619
d D 1.29 97/05/23 13:17:54 clyde 29 28
c Fix call of password history routine
e
s 00001/00001/00622
d D 1.28 97/05/05 10:35:19 clyde 28 27
c Change missing help file message
e
s 00003/00003/00620
d D 1.27 96/09/13 16:45:38 clyde 27 26
c Comment out use of #error
e
s 00086/00062/00537
d D 1.26 96/08/29 13:09:34 clyde 26 25
c 1. Remove 'const' declarations (too much compiler pain)
c 2. Make older C compilers happy
c 3. Compile under SunOS 4 acc
c 4. Fix use of getpass()
c 5. Force use of my getpass()
c 6. Rewrite getpass() - no stdio, honor "use stdin" flag
c 7. Import CallerUid var from global (can't alway rely on getuid(2) on OSF)
c 8. Rewrite some comments
e
s 00005/00005/00594
d D 1.25 96/08/15 11:00:57 clyde 25 24
c Fix const usess
e
s 00003/00003/00596
d D 1.24 96/08/14 19:00:09 clyde 24 23
c Fix punctuation for die() strings
e
s 00005/00004/00594
d D 1.23 96/08/14 11:31:55 clyde 23 22
c beta 3: compiles OSF/1 3.2
e
s 00001/00001/00597
d D 1.22 96/08/13 16:55:09 clyde 22 21
c Change call for copympwent()
e
s 00002/00002/00596
d D 1.21 96/08/09 16:35:24 clyde 21 20
c Use defines from checkpasswd.h
e
s 00007/00006/00591
d D 1.20 96/08/09 16:16:47 clyde 20 19
c Beta 3 development checkin 2
e
s 00137/00130/00460
d D 1.19 96/08/06 14:14:06 clyde 19 18
c beta 3 cycle 1 checkin
e
s 00017/00017/00573
d D 1.18 96/04/03 14:39:24 clyde 18 17
c  Reflect new mpasswd structure element names
e
s 00002/00005/00588
d D 1.17 96/03/27 09:28:22 clyde 17 16
c Use debug() routine for messages
e
s 00141/00121/00452
d D 1.16 95/04/05 16:19:56 clyde 16 15
c Beta 3 development checkin
e
s 00043/00016/00530
d D 1.15 94/10/24 10:33:22 clyde 15 14
c 1. Change "punt()"
c 2. Add better support for Secure RPC passwords 
c 3. Add first level of hooks for NIS+
e
s 00025/00026/00521
d D 1.14 94/09/28 16:14:39 clyde 14 13
c Use new password aging field names
e
s 00005/00003/00542
d D 1.13 94/06/20 13:49:31 clyde 13 12
c Cleanup debugging statements
e
s 00060/00106/00485
d D 1.12 94/05/17 15:38:39 clyde 12 11
c 1. Abstract password age checking.
c 2. Abstract password encryption.
c 3. Support OSF/1 enhanced security.
c 4. Add stub for calling vendor passwd program when needed.
e
s 00012/00013/00579
d D 1.11 94/03/31 17:43:21 clyde 11 10
c Make password aging updates work right
e
s 00004/00007/00588
d D 1.10 94/03/16 11:08:12 clyde 10 9
c Re-enable password checking
e
s 00004/00000/00591
d D 1.9 94/03/16 09:36:55 clyde 9 8
c Make ANSI compilers more happy
e
s 00007/00011/00584
d D 1.8 94/03/15 18:51:54 clyde 8 7
c Hooks for password history
e
s 00005/00005/00590
d D 1.7 94/03/15 11:09:38 clyde 7 6
c Fix debugging code, make work on OSF/1 ALPHA
e
s 00038/00014/00557
d D 1.6 94/03/01 16:01:11 clyde 6 5
c Development checkin:
c 1. Change random_string()
c 2. Stuff moved from other modules
e
s 00004/00000/00567
d D 1.5 93/12/17 17:09:48 clyde 5 4
c Update users' secret key
e
s 00040/00038/00527
d D 1.4 93/12/16 11:04:22 clyde 4 3
c Development checkin
e
s 00146/00010/00419
d D 1.3 93/07/12 15:04:19 clyde 3 2
c 1. Incorporate most of pw_permission().
c 2. Rename cmp_password to password_cmp()
e
s 00041/00004/00388
d D 1.2 93/07/12 11:06:44 clyde 2 1
c Insert password checking code (from backend)
e
s 00392/00000/00000
d D 1.1 93/07/12 09:18:14 clyde 1 0
c date and time created 93/07/12 09:18:14 by clyde
e
u
U
f e 0
t
T
I 1
/*
I 34
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
E 34
 *	This program duplicates the manual page behavior of the 4.XBSD
 *	passwd(1) command.  It can be configured for use with a variety
 *	of passwd systems (/etc/passwd, /etc/shadow, databases).
D 32
 *
E 32
 */
I 32

E 32
#include "npasswd.h"
I 38
#include "pw_svc.h"
E 38
I 6
D 14
#include "pw_defs.h"
E 6
I 3
#include "pw_nis.h"
E 14
I 14
D 20
#include "pwm_defs.h"
E 20
I 20
D 41
#include "Methods/pwm_defs.h"
E 41
I 41
#include "pwm_defs.h"
E 41
I 21
D 36
#include "PasswordCheck/checkpasswd.h"
E 36
I 36
D 38
#include "PasswordCheck/checkpassword.h"
E 38
I 38
#include "checkpassword.h"
E 38
E 36
E 21
E 20
E 14
E 3

D 14
#include <sys/time.h>

E 14
I 6
D 12
#ifdef	ULTRIX_SHADOW
E 12
I 12
D 16
#ifdef	ULTRIX_SECURITY
E 16
I 16
D 39
#if	defined(OS_ULTRIX_4)
E 16
E 12
# include <auth.h>
#endif

E 39
I 32
#if	defined(OS_HPUX)
/*
 * HP-UX code from Mike Stute <mstute@compucom.com>
 */
# include <hpsecurity.h>
# include <prot.h>
#endif

E 32
I 31
#ifdef	AIX_AUTH
# include <userpw.h>
# include <usersec.h>
#endif

E 31
I 19
D 34
#ifndef	VENDOR_PASSWD
# define	VENDOR_PASSWD	"/usr/bin/passwd"
#endif

E 34
E 19
E 6
#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu) %P%";
#endif

D 3
passwd(user, caller)
E 3
I 3
D 19
#ifdef	__STDC__
D 4
static int	password_ok(struct mpasswd *, char *, char *);
static int	can_change(struct mpasswd *, struct mpasswd *);
E 4
I 4
private int	password_ok(struct mpasswd *, char *, char *);
I 16
private void	punt(const char *);
E 16
E 4
#else
D 4
static int	password_ok();
static int	can_change();
E 4
I 4
private int	password_ok();
I 16
private void	punt();
E 16
E 4
#endif
E 19
I 19
/* Local routines */
D 32
private int	password_ok _((struct mpasswd *, char *, char *));
E 32
I 32
D 34
private int	password_ok _((struct mpasswd *, char *, char *, unsigned int));
E 32
D 26
private void	punt _((const char *));
E 26
I 26
private void	punt _((char *));
E 34
E 26
D 20
private void	get_password _((char *, char *, char *, int));
E 20
private char	*random_string _((char *, int));
I 23
D 26
private int	password_cmp _((const char *, const char *));
E 26
I 26
D 33
private int	password_cmp _((char *, char *));
E 33
E 26
E 23
private enum chg_perm	can_change_pw _((struct mpasswd *, struct mpasswd *));
E 19

I 6
D 19
#ifndef PASSWD_HELP
# define	PASSWD_HELP	"/usr/adm/passwd.help"
#endif
E 19
I 19
/*
 * Configuration settings
 */
D 34
Config_Value char	*PasswdHelpFile = PASSWD_HELP,
			*PasswdMotdFile = PASSWD_MOTD;
D 33
Config_Value int	PasswdMatchTries = 3;
I 32
Config_Value unsigned int	PasswdMatchWait = PASSWORD_MATCH_WAIT;
E 32
E 19

E 33
D 19
#ifndef PASSWD_MOTD
# define	PASSWD_MOTD	"/usr/adm/passwd.motd"
#endif

D 11
#define DAYS_PER_WEEK	7
#define SEC_PER_WEEK	((time_t )(24 * DAYS_PER_WEEK * 60 * 60))

E 11
public char	PasswdHelpFile[MAXPATHLEN] = { PASSWD_HELP },
		PasswdMotdFile[MAXPATHLEN] = { PASSWD_MOTD };
public int	PasswdMatchTries = 3;

I 15
#ifndef	VENDOR_PASSWD
# define	VENDOR_PASSWD	(char *)0
#endif
E 19
I 19
/*
 * Private variables
 */
E 19
private char	*vendor_passwd = VENDOR_PASSWD;
E 34
I 34
Config_Value char	*Passwd_Help = PASSWD_HELP,
			*Passwd_Motd = PASSWD_MOTD;
E 34

I 38
private	struct	pw_svc		*svc;	/* Service config */

E 38
E 15
E 6
D 19
public void passwd(user, caller)
E 3
struct mpasswd	*user,
		*caller;
E 19
I 19
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
E 19
{
D 4
#ifdef	DEBUG
E 4
I 4
D 34
#ifdef	DEBUGX
E 34
I 34
#if	(CDEBUG >= CDEBUG_NOEXEC)
E 34
E 4
D 16
	uid_t	myuid = 0;
E 16
I 16
	Uid_t	myuid = 0;
E 16
#else
D 16
	uid_t	myuid = getuid();	/* Userid of caller */
E 16
I 16
D 19
	Uid_t	myuid = getuid();	/* Userid of caller */
E 19
I 19
D 26
	Uid_t	myuid = getuid();	/* Userid of invoker */
E 26
I 26
	Uid_t	myuid = CallerUid;	/* Userid of invoker */
E 26
E 19
E 16
#endif
I 4
D 13
	enum	chg_perm	perm;	/* */
E 13
I 13
	enum	chg_perm	perm;	/* Change permission */
E 13
E 4
D 19
	int	pwchanged = 0;		/* Was the password changed? */
	char	newpw1[STRINGLEN],	/* Temp */
		newpw2[STRINGLEN];	/* Temp */
I 2
D 11
	char	*crypw;
E 11
I 11
D 13
	char	*crypw = 0;
E 13
I 13
	char	*crypw = 0;		/* Encrypted current password */
E 13
E 11
I 8
D 10
	int	rc;
E 10
E 8
I 6
	struct pw_opaque *aux = user->opaque;
E 19
I 19
	int	changes = CHG_NONE;	/* What was changed */
	char	newpw1[STRINGLEN],	/* New password 1 */
		newpw2[STRINGLEN];	/* New password 2 */
	
	struct pw_opaque *aux = theUser->opaque;
	struct mpasswd	*newUser;
E 19
E 6
E 2
 
I 19
D 22
	newUser = copympwent(theUser);
E 22
I 22
	newUser = copympwent(theUser, (struct mpasswd *)0);
I 38
	svc = get_pwsvc();
E 38
I 34
	/*
	 * This section replicates some of the options
	 * for vendor-specific passwd programs.
	 */
E 34
E 22
E 19
D 12
#ifdef	S5_PWAGING
	time_t	lastchange = 0,
		maxpwtime = 0,
		minpwtime = 0;

	if (user->mpw_age) {
		extern long a64l();
		long	pwage;

		pwage = a64l(user->mpw_age);
		maxpwtime = pwage & 077;
		minpwtime = (pwage >> 6) & 077;
		lastchange = (pwage >> 12) * SEC_PER_WEEK;
	}
#endif
D 11
#if	defined(S5_PWAGING) && OS_SUNOS_4
E 11
I 11
#if	defined(S5_PWAGING) && defined(OS_SUNOS_4)
E 12
I 12
#if	defined(OS_SUNOS_4)
E 12
E 11
D 19
	if (CommandLineOption['d']) {	/* Print aging information */
E 19
I 19
	if (Switches['d']) {	/* Print aging information */
E 19
		struct tm	*lt;

D 19
		/* I don't know why localtime() isn't used */
D 12
		lt = gmtime(&lastchange);
		if (lastchange == 0) {
E 12
I 12
D 14
		lt = gmtime(&user->last_change);
		if (user->last_change == 0) {
E 14
I 14
		lt = gmtime(&user->pwage.last_change);
		if (user->pwage.last_change == 0) {
E 19
I 19
		lt = gmtime(&theUser->pwage.last_change);
		if (theUser->pwage.last_change == 0) {
E 19
E 14
E 12
			lt->tm_mon = -1;
			lt->tm_mday = lt->tm_year = 0;
		}
D 19
		printf("%-10s %02d/%02d/%02d %3d %3d\n", user->mpw_name,
E 19
I 19
		printf("%-10s %02d/%02d/%02d %3d %3d\n", theUser->mpw_name,
E 19
			lt->tm_mon + 1, lt->tm_mday, lt->tm_year,
D 12
			minpwtime * DAYS_PER_WEEK, maxpwtime * DAYS_PER_WEEK);
E 12
I 12
D 14
			user->min_change_time / SEC_PER_DAY,
			user->expire / SEC_PER_DAY);
E 14
I 14
D 18
			user->pwage.min_time / SEC_PER_DAY,
			user->pwage.max_time / SEC_PER_DAY);
E 18
I 18
D 19
			user->pwage.can_change / SEC_PER_DAY,
			user->pwage.must_change / SEC_PER_DAY);
E 19
I 19
			theUser->pwage.can_change / SEC_DAY,
			theUser->pwage.must_change / SEC_DAY);
E 19
E 18
E 14
E 12
		return;
	}
D 19
	if (CommandLineOption['e']) {	/* Expire this password */
E 19
I 19
	if (Switches['e']) {	/* Expire this password */
E 19
		if (myuid)
			die("Permission denied.\n");
D 12
		if (!user->mpw_age)
E 12
I 12
D 14
		if (!user->age_password)
E 14
I 14
D 18
		if (!user->pwage.doit)
E 18
I 18
D 19
		if (!user->pwage.do_aging)
E 19
I 19
D 26
		if (!theUser->pwage.mpw_age)
E 26
I 26
		if (!theUser->mpw_age)
E 26
E 19
E 18
E 14
E 12
D 24
			die("Must set password age using the -x option first.");
E 24
I 24
			die("Must set password age using the -x option first.\n");
E 24
D 12
		lastchange = 0;
E 12
I 12
D 14
		user->last_change = 0;
E 14
I 14
D 19
		user->pwage.last_change = 0;
E 14
E 12
I 11
		crypw = user->mpw_passwd;
E 19
I 19
		newUser->pwage.last_change = 0;
D 26
		changes =| CHG_PWAGE;
E 26
I 26
		changes |= CHG_PWAGE;
E 26
E 19
E 11
D 44
		goto updatepw;
E 44
	}
D 19
	if (CommandLineOption['n']) {	/* Set maturity */
E 19
I 19
	if (Switches['n']) {	/* Set maturity */
E 19
		int	days;

		if (myuid)
			die("Permission denied.\n");
D 12
		if (!user->mpw_age)
E 12
I 12
D 14
		if (!user->age_password)
E 14
I 14
D 18
		if (!user->pwage.doit)
E 18
I 18
D 19
		if (!user->pwage.do_aging)
E 19
I 19
D 26
		if (!theUser->pwage.mpw_age)
E 26
I 26
		if (!theUser->mpw_age)
E 26
E 19
E 18
E 14
E 12
D 24
			die("Must set password age using the -x option first.");
E 24
I 24
			die("Must set password age using the -x option first.\n");
E 24
D 19
		if (sscanf(CommandLineOption['n'], "%d", &days) == 0)
E 19
I 19
D 26
		if (xatoi(Switches['n'], (char *)0, &days) == 0)
E 26
I 26
		if (xatoi(Switches['n'], 0, &days) == 0)
E 26
E 19
			die("Invalid argument to option -n\n");
D 12
		minpwtime = (days + DAYS_PER_WEEK - 1) / DAYS_PER_WEEK;
E 12
I 12
D 14
		user->min_change_time = ((days + DAYS_PER_WEEK - 1) / DAYS_PER_WEEK) * SEC_PER_WEEK;
E 14
I 14
D 18
		user->pwage.min_time = ((days + DAYS_PER_WEEK - 1) / DAYS_PER_WEEK) * SEC_PER_WEEK;
E 18
I 18
D 19
		user->pwage.can_change = ((days + DAYS_PER_WEEK - 1) / DAYS_PER_WEEK) * SEC_PER_WEEK;
E 18
E 14
E 12
I 11
		crypw = user->mpw_passwd;
E 19
I 19
		newUser->pwage.can_change =
			((days + DAYS_WEEK - 1) / DAYS_WEEK) * SEC_WEEK;
D 26
		changes =| CHG_PWAGE;
E 26
I 26
		changes |= CHG_PWAGE;
E 26
E 19
E 11
D 44
		goto updatepw;
E 44
	}
D 19
	if (CommandLineOption['x']) {	/* Expiration time */
E 19
I 19
	if (Switches['x']) {	/* Set expiration time */
E 19
		int	days;

		if (myuid)
			die("Permission denied.\n");
D 19
		if (sscanf(CommandLineOption['x'], "%d", &days) == 0)
E 19
I 19
D 26
		if (xatoi(Switches['x'], (char *)0, &days) == 0)
E 26
I 26
		if (xatoi(Switches['x'], 0, &days) == 0)
E 26
E 19
			die("Invalid argument to option -x\n");
D 12
		maxpwtime = (days + DAYS_PER_WEEK - 1) / DAYS_PER_WEEK;
E 12
I 12
D 14
		user->expire = ((days + DAYS_PER_WEEK - 1) / DAYS_PER_WEEK) * SEC_PER_WEEK;
E 14
I 14
D 18
		user->pwage.max_time = ((days + DAYS_PER_WEEK - 1) / DAYS_PER_WEEK) * SEC_PER_WEEK;
E 18
I 18
D 19
		user->pwage.must_change = ((days + DAYS_PER_WEEK - 1) / DAYS_PER_WEEK) * SEC_PER_WEEK;
E 18
E 14
E 12
I 11
		crypw = user->mpw_passwd;
E 19
I 19
D 32
		newUser->pwage.must_change = ((days + DAYS_WEEK - 1) / DAYS_WEEK) * SEC_WEEK;
E 32
I 32
		newUser->pwage.must_change = 
                       ((days + DAYS_WEEK - 1) / DAYS_WEEK) * SEC_WEEK;
E 32
D 26
		changes =| CHG_PWAGE;
E 26
I 26
		changes |= CHG_PWAGE;
E 26
E 19
E 11
D 44
		goto updatepw;
E 44
	}
I 44
	if (changes & CHG_PWAGE)
		goto updatepw;
		
E 44
#endif /* OS_SUNOS_4 */
I 32
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
D 44
		if(myuid)
E 44
I 44
		if (myuid)
E 44
			die("Permission denied.\n");
		if (!theUser->mpw_age)
			die("Must set password age using the -x option first.\n");
		newUser->pwage.last_change = 0;
		changes |= CHG_PWAGE;
D 44
		goto updatepw;
E 44
	}
	if (Switches['n']) { /* Set maturity */
		int days;
		
D 44
		if(myuid)
E 44
I 44
		if (myuid)
E 44
			die("Permission denied.\n");
D 44
		if(theUser->mpw_age)
E 44
I 44
		if (theUser->mpw_age)
E 44
			die("Must set password age using the -x option first.\n");
		if (xatoi(Switches['n'], 0, &days) == 0)
			die("Invalid argument to option -n\n");
		newUser->pwage.can_change =
		((days + DAYS_WEEK -1 ) / DAYS_WEEK);
		changes |= CHG_PWAGE;
D 44
		goto updatepw;
E 44
	}
	if(Switches['x']) { /* Set expiration time */
		int days;
E 32

I 32
		if (myuid)
			die("Permission denied\n");
		if (xatoi(Switches['x'],0,&days)==0)
			die("Invalid argument to option -n\n");
		newUser->pwage.can_change=
			((days + DAYS_WEEK - 1) / DAYS_WEEK);
		changes |= CHG_PWAGE;
D 44
		goto updatepw;
E 44
	}
I 44
	if (changes & CHG_PWAGE)
		goto updatepw;
E 44
#endif /* OS_HPUX */
E 32
D 3
	if (pw_permission(user, caller) == 0)
E 3
I 3
D 4
	if (can_change(user, caller) == 0)
E 4
I 4
D 19
	if ((perm = can_change(user, caller)) == deny)
E 19
I 19
	if ((perm = can_change_pw(theUser, theCaller)) == deny)
E 19
E 4
E 3
		die("Permission denied.\n");

D 4
	if (user->mpw_passwd[0] /* flag to force password read? */)
		get_password(user->mpw_passwd,
			user->password, sizeof(user->password));
E 4
I 4
D 42
	if (perm == self) {
E 42
I 42
D 44
	if (perm == self || XSwitches[Xsw_AskAll]) {
E 44
I 44
	if (perm == self || XSwitches[Xsw_AskAlways]) {
E 44
E 42
D 15
		if (user->mpw_passwd[0])
			get_password(user->mpw_passwd,
E 15
I 15
D 19
		if (user->mpw_passwd[0]) {
			get_password("Current password: ", user->mpw_passwd,
E 15
				user->password, sizeof(user->password));
E 19
I 19
		if (theUser->mpw_passwd[0]) {
I 41
			char	cpw[STRINGLEN];

E 41
			get_password("Current password: ", theUser->mpw_passwd,
D 41
				theUser->password, sizeof(theUser->password));
E 41
I 41
				cpw, sizeof(cpw));
E 41
E 19
I 15
D 16
#ifdef	SUN_SECURITY
E 16
I 16
#ifdef	HAS_SECURE_RPC
E 16
D 19
			if (SecurityLevel == sec_sunC2) {
E 19
I 19
D 20
			if (svc_SecurityLevel == sec_sunC2) {
E 20
I 20
D 38
			if (svc.SecurityLevel == sec_sunC2) {
E 38
I 38
			if (svc->SecurityLevel == sec_sunC2) {
E 38
E 20
E 19
				char	*rpcpw;

D 19
				rpcpw = user->password;
				while (!check_rpc_key(user, rpcpw)) {
E 19
I 19
D 41
				rpcpw = theUser->password;
E 41
I 41
				rpcpw = cpw;
E 41
				while (!check_rpc_key(theUser, rpcpw)) {
E 19
D 30
					rpcpw = getpass("Secure RPC password: ");
E 30
I 30
					rpcpw = np_getpass("Secure RPC password: ");
E 30
				}
D 19
				(void) strcpy(user->key, rpcpw);
E 19
I 19
D 26
				(void) strcpy(theUser->key, rpcpw);
E 26
I 26
D 41
				if (rpcpw) (void) strcpy(theUser->key, rpcpw);
E 41
I 41
				if (rpcpw)
					(void) strcpy(theUser->key, rpcpw);
E 41
E 26
E 19
			}
#endif
I 40
D 41
			zncrypt(theUser->password); /* Obsfugate password */
E 41
I 41
			/* Obsfugate and stash current password */
			(void) strcpy(theUser->password, zncrypt(cpw));
E 41
E 40
		}
E 15
	}
I 19
D 34
	motd(PasswdMotdFile, 0);
E 34
I 34
	motd(Passwd_Motd, 0);
E 34
E 19
E 4

D 6
	motd(PASSWD_MOTD, (char *)0);
E 6
I 6
D 19
	motd(PasswdMotdFile, (char *)0);
E 19
I 19
	printf("Changing password for %s on %s\n",
		theUser->mpw_name, theUser->pws_loc);
E 19
E 6

D 18
	printf("Changing password for %s on %s\n", user->mpw_name, user->where);
E 18
I 18
D 19
	printf("Changing password for %s on %s\n", user->mpw_name, user->pws_loc);
E 18

E 19
	for (;;) {
		char	*px;		/* Temp */
D 19
		int	ntries = 0;	/* Password match counter */
E 19
I 19
		int	tries = 0;	/* Password match counter */
E 19
D 32
		char	checkmsg[512];
E 32
I 32
D 34
		char	checkmsg[STRINGLEN];
E 34
E 32
I 19
		char	salt[8];
I 34
		extern int PasswdMatchTries;
E 34
E 19

D 19
		px = getpass(ProgramInput ? "" : "New password (? for help): ");
E 19
I 19
D 26
		px = getpass(XSwitches[Xsw_UseStdin] ? 
			"" : "New password (? for help): ");
E 19
		if (px == NULL)
			die("EOF during new password read.\n");
I 12
D 19
		if (!*px)
E 19
I 19
		if (!*px)		/* User entered nothing */
E 26
I 26
D 30
		if ((px = getpass("New password (? for help): ")) == NULL)
E 30
I 30
		if ((px = np_getpass("New password (? for help): ")) == NULL)
E 30
			die("Password unchanged.\n");
		if (!*px)
E 26
E 19
			continue;
E 12
		(void) strcpy(newpw1, px);
		if (strcmp(newpw1, "?") == 0) {
D 6
			motd(PASSWD_HELP, "Missing help file");
E 6
I 6
D 28
			motd(PasswdHelpFile, "Missing help file");
E 28
I 28
D 34
			motd(PasswdHelpFile, "Sorry, there is no help.\n");
E 34
I 34
			motd(Passwd_Help, "Sorry, there is no help.\n");
E 34
E 28
E 6
			continue;
		}
I 41
#if	0
		if (strcmp(newpw1, "^") == 0) {
			px = generate_password();
			/* Print and request them to type it in twice */
			/* Skip the checks and break the loop */
		}
#endif
E 41
		/*
I 4
		 * See if its the current password
		 */
D 12
		if (password_cmp(user->mpw_passwd, newpw1)) {
E 12
I 12
D 19
		if (user->mpw_passwd &&
		    *user->mpw_passwd &&
		     password_cmp(user->mpw_passwd, newpw1)) {
E 19
I 19
		if (theUser->mpw_passwd &&
		    *theUser->mpw_passwd &&
		     password_cmp(theUser->mpw_passwd, newpw1)) {
E 19
E 12
			printf("That is your current password.\n");
I 44
			if (XSwitches[Xsw_AskOnce]) {
				die("");
				/*NOTREACHED*/
			}
E 44
			return;
		}
		/*
E 4
		 * Sanity check the new password
		 */
D 2
		if (pw_check(user, newpw1, checkmsg) == 0) {
E 2
I 2
D 19
		if (password_ok(user, newpw1, checkmsg) == 0) {
E 19
I 19
D 34
		if (XSwitches[Xsw_ForcePWChange] == 0 &&
D 32
		    password_ok(theUser, newpw1, checkmsg) == 0) {
E 32
I 32
		    password_ok(theUser, newpw1, checkmsg, sizeof checkmsg) == 0) {
E 32
E 19
E 2
			printf("\nThat password cannot be used because %s.\n",
				checkmsg);
			printf("Try a different password.\n\n");
			continue;
E 34
I 34
		if (XSwitches[Xsw_ForcePWChange] == 0) {
			char	*checkmsg;

			if (checkmsg = checkpassword(newpw1, &theUser->pw)) {
				printf("\nThat password cannot be used because %s.\n",
					checkmsg);
I 44
				if (XSwitches[Xsw_AskOnce])
					die("");
E 44
				printf("Try a different password.\n\n");
				continue;
			}
E 34
		}
		/*
		 * Get confirmation
		 */
D 19
		px = getpass(ProgramInput ? "" : "New password (again): ");
E 19
I 19
D 26
		px = getpass(XSwitches[Xsw_UseStdin] ?
			"" : "New password (again): ");
E 19
		if (px == NULL)
			die("EOF during new password read.\n");
E 26
I 26
D 30
		if ((px = getpass("New password (again): ")) == NULL)
E 30
I 30
D 44
		if ((px = np_getpass("New password (again): ")) == NULL)
E 44
I 44
		if ((px = np_getpass("New password (again): ")) == NULL) {
E 44
E 30
			die("Password unchanged.\n");
I 44
			/*NOTREACHED*/
		}
E 44
E 26
		(void) strcpy(newpw2, px);
		if (strcmp(newpw1, newpw2)) {
D 6
			if (ntries++ >= pwReadTries) 
E 6
I 6
D 19
			if (ntries++ >= PasswdMatchTries) 
E 19
I 19
D 32
			if (tries++ >= PasswdMatchTries) 
E 32
I 32
D 44
			if (tries++ > PasswdMatchTries) 
E 32
E 19
E 6
				die("Too many attempts.\n");
			else
				printf("They don't match; try again.\n\n");
D 19
			if (ProgramInput)
E 19
I 19
			if (XSwitches[Xsw_UseStdin])
E 44
I 44
			if (XSwitches[Xsw_AskOnce] ||
			    XSwitches[Xsw_UseStdin]) {
				printf("Passwords do not match.\n\n");
E 44
E 19
D 32
				die((char *)0);
E 32
I 32
				die("");
E 32
D 44
			else
				continue;
E 44
I 44
				/*NOTREACHED*/
			} else {
				if (tries++ > PasswdMatchTries) {
					die("Too many attempts.\n");
					/*NOTREACHED*/
				}
			 	printf("Passwords do not match; try again.\n\n");
			}
			continue;
E 44
		}
D 4
		/*
		 * Disallow new password == old password
		 */
D 3
		if (cmp_password(user->mpw_passwd, newpw1)) {
E 3
I 3
		if (password_cmp(user->mpw_passwd, newpw1)) {
E 3
			printf("New password must be different than old; try again.\n\n");
			if (ProgramInput)
				die((char *)0);
			else
				continue;
		}
		else {
			pwchanged = 1;
			break;
		}
E 4
I 4
D 19
		pwchanged = 1;
E 19
I 19
D 34
		strcpy(newUser->password, strdup(newpw1));
E 34
I 34
D 40
		/* XXX newUser->password needs to be encrypted somehow */
		/* XXX or not set unless really needed (e.g. NIS) */
I 39

E 40
E 39
D 41
		(void) strcpy(newUser->password, strdup(newpw1));
I 40
		zncrypt(newUser->password);
E 41
I 41
		/* Obsfugate and stash current password */
		(void) strcpy(newUser->password, zncrypt(newpw1));

E 41
E 40
E 34
		(void) random_string(salt, sizeof(salt));
D 20
		newUser->mpw_passwd = strdup((*svc_PasswdCrypt)(newpw1, salt));
E 20
I 20
D 38
		newUser->mpw_passwd = strdup((*svc.PasswdCrypt)(newpw1, salt));
E 38
I 38
		newUser->mpw_passwd = strdup((*svc->PasswdCrypt)(newpw1, salt));
E 38
E 20
D 32
		changes |= CHG_PW;
E 32
I 32
D 44
		changes |= (CHG_PW | CHG_PWAGE);
E 44
I 44
		changes |= CHG_PW;
#ifdef	PWAGE
		/*
		 * If password has aging, update it and tell the user
		 */
		if (newUser->mpw_age)
			changes |= CHG_PWAGE;
E 44
E 32
E 19
		break;
I 44
#endif
E 44
E 4
	}

D 44
updatepw:
E 44
I 44
updatepw:		/* Ugh */
E 44
D 12
#ifdef	S5_PWAGING
E 12
	/*
D 12
	 * Update password aging information
	 */
I 6
	/* Configuration file setting to enforce a max password age? */
E 6
	if (user->mpw_age) {
		if (maxpwtime == 0) {
			*user->mpw_age = '\0';
		}
		else {
			extern char *l64a();
			time_t	now = lastchange / SEC_PER_WEEK,
				pwage;

			if (pwchanged)
				now = time((time_t *)0) / SEC_PER_WEEK;
			pwage = maxpwtime
				+ (minpwtime << 6)
				+ (now << 12);
			if (pwage)
				user->mpw_age = l64a(pwage);
			else
				user->mpw_age = ".";
		}
	}
#endif
	/*
E 12
I 2
D 19
	 * Encrypt the new password
	 */
	if (pwchanged) {
D 4
		(void) random_string(newpw2, sizeof(newpw2));
		crypw = crypt(newpw1, newpw2);
E 4
I 4
		char	salt[8];
I 5

E 5
		(void) random_string(salt, sizeof(salt));
D 12
		crypw = copystr(crypt(newpw1, salt));
E 4
#if     ULTRIX_SHADOW
		if (aux->shadow == sl_local &&
		   (SecurityLevel == sec_u4upgrade ||
		    SecurityLevel == sec_u4enhanced))
D 4
			crypw = crypt16(newpw1, newpw2);
E 4
I 4
			crypw = copystr(crypt16(newpw1, salt));
I 5
#endif
#ifdef	SUN_SHADOW
E 12
I 12
		crypw = copystr((*PasswdCrypt)(newpw1, salt));
D 14
#ifdef	SUN_SECURITY
E 14
I 14
D 16
#if	defined(SUN_SECURITY) && defined(OS_SUNOS_4)
E 16
I 16
#ifdef	HAS_SECURE_RPC
E 16
E 14
E 12
D 15
		update_rpc_key(user, newpw1);
E 15
I 15
		if (SecurityLevel == sec_sunC2)
			update_rpc_key(user, newpw1);
E 15
E 5
E 4
#endif
I 14
D 16
#ifdef	NISPLUS_SUPPORT
E 16
I 16
#ifdef	USE_NISPLUS
E 16
D 15
		update_nis_cred(user, newpw1);
E 15
I 15
		if (aux->sourcePW == srv_nisplus)
			update_nis_cred(user, newpw1);
E 15
#endif
E 14
	}
	/*
E 19
E 2
	 * Stuff the bits back into the password file
	 */
D 11
	if (DebugLevel > DEBUG_PWUPDATE)
E 11
I 11
D 13
	if (DebugLevel >= DB_UPDATE)
E 13
I 13
D 17
	if (DebugLevel >= DB_UPDATE) {
E 13
E 11
		printf("pw_replace(%s, %s, (char *)0, (char *)0)\n",
D 2
			user, pwchanged ? newpw1 : "<null>");
	pw_replace(user, pwchanged ? newpw1 : (char *)0, (char *)0, (char *)0);
E 2
I 2
D 7
			user, pwchanged ? crypw : "<null>");
E 7
I 7
D 11
			user->mpw_name, pwchanged ? crypw : "<null>");
E 7
	pw_replace(user, pwchanged ? crypw : (char *)0, (char *)0, (char *)0);
E 11
I 11
			user->mpw_name, crypw ? crypw : "<null>");
I 13
		fflush(stdout);
	}
E 17
I 17
D 19
	debug(DB_UPDATE, "pw_replace(%s, %s, (char *)0, (char *)0)\n",
		user->mpw_name, crypw ? crypw : "<null>");
E 17
E 13
	pw_replace(user, crypw, (char *)0, (char *)0);
E 19
I 19
	debug(DB_UPDATE, "pw_replace(%s, %s)\n",
		theUser->mpw_name,
		newUser->mpw_passwd ? newUser->mpw_passwd : "<null>");
	pw_replace(theUser, newUser, changes);
E 19
E 11

E 2
D 14
#ifdef	USE_SYSLOG
E 14
D 16
	syslog(MESSAGE_LOG_LEVEL,
E 16
I 16
D 19
	syslog(LOG_INFO,
E 16
		"Password changed on %s for %s by %s\n",
D 18
		user->where, user->mpw_name, caller->mpw_name);
E 18
I 18
		user->pws_loc, user->mpw_name, caller->mpw_name);
E 18
D 14
#endif
E 14
I 14

E 14
D 11
	if (pwchanged)
E 11
I 11
	if (pwchanged) {
E 19
I 19
	/* If pw_replace() failed, this code will not be reached */
	if (changes & CHG_PW) {
E 19
E 11
D 18
		printf("Password changed for %s on %s\n",
			user->mpw_name, user->where);
E 18
I 18
D 37
		printf("%s Password changed for %s on %s\n",
E 37
I 37
		printf("%s password changed for %s on %s\n",
E 37
D 19
			user->pws_name, user->mpw_name, user->pws_loc);
E 18
I 11
		if (update_password_history(&user->pw, crypw))
E 19
I 19
			theUser->pws_name, theUser->mpw_name, theUser->pws_loc);
		syslog(LOG_INFO,
			"Password changed on %s for %s by %s\n",
D 43
			theUser->pws_loc, theUser->mpw_name, theCaller->mpw_name);
I 20
D 29
#ifdef	PASSWORD_HISTORY
E 20
		if (update_password_history(&theUser->pw, newUser->mpw_passwd))
E 19
			warn("Could not update password history database\n");
I 20
#endif
E 29
I 29
D 34
		password_history_update(&theUser->pw, newUser->mpw_passwd);
E 34
I 34
D 35
		password_history_update(theUser->mpw_name, newUser->mpw_passwd);
E 35
I 35
		password_history_update(theUser->mpw_name, newUser->mpw_passwd, 0);
E 43
I 43
			theUser->pws_loc, theUser->mpw_name,
			theCaller->mpw_name);

		if (! in_history(theUser->mpw_name, theUser->mpw_passwd))
			password_history_update(theUser->mpw_name,
				theUser->mpw_passwd, 0);

		password_history_update(theUser->mpw_name,
			newUser->mpw_passwd, 0);
I 44
#ifdef	AUX_PASSWORD_CHANGE
		/* Invoke auxillary password change program here */
#endif
E 44
E 43
E 35
E 34
E 29
E 20
	}
I 44
#ifdef	PWAGE
E 44
E 11
D 19
	else
E 19
I 19
	if (changes & CHG_PWAGE) {
E 19
D 18
		printf("Password aging changed for %s on %s\n",
			 user->mpw_name, user->where);
E 18
I 18
D 37
		printf("%s Password aging changed for %s on %s\n",
E 37
I 37
		printf("%s password aging changed for %s on %s\n",
E 37
D 19
			 user->pws_name, user->mpw_name, user->pws_loc);
E 18
I 4
D 15
#ifdef	YP_PASSWD
E 15
I 15
D 16
#ifdef	YP_SUPPORT
E 15
	yp_sync();		/* Eventually db_sync() */
E 16
I 16
#ifdef	USE_NIS
	yp_sync();
E 16
D 11
#endif
I 8
#ifdef	PASSWORD_HISTORY
D 10
	rc = update_password_history(&user->pw, crypw);
E 10
I 10
	if (update_password_history(&user->pw, crypw))
		warn("Could not update password history database\n");
E 11
E 10
#endif
E 19
I 19
			 theUser->pws_name, theUser->mpw_name, theUser->pws_loc);
		syslog(LOG_INFO,
			"Password aging changed on %s for %s by %s\n",
			theUser->pws_loc, theUser->mpw_name, theCaller->mpw_name);
	}
I 44
#endif
E 44
E 19
E 8
E 4
}

I 26
D 32

E 32
E 26
D 21

E 21
/*
D 33
 *	get_password -- read password and check against current.
 */
I 4
D 7
public /* void */
E 7
I 7
D 19
public void
E 19
I 19
D 20
private void
E 20
I 20
public void
E 20
E 19
E 7
E 4
D 15
get_password(pwd_crypt, pwd_plain, pwlen)
char	*pwd_crypt,		/* Present password (encrypted) */
E 15
I 15
get_password(prompt, pwd_crypt, pwd_plain, pwlen)
D 19
char	*prompt,
	*pwd_crypt,		/* Present password (encrypted) */
E 15
	*pwd_plain;		/* Present password (plain)  */
int	pwlen;			/* Length of present password buffer */
E 19
I 19
D 25
	char	*prompt,
		*pwd_crypt,		/* Present password (encrypted) */
		*pwd_plain;		/* Present password (plain)  */
	int	pwlen;			/* Length of present password buffer */
E 25
I 25
D 26
	const char	*prompt,
			*pwd_crypt;	/* Present password (encrypted) */
	char		*pwd_plain;	/* Present password (plain)  */
	const int	pwlen;		/* Length of present password buffer */
E 26
I 26
	char	*prompt,
		*pwd_crypt;	/* Present password (encrypted) */
	char	*pwd_plain;	/* Present password (plain)  */
	int	pwlen;		/* Length of present password buffer */
E 26
E 25
E 19
{
	int	ntries = 0;	/* Match attempt counter */
	int	doit = 1;
	char	*px;		/* Temp */
I 32
	unsigned int naptime = PasswdMatchWait;	/* Sleep after bad entry */
E 32

	while (doit) {
D 15
		px = getpass(ProgramInput ? "" : "Current password: ");
E 15
I 15
D 19
		px = getpass(ProgramInput ? "" : prompt); 
E 19
I 19
D 26
		px = getpass(XSwitches[Xsw_UseStdin] ? "" : prompt); 
E 19
E 15
		if (px == 0)
			die("EOF during password read.\n");
E 26
I 26
D 30
		if ((px = getpass(prompt)) == NULL)
E 30
I 30
		if ((px = np_getpass(prompt)) == NULL)
E 30
			die("Password unmatched.\n");
E 26
		if (*px == '\0')
			continue;
D 3
		if (!cmp_password(pwd_crypt, px)) {
E 3
I 3
		if (!password_cmp(pwd_crypt, px)) {
E 3
			printf("Password incorrect.\n");
D 6
			if (ntries++ == pwReadTries)
E 6
I 6
D 32
			if (ntries++ == PasswdMatchTries)
E 32
I 32
			if (naptime)
				sleep(naptime);
			if (ntries++ == PasswdMatchTries) {
				if (naptime)
					sleep(naptime);
E 32
E 6
				die("Password not matched.\n");
I 32
			}
E 32
			continue;
		}
		doit = 0;
	}
	(void) strncpy(pwd_plain, px, pwlen);
}

/* 
D 6
 *	randomstring - create a string of random characters
E 6
I 6
 *	random_string - create a string of random characters
E 6
 */
D 6
char	*
E 6
I 6
D 19
public char *
E 19
I 19
private char *
E 19
E 6
random_string(buf, buflen)
D 19
char	*buf;		/* String buffer */
int	buflen;		/* Length of buf */
E 19
I 19
	char	*buf;		/* String buffer */
	int	buflen;		/* Length of buf */
E 19
{
	int	i,		/* Temp */
		n;		/* Temp */
D 6
	time_t	tv;		/* Current time */
E 6
I 6
	unsigned int	tv;	/* Srand seed */
E 6
	char	proto[128];	/* Build buffer */

D 6
	(void) time (&tv);
	/*
	 * Assumes (implicitly) that sizeof(int) == sizeof(long)
	 */
E 6
I 6
	tv = (unsigned int) time((time_t *)0);
E 6
D 14
	(void) srand ( (tv & 0x38d9fcff) ^ getpid ());
E 14
I 14
	(void) srand ( (tv & 0x07201969) ^ getpid ());
E 14
	for (i = 0; i < sizeof(proto); i++) {	/* fill proto vector */
		int	c;		/* Temp */

		for (;;) {
			c = rand() % 0x7f;	/* turn into ASCII */
			if (isalnum(c))
				break;
		}
		proto[i] = (char )c;
	}
D 6
	(void) srand(((unsigned )tv & 0x1a90fefc) ^ getpid());
E 6
I 6
D 14
	(void) srand((tv & 0x1a90fefc) ^ getpid());
E 14
I 14
	(void) srand((tv & 0x11201972) ^ getpid());
E 14
E 6
	for (i = 0; i < buflen; i++) {
D 32
		n = rand() % sizeof(proto);
E 32
I 32
		n = rand() % sizeof proto;
E 32
		buf[i] = proto[n];
	}
	buf[buflen] = 0;
	return(buf);
}

D 16
#if	defined(SYS5_TTY)
#	include <termio.h>		/* Vanilla SV termio */
	struct termio saved_tty_mode;
#endif
E 16

D 16
#if	defined(SUNOS_TTY)
#	include <sys/termios.h>		/* SUN OS 4.0 termio */
#define	TCGETA	TCGETS
#define	TCSETA	TCSETS
	struct termios saved_tty_mode;
#endif

#if	!defined(SUNOS_TTY) && !defined(SYS5_TTY)
#	include <sgtty.h>		/* BSD tty */
	struct sgttyb saved_tty_mode;
	int	saved_local_flags;
#endif
char	saves_valid  = 0;		/* Are the saved values valid? */

E 16
/*
D 16
 *	savetty - save current terminal settings
 */
savetty()
{
#if	defined(SYS5_TTY) || defined(SUNOS_TTY)
	(void) ioctl(0, TCGETA, &saved_tty_mode);
#else
	(void) ioctl(0, TIOCGETP, &saved_tty_mode);
	(void) ioctl(0, TIOCLGET, &saved_local_flags);
#endif
	saves_valid++;
}

/*
 *	fixtty - restore saved terminal settings
 */
fixtty()
{
	if (saves_valid) {
#if	defined(SYS5_TTY) || defined(SUNOS_TTY)
		(void) ioctl(0, TCSETA, &saved_tty_mode);
#else
		(void) ioctl(0, TIOCSETP, &saved_tty_mode);
		(void) ioctl(0, TIOCLSET, &saved_local_flags);
#endif
	}
}

#ifdef	NEED_GETPASS
/*
 *	The system getpass() throws away all but the first 8 characters
 *	of a password string.  If this isn't enough for you, use this
 *	routine instead.  This code assumes that stdin is the terminal.
 */
D 6
char	*
E 6
I 6
public char	*
E 6
getpass(prompt)
I 9
#ifdef	__STDC__
const char	*prompt;
#else
E 9
D 7
char	*prompt;
E 7
I 7
D 8
CONST char	*prompt;
E 8
I 8
char	*prompt;
I 9
#endif
E 9
E 8
E 7
{
#if	defined(SYS5_TTY)
	struct termio	saved,		/* Saved tty characteristics */
			noecho;		/* No-echo tty characteristics */
	char	*strchr();
#else
#if	defined(SUNOS_TTY)
	struct termios	saved,		/* Saved tty characteristics */
			noecho;		/* No-echo tty characteristics */
#else
	struct sgttyb	saved,		/* Saved tty characteristics */
			noecho;		/* No-echo tty characteristics */
#endif	/* defined(SUNOS_TTY) */
#endif	/* defined(SYS5_TTY) */
	static char	ib[64];		/* Input buffer */
	char	*rc;			/* Temp */

#if	defined(SYS5_TTY) || defined(SUNOS_TTY)
	(void) ioctl(0, TCGETA, &saved);
	noecho = saved;
	noecho.c_lflag &= ~ECHO;
	(void) ioctl(0, TCSETA, &noecho);
#else
	(void) ioctl(0, TIOCGETP, &saved);
	noecho = saved;
	noecho.sg_flags &= ~ECHO;
	(void) ioctl(0, TIOCSETP, &noecho);
#endif
	fprintf(stderr, "%s", prompt);
	fflush(stderr);
	rc = fgets(ib, sizeof(ib), stdin);
	putc('\n', stderr);
	fflush(stderr);

#if	defined(SYS5_TTY) || defined(SUNOS_TTY)
	(void) ioctl(0, TCSETA, &saved);
#else
	(void) ioctl(0, TIOCSETP, &saved);
#endif
	if (rc == NULL)
		return(NULL);
D 14
	if (rc = index(ib, '\n'))
E 14
I 14
	if (rc = INDEX(ib, '\n'))
E 14
		*rc = 0;
	return(ib);
}
#endif	/* XGETPASS */

/*
E 16
D 3
 *	cmp_password - compare old and new passwords
E 3
I 3
 *	password_cmp - compare old and new passwords
E 3
 *
 *	Returns 1 if check = new, 0 if not
 */
I 19
private 
E 19
D 3
cmp_password(current, check)
E 3
I 3
password_cmp(current, check)
E 3
D 7
char	*current,
	*check;
E 7
I 7
D 8
CONST char	*current,
E 8
I 8
D 12
 char	*current,
E 8
		*check;
E 12
I 12
D 19
char	*current,
	*check;
E 19
I 19
D 23
	char	*current,
		*check;
E 23
I 23
D 26
	const char	*current,
			*check;
E 26
I 26
	char	*current,
		*check;
E 26
E 23
E 19
E 12
E 7
{
	if (!*current)
		return(1);
D 12
#if	ULTRIX_SECURITY
D 2
	/* Check for  UPGRADE or ENHANCED security mode */
E 2
	if (strlen(current) > STD_PW_LEN)
		return(strcmp(current, crypt16(check, current)) == 0);
	else
#endif
		return(strcmp(current, crypt(check, current)) == 0);
E 12
I 12

D 19
	return (strcmp(current, (*PasswdCrypt)(check, current)) == 0);
E 19
I 19
D 20
	return (strcmp(current, (*svc_PasswdCrypt)(check, current)) == 0);
E 20
I 20
	return (strcmp(current, (*svc.PasswdCrypt)(check, current)) == 0);
E 20
E 19
E 12
}
I 2

/*
E 33
D 3
 *      password_ok - sanity check password.  Right now just calls
 *              the password check code
E 3
I 3
D 34
 *      password_ok - sanity check password.
E 3
 *
D 3
 *      Returns 1 if password is ok to use, 0 otherwise
E 3
I 3
 *      Returns result code from checkpassword().
E 3
 */
D 3
password_ok(theUser, newpwd, mesgbuf)
E 3
I 3
D 19
static int password_ok(theUser, newpwd, mesgbuf)
E 3
struct mpasswd	*theUser;
char		*newpwd,		/* New password (plaintext) */
		*mesgbuf;		/* Error message buffer */
E 19
I 19
private
D 32
password_ok(theUser, newpwd, mesgbuf)
E 32
I 32
password_ok(theUser, newpwd, mesgbuf, mesglen)
E 32
	struct mpasswd	*theUser;
	char		*newpwd,		/* New password (plaintext) */
			*mesgbuf;		/* Error message buffer */
I 32
	unsigned int	mesglen;		/* Length of message buffer */
E 32
E 19
{
I 6
D 10
#if	0	/* XXX */
E 6
D 8
	int	rc = checkpassword(&theUser->pw, newpwd, mesgbuf);
E 8
I 8
	return(checkpassword(&theUser->pw, newpwd, mesgbuf));
E 8
I 6
#else
	return(1);
#endif
E 10
I 10
D 32
	int	rc = checkpassword(newpwd, &theUser->pw, mesgbuf);
E 32
I 32
	int	rc = checkpassword(newpwd, &theUser->pw, mesgbuf, mesglen);
E 32
D 21
	return (rc == 0);
E 21
I 21
	return (rc == PWCK_OK);
E 21
E 10
E 6
D 8

#ifdef	PASSWORD_HISTORY
	if (rc)
		return(rc);
	/* Call password history checker to prevent password reuse */
	rc = passwd_history(&theUser->pw, newpwd, mesgbuf);
#endif
D 6
	return(rc);
E 6
I 6
/* 	return(rc); */	/* XXX */
E 8
E 6
}

I 3
/*
E 34
 *	can_change - check password change permission
 *
 *	Returns 1 if password can be changed
 *		0 if not
 */
D 4
static int can_change(theUser, theCaller)
E 4
I 4
D 19
enum chg_perm can_change(theUser, theCaller)
E 4
struct mpasswd	*theUser,
		*theCaller;
E 19
I 19
private enum chg_perm
can_change_pw(theUser, theCaller)
	struct mpasswd	*theUser,
			*theCaller;
E 19
{
D 16
	uid_t	calluid = getuid();
E 16
I 16
D 26
	Uid_t	calluid = getuid();
E 16

E 26
D 14
#ifdef	YP_PASSWD
E 14
I 14
D 16
#ifdef	YP_SUPPORT
E 16
I 16
#ifdef	USE_NIS
E 16
E 14
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
D 15
	 *
	 * The "ALWAYS_USE_YPPASSWDD" option runs smack into this same
	 * problem, which is one of the reasons that I don't recommend it.
E 15
	 */
	{
D 4
		struct ypinfo *ypi = ypwhich(PASSWD_BYNAME);
E 4
I 4
		struct ypinfo ypinfo;
E 4

I 4
		ypwhich(PASSWD_BYNAME, &ypinfo);
E 4
D 26
		if (calluid == 0 &&
E 26
I 26
D 44
		if (CallerUid == 0 &&
E 26
D 4
		    ypi->status == is_yp_client &&
E 4
I 4
		    ypinfo.status == is_yp_client &&
I 42
		    XSwitches[Xsw_AskAll] == 0 &&
E 42
E 4
D 18
		    theUser->remote) {
E 18
I 18
		    theUser->pws_remote) {
E 44
I 44
		if (CallerUid == 0 &&			/* Caller is root */
		    ypinfo.status == is_yp_client &&	/* On NIS client */
		    XSwitches[Xsw_AskAlways] == 0 &&	/* ! -XA option */
		    theUser->pws_remote) {		/* Passwd not local */
E 44
E 18
			printf("Information can only be changed on NIS master %s.\n",
D 4
				ypi->master);
			return(0);
E 4
I 4
				ypinfo.master);
			return(deny);
E 4
		}
	}
D 31
#endif
E 31
I 31
#endif	/* USE_NIS */

E 31
D 26
	if (calluid == 0)		/* Su can change any passwd */
E 26
I 26
	if (CallerUid == 0)		/* Su can change any passwd */
E 26
D 4
		return(1);
E 4
I 4
		return(other);
E 4

	if (strcmp(theCaller->mpw_name, theUser->mpw_name))
D 4
		return(0);		/* I'm not root and target isn't me */
E 4
I 4
		return(deny);		/* I'm not root and target isn't me */
E 4

D 12
#ifdef	S5_PWAGING
E 12
	/*
 	 * Check password age
	 */
D 12
	if (theUser->mpw_age) {
		time_t	pwage = 0,
			maxpwtime = 0,
			minpwtime = 0,
			now;
		extern long a64l();
E 12
I 12
D 14
	if (theUser->age_password) {
E 14
I 14
D 18
	if (theUser->pwage.doit) {
E 18
I 18
D 19
	if (theUser->pwage.do_aging) {
E 19
I 19
	if (theUser->mpw_age) {
E 19
E 18
E 14
		time_t	now;
E 12

D 12
		pwage = a64l(theUser->mpw_age);
		maxpwtime = pwage & 077;
		minpwtime = (pwage >> 6) & 077;
		pwage >>= 12;
E 12
		(void) time(&now);
D 12
		now /= SEC_PER_WEEK;
		if (pwage <= now) {
			if (calluid && (now < (pwage + minpwtime))) {
				printf("Less than %ld weeks since last change.\n",
				     minpwtime);
E 12
I 12
D 14
		if (theUser->last_change <= now && calluid) {
			if (now < (theUser->last_change + theUser->min_change_time)) {
E 14
I 14
D 26
		if (theUser->pwage.last_change <= now && calluid) {
E 26
I 26
		if (theUser->pwage.last_change <= now && CallerUid) {
I 44

			debug(DB_UPDATE,
				"can_change_pw: Age check last=%d can=%d\n",
				theUser->pwage.last_change,
				theUser->pwage.can_change
			);

E 44
E 26
D 18
			if (now < (theUser->pwage.last_change + theUser->pwage.min_time)) {
E 18
I 18
			if (now < (theUser->pwage.last_change + theUser->pwage.can_change)) {
E 18
E 14
				printf("You may not change your password for %d more days.\n",
D 14
				(theUser->last_change +
				 theUser->min_change_time - now) / SEC_PER_DAY);
E 14
I 14
				(theUser->pwage.last_change +
D 18
				 theUser->pwage.min_time - now) / SEC_PER_DAY);
E 18
I 18
D 19
				 theUser->pwage.can_change - now) / SEC_PER_DAY);
E 19
I 19
				 theUser->pwage.can_change - now) / SEC_DAY);
E 19
E 18
E 14
E 12
D 4
				return(0);
E 4
I 4
				return(deny);
E 4
			}
D 12
			if (calluid && (minpwtime > maxpwtime)) {
				printf("You may not change this password.\n");
E 12
I 12
D 14
			if (theUser->min_change_time > theUser->expire) {
E 14
I 14
D 18
			if (theUser->pwage.min_time > theUser->pwage.max_time) {
E 18
I 18
			if (theUser->pwage.can_change > theUser->pwage.must_change) {
E 18
E 14
				printf("You may not change your password.\n");
E 12
D 4
				return(0);
E 4
I 4
				return(deny);
E 4
			}
		}
	}
D 12
#endif

#ifdef	ULTRIX_SHADOW
E 12
I 12
D 16
#ifdef	ULTRIX_SECURITY
E 16
I 16
D 39
#ifdef	ULTRIX_AUTH
I 32
D 38
	debug(DB_LOOKUP,"svc.SecurityLevel (Ultrix)= %d\n",svc.SecurityLevel);
E 38
I 38
	debug(DB_LOOKUP,"svc->SecurityLevel (Ultrix)= %d\n",svc->SecurityLevel);
E 39
E 38
E 32
E 16
E 12
	/*
D 12
	 * Check the authorization data for password aging
	 * and change permissions.
E 12
I 12
D 39
	 * Check the authorization data for password change permission.
E 39
I 39
	 * Call the method auth check routine
E 39
E 12
	 */
D 23
	if ((SecurityLevel == sec_u4enhanced) ||
E 23
I 23
D 38
	if ((svc.SecurityLevel == sec_u4enhanced) ||
E 38
I 38
D 39
	if ((svc->SecurityLevel == sec_u4enhanced) ||
E 38
E 23
	    (SecurityLevel == sec_u4upgrade &&
D 31
	     strcmp(theUser->mpw_passwd, "*") == 0)) {
E 31
I 31
	     strcmp(theUser->mpw_opasswd, "*") == 0)) {
E 31
		AUTHORIZATION	*a;
E 39
I 39
	if (check_auth(theUser) == deny)
		return(deny);
E 39
D 12
		TIME	now;
E 12

D 12
		if ((a = getauthuid(theUser->mpw_uid)) == 0)
E 12
I 12
D 39
		if ((a = getauthuid(theUser->mpw_uid)) == NULL)
E 12
D 24
			logdie("Cannot get auth data.");
E 24
I 24
			logdie("Cannot get auth data.\n");
E 24
		/*
		 * Can the user change their password?
		 */
D 26
		if (calluid == theUser->mpw_uid &&
E 26
I 26
		if (CallerUid == theUser->mpw_uid &&
E 26
		   !(a->a_authmask & A_CHANGE_PASSWORD)) {
			printf("Permission denied.\n");
D 4
			return(0);
E 4
I 4
			return(deny);
E 4
		}
		/*
		 * Can the user specify their own password?
		 */
D 26
		if (calluid == theUser->mpw_uid &&
E 26
I 26
		if (CallerUid == theUser->mpw_uid &&
E 26
		   !(a->a_authmask & A_ENTER_PASSWORD)) {
I 12
D 15
			Punt();
E 15
E 12
			printf("You must use a system-generated password.\n");
I 15
D 34
			punt("-a");
E 34
E 15
D 12
			/* Of course, I can't make one of those ...
			 * so you are pretty much up the creek right now
			 */
E 12
D 4
			return(0);
E 4
I 4
			return(deny);
E 4
		}
D 12
		/*
		 * Now check password age
		 */
		(void) time(&now);
		if (a->a_pass_mod) {
			if ((now - a->a_pass_mod) < a->a_pw_minexp) {
				printf("Password was changed too recently.\n");
D 4
				return(0);
E 4
I 4
				return(deny);
E 4
			}
E 12
I 12
	}
D 16
#endif	/* ULTRIX_SECURITY */
#ifdef	OSF1_SECURITY
E 16
I 16
#endif
D 32
#ifdef	OSF1_AUTH
E 32
I 32
#if	defined(OSF1_AUTH) || defined(HPUX_AUTH)
E 39
E 32
E 16
	/*
D 39
	 * Check the authorization data for password change permission.
	 */
I 32
#ifdef	HPUX_AUTH
D 38
	debug(DB_LOOKUP,"svc.SecurityLevel (HPUX) = %d\n", svc.SecurityLevel);
	if (svc.SecurityLevel == sec_HPtrusted) {
E 38
I 38
	debug(DB_LOOKUP,"svc->SecurityLevel (HPUX) = %d\n", svc->SecurityLevel);
	if (svc->SecurityLevel == sec_HPtrusted) {
E 38
#endif
#ifdef	OSF1_AUTH
D 38
	debug(DB_LOOKUP,"svc.SecurityLevel (OSF)= %d\n", svc.SecurityLevel);
E 32
D 23
	if (SecurityLevel == sec_OSFenhanced) {
E 23
I 23
	if (svc.SecurityLevel == sec_OSFenhanced) {
E 38
I 38
	debug(DB_LOOKUP,"svc->SecurityLevel (OSF)= %d\n", svc->SecurityLevel);
	if (svc->SecurityLevel == sec_OSFenhanced) {
E 38
E 23
D 32
		struct pr_passwd *pw = getprpwnam(theUser->mpw_name);
E 32
I 32
#endif
		struct pr_passwd *pw =
			(struct pr_passwd *)getprpwnam(theUser->mpw_name);
E 32
		int	pick = 1;

		if (pw == NULL)
D 19
			logdie("Cannot get auth data.");
E 19
I 19
			logdie("Cannot get auth data for %s\n",
D 32
				theUser->mpw_name);
E 32
I 32
     				theUser->mpw_name);
E 32
E 19
		if (pw->sflg.fg_pick_pwd) pick = pw->sfld.fd_pick_pwd;
		if (pw->uflg.fg_pick_pwd) pick = pw->ufld.fd_pick_pwd;
		if (!pick) {
D 15
			Punt();
E 15
			printf("You must use a system-generated password.\n");
I 15
D 34
			punt("-a");
E 34
I 34
			printf("The system administrator must use dxchpwd to do this.\n");
E 34
E 15
			return(deny);
E 12
		}
I 6
	}
E 6
#endif
I 32

E 32
I 31
#ifdef	AIX_AUTH
        /*
         * Check the AIX auth datbase for password flags
         */
I 32
D 38
	debug(DB_LOOKUP,"svc.SecurityLevel (AIX)= %d\n",svc.SecurityLevel);
E 38
I 38
	debug(DB_LOOKUP,"svc->SecurityLevel (AIX)= %d\n",svc->SecurityLevel);
E 38
E 32
        if (strcmp(theUser->mpw_opasswd, "!") == 0) {
                struct userpw   *upw;

                if (setpwdb(S_READ))
                        logdie("Permission for auth DB access denied.");

                upw = getuserpw(theUser->mpw_name);
                endpwdb();
                if (!upw)
                        logdie("Cannot get password for user %s from auth DB.",
                                theUser->mpw_name);
		if ((upw->upw_flags & PW_ADMIN) && CallerUid)
			die("Password must be changed by root.");
        }
#endif
E 31
	/*
E 39
	 * Other checks can be put here to determine if the invoker should
	 * be allowed to change this password.
	 */
	return(pw_permission(theUser, theCaller));
}
E 3
E 2
D 12
/*		End %M%		*/
E 12
I 12

D 15
Punt()
E 15
I 15
D 34
/*
 * punt - execute standard passwd program to do thing that we don't do.
 */
private void
punt(options)
D 19
	char	*options;
E 19
I 19
D 25
	char	*options;		/* USE VARARGS */
E 25
I 25
D 26
	const char	*options;		/* USE VARARGS */
E 26
I 26
	char	*options;		/* USE VARARGS */
E 26
E 25
E 19
E 15
{
D 15
	/* Here we will find the vendor passwd program and run it */
	/* If this succeeds, then this routine will not return */
E 15
I 15
#if	0
	if (!vendor_passwd)
		return;
	if (access(vendor_passwd, 1) < 0)
		return;
D 19
	execl(vendor_passwd, "passwd", options, xxx, 0);
E 19
I 19
	(void) setgid(getgid());
D 26
	(void) setuid(getuid());
E 26
I 26
	(void) setuid(CallerUid);
E 26
	(void) execl(vendor_passwd, "passwd", options, xxx, 0);
E 19
#endif
E 15
}
I 16

E 34
D 33
/*
 * Terminal handling code.
 *
 * The following methods are supported:
 *	termios via POSIX tc[gs]attr() routines
 *	termios via TCGETS/TCSETS
 *	termio via TCGETA/TCSETA
 *	V7 sgtty
 *
 * Configure will set only *one* of the symbols used,  so that
 * termios takes precedence over termio which suprecedes sgtty..
 *
 * This is a bloody damn mess - probably the next revision
 * will toss most of these options and only support termios
E 33
I 33
/* 
 *	random_string - create a string of random characters
E 33
 */
D 33
#ifdef	I_TERMIOS
/*
 * Has TERMIOS
 */
# include <termios.h>
static struct termios saved_tty_mode;
# define	TTY_SAVE	termios
# define	ECHO_OFF(_b_)		_b_.c_lflag =~ ECHO
# define	ECHO_ON(_b_)		_b_.c_lflag =| ECHO
# ifdef	HAS_POSIX_TTY
#  define	GET_TTY(_fd_, _b_)	tcgetattr(_fd_, (_b_))
#  define	SET_TTY(_fd_, _b_)	tcsetattr(_fd_, TCSANOW, (_b_))
# else
#  define	GET_TTY(_fd_, _b_)	ioctl(_fd_, TCGETS, (_b_))
#  define	SET_TTY(_fd_, _b_)	ioctl(_fd_, TCSETS, (_b_))
# endif	/* HAS_POSIX_TTY */
#endif	/* I_TERMIOS */

#if	(defined(I_TERMIO) && !defined(GET_TTY))
/*
 * Has TERMIO
 */
#include <sys/termio.h>		/* SUN OS 4.0 termio */
static struct termio saved_tty_mode;
# define	TTY_SAVE	termio
# define	ECHO_OFF(_b_)		_b_.c_lflag =~ ECHO
# define	ECHO_ON(_b_)		_b_.c_lflag =| ECHO
# define	GET_TTY(_fd_, _b_)	ioctl(_fd_, TCGETA, (_b_))
# define	SET_TTY(_fd_, _b_)	ioctl(_fd_, TCSETA, (_b_))
#endif	/* I_TERMIO */

/*
 * Neither TERMIOS or TERMIO - use BSD sgtty
 */
#if	(defined(I_SGTTY) && !defined(GET_TTY))
# include <sgtty.h>		/* BSD tty */
# define	TTY_SAVE	sgttyb
# define	ECHO_OFF(_b_)		_b_.sg_flags =~ ECHO
# define	ECHO_ON(_b_)		_b_.sg_flags =| ECHO
# define	GET_TTY(_fd_, _b_)	ioctl(_fd_, TIOCGETP, (_b_))
# define	SET_TTY(_fd_, _b_)	ioctl(_fd_, TIOCSETP, (_b_))
#endif	/* I_SGTTY */

#ifndef	GET_TTY
I 19
D 27
# ifdef _STDC_
#	error Cannot figure out how to do tty stuff
# endif
E 27
I 27
/* # ifdef _STDC_ */
/* #	error Cannot figure out how to do tty stuff */
/* # endif */
E 27
E 19
	ERROR Cannot figure out how to do tty stuff
#endif

static struct {
	char		valid;
	struct TTY_SAVE mode;
} tty_save = { 0 };

/*
D 26
 *	savetty - save current terminal settings
E 26
I 26
 * savetty
 *	Save terminal settings
 * Usage:
 *	savetty();
 * Effects:
 *	Stores terminal mode in the "tty_save" structure for
 *	restoration by fixtty()
E 26
 */
public void
savetty()
E 33
I 33
private char *
random_string(buf, buflen)
	char	*buf;		/* String buffer */
	int	buflen;		/* Length of buf */
E 33
{
D 33
	(void) GET_TTY(0, &tty_save.mode);
	tty_save.valid++;
}
E 33
I 33
	int	i,		/* Temp */
		n;		/* Temp */
	unsigned int	tv;	/* Srand seed */
	char	proto[128];	/* Build buffer */
E 33

I 39
	buflen--;		/* Avoid overflowing <buf> */
E 39
D 33
/*
D 26
 *	fixtty - restore saved terminal settings
E 26
I 26
 * fixtty
 *	Restore saved terminal settings
 * Usage:
 *	fixtty()
 * Effects:
 *	Changes terminal settings from the "tty_save" structure
 *	if that data is valid
E 26
 */
public void
fixtty()
{
	if (tty_save.valid)
		(void) SET_TTY(0, &tty_save.mode);
}
E 33
I 33
	tv = (unsigned int) time((time_t *)0);
	(void) srand ( (tv & 0x07201969) ^ getpid ());
	for (i = 0; i < sizeof(proto); i++) {	/* fill proto vector */
		int	c;		/* Temp */
E 33

D 26
#ifdef	NEED_GETPASS
E 26
D 33
/*
D 26
 *	The system getpass() throws away all but the first 8 characters
 *	of a password string.  If this isn't enough for you, use this
 *	routine instead.  This code assumes that stdin is the terminal.
E 26
I 26
D 30
 * getpass
E 30
I 30
 * np_getpass
E 30
 *	Replacement for libc getpass(3)
 * Usage:
D 30
 *	pass = getpass(prompt);
E 30
I 30
 *	pass = np_getpass(prompt);
E 30
 * Returns:
 *	Password string
 *	NULL if EOF encountered or error
 * Comments:
 *	This routine is used instead of getpass(3):
E 26
 *
D 26
 *	This is different from the libc getpass() which reads from /dev/tty!
 *	If the "read from stdin" option is enabled, then this code
 *	is needed instead of the libc version.
E 26
I 26
 *	1. The system getpass() throws away all but the first 8 characters
 *	   of a password string.  On some systems passwords can be longer
 *	   than 8, but getpass(3) hasn't caught up yet.
 *
 *	2. getpass(3) returns a empty string if the user input was empty
 *	   (blank line), or the /dev/tty read got an EOF or error.
 *	   There *is* a difference between those conditions and I really
 *	   want to know it and behave accordingly.  Why make a user
 *	   start over again if they hit RETURN one time too many?
 *
 *	3. The SunOS 4 getpass(3) returns an empty string if the user
 *	   sent a SIGNIT (control-c).  This is stupid behavior.
 *
 *	This code assumes that stdin is the terminal (which has been
 *	verified upstream), so /dev/tty is NOT used.
 *	Signals are caught and terminal modes reset upstream.
E 26
 */
public char	*
D 30
getpass(prompt)
E 30
I 30
np_getpass(prompt)
E 30
D 26
const char	*prompt;
E 26
I 26
char	*prompt;
E 26
{
	struct TTY_SAVE	saved,
			noecho;
	static char	ib[64];		/* Input buffer */
D 26
	char	*rc;			/* Temp */
E 26
I 26
	int	nr;
E 26

D 26
	(void) GET_TTY(0, &saved);
	noecho = saved;
	ECHO_OFF(noecho);
	(void) SET_TTY(0, &noecho);
	fprintf(stderr, "%s", prompt);
	fflush(stderr);
	rc = fgets(ib, sizeof(ib), stdin);
	putc('\n', stderr);
	fflush(stderr);
	SET_TTY(0, &saved);
	if (rc == NULL)
E 26
I 26
	if (!XSwitches[Xsw_UseStdin]) {
		(void) GET_TTY(0, &saved);
		noecho = saved;
		ECHO_OFF(noecho);
		(void) write(2, prompt, strlen(prompt));
		(void) SET_TTY(0, &noecho);
E 33
I 33
		for (;;) {
			c = rand() % 0x7f;	/* turn into ASCII */
			if (isalnum(c))
				break;
		}
		proto[i] = (char )c;
E 33
	}
D 33
	ib[0] = 0;
	nr = read(0, ib, sizeof(ib));
	if (!XSwitches[Xsw_UseStdin])
		SET_TTY(0, &saved);
	(void) write(2, "\n", 1);
	if (nr <= 0)		/* EOF or error */
E 26
		return(NULL);
D 19
	if (rc = index(ib, '\n'))
		*rc = 0;
E 19
I 19
	chop_nl(ib);
E 19
	return(ib);
E 33
I 33
	(void) srand((tv & 0x11201972) ^ getpid());
	for (i = 0; i < buflen; i++) {
		n = rand() % sizeof proto;
		buf[i] = proto[n];
	}
	buf[buflen] = 0;
	return(buf);
E 33
}
I 33

E 33
D 26
#endif	/* NEED_GETPASS */

E 26
E 16
/* End %M% */
E 12
E 1
