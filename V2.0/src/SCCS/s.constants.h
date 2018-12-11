h05306
s 00003/00001/00036
d D 1.9 99/07/26 12:56:02 clyde 9 8
c 1. Add Xsw_ChshSpecial, Xsw_AskOnce
c 2. Change Xsw_AskAll to Xsw_AskAlways
e
s 00001/00000/00036
d D 1.8 98/11/17 10:41:40 clyde 8 7
c Add Xsw_AskAll -X option
e
s 00001/00000/00035
d D 1.7 98/07/09 13:09:56 clyde 7 6
c Add Xsw_Help
e
s 00001/00000/00034
d D 1.6 98/07/01 14:25:52 clyde 6 5
c Add Xsw_ShowConfig suboption define
e
s 00002/00000/00032
d D 1.5 98/06/23 11:07:49 clyde 5 4
c Add more local (-X) options
e
s 00000/00001/00032
d D 1.4 98/04/21 10:56:49 clyde 4 3
c Remove Xsw_Require_OldPW
e
s 00000/00014/00033
d D 1.3 98/03/26 11:18:39 clyde 3 2
c Add debugging levels (taken from defines.h)
e
s 00008/00008/00039
d D 1.2 96/12/05 12:35:33 clyde 2 1
c Change debug level values
e
s 00047/00000/00000
d D 1.1 96/08/06 14:14:57 clyde 1 0
c date and time created 96/08/06 14:14:57 by clyde
e
u
U
f e 0
t
T
I 1
/*
 * 	Constants used throughout npasswd
 *
 *	%W% %G%
 */

/*
D 3
 * Debugging levels.  Debugging is activated by the -D command line option
 */
#define	DB_NONE		0		/* No debug */
#define	DB_VERBOSE	1		/* Mild verbosity */
D 2
#define	DB_LEVEL2	2		/* Nothing yet */
#define	DB_LEVEL3	3		/* Nothing yet */
#define	DB_LOOKUP	4		/* Trace user lookup */
#define	DB_UPDATE	5		/* Trace user update */
#define	DB_LEVEL6	6		/* Nothing yet */
#define	DB_LEVEL7	7		/* Nothing yet */
#define	DB_CONFIG	8		/* Trace configuration processing */
#define	DB_ALL		99		/* Trace *everything* */
E 2
I 2
#define	DB_LOOKUP	2		/* Trace user lookup */
#define	DB_UPDATE	3		/* Trace user update */
#define	DB_LEVEL7	4		/* Nothing yet */
#define	DB_CONFIG	5		/* Trace configuration processing */
#define	DB_MISC1	6		/* Nothing yet */
#define	DB_MISC2	7		/* Nothing yet */
#define	DB_DETAIL	8		/* Lots of details */
#define	DB_ALL		9		/* Trace *everything* */
E 2

/*
E 3
 * -X suboptions
 */
I 5
#define Xsw_Chsh		's'
I 9
#define Xsw_ChshSpecial		'S'
E 9
#define Xsw_Chfn		'f'
I 7
#define Xsw_Help		'h'
I 8
D 9
#define Xsw_AskAll		'A'
E 9
I 9
#define Xsw_AskAlways		'A'
#define Xsw_AskOnce		'O'
E 9
E 8
E 7
E 5
#define Xsw_CheckConfig		'C'
I 6
#define Xsw_ShowConfig		'c'
E 6
#define Xsw_SetDebug		'D'
#define Xsw_ForcePWChange	'F'
#define Xsw_UseStdin		'I'
D 4
#define Xsw_Require_OldPW	'R'
E 4
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

/* End %M% */
E 1
