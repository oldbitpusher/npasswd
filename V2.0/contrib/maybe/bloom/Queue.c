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
| Queue.c								      |
*----------------------------------------------------------------------------*/

#include <malloc.h>
#include <string.h>
#include "Global.h"
#include "Queue.h"

/*----------------------------------------------------------------------------*
| QAppend								      |
| to the end								      |
*----------------------------------------------------------------------------*/

void
QAppend(q, s)
QUEUE* q;
char* s;
{
    char* p;
    NODE* n;

    p = malloc(strlen(s) + 1);
    strcpy(p, s);
    n = (NODE*)malloc(sizeof(NODE));
    n->s = p;
    n->next = 0;
    if (q->last) {
        q->last->next = n;
        q->last = n;
    }
    else
        q->first = q->last = n;
}

/*----------------------------------------------------------------------------*
| QHead									      |
| Delete the first member and return it as a static string		      |
| If the queue is empty, return 0					      |
*----------------------------------------------------------------------------*/

char*
QHead(q)
QUEUE* q;
{
    NODE* temp;
    char* p;
    static char s[MAXSTRING + 1];

    if (!q)
        return 0;
    if (!q->first)
        return 0;
    p = q->first->s;
    strncpy(s, p, MAXSTRING);
    free(p);
    temp = q->first->next;
    free(q->first);
    q->first = temp;
    if (q->first == 0)
        q->last = 0;

    return s;
}
