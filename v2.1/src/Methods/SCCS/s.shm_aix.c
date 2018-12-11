h40064
s 00068/00005/00079
d D 1.3 98/07/17 16:30:54 clyde 3 2
c 1. Add check_auth() routine 
c 2. Make it work right
e
s 00010/00007/00074
d D 1.2 97/09/23 12:27:46 clyde 2 1
c Minor code cleanup
e
s 00081/00000/00000
d D 1.1 97/09/19 10:45:55 clyde 1 0
c date and time created 97/09/19 10:45:55 by clyde
e
u
U
f e 0
t
T
I 1
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
static char sccsid[] = "%W% %G% (cc.utexas.edu)";
#endif

D 2
int  ShadowTolerance = 0;
E 2
I 2
D 3
Config_Value  ShadowTolerance = 0;	/* No-op */
E 3
I 3
Config_Value  int ShadowTolerance = 0;	/* No-op */
E 3
E 2

I 3
/*
 * get_shadow
 *	Get information from AIX auth database
 * Usage
 *	get_shadow(struct mpasswd *);
 * Error exits
 *	If there should be an auth record for <user> but it cannot be found
 */
E 3
public void
get_shadow(userm)
	struct mpasswd *userm;
{
	struct pw_opaque *po = userm->opaque;
	/*
D 3
	 * Check if the password is in the auth datbase (AIX 3)
E 3
I 3
	 * Is the password is in the auth datbase
E 3
	 */
D 2
	if (!strcmp(userm->mpw_passwd, "!")) {
E 2
I 2
	if (strcmp(userm->mpw_passwd, "!") == 0) {
E 2
		struct userpw	*upw;

		if (setpwdb(S_READ))
			logdie("Permission for auth DB access denied.");

		upw = getuserpw(userm->mpw_name);
D 3
		endpwdb();
E 3
		if (!upw)
			logdie("Cannot get password for user %s from auth DB.",
				userm->mpw_name);
I 2

		userm->mpw_opasswd = strdup(userm->mpw_passwd);
E 2
		if ((userm->mpw_passwd = strdup(upw->upw_passwd)) == NULL)
			logdie("out of memory.");
		po->sourceSH = srv_local;
		userm->pwage.last_change = upw->upw_lastupdate;
		debug(DB_LOOKUP, "get_shadow: found auth pw for %s\n",
			userm->mpw_name);
I 3
		endpwdb();	/* Do this last */
E 3
	}
}

I 3
/*
 * update_shadow
 *	Update information in AIX auth database
 * Usage
 *	update_shadow(struct mpasswd *old-data, struct mpasswd *new-data);
 * Error exits
 *	Failure to find auth information for <theUser->mpw_name>
 *	Failure to update auth information for <theUser->mpw_name>
 */
E 3
public void
update_shadow(theUser, newUser)
	struct mpasswd	*theUser;
	struct mpasswd	*newUser;
{
	struct userpw	*upw;
I 2
	char	*putuser_err;
E 2

	if (setpwdb(S_READ | S_WRITE))
		logdie("Write permission for auth DB access denied");

D 2
	if ((upw = getuserpw(theUser->mpw_name)) == NULL)
	{
E 2
I 2
	if ((upw = getuserpw(theUser->mpw_name)) == NULL) {
E 2
		endpwdb();
		logdie("Cannot read auth DB for update.");
	}
D 2

E 2
D 3
	(void) strcpy(upw->upw_passwd, newUser->mpw_passwd);
E 3
I 3
	upw->upw_passwd = newUser->mpw_passwd;
E 3
	upw->upw_lastupdate = time((time_t *)0);
I 3
	/*
	 * Set "force change" if root, clear if not
	 */
	if (CallerUid == 0)		
		upw->upw_flags |= PW_ADMCHG;
	else
		upw->upw_flags &= ~PW_ADMCHG;

E 3
D 2
	if (putuserpw(upw))
E 2
I 2
	if (putuserpwhist(upw, &putuser_err))
E 2
		logdie("Could not update auth database.");
D 2
	newUser->mpw_passwd = "*";
E 2
I 2
	if (putuser_err)
		logerr("Error in updating password history: %s\n", putuser_err);
D 3
	newUser->mpw_passwd = "!";
E 3
I 3

/* 	newUser->mpw_passwd = "!"; */	/* Don't - messes up history */
E 3
E 2
}
I 3

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

E 3
/* End %M */
E 1
