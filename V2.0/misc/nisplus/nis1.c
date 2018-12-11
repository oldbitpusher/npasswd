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

#define	PWTABLE	"passwd.org_dir"
#define	CREDTABLE	"cred.org_dir"

struct nis_result	*pwdp;
struct nis_result	*credp;

char	*domain;
char	*principal;

main(c,v)
char	**v;
{

	char	nisbuf[512];
	int	i; nis_object *obj;

	domain = nis_local_directory();

	sprintf(nisbuf, "%s.%s", PWTABLE, domain);
	pwdp = nis_lookup(nisbuf, FOLLOW_LINKS);
	if (pwdp->status != NIS_SUCCESS) {
		nis_perror(pwdp->status, "where is passwd?");
		printf("%s\n", nisbuf);
		exit(1);
	}
	if (pwdp->objects.objects_val[0].zo_data.zo_type != TABLE_OBJ) {
		printf("It's not a table\n");
		exit(1);
	}
/* 	principal = nis_local_principal(); */
	sprintf(nisbuf, "[name=%s],%s.%s", v[1], PWTABLE, domain);

	pwdp = nis_list(nisbuf, USE_DGRAM+FOLLOW_LINKS+FOLLOW_PATH, NULL, NULL);
	if (pwdp->status != NIS_SUCCESS) {
		printf("Didn't find %s\n", v[1]);
		exit(1);
	}
	obj = NIS_RES_OBJECT(pwdp);
	for (i = 0; i <= 7; i++) {
		char	*v = ENTRY_VAL(obj, i);

		printf("field %d <%s>\n", i, v);
	}
	principal = nis_local_principal();
	sprintf(nisbuf, "[cname=%s.%s,auth_type=DES], %s.%s",
		v[1], domain, CREDTABLE, domain);

	pwdp = nis_list(nisbuf, USE_DGRAM+FOLLOW_LINKS+FOLLOW_PATH, NULL, NULL);
	if (pwdp->status != NIS_SUCCESS) {
		printf("Didn't find %s\n", v[1]);
		exit(1);
	}
}
