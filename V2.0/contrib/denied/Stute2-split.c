diff -rc ./src/Common/split.c ../beta/src/Common/split.c
*** ./src/Common/split.c	Wed Aug  7 15:22:45 1996
--- ../beta/src/Common/split.c	Mon Nov 24 18:55:50 1997
***************
*** 132,139 ****
  			qcx = *s_token;
  			*s_token++ = '\0';
  			e_token++;
! 			while (*e_token && *e_token != qcx)
  				*e_token++;
  			/* ERROR - e_token null (no closing quote) */
  		} else {
  			if (separator)
--- 132,140 ----
  			qcx = *s_token;
  			*s_token++ = '\0';
  			e_token++;
! 			while (*e_token && *e_token != qcx) {
  				*e_token++;
+                         }
  			/* ERROR - e_token null (no closing quote) */
  		} else {
  			if (separator)
