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
  * Written by: Victor Burns
  *       Date: 1999-2000
  *
  *  Client Command processor
  *
  */

#ifndef	_UDP_CLIENT_H
#define	_UDP_CLIENT_H

#ifdef  __cplusplus
extern "C" {
#endif

/*
#ifndef htonl
#define ntohl(x)        (x)
#define ntohs(x)        (x)
#define htonl(x)        (x)
#define htons(x)        (x)
#endif
*/

/*
 *  Calls
 */

extern int udp_client( int, char *, char *, char * );


#ifdef  __cplusplus
}
#endif

#endif  /* _UDP_CLIENT_H */

/* END */
