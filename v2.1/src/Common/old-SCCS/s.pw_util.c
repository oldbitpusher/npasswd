h26166
s 00001/00001/00184
d D 1.7 97/09/19 10:58:50 clyde 7 6
c Fix possible string overflow problem
e
s 00004/00000/00181
d D 1.6 97/05/27 09:24:34 clyde 6 5
c Use memset(0) instead of bzero() where available
e
s 00019/00014/00162
d D 1.5 96/08/29 13:02:12 clyde 5 4
c 1. Remove 'const' declarations (too much compiler pain)
c 2. Fix copypwent() to not bomb on null strings
e
s 00023/00022/00153
d D 1.4 96/08/13 17:59:30 clyde 4 3
c Change some variable names for clarity
c Add const declarations here and there
e
s 00001/00001/00174
d D 1.3 96/08/09 16:19:00 clyde 3 2
c Beta 3 development checkin 2
e
s 00013/00009/00162
d D 1.2 96/08/06 14:49:03 clyde 2 1
c beta 3 development checkin
e
s 00171/00000/00000
d D 1.1 96/04/01 16:15:10 clyde 1 0
c date and time created 96/04/01 16:15:10 by clyde
e
u
U
f e 0
t
T
I 1
/*
 * npasswd module %M%
 *
 * Passwd file utility routines.  Some of these are replacements
 * for possibily missing libc routines, 
 *
 * Compilation: cc -c %M%
 * Includes: npasswd.h
 *
 */

#include "npasswd.h"

#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu) %P%";
#endif

#ifndef	HAS_PUTPWENT
/*
 *	putpwent - Write a passwd entry to a file pointer
 *		The entry is written in "classic" passwd form
 */
public void
putpwent(p, f)
D 4
	struct passwd	*p;	/* Passwd entry to put */
	FILE	*f;		/* File pointer */
E 4
I 4
D 5
	const struct passwd	*p;	/* Passwd entry to put */
E 5
I 5
	struct passwd	*p;	/* Passwd entry to put */
E 5
	FILE		*f;		/* File pointer */
E 4
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
D 2
	if ((p = index(ibuf, '\n')) == 0)		/* Zap newline */
E 2
I 2
	if ((p = strchr(ibuf, '\n')) == 0)		/* Zap newline */
E 2
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
D 4
	struct passwd	*p;	/* Passwd entry to put */
	char		*b;	/* Buffer to build it in */
E 4
I 4
D 5
	const struct passwd	*p;	/* Passwd entry to put */
E 5
I 5
	struct passwd	*p;	/* Passwd entry to put */
E 5
	char			*b;	/* Buffer to build it in */
E 4
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
D 4
	char	*s;		/* Pointer to open passwd format file */
E 4
I 4
D 5
	const char	*s;	/* Passwd format string to crack */
E 5
I 5
	char	*s;		/* Passwd format string to crack */
E 5
E 4
{
	static struct passwd	pwdata;	/* Return data */
I 5
	static char	pwb[PW_LINELEN];
E 5
	char		*p;	/* ACME Pointer Works, Inc */
	char		*pp;	/* ACME Pointer Works, Inc */

I 6
#ifdef	HAS_MEMSET
	memset((char *)&pwdata, 0, sizeof(pwdata));
#else
E 6
	bzero((char *)&pwdata, sizeof(pwdata));
I 6
#endif
E 6
I 5
D 7
	strcpy(pwb, s);
E 7
I 7
	(void) strncpy(pwb, s, sizeof(pwb));
E 7
E 5
#define	skipc while (*p && *p != ':' && *p != '\n') ++p; if (*p) *p++ = 0
D 5
	p = s;
E 5
I 5
	p = pwb;
E 5
	pwdata.pw_name = p;	skipc;
	pwdata.pw_passwd = p;	skipc;
#ifdef	PWAGE
D 2
	if (pp = index(pwdata.pw_passwd, ',')) {
E 2
I 2
	if (pp = strchr(pwdata.pw_passwd, ',')) {
E 2
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
D 4
copypwent(f,t)
	struct passwd	*f,		/* From */
			*t;		/* To */
E 4
I 4
copypwent(pw_from, pw_to)
D 5
	const struct passwd	*pw_from;	/* From */
	struct passwd		*pw_to;		/* To */
E 5
I 5
	struct passwd	*pw_from;	/* From */
	struct passwd	*pw_to;		/* To */
E 5
E 4
{
I 2
D 4
	if (t == NULL) {
D 3
		if ((t = (strct passswd *)malloc(sizeof(*t))) == NULL)
E 3
I 3
		if ((t = (struct passswd *)malloc(sizeof(*t))) == NULL)
E 3
			return(NULL);
E 4
I 4
	if (pw_to == 0) {
		if ((pw_to = (struct passwd *)malloc(sizeof(struct passwd))) == 0)
			logdie("Cannot alloc pwent copy\n");

E 4
	}
E 2
D 4
	*t = *f;	
D 2
	t->pw_name = copystr(f->pw_name);
E 2
I 2
	t->pw_name = strdup(f->pw_name);
E 4
I 4
	*pw_to = *pw_from;	
D 5
	pw_to->pw_name = strdup(pw_from->pw_name);
E 5
I 5
#define	CopyString(f,t) if (f) t = strdup(f)

	CopyString(pw_from->pw_name, pw_to->pw_name);
E 5
E 4
E 2
#ifdef	PWAGE
D 2
	t->pw_age = copystr(f->pw_age);
E 2
I 2
D 4
	t->pw_age = strdup(f->pw_age);
E 4
I 4
D 5
	pw_to->pw_age = strdup(pw_from->pw_age);
E 5
I 5
	CopyString(pw_from->pw_age, pw_to->pw_age);
E 5
E 4
E 2
#endif
#ifdef	PWCOMMENT
D 2
	t->pw_comment = copystr(f->pw_comment);
E 2
I 2
D 4
	t->pw_comment = strdup(f->pw_comment);
E 4
I 4
D 5
	pw_to->pw_comment = strdup(pw_from->pw_comment);
E 5
I 5
	CopyString(pw_from->pw_comment, pw_to->pw_comment);
E 5
E 4
E 2
#endif
D 2
	t->pw_passwd = copystr(f->pw_passwd);
	t->pw_gecos = copystr(f->pw_gecos);
	t->pw_dir = copystr(f->pw_dir);
	t->pw_shell = copystr(f->pw_shell);
E 2
I 2
D 4
	t->pw_passwd = strdup(f->pw_passwd);
	t->pw_gecos = strdup(f->pw_gecos);
	t->pw_dir = strdup(f->pw_dir);
	t->pw_shell = strdup(f->pw_shell);
E 2
	return(t);
E 4
I 4
D 5
	pw_to->pw_passwd = strdup(pw_from->pw_passwd);
	pw_to->pw_gecos = strdup(pw_from->pw_gecos);
	pw_to->pw_dir = strdup(pw_from->pw_dir);
	pw_to->pw_shell = strdup(pw_from->pw_shell);
E 5
I 5
	CopyString(pw_from->pw_passwd, pw_to->pw_passwd);
	CopyString(pw_from->pw_gecos, pw_to->pw_gecos);
	CopyString(pw_from->pw_dir, pw_to->pw_dir);
	CopyString(pw_from->pw_shell, pw_to->pw_shell);
#undef	CopyString
E 5
	return(pw_to);
E 4
}

/*
 *	fgetpwnam - get user from password file
 */
public struct passwd *
fgetpwnam(name, pwfile)
D 4
	char	*name,
		*pwfile;
E 4
I 4
D 5
	const char	*name,
E 5
I 5
	char	*name,
E 5
			*pwfile;
E 4
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

/* End %M% */
E 1
