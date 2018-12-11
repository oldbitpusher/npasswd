/*
 * Copyright (C) 2002  The University of Texas at Austin ("U. T. Austin").
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  Contact: npasswd-support@www.utexas.edu
 *
 */

/*
 *	This program duplicates the manual page behavior of the 4.XBSD
 *	chsh(1) command.
 */
#ifndef lint
static char sccsid[] = "$Id: chsh.c,v 1.14 2002/10/02 15:47:55 clyde Exp $ (cc.utexas.edu) %P%";
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
 * End $RCSfile: chsh.c,v $
 */
