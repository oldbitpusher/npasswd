/*
 * passwdtab.h - list of possible locations for the password file
 *	*** Do not modify this file directly - make changes to %M% ***
 * %W% %G% (cc.utexas.edu)
 */
struct passwd_files etc_passwd[] = {
/*	passwd		temp		old		lock	*/
#ifdef	LOCAL_TEST_FILES
	{ "./etc_passwd", "./etc_ptmp", "./etc_opasswd", "./passwd_lock" },
#endif
#ifdef	XPASSWD_FILE
	{ XPASSWD_FILE, XPASSWD_TEMP, XPASSWD_SAVE, XPASSWD_LOCK },
#endif

	/* Password file /etc/passwd */
	{ "/etc/passwd", "/etc/ptmp", "/etc/opasswd", 0 },
	{ 0 }
};
/* End passwdtab.h */
