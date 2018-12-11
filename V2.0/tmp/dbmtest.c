#include <sys/types.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <pwd.h>
#include <ndbm.h>

/*
 *	Arguments:
 *		chr = character to print
 *	Returns:
 *		address of string buffer containing the character
 *		representation of chr.
 *
 *	Compilation:	cc -O -c ctran.c
 */
char *
ctran (c)
char	c;
{
	static char	cbuf[8];
	char	chr = c & 0177;
	char	*p = cbuf;

	if (c & 0200) {		/* Meta char - weird but what the hey */
		*p++ = 'M';
		*p++ = '-';
	}
	if (chr >= ' ' && chr <= '~') {
		*p++ = chr;
		*p++ = 0;
		return (cbuf);
	}
	if (chr == 0177)
		return("RUBOUT");
	*p++ = '^';
	*p++ = chr + '@';
	*p++ = 0;
	return (cbuf);
}

main(c, v)
	int c;
	char **v;
{
	DBM	*pwd;		/* DBM data base passwd */
	char	*cp;		/* Data storage pointer */
	char	*xp;		/* Data storage pointer */
	int	xc;
	datum	key,		/* DBM key datum */
		data;		/* DBM data store datum */

	int	id;
	char	cd[512];

#define	SCOPY(S) cp = (S); while (*cp++ = *xp++)
#define	ICOPY(B) bcopy(xp, (void *)&(B), sizeof(int)); xp += sizeof(int)

	pwd = dbm_open("/etc/passwd", O_RDONLY, 0);
	if (pwd == NULL) {
		perror("DBM open");
		exit(1);
	}

	key.dptr = *++v;
	key.dsize = strlen(key.dptr);

	data = dbm_fetch(pwd, key);
	if (data.dptr == NULL) {
		printf("%s not found\n", *v);
		exit(1);
	}

	for (xc = data.dsize, xp = data.dptr; xc > 0; xp++, xc--) {
		if (*xp == 0)
			printf("[0]\n");
		else
			printf("%s ", ctran(*xp));
	} 
	printf("\n");

	xp = data.dptr;

	SCOPY(cd); printf("pw_name = %s\n", cd);
	SCOPY(cd); printf("pw_passwd = %s\n", cd);
	ICOPY(id); printf("pw_uid = %u\n", id);
	ICOPY(id); printf("pw_gid = %u\n", id);
	ICOPY(id); printf("pw_quota = %u\n", id);
	SCOPY(cd); printf("pw_comment = %s\n", cd);
	SCOPY(cd); printf("pw_gecos = %s\n", cd);
	SCOPY(cd); printf("pw_dir = %s\n", cd);
	SCOPY(cd); printf("pw_shell = %s\n", cd);
}
