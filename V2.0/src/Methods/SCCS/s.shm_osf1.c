h34150
s 00038/00000/00229
d D 1.9 98/07/20 15:20:21 clyde 9 8
c Move password change auth check from ../passwd.c
e
s 00004/00002/00225
d D 1.8 98/07/16 09:19:21 clyde 8 7
c Change get_pwsvc() usage
e
s 00001/00001/00226
d D 1.7 98/06/23 10:57:27 clyde 7 6
c Change compile-time debug include trigger
e
s 00011/00006/00216
d D 1.6 98/03/31 14:35:08 clyde 6 5
c Fix debugging messages
e
s 00026/00003/00196
d D 1.5 96/08/15 11:04:09 clyde 5 4
c 1. Add ShadowTolerance to make linker happy
c 2. Add comments 
e
s 00006/00006/00193
d D 1.4 96/08/14 11:32:23 clyde 4 3
c Beta 3: compiles under OSF/1 3.2
e
s 00002/00002/00197
d D 1.3 96/08/06 14:14:15 clyde 3 2
c beta 3 cycle 1 checkin
e
s 00006/00013/00193
d D 1.2 96/03/27 09:29:26 clyde 2 1
c Use debug() routine for messages
e
s 00206/00000/00000
d D 1.1 95/04/05 16:21:27 clyde 1 0
c date and time created 95/04/05 16:21:27 by clyde
e
u
U
f e 0
t
T
I 1
/*
 *	%M% - Support for OSF1 auth databases
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

#include <sys/secdefines.h>
#include <sys/security.h>
#include <sia.h>
#include <prot.h>

I 5
Config_Value	int ShadowTolerance = 0;		/* Not used */

/*
 * get_shadow
 *      Look for a user in the auth database.
 *      The user's shadow information is stored in <user>
 *
 * Usage
 *      get_shadow(struct mpasswd *user);
 */
E 5
public void
get_shadow(theUser)
	struct mpasswd *theUser;
{
	struct pr_passwd *pw;
	struct pw_opaque *aux = theUser->opaque;
I 8
	struct pw_svc *svc = get_pwsvc();
E 8

D 4
	if (SecurityLevel != sec_OSFenhanced)
E 4
I 4
D 8
	if (svc.SecurityLevel != sec_OSFenhanced)
E 8
I 8
	if (svc->SecurityLevel != sec_OSFenhanced)
E 8
E 4
		return;

	if ((pw = getprpwnam(theUser->mpw_name)) == NULL) {
		logdie("Cannot get auth record for %s\n",
			theUser->mpw_name);
	}
D 3
	theUser->mpw_passwd = copystr(pw->ufld.fd_encrypt);
E 3
I 3
	theUser->mpw_passwd = strdup(pw->ufld.fd_encrypt);
E 3
	aux->sourceSH = srv_local;
D 2
	if (DebugLevel >= DB_LOOKUP) {
		printf("get_shadow: found auth pw for %s\n", theUser->mpw_name);
		fflush(stdout);
	}
E 2
I 2
	debug(DB_LOOKUP, "get_shadow: found auth pw for %s\n",
		theUser->mpw_name);
E 2

	/*
	 * Process password aging information
	 */
	/* Minimum pw change time */
D 4
	if (pw->sflg.fg_min) theUser->pwage.min_time = pw->sfld.fd_min;
	if (pw->uflg.fg_min) theUser->pwage.min_time = pw->ufld.fd_min;
E 4
I 4
D 6
	if (pw->sflg.fg_min) theUser->pwage.can_change = pw->sfld.fd_min;
	if (pw->uflg.fg_min) theUser->pwage.can_change = pw->ufld.fd_min;
E 6
I 6
	if (pw->sflg.fg_min)
		theUser->pwage.can_change = pw->sfld.fd_min;
	if (pw->uflg.fg_min)
		theUser->pwage.can_change = pw->ufld.fd_min;
E 6
E 4

	/* Time of last password change */
D 6
	if (pw->uflg.fg_schange) theUser->pwage.last_change = pw->ufld.fd_schange;
E 6
I 6
	if (pw->uflg.fg_schange)
		theUser->pwage.last_change = pw->ufld.fd_schange;
E 6

	/* Password expiration time */
D 4
	if (pw->sflg.fg_lifetime) theUser->pwage.max_time = pw->sfld.fd_lifetime;
	if (pw->uflg.fg_lifetime) theUser->pwage.max_time = pw->ufld.fd_lifetime;
E 4
I 4
D 6
	if (pw->sflg.fg_lifetime) theUser->pwage.must_change = pw->sfld.fd_lifetime;
	if (pw->uflg.fg_lifetime) theUser->pwage.must_change = pw->ufld.fd_lifetime;
E 6
I 6
	if (pw->sflg.fg_lifetime)
		theUser->pwage.must_change = pw->sfld.fd_lifetime;
	if (pw->uflg.fg_lifetime)
		theUser->pwage.must_change = pw->ufld.fd_lifetime;
E 6
E 4
D 3
	theUser->pwage.doit = 1;
E 3
I 3
	theUser->mpw_age = "x";
E 3
}

D 5

E 5
I 5
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
E 5
public void
update_shadow(theUser, newUser)
	struct mpasswd	*theUser;
	struct mpasswd	*newUser;
{
	struct pr_passwd *pw,		/* Auth password db lookup temp */
			 px;		/* Auth password update temp */
	int	pwdepth = 0;		/* Depth of password dictionary */
I 8
	struct pw_svc *svc = get_pwsvc();
E 8

D 4
	if (SecurityLevel != sec_OSFenhanced)
E 4
I 4
D 8
	if (svc.SecurityLevel != sec_OSFenhanced)
E 8
I 8
	if (svc->SecurityLevel != sec_OSFenhanced)
E 8
E 4
		return;
	if ((pw = getprpwnam(newUser->mpw_name)) == NULL) {
		logdie("Cannot get shadow password for %s\n",
			newUser->mpw_name);
	}
D 2
	if (DebugLevel >= DB_UPDATE) {
		printf("get_shadow: update auth for %s\n", newUser->mpw_name);
		fflush(stdout);
	}
E 2
I 2
D 6
	debug(DB_UPDATE, "get_shadow: update auth for %s\n", newUser->mpw_name);
E 6
I 6
	debug(DB_UPDATE, "update_shadow: auth for %s\n", newUser->mpw_name);
E 6

E 2
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

D 2
	if (DebugLevel >= DB_UPDATE) {
		printf("update_shadow: updated auth for %s\n",
			newUser->mpw_name);
		fflush(stdout);
	}
E 2
I 2
	debug(DB_UPDATE, "update_shadow: updated auth for %s\n",
		newUser->mpw_name);
E 2
}

D 7
#ifdef	DEBUG
E 7
I 7
#if	(CDEBUG >= CDEBUG_SYSTEM)
E 7
/*
D 5
 * Dump OSF/1 auth database fields & flags structures
E 5
I 5
 * dump_authent
 *	Dump OSF/1 auth database fields & flags structures
 * Usage
 *	dump_authent(struct pr_flag *flags, struct pr_field *fields);
E 5
 */
D 5
dump_field(f, p)
E 5
I 5
private void
dump_authent(f, p)
E 5
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
I 9

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

E 9
/* End %M% */
E 1
