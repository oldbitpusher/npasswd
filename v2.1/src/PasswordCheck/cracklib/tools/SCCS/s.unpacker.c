h19196
s 00001/00001/00045
d D 1.2 98/09/22 11:06:37 clyde 2 1
c Rename intNN to c_intNN to avoid type conflicts with Digital UNIX 4.0d
e
s 00046/00000/00000
d D 1.1 93/06/28 09:19:17 clyde 1 0
c date and time created 93/06/28 09:19:17 by clyde
e
u
U
f e 0
t
T
I 1
/*
 * This program is copyright Alec Muffett 1993. The author disclaims all 
 * responsibility or liability with respect to it's usage or its effect 
 * upon hardware or computer systems, and maintains copyright as set out 
 * in the "LICENCE" document which accompanies distributions of Crack v4.0 
 * and upwards.
 */

#include "packer.h"

int
main(argc, argv)
    int argc;
    char *argv[];
{
D 2
    int32 i;
E 2
I 2
    c_int32 i;
E 2
    PWDICT *pwp;
    char buffer[STRINGSIZE];

    if (argc <= 1)
    {
	fprintf(stderr, "Usage:\t%s dbname\n", argv[0]);
	return (-1);
    }

    if (!(pwp = PWOpen (argv[1], "r")))
    {
	perror ("PWOpen");
	return (-1);
    }

    for (i=0; i < PW_WORDS(pwp); i++)
    {
    	register char *c;

	if (!(c = (char *) GetPW (pwp, i)))
	{
	    fprintf(stderr, "error: GetPW %d failed\n", i);
	    continue;
	}

	printf ("%s\n", c);
    }

    return (0);
}
E 1
