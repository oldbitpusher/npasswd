h09357
s 00007/00001/00073
d D 1.12 98/08/17 14:55:02 clyde 12 11
c Support verbose arg to FascistNpasswd()
e
s 00001/00031/00073
d D 1.11 98/04/14 13:32:36 clyde 11 10
c Massive simplification
e
s 00083/00049/00021
d D 1.10 98/04/07 09:58:07 clyde 10 9
c Major rewrite:
c 1. Add UT copyright
c 2. Rewrite dictionary handling
c 3. Call Cracklib/FascistNpasswd() to do the work
e
s 00011/00008/00059
d D 1.9 98/03/26 10:56:58 clyde 9 8
c Change error message handling & debugging
e
s 00003/00005/00064
d D 1.8 96/09/12 16:20:18 clyde 8 7
c Change debug printing
e
s 00002/00002/00067
d D 1.7 96/08/29 12:59:27 clyde 7 6
c Remove 'const' declarations (too much compiler trouble)
e
s 00003/00003/00066
d D 1.6 96/08/13 13:04:59 clyde 6 5
c Add const where useful
e
s 00001/00005/00068
d D 1.5 96/08/06 14:14:02 clyde 5 4
c beta 3 cycle 1 checkin
e
s 00006/00004/00067
d D 1.4 96/03/27 17:20:23 clyde 4 3
c Add debug hooks
e
s 00000/00000/00071
d D 1.3 95/04/05 16:19:58 clyde 3 2
c Beta 3 development checkin
e
s 00005/00000/00066
d D 1.2 94/03/16 11:06:41 clyde 2 1
c If DEBUG set, don't quit if a dictionary is missing
e
s 00066/00000/00000
d D 1.1 94/03/16 09:52:33 clyde 1 0
c date and time created 94/03/16 09:52:33 by clyde
e
u
U
t
T
I 1
/*
D 10
 *	pwck_crack - Call the 'crack' dictionary checker
 *	Returns:
 *		PWCK_INDICT if <password> was in any dictionary
 *		PWCK_OK if password found in a dictionary
 *		PWCK_FAIL if a dictionary cannot be opened
E 10
I 10
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
E 10
 */

I 10
/*
 * pwck_crack - Call the 'Crack' dictionary checker
 *
 * Usage
 *	error = pwck_crack(char *, struct passwd *);
 *
 * Returns
 *	Error message from Cracklib/FascistNpasswd if password flunks
 *	PWCK_OK if password ok
 *
 */

E 10
#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu)";
#endif

D 5
#include "compatibility.h"
#include "checkpassword.h"
#include "pwck_lib.h"
E 5
I 5
#include "pwck_defines.h"
E 5
D 10
#include "cracklib/packer.h"
E 10

D 10
public int
D 9
pwck_crack(password, user, mesgbuf)
E 9
I 9
pwck_crack(password, user, reply_msg)
E 10
I 10
public char *
pwck_crack(password, user)
E 10
E 9
D 6
	char	*password;	/* Candidate password */
	struct passwd	*user;	/* Passwd info for user */ /*NOTUSED*/
	char	*mesgbuf;	/* Message buffer */
E 6
I 6
D 7
	const char	*password;	/* Candidate password */
	const struct passwd *user;	/* Passwd info for user */ /*NOTUSED*/
E 7
I 7
	char	*password;	/* Candidate password */
	struct passwd *user;	/* Passwd info for user */ /*NOTUSED*/
E 7
D 9
	char	*mesgbuf;		/* Message buffer */
E 9
I 9
D 10
	char	*reply_msg;	/* Message buffer */
E 10
E 9
E 6
{
D 10
	int	rcode;		/* Return code temp */
E 10
	char	*msg;		/* Scratch */
D 10
	dictionary *d;		/* Current dictionary */
E 10

D 10
	for (d = Config.dictionaries; d; d = d->next) {
		PWDICT	*t;
E 10
I 10
D 11
#ifdef	CONSERVE_FDS
	/*
	 * If file descriptors need to be conserved
	 * check the dictionaries one at a time
	 */
	int	i;
	int	ok = 0;
	PWDICT	*px[2];
E 10

D 10
		/*
		 * Check that this dictionary can be opened.  FascistCheck()
		 * will abort if asked to use a non-existent dictionary
		 * and I don't want that behavior.
		 */
		if  ((t = PWOpen(d->path, "r")) == NULL) {
E 10
I 10
	for (i = 0; Config.dict_path[i]; i++) {
		PWDICT	*t = PWOpen(Config.dict_path[i], "r");

		if (!t) {
E 10
I 4
D 8
			if (Config.debug)
				printf("pwck_crack: PWOpen failed on %s\n",
E 8
I 8
			debug(DB_LOOKUP, "pwck_crack: PWOpen failed on %s\n",
E 8
D 10
					d->path);
E 4
D 5
			if (d->flags & DICT_OPTIONAL)
				continue;
E 5
D 9
			if (mesgbuf)
				(void) sprintf(mesgbuf,
E 9
I 9
			if (reply_msg)
				(void) sprintf(reply_msg,
E 9
					"cannot open dictionary \"%s\"",
					d->path);
I 2
#ifdef	DEBUG
D 9
			printf(">> %s\n", mesgbuf);
E 9
I 9
			printf("Dictionary open failure %s\n", reply_msg);
E 9
			return(PWCK_OK);
#else
E 2
			/*
			 * POLICY: If any dictionary cannot be opened, then
			 * don't approve the password because it could be
			 * vunerable.
			 * The dictionary could be ignored, or I could fall
			 * back to doing fgrep of a flat file, or a nicer
			 * abort performed.
			 */
I 9
			debug(DB_PWCHECK,
				"pwck_crack: \"%s\" dictionary open failure\n",
				d->path);
E 9
			return(PWCK_FAIL);
I 2
#endif
E 10
I 10
				Config.dict_path[i]);
			continue;
E 10
E 2
		}
D 10
		PWClose(t);
D 4
#ifdef	DEBUG
		printf("pwck_crack: pw <%s> dictionary \"%s\"\n",
			password, d->path);
#endif
E 4
I 4
D 8
		if (Config.debug)
			printf("pwck_crack: pw \"%s\" dictionary \"%s\"\n",
				password, d->path);
E 8
I 8
D 9
		debug(DB_LOOKUP, "pwck_crack: pw \"%s\" dictionary \"%s\"\n",
E 9
I 9
		debug(DB_PWCHECK, "pwck_crack: pw \"%s\" dictionary \"%s\"\n",
E 9
			password, d->path);
E 8
E 4
		if (msg = FascistCheck(password, d->path)) {
D 9
			if (mesgbuf)
				(void) strcpy(mesgbuf, msg);
E 9
I 9
			if (reply_msg)
				(void) strcpy(reply_msg, msg);
E 9
			return(PWCK_INDICT);
		}
E 10
I 10
		ok++;
		px[0] = t;
		px[1] = (PWDICT *)0;
		msg = FascistNpasswd(px, password);
		(void) PWClose(t);
		if (msg)
			return(msg);
E 10
	}
I 10
	if (ok)
		return(PWCK_OK);
	return("could not open any dictionaries");
#else
	if (msg = FascistNpasswd(Config.dict_ptrs, password))
E 11
I 11
D 12
	if (msg = FascistNpasswd(Config.dictionaries, password))
E 12
I 12
#if	(CDEBUG < CDEBUG_ALL)
	if (msg = FascistNpasswd(Config.dictionaries, password, 0))
E 12
E 11
		return(msg);
I 12
#else
	if (msg = FascistNpasswd(Config.dictionaries, password,
		get_debug() >= DB_DETAIL))
			return(msg);
#endif
E 12
E 10
	return(PWCK_OK);
I 10
D 11
#endif
E 11
E 10
}
/* End %M% */
E 1
