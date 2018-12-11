?RCS:
?RCS: %W% %G%
?RCS:
?RCS: Unit 'p_utmpx' - see if extended utmp format in use
?RCS:
?MAKE:p_futmpx: Inlibc
?MAKE:	-pick add $@ %<
?LINT:set p_utmpx
?S:p_utmpx:
?S:    This variable is set to 'true' if libc utmpx routines are available
?S:.
?C:USE_UTMPX :
?C:	This symbol if defined, indicates that extended wtmp form is used
?C:.
?H:#$p_utmpx	USE_UTMPX	/**/
?H:.
set getutxent p_utmpx
eval "$inlibc"

#$i_unistd I_UNISTD
#$i_stdlib I_STDLIB

#include <stdio.h>
#ifdef I_UNISTD
#  include <unistd.h>
#endif
#include <wtmpx.h>
main()
{
	struct wtmpx wt;
	exit (sizeof(wt.ut_name) > _POSIX_LOGIN_NAME_MAX);
}
EOCP

