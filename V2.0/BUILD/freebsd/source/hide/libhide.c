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
  *  Hide or UnHide a block of characters within a
  *  window of time.
  *
  * Written by: Victor Burns (Texas Instruments)
  *       Date: Apr-Aug 1999
  *    Updates: 2000,2001
  *
  */

#ifdef HPUX
#define _XOPEN_SOURCE
#define _XOPEN_SOURCE_EXTENDED
#endif

#include <sys/types.h>

#define	EXPBUFSIZE 2048

#define INIT		register char *sp = instring;
#define GETC(void)	(*sp++)
#define PEEKC(void)	(*sp)
#define UNGETC(void)	(--sp)
#define RETURN(ptr)	return;
#define ERROR(val)	return;

#include <time.h>
#include <regexp.h>
#include <syslog.h>

#include "libhide.h"

#define	TIME_NOW	0
#define	TIME_FUTURE	1
#define	TIME_PAST	2


/*
 * NOTE: The size of the buffer pointed to by str must be at least
 *       HIDE_SANITY bytes larger than the value of len.  This is
 *       because the data grows by HIDE_SANITY bytes during the
 *       the HIDE process.
 */

int HideStr( mode, str, len, keycode)
    int		mode;
    char	*str;
    int		len;
    const char	*keycode;
{
    char	*buf;
    char	*expbuf;
    char	**endptr = NULL;
    char	RE[] = "^[0-9a-zA-Z]\\{6\\}-[0-9a-zA-Z]\\{6\\}-[0-9a-zA-Z]\\{6\\}-[0-9a-zA-Z]\\{6\\}$";
    int		v,w,x,y,z;
    int		boi[4];

    union key_t {
	time_t		T;
	unsigned char	b[4];
	double		junk; /* Memory alignment issues */
    } key[3], whiskey;     /* Array of two to fix memory alignment issues */

   /*
    * Allocate work space
    */

    buf   = (char *) malloc(len+HIDE_SANITY);

   /*
    * Convert keycode into whiskey
    */

    expbuf = NULL;
    expbuf = (char *) malloc(EXPBUFSIZE);
    (void) compile(RE, expbuf, &expbuf[EXPBUFSIZE],'\0');

    if(step(keycode, expbuf))
    {
	strcpy(buf,"0x"); strcat(buf,keycode);    whiskey.T  = strtol(buf,endptr,16);
	strcpy(buf,"0x"); strcat(buf,keycode+7);  whiskey.T *= strtol(buf,endptr,16);
	strcpy(buf,"0x"); strcat(buf,keycode+14); whiskey.T *= strtol(buf,endptr,16);
	strcpy(buf,"0x"); strcat(buf,keycode+21); whiskey.T *= strtol(buf,endptr,16);
	/* VICB
	   printf("whiskey.T   = %0lx\n",whiskey.T);
	   printf("whiskey.b[0]= %0lx\n",whiskey.b[0]);
	   printf("whiskey.b[1]= %0lx\n",whiskey.b[1]);
	   printf("whiskey.b[2]= %0lx\n",whiskey.b[2]);
	   printf("whiskey.b[3]= %0lx\n",whiskey.b[3]);
	*/
    }
    else
    {
	whiskey.T = 0;
	syslog(LOG_INFO,"Warning: HideStr(): Passwd Invalid KeyCode: Security Compromise");
    }
    if(expbuf) free(expbuf);

   /*
    * Detect ByteOrder for this System Arch
    */

    key[0].T = 0x00000001;
    if( key[0].b[0] ) { boi[0] = 3; boi[1] = 2; boi[2] = 1; boi[3] = 0; }
    if( key[0].b[3] ) { boi[0] = 0; boi[1] = 1; boi[2] = 2; boi[3] = 3; }

   /*
    * What time is it?
    * Use as Key to Hide Data
    */

    key[TIME_NOW].T = key[TIME_FUTURE].T = key[TIME_PAST].T = time(0);

   /*
    *  Simulate future or past delay
    */

#if defined(DEBUG)
    if( mode == HCMD_UNHIDE )
    {
	printf("\n");
	printf(" Time: %d%d%d%d-%d%d%d%d %d%d%d%d-%d%d%d%d %d%d%d%d-%d%d%d%d %d%d%d%d-%d%d%d%d\n",
	 (key[0].T & 0x80000000) > 0, (key[0].T & 0x40000000) > 0, (key[0].T & 0x20000000) > 0, (key[0].T & 0x10000000) > 0,
	 (key[0].T & 0x08000000) > 0, (key[0].T & 0x04000000) > 0, (key[0].T & 0x02000000) > 0, (key[0].T & 0x01000000) > 0,

	 (key[0].T & 0x00800000) > 0, (key[0].T & 0x00400000) > 0, (key[0].T & 0x00200000) > 0, (key[0].T & 0x00100000) > 0,
	 (key[0].T & 0x00080000) > 0, (key[0].T & 0x00040000) > 0, (key[0].T & 0x00020000) > 0, (key[0].T & 0x00010000) > 0,

	 (key[0].T & 0x00008000) > 0, (key[0].T & 0x00004000) > 0, (key[0].T & 0x00002000) > 0, (key[0].T & 0x00001000) > 0,
	 (key[0].T & 0x00000800) > 0, (key[0].T & 0x00000400) > 0, (key[0].T & 0x00000200) > 0, (key[0].T & 0x00000100) > 0,

	 (key[0].T & 0x00000080) > 0, (key[0].T & 0x00000040) > 0, (key[0].T & 0x00000020) > 0, (key[0].T & 0x00000010) > 0,
	 (key[0].T & 0x00000008) > 0, (key[0].T & 0x00000004) > 0, (key[0].T & 0x00000002) > 0, (key[0].T & 0x00000001) > 0
	);

/*	key[0].T = key[1].T = key[2].T += ((rand()%46)-23); */
	if(key[0].T & 0x00000001 == 1)
	{
		key[0].T = key[1].T = key[2].T += 32;
	}
	else
	{
		key[0].T = key[1].T = key[2].T -= 32;
	}

	printf(" Time: %d%d%d%d-%d%d%d%d %d%d%d%d-%d%d%d%d %d%d%d%d-%d%d%d%d %d%d%d%d-%d%d%d%d",
	 (key[0].T & 0x80000000) > 0, (key[0].T & 0x40000000) > 0, (key[0].T & 0x20000000) > 0, (key[0].T & 0x10000000) > 0,
	 (key[0].T & 0x08000000) > 0, (key[0].T & 0x04000000) > 0, (key[0].T & 0x02000000) > 0, (key[0].T & 0x01000000) > 0,

	 (key[0].T & 0x00800000) > 0, (key[0].T & 0x00400000) > 0, (key[0].T & 0x00200000) > 0, (key[0].T & 0x00100000) > 0,
	 (key[0].T & 0x00080000) > 0, (key[0].T & 0x00040000) > 0, (key[0].T & 0x00020000) > 0, (key[0].T & 0x00010000) > 0,

	 (key[0].T & 0x00008000) > 0, (key[0].T & 0x00004000) > 0, (key[0].T & 0x00002000) > 0, (key[0].T & 0x00001000) > 0,
	 (key[0].T & 0x00000800) > 0, (key[0].T & 0x00000400) > 0, (key[0].T & 0x00000200) > 0, (key[0].T & 0x00000100) > 0,

	 (key[0].T & 0x00000080) > 0, (key[0].T & 0x00000040) > 0, (key[0].T & 0x00000020) > 0, (key[0].T & 0x00000010) > 0,
	 (key[0].T & 0x00000008) > 0, (key[0].T & 0x00000004) > 0, (key[0].T & 0x00000002) > 0, (key[0].T & 0x00000001) > 0
	);

	printf(" Elapest Time [ %3d ] seconds\n",(key[0].T-time(0)));
    }
#endif

   /*
    *  1. Drop lowest HIDE_TOSSBITS bits of time
    *  2. Create Future and Past Windows (MUST HAPPEN BEFORE Whiskey!)
    *  3. Apply Whiskey
    *  4. Reuse bits in better/drunken order
    */

    for(v=0;v<3;v++) key[v].T = key[v].T >> HIDE_TOSSBITS;

    key[TIME_FUTURE].T++;
    key[TIME_PAST].T--;

    if(whiskey.T)
    {
	for(v=0;v<3;v++)
	{
	    key[v].b[boi[0]] ^= whiskey.b[boi[1]];
	    key[v].b[boi[1]] ^= whiskey.b[boi[2]];
	    key[v].b[boi[2]] ^= whiskey.b[boi[3]];
	    key[v].b[boi[3]] ^= whiskey.b[boi[0]];
	}
/*
	printf("whiskey.T   = %0lx\n",whiskey.T);
	printf("whiskey.b[0]= %0lx\n",whiskey.b[boi[0]]);
	printf("whiskey.b[1]= %0lx\n",whiskey.b[boi[1]]);
	printf("whiskey.b[2]= %0lx\n",whiskey.b[boi[2]]);
	printf("whiskey.b[3]= %0lx\n",whiskey.b[boi[3]]);
*/
    }
	

    x = key[0].b[boi[3]];
    y = key[1].b[boi[3]];
    z = key[2].b[boi[3]];

    for(v=0;v<3;v++) key[v].T = ( key[v].T * key[v].T ) + 1;

    x = ((x& 1)<<7)|((x& 2)<<5)|((x& 4)<<3)|((x&  8)<<1)|
	((x&16)>>1)|((x&32)>>3)|((x&64)>>5)|((x&128)>>7);

    y = ((y& 1)<<7)|((y& 2)<<5)|((y& 4)<<3)|((y&  8)<<1)|
	((y&16)>>1)|((y&32)>>3)|((y&64)>>5)|((y&128)>>7);

    z = ((z& 1)<<7)|((z& 2)<<5)|((z& 4)<<3)|((z&  8)<<1)|
	((z&16)>>1)|((z&32)>>3)|((z&64)>>5)|((z&128)>>7);

    for(v=0;v<4;v++) key[0].b[boi[v]] = key[0].b[boi[v]] ^ x;
    for(v=0;v<4;v++) key[1].b[boi[v]] = key[1].b[boi[v]] ^ y;
    for(v=0;v<4;v++) key[2].b[boi[v]] = key[2].b[boi[v]] ^ z;

    /* for(v=0;v<3;v++) printf("Key[%d] = 0x%08lX\n", v, key[v].T); */

   /*
    * Traverse incomming buffer and Hide/UnHide it.
    */

    for( w=0 ; w<=2 ; w++ )
    {
	/* if( w==1 ) printf("Using FUTURE Time Key!\n"); */
	/* if( w==2 ) printf("Using PAST   Time Key!\n"); */
	/* if( w ) key[0].T = key[w].T; */ /* Try Old Key */

	/* Insert First HIDE_SANITY bytes to beginning of buffer as sanity check */
	if( mode == HCMD_HIDE ) bcopy(str,str+HIDE_SANITY,len);

	for( x=0, y=len+HIDE_SANITY-1; x<len+HIDE_SANITY ; x++, y--) {

	    w    == 0 &&
	    mode == HCMD_UNHIDE ? ( z = str[x],
		str[x]= ((z& 1)<<7)|((z& 2)<<5)|((z& 4)<<3)|((z&  8)<<1)|
			((z&16)>>1)|((z&32)>>3)|((z&64)>>5)|((z&128)>>7) ) : 0;

	    buf[y] = ( mode == HCMD_UNHIDE ? ( str[x] ^ key[w].b[boi[(x%4)]] ) : str[x] );
	}

	/* Try last time window if sanity check fails */
	v = 0;
	if( mode == HCMD_UNHIDE && w <= 1 )
	for( x=0, y=HIDE_SANITY; x<HIDE_SANITY; x++, y++ ) if( buf[x] != buf[y] ) v++;
	if( mode == HCMD_UNHIDE && w <= 1 && v ) continue;

	for( x=0; x<(len+HIDE_SANITY) ; x++ ) {

	    str[x] = ( mode == HCMD_HIDE ? ( buf[x] ^ key[w].b[boi[(x%4)]] ) : buf[x] );

	    mode == HCMD_HIDE ? ( z = str[x],
		str[x]= ((z& 1)<<7)|((z& 2)<<5)|((z& 4)<<3)|((z& 8)<<1)|
			((z&16)>>1)|((z&32)>>3)|((z&64)>>5)|((z&128)>>7) ) : 0;
	}

	/* Delete First HIDE_SANITY bytes from beginning of buffer */
	if( mode == HCMD_UNHIDE ) bcopy(str+HIDE_SANITY, str, len);
	
	/* Hide using the first key */
	if( mode == HCMD_HIDE ) break;
	if( mode == HCMD_UNHIDE ) break;
    }

   /*
    * Clear buffer with zero's before freeing
    * Then free it.
    */

    bzero(buf, len+HIDE_SANITY);
    free(buf);

   /*
    * Return buffer len
    */

    return(len);
}

/* END */
