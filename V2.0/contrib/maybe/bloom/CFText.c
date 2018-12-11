/*----------------------------------------------------------------------------*
|                                                                             |
|                           Author: Donald Olivier                            |
|                      Instructional Computing Facility                       |
|                      Harvard School of Public Health                        |
|                            677 Huntington Ave.                              |
|                             Boston, MA 02115                                |
|                           don@hsph.harvard.edu                              |
|                                                                             |
|    This code may be distributed freely, provided this notice is retained.   |
|                                                                             |
*----------------------------------------------------------------------------*/

/* #define DB */
/* #define DB1 */
/* #define DB2 */
/*
CFText.c
Iterator for CrackFilter entries derived from text
(meant for gecos field and "dotfiles")
*/

#include <string.h>
#include "Global.h"
#include "CFStr.h"
#include "CFText.h"

/*
GLOBAL
CFText: the iterator

LOCAL
textFix:     Prepare the text
textCurrent: Return the current string
textStep:    Move pointer to next string
textSingle:  Return strings, one at a time
textPair:    Return string pairs, one at a time
textCombine: Return single strings and string pairs combined
       into single words (the way Crack combines them)
*/

static void textFix();
                /* void textFix(char* s, struct textIter * ti) */
static char* textCurrent();
                /* char* textCurrent(struct textIter * ti) */
static void textStep();
                /* void textStep(struct textIter * ti) */
static void textSingle();
                /* void textSingle(struct textIter * ti, char**) */
static void textPair();
                /* void textPair(struct textIter * ti, char**, char**) */
static char* textCombine();
		/* char* textCombine(struct textIter * ti) */

/*
CFText
Iterator
*/

char*
CFText(s)
char* s;
{
    static char text[MAXTEXT + 1];
    static char buf[MAXSTRING + 1];
    struct textIter ti;
    static int state;                   /* 0=single 1=pairs */
    char* p;

    /*
    Initialization
    */

    if (s) {
        strncpy(text, s, MAXTEXT);
        text[MAXTEXT] = '\0';
        textFix(text, &ti);
	textCombine(ti);
        CFStrI(textCombine);
        return 0;
    }

    /*
    Iteration
    */

    p = CFStrI(0);
#   ifdef DB
    printf("\t%s", p);
#   endif DB
    return p;
}

/*
textFix
Modify text (a null-terminated string) to make it suitable for textString:
    convert all non-alphanumerics to null characters
Truncate long strings
Fill in a textiter structure
*/

static void
textFix(s, ti)
char* s;
struct textIter * ti;
{
    char* p;
    int len;

    len = 0;
    for (p = s; *p; p++) {
        if (isalnum(*p)) {
	    if (++len > MAXSTRING)
		*p = '\0';
	}
	else {
            *p = '\0';
	    len = 0;
	}
    }

    ti->text = s;
    ti->slimit = p;
    ti->p = s;
}

/*
textCurrent and textNext expect the text to be alphanumerics and null
    characters, with a null character following

The pointers are external so you can run two of them concurrently
*/

/*
textCurrent
Returns a pointer to the current alphanumeric strings in text, possibly
    skipping over leading null characters, or 0 if there's nothing left
*/

static char*
textCurrent(ti)
struct textIter * ti;
{
    char* p;

    for (p = ti->p; p < ti->slimit && *p == '\0'; p++) ;
                                                /* skip leading nulls */
    if (p == ti->slimit)
        return 0;
    else
        return p;
}

/*
textStep
Moves the pointer to the next alphanumeric string
*/

static void
textStep(ti)
struct textIter * ti;
{
    char* sl;
    char* p;

    sl = ti->slimit;
    p = ti->p;

    while (p < sl && *p == '\0') p++;           /* skip leading nulls */
    while (p < sl && *p != '\0') p++;           /* skip current string */
    while (p < sl && *p == '\0') p++;           /* skip trailing nulls */

    ti->p = p;
    return;
}

/*
textSingle
Returns pointers to alphanumeric strings from text, one at a time
(If ti is nonnull, initializes)
(This routine is a butchered copy of textPair, which is why the style
is funny)
*/

static void
textSingle(ti, pp)
struct textIter * ti;
char** pp;
{
    static struct textIter tj;

    if (ti) {
        tj.text = ti->text; tj.slimit = ti->slimit; tj.p = ti->text;
        return;
    }

    *pp = textCurrent(&tj);
    if (*pp)
        textStep(&tj);
}

/*
textPair
Returns pointers to pairs of alphanumeric strings from text, one at a time
(If ti is nonnull, initializes)
*/

static void
textPair(ti, pp, qq)
struct textIter * ti;
char** pp;
char** qq;
{
    static struct textIter tj;
    static struct textIter tk;

    if (ti) {
        tj.text = ti->text; tj.slimit = ti->slimit; tj.p = ti->text;
        tk.text = ti->text; tk.slimit = ti->slimit; tk.p = ti->text;
        return;
    }

    *pp = textCurrent(&tj);
    *qq = textCurrent(&tk);
    if (!*qq) {
        textStep(&tj);
	*pp = textCurrent(&tj);
        tk.p = tk.text;
	*qq = textCurrent(&tk);
	if (tj.p >= tj.slimit) {
            *pp = *qq = 0;
            return;
        }
    }
    textStep(&tk);
#ifdef DB2
	printf("%s %s\n", *pp, *qq);
#endif DB2
}

/*
textCombine
Returns single strings and string pairs combined into single words
    (the way Crack combines them)
(If ti is nonnull, initializes)
*/

static char*
textCombine(ti)
struct textIter * ti;
{
    static enum state_enum {
	INITIAL,
        ab,
        aB,
        Iab,
        IaB,
        aIb,
        FINAL
    } state;
    static char buf[MAXSTRING + 1];
    static char* p;
    static char* q;
    static int lenp;
    static int lenq;
    int done;

    /*
    Initialization
    */

    if (ti) {
        buf[MAXSTRING] = '\0';
	textPair(ti, 0, 0);
	state = INITIAL;
        return 0;
    }

    /*
    Iteration
    */

    for (done = 0; !done; state++) {	/* loop through states until   */
        switch (state) {		/* there's something to return */
	    case FINAL:
		state = INITIAL;
		/* fall through */
	    
	    case INITIAL:
		textPair(0, &p, &q);
		if (!p)
		    return 0;
		if (p == q) {	    /* on the diagonal, return single string */
		    strcpy(buf, p);
		    break;
		}
		lenp = strlen(p);
		lenq = strlen(q);
		state = ab;
		/* fall through */

            case ab:
		if (lenp <= MAXSTRING - 2) {
		    strcpy(buf, p);
		    strncat(buf, q, MAXSTRING - lenp);
		    buf[lenp + lenq] = '\0';
		    done = 1;
		}
		break;

            case aB:
		if (lenp <= MAXSTRING - 2 && islower(q[0])) {
		    strcpy(buf, p);
		    strncat(buf, q, MAXSTRING - lenp);
		    buf[lenp] = toupper(buf[lenp]);
		    buf[lenp + lenq] = '\0';
		    done = 1;
		}
                break;

            case Iab:
		buf[0] = p[0];
		strncpy(buf + 1, q, MAXSTRING - 1);
		buf[1 + lenq] = '\0';
		done = 1;

            case IaB:
                if (islower(q[0])) {
		    buf[0] = p[0];
		    strncpy(buf + 1, q, MAXSTRING - 1);
		    buf[1] = toupper(buf[1]);
		    buf[1 + lenq] = '\0';
		    done = 1;
                }
                break;

            case aIb:
                if (lenp <= MAXSTRING - 1) {
                    strcpy(buf, p);
                    buf[lenp] = q[0];
                    buf[lenp + 1] = '\0';
                    done = 1;
                }
                break;

	    default:
		CantHappen();
        }
    }

    return buf;
}
