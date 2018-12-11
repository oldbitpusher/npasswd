/*
 * This program is copyright Alec Muffett 1993. The author disclaims all 
 * responsibility or liability with respect to it's usage or its effect 
 * upon hardware or computer systems, and maintains copyright as set out 
 * in the "LICENCE" document which accompanies distributions of Crack v4.0 
 * and upwards.
 */

#ifndef lint
static char sccsid[] = "@(#)teststr.c	1.4 9/22/98 (cc.utexas.edu)";
#endif

#include "packer.h"

int
main (argc, argv)
int	argc;
char	**argv;
{
    c_int32 i;
    PWDICT *pwp;
    char buffer[STRINGSIZE];

    if (argv[1]) {
	    if (!(pwp = PWOpen (argv[1], "r")))
	    {
		perror ("PWOpen");
		return (-1);
	    }
	    printf("Using dictionary %s\n", argv[1]);
    } else {
#ifdef	CRACKLIB_DICTPATH
	    if (!(pwp = PWOpen (CRACKLIB_DICTPATH, "r")))
	    {
		perror ("PWOpen");
		return (-1);
	    }
	    printf("Using dictionary %s\n", CRACKLIB_DICTPATH);
#else
	
	    printf("Usage: %s dictionary-path\n", argv[0]);
	    exit(1);
#endif
    }

    printf("enter dictionary words, one per line...\n");

    while (fgets (buffer, STRINGSIZE, stdin))
    {
    	c_int32 i;

	Chop(buffer);
	i = FindPW(pwp, buffer);
	printf ("%s: %lu%s\n", buffer, i, (i==PW_WORDS(pwp) ? " **** NOT FOUND ****" : ""));
    }

    return (0);
}
