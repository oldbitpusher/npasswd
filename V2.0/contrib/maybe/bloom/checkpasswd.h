
/* --------------------------------------------------------------------  */
/*                                                                       */
/*                         Author: Clyde Hoover                          */
/*                          Computation Center                           */
/*                   The University of Texas at Austin                   */
/*                          Austin, Texas 78712                          */
/*                         clyde@emx.utexas.edu                          */
/*                   uunet!cs.utexas.edu!ut-emx!clyde                    */
/*                                                                       */
/*This code may be distributed freely, provided this notice is retained. */
/*                                                                       */
/* --------------------------------------------------------------------  */
#include <stdio.h>
#include <ctype.h>
#ifdef	SYSV
#include <string.h>
#define index strchr
#else
#include <strings.h>
#endif

#ifdef	_STDC_
extern char	*_flipstring(char *string; int mkcopy);
	/* String flip routine */

#else
extern char	*_flipstring();
	/* String flip routine */

#endif
/*
 *	Return codes from checkpasswd() and pwck_*
 *	Also used as exit codes from main()
 */
#define	PWCK_FAIL      -1	/* Failure during check process */
#define	PWCK_OK		0	/* Password is ok to use */
#define	PWCK_NULL	1 	/* Password is the null string */
#define	PWCK_OBVIOUS	2	/* Password is 'too obvious' */
#define	PWCK_ILLCHAR	3	/* Illegal character in password */
#define	PWCK_SHORT	4	/* Password too short */
#define	PWCK_PASSWD_C   5	/* Constructed from users password info */
#define	PWCK_FINGER_C   6	/* Constructed from users finger info */
#define	PWCK_INDICT	7	/* Password found in a dictionary */
#define	PWCK_INDICT_C   8	/* Constructed from dictionary */

/*
 *	Filter and configuration 
 */

# ifdef	DEBUG
#	define	FILTER_FILE	"checkpasswd.filter" 
# else
#	define	FILTER_FILE	"/usr/adm/checkpasswd.filter"
# endif	/* DEBUG */

#ifndef	CONFIG_FILE
			
# ifdef	DEBUG
#	define	CONFIG_FILE	"checkpasswd.cf" 
# else
#	define	CONFIG_FILE	"/usr/adm/checkpasswd.cf"
# endif	/* DEBUG */

#endif	/*  ! CONFIG_FILE */


/*
 *	Password preferences
 */
int	single_case,		/* Single-case passwords ok or not */
	print_only,		/* Printable characters only */
	run_length,		/* Maximum length of character runs */
	min_length,		/* Minimum password length */
	max_length;		/* Maximum effective length */

#define	sizeof_illegalcc	128
extern char	illegalcc[];		/* Control characters not allowed */

/*
 *	Misc inline subroutine macros
 */

/*	Single string comparasion */
#define try(P,C,V) { \
	if (_cistrcmp((P),(C)) == 0) \
		return(V); \
	}

/*	Multiple string comparasion */
#define mtry(P,C,V) { \
	int i; \
	if ((i = _instring((P),(C),(V))) != PWCK_OK) \
		return(i); \
}

/* Compact string compare */
#define	streq(X,S)	(_cistrncmp((X),(S), strlen(X)) == 0)


/* End checkpasswd.h */
