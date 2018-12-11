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
| MakeBlf.c                                                                   |
| Make a Bloom filter from string list files                                  |
*----------------------------------------------------------------------------*/

#include <stdio.h>
#include "Global.h"
#include "MakeBlf.h"
#include "CFStr.h"
#include "Iter.h"
#include "Blf.h"

char* Usage = 
"MakeBlf [-lp] filename nbytes nhashes file ...\n\
or     MakeBlf [-lp] filename + file ...";

int Literal = 0;

main(argc, argv)
int argc;
char** argv;
{
    extern int optind;
    extern char* optarg;
    int nbytes;
    int nhashes;
    int nentries;
    int ngross;
    int nnew;
    char* filename;
    FILE* fi;
    int c;

    while ((c = getopt(argc, argv, "lp")) != -1) {
	switch (c) {
	    case 'l': Literal = 1;	 break;
	    case 'p': PrintEntry = 1;	 break;
	    case '?': 
		fprintf(stderr, "Usage: %s\n", Usage);
		exit(1);
	}
    }
    filename = argv[optind];
    argv += optind;

    /*------------------------------------------------------------------------*
    | Add to existing filter						      |
    *------------------------------------------------------------------------*/

    if (**++argv == '+') {
        if (!(fi = fopen(filename, "r"))) {
            fprintf(stderr, "Can't open file '%s' for reading\n", filename);
            exit(1);
        }
        BlfRead(fi, &nhashes, nentries);
        fclose(fi);
        if (!(fi = fopen(filename, "w"))) {
            fprintf(stderr, "Can't open file '%s' for writing\n", filename);
            exit(1);
        }
    }

    /*------------------------------------------------------------------------*
    | Create new filter                                                       |
    *------------------------------------------------------------------------*/

    else {
        if (sscanf(*argv, "%d", &nbytes)  != 1 ||
              sscanf(*++argv, "%d", &nhashes) != 1) {
            fprintf(stderr, "%s\n", Usage);
            exit(1);
        }
        if (!(fi = fopen(filename, "w"))) {
            fprintf(stderr, "Can't open file '%s' for writing\n", filename);
            exit(1);
        }
        BlfCon(nbytes, nhashes);
    }

    /*------------------------------------------------------------------------*
    | Add words                                                               |
    *------------------------------------------------------------------------*/

    while (*++argv) {
        FileIter(*argv);
        if (Literal)
            BlfSetI(&nnew, &ngross, "", FileIter);
        else {
            CFStrI(FileIter);
            BlfSetI(&nnew, &ngross, "", CFStrI);
        }
        printf("%7d/%-7d %7d %.5f %s\n",
            nnew,
            ngross,
            BlfReturnNEntries(),
            BlfFalsePos(),
            *argv
        );
	fflush(stdout);
    }

    /*------------------------------------------------------------------------*
    | All done								      |
    *------------------------------------------------------------------------*/

    BlfWrite(fi);
}
