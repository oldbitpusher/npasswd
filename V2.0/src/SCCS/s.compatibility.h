h38740
s 00047/00003/00175
d D 1.19 98/06/23 11:16:33 clyde 19 18
c Add copyright notice
e
s 00005/00000/00173
d D 1.18 98/03/26 11:19:29 clyde 18 17
c Define zeromem() macro to hide memset/bzero difference
e
s 00034/00015/00139
d D 1.17 97/09/23 13:50:46 clyde 17 16
c 1. Move some things around
c 2. Add more comments
e
s 00001/00005/00153
d D 1.16 96/09/13 16:26:41 clyde 16 15
c Remove use of #error directive
e
s 00005/00005/00153
d D 1.15 96/09/13 15:39:32 clyde 15 14
c Change NO_STRINGS comments
e
s 00003/00002/00155
d D 1.14 96/08/15 11:02:29 clyde 14 13
c Change use of HAS_STRRCHR
e
s 00005/00018/00152
d D 1.13 96/08/13 17:57:08 clyde 13 12
c 1. Remove uneeded things
c 2. Pick up system password length on OSF/1
e
s 00014/00010/00156
d D 1.12 96/08/06 14:14:26 clyde 12 11
c beta 3 cycle 1 checkin
e
s 00004/00001/00162
d D 1.11 96/03/27 09:30:57 clyde 11 10
c 1. Add I_DIRENT
c 2. Fix SCCS id comment
e
s 00002/00002/00161
d D 1.10 95/04/05 16:23:59 clyde 10 9
c Beta 3 development checkin
e
s 00096/00170/00067
d D 1.9 95/04/05 16:22:28 clyde 9 8
c Beta 3 development checkin
e
s 00029/00039/00208
d D 1.8 94/09/28 16:14:55 clyde 8 7
c Development checkin - lots of changes
e
s 00016/00000/00231
d D 1.7 94/07/14 17:01:32 clyde 7 6
c Add HP-UX stuff
e
s 00001/00000/00230
d D 1.6 94/05/19 10:34:48 clyde 6 5
c Add defintion of location of OSF/1 security database
e
s 00007/00004/00223
d D 1.5 94/05/17 15:29:58 clyde 5 4
c 1. Add support for OSF/1 security mode
c 2. Change SUN_SHADOW and ULTRIX_SHADOW to SUN_SECURITY and ULTRIX_SECURITY
e
s 00001/00001/00226
d D 1.4 94/04/01 10:07:18 clyde 4 3
c Strip version stuff from OS_DEC_OSF1
e
s 00011/00013/00216
d D 1.3 94/03/31 17:44:28 clyde 3 2
c Make varargs macros more generic
e
s 00083/00088/00146
d D 1.2 94/03/17 15:50:16 clyde 2 1
c Add Solaris 2 support
e
s 00234/00000/00000
d D 1.1 94/03/16 09:37:21 clyde 1 0
c date and time created 94/03/16 09:37:21 by clyde
e
u
U
t
T
I 1
/*
D 19
 *	Comptability and option selection defines for npasswd
D 10
 *	%W% %G%
E 10
I 10
D 11
 *	@(#)compatibility.h	1.9 05 Apr 1995
E 11
I 11
 *	%W% %G% %P%
E 19
I 19
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
E 19
E 11
E 10
 */
I 19

/*
 * Comptability and option selection defines for npasswd
 * %W% %G% (cc.utexas.edu) %P%
 */
E 19
I 3
#ifndef	_compatibility_h
#define	_compatibility_h 1
I 9
#include "config.h"
E 9
E 3

I 8
D 9
/* #define	SIGNAL_T	AC_RETSIGTYPE	/* Type of signal routines */
E 8
D 2
#undef	_ALLDONE_
#undef	CLIBDEFINES
E 2
I 2
D 3
/*#define	SIGNAL_T	void	/* Type of signal routines */
/*#define	SIG_TYPE_BSD	'b'	/* Use BSD signals */
/*#define	SIG_TYPE_POSIX	'p'	/* Use POSIX signals */
/*#define	SIG_TYPE_UNIX	'u'	/* Use traditional UNIX signals */
E 3
I 3
#define	SIGNAL_T	void	/* Type of signal routines */
#define	SIG_TYPE_BSD	'b'	/* Use BSD signals */
#define	SIG_TYPE_POSIX	'p'	/* Use POSIX signals */
#define	SIG_TYPE_UNIX	'u'	/* Use traditional UNIX signals */
E 3
E 2

E 9
D 2
#define	SIGFUNC_T	void
E 2
I 2
D 3
#define	SIGNAL_T	void
#define	SIG_TYPE_BSD	'b'
#define	SIG_TYPE_POSIX	'p'
#define	SIG_TYPE_UNIX	'u'

E 3
/*
 * Look in options.h for a full explanation of the feature selections
 */
I 8
D 9
#define TIME_H	<time.h>
#define ERRNO_H <errno.h>
E 8

E 9
E 2
#ifdef	OS_SUNOS_4			/* SunOS 4.X (up to 4.1.3) */
I 2
# define	NEED_CLIB_DECLS	1	/* Need to define some libc stuff */
D 9
# define	NEED_GETPASS	1	/* Use own version of getpass */
E 2
# define	OS_BSD		1	/* Generically BSD */
D 2
# define	HAS_SIGMASK	1	/* Generically BSD  */
# define	SUNOS_TTY	1	/* Use SunOS ioctls */
# define	NEED_GETPASS	1
# define	S5_PWAGING	1	/* Uses System 5 password aging */
E 2
D 8
# define	PW_COMMENT	1	/* Has pw_comment field */
I 2
# define	S5_PWAGING	1	/* Uses System 5 password aging */
E 8
I 8
# define	HAS_PW_COMMENT	1	/* Has pw_comment field */
# define	HAS_PW_AGE	1	/* Uses System 5 password aging */
E 8
# define	SIG_TYPE	SIG_TYPE_POSIX	/* Select signal type */
# define	SUNOS_TTY	1	/* Use SunOS ioctls */
E 2
D 5
# define	SUN_SHADOW	1	/* Change Sun shadow passwords */
E 5
I 5
# define	SUN_SECURITY	1	/* Change Sun shadow passwords */
E 5
D 2
# define	YP_PASSWD	1	/* Enable RPC password changes */
# define	USE_SYSLOG	1	/* Syslog messages */
E 2
I 2
# define	USE_MEMOPS	1	/* Use system 5 memory routines */
# define	USE_STRING_H	1	/* Include "string.h" */
E 9
D 8
# define	USE_SYSLOG	1	/* Use syslog messages */
E 8
E 2
# define	VENDOR_COMPAT	0	/* Full compatibilty with vendor prog */
D 2
# define	USE_SYS_TIME_H	1	/* Use <sys/time.h> */
# define TIME_H	<sys/time.h>
# 
typedef	void	(*signal_t);
#ifdef	_ALLDONE_
	ERROR_Too_many_os_selections_made
#else
# define	_ALLDONE_	1
E 2
I 2
D 8
# define	YP_PASSWD	1	/* Enable RPC password changes */
E 8
I 8
D 9
# define	YP_SUPPORT	1	/* Enable RPC password changes */
# undef		TIME_H
E 8
# define	TIME_H		<sys/time.h>	/* Time definitions */
# define	_OS_CHOSEN_	1
E 9
E 2
#endif
D 2
#endif
E 2

D 9
#ifdef	OS_SOLARIS_2			/* SunOS 5.X (Solaris 2.X) *?
# define	OS_SYS54	1	/* Mostly SVR4 */
D 2
# define	SYS5_TTY	1	/* Use SYS5 ioctls */
E 2
I 2
D 8
# define	PW_COMMENT	1	/* Has pw_comment field */
E 2
# define	S5_PWAGING	1	/* Uses System 5 password aging */
E 8
I 8
# define	HAS_PW_COMMENT	1	/* Has pw_comment field */
# define	HAS_PW_AGE	1	/* Uses System 5 password aging */
E 8
# define	S5_SHADOW	1	/* Uses System 5 password aging */
D 2
# define	PW_COMMENT	1	/* Has pw_comment field */
# define	YP_PASSWD	1	/* Enable RPC password changes */
# define	USE_SYSLOG	1	/* Syslog messages */
E 2
I 2
# define	SIG_TYPE	SIG_TYPE_POSIX
E 9
I 9
D 12
#ifdef	OS_SUNOS_5			/* SunOS 5.X (Solaris 2.X) *?
E 12
I 12
#ifdef	OS_SUNOS_5			/* SunOS 5.X (Solaris 2.X) */
E 12
E 9
# define	SYS5_TTY	1	/* Use SYS5 ioctls */
E 2
D 9
# define	USE_MEMOPS	1	/* Use system 5 memory routines */
D 2
typedef	void	(*signal_t);
#ifdef	_ALLDONE_
	ERROR_Too_many_os_selections_made
#else
# define	_ALLDONE_	1
E 2
I 2
# define	USE_STRING_H	1
D 8
# define	USE_SYSLOG	1	/* Syslog messages */
/* # define	YP_PASSWD	1	/* Enable RPC password changes */
E 8
I 8
# define	YP_SUPPORT	1	/* Enable RPC password changes */
E 8
#include <sys/systeminfo.h>
#define	gethostname(_b_, _l_) sysinfo(SI_HOSTNAME, _b_, _l_)
# define	_OS_CHOSEN_	1
E 9
E 2
#endif
D 2
#endif
E 2

D 9
#ifdef	OS_ULTRIX_4		/* Ultrix 4.X */
I 2
# define	DBM_PASSWD	1	/* Uses DBM lookaside files */
# define	NEED_FGETPWENT	1	/* Doesn't have fgetpwent(3) */
# define	NEED_PUTPWENT	1	/* Doesn't have putpwent(3) */
# define	NO_CLNT_SPERRNO	1	/* Doesn't have clnt_sperrno(3) */
E 2
# define	OS_BSD		1	/* Generically BSD  */
D 2
# define	USE_UNISTD_H 	1
E 2
I 2
D 8
# define	PW_COMMENT	1	/* Has pw_comment field */
E 8
I 8
# define	HAS_PW_COMMENT	1	/* Has pw_comment field */
E 8
# define	SIG_TYPE	SIG_TYPE_POSIX
# define	STD_PW_LEN	13	/* Length of standard pw string */
D 5
# define	ULTRIX_SHADOW	1	/* Use Ultrix security mode */
E 5
I 5
# define	ULTRIX_SECURITY	1	/* Use Ultrix security mode */
E 5
E 2
# define	USE_STDLIB_H 	1
# define	USE_STRING_H	1
D 2
# define	CLIBDEFINES	1
# define	HAS_SIGMASK	1	/* Generically BSD  */
# define	ULTRIX_SHADOW	1	/* Use Ultrix security mode */
# define	NO_CLNT_SPERRNO	1	/* Doesn't have clnt_sperrno(3) */
# define	NEED_PUTPWENT	1	/* Doesn't have putpwent(3) */
# define	NEED_FGETPWENT	1	/* Doesn't have fgetpwent(3) */
# define	PW_COMMENT	1	/* Has pw_comment field */
# define	YP_PASSWD	1	/* Enable RPC password changes */
# define	DBM_PASSWD	1	/* Uses DBM lookaside files */
E 2
D 8
# define	USE_SYSLOG	1	/* Syslog messages */
E 8
D 2
# define	STD_PW_LEN	13	/* Length of standard pw string */
# define	USE_SYS_TIME_H	0	/* Need to include <time.h> */
E 2
I 2
# define	USE_UNISTD_H 	1
E 2
# define	USE_getsvc	1	/* Use DEC's getsvc() call */
I 2
D 8
# define	YP_PASSWD	1	/* Enable RPC password changes */
E 8
I 8
# define	YP_SUPPORT	1	/* Enable RPC password changes */
E 8
E 2
extern char	*crypt16();
extern char	*getpass();
D 2
typedef	void	(*signal_t);
# ifdef	_ALLDONE_
   ERROR_Too_many_os_selections_made
# else
#  define	_ALLDONE_	1
# endif
E 2
I 2

# define	_OS_CHOSEN_	1
# undef	CPP_HAS_ERROR
E 2
#endif

E 9
D 4
#ifdef	OS_DEC_OSF1_1			/* DEC OSF/1 version 1.X */
E 4
I 4
#ifdef	OS_DEC_OSF1			/* DEC OSF/1 version 1.X */
E 4
D 2
# define	OS_BSD		1	/* Generically BSD */
# define	CLIBDEFINES	1
# define	USE_UNISTD_H 	1
# define	USE_STDLIB_H 	1
# define	USE_MEMOPS	1	/* Use system 5 memory routines */
# define	HAS_SIGMASK	1	/* Generically BSD  */
# define	NEED_GETPASS	1
E 2
I 2
D 9
# define	DBM_PASSWD	1	/* Uses DBM lookaside files */
E 2
# define	NEED_FGETPWENT	1	/* Doesn't have fgetpwent(3) */
D 2
# undef		S5_PWAGING		/* No password aging */
E 2
I 2
# define	NEED_GETPASS	1
# define	OS_BSD		1	/* Generically BSD */
E 2
D 8
# define	PW_COMMENT	1	/* Has pw_comment field */
E 8
I 8
# define	HAS_PW_COMMENT	1	/* Has pw_comment field */
E 8
D 2
# define	YP_PASSWD	1	/* Enable RPC password changes */
# define	DBM_PASSWD	1	/* Uses DBM lookaside files */
E 2
I 2
# define	SIG_TYPE	SIG_TYPE_POSIX
# define	USE_MEMOPS	1	/* Use system 5 memory routines */
# define	USE_STDLIB_H 	1
E 2
D 8
# define	USE_SYSLOG	1	/* Syslog messages */
D 2
# undef		VENDOR_COMPAT
E 2
# define	USE_SYS_TIME_H	1	/* Use <sys/time.h> */
E 8
I 2
# define	USE_UNISTD_H 	1
E 2
# define	USE_getsvc	1	/* Use DEC's getsvc() call */
I 2
D 8
# define	YP_PASSWD	1	/* Enable RPC password changes */
E 8
I 8
# define	YP_SUPPORT	1	/* Enable RPC password changes */
E 8
D 5
# undef		S5_PWAGING		/* No password aging */
E 5
I 5
# define	OSF1_SECURITY	1	/* OSF/1 security */
I 6
# define	OSF1_TCB	"/tcb"	/* Where security db are kept */
E 9
E 6
E 5
# undef		VENDOR_COMPAT
E 2
# undef		_NO_PROTO
D 2
typedef	void	(*signal_t);
extern char    *crypt();
E 2
D 5
extern char    *crypt16();
E 5
I 5
D 9
# include	<sys/secdefines.h>
# include	<sys/security.h>
# include	<sia.h>
# include	<prot.h>
E 5
D 2
#ifdef	_ALLDONE_
	ERROR_Too_many_os_selections_made
#else
# define	_ALLDONE_	1
E 2
I 2
# define	_OS_CHOSEN_	1
E 9
E 2
#endif
D 2
#endif
E 2

D 9
#ifdef	OS_AIX_3			/* AIX 3.2> */
# define	NEED_FGETPWENT	1	/* Doesn't have fgetpwent(3) */
D 8
# define	S5PW_AGE	1	/* Has pw_age field */
E 8
I 8
# define	HAS_PW_AGE	1	/* Has pw_age field */
E 8
# define	USE_MEMOPS	1	/* Use system 5 memory routines */
D 2
# ifdef	_ALLDONE_
   ERROR_Too_many_os_selections_made
# else
#  define	_ALLDONE_	1
# endif
E 2
I 2
# define	_OS_CHOSEN_	1
E 2
#endif

#ifdef	OS_BSD_43			/* Plain 4.3BSD system */
D 2
# define	OS_BSD		1	/* Generically BSD  */
# define	HAS_SIGMASK	1	/* Generically BSD  */
E 2
# define	DBM_PASSWD	1	/* Has DBM lookaside files */
I 2
# define	OS_BSD		1	/* Generically BSD  */
E 2
D 8
# define	PW_COMMENT	1	/* Has pw_comment field */
E 8
I 8
# define	HAS_PW_COMMENT	1	/* Has pw_comment field */
E 8
I 2
# define	SIG_TYPE	SIG_TYPE_BSD
E 2
D 8
# define	USE_SYSLOG	1	/* Syslog messages */
E 8
D 2
# ifdef	_ALLDONE_
   ERROR_Too_many_os_selections_made
# else
#  define	_ALLDONE_	1
E 2
I 2
# define	_OS_CHOSEN_	1
E 2
# endif
D 2
# endif
E 2

D 8
#ifdef	OS_SYS_5123		/* System V R[123]* */
E 8
I 8
#ifdef	OS_SYS_5		/* System V R[123]* */
E 8
# define	OS_SYS5		1
# define	NEED_RENAME	1
# define	SYS5_TTY	1
# define	USE_MEMOPS	1	/* Use system 5 memory routines */
D 2
# ifdef	_ALLDONE_
   ERROR_Too_many_os_selections_made
# else
#  define	_ALLDONE_	1
# endif
E 2
I 2
# define	_OS_CHOSEN_	1
E 2
#endif

#ifdef	OS_SYS_54			/* System V R4 */
# define	OS_SYS5		1
# define	SYS5_TTY	1
# define	USE_MEMOPS	1	/* Use system 5 memory routines */
D 2
# ifdef	_ALLDONE_
   ERROR_Too_many_os_selections_made
# else
#  define	_ALLDONE_	1
# endif
E 2
I 2
# define	_OS_CHOSEN_	1
E 2
#endif

E 9
I 7
#ifdef OS_HPUX
D 8
# define	OS_SYS5               1
# define	SYS5_TTY              1
# define	USE_MEMOPS            1     /* Use system 5 memory routines */
# define	PW_COMMENT            1     /* Has pw_comment field */
# define	NO_CLNT_SPERRNO       1     /* Doesn't have clnt_sperrno(3) */
# define	SIG_TYPE              SIG_TYPE_POSIX
# define	USE_SYSLOG            1     /* Syslog messages */
# define	POSIX_ENV             1     /* HP's have a posix environment */
# define	USE_STRING_H          1
# define	USE_UNISTD_H          1
# define	USE_SYS_TIME_H        1	 /* Use <sys/time.h> */
E 8
I 8
D 9
# define	OS_SYS5		1
E 9
# define	SYS5_TTY	1
D 9
# define	USE_MEMOPS	1     /* Use system 5 memory routines */
# define	HAS_PW_COMMENT	1     /* Has pw_comment field */
# define	NO_CLNT_SPERRNO	1     /* Doesn't have clnt_sperrno(3) */
# define	SIG_TYPE	SIG_TYPE_POSIX
E 9
# define	POSIX_ENV	1     /* HP's have a posix environment */
D 9
# define	USE_STRING_H	1
# define	USE_UNISTD_H	1
E 8
extern char     *getpass();
D 8
# define      _OS_CHOSEN_           1
E 8
I 8
# define      _OS_CHOSEN_	1
E 9
E 8
#endif

E 7
/*
I 2
D 9
 * Somehow I want to blow up if more than one OS selection was made
 */
#ifndef	_OS_CHOSEN_
	ERROR-operating-system-environment-not-defined
#endif

/*
E 2
 * Define compatabilty macros to hide a lot of the difference between
 * UNIX variants.
 */
#ifdef	USE_MEMOPS
			/* String operators */
# include <memory.h>
# define INDEX(s, c)	strchr(s, c)
# define RINDEX(s, c)	strrchr(s, c)
# define BZERO(a, l)	memset(a, 0, l)
# define BCOPY(s, d, l)	memcpy(d, s, l)
#else
# define INDEX(s, c)	index(s, c)
# define RINDEX(s, c)	rindex(s, c)
# define BZERO(a, l)	bzero(a, l)
# define BCOPY(s, d, l)	bcopy(s, d, l)
#endif

/*
 * Stuff needed for ANSI C compiliation environment
 */
I 3
/* Varargs operators */
I 8
/* #ifdef	STDC_VARARGS */
E 8
E 3
#ifdef	__STDC__
D 3
#include <stdlib.h>
			/* Varargs operators */
E 3
I 3
# include <stdlib.h>
E 3
# include <stdarg.h>
D 3
# define VA_DCL(_X_)	(char *_X_, ...)
E 3
I 3
# define VA_DCL(_X_) (_X_, ...)
E 3
# define VA_START(X,Y)	va_start(X,Y)
#else
# include <varargs.h>
D 3
# define VA_DCL(_X_)	(va_alist) va_dcl
E 3
I 3
# define VA_DCL(_X_) (va_alist) va_dcl
E 3
# define VA_START(X,Y)	va_start(X)
#endif

/*
E 9
 * Pull in system include files
 */
D 8
#ifndef	TIME_H
D 2
# define	TIME_H	<time.h>
E 2
I 2
# define TIME_H	<time.h>
E 2
#endif

#ifndef	ERRNO_H
D 2
# define	ERRNO_H	<errno.h>
E 2
I 2
# define ERRNO_H <errno.h>
E 2
#endif

E 8
D 9
#include <sys/param.h>
E 9
I 9
#ifdef	I_SYS_PARAM
# include <sys/param.h>
#endif
E 9
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <signal.h>
#include <stdio.h>
I 8
#include <syslog.h>
E 8
#include <fcntl.h>
#include <pwd.h>
D 9
#include ERRNO_H
#include TIME_H
I 2

E 2
#if	USE_UNISTD_H
E 9
I 9
#include <errno.h>
#ifdef	I_SYS_TIME
# include <sys/time.h>
#else
# include <time.h>
#endif
#ifdef	I_MEMORY
# include <memory.h>
#endif
#ifdef	I_UNISTD
E 9
# include <unistd.h>
#endif
D 9
#if	USE_STDLIB_H
E 9
I 9
#ifdef	I_STDLIB
E 9
# include <stdlib.h>
I 11
#endif
#ifdef	I_DIRENT
# include <dirent.h>
E 11
#endif
D 9
#if	USE_STRINGS_H
# include <strings.h>
E 9
I 9

#ifndef	NO_STRINGS
/*
D 15
 * On Solaris 2, cannot include both <string.h> and <rpc/rpc.h> because
 * the latter includes <memory.h> which has a conflicting definition of
 * some of the memcpy routines.  In order for the pwm_nis module to compile,
 * <string.h> cannot be included.
 * Stupid, stupid rat creatures!
E 15
I 15
 * On some Solaris 2.N (N < 5) systems, cannot include both
 * <string.h> and <rpc/rpc.h> because the latter includes <memory.h>
 * which has a conflicting definition of some of the memcpy routines.
 * In order for the pwm_nis module to compile, <string.h> cannot be included.
 * This error is fixed in 2.5.
E 15
 */
# ifdef	I_STRING
#  include <string.h>
# else
#  include <strings.h>
# endif
E 9
#endif
D 9
#if	USE_STRING_H
# include <string.h>
#endif
E 9

I 17
/*
 * POSIX API not fully supported
 */
E 17
#ifdef	POSIX_ENV		/* XXX */
/* #define	_POSIX_SOURCE	1	*/
#include <fcntl.h>
#include <limits.h>
#include <locale.h>
D 9
#include <stdarg.h>
E 9
#include <stddef.h>
D 9
#include <stdlib.h>
#include <unistd.h>
E 9
#endif

I 2
/*
D 9
 * Signal handler type
E 9
I 9
D 17
 * Figure out what kind of signal handling we have
E 17
I 17
 * Brands of signal handling
E 17
E 9
 */
D 9
typedef	SIGNAL_T	(*signal_t)();
E 9
I 9
#define	SIG_TYPE_BSD	'b'	/* Use BSD signals */
#define	SIG_TYPE_POSIX	'p'	/* Use POSIX signals */
#define	SIG_TYPE_UNIX	'u'	/* Use traditional UNIX signals */

#define	SIG_TYPE		SIG_TYPE_UNIX
#ifdef	HAS_SIGBLOCK
# undef	SIG_TYPE
# define	SIG_TYPE	SIG_TYPE_BSD
#endif
#ifdef	HAS_POSIX_SIGNALS
# undef	SIG_TYPE
# define	SIG_TYPE	SIG_TYPE_POSIX
#endif

/*
D 17
 * Define compatabilty macros to hide a lot of the difference between
 * UNIX variants.
E 17
I 17
 * Macros to hide differences.
E 17
 */
D 13
#ifndef	HAS_BZERO
# define bzero(a, l)	memset((a),0,(l))
#endif
D 12
#ifndef	HAS_BCOPY
# define bcopy(s, d, l)	memcpy((d),(s),(l))
E 12
I 12
#ifndef	HAS_MEMCPY
# define memcpy(d, s, l) bcopy((s), (d), (l))
E 12
#endif
E 13
D 12
#ifndef	HAS_INDEX
# define index(s, c)	strchr((s),(c))
E 12
I 12
#ifndef	HAS_STRCHR
# define strchr(s, c)	index((s),(c))
E 12
D 14
#endif
D 12
#ifndef	HAS_RINDEX
# define rindex(s, c)	strrchr((s),(c))
E 12
I 12
#ifndef	HAS_STRRCHR
E 14
# define strrchr(s, c)	rindex((s),(c))
E 12
#endif
I 17

E 17
I 14
#ifdef	HAS_MEMCPY
# define	bcopy(s,d,c)	memcpy((d),(s),(c))
#endif
E 14

#ifndef	HAS_GETHOSTNAME
# ifdef	HAS_SYSINFO
#  include <sys/systeminfo.h>
#  define gethostname(_b_, _l_) sysinfo(SI_HOSTNAME, _b_, _l_)
D 12
# else
E 12
I 12
# else 	/* HAS_SYSINFO */
D 16
#  ifdef	__STDC__
#	error No gethostname()
#  else		/* STDC */
E 12
	ERROR-gethostname-not-found
D 12
# endif
#endif
E 12
I 12
#  endif	/* STDC */
E 16
I 16
   ERROR-gethostname-not-found
E 16
# endif /* HAS_SYSINFO */
#endif	/* HAS_GETHOSTNAME */
E 12

I 17
/*
 * Macros to hide the differences between varargs and stdargs
 */
#ifdef	__STDC__
# include <stdarg.h>
# define VA_DCL(_X_) (_X_, ...)
# define VA_START(X,Y)	va_start(X,Y)
#else
# include <varargs.h>
# define VA_DCL(_X_) (va_alist) va_dcl
# define VA_START(X,Y)	va_start(X)
#endif


/*
 * Pull in includes for some UNIXes
 */
E 17
D 13
/*
 * If this system has the crypt16() routine, a forward declaration is needed.
 */
#ifdef	HAS_CRYPT16
extern char	*crypt16();
#endif

E 13
#ifdef	OSF1_AUTH
I 17
 /*
  * OSF/1 auth hooks are in serveral places, so do the includes here
  */
E 17
# include <sys/secdefines.h>
# include <sys/security.h>
# include <sia.h>
# include <prot.h>
# define OSF1_TCB	"/tcb"
I 13
# ifdef	AUTH_MAX_PASSWD_LENGTH
#	define	SYSTEM_PASSWD_MAX	AUTH_MAX_PASSWD_LENGTH
D 17
	/* Not really, it depend if C2 security is being used and what
	 * encryption routine the user has */
E 17
I 17
	/*
	 * Not really - it depends if C2 security is being used and which
	 * encryption routine is being used (crypt vs bigcrypt).
	 * But this is a reasonable default to start with.
	 */
E 17
# endif
E 13
#endif

I 18
#ifdef	HAS_MEMSET
# define	zeromem(_O_,_S_) memset((void *)_O_, 0, _S_)
#else
# define	zeromem(_O_,_S_) bzero((char *)_O_, _S_)
#endif
E 18
D 17
/* Varargs operators */
#ifdef	__STDC__
# include <stdarg.h>
# define VA_DCL(_X_) (_X_, ...)
# define VA_START(X,Y)	va_start(X,Y)
#else
# include <varargs.h>
# define VA_DCL(_X_) (va_alist) va_dcl
# define VA_START(X,Y)	va_start(X)
#endif
E 17
E 9

I 17
/*
 * If this isn't already supplied by a system define
 */
E 17
E 2
#ifndef MAXHOSTNAMLEN
# define MAXHOSTNAMLEN 64
#endif
I 2

D 13
/*
 * Declarations for library routines that aren't in unistd.h or stdlib.h
 */
extern char    *crypt();
E 2

E 13
I 3
#endif	/* _compatibility_h */
E 3
D 10
/* End %M% */
E 10
I 10
D 19
/* End compatibility.h */
E 19
I 19
/* End %M% */
E 19
E 10
E 1
