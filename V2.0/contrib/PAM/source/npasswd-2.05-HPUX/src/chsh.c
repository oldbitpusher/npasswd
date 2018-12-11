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
 *	chsh(1) command.
 */
#ifndef lint
static char sccsid[] = "@(#)chsh.c	1.13 06/23/98 (cc.utexas.edu) /usr/share/src/private/ut/share/bin/passwd/V2.0/src/SCCS/s.chsh.c";
#endif

#include "npasswd.h"
#include "Methods/pwm_defs.h"

private enum chg_perm can_change_shell _((struct mpasswd *, struct mpasswd *));
private int shell_ok _((char *));

Config_Value char	*Chsh_Help = CHSH_HELP,
			*Chsh_Motd = CHSH_MOTD,
			*Chsh_Shells = SHELLS_FILE;

/*
 * chsh - Shell change module
 */
public void chsh(theUser, theCaller)
	struct mpasswd	*theUser,
			*theCaller;
{
	char	newShell[BUFSIZ];
	enum	chg_perm	perm;
	struct mpasswd	*newUser;

	if ((perm = can_change_shell (theUser, theCaller)) == deny)
		die("Permission denied.\n");

#ifdef  USE_NIS
	yp_password(theUser);
#endif
	motd(Chsh_Motd, (char *)0);

	if (perm == self && !shell_ok (theUser->mpw_shell)) {
		printf("Cannot change from restricted shell %s.\n", 
			 theUser->mpw_shell);
		return;
	}

	printf("Changing shell for %s on %s\n", 
		theUser->mpw_name, theUser->pws_loc);

	for (;;) {
		if (!XSwitches[Xsw_UseStdin]) {
			printf("Old shell: %s\n", theUser->mpw_shell);
			printf("New shell (? for help): ");
		}
		if (fgets(newShell, BUFSIZ, stdin) == NULL) {
			if (feof(stdin)) {
				printf("\nShell unchanged\n");
				return;
			}
			else {
				die ("Error while reading stdin\n");
			}
		}
		chop_nl(newShell);
		if (strcmp(newShell, "?") == 0) {
			motd(Chsh_Help, "Sorry, there is no help.\n");
			continue;
		}
		break;
	}
	
	if (*newShell == '\0' || strcmp(theUser->mpw_shell, newShell) == 0) {
		printf("Login shell unchanged\n");
		return;
	}

	if (!shell_ok(newShell)) {
		printf("%s is unacceptable as a new shell.\n", newShell);
		return;
	}

	newUser = copympwent(theUser, (struct mpasswd *)0);
	newUser->mpw_shell = newShell;

	pw_replace(theUser, newUser, CHG_SHELL);
	syslog(LOG_INFO,
	       "Login shell changed on %s for %s by %s\n",
	       theUser->pws_loc, theUser->mpw_name, theCaller->mpw_name);
}

/*
 * shell_ok
 *	Validate shell against allowed list
 * Usage
 *	ok = shell_ok(char *shellpath);
 *
 * Use getusershell() if available, else use <ChshShellsFile>.
 */
#ifdef	HAS_GETUSERSHELL

extern char	*getusershell();
extern void	setusershell();

private
shell_ok(theShell)
	char	*theShell;
{
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
	char	*theShell;
{
	FILE	*shellf;
	char	goodShell[BUFSIZ];
	int	found = 0;

	shellf = fopen(Chsh_Shells, "r");
	if (shellf == NULL) {
		/*
		 * No shells file - sanity check against the built-in
		 * list of sensible shells
		 */
		char	**shl;

		for (shl = default_shells; *shl; shl++) {
			if (strcmp(*shl, theShell) == 0)
				return(1);
		}
	}
	/*
	 * Consult the system shells file
	 */
	while (fgets(goodShell, sizeof(goodShell), shellf)) {
		if (strchr(goodShell, '\n') == 0)
			continue;
		chop_nl(goodShell);
		if (goodShell[0] == '#' || goodShell[0] == '\0')
			continue;
		if (strcmp(goodShell, theShell) == 0) {
			found = 1;
			break;
		}
	}
	(void) fclose (shellf);
	return (found);
}
#endif	/* HAS_GETUSERSHELL */

/*
 * can_change_shell
 *	Check shell change permission
 *
 * Returns
 *	<other> if caller is root
 *	<deny> if caller and target are different
 *	<self> if ok
 */
private enum chg_perm
can_change_shell (theUser, theCaller)
	struct mpasswd	*theUser,
			*theCaller;
{
	Uid_t	calluid = getuid();

	if (calluid == 0)		/* Su can change anybody's shell */
		return(other);

	if (strcmp(theCaller->mpw_name, theUser->mpw_name))
		return(deny);		/* I'm not root and target isn't me */

	return(self);			/* I can always change my login shell */
}
/*
 * End chsh.c
 */
