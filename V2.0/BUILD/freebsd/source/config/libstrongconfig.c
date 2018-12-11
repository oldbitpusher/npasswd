 /*
  * Copyright 1998-2001, Texas Instruments. All rights reserved.
  *
  * By using this software the USER indicates that he or she has read,
  * understood and will comply with the following:
  *
  * 1. the above copyright notice appears in all copies of the software
  *    and its documentation, or portions thereof, and
  * 2. a full copy of this notice is included with the software and its
  *    documentation, or portions thereof, and
  * 3. neither the software nor its documentation, nor portions thereof,
  *    is sold for profit. Any commercial sale or license of this software,
  *    copies of the software, its associated documentation and/or
  *    modifications of either is strictly prohibited without the prior
  *    consent of Texas Instruments.
  * 4. This software and any associated documentation are provided "as is,"
  *    and any issues, problems are yours to deal with. The USER takes
  *    full responsibility for the performance of this software.
  *
  *
  *  Read Config File
  *  (Adapted From npasswd's config reading function)
  *
  * Written by: Victor Burns
  *       Date: Apr-Aug 1999
  *    Updates: Feb-Dec 2000
  *
  */
  
#include <time.h>
#include <syslog.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <defines.h>
#include <compatibility.h>
#include <checkpassword.h>
#include <options.h>
#include <common.h>
#include <udpchk.h>
#include "libstrongconfig.h"

static int		debugLog;	/* By default no syslog messages */
static time_t		configmtime=0;	/* Modified time of config file  */
int			errno;		/* System error number storage   */

int
udp_readConfig ( servNames, clntNames, passCode )
    char	*** servNames;
    char	*** clntNames;
    char	**  passCode;
{
    FILE		*pf;		/* Config file I/O               */
    char		*config;	/* Configuration file            */


   /*
    *  Misc variable inits
    */

    config   = CONFIG_FILE;

   /*
    *  Read PW Configuration File
    */

    *servNames  = calloc( MAXSERVERNAMES+1, sizeof((char *)0));	/* Server    */
    *clntNames  = calloc( MAXCLIENTNAMES+1, sizeof((char *)0));	/* Clients   */
    *passCode   = calloc( MAXPASSCODE+1,    sizeof( char    )); /* Pass Code */

    (*servNames)[0] = (*servNames)[MAXSERVERNAMES] = (char *)NULL;
    (*clntNames)[0] = (*clntNames)[MAXCLIENTNAMES] = (char *)NULL;

    if (pf = fopen(config, "r"))	/* open Configuration file           */
	(void) fclose(pf);
    else
	config = "/admin/pam_strong/etc/passwd.conf";

    if (pf = fopen(config, "r"))	/* open Configuration file           */
    {
	char	ibuf[BUFSIZ];		/* input line buffer                 */
	int	cfline = 0;		/* Configuration file line number    */
	char	**p1,**p2,**p3,**p4;	/* misc pointers                     */

	p3 = *servNames;		/* point to top of server list       */
	p4 = *clntNames;		/* point to top of client list       */

	while(fgets(ibuf, BUFSIZ, pf))
	{

	    chop_nl(ibuf);
	    cfline++;

	    if( *ibuf == 0 || *ibuf == '#' ) continue;

	    if( instringcase(ibuf, "authorize.") )
	    {
		p2 = p1 = split(ibuf, 0,0,'#');

		if( strcmp(*p1,"authorize.Passcode") == 0 )
		{
		    p2++;
		    (*passCode)[MAXPASSCODE] = '\0';
		    if(*p2) strncpy(*passCode,*p2,MAXPASSCODE);
		    free(p1);
		    continue;
		}

		if( strcmp(*p1,"authorize.Server") == 0 )
		{
		    for(p2++;*p2;p2++,p3++)
		    {
			if(( p3 - *servNames ) >= MAXSERVERNAMES )
			{
			    /* if(debugLog >= DEBUG_LOG_LEVEL1) */
			    syslog(LOG_INFO,
				"Warning: Dropped server [ %-8s ] "
				"MAXSERVERNAMES = %03d exceeded\n",
				*p2, MAXSERVERNAMES );
			    continue;
			}
			*p3 = malloc(strlen(*p2)+1);
			strcpy(*p3,*p2);
		    }
		    free(p1);
		    continue;
		}

		if( strcmp(*p1,"authorize.Client") == 0 )
		{
		    for(p2++;*p2;p2++,p4++)
		    {
			if(( p4 - *clntNames ) >= MAXCLIENTNAMES )
			{
			    /* if(debugLog >= DEBUG_LOG_LEVEL1) */
			    syslog(LOG_INFO,
				"Warning: Dropped client [ %-8s ] "
				"MAXCLIENTNAMES = %03d exceeded\n",
				*p2, MAXCLIENTNAMES );
			    continue;
			}
			*p4 = malloc(strlen(*p2)+1);
			strcpy(*p4,*p2);
		    }
		    free(p1);
		    continue;
		}

		free(p1);
		continue;
	    }

	    if( instringcase(ibuf, "passwd.") == 0 ) continue;

	}
	(void) fclose(pf);
    }

    return(udp_authorizedServer(*servNames));
}

/*
 *  Reread Config if changed
 */

int
udp_readConfigUpdate ( servNames, clntNames, passCode )
    char	*** servNames;
    char	*** clntNames;
    char	**  passCode;
{
    int			x;
    struct stat		st;
    char		*config;	/* Configuration file            */

   /*
    *  Stat Config file
    */

    config   = CONFIG_FILE;
    x = stat(config,&st);

   /*
    *  Try alternate config file path
    *  When both fail syslog the event and return with current config.
    */

    if(x) config = "/admin/pam_strong/etc/passwd.conf";
    if(x) x = stat(config,&st);

    if(x) {
	syslog(LOG_INFO,"Reconfig: failed in udp_readConfigUpdate() = %d",errno);
	return(udp_authorizedServer(*servNames));
    }

   /*
    *  Stat success
    *
    *   1) Return if file unchanged
    *   2) reconfig if mtime newer
    */

    if( st.st_mtime <= configmtime ) return(udp_authorizedServer(*servNames));

    if( configmtime ) syslog(LOG_INFO,"Reconfig: Config file change detected");

    configmtime = st.st_mtime;

    if(*servNames) for(x=0;(*servNames)[x];x++) { free((*servNames)[x]); (*servNames)[x] = NULL; }
    if(*clntNames) for(x=0;(*clntNames)[x];x++) { free((*clntNames)[x]); (*clntNames)[x] = NULL; }

    if(*servNames) free(*servNames);
    if(*clntNames) free(*clntNames);
    if(*passCode)  free(*passCode);

    return(udp_readConfig( servNames, clntNames, passCode ));
}

/*
 *  Given List of server names
 *  test if we are a authorized server
 *
 *   1 = authorized server
 *   0 = unknown    server
 */

int udp_authorizedServer(servNames)
	char	**servNames;
{

    int			Authorized;	/* Flags Authorized Server       */
    struct utsname	uName;		/* Unix uname info               */
    char		**cl;		/* Temp Pointer                  */

    uname(&uName);
    Authorized = 0;

    for(cl=servNames;*cl;cl++)
    {
	if( strcmp(uName.nodename,*cl) == 0 )
	{
	    Authorized = 1;
	    break;
	}
    }

    return(Authorized);
}

/*
 *  Given list of client names
 *  test if client named is on the list
 *
 *  1 = authorized client
 *  0 = unknown    client
 */

int udp_authorizedClient(clntNames,clientName)
	char	**clntNames;
	char	*clientName;
{
    int			Authorized;	/* Flags Authorized Client       */
    char		**cl;		/* Temp Pointer                  */

    Authorized = 0;
    for(cl=clntNames;*cl;cl++)
    {
	if( strcmp(clientName,*cl) == 0 )
	{
	    Authorized = 1;
	    break;
	}
    }

    return(Authorized);
}

/*
 *  Given list of client names
 *  test if we are on the authorized client list
 *
 *  1 = authorized client
 *  0 = unknown    client
 */

int udp_authorizedClientI(clntNames)
	char	**clntNames;
{
    struct utsname	uName;		/* Unix uname info               */

    uname(&uName);
    return(udp_authorizedClient(clntNames,uName.nodename));
}

/* END */
