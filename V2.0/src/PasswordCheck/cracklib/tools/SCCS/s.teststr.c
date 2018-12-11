h06213
s 00002/00002/00056
d D 1.4 98/09/22 11:06:36 clyde 4 3
c Rename intNN to c_intNN to avoid type conflicts with Digital UNIX 4.0d
e
s 00006/00000/00052
d D 1.3 96/08/09 16:22:25 clyde 3 2
c Beta 3 development checkin 2
e
s 00021/00005/00031
d D 1.2 93/06/25 14:40:30 clyde 2 1
c Take command line argument for name of dictionary database
e
s 00036/00000/00000
d D 1.1 93/06/25 11:05:39 clyde 1 0
c date and time created 93/06/25 11:05:39 by clyde
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

I 2
#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu)";
#endif

E 2
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
D 4
    int32 i;
E 4
I 4
    c_int32 i;
E 4
    PWDICT *pwp;
    char buffer[STRINGSIZE];

D 2
    if (!(pwp = PWOpen (CRACKLIB_DICTPATH, "r")))
    {
	perror ("PWOpen");
	return (-1);
E 2
I 2
    if (argv[1]) {
	    if (!(pwp = PWOpen (argv[1], "r")))
	    {
		perror ("PWOpen");
		return (-1);
	    }
	    printf("Using dictionary %s\n", argv[1]);
    } else {
I 3
#ifdef	CRACKLIB_DICTPATH
E 3
	    if (!(pwp = PWOpen (CRACKLIB_DICTPATH, "r")))
	    {
		perror ("PWOpen");
		return (-1);
	    }
	    printf("Using dictionary %s\n", CRACKLIB_DICTPATH);
I 3
#else
	
	    printf("Usage: %s dictionary-path\n", argv[0]);
	    exit(1);
#endif
E 3
E 2
    }

    printf("enter dictionary words, one per line...\n");

    while (fgets (buffer, STRINGSIZE, stdin))
    {
D 4
    	int32 i;
E 4
I 4
    	c_int32 i;
E 4

	Chop(buffer);
	i = FindPW(pwp, buffer);
	printf ("%s: %lu%s\n", buffer, i, (i==PW_WORDS(pwp) ? " **** NOT FOUND ****" : ""));
    }

    return (0);
}
E 1
