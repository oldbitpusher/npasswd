h39916
s 00008/00000/00039
d D 1.3 98/07/20 15:19:41 clyde 3 2
c Add check_auth()
e
s 00002/00000/00037
d D 1.2 97/09/23 12:26:25 clyde 2 1
c Add ShadowTolerance var so that link will succeed.
e
s 00037/00000/00000
d D 1.1 95/04/05 16:21:25 clyde 1 0
c date and time created 95/04/05 16:21:25 by clyde
e
u
U
f e 0
t
T
I 1
/*
 *	%M% - Null shadow routines
 *
 *	Two routines need to advertised from this module:
 *
 *	void get_shadow(struct mpasswd *theUser)
 *		This routine checks if the password is in a shadow database
 *		and fetches it if so.  Information is stashed in the 
 *		"method" data about where the shadow password was found.
 *
 *	void update_shadow(struct mpasswd *theUser, struct mpasswd *newUser)
 *		Updates the shadow password for "newUser".
 *		
 *	Neither routine returns a value, but changes the meta-passwd record
 *	passed in, and aborts on serious error.
 */

#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu)";
#endif

#include "npasswd.h"
#include "pwm_defs.h"

I 2
Config_Value int	ShadowTolerance = 0;

E 2
public void
get_shadow(userm)
	struct mpasswd *userm;
{
}

public void
update_shadow(theUser, newUser)
	struct mpasswd	*theUser;
	struct mpasswd	*newUser;
{
}
I 3

public enum chg_perm
check_auth(theUser)
	struct mpasswd *theUser;
{
	return(allow);
}

E 3
/* End %M% */
E 1
