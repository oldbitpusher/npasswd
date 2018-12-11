/*----------------------------------------------------------------------------*
|                                                                             |
|                           Author: Donald Olivier                            |
|                      Instructional Computing Facility                       |
|                      Harvard School of Public Health                        |
|                            677 Huntington Ave.                              |
|                             Boston, MA 02115                                |
|                           don@hsph.harvard.edu                              |
|                                                                             |
|    This code may be distributed freely, provided this notice is retained.   |
|                                                                             |
*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
| BitArray.h								      |
*----------------------------------------------------------------------------*/

#ifndef _BitArray
#define _BitArray

#ifndef FILE
#include <stdio.h>
#endif /* FILE */

/*----------------------------------------------------------------------------*
| An array of bits, which can be queried with BitArrayProbe and set with      |
| BitArraySet.	The probe is a *32-bit* integer: it is *right-shifted*	      |
| to fit.  The size of the array must be a power of 2.			      |
*----------------------------------------------------------------------------*/

void BitArrayCon();           /* void BitArrayCon(int nbytes); */
void BitArrayRead();          /* void BitArrayRead(FILE*); */
void BitArrayWrite();         /* void BitArrayWrite(FILE*); */
int  BitArrayProbe();         /* int BitArrayProbe(unsigned int); */
int  BitArraySet();           /* int BitArraySet(unsigned int); */
                              /* returns 1 if not already set */
void BitArrayGetNSet();       /* void BitArrayGetNSet(void); */
int  BitArrayReturnNBytes();  /* int BitArrayReturnNBytes(void); */
int  BitArrayReturnNSet();    /* int BitArrayReturnNSet(void); */
void BitArrayDump();          /* void BitArrayDump(void); */

#endif /* ! _BitArray */
