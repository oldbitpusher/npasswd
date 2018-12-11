h57728
s 00013/00000/00060
d D 1.21 98/07/09 15:22:56 clyde 21 20
c Add defines for trace levels
e
s 00001/00001/00059
d D 1.20 98/07/09 08:52:43 clyde 20 19
c Change type of checkpassword_verify()
e
s 00001/00000/00059
d D 1.19 98/06/30 15:43:02 clyde 19 18
c Add checkpassword_verify()
e
s 00001/00001/00058
d D 1.18 98/06/26 13:29:39 clyde 18 17
c Add second argument to checkpassword_configure()
e
s 00001/00001/00058
d D 1.17 98/06/23 10:43:14 clyde 17 16
c Add fourth argument to password_history_update() prototype
e
s 00005/00000/00054
d D 1.16 98/06/08 14:08:30 clyde 16 15
c Add proto for password_history_update()
e
s 00001/00001/00053
d D 1.15 98/04/16 17:01:53 clyde 15 14
c Change declaration of checkpassword_configure()
e
s 00044/00018/00010
d D 1.14 98/04/07 09:49:16 clyde 14 13
c 1. Add UT copyright notice
c 2. Remove PWCK_XXX codes
c 3. Change the type of checkpassword()
e
s 00001/00001/00027
d D 1.13 98/04/06 13:31:49 clyde 13 12
c Change PWCK_FINGER to PWCK_PASSWD
e
s 00001/00001/00027
d D 1.12 98/03/26 10:57:48 clyde 12 11
c Change prototype for checkpassword()
e
s 00002/00002/00026
d D 1.11 96/08/29 12:59:26 clyde 11 10
c Remove 'const' declarations (too much compiler trouble)
e
s 00005/00008/00023
d D 1.10 96/08/13 13:06:13 clyde 10 9
c Add const where useful
e
s 00000/00000/00031
d D 1.9 96/08/06 14:13:49 clyde 9 8
c beta 3 cycle 1 checkin
e
s 00001/00001/00030
d D 1.8 94/03/15 18:52:25 clyde 8 7
c Fix prototype of checkpassword_configure
e
s 00001/00000/00030
d D 1.7 94/03/15 11:36:11 clyde 7 6
c Add PWCK_REUSE code to indicate reused password
e
s 00010/00079/00020
d D 1.6 94/01/05 15:50:35 clyde 6 5
c Make into public only definitions
e
s 00011/00001/00088
d D 1.5 92/01/27 16:42:06 clyde 5 4
c Add forward decl of _flipstring()
e
s 00001/00001/00088
d D 1.4 90/11/26 09:43:00 clyde 4 3
c Declare illegalcc as extern
e
s 00005/00000/00084
d D 1.3 89/10/04 09:25:53 clyde 3 2
c Add System V ifdef for string routines
e
s 00003/00003/00081
d D 1.2 89/06/05 10:59:54 clyde 2 1
c Rename some internal routines to avoid name collisions
e
s 00084/00000/00000
d D 1.1 89/05/18 10:05:17 clyde 1 0
c date and time created 89/05/18 10:05:17 by clyde
e
u
U
t
T
I 1
/*
D 6
 *	checkpasswd.h - Master include for checkpasswd
E 6
I 6
D 10
 *	checkpassword.h - Public include for checkpasswd users
E 10
I 10
D 14
 *	checkpassword.h - Public include for checkpasswd library
E 14
I 14
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
E 14
E 10
E 6
 * 
D 14
 *	%W% %G% (cc.utexas.edu) %P%
E 14
I 14
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
E 14
 */

D 6
#include <stdio.h>
#include <ctype.h>
I 3
#ifdef	SYSV
#include <string.h>
#define index strchr
#else
E 3
#include <strings.h>
I 3
#endif
E 3

I 5
#ifdef	_STDC_
extern char	*_flipstring(char *string; int mkcopy);
	/* String flip routine */

#else
extern char	*_flipstring();
	/* String flip routine */

#endif
E 6
E 5
/*
D 14
 *	Return codes from checkpasswd() and pwck_*
 *	Also used as exit codes from main()
E 14
I 14
 * checkpassword.h - Public include for checkpasswd library
 * 
 * %W% %G% (cc.utexas.edu)
E 14
 */
D 14
#define	PWCK_FAIL	-1	/* Failure during check process */
#define	PWCK_OK		0	/* Password is ok to use */
#define	PWCK_NULL	1 	/* Password is the null string */
#define	PWCK_OBVIOUS	2	/* Password is 'too obvious' */
D 13
#define	PWCK_FINGER	3	/* Password is part of users finger info */
E 13
I 13
#define	PWCK_PASSWD	3	/* Password is part of user information */
E 13
#define	PWCK_INDICT	4	/* Password found in a dictionary */
#define	PWCK_ILLCHAR	5	/* Illegal character in password */
#define	PWCK_SHORT	6	/* Password too short */
I 7
#define	PWCK_REUSE	7	/* Attempt to reuse password */
E 7

/*
D 6
 *	Dictionary info
E 6
I 6
 * Forward functions
E 6
 */
E 14
D 6
typedef struct _dict {
	char	*dict_path,		/* Path to dictionary */
		*dict_desc;		/* Descriptive phrase */
	struct _dict  *dict_next;	/* Link to next dict */
} dictionary;
extern dictionary	*dictionaries; /* List of dictionaries to check */

/*
 *	This is the default dicitonary to look in
 *	If you have some DBM dictionaries, either repoint this
 *	define or comment it out and place dictionaries in
 *	the configuration file.
 */
#define	DEFAULT_DICT	"/usr/dict/words"	/* Default dictionary */

#ifndef	CONFIG_FILE
			/* Set configuration file name */
# ifdef	DEBUG
#	define	CONFIG_FILE	"checkpasswd.cf" 
# else
#	define	CONFIG_FILE	"/usr/adm/checkpasswd.cf"
# endif	/* DEBUG */
#endif	/* CONFIG_FILE */

I 5

E 5
/*
 *	Password preferences
 */
int	single_case,		/* Single-case passwords ok or not */
	print_only,		/* Printable characters only */
	run_length,		/* Maximum length of character runs */
	min_length,		/* Minimum password length */
	max_length;		/* Maximum effective length */

#define	sizeof_illegalcc	128
D 4
char	illegalcc[];		/* Control characters not allowed */
E 4
I 4
extern char	illegalcc[];		/* Control characters not allowed */
E 4

/*
 *	Misc inline subroutine macros
 */

/*	Single string comparasion */
#define try(P,C,V) { \
D 2
	if (cistrcmp((P),(C)) == 0) \
E 2
I 2
	if (_cistrcmp((P),(C)) == 0) \
E 2
		return(V); \
	}

/*	Multiple string comparasion */
#define mtry(P,C,V) { \
	int i; \
D 2
	if ((i = instring((P),(C),(V))) != PWCK_OK) \
E 2
I 2
	if ((i = _instring((P),(C),(V))) != PWCK_OK) \
E 2
		return(i); \
}

/* Compact string compare */
D 2
#define	streq(X,S)	(cistrncmp((X),(S), strlen(X)) == 0)
E 2
I 2
#define	streq(X,S)	(_cistrncmp((X),(S), strlen(X)) == 0)
E 2


D 5
/*	End %M%	*/
E 5
I 5
/* End %M% */
E 6
I 6
void	checkpassword_init();
I 19
D 20
void	checkpassword_verify();
E 20
I 20
char	*checkpassword_verify();
E 20
E 19
D 10
#ifdef	__STDC__
D 8
int	checkpassword_configure(char *, int);
E 8
I 8
int	checkpassword_configure(char *, char *);
E 8
int	checkpassword(char *, struct passwd *, char *);
#else
int	checkpassword_configure();
int	checkpassword();
#endif
E 10
I 10
D 11
int	checkpassword_configure _((const char *, char *));
int	checkpassword _((const char *, const struct passwd *, char *));
E 11
I 11
D 15
int	checkpassword_configure _((char *, char *));
E 15
I 15
D 18
char	*checkpassword_configure _((char *));
E 18
I 18
char	*checkpassword_configure _((char *, int));
E 18
E 15
D 12
int	checkpassword _((char *, struct passwd *, char *));
E 12
I 12
D 14
int	checkpassword _((char *, struct passwd *, char *, unsigned int));
E 14
I 14
char	*checkpassword _((char *, struct passwd *));
E 14
E 12
E 11

I 16
/*
 * Public password history routines
 */
D 17
int	password_history_update _((char *, char *));
E 17
I 17
int	password_history_update _((char *, char *, time_t));
E 17

I 21
/*
 * Password check library debug levels.
 * These are taken from the npasswd debug level defines (defines.h).
 */
#ifndef	TR_NONE
# define	TR_NONE		0	/* No tracing */
# define	TR_VERBOSE	1	/* Mild verbosity */
# define	TR_UPDATE	3	/* Trace user update */
# define	TR_CONFIG	4	/* Trace configuration processing */
# define	TR_PWCHECK	7	/* Trace password checking */
# define	TR_ALL		9	/* Trace *everything* */
#endif

E 21
E 16
/* End %M% */
E 10
E 6
E 5
E 1
