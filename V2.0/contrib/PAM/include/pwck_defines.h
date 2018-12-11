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
 * pwck_defines.h - definitions for checkpassword library modules
 * 
 * @(#)pwck_defines.h	1.15 08/17/98 (cc.utexas.edu)
 */
#include "compatibility.h"
#include "constants.h"
#include "defines.h"
#include "common.h"
#include "checkpassword.h"
#include "packer.h"

/*
 * Declarations for internal routines.
 * Declarations for external routines are in "checkpasswd.h"
 */
public char	*pwck_crack   _((char *, struct passwd *));
public char	*pwck_lexical _((char *, struct passwd *));
public char	*pwck_local   _((char *, struct passwd *));
public char	*pwck_passwd  _((char *, struct passwd *));
public char	*pwck_vicb    _((char *, struct passwd *));
public char	*pwck_history _((char *, struct passwd *));
public char	*pwck_history_configure _((char **));
public void	pwck_history_probe _((char *));
public char	*ctran _((char));

typedef char	*(*checkproc)();

#define	NBADCHARS	128
#define	NCHECKPROCS	16
#define	NDICTIONARIES	48

#define	PWCK_OK		((char *)0)
#define	PWCK_NULL	"it is empty"
#define	PWCK_OBVIOUS	"it is too easy to guess"
#define	PWCK_PASSWD	"it is part of your user information"
#define	PWCK_INDICT	"it is too similar to a dictionary word"
#define	PWCK_ILLCHAR	"it has an illegal character in it"
#define	PWCK_SHORT	"it is too short"
#define	PWCK_REUSE	"it has been used recently"

/*
 * Configuration block for the password checker
 */
struct checkpassword_config {	/* Configuration block */
	int	initialized,	/* Password checker init flag */
		length_warn,	/* Warn if password is over length */
		single_case,	/* Single-case passwords ok or not */
		alpha_only,	/* All-alpha passwords ok or not */
		print_only,	/* Printable characters only */
		whitespace,	/* Allow whitespace chars */
		char_classes,	/* Minimum number of char classes */
		run_length,	/* Maximum length of character runs */
		min_length,	/* Minimum password length */
		max_length;	/* Maximum effective length */
	char	*dictionaries[NDICTIONARIES]; /* Dictionary paths */
	char	badchars[NBADCHARS];	/* Characters not allowed */
	checkproc checkprocs[NCHECKPROCS]; /* Vector of check routines */
};
extern struct checkpassword_config	Config;

/* End pwck_defines.h */
