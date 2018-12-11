/*
 * pwm_nis.c
 *	Network Information Service (NIS/YP) method routines
 *	Needs -lrpcsvc on many systems
 *
 * Exported routines
 *	init_yp()
 *	ypwhich()
 *	put_yp_user()
 *	update_yp_map()
 *	get_yp_user()
 *	ypsync()
 *	update_rpc_key()
 *	check_rpc_key()
 *	yp_password()
 *
 * Exported variables
 *	ypinfo
 *
 * Compilation flags
 *	cc -I.. ... -lrpcsvc
 */
#if	defined(OS_SUNOS_5) && (OS_MINOR_VERSION < 5)
# define	NO_STRINGS		/* Work around <strings.h> bug */
#endif

#include "npasswd.h"
#include "pwm_defs.h"

#ifndef lint
static char sccsid[] = "@(#)pwm_nis.c	1.36 03/09/00 (cc.utexas.edu)";
#endif

#ifdef	USE_NIS			/* Wraps entire module */

#define	PORTMAP
#include <ndbm.h>
#include <netdb.h>
#include <setjmp.h>
#include <sys/socket.h>
#include <rpc/rpc.h>
#include <rpcsvc/yppasswd.h>
#include <rpcsvc/ypclnt.h>
#define	DATUM			/* Prevent error in next include */
#include <rpcsvc/yp_prot.h>
#undef	DATUM

#ifdef	SECURE_RPC		/* SunOS Secure RPC available */
# include <sys/label.h>
# include <sys/audit.h>
# include <rpc/key_prot.h>
# include <des_crypt.h>
# include <pwdadj.h>
# define PKEY_MAP	"publickey.byname"	/* YP publickey map */
# define ROOT_KEY	"/etc/.rootkey"		/* root key is stashed here */
#endif	/* SECURE_RPC */

#define	MOD_TOKEN	"YP_LAST_MODIFIED"	/* YP map timestamp */
#define	YPPASSWD_TRIES	3			/* RPC call retries */
#define	YPPASSWD_WAIT	2			/* Retry cycle */
#ifndef	YP_TIMEOUT
# define YP_TIMEOUT	20			/* Timeout for YP interaction */
#endif
#ifndef YP_PROBE_TIMEOUT
# define YP_PROBE_TIMEOUT 2			/* Timeout for YP probing */
#endif
#ifndef	NIS_PASSWD_MAX_LEN
# define	NIS_PASSWD_MAX_LEN 8		/* Size of YP password buffer */
#endif

/*
 * Possible locations for YP data directory
 */
private char *ypdirs[] = {
#if	(CDEBUG >= CDEBUG_FILES)
	"./yp",
#endif
#ifdef	SYSTEM_YP_DIR
	SYSTEM_YP_DIR ,
#endif
	"/var/yp",
	"/etc/yp",
	0
};

/*
 * YP configuration block.  Exported for use in other modules.
 */
public struct ypinfo   ypinfo = { 0 };

/*
 *
 */
private jmp_buf	ypxwait;

/*
 * init_yp
 *	Fetches YP configuration information and stashes in the <ypinfo>
 *	structure declared in this module
 * Usage
 *	init_yp()	Usually called from pw_initialize()
 */
public void
init_yp()
{
	static int	inited = 0;

	if (ypinfo.inited) return;
	ypinfo.status = yp_not_running;
	ypwhich(PASSWD_BYNAME, &ypinfo);
	ypinfo.inited = 1;
}

/*
 * yp_sig_catch
 *	Called if yp_master() takes too long.  This will happen
 *	if there is no NIS server available.
 */
private Signal_t
yp_sig_catch()
{
	debug(DB_LOOKUP, "ypwhich: Cannot talk to NIS server\n");
	longjmp(ypxwait,1);
}

/*
 * ypwhich
 *	Get YP configuration.
 * Usage
 *	ypwhich(char *yp-name-name, struct ypinfo *ypinfo);
 */
public void
ypwhich(map, yp)
	char	*map;	/* Name of YP map to find master of */
	struct ypinfo	*yp;	/* Where to stash configuration */
{
	struct hostent	*hinfo;			/* Hostname lookup */
	char	hostname[MAXHOSTNAMLEN];	/* Our host name */
	int	ti; 				/* ACME Temporaries */
	char	*t;				/* ACME Temporaries */
	Signal_t	(*oldalarm)();		/* SIGALARM save */

	zeromem(yp, sizeof *yp);
	yp->status = yp_not_running;	/* Assume no YP running */

	/*
	 * If we already know that YP isn't working, bail.
	 */
	if (ypinfo.inited && ypinfo.status == yp_not_running) {
		return;
	}

	/*
	 * Get NIS domain name
	 */
	if (yp_get_default_domain(&t))
		return;		/* Domain not set */
	yp->domain = strdup(t);
	debug(DB_LOOKUP, "ypwhich: YP domain is \"%s\"\n", yp->domain);

	/*
	 * Set non-local jump for YP probe timeout
	 */
	if (setjmp(ypxwait))
		return;		/* Return if probe timed out */

	(void) alarm(YP_PROBE_TIMEOUT);
	oldalarm = signal(SIGALRM, yp_sig_catch);
	ti = yp_master(yp->domain, map, &t);
	(void) alarm(0);
	(void) signal(SIGALRM, oldalarm);
	if (ti)			/* Assume no YP running */
		return;
	debug(DB_LOOKUP, "ypwhich: YP master \"%s\"\n", t);

	/*
	 * Compare my host name and the YP master's host name.
	 * Use gethostbyname() to return the fully qualified form so that
	 * a string compare can be done.
	 */
	if (strchr(t, '.') == 0) {
		static char	ypmaster_f[MAXHOSTNAMLEN];

		if ((hinfo = gethostbyname(t)) == 0)
			logdie("gethostbyname failed for ypmaster");
		(void) strcpy(ypmaster_f, hinfo->h_name);
		debug(DB_LOOKUP,
			"ypwhich: canonical YP master \"%s\"\n", hinfo->h_name);
		t = ypmaster_f;
	}
	(void) gethostname(hostname, sizeof(hostname));
	if (strchr(hostname, '.') == 0) {

		if ((hinfo = gethostbyname(hostname)) == 0)
			logdie("gethostbyname failed for self");
		(void) strcpy(hostname, hinfo->h_name);
		debug(DB_LOOKUP, "ypwhich: Hostname \"%s\"\n", hinfo->h_name);
	}
	yp->master = strdup(t);
	if (strcasecmp(yp->master, hostname) == 0) {
		char	**dir,			/* ACME Temporaries */
			path[MAXPATHLEN];	/* ACME Temporaries */

		/*
		 * Find the YP data directory
		 */
		yp->status = is_yp_master;
		for (dir = ypdirs; *dir; dir++) {
			(void) sprintf(path, "%s/%s", *dir, yp->domain);
			if (access(path, 0) == 0) {
				yp->data = strdup(path);
				debug(DB_LOOKUP,
					"ypwhich: YP directory is \"%s\"\n", path);
				return;
			}
		}
		logdie("Cannot find YP data directory");
	}
	yp->status = is_yp_client;
}


/*
 * Error message for when yppasswdd fails with error code 1.
 */
static char *yperrmsg =
"Password change failed: Problem with yppasswdd.\n\n\
This is probably because the NIS maps are out of sync\n\
with the NIS passwd file for %s on %s.\n\n\
Please try again later.\n";

/*
 * put_yp_user
 *	Update NIS passwd database
 * Usage
 *	put_yp_user(struct mpasswd *old, struct mpasswd *new, int changes);
 * Side effects
 *	Update secure RPC credentials if applicable
 * Error exits
 *	Failure to set up RPC connection to yppasswdd service
 *	Timeout in sending RPC request (after YPPASSWD_TRIES retries)
 *	Failure in sending RPC request
 *	Error returned from remote yppasswdd server
 */
public void
put_yp_user(theUser, newUser, changes)
	struct mpasswd	*theUser;	/* Original user information */
	struct mpasswd	*newUser;	/* New user information */
	int		changes;	/* What was changed (CHG_X flags) */
{
	int	rc;		/* Return code from ypasswdd */
	int	tries;		/* How many tries to call yppasswdd */
	int	why;		/* RPC call return code */
	int	ypport;		/* Port for RPC call */
	char	cpw[NIS_PASSWD_MAX_LEN + 1];	
				/* Buffer for current password (cleartext) */
	struct yppasswd yppasswd; /* YP passwd change block */
	struct pw_opaque *aux = (struct pw_opaque *)theUser->opaque;
	struct	pw_svc *svc = get_pwsvc();

	/*
	 * Passwd info cannot be updated via the RPC interface
	 * without having the current password in the clear.
	 * This is a basic limitation of the RPC mechanism (at least for SunOS
	 * 4) and there is no way around it.
	 */
	if (theUser->password[0] == 0 && theUser->mpw_passwd[0])
		die("Cannot change passwd info via NIS without old password.\n");
#ifdef	PWAGE
	/*
	 * Update password aging information
	 */
	if (changes & CHG_PWAGE) {

		if (newUser->pwage.must_change == 0) {
			newUser->mpw_age = '\0';
		}
		else {
			extern char *l64a();
			time_t	now = newUser->pwage.last_change / SEC_WEEK,
				pwage;

			if (changes & CHG_PW)
				now = time((time_t *)0) / SEC_WEEK;
#ifdef	OS_HPUX
			{
			char	agetmp[STRINGLEN];

			(void) strcpy(agetmp, l64a(newUser->pwage.must_change));
			if (newUser->pwage.can_change)
				(void) strcat(agetmp,
					l64a(newUser->pwage.can_change));
			else
				(void) strcat(agetmp, ".");
			(void) strcat(agetmp, l64a(now));
			if (strlen(agetmp))
				(void) strcpy(newUser->mpw_age, agetmp);
			else
				newUser->mpw_age = ".";
			}
#else	/* OS_HPUX */
			pwage = newUser->pwage.must_change
				+ (newUser->pwage.can_change << 6)
				+ (now << 12);
			if (pwage)
				newUser->mpw_age = l64a(pwage);
			else
				newUser->mpw_age = ".";
#endif	/* OS_HPUX */
		}
	}
#endif	/* PWAGE */
	(void) strncpy(cpw, zdcrypt(theUser->password), sizeof(cpw));
	cpw[NIS_PASSWD_MAX_LEN] = 0;
	yppasswd.oldpass = cpw;
	copypwent(&newUser->pw, &yppasswd.newpw);

	debug(DB_UPDATE, "put_yp_user: yppasswd(%s, %s)\n",
		cpw, yppasswd.newpw.pw_passwd);

#ifndef	OS_SUNOS_5
	if ((ypport = getrpcport(ypinfo.master, YPPASSWDPROG,
	     YPPASSWDPROC_UPDATE, IPPROTO_UDP)) == 0)
		logdie("ypassswdd on %s is not running", ypinfo.master);

	if (ypport >= IPPORT_RESERVED)
		logdie("yppasswdd on %s is not privleged", ypinfo.master);

#endif	/* OS_SUNOS_5 */
	for (tries = 0; tries <= YPPASSWD_TRIES; tries++) {
		rc = callrpc(ypinfo.master, YPPASSWDPROG, YPPASSWDVERS,
			YPPASSWDPROC_UPDATE, xdr_yppasswd, (char *)&yppasswd,
			xdr_int, (char *)&why);

		if (rc == RPC_SUCCESS)
			break;
		/*
		 * If the call timed out, retry because the NIS master
		 * might be slow
		 */
		if (rc != RPC_TIMEDOUT) {
#ifdef	HAS_CLNT_SPERRNO
			logdie("Password change failed on %s: %s",
				ypinfo.master, clnt_sperrno(rc));
#else
			clnt_perrno(rc);
			logdie("Password change failed on %s", ypinfo.master);
#endif
			/*NOTREACHED*/
		}
		printf("Timeout talking to NIS master - retrying\n");
		sleep(YPPASSWD_WAIT);
	}
	/*
	 * The RPC call suceeded but yppasswdd returned an error code
	 */
	if (why) {
		logerr("yppasswdd error %d on %s for %s",
			why, ypinfo.master, theUser->mpw_name);
		if (why == 1)
			die(yperrmsg,  ypinfo.domain, ypinfo.master);
		else
			logdie("Password change failed");
	}
#ifdef  HAS_SECURE_RPC
	if (svc->SecurityLevel == sec_sunC2)
		update_rpc_key(theUser, zdecrypt(theUser->password));
#endif
}

/*
 * get_yp_user
 *	Look for user in YP passwd map
 * Usage
 *	found = get_pw_yp(char *user, struct mpasswd *where);
 * Returns
 *	1 if <user> found in YP map "passwd.byname"
 *		The user's passwd entry are stored in meta-passwd structure
 *		pointed to by <where>
 *	0 if <user> not found
 */
public int
get_yp_user(name, mp)
	char	*name;	/* Name of user to lookup */
	struct mpasswd	*mp;	/* Where to stash the data */
{
	struct passwd	*pwy;		/* ACME Scratch Storage */
	int	len;			/* ACME Scratch Storage */
	char	*val,			/* ACME Scratch Storage */
		*db;			/* ACME Scratch Storage */
	struct pw_opaque	*opdata = mp->opaque;

	if (ypinfo.status == yp_not_running) {
		debug(DB_LOOKUP, "get_yp_user: NIS not active\n");
		return(0);
	}
	debug(DB_LOOKUP, "get_yp_user: look in NIS map '%s'\n", PASSWD_BYNAME);
	if (yp_match(ypinfo.domain, PASSWD_BYNAME, name, strlen(name), &val, &len))
		return(0);
	debug(DB_LOOKUP, "get_yp_user: found %s\n", name);

	if ((db = malloc(len + 2)) == 0)
		logdie("No memory for NIS passwd info.\n");
#ifdef	HAS_MEMCPY
	(void) memcpy(db, val, len);
#else
	bcopy(val, db, len);
#endif
	db[len] = 0;
	if ((pwy = sgetpwent(db)) == NULL) {
		logerr("Syntax error in NIS pwent (%s)\n", db);
		free(db);
		return(0);
	}
	(void) copypwent(pwy, &mp->pw);
	free(db);
	opdata->sourcePW = srv_yp;
	mp->pws_remote = 1;
	mp->pws_name = "NIS";
	mp->pws_loc = ypinfo.master;
	return(1);
}

/*
 * update_yp_map
 *	Modify the DBM files of a YP map
 * Usage:
 *	result = update_yp_map(char *key-to-change, char *data-to-change,
 *		char *yp-map-name, char *yp-data-directory, int do-push);
 * Returns
 *	1 if DBM database was successfully modified
 *	0 if not
 */
public int
update_yp_map(mapkey, mapdata, mapname, datadir, push)
	char	*mapkey,
			*mapdata,
			*mapname,
			*datadir;
	int	push;
{
	DBM	*pwd;		/* DBM data base passwd */
	datum	key,		/* DBM key datum */
		data;		/* DBM data store datum */
	char	tod[32],	/* Time of day string */
		path[MAXPATHLEN]; /* YP map DBM database name */
	time_t	now;		/* Right now */

	now = time((time_t *)0);	/* Make the YP timestamp cookie */
	(void) sprintf(tod, "%lu", (u_long )now);

	/*
	 * Open the map DBM file
	 */
	(void) sprintf(path, "%s/%s", datadir, mapname);
	if ((pwd = dbm_open(path, O_RDWR, 0)) == 0) {
		logerr("(update_yp_map) Cannot open YP map \"%s\"", path);
		return(0);
	}
	debug(DB_UPDATE, "update_yp_map: Modifying map file \"%s\"\n", path);

	data.dptr = mapdata;
	data.dsize = strlen(mapdata);
	key.dptr = mapkey;
	key.dsize = strlen(mapkey);

	/* Stash the data */
	if (dbm_store(pwd, key, data, DBM_REPLACE) < 0) {
		perror("dbm_store (name data)");
		logerr("(update_yp_map) dbm_store (name data): %m\n");
		dbm_close(pwd);
		return(0);
	}

	/* Update the YP_LAST_MODIFIED token */
	key.dptr = MOD_TOKEN;
	key.dsize = strlen(MOD_TOKEN);
	data.dptr = tod;
	data.dsize = strlen(tod);
	if (dbm_store(pwd, key, data, DBM_REPLACE) < 0) {
		perror("dbm_store (timestamp)");
		logerr("(update_yp_map) dbm_store (timestamp): %m\n");
		dbm_close(pwd);
		return(0);
	}
	dbm_close(pwd);
	ypsync();
	if (push) {
		/* Could invoke yppush */
	}
	return(1);
}
 
#ifdef	OS_SUNOS_5
public void
ypsync()
{
	/* This code will probably look pretty much the same */
}
#else
/*
 * ypsync 
 *	Command local ypserv to flush its cache so it will pick up
 *	map modifications that have been done.
 * Usage
 *	ypsync();
 */
public void
ypsync()
{
	struct sockaddr_in	myaddr;		/* Local machine address */
	struct dom_binding	dom;		/* */
	char			localhost[MAXHOSTNAMELEN];	/* Local host */
	enum clnt_stat		rc;		/* Call return code */
	static	struct timeval	yp_timeout = { YP_TIMEOUT, 0 };

	if (gethostname(localhost, sizeof(localhost))) {
		logerr("(ypsync) cannot get hostname: %m");
		return;
	}
	get_myaddress(&myaddr);
	zeromem(&dom, sizeof dom);
	dom.dom_server_addr.sin_addr = myaddr.sin_addr;
	dom.dom_server_addr.sin_family = AF_INET;
	dom.dom_server_addr.sin_port = htons((u_short)0);
	dom.dom_server_port = htons((u_short)0);
	dom.dom_socket = RPC_ANYSOCK;
	dom.dom_client = clntudp_create(&dom.dom_server_addr, YPPROG, YPVERS,
		yp_timeout, &dom.dom_socket);
	/*
	 * Need to suppress this message when client create failed because
	 * there is no local ypserv running
	 */
	if (dom.dom_client == 0) {
		logerr("(ypsync) cannot talk to ypserv, error %s",
			clnt_spcreateerror(""));
		(void) close(dom.dom_socket);
		return;
	}
	rc = clnt_call(dom.dom_client, YPBINDPROC_NULL,
		(xdrproc_t )xdr_void, 0, (xdrproc_t )xdr_void, 0, yp_timeout);
	if (rc == RPC_SUCCESS) {
		rc = clnt_call(dom.dom_client, YPPROC_CLEAR,
			(xdrproc_t )xdr_void, 0, (xdrproc_t )xdr_void,
			0, yp_timeout);
		if (rc != RPC_SUCCESS)
			logerr("ypsync clear local ypserv error %d", rc);
	}
	clnt_destroy(dom.dom_client);
}
#endif

#ifdef	SECURE_RPC
/*
 * Support for SunOS 4.X Secure RPC (used with C2 security)
 */

/*
 * update_rpc_key
 *	Update the user's Secure RPC secret key
 * Usage
 *	update_rpc_key(struct mpasswd *new-user, char *new-password);
 * Side effects
 *	Changes the private/public key pair in the NIS public key map
 *	or /etc/.rootkey if target user is root.
 * Errors
 *	Returns without changing RPC key on error.
 *	This might not the optimal thing to do.
 */
public void
update_rpc_key(theUser, newpw)
	struct mpasswd	*theUser;	/* User to change key for */
	char		*newpw;		/* New password for key */
{
	char	sysid[MAXNETNAMELEN+1],	/* Entity netname */
		skey[HEXKEYBYTES + 1],	/* Secret key */
		pkey[HEXKEYBYTES + 1],	/* Public key */
		cdat[HEXKEYBYTES + KEYCHECKSUMSIZE + 1], /* New secret key */
		pdat[(HEXKEYBYTES*2) + KEYCHECKSUMSIZE + 4];
					/* New publickey table entry */
	int	rc;		/* Temp */
	struct pw_opaque	*xp = theUser->opaque;	/* Other stuff */

	if (theUser->mpw_uid) {		/* Changing a user's secret key */
		char	*kdata,
			*p;
		int	len;

		user2netname(sysid, theUser->mpw_uid, xp->dbinfo.ypinfo->domain);
		if (yp_match(xp->dbinfo.ypinfo->domain, PKEY_MAP,
			sysid, strlen(sysid), &kdata, &len))
				return;		/* No key for this user */
		kdata[len] = 0;
		if (!(p = strchr(kdata, ':'))) {
			logerr("Malformed publickey %s <%s>", sysid, kdata);
			free(kdata);
			return;
		}
		bcopy(kdata, pkey, HEXKEYBYTES);
		pkey[HEXKEYBYTES] = 0;
		bcopy(++p, skey, HEXKEYBYTES);
		skey[HEXKEYBYTES] = 0;
		free(kdata);
		if (xdecrypt(skey, zdecrypt(theUser->password)) == 0) {
			/* Probable that (network password != login password) */
			printf("Use \"chkey\" to change your RPC password.\n");
			return;
		}
	} else {			/* Changing the root's secret key */
		char	*kdata,
			*p;
		int	len,
			fd;

		getnetname(sysid);
		if (yp_match(xp->dbinfo.ypinfo->domain, PKEY_MAP,
			sysid, strlen(sysid), &kdata, &len)) 
				return;
		kdata[len] = 0;
		if (!(p = strchr(kdata, ':'))) {
			logerr("Malformed publickey %s <%s>", sysid, kdata);
			free(kdata);
			return;	
		}
		bcopy(kdata, pkey, HEXKEYBYTES);
		pkey[HEXKEYBYTES] = 0;
		free(kdata);
		if ((fd = open(ROOT_KEY, 0)) < 0) {
			logerr("Cannot get root key: %m");
			return;
		}
		if (read(fd, skey, HEXKEYBYTES) != HEXKEYBYTES) {
			(void) close(fd);
			return;
		}
		(void) close(fd);
		skey[HEXKEYBYTES] = 0;
	}
	/*
	 * Make a new secret key and stuff the whole thing back into the
	 * publickey YP map.
	 */
	bcopy(skey, cdat, HEXKEYBYTES);
	bcopy(skey, cdat + HEXKEYBYTES, KEYCHECKSUMSIZE);
	cdat[HEXKEYBYTES + KEYCHECKSUMSIZE] = 0;
	xencrypt(cdat, newpw);
	(void) sprintf(pdat, "%s:%s", pkey, cdat);

	debug(DB_UPDATE, "update_rpc_key: New key for <%s> is <%s>\n",
		sysid, pdat);
	/*
	 * Use the YP interface to update the publickey database.
	 * Must do this as the real user, not root.
	 */
	if (fork() == 0) {
		(void) setuid(getuid());
		if (rc = yp_update(xp->dbinfo.ypinfo->domain,
			PKEY_MAP, YPOP_STORE, sysid, strlen(sysid),
			pdat, strlen(pdat))) {
				printf("Error %d updating secret key\n", rc);
				logerr("Error %d updating secret key for %s",
					rc, sysid);
		} else {
			printf("Updated secret key for %s on %s\n",
				theUser->mpw_name, xp->dbinfo.ypinfo->master);
		}
		exit(0);
	}
	(void) wait((int *)0);
}

/*
 * check_rpc_key -
 *	Lookup Secure RPC key for user and check against password
 *
 * Usage
 *	match = check_rpc_key(struct mpasswd *user, char *password);
 * Returns
 *	1 if key found and password matches
 *	0 if key found and password does not match
 *	-1 if no key found
 */
public int
check_rpc_key(theUser, password)
	struct mpasswd	*theUser;	/* User to check RPC key */
	char	*password;		/* Password (plain) */
{
	char	sysid[MAXNETNAMELEN+1],	/* Entity netname */
		skey[HEXKEYBYTES + 1];	/* Secret key */
	struct pw_opaque	*xp = theUser->opaque;	/* Other stuff */
	char	*kdata, *p;
	int	len;

	if (theUser->mpw_uid)
		user2netname(sysid, theUser->mpw_uid,
			xp->dbinfo.ypinfo->domain);
	else
		getnetname(sysid);
	if (yp_match(xp->dbinfo.ypinfo->domain, PKEY_MAP,
		sysid, strlen(sysid), &kdata, &len))
			return(-1);		/* No key for this user */
	kdata[len] = 0;
	if (!(p = strchr(kdata, ':'))) {
		logerr("Malformed publickey %s <%s>", sysid, kdata);
		free(kdata);
		return(-1);
	}
	bcopy(++p, skey, HEXKEYBYTES);
	skey[HEXKEYBYTES] = 0;
	free(kdata);
	return (xdecrypt(skey, password) != 0);
}
#endif	/* SECURE_RPC */

#ifndef	HAS_XDR_PASSWD
/*
 * xdr_yppasswd
 *	RPC passwd XDR encoding routine for those systems which
 *	don't have this in libc or librpcsvc.
 *	Called by YP internal routines only.
 * Usage
 *	xdr_yppasswd(XDR *xdr-data, struct yppasswd *yp);
 */
private bool_t
xdr_yppasswd(xdrp, pw)
	XDR	*xdrp;
	struct yppasswd *pw;
{
	if (	xdr_wrapstring(xdrp, &pw->oldpass)  &&
		xdr_wrapstring(xdrp, &pw->newpw.pw_name) &&
		xdr_wrapstring(xdrp, &pw->newpw.pw_passwd) &&
#ifdef	HAS_XDR_UID
		xdr_uid_t(xdrp, &pw->newpw.pw_uid) &&
		xdr_gid_t(xdrp, &pw->newpw.pw_gid) &&
#else
		xdr_int(xdrp, &pw->newpw.pw_uid) &&
		xdr_int(xdrp, &pw->newpw.pw_gid) &&
#endif
		xdr_wrapstring(xdrp, &pw->newpw.pw_gecos) &&
		xdr_wrapstring(xdrp, &pw->newpw.pw_dir) &&
		xdr_wrapstring(xdrp, &pw->newpw.pw_shell))
			return(TRUE);
	return(FALSE);
}
#endif

/*
 * yp_password
 *	Get the password for YP use
 *	This routine is called from chfn() and chsh() in order to obtain
 *	the password(s) needed for remote YP updates later on.
 * Usage
 *	yp_password(struct mpasswd *user);
 */
public void
yp_password(theUser)
	struct mpasswd	*theUser;
{
	/*
	 * In order to use the RPC interface to replace a passwd entry,
	 * the plaintext of the current password is required.
	 */
	init_yp();

	if (ypinfo.status != is_yp_client) return;	/* Not a YP client */
	if (theUser->pws_remote == 0) return;		/* PW is local */

	if (theUser->mpw_passwd[0]) {
		char	prompt[TMPBUFSIZ],
			ptmp[TMPBUFSIZ];
		struct	pw_svc *svc = get_pwsvc();

		(void) sprintf(prompt,
			"Password for %s: ", theUser->mpw_name);
		get_password(prompt, theUser->mpw_passwd, ptmp, sizeof(ptmp));
#ifdef	HAS_SECURE_RPC
		if (svc->SecurityLevel == sec_sunC2) {
			char	*rpcpw;

			rpcpw = ptmp
			while (!check_rpc_key(theUser, rpcpw)) {
				rpcpw = np_getpass("Secure RPC password: ");
			}
			if (rpcpw)
				(void) strcpy(theUser->key, rpcpw);
		}
#endif
		strcpy(theUser->password, zncrypt(ptmp));
	}
}

#endif	/* USE_NIS */

/* End pwm_nis.c */
