h49231
s 00011/00007/00173
d D 1.4 98/11/17 16:46:41 clyde 4 3
c Cleanup function comments
e
s 00044/00000/00136
d D 1.3 98/11/17 15:44:20 clyde 3 2
c Add copyright notice
e
s 00007/00005/00129
d D 1.2 96/08/13 18:01:23 clyde 2 1
c Add const declarations here and there
e
s 00134/00000/00000
d D 1.1 96/08/07 15:19:17 clyde 1 0
c date and time created 96/08/07 15:19:17 by clyde
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
 * BSD Compatiblity routines
 *
 * Compliation: cc -c %M%
 */

#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu) %P%";
#endif

#include "compatibility.h"

#ifndef	HAS_RENAME
/*
D 4
 *	rename - replacement for BSD rename(2)
E 4
I 4
 * rename
 *	Replacement for BSD rename(2)
E 4
 */
rename(src, dst)
D 2
	char	*src,		/* Source path */
		*dst;		/* Destination path */
E 2
I 2
D 4
	const char	*src,		/* Source path */
			*dst;		/* Destination path */
E 4
I 4
	char	*src,		/* Source path */
		*dst;		/* Destination path */
E 4
E 2
{
	extern int	errno;

	if (unlink(dst) < 0) {
		if (errno != ENOENT)
			return(-1);
	}
	if (link(src, dst) < 0)
		return(-1);
	return(unlink(src));
}
#endif

#ifndef	HAS_STRDUP
/*
D 4
 *	strdup - copy string into new storage
E 4
I 4
 * strdup
 *	Copy string into new storage
E 4
 */
char *strdup(s)
D 2
	char	*s;		/* String to copy */
E 2
I 2
D 4
	const char	*s;		/* String to copy */
E 4
I 4
	char	*s;	/* String to copy */
E 4
E 2
{
	char	*t;	/* Temp */

	if (s == NULL)
		return("");
		if ((t = malloc(strlen(s) + 1)) == NULL)
			return(0);
	(void) strcpy(t, s);
	return(t);
}
#endif


#ifndef	HAS_STRCASECMP
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
static char charmap[] = {
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
D 4
 *	strcasecmp - case independant string compare
E 4
I 4
 * strcasecmp
 *	Case independant string compare
E 4
 */
strcasecmp(s1, s2)
D 2
	char *s1, *s2;
E 2
I 2
	char	*s1,
		*s2;
E 2
{
	while (charmap[*s1] == charmap[*s2++])
		if (*s1++=='\0')
			return(0);
	return(charmap[*s1] - charmap[*--s2]);
}

/*
D 4
 *	strncasecmp - case independant string compare
E 4
I 4
 * strncasecmp
 *	Case independant string compare
E 4
 */
strncasecmp(s1, s2, n)
D 2
	char	*s1, *s2;
E 2
I 2
	char	*s1,
		*s2;
E 2
	int	n;
{
	while (--n >= 0 && charmap[*s1] == charmap[*s2++])
		if (*s1++ == '\0')
			return(0);
	return(n<0 ? 0 : charmap[*s1] - charmap[*--s2]);
}
/* end of UCB copyrighted code 	*/
#endif
/*
 * End %M%
 */
E 1
