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

/*
 * @(#)packer.h	1.7 9/22/98 (cc.utexas.edu)
 */

#include <stdio.h>
#include <ctype.h>

#ifndef NUMWORDS
# define NUMWORDS 	16
#endif
#define MAXWORDLEN	32
#define MAXBLOCKLEN 	(MAXWORDLEN * NUMWORDS)
#define STRINGSIZE	1024
#define	TRUNCSTRINGSIZE	(STRINGSIZE/4)

typedef unsigned char c_int8;
typedef unsigned short int c_int16;
typedef unsigned long int c_int32;

struct pi_header
{
    c_int32 pih_magic;
    c_int32 pih_numwords;
    c_int16 pih_blocklen;
    c_int16 pih_pad;
};

typedef struct
{
    FILE *ifp;
    FILE *dfp;
    FILE *wfp;

    c_int32 flags;
#define PFOR_WRITE	0x0001
#define PFOR_FLUSH	0x0002
#define PFOR_USEHWMS	0x0004

    c_int32 hwms[256];
    struct pi_header header;
    int count;
    char data[NUMWORDS][MAXWORDLEN];
} PWDICT;

#define PW_WORDS(x) ((x)->header.pih_numwords)
#define PIH_MAGIC 0x70775631

/*
 * Cracklib data structures that others need to see
 */
extern char PWioError[];

/*
 * Cracklib routines to export
 */
extern PWDICT	*PWOpen();
extern int	PWClose();
extern int	PutPW();
extern char	*GetPW();
extern c_int32	FindPW();

/*
 * Password "cracking" routines
 */
extern char	*FascistGecos();
extern char	*FascistLook();
extern char	*FascistNpasswd();
extern char	*FascistCheck();
extern int	GTry();

/*
 * String manipulation routines
 */
extern char	*Mangle();
extern char	*Trim();
extern char	*Clone();
extern char	Chop();
extern char	*Uppercase();
extern char	*Lowercase();
extern char	*Reverse();
extern char	*Capitalise();
extern char	*Pluralise();
extern char	*Substitute();

/*
 * Other routines of interest
 */
extern int	PMatch();
extern char	*Mangle();

/* End packer.h */
