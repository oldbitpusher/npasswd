/*
 * Copyright (C) 2002  The University of Texas at Austin ("U. T. Austin").
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  Contact: npasswd-support@www.utexas.edu
 *
 */

/*
 * $Id: common.h,v 1.14 2002/10/02 15:58:53 clyde Exp $
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
/* End $RCSfile: common.h,v $ */
