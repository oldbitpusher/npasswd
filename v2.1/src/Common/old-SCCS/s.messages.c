h53541
s 00130/00041/00174
d D 1.9 98/11/17 16:48:23 clyde 9 8
c 1. Add copyright notice
c 2. Reformat function comments
e
s 00048/00010/00167
d D 1.8 98/07/09 14:16:57 clyde 8 7
c 1. Make DebugLevel a static local
c 2. Make ProgramName (renamed DebugTag) a static local
c 3. Add set_debug_tag(), set_debug(), get_debug() and init_debug()
e
s 00021/00000/00156
d D 1.7 98/07/02 16:41:37 clyde 7 6
c Add set_debug() routine
e
s 00001/00000/00155
d D 1.6 97/09/23 12:30:27 clyde 6 5
c Add define to fix problems with common.h and AIX
e
s 00001/00001/00154
d D 1.5 96/08/29 13:01:29 clyde 5 4
c Remove 'const' declarations (too much compiler pain)
e
s 00013/00002/00142
d D 1.4 96/08/15 11:02:57 clyde 4 3
c Add callback routine for die() and logdie()
e
s 00000/00001/00144
d D 1.3 96/08/09 16:18:58 clyde 3 2
c Beta 3 development checkin 2
e
s 00009/00009/00136
d D 1.2 96/08/07 15:21:06 clyde 2 1
c beta 3 development checkin
e
s 00145/00000/00000
d D 1.1 96/04/01 16:15:09 clyde 1 0
c date and time created 96/04/01 16:15:09 by clyde
e
u
U
f e 0
t
T
I 1
/*
D 2
 * npasswd module %M%
 *
 * These are message routines used throughout npasswd.
 *
 * Compilation: 	cc -c %M%
 * Includes:		npasswd.h
 *
E 2
I 2
D 9
 * Message routines used by npasswd and checkpasswd
E 9
I 9
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
E 9
E 2
 */
I 9

/*
 * Message routines
 *
 * Exported routines:
 *	get_debug
 *	init_debug
 *	set_debug
 *	set_die_callback
 *	set_debug_tag
 *	debug
 *	warn
 *	die
 *	logdie
 *	logerr
 */

E 9
D 2
#include "npasswd.h"

E 2
#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu) %P%";
#endif

I 6
#define	_messages_c
E 6
I 2
D 3
#include <stdio.h>
E 3
#include "defines.h"
#include "constants.h"
#include "compatibility.h"
I 7
#include "common.h"
E 7

D 8
extern	int DebugLevel;
extern	char *ProgramName;
E 8
I 8
D 9
private	int DebugLevel = DB_NONE;
private	char *DebugTag = "passwd";
E 9
I 9
private	int DebugLevel = DB_NONE;	/* Debug level */
private	char *DebugTag = "passwd";	/* Message tag */
private void (*DieCallBack)() = 0;	/* Callback routine */
E 9
E 8

E 2
/*
I 7
D 8
 * setdebug - set debug level
E 8
I 8
 * get_debug
 *	Fetch the debug level
I 9
 * Usage:
 *	level = get_debug();
E 9
E 8
 */
I 8
D 9
public
E 9
I 9
public int
E 9
get_debug()
{
	return(DebugLevel);
}

/*
 * init_debug
 *	Initialize debug level
I 9
 * Usage:
 *	init_debug(number);
E 9
 */
E 8
public void
I 8
init_debug(level)
D 9
	int level;		/* Binary value (DB_xxxx) */
E 9
I 9
	int level;		/* Debug level (DB_XXX from ../defines.h) */
E 9
{
	DebugLevel = level;
}

/*
 * set_debug
D 9
 *	Decode symbolic value and set debug level
E 9
I 9
 *	Set debug level from symbolic name
 * Usage:
 *	set_debug(what, table);
 * Effects:
 *	Looks up <what> in debug table <table> and sets the debug level.
 *	The lookup is case-insensitive.
E 9
 */
public void
E 8
set_debug(arg, dtab)
D 8
	char		*arg;	/* The argument string */
	debug_levels	*dtab;	/* The debug levels structure */
E 8
I 8
	char		*arg;	/* Debug level string */
	debug_table	*dtab;	/* Debug table */
E 8
{
D 9
	if (isdigit(*arg)) {
E 9
I 9
	if (isdigit(*arg)) {		/* Numeric argument */
E 9
		DebugLevel = atoi(arg);
		return;
	}
I 8
D 9
	if (dtab == 0)
E 9
I 9
	if (dtab == 0)			/* No table */
E 9
		return;
E 8
	for (; dtab->name; dtab++) {
		if (strcasecmp(dtab->name, arg) == 0) {
			DebugLevel = dtab->level;
			return;
		}
	}
}

/*
I 8
 * set_debug_title
 *	Set program name tag for debugging and error messages
I 9
 * Usage:
 *	set_debug_title(string);
E 9
 */
public void
D 9
set_debug_tag(title)
	char *title;
E 9
I 9
set_debug_tag(tag)
	char *tag;
E 9
{
D 9
	if (title)
		DebugTag = title;
E 9
I 9
	if (tag)
		DebugTag = tag;
E 9
	else
		DebugTag = "";
}

/*
E 8
E 7
D 9
 * debug - print debug message (contingent upon debugging level)
E 9
I 9
 * debug
 *	Print message to stdout contingent upon debug level
 * Usage:
 *	debug(level, message, args ...);
E 9
 */
public void
#ifdef	__STDC__
debug (int level, char *fmt, ...)
D 9
{
E 9
I 9
{				 /* stdargs version */
E 9
	va_list	args;

	if (DebugLevel < level)
		return;
	va_start(args, fmt);
	vprintf(fmt, args);
	fflush(stdout);
	va_end(args);
}
#else	/* __STDC__ */
debug (va_alist)
va_dcl
D 9
{
E 9
I 9
{				 /* varargs version */
E 9
	va_list	args;
	int	level;
	char	*fmt;

	va_start(args);
	level = va_arg(args, int);
	fmt = va_arg(args, char *);
	if (DebugLevel >= level) {
		vprintf(fmt, args);
		fflush(stdout);
	}
	va_end(args);
}
#endif

/*
D 9
 * die - spew error and die
E 9
I 9
 * warn
 *	Spew message to stderr
 * Usage:
 *	warn(message, args ... );
E 9
 */
I 4
D 9
private void (*DieCallBack)() = 0;

E 9
E 4
public void
I 4
D 9
set_die_callback(rtn)
D 5
	const void (*rtn)();
E 5
I 5
	void (*rtn)();
E 9
I 9
warn VA_DCL(char *msgs)
E 9
E 5
{
D 9
	DieCallBack = rtn;
}
E 9

D 9
public void
E 4
die VA_DCL(char *msgs)
{
E 9
	va_list	args;
#ifdef	__STDC__
D 8
	fprintf(stderr, "%s: ", ProgramName);
E 8
I 8
	fprintf(stderr, "%s: ", DebugTag);
E 8
	va_start(args, msgs);
	vfprintf(stderr, msgs, args);
#else	/* __STDC__ */
	char	*fmt;

	va_start(args);
D 8
	fprintf(stderr, "%s: ", ProgramName);
E 8
I 8
	fprintf(stderr, "%s: ", DebugTag);
E 8
	fmt = va_arg(args, char *);
	vfprintf(stderr, fmt, args);
#endif	/* __STDC__ */
	va_end(args);
	fflush(stderr);
D 4
	pw_cleanup(-1);
E 4
I 4
D 9
	if (DieCallBack)
		(*DieCallBack)(-1);
E 4
	exit(1);
E 9
}

I 9

E 9
/*
D 9
 * warn - spew error
E 9
I 9
 * set_die_callback
 *	Select die callback routine
 * Usage:
 *	set_die_callback(&routine)
E 9
 */
public void
D 9
warn VA_DCL(char *msgs)
E 9
I 9
set_die_callback(rtn)
	void (*rtn)();
E 9
{
I 9
	DieCallBack = rtn;
}
E 9

I 9
/*
 * die
 *	Spew error message and exit
 * Usage:
 *	die(message, args ... );
 */
public void
die VA_DCL(char *msgs)
{
E 9
	va_list	args;
#ifdef	__STDC__
D 8
	fprintf(stderr, "%s: ", ProgramName);
E 8
I 8
	fprintf(stderr, "%s: ", DebugTag);
E 8
	va_start(args, msgs);
	vfprintf(stderr, msgs, args);
#else	/* __STDC__ */
	char	*fmt;

	va_start(args);
D 8
	fprintf(stderr, "%s: ", ProgramName);
E 8
I 8
	fprintf(stderr, "%s: ", DebugTag);
E 8
	fmt = va_arg(args, char *);
	vfprintf(stderr, fmt, args);
#endif	/* __STDC__ */
	va_end(args);
	fflush(stderr);
I 9
	if (DieCallBack)
		(*DieCallBack)(-1);
	exit(1);
E 9
}

/*
D 9
 * logdie - spew error, log message and die
E 9
I 9
 * logdie
 *	Spew error message, syslog it and die.
 * Usage:
 *	logdie(message, args, ...);
E 9
 */
public void
logdie VA_DCL(char *msgs)
{
D 9
	va_list	args;
	char	*fmt;
	char	msgbuf[TMPBUFSIZ];
E 9
I 9
	va_list	args;			/* Argument list */
	char	*fmt;			/* Format */
	char	msgbuf[TMPBUFSIZ];	/* Message buffer */
E 9

	VA_START(args, msgs);
#ifdef	__STDC__
D 9
	vsprintf(msgbuf, msgs, args);
E 9
I 9
	(void) vsprintf(msgbuf, msgs, args);
E 9
#else	/* __STDC__ */
	fmt = va_arg(args, char *);
D 9
	vsprintf(msgbuf, fmt, args);
E 9
I 9
	(void) vsprintf(msgbuf, fmt, args);
E 9
#endif	/* __STDC__ */
	va_end(args);
D 8
	fprintf(stderr, "%s: %s\n", ProgramName, msgbuf);
E 8
I 8
D 9
	fprintf(stderr, "%s: %s\n", DebugTag, msgbuf);
E 8
	fflush(stderr);
E 9
I 9
	(void) fprintf(stderr, "%s: %s\n", DebugTag, msgbuf);
	(void) fflush(stderr);
E 9
	syslog(LOG_ERR, msgbuf);
D 4
	pw_cleanup(-1);
E 4
I 4
	if (DieCallBack)
		(*DieCallBack)(-1);
E 4
	exit(1);
}

/*
D 9
 * log_error - spew error and log message
E 9
I 9
 * logerr
 *	Spew error message and syslog it.
 * Usage:
 *	logerr(message, args, ...);
E 9
 */
public void
logerr VA_DCL(char *msgs)
{
	va_list	args;
	char	*fmt;
	char	msgbuf[TMPBUFSIZ];

	VA_START(args, msgs);
#ifdef	__STDC__
D 9
	vsprintf(msgbuf, msgs, args);
E 9
I 9
	(void) vsprintf(msgbuf, msgs, args);
E 9
#else	/* __STDC__ */
	fmt = va_arg(args, char *);
D 9
	vsprintf(msgbuf, fmt, args);
E 9
I 9
	(void) vsprintf(msgbuf, fmt, args);
E 9
#endif	/* __STDC__ */
	va_end(args);
	syslog(LOG_ERR, msgbuf);
}
/* End %M% */
E 1
