
/* --------------------------------------------------------------------  */
/*                                                                       */
/*                Author: Victor Burns  TI FDAO                          */
/*                                                                       */
/* --------------------------------------------------------------------  */
/*
 *	pwck_vicb - Perform MY SPECIAL CHECKS!
 *
 *		1) No number at beginning or end unles both or
 *		   one in the middle exist too.
 *
 *	Returns:
 *		PWCK_OBVIOUS if <password> fails any of the above
 *		PWCK_FAIL if failure to get the username
 *		PWCK_OK if otherwise
 */

#include "pwck_defines.h"
#include <pwd.h>

static char	My_msg_buf[500];

public char *
pwck_vicb(password, user)
char	*password;	/* Password to check */
struct passwd   *user;
{
	char	*mesg = My_msg_buf;	/* Message buffer */

	char	*p, *pe;

	int	alpha = 0,		/* Count of alphabetics */
		num_sp = 0;		/* Count of numbers/specials */

	debug(DB_PWCHECK, "pwck_strong: \"%s\" length(%d)\n", password, strlen(password));

       /*
	*  Check for NUMBER on only one end.
	*/

	/* we assume that the passwd is greater than or equal to 3 char */
	for( pe=password ; *pe ; pe++ ); pe--;	/* point to last char in password */
	if(!isalpha(*pe)) pe--; pe--;
	if(pe<password) pe=password;

	debug(DB_PWCHECK, "pwck_strong: passwd-end \"%s\"\n", pe);

	p=password; p++;
	if(!isalpha(*password)) p++;
	for ( ; *p ; p++ ) {
		if (isalpha(*p))
			alpha++;
		else if ((isdigit(*p) || ispunct(*p) || isspace(*p)) && (p<=pe))
			num_sp++;
	}

	/* point to last char in password */
	p--;

	/* A number on both ends is OK */
	/* assume *p is last char in password */
	debug(DB_PWCHECK, "pwck_strong: check non-alpha on both ends.\n");
	if (( isdigit(*password) || ispunct(*password) || isspace(*password)) &&
	    ( isdigit(*p) || ispunct(*p) || isspace(*p))) return(PWCK_OK);

	/* A number on any end with a number in the middle is ALSO ok */
	if ( num_sp ) debug(DB_PWCHECK, "pwck_strong: info: non-alpha in middle\n");
	if ( num_sp ) return(PWCK_OK);

	/* No non-alpha */
	if ( isalpha(*password) & isalpha(*p) )
	{
	   (void) strcpy( mesg, " A password requires a non-alpha in the middle or on both ends");
	   debug(DB_PWCHECK, "pwck_strong: No-non-alpha: %s\n", mesg );
	   return(mesg);
	}

	/* A non-alpha on only ONE end is forbidden */
	if ( isdigit(*password) || ispunct(*password) || isspace(*password) ||
	     isdigit(*p) || ispunct(*p) || isspace(*p) )
	{
	   (void) strcpy( mesg, " A password requires a non-alpha in the middle or on both ends");
	   debug(DB_PWCHECK, "pwck_strong: One-non-alpha: %s\n", mesg );
	   return(mesg);
	}

	return(PWCK_OK);
}
/*	End pwck_vicb.c */
