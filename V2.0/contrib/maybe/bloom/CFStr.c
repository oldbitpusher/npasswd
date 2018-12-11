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

/* #define DB */
/* #define DB1 */
/*----------------------------------------------------------------------------*
| CFStr.c								      |
*----------------------------------------------------------------------------*/

#include <string.h>
#include <ctype.h>
#include "Global.h"
#include "CFStr.h"
#include "Queue.h"

/*----------------------------------------------------------------------------*
| PUBLIC								      |
| CFStr:  iterator for CrackFilter entries derived from a string	      |
| CFStrI: iterator for CrackFilter entries derived from an iterator	      |
*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
| CFStr									      |
*----------------------------------------------------------------------------*/

static QUEUE Queue;

char*
CFStr(s)
char* s;
{
    int len;
    int allCaps;
    int inCap;
    int anyWhiteSpace;
    int anyPunct;
    int anyVowel;

    static char buf[MAXSTRING + 1];
    static char buf2[MAXSTRING + 1];

    static char ss[PWLEN + 1];
    char* p;
    char* q;
    int i;
    
    /*------------------------------------------------------------------------*
    | Iteration								      |
    *------------------------------------------------------------------------*/

    if (s == 0) {
        if ((p = QHead(&Queue)) == 0)
            return 0;
        strncpy(ss, p, PWLEN);
        ss[PWLEN] = '\0';               /* truncate to 8 characters */
        return ss;
    }

    /*------------------------------------------------------------------------*
    | Initialization							      |
    | (This is where all the work gets done: making a queue of return strings |
    *------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*
    | See what's special about the string				      |
    *------------------------------------------------------------------------*/

#ifdef DB1
    printf(">%s<\n", s);
#endif DB1

    len = strlen(s);
    allCaps = 1;
    inCap = 0;
    anyWhiteSpace = 0;
    anyPunct = 0;
    anyVowel = 0;
    buf[MAXSTRING] = '\0';

    for (p = s; *p; p++) {
        if (islower(*p))   allCaps = 0;
        if (IsInCap(p, s)) inCap = 1;
        if (isspace(*p))   anyWhiteSpace = 1;
        if (ispunct(*p))   anyPunct = 1;
        if (IsVowel(*p))   anyVowel = 1;
    }
    if (allCaps)
        inCap = 0;

    /*------------------------------------------------------------------------*
    | First, copy the string and normalize case:			      |
    | if all lower, no change						      |
    | if all upper, lowercase all					      |
    | else lowercase initial and final chars				      |
    *------------------------------------------------------------------------*/

    strncpy(buf, s, MAXSTRING);
    if (allCaps) {
        for (p = buf; *p; p++)
            if (isupper(*p))
                *p = tolower(*p);
    }
    else {
        for (p = buf; *p; p++)
            if (isupper(*p) && !IsInCap(p, buf))
                *p = tolower(*p);
    }

    /*------------------------------------------------------------------------*
    | As is								      |
    *------------------------------------------------------------------------*/

#   ifdef DB
    printf("    As is >%s<\n", buf);
#   endif /* DB */
    QAppend(&Queue, buf);

    /*------------------------------------------------------------------------*
    | Lowercase all							      |
    *------------------------------------------------------------------------*/

    if (inCap) {
        strncpy(buf2, buf, MAXSTRING);
        for (p = buf2; *p; p++)
            if (isupper(*p))
                *p = tolower(*p);
#       ifdef DB
        printf("    Lowercase all >%s<\n", buf2);
#       endif /* DB */
        QAppend(&Queue, buf2);
    }

    /*------------------------------------------------------------------------*
    | Strip punctuation							      |
    *------------------------------------------------------------------------*/

    if (anyPunct) {
        for (p = s, q = buf2; *p; p++)
            if (!ispunct(*p))
                *q++ = *p;
        *q = '\0';
        for (p = buf2; *p; p++)
            if (isupper(*p) && !IsInCap(p, buf2))
                *p = tolower(*p);
#       ifdef DB
        printf("    Strip punctuation >%s<\n", buf2);
#       endif /* DB */
        QAppend(&Queue, buf2);

	if (inCap) {
	    for (p = buf2; *p; p++)
		if (isupper(*p))
		    *p = tolower(*p);
#           ifdef DB
	    printf("    and lowercase >%s<\n", buf2);
#           endif /* DB */
	    QAppend(&Queue, buf2);
	}
    }

    /*------------------------------------------------------------------------*
    | Strip whitespace							      |
    *------------------------------------------------------------------------*/

    if (anyWhiteSpace) {
        for (p = s, q = buf2; *p; p++)
            if (!isspace(*p))
                *q++ = *p;
        *q = '\0';
        for (p = buf2; *p; p++)
            if (isupper(*p) && !IsInCap(p, buf2))
                *p = tolower(*p);
#       ifdef DB
        printf("    Strip whitespace >%s<\n", buf2);
#       endif /* DB */
        QAppend(&Queue, buf2);

	if (inCap) {
	    for (p = buf2; *p; p++)
		if (isupper(*p))
		    *p = tolower(*p);
#	    ifdef DB
	    printf("    and lowercase >%s<\n", buf2);
#	    endif /* DB */
	    QAppend(&Queue, buf2);
	}
    }


    /*------------------------------------------------------------------------*
    | Strip punctuation and whitespace					      |
    *------------------------------------------------------------------------*/

    if (anyPunct && anyWhiteSpace) {
        for (p = s, q = buf2; *p; p++)
            if (!ispunct(*p) && !isspace(*p))
                *q++ = *p;
        *q = '\0';
        for (p = buf2; *p; p++)
            if (isupper(*p) && !IsInCap(p, buf2))
                *p = tolower(*p);
#       ifdef DB
        printf("    Strip punctuation and whitespace >%s<\n", buf2);
#       endif /* DB */
        QAppend(&Queue, buf2);

	if (inCap) {
	    for (p = buf2; *p; p++)
		if (isupper(*p))
		    *p = tolower(*p);
#           ifdef DB
	    printf("    and lowercase >%s<\n", buf2);
#           endif /* DB */
	    QAppend(&Queue, buf2);
	}
    }

    /*------------------------------------------------------------------------*
    | If >8 characters, reverse and lowercase				      |
    *------------------------------------------------------------------------*/

#ifdef LONG_REVERSE
    if (len > 8) {
        for (i = 0; i < len && i < MAXSTRING; i++)
            if (isupper(s[len - 1 - i]))
                buf2[i] = tolower(s[len - 1 - i]);
            else
                buf2[i] = s[len - 1 - i];
        buf2[i] = 0;
#       ifdef DB
        printf("    If >8 characters, reverse and lowercase >%s<\n", buf2);
#       endif /* DB */
        QAppend(&Queue, buf2);
    }
#endif LONG_REVERSE

    /*------------------------------------------------------------------------*
    | Strip vowels aeiouAEIOU						      |
    *------------------------------------------------------------------------*/

#ifdef VOWEL_STRIP
    if (anyVowel) {
        for (p = s, q = buf2; q < buf2 + MAXSTRING && *p; p++)
            if (!IsVowel(*p))
                *q++ = *p;
        *q = '\0';
#       ifdef DB
        printf("    Strip vowels aeiouAEIOU >%s<\n", buf2);
#       endif /* DB */
        QAppend(&Queue, buf2);
    }
#endif VOWEL_STRIP

    /*------------------------------------------------------------------------*
    | End of the story							      |
    *------------------------------------------------------------------------*/

    return 0;
}

/*----------------------------------------------------------------------------*
| CFStrI								      |
*----------------------------------------------------------------------------*/

char*
CFStrI(iterator)
char* (*iterator)();
{
    static int initialized = 0;
    static char* (*iter)();
    char* s;

    /*------------------------------------------------------------------------*
    | Initialization							      |
    *------------------------------------------------------------------------*/

    if (iterator) {
        iter = iterator;
        return 0;
    }

    /*------------------------------------------------------------------------*
    | Iteration: loop until there's a string to return			      |
    *------------------------------------------------------------------------*/

    while (1) {
        if (!initialized) {
            s = iter(0);
            if (s == 0) {
                initialized = 0;
                return 0;
            }
            CFStr(s);
            initialized = 1;
        }
        if (s = CFStr(0))
            return s;
        else
            initialized = 0;
    }
}
