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
| Iter.h                                                                      |
*----------------------------------------------------------------------------*/

#ifndef _Iter
#define _Iter

/*----------------------------------------------------------------------------*
| String Iterators: called with a nonzero argument, initialize		      |
|		   called with a zero argument, return pointer to a static    |
|		       string, or 0					      |
*----------------------------------------------------------------------------*/

typedef char* (*ITER);

char* ArgIter();			/* char* ArgIter(char**) */
char* FileIter();			/* char* FileIter(char*) */
char* FileListIter();			/* char* FileListIter(char*(*)) */
char* TextWordIter();			/* char* TextWordIter(char*) */
char* TextWordIterI();			/* char* TextWordIter(char*(*)) */

#endif /* ! _Iter */
