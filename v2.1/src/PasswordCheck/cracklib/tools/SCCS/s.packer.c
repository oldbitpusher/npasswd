h43642
s 00002/00002/00061
d D 1.2 98/09/22 11:06:32 clyde 2 1
c Rename intNN to c_intNN to avoid type conflicts with Digital UNIX 4.0d
e
s 00062/00000/00000
d D 1.1 93/06/28 09:19:12 clyde 1 0
c date and time created 93/06/28 09:19:12 by clyde
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
static char utid[] = "%W% %G% (cc.utexas.edu)";

#include "packer.h"

int
main(argc, argv)
    int argc;
    char *argv[];
{
D 2
    int32 readed;
    int32 wrote;
E 2
I 2
    c_int32 readed;
    c_int32 wrote;
E 2
    PWDICT *pwp;
    char buffer[STRINGSIZE];

    if (argc <= 1)
    {
	fprintf(stderr, "Usage:\t%s dbname\n", argv[0]);
	return (-1);
    }

    if (!(pwp = PWOpen(argv[1], "w")))
    {
	perror(argv[1]);
	return (-1);
    }

    wrote = 0;

    for (readed = 0; fgets(buffer, STRINGSIZE, stdin); /* nothing */)
    {
    	readed++;

	buffer[MAXWORDLEN - 1] = '\0';

	Chop(buffer);

	if (!buffer[0])
	{
	    fprintf(stderr, "skipping line: %lu\n", readed);
	    continue;
	}

	if (PutPW(pwp, buffer))
	{
	    fprintf(stderr, "error: PutPW '%s' line %luy\n", buffer, readed);
	}

	wrote++;
    }

    PWClose(pwp);

    printf("%lu %lu\n", readed, wrote);

    return (0);
}
E 1
