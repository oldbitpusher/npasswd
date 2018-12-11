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
  * UDP Password Strength Server
  *
  * Written by: Victor Burns
  *       Date: Apr-Aug 1999
  *             Oct-Dec 2000
  *             Jan-    2001
  *
  */

#ifdef HPUX
#define _XOPEN_SOURCE
#define _XOPEN_SOURCE_EXTENDED
#endif

  
#include <pwd.h>
#include <shadow.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <errno.h>
#include <syslog.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
/* #include <sys/select.h> */
#include <sys/utsname.h>
#include <sys/uio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/byteorder.h>

#include <libhide.h>
#include <defines.h>
#include <compatibility.h>
#include <checkpassword.h>
#include <options.h>
#include <common.h>
#include <udpchk.h>
#include "libstrongconfig.h"

#define	PATH		"PATH=/usr/lib/passwd/bin:/usr/bin:/usr/ucb"
#define	SHLIB_PATH	"SHLIB_PATH=/usr/lib:/usr/dt/lib:/usr/lib/passwd/lib"
#define	LD_LIBRARY_PATH	"LD_LIBRARY_PATH=/usr/lib:/usr/dt/lib:/usr/openwin/lib:/usr/lib/passwd/lib"

int			errno;
static void		sig_chld(int);
static int		children[MAX_CHILDREN]; /* List of children pids */
static int		debugLog;	/* By default no syslog messages */
typedef void		Sigfunc(int);
Sigfunc *		Signal(int, Sigfunc *);

int
main ( int argc, char *argv[], char *envp[] )
{
    const int		on  = 1;	/* TRUE                          */
/*  const int		off = 0;	   FALSE                         */

    int			status;		/* Function return Status        */
    int			pwSocket;	/* Socket File Descriptor        */
    int			len;		/* Tmp length of data structures */
    int			op_val;		/* Value of socket options       */
    int			uValid;		/* is account valid?             */
    int			j, k;		/* Misc. Working Integers        */
    int			Authorized;	/* Flags Authorization Checks    */
    int			errcount;	/* count errors exit when high   */

    time_t		cTime;		/* Current Time                  */
    pid_t		pid;		/* Child process ID              */

    struct sockaddr_in	SockAddr;	/* Socket Address                */
    struct utsname	uName;		/* Unix uname info               */
    struct servent	*serviceport;	/* Service Entry & Port          */
    struct protoent	*protocol;	/* Protocol type                 */
    struct hostent	*host;		/* Host     entry                */
    struct passwd	*pwinfo;	/* Users Passwd table entry      */
    struct in_addr	in;		/* Internet Address              */
    struct pw_dgram	*dgram;		/* receive/send data             */

    ssize_t		dgram_len;	/* Size of Datagram              */

    char		*SaltSet;	/* String of valid set of salt   */
    char		*msgbuf_i;	/* Incomming Datagram Buffer     */
    char		*checkmsg;	/* Status of password check      */
    char		salt[3];	/* Encrypt Salt                  */

    char		*passCode;	/* valid secret code             */
    char		**servNames;	/* valid servers                 */
    char		**clntNames;	/* valid clients                 */

    FILE		*pf;		/* Config File Pointer           */

debug_table pwcheck_debug[] = {
        { "none",       DB_NONE,        "Debugging off" },
        { "verbose",    DB_VERBOSE,     "Verbose" },
        { "config",     DB_CONFIG,      "Configuration processing" },
        { "pwcheck",    DB_PWCHECK,     "Password checking" },
        { "detail",     DB_DETAIL,      "Detailed debugging" },
        { "all",        DB_ALL,         "All debugging" },
        { 0 },
};


   /*
    *  Only run if user is root
    */

    if( getuid() )
    {
	printf(" Sorry: Must run as root!.\n");
	return(-2);
    }

   /*
    *  Clean Environment
    */

    for(j=0;envp[j];j++)
    {
	if(strstr(envp[j],"PATH=") == envp[j])
	{
	    if(strlen(PATH) > strlen(envp[j])) envp[j] = malloc(strlen(PATH)+1);
	    strcpy(envp[j],PATH);
	    continue;
	}

	if(strstr(envp[j],"SHLIB_PATH=") == envp[j])
	{
	    if(strlen(SHLIB_PATH) > strlen(envp[j])) envp[j] = malloc(strlen(SHLIB_PATH)+1);
	    strcpy(envp[j],SHLIB_PATH);
	    continue;
	}

	if(strstr(envp[j],"LD_LIBRARY_PATH=") == envp[j])
	{
	    if(strlen(LD_LIBRARY_PATH) > strlen(envp[j])) envp[j] = malloc(strlen(LD_LIBRARY_PATH)+1);
	    strcpy(envp[j],LD_LIBRARY_PATH);
	    continue;
	}

	if( strstr(envp[j],"SYSTYPE=") == envp[j] || strstr(envp[j],"SYSREV=") == envp[j] ||
	    strstr(envp[j],"LANG="   ) == envp[j] || strstr(envp[j],"TERM="  ) == envp[j] ||
	    strstr(envp[j],"LOGNAME=") == envp[j] || strstr(envp[j],"SHELL=" ) == envp[j] ||
	    strstr(envp[j],"HOME="   ) == envp[j] || strstr(envp[j],"USER="  ) == envp[j] ||
	    strstr(envp[j],"DISPLAY=") == envp[j]
	  ) continue;

	strcpy(envp[j],"");
    }

   /*
    *  Check Options
    */

    debugLog = 0;

    for(j=1;argv[j];j++)
    {
	if(strcmp(argv[j],"--debug")==0)
	{
	    j++;
	    if(!argv[j]) continue;
	    debugLog = atoi(argv[j]);
	    /* Valid debug levels = 0-5 */
	    if( debugLog < 0 || debugLog > 5 ) debugLog = 0;
	    if( debugLog ) syslog(LOG_INFO,"Debug Level %d",debugLog);
	    continue;
	}
	printf("ERROR: Unknown options [ %s ]\n", argv[j] );
	printf("\n");
	printf(" USAGE: %s [ --debug level ]\n\n",argv[0]);
	printf("         level = 0-5\n\n");
	exit(-1);
    }
    if( debugLog ) syslog(LOG_INFO,"ARGC = %d",argc);

   /*
    *  Become a Daemon IF not in debug mode and run by root
    */

    if( debugLog == 0 && geteuid() == 0 )
    {
	for(j=3;j>=0;j--)	close(j);	/* Close stdin, stdout, errout */
	if (fork())		exit(0);	/* Parent exits                */
    }

   /*
    *  Get local Hostname
    */

    uname(&uName);

  /*
   *  Misc variable inits
   */

    SaltSet  = "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ./0123456789";
    msgbuf_i = (char *) malloc(DGRAMBUFSIZE+1);
    errcount = 0;

   /*
    *  Init PW Libraries
    */

    set_debug_tag("udpPWchk");
    set_die_callback((void(*)())(0));
    checkpassword_init();

   /*
    *  Read PW Configuration File
    */

    servNames = NULL;
    clntNames = NULL;
    passCode  = NULL;

    Authorized = udp_readConfigUpdate( &servNames, &clntNames, &passCode );

    if( Authorized == 0 )
    {
	syslog(LOG_ERR,"This is not the authorized server!  authorized[ %s ] me[ %s ]",
	    *servNames, uName.nodename );

	if( debugLog )
	  printf("This is not the authorized server!  authorized[ %s ] me[ %s ]\n",
	    *servNames, uName.nodename );

	if( debugLog == 0 ) exit(0);
    }

   /*
    *  Create "UDP" socket for incomming requests
    */

    protocol = getprotobyname("udp");
    pwSocket = socket(AF_INET, SOCK_DGRAM, protocol->p_proto);

    if(pwSocket < 0) syslog(LOG_ERR,"socket: Failed socket() call. [ %s ]",strerror(errno));
    if(pwSocket < 0) exit(pwSocket);

    if(debugLog >= DEBUG_LOG_LEVEL5)
	syslog(LOG_INFO,"Socket     File Descriptor : %4d",pwSocket);

   /*
    *  Set SO_REUSEADDR socket option
    */

    op_val = 0;			/* Clear before loading option into it       */
    len    = sizeof(op_val);	/* Set the size to hold this value           */

    if( debugLog >= DEBUG_LOG_LEVEL5 )
    status = getsockopt(	/* What is the current value of SO_REUSEADDR */
	pwSocket,		/* file descriptor for this socket           */
	SOL_SOCKET,		/* level of query                            */	
	SO_REUSEADDR,		/* option requested                          */
	(char *) &op_val,	/* store option here                         */
	&len			/* How much space to hold value              */
    );

    				/* syslog current Value of SO_REUSEADDR      */
    if( debugLog >= DEBUG_LOG_LEVEL5 )
    syslog(LOG_INFO,"Socket option SO_REUSEADDR : %4d",ntohs(op_val));

    status = setsockopt(	/* Turn on the SO_REUSEADDR option           */
	pwSocket,		/* our little socket                         */
	SOL_SOCKET,		/* level of option                           */
	SO_REUSEADDR,		/* option to be set/changed                  */
	(const char *) &on,	/* turn it on                                */
	sizeof(on)              /* its size                                  */
    );

    if(status<0)
    {
	syslog(LOG_ERR,"setsockopt: Failed setsockopt() call. [ %s ]",strerror(errno));
	exit(status);
    }

    				/* syslog current Value of SO_REUSEADDR      */
    op_val = 0;			/* Clear before loading option into it       */
    len    = sizeof(op_val);	/* Set the size to hold this value           */
    if( debugLog >= DEBUG_LOG_LEVEL5 )

    status = getsockopt(	/* What is the current value of SO_REUSEADDR */
	pwSocket,		/* file descriptor for this socket           */
	SOL_SOCKET,		/* level of query                            */	
	SO_REUSEADDR,		/* option requested                          */
	(char *) &op_val,	/* store option here                         */
	&len			/* The size here of the option here          */
    );

    if(debugLog >= DEBUG_LOG_LEVEL5)
    syslog(LOG_INFO,"Socket option SO_REUSEADDR : %4d",ntohs(op_val));

   /*
    *  Set UDP port number by name
    *  Set incomming address to ANY
    *  Bind port to socket
    */

    serviceport = getservbyname("pwmaint", "udp");
    if (serviceport == (struct servent *) NULL) {
	syslog(LOG_ERR,"passwd-strong: udp/pwmaint: unknown service");
	exit(1);
    }
    else
    {
	if(debugLog >= DEBUG_LOG_LEVEL5)
	syslog(LOG_INFO,"Located Service: %s [%s] on Port: %d",
	    serviceport->s_name, serviceport->s_proto, htons(serviceport->s_port));
    }
/* VICB */
	printf("Located Service: %s [%s] on Port: %d\n",
	    serviceport->s_name, serviceport->s_proto, htons(serviceport->s_port));
	printf("Located Service: %s [%s] on Port: %d\n",
	    serviceport->s_name, serviceport->s_proto, serviceport->s_port);

    bzero(&SockAddr, sizeof(struct sockaddr_in));
    SockAddr.sin_family		= AF_INET;
    SockAddr.sin_addr.s_addr	= htonl(INADDR_ANY);
    SockAddr.sin_port		= serviceport->s_port;

    status = bind(
	pwSocket,			/* our socket                        */
	(struct sockaddr *) &SockAddr,	/* port and address to bind          */
	sizeof(struct sockaddr_in)	/* data size                         */
    );

    if(status<0)
    {
	syslog(LOG_ERR,"bind: Failed bind() call. [ %s ]",strerror(errno));
	exit(status);
    }


   /*
    *  Init Children pids & signal on exit of child
    */

    for ( j=0 ; j<MAX_CHILDREN ; j++ ) children[j] = 0;
    Signal(SIGCHLD, sig_chld);

   /*
    *  Handle each request
    */

    for( ; ; ) {

	/*
	 * Wait for request
	 */

	len       = sizeof(struct sockaddr_in);
	dgram_len =
	recvfrom(
	    pwSocket,				/* socket descriptor         */
	    msgbuf_i,				/* buffer for incomming data */
	    DGRAMBUFSIZE,			/* size of buffer            */
	    0,					/* No special options        */
	    (struct sockaddr *) &SockAddr,	/* Source Address of data    */
	    &len				/* length of structure       */
	);

	Authorized = udp_readConfigUpdate( &servNames, &clntNames, &passCode );

	/*
	 * Count errors and Report
	 */

	if((int)dgram_len < 0)
	{
	    errcount++;
	    syslog(LOG_ERR,"Error during recvfrom(): %s",strerror(errno));
	    if( errcount >= 50 ) syslog(LOG_ERR,"Too many errors: [ %d ]",errcount);
	    if( errcount >= 50 ) errcount = 0;
	    continue;
	}

	if(debugLog >= DEBUG_LOG_LEVEL1)
	    syslog(LOG_INFO,"recvfrom() Bytes received %d",dgram_len);

	/*
	 * Host name of received datagram (CLIENT)
	 */

	host =
	gethostbyaddr(
	    (const char *)&SockAddr.sin_addr.s_addr,
	    sizeof(SockAddr.sin_addr.s_addr),
	    AF_INET
	);

	memcpy(&in.s_addr, host->h_addr_list[0], sizeof (in.s_addr));
	if(debugLog >= DEBUG_LOG_LEVEL3)
	{
	    syslog(LOG_INFO,"Client Host : %s", host->h_name );
	    syslog(LOG_INFO,"Client IP   : %s", inet_ntoa(in));
	    syslog(LOG_INFO,"Client Port : %d", ntohs(SockAddr.sin_port));
	}

       /*
	*  How many children do we have?
	*  only proceed if we have less than MAX_CHILDREN
	*/

	for ( ; ; )
	{
	  for ( j=0, k=0 ; j<MAX_CHILDREN ; j++ ) if( children[j] > 0 ) k++;
	  if( k < MAX_CHILDREN ) break; /* OK to create child */
	  if( debugLog >= DEBUG_LOG_LEVEL5 )
	      syslog(LOG_INFO,"Waiting on %d children(OK)",MAX_CHILDREN);

	  wait(0);
	}

	if(pid=fork()) {

	 /*
	  *  I am the "Parent Process"
	  *  store the childs pid into a list to allow tracking of MY children
	  */

	  if(debugLog >= DEBUG_LOG_LEVEL5)
	     syslog(LOG_INFO,"Parent Process of child: %d",pid);

	  for ( ; ; )
	  {
	     for ( j=0 ; j<MAX_CHILDREN ; j++ )
	     {
		if( children[j] == 0 )
		{
		   children[j] = pid;
		   break;
		}
	     }
	     if( children[j] == pid ) break;

	     /*
	      *  If the Parent process has done its
	      *  job RIGHT we should never get here
	      */

	     if( debugLog >= DEBUG_LOG_LEVEL5 )
	         syslog(LOG_INFO,"Waiting on %d children(XXX) This is not normal!",MAX_CHILDREN);

	     /* Sleep one second waiting for a child to awaken */
	     sleep(1);
	  }

	  /* How many children do we have ? */
	  for ( j=0, k=0 ; j<MAX_CHILDREN ; j++ ) if( children[j] > 0 ) k++;

	  /* List children pids */
	  if( debugLog >= DEBUG_LOG_LEVEL5 )
	     syslog(LOG_INFO,"Current Children: %d", k);

	  for ( j=0 ; j<MAX_CHILDREN ; j++ )
	     if( children[j] > 0 && debugLog >= DEBUG_LOG_LEVEL5 )
		syslog(LOG_INFO,"Child pid %7d",children[j]);
	}
	else
	{

	 /*
	  *  Child Process
	  */

	  cTime = time(0);
	  dgram =
	  (struct pw_dgram *) malloc(		/* a record that will do     */
	      (dgram_len > sizeof(struct pw_dgram)
		   ? dgram_len			/* bigger size or ...        */
		   : sizeof(struct pw_dgram))	/* correct size              */
	  );

	  memcpy(dgram,msgbuf_i,dgram_len);	/* copy data into our record */

	  if( dgram_len != sizeof(struct pw_dgram) )
	     syslog(LOG_INFO,
		"Incomming data not the size expected[ %d ] we got[ %d ]",
		sizeof(struct pw_dgram), dgram_len
	     );


	 /*
	  *  Un-Hide the data
	  */

	  HideStr(HCMD_UNHIDE,(char *)dgram,(dgram_len-(HIDE_SANITY)),passCode);

	 /*
	  *  Is this request from a Authorized Client?
	  */

	  Authorized = udp_authorizedClient(clntNames,host->h_name);

	  if( Authorized == 0 )
	  {
		dgram->pw_stat = htonl(PW_STAT_UNAUTHORIZED);
		strcpy(dgram->pw_msg,"UNAUTHORIZED");
	  }

	 /*
	  *  Does this Authorized Client know the correct passcode
	  */

	  if( Authorized )
	  {
		if( strcmp(dgram->pw_pc,passCode) )
		{
		    Authorized = 0;
		    dgram->pw_stat = htonl(PW_STAT_PASSCODE);
		    strcpy(dgram->pw_msg,"UNAUTHORIZED-BAD-PASSCODE");

		   /* LOG BAD PassCode */
		    if(debugLog>=DEBUG_LOG_LEVEL5)
			syslog(LOG_INFO,"Host Passcode?? [ %s ]", dgram->pw_pc );
		}
	  }


	  if( Authorized && debugLog >= DEBUG_LOG_LEVEL4)
	  syslog(LOG_INFO," recv [ %s ]",dgram->pw_msg);

	 /*
	  *  Is this a PING request
	  */

	  if( Authorized && ntohl(dgram->pw_type) == CMD_PING )
	  {
		strcat(dgram->pw_msg, " server:( ");
		strcat(dgram->pw_msg, uName.nodename);
		strcat(dgram->pw_msg, " )");

		if(debugLog >= DEBUG_LOG_LEVEL5)
		    syslog(LOG_INFO," client-host [ %-8s ] try [ %d ]",
			host->h_name,ntohl(dgram->pw_request));

		if(debugLog >= DEBUG_LOG_LEVEL2)
		    printf(         " client-host [ %-8s ] try [ %d ]\n",
			host->h_name,ntohl(dgram->pw_request));

		dgram->pw_stat = htonl(PW_STAT_READY);
	  }

	 /*
	  *  User Unfo Valid?
	  */

	  uValid = 1;
	  if( Authorized && ( ntohl(dgram->pw_type) != CMD_PING ))
	  {
		char **gcos;

		if((pwinfo = getpwnam(dgram->pw_uname)) == NULL)
		{
			uValid = 0;
			dgram->pw_stat = htonl(PW_STAT_FAIL);
			strcpy(dgram->pw_msg, "Could not get passwd data for user.");
		}

	  	if( uValid )
		if( pwinfo->pw_uid != ntohl(dgram->pw_uid))
		{
			uValid = 0;
			dgram->pw_stat = htonl(PW_STAT_FAIL);
			strcpy(dgram->pw_msg, "Users uid does not match uid given.");
			syslog(LOG_INFO,"UID[%d] User[%s] CMD[%d]",dgram->pw_uid,dgram->pw_uname,dgram->pw_type);
		}

		if(debugLog >= DEBUG_LOG_LEVEL2 && uValid )
			printf(" UNAME [ %8s ] GCOS [ %s ]\n", pwinfo->pw_name, pwinfo->pw_gecos );
	  }

	 /*
	  *  Check password history and strength
	  */

	  if( uValid )
	  if( Authorized && ntohl(dgram->pw_type) == CMD_PWCHK )
	  {
#ifdef TI_ITSS_PW_CHECK
	     /*
	      *  0 = ITSS Password match
	      * -1 = failed
	      *  1 = No service
	      */
	     if( itssPWDchk( "sle03.itg.ti.com", axid, dgram->pw_pwd ))
	     {
#endif
		/*
		 * Read Config file (right out of npasswd, checkpassword.c
		 */

		if(debugLog >= DEBUG_LOG_LEVEL5) set_debug("all", pwcheck_debug);
		if ( pf = fopen(CONFIG_FILE, "r"))
		{
			char	ibuf[BUFSIZ];
			int	cfline;

			if(debugLog >= DEBUG_LOG_LEVEL5)
				syslog(LOG_INFO,"pwstrongd: open %s",CONFIG_FILE);

			while (fgets(ibuf, BUFSIZ, pf))
			{
				char	*error;

				chop_nl(ibuf); cfline++;

				if (*ibuf == 0 || *ibuf == '#') continue;
				if (instringcase(ibuf, "passwd.") == 0) continue;

				if(debugLog >= DEBUG_LOG_LEVEL5)
				syslog(LOG_INFO,"pwstrongd: config: %s",ibuf);

				if (error = checkpassword_configure(ibuf, 0))
					syslog(LOG_INFO,"Config file error \"%s\"; line %d; %s\n",
						CONFIG_FILE, cfline, error);
			}
			(void) fclose(pf);

                /* checkpassword_probe("checkpassword."); */
		/* checkpassword_verify(); */

		}

		/*
		 * Check the password
		 */

		if( checkmsg = checkpassword(dgram->pw_pwd, pwinfo))
		{
			uValid = 0;
			dgram->pw_stat = PW_STAT_FAIL;
			strncpy(dgram->pw_msg, checkmsg, MAXMSGSIZE);
			dgram->pw_msg[MAXMSGSIZE] = '\0';
		}
		else
		{
			dgram->pw_stat = htonl(PW_STAT_PASS);
			if(checkmsg) strcpy(dgram->pw_msg, checkmsg);
			strcpy(dgram->pw_msg, "ok");
		}
#ifdef TI_ITSS_PW_CHECK
	     }
	     else
	     {
		if(debugLog >= DEBUG_LOG_LEVEL5)
			syslog(LOG_INFO,"ITSS Password Check for [ %8s ] OK",axid);
	     }
#endif
	  }

	 /*
	  *  Get  password history
	  */

	  if( uValid )
	  if( Authorized && ntohl(dgram->pw_type) == CMD_PWGETHIST )
	  {
	     char  *histstr;

	     /* pwck_history_probe("UDPSRV: "); */

	     histstr = (char *)pwck_get_history(dgram->pw_uname);

	     strcpy(dgram->pw_msg, "");
	     if(histstr) strncpy(dgram->pw_msg, histstr, MAXMSGSIZE);
	     dgram->pw_msg[MAXMSGSIZE] = '\0';
	  }

	 /*
	  *  Save password into history DB
	  */

	  if( uValid )
	  if( Authorized && ntohl(dgram->pw_type) == CMD_PWPUTHIST )
	  {
	     char *msg;

	     srand(time(0));
	     salt[0] = SaltSet[rand()%64];
	     salt[1] = SaltSet[rand()%64]; salt[2] = '\0';

	     password_history_update(
		dgram->pw_uname,
		(char *)crypt((char *)dgram->pw_pwd,
		(char *)salt),
		0
	     );

	     strcpy(dgram->pw_msg, "ok" );
	     dgram->pw_stat = htonl(PW_STAT_OK);
	  }

	 /*
	  *  Change Debug Level (Broken - changes child not parent process)
	  */

	  /* Does not work.  Changes Child not parent  (Really do not need this feature)
	   * A fix may be to do this test before the fork (Data is hidden at that time?)
	   *
	   * I could use the child to signal the parent to change its debug level.
	   *
	   * Threads could also anster this issue.
	   *

	  if( Authorized && (( dgram->pw_type >= CMD_DEBUG_ON1 )&&( dgram->pw_type <= CMD_DEBUG_ON5 )))
		debugLog = ( dgram->pw_type - CMD_DEBUG_OFF );

	  if( Authorized && dgram->pw_type == CMD_DEBUG_OFF )
		debugLog = 0;

	  if( Authorized && (( dgram->pw_type >= CMD_DEBUG_OFF )&&( dgram->pw_type <= CMD_DEBUG_ON5 )))
		syslog(LOG_INFO," debug level now [ %d ]\n",debugLog);
	  */

	  if( Authorized && ( debugLog >= DEBUG_LOG_LEVEL2 ))
	    syslog(LOG_INFO," send [ %s ]",dgram->pw_msg);


	 /*
	  *  Hide data before returning it
	  */

	  HideStr(HCMD_HIDE,(char *)dgram,(dgram_len-(HIDE_SANITY)),passCode);

	 /*
	  *  Send reply back to CLIENT
	  */

	  len    = sizeof(struct sockaddr);
	  status =
	  sendto(
		pwSocket,			/* Socket descriptor         */
		(char *) dgram,			/* out going data            */
		dgram_len,			/* how much  data            */
		0,				/* No special options        */
		(struct sockaddr *) &SockAddr,	/* Source Address of data    */
		len				/* length of structure       */
	  );

	  if(debugLog >= DEBUG_LOG_LEVEL1)
	      syslog(LOG_INFO,"  sendto() Bytes sent     %d",status);

	  if(debugLog >= DEBUG_LOG_LEVEL3)
	      syslog(LOG_INFO,"Child process: %d of parent: %d",getpid(),getppid());

	  free(dgram);

	  /*
	   *  Work around to fix race condition
	   *  when child exits before parent can record it.
	   *  This makes sure the parent is ready to handle
	   *  the signal when the child exits
	   */

	  if((time(0) - cTime) < 2) sleep(1);

	  return(0);
	}

    }

    free(msgbuf_i);
    close(pwSocket);

    return(0);
}

static void
sig_chld(int signo)
{
	pid_t	pid;
	int	stat, j;

	if(debugLog >= DEBUG_LOG_LEVEL5)
	syslog(LOG_INFO,"Signal [ %d/%d ]", signo, SIGCHLD);

	if( signo == SIGCHLD )
	while(( pid = waitpid(-1,&stat,WNOHANG)) > 0)
	{
	  if(debugLog >= DEBUG_LOG_LEVEL3)
	  syslog(LOG_INFO,"child %d terminated with status %d",pid,stat);

	  for ( j=0 ; j<MAX_CHILDREN ; j++ )
		if( children[j] == pid ) break;
	  if(debugLog >= DEBUG_LOG_LEVEL5)
	  if( children[j] != pid ) syslog(LOG_ERR,"Warning: child pid %d not found in list",pid);
	  /* if( children[j] != pid )      printf("Warning: child pid %d not found in list.\n",pid); */
	  if( children[j] == pid ) children[j] = 0;
	}
}

Sigfunc *
Signal(int signo, Sigfunc *func)
{
	struct sigaction act, oact;

	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags   = 0;

#ifdef SA_INTERRUPT
	if( signo == SIGALRM ) {
		act.sa_flags |= SA_INTERRUPT;	/* SunOS 4.x */
	}
#endif

#ifdef SA_RESTART
	if( signo == SIGCHLD ) {
		act.sa_flags |= SA_RESTART;	/* SRV4, 4.4BSD */
	}
#endif

	if( sigaction(signo, &act, &oact) < 0) return(SIG_ERR);
	return(oact.sa_handler);
}

/* END */
