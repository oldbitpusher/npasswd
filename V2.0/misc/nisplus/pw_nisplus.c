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
#define	NPASSWD_COLS	8

#define	fixname(b)	{ if (b[strlen(b)-1] != '.') strcat(b,"."); }

private struct nis_result	*pwdp;
private struct nis_result	*credp;

private char	*nisdomain = NULL;
private char	*nisprincipal = NULL;

nisgetpwnam(who)
char	*who;
{
	char	nisbuf[NIS_MAXNAMLEN+1];
	int	i;
	nis_object *obj;
	static struct passwd	pw;
	int	nobj;

	if (nisdomain == NULL)
		nisdomain = nis_local_directory();

	BZERO((char *)&pw, sizeof(pw));

	(void) sprintf(nisbuf, "%s.%s", PWTABLE, nisdomain);
	fixname(nisbuf);

	pwdp = nis_lookup(nisbuf, FOLLOW_LINKS);
	if (pwdp->status != NIS_SUCCESS)
		return(NULL);		/* Passwd table not found */

	if (pwdp->objects.objects_len < 1)			/* XXX */
		logdie("Malformed NIS+ passwd table\n");	/* XXX */

	if (pwdp->objects.objects_val[0].zo_data.zo_type != TABLE_OBJ)
		logdie("NIS+ passwd is not a table\n");

	(void) sprintf(nisbuf, "[name=%s],%s.%s", v[1], PWTABLE, nisdomain);
	fixname(nisbuf);

	pwdp = nis_list(nisbuf, USE_DGRAM+FOLLOW_LINKS+FOLLOW_PATH, NULL, NULL);
	if (pwdp->status != NIS_SUCCESS)
		return(NULL);

	obj = NIS_RES_OBJECT(pwdp);
	pw.pw_name = strdup(ENTRY_VAL(obj, PWCOL_NAME));
	pw.pw_passwd = strdup(ENTRY_VAL(obj, PWCOL_PASSWD));
	pw.pw_uid = (uid_t) atoi(ENTRY_VAL(obj, PWCOL_UID));
	pw.pw_gid = (gid_t) atoi(ENTRY_VAL(obj, PWCOL_GID));
	pw.pw_gecos = strdup(ENTRY_VAL(obj, PWCOL_GECOS));
	pw.pw_dir = strdup(ENTRY_VAL(obj, PWCOL_DIR));
	pw.pw_shell = strdup(ENTRY_VAL(obj, PWCOL_SHELL));

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
