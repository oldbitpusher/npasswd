/*
 *	shm_osf1.c - Support for OSF1 auth databases
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
static char sccsid[] = "@(#)shm_osf1.c	1.9 07/20/98 (cc.utexas.edu)";
#endif

#include "npasswd.h"
#include "pwm_defs.h"

#include <sys/secdefines.h>
#include <sys/security.h>
#include <sia.h>
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
	struct pw_svc *svc = get_pwsvc();

	if (svc->SecurityLevel != sec_OSFenhanced)
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
	int	pwdepth = 0;		/* Depth of password dictionary */
	struct pw_svc *svc = get_pwsvc();

	if (svc->SecurityLevel != sec_OSFenhanced)
		return;
	if ((pw = getprpwnam(newUser->mpw_name)) == NULL) {
		logdie("Cannot get shadow password for %s\n",
			newUser->mpw_name);
	}
	debug(DB_UPDATE, "update_shadow: auth for %s\n", newUser->mpw_name);

	px = *pw;
	/*
	 * Add current encrypted password to users' dictionary
	 * to be compatible with DEC's passwd program.
	 * Checkpasswd also uses this list in addition to the
	 * system-wide password history.
	 */
	if (px.sflg.fg_pwdepth) pwdepth = px.sfld.fd_pwdepth;
	if (px.uflg.fg_pwdepth) pwdepth = px.ufld.fd_pwdepth;
	if (pwdepth) {
		char	newhist[AUTH_MAX_PASSWD_DICT_SIZE];
		int	hl;

		(void) strcpy(newhist, px.ufld.fd_encrypt);
		hl = strlen(newhist);
		if (px.ufld.fd_pwdict[0]) {
			char	*ts, *te;
			int	ni = 2;
	
			ts = te = px.ufld.fd_pwdict;	
			while (*ts) {
				while (*te && *te != ',') *te++; 
				if (*te)
					*te++ = '\0';
				if (ni > pwdepth ||
				    hl + strlen(ts) + 2 >= AUTH_MAX_PASSWD_DICT_SIZE)
					break;
				(void) strcat(newhist, ",");
				(void) strcat(newhist, ts);
				hl = strlen(newhist);
				ni++;
				ts = te;
			}
			(void) strcpy(px.ufld.fd_pwdict, newhist);
			px.uflg.fg_pwdict = 1;
		}
	}
	/*
	 * Plug new values into auth structure
	 */
	(void) strcpy(px.ufld.fd_encrypt, newUser->mpw_passwd);
	px.ufld.fd_schange = time((time_t *)0);
	px.ufld.fd_pwchanger = getuid();
	px.ufld.fd_oldcrypt = 0;
	/*
	 * Set flags to indicate which values were changed
	 */
	px.uflg.fg_schange = 
	px.uflg.fg_oldcrypt = 
	px.uflg.fg_pwchanger = 
	px.uflg.fg_encrypt = 1;
	/*
	 * Update the auth database
	 */
	if (putprpwnam(newUser->mpw_name, &px) == 0)
		logdie("Could not update auth database.");
	/*
	 * Insert plug value for password (in case it gets written)
	 */
	newUser->mpw_passwd = "*";

	debug(DB_UPDATE, "update_shadow: updated auth for %s\n",
		newUser->mpw_name);
}

#if	(CDEBUG >= CDEBUG_SYSTEM)
/*
 * dump_authent
 *	Dump OSF/1 auth database fields & flags structures
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
	if (f->fg_nice) printf("fd_nice = %d\n", p->fd_nice);
	if (f->fg_cprivs) printf("fd_cprivs = %x\n", p->fd_cprivs);
	if (f->fg_sprivs) printf("fd_sprivs = %x\n", p->fd_sprivs);
	if (f->fg_bprivs) printf("fd_bprivs = %x\n", p->fd_bprivs);
	if (f->fg_auditdisp) printf("fd_auditdisp = %x\n", p->fd_auditdisp);
	if (f->fg_auditcntl) printf("fd_auditcntl = %x\n", p->fd_auditcntl);
	if (f->fg_min) printf("fd_min = %d\n", p->fd_min);
	if (f->fg_minlen) printf("fd_minlen = %d\n", p->fd_minlen);
	if (f->fg_maxlen) printf("fd_maxlen = %d\n", p->fd_maxlen);
	if (f->fg_expire) printf("fd_expire = %d\n", p->fd_expire);
	if (f->fg_lifetime) printf("fd_lifetime = %d\n", p->fd_lifetime);
	if (f->fg_schange) printf("fd_schange = %s", ctime(&p->fd_schange));
	if (f->fg_uchange) printf("fd_uchange = %d\n", p->fd_uchange);
	if (f->fg_pick_pwd) printf("fd_pick_pwd = %d\n", p->fd_pick_pwd);
	if (f->fg_gen_pwd) printf("fd_gen_pwd = %d\n", p->fd_gen_pwd);
	if (f->fg_restrict) printf("fd_restrict = %d\n", p->fd_restrict);
	if (f->fg_policy) printf("fd_policy = %d\n", p->fd_policy);
	if (f->fg_nullpw) printf("fd_nullpw = %d\n", p->fd_nullpw);
	if (f->fg_pwchanger) printf("fd_pwchanger = %d\n", p->fd_pwchanger);
	if (f->fg_gen_chars) printf("fd_gen_chars = %d\n", p->fd_gen_chars);
	if (f->fg_gen_letters) printf("fd_gen_letters = %d\n", p->fd_gen_letters);
	if (f->fg_pwdepth) printf("fd_pwdepth = %d\n", p->fd_pwdepth);
	if (f->fg_pwdict) printf("fd_pwdict = %s\n", p->fd_pwdict);
	if (f->fg_oldcrypt) printf("fd_oldcrypt = %d\n", p->fd_oldcrypt);
	if (f->fg_newcrypt) printf("fd_newcrypt = %d\n", p->fd_newcrypt);
	if (f->fg_slogin) printf("fd_slogin = %s", ctime(&p->fd_slogin));
	if (f->fg_ulogin) printf("fd_ulogin = %s", ctime(&p->fd_ulogin));
	if (f->fg_suctty) printf("fd_suctty = %s\n", p->fd_suctty);
	if (f->fg_unsuctty) printf("fd_unsuctty = %s\n", p->fd_unsuctty);
	if (f->fg_nlogins) printf("fd_nlogins = %u\n", p->fd_nlogins);
	if (f->fg_tod) printf("fd_tod = %s\n", p->fd_tod);
	if (f->fg_max_tries) printf("fd_max_tries = %u\n", p->fd_max_tries);
	if (f->fg_unlockint) printf("fd_unlockint = %u\n", p->fd_unlockint);
	if (f->fg_retired) printf("fd_retired = %u\n", p->fd_retired);
	if (f->fg_lock) printf("fd_lock = %u\n", p->fd_lock);
	if (f->fg_expdate) printf("fd_expdate = %s", ctime(&p->fd_expdate));
	if (f->fg_istemplate) printf("fd_istemplate = %u\n", p->fd_istemplate);
	if (f->fg_template) printf("fd_template = %s\n", p->fd_template);
}
#endif	/* DEBUG */

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
	debug(DB_LOOKUP,"svc->SecurityLevel (OSF) = %d\n", svc->SecurityLevel);
	if (svc->SecurityLevel == sec_OSFenhanced) {
		struct pr_passwd *pw =
			(struct pr_passwd *)getprpwnam(theUser->mpw_name);
		int	pick = 1;

		if (pw == NULL)
			logdie("Cannot get auth data for %s\n",
     				theUser->mpw_name);
		if (pw->sflg.fg_pick_pwd) pick = pw->sfld.fd_pick_pwd;
		if (pw->uflg.fg_pick_pwd) pick = pw->ufld.fd_pick_pwd;
		if (!pick) {
			printf("User must have a system-generated password.\n");
			return(deny);
		}
	}
	return(allow);
}

/* End shm_osf1.c */
