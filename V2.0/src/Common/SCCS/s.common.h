h42878
s 00044/00000/00121
d D 1.13 98/11/17 15:43:59 clyde 13 12
c Add copyright notice
e
s 00012/00000/00109
d D 1.12 98/11/17 15:33:14 clyde 12 11
c Add routines from pager.c and term.c
e
s 00003/00001/00107
d D 1.11 98/10/13 16:46:50 clyde 11 10
c 1. Change FileSizeDiff() to FileSize()
c 2. Add OpenWithLock()
e
s 00006/00002/00102
d D 1.10 98/07/09 14:14:34 clyde 10 9
c 1. Add help field to debug table
c 2. Rename debug_levels to debug_table
c 3. Add protos for set_debug(), set_debug_tag(), get_debug() and init_debug()
e
s 00006/00000/00098
d D 1.9 98/07/02 16:41:59 clyde 9 8
c 1. Add set_debug()
c 2. Add debug_table typedef
e
s 00016/00002/00082
d D 1.8 98/04/30 16:31:44 clyde 8 7
c Add definitions of new comobj routines
e
s 00040/00023/00044
d D 1.7 97/09/23 12:31:28 clyde 7 6
c 1. Group decls by what file they are for
c 2. Wrap some decls in guard #ifdefs (keep AIX cc happy)
e
s 00001/00001/00066
d D 1.6 96/09/13 15:40:50 clyde 6 5
c Fix declaration of set_die_callback()
e
s 00013/00013/00054
d D 1.5 96/08/29 13:02:22 clyde 5 4
c Remove 'const' declarations (too much compiler pain)
e
s 00001/00000/00066
d D 1.4 96/08/15 11:03:17 clyde 4 3
c add set_die_callback()
e
s 00013/00013/00053
d D 1.3 96/08/13 18:00:56 clyde 3 2
c Add const declarations where useful
e
s 00007/00003/00059
d D 1.2 96/08/09 16:19:04 clyde 2 1
c Beta 3 development checkin 2
e
s 00062/00000/00000
d D 1.1 96/08/07 15:19:16 clyde 1 0
c date and time created 96/08/07 15:19:16 by clyde
e
u
U
f e 0
t
T
I 1
/*
I 13
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

/*
E 13
 * %W% %G% (cc.utexas.edu) %P%
 *
 * Function declarations for routines in the common module library
 *
 */
#ifndef	common_h
#define	common_h 1

D 7
#ifndef	HAS_STRDUP
char	*strdup _((char *));
#endif
void	chop_nl _((char *));
E 7
I 7
/*
 * Some compilers (AIX 4) don't like seeing the prototype and the declaration
 * at the same time, especially when the prototype has ellipses (...)
 * So these are gaurded against with #define and #ifndef
 */
E 7

I 9
typedef struct {
	char	*name;
	int	level;
D 10
} debug_levels;
E 10
I 10
	char	*help;
} debug_table;
E 10

E 9
/*
 * Routines in messages.c
 */
I 4
D 6
void	set_die_callback _((void *));
E 6
I 6
D 7
void	set_die_callback _((void(*)()));
E 6
E 4
void	debug _((int, char *, ...));
void	die _((char *, ...));
void	warn _((char *, ...));
void	logdie _((char *, ...));
void	logerr _((char *, ...));
E 7
I 7
#ifndef	_messages_c
I 10
 int	get_debug();
 void	init_debug _((int));
 void	set_debug _((char *, debug_table *));
E 10
 void	set_die_callback _((void(*)()));
I 9
D 10
 void	setdebug _((char *, debug_levels *));
E 10
I 10
 void	set_debug_tag _((char *));
E 10
E 9
 void	debug _((int, char *, ...));
 void	die _((char *, ...));
 void	warn _((char *, ...));
 void	logdie _((char *, ...));
 void	logerr _((char *, ...));
#endif
E 7

I 7
#ifdef	npasswd_h
E 7
/*
 * Routines in singals.c
 */
I 2
D 7
#ifdef	npasswd_h
E 7
I 7
#ifndef	_signals_c
  void	block_signals _((struct sigblk *, ...));
  void	unblock_signals _((struct sigblk *));
#endif
E 7

E 2
D 7
void	block_signals _((struct sigblk *, ...));
D 3
void	unblock_signals _((struct sigblk *));
E 3
I 3
D 5
void	unblock_signals _((const struct sigblk *));
E 5
I 5
void	unblock_signals _((struct sigblk *));
E 5
E 3

E 7
I 7
/*
 * Routines in mpw_util.c
 */
E 7
I 2
D 3
struct mpasswd *copympwent _((struct mpasswd *));
void printmpwent _((struct mpasswd *));
E 3
I 3
D 5
struct mpasswd *copympwent _((const struct mpasswd *, struct mpasswd *));
void printmpwent _((const struct mpasswd *));
E 5
I 5
struct mpasswd *copympwent _((struct mpasswd *, struct mpasswd *));
void printmpwent _((struct mpasswd *));
E 5
E 3

D 8
#endif
E 8
I 8
#endif	/* npasswd_h */
E 8

E 2
D 7
#ifndef HAS_STRCASECMP
int	strcasecmp _((char*, char *));
int	strncasecmp _((char*, char *));
#endif

E 7
I 7
/*
 * Routines in pw_util.c
 */
E 7
#ifndef HAS_PUTPWENT
D 3
void	putpwent _((struct passwd *p, FILE *));
E 3
I 3
D 5
void	putpwent _((const struct passwd *p, FILE *));
E 5
I 5
D 7
void	putpwent _((struct passwd *p, FILE *));
E 7
I 7
 void	putpwent _((struct passwd *p, FILE *));
E 7
E 5
E 3
#endif

#ifndef HAS_FGETPWENT
D 7
struct passwd *fgetpwent _((FILE *));
E 7
I 7
 struct passwd *fgetpwent _((FILE *));
E 7
#endif

#ifndef HAS_SPUTPWENT
D 3
char *sputpwent _((struct passwd *, char *));
E 3
I 3
D 5
char *sputpwent _((const struct passwd *, char *));
E 5
I 5
D 7
char *sputpwent _((struct passwd *, char *));
E 7
I 7
 char *sputpwent _((struct passwd *, char *));
E 7
E 5
E 3
#endif

D 3
struct passwd *sgetpwent _((char *));
struct passwd *copypwent _((struct passwd *, struct passwd *));
struct passwd *fgetpwnam _((char *, char *));
E 3
I 3
D 5
struct passwd *sgetpwent _((const char *));
struct passwd *copypwent _((const struct passwd *, struct passwd *));
struct passwd *fgetpwnam _((const char *, const char *));
E 5
I 5
struct passwd *sgetpwent _((char *));
struct passwd *copypwent _((struct passwd *, struct passwd *));
struct passwd *fgetpwnam _((char *, char *));
E 5
E 3

I 7
/*
I 8
 * Routines in getpass.c
 */
void	get_password _((char *, char *, char *, int));
char	*np_getpass _((char *));
int	password_cmp _((char *, char *));

/*
 * Routines in file_utils.c
 */
D 11
size_t	FileSizeDiff _((char *, char *));
E 11
I 11
size_t	FileSize _((char *));
int	OpenWithLock _((char *));
E 11
int	MakeLockTemp _((char *));
void	FixPwFileMode _((char *, char *));

/*
I 12
 * Routines in term.c
 */
int	term_get_fd();
void	term_set_fd _((int));
void	term_save();
void	term_restore();
void	term_echo _((int));
void	term_raw _((int));
int	term_read _((char *, size_t));

/*
E 12
E 8
 * Routines in other modules
 */
I 12
void	pager _((FILE *));
E 12
E 7
D 2
struct mpasswd *copympwent _((struct mpasswd *));
void printmpwent _((struct mpasswd *));

E 2
D 3
char	**split _((char *, char, char *, char));
int	xatoi _((char *, char **, int *));
E 3
I 3
D 5
char	**split _((const char *, const char, const char *, const char));
int	xatoi _((const char *, char **, int *));
E 5
I 5
char	**split _((char *, char, char *, char));
int	xatoi _((char *, char **, int *));
E 5
E 3
D 7

E 7
D 3
int	decode_boolean _((char *));
int	decode_int _((char *));
void	decode_string _((char *, char *, int));
E 3
I 3
D 5
int	decode_boolean _((const char *));
int	decode_int _((const char *));
void	decode_string _((const char *, const char *, int));
E 5
I 5
int	decode_boolean _((char *));
int	decode_int _((char *));
void	decode_string _((char *, char *, int));
I 7
void	chop_nl _((char *));
E 7
E 5
E 3

I 7
#ifndef HAS_STRCASECMP
 int	strcasecmp _((char*, char *));
 int	strncasecmp _((char*, char *));
E 7
#endif
I 7

#ifndef	HAS_STRDUP
 char	*strdup _((char *));
#endif

D 8
#endif
E 8
I 8
#endif	/* common_h */
E 8
E 7
/* End %M% */
E 1
