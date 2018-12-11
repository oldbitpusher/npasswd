/*
 * Copyright Texas Instruments
 * All rights reserved
 *
 * Written by: Victor Burns
 *       Date: 1999-2000
 *
 *  Common Definitions for UDP Client/Server Data
 *
 */

#ifndef	_UDPCHK_H
#define	_UDPCHK_H

#include <libhide.h>

#ifdef  __cplusplus
extern "C" {
#endif


/*
 *  MISC LIMITS and VALUES
 */

#define	MAX_CHILDREN	3	/* Max Number serviced by server at one time */
#define	DGRAMBUFSIZE	2048	/* Max Buffer size                           */
#define	MAXSERVERNAMES	2	/* Only one server! (Long and Short Names)   */
#define	MAXCLIENTNAMES	5000	/* Max clients (needs to be dynamic)         */


/*
 *  Server Commands
 */

#define	CMD_PING	1001	/* Ping server (is server up?)               */
#define	CMD_PWCHK	1002	/* Check passwd                              */
#define	CMD_PWGETHIST	1003	/* Get users password history                */
#define	CMD_PWPUTHIST	1004	/* Put password in user history              */
#define	CMD_DEBUG_OFF	1070	/* DUBUG level 0   OFF                       */
#define	CMD_DEBUG_ON1	1071	/* DEBUG level 1   LOW                       */
#define	CMD_DEBUG_ON2	1072	/* DEBUG level 2   LITTLE                    */
#define	CMD_DEBUG_ON3	1073	/* DEBUG level 3   MEDIUM                    */
#define	CMD_DEBUG_ON4	1074	/* DEBUG level 4   HIGH                      */
#define	CMD_DEBUG_ON5	1075	/* DEBUG level 5   EXTREME                   */

/*
 *  Server Status/Error Codes
 */

#define	PW_STAT_NOSERVICE	-3
#define	PW_STAT_PASSCODE	-2
#define	PW_STAT_UNAUTHORIZED	-1
#define	PW_STAT_FAIL		 0
#define	PW_STAT_PASS		 1
#define	PW_STAT_OK		 2
#define	PW_STAT_READY		 3

/*
 *  Request/Response Datagram
 */

#define	MAXPASSCODE		31
#define	MAXMSGSIZE		316

struct pw_dgram
{
 uint	pw_type;		/* Request/Response Type			*/
 uint	pw_request;		/* Sequence Number				*/
 int	pw_stat;		/* Status					*/
 time_t	pw_time;		/* Time Transaction was created			*/
 uid_t	pw_uid;			/* User Uid					*/
 char	pw_uname[9];		/* User Uname					*/
 char	pw_pwd[16];		/* Encrypted Password				*/
 char	pw_pc[MAXPASSCODE+1];	/* Security PassCode				*/
 char	pw_msg[MAXMSGSIZE+1];	/* Password maint-library status message	*/
 char	pw_synity[HIDE_SANITY]; /* Sanity Check growing room			*/
};


/*
 *  Debug SYSLOG Message Levels
 */

#define	DEBUG_LOG_LEVEL0	0	/* None */
#define	DEBUG_LOG_LEVEL1	1	/* Low  */
#define	DEBUG_LOG_LEVEL2	2	/* Litt */
#define	DEBUG_LOG_LEVEL3	3	/* Med  */
#define	DEBUG_LOG_LEVEL4	4	/* Lots */
#define	DEBUG_LOG_LEVEL5	5	/* High */

/*
 *  Declared Functions
 */

/*
typedef void		Sigfunc(int);
Sigfunc *		Signal(int, Sigfunc *);
*/


/*
 * Get Password History
 */

extern char * pwck_history (char *, struct passwd *);
extern char * pwck_get_history (char *);
extern void   pwck_history_probe (char *);
extern int    instringcase (char *,char *);
extern char * crypt (const char *, const char *);

#ifdef  __cplusplus
}
#endif

#endif  /* _UDPCHK_H */

/* END */
