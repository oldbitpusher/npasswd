/*
 *	shm_aix3.c - Support for AIX3 auth databases
 *
 *	Original by Richard.North@agric.nsw.gov.au 9/17/97
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
#include "npasswd.h"
#include "pwm_defs.h"

#include <userpw.h>
#include <usersec.h>

#ifndef	lint
static char sccsid[] = "@(#)shm_aix.c	1.3 07/17/98 (cc.utexas.edu)";
#endif

Config_Value  int ShadowTolerance = 0;	/* No-op */

/*
 * get_shadow
 *	Get information from AIX auth database
 * Usage
 *	get_shadow(struct mpasswd *);
 * Error exits
 *	If there should be an auth record for <user> but it cannot be found
 */
public void
get_shadow(userm)
	struct mpasswd *userm;
{
	struct pw_opaque *po = userm->opaque;
	/*
	 * Is the password is in the auth datbase
	 */
	if (strcmp(userm->mpw_passwd, "!") == 0) {
		struct userpw	*upw;

		if (setpwdb(S_READ))
			logdie("Permission for auth DB access denied.");

		upw = getuserpw(userm->mpw_name);
		if (!upw)
			logdie("Cannot get password for user %s from auth DB.",
				userm->mpw_name);

		userm->mpw_opasswd = strdup(userm->mpw_passwd);
		if ((userm->mpw_passwd = strdup(upw->upw_passwd)) == NULL)
			logdie("out of memory.");
		po->sourceSH = srv_local;
		userm->pwage.last_change = upw->upw_lastupdate;
		debug(DB_LOOKUP, "get_shadow: found auth pw for %s\n",
			userm->mpw_name);
		endpwdb();	/* Do this last */
	}
}

/*
 * update_shadow
 *	Update information in AIX auth database
 * Usage
 *	update_shadow(struct mpasswd *old-data, struct mpasswd *new-data);
 * Error exits
 *	Failure to find auth information for <theUser->mpw_name>
 *	Failure to update auth information for <theUser->mpw_name>
 */
public void
update_shadow(theUser, newUser)
	struct mpasswd	*theUser;
	struct mpasswd	*newUser;
{
	struct userpw	*upw;
	char	*putuser_err;

	if (setpwdb(S_READ | S_WRITE))
		logdie("Write permission for auth DB access denied");

	if ((upw = getuserpw(theUser->mpw_name)) == NULL) {
		endpwdb();
		logdie("Cannot read auth DB for update.");
	}
	upw->upw_passwd = newUser->mpw_passwd;
	upw->upw_lastupdate = time((time_t *)0);
	/*
	 * Set "force change" if root, clear if not
	 */
	if (CallerUid == 0)		
		upw->upw_flags |= PW_ADMCHG;
	else
		upw->upw_flags &= ~PW_ADMCHG;

	if (putuserpwhist(upw, &putuser_err))
		logdie("Could not update auth database.");
	if (putuser_err)
		logerr("Error in updating password history: %s\n", putuser_err);

/* 	newUser->mpw_passwd = "!"; */	/* Don't - messes up history */
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
        /*
         * Check the AIX auth datbase for password flags
         */
        if (strcmp(theUser->mpw_opasswd, "!") == 0) {
                struct userpw   *upw;

                if (setpwdb(S_READ))
                        logdie("Permission for auth DB access denied.");

                upw = getuserpw(theUser->mpw_name);
                if (!upw)
                        logdie("Cannot get password for user %s from auth DB.",
                                theUser->mpw_name);
		if ((upw->upw_flags & PW_ADMIN) && CallerUid) {
			printf("Password can only be changed by root.\n");
			endpwdb();
			return(deny);
		}
                endpwdb();
        }
	return(allow);
}

/* End %M */
