h01144
s 00022/00005/00671
d D 1.48 00/01/17 18:13:50 clyde 48 47
c 1. Add option -XS (chsh without shell check)
c 2. Add option -XA (always ask for old password)
c 3. Add option -XO (ask for new password only once)
c 4. Fix SunOS4 option support list
e
s 00034/00002/00642
d D 1.47 99/07/23 11:32:32 clyde 47 46
c Print `uname -a` information
e
s 00007/00006/00637
d D 1.46 98/11/17 15:35:26 clyde 46 45
c 1. Add -XA switch 
c 2. Use new terminal mode save/restore routines
c 3. Use pager() to present help files
e
s 00001/00001/00642
d D 1.45 98/11/10 16:38:56 clyde 45 44
c Add -f to SUNOS 5 deferred options
e
s 00006/00003/00637
d D 1.44 98/09/29 14:19:54 clyde 44 43
c Add -r option for SunOS 5
e
s 00002/00005/00638
d D 1.43 98/09/23 14:25:24 clyde 43 42
c Do not set RLIMIT_NOFILE or RLIMIT_CORE
e
s 00004/00004/00639
d D 1.42 98/07/17 11:26:04 clyde 42 41
c Move uid check to just before the action block
e
s 00054/00031/00589
d D 1.41 98/07/09 14:18:26 clyde 41 40
c 1. Eliminate DebugLevel global - use new debug get/set routines
c 2. Add -Xh option for printing usage message
c 3. Changes for new pwsvc() routines
e
s 00005/00017/00615
d D 1.40 98/07/02 16:42:19 clyde 40 39
c Use set_debug to set debug level
e
s 00030/00006/00602
d D 1.39 98/07/02 08:59:52 clyde 39 38
c 1. Don't loop over -X.... characters
c 2. Allow symbolic debug level names to -XD
e
s 00005/00000/00603
d D 1.38 98/07/01 14:26:18 clyde 38 37
c 1. Fix optind use in main
c 2. Add Xsw_ShowConfig -X option
e
s 00230/00042/00373
d D 1.37 98/06/23 11:10:25 clyde 37 36
c 1. Add copright message
c 2. Change debugging ifdef trigger define
c 3. Rewrite command line option handling code
c 4. Impliment code to defer options to vendor program
c 5. Raise ceiling on some other system resource limits
e
s 00007/00101/00408
d D 1.36 98/04/21 11:00:34 clyde 36 35
c 1. Change call of configure()
c 2. Move file manipulation routines to comobj lib module
e
s 00024/00002/00485
d D 1.35 98/03/26 11:15:11 clyde 35 34
c 1. Fix usage of CallerUid
c 2. Add HP-UX command line options
e
s 00008/00000/00479
d D 1.34 97/09/23 12:21:49 clyde 34 33
c Add hooks to deny chfn and chsh
e
s 00021/00009/00458
d D 1.33 97/05/05 11:22:49 clyde 33 32
c 1. Add retry to MakeLockTemp()
c 2. Add new global vars LockTries and LockCycle
e
s 00002/00000/00465
d D 1.32 97/03/04 16:50:09 clyde 32 31
c Restrict -XF to superuser
e
s 00012/00011/00453
d D 1.31 96/08/29 13:06:33 clyde 31 30
c 1. Remove 'const' declarations (too much compiler pain)
c 2. Move getopt/optind decls to top level
e
s 00001/00001/00463
d D 1.30 96/08/15 11:34:37 clyde 30 29
c Change #ifdef DEBUG_NOEXEC to #ifdef DEBUG
e
s 00007/00006/00457
d D 1.29 96/08/14 19:00:37 clyde 29 28
c 1. Fix punctutation for die() strings
c 2. Set 'die' callback routine
e
s 00002/00002/00461
d D 1.28 96/08/14 17:59:49 clyde 28 27
c Change pwsvc -> pw_svc
e
s 00084/00066/00379
d D 1.27 96/08/13 17:56:42 clyde 27 26
c 1. Add lots of comments
c 2. Add const decls here and there
e
s 00003/00001/00442
d D 1.26 96/08/09 16:16:22 clyde 26 25
c Beta 3 development checkin 2
e
s 00233/00402/00210
d D 1.25 96/08/06 14:13:58 clyde 25 24
c beta 3 cycle 1 checkin
e
s 00006/00005/00606
d D 1.24 96/04/03 14:42:17 clyde 24 23
c  Reflect new mpasswd structure element names
e
s 00002/00002/00609
d D 1.23 96/04/01 16:16:47 clyde 23 22
c Fix reference to svc_get()
e
s 00000/00491/00611
d D 1.22 96/04/01 15:57:39 clyde 22 21
c Split a lot of small routines out into seperate source files
e
s 00046/00013/01056
d D 1.21 96/04/01 14:13:59 clyde 21 20
c 1. Mess around with a couple DEBUG ifdefs
c 2. Change nsswitch processing:
c  a) Eliminate need for svc_ypcompat
c  b) Look for "passwd_compat" if passwd service is "compat"
c  c) Add debugging for nsswitch processing
c 3. Move svc_get() to after command line handling (to have debug level set)
e
s 00119/00083/00950
d D 1.20 96/03/29 11:40:44 clyde 20 19
c 1. Rewrite nsswitch processor
c 2. Rewrite varargs/stdargs routines
e
s 00000/00001/01033
d D 1.19 96/03/27 17:21:30 clyde 19 18
c Remove call to checkpassword_init()
e
s 00019/00000/01015
d D 1.18 96/03/27 09:28:39 clyde 18 17
c Add debug() routine
e
s 00063/00054/00952
d D 1.17 95/04/05 16:19:48 clyde 17 16
c Beta 3 development checkin
e
s 00012/00001/00994
d D 1.16 94/11/03 15:13:54 clyde 16 15
c Add -XC (check config file) option
e
s 00006/00002/00989
d D 1.15 94/10/24 10:37:16 clyde 15 14
c Set DebugLevel based upon #ifdef DEBUGX
e
s 00091/00061/00900
d D 1.14 94/09/28 16:09:33 clyde 14 13
c Development checkin - lots of changes
e
s 00026/00002/00935
d D 1.13 94/07/28 15:58:39 clyde 13 12
c Add chfn and chsh
e
s 00099/00089/00838
d D 1.12 94/07/15 08:53:40 clyde 12 11
c 1. Move from main procedure to os_init().
c 2. Make argument indentation consistent
e
s 00001/00004/00926
d D 1.11 94/05/19 10:33:52 clyde 11 10
c Pull TCB directory path from include file
e
s 00063/00009/00867
d D 1.10 94/05/17 15:26:42 clyde 10 9
c 1. Rewrite svc_get() for OSF/1 security environment.
c 2. Add debug print routine.
c 3. Abstract out which encryption routine to use.
e
s 00092/00015/00784
d D 1.9 94/03/31 17:37:55 clyde 9 8
c Add routines for easy signal blocking and unblocking
e
s 00003/00003/00796
d D 1.8 94/03/17 15:47:43 clyde 8 7
c Use generic types for signal handling
e
s 00001/00000/00798
d D 1.7 94/03/16 11:07:49 clyde 7 6
c Call checkpassword_init()
e
s 00006/00005/00792
d D 1.6 94/03/15 18:49:52 clyde 6 5
c Development checkin
e
s 00060/00031/00737
d D 1.5 94/03/15 11:07:03 clyde 5 4
c Make compile under OSF/1 on alpha AXP
e
s 00040/00020/00728
d D 1.4 94/03/01 15:04:44 clyde 4 3
c Development checkin:
c 1. Add 'warn' routine
c 2. Change some routine names
c 3. Call new configuration routine
c 
e
s 00002/00002/00746
d D 1.3 93/12/20 09:18:23 clyde 3 2
c Don't put a newline at the end of passwd lines created
e
s 00004/00004/00744
d D 1.2 93/12/16 11:02:39 clyde 2 1
c Development checkin
e
s 00748/00000/00000
d D 1.1 93/07/12 09:18:11 clyde 1 0
c date and time created 93/07/12 09:18:11 by clyde
e
u
U
f e 0
t
T
I 1
/*
I 37
 * Copyright 1998, The University of Texas at Austin ("U. T. Austin").
 * All rights reserved.
 *
 * By using this software the USER indicates that he or she has read,
 * understood and will comply with the following:
 *
 * U. T. Austin hereby grants USER permission to use, copy, modify, and
 * distribute this software and its documentation for any purpose and
 * without fee, provided that:
 *
 * 1. the above copyright notice appears in all copies of the software
 *    and its documentation, or portions thereof, and 
 * 2. a full copy of this notice is included with the software and its
 *    documentation, or portions thereof, and 
 * 3. neither the software nor its documentation, nor portions thereof,
 *    is sold for profit. Any commercial sale or license of this software,
 *    copies of the software, its associated documentation and/or
 *    modifications of either is strictly prohibited without the prior
 *    consent of U. T. Austin. 
 * 
 * Title to copyright to this software and its associated documentation
 * shall at all times remain with U. T. Austin. No right is granted to
 * use in advertising, publicity or otherwise any trademark, service
 * mark, or the name of U. T. Austin.
 * 
 * This software and any associated documentation are provided "as is,"
 * and U. T. AUSTIN MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESSED OR
 * IMPLIED, INCLUDING THOSE OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR
 * PURPOSE, OR THAT USE OF THE SOFTWARE, MODIFICATIONS, OR ASSOCIATED
 * DOCUMENTATION WILL NOT INFRINGE ANY PATENTS, COPYRIGHTS, TRADEMARKS OR
 * OTHER INTELLECTUAL PROPERTY RIGHTS OF A THIRD PARTY. U. T. Austin, The
 * University of Texas System, its Regents, officers, and employees shall
 * not be liable under any circumstances for any direct, indirect, special,
 * incidental, or consequential damages with respect to any claim by USER
 * or any third party on account of or arising from the use, or inability
 * to use, this software or its associated documentation, even if U. T.
 * Austin has been advised of the possibility of those damages.
 * 
 * Submit commercialization requests to: Office of the Executive Vice
 * President and Provost, U. T. Austin, 201 Main Bldg., Austin, Texas,
 * 78712, ATTN: Technology Licensing Specialist.
 */

/*
E 37
 *	This program duplicates the manual page behavior of the 4.XBSD
 *	passwd(1) command.  It can be configured for use with a variety
 *	of passwd systems (/etc/passwd, /etc/shadow, databases).
D 25
 *
 *	The System V support is untested (by the author - other sites
 *	tell me it works).
 *
 *	Here we have only the most abstract data needed (login name,
 *	user id, current password, new password).
 *	All other information needed (the full password line, etc),
 *	is kept down in the 'method' routines.
 *
 *	The 'method' routines are:
 *
 *	pw_initalize()		Do initializations 
 *	pw_getuserbyname()	Get user information by name
 *	pw_permission()		Check if user has permission
 *				 to change this users' password
 *	cmp_password()		Compare passwords
 *	pw_check()		Check password
 *				 Returns 1 if ok, 0 otherwise
 *	pw_replace()		Replace the password
 *	pw_cleanup()		Cleanup
E 25
 */
D 37

E 37
#include "npasswd.h"
I 41
#include "pw_svc.h"
E 41
D 17
#include "version.h"
E 17

D 12
#if	OS_BSD
D 4
#include <sys/time.h>
E 4
#include <sys/resource.h>
I 4
D 5
#include <sys/stat.h>
E 5
E 4
#endif

E 12
#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu) %P%";
#endif

I 5
D 6
#ifndef	PASSWD_CONFIG
#define	PASSWD_CONFIG	"config.file"	/* XXX */
E 6
I 6
D 27
#ifndef	CONFIG_FILE
D 12
#define	CONFIG_FILE	"npasswd.config"	/* XXX */
E 12
I 12
# define	CONFIG_FILE	"npasswd.config"	/* XXX */
E 12
E 6
#endif
E 5

E 27
D 25
#define	BASEOPTIONS "X:fs"		/* Baseline command line options */
I 12
extern char	*crypt();
E 25
I 25
D 37
#define	SWITCHES_GENERIC "X:fs"		/* Baseline command line options */
#ifdef	OS_SUNOS_4
# define	SWITCHES_OS "alyd:e:n:x:F:"
#endif
E 37
E 25
D 41

I 35
D 37
#ifdef OS_HPUX
# define	SWITCHES_OS "den:x:"
E 37
I 37
#ifndef	DEBUG_DEFAULT
# define	DEBUG_DEFAULT	DB_NONE
E 37
#endif

E 41
D 36

E 36
E 35
/*
D 25
 * Global storage definitions
E 25
I 25
 * Global variables
E 25
 */
I 15
D 21
#ifdef	DEBUGX
int	DebugLevel = DEBUGX;		/* Debugging level */
E 21
I 21
D 37
#ifdef	DEBUG_TEST
D 25
int	DebugLevel = DEBUG_TEST;	/* Debugging level */
E 25
I 25
public int	DebugLevel = DEBUG_TEST;	/* Debugging level */
E 25
E 21
#else
D 25
int	DebugLevel = 0;			/* Debugging level */
E 25
I 25
public int	DebugLevel = 0;			/* Debugging level */
E 25
#endif
E 37
I 37
D 41
public int	DebugLevel = DEBUG_DEFAULT;	/* Debugging level */
E 41
E 37
E 15
E 12
D 4
int	pwReadTries = 3;		/* Retry limit */
E 4
D 25
int	ProgramInput = 0;		/* Data source is a program */
I 16
char	*ConfigFile = CONFIG_FILE;	/* Configuration file */
E 16
D 4
int	DebugLevel = 99;			/* Debugging level */
E 4
I 4
D 15
int	DebugLevel = 99;		/* Debugging level */
E 15
E 4
char	*CommandLineOption[256];	/* Command line options vector */
D 12
char	*ProgramName;

I 10
extern char	*crypt();
char	*(*PasswdCrypt)() = crypt;

E 10
enum sec_order SecurityLevel;
E 12
I 12
char	*ProgramName;			/* Name for error messages */
char	*(*PasswdCrypt)() = crypt;	/* Password encryption routine */
enum sec_order SecurityLevel;		/* OS security level */
E 12
D 9
enum svc_order ServiceOrder[32];
E 9
I 9
enum svc_order ServiceOrder[32] = {
I 12
	/* Services to call for passwd data lookup */
E 12
D 15
#if	YP_PASSWD
E 15
I 15
D 17
#if	YP_SUPPORT
E 17
I 17
#ifdef	USE_NIS
E 17
E 15
	srv_local, srv_yp, srv_last
#else
	srv_local, srv_last
#endif
};
E 25
I 25
public char	*ConfigFile = CONFIG_FILE;	/* Configuration file */
public char	*Switches[256];			/* Command line switch values */
public char	*XSwitches[256];		/* 'X' Command switches */
D 41
public char	*ProgramName;			/* Program name */
I 26
D 28
public struct pwsvc svc;			/* Service info */
E 28
I 28
public struct pw_svc svc;			/* Service info */
E 41
E 28
E 26
private	struct mpasswd	*TargetPW,		/* Target of change */
			*CallerPW;		/* Who wants to make change */
D 27
private Uid_t	MyUid;
E 27
I 27
public Uid_t	CallerUid;			/* Cached getuid() value */
E 27
E 25
E 9

I 33
D 36
/*
 * File locking retry parameters
 */
#ifndef	FLOCK_TRIES
# define	FLOCK_TRIES 4
#endif
#ifndef	FLOCK_CYCLE
# define	FLOCK_CYCLE 2
#endif
Config_Value int	LockTries = FLOCK_TRIES;	/* How many times */
Config_Value int	LockCycle = FLOCK_CYCLE;	/* How long to wait */

E 36
E 33
I 14
D 25
private	struct mpasswd	*TargetPW,	/* Target of change */
			*CallerPW;	/* Who want to make change */
E 25
I 25
private enum { PASSWD, CHFN, CHSH } what_to_do;	/* What to do */
E 25

I 41
private char	*ProgramName;			/* Program name */
private char	*Usage = "Usage: %s\n\
	Generic options:\n\
	[-Xc]		Show configuration settings\n\
	[-XC config-file] Use alternate configuration file\n\
	[-XD level]	Set debug level\n\
	[-Xf]		Change finger name\n\
	[-XF]		Suppress new password checking (root only)\n\
	[-Xh]		Help\n\
I 48
	[-XA]		Always ask for current password (root only)\n\
	[-XO]		Allow one attempt to set new password (root only)\n\
E 48
	[-XI]		Read passwords from standard input (root only)\n\
	[-Xs]		Change login shell\n\
I 48
	[-XS]		Change login shell without verfication (root only)\n\
E 48
	[-XV]		Print version and patch information\n";

/*
 * Program debug level table
 */
private debug_table npasswd_debug[] = {
	{ "none",	DB_NONE,	"Debugging off" },
	{ "verbose",	DB_VERBOSE,	"Verbose" },
	{ "lookup",	DB_LOOKUP,	"User lookup" },
	{ "update",	DB_UPDATE,	"User update" },
	{ "config",	DB_CONFIG,	"Configuration processing" },
	{ "pwcheck",	DB_PWCHECK,	"Password checking" },
	{ "detail",	DB_DETAIL,	"Detailed debugging" },
	{ "all",	DB_ALL,		"All debugging" },
	{ 0 },
};

E 41
E 14
I 12
D 25
/*
 * Local storage definitions
 */
E 12
I 9

I 12
/*
 * Prototypes for functions used in this file.
 */
E 12
E 9
D 2
int	catchit(/* int signo */);		/* Signal catcher */
E 2
I 2
D 5
signal_t	catchit(/* int signo */);		/* Signal catcher */
E 5
I 5
#ifdef	__STDC__
D 8
private void	catchit(int);		/* Signal catcher */
E 8
I 8
D 17
private SIGNAL_T	catchit(int);		/* Signal catcher */
E 17
I 17
private Signal_t	catchit(int);		/* Signal catcher */
E 25
I 25
D 27
private Signal_t catchit _((int));		/* Signal catcher */
E 27
I 27
D 31
private Signal_t catchit _((const int));		/* Signal catcher */
E 31
I 31
D 36
extern char	*optarg;	/* From getopt() */
extern int	optind;		/* From getopt() */
E 36
D 37

E 37
private Signal_t catchit _((int));		/* Signal catcher */
E 31
E 27
E 25
E 17
E 8
private void	checktty();
D 10
private void	svc_get(char **);
E 10
I 10
D 23
private void	svc_get(int, char **, char **);
E 23
E 10
E 5
E 2
D 12

E 12
I 12
D 25
private void	os_init(int, char **, char **);
I 23
public void	svc_get(int, char **, char **);
E 23
E 12
I 5
#else
D 12

E 12
D 8
private void	catchit();		/* Signal catcher */
E 8
I 8
D 17
private SIGNAL_T	catchit();		/* Signal catcher */
E 17
I 17
private Signal_t	catchit();		/* Signal catcher */
E 17
E 8
private void	checktty();
D 23
private void	svc_get();
E 23
D 12

E 12
I 12
private void	os_init();
I 23
public void	svc_get();
E 23
E 12
#endif
E 25
I 25
private void	os_init _((int, char **, char **));
I 47
private void	print_os_env();
E 47
private void	process_arguments _((int, char **, char **));
E 25

E 5
/*
D 25
 *	passwd - change the password for a user.
 *
 *	This program impliments the 'passwd' command.
E 25
I 25
 *	main program - passwd/chfn/chsh
E 25
 */
main(argc, argv, envp)
D 12
int	argc;
char	*argv[];
char	*envp[];
E 12
I 12
	int	argc;
	char	**argv;
D 14
	char	**envp;
E 14
I 14
	char	**envp;		/* Not ANSI? */
E 14
E 12
{
D 12
	struct passwd	*pwtemp;
E 12
D 25
	char	opts[128];		/* Command line options */
	int	opt;			/* Option processing temp */
D 12
	uid_t	myuid;
	char	*temp;
	char	LoginName[STRINGLEN];	/* Temp */
	struct mpasswd	*TargetPW,
			*CallerPW;

E 12
I 12
D 17
	uid_t	myuid;			/* Caller's uid */
E 17
I 17
	Uid_t	myuid;			/* Caller's uid */
E 17
I 16
	int	cfcheck = 0;		/* Check config file only */
E 25
E 16
	char	*temp;			/* ACME Scratch Variables */
D 27
	char	LoginName[STRINGLEN];	/* User name temp */
E 27
I 27
	char	CallerLogin[STRINGLEN];	/* User name temp */
E 27
	struct passwd	*pwtemp;	/* Lookup temp */
I 38
	extern int	optind;
E 38
D 14
	struct mpasswd	*TargetPW,	/* Target of change */
			*CallerPW;	/* Who want to make change */
E 14
E 12
D 25
	enum {
D 12
		PASSWD,
		CHFN,
		CHSH
	} pfunc;
E 12
I 12
		PASSWD, CHFN, CHSH
	} pfunc;			/* Which function we're doing */
E 12
	extern char	*optarg;	/* From getopt() */
	extern int	optind;		/* From getopt() */
E 25

I 41
#ifdef	DEBUG_DEFAULT
	init_debug(DEBUG_DEFAULT);
#else
	init_debug(DB_NONE);
#endif
E 41
I 35
	CallerUid = getuid();		/* Get uid of invoker */
E 35
I 29
	set_die_callback(pw_cleanup);
E 29
D 4
	setup(envp);
E 4
I 4
D 9
	svc_get(envp);
E 9
E 4
D 12
#if     OS_BSD
	{
E 12
I 12
D 17
	os_init(argc, argv, envp);

E 17
E 12
D 25
	/*
D 12
	 * Remove BSD resource limits
E 12
I 12
	 * Process command line options.
E 12
	 */
D 12
	struct rlimit no_limit;
	no_limit.rlim_cur = no_limit.rlim_max = RLIM_INFINITY;
	(void) setrlimit(RLIMIT_CPU, &no_limit);
	(void) setrlimit(RLIMIT_FSIZE, &no_limit);
	(void) setrlimit(RLIMIT_DATA, &no_limit);
	(void) setrlimit(RLIMIT_CORE, &no_limit);
	(void) setrlimit(RLIMIT_STACK, &no_limit);
	(void) setrlimit(RLIMIT_RSS, &no_limit);
	}
#endif
D 4
	(void) umask(0);		/* Give full control over file modes */
E 4
I 4
	(void) umask((mode_t)0);		/* Give full control over file modes */
E 4

E 12
	(void) strcpy(opts, BASEOPTIONS);
#ifdef	OS_SUNOS_4
	(void) strcat(opts, "alyd:e:n:x:F:");
#endif
#ifdef	OS_ULTRIX_4
D 4
	(void) strcat(options, "");
E 4
I 4
	(void) strcat(opts, "");
E 4
#endif
I 9
D 13
	pfunc = PASSWD;
	ProgramName = "passwd";
E 13
I 13
D 17
	if (temp = RINDEX(argv[0], '/'))
E 17
I 17
	if (temp = rindex(argv[0], '/'))
E 17
		temp++;
	else
		temp = argv[0];
E 13

I 13
	if (strcmp (temp, "chsh") == 0) {
		pfunc = CHSH;
		ProgramName = "chsh";
	}
	else if (strcmp (temp, "chfn") == 0) {
		pfunc = CHFN;
		ProgramName = "chfn";
	}
	else {
		pfunc = PASSWD;
		ProgramName = "passwd";
	}
D 20

E 20
E 13
D 10
	svc_get(envp);
E 10
I 10
D 12
	svc_get(argc, argv, envp);
E 10
E 9
	/*
	 * Process command line options.
	 */
E 12
D 9
	pfunc = PASSWD;
	ProgramName = "passwd";
E 9
D 17
	BZERO((char *)CommandLineOption, sizeof(CommandLineOption));
E 17
I 17
	os_init(argc, argv, envp);
E 17

I 17
	bzero((char *)CommandLineOption, sizeof(CommandLineOption));

E 17
	while ((opt = getopt(argc, argv, opts)) != EOF) {
		switch (opt) {
#ifdef	OS_SUNOS_4
		/*
		 * We slurp up the SunOS options, but don't do much
		 * with them just yet.
		 */
		case 'a':
			CommandLineOption[(char)opt] = "on";
			break;
		case 'l':
			CommandLineOption[(char)opt] = "on";
			break;
		case 'y':
			CommandLineOption[(char)opt] = "on";
			break;
		case 'd':
			CommandLineOption[(char)opt] = "on";
			break;
		case 'e':
			CommandLineOption[(char)opt] = "on";
			break;
		case 'n':
			CommandLineOption[(char)opt] = copystr(optarg);
			break;
		case 'x':
			CommandLineOption[(char)opt] = copystr(optarg);
			break;
		case 'F':
			printf("Option \"-F\" not supported.\n");
			exit(1);
#endif
		case 'f':
			pfunc = CHFN;
			break;
		case 's':
			pfunc = CHSH;
			break;

		case 'X': {
			char	*op;
		
			for (op = optarg; *op; op++) {
			switch (*op) {
I 16
			case 'C':		/* Check config file */
				(void) setgid(getgid()); /* Give away */
				(void) setuid(getuid()); /* privs */
/* 				DebugLevel = DB_CONFIG; */
				configure(++op);
				printf("Configuration file \"%s\" OK\n", op);
				exit(0);
				break;

E 16
			case 'D':		/* Debug level */
				op++;
				if (!isdigit(*op))
					die("Debug level is not a number");
D 5
				DebugLevel = atoi(*op);
E 5
I 5
				DebugLevel = atoi(op);
I 21
				printf("%s: Debug level = %d\n",
					ProgramName, DebugLevel);
E 21
E 5
				break;

			case 'P':		/* Data source is a program */
				if (getuid())
					die("Option \"-XP\" reserved for super-user.\n");
				ProgramInput = 1;
				break;
			case 'R':		/* Require old passwd even for su */
				if (getuid())
					die( "Option \"-XR\" reserved for super-user.\n");
				break;
			case 'V':
D 17
				printf("%s; patch level %s\n",
D 6
					version, patchlevel);
E 6
I 6
					npasswd_version, npasswd_patchlevel);
E 17
I 17
				printf("Version: %s\nPatch level: %s\n%s\n",
					npasswd_version, npasswd_patchlevel,
					build_info);
E 17
E 6
				exit(0);
			}	/* switch */
			}	/* for */
		} /* case 'X' */
		break;
		} /* switch */
	} /* for */
D 21
#ifndef	DEBUG
D 2
	if (geteuid())
		die("Permission denied.\n");
E 2
I 2
/* 	if (geteuid()) */
/* 		die("Permission denied.\n"); */
E 21
I 21

E 25
I 25
	process_arguments(argc, argv, envp); /* Process command line */
E 25
D 26
	svc_get(argc, argv, envp);	/* Get service order */
E 26

I 26
D 27
	(void) svc_info(argc, argv, envp, &svc);	/* Get service order */

E 26
#ifndef	DEBUG_NOEXEC_X	/* XXX */
E 27
I 27
D 30
#ifndef	DEBUG_NOEXEC
E 30
I 30
D 37
#ifndef	DEBUG
E 37
I 37
D 42
#if	(CDEBUG <= CDEBUG_SYSTEM)
E 37
E 30
E 27
	if (geteuid())
		die("Permission denied.\n");
E 21
E 2
#endif
E 42
I 27
D 28
	(void) svc_info(argc, argv, envp, &svc);	/* Get service order */
E 28
I 28
D 41
	(void) get_pwsvc(argc, argv, envp, &svc);
E 41
I 41
D 44
	init_pwsvc(argc, argv);
E 44
I 44
	init_pwsvc(argc, argv, Switches);
E 44
E 41
E 28
E 27
I 13
D 25
#ifdef CMDLINE_CRYPT_PW
	if (EncryptedPassword[0] == '\0' || pfunc != PASSWD)
I 14
		{ /* XXX */ }
E 14
#endif
E 25
E 13
	checktty();
D 46
	savetty();
E 46
I 46
	term_save();
E 46
I 25
D 27
	MyUid = getuid();
E 27
I 27
D 35
	CallerUid = getuid();
E 35
E 27
E 25
	temp = getlogin();
D 25
	myuid = getuid();
	if (temp == 0 || *temp == '\0') {
E 25
I 25
	if (temp == 0 || *temp == '\0') {	/* Can't get login name */
E 25
		static char savedname[STRINGLEN];

D 25
		if ((pwtemp = getpwuid(myuid)) == ((struct passwd *)NULL))
			logdie("Cannot get your login name.\n");
E 25
I 25
D 27
		if ((pwtemp = getpwuid(MyUid)) == ((struct passwd *)NULL))
E 27
I 27
		if ((pwtemp = getpwuid(CallerUid)) == ((struct passwd *)NULL))
E 27
D 29
			logdie("Cannot get your login name\n");
E 29
I 29
			logdie("Cannot get your login name.\n");
E 29
E 25
		(void) strncpy(savedname, pwtemp->pw_name, sizeof(savedname));
		temp = savedname;
	}
D 27
	(void) strcpy(LoginName, temp);
	if ((pwtemp = getpwnam(LoginName)) == NULL)
E 27
I 27
D 35
	(void) strcpy(CallerLogin, temp);
E 35
I 35
	(void) strncpy(CallerLogin, temp, sizeof(CallerLogin));
E 35
	if ((pwtemp = getpwnam(CallerLogin)) == NULL)
E 27
D 25
		logdie("Cannot get user identification from name.\n");
	if (pwtemp->pw_uid != getuid() && myuid) {
E 25
I 25
D 29
		logdie("Cannot get user identification from name\n");
E 29
I 29
		logdie("Cannot get user identification from name.\n");
E 29
D 27
	if (pwtemp->pw_uid != MyUid && MyUid) {
E 27
I 27
	if (pwtemp->pw_uid != CallerUid && CallerUid) {
E 27
E 25
D 37
#ifdef	DEBUG
E 37
I 37
#if	(CDEBUG >= CDEBUG_SYSTEM)
E 37
D 20
		printf("Login name \"%s\" does not belong to uid %d\n",
E 20
I 20
		warn("Login name \"%s\" does not belong to uid %d\n",
E 20
D 25
			pwtemp, myuid);
E 25
I 25
D 27
			pwtemp, MyUid);
E 27
I 27
			pwtemp, CallerUid);
E 27
E 25
#endif
D 37
#ifdef	PARANOID
E 37
I 37
#ifdef	PARANOID_UIDCHECK
E 37
		logdie("Login name \"%s\" does not belong to uid %d\n",
D 25
			pwtemp, myuid);
E 25
I 25
D 27
			pwtemp, MyUid);
E 27
I 27
			pwtemp, CallerUid);
E 27
E 25
#endif
	}
	CallerPW = (struct mpasswd *)calloc(sizeof(struct mpasswd), 1);
I 25
	if (!CallerPW)
		logdie("Cannot allocate memory to store caller information\n");
E 25
	(void) copypwent(pwtemp, &CallerPW->pw);

	/*
	 * Set up signal handling
	 */
D 37
#ifndef	DEBUG
E 37
I 37
#if	(CDEBUG < CDEBUG_SYSTEM)
E 37
	(void) signal(SIGHUP, catchit);
	(void) signal(SIGINT, catchit);
	(void) signal(SIGQUIT, catchit);
	(void) signal(SIGTERM, catchit);
#endif
D 14

#ifdef	USE_SYSLOG
	openlog("passwd", LOG_PID | LOG_CONS, LOG_AUTH);
E 14
I 14
#ifdef	LOG_AUTH
	openlog(ProgramName, LOG_PID, LOG_AUTH);
#else
	openlog(ProgramName, LOG_PID);
E 14
#endif
I 7
D 14
	checkpassword_init();
E 14
E 7
I 4
D 6
	configure(PASSWD_CONFIG);
E 6
I 6
D 16
	configure(CONFIG_FILE);
E 16
I 16
D 36
	configure(ConfigFile);
E 36
I 36
	configure(ConfigFile, 0);
E 36
E 16
E 6
E 4
	pw_initialize(argc, argv);

	if (argv[optind]) {
		if ((TargetPW = pw_getuserbyname(argv[optind])) == NULL)
			die("No such user %s\n", argv[optind]);
	}
	else {
D 27
		if ((TargetPW = pw_getuserbyname(LoginName)) == NULL)
E 27
I 27
		if ((TargetPW = pw_getuserbyname(CallerLogin)) == NULL)
E 27
D 25
			logdie("Cannot get your password information.\n");
E 25
I 25
D 29
			logdie("Cannot get your user information\n");
E 29
I 29
			logdie("Cannot get your user information.\n");
E 29
E 25
	}

I 42
#if	(CDEBUG <= CDEBUG_SYSTEM)
	if (geteuid())
		die("Permission denied.\n");
#endif
I 48
#ifdef	NICE_LEVEL
	(void) nice(NICE_LEVEL);
#endif
E 48
E 42
D 25
	switch (pfunc) {
E 25
I 25
	switch (what_to_do) {
E 25
	case PASSWD:
I 14
D 19
		checkpassword_init();
E 19
E 14
D 4
		setcheckpassword("-c", PASSWD_CONFIG, 0);	/* XXX */
E 4
		passwd(TargetPW, CallerPW);
I 13
		break;
	case CHSH:
I 34
#ifdef	DENY_CHSH
		die("Chsh not available.\n");
#else
E 34
		chsh(TargetPW, CallerPW);
I 34
#endif
E 34
		break;
	case CHFN:
I 34
#ifdef	DENY_CHFN
		die("Chfn not available.\n");
#else
E 34
		chfn(TargetPW, CallerPW);
I 34
#endif
E 34
E 13
		break;
	}
	pw_cleanup(0);
	exit(0);
D 25
	return(0);
E 25
I 25
	return(0);		/* Make ANSI C happy */
E 25
}

/*
D 27
 *	motd - issue 'message of the day'
E 27
I 27
 * motd
 *	Issue 'message of the day'
 * Usage
 *	(void) motd(file, error-message);
E 27
 */
I 5
public void
E 5
motd(fn, complaint)
D 12
char	*fn,			/* Name of file to present */
	*complaint;		/* Complaint if missing */
E 12
I 12
D 27
	char	*fn,			/* Name of file to present */
		*complaint;		/* Complaint if missing */
E 27
I 27
D 31
	const char	*fn,		/* File to present */
			*complaint;	/* Complaint if missing */
E 31
I 31
	char	*fn,		/* File to present */
		*complaint;	/* Complaint if missing */
E 31
E 27
E 12
{
D 20
	char	cmdbuf[BUFSIZ];		/* Buffer to build command in */
E 20
I 20
D 25
	char	cmdbuf[TMPBUFSIZ];	/* Buffer to build command in */
E 20
	int	pid;
E 25
I 25
D 27
	char	inbuf[TMPBUFSIZ];
	FILE	*in;
E 27
I 27
	char	inbuf[TMPBUFSIZ];	/* ACME Scratch Storage */
	FILE	*in;			/* ACME Scratch Storage */
E 27
E 25

D 14
#define	NOBODY	"nobody"
E 14
D 25
	if (access(fn, 0) < 0) {
E 25
I 25
	if ((in = fopen(fn, "r")) == NULL) {
E 25
		if (complaint)
			printf("%s\n", complaint);
		return;
	}
I 17
D 25
#ifndef	PAGER_CMD
#define	PAGER_CMD	"/bin/cat"
#endif
E 17
I 14
	/*
	 * Set SHELL environment to /dev/null to discourage shell escapes
	 * from the pager program
	 */
E 14
	if (isatty(0))
D 14
#ifdef	OS_SYS5
		(void) sprintf(cmdbuf, "SHELL=/dev/null pg -n -s %s", fn);
#else
		(void) sprintf(cmdbuf, "SHELL=/dev/null more -d %s", fn);
#endif
E 14
I 14
D 17
		(void) sprintf(cmdbuf, "SHELL=/dev/null %s %s", PAGER, fn);
E 17
I 17
		(void) sprintf(cmdbuf, "SHELL=/dev/null %s %s", PAGER_CMD, fn);
E 17
E 14
	else
		(void) sprintf(cmdbuf, "cat %s", fn);

	if ((pid = fork()) == 0) {
		if (getuid() == 0) {
			/* Real uid == 0, then set uid to 'nobody' */
I 14
#define	NOBODY	"nobody"
E 14
			struct passwd *nb = getpwnam(NOBODY);
			if (nb) {
				(void) setgid(nb->pw_gid);
				(void) setuid(nb->pw_uid);
			} else {
D 17
				fprintf(stderr, "No safe uid available\n");
				_exit(1);
E 17
I 17
				die("No safe uid available to run help file pager.\n");
E 17
			}
		} else {
D 14
			(void) setgid(getgid());
			(void) setuid(getuid());
E 14
I 14
			(void) setgid(CallerPW->mpw_gid);
			(void) setuid(CallerPW->mpw_uid);
E 14
		}
		(void) execl("/bin/sh", "sh", "-c", cmdbuf, 0);
		_exit(0);
I 14
#undef	NOBODY
E 25
I 25
D 46
	while (fgets(inbuf, sizeof(inbuf), in)) {
		(void) fputs(inbuf, stdout);
		(void) fflush(stdout);
E 25
E 14
	}
E 46
I 46
	pager(in);
E 46
D 25
	(void) wait((int *)0);		/* "Wrong" for BSD, right for SYS V */
E 25
I 25
	(void) fclose(in);
E 25
D 14
#undef	NOBODY
E 14
}

/*
D 14
 *	checktty - Attempt to check against being pipe-fed
E 14
I 14
D 25
 *	checktty - Check for input/output redirection
E 25
I 25
D 27
 *	checktty - Check if standard input has been redirected
 *		Such redirection is considered bad.
E 27
I 27
 * checktty
 *	Check if standard input has been redirected. This is considered bad.
 * Usage
 * 	(void) checktty();
 * Errors
 *	Aborts upon error or ttyname(stdin) != ttyname(stdout)
E 27
E 25
E 14
 */
I 5
private void
E 5
checktty()
{
	char	*stdin_tty,	/* ttyname(0) */
D 14
		*stdout_tty,	/* ttyname(1) */
E 14
		*t;		/* Temp */

D 27
	if (!isatty(0)) {
E 27
I 27
	if (!isatty(fileno(stdin))) {
E 27
D 25
		if (ProgramInput == 0)
E 25
I 25
		if (!XSwitches[Xsw_UseStdin])
E 25
			die("Input not a tty.\n");
I 14
D 25
#if	0
E 14
		if (lseek(0, 0L, 1) < 0) {
			if (errno != ESPIPE)
				die("Input not a tty or pipe.\n");
D 14
			else
				return;
E 14
		}
I 14
#endif
E 25
		return;
E 14
	}
D 25
	ProgramInput = 0;		/* Stdin is a tty - behave normal */
E 25
I 25
	XSwitches[Xsw_UseStdin] = 0;	/* Stdin is a tty - behave normal */
E 25
D 14
	stdin_tty = ttyname(0);
	if (stdin_tty == NULL || *stdin_tty == 0)
		die("Cannot get name (stdin).\n");
	t = malloc(strlen(stdin_tty) + 1);
	if (t == NULL)
		logdie("Cannot allocate temp memory.");
	(void) strcpy(t, stdin_tty);
	stdin_tty = t;
E 14
I 14
D 27
	t = ttyname(0);
E 27
I 27
	t = ttyname(fileno(stdin));
E 27
	if (t == NULL || *t == 0)
		die("Cannot get name for input.\n");
D 25
	stdin_tty = copystr(t);
E 25
I 25
	stdin_tty = strdup(t);
E 25
E 14

D 14
	stdout_tty = ttyname(1);
	if (stdout_tty == NULL || *stdout_tty == 0)
		die("Cannot get name (stdout).\n");
	if (strcmp(stdin_tty, stdout_tty))
E 14
I 14
D 27
	t = ttyname(1);
E 27
I 27
	t = ttyname(fileno(stdout));
E 27
	if (t == NULL || *t == 0)
		die("Cannot get name for output.\n");
	if (strcmp(stdin_tty, t))
E 14
		die("Input and output are not the same tty.\n");
	free(stdin_tty);
}

I 39
D 40
private struct dbtab {
	char	*name;
	int	level;
} debugtab[] = {
E 40
I 40
/*
D 41
 * Program debug level table
 */
private debug_levels main_debug_levels[] = {
E 40
	"none",		DB_NONE,
	"verbose",	DB_VERBOSE,
	"lookup",	DB_LOOKUP,
	"update",	DB_UPDATE,
	"config",	DB_CONFIG,
	"misc1",	DB_MISC1,
	"misc2",	DB_MISC2,
	"pwcheck",	DB_PWCHECK,
	"detail",	DB_DETAIL,
	"all",		DB_ALL,
	0,		-1,
};

E 39
I 27
/*
E 41
I 37
 * Command line option defines.  These are used only in this module.
 */
#define	OPTIONS_GENERIC "X:"		/* Baseline command line options */

#ifdef	OS_SUNOS_4
# define	OPTIONS_DEFER	"a"		/* SunOS 4 options punted */
D 48
# define	OPTIONS_OS 	"fsd:e:n:x:"	/* SunOS 4 options supported */
E 48
I 48
# define	OPTIONS_OS 	"fsden:x:"	/* SunOS 4 options supported */
E 48
# define	OPTIONS_IGNORE 	"F:ly"		/* SunOS 4 options to ignore */
#endif

#ifdef	OS_SUNOS_5
D 44
# define	OPTIONS_DEFER	"adhln:w:x:r:s:"/* SunOS 5 options punted */
# define	OPTIONS_OS 	"eg"		/* SunOS 5 options supported */
E 44
I 44
D 45
# define	OPTIONS_DEFER	"adhln:w:x:s:"	/* SunOS 5 options punted */
E 45
I 45
# define	OPTIONS_DEFER	"adfhln:w:x:s:"	/* SunOS 5 options punted */
E 45
# define	OPTIONS_OS 	"egr:"		/* SunOS 5 options supported */
E 44
# define	OPTIONS_IGNORE 	"D:"		/* SunOS 5 options to ignore */
#endif

#ifdef OS_HPUX
# define	OPTIONS_OS "den:x:"		/* HP-UX options supported */
#endif

#ifdef OS_DEC_OSF
# define	OPTIONS_OS "fs"			/* OSF options supported */
#endif

#ifdef OS_AIX
# define	OPTIONS_OS "fs"			/* AIX options supported */
#endif

/*
E 37
 * process_arguments
 *	Process command line arguments
 * Usage
 *	(void) process_arguments(argc, argv, envp);
 * Effects
 *	Sets lots of global variables
I 37
 *
 * Notes
 *	Npasswd can't do everything, so some command line options are
 *	deferred to the vendor program (stashed in SAVE_DIR).
 *	The encounter of any deferred option (in DEFER_OPTIONS), causes
 *	invocation of the vendor program.
E 37
 */
E 27
I 25
private void
process_arguments(argc, argv, envp)
	int	argc;
	char	**argv;
	char	**envp;
{
D 37
	char	opts[128];		/* Command line options */
E 37
I 37
	char	opts[STRINGLEN];	/* Options string for getopt */
E 37
	int	opt;			/* Option processing temp */
D 27
	char	*pn;
E 27
I 27
	char	*pn;			/* Program name from argv[0] */
I 37
#ifdef	OPTIONS_DEFER
	char	*d_argv[256];		/* Arguments for deferred program */
	int	d_argc = 0;		/* Argument counter */
#endif
E 37
I 36
	extern char	*optarg;	/* From getopt() */
	extern int	optind;		/* From getopt() */
E 36
E 27
D 31
	extern char	*optarg;	/* From getopt() */
	extern int	optind;		/* From getopt() */
E 31

	/*
D 37
	 * Process command line options.
E 37
I 37
	 * Build option string for getopt()
E 37
	 */
D 37
	(void) strcpy(opts, SWITCHES_GENERIC);
#ifdef	SWITCHES_OS
	(void) strcat(opts, SWITCHES_OS);
E 37
I 37
	(void) strcpy(opts, OPTIONS_GENERIC);	/* Start with generic options */
#ifdef	OPTIONS_OS
	(void) strcat(opts, OPTIONS_OS);	/* Add platform options we do */
E 37
#endif
D 37
	if (pn = strrchr(argv[0], '/'))
E 37
I 37
#ifdef	OPTIONS_DEFER
	zeromem(d_argv, sizeof(d_argv));
	(void) strcat(opts, OPTIONS_DEFER);	/* Add platform options we punt */
#endif
#ifdef	OPTIONS_IGNORE
	(void) strcat(opts, OPTIONS_IGNORE);	/* Add platform options we ignore */
#endif
	what_to_do = PASSWD;
	ProgramName = "passwd";

	if (pn = strrchr(argv[0], '/'))		/* Invoked with what name? */
E 37
		pn++;
	else
		pn = argv[0];

D 37
	what_to_do = PASSWD;
	ProgramName = "passwd";
E 37
	if (instring(pn, "chsh")) {
		what_to_do = CHSH;
		ProgramName = "chsh";
	}
	if (instring(pn, "chfn")) {
		what_to_do = CHFN;
		ProgramName = "chfn";
	}
I 41
	set_debug_tag(ProgramName);
E 41

D 37
	os_init(argc, argv, envp);
E 37
I 37
	os_init(argc, argv, envp);		/* Call platform init code */

E 37
D 27

E 27
I 27
D 36
#ifdef	HAS_MEMSET
	(void) memset((void *)Switches, 0, sizeof(Switches));
	(void) memset((void *)XSwitches, 0, sizeof(XSwitches));
#else
E 27
	bzero((char *)Switches, sizeof(Switches));
	bzero((char *)XSwitches, sizeof(XSwitches));
D 27

E 27
I 27
#endif
E 36
I 36
	zeromem(Switches, sizeof Switches);
	zeromem(XSwitches, sizeof XSwitches);
I 37

E 37
E 36
E 27
	while ((opt = getopt(argc, argv, opts)) != EOF) {
		switch (opt) {
#ifdef	OS_SUNOS_4
		/*
		 * SunOS 4 options
		 */
		case 'a':
			Switches[(char)opt] = "on";
			break;
I 37
		case 'f':		/* Change finger */
			what_to_do = CHFN;
			break;
		case 's':		/* Change shell */
			what_to_do = CHSH;
			break;
E 37
		case 'l':
			Switches[(char)opt] = "on";
			break;
		case 'y':
			Switches[(char)opt] = "on";
			break;
		case 'd':
			Switches[(char)opt] = "on";
			break;
		case 'e':
			Switches[(char)opt] = "on";
			break;
		case 'n':
			Switches[(char)opt] = strdup(optarg);
			break;
		case 'x':
			Switches[(char)opt] = strdup(optarg);
			break;
		case 'F':
			printf("Option \"-F\" not supported.\n");
			exit(1);
D 37
#endif
E 37
I 37
#endif	/* OS_SUNOS_4 */
#ifdef	OS_SUNOS_5
		/*
		 * SunOS 5 options
		 */
		case 'e':		/* Change shell */
			what_to_do = CHSH;
			break;
		case 'g':		/* Change finger info */
			what_to_do = CHFN;
			break;
I 44
		case 'r':		/* Select service */
			Switches[(char)opt] = strdup(optarg);
			break;
E 44

#endif	/* OS_SUNOS_5 */
E 37
I 35
#ifdef OS_HPUX
		/*
		 * HP-UX code from mstute@compucom.com (Mike Stute)
		 */
		case 'n':
			Switches[(char)opt] = strdup(optarg);
			break;
		case 'x':
			Switches[(char)opt] = strdup(optarg);
			break;
		case 'd':
			Switches[(char)opt] = "on";
			break;
		case 'e':
			Switches[(char)opt] = "on";
			break;
D 37
#endif
E 35
		case 'f':
			what_to_do = CHFN;
			break;
		case 's':
			what_to_do = CHSH;
			break;

		case 'X': {
E 37
I 37
#endif	/* OS_HPUX */
D 41
		case 'X': {		/* Our special options */
E 41
I 41
		case 'X': {		/* -X [Extended options] */
E 41
E 37
D 39
			char	*op;
E 39
I 39
			char	*op = optarg;
E 39
		
D 39
			for (op = optarg; *op; op++) {
E 39
			switch (*op) {
I 37
			case Xsw_Chfn:
				what_to_do = CHFN;	/* chfn mode */
				break;

			case Xsw_Chsh:			/* chsh mode */
				what_to_do = CHSH;
				break;

I 46
D 48
			case Xsw_AskAll:		/* Alwayws ask for pw */
				XSwitches[Xsw_AskAll] = "on";
E 48
I 48
			case Xsw_ChshSpecial:		/* chsh (no check) */
				if (CallerUid)
					die("Option \"-X%s\" reserved for super-user.\n", Xsw_ChshSpecial);
				XSwitches[Xsw_ChshSpecial] = "on";
				what_to_do = CHSH;
E 48
				break;

I 48
			case Xsw_AskOnce:	/* Try once to read password */
				XSwitches[Xsw_AskOnce] = "on";
				break;

			case Xsw_AskAlways:		/* Always ask for pw */
				XSwitches[Xsw_AskAlways] = "on";
				break;

E 48
E 46
I 38
			case Xsw_ShowConfig:		/* Show config */
				XSwitches[Xsw_ShowConfig] = "on";
				break;

E 38
E 37
			case Xsw_CheckConfig:		/* Check config file */
				(void) setgid(getgid()); /* Give away */
				(void) setuid(getuid()); /* privs */
D 36
				configure(++op);
E 36
I 36
				configure(++op, 1);
E 36
				printf("Configuration file \"%s\" OK\n", op);
				exit(0);
				break;

			case Xsw_SetDebug:		/* Debug level */
D 40
				op++;
D 39
				if (!isdigit(*op))
D 29
					die("Debug level is not a number");
E 29
I 29
					die("Debug level is not a number.\n");
E 29
				DebugLevel = atoi(op);
E 39
I 39
				if (isdigit(*op)) {
					DebugLevel = atoi(op);
				} else {
					struct dbtab *dt;

					for (dt = debugtab; dt->name; dt++) {
					   if (strcasecmp(dt->name, op) == 0) {
						DebugLevel = dt->level;
						break;
					   }
					}
				}
E 40
I 40
D 41
				set_debug(++op, main_debug_levels);
E 41
I 41
				set_debug(++op, npasswd_debug);
E 41
E 40
E 39
D 47
				printf("%s: Debug level = %d\n",
D 41
					ProgramName, DebugLevel);
E 41
I 41
					ProgramName, get_debug());
E 47
I 47
				printf("Debug level = %d\n", get_debug());
				printf("Version: %s\nPatch: %s\n%s",
					npasswd_version,
					npasswd_patchlevel,
					build_info);
				print_os_env();
E 47
E 41
				break;

			case Xsw_ForcePWChange:		/* Force change */
I 32
				if (CallerUid)
D 48
					die("Option \"-XF\" reserved for super-user.\n");
E 48
I 48
					die("Option \"-X%s\" reserved for super-user.\n", Xsw_ForcePWChange);
E 48
E 32
				XSwitches[Xsw_ForcePWChange] = "on";
				break;

			case Xsw_UseStdin:		/* Read from stdin */
D 27
				if (MyUid)
E 27
I 27
				if (CallerUid)
E 27
D 48
					die("Option \"-XI\" reserved for super-user.\n");
E 48
I 48
					die("Option \"-X%s\" reserved for super-user.\n", Xsw_UseStdin);
E 48
				XSwitches[Xsw_UseStdin] = "on";
				break;

D 27
			case Xsw_Require_OldPW:		/* Require old passwd even for su */
				if (MyUid)
					die( "Option \"-XR\" reserved for super-user.\n");
				XSwitches[Xsw_Require_OldPW] = "on";
				break;

E 27
			case Xsw_ShowVersion:
				printf("Version: %s\nPatch level: %s\n%s\n",
					npasswd_version, npasswd_patchlevel,
					build_info);
				exit(0);
I 41

			case Xsw_Help:
				{
				debug_table *dt = npasswd_debug;

				printf(Usage, ProgramName);
				printf("Debug levels (-XD...):\n");
				for (; dt->name; dt++)
					printf("\t%s\t%s\n", dt->name, dt->help);
				exit(0);
				}
				/*NOTREACHED*/
				break;
E 41
			}	/* switch */
D 39
			}	/* for */
E 39
		} /* case 'X' */
		break;
I 37

		/* Switches of OPTIONS_IGNORE are quietly not dealt with */

#ifdef	OPTIONS_DEFER
		default: {
			/*
			 * If this option should be deferred, add the switch
			 * and possbily the next argument to the argument list
			 */
			char *xopt;
			if (xopt = strchr(OPTIONS_DEFER, (char )opt)) {
				char	temp[STRINGLEN];

				(void) sprintf(temp, "-%c", (char )opt);
				if (d_argc == 0) d_argc++; /* leave space */
				d_argv[d_argc++] = strdup(temp);
				if (*++xopt == ':')
					d_argv[d_argc++] = strdup(optarg);
			}
			break;
		}
#endif
E 37
		} /* switch */
	} /* for */
I 37

#ifdef	OPTIONS_DEFER
	if (d_argc) {
		/*
		 * Punt to external program
		 */
		while (argv[optind])	/* Copy remaining arguments */
			d_argv[d_argc++] = argv[optind++];
		punt(d_argv, envp);
		/*NOTREACHED*/
	}
#endif
E 37
}

E 25
/*
I 37
 * punt
 *	Execute vendor program to do something that we don't do.
 * Usage
 *	punt(arg-list, environmnet-list)
 */
private
punt(argv, envp)
	char	**argv;		/* Arguments */
	char	**envp;		/* Environment */
{
	char	xpath[MAXPATHLEN];

	if (access(SAVED_BIN, 0) < 0)
D 41
		logdie("Cannot find original '%s' program\n", ProgramName);
E 41
I 41
		logdie("Cannot find saved '%s'\n", ProgramName);
E 41
	
	(void) sprintf(xpath, "%s/%s", SAVED_BIN, ProgramName);
	if (access(xpath, 0) < 0)
		logdie("Cannot find '%s'\n", xpath);

	(void) setgid(getgid());
	(void) setuid(CallerUid);
	argv[0] = ProgramName;
D 41
	if (DebugLevel >= DB_UPDATE) {
E 41
I 41
	if (get_debug() >= DB_UPDATE) {
E 41
		char	**v = argv;

		printf("punt: %s ", xpath);
		for (; *v; v++) {
			printf("'%s' ", *v);
		}
		printf("\n");
	}
#if	(CDEBUG < CDEBUG_SYSTEM)
	(void) execve(xpath, argv, envp);
	/*NOTREACHED*/
	logdie("(punt) Exec of '%s' failed\n", xpath);
	/*NOTREACHED*/
#else
	printf("punt exec\n");
	exit(0);
#endif
}

/*
E 37
D 27
 *	catchit - tty interrupt catcher
E 27
I 27
 * catchit
 *	Generic signal handler
 * Usage
 *	catchit(signal-number)
 * Effects
 #	Aborts with error message
E 27
 */
D 2
catchit(signo)
E 2
I 2
D 5
signal_t catchit(signo)
E 5
I 5
D 6
private void catchit(signo)
E 6
I 6
D 8
private SIGFUNC_T
E 8
I 8
D 17
private SIGNAL_T
E 17
I 17
private Signal_t
E 17
E 8
catchit(signo)
E 6
E 5
E 2
D 12
int	signo;
E 12
I 12
D 27
	int	signo;
E 27
I 27
D 31
	const int	signo;
E 31
I 31
	int	signo;
E 31
E 27
E 12
{
D 46
	fixtty();
E 46
I 46
	term_restore();
E 46
	pw_cleanup(signo);
I 17
D 27
#ifdef	HAS_PSIGNAL
	/* maybe */
#endif
E 27
E 17
	die("\nInterrupted; changes discarded.\n");
}
D 22

D 17
#ifdef	NEED_PUTPWENT
E 17
I 17
#ifndef	HAS_PUTPWENT
E 17
I 5
public void
E 5
putpwent(p, f)
D 12
struct passwd	*p;	/* Passwd entry to put */
FILE	*f;		/* File pointer */
E 12
I 12
	struct passwd	*p;	/* Passwd entry to put */
	FILE	*f;		/* File pointer */
E 12
{
D 14
	char	pwline[512];
E 14
I 14
	char	pwline[PW_LINELEN];
E 14

D 4
	(void) fprintf("%s\n", sputpwent(p, pwline));
E 4
I 4
	sputpwent(p, pwline);
	(void) fprintf(f, "%s\n", pwline);
E 4
}
D 17
#endif	/* NEED_PUTPWENT */
E 17
I 17
#endif	/* HAS_PUTPWENT */
E 17

D 17
#ifdef	NEED_FGETPWENT
E 17
I 17
#ifndef	HAS_FGETPWENT
E 17
/*
 *	fgetpwent() - read passwd(5) entry from a file
 *		This reads the "standard" passwd file format.
 */
D 5
struct passwd *
E 5
I 5
public struct passwd *
E 5
fgetpwent(f)
D 12
FILE	*f;			/* Pointer to open passwd format file */
E 12
I 12
	FILE	*f;			/* Pointer to open passwd format file */
E 12
{
D 14
	static char	ibuf[BUFSIZ];	/* Input and return data buffer */
E 14
I 14
	static char	ibuf[PW_LINELEN];	/* Input and return data buffer */
E 14
I 4
	char	*p;
E 4

	if (fgets(ibuf, sizeof(ibuf), f) == NULL)
		return(0);
D 17
	if ((p = INDEX(ibuf, '\n')) == 0)		/* Zap newline */
E 17
I 17
	if ((p = index(ibuf, '\n')) == 0)		/* Zap newline */
E 17
		logdie("Ill-formed passwd entry \"%s\".\n", ibuf);
	else
		*p = 0;
	return(sgetpwent(ibuf));
}
D 17
#endif	/* NEED_FGETPWENT */
E 17
I 17
#endif	/* HAS_FGETPWENT */
E 17

/*
 *	putpwent - replacement for the System V routine
 *		This writes the "standard" passwd file format.
 */
D 5
char *
E 5
I 5
public char *
E 5
sputpwent(p, b)
D 12
struct passwd	*p;	/* Passwd entry to put */
char		*b;	/* Buffer to build it in */
E 12
I 12
	struct passwd	*p;	/* Passwd entry to put */
	char		*b;	/* Buffer to build it in */
E 12
{
	char	pwb[48];

	(void) strcpy(pwb, p->pw_passwd);
D 14
#if	S5_PWAGING
E 14
I 14
D 17
#if	HAS_PW_AGE
E 17
I 17
#ifdef	PWAGE
E 17
E 14
	if (p->pw_age && *p->pw_age) {
		(void) strcat(pwb, ",");
		(void) strcat(pwb, p->pw_age);
	}
#endif
#ifdef	UIDS_ARE_SIGNED
D 3
	(void) sprintf(b, "%s:%s:%d:%d:%s:%s:%s\n",
E 3
I 3
	(void) sprintf(b, "%s:%s:%d:%d:%s:%s:%s",
E 3
#else
D 3
	(void) sprintf(b, "%s:%s:%u:%u:%s:%s:%s\n",
E 3
I 3
	(void) sprintf(b, "%s:%s:%u:%u:%s:%s:%s",
E 3
#endif
D 9
		p->pw_name, pwb, p->pw_uid, p->pw_gid,
E 9
I 9
D 17
		p->pw_name, pwb, (uid_t )p->pw_uid, (gid_t )p->pw_gid,
E 17
I 17
		p->pw_name, pwb, (Uid_t )p->pw_uid, (Gid_t )p->pw_gid,
E 17
E 9
		p->pw_gecos, p->pw_dir, p->pw_shell);
	return(b);
}

/*
 *	sgetpwent() - crack a passwd(5) format line
 *		This reads the "standard" passwd file format.
 */
D 5
struct passwd *
E 5
I 5
public struct passwd *
E 5
sgetpwent(s)
D 12
char	*s;			/* Pointer to open passwd format file */
E 12
I 12
	char	*s;			/* Pointer to open passwd format file */
E 12
{
	static struct passwd	pwdata;	/* Return data */
D 5
	char		*p, *pp;	/* ACME Pointer Works, Inc */
E 5
I 5
	char		*p;	/* ACME Pointer Works, Inc */
	char		*pp;	/* ACME Pointer Works, Inc */
E 5

D 17
	BZERO((char *)&pwdata, sizeof(pwdata));
E 17
I 17
	bzero((char *)&pwdata, sizeof(pwdata));
E 17
#define	skipc while (*p && *p != ':' && *p != '\n') ++p; if (*p) *p++ = 0
	p = s;
	pwdata.pw_name = p;	skipc;
	pwdata.pw_passwd = p;	skipc;
D 14
#if	S5_PWAGING
E 14
I 14
D 17
#if	HAS_PW_AGE
E 14
	if (pp = INDEX(pwdata.pw_passwd, ',')) {
E 17
I 17
#ifdef	PWAGE
	if (pp = index(pwdata.pw_passwd, ',')) {
E 17
		*pp++ = 0;
		pwdata.pw_age = pp;
	}	
#endif
	pwdata.pw_uid = atoi(p); skipc;
	pwdata.pw_gid = atoi(p); skipc;
	pwdata.pw_gecos = p;	skipc; 
	pwdata.pw_dir = p;	skipc;
	pwdata.pw_shell = p;
	return(&pwdata);
#undef	skipc
}

/*
 *	copypwent - copy a passwd structure
 */
D 5
struct passwd *
E 5
I 5
public struct passwd *
E 5
copypwent(f,t)
D 12
struct passwd	*f,		/* From */
		*t;		/* To */
E 12
I 12
	struct passwd	*f,		/* From */
			*t;		/* To */
E 12
{
D 4
	*t = *f;	/* Possible memory leak due to the string pointers
			 * which may point to malloced storage that is not
			 * reused or freed.
			 */
E 4
I 4
	*t = *f;	
E 4
	t->pw_name = copystr(f->pw_name);
D 14
#ifdef	S5_PWAGING
E 14
I 14
D 17
#ifdef	HAS_PW_AGE
E 17
I 17
#ifdef	PWAGE
E 17
E 14
	t->pw_age = copystr(f->pw_age);
#endif
D 14
#ifdef	PW_COMMENT
E 14
I 14
D 17
#ifdef	HAS_PW_COMMENT
E 17
I 17
#ifdef	PWCOMMENT
E 17
E 14
	t->pw_comment = copystr(f->pw_comment);
#endif
	t->pw_passwd = copystr(f->pw_passwd);
	t->pw_gecos = copystr(f->pw_gecos);
	t->pw_dir = copystr(f->pw_dir);
	t->pw_shell = copystr(f->pw_shell);
	return(t);
}

/*
 *	fgetpwnam - get user from password file
 */
D 5
struct passwd *
E 5
I 5
public struct passwd *
E 5
fgetpwnam(name, pwfile)
D 12
char	*name,
	*pwfile;
E 12
I 12
	char	*name,
		*pwfile;
E 12
{
	FILE	*pf;
	struct passwd	*px;		/* Password file traversal */

	if ((pf = fopen(pwfile, "r")) == NULL)
		logdie("Cannot open password file \"%s\".", pwfile);
	/*
	 * Scan local password file, looking for user
	 */
	while ((px = fgetpwent(pf)) != NULL) {
		char	*tp = px->pw_name;

		if (*tp == '+') tp++;
		if (strcmp(tp, name) == 0) {
			(void) fclose(pf);
			return(px);
		}
	}
	(void) fclose(pf);
	return(NULL);
}

E 22
D 17
#ifdef	NEED_RENAME
E 17
I 17
D 25
#ifndef	HAS_RENAME
E 25
I 25

#ifdef	I_SYS_RESOURCE
#include <sys/resource.h>
#endif
E 25
E 17
/*
D 14
 *	rename - replacement for the 4.2/4.3 BSD rename system call
E 14
I 14
D 25
 *	rename - replacement for the 4BSD rename system call
E 25
I 25
D 27
 * os_init - Per-operating system initialization code
E 27
I 27
 * os_init
 *	Operating system specific initialization
 * Effects
D 37
 *	Clears out environment (from envp) for safety, removes system
 *	resource limits (if present)
E 37
I 37
 *	Clears out environment (from envp) for safety and removes system
 *	resource limits, to prevent hitting our head.
E 37
E 27
E 25
E 14
 */
I 5
D 25
public
E 5
rename(src, dst)
D 12
char	*src,		/* Source path */
	*dst;		/* Destination path */
E 12
I 12
	char	*src,		/* Source path */
		*dst;		/* Destination path */
E 25
I 25
private void
os_init(argc, argv, envp)
	int	argc;
	char	**argv;
	char	**envp;
E 25
E 12
{
D 25
	if (unlink(dst) < 0) {
		if (errno != ENOENT)
			return(-1);
E 25
I 25
	(void) umask((mode_t)0);	/* Full control over file modes */
#ifdef	I_SYS_RESOURCE
	{
	/*
	 * Remove BSD resource limits
	 */
	struct rlimit no_limit;
I 43

E 43
	no_limit.rlim_cur = no_limit.rlim_max = RLIM_INFINITY;
	(void) setrlimit(RLIMIT_CPU, &no_limit);
D 43
	(void) setrlimit(RLIMIT_FSIZE, &no_limit);
E 43
	(void) setrlimit(RLIMIT_DATA, &no_limit);
D 43
	(void) setrlimit(RLIMIT_CORE, &no_limit);
E 43
	(void) setrlimit(RLIMIT_STACK, &no_limit);
I 43
	(void) setrlimit(RLIMIT_FSIZE, &no_limit);
E 43
I 36
D 37
	/* NOTE To raise file descriptor limit */ /* XXXX */
E 37
E 36
#ifdef	RLIMIT_RSS
	(void) setrlimit(RLIMIT_RSS, &no_limit);
#endif
I 37
#ifdef	RLIMIT_AS
	(void) setrlimit(RLIMIT_AS, &no_limit);
#endif
D 43
#ifdef	RLIMIT_NOFILE
	(void) setrlimit(RLIMIT_NOFILE, &no_limit);
#endif
E 43
E 37
E 25
	}
D 25
	if (link(src, dst) < 0)
		return(-1);
	return(unlink(src));
}
E 25
#endif
I 25
D 37
#ifndef	DEBUG
E 37
I 37
#if	(CDEBUG < CDEBUG_SYSTEM)
E 37
	/*
D 37
	 * Sanitize the environment.  There isn't much we will
	 * let through (if anything).
E 37
I 37
	 * Sanitize the environment, which is all changable by the user and
	 * therefore not trustable.  This avoids *some* strange overflows
	 * and bad assumptions by shared libraries and dyanmic loaders.
	 *
	 * This is usually a pointer to the "real" environment vector, so 
	 * the changes made here will be effective throughout the program.
E 37
 	 */
	while (*envp) *envp++ = "";
#endif
}
E 25

I 47
/*
 * print_os_env
 *	Printer runtime environment
 * Effects
 *	Calls uname(2) to get environment information and prints it.
 */
#ifdef	HAS_UTSNAME_H
#include <sys/utsname.h>

private void
print_os_env()
{
	struct utsname	un;

	if (uname(&un) >= 0)
		printf("Operating system: %s %s %s\nPlatform: %s\nNode: %s\n",
			un.sysname, un.release, un.version,
			un.machine, un.nodename);
}
#else
private void
print_os_env()
{
	/* Use something else here instead of uname(2) */
}
#endif	/* HAS_UTSNAME_H */

E 47
D 36
/*
D 4
 *	_newstr - copy string into new storage
E 4
I 4
D 25
 *	copystr - copy string into new storage
E 25
I 25
 *	Utility routines used all over npasswd
E 25
E 4
 */
D 5
char *
E 5
I 5
D 25
public char *
E 5
copystr(s)
D 12
char	*s;		/* String to copy */
E 12
I 12
	char	*s;		/* String to copy */
E 12
{
	char	*t;	/* Temp */
E 25

D 25
	if (s == NULL)
D 4
		return(NULL);
E 4
I 4
		return("");
E 4
	if ((t = malloc(strlen(s) + 1)) == NULL)
		logdie("No memory for string copy.");
	(void) strcpy(t, s);
	return(t);
}

E 25
I 25
/*
D 27
 * FileSizeDiff - Return size difference between two files
 *
 * Usage:
E 27
I 27
 * FileSizeDiff
 *	Find size difference between two files
 * Usage
E 27
 *	diff = FileSizeDiff(file1, file2);
D 27
 * Returns:
 *	size of <file2> - size of <file1> (in bytes)
E 27
I 27
 * Returns
 *	(size of <file2>) - (size of <file1>) bytes
E 27
 */
E 25
I 5
public size_t
E 5
D 14
sizecheck(fn1, fn2)
E 14
I 14
D 25
cmp_file_size(fn1, fn2)
E 25
I 25
FileSizeDiff(fn1, fn2)
E 25
E 14
D 12
char	*fn1,
	*fn2;
E 12
I 12
D 27
	char	*fn1,
		*fn2;
E 27
I 27
D 31
	const char	*fn1,	
			*fn2;
E 31
I 31
	char	*fn1,	
		*fn2;
E 31
E 27
E 12
{
D 27
	struct stat	stb;
D 14
	long	s1;
E 14
I 14
	size_t	s1;
E 27
I 27
	struct stat	stb;	/* ACME Scratch Storage */
	size_t	s1;		/* ACME Scratch Storage */
E 27
E 14

	if (stat(fn1, &stb) < 0)
		return(-1);
	s1 = stb.st_size;
	if (stat(fn2, &stb) < 0)
		return(-1);
	return(s1 - stb.st_size);
}

I 14
/*
D 25
 *	mklocktemp - Make temp file with exclusive use checking
E 25
I 25
D 27
 * MakeLockTemp - Make temp file with exclusive use checking
E 25
 *
D 25
 *	Returns file descriptor of created file, else exits with error
E 25
I 25
 * Usage:
E 27
I 27
 * MakeLockTemp
 *	Create a file with exclusive use checking
 * Usage
E 27
 *	fd = MakeLockTemp(file);
D 27
 * Returns:
E 27
I 27
 * Returns
E 27
 *	File descriptor of created file
I 27
 * Error
 *	Aborts if file cannot be created, usually because
D 33
 *	the file already exists
E 33
I 33
 *	the file exists.
E 33
E 27
E 25
 */
public int
D 25
mklocktemp(name)
E 25
I 25
MakeLockTemp(name)
E 25
D 27
	char	*name;
E 27
I 27
D 31
	const char	*name;
E 31
I 31
	char	*name;
E 31
E 27
{
D 27
	int	fd;
E 27
I 27
	int	fd;	/* ACME Scratch Storage */
I 33
	int	cnt;	/* Retry counter */
E 33
E 27

D 33
	fd = open(name, O_WRONLY|O_CREAT|O_EXCL, 0600);
	/* Need to loop here  */
	if (fd < 0) {
		if (errno == EEXIST)
D 27
			die("Password file busy - try again");
E 27
I 27
D 29
			die("File \"%s\" is busy", name);
E 29
I 29
			die("File \"%s\" is busy.\n", name);
E 29
E 27
		perror("Tempfile create");
D 27
		logdie("Cannot create temp file");
E 27
I 27
D 29
		logdie("Cannot create temp file \"%s\"", name);
E 29
I 29
		logdie("Cannot create temp file \"%s\"\n", name);
E 33
I 33
	for (cnt = 0; cnt <= LockTries; cnt++) {
		if ((fd = open(name, O_WRONLY|O_CREAT|O_EXCL, 0600)) >= 0) 
			return(fd);
		debug(DB_DETAIL, "MakeLockTemp \"%s\" cycle %d\n", name, cnt);
		(void) sleep(LockCycle);
E 33
E 29
E 27
	}
D 33
	return(fd);
E 33
I 33
	perror("Tempfile create");
	logdie("Cannot create temp file \"%s\"\n", name);
E 33
}

D 17
#define	PASSWD_OWNER	(uid_t)0
#define	PASSWD_GROUP	(gid_t)0
E 17
I 17
D 25
#define	PASSWD_OWNER	(Uid_t)0
#define	PASSWD_GROUP	(Gid_t)0
E 17
#define	PASSWD_MODE	0444
#define	SHADOW_MODE	0400

E 25
I 25
#if	!(defined(HAS_FCHMOD) && defined(HAS_FCHMOD))
/*
D 27
 * FixPwFileMode - Set protection for passwd/shadow files
 *
 * Usage:
E 27
I 27
 * FixPwFileMode
 *	Set protection for passwd/shadow files
 * Usage
E 27
 *	FixPwFileMode(filename, "passwd" | "shadow");
I 27
 *
 * Used only when fchmod() and fchown() do not exist
E 27
 */
E 25
public void
D 25
set_protection(file, type)
E 25
I 25
FixPwFileMode(file, type)
E 25
D 27
	char	*file,
		*type;
E 27
I 27
D 31
	const char	*file,
			*type;
E 31
I 31
	char	*file,
		*type;
E 31
E 27
{
D 25
	(void) chown(file, PASSWD_OWNER, PASSWD_GROUP);
E 25
I 25
	(void) chown(file, PASSWD_UID, PASSWD_GID);
E 25
	(void) chmod(file, PASSWD_MODE);
	if (strcmp(type, "shadow") == 0)
		(void) chmod(file, SHADOW_MODE);
}
D 25


E 14
I 12
D 17
#if	OS_BSD
E 17
I 17
#ifdef	I_SYS_RESOURCE
E 17
#include <sys/resource.h>
E 25
#endif
D 25
/*
 * os_init - Per-operating system initialization code
 */
private void
os_init(argc, argv, envp)
	int	argc;
	char	**argv;
	char	**envp;
{
	(void) umask((mode_t)0);	/* Full control over file modes */
D 17
#if     OS_BSD
E 17
I 17
#ifdef	I_SYS_RESOURCE
E 17
	{
	/*
	 * Remove BSD resource limits
	 */
	struct rlimit no_limit;
	no_limit.rlim_cur = no_limit.rlim_max = RLIM_INFINITY;
	(void) setrlimit(RLIMIT_CPU, &no_limit);
	(void) setrlimit(RLIMIT_FSIZE, &no_limit);
	(void) setrlimit(RLIMIT_DATA, &no_limit);
	(void) setrlimit(RLIMIT_CORE, &no_limit);
	(void) setrlimit(RLIMIT_STACK, &no_limit);
I 17
#ifdef	RLIMIT_RSS
E 17
	(void) setrlimit(RLIMIT_RSS, &no_limit);
I 17
#endif
E 17
	}
#endif
D 21
	svc_get(argc, argv, envp);	/* Get service order */
E 21
#ifndef	DEBUG
	/*
	 * Sanitize the environment.  There isn't much we will
	 * let through (if anything).
 	 */
	while (*envp) *envp++ = "";
D 14
	/* Nuke group list */
E 14
I 14
D 17
	/* Nuke group list? */
E 17
E 14
#endif
}
E 25

E 36
E 12
D 5
#ifdef	OS_ULTRIX_4
E 5
I 5
D 17
#ifdef	USE_getsvc
E 17
I 17
D 22
#ifdef	HAS_SVC_CONF
E 17
E 5
#define	_SETUP	1
D 17

#include <sys/svcinfo.h>

E 17
/*
D 4
 * config - Process the service configuration for Ultrix 4.X
E 4
I 4
D 10
 * svc_get - Process the service configuration for Ultrix 4.X
E 10
I 10
 * svc_get - Process the service configuration for Ultrix 4.X and OSF/1
E 10
E 4
 */
I 17
#include <sys/svcinfo.h>
E 17
I 5
private void
E 5
D 4
setup(envp)
E 4
I 4
D 10
svc_get(envp)
E 10
I 10
svc_get(argc, argv, envp)
D 12
int	argc;
char	**argv;
E 10
E 4
char	**envp;	/*NOTUSED*/
E 12
I 12
	int	argc;
	char	**argv;
	char	**envp;	/*NOTUSED*/
E 12
{
	struct svcinfo	*svc;
	int	i,
		j,
		s;

	SecurityLevel = sec_std;
D 9
	ServiceOrder[0] = srv_last;
E 9

	if ((svc = getsvc()) == 0)
		logdie("Cannot get service configuration.\n");

	for (s = i = 0; (j = svc->svcpath[SVC_PASSWD][i]) != SVC_LAST; i++) {
		switch(j) {
		case SVC_LOCAL:
			ServiceOrder[s++] = srv_local;
			break;
		case SVC_YP:
			ServiceOrder[s++] = srv_yp;
			break;
		case SVC_BIND:
			ServiceOrder[s++] = srv_hesiod;
			break;
		}
	}
	ServiceOrder[s++] = srv_last;

	switch (svc->svcauth.seclevel) {
	case SEC_BSD:
		SecurityLevel = sec_std;
		break;
	case SEC_UPGRADE:
		SecurityLevel = sec_u4upgrade;
		break;
	case SEC_ENHANCED:
		SecurityLevel = sec_u4enhanced;
I 10
D 17
#ifdef	OS_ULTRIX_4
E 17
I 17
#ifdef	ULTRIX_AUTH
E 17
		PasswdCrypt = crypt16;
#endif
E 10
		break;
	}
I 10
D 17
#ifdef	OSF1_SECURITY
E 17
I 17
#ifdef	OSF1_AUTH
E 17
D 11
#ifndef	TCB_DIR
# define	TCB_DIR	"/tcb"
#endif
E 11
E 10
	/*
D 10
	 * TODO: Allow the password length settings to override those
	 * provided in the configuration file.
E 10
I 10
	 * If there is a Trusted Computing Base directory, then
D 17
	 * we are running enhanced security.  On OSF/1, the data returned
	 * by getsvc() will NOT be right.
E 17
I 17
	 * we are running enhanced security.
	 * On OSF/1, the "security level" returned by getsvc() is wrong.
E 17
E 10
	 */
I 10
D 11
	if (access(TCB_DIR, 0) == 0) {
E 11
I 11
	if (access(OSF1_TCB, 0) == 0) {
E 11
D 14
		SIAENTITY *who = NULL;
E 14
I 14
		SIAENTITY *who;
E 14

D 17
		sia_ses_init(&who, argc, argv, NULL, NULL, NULL, 0, NULL);
		SecurityLevel = sec_OSFenhanced;
		PasswdCrypt = bigcrypt;
E 17
I 17
		if (sia_ses_init(&who, argc, argv, NULL, NULL, NULL, 0, NULL)
			== SIASUCCESS) {
				SecurityLevel = sec_OSFenhanced;
				PasswdCrypt = bigcrypt;
		}
E 17
	}
D 14
#undef	TCB_DIR
E 14
#endif
E 10
}
D 10
#endif	/* OS_ULTRIX_4 */
E 10
I 10
#endif	/* USE_getsvc */
E 10

D 17
#ifdef	OS_SOLARIS_2
E 17
I 17
#ifdef	HAS_NSSWITCH
E 17
#define	_SETUP	1
D 17

#include <nsswitch.h>

E 17
/*
D 4
 * setup - Process the 'name service' configuration under Solaris 2.X
E 4
I 4
 * svc_get - Process the 'name service' configuration under Solaris 2.X
E 4
 */
I 17
#include <nsswitch.h>
E 17
I 5
D 20
private void
E 5
D 4
setup(envp)
E 4
I 4
D 10
svc_get(envp)
E 10
I 10
svc_get(argc, argv, envp)
D 12
int	argc;	/*NOTUSED*/
char	**argv;	/*NOTUSED*/
E 10
E 4
char	**envp;	/*NOTUSED*/
E 12
I 12
	int	argc;	/*NOTUSED*/
	char	**argv;	/*NOTUSED*/
	char	**envp;	/*NOTUSED*/
E 20
I 20

private char **
get_nsswitch(what)
	char	*what;
E 20
E 12
{
	struct __nsw_switchconfig *config;
	struct __nsw_lookup     *p;
	enum __nsw_parse_err    error;
D 20
	int	svo = 0;
E 20
I 20
	char	*srvlist[32];	/* LIMIT */
	char	**rv;
	int	svcno = 0;
E 20

D 20
	SecurityLevel = sec_std;
D 9
	ServiceOrder[svo] = srv_last;
E 9

	/*
	 * TODO: Figure out what security level needed for RPC 
	 * i.e. might a key need resetting.
	 */
	config = __nsw_getconfig(__NSW_PASSWD_DB, &error);
E 20
I 20
	config = __nsw_getconfig(what, &error);
E 20
	switch (error) {
I 9
#if	(OS_MINOR_VERSION >= 3)
	case __NSW_CONF_PARSE_SUCCESS:
#else
E 9
	case __NSW_PARSE_SUCCESS:
I 9
#endif
E 9
		break;
I 9
#if	(OS_MINOR_VERSION >= 3)
	case __NSW_CONF_PARSE_NOFILE:
#else
E 9
	case __NSW_PARSE_NOFILE:
I 9
#endif
E 9
		printf("Warning: \"%s\" not found.\n", __NSW_CONFIG_FILE);
		return;
I 9
#if	(OS_MINOR_VERSION >= 3)
	case __NSW_CONF_PARSE_NOPOLICY:
#else
E 9
	case __NSW_PARSE_NOPOLICY:
I 9
#endif
E 9
		return;
I 9
#if	(OS_MINOR_VERSION >= 3)
	case __NSW_CONF_PARSE_SYSERR:
#else
E 9
	case __NSW_PARSE_SYSERR:
I 9
#endif
E 9
		printf("Warning: Syntax error in \"%s\".\n", __NSW_CONFIG_FILE);
		return;
	}
	for (p = config->lookups; p; p = p->next) {
D 20
		if (strcmp(p->service_name, "files") == 0)
E 20
I 20
		srvlist[svcno++] = copystr(p->service_name);
	}
	srvlist[svcno] = 0;
	rv = (char **)calloc(sizeof(char *), svcno);
	if (rv == 0)
		logdie("Cannot allocate memory for service list\n");
	bcopy((void *)&srvlist, (void *)rv, (svcno * sizeof(char *)));
	return(rv);
}

private void
svc_get(argc, argv, envp)
	int	argc;	/*NOTUSED*/
	char	**argv;	/*NOTUSED*/
	char	**envp;	/*NOTUSED*/
{
I 21
#define	SV_NIS		"nis"
#define	SV_NISPLUS	"nisplus"
#define	SV_COMPAT	"compat"
#define	SV_FILES	"files"
#define	SV_PWCOMPAT	"passwd_compat"

E 21
	int	svo = 0;
	char	**svlist;

	SecurityLevel = sec_std;
I 21
	debug(DB_LOOKUP, "svc_get nsswitch: ");
E 21

	/*
	 * TODO: Figure out what security level needed for RPC 
	 * i.e. might a key need resetting.
	 */
	for (svlist = get_nsswitch(__NSW_PASSWD_DB); *svlist; *svlist++) {
D 21
		if (strcmp(*svlist, "files") == 0)
E 21
I 21
		if (strcmp(*svlist, SV_FILES) == 0) {
E 21
E 20
			ServiceOrder[svo++] = srv_local;
I 17
D 21
#ifdef	USE_NIS
E 17
D 20
		if (strcmp(p->service_name, "yp") == 0)
E 20
I 20
		if (strcmp(*svlist, "yp") == 0)
E 21
I 21
			debug(DB_LOOKUP, "local ");
		}
#if	defined(USE_NIS) || defined(USE_NISPLUS)
		if (strcmp(*svlist, SV_NIS) == 0) {
E 21
E 20
			ServiceOrder[svo++] = srv_yp;
D 20
		if (strcmp(p->service_name, "compat") == 0)
E 20
I 20
D 21
		if (strcmp(*svlist, "compat") == 0) {
E 21
I 21
			debug(DB_LOOKUP, "nis ");
		}
		if (strcmp(*svlist, SV_COMPAT) == 0) {
			char	**pwsv = get_nsswitch(SV_PWCOMPAT);
			enum	svc_order sv_compat = srv_yp;
			char	*what = "nis";

E 21
			/* Check for service passwd_compat: */
E 20
D 21
			ServiceOrder[svo++] = srv_ypcompat;
I 20
			ServiceOrder[svo++] = srv_yp;
E 21
I 21
			for (; *pwsv; pwsv++) {
				if (strcmp(*pwsv, SV_NISPLUS) == 0) {
					sv_compat = srv_nisplus;
					what = "nisplus";
				}
			}
			ServiceOrder[svo++] = sv_compat;
			debug(DB_LOOKUP, "compat/%s ", what);
E 21
		}
E 20
I 17
#endif
#ifdef	USE_NISPLUS
E 17
D 9
		if (strcmp(p->service_name, "nisplus") == 0)
			ServiceOrder[svo++] = srv_nisplus;
E 9
I 9
D 20
		if (strcmp(p->service_name, "nisplus") == 0) {
E 20
I 20
D 21
		if (strcmp(*svlist, "nisplus") == 0) {
E 21
I 21
		if (strcmp(*svlist, SV_NISPLUS) == 0) {
E 21
E 20
			die("NIS+ not supported\n");
D 17
/* 			ServiceOrder[svo++] = srv_nisplus; */
E 17
I 17
			ServiceOrder[svo++] = srv_nisplus;
I 21
			debug(DB_LOOKUP, "nisplus ");
E 21
E 17
		}
I 17
#endif
E 17
E 9
	}
	ServiceOrder[svo] = srv_last;
I 21
	debug(DB_LOOKUP, "\n");

#undef	SV_NIS
#undef	SV_NISPLUS
#undef	SV_COMPAT
#undef	SV_FILES
#undef	SV_PWCOMPAT
E 21
D 20
	
E 20
}
D 17
#endif	/* OS_SOLARIS_2 */
E 17
I 17
#endif	/* OS_SUNOS_5 */
E 17

#ifndef	_SETUP
I 14
/*
 * The default svc_get() routine
 */
E 14
I 5
private void
E 5
D 4
setup(envp)
E 4
I 4
D 10
svc_get(envp)
E 10
I 10
svc_get(argc, argv, envp)
D 12
int	argc;	/*NOTUSED*/
char	**argv;	/*NOTUSED*/
E 10
E 4
char	**envp;
E 12
I 12
	int	argc;	/*NOTUSED*/
	char	**argv;	/*NOTUSED*/
D 14
	char	**envp;
E 14
I 14
	char	**envp; /*NOTUSED*/
E 14
E 12
{
	SecurityLevel = sec_std;
D 9
	ServiceOrder[0] = srv_last;
E 9
D 14

E 14
D 17
#ifdef	OS_SUNOS_4
E 17
I 17
#ifdef	SUNOS4_SECURITY
E 17
	if (issecure())
		SecurityLevel = sec_sunC2;
D 12
	/* 
	 * Clear out environment of weird stuff to prevent using
	 * the wrong shared SunOS shared libraries for anything this
	 * program execs.
	 */
	if (getuid() != geteuid()) {
		char  **cpp, **xpp;

		for (cpp = envp; *cpp; cpp++) {
			if (strncmp(*cpp, "LD_", strlen("LD_")))
				continue;
			for (xpp = cpp; xpp[0] = xpp[1]; xpp++);
		}
	}
E 12
#endif	/* OS_SUNOS_4 */
}
#endif	/* _SETUP */

D 5
#include <varargs.h>
E 5
/*
I 5
D 20
 * Varargs stuff needed by the following message routines
 */
#ifdef	__STDC__
#define	VA_GETFMT(x,y,z)	x = y;
#else
#define	VA_GETFMT(x,y,z)	x = va_arg(z, char *)
#endif

/*
E 20
I 18
 * debug - print debug message
 */
public void
D 20
debug VA_DCL(char *msgs)
E 20
I 20
#ifdef	__STDC__
debug (int level, char *fmt, ...)
E 20
{
D 20
	va_list	wargs;
	int	level;
	char	*fmt;
E 20
I 20
	va_list	args;
E 20

D 20
	VA_START(wargs, msgs);
	level = va_arg(wargs, int);
	VA_GETFMT(fmt, msgs, wargs);
E 20
	if (DebugLevel < level)
		return;
D 20
	vprintf(fmt, wargs);
E 20
I 20
	va_start(args, fmt);
	vprintf(fmt, args);
E 20
	fflush(stdout);
I 20
	va_end(args);
E 20
}
I 20
#else
debug (va_alist)
va_dcl
{
	va_list	args;
	int	level;
	char	*fmt;
E 20

I 20
	va_start(args);
	level = va_arg(args, int);
	fmt = va_arg(args, char *);
	if (DebugLevel >= level) {
		vprintf(fmt, args);
		fflush(stdout);
	}
	va_end(args);
}
#endif

E 20
/*
E 18
E 5
D 4
 * warn - spew error and die
E 4
I 4
 * die - spew error and die
E 4
 */
D 5
die(va_alist)
va_dcl
E 5
I 5
public void
D 9
die VA_DCL(msgs)
E 9
I 9
die VA_DCL(char *msgs)
E 9
E 5
{
D 20
	va_list	wargs;
D 5
	char	*p,
		*fmt;
E 5
I 5
	char	*p;
E 5
	char	msgbuf[BUFSIZ];
E 20
I 20
	va_list	args;
#ifdef	__STDC__
	fprintf(stderr, "%s: ", ProgramName);
	va_start(args, msgs);
	vfprintf(stderr, msgs, args);
#else
E 20
I 5
	char	*fmt;
E 5

D 5
	va_start(wargs);
	fmt = va_arg(wargs, char *);
E 5
I 5
D 20
	VA_START(wargs, msgs);
	VA_GETFMT(fmt, msgs, wargs);
E 5
	vsprintf(msgbuf, fmt, wargs);
	va_end(wargs);
	p = &msgbuf[strlen(msgbuf)];
	if (*p == '\n') *p = 0;
	fprintf(stderr, "%s: %s\n", ProgramName, msgbuf);
E 20
I 20
	va_start(args);
	fprintf(stderr, "%s: ", ProgramName);
	fmt = va_arg(args, char *);
	vfprintf(stderr, fmt, args);
#endif
	va_end(args);
E 20
	fflush(stderr);
	pw_cleanup(-1);
	exit(1);
}

/*
I 4
D 20
 * warn - spew error and die
E 20
I 20
 * warn - spew error
E 20
 */
D 5
warn(va_alist)
va_dcl
E 5
I 5
public void
D 9
warn VA_DCL(msgs)
E 9
I 9
warn VA_DCL(char *msgs)
E 9
E 5
{
D 20
	va_list	wargs;
	char	*p,
		*fmt;
	char	msgbuf[BUFSIZ];
E 20

D 5
	va_start(wargs);
	fmt = va_arg(wargs, char *);
E 5
I 5
D 20
	VA_START(wargs, msgs);
	VA_GETFMT(fmt, msgs, wargs);
E 5
	vsprintf(msgbuf, fmt, wargs);
	va_end(wargs);
	p = &msgbuf[strlen(msgbuf)];
	if (*p == '\n') *p = 0;
	fprintf(stderr, "%s: %s\n", ProgramName, msgbuf);
E 20
I 20
	va_list	args;
#ifdef	__STDC__
	fprintf(stderr, "%s: ", ProgramName);
	va_start(args, msgs);
	vfprintf(stderr, msgs, args);
#else
	char	*fmt;

	va_start(args);
	fprintf(stderr, "%s: ", ProgramName);
	fmt = va_arg(args, char *);
	vfprintf(stderr, fmt, args);
#endif
	va_end(args);
E 20
	fflush(stderr);
}

/*
E 4
 * logdie - spew error, log message and die
 */
D 5
logdie(va_alist)
va_dcl
E 5
I 5
public void
D 9
logdie VA_DCL(msgs)
E 9
I 9
logdie VA_DCL(char *msgs)
E 9
E 5
{
D 20
	va_list	wargs;
	char	*p,
		*fmt;
	char	msgbuf[BUFSIZ];
E 20
I 20
	va_list	args;
	char	*fmt;
	char	msgbuf[TMPBUFSIZ];
E 20

D 5
	va_start(wargs);
	fmt = va_arg(wargs, char *);
E 5
I 5
D 20
	VA_START(wargs, msgs);
	VA_GETFMT(fmt, msgs, wargs);
E 5
	vsprintf(msgbuf, fmt, wargs);
	va_end(wargs);
	p = &msgbuf[strlen(msgbuf)];
	if (*p == '\n') *p = 0;
E 20
I 20
	VA_START(args, msgs);
#ifdef	__STDC__
	vsprintf(msgbuf, msgs, args);
#else
	fmt = va_arg(args, char *);
	vsprintf(msgbuf, fmt, args);
#endif
	va_end(args);
E 20
	fprintf(stderr, "%s: %s\n", ProgramName, msgbuf);
	fflush(stderr);
D 14
#ifdef	USE_SYSLOG
E 14
D 17
	syslog(ERROR_LOG_LEVEL, msgbuf);
E 17
I 17
	syslog(LOG_ERR, msgbuf);
E 17
D 14
#endif
E 14
	pw_cleanup(-1);
	exit(1);
}

D 9

E 9
/*
D 14
 * log_error - spew error, log message and die
E 14
I 14
 * log_error - spew error and log message
E 14
 */
public void
D 5
logerr(va_alist)
va_dcl
E 5
I 5
D 9
logerr VA_DCL(msgs)
E 9
I 9
logerr VA_DCL(char *msgs)
E 9
E 5
{
D 20
	va_list	wargs;
	char	*p,
		*fmt;
	char	msgbuf[BUFSIZ];
E 20
I 20
	va_list	args;
	char	*fmt;
	char	msgbuf[TMPBUFSIZ];
E 20

D 5
	va_start(wargs);
	fmt = va_arg(wargs, char *);
E 5
I 5
D 20
	VA_START(wargs, msgs);
	VA_GETFMT(fmt, msgs, wargs);
E 5
	vsprintf(msgbuf, fmt, wargs);
	va_end(wargs);
E 20
I 20
	VA_START(args, msgs);
#ifdef	__STDC__
	vsprintf(msgbuf, msgs, args);
#else
	fmt = va_arg(args, char *);
	vsprintf(msgbuf, fmt, args);
#endif
	va_end(args);
E 20
D 14
#ifdef	USE_SYSLOG
E 14
D 17
	syslog(ERROR_LOG_LEVEL, msgbuf);
E 17
I 17
	syslog(LOG_ERR, msgbuf);
E 17
D 14
#else
	p = &msgbuf[strlen(msgbuf)];
	if (*p == '\n') *p = 0;
	fprintf(stderr, "%s: %s\n", ProgramName, msgbuf);
	fflush(stderr);
I 9
#endif
E 14
}
D 20
#undef	VA_GETFMT
E 20

E 22
D 25
/*
 * Signal block/unblock routines.
 */
public void
block_signals VA_DCL(struct sigblk *args)
{
	va_list	fargs;
	struct sigblk *sigblk;
	int	xsig;

	VA_START(fargs, args);
D 20
#ifdef	__STDC__
	sigblk = (struct sigblk *)args;
#else
E 20
	sigblk = va_arg(fargs, struct sigblk *);
D 20
#endif
E 20
I 20

E 20
#if	(SIG_TYPE == SIG_TYPE_POSIX)
	sigemptyset(&sigblk->savesigs);
	while (xsig = va_arg(fargs, int))
		sigaddset(&sigblk->savesigs, xsig);
	sigprocmask(SIG_BLOCK, &sigblk->savesigs, &sigblk->sigvalues);
#endif
I 20

E 20
#if	(SIG_TYPE == SIG_TYPE_BSD)
	sigblk->savesigs = 0;
	while (xsig = va_arg(fargs, int))
		sigblk->savesigs |= sigmask(xsig);
	sigblk->sigvalues = sigblock(sigblk->savesigs);
#endif
I 20

E 20
#if	(SIG_TYPE == SIG_TYPE_UNIX)
	while (xsig = va_arg(fargs, int))
		sigblk->sigvalues[xsig] = signal(xsig, SIG_IGN);
#endif
}

public void
unblock_signals(sigblk)
	struct sigblk *sigblk;
{
#if	(SIG_TYPE == SIG_TYPE_POSIX)
	sigprocmask(SIG_UNBLOCK, &sigblk->savesigs, (sigset_t *)0);
I 17
	return;
E 17
#endif
#if	(SIG_TYPE == SIG_TYPE_BSD)
	sigsetmask(&sigblk->sigvalues);
#endif
#if	(SIG_TYPE == SIG_TYPE_UNIX)
	int	i;
	
	for (i = 0; i <= NSIG; i++) {
		if (sigblk->sigvalues[i])
			(void) signal(i, sigblk->sigvalues[i]);
	}
I 10
#endif
}

dump_user(theUser)
D 12
struct mpasswd *theUser;
E 12
I 12
	struct mpasswd *theUser;
E 12
{
#ifdef	DEBUG
#define	STRX(_Z_) (_Z_ ? _Z_ : "(null)")
	printf("mpw_name = %s\n", STRX(theUser->mpw_name));
	printf("mpw_passwd = %s\n", STRX(theUser->mpw_passwd));
	printf("mpw_uid = %u\n", theUser->mpw_uid);
	printf("mpw_gid = %u\n", theUser->mpw_gid);
	printf("mpw_shell = %s\n", STRX(theUser->mpw_shell));
	printf("mpw_gecos = %s\n", STRX(theUser->mpw_gecos));
	printf("mpw_shell = %s\n", STRX(theUser->mpw_shell));
	printf("mpw_dir = %s\n", STRX(theUser->mpw_dir));
D 14
#ifdef	S5_PWAGING
E 14
I 14
D 17
#ifdef	HAS_PW_AGE
E 17
I 17
#ifdef	PWAGE
E 17
E 14
	printf("mpw_age = %s\n", STRX(theUser->mpw_age));
#endif
D 14
	printf("age_password = %u\n", theUser->age_password);
	printf("last_change = %u\n", theUser->last_change);
	printf("min_change_time = %u\n", theUser->min_change_time);
	printf("expire = %u\n", theUser->expire);
E 14
I 14
D 24
	printf("age_password = %u\n", theUser->pwage.doit);
E 24
I 24
	printf("age_password = %u\n", theUser->pwage.do_aging);
E 24
	printf("last_change = %u\n", theUser->pwage.last_change);
D 24
	printf("min_time = %u\n", theUser->pwage.min_time);
	printf("max_time = %u\n", theUser->pwage.max_time);
E 24
I 24
	printf("min_time = %u\n", theUser->pwage.can_change);
	printf("max_time = %u\n", theUser->pwage.must_change);
E 24
E 14
	printf("key = %s\n", STRX(theUser->key));
	printf("password = %s\n", STRX(theUser->password));
D 24
	printf("where = %s\n", STRX(theUser->where));
	printf("remote = %u\n", theUser->remote);
E 24
I 24
	printf("where = %s\n", STRX(theUser->pws_loc));
	printf("what = %s\n", STRX(theUser->pws_name));
	printf("remote = %u\n", theUser->pws_remote);
E 24
	printf("opaque = %x\n", theUser->opaque);
E 10
E 9
#endif
}
E 25
I 4
/* End %M% */
E 4
E 1
