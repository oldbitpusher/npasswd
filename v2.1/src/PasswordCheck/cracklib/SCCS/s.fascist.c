h12830
s 00003/00004/00977
d D 2.13 99/02/01 13:54:05 clyde 22 21
c Enable CRACKLIB_ANAL
e
s 00001/00001/00980
d D 2.12 98/11/13 14:45:32 clyde 21 20
c Add third arg to call of PMatch()
e
s 00002/00002/00979
d D 2.11 98/09/22 11:01:15 clyde 20 19
c Rename intNN to c_intNN to avoid type conflicts with Digital UNIX 4.0d
e
s 00012/00002/00969
d D 2.10 98/08/17 14:52:29 clyde 19 18
c 1. Make verbose messages more messy
c 2. Disable some deconstrutors to allow more passwords to pass
e
s 00015/00011/00956
d D 2.9 98/08/17 14:28:20 clyde 18 17
c 1. Add verbose arg to FascistNpasswd()
c 2. Change dictionary found message 
c 3. Include actual word in "found in dict" message
e
s 00006/00001/00961
d D 2.8 98/06/30 15:25:28 clyde 17 16
c Return error message if no dictionaries found by FacistNpasswd()
e
s 00009/00009/00953
d D 2.7 98/06/26 14:17:43 clyde 16 15
c Change %-16s to '%s' (don't be so anal about overflows)
e
s 00001/00001/00961
d D 2.6 98/06/26 14:06:39 clyde 15 14
c Fix call to PWOpen() in FascistNpasswd()
e
s 00016/00005/00946
d D 2.5 98/04/21 15:23:50 clyde 14 13
c 1. Add explanitory comments
c 2. Add to rawtext constructor rules list
e
s 00017/00005/00934
d D 2.4 98/04/14 12:59:31 clyde 13 12
c Change arg1 from (PWDICT **) to (char **)
e
s 00086/00056/00853
d D 2.3 98/04/09 16:48:00 clyde 12 11
c 1. Add UT copyright notice
c 2. Add comments to each routine
c 3. Remove defines & declartions duplicated elsewhere
c 4. Remove NPASSWD_LIB #ifdefs
c 5. Change dictionary lookup loop in FascistNpasswd()
e
s 00018/00000/00891
d D 2.2 98/04/07 13:28:58 clyde 11 10
c Make UT routine change #ifdef NPASSWD_LIB
e
s 00085/00029/00806
d D 2.1 98/04/07 10:15:30 clyde 10 9
c 1. Restore FascistLook() to nearly orignal condition
c 2. Add FascistNpasswd() to do exactly what needed
e
s 00531/00191/00304
d D 2.0 98/04/03 13:27:09 clyde 9 8
c Major rework:
c 1. Merge in cracklib 2.7 mods
c 2. Change debugging print ifdef control
c 3. Enable FascistGecos, add passwd info argument
c 4. Add void casts to make lint happier
c 5. Add a couple of local checks to FascistGecos
c 6. Change use of PWOpen() and PWClose() per changes to packlib.c
e
s 00004/00003/00491
d D 1.8 98/03/26 11:14:07 clyde 8 7
c Change handling of 'lastpath'
e
s 00008/00005/00486
d D 1.7 97/09/23 12:24:40 clyde 7 6
c Finally fix the segfault problem
e
s 00004/00001/00487
d D 1.6 97/05/02 13:20:28 clyde 6 5
c Close dictionary after looking in it
e
s 00005/00001/00483
d D 1.5 96/12/05 12:34:08 clyde 5 4
c Disable FacistGecos() if IN_CHECKPASSWORD defined
e
s 00014/00009/00470
d D 1.4 93/12/23 14:39:55 clyde 4 3
c 1. Don't exit if IN_CHECKPASSWORD defined
c 2. Localize return messages
e
s 00033/00018/00446
d D 1.3 93/06/25 16:38:43 clyde 3 2
c 1. Improve error message for dictionary open failure.
c 2. Make a 'catalog' of return messages.
e
s 00012/00004/00452
d D 1.2 93/06/25 14:54:10 clyde 2 1
c 1. Make return messages consistent
c 2. Americanize
e
s 00456/00000/00000
d D 1.1 93/06/25 09:23:30 clyde 1 0
c date and time created 93/06/25 09:23:30 by clyde
e
u
U
f e 0
t
T
I 1
/*
D 9
 * This program is copyright Alec Muffett 1993. The author disclaims all 
 * responsibility or liability with respect to it's usage or its effect 
 * upon hardware or computer systems, and maintains copyright as set out 
 * in the "LICENCE" document which accompanies distributions of Crack v4.0 
E 9
I 9
 * This program is copyright Alec Muffett 1993. The author disclaims all
 * responsibility or liability with respect to it's usage or its effect
 * upon hardware or computer systems, and maintains copyright as set out
 * in the "LICENCE" document which accompanies distributions of Crack v4.0
E 9
 * and upwards.
 */
I 12
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
E 12

I 12
#ifndef	lint
E 12
D 9
static char vers_id[] = "fascist.c : v2.3p2 Alec Muffett 18 May 1993";
E 9
I 2
static char ut_id[] = "%W% %G% (cc.utexas.edu)";
I 9
static char vers_id[] = "fascist.c : v2.3p3 Alec Muffett 14 dec 1997";
I 12
#endif
E 12
E 9
E 2

D 12
#include "packer.h"
E 12
D 9
#include <ctype.h>
E 9
#include <sys/types.h>
I 8
D 9
#include <sys/param.h>
E 9
E 8
#include <pwd.h>
I 12
#include "packer.h"
E 12

#define ISSKIP(x) (isspace(x) || ispunct(x))

D 9
#define MINDIFF	5
E 9
I 9
D 12
#define MINDIFF 5
E 9
#define MINLEN 6
#define MAXSTEP 4
E 12
I 12
#define MINDIFF 5		/* How many different chars required */
#define MINLEN 6		/* Minimum password length */
#define MAXSTEP 4		/* How far apart replicated chars must be */
E 12

I 14
/*
 * Look in rules.c to find out how these rules work
 */
E 14
I 9
D 12
#undef CRACKLIB_DEBUG
#undef CRACKLIB_DEBUG2

extern char *Reverse();
extern char *Lowercase();

E 12
E 9
static char *r_destructors[] = {
D 9
    ":",			/* noop - must do this to test raw word. */
E 9
I 9
    ":",                        /* noop - must do this to test raw word. */
E 9

D 9
    "[",			/* trimming leading/trailing junk */
E 9
I 9
#ifdef CRACKLIB_DEBUG2
    (char *) 0,
#endif
I 19
/*
D 22
 * I disabled these deconstructors because they cause rejection of
 * passwords which *include* dictionary words but have leading or trailing
 * junk.  I do not see how Crack could guess them.
 * 	-CWH 8/98
E 22
I 22
 * Disable these deconstructors if you think too many passwords are
 * being rejected.
E 22
 */
I 22
#define	CRACKLIB_ANAL
E 22
#ifdef	CRACKLIB_ANAL
E 19
D 12

E 12
    "[",                        /* trimming leading/trailing junk */
E 9
    "]",
    "[[",
    "]]",
    "[[[",
    "]]]",
I 19
#endif
E 19

D 9
    "/?p@?p",			/* purging out punctuation/symbols/junk */
E 9
I 9
    "/?p@?p",                   /* purging out punctuation/symbols/junk */
E 9
    "/?s@?s",
    "/?X@?X",

D 9
    "/$s$s",			/* transmogrifying "$" back into "s", etc... */
    "/4s4a",
    "/2s2a",
    "/3s3e",
    "/0s0o",
    "/1s1i",
    "/4s4h",
    "/1s1l",
    "/$s$s/1s1l",
    "/2s2a/3s3e",
    "/0s0o/4s4h",
    "/1s1l/4s4a",
    "/2s2a/4s4h",
    "/$s$s/3s3e",
E 9
I 9
    /* attempt reverse engineering of password strings */
I 14
    /* These rules are taken from Crack */
E 14

    "/$s$s",
E 9
    "/$s$s/0s0o",
D 9
    "/1s1i/4s4a",
E 9
I 9
    "/$s$s/0s0o/2s2a",
    "/$s$s/0s0o/2s2a/3s3e",
    "/$s$s/0s0o/2s2a/3s3e/5s5s",
    "/$s$s/0s0o/2s2a/3s3e/5s5s/1s1i",
    "/$s$s/0s0o/2s2a/3s3e/5s5s/1s1l",
    "/$s$s/0s0o/2s2a/3s3e/5s5s/1s1i/4s4a",
    "/$s$s/0s0o/2s2a/3s3e/5s5s/1s1i/4s4h",
    "/$s$s/0s0o/2s2a/3s3e/5s5s/1s1l/4s4a",
    "/$s$s/0s0o/2s2a/3s3e/5s5s/1s1l/4s4h",
    "/$s$s/0s0o/2s2a/3s3e/5s5s/4s4a",
    "/$s$s/0s0o/2s2a/3s3e/5s5s/4s4h",
    "/$s$s/0s0o/2s2a/3s3e/5s5s/4s4a",
    "/$s$s/0s0o/2s2a/3s3e/5s5s/4s4h",
    "/$s$s/0s0o/2s2a/3s3e/1s1i",
    "/$s$s/0s0o/2s2a/3s3e/1s1l",
    "/$s$s/0s0o/2s2a/3s3e/1s1i/4s4a",
    "/$s$s/0s0o/2s2a/3s3e/1s1i/4s4h",
    "/$s$s/0s0o/2s2a/3s3e/1s1l/4s4a",
    "/$s$s/0s0o/2s2a/3s3e/1s1l/4s4h",
    "/$s$s/0s0o/2s2a/3s3e/4s4a",
    "/$s$s/0s0o/2s2a/3s3e/4s4h",
    "/$s$s/0s0o/2s2a/3s3e/4s4a",
    "/$s$s/0s0o/2s2a/3s3e/4s4h",
    "/$s$s/0s0o/2s2a/5s5s",
    "/$s$s/0s0o/2s2a/5s5s/1s1i",
    "/$s$s/0s0o/2s2a/5s5s/1s1l",
    "/$s$s/0s0o/2s2a/5s5s/1s1i/4s4a",
    "/$s$s/0s0o/2s2a/5s5s/1s1i/4s4h",
    "/$s$s/0s0o/2s2a/5s5s/1s1l/4s4a",
    "/$s$s/0s0o/2s2a/5s5s/1s1l/4s4h",
    "/$s$s/0s0o/2s2a/5s5s/4s4a",
    "/$s$s/0s0o/2s2a/5s5s/4s4h",
    "/$s$s/0s0o/2s2a/5s5s/4s4a",
    "/$s$s/0s0o/2s2a/5s5s/4s4h",
    "/$s$s/0s0o/2s2a/1s1i",
    "/$s$s/0s0o/2s2a/1s1l",
    "/$s$s/0s0o/2s2a/1s1i/4s4a",
    "/$s$s/0s0o/2s2a/1s1i/4s4h",
    "/$s$s/0s0o/2s2a/1s1l/4s4a",
    "/$s$s/0s0o/2s2a/1s1l/4s4h",
    "/$s$s/0s0o/2s2a/4s4a",
    "/$s$s/0s0o/2s2a/4s4h",
    "/$s$s/0s0o/2s2a/4s4a",
    "/$s$s/0s0o/2s2a/4s4h",
    "/$s$s/0s0o/3s3e",
    "/$s$s/0s0o/3s3e/5s5s",
    "/$s$s/0s0o/3s3e/5s5s/1s1i",
    "/$s$s/0s0o/3s3e/5s5s/1s1l",
    "/$s$s/0s0o/3s3e/5s5s/1s1i/4s4a",
    "/$s$s/0s0o/3s3e/5s5s/1s1i/4s4h",
    "/$s$s/0s0o/3s3e/5s5s/1s1l/4s4a",
    "/$s$s/0s0o/3s3e/5s5s/1s1l/4s4h",
    "/$s$s/0s0o/3s3e/5s5s/4s4a",
    "/$s$s/0s0o/3s3e/5s5s/4s4h",
    "/$s$s/0s0o/3s3e/5s5s/4s4a",
    "/$s$s/0s0o/3s3e/5s5s/4s4h",
    "/$s$s/0s0o/3s3e/1s1i",
    "/$s$s/0s0o/3s3e/1s1l",
    "/$s$s/0s0o/3s3e/1s1i/4s4a",
    "/$s$s/0s0o/3s3e/1s1i/4s4h",
    "/$s$s/0s0o/3s3e/1s1l/4s4a",
    "/$s$s/0s0o/3s3e/1s1l/4s4h",
    "/$s$s/0s0o/3s3e/4s4a",
    "/$s$s/0s0o/3s3e/4s4h",
    "/$s$s/0s0o/3s3e/4s4a",
    "/$s$s/0s0o/3s3e/4s4h",
    "/$s$s/0s0o/5s5s",
    "/$s$s/0s0o/5s5s/1s1i",
    "/$s$s/0s0o/5s5s/1s1l",
    "/$s$s/0s0o/5s5s/1s1i/4s4a",
    "/$s$s/0s0o/5s5s/1s1i/4s4h",
    "/$s$s/0s0o/5s5s/1s1l/4s4a",
    "/$s$s/0s0o/5s5s/1s1l/4s4h",
    "/$s$s/0s0o/5s5s/4s4a",
    "/$s$s/0s0o/5s5s/4s4h",
    "/$s$s/0s0o/5s5s/4s4a",
    "/$s$s/0s0o/5s5s/4s4h",
    "/$s$s/0s0o/1s1i",
    "/$s$s/0s0o/1s1l",
    "/$s$s/0s0o/1s1i/4s4a",
    "/$s$s/0s0o/1s1i/4s4h",
    "/$s$s/0s0o/1s1l/4s4a",
    "/$s$s/0s0o/1s1l/4s4h",
    "/$s$s/0s0o/4s4a",
    "/$s$s/0s0o/4s4h",
    "/$s$s/0s0o/4s4a",
    "/$s$s/0s0o/4s4h",
E 9
    "/$s$s/2s2a",
I 9
    "/$s$s/2s2a/3s3e",
    "/$s$s/2s2a/3s3e/5s5s",
    "/$s$s/2s2a/3s3e/5s5s/1s1i",
    "/$s$s/2s2a/3s3e/5s5s/1s1l",
    "/$s$s/2s2a/3s3e/5s5s/1s1i/4s4a",
    "/$s$s/2s2a/3s3e/5s5s/1s1i/4s4h",
    "/$s$s/2s2a/3s3e/5s5s/1s1l/4s4a",
    "/$s$s/2s2a/3s3e/5s5s/1s1l/4s4h",
    "/$s$s/2s2a/3s3e/5s5s/4s4a",
    "/$s$s/2s2a/3s3e/5s5s/4s4h",
    "/$s$s/2s2a/3s3e/5s5s/4s4a",
    "/$s$s/2s2a/3s3e/5s5s/4s4h",
    "/$s$s/2s2a/3s3e/1s1i",
    "/$s$s/2s2a/3s3e/1s1l",
    "/$s$s/2s2a/3s3e/1s1i/4s4a",
    "/$s$s/2s2a/3s3e/1s1i/4s4h",
    "/$s$s/2s2a/3s3e/1s1l/4s4a",
    "/$s$s/2s2a/3s3e/1s1l/4s4h",
    "/$s$s/2s2a/3s3e/4s4a",
    "/$s$s/2s2a/3s3e/4s4h",
    "/$s$s/2s2a/3s3e/4s4a",
    "/$s$s/2s2a/3s3e/4s4h",
    "/$s$s/2s2a/5s5s",
    "/$s$s/2s2a/5s5s/1s1i",
    "/$s$s/2s2a/5s5s/1s1l",
    "/$s$s/2s2a/5s5s/1s1i/4s4a",
    "/$s$s/2s2a/5s5s/1s1i/4s4h",
    "/$s$s/2s2a/5s5s/1s1l/4s4a",
    "/$s$s/2s2a/5s5s/1s1l/4s4h",
    "/$s$s/2s2a/5s5s/4s4a",
    "/$s$s/2s2a/5s5s/4s4h",
    "/$s$s/2s2a/5s5s/4s4a",
    "/$s$s/2s2a/5s5s/4s4h",
    "/$s$s/2s2a/1s1i",
    "/$s$s/2s2a/1s1l",
    "/$s$s/2s2a/1s1i/4s4a",
    "/$s$s/2s2a/1s1i/4s4h",
    "/$s$s/2s2a/1s1l/4s4a",
    "/$s$s/2s2a/1s1l/4s4h",
    "/$s$s/2s2a/4s4a",
    "/$s$s/2s2a/4s4h",
    "/$s$s/2s2a/4s4a",
    "/$s$s/2s2a/4s4h",
    "/$s$s/3s3e",
    "/$s$s/3s3e/5s5s",
    "/$s$s/3s3e/5s5s/1s1i",
    "/$s$s/3s3e/5s5s/1s1l",
    "/$s$s/3s3e/5s5s/1s1i/4s4a",
    "/$s$s/3s3e/5s5s/1s1i/4s4h",
    "/$s$s/3s3e/5s5s/1s1l/4s4a",
    "/$s$s/3s3e/5s5s/1s1l/4s4h",
    "/$s$s/3s3e/5s5s/4s4a",
    "/$s$s/3s3e/5s5s/4s4h",
    "/$s$s/3s3e/5s5s/4s4a",
    "/$s$s/3s3e/5s5s/4s4h",
    "/$s$s/3s3e/1s1i",
    "/$s$s/3s3e/1s1l",
    "/$s$s/3s3e/1s1i/4s4a",
    "/$s$s/3s3e/1s1i/4s4h",
    "/$s$s/3s3e/1s1l/4s4a",
    "/$s$s/3s3e/1s1l/4s4h",
    "/$s$s/3s3e/4s4a",
    "/$s$s/3s3e/4s4h",
    "/$s$s/3s3e/4s4a",
    "/$s$s/3s3e/4s4h",
    "/$s$s/5s5s",
    "/$s$s/5s5s/1s1i",
    "/$s$s/5s5s/1s1l",
    "/$s$s/5s5s/1s1i/4s4a",
    "/$s$s/5s5s/1s1i/4s4h",
    "/$s$s/5s5s/1s1l/4s4a",
    "/$s$s/5s5s/1s1l/4s4h",
    "/$s$s/5s5s/4s4a",
    "/$s$s/5s5s/4s4h",
    "/$s$s/5s5s/4s4a",
    "/$s$s/5s5s/4s4h",
    "/$s$s/1s1i",
    "/$s$s/1s1l",
    "/$s$s/1s1i/4s4a",
    "/$s$s/1s1i/4s4h",
    "/$s$s/1s1l/4s4a",
    "/$s$s/1s1l/4s4h",
E 9
    "/$s$s/4s4a",
D 9
    "/0s0o/1s1l",
    "/3s3e/4s4h",
    "/1s1l/4s4h",
E 9
    "/$s$s/4s4h",
D 9
    "/1s1i/4s4h",
    "/2s2a/4s4a",
    "/$s$s/1s1i",
    "/0s0o/1s1i",
    "/1s1i/2s2a",
    "/1s1i/3s3e",
    "/0s0o/4s4a",
    "/1s1l/3s3e",
    "/3s3e/4s4a",
E 9
I 9
    "/$s$s/4s4a",
    "/$s$s/4s4h",
    "/0s0o",
E 9
    "/0s0o/2s2a",
I 9
    "/0s0o/2s2a/3s3e",
    "/0s0o/2s2a/3s3e/5s5s",
    "/0s0o/2s2a/3s3e/5s5s/1s1i",
    "/0s0o/2s2a/3s3e/5s5s/1s1l",
    "/0s0o/2s2a/3s3e/5s5s/1s1i/4s4a",
    "/0s0o/2s2a/3s3e/5s5s/1s1i/4s4h",
    "/0s0o/2s2a/3s3e/5s5s/1s1l/4s4a",
    "/0s0o/2s2a/3s3e/5s5s/1s1l/4s4h",
    "/0s0o/2s2a/3s3e/5s5s/4s4a",
    "/0s0o/2s2a/3s3e/5s5s/4s4h",
    "/0s0o/2s2a/3s3e/5s5s/4s4a",
    "/0s0o/2s2a/3s3e/5s5s/4s4h",
    "/0s0o/2s2a/3s3e/1s1i",
    "/0s0o/2s2a/3s3e/1s1l",
    "/0s0o/2s2a/3s3e/1s1i/4s4a",
    "/0s0o/2s2a/3s3e/1s1i/4s4h",
    "/0s0o/2s2a/3s3e/1s1l/4s4a",
    "/0s0o/2s2a/3s3e/1s1l/4s4h",
    "/0s0o/2s2a/3s3e/4s4a",
    "/0s0o/2s2a/3s3e/4s4h",
    "/0s0o/2s2a/3s3e/4s4a",
    "/0s0o/2s2a/3s3e/4s4h",
    "/0s0o/2s2a/5s5s",
    "/0s0o/2s2a/5s5s/1s1i",
    "/0s0o/2s2a/5s5s/1s1l",
    "/0s0o/2s2a/5s5s/1s1i/4s4a",
    "/0s0o/2s2a/5s5s/1s1i/4s4h",
    "/0s0o/2s2a/5s5s/1s1l/4s4a",
    "/0s0o/2s2a/5s5s/1s1l/4s4h",
    "/0s0o/2s2a/5s5s/4s4a",
    "/0s0o/2s2a/5s5s/4s4h",
    "/0s0o/2s2a/5s5s/4s4a",
    "/0s0o/2s2a/5s5s/4s4h",
    "/0s0o/2s2a/1s1i",
    "/0s0o/2s2a/1s1l",
    "/0s0o/2s2a/1s1i/4s4a",
    "/0s0o/2s2a/1s1i/4s4h",
    "/0s0o/2s2a/1s1l/4s4a",
    "/0s0o/2s2a/1s1l/4s4h",
    "/0s0o/2s2a/4s4a",
    "/0s0o/2s2a/4s4h",
    "/0s0o/2s2a/4s4a",
    "/0s0o/2s2a/4s4h",
E 9
    "/0s0o/3s3e",
D 9
    "/1s1l/2s2a",
    "/0s0o/1s1l/2s2a",
E 9
I 9
    "/0s0o/3s3e/5s5s",
    "/0s0o/3s3e/5s5s/1s1i",
    "/0s0o/3s3e/5s5s/1s1l",
    "/0s0o/3s3e/5s5s/1s1i/4s4a",
    "/0s0o/3s3e/5s5s/1s1i/4s4h",
    "/0s0o/3s3e/5s5s/1s1l/4s4a",
    "/0s0o/3s3e/5s5s/1s1l/4s4h",
    "/0s0o/3s3e/5s5s/4s4a",
    "/0s0o/3s3e/5s5s/4s4h",
    "/0s0o/3s3e/5s5s/4s4a",
    "/0s0o/3s3e/5s5s/4s4h",
    "/0s0o/3s3e/1s1i",
    "/0s0o/3s3e/1s1l",
    "/0s0o/3s3e/1s1i/4s4a",
    "/0s0o/3s3e/1s1i/4s4h",
    "/0s0o/3s3e/1s1l/4s4a",
    "/0s0o/3s3e/1s1l/4s4h",
    "/0s0o/3s3e/4s4a",
    "/0s0o/3s3e/4s4h",
    "/0s0o/3s3e/4s4a",
    "/0s0o/3s3e/4s4h",
    "/0s0o/5s5s",
    "/0s0o/5s5s/1s1i",
    "/0s0o/5s5s/1s1l",
    "/0s0o/5s5s/1s1i/4s4a",
    "/0s0o/5s5s/1s1i/4s4h",
    "/0s0o/5s5s/1s1l/4s4a",
    "/0s0o/5s5s/1s1l/4s4h",
    "/0s0o/5s5s/4s4a",
    "/0s0o/5s5s/4s4h",
    "/0s0o/5s5s/4s4a",
    "/0s0o/5s5s/4s4h",
    "/0s0o/1s1i",
    "/0s0o/1s1l",
    "/0s0o/1s1i/4s4a",
E 9
    "/0s0o/1s1i/4s4h",
D 9
    "/1s1l/2s2a/4s4a",
    "/2s2a/3s3e/4s4a",
    "/0s0o/1s1i/2s2a",
    "/1s1i/2s2a/3s3e",
E 9
    "/0s0o/1s1l/4s4a",
D 9
    "/1s1l/2s2a/4s4h",
    "/$s$s/0s0o/1s1l",
    "/$s$s/0s0o/2s2a",
    "/0s0o/1s1i/3s3e",
    "/$s$s/0s0o/3s3e",
    "/1s1i/2s2a/4s4a",
    "/$s$s/0s0o/4s4a",
    "/$s$s/0s0o/4s4h",
E 9
    "/0s0o/1s1l/4s4h",
D 9
    "/1s1i/2s2a/4s4h",
    "/0s0o/1s1l/3s3e",
    "/$s$s/0s0o/1s1i",
    "/0s0o/1s1i/4s4a",
E 9
I 9
    "/0s0o/4s4a",
    "/0s0o/4s4h",
    "/0s0o/4s4a",
    "/0s0o/4s4h",
    "/2s2a",
    "/2s2a/3s3e",
    "/2s2a/3s3e/5s5s",
    "/2s2a/3s3e/5s5s/1s1i",
    "/2s2a/3s3e/5s5s/1s1l",
    "/2s2a/3s3e/5s5s/1s1i/4s4a",
    "/2s2a/3s3e/5s5s/1s1i/4s4h",
    "/2s2a/3s3e/5s5s/1s1l/4s4a",
    "/2s2a/3s3e/5s5s/1s1l/4s4h",
    "/2s2a/3s3e/5s5s/4s4a",
    "/2s2a/3s3e/5s5s/4s4h",
    "/2s2a/3s3e/5s5s/4s4a",
    "/2s2a/3s3e/5s5s/4s4h",
    "/2s2a/3s3e/1s1i",
    "/2s2a/3s3e/1s1l",
    "/2s2a/3s3e/1s1i/4s4a",
    "/2s2a/3s3e/1s1i/4s4h",
    "/2s2a/3s3e/1s1l/4s4a",
    "/2s2a/3s3e/1s1l/4s4h",
    "/2s2a/3s3e/4s4a",
E 9
    "/2s2a/3s3e/4s4h",
D 9
    "/1s1l/2s2a/3s3e",
    "/$s$s/0s0o/1s1l/3s3e",
    "/0s0o/1s1l/2s2a/4s4a",
    "/0s0o/1s1i/2s2a/3s3e",
    "/$s$s/0s0o/1s1i/4s4a",
    "/$s$s/0s0o/1s1i/3s3e",
    "/$s$s/0s0o/1s1l/4s4a",
    "/0s0o/1s1l/2s2a/3s3e",
    "/$s$s/0s0o/1s1i/2s2a",
    "/1s1l/2s2a/3s3e/4s4a",
    "/$s$s/0s0o/1s1l/2s2a",
    "/$s$s/0s0o/1s1i/4s4h",
    "/1s1i/2s2a/3s3e/4s4a",
    "/0s0o/1s1i/2s2a/4s4a",
    "/0s0o/1s1l/2s2a/4s4h",
    "/1s1i/2s2a/3s3e/4s4h",
    "/1s1l/2s2a/3s3e/4s4h",
    "/0s0o/1s1i/2s2a/4s4h",
    "/$s$s/0s0o/1s1l/4s4h",
    "/$s$s/0s0o/1s1i/2s2a/4s4a",
    "/$s$s/0s0o/1s1l/2s2a/4s4h",
    "/$s$s/0s0o/1s1i/2s2a/4s4h",
    "/0s0o/1s1l/2s2a/3s3e/4s4a",
    "/$s$s/0s0o/1s1l/2s2a/4s4a",
    "/0s0o/1s1i/2s2a/3s3e/4s4a",
    "/0s0o/1s1i/2s2a/3s3e/4s4h",
    "/$s$s/0s0o/1s1l/2s2a/3s3e",
    "/0s0o/1s1l/2s2a/3s3e/4s4h",
    "/$s$s/0s0o/1s1i/2s2a/3s3e",
    "/$s$s/0s0o/1s1l/2s2a/3s3e/4s4h",
    "/$s$s/0s0o/1s1l/2s2a/3s3e/4s4a",
    "/$s$s/0s0o/1s1i/2s2a/3s3e/4s4a",
    "/$s$s/0s0o/1s1i/2s2a/3s3e/4s4h",
E 9
I 9
    "/2s2a/3s3e/4s4a",
    "/2s2a/3s3e/4s4h",
    "/2s2a/5s5s",
    "/2s2a/5s5s/1s1i",
    "/2s2a/5s5s/1s1l",
    "/2s2a/5s5s/1s1i/4s4a",
    "/2s2a/5s5s/1s1i/4s4h",
    "/2s2a/5s5s/1s1l/4s4a",
    "/2s2a/5s5s/1s1l/4s4h",
    "/2s2a/5s5s/4s4a",
    "/2s2a/5s5s/4s4h",
    "/2s2a/5s5s/4s4a",
    "/2s2a/5s5s/4s4h",
    "/2s2a/1s1i",
    "/2s2a/1s1l",
    "/2s2a/1s1i/4s4a",
    "/2s2a/1s1i/4s4h",
    "/2s2a/1s1l/4s4a",
    "/2s2a/1s1l/4s4h",
    "/2s2a/4s4a",
    "/2s2a/4s4h",
    "/2s2a/4s4a",
    "/2s2a/4s4h",
    "/3s3e",
    "/3s3e/5s5s",
    "/3s3e/5s5s/1s1i",
    "/3s3e/5s5s/1s1l",
    "/3s3e/5s5s/1s1i/4s4a",
    "/3s3e/5s5s/1s1i/4s4h",
    "/3s3e/5s5s/1s1l/4s4a",
    "/3s3e/5s5s/1s1l/4s4h",
    "/3s3e/5s5s/4s4a",
    "/3s3e/5s5s/4s4h",
    "/3s3e/5s5s/4s4a",
    "/3s3e/5s5s/4s4h",
    "/3s3e/1s1i",
    "/3s3e/1s1l",
    "/3s3e/1s1i/4s4a",
    "/3s3e/1s1i/4s4h",
    "/3s3e/1s1l/4s4a",
    "/3s3e/1s1l/4s4h",
    "/3s3e/4s4a",
    "/3s3e/4s4h",
    "/3s3e/4s4a",
    "/3s3e/4s4h",
    "/5s5s",
    "/5s5s/1s1i",
    "/5s5s/1s1l",
    "/5s5s/1s1i/4s4a",
    "/5s5s/1s1i/4s4h",
    "/5s5s/1s1l/4s4a",
    "/5s5s/1s1l/4s4h",
    "/5s5s/4s4a",
    "/5s5s/4s4h",
    "/5s5s/4s4a",
    "/5s5s/4s4h",
    "/1s1i",
    "/1s1l",
    "/1s1i/4s4a",
    "/1s1i/4s4h",
    "/1s1l/4s4a",
    "/1s1l/4s4h",
    "/4s4a",
    "/4s4h",
    "/4s4a",
    "/4s4h",

    /* done */
E 9
    (char *) 0
};

static char *r_constructors[] = {
    ":",
I 9
D 12

E 12
#ifdef CRACKLIB_DEBUG2
    (char *) 0,
#endif
D 12

E 12
E 9
    "r",
    "d",
    "f",
    "dr",
    "fr",
    "rf",
I 14
    "c",
    "rc",
E 14
    (char *) 0
};

I 12
/*
 * GTry - check if <password> is a permutation of <rawtext>
 */
E 12
I 3
D 4
#define	EM_NAME		"based upon your user name"
#define	EM_PASSWD	"based upon your user information"
#define	EM_DICT		"based upon a word found in a dictionary"
#define	EM_SSN		"looks like a Social Security Number"
E 4
I 4
D 9
#define	EM_NAME		"it is based upon your user name"
#define	EM_PASSWD	"it is based upon your user information"
#define	EM_DICT		"it is based upon a dictionary word"
#define	EM_SSN		"it looks like a Social Security Number"
E 4
#define	EM_RDICT	EM_DICT
D 4
#define	EM_SIMPLE	"too simple"
/* #define	EM_NIN		"looks like a National Insurance number" */
#define	EM_WHITESPC	"made up of all whitespace"
#define	EM_NODIFF	"does not have enough different characters"
#define	EM_SHORT	"too short"
E 4
I 4
#define	EM_SIMPLE	"it is too simple"
/* #define	EM_NIN		"it looks like a National Insurance number" */
#define	EM_WHITESPC	"it is made up of all whitespace"
#define	EM_NODIFF	"it does not have enough different characters"
#define	EM_SHORT	"it is too short"
E 4

E 9
E 3
int
GTry(rawtext, password)
D 9
    register char *rawtext;
    register char *password;
E 9
I 9
    char *rawtext;
    char *password;
E 9
{
D 9
    register int i;
    register char *mp;
E 9
I 9
    int i;
E 9
    int len;
I 9
    char *mp;
E 9

    /* use destructors to turn password into rawtext */
    /* note use of Reverse() to save duplicating all rules */

    len = strlen(password);

    for (i = 0; r_destructors[i]; i++)
    {
	if (!(mp = Mangle(password, r_destructors[i])))
	{
	    continue;
	}

D 9
#ifdef DEBUG
	printf("d1->\t%s vs %s\n", mp, rawtext);
E 9
I 9
#ifdef CRACKLIB_DEBUG
D 16
	printf("Gtry: %-16s = %-16s (destruct %s)\n", mp,
E 16
I 16
	printf("Gtry: '%s' = '%s' (destruct %s)\n", mp,
E 16
		rawtext, r_destructors[i]);
E 9
#endif
I 9

E 9
	if (!strncmp(mp, rawtext, len))
	{
	    return (1);
	}
D 9
#ifdef DEBUG
	printf("d2->\tr(%s) vs %s\n", mp, rawtext);
E 9
I 9

#ifdef CRACKLIB_DEBUG
D 16
	printf("Gtry: %-16s = %-16s (destruct %s reversed)\n", Reverse(mp),
E 16
I 16
	printf("Gtry: '%s' = '%s' (destruct %s reversed)\n", Reverse(mp),
E 16
		rawtext, r_destructors[i]);
E 9
#endif
I 9

E 9
	if (!strncmp(Reverse(mp), rawtext, len))
	{
	    return (1);
	}
    }

I 14
    /*
     * Use constructors to turn rawtext into password
     */
E 14
D 9
    /* use constructors to turn rawtext into password */

E 9
    for (i = 0; r_constructors[i]; i++)
    {
	if (!(mp = Mangle(rawtext, r_constructors[i])))
	{
	    continue;
	}
D 9
#ifdef DEBUG
	printf("c->\t%s vs %s\n", mp, password);
E 9
I 9

#ifdef CRACKLIB_DEBUG
D 16
	printf("Gtry: %-16s = %-16s (construct %s)\n", mp,
E 16
I 16
	printf("Gtry: '%s' = '%s' (construct %s)\n", mp,
E 16
		password, r_constructors[i]);
E 9
#endif
I 9

E 9
	if (!strncmp(mp, password, len))
	{
	    return (1);
	}
    }

    return (0);
}

I 11
D 12
#ifdef	NPASSWD_LIB
E 12
I 12
/*
 * FascistGecos - check if <password> is a permutation of the user's GECOS field
 */
E 12
E 11
I 5
D 9
#ifndef	IN_CHECKPASSWORD
E 9
E 5
char *
D 9
FascistGecos(password, uid)
E 9
I 9
FascistGecos(password, uid, pwin)
E 9
    char *password;
    int uid;
I 9
D 12
    struct passwd *pwin;
I 11
#else
char *
FascistGecos(password, uid)
    char *password;
    int uid;
#endif
E 12
I 12
    struct passwd *pwin;		/* Optional */
E 12
E 11
E 9
{
    int i;
    int j;
    int wc;
I 9
    char *ptr;
    int gwords;
E 9
    struct passwd *pwp;
    char gbuffer[STRINGSIZE];
I 9
    char tbuffer[STRINGSIZE];
E 9
    char *uwords[STRINGSIZE];
D 9
    char buffer[STRINGSIZE];
    register char *ptr = 
        "\101\154\145\143\127\141\163\110\145\162\145";
E 9
I 9
    char longbuffer[STRINGSIZE * 2];
E 9

I 11
D 12
#ifdef	NPASSWD_LIB
E 12
E 11
D 9
    if (!(pwp = getpwuid(uid)))
E 9
I 9
    if (!pwin)
E 9
    {
D 9
	return ("you are not registered in the password file");
E 9
I 9
	if (!(pwp = getpwuid(uid)))
	{
		return ("you cannot be found in the password file");
	}
    } else
    {
	pwp = pwin;
E 9
    }
I 11
D 12
#else
    if (!(pwp = getpwuid(uid)))
    {
	return ("you cannot be found in the password file");
    }
#endif
E 12
E 11

D 9
    if (GTry(pwp->pw_name, password))
E 9
I 9
    /*
     * It never used to be that you got passwd strings > 1024 chars,
     * but now...
     */
    (void) strncpy(tbuffer, pwp->pw_name, STRINGSIZE);
    tbuffer[STRINGSIZE-1] = '\0';
I 14
#ifdef CRACKLIB_DEBUG
    printf("FascistGecos: username check\n");
#endif
E 14
    if (GTry(tbuffer, password))
E 9
    {
D 3
	return ("it is based on your username");
E 3
I 3
D 9
/*	return (EM_NAME); */
	return (EM_PASSWD);
E 9
I 9
	return ("it is based on your username");
E 9
E 3
    }

D 9
    strcpy(gbuffer, Lowercase(pwp->pw_gecos));
E 9
I 9
    /*
     * See if they use something of their home directory path
     */
    (void) strncpy(tbuffer, pwp->pw_dir, STRINGSIZE);
    tbuffer[STRINGSIZE-1] = '\0';
I 14
#ifdef CRACKLIB_DEBUG
    printf("FascistGecos: directory check\n");
#endif
E 14
    if (GTry(tbuffer, password))
    {
	return ("it is derived from your home directory path");
    }
E 9

I 9
    /*
     * Let's get really paranoid and assume a dangerously long gecos entry
     */
    (void) strncpy(tbuffer, pwp->pw_gecos, STRINGSIZE);
    tbuffer[STRINGSIZE-1] = '\0';
    (void) strcpy(gbuffer, Lowercase(tbuffer));

E 9
    wc = 0;
    ptr = gbuffer;
I 9
    gwords = 0;
    uwords[0] = (char *)0;
E 9

    while (*ptr)
    {
	while (*ptr && ISSKIP(*ptr))
	{
	    ptr++;
	}

	if (ptr != gbuffer)
	{
	    ptr[-1] = '\0';
	}

I 9
	gwords++;
E 9
	uwords[wc++] = ptr;

	if (wc == STRINGSIZE)
	{
D 9
	    uwords[--wc] = (char *) 0;	/* to hell with it */
E 9
I 9
	    uwords[--wc] = (char *) 0;  /* to hell with it */
E 9
	    break;
	} else
	{
	    uwords[wc] = (char *) 0;
	}

	while (*ptr && !ISSKIP(*ptr))
	{
	    ptr++;
	}

	if (*ptr)
	{
	    *(ptr++) = '\0';
	}
    }
D 9
#ifdef DEBUG
E 9
I 9

D 14
#ifdef CRACKLIB_DEBUG
E 14
E 9
    for (i = 0; uwords[i]; i++)
    {
I 14
#ifdef CRACKLIB_DEBUG
E 14
D 9
    	printf("u:\t%s\n", uwords[i]);
E 9
I 9
	printf("FascistGecos: gecosword %s\n", uwords[i]);
E 9
D 14
    }
E 14
#endif
I 9
D 14

E 9
    for (i = 0; uwords[i]; i++)
    {
E 14
	if (GTry(uwords[i], password))
	{
D 2
	    return ("it is based upon your password entry");
E 2
I 2
D 3
		return ("it is derived from your password entry");
E 3
I 3
D 9
		return (EM_PASSWD);
E 9
I 9
	    return ("it is based upon your user information");
E 9
E 3
E 2
	}
    }

D 9
    for (j = 1; uwords[j]; j++)
E 9
I 9
    /* since uwords are taken from gbuffer,
	no uword can be longer than gbuffer */

    for (j = 1; (j < gwords) && uwords[j]; j++)
E 9
    {
	for (i = 0; i < j; i++)
	{
D 9
	    strcpy(buffer, uwords[i]);
	    strcat(buffer, uwords[j]);
	    if (GTry(buffer, password))
E 9
I 9
	    (void) strcpy(longbuffer, uwords[i]);
	    (void) strcat(longbuffer, uwords[j]);

	    if (GTry(longbuffer, password))
E 9
	    {
D 3
		return ("it is derived from your password entry");
E 3
I 3
D 9
		return (EM_PASSWD);
E 9
I 9
		return ("it is derived from your user information");
E 9
E 3
	    }

D 9
	    strcpy(buffer, uwords[j]);
	    strcat(buffer, uwords[i]);
	    if (GTry(buffer, password))
E 9
I 9
	    (void) strcpy(longbuffer, uwords[j]);
	    (void) strcat(longbuffer, uwords[i]);

	    if (GTry(longbuffer, password))
E 9
	    {
D 2
		return ("it's derived from your password entry");
E 2
I 2
D 3
		return ("it is derived from your password entry");
E 3
I 3
D 9
		return (EM_PASSWD);
E 9
I 9
		return ("it is derived from your user information");
E 9
E 3
E 2
	    }

D 9
	    buffer[0] = uwords[i][0];
	    buffer[1] = '\0';
	    strcat(buffer, uwords[j]);
	    if (GTry(buffer, password))
E 9
I 9
	    longbuffer[0] = uwords[i][0];
	    longbuffer[1] = '\0';
	    (void) strcat(longbuffer, uwords[j]);

	    if (GTry(longbuffer, password))
E 9
	    {
D 3
		return ("it is derivable from your password entry");
E 3
I 3
D 9
		return (EM_PASSWD);
E 9
I 9
		return ("it is deriveable from your user information");
E 9
E 3
	    }

D 9
	    buffer[0] = uwords[j][0];
	    buffer[1] = '\0';
	    strcat(buffer, uwords[i]);
	    if (GTry(buffer, password))
E 9
I 9
	    longbuffer[0] = uwords[j][0];
	    longbuffer[1] = '\0';
	    (void) strcat(longbuffer, uwords[i]);

	    if (GTry(longbuffer, password))
E 9
	    {
D 2
		return ("it's derivable from your password entry");
E 2
I 2
D 3
		return ("it is derivable from your password entry");
E 3
I 3
D 9
		return (EM_PASSWD);
E 9
I 9
		return ("it is derivable from your user information");
E 9
E 3
E 2
	    }
	}
    }
D 9

E 9
    return ((char *) 0);
}
I 5
D 9
#endif
E 9
E 5

I 12
/*
 * FascistLook - search for <instring> in dictionary <pwp>
 */
E 12
char *
FascistLook(pwp, instring)
    PWDICT *pwp;
    char *instring;
{
D 9
    register int i;
    register char *ptr;
E 9
I 9
    int i;
    char *ptr;
    char *jptr;
E 9
    char junk[STRINGSIZE];
D 9
    register char *jptr;
E 9
I 9
D 10
    static char msgbuf[STRINGSIZE];
E 10
    char *password;
E 9
    char rpassword[STRINGSIZE];
D 9
    register char *password;
E 9
D 20
    int32 notfound;
E 20
I 20
    c_int32 notfound;
E 20

    notfound = PW_WORDS(pwp);
I 9
    /* already truncated if from FascistCheck() */
    /* but pretend it wasn't ... */
    (void) strncpy(rpassword, instring, TRUNCSTRINGSIZE);
    rpassword[TRUNCSTRINGSIZE - 1] = '\0';
E 9
    password = rpassword;

D 9
    strncpy(password, instring, STRINGSIZE);

    password[STRINGSIZE - 1] = '\0';

I 3
D 5
#if	0
E 5
I 5
#ifndef	IN_CHECKPASSWORD
E 9
E 5
E 3
    if (strlen(password) < 4)
    {
D 9
	return ("it's WAY too short");
E 9
I 9
	return ("it is WAY too short");
E 9
    }
I 3
D 9
#endif
E 9
E 3

    if (strlen(password) < MINLEN)
    {
D 3
	return ("it is too short");
E 3
I 3
D 9
	return (EM_SHORT);
E 9
I 9
	return ("it is too short");
E 9
E 3
    }

    jptr = junk;
    *jptr = '\0';

    for (i = 0; i < STRINGSIZE && password[i]; i++)
    {
	if (!strchr(junk, password[i]))
	{
	    *(jptr++) = password[i];
	    *jptr = '\0';
	}
    }

    if (strlen(junk) < MINDIFF)
    {
D 3
	return ("it does not contain enough DIFFERENT characters");
E 3
I 3
D 9
	return (EM_NODIFF);
E 9
I 9
	return ("it does not contain enough DIFFERENT characters");
E 9
E 3
    }

D 9
    strcpy(password, Lowercase(password));
E 9
I 9
    (void) strcpy(password, Lowercase(password));
E 9

    Trim(password);

    while (*password && isspace(*password))
    {
	password++;
    }

    if (!*password)
    {
D 3
	return ("it is all whitespace");
E 3
I 3
D 9
	return (EM_WHITESPC);
E 9
I 9
	return ("it is all whitespace");
E 9
E 3
    }

    i = 0;
    ptr = password;
    while (ptr[0] && ptr[1])
    {
	if ((ptr[1] == (ptr[0] + 1)) || (ptr[1] == (ptr[0] - 1)))
	{
	    i++;
	}
	ptr++;
    }

    if (i > MAXSTEP)
    {
D 3
	return ("it is too simplistic/systematic");
E 3
I 3
D 9
	return (EM_SIMPLE);
E 9
I 9
	return ("it is too simplistic/systematic");
E 9
E 3
    }

I 2
D 3
#if	0
E 3
I 3
D 9
#ifdef	EM_NIN
E 3
E 2
    if (PMatch("aadddddda", password))	/* smirk */
E 9
I 9
D 10
#ifdef	US
    if (PMatch("ddd-dd-dddd", password))  /* smirk */
E 9
    {
D 2
	return ("it looks like a National Insurance number.");
E 2
I 2
D 3
	return ("it looks like a National Insurance number");
E 3
I 3
D 9
	return (EM_NIM);
E 9
I 9
	return ("it looks like a Social Security number");
E 9
E 3
    }
#endif

D 9
    if (PMatch("dddpddpdddd", password))	/* smirk (US version) */
E 9
I 9
#ifdef	UK
E 10
D 21
    if (PMatch("aadddddda", password))  /* smirk */
E 21
I 21
    if (PMatch("aadddddda", password, 0))  /* smirk */
E 21
E 9
    {
D 3
	return ("it looks like a Social Security number");
E 3
I 3
D 9
	return (EM_SSN);
E 9
I 9
	return ("it looks like a National Insurance number");
E 9
E 3
E 2
    }
I 9
D 10
#endif
E 10
E 9

I 11
D 12
#ifdef	NPASSWD_LIB
E 12
E 11
I 5
D 10
#ifndef	IN_CHECKPASSWORD
E 5
    if (ptr = FascistGecos(password, getuid()))
E 10
I 10
    if (ptr = FascistGecos(password, getuid(), (struct passwd *)0))
I 11
D 12
#else
    if (ptr = FascistGecos(password, getuid()))
#endif
E 12
E 11
E 10
    {
	return (ptr);
    }
I 5
D 10
#endif
E 10
E 5

I 9
    /* it should be safe to use Mangle with its reliance on STRINGSIZE
       since password cannot be longer than TRUNCSTRINGSIZE;
       nonetheless this is not an elegant solution */

E 9
    for (i = 0; r_destructors[i]; i++)
    {
	char *a;
I 9

E 9
	if (!(a = Mangle(password, r_destructors[i])))
	{
	    continue;
	}
I 9

#ifdef CRACKLIB_DEBUG
D 16
	printf("FascistLook: %-16s (dict)\n", a);
E 16
I 16
	printf("FascistLook: '%s' (dict)\n", a);
E 16
#endif

E 9
	if (FindPW(pwp, a) != notfound)
	{
D 3
	    return ("it is based on a dictionary word");
E 3
I 3
D 9
	    return (EM_DICT);
E 9
I 9
D 10
#ifdef	IN_CHECKPASSWORD
	    (void) sprintf (msgbuf,
			"it is based on the dictionary word %-16s", a);
	    return (msgbuf);
#else
E 10
	    return ("it is based on a dictionary word");
D 10
#endif
E 10
E 9
E 3
	}
    }

D 3
    strcpy(password, Reverse(password));
E 3
I 3
D 9
    (void) strcpy(password, Reverse(password));
E 9
I 9
D 12
    strcpy(password, Reverse(password));
E 12
I 12
    (void) strcpy(password, Reverse(password));
E 12
E 9
E 3

    for (i = 0; r_destructors[i]; i++)
    {
	char *a;

	if (!(a = Mangle(password, r_destructors[i])))
	{
	    continue;
	}
D 9

E 9
I 9
#ifdef CRACKLIB_DEBUG
D 16
	printf("FascistLook: %-16s (reversed dict)\n", a);
E 16
I 16
	printf("FascistLook: '%s' (reversed dict)\n", a);
E 16
#endif
E 9
	if (FindPW(pwp, a) != notfound)
	{
D 3
	    return ("it is based on a (reversed) dictionary word");
E 3
I 3
D 9
	    return (EM_RDICT);
E 9
I 9
D 10
#ifdef	IN_CHECKPASSWORD
	    (void) sprintf (msgbuf,
			"it is based on the dictionary word %-16s", a);
	    return (msgbuf);
#else
E 10
	    return ("it is based on a (reversed) dictionary word");
D 10
#endif
E 10
E 9
E 3
	}
    }
D 9

E 9
    return ((char *) 0);
}

I 12
/*
 * FascistCheck - look for <password> in dictionary <path>
 */
E 12
char *
FascistCheck(password, path)
    char *password;
    char *path;
{
D 7
    static PWDICT *pwp;
    static char lastpath[STRINGSIZE];
E 7
I 7
D 9
    static PWDICT *pwp = (PWDICT *)0;
D 8
    static char lastpath[STRINGSIZE] = { 0 };
E 8
I 8
    static char lastpath[MAXPATHLEN] = { 0 };
E 8
E 7
I 6
    char *rc;
E 9
I 9
    static char lastpath[STRINGSIZE];
    static PWDICT *pwp;
    char pwtrunced[STRINGSIZE];
E 9
E 6

D 8
    if (pwp && strncmp(lastpath, path, STRINGSIZE))
E 8
I 8
D 9
    if (pwp && strcmp(lastpath, path))
E 9
I 9
    /* security problem: assume we may have been given a really long
       password (buffer attack) and so truncate it to a workable size;
       try to define workable size as something from which we cannot
       extend a buffer beyond its limits in the rest of the code */

    (void) strncpy(pwtrunced, password, TRUNCSTRINGSIZE);
    pwtrunced[TRUNCSTRINGSIZE - 1] = '\0'; /* enforce */

    /* perhaps someone should put something here to check if password
       is really long and syslog() a message denoting buffer attacks?  */

    if (pwp && strncmp(lastpath, path, STRINGSIZE))
E 9
E 8
    {
D 9
    	PWClose(pwp);
    	pwp = (PWDICT *)0;
I 7
    	lastpath[0] = 0;
E 9
I 9
	(void) PWClose(pwp);
	pwp = (PWDICT *)0;
E 9
E 7
    }

    if (!pwp)
    {
	if (!(pwp = PWOpen(path, "r")))
	{
D 3
	    perror("PWOpen");
E 3
I 3
D 7
	    (void) sprintf(lastpath, "FacistCheck-PWOpen \"%s\"", path);
E 7
I 4
D 10
#ifndef	IN_CHECKPASSWORD
E 10
I 7
D 9
	    (void) sprintf(lastpath, "FacistCheck-PWOpen \"%s\"", path);
E 7
E 4
	    perror(lastpath);
E 9
I 9
D 12
	    fprintf(stderr, "%s: PWOpen error %s\n", path, PWioError);
E 12
I 12
	    (void) fprintf(stderr, "%s: PWOpen error %s\n", path, PWioError);
E 12
E 9
E 3
	    exit(-1);
I 4
D 10
#else
D 7
	    return(lastpath);
E 7
I 7
D 9
	    static char errmsg[STRINGSIZE];

	    (void) sprintf(errmsg, "Cannot open dictionary \"%s\"", path);
	    return(errmsg);
E 9
I 9
	    return(PWioError);
E 9
E 7
#endif
E 10
E 4
	}
D 3
	strncpy(lastpath, path, STRINGSIZE);
E 3
I 3
D 8
	(void) strncpy(lastpath, path, STRINGSIZE);
E 8
I 8
D 9
	(void) strncpy(lastpath, path, sizeof lastpath);
E 9
I 9
	(void) strncpy(lastpath, path, STRINGSIZE);
E 9
E 8
E 3
    }
D 9

D 6
    return (FascistLook(pwp, password));
E 6
I 6
    rc = FascistLook(pwp, password);
D 7
    (void) PWClose(pwp);
E 7
    return(rc);
E 9
I 9
    return (FascistLook(pwp, pwtrunced));
E 9
E 6
}
I 10

D 12
#ifdef	NPASSWD_LIB
E 12
/*
D 12
 * FascistNpasswd
 *	Do Cracklib stuff that npasswd needs
E 12
I 12
 * FascistNpasswd - Cracklib stuff that npasswd needs
E 12
 */
char *
D 18
FascistNpasswd(pwl, instring)
E 18
I 18
FascistNpasswd(pwl, instring, verbose)
E 18
D 13
    PWDICT **pwl;		/* List of dictionaries to look in */
    char *instring;		/* Password string */
E 13
I 13
    char **pwl;		/* List of dictionaries to look in */
    char *instring;	/* Password string */
I 18
    int verbose;	/* Verbose flag */
E 18
E 13
{
    char **decon;			/* Mangle deconstructor */
    char *password;			/* Pointer to stuff in rpassword */
    char rpassword[STRINGSIZE];		/* Cleaned copy of <instring> */
    char revpassword[STRINGSIZE];	/* Reversed copy of <rpassword> */
I 17
    int  ndicts = 0;			/* How many dictionaries looked in */
E 17

    /*
     * Copy input string and truncate
     */
    (void) strncpy(rpassword, instring, TRUNCSTRINGSIZE);
    rpassword[TRUNCSTRINGSIZE - 1] = '\0';
    password = rpassword;

    (void) strcpy(password, Lowercase(password));	/* Make lower case */
D 12
    Trim(password);				/* Trim trailing whitespace */
E 12
I 12
    (void) Trim(password);			/* Trim trailing whitespace */
E 12

    while (*password && isspace(*password))	/* Trim leading whitespace */
    {
	password++;
    }

    if (!*password)
    {
	return ("it is all whitespace");
    }

    /* 
     * It should be safe to use Mangle with its reliance on STRINGSIZE
     * since password cannot be longer than TRUNCSTRINGSIZE
     */
    (void) strcpy(revpassword, Reverse(password));

    /* 
     * Iterate through the mangle deconstructors
     */
    for (decon = r_destructors; *decon; decon++)
    {
	static char msgbuf[STRINGSIZE];
I 12
	char mangled[STRINGSIZE];
E 12
D 13
        PWDICT	**pwx;
E 13
I 13
        char **pwx;
E 13
	char *a;

I 12
	mangled[0] = 0;
E 12
	if (a = Mangle(password, *decon))	/* Forward password */
	{
I 12
		(void) strcpy(mangled, a);
E 12
D 18
#ifdef CRACKLIB_DEBUG
D 12
		printf("FascistNpasswd: %-16s (dict)\n", a);
E 12
I 12
D 16
		printf("FascistNpasswd: %-16s (dict)\n", mangled);
E 16
I 16
		printf("FascistNpasswd: '%s' (dict)\n", mangled);
E 16
E 12
#endif
E 18
I 18
		if (verbose)
D 19
			printf("FascistNpasswd: '%s' (dict)\n", mangled);
E 19
I 19
			printf("FascistNpasswd: '%s' (dict) decon '%s'\n",
				mangled, *decon);
E 19
E 18
D 12
		for (pwx = pwl; *pwx; pwx++) {	/* Iterate dictionaries */
			if (FindPW(*pwx, a) != PW_WORDS(*pwx))
			{
			    (void) sprintf (msgbuf,
				"it is based on the dictionary word %-16s", a);
			    return (msgbuf);
			}
		}
E 12
	}
	if (a = Mangle(revpassword, *decon))	/* Reversed password */
	{
D 18
#ifdef CRACKLIB_DEBUG
D 12
		printf("FascistNpaswd: %-16s (reversed dict)\n", a);
E 12
I 12
D 16
		printf("FascistNpasswd: %-16s (reversed dict)\n", a);
E 16
I 16
		printf("FascistNpasswd: '%s' (reversed dict)\n", a);
E 16
E 12
#endif
E 18
I 18
		if (verbose)
D 19
			printf("FascistNpasswd: '%s' (reversed dict)\n", a);
E 19
I 19
			printf("FascistNpasswd: '%s' (rev dict) decon '%s'\n",
				a, *decon);
E 19
E 18
D 12
		for (pwx = pwl; *pwx; pwx++) {	/* Iterate dictionaries */
			if (FindPW(*pwx, a) != PW_WORDS(*pwx))
			{
			    (void) sprintf (msgbuf,
				"it is based on the dictionary word %-16s", a);
			    return (msgbuf);
			}
E 12
I 12
	}
	for (pwx = pwl; *pwx; pwx++) {	/* Iterate dictionaries */
D 13
		if (mangled[0] && FindPW(*pwx, mangled) != PW_WORDS(*pwx))
E 13
I 13
D 15
		PWDICT	*pw = PWOpen(*pwx);
E 15
I 15
		PWDICT	*pw = PWOpen(*pwx, "r");
I 18
D 20
		int32	found;
E 20
I 20
		c_int32	found;
E 20
E 18
E 15

		if (pw == 0)
E 13
		{
		    (void) sprintf (msgbuf,
I 13
			"Lookup error (%s) in dictionary \"%s\"",
				PWioError, *pwx);
		    return (msgbuf);
		}
D 18
		if (mangled[0] && FindPW(pw, mangled) != PW_WORDS(pw))
E 18
I 18
		if (verbose)
			printf("FascistNpasswd: dict '%s'\n", *pwx);
		if (mangled[0] && (found = FindPW(pw, mangled)) != PW_WORDS(pw))
E 18
		{
		    (void) sprintf (msgbuf,
E 13
D 16
			"it is based on the dictionary word %-16s", a);
E 16
I 16
D 18
			"it is based on the dictionary word '%s'", a);
E 18
I 18
			"it can be derived from the word '%s'",
				GetPW(pw, found));
E 18
E 16
I 13
		    (void) PWClose (pw);
E 13
		    return (msgbuf);
E 12
		}
I 12
D 13
		if (a && FindPW(*pwx, a) != PW_WORDS(*pwx))
E 13
I 13
D 18
		if (a && FindPW(pw, a) != PW_WORDS(pw))
E 18
I 18
		if (a && (found = FindPW(pw, a)) != PW_WORDS(pw))
E 18
E 13
		{
		    (void) sprintf (msgbuf,
D 16
			"it is based on the dictionary word %-16s", a);
E 16
I 16
D 18
			"it is based on the dictionary word '%s'", a);
E 18
I 18
			"it can be derived from the word '%s'",
				GetPW(pw, found));
E 18
E 16
I 13
		    (void) PWClose (pw);
E 13
		    return (msgbuf);
		}
I 13
		(void) PWClose (pw);
I 17
		ndicts++;
E 17
E 13
E 12
	}
    }
D 17
    return ((char *) 0);
E 17
I 17
    if (ndicts)
	    return ((char *) 0);
    else
	    return ("no dictionaries were found");
E 17
}
D 12
#endif /* NPASSWD_LIB */
E 12

E 10
I 4
/* End %M% */
E 4
E 1
