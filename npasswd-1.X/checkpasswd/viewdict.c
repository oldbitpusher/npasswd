
/* --------------------------------------------------------------------  */
/*                                                                       */
/*                         Author: Clyde Hoover                          */
/*                          Computation Center                           */
/*                   The University of Texas at Austin                   */
/*                          Austin, Texas 78712                          */
/*                         clyde@emx.utexas.edu                          */
/*                   uunet!cs.utexas.edu!ut-emx!clyde                    */
/*                                                                       */
/*This code may be distributed freely, provided this notice is retained. */
/*                                                                       */
/* --------------------------------------------------------------------  */
/*
 *	viewdict - view DBM dictionary data base
 */
#ifndef lint
static char sccsid[] = "@(#)viewdict.c	1.2 1/27/92 (cc.utexas.edu) /tmp_mnt/usr/share/src/private/ut/share/bin/passwd/checkpasswd/SCCS/s.viewdict.c";
#endif

#include <ndbm.h>
#include <sys/file.h>
#include <stdio.h>

main(argc, argv)
int	argc;
char	*argv[];
{
	DBM	*dp;		/* Database pointer */
	datum	k;		/* Key datum */
	char	t[128];		/* Output buffer */

	if (argc < 2) {
		printf("Usage: viewdict dbm-dictionary\n");
		exit(1);
	}
	dp = dbm_open(argv[1], O_RDWR, 0);
	if (dp == 0) {
		perror(argv[1]);
		exit(1);
	}
	printf("Dictionary %s\n", argv[1]);
	for (k = dbm_firstkey(dp); k.dptr != 0; k = dbm_nextkey(dp)) {
		(void) strncpy(t, k.dptr, k.dsize);
		t[k.dsize] = 0;
		printf("%s\n", t);
	}
	exit(0);
}
/* End viewdict.c */
