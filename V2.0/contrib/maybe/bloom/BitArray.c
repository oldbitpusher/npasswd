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
| BitArray.c								      |
*----------------------------------------------------------------------------*/

#include "Global.h"
#include "BitArray.h"

/*----------------------------------------------------------------------------*
| PUBLIC:								      |
|									      |
| BitArrayCon:	  Construct empty array					      |
| BitArrayRead:	  Load from file					      |
| BitArrayWrite:  Save to file						      |
| BitArrayProbe:  Is bit set?						      |
| BitArraySet:	  Set a bit (returns 1 if not already set)		      |
| BitArrayGetNSet: Calculate nSet					      |
| BitArrayReturnNSet:   Give it back					      |
| BitArrayReturnNBytes: Give it back					      |
| BitArrayDump:	  For debug						      |
|									      |
| PRIVATE:								      |
|									      |
| log2									      |
| exp2									      |
| roundUp								      |
*----------------------------------------------------------------------------*/

int log2();                     /* int log2(unsigned int); */
unsigned int exp2();            /* unsigned int exp2(int); */
unsigned int roundUp();         /* unsigned int roundUp(unsigned int); */

static int nBytes;              /* size */
static int nSet;                /* number of bits set */
static int modShift;            /* shift 32-bit integer to fit size */
static unsigned char* A;        /* pointer to array */

/*----------------------------------------------------------------------------*
| BitArrayCon								      |
*----------------------------------------------------------------------------*/

void
BitArrayCon(nbytes)
int nbytes;
{
    nBytes = roundUp(nbytes);
    modShift = WORDLENGTH - log2(nBytes) - LOGBYTE;
    nSet = 0;
    A = (unsigned char*)malloc(nBytes);
}

/*----------------------------------------------------------------------------*
| BitArrayRead								      |
*----------------------------------------------------------------------------*/

void
BitArrayRead(fi)
FILE* fi;
{
    /* File format: ascii line containing nBytes, followed by bitmap */

    fscanf(fi, "%d", &nBytes); while (getc(fi) != '\n') ;
    modShift = WORDLENGTH - log2(nBytes) - LOGBYTE;
    A = (unsigned char*)malloc(nBytes);

    if (fread(A, 1, nBytes, fi) != nBytes) {
        fprintf(stderr, "BitArray: read error\n");
        exit(1);
    }

    BitArrayGetNSet();
}

/*----------------------------------------------------------------------------*
| BitArrayWrite								      |
*----------------------------------------------------------------------------*/

void
BitArrayWrite(fi)
FILE* fi;
{
    fprintf(fi, "%d\n", nBytes);
    if (fwrite(A, 1, nBytes, fi) != nBytes) {
        fprintf(stderr, "Write error\n");
        exit(1);
    }

}

/*----------------------------------------------------------------------------*
| BitArrayProbe								      |
*----------------------------------------------------------------------------*/

int
BitArrayProbe(n)
unsigned int n;
{
    int mask;

    n >>= modShift;
    mask = 01 << (n & LOGBYTEMASK);
    n >>= LOGBYTE;
    /*DB printf("n=%x A[n]=%x mask=%x return %d\n", n, A[n], mask, A[n] & mask); */
    return ( (A[n] & mask) != 0 );
}

/*----------------------------------------------------------------------------*
| BitArraySet								      |
*----------------------------------------------------------------------------*/

int
BitArraySet(n)
unsigned int n;
{
    int mask;
    int i;

    n >>= modShift;
    mask = 01 << (n & LOGBYTEMASK);
    n >>= LOGBYTE;
    i = ( (A[n] & mask) == 0 );
    A[n] |= mask;
    nSet += i;

    return i;
}

/*----------------------------------------------------------------------------*
| BitArrayGetNSet							      |
*----------------------------------------------------------------------------*/

void
BitArrayGetNSet()
{
    int t[256];
    unsigned char* limit;
    unsigned char* ip;
    int a;
    int i;

    for (i = 0; i < 256; i++) {
	t[i] = 0;
        for (a = i; a; a >>= 1)
            t[i] += a & 0x1;
    }

    nSet = 0;
    limit = A + nBytes;
    for (ip = A; ip < limit; ip++)
	nSet += t[*ip];
}

/*----------------------------------------------------------------------------*
| BitArrayReturnNBytes							      |
*----------------------------------------------------------------------------*/

int
BitArrayReturnNBytes()
{
    return nBytes;
}

/*----------------------------------------------------------------------------*
| BitArrayReturnNSet							      |
*----------------------------------------------------------------------------*/

int
BitArrayReturnNSet()
{
    return nSet;
}

/*----------------------------------------------------------------------------*
| BitArrayDump								      |
*----------------------------------------------------------------------------*/

void
BitArrayDump()
{
    unsigned char* ip;
    unsigned char* limit;
    int lomask = 0x0F;
    int i, j, k;

    ip = A;
    limit = A + nBytes;
    while (1) {
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 4; j++) {
                for (k = 0; k < 4; k++) {
                    if (ip >= limit) {
                        putchar('\n');
                        return;
                    }
                    printf("%01x%01x", *ip & lomask, *ip >> 4);
                    ip++;
                }
                putchar(' ');
            }
            putchar(' ');
        }
        putchar('\n');
    }
}

/*----------------------------------------------------------------------------*
| log2									      |
*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
| unsigned int --> int, truncating					      |
| returns -1 if input is = 0						      |
*----------------------------------------------------------------------------*/

static int
log2(n)
unsigned int n;
{
    int i;
    
    i = -1;
    while (n) {
        n >>= 1;
        i++;
    }
    
    return i;
}

/*----------------------------------------------------------------------------*
| exp2									      |
*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
| int --> unsigned int							      |
| no check for overflow							      |
*----------------------------------------------------------------------------*/

static unsigned int 
exp2(i)
int i;
{
    unsigned int n;
    
    n = 1;
    while (i-- > 0) n <<= 1;

    return n;
}

/*----------------------------------------------------------------------------*
| roundUp								      |
|									      |
| to power of 2								      |
*----------------------------------------------------------------------------*/

static unsigned int 
roundUp(n)
unsigned int n;
{
    unsigned int nn;
    
    nn = exp2(log2(n));
    if (nn != n) nn *= 2;

    return nn;
}
