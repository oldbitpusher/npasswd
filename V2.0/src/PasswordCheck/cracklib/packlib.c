/*
 * This program is copyright Alec Muffett 1993. The author disclaims all 
 * responsibility or liability with respect to it's usage or its effect 
 * upon hardware or computer systems, and maintains copyright as set out 
 * in the "LICENCE" document which accompanies distributions of Crack v4.0 
 * and upwards.
 */
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

#include "packer.h"

static char vers_id[] = "packlib.c : v2.3p2 Alec Muffett 18 May 1993";
static char ut_id[] = "@(#)packlib.c	1.11 9/22/98 (cc.utexas.edu)";

char	PWioError[STRINGSIZE * 2];

extern int	errno;

/*
 * PWOpen - open a hashed dictionary
 */
PWDICT *
PWOpen(prefix, mode)
    char *prefix;
    char *mode;			/* fopen() modes */
{
    c_int32 i;
    PWDICT *pdesc;
    char iname[STRINGSIZE];
    char dname[STRINGSIZE];
    char wname[STRINGSIZE];

    if (strlen(prefix) > (STRINGSIZE - 5)) {
	(void) strcpy (PWioError, "PWOpen: Path too long");
#ifdef	CRACKLIB_PERROR
	(void) fprintf (stderr, "%s\n", PWioError);
#endif
	return ((PWDICT *) 0);
    }

    if ((pdesc = (PWDICT *)malloc(sizeof(PWDICT))) == 0) {
	(void) strcpy(PWioError, "PWOpen: Cannot allocate pwdict block");
#ifdef	CRACKLIB_PERROR
	(void) fprintf(stderr, "%s\n", PWioError);
#endif
	return ((PWDICT *) 0);
    }

    (void) memset(pdesc, '\0', sizeof(*pdesc));

    (void) sprintf(iname, "%s.pwi", prefix);
    (void) sprintf(dname, "%s.pwd", prefix);
    (void) sprintf(wname, "%s.hwm", prefix);

    if (!(pdesc->dfp = fopen(dname, mode)))
    {
#ifdef	CRACKLIB_PERROR
	perror(dname);
#endif
	(void) sprintf(PWioError, "PWOpen: Error %d opening data file", errno);
	free((char *)pdesc);
	return ((PWDICT *) 0);
    }

    if (!(pdesc->ifp = fopen(iname, mode)))
    {
#ifdef	CRACKLIB_PERROR
	perror(iname);
#endif
	(void) sprintf(PWioError, "PWOpen: Error %d opening index file", errno);
	(void) fclose(pdesc->dfp);
	free((char *)pdesc);
	return ((PWDICT *) 0);
    }

    if (pdesc->wfp = fopen(wname, mode))
    {
	pdesc->flags |= PFOR_USEHWMS;
    }

    if (mode[0] == 'w')
    {
	pdesc->flags |= PFOR_WRITE;
	pdesc->header.pih_magic = PIH_MAGIC;
	pdesc->header.pih_blocklen = NUMWORDS;
	pdesc->header.pih_numwords = 0;

	(void) fwrite((char *) &pdesc->header, sizeof(pdesc->header), 1, pdesc->ifp);
    } else
    {
	pdesc->flags &= ~PFOR_WRITE;

	if (!fread((char *) &pdesc->header, sizeof(pdesc->header), 1, pdesc->ifp))
	{
	    (void) strcpy(PWioError, "PWOpen: error reading header");
#ifdef	CRACKLIB_PERROR
	    fprintf(stderr, "%s: %s\n", prefix, PWioError);
#endif
	    (void) fclose(pdesc->ifp);
	    (void) fclose(pdesc->dfp);
	    if (pdesc->flags & PFOR_USEHWMS)
		    (void) fclose(pdesc->wfp);
	    free((char *)pdesc);
	    return ((PWDICT *) 0);
	}

	if (pdesc->header.pih_magic != PIH_MAGIC)
	{
	    (void) strcpy(PWioError, "PWOpen: magic mismatch");
#ifdef	CRACKLIB_PERROR
	    (void) fprintf(stderr, "%s: %s\n", prefix, PWioError);
#endif
	    (void) fclose(pdesc->ifp);
	    (void) fclose(pdesc->dfp);
	    if (pdesc->flags & PFOR_USEHWMS)
		    (void) fclose(pdesc->wfp);
	    free((char *)pdesc);
	    return ((PWDICT *) 0);
	}

	if (pdesc->header.pih_blocklen != NUMWORDS)
	{
	    (void) strcat(PWioError, "PWOpen: size mismatch");
#ifdef	CRACKLIB_PERROR
	    (void) fprintf(stderr, "%s: %s\n", prefix, PWioError);
#endif
	    (void) fclose(pdesc->ifp);
	    (void) fclose(pdesc->dfp);
	    if (pdesc->flags & PFOR_USEHWMS)
		    (void) fclose(pdesc->wfp);
	    free((char *)pdesc);
	    return ((PWDICT *) 0);
	}

	if (pdesc->flags & PFOR_USEHWMS)
	{
	    if (fread(pdesc->hwms, 1, sizeof(pdesc->hwms), pdesc->wfp) != sizeof(pdesc->hwms))
	    {
		pdesc->flags &= ~PFOR_USEHWMS;
	    }
	}
    }
    return (pdesc);
}

/*
 * PWClose - close hashed dictionary
 */
int
PWClose(pwp)
    PWDICT *pwp;
{
    if (pwp->header.pih_magic != PIH_MAGIC)
    {
	(void) strcpy(PWioError, "PWClose: bad magic number");
#ifdef	CRACKLIB_PERROR
	(void) fprintf(stderr, "%s\n", PWioError);
#endif
	return (-1);
    }

    if (pwp->flags & PFOR_WRITE)
    {
	pwp->flags |= PFOR_FLUSH;
	(void) PutPW(pwp, (char *) 0);	/* flush last index if necess */

	if (fseek(pwp->ifp, 0L, 0))
	{
	   (void) strcpy(PWioError, "PWClose: index magic fseek failed");
#ifdef	CRACKLIB_PERROR
	   (void) fprintf(stderr, "%s\n", PWioError);
#endif
	    return (-1);
	}

	if (!fwrite((char *) &pwp->header, sizeof(pwp->header), 1, pwp->ifp))
	{
	   (void) strcpy(PWioError, "PWClose: index magic fwrite failed");
#ifdef	CRACKLIB_PERROR
	   (void) fprintf(stderr, "%s\n", PWioError);
#endif
	    return (-1);
	}

	if (pwp->flags & PFOR_USEHWMS)
	{
	    int i;
	    for (i=1; i<=0xff; i++)
	    {
	    	if (!pwp->hwms[i])
	    	{
	    	    pwp->hwms[i] = pwp->hwms[i-1];
	    	}
#ifdef	CRACKLIB_DEBUG
	    	printf("hwm[%02x] = %d\n", i, pwp->hwms[i]);
#endif
	    }
	    (void) fwrite(pwp->hwms, 1, sizeof(pwp->hwms), pwp->wfp);
	}
    }

    (void) fclose(pwp->ifp);
    (void) fclose(pwp->dfp);
    (void) fclose(pwp->wfp);

    free((char *)pwp);
    return (0);
}

/*
 * PutPW - put a string into dictionary hash files
 */
int
PutPW(pwp, string)
    PWDICT *pwp;
    char *string;
{
    if (pwp->header.pih_magic != PIH_MAGIC)
    {
	(void) strcpy(PWioError, "PutPW: bad magic number");
#ifdef	CRACKLIB_PERROR
	(void) fprintf(stderr, "%s\n", PWioError);
#endif
	return (-1);
    }

    if (!(pwp->flags & PFOR_WRITE))
    {
	return (-1);
    }

    if (string)
    {
	(void) strncpy(pwp->data[pwp->count], string, MAXWORDLEN);
	pwp->data[pwp->count][MAXWORDLEN - 1] = '\0';

	pwp->hwms[string[0] & 0xff] = pwp->header.pih_numwords;

	++(pwp->count);
	++(pwp->header.pih_numwords);

    } else if (!(pwp->flags & PFOR_FLUSH))
    {
	return (-1);
    }

    if ((pwp->flags & PFOR_FLUSH) || !(pwp->count % NUMWORDS))
    {
	int i;
	c_int32 datum;
	register char *ostr;

	datum = (c_int32) ftell(pwp->dfp);

	(void) fwrite((char *) &datum, sizeof(datum), 1, pwp->ifp);

	(void) fputs(pwp->data[0], pwp->dfp);
	(void) putc(0, pwp->dfp);

	ostr = pwp->data[0];

	for (i = 1; i < NUMWORDS; i++)
	{
	    register int j;
	    register char *nstr;
	    nstr = pwp->data[i];

	    if (nstr[0])
	    {
		for (j = 0; ostr[j] && nstr[j] && (ostr[j] == nstr[j]); j++);
		(void) putc(j & 0xff, pwp->dfp);
		(void) fputs(nstr + j, pwp->dfp);
	    }
	    (void) putc(0, pwp->dfp);

	    ostr = nstr;
	}

	(void) memset(pwp->data, '\0', sizeof(pwp->data));
	pwp->count = 0;
    }
    return (0);
}

/*
 * GetPW - fetch a word from dictionary
 */
char *
GetPW(pwp, number)
    PWDICT *pwp;
    c_int32 number;
{
    c_int32 datum;
    register int i;
    register char *ostr;
    register char *nstr;
    register char *bptr;
    char buffer[NUMWORDS * MAXWORDLEN];
    static char data[NUMWORDS][MAXWORDLEN];
    static c_int32 prevblock = 0xffffffff;
    c_int32 thisblock;

    if (pwp->header.pih_magic != PIH_MAGIC)
    {
	(void) sprintf(PWioError, "GetPW: bad magic number");
#ifdef	CRACKLIB_PERROR
	fprintf (stderr, "%s\n", PWioError);
#endif
	return ((char *) 0);
    }

    thisblock = number / NUMWORDS;

    if (prevblock == thisblock)
    {
	return (data[number % NUMWORDS]);
    }

    if (fseek(pwp->ifp, sizeof(struct pi_header) + (thisblock * sizeof(c_int32)), 0))
    {
#ifdef	CRACKLIB_PERROR
	perror("(index fseek failed)");
#endif
	(void) sprintf(PWioError, "GetPW: index seek error %d", errno);
	return ((char *) 0);
    }

    if (!fread((char *) &datum, sizeof(datum), 1, pwp->ifp))
    {
#ifdef	CRACKLIB_PERROR
	perror("GetPW (index fread failed)");
#endif
	(void) sprintf(PWioError, "GetPW: index fread error %d", errno);
	return ((char *) 0);
    }

    if (fseek(pwp->dfp, datum, 0))
    {
#ifdef	CRACKLIB_PERROR
	perror("GetPW (data fseek failed)");
#endif
	(void) sprintf(PWioError, "GetPW: data fseek error %d", errno);
	return ((char *) 0);
    }

    if (!fread(buffer, 1, sizeof(buffer), pwp->dfp))
    {
#ifdef	CRACKLIB_PERROR
	perror("GetPW (data fread failed)");
#endif
	(void) sprintf(PWioError, "GetPW: data fread error %d", errno);
	return ((char *) 0);
    }

    prevblock = thisblock;

    bptr = buffer;

    for (ostr = data[0]; *(ostr++) = *(bptr++); /* nothing */ );

    ostr = data[0];

    for (i = 1; i < NUMWORDS; i++)
    {
	nstr = data[i];
	(void) strcpy(nstr, ostr);

	ostr = nstr + *(bptr++);
	while (*(ostr++) = *(bptr++));

	ostr = nstr;
    }

    return (data[number % NUMWORDS]);
}

/*
 * FindPW - check if <string> is in dictionary <pwp>
 */
c_int32
FindPW(pwp, string)
    PWDICT *pwp;
    char *string;
{
    register c_int32 lwm;
    register c_int32 hwm;
    register c_int32 middle = 0;
    register char *this;

    if (pwp->header.pih_magic != PIH_MAGIC)
    {
	(void) strcpy(PWioError, "FindPW: bad magic number");
#ifdef	CRACKLIB_PERROR
	(void) fprintf(stderr, "%s\n", PWioError);
#endif
        return (PW_WORDS(pwp));		/* Probably bogus */
    }

    if (pwp->flags & PFOR_USEHWMS)
    {
        int idx = string[0] & 0xff;

    	lwm = idx ? pwp->hwms[idx - 1] : 0;
    	hwm = pwp->hwms[idx];
    } else
    {
    	lwm = 0;
    	hwm = PW_WORDS(pwp);
    }

#ifdef	CRACKLIB_DEBUG
    printf("---- lwm=%lu, hwm=%lu ----\n", lwm, hwm);
#endif

    for (;;)
    {
	int cmp;

#ifdef	CRACKLIB_DEBUG
	printf("lwm=%lu, hwm=%lu middle=%lu\n", lwm, hwm, middle);
#endif
	/*
	 * The cast is needed because the operands are unsigned,
	 * but the casted expression can legitimately be negative when
	 * (lwm > hwm).
	 */
	middle = lwm + (((int )(hwm - lwm) + 1) / 2);
#ifdef	CRACKLIB_DEBUG
	printf("new middle=%lu\n", middle);
#endif

	if (middle == hwm)
	{
	    break;
	}

	this = GetPW(pwp, middle);
	cmp = strcmp(string, this);

#ifdef	CRACKLIB_DEBUG
	printf("this=<%s> string=<%s> cmp=%d\n", this, string, cmp);
#endif
	if (cmp < 0)
	{
	    hwm = middle;
	} else if (cmp > 0)
	{
	    lwm = middle;
	} else
	{
	    return (middle);
	}
    }

    return (PW_WORDS(pwp));
}
/* End packlib.c */
