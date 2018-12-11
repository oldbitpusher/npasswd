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
 * String to number converter
 *
 * Exported routines:
 *	xatoi
 */

#ifndef lint
static char sccsid[] = "$Id: xatoi.c,v 1.2 1998/11/17 00:00:00 clyde Exp $ (cc.utexas.edu) %P%";
#endif

#include "compatibility.h"

/*
 *	Is argument an octal digit?
 */
static int
octdigit(c)
	char	c;
{
	if (!isdigit(c))
		return(0);
	switch (c) {
		case '8':
		case '9': return(0);
	}
	return(1);
}

/*
 *	Is argument a decimal digit?
 */
static int
decdigit(c)
	char	c;
{
	return (isdigit(c));
}

/*
 *	Is argument a hexidecimal digit?
 */
static int
hexdigit(c)
	char	c;
{
#ifdef	HAS_ISXDIGIT
	return (isxdigit(c));
#else
	return (decdigit(c) |
		(c >= 'a' && c <= 'f') |
		(c >= 'A' && c <= 'F'));
#endif
}

/*
 * xatoi
 *	Smart 'atoi' which recognizes decimal, octal and hex constants.
 * Usage:
 *	status = xatoi(string, &end-ptr, &rval);
 *
 * <string> can be one of:
 *	[-]DD	= decimal number (with optional minus sign)
 *	[-]0ooo	= octal number (with optional minus sign)
 *	[-]0fxx	= hexidecimal number (with optional minus sign)
 *
 * <end-ptr>
 *	Pointer to place in <string> where first non-numeric found
 *	May be null
 *
 * <rval>
 *	Stash location for decoded value
 *
 * Returns:
 *	1 if conversion successful
 *	0 if conversion error or nothing found
 */
xatoi(ip, ipp, iv)
	char	*ip,	/* Number string */
		**ipp;	/* Pointer to end of string */ /* RETURN VALUE */
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
	if (*ip == '0') { 		/* Leading '0' */
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
/* End $RCSfile: xatoi.c,v $ */
