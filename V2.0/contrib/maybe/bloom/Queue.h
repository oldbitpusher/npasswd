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
| Queue.h								      |
| A queue is an ordinary singly-linked list except that			      |
|  +  the only element you can retrieve is the first			      |
|  +  retrieving that element deletes it				      |
*----------------------------------------------------------------------------*/

#ifndef _Queue
#define _Queue

struct node {
    char* s;
    struct node * next;
};

typedef struct node NODE;

struct queue {
    NODE* first;
    NODE* last;
};

typedef struct queue QUEUE;

void   QDelete();                       /* void   QDelete(QUEUE*); */
void   QAppend();                       /* void   QAppend(QUEUE*, char*); */
char*  QHead();                         /* char*  QHead(QUEUE*); */

#endif /* ! _Queue */
