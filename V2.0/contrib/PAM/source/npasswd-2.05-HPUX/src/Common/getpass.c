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
 * Routines to deal with passwords.
 */

#include "npasswd.h"
#include "pw_svc.h"

#ifndef lint
static char sccsid[] = "@(#)getpass.c	1.7 11/17/98 (cc.utexas.edu) /usr/share/src/private/ut/share/bin/passwd/V2.0/src/Common/SCCS/s.getpass.c";
#endif

/*
 * Configuration settings
 */
Config_Value int		PasswdMatchTries = PASSWORD_MATCH_TRIES;
Config_Value unsigned int	PasswdMatchWait = PASSWORD_MATCH_WAIT;

/*
 * get_password
 *	Read password from user and compare to present
 *
 * Effects:
 *	Stores matching plaintext password in <pwd_plain> buffer
 */
public void
get_password(prompt, pwd_crypt, pwd_plain, pwd_psize)
	char	*prompt,	/* Prompt string */
		*pwd_crypt,	/* Present password (encrypted) */
		*pwd_plain;	/* New password (plain) */
	int	pwd_psize;	/* Size of pwd_plain */
{
	int	ntries = 0;	/* Attempt counter */
	char	*pwtemp;	/* Password read temp */

	for (;;) {
		if ((pwtemp = np_getpass(prompt)) == NULL)
			die("Password unmatched.\n");
		if (*pwtemp == '\0')
			continue;
		if (password_cmp(pwd_crypt, pwtemp) == 0) {
			printf("Password incorrect.\n");
			if (PasswdMatchWait > 0)
				sleep(PasswdMatchWait);
			if (++ntries == PasswdMatchTries) {
				if (PasswdMatchWait > 0)
					(void) sleep(PasswdMatchWait);
				die("Password not matched.\n");
			}
			continue;
		}
		break;
	}
	(void) strncpy(pwd_plain, pwtemp, pwd_psize);
}

/*
 * password_cmp
 *	Compare old and new passwords
 *
 * Returns:
 *	1 if match
 *	0 if not
 */
public 
password_cmp(current, check)
	char	*current,		/* Current password (encrypted) */
		*check;			/* Password to compare (plain) */
{
	struct pw_svc	*svc = get_pwsvc();	/* Passwd service */

	if (*current == 0)		/* Null password */
		return(1);

	return (strcmp(current, (*svc->PasswdCrypt)(check, current)) == 0);
}

/*
 * np_getpass
 *	Replacement for libc getpass(3)
 * Usage:
 *	pass = np_getpass(prompt);
 * Returns:
 *	Password string
 *	NULL if EOF encountered or error
 * Comments:
 *	This routine is used instead of getpass(3):
 *
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
 */
#define	PROMPT_FD	2		/* File descriptor for prompts */

public char	*
np_getpass(prompt)
	char	*prompt;		/* Prompt string */
{
	struct sigblk	blocked;	/* Blocked signals */
	static char	ib[64];		/* Input buffer */
	int		nr;		/* Terminal read return */

	ib[0] = 0;
	if (XSwitches[Xsw_UseStdin] == 0) {	/* Stdin is a tty */
		term_echo(0);
		(void) write(PROMPT_FD, prompt, strlen(prompt));
		block_signals(&blocked, SIGTSTP, 0);
		nr = term_read(ib, sizeof(ib));
		term_echo(1);
		(void) write(PROMPT_FD, "\n", 1);
		unblock_signals(&blocked);
	} else {
		nr = term_read(ib, sizeof(ib));
	}
	if (nr <= 0)			/* EOF or error */
		return(NULL);
	chop_nl(ib);			/* Pitch newline at end */
	return(ib);
}
#undef	PROMPT_FD

/* End getpass.c */
