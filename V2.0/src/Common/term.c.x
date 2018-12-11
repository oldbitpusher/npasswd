
------- term.c -------
*** /tmp/da00924	Wed Dec  8 16:24:09 1999
--- term.c	Tue Jul 27 12:32:59 1999
***************
*** 18,24 ****
  #include "npasswd.h"
  
  #ifndef lint
! static char sccsid[] = "%W% %G% (cc.utexas.edu) %P%";
  #endif
  
  #ifdef	I_TERMIOS
--- 18,24 ----
  #include "npasswd.h"
  
  #ifndef lint
! static char sccsid[] = "@(#)term.c	1.3 07/27/99 (cc.utexas.edu) /usr/share/src/private/ut/share/bin/passwd/V2.0/src/Common/SCCS/s.term.c";
  #endif
  
  #ifdef	I_TERMIOS
***************
*** 242,248 ****
  			break;
  	}
  	*cptr = 0;
! 	return(cin);
  }
  
! /* End %M% */
--- 242,248 ----
  			break;
  	}
  	*cptr = 0;
! 	return(cnt);
  }
  
! /* End term.c */
