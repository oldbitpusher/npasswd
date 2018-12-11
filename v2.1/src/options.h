/*
 * Defaults for npasswd configuration settings.
 * Some of these can be overridden by entries in
 * the configuration file.
 *
 * Change to options.h will go away the next time Configure is run!
 * Make permanent changes to %M%
 *
 * %W% %G% (cc.utexas.edu)
 */

/*
 * Values which are hard wired into the code
 */
#define CONFIG_FILE	"/usr/lib/passwd/passwd.conf"	/* Config file */
#define	SAVED_BIN	"/usr/lib/passwd/xbin"	/* Where vendor programs were saved */
#define DICTIONARIES	"/usr/lib/passwd/dictionaries"	/* Default dictionary collection */

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
#define CHFN_HELP "/usr/lib/passwd/chfn.help"	/* chfn help messsage */
#define CHFN_MOTD "/usr/lib/passwd/chfn.motd"	/* chfn intro message */

#define CHSH_HELP "/usr/lib/passwd/chsh.help"	/* chsh help message */
#define CHSH_MOTD "/usr/lib/passwd/chsh.motd"	/* chsh intro message */

#define PASSWD_HELP "/usr/lib/passwd/passwd.help"	/* passwd help message */
#define PASSWD_MOTD "/usr/lib/passwd/passwd.motd"	/* passwd intro message */

#define	PASSWD_DIFF_OK		128	/* Old <-> new passwd size diff ok */
#define	SHDAOW_DIFF_OK		32	/* Old <-> new shadow size diff ok */
#define	PASSWORD_MATCH_WAIT	2	/* Password match fail delay */
#define	PASSWORD_MATCH_TRIES	3	/* Password match retries */


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
#define	DEBUG			/* Activate debugging */
#define	DEBUG_DEFAULT	N	/* Set default debugging level to N */
#define	DEBUG_FORCE_PWCHANGE	/* Disable uid checking in passwd */
#define	DEBUG_LOCAL_FILES	/* Look for files in current directory */
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

/*
 * Defines for NIS method module "src/Methods/pwm_nis.c"
 */
#define	YP_PROBE_TIMEOUT	N
#define	YP_TIMEOUT		N
#define	NIS_PASSWD_MAX_LEN	N
#define SYSTEM_YP_DIR		/path	/* Alternate NIS data directory */

#endif /* */

/*
 * End %M%
 */
