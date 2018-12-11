h20202
s 00004/00039/00049
d D 1.3 92/01/27 16:51:53 clyde 3 2
c Remove "MDBM" hooks.
e
s 00004/00000/00084
d D 1.2 89/10/04 09:24:49 clyde 2 1
c Add a System V string routine define
e
s 00084/00000/00000
d D 1.1 89/05/18 10:01:04 clyde 1 0
c date and time created 89/05/18 10:01:04 by clyde
e
u
U
t
T
I 1
/*
 *	makedict - Make DBM version of password dictionary
 */

#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu) %P%";
#endif

D 3
#ifdef  MDBM
#include "mdbm.h"
#define DBM		struct mdbm
#define DBM_CLOSE	mdbm_close
#endif

#ifdef	NDBM
E 3
#include <ndbm.h>
D 3
#define DBM_CLOSE	dbm_close
#endif

I 2

E 2
/*
 *	What cpp needs is a way for the programmer to issue an error
 *	message here and abort compilation
 */
#if	!defined(MDBM) && !defined(NDBM)
	"Either NDBM or MDBM must be defined"
#endif

E 3
#include <sys/file.h>
#include <stdio.h>

D 3
char	line[80];		/* Input buffer */
E 3
I 3
char	line[BUFSIZ];		/* Input buffer */
E 3

main(argc, argv)
int	argc;
char	*argv[];
{
	DBM	*dp;		/* Database pointer */
	int	recs = 0;	/* Record counter */
	datum	d,		/* Data datum */
		k;		/* Key datum */
I 2
#ifdef	SYSV
#define index strchr
#endif
E 2
D 3
	char	*index();
E 3
I 3
	extern char	*index();
E 3

	if (argc < 2) {
		printf("Usage: makedict dbm-file < input\n");
		exit(1);
	}
D 3
#ifdef	NDBM
E 3
	dp = dbm_open(argv[1], O_RDWR, 0);
	if (dp == 0) {
		if ((dp = dbm_open(argv[1], O_RDWR|O_CREAT, 0644)) == 0) {
			perror(argv[1]);
			exit(1);
		}
	}
D 3
#endif
#ifdef	MDBM
	dp = mdbm_open(argv[1], O_RDWR, (int *)0, (int *)0, (char *)0);
	if (dp == 0) {
		if ((dp = mdbm_open(argv[1], O_RDWR|O_CREAT, 0644,
		     (int *)0, (int *)0, (char *)0)) == 0) {
			perror(argv[1]);
			exit(1);
		}
	}
#endif
E 3
	while (!feof(stdin)) {
		char	*p;

		(void) fgets(line, sizeof(line), stdin);
		if (p = index(line, '\n'))
			*p = 0;
		d.dptr = line;
		d.dsize = strlen(line);
D 3
#ifdef	MDBM
		mdbm_store(dp, d, d, 1);
#endif
#ifdef	NDBM
E 3
		dbm_store(dp, d, d, DBM_INSERT);
D 3
#endif
E 3
		recs++;
	}
D 3
	DBM_CLOSE(dp);
E 3
I 3
	dbm_close(dp);
E 3
	printf("%s built, %d records\n", argv[1], recs);
}
I 3
/* End %M% */
E 3
E 1
