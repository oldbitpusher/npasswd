#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include <time.h>
#include <rpc/rpc.h>
#include <rpcsvc/nis.h>
#include <pwd.h>
#include <shadow.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <rpc/key_prot.h>
#include <unistd.h>
#include <nsswitch.h>
#include <nss_dbdefs.h>
#include <sys/signal.h>
#include <pwd.h>

#define	PWTABLE		"passwd.org_dir"
#define	CREDTABLE	"cred.org_dir"

#define	PWCOL_NAME	0
#define	PWCOL_PASSWD	1
#define	PWCOL_UID	2
#define	PWCOL_GID	3
#define	PWCOL_GECOS	4
#define	PWCOL_DIR	5
#define	PWCOL_SHELL	6
#define	PWCOL_SHADOW	7

struct passwd *nispgetpwnam(char *who)
{
	char	nisbuf[512];
	static struct passwd	rv;
	struct nis_result	*pwdp;
	int	i;
	char	*t;
	char	*domain;
	nis_object *obj;

	domain = nis_local_directory();

	memset((char *)&rv, sizeof(rv), 0);

	(void) sprintf(nisbuf, "%s.%s", PWTABLE, domain);
	pwdp = nis_lookup(nisbuf, FOLLOW_LINKS);
	if (pwdp->status != NIS_SUCCESS) {
		nis_perror(pwdp->status, "where is passwd?");
		printf("%s\n", nisbuf);
		exit(1);
	}
	if (pwdp->objects.objects_val[0].zo_data.zo_type != TABLE_OBJ) {
		printf("passwd not a table\n");
		exit(1);
	}
	(void) sprintf(nisbuf, "[name=%s],%s.%s", who, PWTABLE, domain);

	pwdp = nis_list(nisbuf, USE_DGRAM+FOLLOW_LINKS+FOLLOW_PATH, NULL, NULL);
	if (pwdp->status != NIS_SUCCESS)
		return(NULL);

	obj = NIS_RES_OBJECT(pwdp);
#define	fetchstring(_F_,_C_) { \
	char *t = ENTRY_VAL(obj, _C_);\
	_F_ = malloc(strlen(t)+1);\
	(void) strcpy(_F_, t); }

#define	fetchint(_F_,_C_)  _F_ = atoi(ENTRY_VAL(obj, _C_))

	fetchstring(rv.pw_name, PWCOL_NAME);
	fetchstring(rv.pw_passwd, PWCOL_PASSWD);
	fetchint(rv.pw_uid, PWCOL_UID);
	fetchint(rv.pw_gid, PWCOL_GID);
	fetchstring(rv.pw_gecos, PWCOL_GECOS);
	fetchstring(rv.pw_dir, PWCOL_DIR);
	fetchstring(rv.pw_shell, PWCOL_SHELL);
	fetchstring(rv.pw_age, PWCOL_SHADOW);
	return(&rv);

#undef	fetchstring
#undef	fetchint
}

#if	0

	sprintf(nisbuf, "[cname=%s.%s,auth_type=DES], %s.%s",
		v[1], domain, CREDTABLE, domain);

	credp = nis_list(nisbuf, USE_DGRAM+FOLLOW_LINKS+FOLLOW_PATH, NULL, NULL);
	if (credp->status != NIS_SUCCESS) {
		printf("Didn't find cred for %s\n", v[1]);
		exit(1);
	}

	printf("\nobjects: %d\n", credp->objects.objects_len);
	for (i = 0; i < credp->objects.objects_len; i++) {
		printf("Object: %d\n", i);
		printf(" name: %s\n", credp->objects.objects_val[i].zo_name);
		printf(" owner: %s\n", credp->objects.objects_val[i].zo_owner);
		printf(" group: %s\n", credp->objects.objects_val[i].zo_group);
		printf(" domain: %s\n", credp->objects.objects_val[i].zo_domain);
		switch (credp->objects.objects_val[i].zo_data.zo_type) {
		case BOGUS_OBJ: printf("type: BOGUS\n"); break;
		case NO_OBJ: printf("type: NO\n"); break;
		case DIRECTORY_OBJ: printf("type: DIRECTORY\n"); break;
		case GROUP_OBJ: printf("type: GROUP\n"); break;
		case TABLE_OBJ: printf("type: TABLE\n"); break;
		case ENTRY_OBJ: 
			nobj = credp->objects.objects_val[i].zo_data.objdata_u.en_data.en_cols.en_cols_len;
			printf("type: ENTRY name=%s ncols=%d\n",
		credp->objects.objects_val[i].zo_data.objdata_u.en_data.en_type,
			nobj);
			break;
		case LINK_OBJ: printf("type: LINK\n"); break;
		case PRIVATE_OBJ: printf("type: PRIVATE\n"); break;
		}
	}
#define	NCRED_COLS	4
#define	CRCOL_NAME	0
#define	CRCOL_TYPE	1
#define	CRCOL_NETNAME	2
#define	CRCOL_PUKEY	3
#define	CRCOL_PRKEY	4

	obj = NIS_RES_OBJECT(credp);
	for (i = 0; i < nobj; i++) {
		char	*v = ENTRY_VAL(obj, i);
		int	l = ENTRY_LEN(obj, i),
			t = ENTRY_TYPE(obj, i);
		char	f[32];

		f[0] = 0;
		if (t & EN_BINARY) strcat(f,"BINARY ");
		if (t & EN_CRYPT) strcat(f,"CRYPT ");
		if (t & EN_XDR) strcat(f,"XDR ");
		if (t & EN_MODIFIED) strcat(f,"MODIFIED ");
		if (t & EN_ASN1) strcat(f,"ASN1 ");
		printf("cred field %d flags=%s(%x) len=%d data=<%s>\n",
			i, f, t, l, v);
	}
	exit(0);
}
#endif

main(c,v)
char	**v;
{
	struct passwd *pw;
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
	}
}

