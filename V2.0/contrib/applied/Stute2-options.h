*** ./src/options_h.SH	Tue Sep 23 12:20:51 1997
--- ../beta/src/options_h.SH	Mon Nov 24 18:36:49 1997
***************
*** 26,31 ****
--- 26,32 ----
   * the configuration file.
   *
   * @(#)options_h.SH	1.7 09/23/97 (cc.utexas.edu)
+  * 10/15/97 MStute	Added SLEEPY for ramp up
   */
  
  /*
***************
*** 56,61 ****
--- 57,64 ----
   */
  #undef	DENY_CHSH	/* Define to disable chsh */
  #undef	DENY_CHFN	/* Define to disable chfn */
+ #define SLEEPY	2	/*Ramp-up start period, 0=OFF*/
+ #undef	DICT_DISP	/* Define to enable dict. word display*/
  
  !GROK!THIS
  
