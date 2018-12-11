/*
 *	makedict - Make DBM version of password dictionary
 */

#ifndef lint
static char sccsid[] = "@(#)makedict.c	1.3 1/27/92 (cc.utexas.edu) /tmp_mnt/usr/share/src/private/ut/share/bin/passwd/checkpassword/old/SCCS/s.makedict.c";
#endif

#include <ndbm.h>
#include <sys/file.h>
#include <stdio.h>

char	line[BUFSIZ];		/* Input buffer */

main(argc, argv)
int	argc;
char	*argv[];
{
	DBM	*dp;		/* Database pointer */
	int	recs = 0;	/* Record counter */
	datum	d,		/* Data datum */
		k;		/* Key datum */
#ifdef	SYSV
#define index strchr
#endif
	extern char	*index();

	if (argc < 2) {
		printf("Usage: makedict dbm-file < input\n");
		exit(1);
	}
	dp = dbm_open(argv[1], O_RDWR, 0);
	if (dp == 0) {
		if ((dp = dbm_open(argv[1], O_RDWR|O_CREAT, 0644)) == 0) {
			perror(argv[1]);
			exit(1);
		}
	}
	while (!feof(stdin)) {
		char	*p;

		(void) fgets(line, sizeof(line), stdin);
		if (p = index(line, '\n'))
			*p = 0;
		d.dptr = line;
		d.dsize = strlen(line);
		dbm_store(dp, d, d, DBM_INSERT);
		recs++;
	}
	dbm_close(dp);
	printf("%s built, %d records\n", argv[1], recs);
}
/* End makedict.c */
