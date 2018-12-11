/*
 * shadowtab.h - list of possible locations for the shadow file
 *	*** Do not modify this file directly - make changes to %M% ***
 * %W% %G% (cc.utexas.edu)
 */
struct passwd_files etc_shadow[] = {
/*	shadow		temp		old		lock	*/
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
	{ "./etc_shadow", "./etc_stmp", "./etc_oshadow", 0 },
#endif
#ifdef	XSHADOW_FILE
	{ XSHADOW_FILE, XSHADOW_TEMP, XSHADOW_SAVE, 0 },
#endif

	/* Shadow file /etc/shadow */
	{ "/etc/shadow", "/etc/stmp", "/etc/oshadow", 0 },
	{ 0 }
};
/* End shadowtab.h */
