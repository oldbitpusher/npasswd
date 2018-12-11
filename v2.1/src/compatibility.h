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
 * Comptability and option selection defines for npasswd
 * $Id: compatibility.h,v 1.19 1998/06/23 00:00:00 clyde Exp $ (cc.utexas.edu) %P%
 */
#ifndef	_compatibility_h
#define	_compatibility_h 1
#include "config.h"

/*
 * Look in options.h for a full explanation of the feature selections
 */
#ifdef	OS_SUNOS_4			/* SunOS 4.X (up to 4.1.3) */
# define	NEED_CLIB_DECLS	1	/* Need to define some libc stuff */
# define	VENDOR_COMPAT	0	/* Full compatibilty with vendor prog */
#endif

#ifdef	OS_SUNOS_5			/* SunOS 5.X (Solaris 2.X) */
# define	SYS5_TTY	1	/* Use SYS5 ioctls */
#endif

#ifdef	OS_DEC_OSF1			/* DEC OSF/1 version 1.X */
# undef		VENDOR_COMPAT
# undef		_NO_PROTO
#endif

#ifdef OS_HPUX
# define	SYS5_TTY	1
# define	POSIX_ENV	1     /* HP's have a posix environment */
#endif

/*
 * Pull in system include files
 */
#ifdef	I_SYS_PARAM
# include <sys/param.h>
#endif
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <signal.h>
#include <stdio.h>
#include <syslog.h>
#include <fcntl.h>
#include <pwd.h>
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
# include <unistd.h>
#endif
#ifdef	I_STDLIB
# include <stdlib.h>
#endif
#ifdef	I_DIRENT
# include <dirent.h>
#endif

#ifndef	NO_STRINGS
/*
 * On some Solaris 2.N (N < 5) systems, cannot include both
 * <string.h> and <rpc/rpc.h> because the latter includes <memory.h>
 * which has a conflicting definition of some of the memcpy routines.
 * In order for the pwm_nis module to compile, <string.h> cannot be included.
 * This error is fixed in 2.5.
 */
# ifdef	I_STRING
#  include <string.h>
# else
#  include <strings.h>
# endif
#endif

/*
 * POSIX API not fully supported
 */
#ifdef	POSIX_ENV		/* XXX */
/* #define	_POSIX_SOURCE	1	*/
#include <fcntl.h>
#include <limits.h>
#include <locale.h>
#include <stddef.h>
#endif

/*
 * Brands of signal handling
 */
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
 * Macros to hide differences.
 */
#ifndef	HAS_STRCHR
# define strchr(s, c)	index((s),(c))
# define strrchr(s, c)	rindex((s),(c))
#endif

#ifdef	HAS_MEMCPY
# define	bcopy(s,d,c)	memcpy((d),(s),(c))
#endif

#ifndef	HAS_GETHOSTNAME
# ifdef	HAS_SYSINFO
#  include <sys/systeminfo.h>
#  define gethostname(_b_, _l_) sysinfo(SI_HOSTNAME, _b_, _l_)
# else 	/* HAS_SYSINFO */
   ERROR-gethostname-not-found
# endif /* HAS_SYSINFO */
#endif	/* HAS_GETHOSTNAME */

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
#ifdef	OSF1_AUTH
 /*
  * OSF/1 auth hooks are in serveral places, so do the includes here
  */
# include <sys/secdefines.h>
# include <sys/security.h>
# include <sia.h>
# include <prot.h>
# define OSF1_TCB	"/tcb"
# ifdef	AUTH_MAX_PASSWD_LENGTH
#	define	SYSTEM_PASSWD_MAX	AUTH_MAX_PASSWD_LENGTH
	/*
	 * Not really - it depends if C2 security is being used and which
	 * encryption routine is being used (crypt vs bigcrypt).
	 * But this is a reasonable default to start with.
	 */
# endif
#endif

#ifdef	HAS_MEMSET
# define	zeromem(_O_,_S_) memset((void *)_O_, 0, _S_)
#else
# define	zeromem(_O_,_S_) bzero((char *)_O_, _S_)
#endif

/*
 * If this isn't already supplied by a system define
 */
#ifndef MAXHOSTNAMLEN
# define MAXHOSTNAMLEN 64
#endif

#endif	/* _compatibility_h */
/* End $RCSfile: compatibility.h,v $ */
