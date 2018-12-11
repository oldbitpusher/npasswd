/*
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
 * @(#)common.h	1.13 11/17/98 (cc.utexas.edu) /usr/share/src/private/ut/share/bin/passwd/V2.0/src/Common/SCCS/s.common.h
 *
 * Function declarations for routines in the common module library
 *
 */
#ifndef	common_h
#define	common_h 1

/*
 * Some compilers (AIX 4) don't like seeing the prototype and the declaration
 * at the same time, especially when the prototype has ellipses (...)
 * So these are gaurded against with #define and #ifndef
 */

typedef struct {
	char	*name;
	int	level;
	char	*help;
} debug_table;

/*
 * Routines in messages.c
 */
#ifndef	_messages_c
 int	get_debug();
 void	init_debug _((int));
 void	set_debug _((char *, debug_table *));
 void	set_die_callback _((void(*)()));
 void	set_debug_tag _((char *));
 void	debug _((int, char *, ...));
 void	die _((char *, ...));
 void	warn _((char *, ...));
 void	logdie _((char *, ...));
 void	logerr _((char *, ...));
#endif

#ifdef	npasswd_h
/*
 * Routines in singals.c
 */
#ifndef	_signals_c
  void	block_signals _((struct sigblk *, ...));
  void	unblock_signals _((struct sigblk *));
#endif

/*
 * Routines in mpw_util.c
 */
struct mpasswd *copympwent _((struct mpasswd *, struct mpasswd *));
void printmpwent _((struct mpasswd *));

#endif	/* npasswd_h */

/*
 * Routines in pw_util.c
 */
#ifndef HAS_PUTPWENT
 void	putpwent _((struct passwd *p, FILE *));
#endif

#ifndef HAS_FGETPWENT
 struct passwd *fgetpwent _((FILE *));
#endif

#ifndef HAS_SPUTPWENT
 char *sputpwent _((struct passwd *, char *));
#endif

struct passwd *sgetpwent _((char *));
struct passwd *copypwent _((struct passwd *, struct passwd *));
struct passwd *fgetpwnam _((char *, char *));

/*
 * Routines in getpass.c
 */
void	get_password _((char *, char *, char *, int));
char	*np_getpass _((char *));
int	password_cmp _((char *, char *));

/*
 * Routines in file_utils.c
 */
size_t	FileSize _((char *));
int	OpenWithLock _((char *));
int	MakeLockTemp _((char *));
void	FixPwFileMode _((char *, char *));

/*
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
 * Routines in other modules
 */
void	pager _((FILE *));
char	**split _((char *, char, char *, char));
int	xatoi _((char *, char **, int *));
int	decode_boolean _((char *));
int	decode_int _((char *));
void	decode_string _((char *, char *, int));
void	chop_nl _((char *));

#ifndef HAS_STRCASECMP
 int	strcasecmp _((char*, char *));
 int	strncasecmp _((char*, char *));
#endif

#ifndef	HAS_STRDUP
 char	*strdup _((char *));
#endif

#endif	/* common_h */
/* End common.h */
