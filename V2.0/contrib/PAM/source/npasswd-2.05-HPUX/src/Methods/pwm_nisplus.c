/*
 */

#ifndef	lint
static char id[] = "@(#)pwm_nisplus.c	1.1 12/17/96 (cc.utexas.edu) /usr/share/src/private/ut/share/bin/passwd/V2.0/src/Methods/SCCS/s.pwm_nisplus.c";
#endif

#include "npasswd.h"

#include <rpc/rpc.h>
#include <rpcsvc/nis.h>
#include <rpc/key_prot.h>

#include "pwm_defs.h"


#ifdef	HAS_NISPASSWD
#include <rpcsvc/nispasswd.h>
#endif

/*
 * Columns of passwd table (corresponding struct passwd field)
 */
#define	PWTABLE		"passwd.org_dir"
#define	PASSWD_NAME	0	/* pw_name (column 0) */
#define	PASSWD_PASSWD	1	/* pw_passwd (column 1) */
#define	PASSWD_UID	2	/* pw_uid (column 2) */
#define	PASSWD_GID	3	/* pw_gid (column 3) */
#define	PASSWD_GECOS	4	/* pw_gecos (column 4) */
#define	PASSWD_DIR	5	/* pw_dir (column 5) */
#define	PASSWD_SHELL	6	/* pw_shell (column 6) */
#define	PASSWD_SHADOW	7	/* pw_age (column 7) */
#define	PASSWD_NCOLS	8	/* How many columns there are */

/*
 * Columns of cred table (not all are used here)
 */
#define	CREDTABLE	"cred.org_dir"	/* Name of the credentials table */
#define	CRED_CNAME	0	/* principal name (column 0) */
#define	CRED_AUTHTYPE	1	/* cred type (column 1) */
#define	CRED_NETNAME	2	/* netname (column 2) */
#define	CRED_PKEY	3	/* public key (column 3) */
#define	CRED_SKEY	4	/* secret key (column 4) */
#define	CRED_NCOLS	5	/* How many columns there are */

#define	fixname(b)	{ if (b[strlen(b)-1] != '.') strcat(b,"."); }

public struct nisinfo nisinfo = { 0 };

public void
init_nis(argc, argv)
	int	argc;		/*NOTUSED*/
	char	**argv;		/*NOTUSED*/
{
	struct nis_result	*lookup;
	NIS_name		nis_name;

	nisinfo.domain = strdup(nis_local_directory());
	nisinfo.principal = strdup(nis_local_principal());

	/*
	 * Sanity check that the passwd table exists
	 */
	(void) sprintf(nis_name, "%s.%s", PWTABLE, nisinfo.domain);
	debug(DB_LOOKUP, "init_nis: verify table '%s'\n", nis_name);
	lookup = nis_lookup(nis_name, FOLLOW_LINKS);
	if (lookup->status != NIS_SUCCESS) {
		nis_freeresult(lookup);
		debug(DB_LOOKUP, "init_nis: No table %s\n", nis_name);
		nisinfo.status = NO_PASSWD_TABLE;
		return;
	}
	if (lookup->objects.objects_val[0].zo_data.zo_type != TABLE_OBJ) {
		nis_freeresult(lookup);
		warn("init_nis: Invalid table %s\n", nis_name);
		nisinfo.status = NO_PASSWD_TABLE;
		return;
	}
	nis_freeresult(lookup);
}

public int
get_nis_user(name, mp)
	char	*name;
	struct mpasswd	*mp;
{
	struct nis_result	*lookup;
	NIS_name		nis_name;
	nis_object		*pwdobj;
	struct pw_opaque	*opdata = mp->opaque;

	if (opdata->nisinfo == 0)
		opdata->dbinfo.nisinfo = &nisinfo;

	(void) sprintf(nis_name, "[name=%s], %s.%s",
		name, PWTABLE, nisinfo.domain);

	debug(DB_LOOKUP, "get_nis_user: get '%s'\n", nis_name);

	if (nisinfo.status == NO_PASSWD_TABLE) {
		debug(DB_LOOKUP, "get_nis_user: bad passwd table\n");
		return(0);
	}

	lookup = nis_list(nis_name,
		USE_DGRAM+FOLLOW_LINKS+FOLLOW_PATH, NULL, NULL);
	if (lookup->status != NIS_SUCCESS) {
		nis_freeresult(lookup);
		if (lookup->status != NIS_NOTFOUND)
			nis_perror("get_nis_user: NIS lookup error"); /* XX */
		return(0);
	}
	debug(DB_LOOKUP, "get_nis_user: found %s\n", name);

	pwdobj = NIS_RES_OBJECT(lookup);

	/*
	 * Fill in the passwd structure
	 */
#define	fetchint(_F_,_C_,_T_)  _F_ = (_T_) atoi(ENTRY_VAL(pwdobj, _C_))
#define	fetchstring(_F_,_C_) _F_ = strdup(ENTRY_VAL(pwdobj, _C_))

	fetchstring(mp->mpw_name, PASSWD_NAME);
	fetchstring(mp->mpw_passwd, PASSWD_PASSWD);
	fetchint(mp->mpw_uid, PASSWD_UID, Uid_t);
	fetchint(mp->mpw_gid, PASSWD_GID, Gid_t);
	fetchstring(mp->mpw_gecos, PASSWD_GECOS);
	fetchstring(mp->mpw_dir, PASSWD_DIR);
	fetchstring(mp->mpw_shell, PASSWD_SHELL);
	fetchstring(mp->mpw_age, PASSWD_SHADOW);
	unpack_pwage(mp, ENTRY_VAL(pwdobj, PASSWD_SHADOW));	/* XXX */

	nis_freeresult(lookup);
	return(1);
#undef	fetchstring
#undef	fetchint
}

/*
 * put_nis_user 
 *	Put a modified passwd table entry for a user 
 *
 * nis_error = nis_putuser(struct passwd *pwp, struct spwd *shp);
 *
 * Returns: NIS error codes
 */
put_nis_user(theUser, newUser, flags)
	struct mpasswd *theUser;
	struct mpasswd *newUser;
	int		flags;
{
	nis_object	*pwdobj,		/* Passwd lookup object */
			*newobj;		/* New passwd object */
	struct nis_result *lookup = 0,		/* Lookup temp */
			  *change = 0;		/* Passwd change */
	entry_col	newpw[PASSWD_NCOLS];		/* New entry vector */
	char		shentry[64];		/* Shadow field buffer */
	NIS_name	nis_name,		/* NIS name buffer */
			owner;			/* Passwd table owner */
	nis_error	status;			/* Return code */

	if (nisinfo.status == NO_PASSWD_TABLE) {
		debug(DB_LOOKUP, "put_nis_user: bad passwd table\n");
		return(0);
	}

#ifndef	HAS_NISPASSWD

#define	change_string(_F_,_C_,_M_) \
		newpw[_C_].ec_value.ec_value_val = _F_;\
		newpw[_C_].ec_value.ec_value_len = strlen(_F_) + 1;\
		newpw[_C_].ec_flags = EN_MODIFIED | _M_;\

#ifdef	HAS_MEMSET
	memset((char *)&newpw, 0, sizeof(newpw));
#else
	bzero((char *)&newpw, sizeof(newpw));
#endif

	/*
	 * Build shadow column entry
	 * The value "-1" is becomes a null string for the time fields
	 */

	/* Now look for the user */
	(void) sprintf(nis_name, "[name=%s],%s.%s",
			theUser->mpw_name, PWTABLE, nisinfo.domain);
	lookup = nis_list(nis_name,
		USE_DGRAM+FOLLOW_LINKS+FOLLOW_PATH, NULL, NULL);

	if (lookup->status != NIS_SUCCESS) {
		warn("Error in lookup\n");
		return;		/* XXX */
	}
	pwdobj = NIS_RES_OBJECT(lookup); 

	if (flags & CHG_PW) {
		if (strcmp(theUser->mpw_passwd, newUser->mpw_passwd) {
			change_string(newUser->mpw_passwd,
				PASSWD_PASSWD, EN_CRYPT);
		}
	}
	if (flags & CHG_PWAGE) {
		char	newshadow[64],
			nb[16];

		oldshadow = ENTRY_VAL(pwdobj, PASSWD_SHADOW);
		shp = unpack_pwage();		/* XXX */

		newshadow[0] = 0;
#define	shadd(_I_, _V_,_F_,_S_) nb[0] = 0; \
if (_I_ != _V_) sprintf(nb, _F_, _I_); \
strcat(newshadow, nb); strcat(newshadow, _S_);

		newshadow[0] = 0;
		shadd(newUser->pwage.last_change, -1, "%ld", ":");
		shadd(newUser->pwage.can_change, -1, "%ld", ":");
		shadd(newUser->pwage.must_change, -1, "%ld", ":");
		shadd(newUser->pwage.warn_user, -1, "%ld", ":");
		shadd(shp->sp_inact, -1, "%ld", ":"); /* XXX */
		shadd(shp->sp_expire, -1, "%ld", ":"); /* XXX */
		shadd(shp->sp_flag, 0, "%lu", ""); /* XXX */
#undef	shadd
		if (strcmp(oldshadow, newshadow) {
			change_string(newshadow, PASSWD_SHADOW, EN_CRYPT);
		}
	}
	if (flags & CHG_FN)
		change_string(newUser->mpw_gecos, PASSWD_GECOS, 0);
	if (flags & CHG_SH)
		change_string(newUser->mpw_shell, PASSWD_SHELL, 0);
#undef	change_string

	/*
	 * Clone the lookup object and use as template
	 */
	newobj = nis_clone_object(NIS_RES_OBJECT(lookup), NULL);
	newobj->EN_data.en_cols.en_cols_val = newpw;
	newobj->EN_data.en_cols.en_cols_len = PASSWD_NCOLS;

	(void) sprintf(nis_name, "[name=%s],passwd.%s",
		pwp->pw_name, NIS_RES_OBJECT(lookup)->zo_domain); 

	change = nis_modify_entry(nis_name, newobj, NULL);
	status = change->status;
	if (change->status != NIS_SUCCESS)
		nis_perror(change->status,
			"Cannot update passwd entry");
	if (flags & CHG_PW) {
		/* Update creditials */
	}
#else
	die("Don't know how to use nispasswd yet\n");
#endif
}


#ifndef	HAS_NISPASSWD

#define	CredLookupFlags	USE_DGRAM+FOLLOW_LINKS+FOLLOW_PATH
#define	CredLookupKey(_B_,_U_)\
	 (void) sprintf(_B_, "[cname=%s.%s,auth_type=DES], %s.%s",\
		_U_, nisinfo.domain, CREDTABLE, nisinfo.domain)

typedef	char	DES_key[HEXKEYBYTES + KEYCHECKSUMSIZE + 1];
typedef char	NIS_name[NIS_MAXNAMELEN + 1];

/*
 * nis_putcred - Update DES credentials for a user
 *
 * Returns: 
 *	    NIS_NOT_ME - old password invalid
 *	    NIS_S_NOTFOUND - empty creditials
 *	Other NIS result codes
 */
nis_putcred (
	const char *user,		/* User name */
	const char *oldpass,		/* Old password (plaintext) */
	const char *newpass)		/* New password (plaintext) */
{
	struct nis_result
			*lookup,		/* Cred lookup result */
			*change;		/* Cred update result */
	DES_key		new_secret_key,		/* New secret key */
			cur_secret_key;		/* Current secret key */
	nis_object	*getobj,		/* Cred fetch object */
			*putobj;		/* Cred update object */
	entry_col	newcred[CRED_NCOLS],	/* New entry vector */
			*savecols;		/* Save pointer */
	nis_error	rc;			/* Return status */
	NIS_name	nis_name;		/* NIS name buffer */
	char	*t;				/* Temporary */
#define	error_return(_C_) { nis_freeresult(lookup); return(_C_); }

	CredLookupKey(nis_name, user);
	lookup = nis_list(nis_name, CredLookupFlags, NULL, NULL);
	if ((rc = lookup->status) != NIS_SUCCESS)
		error_return(rc); 	/* No credentials for <user> */

	getobj = NIS_RES_OBJECT(lookup);
	if (t = ENTRY_VAL(getobj, CRED_SKEY)) 
		memcpy(cur_secret_key, t, sizeof(cur_secret_key));
	else
		error_return(NIS_S_NOTFOUND);

	/*
	 * Make sure the old password decrypts the secret key
	 */
	if (xdecrypt(cur_secret_key, oldpass) == 0)
		error_return(NIS_NOT_ME);
	if (memcmp(cur_secret_key, &cur_secret_key[HEXKEYBYTES], KEYCHECKSUMSIZE))
		error_return(NIS_NOT_ME);

	/*
	 * Make the new secret key
	 */
	memcpy(new_secret_key, cur_secret_key, HEXKEYBYTES);
	memcpy(&new_secret_key[HEXKEYBYTES], cur_secret_key, KEYCHECKSUMSIZE);
	new_secret_key[KEYCHECKSUMSIZE + HEXKEYBYTES] = 0;

	/*
	 * Encrypt the new key
	 */
	if (xencrypt(new_secret_key, newpass) == 0)
		error_return(NIS_NOT_ME);

	memset((char *)&newcred, 0, sizeof(newcred));
	putobj = nis_clone_object(getobj, NULL);
	nis_freeresult(lookup);		/* No longer need the lookup result */
#undef	error_return

	/*
	 * Save the column data so that it can be freed later
	 */
	savecols = putobj->EN_data.en_cols.en_cols_val;
	putobj->EN_data.en_cols.en_cols_val = newcred;
	putobj->EN_data.en_cols.en_cols_len = CRED_NCOLS;

	/*
	 * Setup the new column data
	 */
	newcred[CRED_SKEY].ec_value.ec_value_val = new_secret_key;
	newcred[CRED_SKEY].ec_value.ec_value_len = strlen(new_secret_key) + 1;
	newcred[CRED_SKEY].ec_flags = EN_MODIFIED | EN_CRYPT;

	/*
	 * Update the NIS+ entry
	 */
	change = nis_modify_entry(nis_name, putobj, NULL);

	putobj->EN_data.en_cols.en_cols_val = savecols; /* Put the old data back ... */
	nis_destroy_object(putobj);	/* ... and free the cloned object */

	rc = change->status;
	nis_freeresult(change);		/* Free the result object */
	return(rc);			/* Return the update status */
}
#endif

