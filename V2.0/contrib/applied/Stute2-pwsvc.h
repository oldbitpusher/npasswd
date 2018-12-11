diff -rc ./src/Common/pw_svc.h ../beta/src/Common/pw_svc.h
*** ./src/Common/pw_svc.h	Fri Sep 19 10:58:25 1997
--- ../beta/src/Common/pw_svc.h	Fri Nov 14 15:59:59 1997
***************
*** 2,7 ****
--- 2,8 ----
   *	Defines for using get_svc_conf()
   *
   *	@(#)pw_svc.h	1.4 08/14/96 (cc.utexas.edu)
+  * 11/14/97 MStute	Added HPUX trusted system
   */
  #ifndef	pw_svc_h
  #define	pw_svc_h 1
***************
*** 16,22 ****
  	sec_u4upgrade,		/* Ultrix 4 'upgrade' */
  	sec_u4enhanced,		/* Ultrix 4 'enhanced' */
  	sec_sunC2,		/* SunOS 4 C2 security */
! 	sec_OSFenhanced		/* Digital UNIX (OSF/1) enhanced */
  };
  
  /*
--- 17,24 ----
  	sec_u4upgrade,		/* Ultrix 4 'upgrade' */
  	sec_u4enhanced,		/* Ultrix 4 'enhanced' */
  	sec_sunC2,		/* SunOS 4 C2 security */
! 	sec_OSFenhanced,	/* Digital UNIX (OSF/1) enhanced */
! 	sec_HPtrusted		/* HPUX trusted system*/
  };
  
  /*
