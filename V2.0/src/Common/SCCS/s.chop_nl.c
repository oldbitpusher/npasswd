h57811
s 00004/00008/00062
d D 1.4 98/11/17 16:48:38 clyde 4 3
c Fix function comments
e
s 00044/00000/00026
d D 1.3 98/11/17 15:43:35 clyde 3 2
c Add copyright notice
e
s 00005/00001/00021
d D 1.2 96/08/13 13:18:50 clyde 2 1
c Add comments
e
s 00022/00000/00000
d D 1.1 96/08/07 15:18:23 clyde 1 0
c date and time created 96/08/07 15:18:23 by clyde
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

D 4
/*
E 3
I 2
 * chop_nl
 *	Replace newline with null character
 * Usage
 *	(void) chop_nl(string);
E 2
 */

E 4
#include "compatibility.h"

#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu) %P%";
#endif

/*
D 4
 *	chop_nl - Chop off (first) newline in string
E 4
I 4
 * chop_nl
 *	Zap first newline in string
 * Usage
 *	(void) chop_nl(string);
E 4
 */
void
chop_nl(str)
D 2
	char	*str;		/* String to copy */
E 2
I 2
	char	*str;
E 2
{
	char	*nl;	/* Temp */

	if (nl = strchr(str, '\n'))
		*nl = 0;
}
/* End %M% */
E 1
