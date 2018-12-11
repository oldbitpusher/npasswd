/*
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
 * pwck_lexical - Perform lexical analysis of password candidate.
 *
 * Usage
 *	error = pwck_lexical(char *, struct passwd *);
 *
 * Returns
 *	Error message if password flunks
 *	PWCK_OK if passwd is ok
 */

#ifndef lint
static char sccsid[] = "@(#)pwck_lexical.c	1.18 11/13/98 (cc.utexas.edu)";
#endif

#include "pwck_defines.h"

#define	P_START	0 	/* Start of array */
#define	P_U	0 	/* Upper case in password */
#define	P_L	1 	/* Lower case in password */
#define	P_D	2 	/* Digits in password */
#define	P_P	3 	/* Punctutation chars in password */
#define	P_S	4 	/* Whitespace chars in password */
#define	P_C	5 	/* Control chars in password */
#define	P_END	P_S
#define	P_SIZE	(P_END + 1)

/*
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
 *	ctran - produce printable version of any ASCII character
 */
public char *
ctran (c)
	char	c;		/* Character to represent */
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

public char *
pwck_lexical(password, user)
	char	*password;		/* Password to check */
	struct passwd *user;		/* Passwd info for user */ /* NOTUSED */
{
	int	chr_run,	/* Duplicate character count */
		pwlen;		/* Length of password */
	char	*p;		/* Scratch */
	char	**pat;		/* Match pattern */
	char	last = 0;	/* Last character seen (for run checks) */
	char	ws_cnt[P_SIZE];	/* Character classes */
	static char	mesg[STRINGLEN];	/* Error message temp */

	zeromem(mesg, sizeof mesg);
	zeromem(&ws_cnt, sizeof ws_cnt);

	debug(DB_PWCHECK, "pwck_lexical: \"%s\"\n", password);
	/*
	 * Minimum length check
	 * Maximum length check is done in checkpassword()
	 */
	pwlen = strlen(password);
	if (Config.min_length && pwlen < Config.min_length) {
		(void) sprintf(mesg,
			"it is too short (minimum length is %d characters)",
			Config.min_length);
		return(mesg);
	}
	/*
	 * Scan the password
	 */
	for (p = password; *p; p++) {
		/*
		 * Check for adjacent repeated characters
		 */
		if (*p != last) {
			last = *p;
			chr_run = 1;
		}
		else {
			if (Config.run_length && ++chr_run >= Config.run_length) {
				(void) sprintf(mesg,
					"it has %d or more repeated characters",
					Config.run_length);
				return(mesg);
			}
		}
		/*
		 * Look for forbidden characters
		 */
		if (strchr(Config.badchars, *p)) {
			(void) sprintf(mesg,
				"it has an illegal character '%s'",
				ctran(*p));
			return(mesg);
		}
		/*
		 * Class characters according to ctype
		 */
		if (!isprint(*p)) {	 /* Non-printing character */
			if (Config.print_only)
				return("it has non-printing characters");
			ws_cnt[P_C]++;
		}
		if (isupper(*p)) ws_cnt[P_U]++;
		if (islower(*p)) ws_cnt[P_L]++;
		if (ispunct(*p)) ws_cnt[P_P]++;
		if (isdigit(*p)) ws_cnt[P_D]++;
		if (isspace(*p)) ws_cnt[P_S]++;
	}
	/*
	 * Check for some common patterns
	 * Look at cracklib/rules.c for how to use PMatch
	 */
	if (PMatch("dddsddsdddd", password, 1)) {
		return("it looks like a Social Security number");
	}
	for (pat = phone_patterns; *pat; *pat++) {
		if (PMatch(*pat, password, 1))
			return("it looks like a telephone number");
	}
	/*
	 * Forbidden char class checks
	 */
	if (ws_cnt[P_S] && Config.whitespace == 0) {
		return("whitespace characters not allowed");
	}
	/*
	 * Check for whitespace-only or digits-only
	 */
	if (ws_cnt[P_S] >= pwlen) {
		return("whitespace only passwords not allowed");
	}
	if (ws_cnt[P_D] >= pwlen) {
		return("digits only passwords not allowed");
	}
	/*
	 * Check for single case 
	 */
	if (ws_cnt[P_U] == 0) {		/* No upper case */
		if (Config.single_case == 0) {
			return("lower case only passwords not allowed");
		}
	}
	if (ws_cnt[P_L] == 0) {		/* No lower case */
		if (Config.single_case == 0) {
			return("upper case only passwords not allowed");
		}
	}
	/*
	 * Check for alpha only
	 */
	if (ws_cnt[P_U] + ws_cnt[P_L] == pwlen) {
		if (Config.alpha_only == 0) {
			return("alpha only passwords not allowed");
		}
	}
	/*
	 * Check how many character classes
	 */
	if (Config.char_classes) {
		int	cc = 0,
			ic;

		if (Config.char_classes > P_END) {
			warn("Min character class set too high (%d max)\n", P_END);
			Config.char_classes = P_END;
		}
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
		}
		if (cc < Config.char_classes)
			return(mesg);
	}
	/*
	 * All tests passed
	 */
	return(PWCK_OK);
}
/* End pwck_lexical.c */
