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
  *       Date: Apr-May 1999
  *
  */
  
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include "libhide.h"

int		errno;

int
main ( ARGC, ARGV )
int	ARGC;
char	**ARGV;
{
    int			len = 70;
    int			j;
    char		*block;
    char		*stand;
    char		keycode[] = "AB35C2-B301EE-C11022-D374F0";

    block = (char *) malloc(len+HIDE_SANITY);
    stand = (char *) malloc(len+HIDE_SANITY);

    errno = 0;
    /*     123456789+123456789+123456789+123456789+123456789+123456789+123456789+" */
    bcopy("This is a test of the emergency broadcast system. Please stay    alert",stand,len);
    stand[len] = '\0';

  for(j=0; j<1200 ; j++)
  {
    /*     123456789+123456789+123456789+123456789+123456789+123456789+123456789+" */
    bcopy("Where do you want to go today.  broadcast system. Please stay    alert",block,len);
    bcopy("This is a test of the emergency broadcast system. Please stay    alert",block,len);
    block[len] = '\0';
    /* printf("[%-70s]\n\n",block); */

    sleep(1);

    HideStr(0,block,len,keycode);
    /* printf("[%-70s]\n\n",block); */
    /* printf("Len = %d\n",len); */

    HideStr(1,block,len,keycode);
    /* printf("[%-70s]\n\n",block); */
    /* printf("Len = %d\n",len); */

    block[len] = '\0';

    if( bcmp(stand,block,len) ) {
	printf("\n");
	printf("stand - [%-70s] %08p\n",  stand,stand);
	printf("block - [%-70s] %08p\n\n",block,block);
    }

    if((j%50)==0 && j) write(1,"\n",1);
    write(1,".",1);
  }

  free(block);
  free(stand);

  printf("\n");
}

/* END */
