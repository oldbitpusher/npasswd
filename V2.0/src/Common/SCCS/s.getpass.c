h46796
s 00045/00003/00133
d D 1.7 98/11/17 15:46:11 clyde 7 6
c 1. Add copyright notice 
c 2. Fix introductory comments
e
s 00013/00116/00123
d D 1.6 98/11/17 15:34:01 clyde 6 5
c Move terminal mode stuff to term.c, use new routines
e
s 00042/00038/00197
d D 1.5 98/10/13 16:46:30 clyde 5 4
c 1. Massage comments a bit
c 2. Fix PasswdMatchTries fencepost error
e
s 00006/00001/00229
d D 1.4 98/08/17 14:11:06 clyde 4 3
c Block SIGTSTP while echo is off
e
s 00004/00001/00226
d D 1.3 98/07/09 14:15:35 clyde 3 2
c Call get_pwsvc() when needed
e
s 00017/00001/00210
d D 1.2 98/04/30 16:33:28 clyde 2 1
c 1. Parameterize PasswdMatchTries
c 2. Add password_cmp() [moved from passwd.c]
e
s 00211/00000/00000
d D 1.1 98/03/26 13:40:50 clyde 1 0
c date and time created 98/03/26 13:40:50 by clyde
e
u
U
f e 0
t
T
I 1
/*
D 7
 *	This program duplicates the manual page behavior of the 4.XBSD
 *	passwd(1) command.  It can be configured for use with a variety
 *	of passwd systems (/etc/passwd, /etc/shadow, databases).
E 7
I 7
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
E 7
 */

I 7
/*
 * Routines to deal with passwords.
 */

E 7
#include "npasswd.h"
I 3
#include "pw_svc.h"
E 3

#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu) %P%";
#endif

/*
 * Configuration settings
 */
D 2
Config_Value int		PasswdMatchTries = 3;
E 2
I 2
Config_Value int		PasswdMatchTries = PASSWORD_MATCH_TRIES;
E 2
Config_Value unsigned int	PasswdMatchWait = PASSWORD_MATCH_WAIT;

/*
D 5
 *	get_password -- read password and check against current.
E 5
I 5
 * get_password
 *	Read password from user and compare to present
 *
 * Effects:
 *	Stores matching plaintext password in <pwd_plain> buffer
E 5
 */
public void
D 5
get_password(prompt, pwd_crypt, pwd_plain, pwlen)
	char	*prompt,
		*pwd_crypt;	/* Present password (encrypted) */
	char	*pwd_plain;	/* Present password (plain)  */
	int	pwlen;		/* Length of present password buffer */
E 5
I 5
get_password(prompt, pwd_crypt, pwd_plain, pwd_psize)
	char	*prompt,	/* Prompt string */
		*pwd_crypt,	/* Present password (encrypted) */
		*pwd_plain;	/* New password (plain) */
	int	pwd_psize;	/* Size of pwd_plain */
E 5
{
D 5
	int	ntries = 0;	/* Match attempt counter */
	int	doit = 1;
	char	*px;		/* Temp */
	unsigned int naptime = PasswdMatchWait;	/* Sleep after bad entry */
E 5
I 5
	int	ntries = 0;	/* Attempt counter */
	char	*pwtemp;	/* Password read temp */
E 5

D 5
	while (doit) {
		if ((px = np_getpass(prompt)) == NULL)
E 5
I 5
	for (;;) {
		if ((pwtemp = np_getpass(prompt)) == NULL)
E 5
			die("Password unmatched.\n");
D 5
		if (*px == '\0')
E 5
I 5
		if (*pwtemp == '\0')
E 5
			continue;
D 5
		if (!password_cmp(pwd_crypt, px)) {
E 5
I 5
		if (password_cmp(pwd_crypt, pwtemp) == 0) {
E 5
			printf("Password incorrect.\n");
D 5
			if (naptime)
				sleep(naptime);
			if (ntries++ == PasswdMatchTries) {
				if (naptime)
					sleep(naptime);
E 5
I 5
			if (PasswdMatchWait > 0)
				sleep(PasswdMatchWait);
			if (++ntries == PasswdMatchTries) {
				if (PasswdMatchWait > 0)
					(void) sleep(PasswdMatchWait);
E 5
				die("Password not matched.\n");
			}
			continue;
		}
D 5
		doit = 0;
E 5
I 5
		break;
E 5
	}
D 5
	(void) strncpy(pwd_plain, px, pwlen);
E 5
I 5
	(void) strncpy(pwd_plain, pwtemp, pwd_psize);
E 5
}

I 2
/*
D 5
 *	password_cmp - compare old and new passwords
E 5
I 5
 * password_cmp
 *	Compare old and new passwords
E 5
 *
D 5
 *	Returns 1 if check = new, 0 if not
E 5
I 5
 * Returns:
 *	1 if match
 *	0 if not
E 5
 */
public 
password_cmp(current, check)
D 5
	char	*current,
		*check;
E 5
I 5
	char	*current,		/* Current password (encrypted) */
		*check;			/* Password to compare (plain) */
E 5
{
I 3
D 5
	struct pw_svc	*svc = get_pwsvc();
E 5
I 5
	struct pw_svc	*svc = get_pwsvc();	/* Passwd service */
E 5

E 3
D 5
	if (!*current)
E 5
I 5
	if (*current == 0)		/* Null password */
E 5
		return(1);

D 3
	return (strcmp(current, (*svc.PasswdCrypt)(check, current)) == 0);
E 3
I 3
	return (strcmp(current, (*svc->PasswdCrypt)(check, current)) == 0);
E 3
}

E 2
/*
D 6
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
 */
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
/* # ifdef _STDC_ */
/* #	error Cannot figure out how to do tty stuff */
/* # endif */
	ERROR Cannot figure out how to do tty stuff
#endif

static struct {
	char		valid;
	struct TTY_SAVE mode;
} tty_save = { 0 };

/*
 * savetty
 *	Save terminal settings
 * Usage:
 *	savetty();
 * Effects:
 *	Stores terminal mode in the "tty_save" structure for
 *	restoration by fixtty()
 */
public void
savetty()
{
	(void) GET_TTY(0, &tty_save.mode);
	tty_save.valid++;
}

/*
 * fixtty
 *	Restore saved terminal settings
 * Usage:
 *	fixtty()
 * Effects:
 *	Changes terminal settings from the "tty_save" structure
 *	if that data is valid
 */
public void
fixtty()
{
	if (tty_save.valid)
		(void) SET_TTY(0, &tty_save.mode);
}

/*
E 6
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
I 6
#define	PROMPT_FD	2		/* File descriptor for prompts */

E 6
public char	*
np_getpass(prompt)
D 5
char	*prompt;
E 5
I 5
	char	*prompt;		/* Prompt string */
E 5
{
D 5
	struct TTY_SAVE	saved,
			noecho;
I 4
	struct sigblk	blocked;
E 5
I 5
D 6
	struct TTY_SAVE	saved,		/* Saved TTY modes */
			noecho;		/* TTY mode for 'no echo' mode */
E 6
	struct sigblk	blocked;	/* Blocked signals */
E 5
E 4
	static char	ib[64];		/* Input buffer */
D 5
	int	nr;
E 5
I 5
	int		nr;		/* Terminal read return */
E 5

D 5
	if (!XSwitches[Xsw_UseStdin]) {
E 5
I 5
D 6
	if (!XSwitches[Xsw_UseStdin]) {		/* Suppress tty echo ? */
E 5
		(void) GET_TTY(0, &saved);
		noecho = saved;
		ECHO_OFF(noecho);
		(void) write(2, prompt, strlen(prompt));
		(void) SET_TTY(0, &noecho);
I 4
		block_signals(&blocked, SIGTSTP, 0);
E 4
	}
E 6
	ib[0] = 0;
D 6
	nr = read(0, ib, sizeof(ib));
D 4
	if (!XSwitches[Xsw_UseStdin])
E 4
I 4
D 5
	if (!XSwitches[Xsw_UseStdin]) {
E 5
I 5
	if (!XSwitches[Xsw_UseStdin]) {		/* Reinstate tty echo? */
E 5
E 4
		SET_TTY(0, &saved);
E 6
I 6
	if (XSwitches[Xsw_UseStdin] == 0) {	/* Stdin is a tty */
		term_echo(0);
		(void) write(PROMPT_FD, prompt, strlen(prompt));
		block_signals(&blocked, SIGTSTP, 0);
		nr = term_read(ib, sizeof(ib));
		term_echo(1);
		(void) write(PROMPT_FD, "\n", 1);
E 6
I 4
		unblock_signals(&blocked);
I 6
	} else {
		nr = term_read(ib, sizeof(ib));
E 6
	}
E 4
D 5
	(void) write(2, "\n", 1);
	if (nr <= 0)		/* EOF or error */
E 5
I 5
D 6
	(void) write(2, "\n", 1);	/* Put newline to stderr */
E 6
	if (nr <= 0)			/* EOF or error */
E 5
		return(NULL);
D 5
	chop_nl(ib);
E 5
I 5
	chop_nl(ib);			/* Pitch newline at end */
E 5
	return(ib);
}
I 6
#undef	PROMPT_FD

E 6
I 4
D 5

E 5
E 4
/* End %M% */
E 1
