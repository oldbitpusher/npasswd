h40102
s 00071/00006/00103
d D 1.2 98/11/17 16:47:08 clyde 2 1
c 1. Add copyright notice
c 2. Reformat function comments
e
s 00109/00000/00000
d D 1.1 96/08/07 15:19:20 clyde 1 0
c date and time created 96/08/07 15:19:20 by clyde
e
u
U
f e 0
t
T
I 1
/*
D 2
 *	xdecode - Routines for interperting strings
E 2
I 2
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
E 2
 */

I 2
/*
 * Routines for interperting strings
 *
 * Exported routines:
 *	decode_boolean
 *	decode_int
 *	decode_string
 */

E 2
#ifndef lint
D 2
static char sccsid[] = "%W% %G% (cc.utexas.edu)";
E 2
I 2
static char sccsid[] = "%W% %G% (cc.utexas.edu) %P%";
E 2
#endif

#include "compatibility.h"

int	decode_boolean _((char *));
int	decode_int _((char *));
void	decode_string _((char *, char *, int));

/*
D 2
 *	decode_boolean - decode a boolean value
E 2
I 2
 * decode_boolean
 *	Decode a boolean value string (case insensitive)
 * Usage:
 *	value = decode_boolean(string);
 * Returns:
 *	1 if <string> is "true"
 *	0 otherwise
E 2
 */
int
decode_boolean(s)
D 2
	char	*s;
E 2
I 2
	char	*s;		/* Boolean string */
E 2
{
	return(*s == '1'
		| (strcasecmp(s, "true") == 0)
		| (strcasecmp(s, "yes") == 0)
		| (strcasecmp(s, "on") == 0));
}

/*
D 2
 *	decode_int - decode an integer value
E 2
I 2
 * decode_int
 *	Decode an integer string
 * Usage:
 *	value = decode_int(string);
 * Returns:
 *	Converted value if proper
 *	-1 if conversion error (this means that negative numbers
 *	are not legal)
E 2
 */
int
decode_int(s)
	char	*s;	/* String to decode */
{
	int	t;	/* Temp */

	if (xatoi(s, (char *)0, &t))
		return(t);
	return(-1);
}

/*
D 2
 * decode_string - copy string, converting backslash escapes
E 2
I 2
 * decode_string
 *	Copy string, converting backslash escapes
E 2
 *	Can handle most C backslash escape sequences
I 2
 * Usage:
 * 	decode_string(dst, src, length(dst));
E 2
 */
void
decode_string(dst, src, len)
	char	*dst,		/* Destination */
		*src;		/* Source */
	int	len;		/* sizeof Destination */
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
/*
 * End %M%
 */
E 1
