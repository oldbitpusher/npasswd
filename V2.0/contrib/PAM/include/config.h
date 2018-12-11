/*
 * This file was produced by running the config_h.SH script, which
 * gets its values from config.sh, which is generally produced by
 * running Configure.
 *
 * Feel free to modify any of this as the need arises.  Note, however,
 * that running config_h.SH again will wipe out any changes you've made.
 * For a more permanent change edit config.sh and rerun config_h.SH.
 *
 * $Id: Config_h.U,v 3.0.1.5 1997/02/28 14:57:43 ram Exp $
 */

/*
 * Package name      : npasswd
 * Source directory  : .
 * Configuration time: Tue Aug 31 09:25:48 CDT 1999
 * Configured by     : vicb
 * Target system     : sunos ranger1 5.6 generic_105181-15 sun4u sparc sunw,ultra-1 
 */

#ifndef _config_h_
#define _config_h_

/* BSD:
 *	This symbol, if defined, indicates that the program is running under
 *	a BSD system.
 */
#define BSD		/**/

/* HASCONST:
 *	This symbol, if defined, indicates that this C compiler knows about
 *	the const type. There is no need to actually test for that symbol
 *	within your programs. The mere use of the "const" keyword will
 *	trigger the necessary tests.
 */
#define HASCONST	/**/
#ifndef HASCONST
#define const
#endif

/* HAS_FCHMOD:
 *	This symbol, if defined, indicates that the fchmod routine is available
 *	to change mode of opened files.  If unavailable, use chmod().
 */
#define HAS_FCHMOD		/**/

/* HAS_FCHOWN:
 *	This symbol, if defined, indicates that the fchown routine is available
 *	to change ownership of opened files.  If unavailable, use chown().
 */
#define HAS_FCHOWN		/**/

/* HAS_GETHOSTNAME:
 *	This symbol, if defined, indicates that the C program may use the
 *	gethostname() routine to derive the host name.  See also HAS_UNAME
 *	and PHOSTNAME.
 */
#define HAS_GETHOSTNAME	/**/

/* HAS_MEMCPY:
 *	This symbol, if defined, indicates that the memcpy routine is available
 *	to copy blocks of memory.
 */
#define HAS_MEMCPY	/**/

/* HAS_MEMSET:
 *	This symbol, if defined, indicates that the memset routine is available
 *	to set blocks of memory.
 */
#define HAS_MEMSET	/**/

/* HAS_READDIR:
 *	This symbol, if defined, indicates that the readdir routine is
 *	available to read directory entries. You may have to include
 *	<dirent.h>. See I_DIRENT.
 */
#define HAS_READDIR		/**/

/* HAS_RENAME:
 *	This symbol, if defined, indicates that the rename routine is available
 *	to rename files.  Otherwise you should do the unlink(), link(), unlink()
 *	trick.
 */
#define HAS_RENAME	/**/

/* HAS_SIGBLOCK:
 *	This symbol, if defined, indicates that the sigblock routine is
 *	available to block signal reception.
 */
/*#define HAS_SIGBLOCK	/ **/

/* HAS_STRCASECMP:
 *	This symbol, if defined, indicates that the strcasecmp() routine is
 *	available for case-insensitive string compares.
 */
#define HAS_STRCASECMP	/**/

/* HAS_STRCHR:
 *	This symbol is defined to indicate that the strchr()/strrchr()
 *	functions are available for string searching. If not, try the
 *	index()/rindex() pair.
 */
#define HAS_STRCHR	/**/

/* HAS_STRDUP:
 *	This symbol, if defined, indicates that the strdup routine is
 *	available to duplicate strings in memory. Otherwise, roll up
 *	your own...
 */
#define HAS_STRDUP		/**/

/* Signal_t:
 *	This symbol's value is either "void" or "int", corresponding to the
 *	appropriate return type of a signal handler.  Thus, you can declare
 *	a signal handler using "Signal_t (*handler)()", and define the
 *	handler using "Signal_t handler(sig)".
 */
#define Signal_t void	/* Signal handler's return type */

/* Gid_t:
 *	This symbol holds the return type of getgid() and the type of
 *	argument to setrgid() and related functions.  Typically,
 *	it is the type of group ids in the kernel. It can be int, ushort,
 *	uid_t, etc... It may be necessary to include <sys/types.h> to get
 *	any typedef'ed information.
 */
#define Gid_t gid_t		/* Type for getgid(), etc... */

/* I_DBM:
 *	This symbol, if defined, indicates that <dbm.h> exists and should
 *	be included.
 */
/*#define I_DBM	/ **/

/* I_DIRENT:
 *	This symbol, if defined, indicates to the C program that it should
 *	include <dirent.h>. Using this symbol also triggers the definition
 *	of the Direntry_t define which ends up being 'struct dirent' or
 *	'struct direct' depending on the availability of <dirent.h>.
 */
/* Direntry_t:
 *	This symbol is set to 'struct direct' or 'struct dirent' depending on
 *	whether dirent is available or not. You should use this pseudo type to
 *	portably declare your directory entries.
 */
#define I_DIRENT		/**/
#define Direntry_t struct dirent

/* I_MEMORY:
 *	This symbol, if defined, indicates to the C program that it should
 *	include <memory.h>.
 */
/*#define I_MEMORY		/ **/

/* I_NDBM:
 *	This symbol, if defined, indicates that <ndbm.h> exists and should
 *	be included.
 */
#define I_NDBM	/**/

/* PWQUOTA:
 *	This symbol, if defined, indicates to the C program that struct passwd
 *	contains pw_quota.
 */
/* PWAGE:
 *	This symbol, if defined, indicates to the C program that struct passwd
 *	contains pw_age.
 */
/* PWCOMMENT:
 *	This symbol, if defined, indicates to the C program that struct passwd
 *	contains pw_comment.
 */
/*#define PWQUOTA	/ **/
#define PWAGE	/**/
#define PWCOMMENT	/**/

/* I_STDLIB:
 *	This symbol, if defined, indicates that <stdlib.h> exists and should
 *	be included.
 */
#define I_STDLIB		/**/

/* I_STRING:
 *	This symbol, if defined, indicates to the C program that it should
 *	include <string.h> (USG systems) instead of <strings.h> (BSD systems).
 */
#define I_STRING		/**/

/* I_SYS_PARAM:
 *	This symbol, if defined, indicates to the C program that it should
 *	include <sys/param.h>.
 */
#define I_SYS_PARAM		/**/

/* I_SYS_RESOURCE:
 *	This symbol, if defined, indicates to the C program that it should
 *	include <sys/resource.h>.
 */
#define I_SYS_RESOURCE		/**/

/* I_TERMIO:
 *	This symbol, if defined, indicates that the program should include
 *	<termio.h> rather than <sgtty.h>.  There are also differences in
 *	the ioctl() calls that depend on the value of this symbol.
 */
/* I_TERMIOS:
 *	This symbol, if defined, indicates that the program should include
 *	the POSIX termios.h rather than sgtty.h or termio.h.
 *	There are also differences in the ioctl() calls that depend on the
 *	value of this symbol.
 */
/* I_SGTTY:
 *	This symbol, if defined, indicates that the program should include
 *	<sgtty.h> rather than <termio.h>.  There are also differences in
 *	the ioctl() calls that depend on the value of this symbol.
 */
/*#define I_TERMIO		/ **/
#define I_TERMIOS		/**/
/*#define I_SGTTY		/ **/

/* I_SYS_TIME:
 *	This symbol, if defined, indicates to the C program that it should
 *	include <sys/time.h>.
 */
#define I_SYS_TIME		/**/

/* I_UNISTD:
 *	This symbol, if defined, indicates to the C program that it should
 *	include <unistd.h>.
 */
#define I_UNISTD		/**/

/* CAN_PROTOTYPE:
 *	If defined, this macro indicates that the C compiler can handle
 *	function prototypes.
 */
/* _:
 *	This macro is used to declare function parameters for folks who want
 *	to make declarations with prototypes using a different style than
 *	the above macros.  Use double parentheses.  For example:
 *
 *		int main _((int argc, char *argv[]));
 */
#define	CAN_PROTOTYPE	/**/
#ifdef CAN_PROTOTYPE
#define	_(args) args
#else
#define	_(args) ()
#endif

/* Uid_t:
 *	This symbol holds the type used to declare user ids in the kernel.
 *	It can be int, ushort, uid_t, etc... It may be necessary to include
 *	<sys/types.h> to get any typedef'ed information.
 */
#define Uid_t uid_t		/* UID type */

/* VOIDFLAGS:
 *	This symbol indicates how much support of the void type is given by this
 *	compiler.  What various bits mean:
 *
 *	    1 = supports declaration of void
 *	    2 = supports arrays of pointers to functions returning void
 *	    4 = supports comparisons between pointers to void functions and
 *		    addresses of void functions
 *	    8 = suports declaration of generic void pointers
 *
 *	The package designer should define VOIDUSED to indicate the requirements
 *	of the package.  This can be done either by #defining VOIDUSED before
 *	including config.h, or by defining defvoidused in Myinit.U.  If the
 *	latter approach is taken, only those flags will be tested.  If the
 *	level of void support necessary is not present, defines void to int.
 */
#ifndef VOIDUSED
#define VOIDUSED 15
#endif
#define VOIDFLAGS 15
#if (VOIDFLAGS & VOIDUSED) != VOIDUSED
#define void int		/* is void to be avoided? */
#define M_VOID			/* Xenix strikes again */
#endif

/* DBM_PASSWD:
 *	Enable support for DBM passwd files.
 */
/* USE_NIS:
 *	Enable NIS (YP) support.
 */
/* SECURE_RPC:
 *	Enable secure RPC support.
 */
/* USE_NISPLUS:
 *	Enable NIS+ support.
 */
/* HAS_NISPASSWD:
 *	Use nispasswd interface for changes (Solaris 2.5 *Not Yet Implimented*)
 */
/* USE_KERBEROS:
 *	Enable Kerebos support.
 */
/* HAS_SVCCONF:
 *	This symbol indicates the presence of /etc/svc.conf
 */
/* HAS_NSSWITCH:
 *	This symbol indicates the presence of /etc/nsswitch.conf
 */
/* PARANOID_UIDCHECK:
 *	Enables "paranoid user checking" option.
 */
/* OSF1_AUTH:
 *	Enables OSF/1 (Digital UNIX) auth support.
 */
/* ULTRIX_AUTH:
 *	Enables Ultrix 4 auth support.
 */
/* AIX_AUTH:
 *	Enables AIX auth support.
 */
/* HPUX_AUTH:
 *	Enables HP/UX auth support.
 */
/* PASSWD_DICTIONARIES:
 *	Path to default dictionary collection.
 */
/*#define	USE_NIS		/ **/
/*#define	USE_NISPLUS	/ **/
/*#define	HAS_NISPASSWD	/ **/
/*#define	USE_KERBEROS	/ **/
/*#define	HAS_SVCCONF	/ **/
#define	HAS_NSSWITCH	/**/
/*#define 	DBM_PASSWD	/ **/
/*#define OSF1_AUTH	/ **/
/*#define 	ULTRIX_AUTH	/ **/
/*#define 	AIX_AUTH	/ **/
/*#define	HPUX_AUTH	/ **/
/*#define SECURE_RPC	/ **/
/*#define	PARANOID_UIDCHECK 	/ **/
#define	PASSWD_DICTIONARIES "/usr/lib/passwd/dictionaries"	/**/
#define	PASSWORD_HISTORY_DB "/usr/lib/passwd/etc/history"	/**/

/* HAS_CLNT_SPERRNO:
 *	This symbol, if defined, indicates that clnt_sperrno exists.
 */
#define	HAS_CLNT_SPERRNO	/**/

/* HAS_FGETPWENT:
 *	This symbol, if defined, indicates that libc fgetpwent should be used.
 */
#define	HAS_FGETPWENT	/**/

/* HAS_GETUSERSHELL:
 *	This symbol, if defined, indicates that getusershell exists.
 */
#define	HAS_GETUSERSHELL	/**/

/* HAS_LCKPWDF:
 *	This symbol, if defined, indicates that lckpwdf and ulckpwdf exist.
 */
#define	HAS_LCKPWDF	/**/

/* HAS_PUTPWENT:
 *	This symbol, if defined, indicates that the putpwent routine exists.
 */
#define	HAS_PUTPWENT	/**/

/* HAS_XDR_PASSWD:
 *	This symbol, if defined, indicates that the xdr_passwd routine exists
 */
/*#define HAS_XDR_PASSWD		/ **/

/* HAS_POSIX_SIGNALS:
 *	This symbol, if defined, indicates that the POSIX signal routines exist.
 */
#define	HAS_POSIX_SIGNALS	/**/

/* HAS_SYSINFO:
 *	This symbol, if defined, indicates that the
 *	sysinfo and ugetrlimit routines can be used.
 */
#define	HAS_SYSINFO	/**/

/* HAS_POSIX_TTY:
 *	This symbol, if defined, indicates that the POSIX terminal routines exist.
 */
#define	HAS_POSIX_TTY	/**/

/* UIDS_ARE_SIGNED:
 *	This variable is defined if uid_t is a signed quanity
 */
/*#define	UIDS_ARE_SIGNED	/ * */

#endif
