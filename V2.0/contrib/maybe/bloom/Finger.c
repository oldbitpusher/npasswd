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
| Finger.c								      |
| Add words derived from text in password file and "finger" files to a filter |
|									      |
| Words from password file get {p or {P suffix, words from finger ("dot")     |
|     files get {f or {F						      |
*----------------------------------------------------------------------------*/

#include <stdio.h>
#include <pwd.h>
#include <malloc.h>
#include "Global.h"
#include "Blf.h"
#include "CFText.h"
#include "Finger.h"

char* FingerFiles[] = {         /* list of filenames */
    ".plan",
    ".project",
    ".signature",
    0
};

void
Finger(uid)
int uid;
{
    struct passwd * p;
    int homelen;                        /* length of home dir name */
    char* filename;
    FILE *fi;
    char text[MAXTEXT + 1];
    int nnew;
    int ngross;
    int i;

    if ((p = getpwuid(uid)) == 0)
        return;

    /*------------------------------------------------------------------------*
    | First, the login ID and gecos stuff				      |
    *------------------------------------------------------------------------*/
    
    strcpy(text, p->pw_name);
    strcat(text, " ");
    strcat(text, p->pw_gecos);

    CFText(text);
    BlfSetI(&nnew, &ngross, PASSWD_SUFFIX, CFText);
#ifdef DB
    printf("%7d/%-7d %7d %.5f %s\n",
        nnew,
        ngross,
        BlfReturnNEntries(),
        BlfFalsePos(),
        "login ID and gecos"
    );
#endif DB

    /*------------------------------------------------------------------------*
    | Now the dotfiles							      |
    *------------------------------------------------------------------------*/

    homelen = strlen(p->pw_dir);
    filename = malloc(homelen + 1 + sizeof(".signature") + 1);
    strcpy(filename, p->pw_dir);
    filename[homelen] = '/';

    for (i = 0; FingerFiles[i]; i++) {
        strcpy(&filename[homelen + 1], FingerFiles[i]);
        if (fi = fopen(filename, "r")) {
            int n;
            n = fread(text, 1, MAXTEXT, fi);
            text[n] = '\0';

            CFText(text);
            BlfSetI(&nnew, &ngross, FINGER_SUFFIX, CFText);
#ifdef DB
            printf("%7d/%-7d %7d %.5f %s\n",
                nnew,
                ngross,
                BlfReturnNEntries(),
                BlfFalsePos(),
                filename
            );
#endif DB
        }
    }
}
