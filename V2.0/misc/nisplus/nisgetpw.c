#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <shadow.h>
#include <string.h>
#include <rpc/rpc.h>
#include <rpcsvc/nis.h>

#define	PWTABLE		"passwd.org_dir"

#define	PWCOL_NAME	0
#define	PWCOL_PASSWD	1
#define	PWCOL_UID	2
#define	PWCOL_GID	3
#define	PWCOL_GECOS	4
#define	PWCOL_DIR	5
#define	PWCOL_SHELL	6
#define	PWCOL_SHADOW	7

struct spwd *nisgetspnam(char *who)
{
	static struct spwd	spwd;

	memset((char *)&spwd, sizeof(spwd), 0);
	if (nisgetuser(who, (struct passwd *)NULL, &spwd))
		return(&spwd);
	else
		return(NULL);
}

struct passwd *nispgetpwnam(char *who)
{
	static struct passwd	pwd;

	memset((char *)&pwd, sizeof(pwd), 0);
	if (nisgetuser(who, &pwd, (struct spwd *)NULL))
		return(&pwd);
	else
		return(NULL);
}

nisgetuser(char *who, struct passwd *pwrv, struct spwd *shrv)
{
	char		*domain = nis_local_directory();
	char		nisbuf[512];
	nis_object	*pwdobj;
	struct nis_result *pwdp;

#define skipc while (*p && *p != ':' && *p != '\n') ++p; if (*p) *p++ = 0
#define	fetchint(_F_,_C_)  _F_ = atoi(ENTRY_VAL(pwdobj, _C_))
#define	fetchstring(_F_,_C_) { \
	char *t = ENTRY_VAL(pwdobj, _C_);\
	_F_ = malloc(strlen(t)+1);\
	(void) strcpy(_F_, t); }

	(void) sprintf(nisbuf, "%s.%s", PWTABLE, domain);
	pwdp = nis_lookup(nisbuf, FOLLOW_LINKS);
	if (pwdp->status != NIS_SUCCESS) {
		nis_perror(pwdp->status, "where is passwd?");
		return(0);
	}
	if (pwdp->objects.objects_val[0].zo_data.zo_type != TABLE_OBJ) {
/* 		printf("passwd not a table\n"); */
		return(0);
	}
	(void) sprintf(nisbuf, "[name=%s],%s.%s", who, PWTABLE, domain);

	pwdp = nis_list(nisbuf, USE_DGRAM+FOLLOW_LINKS+FOLLOW_PATH, NULL, NULL);
	if (pwdp->status != NIS_SUCCESS)
		return(0);
	pwdobj = NIS_RES_OBJECT(pwdp);

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

	if (shrv) {
		char	*sh = ENTRY_VAL(pwdobj, PWCOL_SHADOW);
		char	*p = sh;

		shrv->sp_lstchg = atol(p); skipc;
		shrv->sp_min = atol(p); skipc;
		shrv->sp_max = atol(p); skipc;
		shrv->sp_warn = atol(p); skipc;
		shrv->sp_inact = atol(p); skipc;
		shrv->sp_expire = atol(p); skipc;
		shrv->sp_flag = atoi(p); skipc;
		fetchstring(shrv->sp_namp, PWCOL_NAME);
		fetchstring(shrv->sp_pwdp, PWCOL_PASSWD);
	}
	return(1);
#undef	fetchstring
#undef	fetchint
#undef	skipc
}

#ifdef	TEST
main(c,v)
char	**v;
{
	struct passwd *pw;
	struct spwd *spw;
#define STRX(_Z_) (_Z_ ? _Z_ : "(null)")

	for (v++; *v; v++) {
		if ((pw = nispgetpwnam(*v)) == NULL) {
			printf("No passwd for %s\n", *v);
			continue;
		}
		printf("\n");
		printf("pw_name = %s\n", STRX(pw->pw_name));
		printf("pw_passwd = %s\n", STRX(pw->pw_passwd));
		printf("pw_uid = %u\n", pw->pw_uid);
		printf("pw_gid = %u\n", pw->pw_gid);
		printf("pw_shell = %s\n", STRX(pw->pw_shell));
		printf("pw_gecos = %s\n", STRX(pw->pw_gecos));
		printf("pw_shell = %s\n", STRX(pw->pw_shell));
		printf("pw_dir = %s\n", STRX(pw->pw_dir));
		printf("pw_age = %s\n", STRX(pw->pw_age));

		if ((spw = nisgetspnam(*v)) == NULL) {
			printf("No shadow for %s\n", *v);
			continue;
		}
		printf("sp_namp = %s\n", STRX(spw->sp_namp));
		printf("sp_pwdp = %s\n", STRX(spw->sp_pwdp));
		printf("sp_lstchg = %u\n", spw->sp_lstchg);
		printf("sp_min = %u\n", spw->sp_min);
		printf("sp_max = %u\n", spw->sp_max);
		printf("sp_warn = %u\n", spw->sp_warn);
		printf("sp_inact = %u\n", spw->sp_inact);
		printf("sp_expire = %u\n", spw->sp_expire);
		printf("sp_flag = %x\n", spw->sp_flag);
	}
	exit(0);
}
#endif
