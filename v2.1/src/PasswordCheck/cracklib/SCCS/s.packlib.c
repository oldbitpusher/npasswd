h02093
s 00012/00012/00489
d D 1.11 98/09/22 11:01:09 clyde 11 10
c Rename intNN to c_intNN to avoid type conflicts with Digital UNIX 4.0d
e
s 00098/00016/00403
d D 1.10 98/04/09 16:45:48 clyde 10 9
c 1. Add UT copyright notice
c 2. Add comments to each routine
c 3. Add more arugment checking to GetPW(), PutPW() and FindPW()
c 4. Fix order of error messages
c 5. Remove some uneeded code
e
s 00019/00019/00400
d D 1.9 98/04/07 13:29:25 clyde 9 8
c Change #ifndef CRACKLIB_IMBED to #ifdef CRACKLIB_PERROR
e
s 00108/00065/00311
d D 1.8 98/04/02 17:08:42 clyde 8 7
c Considerable rewrite:
c 1. Remove uneeded code
c 2. Allocate PWDICT elements dynamically PWOpen/PWClose
c 3. Stash error message in buffer PWioError
c 4. Disable error printing (control via ifdef CRACKLIB_IMBED)
c 5. Put (void) casts in places to make lint happier
c 6. Fix file descriptor leak in PWOpen and PWClose
c 7. Change debug print enable control to CRACKLIB_DEBUG
c 8. Fix GetPW binary search computation
e
s 00001/00001/00375
d D 1.7 97/08/26 10:35:03 clyde 7 6
c Init some local variables
e
s 00003/00002/00373
d D 1.6 97/05/05 11:25:07 clyde 6 5
c Fix file descriptor leak
e
s 00005/00005/00370
d D 1.5 97/04/29 14:45:13 clyde 5 4
c Change #ifdef DEBUG to #ifdef CRACK_DEBUG
e
s 00007/00003/00368
d D 1.4 93/12/23 14:39:27 clyde 4 3
c Don't perror if IN_CHECKPASSWORD is defined
e
s 00038/00033/00333
d D 1.3 93/06/25 14:24:00 clyde 3 2
c Allocate new PWDICT structure in PWOpen() and free in PWClose()
e
s 00013/00003/00353
d D 1.2 93/06/25 14:11:23 clyde 2 1
c Fix dictionary lookup code in FindPW().
e
s 00356/00000/00000
d D 1.1 93/06/25 11:30:11 clyde 1 0
c date and time created 93/06/25 11:30:11 by clyde
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
I 10
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
E 10

#include "packer.h"

static char vers_id[] = "packlib.c : v2.3p2 Alec Muffett 18 May 1993";
I 2
static char ut_id[] = "%W% %G% (cc.utexas.edu)";
E 2

I 8
char	PWioError[STRINGSIZE * 2];

extern int	errno;

I 10
/*
 * PWOpen - open a hashed dictionary
 */
E 10
E 8
PWDICT *
PWOpen(prefix, mode)
    char *prefix;
D 10
    char *mode;
E 10
I 10
    char *mode;			/* fopen() modes */
E 10
{
D 11
    int32 i;
E 11
I 11
    c_int32 i;
E 11
D 3
    static PWDICT pdesc;
E 3
I 3
    PWDICT *pdesc;
E 3
    char iname[STRINGSIZE];
    char dname[STRINGSIZE];
    char wname[STRINGSIZE];
D 8
    char buffer[STRINGSIZE];
    FILE *dfp;
    FILE *ifp;
    FILE *wfp;
E 8

D 3
    if (pdesc.header.pih_magic == PIH_MAGIC)
    {
	fprintf(stderr, "%s: another dictionary already open\n", prefix);
E 3
I 3
D 8
    if ((pdesc = (PWDICT *)malloc(sizeof(PWDICT))) == 0)
E 8
I 8
    if (strlen(prefix) > (STRINGSIZE - 5)) {
	(void) strcpy (PWioError, "PWOpen: Path too long");
D 9
#ifndef	CRACKLIB_IMBED
E 9
I 9
#ifdef	CRACKLIB_PERROR
E 9
	(void) fprintf (stderr, "%s\n", PWioError);
#endif
E 8
E 3
	return ((PWDICT *) 0);
D 3
    }
E 3
I 3
D 8
	
E 8
I 8
    }

    if ((pdesc = (PWDICT *)malloc(sizeof(PWDICT))) == 0) {
	(void) strcpy(PWioError, "PWOpen: Cannot allocate pwdict block");
D 9
#ifndef	CRACKLIB_IMBED
E 9
I 9
#ifdef	CRACKLIB_PERROR
E 9
	(void) fprintf(stderr, "%s\n", PWioError);
#endif
	return ((PWDICT *) 0);
    }

E 8
D 10
    memset(pdesc, '\0', sizeof(*pdesc));
E 10
I 10
    (void) memset(pdesc, '\0', sizeof(*pdesc));
E 10
E 3

D 3
    memset(&pdesc, '\0', sizeof(pdesc));

E 3
D 4
    sprintf(iname, "%s.pwi", prefix);
    sprintf(dname, "%s.pwd", prefix);
    sprintf(wname, "%s.hwm", prefix);
E 4
I 4
    (void) sprintf(iname, "%s.pwi", prefix);
    (void) sprintf(dname, "%s.pwd", prefix);
    (void) sprintf(wname, "%s.hwm", prefix);
E 4

D 3
    if (!(pdesc.dfp = fopen(dname, mode)))
E 3
I 3
    if (!(pdesc->dfp = fopen(dname, mode)))
E 3
    {
I 4
D 8
#ifndef	IN_CHECKPASSWORD
E 8
I 8
D 10
	(void) sprintf(PWioError, "PWOpen: Error %d opening data file", errno);
E 10
D 9
#ifndef	CRACKLIB_IMBED
E 9
I 9
#ifdef	CRACKLIB_PERROR
E 9
E 8
E 4
	perror(dname);
I 4
#endif
I 10
	(void) sprintf(PWioError, "PWOpen: Error %d opening data file", errno);
E 10
E 4
I 3
D 8
	free(pdesc);
E 8
I 8
	free((char *)pdesc);
E 8
E 3
	return ((PWDICT *) 0);
    }

D 3
    if (!(pdesc.ifp = fopen(iname, mode)))
E 3
I 3
    if (!(pdesc->ifp = fopen(iname, mode)))
E 3
    {
D 3
	fclose(pdesc.dfp);
E 3
I 3
D 8
	fclose(pdesc->dfp);
I 4
#ifndef	IN_CHECKPASSWORD
E 8
I 8
D 10
	(void) sprintf(PWioError, "PWOpen: Error %d opening index file", errno);
E 10
D 9
#ifndef	CRACKLIB_IMBED
E 9
I 9
#ifdef	CRACKLIB_PERROR
E 9
E 8
E 4
E 3
	perror(iname);
I 4
#endif
I 10
	(void) sprintf(PWioError, "PWOpen: Error %d opening index file", errno);
E 10
E 4
I 3
D 8
	free(pdesc);
E 8
I 8
	(void) fclose(pdesc->dfp);
	free((char *)pdesc);
E 8
E 3
	return ((PWDICT *) 0);
    }

D 3
    if (pdesc.wfp = fopen(wname, mode))
E 3
I 3
    if (pdesc->wfp = fopen(wname, mode))
E 3
    {
D 3
	pdesc.flags |= PFOR_USEHWMS;
E 3
I 3
	pdesc->flags |= PFOR_USEHWMS;
E 3
    }

D 3
    ifp = pdesc.ifp;
    dfp = pdesc.dfp;
    wfp = pdesc.wfp;
E 3
I 3
D 8
    ifp = pdesc->ifp;
    dfp = pdesc->dfp;
    wfp = pdesc->wfp;
E 3

E 8
    if (mode[0] == 'w')
    {
D 3
	pdesc.flags |= PFOR_WRITE;
	pdesc.header.pih_magic = PIH_MAGIC;
	pdesc.header.pih_blocklen = NUMWORDS;
	pdesc.header.pih_numwords = 0;
E 3
I 3
	pdesc->flags |= PFOR_WRITE;
	pdesc->header.pih_magic = PIH_MAGIC;
	pdesc->header.pih_blocklen = NUMWORDS;
	pdesc->header.pih_numwords = 0;
E 3

D 3
	fwrite((char *) &pdesc.header, sizeof(pdesc.header), 1, ifp);
E 3
I 3
D 8
	fwrite((char *) &pdesc->header, sizeof(pdesc->header), 1, ifp);
E 8
I 8
	(void) fwrite((char *) &pdesc->header, sizeof(pdesc->header), 1, pdesc->ifp);
E 8
E 3
    } else
    {
D 3
	pdesc.flags &= ~PFOR_WRITE;
E 3
I 3
	pdesc->flags &= ~PFOR_WRITE;
E 3

D 3
	if (!fread((char *) &pdesc.header, sizeof(pdesc.header), 1, ifp))
E 3
I 3
D 8
	if (!fread((char *) &pdesc->header, sizeof(pdesc->header), 1, ifp))
E 8
I 8
	if (!fread((char *) &pdesc->header, sizeof(pdesc->header), 1, pdesc->ifp))
E 8
E 3
	{
D 8
	    fprintf(stderr, "%s: error reading header\n", prefix);

E 8
I 8
	    (void) strcpy(PWioError, "PWOpen: error reading header");
D 9
#ifndef	CRACKLIB_IMBED
E 9
I 9
#ifdef	CRACKLIB_PERROR
E 9
	    fprintf(stderr, "%s: %s\n", prefix, PWioError);
#endif
E 8
D 3
	    pdesc.header.pih_magic = 0;
E 3
I 3
D 10
	    pdesc->header.pih_magic = 0;
E 10
E 3
D 8
	    fclose(ifp);
	    fclose(dfp);
I 3
	    free(pdesc);
E 8
I 8
	    (void) fclose(pdesc->ifp);
	    (void) fclose(pdesc->dfp);
	    if (pdesc->flags & PFOR_USEHWMS)
		    (void) fclose(pdesc->wfp);
	    free((char *)pdesc);
E 8
E 3
	    return ((PWDICT *) 0);
	}

D 3
	if (pdesc.header.pih_magic != PIH_MAGIC)
E 3
I 3
	if (pdesc->header.pih_magic != PIH_MAGIC)
E 3
	{
D 8
	    fprintf(stderr, "%s: magic mismatch\n", prefix);

E 8
I 8
	    (void) strcpy(PWioError, "PWOpen: magic mismatch");
D 9
#ifndef	CRACKLIB_IMBED
E 9
I 9
#ifdef	CRACKLIB_PERROR
E 9
	    (void) fprintf(stderr, "%s: %s\n", prefix, PWioError);
#endif
E 8
D 3
	    pdesc.header.pih_magic = 0;
E 3
I 3
D 10
	    pdesc->header.pih_magic = 0;
E 10
E 3
D 8
	    fclose(ifp);
	    fclose(dfp);
I 3
	    free(pdesc);
E 8
I 8
	    (void) fclose(pdesc->ifp);
	    (void) fclose(pdesc->dfp);
	    if (pdesc->flags & PFOR_USEHWMS)
		    (void) fclose(pdesc->wfp);
D 10
	    (void) free((char *)pdesc);
E 10
I 10
	    free((char *)pdesc);
E 10
E 8
E 3
	    return ((PWDICT *) 0);
	}

D 3
	if (pdesc.header.pih_blocklen != NUMWORDS)
E 3
I 3
	if (pdesc->header.pih_blocklen != NUMWORDS)
E 3
	{
D 8
	    fprintf(stderr, "%s: size mismatch\n", prefix);

E 8
I 8
	    (void) strcat(PWioError, "PWOpen: size mismatch");
D 9
#ifndef	CRACKLIB_IMBED
E 9
I 9
#ifdef	CRACKLIB_PERROR
E 9
	    (void) fprintf(stderr, "%s: %s\n", prefix, PWioError);
#endif
E 8
D 3
	    pdesc.header.pih_magic = 0;
E 3
I 3
D 10
	    pdesc->header.pih_magic = 0;
E 10
E 3
D 8
	    fclose(ifp);
	    fclose(dfp);
I 3
	    free(pdesc);
E 8
I 8
	    (void) fclose(pdesc->ifp);
	    (void) fclose(pdesc->dfp);
	    if (pdesc->flags & PFOR_USEHWMS)
		    (void) fclose(pdesc->wfp);
D 10
	    (void) free((char *)pdesc);
E 10
I 10
	    free((char *)pdesc);
E 10
E 8
E 3
	    return ((PWDICT *) 0);
	}

D 3
	if (pdesc.flags & PFOR_USEHWMS)
E 3
I 3
	if (pdesc->flags & PFOR_USEHWMS)
E 3
	{
D 3
	    if (fread(pdesc.hwms, 1, sizeof(pdesc.hwms), wfp) != sizeof(pdesc.hwms))
E 3
I 3
D 8
	    if (fread(pdesc->hwms, 1, sizeof(pdesc->hwms), wfp) != sizeof(pdesc->hwms))
E 8
I 8
	    if (fread(pdesc->hwms, 1, sizeof(pdesc->hwms), pdesc->wfp) != sizeof(pdesc->hwms))
E 8
E 3
	    {
D 3
		pdesc.flags &= ~PFOR_USEHWMS;
E 3
I 3
		pdesc->flags &= ~PFOR_USEHWMS;
E 3
	    }
	}
    }
D 3

    return (&pdesc);
E 3
I 3
D 8
    pdesc->canfree = 1;
E 8
    return (pdesc);
E 3
}

I 10
/*
 * PWClose - close hashed dictionary
 */
E 10
int
PWClose(pwp)
    PWDICT *pwp;
{
    if (pwp->header.pih_magic != PIH_MAGIC)
    {
D 8
	fprintf(stderr, "PWClose: close magic mismatch\n");
E 8
I 8
D 10
	(void) strcpy(PWioError, "PWClose: close magic mismatch");
E 10
I 10
	(void) strcpy(PWioError, "PWClose: bad magic number");
E 10
D 9
#ifndef	CRACKLIB_IMBED
E 9
I 9
#ifdef	CRACKLIB_PERROR
E 9
	(void) fprintf(stderr, "%s\n", PWioError);
#endif
E 8
	return (-1);
    }

    if (pwp->flags & PFOR_WRITE)
    {
	pwp->flags |= PFOR_FLUSH;
D 10
	PutPW(pwp, (char *) 0);	/* flush last index if necess */
E 10
I 10
	(void) PutPW(pwp, (char *) 0);	/* flush last index if necess */
E 10

	if (fseek(pwp->ifp, 0L, 0))
	{
D 8
	    fprintf(stderr, "index magic fseek failed\n");
E 8
I 8
	   (void) strcpy(PWioError, "PWClose: index magic fseek failed");
D 9
#ifndef	CRACKLIB_IMBED
E 9
I 9
#ifdef	CRACKLIB_PERROR
E 9
	   (void) fprintf(stderr, "%s\n", PWioError);
#endif
E 8
	    return (-1);
	}

	if (!fwrite((char *) &pwp->header, sizeof(pwp->header), 1, pwp->ifp))
	{
D 8
	    fprintf(stderr, "index magic fwrite failed\n");
E 8
I 8
	   (void) strcpy(PWioError, "PWClose: index magic fwrite failed");
D 9
#ifndef	CRACKLIB_IMBED
E 9
I 9
#ifdef	CRACKLIB_PERROR
E 9
	   (void) fprintf(stderr, "%s\n", PWioError);
#endif
E 8
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
D 5
#ifdef DEBUG
E 5
I 5
D 8
#ifdef CRACK_DEBUG
E 8
I 8
D 9
#ifdef CRACKLIB_DEBUG
E 9
I 9
#ifdef	CRACKLIB_DEBUG
E 9
E 8
E 5
	    	printf("hwm[%02x] = %d\n", i, pwp->hwms[i]);
#endif
	    }
D 8
	    fwrite(pwp->hwms, 1, sizeof(pwp->hwms), pwp->wfp);
E 8
I 8
	    (void) fwrite(pwp->hwms, 1, sizeof(pwp->hwms), pwp->wfp);
E 8
	}
    }

D 6
    fclose(pwp->ifp);
    fclose(pwp->dfp);
E 6
I 6
    (void) fclose(pwp->ifp);
    (void) fclose(pwp->dfp);
    (void) fclose(pwp->wfp);
E 6

D 3
    pwp->header.pih_magic = 0;
E 3
I 3
D 8
    if (pwp->canfree)
	free(pwp);
    else
    	pwp->header.pih_magic = 0;
E 3

E 8
I 8
    free((char *)pwp);
E 8
    return (0);
}

I 10
/*
 * PutPW - put a string into dictionary hash files
 */
E 10
int
PutPW(pwp, string)
    PWDICT *pwp;
    char *string;
{
I 10
    if (pwp->header.pih_magic != PIH_MAGIC)
    {
	(void) strcpy(PWioError, "PutPW: bad magic number");
#ifdef	CRACKLIB_PERROR
	(void) fprintf(stderr, "%s\n", PWioError);
#endif
	return (-1);
    }

E 10
    if (!(pwp->flags & PFOR_WRITE))
    {
	return (-1);
    }

    if (string)
    {
D 8
	strncpy(pwp->data[pwp->count], string, MAXWORDLEN);
E 8
I 8
	(void) strncpy(pwp->data[pwp->count], string, MAXWORDLEN);
E 8
	pwp->data[pwp->count][MAXWORDLEN - 1] = '\0';

D 8
	pwp->hwms[string[0] & 0xff]= pwp->header.pih_numwords;
E 8
I 8
	pwp->hwms[string[0] & 0xff] = pwp->header.pih_numwords;
E 8

	++(pwp->count);
	++(pwp->header.pih_numwords);

    } else if (!(pwp->flags & PFOR_FLUSH))
    {
	return (-1);
    }

    if ((pwp->flags & PFOR_FLUSH) || !(pwp->count % NUMWORDS))
    {
	int i;
D 11
	int32 datum;
E 11
I 11
	c_int32 datum;
E 11
	register char *ostr;

D 11
	datum = (int32) ftell(pwp->dfp);
E 11
I 11
	datum = (c_int32) ftell(pwp->dfp);
E 11

D 8
	fwrite((char *) &datum, sizeof(datum), 1, pwp->ifp);
E 8
I 8
	(void) fwrite((char *) &datum, sizeof(datum), 1, pwp->ifp);
E 8

D 8
	fputs(pwp->data[0], pwp->dfp);
	putc(0, pwp->dfp);
E 8
I 8
	(void) fputs(pwp->data[0], pwp->dfp);
	(void) putc(0, pwp->dfp);
E 8

	ostr = pwp->data[0];

	for (i = 1; i < NUMWORDS; i++)
	{
	    register int j;
	    register char *nstr;
	    nstr = pwp->data[i];

	    if (nstr[0])
	    {
		for (j = 0; ostr[j] && nstr[j] && (ostr[j] == nstr[j]); j++);
D 8
		putc(j & 0xff, pwp->dfp);
		fputs(nstr + j, pwp->dfp);
E 8
I 8
		(void) putc(j & 0xff, pwp->dfp);
		(void) fputs(nstr + j, pwp->dfp);
E 8
	    }
D 8
	    putc(0, pwp->dfp);
E 8
I 8
	    (void) putc(0, pwp->dfp);
E 8

	    ostr = nstr;
	}

D 10
	memset(pwp->data, '\0', sizeof(pwp->data));
E 10
I 10
	(void) memset(pwp->data, '\0', sizeof(pwp->data));
E 10
	pwp->count = 0;
    }
    return (0);
}

I 10
/*
 * GetPW - fetch a word from dictionary
 */
E 10
char *
GetPW(pwp, number)
    PWDICT *pwp;
D 11
    int32 number;
E 11
I 11
    c_int32 number;
E 11
{
D 11
    int32 datum;
E 11
I 11
    c_int32 datum;
E 11
    register int i;
    register char *ostr;
    register char *nstr;
    register char *bptr;
    char buffer[NUMWORDS * MAXWORDLEN];
    static char data[NUMWORDS][MAXWORDLEN];
D 11
    static int32 prevblock = 0xffffffff;
    int32 thisblock;
E 11
I 11
    static c_int32 prevblock = 0xffffffff;
    c_int32 thisblock;
E 11

I 10
    if (pwp->header.pih_magic != PIH_MAGIC)
    {
	(void) sprintf(PWioError, "GetPW: bad magic number");
#ifdef	CRACKLIB_PERROR
	fprintf (stderr, "%s\n", PWioError);
#endif
	return ((char *) 0);
    }

E 10
    thisblock = number / NUMWORDS;

    if (prevblock == thisblock)
    {
	return (data[number % NUMWORDS]);
    }

D 11
    if (fseek(pwp->ifp, sizeof(struct pi_header) + (thisblock * sizeof(int32)), 0))
E 11
I 11
    if (fseek(pwp->ifp, sizeof(struct pi_header) + (thisblock * sizeof(c_int32)), 0))
E 11
    {
I 8
D 9
#ifndef	CRACKLIB_IMBED
E 9
I 9
#ifdef	CRACKLIB_PERROR
E 9
E 8
	perror("(index fseek failed)");
I 8
#endif
	(void) sprintf(PWioError, "GetPW: index seek error %d", errno);
E 8
	return ((char *) 0);
    }

    if (!fread((char *) &datum, sizeof(datum), 1, pwp->ifp))
    {
D 8
	perror("(index fread failed)");
E 8
I 8
D 9
#ifndef	CRACKLIB_IMBED
E 9
I 9
#ifdef	CRACKLIB_PERROR
E 9
	perror("GetPW (index fread failed)");
#endif
	(void) sprintf(PWioError, "GetPW: index fread error %d", errno);
E 8
	return ((char *) 0);
    }

    if (fseek(pwp->dfp, datum, 0))
    {
D 8
	perror("(data fseek failed)");
E 8
I 8
D 9
#ifndef	CRACKLIB_IMBED
E 9
I 9
#ifdef	CRACKLIB_PERROR
E 9
	perror("GetPW (data fseek failed)");
#endif
	(void) sprintf(PWioError, "GetPW: data fseek error %d", errno);
E 8
	return ((char *) 0);
    }

    if (!fread(buffer, 1, sizeof(buffer), pwp->dfp))
    {
D 8
	perror("(data fread failed)");
E 8
I 8
D 9
#ifndef	CRACKLIB_IMBED
E 9
I 9
#ifdef	CRACKLIB_PERROR
E 9
	perror("GetPW (data fread failed)");
#endif
	(void) sprintf(PWioError, "GetPW: data fread error %d", errno);
E 8
	return ((char *) 0);
    }

    prevblock = thisblock;

    bptr = buffer;

    for (ostr = data[0]; *(ostr++) = *(bptr++); /* nothing */ );

    ostr = data[0];

    for (i = 1; i < NUMWORDS; i++)
    {
	nstr = data[i];
D 10
	strcpy(nstr, ostr);
E 10
I 10
	(void) strcpy(nstr, ostr);
E 10

	ostr = nstr + *(bptr++);
	while (*(ostr++) = *(bptr++));

	ostr = nstr;
    }

    return (data[number % NUMWORDS]);
}

I 10
/*
 * FindPW - check if <string> is in dictionary <pwp>
 */
E 10
D 11
int32
E 11
I 11
c_int32
E 11
FindPW(pwp, string)
    PWDICT *pwp;
    char *string;
{
D 11
    register int32 lwm;
    register int32 hwm;
D 7
    register int32 middle;
E 7
I 7
    register int32 middle = 0;
E 11
I 11
    register c_int32 lwm;
    register c_int32 hwm;
    register c_int32 middle = 0;
E 11
E 7
    register char *this;
D 8
    int idx;
E 8

I 2
D 8
#if	0
    /* This does not work under all circumstances, so don't bother */
E 8
I 8
D 10
#if	1
E 10
I 10
    if (pwp->header.pih_magic != PIH_MAGIC)
    {
	(void) strcpy(PWioError, "FindPW: bad magic number");
#ifdef	CRACKLIB_PERROR
	(void) fprintf(stderr, "%s\n", PWioError);
#endif
        return (PW_WORDS(pwp));		/* Probably bogus */
    }

E 10
E 8
E 2
    if (pwp->flags & PFOR_USEHWMS)
    {
D 8
	idx = string[0] & 0xff;
E 8
I 8
        int idx = string[0] & 0xff;

E 8
    	lwm = idx ? pwp->hwms[idx - 1] : 0;
    	hwm = pwp->hwms[idx];
    } else
I 2
D 10
#endif
E 10
E 2
    {
    	lwm = 0;
D 2
    	hwm = PW_WORDS(pwp) - 1;
E 2
I 2
    	hwm = PW_WORDS(pwp);
E 2
    }

D 5
#ifdef DEBUG
E 5
I 5
D 8
#ifdef CRACK_DEBUG
E 8
I 8
D 9
#ifdef CRACKLIB_DEBUG
E 9
I 9
#ifdef	CRACKLIB_DEBUG
E 9
E 8
E 5
D 2
    printf("---- %lu, %lu ----\n", lwm, hwm);
E 2
I 2
    printf("---- lwm=%lu, hwm=%lu ----\n", lwm, hwm);
E 2
#endif

    for (;;)
    {
	int cmp;

D 5
#ifdef DEBUG
E 5
I 5
D 8
#ifdef CRACK_DEBUG
E 8
I 8
D 9
#ifdef CRACKLIB_DEBUG
E 9
I 9
#ifdef	CRACKLIB_DEBUG
E 9
E 8
E 5
D 2
	printf("%lu, %lu\n", lwm, hwm);
E 2
I 2
	printf("lwm=%lu, hwm=%lu middle=%lu\n", lwm, hwm, middle);
E 2
#endif
D 8

	middle = lwm + ((hwm - lwm + 1) / 2);
I 2
D 5
#ifdef DEBUG
E 5
I 5
#ifdef CRACK_DEBUG
E 8
I 8
	/*
	 * The cast is needed because the operands are unsigned,
	 * but the casted expression can legitimately be negative when
	 * (lwm > hwm).
	 */
	middle = lwm + (((int )(hwm - lwm) + 1) / 2);
D 9
#ifdef CRACKLIB_DEBUG
E 9
I 9
#ifdef	CRACKLIB_DEBUG
E 9
E 8
E 5
	printf("new middle=%lu\n", middle);
#endif
E 2

	if (middle == hwm)
	{
	    break;
	}

	this = GetPW(pwp, middle);
D 10
	cmp = strcmp(string, this);		/* INLINE ? */
E 10
I 10
	cmp = strcmp(string, this);
E 10

I 2
D 5
#ifdef DEBUG
E 5
I 5
D 8
#ifdef CRACK_DEBUG
E 8
I 8
D 9
#ifdef CRACKLIB_DEBUG
E 9
I 9
#ifdef	CRACKLIB_DEBUG
E 9
E 8
E 5
	printf("this=<%s> string=<%s> cmp=%d\n", this, string, cmp);
#endif
E 2
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
I 8
/* End %M% */
E 8
E 1
