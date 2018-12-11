h21630
s 00010/00010/00134
d D 1.7 98/09/22 11:00:35 clyde 8 7
c Rename intNN to c_intNN to avoid type conflicts with Digital UNIX 4.0d
e
s 00095/00015/00049
d D 1.6 98/04/09 16:41:28 clyde 7 6
c 1. Add UT copyright message
c 2. Remove NPASSWD_LIB define
c 3. Add declarations for cracklib routines
e
s 00000/00003/00064
d D 1.5 98/04/07 13:11:50 clyde 6 5
c Move some macros to rules.c where they are referenced
e
s 00004/00000/00063
d D 1.4 98/04/07 10:11:50 clyde 5 4
c Add FascistNpasswd()
e
s 00001/00000/00062
d D 1.3 98/04/02 16:57:19 clyde 4 3
c Add PWioError
e
s 00005/00001/00057
d D 1.2 98/04/02 10:20:35 clyde 3 1
c Add mods from cracklib 2.7
e
s 00004/00000/00058
d R 1.2 93/06/25 14:25:11 clyde 2 1
c Add field 'canfree' to PWDICT
e
s 00058/00000/00000
d D 1.1 93/06/25 14:18:46 clyde 1 0
c date and time created 93/06/25 14:18:46 by clyde
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
I 3
D 7
/* %W% %G% (cc.utexas.edu) */
E 7
I 7
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
E 7
E 3

I 7
/*
 * %W% %G% (cc.utexas.edu)
 */

E 7
#include <stdio.h>
I 3
#include <ctype.h>
E 3

I 7
#ifndef NUMWORDS
# define NUMWORDS 	16
#endif
#define MAXWORDLEN	32
#define MAXBLOCKLEN 	(MAXWORDLEN * NUMWORDS)
E 7
D 3
#define STRINGSIZE	256
E 3
I 3
#define STRINGSIZE	1024
#define	TRUNCSTRINGSIZE	(STRINGSIZE/4)
E 3

D 8
typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned long int int32;
E 8
I 8
typedef unsigned char c_int8;
typedef unsigned short int c_int16;
typedef unsigned long int c_int32;
E 8
D 7
#ifndef NUMWORDS
#define NUMWORDS 	16
#endif
#define MAXWORDLEN	32
#define MAXBLOCKLEN 	(MAXWORDLEN * NUMWORDS)
E 7

struct pi_header
{
D 8
    int32 pih_magic;
    int32 pih_numwords;
    int16 pih_blocklen;
    int16 pih_pad;
E 8
I 8
    c_int32 pih_magic;
    c_int32 pih_numwords;
    c_int16 pih_blocklen;
    c_int16 pih_pad;
E 8
};

typedef struct
{
    FILE *ifp;
    FILE *dfp;
    FILE *wfp;

D 8
    int32 flags;
E 8
I 8
    c_int32 flags;
E 8
#define PFOR_WRITE	0x0001
#define PFOR_FLUSH	0x0002
#define PFOR_USEHWMS	0x0004

D 8
    int32 hwms[256];
E 8
I 8
    c_int32 hwms[256];
E 8
D 7

E 7
    struct pi_header header;
D 7

E 7
    int count;
    char data[NUMWORDS][MAXWORDLEN];
} PWDICT;

#define PW_WORDS(x) ((x)->header.pih_numwords)
#define PIH_MAGIC 0x70775631

D 7
extern PWDICT *PWOpen();
extern char *Mangle();
I 5
extern char *FascistGecos();
E 5
extern char *FascistCheck();
E 7
I 7
/*
 * Cracklib data structures that others need to see
 */
E 7
I 4
extern char PWioError[];
I 5
D 7
#ifdef	NPASSWD_LIB
extern char *FascistNpasswd();
#endif
E 7
E 5
E 4

I 7
/*
 * Cracklib routines to export
 */
extern PWDICT	*PWOpen();
extern int	PWClose();
extern int	PutPW();
extern char	*GetPW();
D 8
extern int32	FindPW();
E 8
I 8
extern c_int32	FindPW();
E 8

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

E 7
D 6
#define CRACK_TOLOWER(a) 	(isupper(a)?tolower(a):(a)) 
#define CRACK_TOUPPER(a) 	(islower(a)?toupper(a):(a)) 
#define STRCMP(a,b)		strcmp((a),(b))
E 6
I 3
/* End %M% */
E 3
E 1
