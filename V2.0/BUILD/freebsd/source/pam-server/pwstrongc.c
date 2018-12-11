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
  * UDP Based Client to request Password Strength Check
  *   Just another server test program
  *
  *   Author: Victor Burns (Texas Instruments)
  *
  */

#include <pwd.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <errno.h>
#include <syslog.h>
#include <string.h>
#include <strings.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <time.h>

#include <libhide.h>
#include <udpchk.h>
#include <libstrongconfig.h>

#define PATH            "PATH=/usr/lib/passwd/bin:/usr/bin:/usr/ucb"
#define SHLIB_PATH      "SHLIB_PATH=/usr/lib:/usr/dt/lib:/usr/lib/passwd/lib"
#define LD_LIBRARY_PATH "LD_LIBRARY_PATH=/usr/lib:/usr/dt/lib:/usr/openwin/lib:/usr/lib/passwd/lib"

#define DATA "The quick brown fox jumped over the lazy dogs back! "
#define TRYS  3
#define DELAY 20

static void sig_alrm(int signo);
static int		socket_fd;	/* Socket File Descriptor                */
       int		errno;
char   tbuf[256];

char * getstr(p,l)
char *p;
int  l;
{
	bcopy(p,tbuf,l);
	tbuf[l] = '\0';
	return(tbuf);
}

int
main( int argc, char *argv[], char *envp[] )
{
    int			n, j;		/* misc int                              */
    int			trys;		/* number of request trys                */
    int			status;		/* function return status                */
    int			debug_lev = -1;	/* Debug Change request and level        */
    int			ping  = 0;	/* Send Ping Request                     */
    int			putpw = 0;	/* Put password in history               */
    int			getpw = 0;	/* Get password    history               */
    int			sDgramSize;	/* Send    Datagram Size                 */
    int			rDgramSize;	/* Recieve Datagrem Size                 */

    struct pw_dgram	*sDgram;	/* Send    Datagram                      */
    struct pw_dgram	*rDgram;	/* Receive Datagram                      */
    struct sockaddr_in	clntaddr;	/* Address of Client                     */
    struct sockaddr_in	servaddr;	/* Address of Server                     */
    struct hostent	*hp;
    struct servent	*sp;
    struct utsname	uName;          /* Unix uname info                       */

    char		*passCode;	/* Secret Passcode                       */
    char		*passwd;	/* Password                              */
    char		*server;	/* Server Host name                      */
    char		useruname[9];	/* Users Uname                           */
    char		**servNames;	/* Server Name List                      */
    char		**clntNames;	/* Client Name List                      */


   /*
    *  Has Possible server host name been given?
    */

    if(argc < 2) {
	printf("usage: %s [ --server <hostname> ] [ --ping | --put | --get ] [ --uname name ] [ --password password ]\n",*argv);
	exit(1);
    }

   /*
    *  Read PW Configuration File
    */

    udp_readConfig( &servNames, &clntNames, &passCode );
    server = *servNames;

    passwd = (char *) malloc(9);
    strcpy(passwd,"Password");

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
    *  Options
    */

    useruname[0] = '\0';

    for(n=1;argv[n];n++)
    {
	if(strcmp(argv[n],"--ping")==0)
	{
		ping = 1; continue;
	}

	if(strcmp(argv[n],"--put")==0)
	{
		putpw = 1; continue;
	}

	if(strcmp(argv[n],"--get")==0)
	{
		getpw = 1; continue;
	}

	if(strcmp(argv[n],"--server")==0)
	{
		n++;
		if(argv[n]==0) continue;
		server = (char *) malloc(strlen(argv[n])+1);
		strcpy(server,argv[n]);
		printf(" Server set to : %s\n", server );
		continue;
	}

	if(strcmp(argv[n],"--password")==0)
	{
		n++;
		if(argv[n]==0) continue;
		strncpy(passwd,argv[n],8);
		continue;
	}

	if(strcmp(argv[n],"--uname")==0)
	{
		n++;
		if(argv[n]==0) continue;
		strncpy(useruname,argv[n],8);
		continue;
	}

	if(strcmp(argv[n],"--debug")==0)
	{
		n++;
		if(argv[n]==0) continue;
		debug_lev = atoi(argv[n]);
		debug_lev += CMD_DEBUG_OFF;
		if( debug_lev < CMD_DEBUG_OFF || debug_lev > CMD_DEBUG_ON5 ) debug_lev = -1;
		if( debug_lev < 0 ) printf("Warning: --debug 0-5\n");
		continue;
	}

	printf(" Warning: Unknown option [ %s ]\n",argv[n]);
    }

    if( useruname[0] == 0 )
    {
	strcpy(useruname,(getpwuid(getuid()))->pw_name);
	printf(" uid[ %d ] = uname[ %s ]\n",getuid(), useruname);
    }

   /*
    *  Our hostname
    */

    uname(&uName);

   /*
    *  Create a socket for datagram transfer
    */

    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(socket_fd < 0) { perror("socket() error"); exit(errno); }

   /*
    *  What is the name and port for this service
    */

    sp = getservbyname("pwmaint", "udp");
    if (sp == (struct servent *) NULL) {
	printf("udp/pwmaint: unknown service\n");
	exit(-1);
    }

    printf("Located Service: %s [%s] on Port: %d\n",sp->s_name,sp->s_proto,ntohs(sp->s_port));

   /*
    *  Bind the local address(s)  (Any interface with random port)
    */

    bzero(&clntaddr, sizeof(clntaddr));
    clntaddr.sin_addr.s_addr	= htonl(INADDR_ANY);
    clntaddr.sin_family		= AF_INET;
    clntaddr.sin_port		= htons(0);

    status = bind(socket_fd, (struct sockaddr *) &clntaddr, sizeof(clntaddr));
    if(status<0) printf("bind: Failed bind() call. [ %d ]\n",status);
    if(status<0) exit(status);

   /*
    *   What port did we get?
    */

    n      = sizeof(clntaddr);
    status = getsockname(socket_fd, (struct sockaddr *) &clntaddr, &n );
    printf("local port number [ %d ]\n",ntohs(clntaddr.sin_port));

   /*
    *  UDP Connect to server
    */

    hp = gethostbyname(server);
    if (hp == (struct hostent *) 0) {
	printf("unknown host: %s\n", server );
	exit(-2);
    }

    bzero(&servaddr, sizeof(servaddr));
    memcpy((char *) &servaddr.sin_addr, (char *) hp->h_addr, hp->h_length);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = sp->s_port;
    status = connect(socket_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    if(status) printf("Connect Failed: %s\n",strerror(errno));

   /*
    *  Allocate Send Recieve buffers
    */

    sDgramSize = sizeof(struct pw_dgram);
    rDgramSize = sizeof(struct pw_dgram);

    sDgram = (struct pw_dgram *) malloc(sDgramSize);
    rDgram = (struct pw_dgram *) malloc(rDgramSize);

   /*
    *  Send/Try "TRYS" times
    */

    for(trys=TRYS;trys>0;trys--)
    {

       /*
	*  Send Request Message
	*/

	sDgram->pw_type    = htonl(CMD_PWCHK);

	if(ping)
	sDgram->pw_type    = htonl(CMD_PING);

	if(debug_lev >= CMD_DEBUG_OFF)
	sDgram->pw_type    = htonl(debug_lev);

	if(putpw)
	sDgram->pw_type    = htonl(CMD_PWPUTHIST);

	if(getpw)
	sDgram->pw_type    = htonl(CMD_PWGETHIST);

	sDgram->pw_request = htonl(abs((trys-TRYS)-1));
	sDgram->pw_stat    = htonl(PW_STAT_OK);
	sDgram->pw_time    = htonl(time(NULL));

	strcpy(sDgram->pw_pc,passCode);
	strncpy(sDgram->pw_uname, useruname, 8);
	strcpy(sDgram->pw_pwd,passwd);
	if(getpwnam(useruname))
	{
	  sDgram->pw_uid   = htonl((getpwnam(useruname))->pw_uid);
	}
	else
	{
	  printf(" ERROR: Unknown uname [ %s ]\n", useruname );
	  exit(-1);
	}

	strcpy(sDgram->pw_msg,DATA);
	strcat(sDgram->pw_msg," client:( ");
	strcat(sDgram->pw_msg,uName.nodename);
	strcat(sDgram->pw_msg," )");

	HideStr(HCMD_HIDE,(char *)sDgram,(sizeof( struct pw_dgram )-(HIDE_SANITY)),passCode);

	status = send(socket_fd, (char *) sDgram, sizeof( struct pw_dgram ), 0);
	if(status == -1) {
	   printf("sending datagram message [ %s ]\n",strerror(errno));
	   if(errno == (int)ECONNREFUSED) {
		alarm(0);
		signal(SIGALRM, NULL);
		close(socket_fd);
		exit(errno);
	   }
	} else
	   printf("Message  Sent to: %s %d bytes.\n", server, sizeof( struct pw_dgram ));

       /*
	*  Set Timmer Alarm
	*/

	signal(SIGALRM, sig_alrm);
	printf("Set timer for [ %d ] seconds\n",DELAY*abs((trys-TRYS)-1));
	alarm(DELAY*abs((trys-TRYS)-1));

       /*
	*  Receive Response
	*/

	bzero(rDgram,sizeof(struct pw_dgram));
	status = recv(socket_fd,(char *) rDgram, sizeof(struct pw_dgram), MSG_WAITALL);
	if(status == -1 )
	{
	   if(errno == (int)ECONNREFUSED) {
		printf("receiving datagram message [ %s ]\n",strerror(errno));
		alarm(0);
		signal(SIGALRM, NULL);
		close(socket_fd);
		printf("Is the server currently running on host [ %s ]\n", server);
		exit(errno);
	   }
	   printf("receiving datagram message [ %s ]\n",strerror(errno));
	}
	else
	{
	   printf("Message Received: %s %d bytes.\n", server, status);

	   HideStr(HCMD_UNHIDE,(char *)rDgram,(sizeof( struct pw_dgram )-(HIDE_SANITY)),passCode);

	   printf("   Type: %d - ", ntohl(rDgram->pw_type));

	   if(ntohl(rDgram->pw_type) == CMD_PING)
	   printf("Ping\n");

	   if(ntohl(rDgram->pw_type) == CMD_PWCHK)
	   printf("Password Check\n");

	   if(ntohl(rDgram->pw_type) == CMD_PWGETHIST)
	   printf("History Get\n");

	   if(ntohl(rDgram->pw_type) == CMD_PWPUTHIST)
	   printf("History Put\n");

	   if(ntohl(rDgram->pw_type) >= CMD_DEBUG_OFF && ntohl(rDgram->pw_type) <= CMD_DEBUG_ON5)
	   printf("Debug Level\n");

	   printf("    Try: %d\n", ntohl(rDgram->pw_request));
	   printf("   Stat: %d\n", ntohl(rDgram->pw_stat));
	   printf("   Time: %d seconds\n", (time(NULL) - ntohl(rDgram->pw_time)));
	   printf("  Uname: %s\n", getstr(rDgram->pw_uname,8));
	   printf(" Passwd: %s\n", getstr(rDgram->pw_pwd,13));
	   printf(" [ %s ]\n\n",rDgram->pw_msg);

	   break;
	}

    } /* for (trys) */

    alarm(0);
    close(socket_fd);
    free(sDgram);
    free(rDgram);
    return(0);
}

static void
sig_alrm(int signo)
{
	printf("Timeout on signal [ %d ] Request resend in progress.\n", signo);
	signal(signo, sig_alrm);
}

/* END */
