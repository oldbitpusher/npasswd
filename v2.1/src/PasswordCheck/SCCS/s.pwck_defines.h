h50735
s 00001/00000/00104
d D 1.15 98/08/17 13:20:04 clyde 15 14
c Add 'whitespace
e
s 00002/00000/00102
d D 1.14 98/07/17 11:14:03 clyde 14 13
c Add ctran() and pwck_history_probe()
e
s 00000/00003/00102
d D 1.13 98/07/09 11:08:52 clyde 13 12
c  Remove pw_svc stuff
e
s 00001/00001/00104
d D 1.12 98/06/26 14:26:08 clyde 12 11
c Change checkpasswd.h to checkpassword.h
e
s 00005/00004/00100
d D 1.11 98/04/14 13:33:48 clyde 11 10
c 1. Add prototype for pwck_history_configure()
c 2. Increase NDICTIONARIES
c 3. Change dictionary list element in Config block
e
s 00045/00002/00059
d D 1.10 98/04/07 09:48:24 clyde 10 9
c Add UT copyright
e
s 00025/00030/00036
d D 1.9 98/04/07 09:46:51 clyde 9 8
c 1. Remove inline function defines
c 2. Change dictionaries from linked list to arrays
c 3. Change PWCK_XXX from integer to string values
c 4. Add more include files
c 5. Change the type of pwck_<foo> routines to (char *)
e
s 00002/00017/00064
d D 1.8 98/03/26 11:09:39 clyde 8 7
c 1. Add new Configure field
c 2. Remove unused & duplicated stuff
e
s 00001/00000/00080
d D 1.7 97/10/29 14:06:30 clyde 7 6
c Add alpha_only to Config block
e
s 00015/00003/00065
d D 1.6 96/09/11 18:07:33 clyde 6 5
c Remove debug from Config block, add DB_XXX defines (if not defined)
e
s 00006/00006/00062
d D 1.5 96/08/29 12:59:28 clyde 5 4
c Remove 'const' declarations (too much compiler trouble)
e
s 00001/00001/00067
d D 1.4 96/08/14 18:43:04 clyde 4 3
c Change svc_info to pw_svc
e
s 00009/00009/00059
d D 1.3 96/08/13 13:04:28 clyde 3 2
c 1. Add const declarations
c 2. Fix 'try' macros to reflect new instring behavior
e
s 00003/00001/00065
d D 1.2 96/08/09 16:17:52 clyde 2 1
c Beta 3 development checkin 2
e
s 00066/00000/00000
d D 1.1 96/08/06 14:14:59 clyde 1 0
c date and time created 96/08/06 14:14:59 by clyde
e
u
U
f e 0
t
T
I 1
/*
D 10
 *	pwck_lib.h - definitions for checkpassword library modules
E 10
I 10
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
E 10
 * 
D 10
 *	%W% %G% (cc.utexas.edu) %P%
E 10
I 10
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
E 10
 */

I 10
/*
 * %M% - definitions for checkpassword library modules
 * 
 * %W% %G% (cc.utexas.edu)
 */
E 10
#include "compatibility.h"
I 9
#include "constants.h"
E 9
#include "defines.h"
I 9
#include "common.h"
E 9
D 12
#include "checkpasswd.h"
E 12
I 12
#include "checkpassword.h"
E 12
I 2
D 4
#include "svc_info.h"
E 4
I 4
D 13
#include "pw_svc.h"
E 13
I 9
#include "packer.h"
E 9
E 4
E 2

/*
 * Declarations for internal routines.
D 3
 * Declarations for external routines are in "checkpassword.h"
E 3
I 3
 * Declarations for external routines are in "checkpasswd.h"
E 3
 */
D 3
public char	*_flipstring _((char *, char *));
D 2
public char	*_ctran _((char));
E 2
public int	pwck_crack _((char *, struct passwd *, char *));
public int	pwck_lexical _((char *, struct passwd *, char *));
public int	pwck_local _((char *, struct passwd *, char *));
public int	pwck_passwd _((char *, struct passwd *, char *));
public int	pwck_history _((char *, struct passwd *, char *));
E 3
I 3
D 5
public char	*_flipstring _((const char *, char *));
public int	pwck_crack _((const char *, const struct passwd *, char *));
public int	pwck_lexical _((const char *, const struct passwd *, char *));
public int	pwck_local _((const char *, const struct passwd *, char *));
public int	pwck_passwd _((const char *, const struct passwd *, char *));
public int	pwck_history _((const char *, const struct passwd *, char *));
E 5
I 5
D 9
public char	*_flipstring _((char *, char *));
public int	pwck_crack _((char *, struct passwd *, char *));
public int	pwck_lexical _((char *, struct passwd *, char *));
public int	pwck_local _((char *, struct passwd *, char *));
public int	pwck_passwd _((char *, struct passwd *, char *));
public int	pwck_history _((char *, struct passwd *, char *));
E 9
I 9
public char	*pwck_crack _((char *, struct passwd *));
public char	*pwck_lexical _((char *, struct passwd *));
public char	*pwck_local _((char *, struct passwd *));
public char	*pwck_passwd _((char *, struct passwd *));
public char	*pwck_history _((char *, struct passwd *));
I 11
public char	*pwck_history_configure _((char **));
I 14
public void	pwck_history_probe _((char *));
public char	*ctran _((char));
E 14
E 11
E 9
E 5
E 3

D 9
/*
 *	Dictionary info
 */
typedef struct _dict {
	char	*path;		/* Path to dictionary */
	struct _dict  *next;	/* Link to next dict */
} dictionary;
E 9
I 9
typedef char	*(*checkproc)();
E 9

D 9
typedef int     (*checkproc)();

E 9
#define	NBADCHARS	128
D 9
#define	NCHECKPROCS	16
E 9
I 9
D 11
#define	NCHECKPROCS	16	/* options.h ? XXX */
#define	NDICTIONARIES	16	/* options.h ? XXX */
E 11
I 11
#define	NCHECKPROCS	16
#define	NDICTIONARIES	48
E 11
E 9

I 9
#define	PWCK_OK		((char *)0)
#define	PWCK_NULL	"it is empty"
#define	PWCK_OBVIOUS	"it is too easy to guess"
#define	PWCK_PASSWD	"it is part of your user information"
#define	PWCK_INDICT	"it is too similar to a dictionary word"
#define	PWCK_ILLCHAR	"it has an illegal character in it"
#define	PWCK_SHORT	"it is too short"
#define	PWCK_REUSE	"it has been used recently"

E 9
/*
 * Configuration block for the password checker
 */
struct checkpassword_config {	/* Configuration block */
D 6
	int	debug,		/* Debug level */
		initialized,	/* Is this unit initialized */
E 6
I 6
D 9
	int	initialized,	/* Is this unit initialized */
E 9
I 9
	int	initialized,	/* Password checker init flag */
I 11
		length_warn,	/* Warn if password is over length */
E 11
E 9
E 6
		single_case,	/* Single-case passwords ok or not */
I 7
		alpha_only,	/* All-alpha passwords ok or not */
E 7
		print_only,	/* Printable characters only */
I 15
		whitespace,	/* Allow whitespace chars */
E 15
I 8
		char_classes,	/* Minimum number of char classes */
E 8
		run_length,	/* Maximum length of character runs */
		min_length,	/* Minimum password length */
		max_length;	/* Maximum effective length */
D 9
	dictionary	*dictionaries; /* List of dictionaries to check */
	char		badchars[NBADCHARS];	/* Characters not allowed */
	checkproc	checkprocs[NCHECKPROCS]; /* Vector of check routines */
E 9
I 9
D 11
	char	*dict_path[NDICTIONARIES]; /* Dictionary paths */
	PWDICT	*dict_ptrs[NDICTIONARIES]; /* Dictionary pointers */
E 11
I 11
	char	*dictionaries[NDICTIONARIES]; /* Dictionary paths */
E 11
	char	badchars[NBADCHARS];	/* Characters not allowed */
	checkproc checkprocs[NCHECKPROCS]; /* Vector of check routines */
E 9
};
extern struct checkpassword_config	Config;

I 2
D 6
extern struct pwsvc	svc;
E 6
I 6
D 13
extern struct pw_svc	svc;
E 6

E 13
I 6
D 8
#ifndef	DB_NONE
# define	DB_NONE		0	/* No debug */
# define	DB_VERBOSE	1	/* Mild verbosity */
# define	DB_LEVEL2	2	/* Nothing yet */
# define	DB_LEVEL3	3	/* Nothing yet */
# define	DB_LOOKUP	4	/* Trace user lookup */
# define	DB_UPDATE	5	/* Trace user update */
# define	DB_LEVEL6	6	/* Nothing yet */
# define	DB_LEVEL7	7	/* Nothing yet */
# define	DB_CONFIG	8	/* Trace configuration processing */
# define	DB_ALL		99	/* Trace *everything* */
#endif

E 8
E 6
E 2
D 9
/*
 * Macros for inline functions
 */

/* Single string comparasion */
D 3
#define try(_P_,_C_,_V_) if (strcasecmp((_P_),(_C_)) == 0) return(_V_)
E 3
I 3
#define try(_P_,_C_,_V_) if (*(_C_) && strcasecmp((_P_),(_C_)) == 0) return(_V_)
E 3

/* Multiple string comparasion */
D 3
#define mtry(_P_,_C_,_V_)  if (instring((_P_),(_C_))) return(_V_)
E 3
I 3
D 8
#define mtry(_P_,_C_,_V_)  if (*(_C_) && instring((_P_),(_C_))) return(_V_)
E 8
I 8
#define mtry(_P_,_C_,_V_)  if (*(_C_) && instringcase((_P_),(_C_))) return(_V_)
E 8
E 3

E 9
D 8
/* Compact string compare */
#define	streq(_X_,_S_)	(strncasecmp((_X_),(_S_), strlen(_X_)) == 0)

E 8
/* End %M% */
E 1
