/*
 * 	Tangled web of ifdefs for various systems
 *	This cleans up the Makefile
 *
 *	$Id: npasswd.h,v 1.31 1998/07/17 00:00:00 clyde Exp $
 */

#define	npasswd_h 1

#include "constants.h"
#include "defines.h"
#include "compatibility.h"
#include "options.h"

#ifdef	NEED_CLIB_DECLS
/*
 * This block of declarations may cause compilation to fail on
 * systems that have any of the routines already defined in
 * a system include file.
 */
char	*getlogin(),
	*malloc(),
	*index(),
	*rindex(),
	*ttyname();
#endif

/*
 * Password change permission type
 */
enum chg_perm {
	deny = 0,	/* Cannot change */
	self,		/* Changing own password */
	other,		/* Privleged user changing other */
	allow		/* Generic "I'm not unhappy" code */
};

struct passwd_files {
	char	*pwfile,	/* Name of password file */
		*tempfile,	/* Name of password temp file */
		*savefile,	/* Name of password save file */
		*lockfile;	/* Name of password lock file */
	uid_t	uid;		/* File owner */
	gid_t	gid;		/* File group */
	mode_t	mode;		/* File mode */
};

/*
 * The "meta-passwd" entry
 */
struct mpasswd {
	struct passwd	pw;
#define	mpw_name	pw.pw_name	/* Conveince definitions */
#define	mpw_passwd	pw.pw_passwd	/* to simplify access to */
#define	mpw_uid		pw.pw_uid	/* passwd structure elements */
#define	mpw_gid		pw.pw_gid
#define	mpw_shell	pw.pw_shell
#define	mpw_gecos	pw.pw_gecos
#define	mpw_shell	pw.pw_shell
#define	mpw_dir		pw.pw_dir
#ifdef	PWQUOTA
#define	mpw_quota	pw.pw_quota
#endif
#ifdef	PWCOMMENT
#define	mpw_comment	pw.pw_comment
#endif
	char		*mpw_opasswd;	/* Original password string */
					/* which might be a shadow cookie */
	struct {		/* Password aging information */
		time_t	last_change;	/* Time of last change */
		time_t	can_change;	/* Time till change ok */
		time_t	must_change;	/* Time when must change */
		time_t	warn_user;	/* When user gets warned */
#ifdef	PWAGE
#define	mpw_age		pw.pw_age
#else
#define	mpw_age		pwage.xage
		char	*xage;
#endif
	} pwage;
	char	key[128],	/* Database "access key" */
		password[128];	/* Database "access pass" */
	char	*pws_name,	/* Service name (NIS, NIS+) */
		*pws_loc;	/* Location of service (hostname) */
	int	pws_remote;	/* Is the service local? */
	void	*opaque;	/* Method opaque data block */
};

/*
 * Signal stuff
 */
struct sigblk {
#if	(SIG_TYPE == SIG_TYPE_UNIX)
	Signal_t	(*sigvalues[NSIG])();
#endif
#if	(SIG_TYPE == SIG_TYPE_POSIX)
	sigset_t	sigvalues,
			savesigs;
#endif
#if	(SIG_TYPE == SIG_TYPE_BSD)
	unsigned int	sigvalues,
			savesigs;
#endif
};


/*
 * Function prototypes
 */
void		pw_initialize();
struct mpasswd	*pw_getuserbyname _((char *));
enum chg_perm	pw_permission _((struct mpasswd *, struct mpasswd *));
int		pw_check _((struct mpasswd *, char *, char *));
void		pw_replace _((struct mpasswd *, struct mpasswd *, int));
void		pw_cleanup _((int));
void		passwd _((struct mpasswd *, struct mpasswd *));
void		chfn _((struct mpasswd *, struct mpasswd *));
void		chsh _((struct mpasswd *, struct mpasswd *));
void		motd _((char *, char *));

#ifdef	USE_NIS
struct passwd	*ypgetpwnam _((char *, char *));
#endif

/*
 * Variables in main.c
 */
extern char	*Switches[];
extern char	*XSwitches[];
extern Uid_t	CallerUid;

extern int	LockTries,
		LockCycle;

extern char	*npasswd_version,
		*npasswd_patchlevel,
		*checkpasswd_version,
		*checkpasswd_patchlevel,
		*build_info;

extern int	errno;			/* System error code */

#include "Common/common.h"	/* Include later to pick up type decls */

/* End $RCSfile: npasswd.h,v $ */
