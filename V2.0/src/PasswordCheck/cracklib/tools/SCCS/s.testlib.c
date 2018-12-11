h21720
s 00001/00001/00036
d D 1.3 98/09/22 11:06:35 clyde 3 2
c Rename intNN to c_intNN to avoid type conflicts with Digital UNIX 4.0d
e
s 00004/00002/00033
d D 1.2 96/08/09 16:22:27 clyde 2 1
c Beta 3 development checkin 2
e
s 00035/00000/00000
d D 1.1 93/06/28 09:19:14 clyde 1 0
c date and time created 93/06/28 09:19:14 by clyde
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
D 2
main ()
E 2
I 2
main (argc, argv)
	int	argc;
	char	**argv;
E 2
{
D 3
    int32 i;
E 3
I 3
    c_int32 i;
E 3
    char buffer[STRINGSIZE];

    printf("enter potential passwords, one per line...\n");

    while (fgets (buffer, STRINGSIZE, stdin))
    {
    	char *val;
 
	Chop(buffer);

D 2
	val = FascistCheck(buffer, CRACKLIB_DICTPATH);
E 2
I 2
	val = FascistCheck(buffer, argv[1]);
E 2

	if (!val)
	{
		val = "ok";
	}	
	printf ("%s: %s\n", buffer, val);
    }

    return (0);
}
E 1
