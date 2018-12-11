h44224
s 00582/00000/00000
d D 1.1 96/04/16 17:35:57 clyde 1 0
c date and time created 96/04/16 17:35:57 by clyde
e
u
U
f e 0
t
T
I 1
/*
 * NIS+ passwd table manipulation routines
 *
 * Compile with Sun C compiler, using option "-Xa" (ANSI mode)
 *
 * Routines in this module:
 *
 * nis_putspent() - Put shadow entry
 * nis_putpwent() - Put passwd entry
 * nis_getpwnam() - Get passwd entry (by name)
 * nis_getpwuid() - Get passwd entry (by uid)
 * nis_getspnam() - Get shadow entry (by name)
 * nis_getuser() - Internal routine 
 * nis_putuser() - Internal routine
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <shadow.h>
#include <string.h>
#include <rpc/rpc.h>
#include <rpcsvc/nis.h>

#define	PWTABLE		"passwd.org_dir"	/* Name of the password table */

#ifndef	lint
static char	sccsid[] = "%W% %G% (cc.utexas.edu) %P%";
#endif

/*
 * Columns of passwd table entry (corresponding struct passwd field)
 */
#define	PWCOL_NAME	0	/* pw_name (column 0) */
#define	PWCOL_PASSWD	1	/* pw_passwd (column 1) */
#define	PWCOL_UID	2	/* pw_uid (column 2) */
#define	PWCOL_GID	3	/* pw_gid (column 3) */
#define	PWCOL_GECOS	4	/* pw_gecos (column 4) */
#define	PWCOL_DIR	5	/* pw_dir (column 5) */
#define	PWCOL_SHELL	6	/* pw_shell (column 6) */
#define	PWCOL_SHADOW	7	/* pw_age (column 7) */
#define	NPWCOL		8	/* How many columns there are */

static char	*domain = 0;	/* NIS domain name */
nis_error	nis_pwerrno = NIS_SUCCESS;	/* Backdoor error code return */

/*
 * nis_getuser 
 *	Fetch a passwd table entry and return in passwd/shadow structures
 *
 * nis_error = nis_getuser(char *who, struct passwd *pwrv, struct spwd *shrv)
 *	Either <pwrv> or <shrv> can be null.
 *
 * Returns: NIS error codes
 */
/* static */
nis_error nis_getuser(char *query, struct passwd *pwrv, struct spwd *shrv)
{
	struct nis_result *lookup;		/* Lookup temp */
	nis_object	*pwdobj;		/* New entry object */
	char	nis_name[NIS_MAXNAMELEN];	/* NIS name buffer */


	if (domain == NULL)
		domain = nis_local_directory();
	(void) sprintf(nis_name, "%s.%s", PWTABLE, domain);
	lookup = nis_lookup(nis_name, FOLLOW_LINKS);
	if (lookup->status != NIS_SUCCESS) {
		nis_freeresult(lookup);
		return(nis_pwerrno = lookup->status);
	}
	if (lookup->objects.objects_val[0].zo_data.zo_type != TABLE_OBJ) {
		nis_freeresult(lookup);
		return(nis_pwerrno = NIS_FAIL);		/* XXX what code? */
	}
	nis_freeresult(lookup);		/* Done with that incarnation */

	/*
	 * The table is ok - now look for the user 
	 */
	(void) sprintf(nis_name, "%s,%s.%s", query, PWTABLE, domain);
	lookup = nis_list(nis_name,
		USE_DGRAM+FOLLOW_LINKS+FOLLOW_PATH, NULL, NULL);

	if (lookup->status != NIS_SUCCESS) {
		nis_freeresult(lookup);
		return(nis_pwerrno = lookup->status);
	}
	pwdobj = NIS_RES_OBJECT(lookup);

	/*
	 * If storage for (struct passwd *) provided, fill it
	 */

	/* Convenience macros */
#define	fetchint(_F_,_C_)  _F_ = atoi(ENTRY_VAL(pwdobj, _C_))
#define	fetchstring(_F_,_C_) { \
	char *t = ENTRY_VAL(pwdobj, _C_);\
	_F_ = malloc(strlen(t)+1);\
	(void) strcpy(_F_, t);\
	}

#define skipc while (*p && *p != ':' && *p != '\n') ++p; if (*p) *p++ = 0
	if (pwrv) {
		fetchstring(pwrv->pw_name, PWCOL_NAME);
		fetchstring(pwrv->pw_passwd, PWCOL_PASSWD);
		fetchint(pwrv->pw_uid, PWCOL_UID);
		fetchint(pwrv->pw_gid, PWCOL_GID);
		fetchstring(pwrv->pw_gecos, PWCOL_GECOS);
		fetchstring(pwrv->pw_dir, PWCOL_DIR);
		fetchstring(pwrv->pw_shell, PWCOL_SHELL);
		fetchstring(pwrv->pw_age, PWCOL_SHADOW);
	}
	/*
	 * If storage for (struct spwd *) provided, fill it
	 */
	if (shrv) {
		char	*p = ENTRY_VAL(pwdobj, PWCOL_SHADOW);

		shrv->sp_lstchg = ( *p != ':' ? atol(p) : -1); skipc;
		shrv->sp_min = ( *p != ':' ? atol(p) : -1); skipc;
		shrv->sp_max = ( *p != ':' ? atol(p) : -1); skipc;
		shrv->sp_warn = ( *p != ':' ? atol(p) : -1); skipc;
		shrv->sp_inact = ( *p != ':' ? atol(p) : -1); skipc;
		shrv->sp_expire = ( *p != ':' ? atol(p) : -1); skipc;
		shrv->sp_flag = atoi(p); skipc;
		fetchstring(shrv->sp_namp, PWCOL_NAME);
		fetchstring(shrv->sp_pwdp, PWCOL_PASSWD);
	}
	nis_freeresult(lookup);
	return(NIS_SUCCESS);
#undef	skipc
#undef	fetchstring
#undef	fetchint
}

/*
 * nis_putuser 
 *	Put a modified passwd table entry for a user 
 *
 * nis_error = nis_putuser(struct passwd *pwp, struct spwd *shp);
 *
 * Returns: NIS error codes
 */
/* static */
nis_error nis_putuser(struct passwd *pwp, struct spwd *shp)
{
	nis_object	*pwdobj,		/* Passwd lookup object */
			*newobj;		/* New passwd object */
	struct nis_result *lookup = 0,		/* Lookup temp */
			  *change = 0;		/* Passwd change */
	entry_col	newpw[NPWCOL];		/* New entry vector */
	char		shentry[64];		/* Shadow field buffer */
	char		nis_name[NIS_MAXNAMELEN],	/* NIS name buffer */
			owner[NIS_MAXNAMELEN];		/* Passwd table owner */
	char		uidb[16],		/* Printable form of pw_uid */
			gidb[16];		/* Printable form of pw_gid */
	nis_error	status;			/* Return code */

	/* Convenience macros */
#define	change_int(_F_,_C_,_B_) if (atoi(ENTRY_VAL(pwdobj, _C_)) != _F_) {\
		(void) sprintf(_B_, "%lu", _F_);\
		newpw[_C_].ec_value.ec_value_val = _B_;\
		newpw[_C_].ec_value.ec_value_len = strlen(_B_) + 1;\
		newpw[_C_].ec_flags = EN_MODIFIED;\
	}
#define	change_string(_F_,_C_,_M_) if (strcmp(ENTRY_VAL(pwdobj, _C_),_F_)) {\
		newpw[_C_].ec_value.ec_value_val = _F_;\
		newpw[_C_].ec_value.ec_value_len = strlen(_F_) + 1;\
		newpw[_C_].ec_flags = EN_MODIFIED | _M_;\
	}

#define	set_int(_F_,_C_,_B_) (void) sprintf(_B_, "%lu", _F_);\
		newpw[_C_].ec_value.ec_value_val = _B_;\
		newpw[_C_].ec_value.ec_value_len = strlen(_B_) + 1;\
		newpw[_C_].ec_flags = EN_MODIFIED;

#define	set_string(_F_,_C_,_M_) newpw[_C_].ec_value.ec_value_val = _F_;\
		newpw[_C_].ec_value.ec_value_len = strlen(_F_) + 1;\
		newpw[_C_].ec_flags = EN_MODIFIED | _M_;

	if (domain == NULL)
		domain = nis_local_directory();
	memset((char *)&newpw, 0, sizeof(newpw));

	(void) sprintf(nis_name, "%s.%s", PWTABLE, domain);
	lookup = nis_lookup(nis_name, FOLLOW_LINKS);
	if (lookup->status != NIS_SUCCESS) {
		nis_freeresult(lookup);
		return(nis_pwerrno = lookup->status);
	}
	if (lookup->objects.objects_val[0].zo_data.zo_type != TABLE_OBJ) {
		nis_freeresult(lookup);
		return(nis_pwerrno = NIS_FAIL);	/* XXX right code? */
	}
	nis_freeresult(lookup);		/* Done with that */

	/*
	 * Build shadow column entry
	 * The value "-1" is becomes a null string for the time fields
	 */
	if (shp) {
		char	nb[16];
#define	shadd(_I_, _V_,_F_,_S_) nb[0] = 0; \
		if (_I_ != _V_) sprintf(nb, _F_, _I_); \
		strcat(shentry, nb); strcat(shentry, _S_);

		shentry[0] = 0;
		shadd(shp->sp_lstchg, -1, "%ld", ":");
		shadd(shp->sp_min, -1, "%ld", ":");
		shadd(shp->sp_max, -1, "%ld", ":");
		shadd(shp->sp_warn, -1, "%ld", ":");
		shadd(shp->sp_inact, -1, "%ld", ":");
		shadd(shp->sp_expire, -1, "%ld", ":");
		shadd(shp->sp_flag, 0, "%lu", "");
#undef	shadd
	} else {
		(void) strcpy(shentry, pwp->pw_age);
	}

	/* Now look for the user */
	(void) sprintf(nis_name, "[name=%s],%s.%s",
			pwp->pw_name, PWTABLE, domain);
	lookup = nis_list(nis_name,
		USE_DGRAM+FOLLOW_LINKS+FOLLOW_PATH, NULL, NULL);

	switch (lookup->status) {
	case  NIS_SUCCESS:		/* Modify existing entry */
		pwdobj = NIS_RES_OBJECT(lookup);
		/*
		 * Tag the changed columns
		 */
		change_string(pwp->pw_passwd, PWCOL_PASSWD, EN_CRYPT);
		change_int(pwp->pw_uid, PWCOL_UID, uidb);
		change_int(pwp->pw_gid, PWCOL_GID, gidb);
		change_string(pwp->pw_gecos, PWCOL_GECOS, 0);
		change_string(pwp->pw_dir, PWCOL_DIR, 0);
		change_string(pwp->pw_shell, PWCOL_SHELL, 0);
		change_string(shentry, PWCOL_SHADOW, EN_CRYPT);
		/*
		 * Clone the lookup object and use as template
		 */
		newobj = nis_clone_object(NIS_RES_OBJECT(lookup), NULL);
		newobj->EN_data.en_cols.en_cols_val = newpw;
		newobj->EN_data.en_cols.en_cols_len = NPWCOL;

		(void) sprintf(nis_name, "[name=%s],passwd.%s",
			pwp->pw_name, NIS_RES_OBJECT(lookup)->zo_domain); 

		change = nis_modify_entry(nis_name, newobj, NULL);
		status = change->status;
		if (change->status != NIS_SUCCESS)
			nis_perror(change->status,
				"Cannot update passwd entry");
		break;

	case NIS_NOTFOUND: 		/* User not found - need to add */
		/*
		 * Fill in the columns of the entries vector
		 */
		set_string(pwp->pw_name, PWCOL_NAME, 0);
		set_string(pwp->pw_passwd, PWCOL_PASSWD, EN_CRYPT);
		set_int(pwp->pw_uid, PWCOL_UID, uidb);
		set_int(pwp->pw_gid, PWCOL_GID, gidb);
		set_string(pwp->pw_gecos, PWCOL_GECOS, 0);
		set_string(pwp->pw_dir, PWCOL_DIR, 0);
		set_string(pwp->pw_shell, PWCOL_SHELL, 0);
		set_string(shentry, PWCOL_SHADOW, EN_CRYPT);

		/*
		 * Dirty trick - get the first object from the passwd
		 * table and use it as a template for the new object.
		 * It's hopefully better than making assumptions about
		 * what a passwd table entry is supposed look like.
		 */
		(void) sprintf(nis_name, "%s.%s", PWTABLE, domain);
		lookup = nis_first_entry(nis_name);
		if (lookup->status != NIS_SUCCESS) {
			status = lookup->status;
		} else {
			/* Clone the lookup object and use as template */
			newobj = nis_clone_object(
					NIS_RES_OBJECT(lookup), NULL);

			/* Set NIS owner of entry */
			(void) sprintf(owner, "%s.%s", pwp->pw_name, domain);
			newobj->zo_owner = owner;

			/* Point to the entry vector */
			newobj->EN_data.en_cols.en_cols_val = newpw;
			newobj->EN_data.en_cols.en_cols_len = NPWCOL;

			(void) sprintf(nis_name, "[name=%s],passwd.%s",
				pwp->pw_name,
				NIS_RES_OBJECT(lookup)->zo_domain); 

			change = nis_add_entry(nis_name, newobj, 0);
			status = change->status;
			if (change->status != NIS_SUCCESS) 
				nis_perror(change->status,
					"Cannot make new passwd table entry");
		}
		break;

	default:
		status = lookup->status;
		break;
	}
	nis_freeresult(lookup);
	if (change)
		nis_freeresult(change);
	return(status);

#undef	set_string
#undef	set_int
#undef	change_string
#undef	change_int
}

/*
 * nis_putspent - Put shadow entry
 *
 * Return:
 *	0 on success
 *	-1 on failure and nis_pwerrno is set to the NIS error code
 */
nis_putspent(struct spwd *sp)
{
	struct passwd	pw;	/* Temporary */
	char	querybuf[NIS_MAXNAMELEN];	/* NIS search criteria */

	(void) sprintf(querybuf, "[name=%s]", sp->sp_namp);
	if (nis_getuser(querybuf, &pw, NULL) != NIS_SUCCESS)
		return(-1);
	if (nis_putuser(&pw, sp) != NIS_SUCCESS)
		return(-1);
	return(0);
}

/*
 * nis_putpwent - Put passwd entry
 *
 * Return:
 *	0 on success
 *	-1 on failure and nis_pwerrno is set to the NIS error code
 */
nis_putpwent(struct passwd *pw)
{
	return(nis_putuser(pw, NULL) == NIS_SUCCESS ? 0 : -1);
}

/*
 * nis_getpwnam - Get passwd entry by name
 *
 * Return:
 *	Pointer to passwd structure if success
 *	NULL on failure and nis_pwerrno is set to the NIS error code
 */
struct passwd *nis_getpwnam(const char *name)
{
	static struct passwd	pwd;	/* Return (struct passwd) */
	char	querybuf[NIS_MAXNAMELEN];	/* NIS serach criteria */

	memset((char *)&pwd, 0, sizeof(pwd));
	(void) sprintf(querybuf, "[name=%s]", name);
	if (nis_getuser(querybuf, &pwd, NULL) == NIS_SUCCESS)
		return(&pwd);
	else
		return(NULL);
}

/*
 * nis_getpwuid - Get passwd entry by uid
 *
 * Return:
 *	Pointer to passwd structure if success
 *	NULL on failure and nis_pwerrno is set to the NIS error code
 */
struct passwd *nis_getpwuid(const uid_t uid)
{
	static struct passwd	pwd;	/* Temporary */
	char	querybuf[NIS_MAXNAMELEN];	/* NIS serach criteria */

	memset((char *)&pwd, 0, sizeof(pwd));
	(void) sprintf(querybuf, "[uid=%ld]", uid);
	if (nis_getuser(querybuf, &pwd, NULL) == NIS_SUCCESS)
		return(&pwd);
	else
		return(NULL);
}

/*
 * nis_getspnam - Get shadow entry by name
 *
 * Return:
 *	Pointer to shadow structure if success
 *	NULL on failure and nis_pwerrno is set to the NIS error code
 */
struct spwd *nis_getspnam(const char *name)
{
	static struct spwd spwd;	/* Return (struct spwd) */
	struct passwd pwd;		/* Scratch */
	char	querybuf[NIS_MAXNAMELEN];	/* NIS search criteria */

	memset((char *)&pwd, 0, sizeof(pwd));
	memset((char *)&spwd, 0, sizeof(spwd));
	(void) sprintf(querybuf, "[name=%s]", name);
	if (nis_getuser(querybuf, &pwd, &spwd) == NIS_SUCCESS)
		return(&spwd);
	else
		return(NULL);
}

#ifdef	TEST
main(c,v)
char	**v;
{
	struct passwd pw, *xpw;
	struct spwd	*xsp, osp;
	char	xb[30];
	int	xuid = 1000;

	for (v++; *v; v++) {
		int	i;

		printf("\nUser name '%s'\n", *v);

		memset((char *)&pw, 0, sizeof(pw));
		pw.pw_name = *v;
		pw.pw_passwd = (char *)crypt(*v, "O0");
		pw.pw_uid = xuid;
		pw.pw_gid = xuid++;
		sprintf(xb, "made by %d @ %ld", getpid(), time((time_t )0));
		pw.pw_gecos = xb;
		pw.pw_dir = "/tmp/nowhere";
		pw.pw_shell = "/bin/csh";
		pw.pw_age = "1234::::::";

		printf("\nNEW %s:%s:%u:%u:%s:%s:%s:%s\n",
			pw.pw_name, pw.pw_passwd,
			pw.pw_uid, pw.pw_gid, pw.pw_gecos,
			pw.pw_dir, pw.pw_shell, pw.pw_age);

		printf("nis_putpwent() [add] ... ");
		if (nis_putpwent(&pw) < 0) {
			nis_perror(nis_pwerrno, "");
			exit(1);
		}
		printf("success\n");

		printf("nis_getpwnam() [check] ... ");
		if ((xpw = nis_getpwnam(*v)) == NULL) {
			nis_perror(nis_pwerrno, "");
			exit(1);
		}
		printf("success\n");
		cmp_pwent("Creation check ...", &pw, xpw);

#if	0
		printf("\nGET %s:%s:%u:%u:%s:%s:%s:%s\n",
			xpw->pw_name, xpw->pw_passwd,
			xpw->pw_uid, xpw->pw_gid, xpw->pw_gecos,
			xpw->pw_dir, xpw->pw_shell, xpw->pw_age);

#endif
		sprintf(xb, "Changed at @ %ld", time((time_t )0));
		pw.pw_gecos = xb;
		printf("\nChanging pw_gecos to '%s'\n", xb);

		printf("nis_putpwent() [change] ... ");
		if (nis_putpwent(&pw) < 0) {
			nis_perror(nis_pwerrno, "");
			exit(1);
		}
		printf("success\n");

		printf("nis_getpwnam() [check] ... ");
		if ((xpw = nis_getpwnam(*v)) == NULL) {
			nis_perror(nis_pwerrno, "");
			exit(1);
		}
		printf("success\n");
		cmp_pwent("GECOS change check ...", &pw, xpw);

#if	0
		printf("\nGET %s:%s:%u:%u:%s:%s:%s:%s\n",
			xpw->pw_name, xpw->pw_passwd,
			xpw->pw_uid, xpw->pw_gid, xpw->pw_gecos,
			xpw->pw_dir, xpw->pw_shell, xpw->pw_age);
#endif
		/*
		 * Test shadow routines
		 */
		printf("\nTesting shadow get/put routines\n");

		printf("nis_getspnam() ... ");
		if ((xsp = nis_getspnam(*v)) == NULL) {
			nis_perror(nis_pwerrno, "");
			exit(1);
		}
		printf("success\n");

		printf("\n%ld:%ld:%ld:%ld:%ld:%ld:%lu\n",
			xsp->sp_lstchg, xsp->sp_min, xsp->sp_max,
			xsp->sp_warn, xsp->sp_inact, xsp->sp_expire,
			xsp->sp_flag);

		osp = *xsp;

		osp.sp_lstchg = time((time_t *)0) / 86400;
		printf("\nChanging sp_lstchg to %lu\n", osp.sp_lstchg);

		printf("nis_putspent() ... ");
		if (nis_putspent(&osp) < 0) {
			nis_perror(nis_pwerrno, "");
			exit(1);
		}
		printf("success\n");

		printf("nis_getspnam() [check] ... ");
		if ((xsp = nis_getspnam(*v)) == NULL) {
			nis_perror(nis_pwerrno, "");
			exit(1);
		}
		printf("success\n");

		cmp_spent("Shadow change check ... ", &osp, xsp);
#if	0
		printf("\nNEW %ld:%ld:%ld:%ld:%ld:%ld:%lu\n",
			xsp->sp_lstchg, xsp->sp_min, xsp->sp_max,
			xsp->sp_warn, xsp->sp_inact, xsp->sp_expire,
			xsp->sp_flag);

#endif
		printf("\n\nTests done for username '%s'\n", *v);
	}
	printf("\nAll tests done\n");
	exit(0);
}

cmp_pwent(char *comment, struct passwd *one, struct passwd *two)
{
	char	oneb[512],
		twob[512];

	(void) sprintf(oneb, "%s:%s:%u:%u:%s:%s:%s:%s",
			one->pw_name, one->pw_passwd,
			one->pw_uid, one->pw_gid, one->pw_gecos,
			one->pw_dir, one->pw_shell, one->pw_age);
	(void) sprintf(twob, "%s:%s:%u:%u:%s:%s:%s:%s",
			two->pw_name, two->pw_passwd,
			two->pw_uid, two->pw_gid, two->pw_gecos,
			two->pw_dir, two->pw_shell, two->pw_age);
	if (strcmp(oneb, twob)) {
		printf("mismatch\n< %s\n> %s\n", oneb, twob);
		return(0);
	}
	printf("match\n");
	return(1);
}

cmp_spent(char *comment, struct spwd *one, struct spwd *two)
{
	char	oneb[512],
		twob[512];

	(void) sprintf(oneb, "%ld:%ld:%ld:%ld:%ld:%ld:%lu",
		one->sp_lstchg, one->sp_min, one->sp_max,
		one->sp_warn, one->sp_inact, one->sp_expire, one->sp_flag);
	(void) sprintf(twob, "%ld:%ld:%ld:%ld:%ld:%ld:%lu",
		two->sp_lstchg, two->sp_min, two->sp_max,
		two->sp_warn, two->sp_inact, two->sp_expire, two->sp_flag);
	printf("%s ", comment);
	if (strcmp(oneb, twob)) {
		printf("mismatch\n< %s\n> %s\n", oneb, twob);
		return(0);
	}
	printf("match\n");
	return(1);
}
#endif	/* TEST */
/* End %M% */
E 1
