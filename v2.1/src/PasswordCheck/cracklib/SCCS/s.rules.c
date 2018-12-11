h36559
s 00005/00003/01036
d D 1.7 98/11/13 14:44:57 clyde 7 6
c Add argument to PMatch to allow initial string match
e
s 00147/00029/00892
d D 1.6 98/04/21 15:23:03 clyde 6 5
c 1. Add more rules from Crack 5.0
c 2. Add explanation of what each rules does
c 3. Add explanation of match rules
c 4. Break out language-depedant strings into defines
e
s 00156/00065/00765
d D 1.5 98/04/09 16:40:36 clyde 5 4
c 1. Add UT copyright message 
c 2. Sprinkle (void) to make lint happier
c 3. Change Debug() routine & call
c 4. Add comments to each routine
e
s 00011/00011/00819
d D 1.4 98/04/07 16:44:47 clyde 4 3
c Move Debug() to after cracklib_rules_debug
e
s 00008/00001/00822
d D 1.3 98/04/07 12:58:40 clyde 3 2
c 1. Enable debugging via "cracklib_rules_debug" variable
c 2. Move some macros from packer.h
e
s 00001/00009/00822
d D 1.2 97/09/23 12:23:38 clyde 2 1
c 1. Comment out debugging code
c 2. Remove Crack internal hooks
e
s 00830/00000/00000
d D 1.1 96/08/09 16:29:42 clyde 1 0
c date and time created 96/08/09 16:29:42 by clyde
e
u
U
f e 0
t
T
I 1
/*
 * This program is copyright Alec Muffett 1993. The author disclaims all 
 * responsibility or liability with respect to it's usage or its effect 
 * upon hardware or computer systems, and maintains copyright as set out 
 * in the "LICENCE" document which accompanies distributions of Crack v4.0 
 * and upwards.
 */
I 5
/*
 * Modifications made by Clyde Hoover
 *	Academic Computing & Instructional Technologies Services
 *	University of Texas at Austin
 *
 * Title to copyright to original version of this software shall at all times
 * remain with Alec Muffett.
 *
 * Title to copyright to U. T. Austin modificiations to this software and 
 * its associated documentation shall at all times remain with U. T. Austin.
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
 * No right is granted to use in advertising, publicity
 * or otherwise any trademark, service mark, or the name of U. T. Austin.
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
E 5

I 5
#ifndef	lint
E 5
static char vers_id[] = "rules.c : v5.0p3 Alec Muffett 20 May 1993";
static char ut_id[] = "%W% %G% (cc.utexas.edu)";
I 5
#endif
E 5

D 2
#ifndef IN_CRACKLIB

#include "crack.h"

#else

E 2
#include "packer.h"

D 4
static void
Debug(val, a, b, c, d, e, f, g)
    int val;
    char *a, *b, *c, *d, *e, *f, *g;
{
D 2
    fprintf(stderr, a, b, c, d, e, f);
E 2
I 2
D 3
/*     fprintf(stderr, a, b, c, d, e, f); */
E 3
I 3
    if (cracklib_rules_debug > val)
	fprintf(stderr, a, b, c, d, e, f);
E 3
E 2
}

I 3
int	cracklib_rules_debug = 0;

E 4
#define CRACK_TOLOWER(a) 	(isupper(a)?tolower(a):(a)) 
#define CRACK_TOUPPER(a) 	(islower(a)?toupper(a):(a)) 
#define STRCMP(a,b)		strcmp((a),(b))

E 3
D 2
#endif

E 2
D 6
#define RULE_NOOP	':'
#define RULE_PREPEND	'^'
#define RULE_APPEND	'$'
#define RULE_REVERSE	'r'
#define RULE_UPPERCASE	'u'
#define RULE_LOWERCASE	'l'
#define RULE_PLURALISE	'p'
#define RULE_CAPITALISE	'c'
#define RULE_DUPLICATE	'd'
#define RULE_REFLECT	'f'
#define RULE_SUBSTITUTE	's'
#define RULE_MATCH	'/'
#define RULE_NOT	'!'
#define RULE_LT		'<'
#define RULE_GT		'>'
#define RULE_EXTRACT	'x'
#define RULE_OVERSTRIKE	'o'
#define RULE_INSERT	'i'
#define RULE_EQUALS	'='
#define RULE_PURGE	'@'
#define RULE_CLASS	'?'	/* class rule? socialist ethic in cracker? */
E 6
I 6
#define RULE_NOOP	':'	/* Do nothing */
#define RULE_PREPEND	'^'	/* ^N = Prepend N to string */
#define RULE_APPEND	'$'	/* $N = Append N to string */
#define RULE_REVERSE	'r'	/* Reverse the string */
#define RULE_UPPERCASE	'u'	/* Make string upper case */
#define RULE_LOWERCASE	'l'	/* Make string lower case */
#define RULE_PLURALISE	'p'	/* Add plural suffix */
#define RULE_CAPITALISE	'c'	/* Capitalise first char of word */
#define RULE_DUPLICATE	'd'	/* Append duplicate of string */
#define RULE_REFLECT	'f'	/* string = stringgnirts */
#define RULE_SUBSTITUTE	's'	/* sON = replace O with N */
				/* s?CN = replace chars in class C with N */
#define RULE_MATCH	'/'	/* /O = find char O */
				/* /?C = find char class C */
#define RULE_NOT	'!'	/* !O = find not char O */
				/* !?C = find not class C */
#define RULE_LT		'<'	/* <N = string length < N? */
#define RULE_GT		'>'	/* >N = string length > N? */
#define RULE_EXTRACT	'x'	/* xSL = extract L chars from string[S+1] */
#define RULE_OVERSTRIKE	'o'	/* oXN = Replace string[X] with N */
#define RULE_INSERT	'i'	/* iXSTR = insert X chars of STR... */
#define RULE_EQUALS	'='	/* =XN = if next X chars == N */
				/* =X?C = if next X chars in class C */
#define RULE_PURGE	'@'	/* @O = Remove occurances of char O */
				/* @?C = Remove all chars in class C */
#define RULE_CLASS	'?'	/* Trigger use of class rule syntax */
				/* class rule? socialist ethic in cracker? */
E 6

D 6
#define RULE_DFIRST	'['
#define RULE_DLAST	']'
#define RULE_MFIRST	'('
#define RULE_MLAST	')'
E 6
I 6
#define RULE_DFIRST	'['	/* Delete first character */
#define RULE_DLAST	']'	/* Delete last character */
#define RULE_MFIRST	'('	/* (O = string[0] == O? */
				/* (?C = string[0] in class C? */
#define RULE_MLAST	')'	/* )O = string[end] == O? */
				/* )?C = string[end] in class C? */
#define RULE_RESTART	'*'	/* Discard changes */
#define RULE_SNIP	'\''	/* 'N = string[N] = 0 */
#define RULE_ATLEAST	'%'	/* %NX = At least N of X in string? */
				/* %N?C = At least N of class C in string? */
E 6

I 4
D 5
int	cracklib_rules_debug = 0;
E 5
I 5
int	Rules_Debug = 0;		/* Debugging switch */
E 5

I 5
/*
 * Debug - print debug messages
 */
E 5
static void
D 5
Debug(val, a, b, c, d, e, f, g)
    int val;
E 5
I 5
Debug(a, b, c, d, e, f, g)
E 5
    char *a, *b, *c, *d, *e, *f, *g;
{
D 5
    if (cracklib_rules_debug > val)
	fprintf(stderr, a, b, c, d, e, f);
E 5
I 5
    if (Rules_Debug)
	(void) fprintf(stderr, a, b, c, d, e, f);
E 5
}

I 5
/*
 * Suffix - Check if <myword> ends in <suffix>
 */
E 5
E 4
int
Suffix(myword, suffix)
    char *myword;
    char *suffix;
{
    register int i;
    register int j;
    i = strlen(myword);
    j = strlen(suffix);

    if (i > j)
    {
	return (STRCMP((myword + i - j), suffix));
    } else
    {
	return (-1);
    }
}

I 5
/*
 * Reverse - invert character order in string
 */
E 5
char *
D 5
Reverse(str)			/* return a pointer to a reversal */
E 5
I 5
Reverse(str)
E 5
    register char *str;
{
    register int i;
    register int j;
    static char area[STRINGSIZE];
    j = i = strlen(str);
    while (*str)
    {
	area[--i] = *str++;
    }
    area[j] = '\0';
    return (area);
}

I 5
/*
 * Uppercase - convert alphas to upper case
 */
E 5
char *
D 5
Uppercase(str)			/* return a pointer to an uppercase */
E 5
I 5
Uppercase(str)
E 5
    register char *str;
{
    register char *ptr;
    static char area[STRINGSIZE];
    ptr = area;
    while (*str)
    {
	*(ptr++) = CRACK_TOUPPER(*str);
	str++;
    }
    *ptr = '\0';

    return (area);
}

I 5
/*
 * Lowercase - convert alphas to lower case
 */
E 5
char *
D 5
Lowercase(str)			/* return a pointer to an lowercase */
E 5
I 5
Lowercase(str)
E 5
    register char *str;
{
    register char *ptr;
    static char area[STRINGSIZE];
    ptr = area;
    while (*str)
    {
	*(ptr++) = CRACK_TOLOWER(*str);
	str++;
    }
    *ptr = '\0';

    return (area);
}

I 5
/*
 * Capitalise - convert string to lower case, make first char upper case
 */
E 5
char *
D 5
Capitalise(str)			/* return a pointer to an capitalised */
E 5
I 5
Capitalise(str)
E 5
    register char *str;
{
    register char *ptr;
    static char area[STRINGSIZE];
    ptr = area;

    while (*str)
    {
	*(ptr++) = CRACK_TOLOWER(*str);
	str++;
    }

    *ptr = '\0';
    area[0] = CRACK_TOUPPER(area[0]);
    return (area);
}

I 5
/*
 * Pluralise - try to make a word into a plural
 *	This works only for English
 */
E 5
char *
Pluralise(string)		/* returns a pointer to a plural */
    register char *string;
{
    register int length;
    static char area[STRINGSIZE];
    length = strlen(string);
D 5
    strcpy(area, string);
E 5
I 5
    (void) strcpy(area, string);
E 5

    if (!Suffix(string, "ch") ||
	!Suffix(string, "ex") ||
	!Suffix(string, "ix") ||
	!Suffix(string, "sh") ||
	!Suffix(string, "ss"))
    {
	/* bench -> benches */
D 5
	strcat(area, "es");
E 5
I 5
	(void) strcat(area, "es");
E 5
    } else if (length > 2 && string[length - 1] == 'y')
    {
	if (strchr("aeiou", string[length - 2]))
	{
	    /* alloy -> alloys */
D 5
	    strcat(area, "s");
E 5
I 5
	    (void) strcat(area, "s");
E 5
	} else
	{
	    /* gully -> gullies */
D 5
	    strcpy(area + length - 1, "ies");
E 5
I 5
	    (void) strcpy(area + length - 1, "ies");
E 5
	}
    } else if (string[length - 1] == 's')
    {
	/* bias -> biases */
D 5
	strcat(area, "es");
E 5
I 5
	(void) strcat(area, "es");
E 5
    } else
    {
	/* catchall */
D 5
	strcat(area, "s");
E 5
I 5
	(void) strcat(area, "s");
E 5
    }

    return (area);
}

I 5
/*
 * Substitute - transliterate <old> to <new> in <string>
 */
E 5
char *
D 5
Substitute(string, old, new)	/* returns pointer to a swapped about copy */
E 5
I 5
Substitute(string, old, new)
E 5
    register char *string;
    register char old;
    register char new;
{
    register char *ptr;
    static char area[STRINGSIZE];
    ptr = area;
    while (*string)
    {
	*(ptr++) = (*string == old ? new : *string);
	string++;
    }
    *ptr = '\0';
    return (area);
}

I 5
/*
 * Purge - remote <target> from <string>
 */
E 5
char *
Purge(string, target)		/* returns pointer to a purged copy */
    register char *string;
    register char target;
{
    register char *ptr;
    static char area[STRINGSIZE];
    ptr = area;
    while (*string)
    {
	if (*string != target)
	{
	    *(ptr++) = *string;
	}
	string++;
    }
    *ptr = '\0';
    return (area);
}
I 5

E 5
/* -------- CHARACTER CLASSES START HERE -------- */

/*
I 6
 * These class definitions are not used in the code, but
 * are provided as documentation.
 * Either upper or lower case is accepted.
 */
#define	CC_QUOTE	'?'	/* Quote the ? char */
#define	CC_VOWELS	'v'	/* English vowels */
#define	CC_CONSONANTS	'c'	/* English consonants */
#define	CC_WHITESPACE	'w'	/* Tab and space */
#define	CC_PUNCTUATION	'p'	/* Punctuation chars */
#define	CC_SYMBOLS	's'	/* Special symbols */
#define	CC_LOWER	'l'	/* Lower case alpha */
#define	CC_UPPER	'u'	/* Upper case alpha */
#define	CC_ALPHA	'a'	/* Alphas */
#define	CC_ALPHANUM	'x'	/* Alphanumerics */
#define	CC_DIGIT	'd'	/* Digits */

/*
 * Locale dependant strings
 *
 * These can be changed or #ifdef for languagues other than English
 * or character sets other than US ASCII.  These would be in 
 * a messages catalog for a international version.
 */
#define	CONSONANTS	"bcdfghjklmnpqrstvwxyz"
#define	VOWELS		"aeiou"
D 7
#define	SYMBOLS		"$%%^&*()-_+=|\\[]{}#@/~"
E 7
I 7
#define	SYMBOLS		"$%^&*()-_+=|\\[]{}#@/~"
E 7
#define	PUNCTUATION	".`,:;'!?\""

/*
E 6
D 5
 * this function takes two inputs, a class identifier and a character, and
 * returns non-null if the given character is a member of the class, based
 * upon restrictions set out below
E 5
I 5
 * MatchClass - check if <input> is a member of <class>
E 5
 */
D 5

E 5
int
MatchClass(class, input)
    register char class;
    register char input;
{
    register char c;
    register int retval;
    retval = 0;

    switch (class)
    {
	/* ESCAPE */

    case '?':			/* ?? -> ? */
	if (input == '?')
	{
	    retval = 1;
	}
	break;

	/* ILLOGICAL GROUPINGS (ie: not in ctype.h) */

    case 'V':
    case 'v':			/* vowels */
	c = CRACK_TOLOWER(input);
D 6
	if (strchr("aeiou", c))
E 6
I 6
	if (strchr(VOWELS, c))
E 6
	{
	    retval = 1;
	}
	break;

    case 'C':
    case 'c':			/* consonants */
	c = CRACK_TOLOWER(input);
D 6
	if (strchr("bcdfghjklmnpqrstvwxyz", c))
E 6
I 6
	if (strchr(CONSONANTS, c))
E 6
	{
	    retval = 1;
	}
	break;

    case 'W':
    case 'w':			/* whitespace */
	if (strchr("\t ", input))
	{
	    retval = 1;
	}
	break;

    case 'P':
    case 'p':			/* punctuation */
D 6
	if (strchr(".`,:;'!?\"", input))
E 6
I 6
	if (strchr(PUNCTUATION, input))
E 6
	{
	    retval = 1;
	}
	break;

    case 'S':
    case 's':			/* symbols */
D 6
	if (strchr("$%%^&*()-_+=|\\[]{}#@/~", input))
E 6
I 6
	if (strchr(SYMBOLS, input))
E 6
	{
	    retval = 1;
	}
	break;

	/* LOGICAL GROUPINGS */

    case 'L':
    case 'l':			/* lowercase */
	if (islower(input))
	{
	    retval = 1;
	}
	break;

    case 'U':
    case 'u':			/* uppercase */
	if (isupper(input))
	{
	    retval = 1;
	}
	break;

    case 'A':
    case 'a':			/* alphabetic */
	if (isalpha(input))
	{
	    retval = 1;
	}
	break;

    case 'X':
    case 'x':			/* alphanumeric */
	if (isalnum(input))
	{
	    retval = 1;
	}
	break;

    case 'D':
    case 'd':			/* digits */
	if (isdigit(input))
	{
	    retval = 1;
	}
	break;

    default:
D 5
	Debug(1, "MatchClass: unknown class %c\n", class);
E 5
I 5
	Debug("MatchClass: unknown class %c\n", class);
E 5
	return (0);
	break;
    }

    if (isupper(class))
    {
	return (!retval);
    }
    return (retval);
}

I 5
/*
 * PolyStrchr - find if any chars of <class> are in <string>
 */
E 5
char *
PolyStrchr(string, class)
    register char *string;
    register char class;
{
    while (*string)
    {
	if (MatchClass(class, *string))
	{
	    return (string);
	}
	string++;
    }
    return ((char *) 0);
}

I 5
/*
 * PolySubst - replace all chars in <string> that are of <class> with <new>
 */
E 5
char *
D 5
PolySubst(string, class, new)	/* returns pointer to a swapped about copy */
E 5
I 5
PolySubst(string, class, new)
E 5
    register char *string;
    register char class;
    register char new;
{
    register char *ptr;
    static char area[STRINGSIZE];
    ptr = area;
    while (*string)
    {
	*(ptr++) = (MatchClass(class, *string) ? new : *string);
	string++;
    }
    *ptr = '\0';
    return (area);
}

I 5
/*
 * PolyPurge - removed all chars in <string> that are of <class>
 */
E 5
char *
D 5
PolyPurge(string, class)	/* returns pointer to a purged copy */
E 5
I 5
PolyPurge(string, class)
E 5
    register char *string;
    register char class;
{
    register char *ptr;
    static char area[STRINGSIZE];
    ptr = area;
    while (*string)
    {
	if (!MatchClass(class, *string))
	{
	    *(ptr++) = *string;
	}
	string++;
    }
    *ptr = '\0';
    return (area);
}
/* -------- BACK TO NORMALITY -------- */

I 5
/*
 * Char2Int - convert character to numeric equivilant
 */
E 5
int
Char2Int(character)
    char character;
{
    if (isdigit(character))
    {
	return (character - '0');
    } else if (islower(character))
    {
	return (character - 'a' + 10);
    } else if (isupper(character))
    {
	return (character - 'A' + 10);
    }
    return (-1);
}

I 5
/*
 * Mangle - permutate <input> according to <control>
 */
E 5
char *
D 5
Mangle(input, control)		/* returns a pointer to a controlled Mangle */
E 5
I 5
Mangle(input, control)
E 5
    char *input;
    char *control;
{
    int limit;
    register char *ptr;
    static char area[STRINGSIZE];
    char area2[STRINGSIZE];
    area[0] = '\0';
D 5
    strcpy(area, input);
E 5
I 5
    (void) strcpy(area, input);
E 5

    for (ptr = control; *ptr; ptr++)
    {
	switch (*ptr)
	{
	case RULE_NOOP:
	    break;
I 6
	case RULE_RESTART:
	    (void) strcpy(area, input);
	    break;
E 6
	case RULE_REVERSE:
D 5
	    strcpy(area, Reverse(area));
E 5
I 5
	    (void) strcpy(area, Reverse(area));
E 5
	    break;
	case RULE_UPPERCASE:
D 5
	    strcpy(area, Uppercase(area));
E 5
I 5
	    (void) strcpy(area, Uppercase(area));
E 5
	    break;
	case RULE_LOWERCASE:
D 5
	    strcpy(area, Lowercase(area));
E 5
I 5
	    (void) strcpy(area, Lowercase(area));
E 5
	    break;
	case RULE_CAPITALISE:
D 5
	    strcpy(area, Capitalise(area));
E 5
I 5
	    (void) strcpy(area, Capitalise(area));
E 5
	    break;
	case RULE_PLURALISE:
D 5
	    strcpy(area, Pluralise(area));
E 5
I 5
	    (void) strcpy(area, Pluralise(area));
E 5
	    break;
	case RULE_REFLECT:
D 5
	    strcat(area, Reverse(area));
E 5
I 5
	    (void) strcat(area, Reverse(area));
E 5
	    break;
	case RULE_DUPLICATE:
D 5
	    strcpy(area2, area);
	    strcat(area, area2);
E 5
I 5
	    (void) strcpy(area2, area);
	    (void) strcat(area, area2);
E 5
	    break;
I 6
	case RULE_SNIP:
	    if (!ptr[1])
	    {
		Debug("Mangle: <SNIP> missing argument in '%s'\n", control);
		return ((char *) 0);
	    }
	    else
	    {
		limit = Char2Int(*(++ptr));
		if (limit < 0)
		{
		    Debug("Mangle: '>' weird argument in '%s'\n", control);
		    return ((char *) 0);
		}
		area[limit] = '\0';
	    }
	    break;
E 6
	case RULE_GT:
	    if (!ptr[1])
	    {
D 5
		Debug(1, "Mangle: '>' missing argument in '%s'\n", control);
E 5
I 5
		Debug("Mangle: '>' missing argument in '%s'\n", control);
E 5
		return ((char *) 0);
	    } else
	    {
		limit = Char2Int(*(++ptr));
		if (limit < 0)
		{
D 5
		    Debug(1, "Mangle: '>' weird argument in '%s'\n", control);
E 5
I 5
		    Debug("Mangle: '>' weird argument in '%s'\n", control);
E 5
		    return ((char *) 0);
		}
		if (strlen(area) <= limit)
		{
		    return ((char *) 0);
		}
	    }
	    break;
	case RULE_LT:
	    if (!ptr[1])
	    {
D 5
		Debug(1, "Mangle: '<' missing argument in '%s'\n", control);
E 5
I 5
		Debug("Mangle: '<' missing argument in '%s'\n", control);
E 5
		return ((char *) 0);
	    } else
	    {
		limit = Char2Int(*(++ptr));
		if (limit < 0)
		{
D 5
		    Debug(1, "Mangle: '<' weird argument in '%s'\n", control);
E 5
I 5
		    Debug("Mangle: '<' weird argument in '%s'\n", control);
E 5
		    return ((char *) 0);
		}
		if (strlen(area) >= limit)
		{
		    return ((char *) 0);
		}
	    }
	    break;
	case RULE_PREPEND:
	    if (!ptr[1])
	    {
D 5
		Debug(1, "Mangle: prepend missing argument in '%s'\n", control);
E 5
I 5
		Debug("Mangle: prepend missing argument in '%s'\n", control);
E 5
		return ((char *) 0);
	    } else
	    {
		area2[0] = *(++ptr);
D 5
		strcpy(area2 + 1, area);
		strcpy(area, area2);
E 5
I 5
		(void) strcpy(area2 + 1, area);
		(void) strcpy(area, area2);
E 5
	    }
	    break;
	case RULE_APPEND:
	    if (!ptr[1])
	    {
D 5
		Debug(1, "Mangle: append missing argument in '%s'\n", control);
E 5
I 5
		Debug("Mangle: append missing argument in '%s'\n", control);
E 5
		return ((char *) 0);
	    } else
	    {
		register char *string;
		string = area;
		while (*(string++));
		string[-1] = *(++ptr);
		*string = '\0';
	    }
	    break;
	case RULE_EXTRACT:
	    if (!ptr[1] || !ptr[2])
	    {
D 5
		Debug(1, "Mangle: extract missing argument in '%s'\n", control);
E 5
I 5
		Debug("Mangle: extract missing argument in '%s'\n", control);
E 5
		return ((char *) 0);
	    } else
	    {
		register int i;
		int start;
		int length;
		start = Char2Int(*(++ptr));
		length = Char2Int(*(++ptr));
		if (start < 0 || length < 0)
		{
D 5
		    Debug(1, "Mangle: extract: weird argument in '%s'\n", control);
E 5
I 5
		    Debug("Mangle: extract: weird argument in '%s'\n", control);
E 5
		    return ((char *) 0);
		}
D 5
		strcpy(area2, area);
E 5
I 5
		(void) strcpy(area2, area);
E 5
		for (i = 0; length-- && area2[start + i]; i++)
		{
		    area[i] = area2[start + i];
		}
		/* cant use strncpy() - no trailing NUL */
		area[i] = '\0';
	    }
	    break;
	case RULE_OVERSTRIKE:
	    if (!ptr[1] || !ptr[2])
	    {
D 5
		Debug(1, "Mangle: overstrike missing argument in '%s'\n", control);
E 5
I 5
		Debug("Mangle: overstrike missing argument in '%s'\n", control);
E 5
		return ((char *) 0);
	    } else
	    {
		register int i;
		i = Char2Int(*(++ptr));
		if (i < 0)
		{
D 5
		    Debug(1, "Mangle: overstrike weird argument in '%s'\n",
E 5
I 5
		    Debug("Mangle: overstrike weird argument in '%s'\n",
E 5
			  control);
		    return ((char *) 0);
		} else
		{
		    ++ptr;
		    if (area[i])
		    {
			area[i] = *ptr;
		    }
		}
	    }
	    break;
	case RULE_INSERT:
	    if (!ptr[1] || !ptr[2])
	    {
D 5
		Debug(1, "Mangle: insert missing argument in '%s'\n", control);
E 5
I 5
		Debug("Mangle: insert missing argument in '%s'\n", control);
E 5
		return ((char *) 0);
	    } else
	    {
		register int i;
		register char *p1;
		register char *p2;
		i = Char2Int(*(++ptr));
		if (i < 0)
		{
D 5
		    Debug(1, "Mangle: insert weird argument in '%s'\n",
E 5
I 5
		    Debug("Mangle: insert weird argument in '%s'\n",
E 5
			  control);
		    return ((char *) 0);
		}
		p1 = area;
		p2 = area2;
		while (i && *p1)
		{
		    i--;
		    *(p2++) = *(p1++);
		}
		*(p2++) = *(++ptr);
D 5
		strcpy(p2, p1);
		strcpy(area, area2);
E 5
I 5
		(void) strcpy(p2, p1);
		(void) strcpy(area, area2);
E 5
	    }
	    break;
	    /* THE FOLLOWING RULES REQUIRE CLASS MATCHING */

	case RULE_PURGE:	/* @x or @?c */
	    if (!ptr[1] || (ptr[1] == RULE_CLASS && !ptr[2]))
	    {
D 5
		Debug(1, "Mangle: delete missing arguments in '%s'\n", control);
E 5
I 5
		Debug("Mangle: delete missing arguments in '%s'\n", control);
E 5
		return ((char *) 0);
	    } else if (ptr[1] != RULE_CLASS)
	    {
D 5
		strcpy(area, Purge(area, *(++ptr)));
E 5
I 5
		(void) strcpy(area, Purge(area, *(++ptr)));
E 5
	    } else
	    {
D 5
		strcpy(area, PolyPurge(area, ptr[2]));
E 5
I 5
		(void) strcpy(area, PolyPurge(area, ptr[2]));
E 5
		ptr += 2;
	    }
	    break;
	case RULE_SUBSTITUTE:	/* sxy || s?cy */
	    if (!ptr[1] || !ptr[2] || (ptr[1] == RULE_CLASS && !ptr[3]))
	    {
D 5
		Debug(1, "Mangle: subst missing argument in '%s'\n", control);
E 5
I 5
		Debug("Mangle: subst missing argument in '%s'\n", control);
E 5
		return ((char *) 0);
	    } else if (ptr[1] != RULE_CLASS)
	    {
D 5
		strcpy(area, Substitute(area, ptr[1], ptr[2]));
E 5
I 5
		(void) strcpy(area, Substitute(area, ptr[1], ptr[2]));
E 5
		ptr += 2;
	    } else
	    {
D 5
		strcpy(area, PolySubst(area, ptr[2], ptr[3]));
E 5
I 5
		(void) strcpy(area, PolySubst(area, ptr[2], ptr[3]));
E 5
		ptr += 3;
	    }
	    break;
	case RULE_MATCH:	/* /x || /?c */
	    if (!ptr[1] || (ptr[1] == RULE_CLASS && !ptr[2]))
	    {
D 5
		Debug(1, "Mangle: '/' missing argument in '%s'\n", control);
E 5
I 5
		Debug("Mangle: '/' missing argument in '%s'\n", control);
E 5
		return ((char *) 0);
	    } else if (ptr[1] != RULE_CLASS)
	    {
		if (!strchr(area, *(++ptr)))
		{
		    return ((char *) 0);
		}
	    } else
	    {
		if (!PolyStrchr(area, ptr[2]))
		{
		    return ((char *) 0);
		}
		ptr += 2;
	    }
	    break;
	case RULE_NOT:		/* !x || !?c */
	    if (!ptr[1] || (ptr[1] == RULE_CLASS && !ptr[2]))
	    {
D 5
		Debug(1, "Mangle: '!' missing argument in '%s'\n", control);
E 5
I 5
		Debug("Mangle: '!' missing argument in '%s'\n", control);
E 5
		return ((char *) 0);
	    } else if (ptr[1] != RULE_CLASS)
	    {
		if (strchr(area, *(++ptr)))
		{
		    return ((char *) 0);
		}
	    } else
	    {
		if (PolyStrchr(area, ptr[2]))
		{
		    return ((char *) 0);
		}
		ptr += 2;
	    }
	    break;
	    /*
	     * alternative use for a boomerang, number 1: a standard throwing
	     * boomerang is an ideal thing to use to tuck the sheets under
	     * the mattress when making your bed.  The streamlined shape of
	     * the boomerang allows it to slip easily 'twixt mattress and
	     * bedframe, and it's curve makes it very easy to hook sheets
	     * into the gap.
	     */

	case RULE_EQUALS:	/* =nx || =n?c */
	    if (!ptr[1] || !ptr[2] || (ptr[2] == RULE_CLASS && !ptr[3]))
	    {
D 5
		Debug(1, "Mangle: '=' missing argument in '%s'\n", control);
E 5
I 5
		Debug("Mangle: '=' missing argument in '%s'\n", control);
E 5
		return ((char *) 0);
	    } else
	    {
		register int i;
		if ((i = Char2Int(ptr[1])) < 0)
		{
D 5
		    Debug(1, "Mangle: '=' weird argument in '%s'\n", control);
E 5
I 5
		    Debug("Mangle: '=' weird argument in '%s'\n", control);
E 5
		    return ((char *) 0);
		}
		if (ptr[2] != RULE_CLASS)
		{
		    ptr += 2;
		    if (area[i] != *ptr)
		    {
			return ((char *) 0);
		    }
		} else
		{
		    ptr += 3;
		    if (!MatchClass(*ptr, area[i]))
		    {
			return ((char *) 0);
I 6
		    }
		}
	    }
	    break;

	case RULE_ATLEAST:	/* %nx || %n?c */
	    if (!ptr[1] || !ptr[2] || (ptr[2] == RULE_CLASS && !ptr[3]))
	    {
		Debug(1, "Mangle: '%%' missing argument in '%s'\n", control);
		return ((char *) 0);
	    }
	    else
	    {
		int i;

		if ((i = Char2Int(ptr[1])) < 0)
		{
		    Debug(1, "Mangle: '%%' weird argument in '%s'\n", control);
		    return ((char *) 0);
		}

		if (ptr[2] != RULE_CLASS)
		{
		    int j, k;

		    k = 0;
		    ptr += 2;

		    for (j = 0; area[j]; j++)
		    {
			if (area[j] == *ptr)
			{
			    k++;
			}
		    }
		    if (k < i)
		    {
			return ((char *) 0);
		    }
		}
		else
		{
		    int j, k;

		    k = 0;
		    ptr += 3;

		    for (j = 0; area[j]; j++)
		    {
			if (MatchClass(*ptr, area[j]))
			{
			    k++;
			}
		    }
		    if (k < i)
		    {
			return ((char *) 0);
E 6
		    }
		}
	    }
	    break;

	case RULE_DFIRST:
	    if (area[0])
	    {
		register int i;
		for (i = 1; area[i]; i++)
		{
		    area[i - 1] = area[i];
		}
		area[i - 1] = '\0';
	    }
	    break;

	case RULE_DLAST:
	    if (area[0])
	    {
		register int i;
		for (i = 1; area[i]; i++);
		area[i - 1] = '\0';
	    }
	    break;

	case RULE_MFIRST:
	    if (!ptr[1] || (ptr[1] == RULE_CLASS && !ptr[2]))
	    {
D 5
		Debug(1, "Mangle: '(' missing argument in '%s'\n", control);
E 5
I 5
		Debug("Mangle: '(' missing argument in '%s'\n", control);
E 5
		return ((char *) 0);
	    } else
	    {
		if (ptr[1] != RULE_CLASS)
		{
		    ptr++;
		    if (area[0] != *ptr)
		    {
			return ((char *) 0);
		    }
		} else
		{
		    ptr += 2;
		    if (!MatchClass(*ptr, area[0]))
		    {
			return ((char *) 0);
		    }
		}
	    }
	case RULE_MLAST:
	    if (!ptr[1] || (ptr[1] == RULE_CLASS && !ptr[2]))
	    {
D 5
		Debug(1, "Mangle: ')' missing argument in '%s'\n", control);
E 5
I 5
		Debug("Mangle: ')' missing argument in '%s'\n", control);
E 5
		return ((char *) 0);
	    } else
	    {
		register int i;

		for (i = 0; area[i]; i++);

		if (i > 0)
		{
		    i--;
		} else
		{
		    return ((char *) 0);
		}

		if (ptr[1] != RULE_CLASS)
		{
		    ptr++;
		    if (area[i] != *ptr)
		    {
			return ((char *) 0);
		    }
		} else
		{
		    ptr += 2;
		    if (!MatchClass(*ptr, area[i]))
		    {
			return ((char *) 0);
		    }
		}
	    }

	default:
D 5
	    Debug(1, "Mangle: unknown command %c in %s\n", *ptr, control);
E 5
I 5
	    Debug("Mangle: unknown command %c in %s\n", *ptr, control);
E 5
	    return ((char *) 0);
	    break;
	}
    }
    if (!area[0])		/* have we deweted de poor widdle fing away? */
    {
	return ((char *) 0);
    }
    return (area);
}

I 5
/*
 * PMatch - class-driven string compare
 */
E 5
int
D 7
PMatch(control, string)
E 7
I 7
PMatch(control, string, initial)
E 7
D 5
register char *control;
register char *string;
E 5
I 5
    register char *control;
    register char *string;
I 7
    int initial;
E 7
E 5
{
    while (*string && *control)
    {
    	if (!MatchClass(*control, *string))
    	{
    	    return(0);
    	}

    	string++;
    	control++;
    }

D 7
    if (*string || *control)
E 7
I 7
    if ((*string || *control) && initial == 0)
E 7
    {
    	return(0);
    }

    return(1);
}
I 7

E 7
I 5
/* End %M% */
E 5
E 1
