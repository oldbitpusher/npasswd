/*
 * npasswd module $RCSfile: pw_util.c,v $
 *
 * Passwd file utility routines.  Some of these are replacements
 * for possibily missing libc routines, 
 *
 * Compilation: cc -c $RCSfile: pw_util.c,v $
 * Includes: npasswd.h
 *
 */

#include "npasswd.h"

#ifndef lint
static char sccsid[] = "$Id: pw_util.c,v 1.7 1997/09/19 00:00:00 clyde Exp $ (cc.utexas.edu) %P%";
#endif

#ifndef	HAS_PUTPWENT
/*
 *	putpwent - Write a passwd entry to a file pointer
 *		The entry is written in "classic" passwd form
 */
public void
putpwent(p, f)
	struct passwd	*p;	/* Passwd entry to put */
	FILE		*f;		/* File pointer */
{
	char	pwline[PW_LINELEN];

	sputpwent(p, pwline);
	(void) fprintf(f, "%s\n", pwline);
}
#endif	/* HAS_PUTPWENT */

#ifndef	HAS_FGETPWENT
/*
 *	fgetpwent - read passwd entry from a file pointer
 *		This expects the "classic" passwd format
 */
public struct passwd *
fgetpwent(f)
	FILE	*f;			/* Pointer to open passwd format file */
{
	static char	ibuf[PW_LINELEN];	/* Input and return data buffer */
	char	*p;

	if (fgets(ibuf, sizeof(ibuf), f) == NULL)
		return(0);
	if ((p = strchr(ibuf, '\n')) == 0)		/* Zap newline */
		logdie("Ill-formed passwd entry \"%s\".\n", ibuf);
	else
		*p = 0;
	return(sgetpwent(ibuf));
}
#endif	/* HAS_FGETPWENT */

#ifndef	HAS_SPUTPWENT
/*
 *	sputpwent - create a passwd entry in a buffer
 *		This creates a "classic" passwd format
 */
public char *
sputpwent(p, b)
	struct passwd	*p;	/* Passwd entry to put */
	char			*b;	/* Buffer to build it in */
{
	char	pwb[PW_LINELEN];

	(void) strcpy(pwb, p->pw_passwd);
#ifdef	PWAGE		/* Does the pw_age field exist? */
	if (p->pw_age && *p->pw_age) {
		(void) strcat(pwb, ",");
		(void) strcat(pwb, p->pw_age);
	}
#endif	/* PWAGE */
#ifdef	UIDS_ARE_SIGNED		/* Are uids signed? */
	(void) sprintf(b, "%s:%s:%d:%d:%s:%s:%s",
#else	/* UIDS_ARE_SIGNED */
	(void) sprintf(b, "%s:%s:%u:%u:%s:%s:%s",
#endif	/* UIDS_ARE_SIGNED */
		p->pw_name, pwb, (Uid_t )p->pw_uid, (Gid_t )p->pw_gid,
		p->pw_gecos, p->pw_dir, p->pw_shell);
	return(b);
}
#endif	/* HAS_SPUTPWENT */

/*
 *	sgetpwent() - crack a passwd line
 *		This reads the "classic" passwd file format.
 */
public struct passwd *
sgetpwent(s)
	char	*s;		/* Passwd format string to crack */
{
	static struct passwd	pwdata;	/* Return data */
	static char	pwb[PW_LINELEN];
	char		*p;	/* ACME Pointer Works, Inc */
	char		*pp;	/* ACME Pointer Works, Inc */

#ifdef	HAS_MEMSET
	memset((char *)&pwdata, 0, sizeof(pwdata));
#else
	bzero((char *)&pwdata, sizeof(pwdata));
#endif
	(void) strncpy(pwb, s, sizeof(pwb));
#define	skipc while (*p && *p != ':' && *p != '\n') ++p; if (*p) *p++ = 0
	p = pwb;
	pwdata.pw_name = p;	skipc;
	pwdata.pw_passwd = p;	skipc;
#ifdef	PWAGE
	if (pp = strchr(pwdata.pw_passwd, ',')) {
		*pp++ = 0;
		pwdata.pw_age = pp;
	}	
#endif
	pwdata.pw_uid = atoi(p); skipc;
	pwdata.pw_gid = atoi(p); skipc;
	pwdata.pw_gecos = p;	skipc; 
	pwdata.pw_dir = p;	skipc;
	pwdata.pw_shell = p;
	return(&pwdata);
#undef	skipc
}

/*
 *	copypwent - copy a passwd structure
 */
public struct passwd *
copypwent(pw_from, pw_to)
	struct passwd	*pw_from;	/* From */
	struct passwd	*pw_to;		/* To */
{
	if (pw_to == 0) {
		if ((pw_to = (struct passwd *)malloc(sizeof(struct passwd))) == 0)
			logdie("Cannot alloc pwent copy\n");

	}
	*pw_to = *pw_from;	
#define	CopyString(f,t) if (f) t = strdup(f)

	CopyString(pw_from->pw_name, pw_to->pw_name);
#ifdef	PWAGE
	CopyString(pw_from->pw_age, pw_to->pw_age);
#endif
#ifdef	PWCOMMENT
	CopyString(pw_from->pw_comment, pw_to->pw_comment);
#endif
	CopyString(pw_from->pw_passwd, pw_to->pw_passwd);
	CopyString(pw_from->pw_gecos, pw_to->pw_gecos);
	CopyString(pw_from->pw_dir, pw_to->pw_dir);
	CopyString(pw_from->pw_shell, pw_to->pw_shell);
#undef	CopyString
	return(pw_to);
}

/*
 *	fgetpwnam - get user from password file
 */
public struct passwd *
fgetpwnam(name, pwfile)
	char	*name,
			*pwfile;
{
	FILE	*pf;
	struct passwd	*px;		/* Password file traversal */

	if ((pf = fopen(pwfile, "r")) == NULL)
		logdie("Cannot open password file \"%s\".", pwfile);
	/*
	 * Scan local password file, looking for user
	 */
	while ((px = fgetpwent(pf)) != NULL) {
		char	*tp = px->pw_name;

		if (*tp == '+') tp++;		/* Ignore NIS stub entries */
		if (strcmp(tp, name) == 0) {
			(void) fclose(pf);
			return(px);
		}
	}
	(void) fclose(pf);
	return(NULL);
}

/* End $RCSfile: pw_util.c,v $ */
