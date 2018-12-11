/*
 *	shm_ultrix.c - Support for Ultrix/OSF1 auth databases
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
static char sccsid[] = "@(#)shm_ultrix.c	1.4 07/20/98 (cc.utexas.edu)";
#endif

#include "npasswd.h"
#include "pwm_defs.h"

#include <auth.h>

public void
get_shadow(userm)
	struct mpasswd *userm;
{
	struct pw_opaque *po = userm->opaque;
	/*
	 * Check if the password is in the auth datbase (Ultrix 4.X)
	 */
	if ((SecurityLevel == sec_u4enhanced) ||
	    (SecurityLevel == sec_u4upgrade &&
	     strcmp(userm->mpw_passwd, "*") == 0)) {
		AUTHORIZATION	*a;

		if ((a = getauthuid(userm->mpw_uid)) == 0)
			logdie("Cannot get password for uid %d from auth db",
				userm->mpw_uid);
		userm->mpw_opasswd = strdup(userm->mpw_passwd);
		userm->mpw_passwd = strdup(a->a_password);
		po->sourceSH = srv_local;
		userm->pwage.last_change = a->a_pass_mod;
		userm->pwage.min_time = a->a_pw_minexp;
		userm->pwage.max_time = a->a_pw_maxexp;
		debug(DB_LOOKUP, "get_shadow: found auth pw for %s\n",
			userm->mpw_name);
	}
}

public void
update_shadow(theUser, newUser)
	struct mpasswd	*theUser;
	struct mpasswd	*newUser;
{
	AUTHORIZATION	*a;

	if ( SecurityLevel != sec_u4upgrade &&
	     SecurityLevel != sec_u4enhanced)
		return;

	if ((a = getauthuid(theUser->mpw_uid)) == NULL)
		logdie("Could not read auth database for update.");
	(void) strcpy(a->a_password, newUser->mpw_passwd);
	a->a_pass_mod = time((time_t *)0);
	if (storeauthent(a))
		logdie("Could not update auth database.");
	newUser->mpw_passwd = "*";
}

/*
 * check_auth
 *	Check the password change bits in auth database
 * Usage:
 *	check_auth(struct mpasswd *)
 * Returns:
 *	deny = auth says no
 *	allow = no deny
 */
public enum chg_perm
check_auth(theUser)
	struct mpasswd *theUser;
{
	struct pw_svc *svc = get_pwsvc();

	debug(DB_LOOKUP,"svc->SecurityLevel (Ultrix)= %d\n",svc->SecurityLevel);
	/*
	 * Check the authorization data for password change permission.
	 */
	if ((svc->SecurityLevel == sec_u4enhanced) ||
	    (SecurityLevel == sec_u4upgrade &&
	     strcmp(theUser->mpw_opasswd, "*") == 0)) {
		AUTHORIZATION	*a;

		if ((a = getauthuid(theUser->mpw_uid)) == NULL)
			logdie("Cannot get auth data.\n");
		/*
		 * Can the user change their password?
		 */
		if (CallerUid == theUser->mpw_uid &&
		   !(a->a_authmask & A_CHANGE_PASSWORD)) {
			printf("Permission denied.\n");
			return(deny);
		}
		/*
		 * Can the user specify their own password?
		 */
		if (CallerUid == theUser->mpw_uid &&
		   !(a->a_authmask & A_ENTER_PASSWORD)) {
			printf("User must have a system-generated password.\n");
			return(deny);
		}
	}
	return(allow);
}

/* End shm_ultrix.c */
