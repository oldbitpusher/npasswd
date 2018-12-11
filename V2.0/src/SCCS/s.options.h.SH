h06121
s 00003/00000/00190
d D 1.12 98/10/14 10:43:59 clyde 12 11
c Add SHORT_FILE_WARN comment
e
s 00008/00010/00182
d D 1.11 98/07/16 09:17:57 clyde 11 10
c Use new config path vars
e
s 00133/00023/00059
d D 1.10 98/06/23 11:08:38 clyde 10 9
c Major rework
e
s 00010/00001/00072
d D 1.9 98/03/26 11:22:42 clyde 9 8
c Insert some defines removed from config.h
e
s 00004/00000/00069
d D 1.8 98/03/24 15:23:46 clyde 8 7
c Add DICT_DISP, PASSWORD_MATCH_WAIT and LONG_PASSWORD_WARNING
e
s 00006/00000/00063
d D 1.7 97/09/23 12:20:38 clyde 7 6
c Add DENY_CHSH and DENY_CHFN options (disabled)
e
s 00002/00000/00061
d D 1.6 96/12/05 11:01:26 clyde 6 5
c Add DICTIONARIES define
e
s 00000/00003/00061
d D 1.5 96/09/13 15:39:58 clyde 5 4
c Remove password history defines (now in config.h)
e
s 00003/00000/00061
d D 1.4 96/08/13 17:58:08 clyde 4 3
c Add PASSWD_DIFF_OK and SHADOW_DIFF_OK
e
s 00019/00010/00042
d D 1.3 96/08/13 09:20:48 clyde 3 2
c Update comments, add password history config items
e
s 00001/00001/00051
d D 1.2 96/08/06 14:14:01 clyde 2 1
c beta 3 cycle 1 checkin
e
s 00052/00000/00000
d D 1.1 95/04/05 16:26:56 clyde 1 0
c date and time created 95/04/05 16:26:56 by clyde
e
u
U
f e 0
t
T
I 1
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
: This forces SH files to create target in same directory as SH file.
: This is so that make depend always knows where to find SH derivatives.
case "$0" in
*/*) cd `expr X$0 : 'X\(.*\)/'` ;;
esac
echo "Extracting options.h (with variable substitutions)"

$rm -f options.h
$spitshell >options.h <<!GROK!THIS
/*
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
E 10
D 3
 * Configuration options for npasswd and checkpassword
E 3
I 3
 * Defaults for npasswd configuration settings.
D 10
 * Most of these can be overridden by entries in
E 10
I 10
 * Some of these can be overridden by entries in
E 10
 * the configuration file.
E 3
 *
I 10
 * Change to options.h will go away the next time Configure is run!
 * Make permanent changes to %M%
 *
E 10
 * %W% %G% (cc.utexas.edu)
 */
I 3

E 3
/*
D 3
 * Paths to various files
E 3
I 3
D 10
 * Items for npasswd
E 10
I 10
 * Values which are hard wired into the code
E 10
E 3
 */
D 3
#define CONFIG_FILE "$privlibexp/passwd.conf"
E 3
I 3
D 10
#define CONFIG_FILE "$privlibexp/passwd.conf"	/* Configuration file */
E 10
I 10
D 11
#define CONFIG_FILE	"$privlibexp/passwd.conf"	/* Config file */
E 11
I 11
#define CONFIG_FILE	"$p_installdir/passwd.conf"	/* Config file */
E 11
#define	SAVED_BIN	"$p_keepdir"	/* Where vendor programs were saved */
D 11
#define DICTIONARIES	"$p_dictlib"	/* Default dictionary collection */
E 11
I 11
#define DICTIONARIES	"$p_dictionaries" /* Dictionary collection */
E 11
E 10
E 3

I 10
#define	PASSWD_UID	0		/* Uid for passwd files */
#define	PASSWD_GID	0		/* Gid for passwd files */
#define	PASSWD_MODE	0444		/* Mode for passwd files */

#define	SHADOW_UID	0		/* Mode for shadow files */
#define	SHADOW_GID	0		/* Mode for shadow files */
#define	SHADOW_MODE	0400		/* Mode for shadow files */

#define	SHELLS_FILE	"/etc/shells"	/* List of blessed shells */

D 11
#define	DEFER_SWITCHES	"$defer_options"

E 11
/*
 * Defaults for settings which can be altered in the config file
 */
E 10
D 3
#define CHFN_HELP "$privlibexp/chfn.help"
#define CHFN_MOTD "$privlibexp/chfn.motd"
E 3
I 3
D 11
#define CHFN_HELP "$privlibexp/chfn.help"	/* chfn help messsage */
#define CHFN_MOTD "$privlibexp/chfn.motd"	/* chfn intro message */
E 11
I 11
#define CHFN_HELP "$p_installdir/chfn.help"	/* chfn help messsage */
#define CHFN_MOTD "$p_installdir/chfn.motd"	/* chfn intro message */
E 11
E 3

D 3
#define CHSH_HELP "$privlibexp/chsh.help"
#define CHSH_MOTD "$privlibexp/chsh.motd"
E 3
I 3
D 11
#define CHSH_HELP "$privlibexp/chsh.help"	/* chsh help message */
#define CHSH_MOTD "$privlibexp/chsh.motd"	/* chsh intro message */
E 11
I 11
#define CHSH_HELP "$p_installdir/chsh.help"	/* chsh help message */
#define CHSH_MOTD "$p_installdir/chsh.motd"	/* chsh intro message */
E 11
E 3

D 3
#define PASSWD_HELP "$privlibexp/passwd.help"
#define PASSWD_MOTD "$privlibexp/passwd.motd"
#define	PASSWD_HISTORY	"$o_histfile"
E 3
I 3
D 11
#define PASSWD_HELP "$privlibexp/passwd.help"	/* passwd help message */
#define PASSWD_MOTD "$privlibexp/passwd.motd"	/* passwd intro message */
E 11
I 11
#define PASSWD_HELP "$p_installdir/passwd.help"	/* passwd help message */
#define PASSWD_MOTD "$p_installdir/passwd.motd"	/* passwd intro message */
E 11
E 3

I 6
D 10
#define DICTIONARIES "$p_dictlib"		 /* default dictionaries */
E 10
I 10
#define	PASSWD_DIFF_OK		128	/* Old <-> new passwd size diff ok */
#define	SHADOW_DIFF_OK		32	/* Old <-> new shadow size diff ok */
#define	PASSWORD_MATCH_WAIT	2	/* Password match fail delay */
#define	PASSWORD_MATCH_TRIES	3	/* Password match retries */
E 10

I 9
D 10
#define	PASSWD_UID	0
#define	PASSWD_GID	0
#define	PASSWD_MODE	0444
E 10
I 10
#define	PASSWORD_HISTORY_AGE	180	/* Maximum age in password history */
#define	PASSWORD_HISTORY_DEPTH	2	/* Passwords per user in history */
E 10

D 10
#define	SHADOW_UID	0
#define	SHADOW_GID	0
#define	SHADOW_MODE	0400
E 10
I 10
!GROK!THIS
E 10

D 10
#define	SHELLS_FILE	"/etc/shells"
E 10
I 10
$spitshell >>options.h <<'!NO!SUBS!'
E 10

E 9
E 6
I 3
/*
D 10
 * Items for checkpasswd library and standalone program
E 10
I 10
 * More program options
E 10
 */
I 10
#undef	DENY_CHSH			/* Define to disable chsh */
#undef	DENY_CHFN			/* Define to disable chfn */
#undef	PASSWORD_MATCH_BACKOFF		/* Define to use expotential backoff
					 * after user enters wrong password */
/*
 * Defines which are here for documentation purposes.
 * They are really defined in various places, but can be overridden
 * by defining them here (or in the Makefile).
 *
 * If you need to change them permanently, move the line out of the
 * "#ifdef ___DEFINE_COMMENTS___" block.
 */
#ifdef	___DEFINE_COMMENTS___
E 10
D 5
#define	PASSWD_HISTORY	"$o_histfile"		/* password history db */
#define	PASSWD_HISTORY_DEPTH	$o_pwhSize	/* How many items to keep */
#define	PASSWD_HISTORY_AGE	$o_pwhTime	/* expiration age for history */
E 5

I 4
D 10
#define	PASSWD_DIFF_OK	128
#define	SHDAOW_DIFF_OK	32
E 10
I 10
/*
 * Defines to make debugging / test versions
 */
#define	CDEBUG			/* Build test code */
				/* Levels are in defines.h */
#define	DEBUG_DEFAULT	N	/* Set default debugging level to N */
#define	CRACKLIB_DEBUG		/* Enable debugging in Cracklib */
#define	CRACKLIB_PERROR		/* Enable error message spew in Cracklib */
E 10

I 12

E 12
I 7
/*
D 10
 * More program options
E 10
I 10
 * Defines which will are usually set by Configure
E 10
 */
D 10
#undef	DENY_CHSH	/* Define to disable chsh */
#undef	DENY_CHFN	/* Define to disable chfn */
I 8
#undef	DICT_DISP	/* Define to enable dictionary word display */
#define	PASSWORD_MATCH_WAIT	3	/* Password match fail delay */
#undef	LONG_PASSWORD_WARNING	/* Define to enable warnings about passwords
				 * longer than the configured maximum */
E 8
D 9

E 9
E 7
E 4
E 3
!GROK!THIS
E 10
I 10
#undef	SWITCHES_OS	/* OS-specific commmand line options supported */
#undef	SWITCHES_DEFER	/* OS-specific commmand line options
			 * for which the saved programs are run. */
#define	UIDS_ARE_SIGNED	/* UID type (uid_t) is signed (vs. unsigned) */
E 10

D 10
$spitshell >>options.h <<'!NO!SUBS!'
E 10
/*
I 10
 * Defines to override internal settings 
 */
#define	FLOCK_TRIES	N	/* Set file locking retry count to N */
#define	FLOCK_CYCLE	N	/* Set file locking retry wait to N seconds */
#define	SYSTEM_PASSWD_MIN N	/* Set minimum acceptable password length */
#define	SYSTEM_PASSWD_MAX N	/* Set maximum effective password length */

/*
 * Defines for method modules
 */
#define XSHADOW_FILE	/path	/* Alternate shadow file */
#define XSHADOW_TEMP	/path	/* Alternate shadow temp file */
#define XSHADOW_SAVE	/path	/* Alternate shadow save file */
#define XSHADOW_LOCK	/path	/* Alternate shadow lock file */

#define XPASSWD_FILE	/path	/* Alternate passwd file */
#define XPASSWD_TEMP	/path	/* Alternate passwd temp file */
#define XPASSWD_SAVE	/path	/* Alternate passwd save file */
#define XPASSWD_LOCK	/path	/* Alternate passwd lock file */

I 12
#define	SHORT_FILE_WARN		/* Do not abort when temp files come up short */

E 12
/*
 * Defines for NIS method module "src/Methods/pwm_nis.c"
 */
#define	YP_PROBE_TIMEOUT	N
#define	YP_TIMEOUT		N
#define	NIS_PASSWD_MAX_LEN	N
#define SYSTEM_YP_DIR		/path	/* Alternate NIS data directory */

#endif	/* ___DEFINE_COMMENTS___ */

/*
E 10
 * End %M%
 */
!NO!SUBS!

chmod 444 options.h
D 2
exit 0
E 2
I 2
# exit 0
E 2
E 1
