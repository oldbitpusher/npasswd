/*
 * shadowtab.h - list of possible locations for the shadow file
 *	*** Do not modify this file directly - make changes to %M% ***
 * %W% %G% (cc.utexas.edu)
 */
struct passwd_files etc_shadow[] = {
/*	shadow		temp		old		lock	*/
#ifdef	LOCAL_TEST_FILES
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
