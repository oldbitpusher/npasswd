h47087
s 00001/00001/00279
d D 1.4 99/07/26 12:45:12 clyde 4 3
c Fix string allocation
e
s 00052/00012/00228
d D 1.3 98/11/17 16:46:23 clyde 3 2
c 1. Add copyright notice
c 2. Cleanup some comments
c 3. Move some declarations around
e
s 00005/00005/00235
d D 1.2 96/08/06 14:48:57 clyde 2 1
c beta 3 development checkin
e
s 00240/00000/00000
d D 1.1 96/06/06 16:24:16 clyde 1 0
c date and time created 96/06/06 16:24:16 by clyde
e
u
U
f e 0
t
T
I 1
/*
I 3
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
E 3
 *	split - Handy dandy use-everywhere string splitter
 */
#include <strings.h>
#include <ctype.h>
#include <stdio.h>

D 3
/* Uncomment if needed */
/* extern char	*malloc(); */

E 3
#ifndef	lint
static char sccsid[] = "%W% %G% (cc.utexas.edu) %P%";
#endif

I 3
struct _tk {				/* Token tree item */
	char	*t_data;
	struct _tk	*t_next;
};
typedef struct _tk token;		/* And item typedef */
#define	NULLT	(token *)0

E 3
/*
 *	split - split string into tokens.
 *
 *	Returns: Address of (char *) vector containing
 *		pointers to the split up <string>
 *		(char **)0 if error or empty line
 *
 *	+-----------------------+
 *	| addr of string 1	| <--- address returned that can
 *	+-----------------------+      be passed to free()
 *	| addr of string 2	|
 *	+-----------------------+
 *	| 	...		|
 *	+-----------------------+
 *	| addr of string N	|
 *	+-----------------------+
 *	|      (char *)0      	|
 *	+-----------------------+
 *	|   Char 0 / String 1   |
 *	|   Char 1 / String 1   |
 *	|   (char )0            |
 *	+-----------------------+
 *	| 	.....		|
 *	+-----------------------+
 *	|   Char 0 / String N   |
 *	|   Char 1 / String N   |
 *	|   (char )0            |
 *	+-----------------------+
 *
 */
D 3

struct _tk {
	char	*t_data;
	struct _tk	*t_next;
};
typedef struct _tk token;
#define	NULLT	(token *)0

E 3
char **
split(string, separator, quotes, comment)
	char	*string;	/* String to split */
D 3
	char	separator;		/* Character to split on */
E 3
I 3
	char	separator;	/* Character to split on */
E 3
	char	*quotes;	/* String of quote characters */
	char	comment;	/* Character that starts comment */
{
	token	*T;		/* Token tree traverser */
	char	*s_token,	/* Start of token */
		*e_token;	/* End of token */
	int	ntokens = 0;	/* Number of tokens found */
	char	*splitbuf,	/* Split buffer */
		*result;	/* Thing that is returned */
	char	**c_strp;	/* String address pointer */
	char	*c_strs;	/* String storage pointer */
	static token	*c_head = NULLT;	/* Head of token tree */

	/*
	 * Initialize token tree
	 */
	if (c_head == NULLT) {
		T = (token *)malloc(sizeof (token));
		if (T == NULLT)
			return((char **)0);
		c_head = T;
		c_head->t_next = NULLT;
		c_head->t_data = (char *)0;
	}

	/*
	 * No string or empty string?
	 */
	if (string == 0 || !*string)
		return(0);

	/*
	 * Allocate parsing buffer and copy string
	 */
	if ((splitbuf = (char *)malloc((unsigned )strlen(string)+1)) == (char *)0) {
		return(0);
	}
	(void) strcpy (splitbuf, string);

	/*
	 * Do the split
	 */
	T = c_head;			/* Top of token tree */
	s_token = e_token = splitbuf;
	while (*s_token) {
		if (!separator) {
			/* Find start of next field (whitespace seperation) */
			while (*e_token && isspace(*e_token))
				e_token++;
		}
		if (!*e_token)		/* End of string? */
			break;
		s_token = e_token;

		/*
		 * Check for comment starting with the comment character
		 * and continuing to end of string or newline
		 */
		if (comment && comment == *s_token) {
			while (*s_token && *s_token != '\n')
				s_token++;
			if (!*s_token)
				break;	/* from main parse loop */
			s_token++;		/* Skip the newline */
			e_token = s_token;	/* Point to after newline */
			continue;
		}

		/*
		 * Find end of this token
		 */
D 2
		if (quotes && index(quotes, *s_token)) {
E 2
I 2
		if (quotes && strchr(quotes, *s_token)) {
E 2
				/* Handle quoted string ("x=y z") */
			char	qcx;

			qcx = *s_token;
			*s_token++ = '\0';
			e_token++;
			while (*e_token && *e_token != qcx)
				*e_token++;
			/* ERROR - e_token null (no closing quote) */
		} else {
			if (separator)
				while (*e_token && *e_token != separator)
					*e_token++;
			else
				while (*e_token && !isspace(*e_token))
					*e_token++;
		}
		if (*e_token)
			*e_token++ = '\0';

		/*
		 * Store this token in the token tree
		 */
		T->t_data = s_token;
		if (T->t_next == NULLT) {	/* Extend token tree */
			token	*N;

			N = (token *)malloc(sizeof (token));
			if (N == NULLT)
				break;

			N->t_next = NULLT;
			N->t_data = (char *)0;
			T->t_next = N;
		}
		T = T->t_next;
		ntokens++;
	}

	/*
	 * Allocate result buffer
	 */
	result = (char *)malloc(
		(unsigned )((ntokens+2) * sizeof (char *)) + /* # of tokens */
D 4
		(unsigned )strlen(string));		/* String data */
E 4
I 4
		(unsigned )strlen(string)+1);		/* String data */
E 4
	if (result == 0)
		return(0);

	/*
	 * Traverse the token tree and copy strings into the result buffer
	 */
	c_strp = (char **)result;
	c_strs = &result[(ntokens+2) * sizeof (char *)];

	for (T = c_head; T->t_data; T = T->t_next) {
		char	*s;		/* Temporary */

		*c_strp++ = c_strs;
		s = T->t_data;
		while (*s) *c_strs++ = *s++;
		*c_strs++ = 0;
		T->t_data = 0;		/* Clean up token */
	}
	*c_strp = 0;

	free(splitbuf);			/* Release split buffer */
	return((char **)result);
}


#ifdef	_TEST_PROGRAM_
main()
{
	char buf[80];
	char sep[16];
	char quote[16];
	char comment[16];
	char	**vp, **pp;

	for (;;) {
		printf("\n\nString: ");
		fgets(buf, 80, stdin);
D 2
		*(index(buf, '\n')) = 0;
E 2
I 2
		*(strchr(buf, '\n')) = 0;
E 2

		printf("Seperator (null for whitespace): ");
		fgets(sep, 16, stdin);
D 2
		*(index(sep, '\n')) = 0;
E 2
I 2
		*(strchr(sep, '\n')) = 0;
E 2

		printf("Quote char (null for nothing): ");
		fgets(quote, 16, stdin);
D 2
		*(index(quote, '\n')) = 0;
E 2
I 2
		*(strchr(quote, '\n')) = 0;
E 2

		printf("Comment char (null for nothing): ");
		fgets(comment, 16, stdin);
D 2
		*(index(comment, '\n')) = 0;
E 2
I 2
		*(strchr(comment, '\n')) = 0;
E 2

		vp = split(buf, sep[0], quote, comment[0]);
		if (vp == 0) {
			printf("Split error\n");
			continue;
		}
		printf("split returns %x\n", vp);
		for (pp = vp; *pp; pp++) {
			printf("addr %x ptr %x str <%s>\n", pp, *pp, *pp);
		}
		free(vp);
	}
}
#endif
/*
 * End %M%
 */
E 1
