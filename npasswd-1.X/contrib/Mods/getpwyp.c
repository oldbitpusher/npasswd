+ /* Get the current yp pw entry directly from the server */
+ /* only get it once */
+ static passwdp
+ getypent(username)
+ 	char	*username;
+ {
+ 	static passwd	xpwent;
+ 	static int	gotypent = 0;	/* used ONLY in getypent */
+ 	int	vallen;
+ 	int	rc;		/* Return code from ypasswdd */
+ 	char	*val, *p, *index();
+ 
+ 	if (gotypent == 0) {
+ 		passwdp	pwy;
+ 
+ 		rc = yp_match(ypdomain, PASSWD_MAP, username,
+ 			strlen(username), &val, &vallen);
+ 		if (rc) {
+ #if	NO_CLNT_SPERRNO
+ 			clnt_perrno(rc);
+ 			quit(1, "yp_match failed: %d\n", rc);
+ #else
+ 			quit(1, "yp_match failed: %s\n",
+ 				clnt_sperrno(rc));
+ #endif
+ 		}
+ 		pwy = pw_xlate(val, vallen);
+ 		if (pwy == NULL)
+ 			quit(1, "yp pwent syntax error\n");
+ 	/*	free(val); /* */
+ 	/*	if ( p = index(pwy->pw_passwd, ',') )  *p = 0; /* */
+ 		gotypent++;
+ 		_cppasswd(pwy, &yppwent);
+ 	}
+ 	_cppasswd(&yppwent, &xpwent);
+ 	return &xpwent;
+ }
+ 
