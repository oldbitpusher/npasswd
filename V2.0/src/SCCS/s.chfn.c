h21941
s 00001/00000/00217
d D 1.14 00/08/11 11:11:05 clyde 14 13
c Fix bug with gecos data read
e
s 00044/00000/00173
d D 1.13 98/06/23 11:12:58 clyde 13 12
c Add copyright notice
e
s 00004/00004/00169
d D 1.12 98/04/28 16:49:47 clyde 12 11
c Change name of help & motd file
e
s 00001/00001/00172
d D 1.11 98/03/26 11:17:40 clyde 11 10
c More careful string copying
e
s 00001/00001/00172
d D 1.10 97/05/05 10:35:00 clyde 10 9
c Change missing help file message
e
s 00001/00001/00172
d D 1.9 96/08/14 19:00:51 clyde 9 8
c Fix punctutation for die() messages
e
s 00022/00012/00151
d D 1.8 96/08/13 17:55:50 clyde 8 7
c 1. Change configuration var names
c 2. Deal with missing GECOS fields
e
s 00001/00001/00162
d D 1.7 96/08/09 16:17:07 clyde 7 6
c Beta 3 development checkin 2
e
s 00082/00159/00081
d D 1.6 96/08/06 14:14:24 clyde 6 5
c beta 3 cycle 1 checkin
e
s 00002/00002/00238
d D 1.5 96/04/03 14:46:34 clyde 5 4
c Reflect new mpasswd structure element names
e
s 00004/00007/00236
d D 1.4 95/04/05 16:20:09 clyde 4 3
c Beta 3 development checkin
e
s 00001/00001/00242
d D 1.3 94/10/24 10:36:36 clyde 3 2
c Change YP_PASSWD to YP_SUPPORT
e
s 00001/00004/00242
d D 1.2 94/09/28 16:26:38 clyde 2 1
c Fix include file
e
s 00246/00000/00000
d D 1.1 94/07/28 15:58:11 clyde 1 0
c date and time created 94/07/28 15:58:11 by clyde
e
u
U
f e 0
t
T
I 1
/*
I 13
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
E 13
 *	This program duplicates the manual page behavior of the 4.XBSD
 *	chfn(1) command.
 */
#include "npasswd.h"
D 2
#include "pw_defs.h"
#include "pw_nis.h"

#include TIME_H
E 2
I 2
D 7
#include "pwm_defs.h"
E 7
I 7
#include "Methods/pwm_defs.h"
E 7
E 2

#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu) %P%";
#endif

D 6
#ifdef __STDC__
private enum chg_perm can_change_finfo (struct mpasswd *, struct mpasswd *);
private int is_none (char *field);
#else
private enum chg_perm can_change_finfo ();
private int is_none ();
#endif
E 6
I 6
D 8
Config_Value char	*chfn_help = CHFN_HELP,
			*chfn_motd = CHFN_MOTD;
E 8
I 8
D 12
Config_Value char	*ChfnHelpFile = CHFN_HELP,
			*ChfnMotdFile = CHFN_MOTD;
E 12
I 12
Config_Value char	*Chfn_Help = CHFN_HELP,
			*Chfn_Motd = CHFN_MOTD;
E 12
E 8
E 6

I 6
#define	GECOS_SIZE	128
E 6

D 6
#ifndef CHFN_HELP
# define	CHFN_HELP	"/usr/adm/chfn.help"
#endif
E 6
I 6
private int	check_name _((char *));
private int	check_roomnum _((char *));
private int	check_phone _((char *));
E 6

D 6
#ifndef CHFN_MOTD
# define	CHFN_MOTD	"/usr/adm/chfn.motd"
#endif

public char	chfn_help[MAXPATHLEN] = { CHFN_HELP },
		chfn_motd[MAXPATHLEN] = { CHFN_MOTD };

#define NUM_GECOS_ENTRIES 4
#define GECOS_SIZE 200
char *gecosLabels[NUM_GECOS_ENTRIES] = {
	"Name",
	"Office number",
	"Office phone",
	"Home phone"
E 6
I 6
struct gecosFields {
	char	*label;
	int	(*check)();
I 8
	char	*oldvalue;
E 8
E 6
};

I 8
/* These must be in the right order */
E 8
D 6
typedef int (*GecosCheckFun)();
private int check_name(), check_roomnum(), check_phone();

GecosCheckFun check_gecos[NUM_GECOS_ENTRIES] = {
	check_name, check_roomnum, check_phone, check_phone
E 6
I 6
private struct gecosFields Fields[] = {
	{ "Name",		check_name },
	{ "Office number",	check_roomnum },
	{ "Office phone",	check_phone },
	{ "Home phone",		check_phone },
	{ 0 },
E 6
};
D 6
	
public void chfn(user, caller)
struct mpasswd	*user,
		*caller;
E 6
I 6

public void chfn(theUser, theCaller)
struct mpasswd	*theUser,
		*theCaller;
E 6
{
D 6
	enum	chg_perm	perm;
E 6
	char	newGecos[GECOS_SIZE];
D 6
	char	oldGecos[GECOS_SIZE];
	char	*gecosValues[NUM_GECOS_ENTRIES];
	char	*gecosPtr = newGecos;
	char	*rptr;
	char	*tptr;
	int	cnt;
E 6
I 6
	char	*t;
	char	**oldGecos;
I 8
	char	**x;
E 8
	int	field;
I 8
	int	ismore = 1;
E 8
	struct gecosFields *gptr;
	struct mpasswd	*newUser;
E 6

D 6
	if ((perm = can_change_finfo (user, caller)) == deny) {
E 6
I 6
#ifdef	USE_NIS
	yp_password(theUser);	/* If a NIS client get user password */
#endif
D 8
	if (theCaller->mpw_uid && strcmp(theCaller->mpw_name, theUser->mpw_name)) {
E 8
I 8
	if (theCaller->mpw_uid &&
	    strcmp(theCaller->mpw_name, theUser->mpw_name))
E 8
E 6
		die("Permission denied.\n");
D 8
	}
I 6
	motd(chfn_motd, 0);
E 8
E 6

I 8
D 12
	motd(ChfnMotdFile, 0);
E 12
I 12
	motd(Chfn_Motd, 0);
I 14
	newGecos[0] = 0;
E 14
E 12

E 8
D 6
	motd(chfn_motd, (char *)0);

	if (!ProgramInput) {
		fprintf(stderr,
			"Changing finger information for %s on %s\n",
D 5
			user->mpw_name, user->where);
E 5
I 5
			user->mpw_name, user->pws_loc);
E 5
		fprintf(stderr,	"Default values are printed inside of '[]'\n");
		fprintf(stderr, "To accept the default, type <return>\n");
		fprintf(stderr, "To have a blank entry, type the word 'none'\n");
		fprintf(stderr, "For more information, type '?'\n");
		fflush(stderr);
E 6
I 6
	if (!XSwitches[Xsw_UseStdin]) {
		printf("Changing finger information for %s on %s\n",
			theUser->mpw_name, theUser->pws_loc);
		printf("Default values are printed inside of '[]'\n");
		printf("To accept the default, type <return>\n");
		printf("To have a blank entry, type the word 'none'\n");
		printf("For more information, type '?'\n");
		fflush(stdout);
E 6
	}
I 6
	oldGecos = split(theUser->mpw_gecos, ',', 0, 0);
E 6

I 8
	for (gptr = Fields, x = oldGecos; gptr->label; gptr++) {
		if (x && *x) gptr->oldvalue = *x++;
		else gptr->oldvalue = "";
	}

E 8
D 6
	strcpy(oldGecos, user->mpw_gecos);
	for (tptr = oldGecos, cnt = 0; *tptr != '\0'; tptr++) {
		if (*tptr == ',') {
			cnt++;
		}
	}
	for ( ; cnt < NUM_GECOS_ENTRIES ; cnt++ ) {
		strcat(oldGecos, ",");
	}
	tptr = oldGecos;
	
	for (cnt = 0; cnt < NUM_GECOS_ENTRIES; cnt++) {
		gecosValues[cnt] = tptr;
		for ( ; *tptr != ',' ; tptr++ ) ;
		*tptr++ = '\0';
	}
E 6
I 6
	for (field = 0; (&Fields[field])->label; field++) {
		char	inbuf[GECOS_SIZE];
E 6

D 6
	tptr = newGecos;
	for (cnt = 0; cnt < NUM_GECOS_ENTRIES; cnt++) {
		if (!ProgramInput) {
			fprintf (stderr, "%s [%s]: ",
				 gecosLabels[cnt],
				 gecosValues[cnt]);
			fflush(stderr);
E 6
I 6
		gptr = &Fields[field];
D 8
		if (!XSwitches[Xsw_UseStdin]) {
			printf("%s [%s]: ", gptr->label, oldGecos[field]);
E 6
		}
E 8
I 8
		if (!XSwitches[Xsw_UseStdin])
			printf("%s [%s]: ", gptr->label, gptr->oldvalue);

E 8
D 6

		rptr = fgets(tptr, GECOS_SIZE, stdin);
		if (rptr == NULL) {
E 6
I 6
		if (fgets(inbuf, GECOS_SIZE, stdin) == NULL) {
E 6
			if (feof(stdin)) {
D 6
				fprintf (stderr,
					 "\nFinger information unchanged\n");
				fflush(stderr);
E 6
I 6
				printf("\nFinger information unchanged\n");
E 6
				return;
			}
			else {
D 6
				die ("Error while reading stdin\n");
E 6
I 6
D 9
				die("Error while reading stdin\n");
E 9
I 9
				die("Error while reading stdin.\n");
E 9
E 6
			}
		}
D 4
		if (rptr = INDEX(tptr, '\n'))
E 4
I 4
D 6
		if (rptr = index(tptr, '\n'))
E 4
			*rptr = '\0';

		if (*tptr == '\0') {
			(void) strcpy(tptr, gecosValues[cnt]);
			for ( ; *tptr != '\0'; tptr++) ;
			*tptr++ = ',';
			continue;
		}

		if (strcmp(tptr, "?") == 0) {
E 6
I 6
		chop_nl(inbuf);
		if (strcmp(inbuf, "?") == 0) {
E 6
D 8
			motd(chfn_help, "Missing help file");
E 8
I 8
D 10
			motd(ChfnHelpFile, "Missing help file");
E 10
I 10
D 12
			motd(ChfnHelpFile, "Sorry, there is no help.\n");
E 12
I 12
			motd(Chfn_Help, "Sorry, there is no help.\n");
E 12
E 10
E 8
D 6
			cnt--;
E 6
I 6
			field--;
E 6
			continue;
I 6
		} else if (*inbuf == '\0') {
D 8
			(void) strcpy(inbuf, oldGecos[field]);
		} else if (strcasecmp(inbuf, "none")) {
E 8
I 8
D 11
			(void) strcpy(inbuf, gptr->oldvalue);
E 11
I 11
			(void) strncpy(inbuf, gptr->oldvalue, sizeof inbuf);
E 11
		} else if (strcasecmp(inbuf, "none") == 0) {
E 8
			inbuf[0] = 0;
		} else {
			if (!(gptr->check)(inbuf)) {
				printf("Invalid %s: %s\n", gptr->label, inbuf);
				fflush(stdout);
				field--;
				continue;
			}
E 6
		}
D 6

		if (is_none(tptr)) {
			*tptr++ = ',';
			continue;
		}
		
		if (! (check_gecos[cnt])(tptr)) {
			fprintf (stderr, "Invalid %s: %s\n", 
				 gecosLabels[cnt], tptr);
			fflush (stderr);
			cnt--;
			continue;
		}

		while ( *tptr++ != '\0') ;
		*(tptr-1) = ',';
E 6
I 6
		(void) strcat(newGecos, inbuf);
		(void) strcat(newGecos, ",");
E 6
	}
D 6
	*--tptr = '\0';
E 6
I 6
	t = strrchr(newGecos, ',');
	*t = 0;
E 6

D 6
	pw_replace(user, (char *)0, newGecos, (char *)0);
E 6
I 6
D 8
	newUser = copympwent(theUser);
E 8
I 8
	newUser = copympwent(theUser, (struct mpasswd *)0);
E 8
	newUser->mpw_gecos = newGecos;

	pw_replace(theUser, newUser, CHG_GECOS);
E 6
D 4

#ifdef	USE_SYSLOG
	syslog(MESSAGE_LOG_LEVEL,
E 4
I 4
	syslog(LOG_INFO,
E 4
	       "Finger information changed on %s for %s by %s\n",
D 5
	       user->where, user->mpw_name, caller->mpw_name);
E 5
I 5
D 6
	       user->pws_loc, user->mpw_name, caller->mpw_name);
E 5
D 4
#endif
E 4

D 3
#ifdef	YP_PASSWD
E 3
I 3
D 4
#ifdef	YP_SUPPORT
E 4
I 4
#ifdef	USE_NIS
E 4
E 3
	yp_sync();
#endif
	return;
E 6
I 6
	       theUser->pws_loc, theUser->mpw_name, theCaller->mpw_name);
E 6
}

/*
D 6
 *	can_change_finfo - check finger information change permission
 *
 *	Returns 1 if finger information can be changed
 *		0 if not
 */
private enum chg_perm can_change_finfo (theUser, theCaller)
struct mpasswd	*theUser,
		*theCaller;
{
D 4
	uid_t	calluid = getuid();
E 4
I 4
	Uid_t	calluid = getuid();
E 4

	if (calluid == 0)	/* Su can change anybody's finger info */
		return(other);

	if (strcmp(theCaller->mpw_name, theUser->mpw_name))
		return(deny);		/* I'm not root and target isn't me */

	return(self);			/* I can always change my finger info */
}

private int is_none (field)
char	*field;
{
	if (field[0] != 'n' && field[0] != 'N') return 0;
	if (field[1] != 'o' && field[1] != 'O') return 0;
	if (field[2] != 'n' && field[2] != 'N') return 0;
	if (field[3] != 'e' && field[3] != 'E') return 0;
	if (field[4] != '\0' && field[4] != '\0') return 0;
	return 1;
}

/*
E 6
 *	check_name	- check for valid user name
 *	check_roomnum	- check for valid room number
 *	check_phone	- check for valid phone number
 *
 *	These three routines can be used to provide sanity checks for 
 *	 values to be stored in the password file gecos fields.
 *
 *	Return 1 if field is OK
 *	       0 if not.
 */

D 6
private int check_name (name)
char *name;
E 6
I 6
private int
check_name (name)
	char	*name;
E 6
{
D 6
	for ( ; *name != '\0' ; name++ ) {
E 6
I 6
	for ( ; *name; name++ ) {
E 6
		if (*name == ':' || *name == ',' || !isprint(*name)) {
D 6
			return 0;
E 6
I 6
			return(0);
E 6
		}
	}
D 6
	return 1;
E 6
I 6
	return(1);
E 6
}

D 6
private int check_roomnum (num)
char *num;
E 6
I 6
private int
check_roomnum (num)
char	*num;
E 6
{
	for ( ; *num != '\0' ; num++ ) {
		if (*num == ':' || *num == ',' || !isprint(*num)) {
			return 0;
		}
	}
	return 1;
}

D 6
private int check_phone (phonenum)
char *phonenum;
E 6
I 6
private int
check_phone (phonenum)
char	*phonenum;
E 6
{
	for ( ; *phonenum != '\0' ; phonenum++ ) {
		if (!isdigit (*phonenum) && *phonenum != '-' &&
		    *phonenum != '(' && *phonenum != ')') {
			return 0;
		}
I 6
		/* Space is ok */
E 6
	}
	return 1;
}
/*
 * End %M%
 */
E 1
