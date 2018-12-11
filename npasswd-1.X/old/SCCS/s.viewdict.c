h34261
s 00002/00023/00035
d D 1.2 92/01/27 16:51:51 clyde 2 1
c Remove "MDBM" hooks.
e
s 00058/00000/00000
d D 1.1 89/05/18 10:00:57 clyde 1 0
c date and time created 89/05/18 10:00:57 by clyde
e
u
U
t
T
I 1
/*
 *	viewdict - view DBM dictionary data base
 */
#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu) %P%";
#endif

D 2
#ifdef  MDBM
#include "mdbm.h"
#define DBM		struct mdbm
#endif

#ifdef	NDBM
E 2
#include <ndbm.h>
D 2
#endif

#if	!defined(MDBM) && !defined(NDBM)
	"Either NDBM or MDBM must be defined"
#endif

E 2
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
D 2
#ifdef	NDBM
E 2
	dp = dbm_open(argv[1], O_RDWR, 0);
D 2
#endif
#ifdef	MDBM
	dp = mdbm_open(argv[1], O_RDONLY, 0, (int *)0, (int *)0, (char *)0);
#endif
E 2
	if (dp == 0) {
		perror(argv[1]);
		exit(1);
	}
D 2
/* 	printf("Dictionary %s\n", argv[1]); */
#ifdef	NDBM
E 2
I 2
	printf("Dictionary %s\n", argv[1]);
E 2
	for (k = dbm_firstkey(dp); k.dptr != 0; k = dbm_nextkey(dp)) {
D 2
#endif
#ifdef	MDBM
	for (k = mdbm_firstkey(dp); k.dptr != 0; k = mdbm_nextkey(dp, k)) {
#endif
E 2
		(void) strncpy(t, k.dptr, k.dsize);
		t[k.dsize] = 0;
		printf("%s\n", t);
	}
	exit(0);
}
I 2
/* End %M% */
E 2
E 1
