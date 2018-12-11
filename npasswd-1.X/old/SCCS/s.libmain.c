h63336
s 00010/00001/00102
d D 1.3 92/02/18 16:32:33 clyde 3 2
c 1. Add the option "-P passwd-entry".
c 2. Rename var "standalone" to "PWCK_standalone".
c 3. Add var "PWCK_auxpwline" to impliment #1.
e
s 00002/00001/00101
d D 1.2 89/11/14 17:35:10 clyde 2 1
c Add hook to differentiate between running as library and as standalone application
e
s 00102/00000/00000
d D 1.1 89/05/18 10:05:47 clyde 1 0
c date and time created 89/05/18 10:05:47 by clyde
e
u
U
t
T
I 1
/*
 *	checkpasswd - Library version main routine
 *
 *	Compilation:	ld -r -o checkpasswd.o checkpasswd.o libmain.o
 *		pwck_dict.o pwck_passwd.o pwck_lexical.o pwck_local.o util.o 
 */
#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu)";
#endif

#include "checkpasswd.h"
#include <varargs.h>

static char *replies[] = {
	0,					/* PWCK_OK */
	"Empty password",			/* PWCK_NULL */
	"This password is too easy to guess",	/* PWCK_OBVIOUS */
	"This password is part of your 'finger' information", /* PWCK_FINGER */
	"This password was found in a dictionary",	/* PWCK_INDICT */
	"This password has an illegal character in it",	/* PWCK_ILLCHAR */
	"This password is too short",			/* PWCK_SHORT */
	0
};
#define	NREPLIES	7	/* Number of messages in replies */

static char	elucidate[BUFSIZ];	/* Expanded error message */
static char	*configfile = CONFIG_FILE;	/* Configuration file */
static char	configured = 0;		/* Has cf been read? */
D 2
static char	silent = 0;		/* Don't print messages */
E 2
I 2
static int	silent = 0;		/* Don't print messages */
E 2
		returncode = 0;		/* Return PWCK return code */
I 2
D 3
int	standalone = 0;			/* Not a standalone application */
E 3
I 3
int	PWCK_standalone = 0;		/* Not a standalone application */
char	PWCK_auxpwline[BUFSIZ];		/* Auxillary passwd line */
E 3
E 2

/*
 *	setcheckpasswd - set parameters for checkpasswd
 *
 *	e.g setcheckpasswd("-c", <configfile>, "-e", "-s", 0);
 */
setcheckpasswd(va_alist)
va_dcl		/* List of options */
{
	va_list	optlist;
	char	*optx;

	va_start(optlist);
	while (optx = va_arg(optlist, char *)) {
		if (*optx == '-') {
			switch(*++optx) {
			case 's':	/* -s (silent) */
				silent = 1;
				break;
			case 'e':	/* -e (return error code) */
				returncode = 1;
				break;
			case 'c':	/* -c config-file */
				if (*++optx)
					configfile = optx;
				else {
					optx = va_arg(optlist, char *);
					if (optx)
						configfile = optx;
I 3
				}
			case 'P':	/* -P passwd-file-line */
				if (*++optx)
					strcpy(PWCK_auxpwline, optx);
				else {
					optx = va_arg(optlist, char *);
					if (optx)
						strcpy(PWCK_auxpwline, optx);
E 3
				}
				break;
			}
		}
	}
	va_end(optlist);
}

/*
 *	checkpasswd - check password candidate
 *
 *	Returns 1 if <pwd> is ok to use as a password
 *		0 if not & an appropriate error message is issued
 */
checkpasswd(uid, pwd)
int	uid;		/* User who wants this password */
char	*pwd;		/* Password they want */
{
	int	rc;	/* Return code */

#ifdef	DEBUG
	printf("checkpasswd %d %s\n", uid, pwd);
#endif
	if (!configured) {
		readconfig(configfile);
		configured++;
	}
	rc = checkpassword(pwd, uid, elucidate);
	if (rc == PWCK_OK)		/* Always silent on success */
		return(returncode ? rc : 1);
	if (silent)
		return(returncode ? rc : 0);
	if (rc <= NREPLIES) {
		if (elucidate[0])
			printf("%s.\n", elucidate);
		else if (replies[rc])
			printf("%s.\n", replies[rc]);
		else
			putchar('\n');
	}
	return(returncode ? rc : 0);
}
/*	End %M% */
E 1
