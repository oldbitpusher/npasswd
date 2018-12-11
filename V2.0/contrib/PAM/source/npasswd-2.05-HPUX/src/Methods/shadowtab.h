/*
 * shadowtab.h - list of possible locations for the shadow file
 *	*** Do not modify this file directly - make changes to shadowtab.h.SH ***
 * @(#)shadowtab.h.SH	1.5 06/23/98 (cc.utexas.edu)
 */
struct passwd_files etc_shadow[] = {
/*	shadow		temp		old		lock	*/
#if	(CDEBUG >= CDEBUG_FILES)
	{ "./etc_shadow", "./etc_stmp", "./etc_oshadow", 0 },
#endif
#ifdef	XSHADOW_FILE
	{ XSHADOW_FILE, XSHADOW_TEMP, XSHADOW_SAVE, 0 },
#endif
	{ 0 }
};
/* End shadowtab.h */
