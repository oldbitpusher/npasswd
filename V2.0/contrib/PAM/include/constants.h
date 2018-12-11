/*
 * 	Constants used throughout npasswd
 *
 *	@(#)constants.h	1.8 11/17/98
 */

/*
 * -X suboptions
 */
#define Xsw_Chsh		's'
#define Xsw_Chfn		'f'
#define Xsw_Help		'h'
#define Xsw_AskAll		'A'
#define Xsw_CheckConfig		'C'
#define Xsw_ShowConfig		'c'
#define Xsw_SetDebug		'D'
#define Xsw_ForcePWChange	'F'
#define Xsw_UseStdin		'I'
#define Xsw_ShowVersion		'V'

/*
 * Various string buffer sizings
 */
#define	STRINGLEN	32		/* Length for miscelleanous strings */
#define	PW_LINELEN	512		/* Length for passwd lines */
#define	TMPBUFSIZ	1024		/* Size of miscellanous buffers */

/*
 * The following are fundamental constants.
 * Don't alter these unless a major change has taken place
 * (e.g. adoption of a new calendar, revocation of the laws of physics)
 */
#define	DAYS_WEEK	7
#define	SEC_DAY		(time_t)86400
#define	SEC_WEEK	(time_t)(SEC_DAY * DAYS_WEEK)

/* End constants.h */
