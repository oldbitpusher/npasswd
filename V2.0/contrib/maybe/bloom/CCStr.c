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
/*----------------------------------------------------------------------------*
| CCStr.c                                                                     |
*----------------------------------------------------------------------------*/

#include <string.h>
#include <ctype.h>
#include "Global.h"
#include "CCStr.h"
#include "Queue.h"

/*----------------------------------------------------------------------------*
| PUBLIC                                                                      |
| CCStr:  iterator for CrackCheck entries derived from a string               |
| CCStrI: iterator for CrackCheck entries derived from an iterator            |
*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
| CCStr                                                                       |
*----------------------------------------------------------------------------*/

static QUEUE Queue;

char*
CCStr(s)
char* s;
{
    int len;
    char buf[MAXSTRING + 1];
    char bufx[MAXSTRING + 1];
    int allcaps;
    char* ss;
    char* p;
    char* q;
    int i, j, k;;
    
    /*------------------------------------------------------------------------*
    | Iteration                                                               |
    *------------------------------------------------------------------------*/

    if (s == 0) {
        if (Queue.first == 0)
            return 0;
        ss = (char*)QHead(&Queue, 0);
        return ss;
    }

    /*------------------------------------------------------------------------*
    | Initialization                                                          |
    | (This is where all the work gets done: making a queue of return strings |
    *------------------------------------------------------------------------*/

    if ((len = strlen(s)) == 0)
	return;
    if (len > PWLEN)
        len = PWLEN;
    strncpy(buf, s, len);
    buf[len] = '\0';

    /*------------------------------------------------------------------------*
    | First normalize the case                                                |
    *------------------------------------------------------------------------*/

    allcaps = 1;
    for (p = buf; *p && allcaps; p++)
        if (islower(*p))
            allcaps = 0;
    if (allcaps) {
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
    | Test as is							      |
    *------------------------------------------------------------------------*/

#   ifdef DB
    printf("    As is >%s<\n", buf);
#   endif /* DB */
    QAppend(&Queue, buf);

    if (len == 1)
	return;

    /*------------------------------------------------------------------------*
    | Strip extremal nonalpha                                                 |
    *------------------------------------------------------------------------*/

    if (!isalpha(buf[0])) {
        strcpy(bufx, &buf[1]);
#       ifdef DB
        printf("    Strip initial nonalpha >%s<\n", bufx);
#       endif /* DB */
        QAppend(&Queue, bufx);
    }
    if (!isalpha(buf[len - 1])) {
        strcpy(bufx, buf);
        bufx[len - 1] = '\0';
#       ifdef DB
        printf("    Strip terminal nonalpha >%s<\n", bufx);
#       endif /* DB */
        QAppend(&Queue, bufx);
    }
    if (!isalpha(buf[0]) && len == PWLEN) {
        strcpy(bufx, &buf[1]);
        for (i = ' '; i < 0x7f; i++) {
            bufx[PWLEN - 1] = i;
            bufx[PWLEN] = '\0';
#           ifdef DB
            printf("     Strip initial nonalpha (8) >%s<\n", bufx);
#           endif /* DB */
            QAppend(&Queue, bufx);
        }
    }

    /*------------------------------------------------------------------------*
    | Unpluralize                                                             |
    | Quick and dirty                                                         |
    *------------------------------------------------------------------------*/

    if (buf[len - 1] == 's') {
        strcpy(bufx, buf);
        bufx[len - 1] = '\0';
#       ifdef DB
        printf("    Unpluralize >%s<\n", bufx);
#       endif /* DB */
        QAppend(&Queue, bufx);
    }
    if (strcmp(&buf[len - 2], "es") == 0) {
	if (buf[len - 3] == 'h' || buf[len - 3] == 'j' || buf[len - 3] == 's' ||
				    buf[len - 3] == 'x' || buf[len - 3] == 'z') {
	    strcpy(bufx, buf);
	    bufx[len - 2] = '\0';
#	    ifdef DB
	    printf("    Unpluralize >%s<\n", bufx);
#	    endif /* DB */
	    QAppend(&Queue, bufx);
	}
    }
    if (len == PWLEN && buf[PWLEN - 1] == 'e') {
	if (buf[PWLEN - 2] == 'h' || buf[PWLEN - 2] == 'j' || 
		buf[PWLEN - 2] == 's' || buf[PWLEN - 2] == 'x' || 
		buf[PWLEN - 2] == 'z') {
	    strcpy(bufx, buf);
	    bufx[PWLEN - 1] = '\0';
#	    ifdef DB
	    printf("    Unpluralize >%s<\n", bufx);
#	    endif /* DB */
	    QAppend(&Queue, bufx);
	}
        strcpy(bufx, buf);
    }
    if (strcmp(&buf[len - 3], "ies") == 0) {
        strcpy(bufx, buf);
        strcpy(&bufx[len - 3], "y");
#       ifdef DB
        printf("    Unpluralize >%s<\n", bufx);
#       endif /* DB */
        QAppend(&Queue, bufx);
    }
    if (len == PWLEN && strcmp(&buf[PWLEN - 2], "ie") == 0) {
        strcpy(bufx, buf);
        strcpy(&bufx[PWLEN - 2], "y");
#       ifdef DB
        printf("    Unpluralize >%s<\n", bufx);
#       endif /* DB */
        QAppend(&Queue, bufx);
    }
    if (len == PWLEN && buf[PWLEN - 1] == 'i') {
        strcpy(bufx, buf);
        bufx[PWLEN - 1] = 'y';
#       ifdef DB
        printf("    Unpluralize >%s<\n", bufx);
#       endif /* DB */
        QAppend(&Queue, bufx);
    }

    /*------------------------------------------------------------------------*
    | Unreverse                                                               |
    *------------------------------------------------------------------------*/

    for (i = 0; i < len; i++)
        bufx[i] = s[strlen(s) - i - 1];
    bufx[len] = '\0';
#   ifdef DB
    printf("    Ureverse >%s<\n", bufx);
#   endif /* DB */
    QAppend(&Queue, bufx);

    /*------------------------------------------------------------------------*
    | Unduplicate                                                             |
    *------------------------------------------------------------------------*/

    strcpy(bufx, buf);
    if (len < PWLEN && len%2 == 0) {
        for (j = 0, k = len/2; buf[k] == buf[j]; j++, k++) ;
        if (k == len) {
            bufx[len/2] = '\0';
#           ifdef DB
            printf("    Unduplicate >%s<\n", bufx);
#           endif /* DB */
            QAppend(&Queue, bufx);
        }
    }
    else if (len == PWLEN) {
        for (i = PWLEN/2; i < PWLEN; i++) {
            for (j = 0, k = i; buf[k] == buf[j]; j++, k++) ;
            if (k == PWLEN) {
                bufx[i] = '\0';
#               ifdef DB
                printf("    Unduplicate >%s<\n", bufx);
#               endif /* DB */
                QAppend(&Queue, bufx);
            }
        }
    }

    /*------------------------------------------------------------------------*
    | Unreflect                                                               |
    *------------------------------------------------------------------------*/

    if (len < PWLEN) {
        for (j = 0, k = len - 1; k >= j &&  buf[k] == buf[j]; j++, k--) ;
        if (k < j) {
            strcpy(bufx, buf);
            bufx[j] = '\0';
#           ifdef DB
            printf("    Unreflect >%s<\n", bufx);
#           endif /* DB */
            QAppend(&Queue, bufx);
        }
    }
    else {      /* len == PWLEN */
        for (i = 0; i < PWLEN - 1; i++) {
            for (j = i, k = PWLEN - 1; k >= j && buf[k] == buf[j]; j++, k--) ;
            if (k < j) {
                strcpy(bufx, buf);
                bufx[j] = '\0';
#               ifdef DB
                printf("    Unreflect >%s<\n", bufx);
#               endif /* DB */
                QAppend(&Queue, bufx);
            }
        }
    }

    /*------------------------------------------------------------------------*
    | Undo Mycroft transforms and other letter-substitutions		      |
    *------------------------------------------------------------------------*/

    Mycroft(buf);
    while (ss = Mycroft(0)) {
#       ifdef DB
        printf("    Mycroft >%s<\n", ss);
#       endif /* DB */
        QAppend(&Queue, ss);
    }

    /*------------------------------------------------------------------------*
    | End of the story                                                        |
    *------------------------------------------------------------------------*/

    return 0;
}

/*----------------------------------------------------------------------------*
| CCStrI                                                                      |
*----------------------------------------------------------------------------*/

char*
CCStrI(iterator)
char* (*iterator)();
{
    static int initialized = 0;
    static char* (*iter)();
    char* s;

    /*------------------------------------------------------------------------*
    | Initialization                                                          |
    *------------------------------------------------------------------------*/

    if (iterator) {
        iter = iterator;
        return 0;
    }

    /*------------------------------------------------------------------------*
    | Iteration: loop until there's a string to return                        |
    *------------------------------------------------------------------------*/

    while (1) {
        if (!initialized) {
            s = iter(0);
            if (s == 0) {
                initialized = 0;
                return 0;
            }
            CCStr(s);
            initialized = 1;
        }
        if (s = CCStr(0))
            return s;
        else
            initialized = 0;
    }
}
