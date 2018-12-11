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
  *  Query Main Frame server. Verify password.
  *
  *  Author: Victor Burns
  *    Date: 12-Dec-2000
  */

#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int errno;

#ifdef TEST_ims_pw_chk
int main(argc,argv)
	int	argc;
	char	**argv;
{
	int	status;

	if(argc < 3) {
		printf("USAGE: $ %s ITSSACCT ITSSPW\n", argv[0] );
		exit(0);
	}

	switch (status = itssPWDchk("sle03.itg.ti.com",argv[1],argv[2]))
	{
	
	case  0 : {
			printf(" Account verified!\n");
			break;
		}

	case -1 : {
			printf(" Account failed!\n");
			break;
		}

	default : {
			printf(" Service Failed.\n");
		}
	}

	return(status);
}
#endif

#define R_MXBUF_SZ	(1024*4)

int itssPWDchk ( server, user_name, password )
	char	*server;
	char	*user_name;
	char	*password;
{
	int		st, x;
	int		PIPE[2];
	pid_t		pid;
	char		messages[5][40] = { "open ", "user ", "status\n", "bye\n", "\0" };
	char		response[40];

	if(st = pipe(PIPE)) return(st);

	if(pid=fork())
	{
	       /*
		* Parent Reads from child
		*/

		char big[R_MXBUF_SZ] = "";

		close(PIPE[0]);

		strcat(messages[0], server);
		strcat(messages[0], "\n");

		strcat(messages[1], user_name);
		strcat(messages[1], " ");
		strcat(messages[1], password);
		strcat(messages[1], "\n");

		for( x=0 ; *(messages[x]); x++ )
		{
			write(PIPE[1], messages[x], strlen(messages[x]));
		}

		while(x=read(PIPE[1], response, 39))
		{
			response[x] = '\0';
			if((strlen(big)+strlen(response)) < R_MXBUF_SZ)
				strcat(big,response); else break;
		}
		close(PIPE[1]);

		/* printf(" %3d [\n%s     ]\n", strlen(big), big); */

		if(strstr(big,"failed")) return(-1);
		if(strstr(big,"Mode:" )) return(0);
		return(-2);
	}
	else
	{
	       /*
		* Child calls ftp
		*/

		write(PIPE[1], "Child  Exit(1)\n", strlen("Child  Exit(1)\n"));
		close(PIPE[1]);

		dup2(PIPE[0],0);
		dup2(PIPE[0],1);
		dup2(PIPE[0],2);

		st = execl("/usr/bin/ftp", "/usr/bin/ftp", "-in", NULL );

		printf("%d - %d\n",st, errno);
		perror("Child error");
	}

	close(PIPE[1]);
	return(st);
}

/*
 *  END
 */
