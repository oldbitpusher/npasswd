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
  *
  * Written by: Victor Burns (Texas Instruments)
  *       Date: 1999-2000
  *
  *  Configuration and config test
  *
  */

#ifndef	_UDP_READCONFIG_H
#define	_UDP_READCONFIG_H

#ifdef  __cplusplus
extern "C" {
#endif


/*
 *  Calls
 */

extern int udp_readConfig        ( char ***, char ***, char ** );
extern int udp_authorizedServer  ( char ** );
extern int udp_authorizedClient  ( char **, char * );
extern int udp_authorizedClientI ( char ** );


#ifdef  __cplusplus
}
#endif

#endif  /* _UDP_READCONFIG_H */

/* END */
