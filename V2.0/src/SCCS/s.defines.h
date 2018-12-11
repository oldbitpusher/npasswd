h48126
s 00010/00001/00025
d D 1.4 98/06/23 11:08:14 clyde 4 3
c Add symbolic debugging level name defines
e
s 00014/00000/00012
d D 1.3 98/03/26 11:19:00 clyde 3 2
c Remove debugging levels (moved to constants.h)
e
s 00000/00005/00012
d D 1.2 96/08/15 11:01:18 clyde 2 1
c Remove const setting (already in config.sh)
e
s 00017/00000/00000
d D 1.1 96/08/06 14:14:56 clyde 1 0
c date and time created 96/08/06 14:14:56 by clyde
e
u
U
f e 0
t
T
I 1
/*
 *	%W% %G%
 */

/*
 * Definitions for making the source look pretty
 */
#define	Config_Value	/* */
#define	public		/* */
#define	private	static
D 2
#ifdef	HAS_CONST
# define	const	const
#else
# define	const	/* */
#endif
E 2

I 3
/*
D 4
 * Debugging levels for npasswd and checkpasswd
E 4
I 4
 * Internal debug levels for npasswd and checkpasswd
E 4
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

I 4
/*
 * Compliation debug levels
 */
#define	CDEBUG_NONE	0		/* No debug code active */
#define	CDEBUG_DBX	1		/* Debugger friendly */
#define	CDEBUG_FILES	2		/* Put local files first in path */
#define	CDEBUG_SYSTEM	3		/* Supress lots of system stuff */
#define	CDEBUG_ALL	7		/* Activate all debugging */

E 4
E 3
/* End %M% */
E 1
