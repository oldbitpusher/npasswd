h61369
s 00003/00002/00088
d D 1.15 00/01/17 18:16:25 clyde 15 14
c Lift decls for zncrypt() and zdcrypt() from #ifdef NIS
e
s 00002/00007/00088
d D 1.14 98/08/17 13:22:46 clyde 14 13
c Replace zncrypt() and zdcrypt() macros with function decls
e
s 00007/00000/00088
d D 1.13 98/07/21 09:32:10 clyde 13 12
c Add stubs for zncrypt() and zdcrypt()
e
s 00002/00000/00086
d D 1.12 98/07/16 09:19:55 clyde 12 11
c Add pw_svc.h
e
s 00005/00001/00081
d D 1.11 96/12/17 11:01:48 clyde 11 10
c 1. Change dbinfo from union to struct 
c 2. Add status to nisinfo block
e
s 00002/00002/00080
d D 1.10 96/08/29 13:03:21 clyde 10 9
c Remove 'const' declarations (too much compiler pain)
e
s 00002/00001/00080
d D 1.9 96/08/13 16:34:26 clyde 9 8
c Add some prototypes
e
s 00002/00002/00079
d D 1.8 96/08/09 16:18:08 clyde 8 7
c Beta 3 development checkin 2
e
s 00040/00013/00041
d D 1.7 96/08/06 14:14:16 clyde 7 6
c beta 3 cycle 1 checkin
e
s 00001/00001/00053
d D 1.6 95/04/05 16:22:59 clyde 6 5
c Beta 3 development checkin
e
s 00031/00021/00023
d D 1.5 94/09/28 16:14:03 clyde 5 4
c Subsume pw_nis.h
e
s 00001/00001/00043
d D 1.4 94/03/31 17:39:15 clyde 4 3
c Change "shadowpw" to "origpw"
e
s 00004/00000/00040
d D 1.3 93/12/16 11:04:39 clyde 3 2
c Development checkin
e
s 00007/00000/00033
d D 1.2 93/07/12 11:11:03 clyde 2 1
c Add field change flags
e
s 00033/00000/00000
d D 1.1 93/07/12 09:18:18 clyde 1 0
c date and time created 93/07/12 09:18:18 by clyde
e
u
U
f e 0
t
T
I 1
/*
I 7
 *
 * npasswd - %M%
 *
 * Include for password database access/update method modules
 * and routines that use them.
 *
E 7
D 5
 *
 *
E 5
 * %W% %G% (cc.utexas.edu)
I 7
 *
E 7
D 5
 *
E 5
 */

I 12
#include "pw_svc.h"

E 12
/*
 * Opaque data that will be put into the mpasswd entry 
 */
struct pw_opaque {
D 5
#	define	OPAQUE_MAGIC	(long )0xdeadbabe
	long	magic;
	enum {			/* Where the entry came from */
		pl_unknown = 0,	/* Not known */
		pl_local,	/* Flat file */
		pl_yp,		/* NIS */
		pl_nisplus,	/* NIS+ */ /* NYI */
		pl_nidot,	/* Netinfo '.' domain */ /* NYI */
		pl_niroot,	/* Netinfo '/' domain */ /* NYI */
		pl_hesiod,	/* Hesiod */ /* NYI */
		pl_kerberos	/* Kerberos */ /* NYI */
	} source;
	enum {
		sl_none = 0,
		sl_local,	/* Shadow pw in local file */
		sl_yp		/* Shadow pw in YP map */
	} shadow;
I 3
D 4
	char	*shadowpw;	/* Password from shadow file */
E 4
I 4
	char	*origpw;	/* "Original" password (may be shadow cookie) */
E 5
I 5
D 7
	enum svc_order sourcePW;	/* Where passwd entry came from */
	enum svc_order sourceSH;	/* Where shadow entry came from */
E 7
I 7
D 8
	enum svc_names sourcePW;	/* Where passwd entry came from */
	enum svc_names sourceSH;	/* Where shadow entry came from */
E 8
I 8
	enum svc_services sourcePW;	/* Where passwd entry came from */
	enum svc_services sourceSH;	/* Where shadow entry came from */
E 8
E 7
E 5
E 4
E 3
	struct	passwd_files	*whichPW;	/* Which passwd file */
	struct	passwd_files	*whichSH;	/* Which shadow file */
I 3
D 11
	union {
E 11
I 11
	struct {
E 11
I 7
		int	noop;
#ifdef	USE_NIS
E 7
		struct ypinfo	*ypinfo;	/* YP config info */
I 7
#endif
#ifdef	USE_NISPLUS
		struct nisinfo	*nisinfo;	/* NIS+ config info */
#endif
E 7
	} dbinfo;
E 3
};

I 2
/*
D 7
 * Field change flags
E 7
I 7
 * Password field change flags
E 7
 */
D 7
#define CHG_PW	0x1
#define CHG_FN	0x2
#define CHG_SH	0x4
E 7
I 7
#define	CHG_NONE	0		/* No changes */
#define CHG_PW		0x1		/* Changed encrypted password */
#define CHG_PWAGE	0x2		/* Changed password agaig */
#define CHG_GECOS	0x4		/* Changed GECOS */
#define CHG_SHELL	0x8		/* Changed shell */
E 7
I 5

I 15
char *zncrypt _((char *));
char *zdcrypt _((char *));

E 15
D 6
#ifdef	YP_SUPPORT
E 6
I 6
#ifdef	USE_NIS
E 6
/*
D 7
 * Return data from ypstatus()
E 7
I 7
 * NIS configuration information
E 7
 */
struct ypinfo {
	enum _yps {
		yp_not_running = 0,
		is_yp_master,
		is_yp_client
	} status;
I 7
	char	inited;		/* This data has been set */
E 7
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

I 13
D 14
/*
 * Definition stubs for things that obsfugate and clarify the plaintext
 * password stashed in memory.  These don't do anything yet.
 */
#define	zncrypt(_str_)	/* Nothing */
#define	zdcrypt(_str_)	_str_

E 14
I 14
D 15
char *zncrypt _((char *));
char *zdcrypt _((char *));
E 15
E 14
E 13
D 7
#ifdef	__STDC__
void ypwhich(char *, struct ypinfo *);
#else
void ypwhich();
#endif
#endif	/* YP_SUPPORT */
E 7
I 7
D 9
void ypwhich _((char *, struct ypinfo *));
E 9
I 9
D 10
void ypwhich _((const char *, struct ypinfo *));
int update_yp_map _((const char *, const char *, const char *, const char *, const int));
E 10
I 10
void ypwhich _((char *, struct ypinfo *));
int update_yp_map _((char *, char *, char *, char *, int));
E 10
E 9
void ypsync();
E 7
E 5

I 7
#endif	/* USE_NIS */

#ifdef	USE_NISPLUS
/*
 * NIS+ configuration information
 */
I 11

#define	NO_PASSWD_TABLE	1		/* passwd.org_dir missing or bad */

E 11
struct nisinfo {
	char	*domain;
I 11
	int	status;
E 11
};

#define	PASSWD_TABLE	"passwd.org_dir"
#define	CRED_TABLE	"cred.org_dir"

#endif	/* USE_NISPLUS */

E 7
E 2
/* End %M% */
E 1
