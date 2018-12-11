diff -rc ./src/Common/messages.c ../beta/src/Common/messages.c
*** ./src/Common/messages.c	Tue Sep 23 12:30:39 1997
--- ../beta/src/Common/messages.c	Mon Nov 24 18:55:50 1997
***************
*** 1,5 ****
--- 1,7 ----
  /*
   * Message routines used by npasswd and checkpasswd
+  *
+  * 11/21/97 MStute	Removed all debugging if compiling non-DEBUG
   */
  #ifndef lint
  static char sccsid[] = "@(#)messages.c	1.6 09/23/97 (cc.utexas.edu) /usr/share/src/private/ut/share/bin/passwd/V2.0/src/Common/SCCS/s.messages.c";
***************
*** 20,25 ****
--- 22,28 ----
  #ifdef	__STDC__
  debug (int level, char *fmt, ...)
  {
+ #ifdef DEBUG
  	va_list	args;
  
  	if (DebugLevel < level)
***************
*** 28,38 ****
--- 31,43 ----
  	vprintf(fmt, args);
  	fflush(stdout);
  	va_end(args);
+ #endif
  }
  #else	/* __STDC__ */
  debug (va_alist)
  va_dcl
  {
+ #ifdef DEBUG
  	va_list	args;
  	int	level;
  	char	*fmt;
***************
*** 45,50 ****
--- 50,56 ----
  		fflush(stdout);
  	}
  	va_end(args);
+ #endif
  }
  #endif
  
