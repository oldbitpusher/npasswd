h02682
s 00001/00001/00748
d D 1.33 98/10/13 18:13:03 clyde 33 32
c Fix probe label for MaxRepeat
e
s 00021/00014/00728
d D 1.32 98/08/17 13:21:31 clyde 32 31
c 1. Add "whitespace" config directive
c 2. Output check settings in alpha order
c 3. Output 'maxrepeat' setting in probe rtn
e
s 00055/00000/00687
d D 1.31 98/07/17 11:16:16 clyde 31 30
c Add pwck_history_probe()
e
s 00002/00004/00685
d D 1.30 98/07/09 14:21:34 clyde 30 29
c 1. Use new pwsvc() routines
c 2. Use set_debug() for "debug" directive
e
s 00004/00003/00685
d D 1.29 98/07/09 08:51:30 clyde 29 28
c Change checkpassword_verify() to char *
e
s 00014/00000/00674
d D 1.28 98/06/30 15:43:59 clyde 28 27
c Add routine checkpassword_verify() to sanity check password check settings
e
s 00008/00004/00666
d D 1.27 98/06/26 13:30:18 clyde 27 26
c Add second argument to checkpassword_configure()
e
s 00002/00002/00668
d D 1.26 98/06/04 08:44:27 clyde 26 25
c 1. Update debug compile conditional
c 2. Change hash file detect code
e
s 00001/00001/00669
d D 1.25 98/04/17 16:18:59 clyde 25 24
c Fix call of pwck_history_configure()
e
s 00161/00096/00509
d D 1.24 98/04/16 17:01:26 clyde 24 23
c 1. Move check proc table to front of file
c 2. Make overlength password warning a config file option
c 3. Rearrange default configuration
c 4. Change configuration directive processing
c 5. Change dictionary processing
e
s 00192/00132/00413
d D 1.23 98/04/07 10:03:15 clyde 23 22
c 1. Add UT copyright
c 2. Change type of pwck_<foo>() to (char *)
c 3. Change calling sequence of pwck_<foo>()
c 4. Remove error code to error message conversions
c 5. Change MinPassword to 6
c 6. Change type of checkpassword() to (char *)
c 7. Make some password check functions mandatory
c 8. Change dictionary from linked list to arrays
c 9. Remove _flipstring (no longer used)
e
s 00099/00046/00446
d D 1.22 98/03/26 11:13:14 clyde 22 21
c 1. Change reply message lookup 
c 2. Add MinCharClasses configuration setting 
c 3. Add argument for size of message buffer 
c 4. Change debug() calls
c 5. Check password for maximum length overflow 
c 6. Change checkproc config handling 
c 7. Avoid duplication in dictionary list
e
s 00005/00000/00487
d D 1.21 97/10/29 14:39:37 clyde 21 20
c Add "alpha only" config switch
e
s 00007/00002/00480
d D 1.20 96/12/05 12:35:09 clyde 20 19
c 1. Fix config parsing bug
c 2. Add 'dictionaries' directive to built-in config
e
s 00037/00047/00445
d D 1.19 96/09/12 16:21:32 clyde 19 18
c 1. Change debug statements
c 2. Use case-insensitive string compares
c 3. Call history checker init routine
e
s 00014/00014/00478
d D 1.18 96/08/29 12:59:34 clyde 18 17
c Remove 'const' declarations (too much compiler trouble)
e
s 00169/00113/00323
d D 1.17 96/08/15 13:46:33 clyde 17 16
c 1. Add lots of comments
c 2. Fix const usage
c 3. More cleanup of checkpassword_configure()
e
s 00037/00016/00399
d D 1.16 96/08/13 13:06:52 clyde 16 15
c 1. Add const where useful
c 2. Explicit use of bcopy/memcpy
c 3. Add more configuration hooks
e
s 00001/00001/00414
d D 1.15 96/08/09 16:17:55 clyde 15 14
c Beta 3 development checkin 2
e
s 00021/00017/00394
d D 1.14 96/08/09 14:56:50 clyde 14 13
c Beta 3 development checkin 2
e
s 00035/00418/00376
d D 1.13 96/08/06 14:13:51 clyde 13 12
c beta 3 cycle 1 checkin
e
s 00040/00013/00754
d D 1.12 96/03/27 17:20:06 clyde 12 11
c 1. Add debug flag to Config structure
c 2. More diagnostics for add_all_dicts use
e
s 00072/00011/00695
d D 1.11 96/03/26 14:11:54 clyde 11 10
c Add 'dictionaries' directive
e
s 00009/00007/00697
d D 1.10 95/04/05 16:20:02 clyde 10 9
c Beta 3 development checkin
e
s 00005/00002/00699
d D 1.9 94/07/14 17:00:59 clyde 9 8
c Make writable copy of configuration strings before using
e
s 00001/00001/00700
d D 1.8 94/03/17 15:49:56 clyde 8 7
c Use BCOPY for bcopy
e
s 00004/00001/00697
d D 1.7 94/03/16 11:08:52 clyde 7 6
c 1. Add reply codes for PWCK_REUSE
c 2. Don't initialize twice
e
s 00015/00007/00683
d D 1.6 94/03/15 18:53:07 clyde 6 5
c Use new include files
c Add history to checkorder
c Add history configuration directive
e
s 00029/00015/00661
d D 1.5 94/01/07 18:16:44 clyde 5 4
c 1. Fix routine decls
c 2. Minor change of interface to configure_checkpassword()
e
s 00011/00003/00665
d D 1.4 94/01/06 14:44:06 clyde 4 3
c Return the right code, add comments
e
s 00622/00058/00046
d D 1.3 94/01/05 15:49:43 clyde 3 2
c Development checkin
e
s 00001/00001/00103
d D 1.2 93/06/07 14:20:46 clyde 2 1
c Change '\0177' to '\177' to make some compilers happy
e
s 00104/00000/00000
d D 1.1 89/05/18 10:05:15 clyde 1 0
c date and time created 89/05/18 10:05:15 by clyde
e
u
U
t
T
I 1
/*
I 23
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
E 23
D 3
 *	checkpasswd.c - Password check driver and data initialization
E 3
I 3
D 17
 *	checkpasswd.c - Password checking library entry point
E 17
I 17
 * %M%
 *	Password check library entry point
 *
 * Exported routines
 *	checkpassword()			Public
 *	checkpassword_init()		Public
 *	checkpassword_configure()	Public
D 23
 *	_flipstring()			libpwcheck modules
E 23
 *
 * Exported variables
 *	Config				libpwcheck modules
 *
D 23
 * Compilation
 *	cc -I.. -I../Common ...
E 23
I 23
 * The 'pwck_*' routines return a string telling why the password
 * is not acceptable, or (char *)0 if it's ok
E 23
 *
D 23
 *	The 'pwck_*' routines all use the PWCK_* return
 *	codes, which are then passed to the caller.
 *
 *	The pwck_* routines are called thusly:
D 18
 *		rc = pwck_foo(const char *password, struct passwd *user,
E 18
I 18
 *		rc = pwck_foo(char *password, struct passwd *user,
E 18
 *			char *mesg);
E 23
I 23
 * The pwck_* routines are called thusly:
 *	message = pwck_foo(char *, struct passwd *)
E 23
E 17
E 3
 */

#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu)";
#endif

D 3
#include "checkpasswd.h"
E 3
I 3
D 6
#include "compat.h"
#include "lib.h"
E 6
I 6
D 13
#include "compatibility.h"
E 6
#include "checkpassword.h"
I 6
#include "pwck_lib.h"
E 13
I 13
#include "pwck_defines.h"
D 14
#include "lib/lib_util.h"
E 14
I 14
D 23
#include "common.h"
I 20
#include "options.h"
E 23
E 20
E 14
E 13
E 6
E 3

I 3
D 13
#ifdef	__STDC__
D 11
private void	add_dict(char *, int);
E 11
I 11
private void	add_one_dict(char *, int);
private int	add_all_dicts(char *);
E 11
private void	add_proc(char *);
private int	split(char *, char **);
private int	xatoi(char *, char **, int *);
private int	decode_boolean(char *);
private int	decode_int(char *);
D 11
/* private int	octdigit(char); */
/* private int	decdigit(char); */
/* private int	hexdigit(char); */
E 11
I 11
private int	octdigit(char);
private int	decdigit(char);
private int	hexdigit(char);
E 11
private void	decode_string(char *, char *, int);
I 5
#else
D 11
private void	add_dict();
E 11
I 11
private void	add_one_dict();
private int	add_all_dicts();
E 11
private void	add_proc();
I 11
private int	octdigit();
private int	decdigit();
private int	hexdigit();
private void	decode_string();
E 11
E 5
#endif
E 13
I 13
D 16
private void	add_one_dict _((char *));
private int	add_all_dicts _((char *));
private void	add_proc _((char *));
E 16
I 16
D 18
private void	add_one_dict _((const char *));
private int	add_all_dicts _((const char *));
private void	add_proc _((const char *));
E 18
I 18
D 23
private void	add_one_dict _((char *));
E 23
I 23
private int	add_one_dict _((char *));
E 23
private int	add_all_dicts _((char *));
D 23
private void	add_proc _((char *));
E 23
I 23
private char	*add_proc _((char *));
private char	*check_procs();
E 23
E 18
E 16
E 13

I 17
/*
D 23
 * Explanitory texts for why a password was rejected
 */
E 17
D 22
private char *replies[] = {
	0,					/* PWCK_OK */
	"it is empty",				/* PWCK_NULL */
	"it is too easy to guess",		/* PWCK_OBVIOUS */
	"it is part of your 'finger' information", /* PWCK_FINGER */
	"it was found in a dictionary",		/* PWCK_INDICT */
	"it has an illegal character in it",	/* PWCK_ILLCHAR */
	"it is too short",			/* PWCK_SHORT */
I 7
	"it has been used recently ",		/* PWCK_REUSE */
E 7
	0
E 22
I 22
struct canned_message {
	char	*mesg;
	int	code;
E 22
};
D 7
#define	NREPLIES	7	/* Number of messages in replies */
E 7
I 7
D 22
#define	NREPLIES	8	/* Number of messages in replies */
E 22
I 22
private struct canned_message canned_replies[] = {
	{ "it is empty",			 PWCK_NULL },
	{ "it is too easy to guess",		 PWCK_OBVIOUS },
	{ "it is part of your 'finger' information",  PWCK_FINGER },
	{ "it is too similar to a dictionary word",   PWCK_INDICT },
	{ "it has an illegal character in it",	 PWCK_ILLCHAR },
	{ "it is too short",			 PWCK_SHORT },
	{ "it has been used recently ",		 PWCK_REUSE },
	{ 0, 0 },
};
E 22
E 7

I 22

E 22
E 3
/*
E 23
D 3
 *	Table of password check parameters
 *	May be modified via the configuration file
E 3
I 3
D 17
 * Data for checkpassword configuration
E 17
I 17
 * Default checkpasswd configuration
E 17
E 3
 */
D 3
int	single_case =	0,		/* Single-case pwds ok */
	print_only =	0,		/* Printable ASCII chars only */
	run_length =	3,		/* How long chars runs can be */
	min_length =	5,		/* Minimum length */
	max_length =	8;		/* Maximum effective length */
E 3
I 3
private char	*_default_config[] = {
I 16
D 23
	"PasswordChecks	history lexical local passwd crack",
E 23
I 23
D 24
	"PasswordChecks	lexical history local dictionary",
E 23
E 16
D 14
	"singlecase	yes",		/* Allow mono case */
	"printonly 	no",		/* Printable ASCII chars only */
	"runlength 	3",		/* How long chars runs can be */
	"minlength 	5",		/* Minimum length */
	"maxlength 	8",		/* Maximum effective length */
D 11
	"mandatory	/usr/dict/words",
D 6
	"checkorder	lexical local passwd crack",
E 6
I 6
	"history	/etc/passwd.history",
E 11
	"checkorder	history lexical local passwd crack",
E 14
I 14
	"MonocaseOK	yes",		/* Allow mono case */
	"PrintableOnly 	no",		/* Printable ASCII chars only */
E 24
I 24
	"PasswordChecks	lexical passwd local history dictionary",
E 24
	"MaxRepeat 	3",		/* How long chars runs can be */
D 16
	"MinPassword 	5",		/* Minimum length */
	"MaxPassword 	8",		/* Maximum effective length */
	"PasswordChecks	history lexical local passwd crack",
E 16
I 16
#ifdef	SYSTEM_PASSWD_MIN
	"MinPassword 	SYSTEM_PASSWD_MIN",	/* Minimum length */
#else
D 23
	"MinPassword 	5",			/* Minimum length */
E 23
I 23
D 24
	"MinPassword 	6",			/* Minimum length */
E 24
I 24
	"MinPassword 	6",		/* Minimum length */
E 24
E 23
#endif
#ifdef	SYSTEM_PASSWD_MAX
	"MaxPassword 	SYSTEM_PASSWD_MAX",	/* Maximum effective length */
#else
D 24
	"MaxPassword 	8",			/* Maximum effective length */
E 24
I 24
	"MaxPassword 	8",		/* Maximum effective length */
E 24
#endif
I 22
D 24
	"MinCharClasses	1",		/* Minimum required character classes */
E 22
I 20
	"Dictionaries	@",
E 24
I 24
	"Dictionaries	@",		/* Where default dictionaries live */
	"PrintableOnly 	no",		/* Allow control chars */
I 32
	"WhiteSpace 	yes",		/* Allow whitespace */
E 32
	/*
	 * The next three defaults interlock:
	 */
	"SingleCase	yes",		/* Allow single case alpha */
	"AlphaOnly	yes",		/* Allow alpha only */
	"CharClasses	1",		/* Minimum required character classes */
E 24
E 20
E 16
E 14
E 6
	0
};
E 3

/*
 *	Control characters best avoided - commonly-used terminal controls.
 *	Add characters here or replace entire contents via the
 *	configuration file.
 */
D 3
#define	ctrl(d)	('d' & 037)
E 3
I 3
#define	ctrl(d)	((d) & 037)
E 3

D 3
char	illegalcc[sizeof_illegalcc] = {
	ctrl(c),	/* Interrupt character */
	ctrl(d),	/* UNIX end-of-file */
	ctrl(h),	/* Backspace */
/* 	ctrl(i), */
	ctrl(j),	/* Newline */
	ctrl(m),	/* Carriage return */
	ctrl(o),	/* Flush output */
	ctrl(r),	/* Retype pending input */
	ctrl(s),	/* Suspend output */
	ctrl(q),	/* Resume output */
	ctrl(y),	/* Suspend program deferred */
	ctrl(z),	/* Suspend program immediate */
	ctrl(\\),	/* Quit signal */
	ctrl([),	/* escape - may do strange things to ttys if echoed */
	ctrl(]),	/* UNIX telnet escape */
E 3
I 3
char	_illchar[] = {
	ctrl('c'),	/* Interrupt character */
	ctrl('d'),	/* UNIX end-of-file */
	ctrl('h'),	/* Backspace */
	ctrl('j'),	/* Newline */
	ctrl('m'),	/* Carriage return */
	ctrl('o'),	/* Flush output */
	ctrl('r'),	/* Retype pending input */
	ctrl('s'),	/* Suspend output */
	ctrl('q'),	/* Resume output */
	ctrl('y'),	/* Suspend program deferred */
	ctrl('z'),	/* Suspend program immediate */
	ctrl('\\'),	/* Quit signal */
	ctrl('['),	/* escape - may do strange things to ttys if echoed */
	ctrl(']'),	/* UNIX telnet escape */
E 3
D 2
	'\0177',	/* rubout */
E 2
I 2
	'\177',		/* rubout */
E 2
	0
};
I 4
#undef	ctrl
E 4

/*
I 24
 * This is the table of password check routines
 * Additional checks can be added to this table
 */
struct _procnames {
	char		*name;		/* Function name */
	checkproc	addr;		/* Address */
	int		mandatory;	/* Is this check mandatory? */
};
private struct _procnames procnames[] = {
	{ "lexical",	pwck_lexical,	1 },
	{ "local",	pwck_local,	0 },
	{ "passwd",	pwck_passwd,	1 },
	{ "dictionary",	pwck_crack,	1 },
	{ "history",	pwck_history,	0 },
	0
};

/*
E 24
I 3
D 17
 * The configuration block
E 17
I 17
 * The checkpasswd configuration block
E 17
 */
D 12
public struct checkpassword_config	Config = { 0 };
E 12
I 12
D 16
public struct checkpassword_config	Config = { 1, 0 }; /* XXX */
E 16
I 16
D 19
public struct checkpassword_config	Config = {
#ifdef	DEBUG
	/* Config.debug = */ 1,
#endif
	0 
};
E 19
I 19
public struct checkpassword_config	Config = { 0 };
E 19
E 16
E 12

/*
I 31
 * checkpassword_probe
 *	Print the state of the password check system to stdout
 * Usage:
 *	checkpassword_probe(char *message-prefix)
 */
public void
checkpassword_probe(prefix)
	char	*prefix;
{
	int	i;
	char	*p;
	checkproc	*c;
	char	tn[STRINGLEN];

D 32
	(void) sprintf(tn, "%shistory\t", prefix);
E 32
I 32
	(void) sprintf(tn, "%sHistory\t", prefix);
E 32
	pwck_history_probe(tn);

D 32
	printf("%sMinPassword\t%d\n", prefix, Config.min_length);
	printf("%sMaxPassword\t%d\n", prefix, Config.max_length);
E 32
I 32
	printf("%sAlphaOnly\t%s\n", prefix, Config.alpha_only ? "yes" : "no");
E 32
	printf("%sCharClasses\t%d\n", prefix, Config.char_classes);
D 32

	printf("%sSingleCase\t%s\n",
		prefix, Config.single_case ? "yes" : "no");
	printf("%sAlphaOnly\t%s\n",
		prefix, Config.alpha_only ? "yes" : "no");
	printf("%sPrintOnly\t%s\n",
		prefix, Config.print_only ? "yes" : "no");
	printf("%sLengthWarn\t%s\n", prefix,
		Config.length_warn ? "yes" : "no");

E 32
	printf("%sDisallowedChars\t", prefix);
	for (p = Config.badchars; *p; p++) {
		printf("%s ", ctran(*p));
	}
	printf("\n");
I 32
	printf("%sLengthWarn\t%s\n", prefix,
		Config.length_warn ? "yes" : "no");
E 32

I 32
	printf("%sMaxPassword\t%d\n", prefix, Config.max_length);
D 33
	printf("%sMaxRepeats\t%d\n", prefix, Config.run_length);
E 33
I 33
	printf("%sMaxRepeat\t%d\n", prefix, Config.run_length);
E 33
	printf("%sMinPassword\t%d\n", prefix, Config.min_length);

E 32
	printf("%sPasswordChecks\t", prefix);
	for (c = Config.checkprocs; *c; c++) {
		struct _procnames	*pn;

		for (pn = procnames; pn->name; pn++) {
			if (pn->addr == *c)
				printf("%s ", pn->name);
		}
	}
	printf("\n");

I 32
	printf("%sPrintOnly\t%s\n",
		prefix, Config.print_only ? "yes" : "no");
	printf("%sSingleCase\t%s\n",
		prefix, Config.single_case ? "yes" : "no");
	printf("%sWhiteSpace\t%s\n",
		prefix, Config.whitespace ? "yes" : "no");

E 32
	printf("%sDictionaries\n", prefix);
	for (i = 0; Config.dictionaries[i]; i++) {
		printf("\t%s\n", Config.dictionaries[i]);
	}
D 32

E 32
}

/*
E 31
D 17
 *	checkpassword - Password candidate sanity checker.
E 17
I 17
 * checkpassword
 *	Password sanity checker
E 17
 *
D 17
 *	Arguments;
 *		password = plain text password string to check.
 *		userid = the uid whom the password is for, -1 to disable.
 *		mesgbuf = buffer to stash error message
E 17
I 17
 * Usage
D 23
 *	ok = checkpassword(char *password, struct passwd *user, char *message);
E 23
I 23
 *	ok = checkpassword(char *password, struct passwd *user);
E 23
E 17
 *
D 17
 *	Returns:
 *		1 if the password is ok to use,
 *		0 otherwise, and the reason is stashed in mesgbuf
E 17
I 17
 * Returns
D 23
 *	1 if the password is ok to use,
D 22
 *	0 if not - the reason is stashed in mesgbuf
E 22
I 22
 *	0 if not - the reason is stashed in reply_buf
E 23
I 23
 *	(char *)0 if the password is ok to use
 *	Message why not if not
E 23
E 22
E 17
 */
D 23
public int
D 22
checkpassword(password, user, mesgbuf)
E 22
I 22
checkpassword(password, user, reply_buf, sz_reply_buf)
E 23
I 23
public char *
checkpassword(password, user)
E 23
E 22
D 16
	char	*password;		/* Candidate password */
	struct passwd *user;		/* Passwd entry for the user */
E 16
I 16
D 17
	const char	*password;		/* Candidate password */
	const struct passwd *user;		/* Passwd entry for the user */
E 16
	char	*mesgbuf;		/* Where to stash message */
E 17
I 17
D 18
	const char	*password;	/* Candidate password */
	const struct passwd *user;	/* Passwd entry for target user */
E 18
I 18
D 19
	char	*password;	/* Candidate password */
	struct passwd *user;	/* Passwd entry for target user */
E 19
I 19
	char		*password;	/* Candidate password */
D 22
	struct passwd *user;		/* Passwd entry for target user */
E 19
E 18
	char		*mesgbuf;	/* Where to stash message */
E 22
I 22
	struct passwd	*user;		/* Passwd entry for target user */
D 23
	char		*reply_buf;	/* Where to stash message */
	unsigned int	sz_reply_buf;	/* Size of message stash */
E 23
E 22
E 17
{
D 23
	int		rcode;		/* General purpose scratch */
E 23
I 23
	char		*rmsg;
E 23
	checkproc	*checkfunc;	/* Check function pointer */
D 23
	static char	elucidate[BUFSIZ];	/* Expanded error message */
E 23
D 17
	static char	xpasswd[32];	/* Temporary storage for candidate */
E 17
I 17
	static char	xpasswd[BUFSIZ];	/* Temporary storage for candidate */
I 22
D 23
	struct canned_message *cm;
E 23
E 22
E 17

I 22
D 23
#define	getreply(_O_) {\
	for (cm = canned_replies; cm->mesg; cm++) {\
		if (cm->code == _O_) { \
			(void) strncpy(reply_buf, cm->mesg, sz_reply_buf);\
			break;\
		}\
	 } \
	}

E 23
E 22
D 17
	if (password == 0 || *password == 0)	/* Null password */
		return(PWCK_NULL);

	(void) strcpy(xpasswd, password);
D 12
#ifdef	DEBUG
	printf("checkpassword %d %s %x\n", user->pw_uid, xpasswd, mesgbuf);
#endif
E 12
I 12

E 17
E 12
	if (Config.initialized == 0)
		checkpassword_init();
D 17

E 17
I 12
D 19
	if (Config.debug)
		printf("checkpassword: uid=%d passwd=\"%s\" mesgbuf=0x%x\n",
D 17
			user->pw_uid, xpasswd, mesgbuf);

E 12
D 13
	xpasswd[Config.max_length] = 0;	/* Truncate to effective length */
E 13
I 13
D 16
	xpasswd[Config.max_length] = 0;		/* XXX */
E 16
I 16
	xpasswd[Config.max_length] = 0;
E 16

E 17
I 17
			user->pw_uid, password, mesgbuf);
E 19
I 19
D 22
	debug(DB_LOOKUP, "checkpassword: name=%s passwd=\"%s\" mesgbuf=0x%x\n",
			user->pw_name, password, mesgbuf);
E 19
E 17
E 13
	if (mesgbuf)
		mesgbuf[0] = 0;
E 22
I 22
D 23
	debug(DB_PWCHECK, "checkpassword: name=%s passwd=\"%s\" reply_buf=0x%x\n",
			user->pw_name, password, reply_buf);
	if (reply_buf)
		reply_buf[0] = 0;
E 23
I 23
	debug(DB_PWCHECK,
		"checkpassword: name=%s passwd=\"%s\"\n",
		user->pw_name, password);
E 23
E 22
I 17
	if (password == 0 || *password == 0) {	/* Empty password */
D 22
		if (mesgbuf)
			(void) strcpy(mesgbuf, replies[PWCK_NULL]);
E 22
I 22
D 23
		if (reply_buf)
			getreply(PWCK_NULL);
		debug(DB_PWCHECK, "checkpassword: return %d\n", PWCK_NULL);
E 23
I 23
		debug(DB_PWCHECK, "checkpassword: Null password\n");
E 23
E 22
		return(PWCK_NULL);
	}
	/*
	 * Cut to length *after* checkpasword_init(),
D 22
	 * since max_length may be set therein
E 22
I 22
	 * since max_length should be set therein.
	 *
	 * The original is *not* chopped, because it may well be read-only.
	 * Also, there can be a skew between what this code thinks the
	 * maximum functional password length is, and what it really is.
E 22
	 */
D 22
	(void) strcpy(xpasswd, password);
D 19
	xpasswd[Config.max_length] = 0;
E 19
I 19
	if (Config.max_length)
E 22
I 22
	(void) strncpy(xpasswd, password, sizeof xpasswd);
I 23
	xpasswd[ (sizeof xpasswd) - 1] = 0;
E 23
	if (Config.max_length) {
E 22
D 23
		xpasswd[Config.max_length] = 0;
E 23
I 23
D 24
#ifdef	LONG_PASSWORD_WARNING
E 24
E 23
I 22
		/*
		 * Only the first <max_length> characters of a password are
		 * actually used by crypt(3).  If the given password is longer
		 * than this, issue warning message.
		 * This test logically belongs in pwck_lexical, but
		 * the password is chopped here.
		 *
		 * The test is disabled by default.
		 * This message gets some users get very confused.
		 */
D 23
#ifdef	LONG_PASSWORD_WARNING
E 23
D 24
		if (strlen(password) > Config.max_length) {
E 24
I 24
		if (strlen(password) > Config.max_length && Config.length_warn) {
E 24
D 23
			printf("Only the first %d characters of this password will be used\n",
E 23
I 23
			warn("Only the first %d characters of this password will be used\n",
E 23
				Config.max_length);
		}
D 24
#endif
E 24
I 23
		xpasswd[Config.max_length] = 0;
E 23
	}
E 22
E 19
E 17

	for (checkfunc = Config.checkprocs; *checkfunc; checkfunc++) {
I 20
D 22
	debug(DB_LOOKUP, "checkpassword: func=%x\n", *checkfunc);
E 22
I 22
		debug(DB_PWCHECK, "checkpassword: func=%x\n", *checkfunc);
D 23
		elucidate[0] = 0;
E 22
E 20
		if ((rcode = (*checkfunc)(xpasswd, user, elucidate)) != PWCK_OK) {
D 17
			if (elucidate[0])
E 17
I 17
D 22
			if (elucidate[0] && mesgbuf)
E 17
				(void) strcpy(mesgbuf, elucidate);
D 17
			else if (rcode > 0 && rcode <= NREPLIES && replies[rcode])
E 17
I 17
			else if (rcode > 0 && rcode <= NREPLIES && replies[rcode] && mesgbuf)
E 17
				(void) strcpy(mesgbuf, replies[rcode]);
I 12
D 19
			if (Config.debug)
				printf("checkpassword: return code %d, message \"%s\"\n",
E 19
I 19
			debug(DB_LOOKUP,
E 22
I 22
			if (reply_buf) {
				if (elucidate[0])
					(void) strncpy(reply_buf,
						 elucidate, sz_reply_buf);
				else 
					getreply(rcode);
			}
E 23
I 23
		if ((rmsg = (*checkfunc)(xpasswd, user)) != PWCK_OK) {
E 23
			debug(DB_PWCHECK,
E 22
D 23
				"checkpassword: return %d, message \"%s\"\n",
E 19
D 22
					rcode, mesgbuf);
E 22
I 22
					rcode, reply_buf ? reply_buf : "");
E 22
E 12
D 4
			return(0);
E 4
I 4
			return(rcode);
E 23
I 23
				"checkpassword: return \"%s\"\n", rmsg);
			return(rmsg);
E 23
E 4
		}
	}
I 12
D 19
	if (Config.debug)
		printf("checkpassword: password OK\n");
E 19
I 19
D 22
	debug(DB_VERBOSE, "checkpassword: password OK\n");
E 22
I 22
	debug(DB_PWCHECK, "checkpassword: password OK\n");
E 22
E 19
E 12
D 4
	return(1);
E 4
I 4
	return(PWCK_OK);
E 4
}

/*
D 13
 *	decode_boolean - decode a boolean value
 */
private int
decode_boolean(s)
	char	*s;
{
	return(*s == '1'
		| streq(s, "true")
		| streq(s, "yes")
		| streq(s, "on"));
}

/*
 *	decode_int - decode an integer value
 */
private int
decode_int(s)
	char	*s;		/* String to decode */
{
	int	t;	/* Temp */

	if (xatoi(s, (char **)0, &t))
		return(t);
	return(-1);
}

/*
 *	Is argument an octal digit?
 */
private	int
octdigit(c)
	char	c;
{
	return (c >= '0' && c <= '7');
}

/*
 *	Is argument a decimal digit?
 */
private	int
decdigit(c)
	char	c;
{
	return (c >= '0' && c <= '9');
}

/*
 *	Is argument a hexidecimal digit?
 */
private int
hexdigit(c)
	char	c;
{
	return (decdigit(c) |
		(c >= 'a' &&  c <= 'f') |
		(c >= 'A' && c <= 'F'));
}

/*
 *	xatoi - Smart 'atoi' recognizes decimal, octal and hex constants
 */
private
xatoi(ip, ipp, iv)
	char	*ip,	/* Pointer to number string */
		**ipp;	/* Stash pointer to end of string */ /* RETURN VALUE */
	int	*iv;	/* RETURN VALUE */
{
	int	(*func)() = decdigit,	/* Function to check char */
		base = 10;		/* Conversion base */
	int	t = 0,			/* Return value */
		mult = 1;		/* Sign of result */
	char	*fcc = ip;		/* First char position */

	if (*ip == '-') {		/* Negative number? */
		ip++;
		mult = -1;
	}
	if (*ip == '0') { 	/* Leading '0'? */
		ip++;
		if (*ip == 'x' || *ip == 'X') {	/* Hex */
			base = 16;
			func = hexdigit;
			ip++;
		}
		else {
			base = 8;		/* Octal */
			func = octdigit;
		}
	}
	while (*ip && (*func)(*ip)) {
		t *= base;
		if (decdigit(*ip))
			t += (*ip - '0');
		else
			t += (*ip >= 'a' ? *ip - 0x57 : *ip - 0x37);
		ip++;
	}
	if (ip == fcc)		/* Nothing processed */
		return(0);
	if (ipp)		/* Stash new pointer location */
		*ipp = ip;
	*iv = (t * mult);
	return(1);
}

/*
 * decode_string - copy string, converting backslash escapes
 *	Can handle most C backslash escape sequences
 */
private void
decode_string(dst, src, len)
	char	*dst,		/* Destination */
		*src;		/* Source */
	int	len;		/* How big the destination is */
{
	int	t;		/* Temp */
	char	*dstx = dst;	/* Pointer to start of destination */
	char	quote = 0;	/* Quote character */

	if (*src == '"' || *src == '\'')
		quote = *src++;

#define	putxchar(P) *dst++ = (P)
	for (; *src && (dst - dstx) < len; ) {
		if (*src == '\\') {
			src++;
			switch(*src) {
			case 'a':	putxchar('\007'); src++; break;
			case 'b':	putxchar('\b'); src++; break;
			case 'f':	putxchar('\f'); src++; break;
			case 'n':	putxchar('\n'); src++; break;
			case 'r':	putxchar('\r'); src++; break;
			case 't':	putxchar('\t'); src++; break;
			case '\\':	putxchar('\\'); src++; break;
			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7':
			case 'x':
				if (xatoi(src, &src, &t))
					putxchar(t & 0xff);
				break;
			default:
				if (quote && *src == quote)
					*dst++ = *src++;
				break;
			}
			continue;
		}
		if (*src == '^') {	/* ^C = control-c */
			src++;
			if (isupper(*src))
				putxchar(*src - '@');
			else if (islower(*src))
				putxchar(*src - '`');
			else switch (*src) {
			     case '[':	putxchar('\033'); break;
			     case '\\':	putxchar('\034'); break;
			     case ']':	putxchar('\035'); break;
			     case '^':	putxchar('\036'); break;
			     case '-':	putxchar('\037'); break;
			}
			src++;
			continue;
		}
		if (quote && *src == quote)
			break;
		*dst++ = *src++;
	}
#undef	putxchar
	*dst = 0;
}

I 4
/*
E 13
D 17
 * checkpassword_init - Setup the default configuration
E 17
I 17
 * checkpassword_init 
 *	Reset configuration to builtin defaults
 *
 * Usage
 *	checkpassword_init();
E 17
 */
E 4
public void
checkpassword_init()
{
D 17
	char	**cfi = _default_config;
I 9
	char	cfbuf[512];
E 17
I 17
D 24
	char	**cfi = _default_config;	/* Internal config "file" */
	char	cfbuf[BUFSIZ];			/* Temporary */
E 24
I 24
	char	**cfi;	/* Internal config "file" */
E 24
E 17
E 9

I 7
	if (Config.initialized)
		return;
I 17
	/*
	 * Clear the config block
	 */
E 17
I 16
D 22
#ifdef	HAS_MEMSET
	memset((void *)&Config, 0, sizeof Config);
#else
E 16
E 7
I 4
D 10
	BZERO((char *)&Config, sizeof Config);
E 4
D 8
	bcopy(_illchar, Config.badchars, sizeof(_illchar));
E 8
I 8
	BCOPY(_illchar, Config.badchars, sizeof(_illchar));
E 10
I 10
	bzero((char *)&Config, sizeof Config);
I 16
#endif
E 22
I 22
	zeromem(&Config, sizeof Config);

E 22
I 17
	/*
	 * Copy the default bad character list into the config block
	 */
E 17
#ifdef	HAS_MEMCPY
	memcpy((void *)Config.badchars, (void *)_illchar, sizeof(_illchar));
#else
E 16
	bcopy(_illchar, Config.badchars, sizeof(_illchar));
I 16
#endif
I 17
	/*
	 * Reinstantiate the built-in settings
	 */
E 17
E 16
E 10
E 8
D 9
	while (*cfi)
D 6
		checkpassword_configure(*cfi++, 0);
E 6
I 6
		checkpassword_configure(*cfi++, (char *)0);
E 9
I 9
D 24
	while (*cfi) {
		(void) strcpy(cfbuf, *cfi++);
		checkpassword_configure(cfbuf, (char *)0);
E 24
I 24
	for (cfi = _default_config; *cfi; cfi++) {
		char	cfbuf[BUFSIZ];			/* Temporary */
		char	*cferror;

		(void) strcpy(cfbuf, *cfi);
D 27
		if (cferror = checkpassword_configure(cfbuf)) {
E 27
I 27
		if (cferror = checkpassword_configure(cfbuf, 1)) {
E 27
			logdie("checkpassword_init setup error h%s] on \"%s\"",
				cferror, *cfi);
		}
E 24
	}
E 9
E 6
	Config.initialized = 1;
I 30
	(void) get_pwsvc();
E 30
I 12
D 19
#ifdef	DEBUG
	Config.debug = 1;
	printf("checkpassword_init: done\n");
#endif
E 19
I 19
	debug(DB_CONFIG, "checkpassword_init: done\n");
E 19
E 12
}

/*
I 28
 * checkpassword_verify 
 *	Verify that checkpassword is properly configured
D 29
 *	Aborts if things are not right
E 29
I 29
 *	Returns nastygram if config error
E 29
 * Usage
 *	checkpassword_verify();
 */
D 29
public void
E 29
I 29
public char *
E 29
checkpassword_verify()
{
	if (Config.dictionaries[0] == 0)
D 29
		logdie("No dictionaries found");
E 29
I 29
		return("No dictionaries found");
	return(0);
E 29
}

/*
E 28
D 4
 * checkpassword_configure - 
E 4
I 4
D 17
 * checkpassword_configure - Process a configuration directive
E 17
I 17
 * checkpassword_configure
 *	Process a configuration directive
 *
 * Usage
D 27
 *	ok = checkpassword_configure(char *string, char *error);
E 27
I 27
 *	ok = checkpassword_configure(char *string, int flag-error);
E 27
 * Returns
D 24
 *	1 if directive was recognized and processed correctly
 *	0 if not
E 24
I 24
 *	(char *)0 if directive was recognized and processed correctly
 *	error message otherwise
E 24
E 17
E 4
 */
D 24
public int
D 5
checkpassword_configure(cfline, complain)
E 5
I 5
checkpassword_configure(cfline, errorbuf)
E 24
I 24
public char *
D 27
checkpassword_configure(cfline)
E 27
I 27
checkpassword_configure(cfline, flagerror)
E 27
E 24
E 5
D 16
	char	*cfline;		/* Configuration directive */
E 16
I 16
D 17
	const char	*cfline;		/* Configuration directive */
E 16
D 5
	int	complain;		/* Complain about error? */
E 5
I 5
	char	*errorbuf;		/* Complain about error? */
E 17
I 17
D 18
	const char	*cfline;	/* Directive to process */
E 18
I 18
	char	*cfline;	/* Directive to process */
I 27
	int	flagerror;	/* Flag unknown directives as error? */
E 27
E 18
D 23
	char		*errorbuf;	/* Error message stash */
E 23
I 23
D 24
	char	*errorbuf;	/* Error message stash */
E 24
E 23
E 17
E 5
{
I 17
D 19
	/* Convient error bailout macro.  Note that <data> is not free()d */
E 19
I 19
D 30
	extern int	DebugLevel;	/* From checkpasswd main
					 * or npasswd main */

E 30
D 24
	/* Error bailout macro.  Note that <data> is not free()d */
E 19
E 17
D 5
	int	ok = 0;			/* Temp */
E 5
D 13
	char	*data[64];		/* Line split pointer array */
E 13
I 5
#define	cf_error(_S_) { if (errorbuf) (void)strcpy(errorbuf, _S_); return(0); }
E 24
I 19
	/* Normal return macro.  Makes sure that <data> is freed */
E 19
I 13
D 17
	char	**data;			/* Line split pointer array */
E 17
I 17
D 24
#define	cf_ok	{ if (data) free((char *)data); return(1); }
E 24
I 24
#define	cf_ok	{ if (data) free((char *)data); return(0); }
E 24
I 19

E 19
	char	**data = 0,		/* Line split pointer array */
		*dot,			/* ACME Temp Storage INC */
		*item;			/* ACME Temp Storage INC */
E 17
E 13
E 5

D 17
	if (*cfline == '\n' || *cfline == '#')		/* Empty line */
		return(1);
D 13
	(void) split(cfline, data);
E 13
I 13
	data = split(cfline, '\0', (char *)0, '\0');
E 13
I 11
	if (errorbuf) *errorbuf = 0;
E 17
I 17
D 24
	if (errorbuf)			/* Empty error buffer */
		*errorbuf = 0;

E 24
	if (*cfline == '\n' || *cfline == '#')	/* Empty line or comment */
		cf_ok;

D 20
	if ((data = split(cfline, 0, 0, '#')) == 0)
E 20
I 20
	if ((data = split(cfline, 0, 0, 0)) == 0)
E 20
D 24
		cf_error("Directive parse failure");
E 24
I 24
		return("Line did not parse");
E 24

	if (dot = strrchr(data[0], '.'))	/* Ignore up to last '.' */
		item = ++dot;
	else
		item = data[0];
E 17
I 12
D 19
	if (Config.debug)
D 17
		printf("checkpassword_configure: %s\n", data[0]);
E 12
E 11
D 14
	if (streq(data[0], "singlecase")) {
E 14
I 14
	if (streq(data[0], "MonocaseOK")) {
E 17
I 17
		printf("checkpassword_configure: [%s]\n", item);
E 19
I 19
	debug(DB_CONFIG, "checkpassword_configure: [%s]\n", item);
I 24
#define	check_arg(_V_) { if (data[_V_] == 0) return("Missing value"); }
E 24
E 19
	/*
	 * Token matching
	 */
D 19
	if (strcmp(item, "MonocaseOK") == 0) {
E 19
I 19
D 24
	if (strcasecmp(item, "monocaseok") == 0) {
E 19
E 17
E 14
I 5
		if (!data[1]) cf_error("Missing value");
E 24
I 24
	if (strcasecmp(item, "singlecase") == 0) {
		check_arg(1);
E 24
E 5
		Config.single_case = decode_boolean(data[1]);
I 13
D 17
		free((char *)data);
E 13
D 5
		ok++;
E 5
I 5
		return(1);
E 17
I 17
		cf_ok;
E 17
E 5
	}
I 24
	if (strcasecmp(item, "lengthwarn") == 0) {
		check_arg(1);
		Config.length_warn = decode_boolean(data[1]);
		cf_ok;
	}
E 24
I 21
	if (strcasecmp(item, "alphaonly") == 0) {
D 24
		if (!data[1]) cf_error("Missing value");
E 24
I 24
		check_arg(1);
E 24
		Config.alpha_only = decode_boolean(data[1]);
		cf_ok;
	}
E 21
D 14
	if (streq(data[0], "minlength")) {
E 14
I 14
D 17
	if (streq(data[0], "MinPassword")) {
E 17
I 17
D 19
	if (strcmp(item, "MinPassword") == 0) {
E 19
I 19
	if (strcasecmp(item, "minpassword") == 0) {
E 19
E 17
E 14
I 5
D 24
		if (!data[1]) cf_error("Missing value");
E 24
I 24
		check_arg(1);
E 24
E 5
		Config.min_length = decode_int(data[1]);
I 13
D 17
		free((char *)data);
E 13
D 5
		ok++;
E 5
I 5
		return(1);
E 17
I 17
		cf_ok;
E 17
E 5
	}
D 14
	if (streq(data[0], "maxlength")) {
E 14
I 14
D 17
	if (streq(data[0], "MaxPassword")) {
E 17
I 17
D 19
	if (strcmp(item, "MaxPassword") == 0) {
E 19
I 19
	if (strcasecmp(item, "maxpassword") == 0) {
E 19
E 17
E 14
I 5
D 24
		if (!data[1]) cf_error("Missing value");
E 24
I 24
		check_arg(1);
E 24
E 5
		Config.max_length = decode_int(data[1]);
I 13
D 17
		free((char *)data);
E 13
D 5
		ok++;
E 5
I 5
		return(1);
E 17
I 17
		cf_ok;
E 17
E 5
	}
D 14
	if (streq(data[0], "runlength")) {
E 14
I 14
D 17
	if (streq(data[0], "MaxRepeat")) {
E 17
I 17
D 19
	if (strcmp(item, "MaxRepeat") == 0) {
E 19
I 19
	if (strcasecmp(item, "maxrepeat") == 0) {
E 19
E 17
E 14
I 5
D 24
		if (!data[1]) cf_error("Missing value");
E 24
I 24
		check_arg(1);
E 24
E 5
		Config.run_length = decode_int(data[1]);
I 13
D 17
		free((char *)data);
E 13
D 5
		ok++;
E 5
I 5
		return(1);
E 17
I 17
		cf_ok;
E 17
E 5
	}
I 12
D 14
	if (streq(data[0], "debug")) {
E 14
I 14
D 17
	if (streq(data[0], "DebugLevel")) {
E 17
I 17
D 19
	if (strcmp(item, "DebugLevel") == 0) {
E 19
I 19
	if (strcasecmp(item, "debug") == 0) {
E 19
E 17
E 14
D 24
		if (!data[1]) cf_error("Missing value");
E 24
I 24
		check_arg(1);
E 24
D 19
		Config.debug = decode_int(data[1]);
E 19
I 19
D 30
		DebugLevel = decode_int(data[1]);
E 30
I 30
		set_debug(data[1], 0);
E 30
E 19
I 13
D 17
		free((char *)data);
E 13
		return(1);
E 17
I 17
		cf_ok;
E 17
	}
E 12
D 14
	if (streq(data[0], "printonly")) {
E 14
I 14
D 17
	if (streq(data[0], "PrintableOnly")) {
E 17
I 17
D 19
	if (strcmp(item, "PrintableOnly") == 0) {
E 19
I 19
	if (strcasecmp(item, "printableonly") == 0) {
E 19
E 17
E 14
I 5
D 24
		if (!data[1]) cf_error("Missing value");
E 24
I 24
		check_arg(1);
E 24
E 5
		Config.print_only = decode_boolean(data[1]);
I 13
D 17
		free((char *)data);
E 13
D 5
		ok++;
E 5
I 5
		return(1);
E 17
I 17
		cf_ok;
E 17
E 5
	}
I 32
	if (strcasecmp(item, "whitespace") == 0) {
		check_arg(1);
		Config.whitespace = decode_boolean(data[1]);
		cf_ok;
	}
E 32
I 11
D 14
	if (streq(data[0], "dictionaries")) {
E 14
I 14
D 17
	if (streq(data[0], "Dictionaries")) {
E 17
I 17
D 19
	if (strcmp(item, "Dictionaries") == 0) {
E 19
I 19
	if (strcasecmp(item, "dictionaries") == 0) {
E 19
E 17
E 14
D 24
		char	**pp = &data[1];
E 24
I 24
		char	**pp;
		static char	emsg[MAXPATHLEN + 32];
E 24

D 24
		if (!data[1]) cf_error("Missing value");
D 12
		while (*pp)
			add_all_dicts(*pp++);
E 12
I 12
		while (*pp) {
			int	rc = add_all_dicts(*pp++);
			if (rc < 0)
D 13
				cf_error("Dictionaries find error");
E 13
I 13
D 15
				CF_ERROR("Dictionaries find error");
E 15
I 15
				cf_error("Dictionaries find error");
E 24
I 24
		check_arg(1);
		for (pp = &data[1]; *pp; pp++) {
			if (add_all_dicts(*pp) < 0) {
				(void) sprintf(emsg,
					"Error adding dictionaries in \"%s\"",
					*pp);
				return(emsg);
			}
E 24
E 15
E 13
		}
I 13
D 17
		free((char *)data);
E 13
E 12
		return(1);
E 17
I 17
		cf_ok;
E 17
	}
E 11
D 13
	if (streq(data[0], "mandatory")) {
		char	**pp = &data[1];

I 5
		if (!data[1]) cf_error("Missing value");
E 5
		while (*pp)
D 11
			add_dict(*pp++, DICT_MANDATORY);
E 11
I 11
			add_one_dict(*pp++, DICT_MANDATORY);
E 11
D 5
		ok++;
E 5
I 5
		return(1);
E 5
	}
	if (streq(data[0], "optional")) {
		char	**pp = &data[1];

I 5
		if (!data[1]) cf_error("Missing value");
E 5
		while (*pp)
D 11
			add_dict(*pp++, DICT_OPTIONAL);
E 11
I 11
			add_one_dict(*pp++, DICT_OPTIONAL);
E 11
D 5
		ok++;
E 5
I 5
		return(1);
E 5
	}
E 13
I 6
D 14
	if (streq(data[0], "history")) {
E 14
I 14
D 17
	if (streq(data[0], "HistoryDatabase")) {
E 14
		extern char	PasswordHistoryFile[];
E 17
I 17
D 19
	if (strcmp(item, "HistoryDatabase") == 0) {
		extern char	PasswordHistoryFile[];	/* In pwck_dict.c */
E 19
I 19
D 20
	if (instringcase(item, "history") == 0) {
E 20
I 20
	if (instringcase(item, "history")) {
E 20
D 24
		char	tmp[128];
E 24
I 24
		char	*tmp;
E 24
E 19
E 17

D 24
		if (!data[1]) cf_error("Missing value");
D 19
		(void) strncpy(PasswordHistoryFile, data[1], MAXPATHLEN);
E 19
I 19
		if (pwck_history_configure(item, &data[1], tmp) == 0)
			cf_error(tmp);
E 24
I 24
		check_arg(1);
D 25
		if (tmp = pwck_history_configure(data))
E 25
I 25
		if (tmp = pwck_history_configure(&data[1]))
E 25
			return(tmp);
E 24
E 19
I 13
D 17
		free((char *)data);
E 13
		return(1);
E 17
I 17
		cf_ok;
E 17
	}
E 6
D 14
	if (streq(data[0], "checkorder")) {
E 14
I 14
D 17
	if (streq(data[0], "HistoryParams")) {
		free((char *)data);	/* Recognized but ignored */
		return(1);
E 17
I 17
D 19
	if (strcmp(item, "HistoryParams") == 0) {
		cf_ok;
E 17
	}
D 17
	if (streq(data[0], "PasswordChecks")) {
E 17
I 17
	if (strcmp(item, "PasswordChecks") == 0) {
E 19
I 19
	if (strcasecmp(item, "passwordchecks") == 0) {
E 19
E 17
E 14
		char	**pp = &data[1];
I 23
		char	*tx;
E 23

I 5
D 24
		if (!data[1]) cf_error("Missing value");
E 24
I 24
		check_arg(1);
E 24
I 22
		zeromem(&Config.checkprocs, sizeof Config.checkprocs);
E 22
E 5
		while (*pp)
			add_proc(*pp++);
I 23
		if (tx = check_procs())
D 24
			cf_error(tx);
E 24
I 24
			return(tx);
E 24
E 23
I 13
D 17
		free((char *)data);
E 13
D 5
		ok++;
E 5
I 5
		return(1);
E 17
I 17
		cf_ok;
E 17
E 5
	}
D 14
	if (streq(data[0], "badchars")) {
E 14
I 14
D 17
	if (streq(data[0], "DisallowedChars")) {
E 17
I 17
D 19
	if (strcmp(item, "DisallowedChars") == 0) {
E 19
I 19
	if (strcasecmp(item, "disallowedchars") == 0) {
E 19
E 17
E 14
		char	xcc[BUFSIZ];
		char	append = 0;
		char	*pp = data[1];

I 5
D 24
		if (!data[1]) cf_error("Missing value");
E 24
I 24
		check_arg(1);
E 24
E 5
		if (*pp == '+')		/* Add to existing list */
			append = *pp++;
D 13
		decode_string(xcc, pp, BUFSIZ);
E 13
I 13
		decode_string(xcc, pp, sizeof(xcc));
E 13
		if (xcc[0] == 0)
			return(0);
		if (append)
D 22
			(void) strcat(Config.badchars, xcc);
E 22
I 22
			(void) strncat(Config.badchars, xcc,
			        sizeof(Config.badchars) - strlen(Config.badchars));
E 22
		else
			(void) strncpy(Config.badchars, xcc,
				sizeof(Config.badchars));
I 13
D 17
		free((char *)data);
E 13
D 5
		ok++;
E 5
I 5
		return(1);
E 17
I 17
		cf_ok;
E 17
E 5
	}
I 22
D 24
	if (strcasecmp(item, "mincharclasses") == 0) {
		if (!data[1]) cf_error("Missing value");
E 24
I 24
	if (strcasecmp(item, "charclasses") == 0) {
		check_arg(1);
E 24
		Config.char_classes = decode_int(data[1]);
		cf_ok;
	}

E 22
D 5
	if (ok == 0 && complain)
		printf("Unrecognized keyword '%s'.\n", data[0]);
	return(ok);
E 5
I 5
D 17
	if (errorbuf)
		(void) sprintf(errorbuf, "Unrecognized keyword '%s'.\n",
			 data[0]);
E 17
I 13
	free((char *)data);
E 13
D 17
	return(0);
E 17
I 17
D 24
	cf_error("Unrecognized keyword");
E 17
#undef	cf_error
E 24
I 24
D 27
	return("Unrecognized keyword");
E 27
I 27
	if (flagerror)
		return("Unrecognized keyword");
	else
		return(0);
E 27
E 24
I 17
#undef	cf_ok
I 24
#undef	check_arg
E 24
E 17
E 5
}

/*
D 11
 *	add_dict - Add a dictionary to the search list
E 11
I 11
D 17
 *	add_one_dict - Add a dictionary to the search list
E 17
I 17
 * add_one_dict
 *	Add one Crack dictionary to the search list
 *
 * Usage
D 18
 *	add_one_dict(const char *path-to-dictionary);
E 18
I 18
 *	add_one_dict(char *path-to-dictionary);
I 23
 * Returns
 *	 1 - success
 *	 0 - dictionary already in list
 *	-1 - error (warning message issued sometimes)
E 23
E 18
E 17
E 11
D 13
 *
 *	Arguments:
 *		The rest of the line from the configuration file
 *		which contains the path to the dictionary and optionally
 *		a descriptive phrase
E 13
 */
D 23
private void
E 23
I 23
private int
E 23
D 11
add_dict(dict, flags)
E 11
I 11
D 13
add_one_dict(dict, flags)
E 11
char	*dict;		/* Path to dictionary */
int	flags;		/* Flags for this entry */
E 13
I 13
add_one_dict(dict)
D 16
	char	*dict;		/* Path to dictionary */
E 16
I 16
D 18
	const char	*dict;		/* Path to dictionary */
E 18
I 18
	char	*dict;		/* Path to dictionary */
E 18
E 16
E 13
{
D 23
	dictionary	*dx,	/* Tail of directory list */
			*dn;	/* New entry */
E 23
I 23
	int	dp;	/* Counter */
	PWDICT	*pw;	/* Dictionary pointer */
E 23
D 13
	char	*tx,		/* Scratch */
		*p;		/* Scratch */
E 13

D 12
#ifdef	DEBUG
	printf("Dictionary '%s' flags %d\n", dict, flags);
#endif
E 12
I 12
D 19
	if (Config.debug)
D 13
		printf("add_one_dict: Dictionary \"%s\" flags %d\n",
			dict, flags);
E 13
I 13
		printf("add_one_dict: \"%s\"\n", dict);
E 19
I 19
	debug(DB_CONFIG, "add_one_dict: \"%s\"\n", dict);
E 19
E 13
E 12
D 23
	dn = (dictionary *)calloc(sizeof(dictionary), 1);
	if (Config.dictionaries == 0)
		Config.dictionaries = dn;

D 22
	for (dx = Config.dictionaries; dx->next ; dx = dx->next);
E 22
I 22
	for (dx = Config.dictionaries; dx->next ; dx = dx->next) {
		if (strcmp(dx->path, dict) == 0) {
			free(dn);	/* Dictionary already in list */
			return;
		}
E 23
I 23
	/*
	 * Append to list unless already present
	 */
	for (dp = 0; dp < NDICTIONARIES; dp++) {
D 24
		if (Config.dict_path[dp] == 0)
E 24
I 24
		if (Config.dictionaries[dp] == 0)
E 24
			break;
D 24
		if (strcmp(Config.dict_path[dp], dict) == 0)
E 24
I 24
		if (strcmp(Config.dictionaries[dp], dict) == 0)
E 24
			return(0);
E 23
	}
E 22
D 23

D 6
	tx = malloc(strlen(dict) + 1);
E 6
I 6
D 13
	tx = (char *)malloc(strlen(dict) + 1);
E 6
	(void) strcpy(tx, dict);
	p = tx;
	while (*p && *p > ' ') p++;
	if (*p)
		*p++ = 0;
	dn->path = tx;
	dn->flags = flags;
E 13
I 13
	dn->path = strdup(dict);
E 13
	dx->next = dn;
	dn->next = 0;
E 23
I 23
	if (dp == NDICTIONARIES) {
D 24
		warn("Too many dictionaries (maximum is %d)\n", NDICTIONARIES);
		return(-1);
E 24
I 24
		debug(DB_CONFIG,
			"add_one_dict: overflow (MAX %d)\n", NDICTIONARIES);
		return(-2);
E 24
	}
	/*
D 24
	 * Open the dictionary hash files
E 24
I 24
	 * Verify that the dictionary hash files can be opened
E 24
	 */
	if ((pw = PWOpen(dict, "r")) == 0) {
D 24
		warn("add_one_dict: PWOpen of \"%s\" failed %s",
			dict, PWioError);
E 24
I 24
		debug(DB_CONFIG, "add_one_dict: (%s)\n", PWioError);
E 24
		return(-1);
	}
I 24
	(void) PWClose(pw);
E 24
	/*
	 * Stash in the dictionary arrays
	 */
D 24
	Config.dict_path[dp] = strdup(dict);
	Config.dict_ptrs[dp] = pw;
	dp++;
	Config.dict_path[dp] = (char *)0;
	Config.dict_ptrs[dp] = (PWDICT *)0;
E 24
I 24
	Config.dictionaries[dp++] = strdup(dict);
	Config.dictionaries[dp] = (char *)0;
E 24
	return(1);
E 23
}

I 11
/*
D 17
 *	add_all_dicts - Find the Crack dictionaries in a directory
E 17
I 17
 * add_all_dicts
 *	Add all Crack dictionaries in a directory
E 17
 *
D 17
 *	Arguments:
 *		The path to a directory to scan for Crack dictionaries
E 17
I 17
 * Usage
D 18
 *	howmany = add_all_dicts(const char *directory);
E 18
I 18
 *	howmany = add_all_dicts(char *directory);
E 18
 * Returns
 *	How many dictionaries were found or -1 on error
 * Error exits
 *	Failure to open directory for searching
E 17
 */
I 24
private char	*dict_suffixes[] = { ".pwi", ".pwd", ".hwm", 0 };

E 24
private int
add_all_dicts(where)
D 16
char	*where;			/* What directory to look in */
E 16
I 16
D 18
	const char	*where;			/* What directory to look in */
E 18
I 18
	char	*where;			/* What directory to look in */
E 18
E 16
{
D 17
	DIR		*dd;
	Direntry_t	*dp;
	int		found = 0;
E 17
I 17
	DIR		*dd;			/* Directory scanner */
	Direntry_t	*dp;			/* Directory entry */
	int		found = 0;		/* Counter */
E 17

I 20
D 23
	if (*where = '@')
		where = DICTIONARIES;
E 23
I 23
	if (*where == '@')
		where = PASSWD_DICTIONARIES;
E 23
E 20
I 17
D 19
	if (Config.debug)
		printf("add_all_dicts: \"%s\"\n", where);
E 19
I 19
	debug(DB_CONFIG, "add_all_dicts: \"%s\"\n", where);
E 19
E 17
#ifdef	HAS_READDIR
D 12
	if ((dd = opendir(where)) == NULL)
E 12
I 12
	if ((dd = opendir(where)) == NULL) {
D 26
#ifdef	DEBUG
E 26
I 26
#if	(CDEBUG >= CDEBUG_SYSTEM)
E 26
		perror(where);
E 12
		return(-1);
I 12
D 17
#else
E 17
I 17
#else	/* DEBUG */
E 17
D 13
		die();		/* XXX */
E 13
I 13
		die("Cannot scan \"%s\" for dictionaries\n", where);
E 13
D 17
#endif
E 17
I 17
#endif	/* DEBUG */
E 17
	}
E 12
	while (dp = readdir(dd)) {
D 24
		struct stat	stb;
E 24
		char 	fullname[MAXPATHLEN];
D 24
		char	*p;
E 24
I 24
		int	ok;
		char	*p,
			**ext;
E 24

D 24
		(void) sprintf(fullname, "%s/%s", where, dp->d_name);
		if (stat(fullname, &stb) < 0)
			continue;
		if (!(stb.st_mode & S_IFREG))
			continue;
D 13
		p = rindex(dp->d_name, '.');
		if (p == 0)
E 13
I 13
		if ((p = strrchr(dp->d_name, '.')) == 0)
E 13
			continue;
E 24
		/*
		 * This string must match one of the suffixes used
		 * for the Crack hash files.  See "cracklib/packlib.c".
		 */
I 24
		if ((p = strrchr(dp->d_name, '.')) == 0)
			continue;
E 24
D 26
		if (strcmp(p, ".pwi"))
E 26
I 26
		if (strcmp(p, dict_suffixes[0]))
E 26
			continue;
		*p = 0;
I 24
		/*
		 * Sanity check the mode & ownership of the dictionary files.
		 */
		ok = 0;
		for (ext = dict_suffixes; *ext; ext++) {
			struct stat	stb;

			(void) sprintf(fullname, "%s/%s%s",
				where, dp->d_name, *ext);
			if (stat(fullname, &stb) < 0) {
				warn("Missing dictionary file '%s'\n",
					fullname);
				break;
			}
			if (!(stb.st_mode & S_IFREG)) {
				warn("'%s' is not a file\n", fullname);
				break;
			}
#ifdef	S_IWOTH
			if (stb.st_mode & S_IWOTH) {
#else
			if (stb.st_mode & 02) {
#endif
				warn("Dictionary rejected - file '%s' is world writable",
					fullname);
				break;
			}
			ok++;
		}
		if (!ok)
			continue;
E 24
		(void) sprintf(fullname, "%s/%s", where, dp->d_name);
D 13
		add_one_dict(fullname, DICT_OPTIONAL);
E 13
I 13
D 23
		add_one_dict(fullname);
E 13
		found++;
E 23
I 23
		switch (add_one_dict(fullname)) {
D 24
			case 1:
E 24
I 24
			case 1:			/* Success */
E 24
				found++;
				break;
D 24
			case 0:
				warn("Dictionary \"%s\" already in use",
E 24
I 24
			case 0:			/* Dictionary already in list */
				/*
				 * POLICY - duplicate dictionaries is not
				 * a serious error.  An error message is
				 * displayed and logged for the admin to fix
				 * the configuration file.
				 */
				logerr("Dictionary \"%s\" already in use",
E 24
					fullname);
				break;
D 24
			case -1:
				die("Dictionary add failure");
E 24
I 24
			case -1:		/* List overflow */
				/*
				 * POLICY - overflow of the dictionary list
				 * is a unrecoverable error.  Error status
				 * is passed up to caller, which then will
				 * do what it deems appropriate.
				 */
				logerr("Dictionary list overflow (max %d)",
					NDICTIONARIES);
				closedir(dd);
				return(-1);
E 24
				break;
I 24
			case -2:		/* Error opening dictionary */
				/*
				 * POLICY - the failure to open a dictionary
				 * is a unrecoverable error.  Error status
				 * is passed up to caller, which then will
				 * do what it deems appropriate.
				 */
				logerr("Dictionary open \"%s\" failed, error %s\n",
					fullname, PWioError);
				closedir(dd);
				return(-1);
				break;
E 24
		}
E 23
	}
	closedir(dd);
	return(found);
D 17
#else
E 17
I 17
#else	/* HAS_READDIR */

E 17
I 13
D 16
	die("Cannot scan \"%s\" for dictionaries\n", where); /* XXX */
E 16
I 16
	die("Cannot scan \"%s\" for dictionaries\n", where);
E 16
E 13
D 17
	return(0);
#endif
E 17
I 17
	/*NOTREACHED*/

#endif	/* HAS_READDIR */
E 17
}

E 11
D 17
/*
E 3
 *	The 'pwck_*' routines all use the PWCK_* return
 *	codes, which are then propigated up to the caller of checkpassword().
 *
 *	All pwck_* routines in the table below are called thusly:
 *		pwck_*(password, userid, mesg)
 *			password = plaintext password string to test.
 *			userid = the user id which wants to use <password>.
 *			mesg = buffer to place long explanation into
 *
 *	If more checks are desired, add the functions to the tables below.
 */
E 17
D 3
extern int
	pwck_lexical(),
	pwck_local(),
	pwck_passwd(),
	pwck_dictionary();
E 3
D 23

E 23
I 4
/*
D 17
 * add_proc - Add an entry to the check function list
E 17
I 17
D 24
 * This is the table of password check routines
D 23
 * If more checks are desired, add the functions to the tables below.
E 23
I 23
 * Additional checks can be added to this table
E 23
E 17
 */
E 4
D 3
typedef	int	(*function)();

function checkprocs[] = {
	pwck_lexical,
	pwck_local,
	pwck_passwd,
	pwck_dictionary,
E 3
I 3
struct _procnames {
D 23
	char	*name;
	checkproc	addr;
E 23
I 23
	char		*name;		/* Function name */
	checkproc	addr;		/* Address */
	int		mandatory;	/* Is this check mandatory? */
E 23
};
private struct _procnames procnames[] = {
D 23
	{ "lexical",	pwck_lexical },
	{ "local",	pwck_local  },
	{ "passwd",	pwck_passwd },
	{ "crack",	pwck_crack },
I 6
	{ "history",	pwck_history },
E 23
I 23
	{ "lexical",	pwck_lexical,	1 },
	{ "local",	pwck_local,	0 },
	{ "passwd",	pwck_passwd,	1 },
	{ "dictionary",	pwck_crack,	1 },
	{ "history",	pwck_history,	0 },
E 23
E 6
E 3
	0
};

I 17
/*
E 24
 * add_proc
 *	Add entry to the password check function list
 * Usage
D 18
 *	add_proc(const char *fuction-name);
E 18
I 18
D 23
 *	add_proc(char *fuction-name);
E 23
I 23
 *	error = add_proc(char *fuction-name);
 * Returns
 *	Error mesage string upon failure; (char *)0 on success
E 23
E 18
 */
E 17
I 3
D 23
private void
E 23
I 23
private char *
E 23
add_proc(procname)
D 16
char	*procname;
E 16
I 16
D 18
	const char	*procname;
E 18
I 18
	char	*procname;
E 18
E 16
{
D 17
	struct _procnames *p = procnames;
	checkproc	*pp;
E 17
I 17
D 23
	struct _procnames *p = procnames;	/* ACME Scratch Storage */
	checkproc	*pp;			/* ACME Scratch Storage */
E 23
I 23
	struct _procnames *p = procnames;
	checkproc	*pp, px;
E 23
E 17

D 23
	for (pp = Config.checkprocs; *pp; pp++);
I 22

E 22
	for (p = procnames; p->name; p++) {
E 23
I 23
	/*
	 * Lookup the address for <procname>
	 */
	for (p = procnames, px = 0; p->name; p++) {
E 23
D 19
		if (strcmp(procname, p->name))
E 19
I 19
D 22
		if (strcasecmp(procname, p->name))
E 19
			continue;
D 12
#ifdef	DEBUG
		printf("Add checkproc %s = %x\n", procname, p->addr);
#endif
E 12
I 12
D 19
		if (Config.debug)
			printf("add_proc: add '%s' @ 0x%x\n",
				procname, p->addr);
E 19
I 19
		debug(DB_CONFIG, "add_proc: add '%s' @ 0x%x\n",
			procname, p->addr);
E 19
E 12
		*pp++ = p->addr;
		*pp = 0;
E 22
I 22
		if (strcasecmp(procname, p->name) == 0) {
			debug(DB_CONFIG, "add_proc: add '%s' @ 0x%x\n",
				procname, p->addr);
D 23
			*pp++ = p->addr;
			*pp = 0;
E 23
I 23
			px = p->addr;
E 23
			break;
		}
E 22
	}
I 23
	/*
	 * Didn't find <procname> in the table?
	 */
	if (px == 0) {
		static char emsg[STRINGLEN];

		(void) sprintf(emsg, "Unknown check function '%s'", procname);
		return(emsg);
	}
	/*
	 * Append proc address to the list, prevent duplicates
	 */
	for (pp = Config.checkprocs; *pp; pp++) {
		if (*pp == px) {
			warn("add_proc: Check function '%s' already in list\n",
				procname);
			return((char *)0);
		}
	}
	*pp++ = px;
	pp = 0;
	return((char *)0);
E 23
}

E 3
/*
D 3
 *	checkpassword - Password candidate sanity checker.
E 3
I 3
D 13
 * split - Tokenize line
 */
private int
split(cbuf, vbuf)
char	*cbuf;
char	**vbuf;
{
	register char	*ts,	/* Start of token */
			*te;	/* End of token */
	int	nitems = 0;

	if (cbuf == 0)
		return(0);
	ts = te = cbuf;
	while (*ts) {
		while (*te && *te <= ' ')	/* Find start of next token */
			te++;
		if (!*te)
			break;
		ts = te;
		while (*te && *te > ' ') *te++; /* Find end of this token */
		if (*te)
			*te++ = '\0';
		*vbuf++ = ts;
		nitems++;
	}
	*vbuf = 0;
	return(nitems);
}

/*
 *	_instring - Compare all sub-strings
E 3
 *
D 3
 *	Arguments;
 *		password = plain text password string to check.
 *		userid = the uid whom the password is for, -1 to disable.
 *
E 3
 *	Returns:
D 3
 *		PWCK_* values (see checkpasswd.h)
E 3
I 3
 *		0 if match not found
 *		rc if match found
E 3
 */
D 3
checkpassword(password, userid, mesg)
char	*password;		/* Plaintext of password to check */
int	userid;			/* The user this is for */
char	*mesg;			/* Where to stash explanation message */
E 3
I 3
public int
_instring(s1, s2, rc)
char	*s1,		/* String to look for */
	*s2;		/* String to look for <s1> in */
int	rc;		/* What to return on match */
E 3
{
D 3
	int		rcode;		/* General purpose scratch */
	function	*checkfunc;	/* Check function pointer */
E 3
I 3
	int	l;		/* Temp */
E 3

D 3
	if (password == 0 || *password == 0)
		return(PWCK_NULL);		/* Null password */
E 3
I 3
	for (l = strlen(s1); *s2; s2++)
D 10
		if (_cistrncmp(s1, s2, l) == 0)
E 10
I 10
		if (strncasecmp(s1, s2, l) == 0)
E 10
			return (rc);
	return(0);
}
E 3

D 3
	mesg[0] = 0;
	for (checkfunc = checkprocs; *checkfunc; checkfunc++) {
		if ((rcode = (*checkfunc)(password, userid, mesg)) != PWCK_OK)
			return(rcode);
E 3
I 3
/*
E 13
D 17
 *	_flipstring - reverse a string in place
E 17
I 17
D 23
 * _flipstring 
 *	 Reverse a string
 * Usage
 *	filpped = _flipstring(char *string, char *copy);
E 23
I 23
 * check_procs
 *	Verify integrity of password check function list
 * Returns
 *	Error mesage string upon failure; (char *)0 on success
E 23
E 17
 */
D 23
public char *
D 13
_flipstring(string, makecopy)
char	*string;		/* String to reverse */
int	makecopy;		/* "Make copy" flag */
E 13
I 13
_flipstring(string, copy)
D 16
	char	*string;	/* String to reverse */
E 16
I 16
D 18
	const char	*string;	/* String to reverse */
E 18
I 18
	char	*string;	/* String to reverse */
E 18
E 16
D 17
	char	*copy;		/* "Make copy" flag */
E 17
I 17
D 22
	char		*copy;		/* Where to put it */
E 22
I 22
	char	*copy;		/* Where to put it */
E 23
I 23
private char *
check_procs()
E 23
E 22
E 17
E 13
{
D 17
	char	*p,	/* Scratch */
		*t,	/* Scratch */
		*ss,	/* Scratch */
		*r;	/* Scratch */
E 17
I 17
D 23
	char	*p,	/* ACME Scratch Storage */
		*t,	/* ACME Scratch Storage */
		*ss;	/* ACME Scratch Storage */
E 23
I 23
	struct _procnames *p;
E 23
E 17
D 6
	char	*malloc();
E 6

D 17
	for (p = string; *p; p++);	/* Find end of string */
E 17
I 17
D 23
	for (p = (char *)string; *p; p++);	/* Find end of string */
E 17
	--p;
D 6
	r = t = malloc(strlen(string) + 1);
E 6
I 6
D 13
	r = t = (char *)malloc(strlen(string) + 1);
E 6
	if (r == (char *)0)
		return(0);
E 13
I 13
	t = copy;
E 13
D 17
	for (ss = string; *ss; ss++ )
E 17
I 17
	for (ss = (char *)string; *ss; ss++)
E 17
		*t++ = *p--;
	*t = 0;
D 13
	if (makecopy)
		return(r);
	(void) strcpy(string, r);
	free(r);
	return(string);
E 13
I 13
	return(copy);
E 23
I 23
	for (p = procnames; p->name; p++) {
		checkproc *pp;
		int ok = 0;

		if (p->mandatory == 0) continue;
		for (pp = Config.checkprocs; *pp; pp++) {
			if (*pp == p->addr) {
				ok++;
				break;
			}
		}
		if (ok == 0) {
			static char emsg[STRINGLEN];

			(void) sprintf(emsg, "check %s cannot be disabled",
				 p->name);
			return(emsg);
		}
	}
	return((char *)0);
E 23
E 13
}
D 17

E 17
I 10
D 13
#ifndef	HAS_STRCASECMP
E 10
/*
 *	Case indepedant string comparasion routines swiped from
 *	the source to MIT Hesiod.
 *	Since these routines are publicly available,
 *	I presume to redistribute them is not in violation of copyright.
 */

/*
 * Copyright (c) 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

/*
 * This array is designed for mapping upper and lower case letter
 * together for a case independent comparison.  The mappings are
 * based upon ascii character sequences.
 */
private char charmap[] = {
	'\000', '\001', '\002', '\003', '\004', '\005', '\006', '\007',
	'\010', '\011', '\012', '\013', '\014', '\015', '\016', '\017',
	'\020', '\021', '\022', '\023', '\024', '\025', '\026', '\027',
	'\030', '\031', '\032', '\033', '\034', '\035', '\036', '\037',
	'\040', '\041', '\042', '\043', '\044', '\045', '\046', '\047',
	'\050', '\051', '\052', '\053', '\054', '\055', '\056', '\057',
	'\060', '\061', '\062', '\063', '\064', '\065', '\066', '\067',
	'\070', '\071', '\072', '\073', '\074', '\075', '\076', '\077',
	'\100', '\141', '\142', '\143', '\144', '\145', '\146', '\147',
	'\150', '\151', '\152', '\153', '\154', '\155', '\156', '\157',
	'\160', '\161', '\162', '\163', '\164', '\165', '\166', '\167',
	'\170', '\171', '\172', '\133', '\134', '\135', '\136', '\137',
	'\140', '\141', '\142', '\143', '\144', '\145', '\146', '\147',
	'\150', '\151', '\152', '\153', '\154', '\155', '\156', '\157',
	'\160', '\161', '\162', '\163', '\164', '\165', '\166', '\167',
	'\170', '\171', '\172', '\173', '\174', '\175', '\176', '\177',
	'\200', '\201', '\202', '\203', '\204', '\205', '\206', '\207',
	'\210', '\211', '\212', '\213', '\214', '\215', '\216', '\217',
	'\220', '\221', '\222', '\223', '\224', '\225', '\226', '\227',
	'\230', '\231', '\232', '\233', '\234', '\235', '\236', '\237',
	'\240', '\241', '\242', '\243', '\244', '\245', '\246', '\247',
	'\250', '\251', '\252', '\253', '\254', '\255', '\256', '\257',
	'\260', '\261', '\262', '\263', '\264', '\265', '\266', '\267',
	'\270', '\271', '\272', '\273', '\274', '\275', '\276', '\277',
	'\300', '\341', '\342', '\343', '\344', '\345', '\346', '\347',
	'\350', '\351', '\352', '\353', '\354', '\355', '\356', '\357',
	'\360', '\361', '\362', '\363', '\364', '\365', '\366', '\367',
	'\370', '\371', '\372', '\333', '\334', '\335', '\336', '\337',
	'\340', '\341', '\342', '\343', '\344', '\345', '\346', '\347',
	'\350', '\351', '\352', '\353', '\354', '\355', '\356', '\357',
	'\360', '\361', '\362', '\363', '\364', '\365', '\366', '\367',
	'\370', '\371', '\372', '\373', '\374', '\375', '\376', '\377',
};

/*
D 10
 *	cistrcmp - case independant string compare
E 10
I 10
 *	strcasecmp - case independant string compare
E 10
 */
public int
D 10
_cistrcmp(s1, s2)
E 10
I 10
strcasecmp(s1, s2)
E 10
register char *s1, *s2;
{
	register char *cm = charmap;

	while (cm[*s1] == cm[*s2++])
		if (*s1++=='\0')
			return(0);
	return(cm[*s1] - cm[*--s2]);
}

/*
D 10
 *	cistrncmp - case independant string compare
E 10
I 10
 *	strncasecmp - case independant string compare
E 10
 */
public int
D 10
_cistrncmp(s1, s2, n)
E 10
I 10
strncasecmp(s1, s2, n)
E 10
register char *s1, *s2;
register n;
{
	register char *cm = charmap;

	while (--n >= 0 && cm[*s1] == cm[*s2++])
		if (*s1++ == '\0')
			return(0);
	return(n<0 ? 0 : cm[*s1] - cm[*--s2]);
}
/* end of UCB copyrighted code 	*/
I 10
#endif
E 10

/*
 *	_ctran - produce printable version of any ASCII character
 */
public char *
_ctran (c)
char	c;		/* Character to represent */
{
	static char	cbuf[8];	/* Return value buffer */
	char	*p = cbuf;		/* Pointer to cbuf */
	char	chr = c & 0177;		/* Scratch */

	if (c & 0200) {		/* Meta char - weird but what the hey */
		*p++ = 'M';
		*p++ = '-';
E 3
	}
D 3
	return(PWCK_OK);
E 3
I 3
	if (chr >= ' ' && chr <= '~') {
		*p++ = chr;
		*p++ = 0;
		return (cbuf);
	}
	if (chr == 0177)
		return("DEL");
	*p++ = '^';
	*p++ = chr + '@';
	*p++ = 0;
	return (cbuf);
E 3
}
E 13
D 3
/*	End %M% */
E 3
I 3
/* End %M% */
E 3
E 1
