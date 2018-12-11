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
#include "compatibility.h"

#ifndef lint
static char sccsid[] = "$Id: chop_nl.c,v 1.5 2002/10/02 16:07:38 clyde Exp $";
#endif

/*
 * chop_nl
 *	Zap first newline in string
 * Usage
 *	(void) chop_nl(string);
 */
void
chop_nl(str)
	char	*str;
{
	char	*nl;	/* Temp */

	if (nl = strchr(str, '\n'))
		*nl = 0;
}
/* End $RCSfile: chop_nl.c,v $ */
