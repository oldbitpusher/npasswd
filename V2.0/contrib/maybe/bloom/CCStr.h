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
| CCStr.h								      |
*----------------------------------------------------------------------------*/

#ifndef _CCStr
#define _CCStr

/* An iterator returning all the CrackCheck entries implied by a string */

extern int LongReverse;
extern int VowelStrip;

char* CCStr();                  /* char* CCStr(char*); */
char* CCStrI();                 /* char* CCStr(char* (*iterator)()); */
char* Mycroft();                /* char* Mycroft(char*); */

#endif /* ! _CCStr */
