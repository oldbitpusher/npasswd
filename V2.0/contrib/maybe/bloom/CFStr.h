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
| CFStr.h								      |
*----------------------------------------------------------------------------*/

#ifndef _CFStr
#define _CFStr

/*----------------------------------------------------------------------------*
| An iterator returning all the CrackFilter entries implied by a string	      |
*----------------------------------------------------------------------------*/

extern int LongReverse;
extern int VowelStrip;

char* CFStr();                  /* char* CFStr(char*); */
char* CFStrI();			/* char* CFStrI( char* (*iterator)() ) */

#endif /* ! _CFStr */
