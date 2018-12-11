/*
 *	$Id: defines.h,v 1.4 1998/06/23 00:00:00 clyde Exp $
 */

/*
 * Definitions for making the source look pretty
 */
#define	Config_Value	/* */
#define	public		/* */
#define	private	static

/*
 * Internal debug levels for npasswd and checkpasswd
 */
#define	DB_NONE		0		/* No debug */
#define	DB_VERBOSE	1		/* Mild verbosity */
#define	DB_LOOKUP	2		/* Trace user lookup */
#define	DB_UPDATE	3		/* Trace user update */
#define	DB_CONFIG	4		/* Trace configuration processing */
#define	DB_MISC1	5		/* Nothing yet */
#define	DB_MISC2	6		/* Nothing yet */
#define	DB_PWCHECK	7		/* Password checking */
#define	DB_DETAIL	8		/* Lots of details */
#define	DB_ALL		9		/* Trace *everything* */

/*
 * Compliation debug levels
 */
#define	CDEBUG_NONE	0		/* No debug code active */
#define	CDEBUG_DBX	1		/* Debugger friendly */
#define	CDEBUG_FILES	2		/* Put local files first in path */
#define	CDEBUG_SYSTEM	3		/* Supress lots of system stuff */
#define	CDEBUG_ALL	7		/* Activate all debugging */

/* End $RCSfile: defines.h,v $ */
