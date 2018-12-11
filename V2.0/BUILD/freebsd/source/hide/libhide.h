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
  *  Hide & UnHide
  */

#ifndef _HIDE_H
#define _HIDE_H

#ifdef  __cplusplus
extern "C" {
#endif


/* Commands */
#define	HCMD_HIDE	0
#define	HCMD_UNHIDE	1

#define	HIDE_TOSSBITS	5
#define	HIDE_SANITY	5

/* Function */
extern int HideStr(int, char *, int, const char *);


#ifdef  __cplusplus
}
#endif

#endif  /* _HIDE_H */

/* END */
