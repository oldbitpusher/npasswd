/*
 * pwm_main.c
 *	Passwd database method entry points
 *
 * Exported routines
 *	pw_getuserbyname()
 *	pw_permission()
 *	pw_replace()
 *	pw_cleanup()
 *
 * Compilation flags
 *	cc -I.. ...
 */
#include "npasswd.h"
#include "pwm_defs.h"

#ifndef lint
static char sccsid[] = "@(#)pwm_main.c	1.14 5/13/00 (cc.utexas.edu)";
#endif

int	get_local_user();
void	put_local_user();

#ifdef	USE_NIS
/*
 * NIS (YP) method table entry
 */
 void	init_yp();
 int	get_yp_user();
 void	put_yp_user();
# define YP_TAB { srv_yp, "NIS", init_yp, get_yp_user, put_yp_user, NULL }
#else
# define YP_TAB { srv_yp, "NIS", NULL, NULL, NULL, NULL }
#endif

#ifdef	USE_NISPLUS
/*
 * NIS+ method table entry (NYI)
 */
 void	init_nis();
 int	get_nis_user();
 void	put_nis_user();
# define NIS_TAB \
	{ srv_nisplus, "NIS+", init_nis, get_nis_user, put_nis_user, NULL }
#else
# define NIS_TAB { srv_nisplus, "NIS+",	NULL, NULL, NULL, NULL }
#endif

#ifdef	USE_KERBEROS
/*
 * Kerberos method table entry (NYI)
 */
 void	init_kerb();
 int	get_kerb_user();
 void	put_kerb_user();
# define KERB_TAB \
	{ srv_kerb, "Kerberos", init_kerb, get_kerb_user, put_kerb_user, NULL }
#else
# define KERB_TAB { srv_kerb, "Kerberos", NULL, NULL, NULL, NULL }
#endif

/*
 * Password database method switch 
 */
struct methodsw {
	enum svc_services service;	/* Service type */
	char	*name;			/* Name */
	void	(*init)();		/* Init routine */
	int	(*get)();		/* Get routine */
	void	(*put)();		/* Put routine */
	void	(*cleanup)();		/* Cleanup routine */
};

/*
 * Passwd database master method switch
 */
private struct methodsw methods[] = {
	{ srv_local,	"local", NULL, get_local_user, put_local_user, NULL },
	YP_TAB,
	NIS_TAB,
	KERB_TAB,
	{ srv_last,	NULL,		NULL, NULL, NULL, NULL }
};

#undef	YP_TAB
#undef	NIS_TAB
#undef	KERB_TAB

/*
 * pw_initialize
 *	Initialize the method routines
 * Usage
 *	pw_initialize();
 */
public void pw_initialize()
{
	struct methodsw	*ms;

	for (ms = methods; ms->service != srv_last; ms++) {
		if (ms->init)
			(*ms->init)();
	}
}

/*
 * pw_getuserbyname
 *	Fetch user information by name
 * Returns
 *	Pointer to mpasswd sturcture if <name> found, 0 otherwise
 * Errors
 *	Failures to allocate memory for mpasswd data
 */
struct mpasswd *
pw_getuserbyname(name)
	char	*name;		/* User name */
{
	struct mpasswd	*mpw;		/* Return mpasswd record */
	struct pw_opaque *xv;		/* Method opaque data block */
	struct pw_svc	*svc = get_pwsvc();
	int	i;

	mpw = (struct mpasswd *)calloc(sizeof(struct mpasswd), 1);
	if (mpw == NULL)
		logdie("Cannot allocate memory for mpasswd data");

	xv = (struct pw_opaque *)calloc(sizeof(struct pw_opaque), 1);
	if (xv == NULL)
		logdie("Cannot allocate memory for opaque data");

	mpw->opaque = (void *)xv;
	xv->sourcePW = srv_unknown;
	xv->sourceSH = srv_unknown;

	for (i = 0; svc->ServiceOrder[i] != srv_last; i++) {
		struct methodsw	*ms;

		for (ms = methods; ms->service != srv_last; ms++) {
			if (ms->service != svc->ServiceOrder[i])
				continue;
			debug(DB_LOOKUP, "pw_getuserbyname: name '%s' get 0x%x\n",
				name, ms->get);
			if (!ms->get) {
				warn("Method \"%s\" not supported.\n",
					ms->name);
				continue;
			}
			if ((*ms->get)(name, mpw)) {
				debug(DB_LOOKUP,
					"pw_getuserbyname: name '%s', return 0x%x\n",
					name, mpw);
				return(mpw);
			}
		}
	}
	return(NULL);
}

/*
 * pw_permission
 *	Check information change permission
 * Returns
 *	A value from <enum chg_perm>
 *
 * This routine is a hook to allow method-dependant permissions
 * checking for updating passwd information.  It is not used but
 * stubbed in for possible future use.
 */
enum chg_perm
pw_permission(theUser, theCaller)
	struct mpasswd	*theUser,
			*theCaller;
{
	return(self);		/* Always say yes right now */
}

/*
 * pw_replace
 *      Update user information
 *	Calls the appropriate method update routine
 * Usage
 *	pw_replace(struct mpasswd *old, struct mpasswd *new, int changes);
 */
public void
pw_replace(theUser, newUser, changes)
	struct mpasswd	*theUser;	/* Old User block */
	struct mpasswd	*newUser;	/* New User block */
	int		changes;	/* What was changed (CHG_X flags) */
{
	struct methodsw	*ms;
	struct pw_opaque *aux = (struct pw_opaque *)theUser->opaque;

	for (ms = methods; ms->service != srv_last; ms++) {
		if (ms->service != aux->sourcePW)
			continue;
		if (!ms->get)		/* Sanity check */
			logdie("Unsupported source \"%s\"!\n", ms->name);
		(*ms->put)(theUser, newUser, changes);
	}
}

/*
 * pw_cleanup
 *	Run method cleanup routines if present
 *	This routine is the bookend for pw_initialize()
 * Usage
 *	pw_cleanup(int code);
 */
public void
pw_cleanup(code)
	int	code;		/* 0 for normal, 1 for abort */
{
	struct methodsw	*ms;

	for (ms = methods; ms->service != srv_last; ms++) {
		if (ms->cleanup)
			(*ms->cleanup)(code);
	}
}

#define	CMAGIC	0x84

/*
 * zncrypt
 *	Trivial string encrypt
 *
 * Returns
 *	Trivally encrypted string which can be free()d
 */
public char *
zncrypt(str)
	char	*str;		/* String to encrypt */
{
	char	*rv = (char *)malloc(strlen(str) + 2);
	char	*rc;

	if (rv == 0)
		logdie("zncrypt cannot allocate memory\n");
	rc = rv;
	*rc++ = CMAGIC;
	while (*str)
		*rc++ = (*str++ ^ CMAGIC);
	*rc = 0;
	return(rv);
}

/*
 * zdcrypt
 *	Trivial string decrypt
 *
 * Returns
 *	Trivally decrypted string which can be free()d
 */
public char *
zdcrypt(str)
	char	*str;		/* Cyphertext */
{
	char	*rv,
		*rc;

	if ((*str & 0xff) != CMAGIC)
		return(str);
	rv = (char *)malloc(strlen(str) + 2);
	if (rv == 0)
		logdie("zncrypt cannot allocate memory\n");
	str++;
	rc = rv;
	while (*str)
		*rc++ = (*str++ ^ CMAGIC);
	*rc = 0;
	return(rv);
}

/* End pwm_main.c */
