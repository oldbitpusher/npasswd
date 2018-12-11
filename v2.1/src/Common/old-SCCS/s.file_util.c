h41121
s 00044/00000/00120
d D 1.3 98/11/17 15:44:45 clyde 3 2
c Add copyright notice
e
s 00037/00014/00083
d D 1.2 98/10/13 16:47:19 clyde 2 1
c 1. hange FileSizeDiff() to FileSize()
c 2. Add OpenWithLock() routine
e
s 00097/00000/00000
d D 1.1 98/03/26 13:40:51 clyde 1 0
c date and time created 98/03/26 13:40:51 by clyde
e
u
U
f e 0
t
T
I 1
/*
I 3
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
E 3
 *	A collection of file utility routines used by npasswd
 */

#include "npasswd.h"

#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu) %P%";
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
D 2
 * FileSizeDiff
 *	Find size difference between two files
E 2
I 2
 * FileSize
 *	Get size of a file 
E 2
 * Usage
D 2
 *	diff = FileSizeDiff(file1, file2);
E 2
I 2
 *	size = FileSize(file);
E 2
 * Returns
D 2
 *	(size of <file2>) - (size of <file1>) bytes
E 2
I 2
 *	size of <fn> (bytes)
E 2
 */
public size_t
D 2
FileSizeDiff(fn1, fn2)
	char	*fn1,	
		*fn2;
E 2
I 2
FileSize(fn)
	char	*fn;	
E 2
{
	struct stat	stb;	/* ACME Scratch Storage */
D 2
	size_t	s1;		/* ACME Scratch Storage */
E 2

D 2
	if (stat(fn1, &stb) < 0)
		return(-1);
	s1 = stb.st_size;
	if (stat(fn2, &stb) < 0)
		return(-1);
	return(s1 - stb.st_size);
E 2
I 2
	if (stat(fn, &stb) < 0)
		return(0);
	return(stb.st_size);
E 2
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

I 2
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

E 2
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

/* End %M% */
E 1
