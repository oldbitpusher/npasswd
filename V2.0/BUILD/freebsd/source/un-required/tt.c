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
  */

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

int
main( int argc, char *argv[], char *envp[] )
{
	short	a;
	int	x;
	long	l;

	printf(" Sizeof short = %d\n", sizeof(a));
	printf(" Sizeof int   = %d\n", sizeof(x));
	printf(" Sizeof long  = %d\n", sizeof(l));

	for(x=0,l=0;x<10;x++,l++) printf(" %d = %4d = %9ld\n", x, htons(x), htonl(l));

	return(0);
}

/* END */
