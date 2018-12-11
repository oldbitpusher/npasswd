h36097
s 00046/00000/00074
d D 1.4 98/07/20 15:20:02 clyde 4 3
c Move password change auth check from ../passwd.c
e
s 00002/00001/00072
d D 1.3 97/09/23 12:26:48 clyde 3 2
c Stash original encrypted password
e
s 00002/00005/00071
d D 1.2 96/03/27 09:29:41 clyde 2 1
c Use debug() routine for messages
e
s 00076/00000/00000
d D 1.1 95/04/05 16:21:28 clyde 1 0
c date and time created 95/04/05 16:21:28 by clyde
e
u
U
f e 0
t
T
I 1
/*
 *	%M% - Support for Ultrix/OSF1 auth databases
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
D 3
		userm->mpw_passwd = copystr(a->a_password);
E 3
I 3
		userm->mpw_opasswd = strdup(userm->mpw_passwd);
		userm->mpw_passwd = strdup(a->a_password);
E 3
		po->sourceSH = srv_local;
		userm->pwage.last_change = a->a_pass_mod;
		userm->pwage.min_time = a->a_pw_minexp;
		userm->pwage.max_time = a->a_pw_maxexp;
D 2
		if (DebugLevel >= DB_LOOKUP) {
			printf("get_shadow: found auth pw for %s\n",
				userm->mpw_name);
			fflush(stdout);
		}
E 2
I 2
		debug(DB_LOOKUP, "get_shadow: found auth pw for %s\n",
			userm->mpw_name);
E 2
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

I 4
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

E 4
/* End %M% */
E 1
