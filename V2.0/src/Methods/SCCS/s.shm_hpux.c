h10100
s 00000/00004/00212
d D 1.4 99/02/01 13:51:12 clyde 4 3
c Don't plug newuser password (gets written to shadow file)
e
s 00037/00000/00179
d D 1.3 98/07/20 15:21:22 clyde 3 2
c Move password change auth check from ../passwd.c
e
s 00002/00001/00177
d D 1.2 98/07/16 09:19:28 clyde 2 1
c Change get_pwsvc() usage
e
s 00178/00000/00000
d D 1.1 98/04/30 14:37:02 clyde 1 0
c date and time created 98/04/30 14:37:02 by clyde
e
u
U
f e 0
t
T
I 1
/*
 *	shm_hpux.c - Support for HPUX auth databases
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
 *
 * 10/15/97 MStute	Created - based on OSF/1 version
 */
#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu)";
#endif

#include "npasswd.h"
#include "pwm_defs.h"

#include <hpsecurity.h>
#include <prot.h>

Config_Value	int ShadowTolerance = 0;		/* Not used */

/*
 * get_shadow
 *      Look for a user in the auth database.
 *      The user's shadow information is stored in <user>
 *
 * Usage
 *      get_shadow(struct mpasswd *user);
 */
public void
get_shadow(theUser)
	struct mpasswd *theUser;
{
	struct pr_passwd *pw;
	struct pw_opaque *aux = theUser->opaque;
I 2
	struct pw_svc *svc = get_pwsvc();
E 2

D 2
	if (svc.SecurityLevel != sec_HPtrusted)
E 2
I 2
	if (svc->SecurityLevel != sec_HPtrusted)
E 2
		return;

	if ((pw = getprpwnam(theUser->mpw_name)) == NULL) {
		logdie("Cannot get auth record for %s\n",
			theUser->mpw_name);
	}
	theUser->mpw_passwd = strdup(pw->ufld.fd_encrypt);
	aux->sourceSH = srv_local;
	debug(DB_LOOKUP, "get_shadow: found auth pw for %s\n",
		theUser->mpw_name);
	/*
	 * Process password aging information
	 */

	/* Minimum pw change time */
	if (pw->sflg.fg_min)
		theUser->pwage.can_change = pw->sfld.fd_min;
	if (pw->uflg.fg_min)
		theUser->pwage.can_change = pw->ufld.fd_min;

	/* Time of last password change */
	if (pw->uflg.fg_schange)
		theUser->pwage.last_change = pw->ufld.fd_schange;

	/* Password expiration time */
	if (pw->sflg.fg_lifetime)
		theUser->pwage.must_change = pw->sfld.fd_lifetime;
	if (pw->uflg.fg_lifetime)
		theUser->pwage.must_change = pw->ufld.fd_lifetime;
	theUser->mpw_age = "x";
}

/*
 * update_shadow
 *      Update auth database
 *
 * Usage
 *      update_shadow(struct mpasswd *old-data, struct mpasswd *new-data);
 * Error exits
 *      Failure to find auth information for <theUser->mpw_name>
 *      Failure to update auth information for <theUser->mpw_name>
 */
public void
update_shadow(theUser, newUser)
	struct mpasswd	*theUser;
	struct mpasswd	*newUser;
{
	struct pr_passwd *pw,		/* Auth password db lookup temp */
			 px;		/* Auth password update temp */

	if ((pw = getprpwnam(newUser->mpw_name)) == NULL) {
		logdie("Cannot get shadow password for %s\n",
			newUser->mpw_name);
	}
	debug(DB_UPDATE, "update_shadow: auth for %s\n", newUser->mpw_name);
	px = *pw;
	/*
	 * Plug new values into auth structure
	 */
	(void) strcpy(px.ufld.fd_encrypt, newUser->mpw_passwd);
	px.ufld.fd_schange = time((time_t *)0);
	px.ufld.fd_pwchanger = getuid();
	/*
	 * Set flags to indicate which values were changed
	 */
	px.uflg.fg_schange = 
	px.uflg.fg_pwchanger = 
	px.uflg.fg_encrypt = 1;
	/*
	 * Update the auth database
	 */
	if (putprpwnam(newUser->mpw_name, &px) == 0)
		logdie("Could not update auth database.");
D 4
	/*
	 * Insert plug value for password (in case it gets written)
	 */
	newUser->mpw_passwd = "*";
E 4

	debug(DB_UPDATE, "update_shadow: updated auth for %s\n",
		newUser->mpw_name);
}

#if	(CDEBUG >= CDEBUG_SYSTEM)
/*
 * dump_authent
 *	Dump HPUX auth database fields & flags structures
 * Usage
 *	dump_authent(struct pr_flag *flags, struct pr_field *fields);
 */
private void
dump_authent(f, p)
	struct pr_flag *f;
	struct pr_field *p;
{
	if (f->fg_name) printf("fd_name = %s\n", p->fd_name);
	if (f->fg_uid) printf("fd_uid = %d\n", p->fd_uid);
	if (f->fg_encrypt) printf("fd_encrypt = %s\n", p->fd_encrypt);
	if (f->fg_owner) printf("fd_owner = %s\n", p->fd_owner);
	if (f->fg_boot_auth) printf("fd_boot_auth = %c\n", p->fd_boot_auth);
	if (f->fg_pw_audid) printf("fd_pw_audid = %x\n", p->fd_pw_audid);
	if (f->fg_pw_audflg) printf("fd_pw_audflg = %x\n", p->fd_pw_audflg);
	if (f->fg_min) printf("fd_min = %d\n", p->fd_min);
	if (f->fg_maxlen) printf("fd_maxlen = %d\n", p->fd_maxlen);
	if (f->fg_expire) printf("fd_expire = %d\n", p->fd_expire);
	if (f->fg_lifetime) printf("fd_lifetime = %d\n", p->fd_lifetime);
	if (f->fg_schange) printf("fd_schange = %s", ctime(&p->fd_schange));
	if (f->fg_uchange) printf("fd_uchange = %s\n", ctime(&p->fd_uchange));
	if (f->fg_acct_expire) printf("fd_acct_expire = %d\n", p->fd_acct_expire);
	if (f->fg_max_llogin) printf("fd_max_llogin = %d\n", p->fd_max_llogin);
/*        if (f->fg_pw_expire_warning) printf("fg_pw_expire_warning = %d\n",
                   fd_pw_expire_warning);*/
	if (f->fg_pswduser) printf("fd_pswduser = %u\n", p->fd_pswduser);
	if (f->fg_pick_pwd) printf("fd_pick_pwd = %d\n", p->fd_pick_pwd);
	if (f->fg_gen_pwd) printf("fd_gen_pwd = %d\n", p->fd_gen_pwd);
	if (f->fg_restrict) printf("fd_restrict = %d\n", p->fd_restrict);
	if (f->fg_nullpw) printf("fd_nullpw = %d\n", p->fd_nullpw);
	if (f->fg_pwchanger) printf("fd_pwchanger = %d\n", p->fd_pwchanger);
	if (f->fg_pw_admin_num) printf("fd_pw_admin_num = %d\n", p->fd_pw_admin_num); 
	if (f->fg_gen_chars) printf("fd_gen_chars = %d\n", p->fd_gen_chars);
	if (f->fg_gen_letters) printf("fd_gen_letters = %d\n", p->fd_gen_letters);

	if (f->fg_slogin) printf("fd_slogin = %s", ctime(&p->fd_slogin));
	if (f->fg_ulogin) printf("fd_ulogin = %s", ctime(&p->fd_ulogin));
	if (f->fg_suctty) printf("fd_suctty = %s\n", p->fd_suctty);
	if (f->fg_unsuctty) printf("fd_unsuctty = %s\n", p->fd_unsuctty);
	if (f->fg_nlogins) printf("fd_nlogins = %u\n", p->fd_nlogins);
	if (f->fg_tod) printf("fd_tod = %s\n", p->fd_tod);
	if (f->fg_max_tries) printf("fd_max_tries = %u\n", p->fd_max_tries);
	if (f->fg_lock) printf("fd_lock = %u\n", p->fd_lock);
}
#endif	/* DEBUG */
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
	struct pw_svc *svc = get_pwsvc();

	/*
	 * Check the authorization data for password change permission.
	 */
	debug(DB_LOOKUP,"svc->SecurityLevel (HPUX) = %d\n", svc->SecurityLevel);
	if (svc->SecurityLevel == sec_HPtrusted) {
		struct pr_passwd *pw =
			(struct pr_passwd *)getprpwnam(theUser->mpw_name);
		int	pick = 1;

		if (pw == NULL)
			logdie("Cannot get auth data for %s\n",
     				theUser->mpw_name);
		if (pw->sflg.fg_pick_pwd) pick = pw->sfld.fd_pick_pwd;
		if (pw->uflg.fg_pick_pwd) pick = pw->ufld.fd_pick_pwd;
		if (!pick) {
			printf("You must use a system-generated password.\n");
			return(deny);
		}
	}
	return(allow);
}
E 3
/* End %M% */
E 1
