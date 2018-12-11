*** ./src/npasswd.h	Tue Sep 23 12:20:28 1997
--- ../beta/src/npasswd.h	Tue Nov 18 16:33:31 1997
***************
*** 3,8 ****
--- 3,11 ----
   *	This cleans up the Makefile
   *
   *	@(#)npasswd.h	1.28 09/23/97
+  *
+  * 09/12/97 MStute	Properly cast pointer-to-function in struct sigblk
+  *			for SIG_TYPE_UNIX signal processing
   */
  
  #define	npasswd_h 1
***************
*** 91,97 ****
   */
  struct sigblk {
  #if	(SIG_TYPE == SIG_TYPE_UNIX)
! 	Signal_t	(*sigvalues[NSIG])();
  #endif
  #if	(SIG_TYPE == SIG_TYPE_POSIX)
  	sigset_t	sigvalues,
--- 94,100 ----
   */
  struct sigblk {
  #if	(SIG_TYPE == SIG_TYPE_UNIX)
! 	Signal_t	(*sigvalues[NSIG])(); /*MRS 09/12/97*/
  #endif
  #if	(SIG_TYPE == SIG_TYPE_POSIX)
  	sigset_t	sigvalues,
