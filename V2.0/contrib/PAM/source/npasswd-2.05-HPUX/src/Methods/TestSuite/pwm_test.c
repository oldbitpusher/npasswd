/*
 * Driver for testing npasswd password database method routines.
 *
 * Compilation: pwm_test.c -DTEST_NAME method.o ... method.o ../../Common/libcomobj.a
 */
#include "npasswd.h"
#include "pw_svc.h"

#ifndef lint
static char sccsid[] = "@(#)pwm_test.c	1.3 09/23/98 (cc.utexas.edu)";
#endif

/*
 * Global variables
 */
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
	set_debug_tag(ProgramName);
	init_debug(DB_ALL);
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
			struct pw_svc *svc = get_pwsvc();
			enum svc_services *ss = svc->ServiceOrder;
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
/* End pwm_test.c */
