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
| Global.h								      |
*----------------------------------------------------------------------------*/

#ifndef _Global
#define _Global

#define MARK_CONSTRUCT

#define WORDLENGTH 32	   /* machine word (bits) */
#define BITSPERBYTE 8      /* number of bits in a byte */
#define LOGBYTE 3          /* log of number of bits in a byte */
#define LOGBYTEMASK 0x7    /* select Logbyte low-order bits */

#define MAXSTRING 32	   /* dictionary strings can't be longer */
#define MAXLINE  255	   /* input lines can't be longer */
#define MAXTEXT 1024 	   /* only this much text is processed */
#define PWLEN  8	   /* password algorithm only uses this many */

#endif /* ! _Global */
