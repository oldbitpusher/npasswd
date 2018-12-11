diff -rc ./src/Common/pw_svc.c ../beta/src/Common/pw_svc.c
*** ./src/Common/pw_svc.c	Fri Sep 19 10:58:17 1997
--- ../beta/src/Common/pw_svc.c	Mon Nov 24 18:55:50 1997
***************
*** 6,11 ****
--- 6,15 ----
   *
   * Exported routines
   *	get_pwsvc()
+  *
+  * 09/18/97 MStute	Added local and compat service to NIS get_pwsvc
+  *			service request
+  * 11/14/97 MStute	Added TCB trusted system get_pwsvc
   */
  #ifndef lint
  static char sccsid[] = "@(#)pw_svc.c	1.9 09/19/97 (cc.utexas.edu) /usr/share/src/private/ut/share/bin/passwd/V2.0/src/Common/SCCS/s.pw_svc.c";
***************
*** 25,30 **** APPLIED in ALTERNATE FORM
--- 29,38 ----
  extern char 	*bigcrypt();	/* Really extended encryptor */
  #endif
  
+ #ifdef HPUX_AUTH
+ extern char	*bigcrypt();	/* Really extended encryptor */
+ #endif
+ 
  static struct pw_svc _svcinfo = { 
  	crypt,			/* Password encryptor */
  	sec_std,		/* System security level */
***************
*** 205,211 **** APPLIED
  	char	**svlist;
  
  	_svcinfo.SecurityLevel = sec_std;
! 	debug(DB_LOOKUP, "svc_get nsswitch: ");
  
  	/*
  	 * TODO: Figure out what security level needed for RPC 
--- 213,219 ----
  	char	**svlist;
  
  	_svcinfo.SecurityLevel = sec_std;
! 	debug(DB_LOOKUP, "get_svc nsswitch: ");
  
  	/*
  	 * TODO: Figure out what security level needed for RPC 
***************
*** 236,242 **** APPLIED
  				}
  				_svcinfo.ServiceOrder[svo++] = sv_compat;
  				debug(DB_LOOKUP, "compat/%s ", what);
! 			} else {
  				_svcinfo.ServiceOrder[svo++] = srv_local;
  				_svcinfo.ServiceOrder[svo++] = sv_compat;
  				debug(DB_LOOKUP, "compat/%s ", what);
--- 244,250 ----
  				}
  				_svcinfo.ServiceOrder[svo++] = sv_compat;
  				debug(DB_LOOKUP, "compat/%s ", what);
! 			} else { /*MRS 09/18/98*/
  				_svcinfo.ServiceOrder[svo++] = srv_local;
  				_svcinfo.ServiceOrder[svo++] = sv_compat;
  				debug(DB_LOOKUP, "compat/%s ", what);
***************
*** 265,271 ****		APPLIED IN ALTERNATE FORM
  #undef	SV_FILES
  #undef	SV_PWCOMPAT
  }
! #endif	/* OS_SUNOS_5 */
  
  #ifndef	_SETUP
  /*
--- 273,312 ----
  #undef	SV_FILES
  #undef	SV_PWCOMPAT
  }
! #endif	/* HAS_NSSWITCH */
! 
! #ifdef HAS_TCBDFLT
! #define	_SETUP	1
! /*
!  * get_pwsvc
!  *	Really nothing to do, we already know we have a trusted system
!  *	with a Trusted Computing Base.
!  * Usage
!  *	Call me, I'm easy.
!  */
! public struct pw_svc
! get_pwsvc(argc, argv, envp, svp)
! 	int argc;		/*NOT USED*/
! 	char **argv;		/*NOT USED*/
! 	char **envp;		/*NOT USED*/
! 	struct pw_svc *svp;	/*return pointer if supplied*/
! {
! 	_svcinfo.SecurityLevel = sec_std;
! 	_svcinfo.PasswordCrypt = crypt;
! 	debug(DB_LOOKUP, "get_svc (tcbdflt) : ");
! #  ifdef HPUX_AUTH
! 	_svcinfo.SecurityLevel = sec_HPUXtrusted;
! 	_svcinfo.PasswdCrypt = crypt;	/*not Secureware's bigcrypt*/
! 	debug(DB_LOOKUP,"(security_trusted)\n");
! 
! #  endif /*HPUX_AUTH*/
! 	if(svp) {
! 		*svp = _svcinfo;
! 		return(svp);
! 	}
! 	return(_svcinfo);
! }
! #endif /*HAS_TCBDFLT*/
  
  #ifndef	_SETUP
  /*
