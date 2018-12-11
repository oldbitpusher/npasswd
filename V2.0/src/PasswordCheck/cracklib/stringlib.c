/*
 * This program is copyright Alec Muffett 1993. The author disclaims all 
 * responsibility or liability with respect to it's usage or its effect 
 * upon hardware or computer systems, and maintains copyright as set out 
 * in the "LICENCE" document which accompanies distributions of Crack v4.0 
 * and upwards.
 */
/*
 * Modifications made by Clyde Hoover
 *	Academic Computing & Instructional Technologies Services
 *	University of Texas at Austin
 *
 * Title to copyright to original version of this software shall at all times
 * remain with Alec Muffett.
 *
 * Title to copyright to U. T. Austin modificiations to this software and 
 * its associated documentation shall at all times remain with U. T. Austin.
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
 * No right is granted to use in advertising, publicity
 * or otherwise any trademark, service mark, or the name of U. T. Austin.
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

#include "packer.h"

#ifndef	lint
static char vers_id[] = "stringlib.c : v2.3p2 Alec Muffett 18 May 1993";
static char ut_id[] = "@(#)stringlib.c	1.2 04/09/98 (cc.utexas.edu)";
#endif

/*
 * Chop - remove and return the last character from <string>
 */
char
Chop(string)
    register char *string;
{
    register char c;
    register char *ptr;
    c = '\0';

    for (ptr = string; *ptr; ptr++);
    if (ptr != string)
    {
	c = *(--ptr);
	*ptr = '\0';
    }
    return (c);
}

/*
 * Trim - remove trailing whitespace from <string>
 */
char *
Trim(string)
    register char *string;
{
    register char *ptr;
    for (ptr = string; *ptr; ptr++);

    while ((--ptr >= string) && isspace(*ptr));

    *(++ptr) = '\0';

    return (ptr);
}

/*
 * Clone - make a copy of <string>
 */
char *
Clone(string)
    char *string;
{
    register char *retval;
    retval = (char *) malloc(strlen(string) + 1);
    if (retval)
    {
	(void) strcpy(retval, string);
    }
    return (retval);
}
/* End stringlib.c */
