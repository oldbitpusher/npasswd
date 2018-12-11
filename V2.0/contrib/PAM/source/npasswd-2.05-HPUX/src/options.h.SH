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
 * Defaults for npasswd configuration settings.
 * Some of these can be overridden by entries in
 * the configuration file.
 *
 * Change to options.h will go away the next time Configure is run!
 * Make permanent changes to options.h.SH
 *
 * @(#)options.h.SH	1.12 10/14/98 (cc.utexas.edu)
 */

/*
 * Values which are hard wired into the code
 */
#define CONFIG_FILE	"$p_installdir/passwd.conf"	/* Config file */
#define	SAVED_BIN	"$p_keepdir"	/* Where vendor programs were saved */
#define DICTIONARIES	"$p_dictionaries" /* Dictionary collection */

#define	PASSWD_UID	0		/* Uid for passwd files */
#define	PASSWD_GID	0		/* Gid for passwd files */
#define	PASSWD_MODE	0444		/* Mode for passwd files */

#define	SHADOW_UID	0		/* Mode for shadow files */
#define	SHADOW_GID	0		/* Mode for shadow files */
#define	SHADOW_MODE	0400		/* Mode for shadow files */

#define	SHELLS_FILE	"/etc/shells"	/* List of blessed shells */

/*
 * Defaults for settings which can be altered in the config file
 */
#define CHFN_HELP "$p_installdir/chfn.help"	/* chfn help messsage */
#define CHFN_MOTD "$p_installdir/chfn.motd"	/* chfn intro message */

#define CHSH_HELP "$p_installdir/chsh.help"	/* chsh help message */
#define CHSH_MOTD "$p_installdir/chsh.motd"	/* chsh intro message */

#define PASSWD_HELP "$p_installdir/passwd.help"	/* passwd help message */
#define PASSWD_MOTD "$p_installdir/passwd.motd"	/* passwd intro message */

#define	PASSWD_DIFF_OK		128	/* Old <-> new passwd size diff ok */
#define	SHADOW_DIFF_OK		32	/* Old <-> new shadow size diff ok */
#define	PASSWORD_MATCH_WAIT	2	/* Password match fail delay */
#define	PASSWORD_MATCH_TRIES	3	/* Password match retries */

#define	PASSWORD_HISTORY_AGE	180	/* Maximum age in password history */
#define	PASSWORD_HISTORY_DEPTH	2	/* Passwords per user in history */

!GROK!THIS

$spitshell >>options.h <<'!NO!SUBS!'

/*
 * More program options
 */
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

/*
 * Defines to make debugging / test versions
 */
#define	CDEBUG			/* Build test code */
				/* Levels are in defines.h */
#define	DEBUG_DEFAULT	N	/* Set default debugging level to N */
#define	CRACKLIB_DEBUG		/* Enable debugging in Cracklib */
#define	CRACKLIB_PERROR		/* Enable error message spew in Cracklib */


/*
 * Defines which will are usually set by Configure
 */
#undef	SWITCHES_OS	/* OS-specific commmand line options supported */
#undef	SWITCHES_DEFER	/* OS-specific commmand line options
			 * for which the saved programs are run. */
#define	UIDS_ARE_SIGNED	/* UID type (uid_t) is signed (vs. unsigned) */

/*
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

#define	SHORT_FILE_WARN		/* Do not abort when temp files come up short */

/*
 * Defines for NIS method module "src/Methods/pwm_nis.c"
 */
#define	YP_PROBE_TIMEOUT	N
#define	YP_TIMEOUT		N
#define	NIS_PASSWD_MAX_LEN	N
#define SYSTEM_YP_DIR		/path	/* Alternate NIS data directory */

#endif	/* ___DEFINE_COMMENTS___ */

/*
 * End options.h.SH
 */
!NO!SUBS!

chmod 444 options.h
# exit 0
