h24620
s 00054/00013/00227
d D 1.18 98/11/13 16:35:02 clyde 18 17
c 1. Call PMatch() with "initial match" mode
c 2. Add more telephone number patterns
c 3. Provide better error message for character class violations
e
s 00016/00008/00224
d D 1.17 98/08/17 13:19:40 clyde 17 16
c 1. Move bad character test code
c 2. Add 'no whitespace' check
e
s 00004/00004/00228
d D 1.16 98/07/17 10:51:32 clyde 16 15
c Make ctran a public routine
e
s 00036/00030/00196
d D 1.15 98/04/14 13:32:17 clyde 15 14
c 1. Remove old comment & add new ones
c 2. Fix character class check code
c 3. Fully integrate character class checking
e
s 00086/00047/00140
d D 1.14 98/04/07 09:52:42 clyde 14 13
c 1. Add UT copyright notice
c 2. Change return from code to message string
c 3. Use Cracklib/PMatch to check for some patterns
e
s 00028/00031/00159
d D 1.13 98/03/26 10:56:01 clyde 13 12
c 1. Add character class checks (from Donnie.Emeson@Colorado.edu)
c 2. Remove maximum length check (done earlier in the call chain)
c 3. Fix a few problems
e
s 00001/00001/00189
d D 1.12 97/11/25 13:20:38 clyde 12 11
c Fix P_MAX define to deal with compiler stuff
e
s 00008/00004/00182
d D 1.11 97/10/29 14:39:18 clyde 11 10
c Add "alpha only" switch
e
s 00063/00035/00123
d D 1.10 97/09/23 12:22:29 clyde 10 9
c Rewrite lexical check code
e
s 00003/00003/00155
d D 1.9 96/08/29 12:59:31 clyde 9 8
c Remove 'const' declarations (too much compiler trouble)
e
s 00002/00002/00156
d D 1.8 96/08/13 13:05:16 clyde 8 7
c Add const where useful
e
s 00036/00006/00122
d D 1.7 96/08/06 14:13:56 clyde 7 6
c beta 3 cycle 1 checkin
e
s 00001/00001/00127
d D 1.6 95/04/05 16:19:59 clyde 6 5
c Beta 3 development checkin
e
s 00003/00002/00125
d D 1.5 94/03/15 18:52:40 clyde 5 4
c Use new include files
e
s 00033/00023/00094
d D 1.4 94/01/05 15:49:10 clyde 4 3
c Development checkin
e
s 00001/00006/00116
d D 1.3 89/11/07 16:54:22 clyde 3 2
c Don't truncate overlong passwords
e
s 00002/00002/00120
d D 1.2 89/06/05 11:00:06 clyde 2 1
c Rename some internal routines to avoid name collisions
e
s 00122/00000/00000
d D 1.1 89/05/18 10:05:53 clyde 1 0
c date and time created 89/05/18 10:05:53 by clyde
e
u
U
t
T
I 1
/*
D 14
 *	pwck_lexical - Perform lexical analysis of password candidate.
E 14
I 14
 * Copyright 1998, The University of Texas at Austin ("U. T. Austin").
 * All rights reserved.
E 14
 *
D 14
 *	Things which are ok:
 *		Mixed case
 *		Digits
 *		Punctutation
 *		Control characters (except for those in the forbidden table)
E 14
I 14
 * By using this software the USER indicates that he or she has read,
 * understood and will comply with the following:
E 14
 *
D 14
 *	Things which are NOT ok:
 *		Passwords less than 'min_length' characters
 *		Runs of more than <run_length> of the same character
 *			(e.g. 'zzz')
 *		Single-case strings (selectable via the config file)
E 14
I 14
 * U. T. Austin hereby grants USER permission to use, copy, modify, and
 * distribute this software and its documentation for any purpose and
 * without fee, provided that:
E 14
 *
D 14
 *	Things NOT checked for:
 *		Cycles of character groups (e.g. 'aabbcc' or 'ababab')
 *		Sequential characters 'abcdef' or '123456'
E 14
I 14
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
 * pwck_lexical - Perform lexical analysis of password candidate.
E 14
I 4
 *
D 14
 *	Returns:
 *		PWCK_SHORT if password is too short
 *		PWCK_OBVIOUS if password has too many repeated characters
 *		PWCK_ILLCHAR if password has an illegal character
 *		PWCK_OK if passwd is ok
E 14
I 14
D 15
 * Things which are ok:
 *	Mixed case
 *	Digits
 *	Punctutation
 *	Control characters (except for those in the forbidden table)
 *
 * Things which are NOT ok:
 *	Passwords less than 'min_length' characters
 *	Runs of more than <run_length> of the same character (e.g. 'zzz')
 *	Single-case strings (selectable via the config file)
 *
E 15
 * Usage
 *	error = pwck_lexical(char *, struct passwd *);
 *
 * Returns
 *	Error message if password flunks
 *	PWCK_OK if passwd is ok
E 14
E 4
 */

#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu)";
#endif

D 4
#include "checkpasswd.h"
E 4
I 4
D 5
#include "compat.h"
#include "lib.h"
E 5
I 5
D 7
#include "compatibility.h"
E 5
#include "checkpassword.h"
I 5
#include "pwck_lib.h"
E 7
I 7
#include "pwck_defines.h"
E 7
E 5
E 4

D 10
#define	P_U	0x1 	/* Upper case in password */
#define	P_L	0x2 	/* Lower case in password */
#define	P_C	0x4 	/* Control chars in password */
#define	P_D	0x8 	/* Digits in password */
#define	P_P	0x10 	/* Punctutation chars in password */
E 10
I 10
D 13
#define	P_U	1 	/* Upper case in password */
#define	P_L	2 	/* Lower case in password */
#define	P_C	3 	/* Control chars in password */
#define	P_D	4 	/* Digits in password */
#define	P_P	5 	/* Punctutation chars in password */
#define	P_S	6 	/* Whitespace chars in password */
D 12
#define	P_MAX	P_S
E 12
I 12
#define	P_MAX	P_S+1
E 13
I 13
#define	P_START	0 	/* Start of array */
#define	P_U	0 	/* Upper case in password */
#define	P_L	1 	/* Lower case in password */
D 18
#define	P_C	2 	/* Control chars in password */
#define	P_D	3 	/* Digits in password */
#define	P_P	4 	/* Punctutation chars in password */
#define	P_S	5 	/* Whitespace chars in password */
E 18
I 18
#define	P_D	2 	/* Digits in password */
#define	P_P	3 	/* Punctutation chars in password */
#define	P_S	4 	/* Whitespace chars in password */
#define	P_C	5 	/* Control chars in password */
E 18
D 15
#define	P_END	(P_S + 1)
E 15
I 15
#define	P_END	P_S
#define	P_SIZE	(P_END + 1)
E 15
E 13
E 12
E 10

D 10
#define	hasone(P)	(what |= (P))
#define	hasany(P)	((what & (P)) == (P))
E 10
D 13

E 13
I 7
/*
I 18
 * Messages describing each character class
 */
private char *class_msg[] = {
	"upper case letters",		/* P_U */
	"lower case letters",		/* P_L */
	"digits",			/* P_D */
	"punctuation characters",	/* P_P */
	"whitespace",			/* P_S */
	"",				/* P_C */
	0
};

/*
 * PMatch patterns for phone numbers
 */
private char *phone_patterns[] = {
	"dddsdddd", 		/* NNN-NNNN */
	"dddwdddd", 		/* NNN NNNN */
	"dddpdddd", 		/* NNN.NNNN */

	"dddsdddsdddd", 	/* NNN-NNN-NNNN */
	"dddwdddwdddd", 	/* NNN NNN NNNN */
	"dddpdddpdddd", 	/* NNN.NNN.NNNN */

	"dsdddsdddsdddd", 	/* N-NNN-NNN-NNNN */
	"dwdddwdddwdddd", 	/* N NNN NNN NNNN */
	"dpdddpdddpdddd", 	/* N.NNN.NNN.NNNN */
	0
};

/*
E 18
D 16
 *	_ctran - produce printable version of any ASCII character
E 16
I 16
 *	ctran - produce printable version of any ASCII character
E 16
 */
D 16
private char *
_ctran (c)
E 16
I 16
public char *
ctran (c)
E 16
D 9
	const char	c;		/* Character to represent */
E 9
I 9
	char	c;		/* Character to represent */
E 9
{
	static char	cbuf[8];	/* Return value buffer */
	char	*p = cbuf;		/* Pointer to cbuf */
	char	chr;			/* Scratch */

	if (c & 0x80) {		/* Meta char - weird but what the hey */
		*p++ = 'M';
		*p++ = '-';
	}
	chr = (c & 0x7f);
	if (chr == 0x7f)
		return("DEL");
	if (isprint(chr)) {	 /* Printing character */
		*p++ = chr;
		*p++ = 0;
		return (cbuf);
	}
	*p++ = '^';
	*p++ = chr + '@';
	*p++ = 0;
	return (cbuf);
}

E 7
I 5
D 14
public int
E 5
D 4
pwck_lexical(password, userid, mesg)
char	*password;		/* Password to check */
int	userid;			/* NOTUSED */
char	*mesg;		/* Message buffer */
E 4
I 4
pwck_lexical(password, user, mesg)
E 14
I 14
public char *
pwck_lexical(password, user)
E 14
D 8
	char	*password;		/* Password to check */
	struct passwd *user;		/* Passwd info for user */ /* NOTUSED */
E 8
I 8
D 9
	const char	*password;		/* Password to check */
	const struct passwd *user;		/* Passwd info for user */ /* NOTUSED */
E 9
I 9
	char	*password;		/* Password to check */
	struct passwd *user;		/* Passwd info for user */ /* NOTUSED */
E 9
E 8
D 14
	char	*mesg;			/* Message buffer */
E 14
E 4
{
D 10
	int	rc;		/* Duplicate character run count */
E 10
I 10
D 15
	int	chr_run,	/* Duplicate character run count */
E 15
I 15
	int	chr_run,	/* Duplicate character count */
E 15
		pwlen;		/* Length of password */
E 10
D 15
	char	*p = password;	/* Scratch */
E 15
I 15
	char	*p;		/* Scratch */
I 18
	char	**pat;		/* Match pattern */
E 18
E 15
D 14
	char	what = 0,	/* Lexical analysis result flags */
		last = 0;	/* Last character seen (for run checks) */
I 10
D 13
	char	ws_cnt[P_MAX];
E 13
I 13
	char	ws_cnt[P_END];
E 14
I 14
	char	last = 0;	/* Last character seen (for run checks) */
D 15
	char	ws_cnt[P_END];	/* Character classes */
E 15
I 15
	char	ws_cnt[P_SIZE];	/* Character classes */
E 15
	static char	mesg[STRINGLEN];	/* Error message temp */
E 14
E 13
E 10

D 14
	mesg[0] = 0;
E 14
I 14
	zeromem(mesg, sizeof mesg);
E 14
I 10
D 13
#ifdef  HAS_MEMSET
	memset((void *)&ws_cnt, 0, sizeof ws_cnt);
#else
	bzero((char *)&ws_cnt, sizeof ws_cnt);
#endif
E 13
I 13
	zeromem(&ws_cnt, sizeof ws_cnt);
E 13

E 10
D 13
#ifdef	DEBUG
	printf("pwck_lexical: \"%s\"\n", password);
#endif
E 13
I 13
	debug(DB_PWCHECK, "pwck_lexical: \"%s\"\n", password);
I 15
	/*
	 * Minimum length check
	 * Maximum length check is done in checkpassword()
	 */
E 15
E 13
D 10
	rc = strlen(password);
D 4
	if (min_length && rc < min_length)
E 4
I 4
	if (Config.min_length && rc < Config.min_length) {
E 10
I 10
	pwlen = strlen(password);
	if (Config.min_length && pwlen < Config.min_length) {
E 10
		(void) sprintf(mesg,
			"it is too short (minimum length is %d characters)",
			Config.min_length);
E 4
D 14
		return(PWCK_SHORT);
E 14
I 14
		return(mesg);
E 14
I 4
	}
I 15
	/*
	 * Scan the password
	 */
E 15
E 4
D 13
	/*
	 * Only the first <max_length> characters of a password are actually
	 * used due to the limitations of crypt(3).  If the given
D 3
	 * password is longer than this, issue warning and truncate to the
	 * actual usable length.
	 *
	 * NOTE: Since <password> is passed by reference, the truncation
	 * done here affects all subsequent checks.
E 3
I 3
	 * password is longer than this, issue warning message.
E 3
	 */
I 7
#if	0
E 7
D 4
	if (max_length && rc > max_length) {
		printf("WARNING: Only the first %d characters of this password will be used \n",
			max_length);
E 4
I 4
	if (Config.max_length && rc > Config.max_length) {
D 7
/* 		printf("WARNING: Only the first %d characters of this password will be used \n", */
/* 			Config.max_length); */
E 7
I 7
		printf("WARNING: Only the first %d characters of this password will be used \n",
			Config.max_length);
E 7
E 4
D 3
		password[max_length] = 0;	/* Truncate to length */
E 3
	}
I 7
#endif
E 7

E 13
	for (p = password; *p; p++) {
I 15
		/*
		 * Check for adjacent repeated characters
		 */
E 15
		if (*p != last) {
			last = *p;
D 10
			rc = 1;
E 10
I 10
			chr_run = 1;
E 10
		}
D 15
		else {		/* Run of same characters */
E 15
I 15
		else {
E 15
D 4
			if (run_length && ++rc >= run_length) {
E 4
I 4
D 10
			if (Config.run_length && ++rc >= Config.run_length) {
E 10
I 10
			if (Config.run_length && ++chr_run >= Config.run_length) {
E 10
E 4
				(void) sprintf(mesg,
D 4
			"This password has %d or more repeated characters",
					run_length);
E 4
I 4
					"it has %d or more repeated characters",
					Config.run_length);
E 4
D 14
				return(PWCK_OBVIOUS);
E 14
I 14
				return(mesg);
E 14
			}
		}
I 15
		/*
I 17
		 * Look for forbidden characters
		 */
		if (strchr(Config.badchars, *p)) {
			(void) sprintf(mesg,
				"it has an illegal character '%s'",
				ctran(*p));
			return(mesg);
		}
		/*
E 17
		 * Class characters according to ctype
		 */
E 15
D 4
		if (*p < ' ' || *p > '~') {	/* Non-printing character */
D 2
			char	*ctran();
E 2
I 2
			char	*_ctran();
E 2

			if (print_only) {
E 4
I 4
		if (!isprint(*p)) {	 /* Non-printing character */
D 17
			if (Config.print_only) {
E 17
I 17
			if (Config.print_only)
E 17
E 4
D 14
				(void) strcpy(mesg,
D 4
			"This password has non-printing characters");
E 4
I 4
					"it has non-printing characters");
E 4
				return(PWCK_ILLCHAR);
E 14
I 14
				return("it has non-printing characters");
E 14
D 17
			}
D 4
			if (index(illegalcc, *p)) {
E 4
I 4
D 6
			if (INDEX(Config.badchars, *p)) {
E 6
I 6
D 7
			if (index(Config.badchars, *p)) {
E 7
I 7
			if (strchr(Config.badchars, *p)) {
E 7
E 6
E 4
				(void) sprintf(mesg,
D 4
				"Illegal character '%s' in this password",
E 4
I 4
					"it has an illegal character '%s'",
E 4
D 2
					ctran(*p));
E 2
I 2
D 16
					_ctran(*p));
E 16
I 16
					ctran(*p));
E 16
E 2
D 14
				return(PWCK_ILLCHAR);
E 14
I 14
				return(mesg);
E 14
			}
E 17
D 10
			hasone(P_C);
E 10
I 10
			ws_cnt[P_C]++;
E 10
		}
D 10
		else if (isupper(*p))	hasone(P_U);
		else if (islower(*p))	hasone(P_L);
		else if (ispunct(*p))	hasone(P_P);
		else if (isdigit(*p))	hasone(P_D);
E 10
I 10
		if (isupper(*p)) ws_cnt[P_U]++;
		if (islower(*p)) ws_cnt[P_L]++;
		if (ispunct(*p)) ws_cnt[P_P]++;
		if (isdigit(*p)) ws_cnt[P_D]++;
		if (isspace(*p)) ws_cnt[P_S]++;
E 10
	}
D 10
	if (hasany(P_U | P_L))	return(PWCK_OK);	/* UC+lc */
	if (hasany(P_D))	return(PWCK_OK);	/* Numbers */
	if (hasany(P_P))	return(PWCK_OK);	/* Punctutation chars */
	if (hasany(P_C))	return(PWCK_OK);	/* Control chars */
E 10
	/*
I 14
	 * Check for some common patterns
D 15
	 * Look at cracklib/rules.c for how to use PMatch pattern matching
	 * It would be quite nice to have PERL-style regular expressions :-)
E 15
I 15
	 * Look at cracklib/rules.c for how to use PMatch
E 15
	 */
D 18
	if (PMatch("dddsddsdddd", password)) {
E 18
I 18
	if (PMatch("dddsddsdddd", password, 1)) {
E 18
		return("it looks like a Social Security number");
	}
D 15
	if (PMatch("dddsdddd", password)) {
E 15
I 15
D 18
	if (PMatch("dddsdddd", password) ||
	    PMatch("dddsdddsdddd", password) ||
	    PMatch("dsdddsdddsdddd", password)) {
E 15
		return("it looks like a telephone number");
E 18
I 18
	for (pat = phone_patterns; *pat; *pat++) {
		if (PMatch(*pat, password, 1))
			return("it looks like a telephone number");
E 18
	}
	/*
I 17
	 * Forbidden char class checks
	 */
	if (ws_cnt[P_S] && Config.whitespace == 0) {
		return("whitespace characters not allowed");
	}
	/*
E 17
E 14
D 10
	 *	Check for mono-case passwords 
E 10
I 10
D 15
	 * Check for whitespace-only and digits-only passwords
E 15
I 15
	 * Check for whitespace-only or digits-only
E 15
E 10
	 */
D 4
	if (!hasany(P_U) && single_case)	/* All lower case alpha */
E 4
I 4
D 10
	if (!hasany(P_U) && Config.single_case)	/* All lower case alpha */
E 4
		return(PWCK_OK);
D 4
	if (!hasany(P_L) && single_case)	/* All upper case alpha */
E 4
I 4
	if (!hasany(P_L) && Config.single_case)	/* All upper case alpha */
E 4
		return(PWCK_OK);

	if (!hasany(P_L))
		(void) strcpy(mesg,
D 4
			"Upper-case only passwords not allowed");
E 4
I 4
			"upper-case only passwords not allowed");
E 4
	if (!hasany(P_U))
		(void) strcpy(mesg,
D 4
			"Lower-case only passwords not allowed");
E 4
I 4
			"lower-case only passwords not allowed");
E 10
I 10
	if (ws_cnt[P_S] >= pwlen) {
D 14
		(void) strcpy(mesg, "whitespace only passwords not allowed");
		return(PWCK_ILLCHAR);
E 14
I 14
		return("whitespace only passwords not allowed");
E 14
	}
	if (ws_cnt[P_D] >= pwlen) {
D 14
		(void) strcpy(mesg, "digits only passwords not allowed");
		return(PWCK_ILLCHAR);
E 14
I 14
		return("digits only passwords not allowed");
E 14
	}
	/*
D 15
	 * Check for mono-case passwords 
E 15
I 15
	 * Check for single case 
E 15
	 */
	if (ws_cnt[P_U] == 0) {		/* No upper case */
D 11
		if (!Config.single_case) {
E 11
I 11
		if (Config.single_case == 0) {
E 11
D 14
			(void) strcpy(mesg,
D 13
				"lower-case only passwords not allowed");
E 13
I 13
				"lower case only passwords not allowed");
E 13
			return(PWCK_ILLCHAR);
E 14
I 14
			return("lower case only passwords not allowed");
E 14
		}
	}
	if (ws_cnt[P_L] == 0) {		/* No lower case */
D 11
		if (!Config.single_case) {
E 11
I 11
		if (Config.single_case == 0) {
E 11
D 14
			(void) strcpy(mesg,
D 13
				"upper-case only passwords not allowed");
E 13
I 13
				"upper case only passwords not allowed");
E 13
			return(PWCK_ILLCHAR);
E 14
I 14
			return("upper case only passwords not allowed");
E 14
		}
	}
I 15
	/*
	 * Check for alpha only
	 */
E 15
	if (ws_cnt[P_U] + ws_cnt[P_L] == pwlen) {
D 11
		(void) strcpy(mesg, "alpha only passwords not allowed");
		return(PWCK_ILLCHAR);
E 11
I 11
		if (Config.alpha_only == 0) {
D 14
			(void) strcpy(mesg, "alpha only passwords not allowed");
			return(PWCK_ILLCHAR);
E 14
I 14
			return("alpha only passwords not allowed");
E 14
D 15
		} else {
			return(PWCK_OK);
E 15
		}
E 11
	}
	/*
D 15
	 * Check alpha passwords for more goodies that make it harder to crack
E 15
I 15
	 * Check how many character classes
E 15
	 */
I 13
	if (Config.char_classes) {
		int	cc = 0,
			ic;

		if (Config.char_classes > P_END) {
D 15
			warn("Min character class set too high\n");
E 15
I 15
			warn("Min character class set too high (%d max)\n", P_END);
			Config.char_classes = P_END;
E 15
		}
D 18
		for (ic = P_START; ic <= P_END; ic++)
D 15
			cc += ws_cnt[ic];
E 15
I 15
			cc += (ws_cnt[ic] != 0);
E 15
		if (cc < Config.char_classes) {
D 14
			(void) strcpy(mesg,
				"password needs more character classes");
			return(PWCK_ILLCHAR);
E 14
I 14
			return("password needs more character classes");
E 18
I 18
		for (ic = P_START; ic <= P_END; ic++) {
			if (ws_cnt[ic] == 0) {
				if (*class_msg[ic] == 0)
					continue;
				if (mesg[0])
					(void) strcat(mesg, " or ");
				else
					(void) strcpy(mesg, "needs more ");
				(void) strcat(mesg, class_msg[ic]);
			} else {
				cc++;
			}
E 18
E 14
		}
I 18
		if (cc < Config.char_classes)
			return(mesg);
E 18
	}
E 13
D 15
	if (ws_cnt[P_D]) return(PWCK_OK);	/* Does it have digits? */
	if (ws_cnt[P_P]) return(PWCK_OK);	/* Punctutation chars? */
	if (ws_cnt[P_C]) return(PWCK_OK);	/* Control chars? */
E 10
E 4
	return(PWCK_ILLCHAR);
E 15
I 15
	/*
	 * All tests passed
	 */
	return(PWCK_OK);
E 15
}
I 7
D 10

E 7
/*	End %M% */
E 10
I 10
/* End %M% */
E 10
E 1
