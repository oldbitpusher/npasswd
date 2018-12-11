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
| Hash.c                                                                      |
| Multiple hash codes: 32-bit integers from ascii strings                     |
*----------------------------------------------------------------------------*/

#include "Hash.h"

/*----------------------------------------------------------------------------*
| cf.  Cormen, Thomas H., Leiserson, Charles E., and Rivest, Ronald L.        |
|      Introduction to Algorithms.                                            |
|      Cambridge, MA, MIT Press, 1990.                                        |
*----------------------------------------------------------------------------*/

#define A1 0x9e3779b9
#define A2 0xbb67ae87

/*----------------------------------------------------------------------------*
| X1 = (sqrt(5)-1)/2                                                          |
| X2 = sqrt(3) - 1                                                            |
|                                                                             |
| A1 = (int)(X1 * 2^32)                                                       |
| A2 = (int)(X2 * 2^32) + epsilon (to make it odd and relatively prime to A1) |
|                                                                             |
| Cf. Knuth, Art of Computer Programming, v 3 p 508ff                         |
*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
| PUBLIC:                                                                     |
| Hash: hash iterator                                                         |
|                                                                             |
| PRIVATE:                                                                    |
| hashs: integer from string                                                  |
*----------------------------------------------------------------------------*/

unsigned int hashs();           /* unsigned int hashs(char*); */

static unsigned int H1;
static unsigned int H2;

/*----------------------------------------------------------------------------*
| Hash                                                                        |
*----------------------------------------------------------------------------*/

unsigned int
Hash(s)
char* s;
{
    unsigned int u;

    /*------------------------------------------------------------------------*
    | Initialize							      |
    *------------------------------------------------------------------------*/

    if (s) {
        u = hashs(s);
        H1 = u * A1;
        H2 = u * A2;
        return 0;
    }

    /*------------------------------------------------------------------------*
    | Iterate								      |
    *------------------------------------------------------------------------*/

    else {
        u = H1;
        H1 += H2;
        return u;
    }
}

/*----------------------------------------------------------------------------*
| hashs                                                                       |
*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
| An array of arbitrary large numbers.                                        |
|                                                                             |
| There's nothing magic about these.  In fact, they're the first numbers      |
| produced by random(3) after calling srandom with seed 1.  Billions of       |
| other choices would have worked just as well.                               |
*----------------------------------------------------------------------------*/

static unsigned int R[] = {
    0x7be9c1bd, 0x088aa102, 0x3d38509b, 0x746b9fbe,
    0x2d04417f, 0x775d4351, 0x53c48d96, 0x02b26e0b,
    0x418fedcf, 0x19dbc19e, 0x78512adb, 0x1a1f5e2b,
    0x307d7761, 0x6584c1f0, 0x24e3c36f, 0x2232310f,
    0x2dac5ceb, 0x106e8b5a, 0x5a05a938, 0x5e6392b6,
    0x66b90348, 0x75264901, 0x4174f402, 0x618b18a4,
    0x3a6ab4bf, 0x3c4bc289, 0x2657a9a9, 0x4e68589b,
    0x09648aa6, 0x3fc489bb, 0x1c1b715c, 0x054e4c63
};

static unsigned int
hashs(s)
char* s;
{
    unsigned int u = 0;
    unsigned int* ip = R;

    while (*s) {
        u += *ip++ * *s++;
        if (ip >= R + sizeof(R)) ip = R;
    }
    if (u%2 == 0) u++;          /* make sure it's odd */

    return u;
}
