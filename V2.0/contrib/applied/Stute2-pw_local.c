*** ./src/Methods/pwm_local.c	Tue Sep 23 12:27:28 1997
--- ../beta/src/Methods/pwm_local.c	Mon Nov 24 18:32:55 1997
***************
*** 17,22 ****
--- 17,29 ----
   *
   * Compilation flags
   *	cc -I.. -I../Common ...
+  * 
+  * 09/18/97 MStute	Added support for PWCOMMENT in update_dbm_passwd
+  *			Added code for DEC OSF1 to handle multiple entries
+  *			separated by NLs in put_local_user (from T. Nau)
+  * 10/17/97 MStute	Added HPUX PWAGE code
+  *			
+  *			
   */
  #include "npasswd.h"
  #include "pwm_defs.h"
***************
*** 105,110 ****
--- 112,131 ---- APPLIED
  	(void) copypwent(pwinfo, &mp->pw);
  	get_shadow(mp);
  #ifdef	PWAGE
+ #ifdef	OS_HPUX
+ 	if(mp->mpw_age && *mp->mpw_age) {	/*MRS 10/97*/
+ 		extern long a64l();
+ 		char temp[10],*tmpAge;	/*ACME*/
+ 
+ 		temp[0] = mp->mpw_age[0];	/*QUICK and dirty*/
+ 		temp[1] = '\0';
+ 		mp->pwage.must_change = a64l(temp);
+ 		temp[0]=mp->mpw_age[1];
+ 		mp->pwage.can_change = a64l(temp);
+ 		tmpAge=&(mp->mpw_age[2]);	/*The portable way*/
+ 		mp->pwage.last_change = a64l(tmpAge);
+         }
+ #else /* end of HPUX*/
  	if (mp->mpw_age && *mp->mpw_age) {
  		time_t pwage = 0;
  		extern long	a64l();
***************
*** 114,120 ****
  		mp->pwage.can_change = ((pwage >> 6) & 077) * SEC_WEEK;
  		mp->pwage.last_change = (pwage >> 12) * SEC_WEEK;
  	}
! #endif
  	return(1);
  }
  
--- 135,147 ----
  		mp->pwage.can_change = ((pwage >> 6) & 077) * SEC_WEEK;
  		mp->pwage.last_change = (pwage >> 12) * SEC_WEEK;
  	}
! #endif /* Generic age code */
! 		debug(DB_DETAIL,"Must change: %ld\nCan Change: %ld\nLast Change: %ld\n",
! 			mp->pwage.must_change,
! 			mp->pwage.can_change,
! 			mp->pwage.last_change);
! 
! #endif /* if PWAGE */
  	return(1);
  }
  
***************
*** 212,218 ****
  	struct passwd	*px;	/* Password file traversal */
  	struct pw_opaque *aux = (struct pw_opaque *)theUser->opaque;
  	struct sigblk	blocked;
! 
  	if (changes == 0)
  		logdie("Error: put_local_user called with null changes\n");
  
--- 239,247 ---- APPLIED
  	struct passwd	*px;	/* Password file traversal */
  	struct pw_opaque *aux = (struct pw_opaque *)theUser->opaque;
  	struct sigblk	blocked;
! #ifdef OS_HPUX
! 	char szAge[12];		/* ACME */
! #endif
  	if (changes == 0)
  		logdie("Error: put_local_user called with null changes\n");
  
***************
*** 220,225 ****
--- 249,258 ---- APPLIED
  	/*
  	 * Update password aging information
  	 */
+ 
+ 	debug(DB_DETAIL,"Updating age\nChanges: %d\nAge: %ld\n",
+ 		changes & CHG_PWAGE,newUser->pwage.must_change);
+ 
  	if (changes & CHG_PWAGE) {
  		if (newUser->pwage.must_change == 0) {
  			newUser->mpw_age = '\0';
***************
*** 231,236 ****
--- 264,282 ---- APPLIED
  
  			if (changes & CHG_PW)
  				now = time((time_t *)0) / SEC_WEEK;
+ #ifdef OS_HPUX		
+ 			strcpy(szAge,l64a(newUser->pwage.must_change));
+ 			if(newUser->pwage.can_change)
+ 			  strcat(szAge,l64a(newUser->pwage.can_change));
+ 			else
+ 			  strcat(szAge,".");
+ 			strcat(szAge,l64a(now));
+ 			debug(DB_DETAIL,"HPUX Age=&s\n",szAge);
+ 			if(strlen(szAge))
+ 			  strcpy(newUser->mpw_age,szAge);
+ 			else
+ 			  newUser->mpw_age=".";
+ #else
  			pwage = newUser->pwage.must_change
  				+ (newUser->pwage.can_change << 6)
  				+ (now << 12);
***************
*** 238,243 ****
--- 284,290 ---- APPLIED
  				newUser->mpw_age = l64a(pwage);
  			else
  				newUser->mpw_age = ".";
+ #endif /*Generic age*/
  		}
  	}
  #endif	/* PWAGE */
***************
*** 306,312 ****
--- 354,386 ----	DENIED
  #ifndef	DEBUG
  	block_signals(&blocked, SIGHUP, SIGINT, SIGQUIT, SIGTSTP, 0);
  #endif
+ 	/*MRS 9/97 Added DEC OSF1 code for NIS entries
+ 		   for testing. Check them since I don't
+ 		   have a clue why Thomas did this.
+         */
+ 
+ #ifdef OS_DEC_OSF1
+ 	while(1) {
+ 	  int c;
+ 
+ 	  /*handle NIS entries*/
+ 	  if((c=getc(pf)=='+') {
+ 		/*copy line*/
+ 	    for(;c!='\n' && c!=EOF;c=getc(pf))
+ 		putc(c,tf);
+   	    if(c=='\n')
+ 		  putc(c,tf);
+ 	    continue;
+ 	  } 
+ 	  if(c==EOF)
+ 	    break;
+ 	  ungetc(c,pf);
+ 	  if((px=fgetpwent(pf))!=NULL)
+ 	    break;
+ #else
+ 
  	while ((px = fgetpwent(pf)) != NULL) {
+ #endif 
  		if (px->pw_name == 0 || px->pw_name[0] == 0) /* Sanity check */
  			continue;
  		if (!repdone && strcmp(px->pw_name, theUser->mpw_name) == 0) {
