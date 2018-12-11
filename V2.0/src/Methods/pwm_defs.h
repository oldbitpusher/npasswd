/*
 *
 * npasswd - pwm_defs.h
 *
 * Include for password database access/update method modules
 * and routines that use them.
 *
 * @(#)pwm_defs.h	1.15 01/17/00 (cc.utexas.edu)
 *
 */

#include "pw_svc.h"

/*
 * Opaque data that will be put into the mpasswd entry 
 */
struct pw_opaque {
	enum svc_services sourcePW;	/* Where passwd entry came from */
	enum svc_services sourceSH;	/* Where shadow entry came from */
	struct	passwd_files	*whichPW;	/* Which passwd file */
	struct	passwd_files	*whichSH;	/* Which shadow file */
	struct {
		int	noop;
#ifdef	USE_NIS
		struct ypinfo	*ypinfo;	/* YP config info */
#endif
#ifdef	USE_NISPLUS
		struct nisinfo	*nisinfo;	/* NIS+ config info */
#endif
	} dbinfo;
};

/*
 * Password field change flags
 */
#define	CHG_NONE	0		/* No changes */
#define CHG_PW		0x1		/* Changed encrypted password */
#define CHG_PWAGE	0x2		/* Changed password agaig */
#define CHG_GECOS	0x4		/* Changed GECOS */
#define CHG_SHELL	0x8		/* Changed shell */

char *zncrypt _((char *));
char *zdcrypt _((char *));

#ifdef	USE_NIS
/*
 * NIS configuration information
 */
struct ypinfo {
	enum _yps {
		yp_not_running = 0,
		is_yp_master,
		is_yp_client
	} status;
	char	inited;		/* This data has been set */
	char	*domain,	/* NIS domain name */
		*master,	/* NIS master host */
		*data;		/* NIS database directory */
};

/*
 * Names of NIS maps where passwd information is stored
 */
#define	PASSWD_BYNAME	"passwd.byname"
#define	PASSWD_BYUID	"passwd.byuid"
#define	ADJUNCT_BYNAME	"passwd.adjunct.byname"

void ypwhich _((char *, struct ypinfo *));
int update_yp_map _((char *, char *, char *, char *, int));
void ypsync();

#endif	/* USE_NIS */

#ifdef	USE_NISPLUS
/*
 * NIS+ configuration information
 */

#define	NO_PASSWD_TABLE	1		/* passwd.org_dir missing or bad */

struct nisinfo {
	char	*domain;
	int	status;
};

#define	PASSWD_TABLE	"passwd.org_dir"
#define	CRED_TABLE	"cred.org_dir"

#endif	/* USE_NISPLUS */

/* End pwm_defs.h */
