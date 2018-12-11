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
| Mycroft.c								      |
| Iterator for inverse of Crack 4.1's "Mycroft" transforms		      |
*----------------------------------------------------------------------------*/

#include "Global.h"

static struct {
    char* letters;
    int nlet;
} Transform[] = {
    "0oO", 3,
    "1ilI", 4,
    "2a", 2,
    "3e", 2,
    "4ah", 3,
    "$s", 2,
     0, 0
};

static struct {
    int flag;           /* 1 if transformable character */
    int tset;
    int index;
} T[PWLEN+1];

static char Buf[PWLEN+1];

static int Any;         /* 1 if any transformable character */

char* Mycroft(s)
char* s;
{
    int i, j;

    /*------------------------------------------------------------------------*
    | Initialize							      |
    *------------------------------------------------------------------------*/

    if (s) { 
        Any = 0;
	if (!s[0])
	    return;
        for (i = 0; s[i]; i++) {
            Buf[i] = s[i];
            for (j = 0; Transform[j].letters; j++)
                if (Transform[j].letters[0] == s[i])
                    break;
            if (Transform[j].letters) {
                T[i].flag = 1;
                Any = 1;
                T[i].tset = j;
                T[i].index = 0;
            }
            else
                T[i].flag = 0;
        }
        Buf[i] = '\0';
    }

    /*------------------------------------------------------------------------*
    | Iterate								      |
    *------------------------------------------------------------------------*/

    else {
        if (!Any)
            return 0;
        for (i = 0; Buf[i]; i++) {
            if (!T[i].flag)
                continue;
            else if (++T[i].index >= Transform[T[i].tset].nlet) {
                T[i].index = 0;
                Buf[i] = Transform[T[i].tset].letters[0];
                continue;
            }
            else {
                Buf[i] = Transform[T[i].tset].letters[T[i].index];
                break;
            }
        }
        if (Buf[i])
            return Buf;
        else
            return 0;
    }
}
