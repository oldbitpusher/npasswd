h62240
s 00001/00001/00100
d D 1.4 98/08/17 14:28:42 clyde 4 3
c Add third arg to FascistNpasswd() call
e
s 00003/00002/00098
d D 1.3 98/04/14 12:59:01 clyde 3 2
c Change dictionary handling (changed arg 1 of FascistNpasswd)
e
s 00045/00000/00055
d D 1.2 98/04/09 16:50:02 clyde 2 1
c Add UT copyright notice
e
s 00055/00000/00000
d D 1.1 98/04/07 14:37:41 clyde 1 0
c date and time created 98/04/07 14:37:41 by clyde
e
u
U
f e 0
t
T
I 1
/*
 * This program is copyright Alec Muffett 1993. The author disclaims all 
 * responsibility or liability with respect to it's usage or its effect 
 * upon hardware or computer systems, and maintains copyright as set out 
 * in the "LICENCE" document which accompanies distributions of Crack v4.0 
 * and upwards.
 */
I 2
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
E 2

/*
 * Test routine FacistNpasswd()
 */

static char ut_id[] = "%W% %G% (cc.utexas.edu)";

#include "packer.h"

int
main (argc, argv)
	int	argc;
	char	**argv;
{
    char buffer[STRINGSIZE];
D 3
    PWDICT	*plist[8];
E 3
I 3
    char	*plist[8];
E 3
    int		pctr = 0;

    for (argv++; *argv; argv++) {
	PWDICT	*p;
	if ((p = PWOpen(*argv, "r")) == 0) {
		printf("Cannot PWOpen dictionary %s\n", *argv);
		printf("Error %s\n", PWioError);
		exit(1);
	}
D 3
	plist[pctr++] = p;
E 3
I 3
	(void) PWClose(p);
	plist[pctr++] = *argv;
E 3
	plist[pctr] = 0;
        if (pctr == 7)
		break;
    }
	
    printf("enter potential passwords, one per line...\n");

    while (fgets (buffer, STRINGSIZE, stdin))
    {
    	char *val;
 
	Chop(buffer);

D 4
	if (val = FascistNpasswd(plist, buffer))
E 4
I 4
	if (val = FascistNpasswd(plist, buffer, 0))
E 4
		printf ("%s: %s\n", buffer, val);
	else
		printf ("%s: ok\n", buffer);
    }

    return (0);
}
/* End %M% */
E 1
