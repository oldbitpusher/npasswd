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
  *  (Server testing tool)
  *
  */

#include <pwd.h>
#include <shadow.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/utsname.h>

#ifndef HPUX
extern  uint32_t htonl(uint32_t);
extern  uint16_t htons(uint16_t);
extern  uint32_t ntohl(uint32_t);
extern  uint16_t ntohs(uint16_t);
#endif

#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>

#include <udp-client.h>
#include <udpchk.h>

#define PATH            "PATH=/usr/lib/passwd/bin:/usr/bin:/usr/ucb"
#define SHLIB_PATH      "SHLIB_PATH=/usr/lib:/usr/dt/lib:/usr/lib/passwd/lib"
#define LD_LIBRARY_PATH "LD_LIBRARY_PATH=/usr/lib:/usr/dt/lib:/usr/openwin/lib:/usr/lib/passwd/lib"


int
main( int argc, char *argv[], char *envp[] )
{
    int			cmd;		/* Command to process                    */
    int			n, j;		/* misc int                              */
    int			status;		/* function return status                */
    int			debug_lev = -1;	/* Debug Change request and level        */

    char		*password;	/* Password                              */
    char		useruname[9];	/* Users Uname                           */

    char		message_text[MAXMSGSIZE+1];


   /*
    *  Read ARGS
    */

    if(argc < 2) {
	printf("usage: %s [ --debug 1-5 | --ping | --put | --get ] [ --uname name ] [ --password password ]\n",*argv);
	exit(1);
    }

    cmd = CMD_PWCHK;
    password = (char *) malloc(9);
    strcpy(password,"Password");

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
    useruname[8] = '\0';

    for(n=1;argv[n];n++)
    {
	if(strcmp(argv[n],"--ping")==0)
	{
		cmd = CMD_PING;		continue;
	}

	if(strcmp(argv[n],"--put")==0)
	{
		cmd = CMD_PWPUTHIST;	continue;
	}

	if(strcmp(argv[n],"--get")==0)
	{
		cmd = CMD_PWGETHIST;	continue;
	}

	if(strcmp(argv[n],"--password")==0)
	{
		n++;
		if(argv[n]==0) continue;
		strncpy(password,argv[n],8);
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
		if( debug_lev == -1 ) printf("Warning: --debug 0-5\n");
		continue;
	}

	printf(" Warning: Unknown option [ %s ]\n",argv[n]);
    }

    if( useruname[0] == 0 )
    {
	strncpy(useruname,(getpwuid(getuid()))->pw_name,8);
    }

    printf("\n");
    printf(" UDP Clint: (Test Program)\n");
    printf("\n");
    printf(" User Information\n");
    if( getspnam(useruname) == NULL )
    {
	printf(" (getspnam)unknown        uname[ %s ]\n", useruname );
    }
    else
    {
	printf(" (getspnam)uid[ %5d ] = uname[ %s ] %s \n",
		(getpwnam(useruname))->pw_uid,
		 useruname,
		(getspnam(useruname))->sp_pwdp);
    }
    if( getpwnam(useruname) == NULL )
    {
	printf(" (getpwnam)unknown        uname[ %s ]\n", useruname );
    }
    else
    {
	printf(" (getpwnam)uid[ %5d ] = uname[ %s ] %s \n",
		(getpwnam(useruname))->pw_uid,
		 useruname,
		(getpwnam(useruname))->pw_passwd);
    }
    printf("\n");

   /*
    *  Send Command to server
    */

    status = 0;
    *message_text = '\0';

    status = udp_client( cmd, useruname, password, message_text );

    switch (status)
    {
	case PW_STAT_NOSERVICE :
		printf(" status = PW_STAT_NOSERVICE     [ %d ]\n", status );
		break;

	case PW_STAT_PASSCODE :
		printf(" status = PW_STAT_PASSCODE      [ %d ]\n", status );
		break;

	case PW_STAT_UNAUTHORIZED :
		printf(" status = PW_STAT_UNAUTHORIZED  [ %d ]\n", status );
		break;

	case PW_STAT_FAIL :
		printf(" status = PW_STAT_FAIL          [ %d ]\n", status );
		break;

	case PW_STAT_PASS :
		printf(" status = PW_STAT_PASS          [ %d ]\n", status );
		break;

	case PW_STAT_OK	 :
		printf(" status = PW_STAT_OK            [ %d ]\n", status );
		break;

	case PW_STAT_READY :
		printf(" status = PW_STAT_READY         [ %d ]\n", status );
		break;
	
	default :
		printf(" status = PW_UNKNOWN            [ %d ]\n", status );
    }

    printf("\n [ (Returned Message) ]\n%s\n\n", strlen(message_text) ? message_text : " 'No Message'" );

    return(status);
}

/* END */
