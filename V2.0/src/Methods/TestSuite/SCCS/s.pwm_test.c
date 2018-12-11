h27398
s 00001/00000/00125
d D 1.3 98/09/23 14:27:05 clyde 3 2
c Include pw_svc.h
e
s 00004/00004/00121
d D 1.2 98/07/14 16:25:43 clyde 2 1
c Change for new debug/getsvc code
e
s 00125/00000/00000
d D 1.1 98/03/31 11:23:10 clyde 1 0
c date and time created 98/03/31 11:23:10 by clyde
e
u
U
f e 0
t
T
I 1
/*
 * Driver for testing npasswd password database method routines.
 *
 * Compilation: %M% -DTEST_NAME method.o ... method.o ../../Common/libcomobj.a
 */
#include "npasswd.h"
I 3
#include "pw_svc.h"
E 3

#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu)";
#endif

/*
 * Global variables
 */
D 2
public int	DebugLevel = DB_ALL;		/* Debugging level */
public struct pw_svc svc;			/* Service info */
E 2
private	struct mpasswd	*theUser,		/* Target of change */
			*newUser;		/* Who wants to make change */
public char	*XSwitches[256] = { 0 };	/* Make modules happy */
int		IgnoreErrors = 0;		/* Ignore errors? */

/*
 * Set program name for the message routines
 */
#ifdef	TEST_GETUSER
public char	*ProgramName = "getuser-test";
#define	_PN 1
#endif

#ifndef	_PN
error	No test name definied
#endif

extern char	*optarg;	/* From getopt() */
extern int	optind;		/* From getopt() */

/*
 * List of methods (for -S option)
 */
struct servlist {
	char	*name;
	enum svc_services srvno;
};

struct servlist myservlist[] = {
	{ "local",	srv_local },
#ifdef	USE_NIS
	{ "nis",	srv_yp },
#endif
#ifdef	USE_NISPLUS
	{ "nisplus",	srv_nisplus },
#endif
	{ 0, 0 }
};

/*
 *
 */
main(argc, argv, envp)
	int	argc;
	char	**argv;
	char	**envp;		/* Not ANSI? */
{
	int	opt;

	(void) umask(0);
D 2
	(void) get_pwsvc(argc, argv, envp, &svc);
E 2
I 2
	set_debug_tag(ProgramName);
	init_debug(DB_ALL);
E 2
	pw_initialize(argc, argv);

	while ((opt = getopt(argc, argv, "eS:")) != EOF) {
		switch (opt) {
		case 'e':
			IgnoreErrors = 1;
			break;
		/*
		 * -S service,service
		 * Select which services will be used for the test
		 */
		case 'S':
			{
D 2
			enum svc_services *ss = svc.ServiceOrder;
E 2
I 2
			struct pw_svc *svc = get_pwsvc();
			enum svc_services *ss = svc->ServiceOrder;
E 2
			char	**sp;

			for (sp = split(optarg,',',(char *)0,(char )0); *sp; sp++) {
				struct servlist *sl;
				int ok = 0;

				for (sl = myservlist; sl->name; sl++) {
					if (strcmp(*sp, sl->name)) continue;
					*ss++ = sl->srvno;
					ok++;
					printf("%s: Set service '%s'\n",
						ProgramName, *sp);
					break;
				}
				if (!ok) {
					printf("%s: Unsupported service '%s'\n",
						ProgramName, *sp);
					exit(1);
				}
			}
			*ss = srv_last;
			}
			break;
		}
	}

#ifdef	TEST_GETUSER
	for (; argv[optind]; optind++) {
		printf("\n%s: Looking for user '%s'\n", ProgramName, argv[optind]);
		if ((theUser = pw_getuserbyname(argv[optind])) == NULL) {
			printf("%s: Could not find user '%s'\n",
				ProgramName, argv[optind]);
			if (!IgnoreErrors) exit(1);
		}
		else {
			printf("%s: Meta-passwd for '%s'\n",
				ProgramName, argv[optind]);
			printmpwent(theUser);
		}
	}
#endif
	exit(0);
}
/* End %M% */
E 1
