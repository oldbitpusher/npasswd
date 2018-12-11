/*
 * Copyright (C) 2002  The University of Texas at Austin ("U. T. Austin").
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  Contact: npasswd-support@www.utexas.edu
 *
 */

/*
 * BSD Compatiblity routines
 *
 * Compliation: cc -c $RCSfile: compatibility.c,v $
 */

#ifndef lint
static char sccsid[] = "$Id: compatibility.c,v 1.5 2002/10/02 16:11:04 clyde Exp $";
#endif

#include "compatibility.h"

#ifndef	HAS_RENAME
/*
 * rename
 *	Replacement for BSD rename(2)
 */
rename(src, dst)
	char	*src,		/* Source path */
		*dst;		/* Destination path */
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
 * strdup
 *	Copy string into new storage
 */
char *strdup(s)
	char	*s;	/* String to copy */
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
 * strcasecmp
 *	Case independant string compare
 */
strcasecmp(s1, s2)
	char	*s1,
		*s2;
{
	while (charmap[*s1] == charmap[*s2++])
		if (*s1++=='\0')
			return(0);
	return(charmap[*s1] - charmap[*--s2]);
}

/*
 * strncasecmp
 *	Case independant string compare
 */
strncasecmp(s1, s2, n)
	char	*s1,
		*s2;
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
 * End $RCSfile: compatibility.c,v $
 */
