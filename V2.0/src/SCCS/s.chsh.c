h33518
s 00044/00000/00191
d D 1.13 98/06/23 11:12:58 clyde 13 12
c Add copyright notice
e
s 00012/00014/00179
d D 1.12 98/04/28 16:50:28 clyde 12 11
c 1. Change name of help & motd file
c 2. Replace SHELL_NAME_SIZE with BUFSIZ
e
s 00001/00001/00192
d D 1.11 97/05/05 10:35:02 clyde 11 10
c Change missing help file message
e
s 00007/00007/00186
d D 1.10 96/08/29 13:05:00 clyde 10 9
c Remove 'const' declarations (too much compiler pain)
e
s 00051/00018/00142
d D 1.9 96/08/15 11:01:53 clyde 9 8
c 1. Fix use of const
c 2. Use getusershell() if available
e
s 00007/00007/00153
d D 1.8 96/08/13 17:54:52 clyde 8 7
c Change configuration variable names
e
s 00001/00001/00159
d D 1.7 96/08/09 16:17:19 clyde 7 6
c Beta 3 development checkin 2
e
s 00068/00086/00092
d D 1.6 96/08/06 14:14:11 clyde 6 5
c beta 3 cycle 1 checkin
e
s 00002/00002/00176
d D 1.5 96/04/03 14:46:36 clyde 5 4
c Reflect new mpasswd structure element names
e
s 00004/00011/00174
d D 1.4 95/04/05 16:20:11 clyde 4 3
c Beta 3 development checkin
e
s 00001/00001/00184
d D 1.3 94/10/24 10:36:37 clyde 3 2
c Change YP_PASSWD to YP_SUPPORT
e
s 00001/00002/00184
d D 1.2 94/09/28 16:13:03 clyde 2 1
c Change include file used
e
s 00186/00000/00000
d D 1.1 94/07/28 15:58:12 clyde 1 0
c date and time created 94/07/28 15:58:12 by clyde
e
u
U
f e 0
t
T
I 1
/*
I 13
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
E 13
 *	This program duplicates the manual page behavior of the 4.XBSD
 *	chsh(1) command.
 */
#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu) %P%";
#endif

#include "npasswd.h"
D 2
#include "pw_defs.h"
#include "pw_nis.h"
E 2
I 2
D 7
#include "pwm_defs.h"
E 7
I 7
#include "Methods/pwm_defs.h"
E 7
E 2

D 4
#include TIME_H

E 4
D 6
#ifdef __STDC__
private enum chg_perm can_change_shell(struct mpasswd *, struct mpasswd *);
private int shell_ok(char *);
#else
private enum chg_perm can_change_shell();
private int shell_ok();
#endif
E 6
I 6
D 9
private enum chg_perm can_change_shell _((struct mpasswd *, struct mpasswd *));
private int shell_ok _((char *));
E 9
I 9
D 10
private enum chg_perm can_change_shell _((const struct mpasswd *, const struct mpasswd *));
private int shell_ok _((const char *));
E 10
I 10
private enum chg_perm can_change_shell _((struct mpasswd *, struct mpasswd *));
private int shell_ok _((char *));
E 10
E 9
E 6

D 6

#ifndef CHSH_HELP
# define	CHSH_HELP	"/usr/adm/chsh.help"
#endif

#ifndef CHSH_MOTD
# define	CHSH_MOTD	"/usr/adm/chsh.motd"
#endif

#ifndef CHSH_SHELLS
# define	CHSH_SHELLS	"/etc/shells"
#endif

E 6
D 12
#ifndef SHELL_NAME_SIZE
# define SHELL_NAME_SIZE 80
#endif
E 12
I 12
Config_Value char	*Chsh_Help = CHSH_HELP,
			*Chsh_Motd = CHSH_MOTD,
			*Chsh_Shells = SHELLS_FILE;
E 12

D 6
public char	chsh_help[MAXPATHLEN] = { CHSH_HELP },
		chsh_motd[MAXPATHLEN] = { CHSH_MOTD },
		chsh_shells[MAXPATHLEN] = { CHSH_SHELLS };
E 6
I 6
D 8
Config_Value char	*chsh_help = CHSH_HELP,
			*chsh_motd = CHSH_MOTD,
			*chsh_shells = SHELLS_FILE;
E 8
I 8
D 12
Config_Value char	*ChshHelpFile = CHSH_HELP,
			*ChshMotdFile = CHSH_MOTD,
			*ChshShellList = SHELLS_FILE;
E 8
E 6

E 12
D 6
public void chsh(user, caller)
struct mpasswd	*user,
		*caller;
E 6
I 6
D 9
private char *default_shells[] = {
	"/bin/sh",
	"/bin/csh",
	0
};

E 9
/*
 * chsh - Shell change module
 */
public void chsh(theUser, theCaller)
	struct mpasswd	*theUser,
			*theCaller;
E 6
{
D 6
	char	*sx;
E 6
D 12
	char	newShell[SHELL_NAME_SIZE];
E 12
I 12
	char	newShell[BUFSIZ];
E 12
	enum	chg_perm	perm;
D 6
	
	if ((perm = can_change_shell (user, caller)) == deny)
E 6
I 6
	struct mpasswd	*newUser;

	if ((perm = can_change_shell (theUser, theCaller)) == deny)
E 6
		die("Permission denied.\n");
D 6
	
E 6
I 6

#ifdef  USE_NIS
	yp_password(theUser);
#endif
D 9

E 9
E 6
D 8
	motd(chsh_motd, (char *)0);
E 8
I 8
D 12
	motd(ChshMotdFile, (char *)0);
E 12
I 12
	motd(Chsh_Motd, (char *)0);
E 12
E 8
D 6
	
	if (!ProgramInput) {
		fprintf(stderr,
			"Changing shell for %s on %s\n", 
D 5
			user->mpw_name, user->where);
E 5
I 5
			user->mpw_name, user->pws_loc);
E 5
		fflush(stderr);
	}
E 6

D 6
	if (perm == self && !shell_ok (user->mpw_shell)) {
		fprintf(stderr, "Cannot change from restricted shell %s.\n", 
			 user->mpw_shell);
		fflush(stderr);
E 6
I 6
	if (perm == self && !shell_ok (theUser->mpw_shell)) {
		printf("Cannot change from restricted shell %s.\n", 
			 theUser->mpw_shell);
E 6
		return;
	}

D 6
	for ( ;; ) {
		if (!ProgramInput) {
			fprintf(stderr, "Old shell: %s\n", user->mpw_shell);
			fprintf(stderr, "New shell (? for help): ");
			fflush(stderr);
		}
		sx = fgets(newShell, SHELL_NAME_SIZE, stdin);
E 6
I 6
	printf("Changing shell for %s on %s\n", 
		theUser->mpw_name, theUser->pws_loc);
E 6

D 6
		if (sx == NULL) {
E 6
I 6
	for (;;) {
		if (!XSwitches[Xsw_UseStdin]) {
			printf("Old shell: %s\n", theUser->mpw_shell);
			printf("New shell (? for help): ");
		}
D 12
		if (fgets(newShell, SHELL_NAME_SIZE, stdin) == NULL) {
E 12
I 12
		if (fgets(newShell, BUFSIZ, stdin) == NULL) {
E 12
E 6
			if (feof(stdin)) {
D 6
				fprintf(stderr, "\nLogin shell unchanged\n");
				fflush(stderr);
E 6
I 6
				printf("\nShell unchanged\n");
E 6
				return;
			}
			else {
				die ("Error while reading stdin\n");
			}
		}
D 4
		if (sx = INDEX(newShell, '\n'))
E 4
I 4
D 6
		if (sx = index(newShell, '\n'))
E 4
			*sx = '\0';
E 6
I 6
		chop_nl(newShell);
E 6
		if (strcmp(newShell, "?") == 0) {
D 8
			motd(chsh_help, "Missing help file");
E 8
I 8
D 11
			motd(ChshHelpFile, "Missing help file");
E 11
I 11
D 12
			motd(ChshHelpFile, "Sorry, there is no help.\n");
E 12
I 12
			motd(Chsh_Help, "Sorry, there is no help.\n");
E 12
E 11
E 8
			continue;
		}
		break;
	}
	
D 6
	if (*newShell == '\0' || strcmp(user->mpw_shell, newShell) == 0) {
		fprintf(stderr, "Login shell unchanged\n");
		fflush(stderr);
E 6
I 6
	if (*newShell == '\0' || strcmp(theUser->mpw_shell, newShell) == 0) {
		printf("Login shell unchanged\n");
E 6
		return;
	}

	if (!shell_ok(newShell)) {
D 6
		fprintf(stderr, "%s is unacceptable as a new shell.\n",
			newShell);
		fflush(stderr);
E 6
I 6
		printf("%s is unacceptable as a new shell.\n", newShell);
E 6
		return;
	}
D 6
	pw_replace(user, (char *)0, (char *)0, newShell);
E 6
I 6

D 8
	newUser = copympwent(theUser);
E 8
I 8
	newUser = copympwent(theUser, (struct mpasswd *)0);
E 8
	newUser->mpw_shell = newShell;

	pw_replace(theUser, newUser, CHG_SHELL);
E 6
D 4

#ifdef	USE_SYSLOG
	syslog(MESSAGE_LOG_LEVEL,
E 4
I 4
	syslog(LOG_INFO,
E 4
	       "Login shell changed on %s for %s by %s\n",
D 5
	       user->where, user->mpw_name, caller->mpw_name);
E 5
I 5
D 6
	       user->pws_loc, user->mpw_name, caller->mpw_name);
E 5
D 4
#endif

D 3
#ifdef	YP_PASSWD
E 3
I 3
#ifdef	YP_SUPPORT
E 4
I 4
#ifdef	USE_NIS
E 4
E 3
	yp_sync();
#endif
D 4

E 4
	return;
E 6
I 6
	       theUser->pws_loc, theUser->mpw_name, theCaller->mpw_name);
E 6
}

/*
D 9
 *      shell_ok - check shell against CHSH_SHELLS file.
E 9
I 9
 * shell_ok
 *	Validate shell against allowed list
 * Usage
D 10
 *	ok = shell_ok(const char *shellpath);
E 10
I 10
 *	ok = shell_ok(char *shellpath);
E 10
 *
 * Use getusershell() if available, else use <ChshShellsFile>.
E 9
 */
D 9
private int shell_ok(theShell)
char	*theShell;
E 9
I 9
#ifdef	HAS_GETUSERSHELL

extern char	*getusershell();
extern void	setusershell();

private
shell_ok(theShell)
D 10
	const char	*theShell;
E 10
I 10
	char	*theShell;
E 10
E 9
{
I 9
	/*
	 * Use system routines to get blessed shells
	 */
	char	*goodShell;

	setusershell();
	while (goodShell = getusershell()) {
		if (strcmp(theShell, goodShell) == 0)
			return(1);
	}
	return(0);
}
#else	/* HAS_GETUSERSHELL */

private char *default_shells[] = {
	"/bin/sh",
	"/bin/csh",
	0
};

private
shell_ok(theShell)
D 10
	const char	*theShell;
E 10
I 10
	char	*theShell;
E 10
{
E 9
D 6
	FILE	*shells;
	char	*rc;
E 6
I 6
	FILE	*shellf;
E 6
D 12
	char	goodShell[SHELL_NAME_SIZE];
E 12
I 12
	char	goodShell[BUFSIZ];
E 12
D 6
	char	*tptr;
E 6
	int	found = 0;

D 6
	shells = fopen(CHSH_SHELLS, "r");
	if (shells == NULL) {
		die("/etc/shells file missing\n");
	}
	while (!found) {
		rc = fgets(goodShell, SHELL_NAME_SIZE, shells);
		if (rc == NULL) {
			if (feof(shells)) {
				break;
			}
			else {
				die("error reading /etc/shells\n");
			}
E 6
I 6
D 8
	shellf = fopen(chsh_shells, "r");
E 8
I 8
D 12
	shellf = fopen(ChshShellList, "r");
E 12
I 12
	shellf = fopen(Chsh_Shells, "r");
E 12
E 8
	if (shellf == NULL) {
		/*
		 * No shells file - sanity check against the built-in
		 * list of sensible shells
		 */
		char	**shl;

		for (shl = default_shells; *shl; shl++) {
			if (strcmp(*shl, theShell) == 0)
				return(1);
E 6
		}
D 6
		if (goodShell[0] == '#' || goodShell[0] == '\0') {
E 6
I 6
	}
	/*
	 * Consult the system shells file
	 */
D 12
	while (fgets(goodShell, SHELL_NAME_SIZE, shellf)) {
E 12
I 12
	while (fgets(goodShell, sizeof(goodShell), shellf)) {
		if (strchr(goodShell, '\n') == 0)
			continue;
E 12
		chop_nl(goodShell);
		if (goodShell[0] == '#' || goodShell[0] == '\0')
E 6
			continue;
D 6
		}
		for (tptr = goodShell; *tptr != '\n' && *tptr != '\0'; tptr++) ;
		if (*tptr == '\n') *tptr = '\0';
E 6
		if (strcmp(goodShell, theShell) == 0) {
			found = 1;
I 6
			break;
E 6
		}
	}
D 6
	(void) fclose (shells);
E 6
I 6
	(void) fclose (shellf);
E 6
	return (found);
}
I 9
#endif	/* HAS_GETUSERSHELL */
E 9

/*
D 9
 *	can_change_shell - check shell change permission
E 9
I 9
 * can_change_shell
 *	Check shell change permission
E 9
 *
D 9
 *	Returns 1 if shell can be changed
 *		0 if not
E 9
I 9
 * Returns
 *	<other> if caller is root
 *	<deny> if caller and target are different
 *	<self> if ok
E 9
 */
D 9
private enum chg_perm can_change_shell (theUser, theCaller)
struct mpasswd	*theUser,
		*theCaller;
E 9
I 9
private enum chg_perm
can_change_shell (theUser, theCaller)
D 10
	const struct mpasswd	*theUser,
				*theCaller;
E 10
I 10
	struct mpasswd	*theUser,
			*theCaller;
E 10
E 9
{
D 4
	uid_t	calluid = getuid();
E 4
I 4
	Uid_t	calluid = getuid();
E 4

	if (calluid == 0)		/* Su can change anybody's shell */
		return(other);

	if (strcmp(theCaller->mpw_name, theUser->mpw_name))
		return(deny);		/* I'm not root and target isn't me */

	return(self);			/* I can always change my login shell */
}
/*
 * End %M%
 */
E 1
