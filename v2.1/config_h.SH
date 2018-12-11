case $CONFIG in
'')
	if test -f config.sh; then TOP=.;
	elif test -f ../config.sh; then TOP=..;
	elif test -f ../../config.sh; then TOP=../..;
	elif test -f ../../../config.sh; then TOP=../../..;
	elif test -f ../../../../config.sh; then TOP=../../../..;
	else
		echo "Can't find config.sh."; exit 1
	fi
	. $TOP/config.sh
	;;
esac
case "$0" in
*/*) cd `expr X$0 : 'X\(.*\)/'` ;;
esac
echo "Extracting config.h (with variable substitutions)"
sed <<!GROK!THIS! >config.h -e 's!^#undef\(.*/\)\*!/\*#define\1 \*!' -e 's!^#un-def!#undef!'
/*
 * This file was produced by running the config_h.SH script, which
 * gets its values from config.sh, which is generally produced by
 * running Configure.
 *
 * Feel free to modify any of this as the need arises.  Note, however,
 * that running config_h.SH again will wipe out any changes you've made.
 * For a more permanent change edit config.sh and rerun config_h.SH.
 *
 * \$Id: Config_h.U,v 3.0.1.5 1997/02/28 14:57:43 ram Exp $
 */

/*
 * Package name      : $package
 * Source directory  : $src
 * Configuration time: $cf_time
 * Configured by     : $cf_by
 * Target system     : $myuname
 */

#ifndef _config_h_
#define _config_h_

/* BSD:
 *	This symbol, if defined, indicates that the program is running under
 *	a BSD system.
 */
#$d_bsd BSD		/**/

/* HASCONST:
 *	This symbol, if defined, indicates that this C compiler knows about
 *	the const type. There is no need to actually test for that symbol
 *	within your programs. The mere use of the "const" keyword will
 *	trigger the necessary tests.
 */
#$d_const HASCONST	/**/
#ifndef HASCONST
#define const
#endif

/* HAS_FCHMOD:
 *	This symbol, if defined, indicates that the fchmod routine is available
 *	to change mode of opened files.  If unavailable, use chmod().
 */
#$d_fchmod HAS_FCHMOD		/**/

/* HAS_FCHOWN:
 *	This symbol, if defined, indicates that the fchown routine is available
 *	to change ownership of opened files.  If unavailable, use chown().
 */
#$d_fchown HAS_FCHOWN		/**/

/* HAS_GETHOSTNAME:
 *	This symbol, if defined, indicates that the C program may use the
 *	gethostname() routine to derive the host name.  See also HAS_UNAME
 *	and PHOSTNAME.
 */
#$d_gethname HAS_GETHOSTNAME	/**/

/* HAS_MEMCPY:
 *	This symbol, if defined, indicates that the memcpy routine is available
 *	to copy blocks of memory.
 */
#$d_memcpy HAS_MEMCPY	/**/

/* HAS_MEMSET:
 *	This symbol, if defined, indicates that the memset routine is available
 *	to set blocks of memory.
 */
#$d_memset HAS_MEMSET	/**/

/* HAS_READDIR:
 *	This symbol, if defined, indicates that the readdir routine is
 *	available to read directory entries. You may have to include
 *	<dirent.h>. See I_DIRENT.
 */
#$d_readdir HAS_READDIR		/**/

/* HAS_RENAME:
 *	This symbol, if defined, indicates that the rename routine is available
 *	to rename files.  Otherwise you should do the unlink(), link(), unlink()
 *	trick.
 */
#$d_rename HAS_RENAME	/**/

/* HAS_SIGBLOCK:
 *	This symbol, if defined, indicates that the sigblock routine is
 *	available to block signal reception.
 */
#$d_sigblock HAS_SIGBLOCK	/**/

/* HAS_STRCASECMP:
 *	This symbol, if defined, indicates that the strcasecmp() routine is
 *	available for case-insensitive string compares.
 */
#$d_strccmp HAS_STRCASECMP	/**/

/* HAS_STRCHR:
 *	This symbol is defined to indicate that the strchr()/strrchr()
 *	functions are available for string searching. If not, try the
 *	index()/rindex() pair.
 */
#$d_strchr HAS_STRCHR	/**/

/* HAS_STRDUP:
 *	This symbol, if defined, indicates that the strdup routine is
 *	available to duplicate strings in memory. Otherwise, roll up
 *	your own...
 */
#$d_strdup HAS_STRDUP		/**/

/* Signal_t:
 *	This symbol's value is either "void" or "int", corresponding to the
 *	appropriate return type of a signal handler.  Thus, you can declare
 *	a signal handler using "Signal_t (*handler)()", and define the
 *	handler using "Signal_t handler(sig)".
 */
#define Signal_t $signal_t	/* Signal handler's return type */

/* Gid_t:
 *	This symbol holds the return type of getgid() and the type of
 *	argument to setrgid() and related functions.  Typically,
 *	it is the type of group ids in the kernel. It can be int, ushort,
 *	uid_t, etc... It may be necessary to include <sys/types.h> to get
 *	any typedef'ed information.
 */
#define Gid_t $gidtype		/* Type for getgid(), etc... */

/* I_DBM:
 *	This symbol, if defined, indicates that <dbm.h> exists and should
 *	be included.
 */
#$i_dbm I_DBM	/**/

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
#$i_dirent I_DIRENT		/**/
#define Direntry_t $direntrytype

/* I_MEMORY:
 *	This symbol, if defined, indicates to the C program that it should
 *	include <memory.h>.
 */
#$i_memory I_MEMORY		/**/

/* I_NDBM:
 *	This symbol, if defined, indicates that <ndbm.h> exists and should
 *	be included.
 */
#$i_ndbm I_NDBM	/**/

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
#$d_pwquota PWQUOTA	/**/
#$d_pwage PWAGE	/**/
#$d_pwcomment PWCOMMENT	/**/

/* I_STDLIB:
 *	This symbol, if defined, indicates that <stdlib.h> exists and should
 *	be included.
 */
#$i_stdlib I_STDLIB		/**/

/* I_STRING:
 *	This symbol, if defined, indicates to the C program that it should
 *	include <string.h> (USG systems) instead of <strings.h> (BSD systems).
 */
#$i_string I_STRING		/**/

/* I_SYS_PARAM:
 *	This symbol, if defined, indicates to the C program that it should
 *	include <sys/param.h>.
 */
#$i_sysparam I_SYS_PARAM		/**/

/* I_SYS_RESOURCE:
 *	This symbol, if defined, indicates to the C program that it should
 *	include <sys/resource.h>.
 */
#$i_sysresrc I_SYS_RESOURCE		/**/

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
#$i_termio I_TERMIO		/**/
#$i_termios I_TERMIOS		/**/
#$i_sgtty I_SGTTY		/**/

/* I_SYS_TIME:
 *	This symbol, if defined, indicates to the C program that it should
 *	include <sys/time.h>.
 */
#$i_systime I_SYS_TIME		/**/

/* I_UNISTD:
 *	This symbol, if defined, indicates to the C program that it should
 *	include <unistd.h>.
 */
#$i_unistd I_UNISTD		/**/

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
#$prototype	CAN_PROTOTYPE	/**/
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
#define Uid_t $uidtype		/* UID type */

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
#define VOIDUSED $defvoidused
#endif
#define VOIDFLAGS $voidflags
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
/* HAS_UTSNAME_H:
 *	Defined if <sys/utsname.h> is available
 */
#$p_utsname	HAS_UTSNAME_H	/**/
#$p_nis	USE_NIS		/**/
#$p_nisplus	USE_NISPLUS	/**/
#$p_nispasswd	HAS_NISPASSWD	/**/
#$p_kerberos	USE_KERBEROS	/**/
#$p_svcconf	HAS_SVCCONF	/**/
#$p_nsswitch	HAS_NSSWITCH	/**/
#$p_dbmpw 	DBM_PASSWD	/**/
#$p_osf1auth OSF1_AUTH	/**/
#$p_u4auth 	ULTRIX_AUTH	/**/
#$p_aixauth 	AIX_AUTH	/**/
#$p_hpuxauth	HPUX_AUTH	/**/
#$p_secure_rpc SECURE_RPC	/**/
#$p_paranoid	PARANOID_UIDCHECK 	/**/
#define	PASSWD_DICTIONARIES "$p_dictionaries"	/**/
#define	PASSWORD_HISTORY_DB "$p_history"	/**/

/* HAS_CLNT_SPERRNO:
 *	This symbol, if defined, indicates that clnt_sperrno exists.
 */
#$p_clnt_sperrno	HAS_CLNT_SPERRNO	/**/

/* HAS_FGETPWENT:
 *	This symbol, if defined, indicates that libc fgetpwent should be used.
 */
#$p_fgetpwent	HAS_FGETPWENT	/**/

/* HAS_GETUSERSHELL:
 *	This symbol, if defined, indicates that getusershell exists.
 */
#$p_getusershell	HAS_GETUSERSHELL	/**/

/* HAS_LCKPWDF:
 *	This symbol, if defined, indicates that lckpwdf and ulckpwdf exist.
 */
#$p_lckpwdf	HAS_LCKPWDF	/**/

/* HAS_PUTPWENT:
 *	This symbol, if defined, indicates that the putpwent routine exists.
 */
#$p_putpwent	HAS_PUTPWENT	/**/

/* HAS_XDR_PASSWD:
 *	This symbol, if defined, indicates that the xdr_passwd routine exists
 */
#$p_xdr_passwd HAS_XDR_PASSWD		/**/

/* HAS_POSIX_SIGNALS:
 *	This symbol, if defined, indicates that the POSIX signal routines exist.
 */
#$p_sigposix	HAS_POSIX_SIGNALS	/**/

/* HAS_SYSINFO:
 *	This symbol, if defined, indicates that the
 *	sysinfo and ugetrlimit routines can be used.
 */
#$p_sysinfo	HAS_SYSINFO	/**/

/* HAS_POSIX_TTY:
 *	This symbol, if defined, indicates that the POSIX terminal routines exist.
 */
#$p_ttyposix	HAS_POSIX_TTY	/**/

/* UIDS_ARE_SIGNED:
 *	This variable is defined if uid_t is a signed quanity
 */
#$uidsigned	UIDS_ARE_SIGNED	/* */

#endif
!GROK!THIS!
