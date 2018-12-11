/*
 *	pwck_crack - Call the 'crack' dictionary checker
 *	Returns:
 *		PWCK_INDICT if <password> was in any dictionary
 *		PWCK_OK if password found in a dictionary
 *		PWCK_FAIL if a dictionary cannot be opened
 */

#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu)";
#endif

#include "compatibility.h"
#include "checkpassword.h"
#include "pwck_lib.h"
#include "bloom/CCStr.h"
#include "bloom/Blf.h"
#include "bloom/Finger.h"

public int
pwck_bloom(password, user, mesgbuf)
	char	*password;	/* Candidate password */
	struct passwd	*user;	/* Passwd info for user */ /*NOTUSED*/
	char	*mesgbuf;	/* Message buffer */
{
	int	rcode;		/* Return code temp */
	char	*msg;		/* Scratch */
	dictionary *d;		/* Current dictionary */

	CCStr(password);
	for (d = Config.filters; d; d = d->next) {
		FILE	*t;

		if  ((t = fopen(d->path, "r")) == NULL) {
			if (d->flags & DICT_OPTIONAL)
				continue;
			if (mesgbuf)
				(void) sprintf(mesgbuf,
					"cannot open filter \"%s\"",
					d->path);
#ifdef	DEBUG
			printf(">> %s\n", mesgbuf);
			return(PWCK_OK);
#else
			/*
			 * POLICY: If any dictionary cannot be opened, then
			 * don't approve the password because it could be
			 * vunerable.
			 * The dictionary could be ignored, or I could fall
			 * back to doing fgrep of a flat file, or a nicer
			 * abort performed.
			 */
			return(PWCK_FAIL);
#endif
		}
		BlfRead(t);
#ifdef	DEBUG
		printf("pwck_crack: pw <%s> dictionary \"%s\"\n",
			password, d->path);
#endif
		if (msg = FascistCheck(password, d->path)) {
			if (mesgbuf)
				(void) strcpy(mesgbuf, msg);
			return(PWCK_INDICT);
		}
	}
	return(PWCK_OK);
}
/* End %M% */
