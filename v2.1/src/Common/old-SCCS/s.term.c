h05076
s 00001/00001/00247
d D 1.3 99/07/27 12:33:03 clyde 3 2
c Fix return code for term_read()
e
s 00021/00004/00227
d D 1.2 99/02/01 13:55:28 clyde 2 1
c Changes to term_read() \
c 1. Read chars one at a time\
c 2. Recognize \r or \n as end of line\
e
s 00231/00000/00000
d D 1.1 98/11/17 15:34:12 clyde 1 0
c date and time created 98/11/17 15:34:12 by clyde
e
u
U
f e 0
t
T
I 1
/*
 * Terminal handling code.  This module encapsulates most of the
 * mess of reading from the terminal.
 *
 * The following methods are supported:
 *	termios via POSIX tc[gs]attr() routines
 *	termios via TCGETS/TCSETS
 *	termio via TCGETA/TCSETA
 *	V7 sgtty
 *
 * Configure will set only *one* of the symbols used,  so that
 * termios takes precedence over termio which suprecedes sgtty.
 *
 * This is a bloody damn mess - some future revision
 * will toss most of these options and only support termios
 */

#include "npasswd.h"

#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu) %P%";
#endif

#ifdef	I_TERMIOS
/*
 * Has TERMIOS
 */
# include <termios.h>
static struct termios saved_tty_mode;
# define	TTY_SAVE	termios
# define	ECHO_OFF(_b_)		_b_.c_lflag &= ~ECHO
# define	ECHO_ON(_b_)		_b_.c_lflag |= ECHO
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
# define	ECHO_OFF(_b_)		_b_.c_lflag &= ~ECHO
# define	ECHO_ON(_b_)		_b_.c_lflag |= ECHO
# define	GET_TTY(_fd_, _b_)	ioctl(_fd_, TCGETA, (_b_))
# define	SET_TTY(_fd_, _b_)	ioctl(_fd_, TCSETA, (_b_))
#endif	/* I_TERMIO */

/*
 * Neither TERMIOS or TERMIO - use BSD sgtty
 */
#if	(defined(I_SGTTY) && !defined(GET_TTY))
# include <sgtty.h>		/* BSD tty */
# define	TTY_SAVE	sgttyb
# define	ECHO_OFF(_b_)		_b_.sg_flags &= ~ECHO
# define	ECHO_ON(_b_)		_b_.sg_flags |= ECHO
# define	GET_TTY(_fd_, _b_)	ioctl(_fd_, TIOCGETP, (_b_))
# define	SET_TTY(_fd_, _b_)	ioctl(_fd_, TIOCSETP, (_b_))
#endif	/* I_SGTTY */

#ifndef	GET_TTY
/* # ifdef _STDC_ */
/* #	error Cannot figure out how to do tty stuff */
/* # endif */
	ERROR Cannot figure out how to do tty stuff
#endif

static struct {				/* Terminal saved mode */
	char		valid;
	struct TTY_SAVE modes;
} term_saved = { 0 };

static int	term_input_fd = 0;	/* Input file descriptor */

/*
 * term_set_fd
 *	Set terminal input file descriptor
 * Usage:
 *	term_set_fd(filedes)
 * Effects:
 *	Sets the local variable "term_input_fd"
 */
public void
term_set_fd(fd)
	int	fd;
{
D 2
	/* Check if open? */
E 2
	term_input_fd = fd;
}

/*
 * term_get_fd
 *	Get the terminal input file descriptor
 * Usage:
 *	term_get_fd(filedes)
 * Returns:
 *	Local variable "term_input_fd"
 */
public int
term_get_fd()
{
	return(term_input_fd);
}

/*
 * term_save
 *	Save terminal settings
 * Usage:
 *	term_save();
 * Effects:
 *	Stores terminal mode in the "term_saved" structure for
 *	restoration by fixtty()
 */
public void
term_save()
{
	(void) GET_TTY(term_input_fd, &term_saved.modes);
	term_saved.valid++;
}

/*
 * fixtty
 *	Restore saved terminal settings
 * Usage:
 *	term_restore()
 * Effects:
 *	Changes terminal settings from the "term_saved" structure
 *	if that data is valid
 */
public void
term_restore()
{
	if (term_saved.valid)
		(void) SET_TTY(term_input_fd, &term_saved.modes);
	term_saved.valid = 0;
}


/*
 * term_echo
 *	Toggle terminal echo mode
 * Usage:
 *	term_echo(0 = off, !0 = on)
 */
public void
term_echo(func)
	int	func;		/* On/off switch */
{
	struct TTY_SAVE	xecho;

	(void) GET_TTY(term_input_fd, &xecho);
	if (func)
		ECHO_ON(xecho);
	else
		ECHO_OFF(xecho);
	(void) SET_TTY(term_input_fd, &xecho);
}

/*
 * term_raw
 *	Toggle terminal raw mode
 * Usage:
 *	term_raw(0 = off, !0 = on)
 */
public void
term_raw(func)
	int	func;		/* On/off switch */
{
#if	(defined(I_TERMIOS) || defined(I_TERMIO))
	/*
	 * In termio(s) non-canonical (raw) mode is not a toggle.
	 * Save the old mode so that it can be restored.
	 */
	static struct TTY_SAVE save;	/* Saved terminal mode */
	static int save_valid = 0;	/* Is the save valid? */
	struct TTY_SAVE	change;		/* Terminal change */

	if (func) {			/* Enabling 'raw' mode */
		(void) GET_TTY(term_input_fd, &save);
		save_valid = 1;
		(void) GET_TTY(term_input_fd, &change);
		change.c_oflag = 0;
		change.c_lflag = 0;
		change.c_cc[VMIN] = 1;
		change.c_cc[VTIME] = 0;
		(void) SET_TTY(term_input_fd, &change);
	} else {			/* Disabling 'raw' mode */
		if (save_valid) {
			(void) SET_TTY(term_input_fd, &save);
			save_valid = 0;
		}
	}
#endif
#ifdef	I_SGTTY
	/*
	 * Raw mode is a toggle so state is not saved.
	 */
	struct TTY_SAVE	change;

	(void) GET_TTY(term_input_fd, &change);
	if (func) {
		change.sg_flags |= RAW;
		(void) SET_TTY(term_input_fd, &change);
	} else {
		change.sg_flags &= ~RAW;
	}
	(void) SET_TTY(term_input_fd, &change);
#endif
}

/*
 * term_read
 *	Read from terminal
I 2
 *
E 2
 * Usage:
 *	count = term_read(buffer, sizeof buffer)
I 2
 *
 * Returns:
 *	Count of characters read, up to <buffer_size>
 *	
E 2
 */
public int
term_read(buffer, buffer_size)
D 2
	char	*buffer;
	size_t	buffer_size;
E 2
I 2
	char	*buffer;	/* Buffer for input */
	size_t	buffer_size;	/* How big <buffer> is */
E 2
{
D 2
	return (read(term_input_fd, buffer, buffer_size));
E 2
I 2
	char	cin;		/* Input character */
	char	*cptr = buffer;	/* Pointer into input buffer */
	size_t	cnt = 0;	/* Counter */

	while (read(term_input_fd, &cin, 1) == 1) {
		*cptr++ = cin;
		if (cnt == (buffer_size - 1))		/* Avoid overflow */
			break;
		cnt++;
		if (cin == '\n' || cin == '\r')	/* Break on \r or \n */
			break;
	}
	*cptr = 0;
D 3
	return(cin);
E 3
I 3
	return(cnt);
E 3
E 2
}

/* End %M% */
E 1
