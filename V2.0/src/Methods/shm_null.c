/*
 *	shm_null.c - Null shadow routines
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
static char sccsid[] = "@(#)shm_null.c	1.3 07/20/98 (cc.utexas.edu)";
#endif

#include "npasswd.h"
#include "pwm_defs.h"

Config_Value int	ShadowTolerance = 0;

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

public enum chg_perm
check_auth(theUser)
	struct mpasswd *theUser;
{
	return(allow);
}

/* End shm_null.c */
