*** ./src/chfn.c	Mon May  5 10:35:04 1997
--- ../beta/src/chfn.c	Fri Nov 21 11:10:18 1997
***************
*** 93,99 ****
  			field--;
  			continue;
  		} else if (*inbuf == '\0') {
! 			(void) strcpy(inbuf, gptr->oldvalue);
  		} else if (strcasecmp(inbuf, "none") == 0) {
  			inbuf[0] = 0;
  		} else {
--- 93,99 ----
  			field--;
  			continue;
  		} else if (*inbuf == '\0') {
! 			(void) strncpy(inbuf, gptr->oldvalue,sizeof(inbuf));
  		} else if (strcasecmp(inbuf, "none") == 0) {
  			inbuf[0] = 0;
  		} else {
