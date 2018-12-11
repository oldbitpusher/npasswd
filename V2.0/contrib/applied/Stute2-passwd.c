*** ./src/passwd.c	Tue Sep 23 12:21:42 1997
--- ../beta/src/passwd.c	Fri Nov 21 12:59:07 1997
***************
*** 3,9 ****
--- 3,13 ----
   *	passwd(1) command.  It can be configured for use with a variety
   *	of passwd systems (/etc/passwd, /etc/shadow, databases).
   *
+  * 09/19/97 MStute	Added sleep ramp up on invalid password tries to
+  *			discourage automated attempts (especially over a modem)
+  * 10/09/97 MStute	Added code for switches d, e, n, and x for HPUX
   */
+ 
  #include "npasswd.h"
  #include "Methods/pwm_defs.h"
  #include "PasswordCheck/checkpasswd.h"
***************
*** 12,18 ****
--- 16,28 ----
  # include <auth.h>
  #endif
  
+ #if	defined(OS_HPUX)
+ # include <hpsecurity.h>
+ # include <prot.h>
+ #endif
+ 
  #ifdef	AIX_AUTH
+ 
  # include <userpw.h>
  # include <usersec.h>
  #endif
***************
*** 114,125 ****
  			die("Permission denied.\n");
  		if (xatoi(Switches['x'], 0, &days) == 0)
  			die("Invalid argument to option -x\n");
! 		newUser->pwage.must_change = ((days + DAYS_WEEK - 1) / DAYS_WEEK) * SEC_WEEK;
  		changes |= CHG_PWAGE;
  		goto updatepw;
  	}
  #endif /* OS_SUNOS_4 */
  
  	if ((perm = can_change_pw(theUser, theCaller)) == deny)
  		die("Permission denied.\n");
  
--- 124,186 ----
  			die("Permission denied.\n");
  		if (xatoi(Switches['x'], 0, &days) == 0)
  			die("Invalid argument to option -x\n");
! 		newUser->pwage.must_change = 
!                        ((days + DAYS_WEEK - 1) / DAYS_WEEK) * SEC_WEEK;
  		changes |= CHG_PWAGE;
  		goto updatepw;
  	}
  #endif /* OS_SUNOS_4 */
+ #ifdef OS_HPUX
+ 		if(Switches['d']) { /*Print aging information*/
+ 		  struct tm *lt;
+ 		  time_t timen = theUser->pwage.last_change * SEC_WEEK;
  
+ 		  lt = (struct tm *)gmtime(&timen);
+ 		  if(theUser->pwage.last_change==0) {
+ 			lt->tm_mon=-1;
+ 			lt->tm_mday=lt->tm_year=0;
+ 	          }
+ 		  printf("%-10s %02d/%02d/%02d %3d %3d\n", theUser->mpw_name,
+ 		  	lt->tm_mon+1, lt->tm_mday, lt->tm_year,
+ 		  	theUser->pwage.can_change,
+ 			theUser->pwage.must_change);
+ 		  return;
+ 		}
+ 		if(Switches['e']) { /*Expire password*/
+ 		  if(myuid)
+ 		  	die("Permission denied.\n");
+ 		  if(!theUser->mpw_age)
+ 			die("Must set password age using the -x option first.\n");
+ 		  newUser->pwage.last_change = 0;
+ 		  changes |= CHG_PWAGE;
+ 		  goto updatepw;
+                 }
+ 		if(Switches['n']) { /*Set maturity*/
+ 		  int days;
+ 
+ 		  if(myuid)
+ 		  	die("Permission denied.\n");
+   		  if(theUser->mpw_age)
+ 		  	  die("Must set password age using the -x option first.\n");
+ 		  if (xatoi(Switches['n'], 0, &days) == 0)
+ 			  die("Invalid argument to option -n\n");
+ 		  newUser->pwage.can_change =
+ 			  ((days + DAYS_WEEK -1 ) / DAYS_WEEK);
+ 		  changes |= CHG_PWAGE;
+ 		  goto updatepw;
+ 		}
+ 		if(Switches['x']) { /* Set expiration time */
+ 		  int days;
+ 		  if(myuid)
+ 			  die("Permission denied\n");
+ 		  if(xatoi(Switches['x'],0,&days)==0)
+ 			  die("Invalid argument to option -n\n");
+ 		  newUser->pwage.can_change=
+ 			  ((days + DAYS_WEEK - 1) / DAYS_WEEK);
+ 		  changes |= CHG_PWAGE;
+ 		  goto updatepw;
+ 		}
+ #endif /*OS_HPUX*/
  	if ((perm = can_change_pw(theUser, theCaller)) == deny)
  		die("Permission denied.\n");
  
***************
*** 198,204 ****
  		strcpy(newUser->password, strdup(newpw1));
  		(void) random_string(salt, sizeof(salt));
  		newUser->mpw_passwd = strdup((*svc.PasswdCrypt)(newpw1, salt));
! 		changes |= CHG_PW;
  		break;
  	}
  
--- 259,265 ----
  		strcpy(newUser->password, strdup(newpw1));
  		(void) random_string(salt, sizeof(salt));
  		newUser->mpw_passwd = strdup((*svc.PasswdCrypt)(newpw1, salt));
! 		changes |= CHG_PW | CHG_PWAGE;
  		break;
  	}
  
***************
*** 243,248 ****
--- 304,310 ----
  	int	ntries = 0;	/* Match attempt counter */
  	int	doit = 1;
  	char	*px;		/* Temp */
+ 	int	naptime=SLEEPY;	/* Time to sleep after bad entry (guess?) */
  
  	while (doit) {
  		if ((px = np_getpass(prompt)) == NULL)
***************
*** 251,258 ****
  			continue;
  		if (!password_cmp(pwd_crypt, px)) {
  			printf("Password incorrect.\n");
! 			if (ntries++ == PasswdMatchTries)
  				die("Password not matched.\n");
  			continue;
  		}
  		doit = 0;
--- 313,328 ----
  			continue;
  		if (!password_cmp(pwd_crypt, px)) {
  			printf("Password incorrect.\n");
! 			if (ntries++ == PasswdMatchTries) {
! #if(SLEEPY)
! 				sleep(naptime);	/*Make 'em wait again*/
! #endif
  				die("Password not matched.\n");
+                         }
+ #if(SLEEPY)
+ 			sleep(naptime);
+ 			naptime = naptime << 1;
+ #endif
  			continue;
  		}
  		doit = 0;
***************
*** 393,398 ****
--- 463,469 ----
  		}
  	}
  #ifdef	ULTRIX_AUTH
+ 	debug(DB_LOOKUP,"svc.SecurityLevel (Ultrix)= %d\n",svc.SecurityLevel);
  	/*
  	 * Check the authorization data for password change permission.
  	 */
***************
*** 423,428 ****
--- 494,500 ----
  	}
  #endif
  #ifdef	OSF1_AUTH
+ 	debug(DB_LOOKUP,"svc.SecurityLevel (OSF)= %d\n",svc.SecurityLevel);
  	/*
  	 * Check the authorization data for password change permission.
  	 */
***************
*** 432,438 ****
  
  		if (pw == NULL)
  			logdie("Cannot get auth data for %s\n",
! 				theUser->mpw_name);
  		if (pw->sflg.fg_pick_pwd) pick = pw->sfld.fd_pick_pwd;
  		if (pw->uflg.fg_pick_pwd) pick = pw->ufld.fd_pick_pwd;
  		if (!pick) {
--- 504,510 ----
  
  		if (pw == NULL)
  			logdie("Cannot get auth data for %s\n",
!      				theUser->mpw_name);
  		if (pw->sflg.fg_pick_pwd) pick = pw->sfld.fd_pick_pwd;
  		if (pw->uflg.fg_pick_pwd) pick = pw->ufld.fd_pick_pwd;
  		if (!pick) {
***************
*** 442,451 ****
--- 514,546 ----
  		}
  	}
  #endif
+ 
+ #ifdef HPUX_AUTH
+ 	debug(DB_LOOKUP,"svc.SecurityLevel (HPUX) = %d\n",svc.SecurityLevel);
+ 	if (svc.SecurityLevel == sec_HPtrusted) {
+ 	/*
+ 	 * Check the authorization data for password change permission
+ 	 */
+ 		struct pr_passwd *pw = 
+                		(struct pr_passwd *)getprpwnam(theUser->mpw_name);
+ 		int	pick = 1;
+ 
+ 		if(pw == NULL)
+ 			logdie("!Cannot get auth data for %s\n", theUser->mpw_name);
+ 		if(pw->sflg.fg_pick_pwd) pick = pw->sfld.fd_pick_pwd;
+ 		if(pw->uflg.fg_pick_pwd) pick = pw->ufld.fd_pick_pwd;
+ 		if(!pick) {
+ 			printf("You must use a system-generated password.\n");
+ 			punt("-a");
+ 			return(deny);
+ 		}
+ 	}
+ #endif
  #ifdef	AIX_AUTH
          /*
           * Check the AIX auth datbase for password flags
           */
+ 	debug(DB_LOOKUP,"svc.SecurityLevel (AIX)= %d\n",svc.SecurityLevel);
          if (strcmp(theUser->mpw_opasswd, "!") == 0) {
                  struct userpw   *upw;
  
