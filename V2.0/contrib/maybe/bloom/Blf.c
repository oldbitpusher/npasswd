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
| Blf.c									      |
| Bloom filter machinery						      |
*----------------------------------------------------------------------------*/

#include <stdio.h>
#include <math.h>
#include "Global.h"
#include "MakeBlf.h"
#include "Hash.h"
#include "BitArray.h"
#include "Blf.h"

int PrintEntry;

static int nBytes;
static int nHashes;
static int nEntries;

/*----------------------------------------------------------------------------*
| BlfCon								      |
*----------------------------------------------------------------------------*/

void
BlfCon(nbytes, nhashes)
int nbytes;
int nhashes; 
{
    BitArrayCon(nbytes);
    nBytes = nbytes;
    nHashes = nhashes;
    nEntries = 0;
}

/*----------------------------------------------------------------------------*
| BlfRead								      |
*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
| File has 1 line for nHashes,						      |
|	   1 line for Entries,						      |
|	   followed by the bitarray					      |
*----------------------------------------------------------------------------*/

void BlfRead(fi)
FILE* fi;
{
    fscanf(fi, "%d%d", &nHashes, &nEntries);
    while (getc(fi) != '\n') ;
    BitArrayRead(fi);
}

/*----------------------------------------------------------------------------*
| BlfWrite								      |
*----------------------------------------------------------------------------*/

void BlfWrite(fi)
FILE* fi;
{
    fprintf(fi, "%d\n%d\n", nHashes, nEntries);
    BitArrayWrite(fi);
}

/*----------------------------------------------------------------------------*
| BlfProbe								      |
*----------------------------------------------------------------------------*/

int
BlfProbe(s)
char* s;
{
    unsigned int n;
    int i;

    Hash(s);
    for (i = 0; i < nHashes; i++) {
        n = Hash(0);
        if (!BitArrayProbe(n)) return 0;
    }
    return 1;
}

/*----------------------------------------------------------------------------*
| BlfSet								      |
*----------------------------------------------------------------------------*/

int
BlfSet(s)
char* s;
{
    int isNew = 0;
    unsigned int n;
    int i;

    Hash(s);
    for (i = 0; i < nHashes; i++) {
        n = Hash(0);
        if (BitArraySet(n)) isNew = 1;
    }

    nEntries += isNew;
    if (PrintEntry && isNew)
	 puts(s);
    return isNew;
}

/*----------------------------------------------------------------------------*
| BlfSetI								      |
*----------------------------------------------------------------------------*/

void
BlfSetI(pnew, pgross, suffix, iterator)
int* pnew;
int* pgross;
char* suffix;
char* (*iterator)();
{
    char* s;
    char buf[MAXSTRING + 3];

    *pgross = *pnew = 0;
    while (s = iterator(0)) {
	strcpy(buf, s);
	strcat(buf, suffix);
        (*pgross)++;
        *pnew += BlfSet(buf);
    }
}

/*----------------------------------------------------------------------------*
| BlfReturnNentries							      |
*----------------------------------------------------------------------------*/

int
BlfReturnNEntries()
{
    return(nEntries);
}

/*----------------------------------------------------------------------------*
| BlfFalsePos								      |
*----------------------------------------------------------------------------*/

double
BlfFalsePos()
{
    int nbytes;
    double load;
    double x;

    nbytes = BitArrayReturnNBytes();
    load = (double)nHashes * (double)nEntries / (double)(BITSPERBYTE * nbytes);
    if (load > 0) {
	x = log(1.0 - exp(-load));
        return exp((double)nHashes * x);
    }
    else
        return 0.0;
}
