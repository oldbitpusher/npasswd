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
| Blf.h									      |
| Bloom Filter Word List						      |
*----------------------------------------------------------------------------*/

#ifndef _Blf
#define _Blf

/*----------------------------------------------------------------------------*
| A bit-array which makes it possible to test whether a word is in the	      |
| list, with a fast lookup time which is essentially independent of the	      |
| size of the list.  Cf. Bloom, B. H., "Space-time tradeoffs in hash	      |
| coding with allowable errors."  Communications of the ACM 13, 422-426,      |
| 1970.									      |
|									      |
| Each word in the input list is hashed m times and the corresponding	      |
| bits of the array are set; then a word for which all m bits are set is      |
| deemed to be on the list.  Except for details of the hash coding, this      |
| is the same algorithm the Unix "spell" program uses.			      |
|									      |
| The expected false-positive rate f depends on he multiplicty m and the      |
| ratio of the size of the filter to the number of list items.	    If r is   |
| the ratio of the number of bits in the filter to the number of words in     |
| the list, the expected rate will be approximately			      |
|     f = (1 - exp(-m/r)^m .						      |
| With optimal multiplicity, about half of the bits in the filter will be     |
| set, and the expected rate will be about				      |
|     f = exp(-kr)							      |
| where k = (log 2)^2 = .48.						      |
*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
|     Table of -log10(expected false positive rate)			      |
|									      |
|									      |
|	       r = filter bits / list entry				      |
|									      |
|	     8	10  12	14  16	18  20	22  24				      |
|									      |
|	4  1.6 1.9 2.2 2.4 2.6 2.8 3.0 3.1 3.3				      |
|	5  1.7 2.0 2.3 2.6 2.9 3.1 3.3 3.5 3.6				      |
|	6  1.7 2.1 2.4 2.7 3.0 3.3 3.5 3.7 3.9				      |
|   M	7  1.6 2.1 2.5 2.8 3.2 3.4 3.7 4.0 4.2				      |
|   u	8  1.6 2.1 2.5 2.9 3.2 3.6 3.9 4.1 4.4				      |
|   l	9  1.5 2.0 2.5 2.9 3.3 3.6 4.0 4.3 4.5				      |
|   t  10  1.5 2.0 2.5 2.9 3.3 3.7 4.1 4.4 4.7				      |
|   i  11  1.4 1.9 2.4 2.9 3.3 3.7 4.1 4.5 4.8				      |
|   p  12  1.3 1.9 2.4 2.9 3.3 3.8 4.1 4.5 4.9				      |
|   l  13  1.2 1.8 2.3 2.8 3.3 3.8 4.2 4.6 4.9				      |
|   i  14  1.2 1.7 2.3 2.8 3.3 3.7 4.2 4.6 5.0				      |
|   c  15  1.1 1.6 2.2 2.7 3.2 3.7 4.2 4.6 5.0				      |
|   i  16  1.0 1.6 2.1 2.7 3.2 3.7 4.1 4.6 5.0				      |
|   t  17  0.9 1.5 2.1 2.6 3.1 3.6 4.1 4.6 5.0				      |
|   y  18  0.9 1.4 2.0 2.5 3.1 3.6 4.1 4.5 5.0				      |
|      19  0.8 1.3 1.9 2.5 3.0 3.5 4.0 4.5 5.0				      |
|      20  0.7 1.3 1.8 2.4 2.9 3.5 4.0 4.5 5.0				      |
|									      |
| Rules of thumb:							      |
|     for < .01   false positives, use m = 7,  at least 1.25 bytes per entry  |
|     for < .003  false positives, use m = 9,  at least 1.5  bytes per entry  |
|     for < .001  false positives, use m = 11, at least 2    bytes per entry  |
|     for < .0001 false positives, use m = 14, at least 2.5  bytes per entry  |
*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
| In this implementation the array size must be a power of 2.		      |
*----------------------------------------------------------------------------*/

extern int PrintEntry;          /* print strings set to stdout */

void BlfCon();                  /* void BlfCon(int nbytes, nhashes); */
void BlfRead();                 /* void BlfRead(FILE*); */
void BlfWrite();                /* void BlfWrite(FILE*); */
int  BlfProbe();                /* int BlfProbe(char*); */
int  BlfSet();                  /* int BlfSet(char*); */
                                /* returns 1 if not already set */
void BlfSetI();                 /* int BlfSet(int* nnew, int* ngross,
                                              char* suffix, char* (*iter()); */
double BlfFalsePos();           /* double BlfFalsePos(void); */

#endif  /* ! _Blf */
