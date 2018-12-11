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

#ifndef lint
static char sccsid[] = "$Id: messages.c,v 1.9 1998/11/17 00:00:00 clyde Exp $ (cc.utexas.edu) %P%";
#endif

#define	_messages_c
#include "defines.h"
#include "constants.h"
#include "compatibility.h"
#include "common.h"

private	int DebugLevel = DB_NONE;	/* Debug level */
private	char *DebugTag = "passwd";	/* Message tag */
private void (*DieCallBack)() = 0;	/* Callback routine */

/*
 * get_debug
 *	Fetch the debug level
 * Usage:
 *	level = get_debug();
 */
public int
get_debug()
{
	return(DebugLevel);
}

/*
 * init_debug
 *	Initialize debug level
 * Usage:
 *	init_debug(number);
 */
public void
init_debug(level)
	int level;		/* Debug level (DB_XXX from ../defines.h) */
{
	DebugLevel = level;
}

/*
 * set_debug
 *	Set debug level from symbolic name
 * Usage:
 *	set_debug(what, table);
 * Effects:
 *	Looks up <what> in debug table <table> and sets the debug level.
 *	The lookup is case-insensitive.
 */
public void
set_debug(arg, dtab)
	char		*arg;	/* Debug level string */
	debug_table	*dtab;	/* Debug table */
{
	if (isdigit(*arg)) {		/* Numeric argument */
		DebugLevel = atoi(arg);
		return;
	}
	if (dtab == 0)			/* No table */
		return;
	for (; dtab->name; dtab++) {
		if (strcasecmp(dtab->name, arg) == 0) {
			DebugLevel = dtab->level;
			return;
		}
	}
}

/*
 * set_debug_title
 *	Set program name tag for debugging and error messages
 * Usage:
 *	set_debug_title(string);
 */
public void
set_debug_tag(tag)
	char *tag;
{
	if (tag)
		DebugTag = tag;
	else
		DebugTag = "";
}

/*
 * debug
 *	Print message to stdout contingent upon debug level
 * Usage:
 *	debug(level, message, args ...);
 */
public void
#ifdef	__STDC__
debug (int level, char *fmt, ...)
{				 /* stdargs version */
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
{				 /* varargs version */
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
 * warn
 *	Spew message to stderr
 * Usage:
 *	warn(message, args ... );
 */
public void
warn VA_DCL(char *msgs)
{

	va_list	args;
#ifdef	__STDC__
	fprintf(stderr, "%s: ", DebugTag);
	va_start(args, msgs);
	vfprintf(stderr, msgs, args);
#else	/* __STDC__ */
	char	*fmt;

	va_start(args);
	fprintf(stderr, "%s: ", DebugTag);
	fmt = va_arg(args, char *);
	vfprintf(stderr, fmt, args);
#endif	/* __STDC__ */
	va_end(args);
	fflush(stderr);
}


/*
 * set_die_callback
 *	Select die callback routine
 * Usage:
 *	set_die_callback(&routine)
 */
public void
set_die_callback(rtn)
	void (*rtn)();
{
	DieCallBack = rtn;
}

/*
 * die
 *	Spew error message and exit
 * Usage:
 *	die(message, args ... );
 */
public void
die VA_DCL(char *msgs)
{
	va_list	args;
#ifdef	__STDC__
	fprintf(stderr, "%s: ", DebugTag);
	va_start(args, msgs);
	vfprintf(stderr, msgs, args);
#else	/* __STDC__ */
	char	*fmt;

	va_start(args);
	fprintf(stderr, "%s: ", DebugTag);
	fmt = va_arg(args, char *);
	vfprintf(stderr, fmt, args);
#endif	/* __STDC__ */
	va_end(args);
	fflush(stderr);
	if (DieCallBack)
		(*DieCallBack)(-1);
	exit(1);
}

/*
 * logdie
 *	Spew error message, syslog it and die.
 * Usage:
 *	logdie(message, args, ...);
 */
public void
logdie VA_DCL(char *msgs)
{
	va_list	args;			/* Argument list */
	char	*fmt;			/* Format */
	char	msgbuf[TMPBUFSIZ];	/* Message buffer */

	VA_START(args, msgs);
#ifdef	__STDC__
	(void) vsprintf(msgbuf, msgs, args);
#else	/* __STDC__ */
	fmt = va_arg(args, char *);
	(void) vsprintf(msgbuf, fmt, args);
#endif	/* __STDC__ */
	va_end(args);
	(void) fprintf(stderr, "%s: %s\n", DebugTag, msgbuf);
	(void) fflush(stderr);
	syslog(LOG_ERR, msgbuf);
	if (DieCallBack)
		(*DieCallBack)(-1);
	exit(1);
}

/*
 * logerr
 *	Spew error message and syslog it.
 * Usage:
 *	logerr(message, args, ...);
 */
public void
logerr VA_DCL(char *msgs)
{
	va_list	args;
	char	*fmt;
	char	msgbuf[TMPBUFSIZ];

	VA_START(args, msgs);
#ifdef	__STDC__
	(void) vsprintf(msgbuf, msgs, args);
#else	/* __STDC__ */
	fmt = va_arg(args, char *);
	(void) vsprintf(msgbuf, fmt, args);
#endif	/* __STDC__ */
	va_end(args);
	syslog(LOG_ERR, msgbuf);
}
/* End $RCSfile: messages.c,v $ */
