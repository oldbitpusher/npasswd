/*
 * Copyright 1998, The University of Texas at Austin ("U. T. Austin").
 * All rights reserved.
 *
 * By using this software the USER indicates that he or she has read,
 * understood and will comply with the following:
 *
 * U. T. Austin hereby grants USER permission to use, copy, modify, and
 * distribute this software and its documentation for any purpose and
 * without fee, provided that:
 *
 * 1. the above copyright notice appears in all copies of the software
 *    and its documentation, or portions thereof, and 
 * 2. a full copy of this notice is included with the software and its
 *    documentation, or portions thereof, and 
 * 3. neither the software nor its documentation, nor portions thereof,
 *    is sold for profit. Any commercial sale or license of this software,
 *    copies of the software, its associated documentation and/or
 *    modifications of either is strictly prohibited without the prior
 *    consent of U. T. Austin. 
 * 
 * Title to copyright to this software and its associated documentation
 * shall at all times remain with U. T. Austin. No right is granted to
 * use in advertising, publicity or otherwise any trademark, service
 * mark, or the name of U. T. Austin.
 * 
 * This software and any associated documentation are provided "as is,"
 * and U. T. AUSTIN MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESSED OR
 * IMPLIED, INCLUDING THOSE OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR
 * PURPOSE, OR THAT USE OF THE SOFTWARE, MODIFICATIONS, OR ASSOCIATED
 * DOCUMENTATION WILL NOT INFRINGE ANY PATENTS, COPYRIGHTS, TRADEMARKS OR
 * OTHER INTELLECTUAL PROPERTY RIGHTS OF A THIRD PARTY. U. T. Austin, The
 * University of Texas System, its Regents, officers, and employees shall
 * not be liable under any circumstances for any direct, indirect, special,
 * incidental, or consequential damages with respect to any claim by USER
 * or any third party on account of or arising from the use, or inability
 * to use, this software or its associated documentation, even if U. T.
 * Austin has been advised of the possibility of those damages.
 * 
 * Submit commercialization requests to: Office of the Executive Vice
 * President and Provost, U. T. Austin, 201 Main Bldg., Austin, Texas,
 * 78712, ATTN: Technology Licensing Specialist.
 */
/*
 * pwck_main.c
 *	Password check library entry point
 *
 * Exported routines
 *	checkpassword()			Public
 *	checkpassword_init()		Public
 *	checkpassword_configure()	Public
 *
 * Exported variables
 *	Config				libpwcheck modules
 *
 * The 'pwck_*' routines return a string telling why the password
 * is not acceptable, or (char *)0 if it's ok
 *
 * The pwck_* routines are called thusly:
 *	message = pwck_foo(char *, struct passwd *)
 */

#ifndef lint
static char sccsid[] = "@(#)pwck_main.c	1.33 10/13/98 (cc.utexas.edu)";
#endif

#include "pwck_defines.h"

private int	add_one_dict _((char *));
private int	add_all_dicts _((char *));
private char	*add_proc _((char *));
private char	*check_procs();

/*
 * Default checkpasswd configuration
 */
private char	*_default_config[] = {
	"PasswordChecks	lexical passwd local strong history dictionary",
	"MaxRepeat 	3",		/* How long chars runs can be */
#ifdef	SYSTEM_PASSWD_MIN
	"MinPassword 	SYSTEM_PASSWD_MIN",	/* Minimum length */
#else
	"MinPassword 	6",		/* Minimum length */
#endif
#ifdef	SYSTEM_PASSWD_MAX
	"MaxPassword 	SYSTEM_PASSWD_MAX",	/* Maximum effective length */
#else
	"MaxPassword 	8",		/* Maximum effective length */
#endif
	"Dictionaries	@",		/* Where default dictionaries live */
	"PrintableOnly 	no",		/* Allow control chars */
	"WhiteSpace 	yes",		/* Allow whitespace */
	/*
	 * The next three defaults interlock:
	 */
	"SingleCase	yes",		/* Allow single case alpha */
	"AlphaOnly	yes",		/* Allow alpha only */
	"CharClasses	1",		/* Minimum required character classes */
	0
};

/*
 *	Control characters best avoided - commonly-used terminal controls.
 *	Add characters here or replace entire contents via the
 *	configuration file.
 */
#define	ctrl(d)	((d) & 037)

char	_illchar[] = {
	ctrl('c'),	/* Interrupt character */
	ctrl('d'),	/* UNIX end-of-file */
	ctrl('h'),	/* Backspace */
	ctrl('j'),	/* Newline */
	ctrl('m'),	/* Carriage return */
	ctrl('o'),	/* Flush output */
	ctrl('r'),	/* Retype pending input */
	ctrl('s'),	/* Suspend output */
	ctrl('q'),	/* Resume output */
	ctrl('y'),	/* Suspend program deferred */
	ctrl('z'),	/* Suspend program immediate */
	ctrl('\\'),	/* Quit signal */
	ctrl('['),	/* escape - may do strange things to ttys if echoed */
	ctrl(']'),	/* UNIX telnet escape */
	'\177',		/* rubout */
	0
};
#undef	ctrl

/*
 * This is the table of password check routines
 * Additional checks can be added to this table
 */
struct _procnames {
	char		*name;		/* Function name */
	checkproc	addr;		/* Address */
	int		mandatory;	/* Is this check mandatory? */
};
private struct _procnames procnames[] = {
	{ "lexical",	pwck_lexical,	1 },
	{ "local",	pwck_local,	0 },
	{ "passwd",	pwck_passwd,	1 },
	{ "strong",	pwck_vicb,	0 },
	{ "dictionary",	pwck_crack,	0 },
	{ "history",	pwck_history,	1 },
	0
};

/*
 * The checkpasswd configuration block
 */
public struct checkpassword_config	Config = { 0 };

/*
 * checkpassword_probe
 *	Print the state of the password check system to stdout
 * Usage:
 *	checkpassword_probe(char *message-prefix)
 */
public void
checkpassword_probe(prefix)
	char	*prefix;
{
	int	i;
	char	*p;
	checkproc	*c;
	char	tn[STRINGLEN];

	(void) sprintf(tn, "%sHistory\t", prefix);
	pwck_history_probe(tn);

	printf("%sAlphaOnly\t%s\n", prefix, Config.alpha_only ? "yes" : "no");
	printf("%sCharClasses\t%d\n", prefix, Config.char_classes);
	printf("%sDisallowedChars\t", prefix);
	for (p = Config.badchars; *p; p++) {
		printf("%s ", ctran(*p));
	}
	printf("\n");
	printf("%sLengthWarn\t%s\n", prefix,
		Config.length_warn ? "yes" : "no");

	printf("%sMaxPassword\t%d\n", prefix, Config.max_length);
	printf("%sMaxRepeat\t%d\n", prefix, Config.run_length);
	printf("%sMinPassword\t%d\n", prefix, Config.min_length);

	printf("%sPasswordChecks\t", prefix);
	for (c = Config.checkprocs; *c; c++) {
		struct _procnames	*pn;

		for (pn = procnames; pn->name; pn++) {
			if (pn->addr == *c)
				printf("%s ", pn->name);
		}
	}
	printf("\n");

	printf("%sPrintOnly\t%s\n",
		prefix, Config.print_only ? "yes" : "no");
	printf("%sSingleCase\t%s\n",
		prefix, Config.single_case ? "yes" : "no");
	printf("%sWhiteSpace\t%s\n",
		prefix, Config.whitespace ? "yes" : "no");

	printf("%sDictionaries\n", prefix);
	for (i = 0; Config.dictionaries[i]; i++) {
		printf("\t%s\n", Config.dictionaries[i]);
	}
}

/*
 * checkpassword
 *	Password sanity checker
 *
 * Usage
 *	ok = checkpassword(char *password, struct passwd *user);
 *
 * Returns
 *	(char *)0 if the password is ok to use
 *	Message why not if not
 */
public char *
checkpassword(password, user)
	char		*password;	/* Candidate password */
	struct passwd	*user;		/* Passwd entry for target user */
{
	char		*rmsg;
	checkproc	*checkfunc;	/* Check function pointer */
	static char	xpasswd[BUFSIZ];	/* Temporary storage for candidate */

	if (Config.initialized == 0)
		checkpassword_init();
	debug(DB_PWCHECK,
		"checkpassword: name=%s passwd=\"%s\"\n",
		user->pw_name, password);
	if (password == 0 || *password == 0) {	/* Empty password */
		debug(DB_PWCHECK, "checkpassword: Null password\n");
		return(PWCK_NULL);
	}
	/*
	 * Cut to length *after* checkpasword_init(),
	 * since max_length should be set therein.
	 *
	 * The original is *not* chopped, because it may well be read-only.
	 * Also, there can be a skew between what this code thinks the
	 * maximum functional password length is, and what it really is.
	 */
	(void) strncpy(xpasswd, password, sizeof xpasswd);
	xpasswd[ (sizeof xpasswd) - 1] = 0;
	if (Config.max_length) {
		/*
		 * Only the first <max_length> characters of a password are
		 * actually used by crypt(3).  If the given password is longer
		 * than this, issue warning message.
		 * This test logically belongs in pwck_lexical, but
		 * the password is chopped here.
		 *
		 * The test is disabled by default.
		 * This message gets some users get very confused.
		 */
		if (strlen(password) > Config.max_length && Config.length_warn) {
			warn("Only the first %d characters of this password will be used\n",
				Config.max_length);
		}
		xpasswd[Config.max_length] = 0;
	}

	for (checkfunc = Config.checkprocs; *checkfunc; checkfunc++) {
		debug(DB_PWCHECK, "checkpassword: func=%x\n", *checkfunc);
		if ((rmsg = (*checkfunc)(xpasswd, user)) != PWCK_OK) {
			debug(DB_PWCHECK,
				"checkpassword: return \"%s\"\n", rmsg);
			return(rmsg);
		}
	}
	debug(DB_PWCHECK, "checkpassword: password OK\n");
	return(PWCK_OK);
}

/*
 * checkpassword_init 
 *	Reset configuration to builtin defaults
 *
 * Usage
 *	checkpassword_init();
 */
public void
checkpassword_init()
{
	char	**cfi;	/* Internal config "file" */

	if (Config.initialized)
		return;
	/*
	 * Clear the config block
	 */
	zeromem(&Config, sizeof Config);

	/*
	 * Copy the default bad character list into the config block
	 */
#ifdef	HAS_MEMCPY
	memcpy((void *)Config.badchars, (void *)_illchar, sizeof(_illchar));
#else
	bcopy(_illchar, Config.badchars, sizeof(_illchar));
#endif
	/*
	 * Reinstantiate the built-in settings
	 */
	for (cfi = _default_config; *cfi; cfi++) {
		char	cfbuf[BUFSIZ];			/* Temporary */
		char	*cferror;

		(void) strcpy(cfbuf, *cfi);
		if (cferror = checkpassword_configure(cfbuf, 1)) {
			logdie("checkpassword_init setup error h%s] on \"%s\"",
				cferror, *cfi);
		}
	}
	Config.initialized = 1;
	(void) get_pwsvc();
	debug(DB_CONFIG, "checkpassword_init: done\n");
}

/*
 * checkpassword_verify 
 *	Verify that checkpassword is properly configured
 *	Returns nastygram if config error
 * Usage
 *	checkpassword_verify();
 */
public char *
checkpassword_verify()
{
	if (Config.dictionaries[0] == 0)
		return("No dictionaries found\n");
	return(0);
}

/*
 * checkpassword_configure
 *	Process a configuration directive
 *
 * Usage
 *	ok = checkpassword_configure(char *string, int flag-error);
 * Returns
 *	(char *)0 if directive was recognized and processed correctly
 *	error message otherwise
 */
public char *
checkpassword_configure(cfline, flagerror)
	char	*cfline;	/* Directive to process */
	int	flagerror;	/* Flag unknown directives as error? */
{
	/* Normal return macro.  Makes sure that <data> is freed */
#define	cf_ok	{ if (data) free((char *)data); return(0); }

	char	**data = 0,		/* Line split pointer array */
		*dot,			/* ACME Temp Storage INC */
		*item;			/* ACME Temp Storage INC */

	if (*cfline == '\n' || *cfline == '#')	/* Empty line or comment */
		cf_ok;

	if ((data = split(cfline, 0, 0, 0)) == 0)
		return("Line did not parse");

	if (dot = strrchr(data[0], '.'))	/* Ignore up to last '.' */
		item = ++dot;
	else
		item = data[0];
	debug(DB_CONFIG, "checkpassword_configure: [%s]\n", item);
#define	check_arg(_V_) { if (data[_V_] == 0) return("Missing value"); }
	/*
	 * Token matching
	 */
	if (strcasecmp(item, "singlecase") == 0) {
		check_arg(1);
		Config.single_case = decode_boolean(data[1]);
		cf_ok;
	}
	if (strcasecmp(item, "lengthwarn") == 0) {
		check_arg(1);
		Config.length_warn = decode_boolean(data[1]);
		cf_ok;
	}
	if (strcasecmp(item, "alphaonly") == 0) {
		check_arg(1);
		Config.alpha_only = decode_boolean(data[1]);
		cf_ok;
	}
	if (strcasecmp(item, "minpassword") == 0) {
		check_arg(1);
		Config.min_length = decode_int(data[1]);
		cf_ok;
	}
	if (strcasecmp(item, "maxpassword") == 0) {
		check_arg(1);
		Config.max_length = decode_int(data[1]);
		cf_ok;
	}
	if (strcasecmp(item, "maxrepeat") == 0) {
		check_arg(1);
		Config.run_length = decode_int(data[1]);
		cf_ok;
	}
	if (strcasecmp(item, "debug") == 0) {
		check_arg(1);
		set_debug(data[1], 0);
		cf_ok;
	}
	if (strcasecmp(item, "printableonly") == 0) {
		check_arg(1);
		Config.print_only = decode_boolean(data[1]);
		cf_ok;
	}
	if (strcasecmp(item, "whitespace") == 0) {
		check_arg(1);
		Config.whitespace = decode_boolean(data[1]);
		cf_ok;
	}
	if (strcasecmp(item, "dictionaries") == 0) {
		char	**pp;
		static char	emsg[MAXPATHLEN + 32];

		check_arg(1);
		for (pp = &data[1]; *pp; pp++) {
			if (add_all_dicts(*pp) < 0) {
				(void) sprintf(emsg,
					"Error adding dictionaries in \"%s\"",
					*pp);
				return(emsg);
			}
		}
		cf_ok;
	}
	if (instringcase(item, "history")) {
		char	*tmp;

		check_arg(1);
		if (tmp = pwck_history_configure(&data[1]))
			return(tmp);
		cf_ok;
	}
	if (strcasecmp(item, "passwordchecks") == 0) {
		char	**pp = &data[1];
		char	*tx;

		check_arg(1);
		zeromem(&Config.checkprocs, sizeof Config.checkprocs);
		while (*pp)
			add_proc(*pp++);
		if (tx = check_procs())
			return(tx);
		cf_ok;
	}
	if (strcasecmp(item, "disallowedchars") == 0) {
		char	xcc[BUFSIZ];
		char	append = 0;
		char	*pp = data[1];

		check_arg(1);
		if (*pp == '+')		/* Add to existing list */
			append = *pp++;
		decode_string(xcc, pp, sizeof(xcc));
		if (xcc[0] == 0)
			return(0);
		if (append)
			(void) strncat(Config.badchars, xcc,
			        sizeof(Config.badchars) - strlen(Config.badchars));
		else
			(void) strncpy(Config.badchars, xcc,
				sizeof(Config.badchars));
		cf_ok;
	}
	if (strcasecmp(item, "charclasses") == 0) {
		check_arg(1);
		Config.char_classes = decode_int(data[1]);
		cf_ok;
	}

	free((char *)data);
	if (flagerror)
		return("Unrecognized keyword");
	else
		return(0);
#undef	cf_ok
#undef	check_arg
}

/*
 * add_one_dict
 *	Add one Crack dictionary to the search list
 *
 * Usage
 *	add_one_dict(char *path-to-dictionary);
 * Returns
 *	 1 - success
 *	 0 - dictionary already in list
 *	-1 - error (warning message issued sometimes)
 */
private int
add_one_dict(dict)
	char	*dict;		/* Path to dictionary */
{
	int	dp;	/* Counter */
	PWDICT	*pw;	/* Dictionary pointer */

	debug(DB_CONFIG, "add_one_dict: \"%s\"\n", dict);
	/*
	 * Append to list unless already present
	 */
	for (dp = 0; dp < NDICTIONARIES; dp++) {
		if (Config.dictionaries[dp] == 0)
			break;
		if (strcmp(Config.dictionaries[dp], dict) == 0)
			return(0);
	}
	if (dp == NDICTIONARIES) {
		debug(DB_CONFIG,
			"add_one_dict: overflow (MAX %d)\n", NDICTIONARIES);
		return(-2);
	}
	/*
	 * Verify that the dictionary hash files can be opened
	 */
	if ((pw = PWOpen(dict, "r")) == 0) {
		debug(DB_CONFIG, "add_one_dict: (%s)\n", PWioError);
		return(-1);
	}
	(void) PWClose(pw);
	/*
	 * Stash in the dictionary arrays
	 */
	Config.dictionaries[dp++] = strdup(dict);
	Config.dictionaries[dp] = (char *)0;
	return(1);
}

/*
 * add_all_dicts
 *	Add all Crack dictionaries in a directory
 *
 * Usage
 *	howmany = add_all_dicts(char *directory);
 * Returns
 *	How many dictionaries were found or -1 on error
 * Error exits
 *	Failure to open directory for searching
 */
private char	*dict_suffixes[] = { ".pwi", ".pwd", ".hwm", 0 };

private int
add_all_dicts(where)
	char	*where;			/* What directory to look in */
{
	DIR		*dd;			/* Directory scanner */
	Direntry_t	*dp;			/* Directory entry */
	int		found = 0;		/* Counter */

	if (*where == '@')
		where = PASSWD_DICTIONARIES;
	debug(DB_CONFIG, "add_all_dicts: \"%s\"\n", where);
#ifdef	HAS_READDIR
	if ((dd = opendir(where)) == NULL) {
#if	(CDEBUG >= CDEBUG_SYSTEM)
		perror(where);
		return(-1);
#else	/* DEBUG */
		die("Cannot scan \"%s\" for dictionaries\n", where);
#endif	/* DEBUG */
	}
	while (dp = readdir(dd)) {
		char 	fullname[MAXPATHLEN];
		int	ok;
		char	*p,
			**ext;

		/*
		 * This string must match one of the suffixes used
		 * for the Crack hash files.  See "cracklib/packlib.c".
		 */
		if ((p = strrchr(dp->d_name, '.')) == 0)
			continue;
		if (strcmp(p, dict_suffixes[0]))
			continue;
		*p = 0;
		/*
		 * Sanity check the mode & ownership of the dictionary files.
		 */
		ok = 0;
		for (ext = dict_suffixes; *ext; ext++) {
			struct stat	stb;

			(void) sprintf(fullname, "%s/%s%s",
				where, dp->d_name, *ext);
			if (stat(fullname, &stb) < 0) {
				warn("Missing dictionary file '%s'\n",
					fullname);
				break;
			}
			if (!(stb.st_mode & S_IFREG)) {
				warn("'%s' is not a file\n", fullname);
				break;
			}
#ifdef	S_IWOTH
			if (stb.st_mode & S_IWOTH) {
#else
			if (stb.st_mode & 02) {
#endif
				warn("Dictionary rejected - file '%s' is world writable",
					fullname);
				break;
			}
			ok++;
		}
		if (!ok)
			continue;
		(void) sprintf(fullname, "%s/%s", where, dp->d_name);
		switch (add_one_dict(fullname)) {
			case 1:			/* Success */
				found++;
				break;
			case 0:			/* Dictionary already in list */
				/*
				 * POLICY - duplicate dictionaries is not
				 * a serious error.  An error message is
				 * displayed and logged for the admin to fix
				 * the configuration file.
				 */
				logerr("Dictionary \"%s\" already in use",
					fullname);
				break;
			case -1:		/* List overflow */
				/*
				 * POLICY - overflow of the dictionary list
				 * is a unrecoverable error.  Error status
				 * is passed up to caller, which then will
				 * do what it deems appropriate.
				 */
				logerr("Dictionary list overflow (max %d)",
					NDICTIONARIES);
				closedir(dd);
				return(-1);
				break;
			case -2:		/* Error opening dictionary */
				/*
				 * POLICY - the failure to open a dictionary
				 * is a unrecoverable error.  Error status
				 * is passed up to caller, which then will
				 * do what it deems appropriate.
				 */
				logerr("Dictionary open \"%s\" failed, error %s\n",
					fullname, PWioError);
				closedir(dd);
				return(-1);
				break;
		}
	}
	closedir(dd);
	return(found);
#else	/* HAS_READDIR */

	die("Cannot scan \"%s\" for dictionaries\n", where);
	/*NOTREACHED*/

#endif	/* HAS_READDIR */
}

/*
 * add_proc
 *	Add entry to the password check function list
 * Usage
 *	error = add_proc(char *fuction-name);
 * Returns
 *	Error mesage string upon failure; (char *)0 on success
 */
private char *
add_proc(procname)
	char	*procname;
{
	struct _procnames *p = procnames;
	checkproc	*pp, px;

	/*
	 * Lookup the address for <procname>
	 */
	for (p = procnames, px = 0; p->name; p++) {
		if (strcasecmp(procname, p->name) == 0) {
			debug(DB_CONFIG, "add_proc: add '%s' @ 0x%x\n",
				procname, p->addr);
			px = p->addr;
			break;
		}
	}
	/*
	 * Didn't find <procname> in the table?
	 */
	if (px == 0) {
		static char emsg[STRINGLEN];

		(void) sprintf(emsg, "Unknown check function '%s'", procname);
		return(emsg);
	}
	/*
	 * Append proc address to the list, prevent duplicates
	 */
	for (pp = Config.checkprocs; *pp; pp++) {
		if (*pp == px) {
			warn("add_proc: Check function '%s' already in list\n",
				procname);
			return((char *)0);
		}
	}
	*pp++ = px;
	pp = 0;
	return((char *)0);
}

/*
 * check_procs
 *	Verify integrity of password check function list
 * Returns
 *	Error mesage string upon failure; (char *)0 on success
 */
private char *
check_procs()
{
	struct _procnames *p;

	for (p = procnames; p->name; p++) {
		checkproc *pp;
		int ok = 0;

		if (p->mandatory == 0) continue;
		for (pp = Config.checkprocs; *pp; pp++) {
			if (*pp == p->addr) {
				ok++;
				break;
			}
		}
		if (ok == 0) {
			static char emsg[STRINGLEN];

			(void) sprintf(emsg, "check %s cannot be disabled",
				 p->name);
			return(emsg);
		}
	}
	return((char *)0);
}
/* End pwck_main.c */
