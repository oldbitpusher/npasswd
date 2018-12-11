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
  *  Written by: Victor Burns
  *        Date: 1999-2000
  *
  *  UDP Based Client to request Password Strength Check
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
#include <sys/socket.h>
#include <sys/utsname.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <time.h>
#include <sys/byteorder.h>


#include <libhide.h>
#include <libstrongconfig.h>
#include <udpchk.h>
#include "udp-client.h"

#define UDPDATA		"The quick brown fox jumped over the lazy dogs back! "
#define UDPTRYS		3
#define UDPDELAY	20

static void		udp_sig_alrm(int signo);
static int		udp_socket_fd;			/* Socket File Descriptor           */
       int		errno;


static char		udp_tbuf[256];

char * getstr(p,l)
char *p;
int  l;
{
	bcopy(p,udp_tbuf,l);
	udp_tbuf[l] = '\0';
	return(udp_tbuf);
}

int
udp_client( cmd, useruname, password, message_text )
    int			  cmd;
    char		* useruname;
    char		* password;
    char		* message_text;
{
    int			n;		/* misc int                              */
    int			trys;		/* number of request trys                */
    int			status;		/* function return status                */
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
    char		**server;	/* Server Host name                      */
    char		**servNames;	/* Server Name List                      */
    char		**clntNames;	/* Client Name List                      */


   /*
    *  Read PW Configuration File
    */

    udp_readConfig( &servNames, &clntNames, &passCode );
    server = servNames;

    if( *server == NULL )
    {
	syslog(LOG_ERR,"STRONG: Server Name is null and undefined. [ config file problem? ]");
	strcpy(message_text," STRONG: Server Name is null and undefined. [ config file problem? ]");
	return(PW_STAT_NOSERVICE);
    }

   /*
    * Does the client really care? (Not at this time)
    *

    if( *clntNames == NULL )
    {
	syslog(LOG_ERR,"STRONG: Client List is null and undefined. [ config file problem? ]");
	strcpy(message_text," STRONG: Client List is null and undefined. [ config file problem? ]");
	return(PW_STAT_NOSERVICE);
    }

    *
    */

    if( strlen(passCode) <=1 )
    {
	syslog(LOG_ERR,"STRONG: Passcode is null and undefined. [ config file problem? ]");
	strcpy(message_text," STRONG: Passcode is null and undefined. [ config file problem? ]");
	return(PW_STAT_NOSERVICE);
    }

   /*
    *  Our hostname
    */

    uname(&uName);

   /*
    *  Create a socket for datagram transfer
    */

    udp_socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(udp_socket_fd < 0)
    {
	syslog(LOG_ERR,"Can not open socket");
	strcpy(message_text," Strong: Service not available [socket open]");
	return(PW_STAT_NOSERVICE);
    }

   /*
    *  What is the name and port for this service
    */

    sp = getservbyname("pwmaint", "udp");
    if(sp == (struct servent *) NULL) {
	syslog(LOG_ERR,"udp/pwmaint: unknown service");
	strcpy(message_text," Strong: Service Not Available. [udp/pwmaint: unknown service]");
	return(PW_STAT_NOSERVICE);
    }

   /*
    * Test Messages
    syslog(LOG_INFO,"Located Service: %s [%s] on Port: %d",  sp->s_name,sp->s_proto,ntohs(sp->s_port));
    printf(         "Located Service: %s [%s] on Port: %d\n",sp->s_name,sp->s_proto,ntohs(sp->s_port));
    */

   /*
    *  Bind the local address(s)  (Any interface with random port)
    */

    bzero(&clntaddr, sizeof(clntaddr));
    clntaddr.sin_addr.s_addr	= htonl(INADDR_ANY);
    clntaddr.sin_family		= AF_INET;
    clntaddr.sin_port		= htons(0);

    status = bind(udp_socket_fd, (struct sockaddr *) &clntaddr, sizeof(clntaddr));
    if(status<0)
    {
	syslog(LOG_ERR,"bind: Failed bind() call. [ %d ]",status);
	strcpy(message_text," Strong: Service Not Available. [bind()]");
	return(PW_STAT_NOSERVICE);
    }

   /*
    *   What port did we get?
    */

    n      = sizeof(clntaddr);
    status = getsockname(udp_socket_fd, (struct sockaddr *) &clntaddr, (int *)&n );

   /*
    * Test Messages
    syslog(LOG_INFO,"local port number [ %d ]",ntohs(clntaddr.sin_port));
    printf("local port number [ %d ]\n",ntohs(clntaddr.sin_port));
    */

   /*
    *  UDP Connect to server
    */

    while ( 1 )
    {
	if ( *server == NULL )
	{
		strcpy(message_text," Strong: Service not available [no known server OR all servers unavailable]");
		return(PW_STAT_NOSERVICE);
	}

	syslog(LOG_INFO,"(strong)Trying Server: %s", *server);
	hp = gethostbyname(*server);
	if (hp == (struct hostent *) 0)
	{
		syslog(LOG_ERR,"unknown server: %s", *server );
		server++;
		continue;
	}

	bzero(&servaddr, sizeof(servaddr));
	memcpy((char *) &servaddr.sin_addr, (char *) hp->h_addr, hp->h_length);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = sp->s_port;
	status = connect(udp_socket_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	if( status )
	{
		syslog(LOG_ERR,"Connect Failed: %s",strerror(errno));
		server++;
		continue;
	}
	break;
    }

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

    for(trys=UDPTRYS;trys>0;trys--)
    {

       /*
	*  Send Request Message
	*/

	sDgram->pw_type    = htonl(cmd);

	sDgram->pw_request = htonl(abs((trys-UDPTRYS)-1));
	sDgram->pw_stat    = htonl(PW_STAT_OK);
	sDgram->pw_time    = htonl(time(NULL));

	sDgram->pw_uname[8] = '\0';
	strncpy(sDgram->pw_uname, useruname, 8);
	strcpy(sDgram->pw_pc,passCode);
	strcpy(sDgram->pw_pwd,password);

	if(getpwnam(useruname))
	{
	    sDgram->pw_uid   = htonl((getpwnam(useruname))->pw_uid);
	}
	else
	{
	    syslog(LOG_ERR," ERROR: Unknown uname [ %s ]\n", useruname );
	    strcpy(message_text," Strong: Service failure       [unknown user]");
	    status = PW_STAT_NOSERVICE;
	    break;
	}

	strcpy(sDgram->pw_msg,UDPDATA);
	strcat(sDgram->pw_msg," client:( ");
	strcat(sDgram->pw_msg,uName.nodename);
	strcat(sDgram->pw_msg," )");

	HideStr(HCMD_HIDE,(char *)sDgram,(sizeof( struct pw_dgram )-(HIDE_SANITY)),passCode);

	status = send(udp_socket_fd, (char *) sDgram, sizeof( struct pw_dgram ), 0);
	if(status == -1) {
	   syslog(LOG_ERR,"sending datagram message [ %s ]",strerror(errno));
	   if(errno == (int)ECONNREFUSED) {
		alarm(0);
		signal(SIGALRM, NULL);
		close(udp_socket_fd);
		syslog(LOG_ERR,"Is the server currently running on host [ %s ]", *server);
		strcpy(message_text," Strong: Service not available [send()]");
		status = PW_STAT_NOSERVICE;
		break;
	   }
	}

	syslog(LOG_INFO,"Message  Sent to: %s %d bytes.\n", *server, sizeof( struct pw_dgram ));

       /*
	*  Set Timmer Alarm
	*/

	signal(SIGALRM, udp_sig_alrm);
	syslog(LOG_INFO,"Set timer for [ %d ] seconds\n",UDPDELAY*abs((trys-UDPTRYS)-1));
	alarm(UDPDELAY*abs((trys-UDPTRYS)-1));

       /*
	*  Receive Response
	*/

	bzero(rDgram,sizeof(struct pw_dgram));
	status = recv(udp_socket_fd,(char *) rDgram, sizeof(struct pw_dgram), MSG_WAITALL);
	if(status == -1 )
	{
	    syslog(LOG_ERR,"receiving datagram message [ %s ]",strerror(errno));
	    if(errno == (int)ECONNREFUSED) {
		alarm(0);
		signal(SIGALRM, NULL);
		close(udp_socket_fd);
		syslog(LOG_ERR,"Is the server currently running on host [ %s ]", *server);
		strcpy(message_text," Strong: Service not available [recv()]");
		status = PW_STAT_NOSERVICE;
		break;
	    }
	}
	else
	{
	    syslog(LOG_INFO,"Message Received: %s %d bytes.", *server, status);

	    HideStr(HCMD_UNHIDE,(char *)rDgram,(sizeof( struct pw_dgram )-(HIDE_SANITY)),passCode);

	    status = ntohl(rDgram->pw_stat);
	    strncpy(message_text,rDgram->pw_msg,MAXMSGSIZE);
	    message_text[MAXMSGSIZE] = '\0';

	    break;
	}

    } /* for (trys) */


    alarm(0);
    close(udp_socket_fd);

    free(sDgram);
    free(rDgram);

    return(status);
}

static void
udp_sig_alrm(int signo)
{
	syslog(LOG_INFO,"Timeout on signal [ %d ] Request resend in progress.", signo);
	signal(signo, udp_sig_alrm);
}

/* END */
