h12816
s 00001/00001/00272
d D 1.14 00/05/13 06:18:13 clyde 14 13
c Fix forward decl of method init routine
e
s 00001/00000/00272
d D 1.13 99/02/01 13:50:38 clyde 13 12
c Fix buglet in zncrypt()
e
s 00053/00000/00219
d D 1.12 98/08/17 16:56:32 clyde 12 11
c Flesh out zdcrypt() and zncrypt()
e
s 00003/00002/00216
d D 1.11 98/07/16 09:19:09 clyde 11 10
c Change get_pwsvc() usage
e
s 00002/00013/00216
d D 1.10 98/03/31 14:36:51 clyde 10 9
c 1. Remove table stubs for Hesiod and Netinfo
c 2. Fix erroreous debugging message
e
s 00012/00012/00217
d D 1.9 96/12/17 11:03:01 clyde 9 8
c Rename some method modules
e
s 00009/00005/00220
d D 1.8 96/08/29 13:04:23 clyde 8 7
c 1. Remove 'const' declarations (too much compiler pain)
c 2. Add more debugging
e
s 00099/00053/00126
d D 1.7 96/08/13 15:46:23 clyde 7 6
c 1. Add lots of comments
c 2. Add cleanup() routine to method switch & make pw_cleanup() use it
c 3. Eliminate arguments to pw_initialize()
c 4. Change names of some fields in method switch
e
s 00003/00003/00176
d D 1.6 96/08/09 16:18:10 clyde 6 5
c Beta 3 development checkin 2
e
s 00008/00019/00171
d D 1.5 96/08/06 14:14:22 clyde 5 4
c beta 3 cycle 1 checkin
e
s 00002/00006/00188
d D 1.4 96/04/01 14:14:22 clyde 4 3
c Eliminate the "ypcompat" table
e
s 00002/00000/00192
d D 1.3 96/03/29 11:37:58 clyde 3 2
c Add debugging message
e
s 00012/00004/00180
d D 1.2 95/04/05 16:20:07 clyde 2 1
c Beta 3 development checkin
e
s 00184/00000/00000
d D 1.1 94/09/28 16:17:13 clyde 1 0
c date and time created 94/09/28 16:17:13 by clyde
e
u
U
f e 0
t
T
I 1
D 7

E 7
I 7
/*
 * %M%
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
E 7
#include "npasswd.h"
#include "pwm_defs.h"

#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu)";
#endif

D 9
int	get_local_pw();
void	update_local_pw();
E 9
I 9
int	get_local_user();
void	put_local_user();
E 9

D 2
#ifdef	YP_SUPPORT
E 2
I 2
#ifdef	USE_NIS
I 7
/*
 * NIS (YP) method table entry
 */
E 7
E 2
 void	init_yp();
D 9
 int	get_yp_pw();
 void	update_yp_pw();
D 4
# define YP_TAB \
	{ srv_ypcompat, "local", NULL, get_local_pw, update_local_pw }, \
	{ srv_yp, "NIS", init_yp, get_yp_pw, update_yp_pw }
E 4
I 4
D 7
# define YP_TAB { srv_yp, "NIS", init_yp, get_yp_pw, update_yp_pw }
E 7
I 7
# define YP_TAB { srv_yp, "NIS", init_yp, get_yp_pw, update_yp_pw, NULL }
E 9
I 9
 int	get_yp_user();
 void	put_yp_user();
# define YP_TAB { srv_yp, "NIS", init_yp, get_yp_user, put_yp_user, NULL }
E 9
E 7
E 4
#else
D 4
# define YP_TAB \
	{ srv_ypcompat, "local", NULL, NULL, NULL }, \
	{ srv_yp, "NIS", NULL, NULL, NULL }
E 4
I 4
D 7
# define YP_TAB { srv_yp, "NIS", NULL, NULL, NULL }
E 7
I 7
# define YP_TAB { srv_yp, "NIS", NULL, NULL, NULL, NULL }
E 7
E 4
#endif

D 2
#ifdef	NISPLUS_SUPPORT
E 2
I 2
#ifdef	USE_NISPLUS
I 7
/*
 * NIS+ method table entry (NYI)
 */
E 7
E 2
D 14
 void	init_nisplus();
E 14
I 14
 void	init_nis();
E 14
D 9
 int	get_nisplus_pw();
 void	update_nisplus_pw();
E 9
I 9
 int	get_nis_user();
 void	put_nis_user();
E 9
D 7
# define NIS_TAB { srv_nisplus,	"NIS+", init_nis, get_nis_pw, update_nis_pw }
E 7
I 7
# define NIS_TAB \
D 9
	{ srv_nisplus, "NIS+", init_nis, get_nis_pw, update_nis_pw, NULL }
E 9
I 9
	{ srv_nisplus, "NIS+", init_nis, get_nis_user, put_nis_user, NULL }
E 9
E 7
#else
D 7
# define NIS_TAB { srv_nisplus,	"NIS+",	NULL, NULL, NULL }
E 7
I 7
# define NIS_TAB { srv_nisplus, "NIS+",	NULL, NULL, NULL, NULL }
E 7
#endif

D 2
#ifdef	KEREBOS_SUPPORT
E 2
I 2
#ifdef	USE_KERBEROS
I 7
/*
 * Kerberos method table entry (NYI)
 */
E 7
E 2
 void	init_kerb();
D 9
 int	get_kerb_pw();
 void	update_kerb_pw();
E 9
I 9
 int	get_kerb_user();
 void	put_kerb_user();
E 9
D 7
# define KERB_TAB { srv_kerb, "Kerberos", init_kerb, get_kerb,pw, update_kerb_pw }
E 7
I 7
# define KERB_TAB \
D 9
	{ srv_kerb, "Kerberos", init_kerb, get_kerb,pw, update_kerb_pw, NULL }
E 9
I 9
	{ srv_kerb, "Kerberos", init_kerb, get_kerb_user, put_kerb_user, NULL }
E 9
E 7
#else
D 7
# define KERB_TAB { srv_kerb,	"Kerberos",	NULL,	NULL,	NULL }
E 7
I 7
# define KERB_TAB { srv_kerb, "Kerberos", NULL, NULL, NULL, NULL }
E 7
#endif

I 2
D 10
#ifdef	USE_HESIOD
D 7
	/* Nothing here yet */
E 7
I 7
	/* Hesiod table could go here */
E 7
#endif

#ifdef	USE_NETINFO
D 7
	/* Nothing here yet */
E 7
I 7
	/* Netinfo table could go here */
E 7
#endif

E 10
I 7
/*
 * Password database method switch 
 */
E 7
E 2
struct methodsw {
D 5
	enum svc_order	method;
E 5
I 5
D 6
	enum svc_names	method;
E 6
I 6
D 7
	enum svc_services	method;
E 6
E 5
	char	*type;
	void	(*init)();
	int	(*get)();
	void	(*put)();
E 7
I 7
	enum svc_services service;	/* Service type */
	char	*name;			/* Name */
	void	(*init)();		/* Init routine */
	int	(*get)();		/* Get routine */
	void	(*put)();		/* Put routine */
	void	(*cleanup)();		/* Cleanup routine */
E 7
};

I 7
/*
 * Passwd database master method switch
 */
E 7
private struct methodsw methods[] = {
D 7
	{ srv_local,	"local", NULL, get_local_pw, update_local_pw },
E 7
I 7
D 9
	{ srv_local,	"local", NULL, get_local_pw, update_local_pw, NULL },
E 9
I 9
	{ srv_local,	"local", NULL, get_local_user, put_local_user, NULL },
E 9
E 7
	YP_TAB,
	NIS_TAB,
	KERB_TAB,
D 7
	{ srv_hesiod,	"Hesiod",	NULL,	NULL,	NULL },
	{ srv_niroot,	"Netinfo",	NULL,	NULL,	NULL },
	{ srv_nidot,	"Netinfo",	NULL,	NULL,	NULL },
	{ srv_last,	NULL,		NULL,	NULL,	NULL }
E 7
I 7
D 10
	{ srv_hesiod,	"Hesiod",	NULL, NULL, NULL, NULL },
	{ srv_niroot,	"Netinfo",	NULL, NULL, NULL, NULL },
	{ srv_nidot,	"Netinfo",	NULL, NULL, NULL, NULL },
E 10
	{ srv_last,	NULL,		NULL, NULL, NULL, NULL }
E 7
};

#undef	YP_TAB
#undef	NIS_TAB
#undef	KERB_TAB

/*
D 7
 *	pw_initialize - set up
E 7
I 7
 * pw_initialize
 *	Initialize the method routines
 * Usage
 *	pw_initialize();
E 7
 */
D 7
public void pw_initialize(argc, argv)
	int	argc;		/* NOTUSED */
	char	**argv;		/* NOTUSED */
E 7
I 7
public void pw_initialize()
E 7
{
	struct methodsw	*ms;

D 7
	for (ms = methods; ms->method != srv_last; ms++) {
E 7
I 7
	for (ms = methods; ms->service != srv_last; ms++) {
E 7
		if (ms->init)
D 7
			(*ms->init)(argc, argv);
E 7
I 7
			(*ms->init)();
E 7
	}
}

/*
D 7
 *	pw_getuserbyname - get paswd information by user name.
 *
 *	Returns: Pointer to mpasswd sturcture if <name> found
 *		 NULL otherwise
E 7
I 7
 * pw_getuserbyname
 *	Fetch user information by name
 * Returns
 *	Pointer to mpasswd sturcture if <name> found, 0 otherwise
 * Errors
 *	Failures to allocate memory for mpasswd data
E 7
 */
struct mpasswd *
pw_getuserbyname(name)
D 7
	char	*name;		/* User name */
E 7
I 7
D 8
	const char	*name;		/* User name */
E 8
I 8
	char	*name;		/* User name */
E 8
E 7
{
	struct mpasswd	*mpw;		/* Return mpasswd record */
	struct pw_opaque *xv;		/* Method opaque data block */
I 11
	struct pw_svc	*svc = get_pwsvc();
E 11
	int	i;

	mpw = (struct mpasswd *)calloc(sizeof(struct mpasswd), 1);
	if (mpw == NULL)
		logdie("Cannot allocate memory for mpasswd data");

	xv = (struct pw_opaque *)calloc(sizeof(struct pw_opaque), 1);
	if (xv == NULL)
		logdie("Cannot allocate memory for opaque data");

	mpw->opaque = (void *)xv;
	xv->sourcePW = srv_unknown;
D 2
	xv->sourceSH = srv_local;
E 2
I 2
	xv->sourceSH = srv_unknown;
E 2

D 5
	for (i = 0; ServiceOrder[i] != srv_last; i++) {
E 5
I 5
D 6
	for (i = 0; svc_ServiceOrder[i] != srv_last; i++) {
E 6
I 6
D 11
	for (i = 0; svc.ServiceOrder[i] != srv_last; i++) {
E 11
I 11
	for (i = 0; svc->ServiceOrder[i] != srv_last; i++) {
E 11
E 6
E 5
		struct methodsw	*ms;

D 7
		for (ms = methods; ms->method != srv_last; ms++) {
D 5
			if (ms->method != ServiceOrder[i])
E 5
I 5
D 6
			if (ms->method != svc_ServiceOrder[i])
E 6
I 6
			if (ms->method != svc.ServiceOrder[i])
E 7
I 7
		for (ms = methods; ms->service != srv_last; ms++) {
D 11
			if (ms->service != svc.ServiceOrder[i])
E 11
I 11
			if (ms->service != svc->ServiceOrder[i])
E 11
E 7
E 6
E 5
				continue;
I 3
D 8
			debug(DB_LOOKUP, "pw_getuserbyname: method '%s', get func 0x%x\n",
E 8
I 8
			debug(DB_LOOKUP, "pw_getuserbyname: name '%s' get 0x%x\n",
E 8
D 7
				ms->type, ms->get);
E 7
I 7
D 10
				ms->name, ms->get);
E 10
I 10
				name, ms->get);
E 10
E 7
E 3
			if (!ms->get) {
				warn("Method \"%s\" not supported.\n",
D 7
					ms->type);
E 7
I 7
					ms->name);
E 7
				continue;
			}
D 8
			if ((*ms->get)(name, mpw))
E 8
I 8
			if ((*ms->get)(name, mpw)) {
				debug(DB_LOOKUP,
					"pw_getuserbyname: name '%s', return 0x%x\n",
D 10
					ms->name, mpw);
E 10
I 10
					name, mpw);
E 10
E 8
				return(mpw);
I 8
			}
E 8
		}
	}
	return(NULL);
}

/*
D 7
 *	pw_permission - check information change permission
E 7
I 7
 * pw_permission
 *	Check information change permission
 * Returns
 *	A value from <enum chg_perm>
E 7
 *
D 7
 *	Returns 1 if information can be changed
 *		0 if not
 *
 *	This routine does method-dependant permissions checking for updating
 *	passwd information.
E 7
I 7
 * This routine is a hook to allow method-dependant permissions
 * checking for updating passwd information.  It is not used but
 * stubbed in for possible future use.
E 7
 */
enum chg_perm
pw_permission(theUser, theCaller)
D 7
	struct mpasswd	*theUser,
			*theCaller;
E 7
I 7
D 8
	const struct mpasswd	*theUser,
				*theCaller;
E 8
I 8
	struct mpasswd	*theUser,
			*theCaller;
E 8
E 7
{
	return(self);		/* Always say yes right now */
}

/*
D 7
 *      pw_replace - replace password in passwd file 
E 7
I 7
 * pw_replace
 *      Update user information
 *	Calls the appropriate method update routine
 * Usage
 *	pw_replace(struct mpasswd *old, struct mpasswd *new, int changes);
E 7
 */
public void
D 5
pw_replace(theUser, newpw, newfn, newsh)
	struct mpasswd	*theUser;	/* User block */
	char	*newpw,			/* New password (encrypted) */
		*newfn,			/* New full name */
		*newsh;			/* New shell */
E 5
I 5
pw_replace(theUser, newUser, changes)
	struct mpasswd	*theUser;	/* Old User block */
	struct mpasswd	*newUser;	/* New User block */
D 7
	int		changes;	/* What was changed */
E 7
I 7
	int		changes;	/* What was changed (CHG_X flags) */
E 7
E 5
{
	struct methodsw	*ms;
	struct pw_opaque *aux = (struct pw_opaque *)theUser->opaque;
D 5
	struct mpasswd	newUser;
	int	changes = 0;
E 5

D 5
	newUser = *theUser;
	(void) copypwent(&theUser->pw, &newUser.pw);
	if (newfn)
		newUser.mpw_gecos = copystr(newfn), changes |= CHG_FN;
	if (newsh)
		newUser.mpw_shell = copystr(newsh), changes |= CHG_SH;
	if (newpw)
		newUser.mpw_passwd = copystr(newpw), changes |= CHG_PW;

E 5
D 7
	for (ms = methods; ms->method != srv_last; ms++) {
		if (ms->method != aux->sourcePW)
E 7
I 7
	for (ms = methods; ms->service != srv_last; ms++) {
		if (ms->service != aux->sourcePW)
E 7
			continue;
D 7
		if (!ms->get)
			logdie("Unsupported source \"%s\"!\n", ms->type);
		(*ms->put)(theUser, &newUser, changes);
E 7
I 7
		if (!ms->get)		/* Sanity check */
			logdie("Unsupported source \"%s\"!\n", ms->name);
		(*ms->put)(theUser, newUser, changes);
E 7
	}
}

/*
D 7
 *      pw_cleanup - clean up after myself
E 7
I 7
 * pw_cleanup
 *	Run method cleanup routines if present
 *	This routine is the bookend for pw_initialize()
 * Usage
 *	pw_cleanup(int code);
E 7
 */
public void
pw_cleanup(code)
D 7
	int	code;		/* 0 for normal, 1 for abort */ /*NOTUSED*/
E 7
I 7
	int	code;		/* 0 for normal, 1 for abort */
E 7
{
D 7
	/* do nothing */
}
E 7
I 7
	struct methodsw	*ms;
E 7
I 5

I 7
	for (ms = methods; ms->service != srv_last; ms++) {
		if (ms->cleanup)
			(*ms->cleanup)(code);
	}
}
I 12

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
I 13
	*rc = 0;
E 13
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

E 12
E 7
E 5
/* End %M% */
E 1
