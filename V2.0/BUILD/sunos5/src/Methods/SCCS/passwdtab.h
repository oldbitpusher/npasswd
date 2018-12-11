/*
 * passwdtab.h - list of possible locations for the password file
 *	*** Do not modify this file directly - make changes to %M% ***
 * %W% %G% (cc.utexas.edu)
 */
struct passwd_files etc_passwd[] = {
/*	passwd		temp		old		lock	*/
D 2
#ifdef	DEBUG_FILES
E 2
I 2
D 3
#ifdef	LOCAL_TEST_FILES
E 3
I 3
D 4
#ifdef	LOCAL_FILES
E 4
I 4
D 5
#ifdef	DEBUG_LOCAL_FILES
E 5
I 5
#if	(CDEBUG >= CDEBUG_FILES)
E 5
E 4
E 3
E 2
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
