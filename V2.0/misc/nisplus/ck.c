/*
 * NIS+ passwd table manipulation routines
 *
 * Compile with Sun C compiler, using option "-Xa" (ANSI mode)
 *
 * Routines in this module:
 *
 * nis_putspent() - Put shadow entry
 * nis_putpwent() - Put passwd entry
 * nis_getpwnam() - Get passwd entry (by name)
 * nis_getpwuid() - Get passwd entry (by uid)
 * nis_getspnam() - Get shadow entry (by name)
 * nis_getuser() - Internal routine 
 * nis_putuser() - Internal routine
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <shadow.h>

main(c,v)
char	**v;
{
	struct spwd	*xsp;

	for (v++; *v; v++) {
		if ((xsp = getspnam(*v)) == NULL)
			exit(1);
		printf("%s:%s:%ld:%ld:%ld:%ld:%ld:%ld:%lu\n",
			xsp->sp_namp, xsp->sp_pwdp,
			xsp->sp_lstchg, xsp->sp_min, xsp->sp_max,
			xsp->sp_warn, xsp->sp_inact, xsp->sp_expire,
			xsp->sp_flag);
	}
	exit(0);
}

