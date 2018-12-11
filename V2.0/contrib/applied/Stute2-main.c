*** ./src/main.c	Tue Sep 23 12:22:02 1997
--- ../beta/src/main.c	Fri Nov 21 15:59:51 1997
***************
*** 2,7 ****
--- 2,9 ----
   *	This program duplicates the manual page behavior of the 4.XBSD
   *	passwd(1) command.  It can be configured for use with a variety
   *	of passwd systems (/etc/passwd, /etc/shadow, databases).
+  *
+  * 10/09/97 Mstute	Implemented d, e, n, and x switches for HPUX
   */
  
  #include "npasswd.h"
***************
*** 14,19 ****
--- 16,25 ----
  #ifdef	OS_SUNOS_4
  # define	SWITCHES_OS "alyd:e:n:x:F:"
  #endif
+ 		/*MRS 10/09/97*/
+ #ifdef OS_HPUX
+ #define		SWITCHES_OS "den:x:"
+ #endif
  
  /*
   * Global variables
***************
*** 86,92 ****
  		(void) strncpy(savedname, pwtemp->pw_name, sizeof(savedname));
  		temp = savedname;
  	}
! 	(void) strcpy(CallerLogin, temp);
  	if ((pwtemp = getpwnam(CallerLogin)) == NULL)
  		logdie("Cannot get user identification from name.\n");
  	if (pwtemp->pw_uid != CallerUid && CallerUid) {
--- 92,99 ----
  		(void) strncpy(savedname, pwtemp->pw_name, sizeof(savedname));
  		temp = savedname;
  	}
! 
! 	(void) strncpy(CallerLogin, temp,sizeof(CallerLogin));
  	if ((pwtemp = getpwnam(CallerLogin)) == NULL)
  		logdie("Cannot get user identification from name.\n");
  	if (pwtemp->pw_uid != CallerUid && CallerUid) {
***************
*** 292,297 ****
--- 299,318 ----
  		case 'F':
  			printf("Option \"-F\" not supported.\n");
  			exit(1);
+ #endif
+ #ifdef OS_HPUX
+ 		case 'n':
+ 			Switches[(char)opt] = strdup(optarg);
+ 			break;
+ 		case 'x':
+ 			Switches[(char)opt] = strdup(optarg);
+ 			break;
+ 		case 'd':
+ 			Switches[(char)opt] = "on";
+ 			break;
+ 		case 'e':
+ 			Switches[(char)opt] = "on";
+ 			break;
  #endif
  		case 'f':
  			what_to_do = CHFN;
