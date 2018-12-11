/*
 * Copyright (C) 2002  The University of Texas at Austin ("U. T. Austin").
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  Contact: npasswd-support@www.utexas.edu
 *
 */

/*
 * configure
 *	Process the npasswd configuration file.
 *	Many of directives are passed to the pasword check library
 *	configuration routine.
 *
 * Exported routines
 *	configure()
 * Imported variables
 *	See below
 */

#ifndef lint
static char sccsid[] = "$Id: configure.c,v 1.33 2002/10/02 15:49:16 clyde Exp $ (cc.utexas.edu) %P%";
#endif

#include "npasswd.h"
#include "checkpassword.h"

extern char	*Passwd_Help;		/* From passwd.c */
extern char	*Passwd_Motd;		/* From passwd.c */

extern char	*Chsh_Help;		/* From chsh.c */
extern char	*Chsh_Motd;		/* From chsh.c */
extern char	*Chsh_Shells;		/* From chsh.c */

extern char	*Chfn_Help;		/* From chfn.c */
extern char	*Chfn_Motd;		/* From chfn.c */

extern int	PasswdMatchTries;	/* From getpass.c */
extern int	PasswdMatchWait;	/* From getpass.c */
extern int	PasswdTolerance;	/* From pwm_local.c */
extern int	ShadowTolerance;	/* From active shadow module */

#define	PWCHECK_PASSTHRU	'p'	/* Pass to checkpasswd_configure() */
/*
 * Configuration table
 */
struct cftab {
        char	*keyword;	/* String to match */
	int	code;		/* Entry code */
	enum _cftdt {		/* Data type required */
		BOOLEAN, INT, STRING, PATH, NONE
	} datatype;
	void	*where;		/* Where to put the stuff */
};

/*
 * The master configuration table.
 * I'm using a brute-force method for this, but since there are
 * few directives, so brutal-but-simple wins.
 */
private struct cftab cftab[] = {
	/* Global configuration */
	{ "PasswdTolerance",	0,	INT,	(void *)&PasswdTolerance },
	{ "ShadowTolerance",	0,	INT,	(void *)&ShadowTolerance },
	{ "MatchTries",		0,	INT,	(void *)&PasswdMatchTries },
	{ "MatchWait",		0,	INT,	(void *)&PasswdMatchWait },

	/* Configuration for checkpassword() */
	{ "passwd.Dictionaries",	PWCHECK_PASSTHRU,	NONE },
	{ "passwd.SingleCase",		PWCHECK_PASSTHRU,	NONE },
	{ "passwd.AlphaOnly",		PWCHECK_PASSTHRU,	NONE },
	{ "passwd.MinPassword",		PWCHECK_PASSTHRU,	NONE },
	{ "passwd.MaxPassword",		PWCHECK_PASSTHRU,	NONE },
	{ "passwd.MaxRepeat",		PWCHECK_PASSTHRU,	NONE },
	{ "passwd.LengthWarn",		PWCHECK_PASSTHRU,	NONE },
	{ "passwd.PrintableOnly",	PWCHECK_PASSTHRU,	NONE },
	{ "passwd.WhiteSpace",		PWCHECK_PASSTHRU,	NONE },
	{ "passwd.DisallowedChars",	PWCHECK_PASSTHRU,	NONE },
	{ "passwd.CharClasses",		PWCHECK_PASSTHRU,	NONE },
	{ "passwd.PasswordChecks",	PWCHECK_PASSTHRU,	NONE },
	{ "passwd.History",		PWCHECK_PASSTHRU,	NONE },

	/* Configuration for 'passwd' module */
	{ "passwd.Help",  	0, PATH,	(void *)&Passwd_Help },
	{ "passwd.Message",  	0, PATH,	(void *)&Passwd_Motd },

	/* Configurationf for 'chsh' module */
	{ "chsh.Help",  	0, PATH,	(void *)&Chsh_Help },
	{ "chsh.Message",  	0, PATH,	(void *)&Chsh_Motd },
	{ "chsh.Shells",	0, PATH,	(void *)&Chsh_Shells },

	/* Configurationf for 'chfn' module */
	{ "chfn.Help",  	0, PATH,	(void *)&Chfn_Help },
	{ "chfn.Message",  	0, PATH,	(void *)&Chfn_Motd },
	{ 0 },
};

/*
 * dump_config
 *	Print confiuration table
 */
private void
dump_config(vflag)
	int vflag;		/* Verbose flag */
{
	struct cftab	*f;

	for (f = cftab; f->keyword; f++) {
		switch(f->datatype) {
		case NONE:
			if (vflag == 0)
				break;
			printf("%-20s code=%-5d type=%-5d ",
				f->keyword, f->code, f->datatype);
			if (f->code == PWCHECK_PASSTHRU)
				printf("passthru ");
			if (f->where)
				printf("loc=%0x", f->where);
			printf("\n");
			break;
		case INT:
			if (vflag)
				printf("%-20s code=%-5d type=%d loc=%0x data=%0x\n",
					f->keyword, f->code, f->datatype,
					f->where, *((int *)f->where));
			else
				printf("%-20s %d\n", f->keyword,
					*((int *)f->where));
			break;

		case PATH:
			if (vflag)
				printf("%-20s code=%-5d type=%d loc=%0x data=%0x\n",
					f->keyword, f->code, f->datatype,
					f->where, *((char **)f->where));
			else
				printf("%-20s %s\n", f->keyword,
					*((char **)f->where));
			break;
		}
	}
}

/*
 * config
 *	Read validation configuration file and stash away.
 *
 * Usage
 *	configure(char *config-file-name, int secure-check);
 * Error exits
 *	Syntax error or unknown directive encountered
 */
public void
configure(cfn, secure)
	char	*cfn;		/* Config file name */
	int	secure;		/* Do security checks */	
{
	char	cfline[TMPBUFSIZ]; /* Input buffer */
	FILE	*cf;		/* Config file pointer */
	char	*t;		/* Temp */
	int	lineno = 0;	/* Config file line number */
	struct stat cfstat;

	if (lstat(cfn, &cfstat) < 0)
		die("Cannot find configuration file \"%s\"\n", cfn);
#if	(CDEBUG < CDEBUG_SYSTEM)
	/*
	 * Security checks:
	 *   File cannot be world-writable
	 *   File cannot be a symlink (too many race condition scenarios)
	 *   File must be owned by the effective uid
	 */
	if (secure == 0) {
		Uid_t	euid = geteuid();

		if (cfstat.st_uid != euid)
			die("Configuration file \"%s\" not owned by uid %d\n",
				cfn, euid);
#ifdef	S_IWOTH
		if (cfstat.st_mode & S_IWOTH)
#else
		if (cfstat.st_mode & 02)
#endif
			die("Configuration file \"%s\" is writable\n", cfn);
		if ((cfstat.st_mode & S_IFLNK) == S_IFLNK) 
			die("Configuration file \"%s\" is a symlink\n", cfn);
	}
#endif
	if ((cf = fopen(cfn, "r")) == NULL) {
		perror(cfn);
		die("Cannot open configuration file \"%s\"\n", cfn);
	}
	if (get_debug() >= DB_CONFIG) {
		printf("\nBefore reading config file \"%s\"\n", cfn);
		dump_config(1);
	}
	checkpassword_init();
	while (fgets(cfline, sizeof(cfline), cf)) {
		struct cftab *cfi;	/* Table lookup temp */
		int	ok,		/* Temp */
			itemp;		/* Temp */
		char	**cfv;		/* Tokenized cfline */

		lineno++;
		if (cfline[0] == '#' || cfline[0] == '\n' || cfline[0] == '\0')
			continue;
		chop_nl(cfline);
		if ((cfv = split(cfline, 0, 0, '#')) == 0)
			continue;
		debug(DB_CONFIG, "[%d] %s\n", lineno, cfline);
		ok = 0;
		for (cfi = cftab; cfi->keyword; cfi++) {
			if (strcasecmp(cfv[0], cfi->keyword) == 0) {
				ok++;
				break;
			}
		}
		if (ok == 0) {
#if	(DEBUG <= CDEBUG_SYSTEM)
			warn("File '%s' line %d: Unrecognized directive\n",
				cfn, lineno);
			continue;
#else
			die("File '%s' line %d: Unrecognized directive\n", cfn, lineno);
#endif
		}
		switch (cfi->datatype) {
		case NONE:
			if (cfi->code == PWCHECK_PASSTHRU) {
				char	*rc;

				if (rc = checkpassword_configure(cfline, 1))
					die("Line %d: Error %s\n", lineno, rc);
				break;
			}
			die("Line %d: Internal error (NONE)\n", lineno);
			break;

		case BOOLEAN:
			if (cfv[1] && *cfv[1])
				itemp = decode_boolean(cfv[1]);
			else
				die("Line %d: Missing argument\n", lineno);
			*((int *)cfi->where) = itemp;
			break;

		case INT:
			if (cfv[1] && *cfv[1])
				itemp = decode_int(cfv[1]);
			else
				die("Line %d: Missing count\n", lineno);
			*((int *)cfi->where) = itemp;
			break;

		case PATH:
			if (!cfv[1] || *cfv[1] != '/')
				die("Line %d: Missing argument\n", lineno);
			*((char **)cfi->where)= strdup(cfv[1]);
			break;

		case STRING:
			if (cfv[1])
				*((char **)cfi->where) = strdup(cfv[1]);
			else
				die("Line %d: Missing argument\n", lineno);
			break;

		default:
			warn("Line %d: Internal error (UNKNOWN)\n", cfline);
			break;
		}
	}
	(void) fclose(cf);
	if (get_debug() >= DB_CONFIG) {
		printf("\nAfter reading config file\n");
		dump_config(1);
	}
	if (t = checkpassword_verify())
		logdie(t);
	if (XSwitches[Xsw_ShowConfig]) {
		dump_config(0);
		checkpassword_probe("passwd.");
		exit(0);
	}
}
/* End $RCSfile: configure.c,v $ */
