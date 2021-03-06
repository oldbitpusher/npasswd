h35490
s 00061/00003/00032
d D 1.2 98/11/17 15:49:26 clyde 2 1
c Add copyright notice, function descriptions
e
s 00035/00000/00000
d D 1.1 96/08/07 15:19:18 clyde 1 0
c date and time created 96/08/07 15:19:18 by clyde
e
u
U
f e 0
t
T
I 1
/*
I 2
 * Copyright 1998, The University of Texas at Austin ("U. T. Austin").
 * All rights reserved.
E 2
 *
D 2
 *	instring - check one string for occurance of another
E 2
I 2
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
E 2
 */

#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu)";
#endif

I 2
/*
 * instring
 *	Check one string for occurance of another
 * Usage:
 *	i = instring(in, for);
 *	i = instringcase(in, for);
 * Returns:
 *	1 if string <for> located in string <in>
 *	0 if not
 */
E 2
instring(searchin, searchfor)
	char	*searchin,		/* String to search in */
		*searchfor;		/* String to search for */
{
D 2
	int	l;
E 2
I 2
	int	l;		/* Temp */
E 2

	for (l = strlen(searchfor); *searchin; searchin++) {
		if (strncmp(searchin, searchfor, l) == 0)
			return(1);
	}
	return(0);
}

I 2
/*
 * instringcase
 *	Check one string for occurance of another (case insensitive)
 * Usage:
 *	i = instringcase(in, for);
 * Returns:
 *	1 if string <for> located in string <in>
 *	0 if not
 */
E 2
instringcase(searchin, searchfor)
	char	*searchin,		/* String to search in */
		*searchfor;		/* String to search for */
{
D 2
	int	l;
E 2
I 2
	int	l;		/* Temp */
E 2

	for (l = strlen(searchfor); *searchin; searchin++) {
		if (strncasecmp(searchin, searchfor, l) == 0)
			return(1);
	}
	return(0);
}
/* End %M% */
E 1
