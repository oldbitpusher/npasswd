/*
 * NIS+ cred table manipulation routines
 *
 * Compile with Sun C compiler, using option "-Xa" (ANSI mode)
 *
 * Routines in this module:
 *
 * nis_getcred()
 * nis_putcred()
 *
 * Libaries needed: -lnsl 
 * Routines needed: xencrypt() and xdecrypt()
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <crypt.h>
#include <rpc/rpc.h>
#include <rpcsvc/nis.h>
#include <rpc/key_prot.h>

#ifndef	lint
static char	sccsid[] = "@(#)nis_cred.c	1.1 04/16/96 (cc.utexas.edu) /usr/share/src/private/ut/share/bin/passwd/nisplus/SCCS/s.nis_cred.c";
#endif

/*
 * Columns of cred table (not all are used here)
 */
#define	CRED_CNAME	0	/* principal name (column 0) */
#define	CRED_AUTHTYPE	1	/* cred type (column 1) */
#define	CRED_NETNAME	2	/* netname (column 2) */
#define	CRED_PKEY	3	/* public key (column 3) */
#define	CRED_SKEY	4	/* secret key (column 4) */
#define	CRED_NCOLS	5	/* How many columns there are */

#define	CREDTABLE	"cred.org_dir"	/* Name of the credentials table */

typedef	char	des_key[HEXKEYBYTES + KEYCHECKSUMSIZE + 1];

#define	CredLookupFlags	USE_DGRAM+FOLLOW_LINKS+FOLLOW_PATH
#define	CredLookupKey(_B_,_U_)\
	 (void) sprintf(_B_, "[cname=%s.%s,auth_type=DES], %s.%s",\
		_U_, domain, CREDTABLE, domain)

static char	*domain = 0;	/* NIS domain name */

/*
 * nis_getcred
 *	Fetch a cred table entry
 *
 * nis_error = nis_getuser(char *who, struct passwd *pwrv, struct spwd *shrv)
 *
 * Returns: NIS error codes
 */
nis_error nis_getcred (
	const char *user,
	char *publickey, char *privatekey)
{
	struct nis_result
			*lookup;		/* Cred lookup result */
	nis_object	*credobj;		/* Cred object */
	nis_error	rc;			/* Return code */
	char		nis_name[NIS_MAXNAMELEN]; /* NIS name buffer */
	char		*t;			/* Temporary */

	if (domain == NULL)
		domain = nis_local_directory();

	CredLookupKey(nis_name, user);
	lookup = nis_list(nis_name, CredLookupFlags, NULL, NULL);
	rc = lookup->status;

	if (rc != NIS_SUCCESS) {
		nis_freeresult(lookup);
		return(rc);
	}
	credobj = NIS_RES_OBJECT(lookup);

	publickey[0] = 0;
	if ((t = ENTRY_VAL(credobj, CRED_PKEY)))
		strcpy(publickey, t);

	privatekey[0] = 0;
	if ((t = ENTRY_VAL(credobj, CRED_SKEY)))
		strcpy(privatekey, t);

	nis_freeresult(lookup);
	return(rc);
}

/*
 * nis_putcred - Update DES credentials for a user
 *
 * Returns: 
 *	    NIS_NOT_ME - old password invalid
 *	    NIS_S_NOTFOUND - empty creditials
 *	Other NIS result codes
 */
nis_error nis_putcred (
	const char *user,		/* User name */
	const char *oldpass,		/* Old password (plaintext) */
	const char *newpass)		/* New password (plaintext) */
{
	struct nis_result
			*lookup,		/* Cred lookup result */
			*change;		/* Cred update result */
	des_key		new_secret_key,		/* New secret key */
			cur_secret_key;		/* Current secret key */
	nis_object	*getobj,		/* Cred fetch object */
			*putobj;		/* Cred update object */
	entry_col	newcred[CRED_NCOLS],	/* New entry vector */
			*savecols;		/* Save pointer */
	nis_error	rc;			/* Return status */
	char	nis_name[NIS_MAXNAMELEN];	/* NIS name buffer */
	char	*t;				/* Temporary */
#define	error_return(_C_) { nis_freeresult(lookup); return(_C_); }

	if (domain == NULL)
		domain = nis_local_directory();

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

#ifdef	TEST
main(c,v)
char	**v;
{
	char	pub[512], priv[512];
	char	p1[512], p2[512];

	for (v++; *v; v++) {
		nis_error	i;

		printf("\nUser name '%s'\n", *v);
		i = nis_getcred(*v, pub, priv);
		if (i != NIS_SUCCESS) {
			nis_perror(i, "get cred");
		} else {
/* 			printf("%s %s %s\n", *v, pub, priv); */
		}
		printf("\n");
		sprintf(pub, "old password for %s: ", *v);
		strcpy(p1, getpass(pub));
		sprintf(pub, "new password for %s: ", *v);
		strcpy(p2, getpass(pub));
		i = nis_putcred(*v, p1, p2);
		if (i != NIS_SUCCESS) {
			nis_perror(i, "put cred");
			exit(1);
		}
		i = nis_getcred(*v, pub, priv);
		if (i != NIS_SUCCESS) {
			nis_perror(i, "get cred 2");
		} else {
			printf("%s %s %s\n", *v, pub, priv);
		}
	}
	exit(0);
}
#endif
/* End nis_cred.c */
