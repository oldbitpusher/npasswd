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
| Util.c                                                                      |
| Utility routines                                                            |
*----------------------------------------------------------------------------*/

#include <ctype.h>
#include <stdio.h>
#include "Util.h"

/*----------------------------------------------------------------------------*
| IsVowel: is a character aeiouAEIOU					      |
| IsInCap: is a character a non-word-initial and non-word-final cap	      |
*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
| IsVowel								      |
*----------------------------------------------------------------------------*/

int
IsVowel(c)
char c;
{
    return  c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

/*----------------------------------------------------------------------------*
| IsInCap								      |
*----------------------------------------------------------------------------*/

int
IsInCap(p, s)
char* p;        /* pointer to character */
char* s;        /* pointer to string */
{
    if (!isupper(*p))     return 0;
    if (!isalnum(*(p+1))) return 0;
    if (p == s)           return 0;
    if (!isalnum(*(p-1))) return 0;
    return 1;
}

/*----------------------------------------------------------------------------*
| CantHappen                                                                  |
*----------------------------------------------------------------------------*/

void
CantHappen()
{
    fprintf(stderr, "Can't happen\n");
    abort();
}
