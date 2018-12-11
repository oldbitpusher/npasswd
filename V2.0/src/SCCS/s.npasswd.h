h63864
s 00002/00001/00143
d D 1.31 98/07/17 16:32:55 clyde 31 30
c Add new code to permission enum
e
s 00000/00006/00144
d D 1.30 98/07/09 14:19:10 clyde 30 29
c Remove global vars svc, ProgramName, DebugLevel and pwReadTries
e
s 00001/00008/00149
d D 1.29 98/04/21 10:56:33 clyde 29 28
c Remove some function prototypes
e
s 00005/00001/00152
d D 1.28 97/09/23 12:20:16 clyde 28 27
c 1.Wrap pw_comment if PWCOMMENT ifdef
c 2. Fix Signal_t type
c 3. Add "orignal password" field to struct mpasswd
e
s 00001/00001/00152
d D 1.27 97/06/18 13:35:03 clyde 27 26
c 1. Remove getpass() decl
c 2. Add np_getpass() decl
e
s 00002/00000/00151
d D 1.26 97/05/23 11:13:56 clyde 26 25
c Ifdef PWQUOTA use of pw_quota
e
s 00003/00000/00148
d D 1.25 97/05/05 10:33:33 clyde 25 24
c Add definitions for LockTries & LockCycle
e
s 00003/00000/00145
d D 1.24 96/09/23 17:17:07 clyde 24 23
c Add uid/gid/mode elements to struct passwd_files
e
s 00012/00018/00133
d D 1.23 96/08/29 13:00:54 clyde 23 22
c 1. Remote NEED_GETPASS
c 2. Remove 'const' declarations (too much compiler pain)
c 
e
s 00002/00002/00149
d D 1.22 96/08/14 17:59:37 clyde 22 21
c Change pwsvc -> pw_svc
e
s 00006/00001/00145
d D 1.21 96/08/14 11:33:19 clyde 21 20
c Beta 3: compiles under OSF/1 3.2
e
s 00019/00014/00127
d D 1.20 96/08/13 16:50:54 clyde 20 19
c Add lots of const decls 
e
s 00012/00060/00129
d D 1.19 96/08/09 16:16:40 clyde 19 18
c Beta 3 development checkin 2
e
s 00056/00123/00133
d D 1.18 96/08/06 14:14:32 clyde 18 17
c beta 3 cycle 1 checkin
e
s 00015/00015/00241
d D 1.17 96/04/03 14:20:59 clyde 17 16
c Rename some elements of the mpasswd struct
e
s 00000/00001/00256
d D 1.16 96/04/01 14:14:47 clyde 16 15
c Eliminate the "ypcompat" service number
e
s 00014/00005/00243
d D 1.15 96/03/29 11:39:44 clyde 15 14
c 1. Change debug level numbers, fill in empty slots
c 2. Change XBUFLEN to TMPBUFSIZ
c 3. Add prototypes for debug() routine
e
s 00026/00003/00222
d D 1.14 95/04/05 16:28:07 clyde 14 13
c Beta 3 development checkin
e
s 00001/00001/00224
d D 1.13 94/10/24 10:29:40 clyde 13 12
c Change arguments to get_password
e
s 00018/00013/00207
d D 1.12 94/09/28 16:10:18 clyde 12 11
c Change password aging stuff in mpasswd struct
e
s 00019/00005/00201
d D 1.11 94/06/20 13:49:56 clyde 11 10
c Cleanup debugging level defines
e
s 00008/00009/00198
d D 1.10 94/05/17 15:28:11 clyde 10 9
c 1. Add support for OSF/1 security mode.
c 2. Add password aging into to struct mpasswd.
c 3. Add pointer to which encryption routine to use.
e
s 00043/00036/00164
d D 1.9 94/03/31 17:38:54 clyde 9 8
c Move stuff around and remove other stuff
e
s 00002/00002/00198
d D 1.8 94/03/17 15:49:38 clyde 8 7
c Change CLIBDEFINES to  NEED_CLIB_DECLS
e
s 00000/00016/00200
d D 1.7 94/03/16 09:42:59 clyde 7 6
c Move syslog stuff into options.h
e
s 00009/00214/00207
d D 1.6 94/03/15 18:50:24 clyde 6 5
c 1. Move compatibilty stuff to compatiblity.h
c 2. Provide more function decls
e
s 00065/00020/00356
d D 1.5 94/03/15 11:11:04 clyde 5 4
c Support OSF/1 on ALPHA
e
s 00014/00049/00362
d D 1.4 94/03/01 15:22:18 clyde 4 3
c Development checkin:
c 1. Remove some stuff not globally needed
c 2. Fix include of time.h
c 3. Make acc happier
e
s 00018/00002/00393
d D 1.3 93/12/16 11:03:08 clyde 3 2
c Development checkin
e
s 00025/00017/00370
d D 1.2 93/07/12 15:09:31 clyde 2 1
c Add more function prototypes
e
s 00387/00000/00000
d D 1.1 93/07/12 11:11:35 clyde 1 0
c date and time created 93/07/12 11:11:35 by clyde
e
u
U
f e 0
t
T
I 1
/*
 * 	Tangled web of ifdefs for various systems
 *	This cleans up the Makefile
 *
 *	%W% %G%
 */

I 19
#define	npasswd_h 1

E 19
I 18
#include "constants.h"
#include "defines.h"
E 18
D 6
#undef	_ALLDONE_
I 5
#define		TIME_H	<time.h>
#define		ERRNO_H	<errno.h>
#define	CONST	const
E 6
I 6
#include "compatibility.h"
#include "options.h"
I 19
D 22
#include "Common/svc_info.h"
E 22
I 22
D 30
#include "Common/pw_svc.h"
E 30
E 22
E 19
E 6
E 5

D 6
#ifdef	OS_SUNOS_4			/* SunOS 4.X (up to 4.1.3) */
# define	OS_BSD		1	/* Generically BSD */
D 5
# define	BSD_SIGNALS	1	/* Generically BSD  */
E 5
I 5
# define	HAS_SIGMASK	1	/* Generically BSD  */
E 5
# define	SUNOS_TTY	1	/* Use SunOS ioctls */
# define	NEED_GETPASS	1
# define	S5_PWAGING	1	/* Uses System 5 password aging */
# define	PW_COMMENT	1	/* Has pw_comment field */
# define	SUN_SHADOW	1	/* Change Sun shadow passwords */
# define	YP_PASSWD	1	/* Enable RPC password changes */
# define	USE_SYSLOG	1	/* Syslog messages */
# define	VENDOR_COMPAT	0	/* Full compatibilty with vendor prog */
I 4
# define	USE_SYS_TIME_H	1	/* Use <sys/time.h> */
I 5
# undef	TIME_H
# define TIME_H	<sys/time.h>
E 5
E 4
I 3
typedef	void	(*signal_t);
E 3
#ifdef	_ALLDONE_
	ERROR_Too_many_os_selections_made
#else
# define	_ALLDONE_	1
#endif
#endif

#ifdef	OS_SOLARIS_2			/* SunOS 5.X (Solaris 2.X) *?
# define	OS_SYS54	1	/* Mostly SVR4 */
# define	SYS5_TTY	1	/* Use SYS5 ioctls */
# define	S5_PWAGING	1	/* Uses System 5 password aging */
# define	S5_SHADOW	1	/* Uses System 5 password aging */
# define	PW_COMMENT	1	/* Has pw_comment field */
# define	YP_PASSWD	1	/* Enable RPC password changes */
# define	USE_SYSLOG	1	/* Syslog messages */
# define	USE_MEMOPS	1	/* Use system 5 memory routines */
#ifdef	_ALLDONE_
	ERROR_Too_many_os_selections_made
#else
# define	_ALLDONE_	1
#endif
#endif

#ifdef	OS_ULTRIX_4		/* Ultrix 4.X */
# define	OS_BSD		1	/* Generically BSD  */
D 5
# define	BSD_SIGNALS	1	/* Generically BSD  */
E 5
I 5
# define	HAS_SIGMASK	1	/* Generically BSD  */
E 5
# define	ULTRIX_SHADOW	1	/* Use Ultrix security mode */
# define	NO_CLNT_SPERRNO	1	/* Doesn't have clnt_sperrno(3) */
# define	NEED_PUTPWENT	1	/* Doesn't have putpwent(3) */
# define	NEED_FGETPWENT	1	/* Doesn't have fgetpwent(3) */
# define	PW_COMMENT	1	/* Has pw_comment field */
# define	YP_PASSWD	1	/* Enable RPC password changes */
# define	DBM_PASSWD	1	/* Uses DBM lookaside files */
# define	USE_SYSLOG	1	/* Syslog messages */
# define	STD_PW_LEN	13	/* Length of standard pw string */
I 4
# define	USE_SYS_TIME_H	0	/* Need to include <time.h> */
I 5
# define	USE_getsvc	1	/* Use DEC's getsvc() call */
E 5
E 4
extern char    *crypt16();
I 4
typedef	void	(*signal_t);
E 4
# ifdef	_ALLDONE_
   ERROR_Too_many_os_selections_made
# else
#  define	_ALLDONE_	1
# endif
#endif

I 5
#ifdef	OS_DEC_OSF1_1			/* DEC OSF/1 version 1.X */
# define	OS_BSD		1	/* Generically BSD */
# define	USE_UNISTD_H 	0
# define	USE_STDLIB_H 	1
# define	USE_MEMOPS	1	/* Use system 5 memory routines */
# define	HAS_SIGMASK	1	/* Generically BSD  */
# define	NEED_GETPASS	1
# define	NEED_FGETPWENT	1	/* Doesn't have fgetpwent(3) */
# undef		S5_PWAGING		/* No password aging */
# define	PW_COMMENT	1	/* Has pw_comment field */
# define	YP_PASSWD	1	/* Enable RPC password changes */
# define	DBM_PASSWD	1	/* Uses DBM lookaside files */
# define	USE_SYSLOG	1	/* Syslog messages */
# undef		VENDOR_COMPAT
# define	USE_SYS_TIME_H	1	/* Use <sys/time.h> */
# define	USE_getsvc	1	/* Use DEC's getsvc() call */
# undef		_NO_PROTO
typedef	void	(*signal_t);
extern char    *crypt();
extern char    *crypt16();
#ifdef	_ALLDONE_
	ERROR_Too_many_os_selections_made
#else
# define	_ALLDONE_	1
#endif
#endif

E 5
#ifdef	OS_AIX_3			/* AIX 3.2> */
# define	NEED_FGETPWENT	1	/* Doesn't have fgetpwent(3) */
# define	S5PW_AGE	1	/* Has pw_age field */
# define	USE_MEMOPS	1	/* Use system 5 memory routines */
# ifdef	_ALLDONE_
   ERROR_Too_many_os_selections_made
# else
#  define	_ALLDONE_	1
# endif
#endif

#ifdef	OS_BSD_43			/* Plain 4.3BSD system */
# define	OS_BSD		1	/* Generically BSD  */
D 5
# define	BSD_SIGNALS	1	/* Generically BSD  */
E 5
I 5
# define	HAS_SIGMASK	1	/* Generically BSD  */
E 5
# define	DBM_PASSWD	1	/* Has DBM lookaside files */
# define	PW_COMMENT	1	/* Has pw_comment field */
# define	USE_SYSLOG	1	/* Syslog messages */
# ifdef	_ALLDONE_
   ERROR_Too_many_os_selections_made
# else
#  define	_ALLDONE_	1
# endif
# endif

D 5
#ifdef	OS_DEC_OSF_1		/* Dec's OSF/1 system */
# define	BSD_SIGNALS	1	/* Generically BSD  */
# define	USE_SYSLOG	1	/* Syslog messages */
# ifdef	_ALLDONE_
   ERROR_Too_many_os_selections_made
# else
#  define	_ALLDONE_	1
# endif
#endif

E 5
#ifdef	OS_SYS_5123		/* System V R[123]* */
# define	OS_SYS5		1
# define	NEED_RENAME	1
# define	SYS5_TTY	1
# define	USE_MEMOPS	1	/* Use system 5 memory routines */
# ifdef	_ALLDONE_
   ERROR_Too_many_os_selections_made
# else
#  define	_ALLDONE_	1
# endif
#endif

#ifdef	OS_SYS_54			/* System V R4 */
# define	OS_SYS5		1
# define	SYS5_TTY	1
# define	USE_MEMOPS	1	/* Use system 5 memory routines */
# ifdef	_ALLDONE_
   ERROR_Too_many_os_selections_made
# else
#  define	_ALLDONE_	1
# endif
#endif

#ifdef	POSIX_ENV		/* XXX */
D 5
#define	_POSIX_SOURCE	1	/* XXX */
E 5
I 5
/* #define	_POSIX_SOURCE	1	/* XXX */
E 5
#include <fcntl.h>
#include <limits.h>
#include <locale.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#endif

/*
 *	Pull in system include files
 */
#include <sys/param.h>
#include <sys/types.h>
I 5
#include <sys/stat.h>
E 5
#include <ctype.h>
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <pwd.h>
I 5
#ifdef	__STDC__
#include <stdarg.h>
# define	VA_DCL(_X_)	(char *_X_, ...)
# define	VA_START(X,Y)	va_start(X,Y)
#else
#include <varargs.h>
# define	VA_DCL(_X_)	(va_alist) va_dcl
# define	VA_START(X,Y)	va_start(X)
#endif
E 5

#ifdef  USE_SYS_ERRNO_H
# include <sys/errno.h>
#else
# include <errno.h>
#endif

I 4
#ifdef  USE_SYS_TIME_H
# include <sys/time.h>
#else
# include <time.h>
#endif

E 4
#ifdef	DEBUG
#undef	USE_SYSLOG		/* XXXX */
#endif

E 6
D 7
#ifdef	USE_SYSLOG
#include <syslog.h>
# ifndef	LOG_AUTH
#  define	LOG_AUTH	0
# endif
# ifndef	LOG_CONS
#  define	LOG_CONS	0
# endif
# ifndef	ERROR_LOG_LEVEL
#  define	ERROR_LOG_LEVEL		LOG_ERR
# endif
# ifndef	MESSAGE_LOG_LEVEL
#  define	MESSAGE_LOG_LEVEL	LOG_INFO
# endif
#endif

E 7
D 6
#ifdef	USE_MEMOPS
# include <memory.h>
# define	INDEX(s, c)	strchr(s, c)
# define	RINDEX(s, c)	strrchr(s, c)
# define	BZERO(a, l)	memset(a, 0, l)
# define	BCOPY(s, d, l)	memcpy(d, s, l)
#else
# define	INDEX(s, c)	index(s, c)
# define	RINDEX(s, c)	rindex(s, c)
# define	BZERO(a, l)	bzero(a, l)
# define	BCOPY(s, d, l)	bcopy(s, d, l)
#endif

D 5
#if	(USE_UNISTD_H || POSIX)
E 5
I 5
#ifdef	USE_UNISTD_H
E 5
# include <unistd.h>
D 5
# else
# ifdef	USE_STDLIB_H
E 5
I 5
#endif
#ifdef	USE_STDLIB_H
E 5
#  include <stdlib.h>
D 5
# else
E 5
I 5
#endif
# if !defined(USE_STDLIB_H) && !defined(USE_UNISTD_H)
E 6
I 6
D 8
#ifndef	CLIBDEFINES
E 8
I 8
D 14
#ifdef	NEED_CLIB_DECLS
E 14
I 14
D 20
#ifdef	XNEED_CLIB_DECLS
E 20
I 20
#ifdef	NEED_CLIB_DECLS
E 20
E 14
E 8
E 6
E 5
/*
 * This block of declarations may cause compilation to fail on
 * systems that have any of the routines already defined in
 * a system include file.
 */
char	*getlogin(),
D 18
	*crypt(),
E 18
	*malloc(),
	*index(),
I 20
	*rindex(),
E 20
D 23
	*ttyname(),
	*getpass();
E 23
I 23
	*ttyname();
D 27
char	*getpass _((char *));
E 27
E 23
D 6
# endif /* USE_STDLIB_H */
E 6
I 6
D 8
# endif /* CLIBDEFINES */
E 8
I 8
D 12
# endif
E 12
I 12
#endif
E 12
E 8
E 6
D 5
#endif	/* USE_UNISTD_H */
E 5

D 6
#define	SIGTYPE	(void *)		/* This might be wrong */

#ifndef MAXHOSTNAMLEN
# define MAXHOSTNAMLEN 64
#endif

E 6
D 4

E 4
/*
D 4
 *
E 4
D 18
 * End the configuration code (tangled wed of preprocessor commands)
E 18
I 18
D 19
 * Security level names
E 18
D 4
 *
E 4
 */
D 18

/*
D 4
 *	File names - many can be overidden by the config file
 */
#ifndef	PASSWD_FILE
# define	PASSWD_FILE	"/etc/passwd"
#endif
 
#ifndef	PASSWD_SAVE
# define	PASSWD_SAVE	"/etc/opasswd"
#endif

#ifndef	PASSWD_TEMP
# define	PASSWD_TEMP	"/etc/ptmp"
#endif

#ifndef	PASSWD_LOCK
# define	PASSWD_LOCK	"/etc/passwd.ptmp"
#endif

#ifndef	PASSWD_CONFIG
# define	PASSWD_CONFIG	"/usr/adm/passwd.conf"
#endif
#ifndef	PASSWD_HELP
# define	PASSWD_HELP	"/usr/adm/passwd.help"
#endif
#ifndef	PASSWD_MOTD
# define	PASSWD_MOTD	"/usr/adm/passwd.motd"
#endif

/*
E 4
D 11
 * Constants
E 11
I 11
 * Definitions for making the source look pretty
E 11
 */
#define	public	/* */
#define	private	static
I 11
D 12
#ifdef	__STDC__
# define	fixed	const
E 12
I 12
D 14
#if	defined(__STDC__) || defined(AC_CONST)
E 14
I 14
#ifdef	HAS_CONST
E 14
# define	const	const
E 12
#else
D 12
# define	fixed	/* */
E 12
I 12
# define	const	/* */
E 12
#endif
E 11

D 4
#define	PASSWD_MODE	0644

/*
 * Names of NIS maps where passwd information is stored
 */
#define	PASSWD_BYNAME	"passwd.byname"
#define	PASSWD_BYUID	"passwd.byuid"
I 3
#define	ADJUNCT_BYNAME	"passwd.adjunct.byname"
E 3

#define	PASSWD_SIZE_SLOP	128
 
E 4
D 9
#define	DEBUG_NONE	0
#define	DEBUG_VERBOSE	1
#define	DEBUG_PWUPDATE	8
E 9
I 9
D 11
#define	DB_NONE	0
#define	DB_VERBOSE	1
#define	DB_LOOKUP	6
#define	DB_UPDATE	7
E 11
I 11
/*
 * Debugging levels.  Debugging is activated by the -D command line option
 */
#define	DB_NONE		0		/* No debug */
#define	DB_VERBOSE	1		/* Mild verbosity */
D 15
#define	DB_LOUD		2		/* More verbosity */
#define	DB_CONFIG	3		/* Trace configuration processing */
#define	DB_LOOKUP	6		/* Trace user lookup */
#define	DB_UPDATE	7		/* Trace user update */
E 15
I 15
#define	DB_LEVEL2	2		/* Nothing yet */
#define	DB_LEVEL3	3		/* Nothing yet */
#define	DB_LOOKUP	4		/* Trace user lookup */
#define	DB_UPDATE	5		/* Trace user update */
#define	DB_LEVEL6	6		/* Nothing yet */
#define	DB_LEVEL7	7		/* Nothing yet */
#define	DB_CONFIG	8		/* Trace configuration processing */
#define	DB_ALL		99		/* Trace *everything* */
E 15
E 11
E 9

I 15
/*
 * Various string buffer sizings
 */
E 15
D 12
#define	STRINGLEN	32
I 9
#define	PASSWD_FILE_SLOP 128
I 11

E 12
I 12
#define	STRINGLEN	32		/* Length for miscelleanous strings */
#define	PW_LINELEN	512		/* Length for passwd lines */
I 14
D 15
#define	XBUFLEN		1024		/* Size of miscellanous buffers */
E 15
I 15
#define	TMPBUFSIZ	1024		/* Size of miscellanous buffers */
E 15
E 14
E 12
/*
 * Time stuff
 */
E 11
#define DAYS_PER_WEEK   7
#define	SEC_PER_DAY	(time_t )(24 * 60 * 60)
#define	SEC_PER_WEEK	(time_t )(SEC_PER_DAY * DAYS_PER_WEEK)
E 9

D 4
#define DAYS_PER_WEEK	7
#define SEC_PER_WEEK	((time_t )(24 * DAYS_PER_WEEK * 60 * 60))


E 4
/*
 * Service lookup ordering
 */
E 18
enum sec_order {		/* System security level */
	sec_std = 0,
D 18
	sec_u4upgrade,		/* Ultrix 4.X 'upgrade' */
	sec_u4enhanced,		/* Ultrix 4.X 'enhanced' */
D 10
	sec_sunC2		/* SunOS 4.X C2 security */
E 10
I 10
	sec_sunC2,		/* SunOS 4.X C2 security */
	sec_OSFenhanced		/* OSF/1 2.X 'enhanced' */
E 18
I 18
	sec_u4upgrade,		/* Ultrix 4 'upgrade' */
	sec_u4enhanced,		/* Ultrix 4 'enhanced' */
	sec_sunC2,		/* SunOS 4 C2 security */
	sec_OSFenhanced		/* Digital UNIX (OSF/1) enhanced */
E 18
E 10
};
D 18
extern enum sec_order SecurityLevel;
E 18
I 18
extern enum sec_order svc_SecurityLevel;
E 18

D 18
enum svc_order {			/* Service order */
E 18
I 18
/*
 * Database service names
 */
enum svc_names {
E 18
	srv_local,
	srv_yp,
D 16
	srv_ypcompat,
E 16
	srv_nisplus,
	srv_nidot,
	srv_niroot,
	srv_kerb,
	srv_hesiod,
I 12
	srv_unknown,
E 12
	srv_last = 99
};
D 18
extern enum svc_order ServiceOrder[];
E 18
I 18
extern enum svc_names svc_ServiceOrder[];
E 18

I 10
D 18
extern char *(*PasswdCrypt)();
E 18
I 18
/*
 * Password encryptor
 */
extern char *(*svc_PasswdCrypt)();
E 18

E 10
I 3
/*
E 19
 * Password change permission type
 */
enum chg_perm {
	deny = 0,	/* Cannot change */
	self,		/* Changing own password */
D 31
	other		/* Privleged user changing other */
E 31
I 31
	other,		/* Privleged user changing other */
	allow		/* Generic "I'm not unhappy" code */
E 31
};

E 3
struct passwd_files {
	char	*pwfile,	/* Name of password file */
		*tempfile,	/* Name of password temp file */
		*savefile,	/* Name of password save file */
		*lockfile;	/* Name of password lock file */
I 24
	uid_t	uid;		/* File owner */
	gid_t	gid;		/* File group */
	mode_t	mode;		/* File mode */
E 24
};

D 4
struct mpasswd {		/* Meta-passwd entry */
E 4
I 4
/*
 * The "meta-passwd" entry
 */
struct mpasswd {
E 4
D 17
	struct passwd	pw;	/* Passwd info */
#define	mpw_name	pw.pw_name
#define	mpw_passwd	pw.pw_passwd
#define	mpw_uid		pw.pw_uid
E 17
I 17
	struct passwd	pw;
#define	mpw_name	pw.pw_name	/* Conveince definitions */
#define	mpw_passwd	pw.pw_passwd	/* to simplify access to */
#define	mpw_uid		pw.pw_uid	/* passwd structure elements */
E 17
#define	mpw_gid		pw.pw_gid
#define	mpw_shell	pw.pw_shell
#define	mpw_gecos	pw.pw_gecos
#define	mpw_shell	pw.pw_shell
I 9
#define	mpw_dir		pw.pw_dir
I 26
#ifdef	PWQUOTA
E 26
E 9
D 21
#define	mpw_age		pw.pw_age
E 21
#define	mpw_quota	pw.pw_quota
I 26
#endif
I 28
#ifdef	PWCOMMENT
E 28
E 26
#define	mpw_comment	pw.pw_comment
I 28
#endif
	char		*mpw_opasswd;	/* Original password string */
					/* which might be a shadow cookie */
E 28
I 9
D 10
#ifdef	S5_SHADOW
	long		sp_lstchg;
	long		sp_min;
	long		sp_max;
	long		sp_warn;
	long		sp_inact;
	long		sp_expire;
#endif
E 10
I 10
D 12
	char		age_password;		/* Should aging be done? */
	time_t		last_change;		/* Last password change */
	time_t		min_change_time;	/* Time till change ok */
	time_t		expire;			/* Time when must change */
E 12
I 12
D 17
	struct {
		char	doit;			/* Should aging be done? */
		time_t	last_change;		/* Time of last change */
		time_t	min_time;		/* Time till change ok */
		time_t	max_time;		/* Time when must change */
E 17
I 17
	struct {		/* Password aging information */
D 18
		char	do_aging;	/* Should aging be done? */
E 18
		time_t	last_change;	/* Time of last change */
		time_t	can_change;	/* Time till change ok */
		time_t	must_change;	/* Time when must change */
I 18
		time_t	warn_user;	/* When user gets warned */
I 21
#ifdef	PWAGE
#define	mpw_age		pw.pw_age
#else
#define	mpw_age		pwage.xage
		char	*xage;
#endif
E 21
E 18
E 17
	} pwage;
D 17
	char		*misc;			/* Miscellanous stuff */
E 12
E 10
E 9
	char		key[128],		/* Database "access key" */
			password[128];		/* Database "access pass" */
	char		*where;			/* Where they are */
	int		remote;			/* Is it remote or not */
	void		*opaque;		/* Method opaque data block */
E 17
I 17
	char	key[128],	/* Database "access key" */
		password[128];	/* Database "access pass" */
	char	*pws_name,	/* Service name (NIS, NIS+) */
		*pws_loc;	/* Location of service (hostname) */
	int	pws_remote;	/* Is the service local? */
	void	*opaque;	/* Method opaque data block */
E 17
};

D 9
#if	SUN_SHADOW
E 9
/*
D 9
 * Would like to use the real Sun adjunct passwd structure, but it's pretty
 * messy to encode and decode, so use a stupid subsitute (which is what the
 * Sun version does also).  What a crock.
E 9
I 9
 * Signal stuff
E 9
 */
D 9
struct passwd_Xadjunct {
	char	*pwa_name;
	char	*pwa_passwd;
	char	*pwa_minimum;
	char	*pwa_maximum;
	char	*pwa_def;
	char	*pwa_au_always;
	char	*pwa_au_never;
	char	*pwa_version;
	char	*pwa_age;
E 9
I 9
struct sigblk {
#if	(SIG_TYPE == SIG_TYPE_UNIX)
D 14
	signal_t	sigvalues[NSIG];
E 14
I 14
D 28
	Signal_t	sigvalues[NSIG];
E 28
I 28
	Signal_t	(*sigvalues[NSIG])();
E 28
E 14
#endif
#if	(SIG_TYPE == SIG_TYPE_POSIX)
	sigset_t	sigvalues,
			savesigs;
#endif
#if	(SIG_TYPE == SIG_TYPE_BSD)
	unsigned int	sigvalues,
			savesigs;
#endif
E 9
};
D 9
# ifdef	__STDC__
struct passwd_Xadjunct   *fgetapwent(FILE *);
I 5
char		*sputpwaent(struct passwd_Xadjunct *, char *);
E 5
# else
D 4
struct passwd_Xadjunct   *fgetapwent(/* FILE *af */);
E 4
I 4
struct passwd_Xadjunct   *fgetapwent();
I 5
char		*sputpwaent();
E 5
E 4
# endif
#endif	/* SUN_SHADOW */

E 9
D 18
#ifdef	__STDC__
I 14
/*
 * If your compiler claims __STDC__ but doesn't have prototypes,
 * get another compiler.  I suggest gcc.
 */
E 14
void		pw_initialize(int, char **);
struct mpasswd	*pw_getuserbyname(char *);
D 3
int		pw_permission(struct mpasswd *, struct mpasswd *);
E 3
I 3
enum chg_perm	pw_permission(struct mpasswd *, struct mpasswd *);
E 3
D 2
int		pw_passwdcmp(char *, char *);
E 2
int		pw_check(struct mpasswd *, char *, char *);
void		pw_replace(struct mpasswd *, char *, char *, char *);
void		pw_cleanup(int);
E 18
I 2

D 18
void		passwd(struct mpasswd *, struct mpasswd *);
void		chfn(struct mpasswd *, struct mpasswd *);
void		chsh(struct mpasswd *, struct mpasswd *);
E 18
I 18
D 20
void		pw_initialize _((int, char **));
struct mpasswd	*pw_getuserbyname _((char *));
enum chg_perm	pw_permission _((struct mpasswd *, struct mpasswd *));
int		pw_check _((struct mpasswd *, char *, char *));
E 20
I 20

/*
 * Function prototypes
 */
void		pw_initialize();
D 23
struct mpasswd	*pw_getuserbyname _((const char *));
enum chg_perm	pw_permission _((const struct mpasswd *, const struct mpasswd *));
int		pw_check _((const struct mpasswd *, const char *, char *));
E 23
I 23
struct mpasswd	*pw_getuserbyname _((char *));
enum chg_perm	pw_permission _((struct mpasswd *, struct mpasswd *));
int		pw_check _((struct mpasswd *, char *, char *));
E 23
E 20
void		pw_replace _((struct mpasswd *, struct mpasswd *, int));
D 20
void		pw_cleanup _((int));
E 20
I 20
D 23
void		pw_cleanup _((const int));
E 23
I 23
void		pw_cleanup _((int));
E 23
E 20
E 18
D 19

E 19
E 2
D 18
char		*copystr(char *);
struct passwd	*copypwent(struct passwd*, struct passwd *);
struct passwd	*fgetpwnam(char *, char *);
struct passwd	*fgetpwent(FILE *);
struct passwd	*sgetpwent(char *);
I 9
char		*sputpwent(struct passwd *, char *);
E 9
struct passwd	*ypgetpwnam(char *s, char *);
E 18
I 18
void		passwd _((struct mpasswd *, struct mpasswd *));
void		chfn _((struct mpasswd *, struct mpasswd *));
void		chsh _((struct mpasswd *, struct mpasswd *));
I 19
D 20
void		motd _((char *, char *));
void		get_password _((char *, char *, char *, int));
E 20
I 20
D 23
void		motd _((const char *, const char *));
void		get_password _((const char *, const char *, char *, const int));
E 23
I 23
void		motd _((char *, char *));
D 29
void		get_password _((char *, char *, char *, int));
I 27
char		*np_getpass _((char *));
E 29
E 27
E 23
E 20
E 19
E 18
I 5

E 5
D 9
char		*sputpwent(struct passwd *, char *);
I 3
D 5
char		*sputpwaent(struct passwd_Xadjunct *, char *);
E 5
E 3
I 2

E 2
char		*random_string(char *, int);
E 9
I 9
D 18
char	*random_string(char *, int);
E 9
I 3
enum chg_perm	can_change(struct mpasswd *, struct mpasswd *);
I 5
D 9
size_t		sizecheck(char *, char *);
E 9
I 9
D 12
size_t	sizecheck(char *, char *);
E 12
I 12
size_t	cmp_file_size(char *, char *);
E 18
I 18
D 19
struct passwd	*copypwent _((struct passwd*, struct passwd *));
struct passwd	*fgetpwnam _((char *, char *));
struct passwd	*fgetpwent _((FILE *));
struct passwd	*sgetpwent _((char *));
char		*sputpwent _((struct passwd *, char *));
E 19
I 19
D 20

E 20
#ifdef	USE_NIS
E 19
D 20
struct passwd	*ypgetpwnam _((char *s, char *));
E 20
I 20
D 23
struct passwd	*ypgetpwnam _((const char *, char *));
E 23
I 23
struct passwd	*ypgetpwnam _((char *, char *));
E 23
E 20
I 19
#endif
E 19
E 18
E 12
E 9
E 5
E 3

I 5
D 9
void		get_password(char *, char *, int);
void		motd(char *, char *);
void		die(char *, ...);
void		warn(char *, ...);
void		logdie(char *, ...);
void		logerr(char *, ...);
E 9
I 9
D 13
void	get_password(char *, char *, int);
E 13
I 13
D 18
void	get_password(char *, char *, char *, int);
E 13
void	motd(char *, char *);
I 15
void	debug(int, char *, ...);
E 15
void	die(char *, ...);
void	warn(char *, ...);
void	logdie(char *, ...);
void	logerr(char *, ...);
void	block_signals(struct sigblk *, ...);
void	unblock_signals(struct sigblk *);
I 12
int	mklocktemp(char *);
E 18
I 18
D 19
void	svc_get _((int, char **, char **));
E 18
E 12
E 9

E 5
D 18
#else
E 18
I 18
void	motd _((char *, char *));
void	debug _((int, char *, ...));
E 18

D 2
void		pw_initialize(/* int argc, char **argv */);
struct mpasswd	*pw_getuserbyname(/* char *username  */);
int		pw_permission(/* struct mpasswd *user, *caller */);
int		pw_passwdcmp(/* char *current, *new */);
int		pw_check(/* struct mpasswd *user, char *newpass */);
void		pw_replace(/* struct mpasswd *theUser, char *newpw,
			*newfn, *newsh */);
void		pw_cleanup(/* int condition */);
char		*copystr(/* char *s */);
struct passwd	*copypwent(/* struct pwent s,d */);
struct passwd	*fgetpwnam(/* char *name, *pwfile */);
struct passwd	*fgetpwent(/* FILE *p */);
struct passwd	*sgetpwent(/* char *s */);
struct passwd	*ypgetpwnam(/* char *s, *domain */);
char		*sputpwent(/* struct passwd *p, char *b */);
char		*random_string(/* char buf, int buflen */);
E 2
I 2
D 18
void		pw_initialize();
struct mpasswd	*pw_getuserbyname();
D 3
int		pw_permission();
E 3
I 3
enum chg_perm	pw_permission();
E 3
int		pw_check();
void		pw_replace();
void		pw_cleanup();
E 18
I 18
void	die _((char *, ...));
void	warn _((char *, ...));
E 18

D 18
void		passwd();
void		chfn();
void		chsh();
E 18
I 18
void	logdie _((char *, ...));
void	logerr _((char *, ...));
E 18

D 18
char		*copystr();
struct passwd	*copypwent();
struct passwd	*fgetpwnam();
struct passwd	*fgetpwent();
struct passwd	*sgetpwent();
struct passwd	*ypgetpwnam();
char		*sputpwent();
I 3
char		*sputpwaent();
E 3
char		*random_string();
I 3
enum chg_perm	can_change();
I 5
D 12
size_t		sizecheck();
E 12
I 12
size_t		cmp_file_size();
E 12
I 6
void		get_password();
E 6
void		motd();
I 15
void		debug();
E 15
I 6
void		die();
void		warn();
void		logdie();
void		logerr();
I 9
void		block_signals();
void		unblock_signals();
I 12
int		mklocktemp();
E 18
I 18
void	block_signals _((struct sigblk *, ...));
void	unblock_signals _((struct sigblk *));
E 18
E 12
E 9
E 6
E 5

E 19
I 18
/*
D 29
 * Routines in main.c
E 29
I 29
 * Variables in main.c
E 29
 */
D 20
size_t	FileSizeDiff _((char *, char *));
int	MakeLockTemp _((char *));
void	FixPwFileMode _((char *, char *));
E 20
I 20
D 23
size_t	FileSizeDiff _((const char *, const char *));
int	MakeLockTemp _((const char *));
void	FixPwFileMode _((const char *, const char *));
E 23
I 23
D 29
size_t	FileSizeDiff _((char *, char *));
int	MakeLockTemp _((char *));
void	FixPwFileMode _((char *, char *));
E 23
E 20

D 19
#ifndef HAS_STRCASECMP
int	strcasecmp _((char*, char *));
int	strncasecmp _((char*, char *));
E 18
E 3
E 2
#endif

E 19
I 14
D 18
#if	0
E 18
D 23
/* Damn systems that define this already ... */
#ifdef	NEED_GETPASS
D 19
public char	*getpass(char *);
E 19
I 19
D 20
public char	*getpass _((char *));
E 20
I 20
char	*getpass _((const char *));
E 20
E 19
#else
extern char     *getpass();
#endif
E 23
D 18
#endif
E 18

E 29
D 18

E 14
extern char	*CommandLineOption[];
E 18
I 18
extern char	*Switches[];
extern char	*XSwitches[];
E 18
D 30
extern char	*ProgramName;
extern int	DebugLevel,
D 18
		ProgramInput,
E 18
		pwReadTries;
E 30
I 20
extern Uid_t	CallerUid;
E 20

I 25
extern int	LockTries,
		LockCycle;

E 25
I 14
extern char	*npasswd_version,
		*npasswd_patchlevel,
		*checkpasswd_version,
		*checkpasswd_patchlevel,
		*build_info;

E 14
extern int	errno;			/* System error code */
I 14

I 18
D 19
#include "lib/lib_util.h"	/* Include later to pick up type decls */
E 19
I 19
D 22
extern struct pwsvc	svc;	/* System "name service" info */
E 22
I 22
D 30
extern struct pw_svc	svc;	/* System "name service" info */
E 22
E 19

E 30
I 19
#include "Common/common.h"	/* Include later to pick up type decls */

E 19
E 18
/* End %M% */
E 14
E 1
