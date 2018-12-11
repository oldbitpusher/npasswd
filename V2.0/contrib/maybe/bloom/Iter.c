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
| Iter.c								      |
*----------------------------------------------------------------------------*/

#include <string.h>
#include <stdio.h>
#include "Global.h"
#include "Iter.h"

/*----------------------------------------------------------------------------*
| ArgIter								      |
| (Initialize with argv)						      |
*----------------------------------------------------------------------------*/

char*
ArgIter(argv)
char** argv;
{
    static char** v;
    static char s[MAXSTRING + 1];

    if (argv)
        v = argv;
    else if (*v) {
        strncpy(s, *v++, MAXSTRING);
        return s;
    }
    return 0;
}

/*----------------------------------------------------------------------------*
| FileIter								      |
| (Initialize with filename)						      |
*----------------------------------------------------------------------------*/

char*
FileIter(filename)
char* filename;
{
    static FILE* fi;
    static char s[MAXLINE + 1];
    char* p;
    char c;

    if (filename) {
        if (!(fi = fopen(filename, "r"))) {
            fprintf(stderr, "Can't open file '%s'\n", filename);
            exit(1);
        }
    }
    else while (1) {
	if (fgets(s, sizeof(s), fi) == 0) {
	    fclose(fi);
	    return 0;
	}
	else if (p = strchr(s, '\n'))
	    *p = '\0';
	else
	    while ((c = getc(fi)) != '\n' && c != EOF) ;
	if (s[0] && s[0] != '#')
	    return(s);
    }
}

/*----------------------------------------------------------------------------*
| FileListIter								      |
| (Initialize with iterator for filenames)				      |
*----------------------------------------------------------------------------*/

char*
FileListIter(iter)
char* (*iter)();
{
    static char* (*FIter)();
    char* filename;
    char* s;


    if (iter) {
	FIter = iter;
	return 0;
    }

    while ((s = FileIter(0)) == 0) {
	filename = FIter(0);
	if (!filename)
	    return 0;
	FileIter(filename);
    }
}

/*----------------------------------------------------------------------------*
| TextWordIter								      |
| (Initialize with char pointer to text)				      |
*----------------------------------------------------------------------------*

#define ALNUM(c) (isalnum(c) || (c) == '_' || (c) == '-')

char*
TextWordIter(filename)
char* filename;
{
    static char* s;
    static char* p;
    static char word[MAXSTRING + 1];
    char* q;
    int len;

    if (filename) {
        FileIter(filename);
	return 0;
    }

    if (p)
	while (*p && !ALNUM(*p))
	    p++;

    if (!p || !*p) {
        s = FileIter(0);
        if (!s)
            return 0;
        p = s;
    }

    /*------------------------------------------------------------------------*
    | p points to the beginning of a word.				      |
    | make q point 1 after the end.					      |
    | copy the first characters of the word.				      |
    *------------------------------------------------------------------------*

    for (q = p; ALNUM(*q); q++) ;
    len = q - p;
    if (len > MAXSTRING)
        len = MAXSTRING;
    strncpy(word, p, len);
    word[len] = '\0';
    p = q;

    return word;
}
*/
