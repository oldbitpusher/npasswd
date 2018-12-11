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
 *	A collection of file utility routines used by npasswd
 */

#include "npasswd.h"

#ifndef lint
static char sccsid[] = "$Id: file_util.c,v 1.4 2002/10/02 16:11:38 clyde Exp $ (cc.utexas.edu) %P%";
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

/* End $RCSfile: file_util.c,v $ */
