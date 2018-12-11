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
 *	A collection of file utility routines used by npasswd
 */

#include "npasswd.h"

#ifndef lint
static char sccsid[] = "@(#)file_util.c	1.3 11/17/98 (cc.utexas.edu) /usr/share/src/private/ut/share/bin/passwd/V2.0/src/Common/SCCS/s.file_util.c";
#endif

/*
 * File locking retry parameters
 */
#ifndef	FLOCK_TRIES
# define	FLOCK_TRIES 4
#endif
#ifndef	FLOCK_CYCLE
# define	FLOCK_CYCLE 2
#endif

Config_Value int	LockTries = FLOCK_TRIES;	/* How many times */
Config_Value int	LockCycle = FLOCK_CYCLE;	/* How long to wait */

/*
 * FileSize
 *	Get size of a file 
 * Usage
 *	size = FileSize(file);
 * Returns
 *	size of <fn> (bytes)
 */
public size_t
FileSize(fn)
	char	*fn;	
{
	struct stat	stb;	/* ACME Scratch Storage */

	if (stat(fn, &stb) < 0)
		return(0);
	return(stb.st_size);
}

/*
 * MakeLockTemp
 *	Create a file with exclusive use checking
 * Usage
 *	fd = MakeLockTemp(file);
 * Returns
 *	File descriptor of created file
 * Error
 *	Aborts if file cannot be created, usually because
 *	the file exists.
 */
public int
MakeLockTemp(name)
	char	*name;
{
	int	fd;	/* ACME Scratch Storage */
	int	cnt;	/* Retry counter */

	for (cnt = 0; cnt <= LockTries; cnt++) {
		if ((fd = open(name, O_WRONLY|O_CREAT|O_EXCL, 0600)) >= 0) 
			return(fd);
		debug(DB_DETAIL, "MakeLockTemp \"%s\" cycle %d\n", name, cnt);
		(void) sleep(LockCycle);
	}
	perror("Tempfile create");
	logdie("Cannot create temp file \"%s\"\n", name);
}

/*
 * OpenWithLock
 *	Open a file with exclusive use checking
 * Usage
 *	fd = OpenWithLock(file);
 * Returns
 *	File descriptor of created file
 * Error
 *	Aborts if file cannot be created, usually because
 *	the file exists.
 */
public int
OpenWithLock(name)
	char	*name;
{
	int	fd;	/* ACME Scratch Storage */
	int	cnt;	/* Retry counter */

	for (cnt = 0; cnt <= LockTries; cnt++) {
		if ((fd = open(name, O_WRONLY|O_EXCL, 0)) >= 0) 
			return(fd);
		debug(DB_DETAIL, "OpenWithLock \"%s\" cycle %d\n", name, cnt);
		(void) sleep(LockCycle);
	}
	perror("File open");
	logdie("Cannot lock open file \"%s\"\n", name);
}

#if	!(defined(HAS_FCHMOD) && defined(HAS_FCHMOD))
/*
 * FixPwFileMode
 *	Set protection for passwd/shadow files
 * Usage
 *	FixPwFileMode(filename, "passwd" | "shadow");
 *
 * Used only when fchmod() and fchown() do not exist
 */
public void
FixPwFileMode(file, type)
	char	*file,
		*type;
{
	(void) chown(file, PASSWD_UID, PASSWD_GID);
	(void) chmod(file, PASSWD_MODE);
	if (strcmp(type, "shadow") == 0)
		(void) chmod(file, SHADOW_MODE);
}
#endif

/* End file_util.c */
