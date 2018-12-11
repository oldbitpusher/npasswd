*** ./src/Methods/pwm_nis.c	Tue Sep 23 12:28:51 1997
--- ../beta/src/Methods/pwm_nis.c	Mon Nov 24 18:26:57 1997
***************
*** 19,24 ****
--- 19,29 ----
   *
   * Compilation flags
   *	cc -I.. ... -lrpcsvc
+  *
+  * 10/16/97 MStute Changed the cpw variable from 8 to 9 characters to
+  *		   make room for the zero terminator
+  * 11/21/97 MStute Added support for password lengths longer then 8
+  *
   */
  #if	defined(OS_SUNOS_5) && (OS_MINOR_VERSION < 5)
  # define	NO_STRINGS		/* Work around <strings.h> bug */
***************
*** 65,70 ****
--- 70,79 ----
  # define YP_PROBE_TIMEOUT 2			/* Timeout for YP probing */
  #endif
  
+ #ifndef NIS_PASSWD_MAX_LEN
+ #define NIS_PASSWD_MAX_LEN	9		/*NIS max password length
+ 						  plus zero terminator*/
+ #endif
  /*
   * Possible locations for YP data directory
   */
***************
*** 249,261 ****
  	int	tries;		/* How many tries to call yppasswdd */
  	int	why;		/* RPC call return code */
  	int	ypport;		/* Port for RPC call */
! 	char	cpw[8];		/* Buffer for current password (cleartext) */
  	struct yppasswd yppasswd; /* YP passwd change block */
  	struct pw_opaque *aux = (struct pw_opaque *)theUser->opaque;
  
  	if (theUser->password[0] == 0 && theUser->mpw_passwd[0]) /* XXX */
  		die("Cannot change passwd info via NIS without old password.\n");
! #ifdef	PWAGE
  	/*
  	 * Update password aging information
  	 */
--- 258,277 ----
  	int	tries;		/* How many tries to call yppasswdd */
  	int	why;		/* RPC call return code */
  	int	ypport;		/* Port for RPC call */
! 	char	cpw[NIS_PASSWD_MAX_LEN]; 
! 		/* ^- Buffer for current password (cleartext) */
  	struct yppasswd yppasswd; /* YP passwd change block */
  	struct pw_opaque *aux = (struct pw_opaque *)theUser->opaque;
  
+ #ifdef PWAGE
+ #ifdef OS_HPUX
+ 			char szAge[12];
+ #endif
+ 
+ #endif
  	if (theUser->password[0] == 0 && theUser->mpw_passwd[0]) /* XXX */
  		die("Cannot change passwd info via NIS without old password.\n");
! #ifdef PWAGE
  	/*
  	 * Update password aging information
  	 */
***************
*** 270,292 ****
  
  			if (changes & CHG_PW)
  				now = time((time_t *)0) / SEC_WEEK;
  			pwage = newUser->pwage.must_change
  				+ (newUser->pwage.can_change << 6)
  				+ (now << 12);
  			if (pwage)
  				newUser->mpw_age = l64a(pwage);
! 			else
  				newUser->mpw_age = ".";
  		}
  	}
! #endif
  	(void) strncpy(cpw, theUser->password, sizeof(cpw));
! 	cpw[8] = 0;
  	yppasswd.oldpass = cpw;
  	copypwent(&newUser->pw, &yppasswd.newpw);
  
  	debug(DB_UPDATE, "put_yp_user: yppasswd(%s, %s)\n",
  		cpw, yppasswd.newpw.pw_passwd);
  #ifndef	DEBUG_NOEXEC
  #ifndef	OS_SUNOS_5
  	if ((ypport = getrpcport(ypinfo.master, YPPASSWDPROG,
--- 286,326 ----
  
  			if (changes & CHG_PW)
  				now = time((time_t *)0) / SEC_WEEK;
+ #ifdef OS_HPUX
+ 			strcpy(szAge,l64a(newUser->pwage.must_change));
+ 			if(newUser->pwage.can_change)
+ 				strcat(szAge,l64a(newUser->pwage.can_change));
+ 			else
+ 				strcat(szAge,".");
+ 			strcat(szAge,l64a(now));
+ 
+ 			if(strlen(szAge))
+ 				strcpy(newUser->mpw_age,szAge);
+ 				
+ 			else
+ 				newUser->mpw_age=".";
+ 
+ #else /*HPUX Aging code*/
  			pwage = newUser->pwage.must_change
  				+ (newUser->pwage.can_change << 6)
  				+ (now << 12);
  			if (pwage)
  				newUser->mpw_age = l64a(pwage);
! 			else  /*on HPUX l64a(0) = "\0"*/
  				newUser->mpw_age = ".";
+ #endif /*Generic Age code*/
+ 
  		}
  	}
! #endif /*PWAGE*/
  	(void) strncpy(cpw, theUser->password, sizeof(cpw));
! 	cpw[NIS_PASSWD_MAX_LEN] = 0;
  	yppasswd.oldpass = cpw;
  	copypwent(&newUser->pw, &yppasswd.newpw);
  
  	debug(DB_UPDATE, "put_yp_user: yppasswd(%s, %s)\n",
  		cpw, yppasswd.newpw.pw_passwd);
+ 
  #ifndef	DEBUG_NOEXEC
  #ifndef	OS_SUNOS_5
  	if ((ypport = getrpcport(ypinfo.master, YPPASSWDPROG,
