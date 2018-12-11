*** ./src/compatibility.h	Tue Sep 23 14:08:04 1997
--- ../beta/src/compatibility.h	Thu Nov 13 16:02:16 1997
***************
*** 1,6 ****
--- 1,8 ----
  /*
   *	Comptability and option selection defines for npasswd
   *	@(#)compatibility.h	1.17 09/23/97 /usr/share/src/private/ut/share/bin/passwd/V2.0/src/SCCS/s.compatibility.h
+  *	09/19/97 MStute   Set up POSIX signals and SIG_LOCK for SVR4 systems.
+  *			  T. Nai orignially fixed the problem for SunOS4
   */
  #ifndef	_compatibility_h
  #define	_compatibility_h 1
***************
*** 95,104 ****
--- 97,109 ----
  #define	SIG_TYPE_UNIX	'u'	/* Use traditional UNIX signals */
  
  #define	SIG_TYPE		SIG_TYPE_UNIX
+ 
+ 	/*MRS 09/97*/
  #ifdef	HAS_SIGBLOCK
  # undef	SIG_TYPE
  # define	SIG_TYPE	SIG_TYPE_BSD
  #endif
+ 
  #ifdef	HAS_POSIX_SIGNALS
  # undef	SIG_TYPE
  # define	SIG_TYPE	SIG_TYPE_POSIX
