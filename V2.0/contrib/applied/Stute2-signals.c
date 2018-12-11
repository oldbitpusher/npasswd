--- ../beta/src/Common/signals.c	Mon Nov 24 18:55:50 1997
***************
*** 3,8 ****
--- 3,11 ----
   *
   * Compliation: cc -c signals.c
   * Includes: npasswd.h
+  *
+  * 09/18/97 MStute	Added provisions for standard C (sigblk=args)
+  *			Cleaned up BSD block
   */
  
  #define	_signals_c
***************
*** 23,29 ****
  	int	xsig;
  
  	VA_START(fargs, args);
! #ifdef	__STDC__
  	sigblk = args;
  #else
  	sigblk = va_arg(fargs, struct sigblk *);
--- 26,32 ----
  	int	xsig;
  
  	VA_START(fargs, args);
! #ifdef	__STDC__	/*MRS 09/18/97*/
  	sigblk = args;
  #else
  	sigblk = va_arg(fargs, struct sigblk *);
***************
*** 38,45 ****
  
  #if	(SIG_TYPE == SIG_TYPE_BSD)
  	sigblk->savesigs = 0;
! 	while (xsig = va_arg(fargs, int))
  		sigblk->savesigs |= sigmask(xsig);
  	sigblk->sigvalues = sigblock(sigblk->savesigs);
  #endif
  
--- 41,49 ----
  
  #if	(SIG_TYPE == SIG_TYPE_BSD)
  	sigblk->savesigs = 0;
! 	while (xsig = va_arg(fargs, int)) {
  		sigblk->savesigs |= sigmask(xsig);
+         }
  	sigblk->sigvalues = sigblock(sigblk->savesigs);
  #endif
  
