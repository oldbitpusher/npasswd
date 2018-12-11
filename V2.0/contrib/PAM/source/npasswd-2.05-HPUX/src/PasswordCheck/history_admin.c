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
 * history_admin.c
 *	Utility to administer the password history database.
 *
 *	This is an extension of the npasswd password history routines,
 *	and shares a lot of state internal to that code.
 */
#ifndef lint
static char sccsid[] = "@(#)history_admin.c	1.12 10/13/98 (cc.utexas.edu) /usr/share/src/private/ut/share/bin/passwd/V2.0/src/PasswordCheck/SCCS/s.history_admin.c";
#endif

/*
 * System includes
 */
#include <stdio.h>
#include <ctype.h>

/*
 * Npasswd includes
 */
#include "defines.h"
#include "compatibility.h"
#include "options.h"
#include "pwck_defines.h"
#include "pwck_history.h"

#ifdef	I_NDBM
# include <ndbm.h>
#endif

/*
 * Definitions for linked list management
 */
typedef struct _list_item {	/* List data item */
	char	*tag,		/* Tag value */
		*data;		/* Datum */
	struct _list_item *next; /* Next item in list */
} list_item;

typedef struct {		/* List descriptor */
	list_item *head,	/* First data item */
		  *tail,	/* End of list (insert point) */
		  *curr;	/* Current point (for traversal) */
} list_table;

#define	list_new()	((list_table *) calloc(sizeof(list_table), 1))
int		list_insert _((list_table *, char *, char *));
list_item	*list_first _((list_table *));
list_item	*list_find _((list_table *, char *));
list_item	*list_next _((list_table *));
void		list_item_update _((list_item *, char *, char *));
void		list_item_append _((list_item *, char *, char *));

/*
 * Global variables
 */
int	logging = 0;		/* Emit messages via syslog? */
int	verbose = 0;		/* User level verbose */
void	(*xdie)() = die;	/* Fatal error report routine */
				/* Either die() or logdie() in comobj.a */

/*
 * Program debug level table
 */
debug_table admin_debug[] = {
	{ "none",	DB_NONE,	"Debugging off" },
	{ "verbose",	DB_VERBOSE,	"Verbose" },
	{ "config",	DB_CONFIG,	"Configuration processing" },
	{ "detail",	DB_DETAIL,	"Detailed debugging" },
	{ "all",	DB_ALL,		"All debugging" },
	{ 0 },
};

char *Usage = "Usage: %s\n\
	[-a N]		Set password retention age to N days\n\
	[-c file]	Alternate npasswd configuration file\n\
	[-d N]		Set password retention depth to N\n\
	[-f file]	Set database path\n\
	[-i file]	Input data file\n\
	[-l]		Log errors via syslog\n\
	[-m method]	Set database method\n\
	[-v]		Verbose mode\n\
	[-XDN]		Set debug level\n\
	[-Xh]		Help\n\
	function	What to do:\n\
		load - build history database from stdin\n\
		merge - merge into history database from stdin\n\
		dump - dump history database to stdout\n\
		purge - remove dead users and old passwords\n\
";

/*
 * Function prototypes
 */
char	*filter_input _((char *));
int	file_dump _((char *));
int	file_load _((char *, FILE *, int));
int	file_purge _((char *));
#ifdef	I_NDBM
int	dbm_dump _((char *));
int	dbm_load _((char *, FILE *));
int	dbm_merge _((char *, FILE *));
int	dbm_purge _((char *));
#endif

#define	ProgramName	"history_admin"
#define	vprintf		if (verbose) printf
#define	nullstr(_P_)	((_P_) == NULL || *(_P_) == 0)

/*
 * main
 *	Main program
 */
main(argc, argv, envp)
	int	argc;
	char	**argv;
	char	**envp;
{
	int	opt;			/* Arg process temp */
	char	*function = 0,		/* What to do */
		*method = DEFAULT_METHOD, /* DB method */
		*dbfile = 0;		/* DB filename */
	char	*configfile = CONFIG_FILE; /* Npasswd configuration file */
	FILE	*cfp;			/* Control file */
	FILE	*input = stdin;		/* Data stream */
	extern char	*optarg;	/* From getopt() */
	extern int	optind;		/* From getopt() */

	set_debug_tag(ProgramName); /* Tag for die() and warn() */
	/*
	 * Process command line arguments
	 */
	while ((opt = getopt(argc, argv, "a:c:d:f:i:lm:vX:")) != EOF) {
		switch (opt) {
		case 'a':	/* -a password-age */
			HistoryAge = atoi(optarg) * SEC_DAY;
			break;
		case 'c':	/* -c config-file */
			configfile = optarg;
			break;
		case 'd':	/* -d password-depth */
			HistoryDepth = atoi(optarg);
			break;
		case 'f':	/* -f history-file */
			dbfile = optarg;
			break;
		case 'i':	/* -i input-file */
			if ((input = fopen(optarg, "r")) == NULL) {
				perror(optarg);
				die("Cannot open input file\n");
			}
			break;
		case 'l':	/* -l (logging) */
			logging = 1;
			break;
		case 'm':	/* -m history-method */
			method = optarg;
			break;
		case 'v':	/* -v (verbose) */
			verbose = 1;
			break;
		case 'X':
			switch (*optarg) {
			case 'D':
				set_debug(++optarg, admin_debug);
				verbose = 1;
				break;
			case 'h': {
				debug_table *dt = admin_debug;

				printf(Usage, argv[0]);
				printf("Debug levels (-XD...):\n");
				for (; dt->name; dt++)
					printf(" %s\t%s\n", dt->name, dt->help);
				return(0);
				}
			case 'V':
				printf("Version %s of %s\n", "1.12", "10/13/98");
				return(0);
			}
		}
	}
	/*
	 * Drop syslog messages on fatal errors?
	 */
	if (logging) {
		xdie = logdie;
		openlog(ProgramName, LOG_PID, LOG_AUTH);
	}

	/*
	 * Get & verify function argument
	 */
	if (function == 0)
		function = argv[optind++];
	if (function == 0) {
		debug_table *dt = admin_debug;

		printf(Usage, argv[0]);
		printf("Debug levels (-XD...):\n");
		for (; dt->name; dt++)
			printf(" %s\t%s\n", dt->name, dt->help);
		return(1);
	}
	/*
	 * Read npasswd configuration and pick out history directives
	 */
	if (cfp = fopen(configfile, "r")) {
		char    ibuf[BUFSIZ];
		int	cfline = 0;

		while (fgets(ibuf, BUFSIZ, cfp)) {
			char	**cfv,
				*error;

			cfline++;
			chop_nl(ibuf);
			if (ibuf[0] == '#' || ibuf[0] == '\0')
				continue;
			if ((cfv = split(ibuf, 0, 0, '#')) == 0)
				continue;
			if (strcasecmp(cfv[0], "passwd.history")) {
				free((char *)cfv);
				continue;
			}
			if (error = pwck_history_configure(&cfv[1])) {
				(*xdie)("Config file error '%s' line %d; %s\n",
					configfile, ibuf, error);
			}
			free((char *)cfv);
		}
		(void) fclose(cfp);
	}
	/*
	 * Database path or method set on command line?
	 */
	if (dbfile || strcmp(method, DEFAULT_METHOD)) {
		char	*tmp[4];
		char	*error;

		tmp[0] = "database";
		tmp[1] = method;
		tmp[2] = dbfile ? dbfile : HISTORYDB_DEFAULT;
		tmp[3] = 0;
		if (error = pwck_history_configure(tmp))
			(*xdie)("Database error: file '%s' method '%s' error '%s'\n",
				dbfile, method, error);
	}

	if (get_debug()) {
		printf("History database = \"%s\"\n", HistoryDB);
		printf("History method = %s\n", HistoryMethod);
		printf("History depth = %d\n", HistoryDepth);
		printf("History age = %d days\n", HistoryAge / SEC_DAY);
	}

#define	Method_File	(strcmp(HistoryMethod, "file") == 0)
#define	Method_DBM	(strcmp(HistoryMethod, "dbm") == 0)

	/*
	 * Function 'dump' - Spew raw history to stdout
	 */
	if (instringcase(function, "dump")) {
		if (HistoryDB == 0)
			(*xdie)("No history database\n");
		if (Method_File)
			return(file_dump(HistoryDB));
#ifdef	I_NDBM
		if (Method_DBM)
			return(dbm_dump(HistoryDB));
#endif
		return(2);
	}
	/*
	 * Function 'load' - build history from stdin data
	 */
	if (instringcase(function, "load")) {
		if (HistoryDB == 0)
			(*xdie)("No history database\n");
		if (Method_File)
			return(file_load(HistoryDB, input, 0));
#ifdef	I_NDBM
		if (Method_DBM)
			return(dbm_load(HistoryDB, input));
#endif
		return(2);
	}
	/*
	 * Function 'merge' - merge to history from stdin data
	 */
	if (instringcase(function, "merge")) {
		if (HistoryDB == 0)
			(*xdie)("No history database\n");
		if (Method_File)
			return(file_load(HistoryDB, input, 1));
#ifdef	I_NDBM
		if (Method_DBM)
			return(dbm_merge(HistoryDB, input));
#endif
		return(2);
	}
	/*
	 * Function 'purge' - Clean up history
	 */
	if (instringcase(function, "purge")) {
		if (HistoryDB == 0)
			(*xdie)("No history database\n");
		if (Method_File)
			return(file_purge(HistoryDB));
#ifdef	I_NDBM
		if (Method_DBM)
			return(dbm_purge(HistoryDB));
#endif
		return(2);
	}
	/*
	 * Unknown function
	 */
	(*die)("Unknown function '%s'\n", function);
	/*NOTREACHED*/
}
#undef	Method_File
#undef	Method_DBM

/*
 * clone_file_stat
 *	Clone ownership and modes from file to file
 *
 * Returns
 *	Number of errors
 */
clone_file_stat(donor, target)
	char	*donor,		/* Donor file */
		*target;	/* Target file */
{
	struct stat	stb;
	int	errors = 0;

	if (stat(donor, &stb) == 0) {
		if (chown(target, stb.st_uid, stb.st_gid) < 0) {
			perror("clone_mode chown");
			errors++;
		}
		if (chmod(target, stb.st_mode) < 0) {
			perror("clone_mode chmod");
			errors++;
		}
	}
	return(errors);
}

/*
 * install_file
 *	Install a new file with various checks
 *
 * Returns
 *	0 on success
 *	1 on failure
 */
install_file(target, new, save)
	char	*target,	/* Target file */
		*new,		/* New file */
		*save;		/* Save file */
{
	if (save && access(target, 0) == 0) {	/* Move target to save */
		(void) unlink(save);
		if (rename(target, save) < 0) {
			int xerrno = errno;

			perror("Save file rename");
			if (logging)
				logerr("Install save ('%s','%s') failure %d",
					target, save, xerrno);
			return(1);
		}
	}

	if (rename(new, target) < 0) {		/* Move new to current */
		int xerrno = errno;

		perror("New file rename");
		if (logging)
			logerr("Install new ('%s','%s') failure %d",
				new, target, xerrno);
		(void) unlink(target);
		if (save) {
			if (rename(save, target) < 0) {
				int xerrno = errno;
			
				perror("Save file putback");
				if (logging)
					logerr("Install putback ('%s','%s') failure %d",
						save, target, xerrno);
			}
		}
		return(1);
	}
	return(0);
}

/*
 * filter_input
 *	Verify history line
 *
 * Usage
 *	ptr = filter_input(string);
 * Return
 *	pointer to first non-whitespace character of <string>
 *	NULL if line is empty, a comment or malformed
 */
char *filter_input(str)
	char	*str;	/*ARGSUSED*/
{
	if (*str == '\n' || *str == '#')
		return(0);
	while (*str && isspace(*str))
		str++;
	if (*str)
		return(str);
	return(0);
}

/*
 * Routines for manipulating flat file history databases
 */

/*
 * file_read
 *	Read a history database and store in list
 *
 * There may be multiple records for a user, only the last of which is used.
 *
 * Returns
 *	List descriptor on success
 *	Aborts on error
 */
list_table	*
file_read(file)
	char	*file;			/* History file */
{
	FILE		*in;		/* Input file pointer */
	list_table	*nl;		/* List table pointer */
	char		buf[BUFSIZ];	/* Input buffer */

	if ((nl = list_new()) == NULL)
		(*xdie)("No memory for read list\n");

	if ((in = fopen(file, "r")) == NULL) {
		int xerrno = errno;

		perror(file);
		(*xdie)("Cannot open history file '%s', error %d\n",
			file, xerrno);
	}
	while (fgets(buf, sizeof(buf), in)) {
		list_item	*lp;
		char		*iptr,	/* Input pointer */
				*dptr;	/* Data pointer  */

		if ((iptr = filter_input(buf)) == 0)
			continue;
		chop_nl(buf);
		if ((dptr = strchr(buf, ENTRY_SEP)) == NULL)
			continue;
		*dptr++ = 0;
		if (lp = list_find(nl, buf))
			list_item_update(lp, NULL, dptr);
		else
			list_insert(nl, iptr, dptr);
	}
	(void) fclose(in);
	return(nl);
}

/*
 * file_purge
 *	Clean a flat file history datbase
 *
 * Returns
 *	0 on success
 *	1 on failure
 */
file_purge(file)
	char *file;			/* History file */
{
	FILE	*out;			/* Output stream */
	char	*tempfile,		/* Temp history file */
		*savefile,		/* Saved history file */
		buf[HISTORY_RECLEN];	/* Read buffer */
	int	errors = 0,		/* Error count */
		how_many = 0,		/* Record count */
		deleted = 0,		/* Deleted record count */
		t;			/* Temp */
	list_table	*history;	/* History list */
	list_item	*hi;		/* History list item */

	if (access(file, 0) < 0) {
		if (verbose)
			warn("No history file\n");
		return(1);
	}

	/*
	 * Construct temporary and save file names
	 */
	if ((tempfile = malloc(strlen(file) + 8)) == 0)
		(*xdie)("No memory for tempfile string\n");
	(void) sprintf(tempfile, "%s.temp", file);

	if ((savefile = malloc(strlen(file) + 8)) == 0)
		(*xdie)("No memory for savefile string\n");
	(void) sprintf(savefile, "%s.old", file);

	/*
	 * Create the temp file
	 */
	if ((t = MakeLockTemp(tempfile)) < 0) {
		(*xdie)("Cannot make temp file '%s', error %d\n",
			tempfile, errno);
	}
	out = fdopen(t, "w");		/* Get stdio pointer */
	debug(DB_VERBOSE, "purge_file: file '%s'\ntemp '%s'\nsave '%s'\n",
		file, tempfile, savefile);

	/*
	 * Traverse the history, checking if the user is still in the
	 * password file and if so, clean their entry and put to temp file.
	 */
	history = file_read(file);
	for (hi = list_first(history); hi; hi = list_next(history)) {
		char	*t;	/* Temp */

		how_many++;
		if (getpwnam(hi->tag) == 0) {
			vprintf("Delete history for %s (not in passwd)\n", hi->tag);
			deleted++;
			continue;
		}
		t = clean_history(hi->data, HistoryDepth, HistoryAge, 0, 0);
		if (nullstr(t)) {
			vprintf("Delete history for %s (null)\n", hi->tag);
			continue; 
		}
		debug(DB_DETAIL, "New purge entry <%s%c%s>\n",
			hi->tag, ENTRY_SEP, t);
		(void) fprintf(out, "%s%c%s\n", hi->tag, ENTRY_SEP, t);
	}
	(void) fclose(out);

	/*
	 * Install temp file as history file
	 */
	if (clone_file_stat(file, tempfile)) {
		warn("History purge errors - new database left in '%s'\n",
			tempfile);
		return(1);
	}
	if (install_file(file, tempfile, savefile)) {
		warn("History purge errors - new database left in '%s'\n",
			tempfile);
		return(1);
	}

	if (logging)
		syslog(LOG_INFO,
			"Password history purge: %d records %d deletions",
			how_many, deleted);
	vprintf("Password history purge: %d records %d deletions\n",
		how_many, deleted);
	return(0);
}

/*
 * file_dump
 *	Dump a flat file history database to standard output
 *	Entries are not run through clean_history()
 *
 * Returns
 *	0 on success
 *	1 if history file missing
 */
file_dump(file)
	char	*file;		/* History file */
{
	list_table	*hlist;	/* List pointer */
	list_item	*hitem;	/* List item */

	if (access(file, 0) < 0) {
		if (verbose)
			warn("No history file\n");
		return(1);
	}
	hlist = file_read(file);
	for (hitem = list_first(hlist); hitem; hitem = list_next(hlist)) {
		printf("%s%c%s\n", hitem->tag, ENTRY_SEP, hitem->data);
	}
	return(0);
}

/*
 * file_load
 *	Build history database file from stdin data
 *
 * Returns
 *	0 on success
 *	1 on failure
 */
file_load(file, input, merge)
	char	*file;			/* History file */
	FILE	*input;			/* Input stream */
	int	merge;			/* Add to existing data? */
{
	FILE	*out;			/* Output stream */
	char	*tempfile,	/* Temp history file */
		*savefile,	/* Saved history file */
		buf[HISTORY_RECLEN];	/* Read buffer */
	int	how_many = 0,		/* Record count */
		ofd;			/* Temp */
	list_table	*hlist;
	list_item	*hitem;

	/*
	 * Construct temporary and save file names
	 */
	if ((tempfile = malloc(strlen(file) + 8)) == 0)
		(*xdie)("No memory for tempfile string\n");
	(void) sprintf(tempfile, "%s.temp", file);

	if ((savefile = malloc(strlen(file) + 8)) == 0)
		(*xdie)("No memory for savefile string\n");
	(void) sprintf(savefile, "%s.old", file);

	debug(DB_VERBOSE, "file_load: file '%s'\ntemp '%s'\nsave '%s'\n",
		file, tempfile, savefile);
	/*
	 * Make the temp file
	 */
	if ((ofd = MakeLockTemp(tempfile)) < 0) {
		(*xdie)("Cannot make temp file '%s', error %d\n",
			tempfile, errno);
	}
	out = fdopen(ofd, "w");		/* Get stdio pointer */

	/*
	 * If merging read the database, else make new list
	 */
	if (merge)
		hlist = file_read(file);
	else
		hlist = list_new();

	/*
	 * Read history lines from <input> and pack/merge into the database
	 */
	while (fgets(buf, sizeof(buf), input)) {
		char	*iptr,
			*dptr;		/* Temp */

		chop_nl(buf);
		if ((iptr = filter_input(buf)) == 0)
			continue;
		if ((dptr = strchr(iptr, ENTRY_SEP)) == 0)
			continue;
		*dptr++ = 0;

		/*
		 * If user is already in history, replace with input
		 * or append input to entry
		 */
		if (hitem = list_find(hlist, iptr)) {
			if (merge) {
				*--dptr = ENTRY_SEP;
				debug(DB_DETAIL,
					"file_load: Append <%s> to <%s:%s>\n",
					dptr, hitem->tag, hitem->data);
				list_item_append(hitem, NULL, dptr);
			} else {
				debug(DB_DETAIL, "file_load: Update %s:<%s>\n",
					iptr, dptr);
				list_item_update(hitem, NULL, dptr);
			}
		} else {
			debug(DB_DETAIL,
				"file_load: Insert <%s:%s>\n", iptr, dptr);
			list_insert(hlist, iptr, dptr);
		}
		how_many++;
	}

	/*
	 * Traverse the history list, clean the entries and put
	 * into the new history
	 */
	for (hitem = list_first(hlist); hitem; hitem = list_next(hlist)) {
		char	*t = clean_history(hitem->data, 0, 0, 0, 0);

		if (nullstr(t))		/* "Shouldn't happen" */
			continue;
		(void) fprintf(out, "%s%c%s\n", hitem->tag, ENTRY_SEP, t);
	}
	(void) fclose(out);

	/*
	 * If the database file exists, copy the mode and ownership
	 */
	if (access(file, 0) == 0) {
		if (clone_file_stat(file, tempfile)) {
			warn("History load/merge errors - new database left in '%s'\n",
				tempfile);
			return(1);
		}
	}
	/*
	 * Move temp file to database file
	 */
	if (install_file(file, tempfile, savefile)) {
		warn("History load/merge errors - new database left in '%s'\n",
			tempfile);
		return(1);
	}
	/*
	 * Confirm and finish
 	 */
	if (logging)
		syslog(LOG_INFO, "%d records %sed to history file '%s'",
			how_many, (merge ? "merg" : "add"), file);
	vprintf("%d records %sed to password history file '%s'\n",
		how_many,  (merge ? "merg" : "add"), file);
	return(0);
}

/*
 * Routines for manipulating DBM history databases
 */

#ifdef	I_NDBM
/*
 * NDBM support for history database
 */

/*
 * C string to DBM value conversion
 */
#define	str2dbm(_D_,_S_) { _D_.dptr = _S_; _D_.dsize = strlen(_S_); }

/*
 * DBM value to C string conversion (assumes that _D_ is large enough)
 */
#define	dbm2str(_S_,_D_) { (void) strncpy(_S_,_D_.dptr,_D_.dsize);\
				  _S_[_D_.dsize] = 0; }
/* 
 * dbm_purge
 *	Cleanup DBM history database
 *
 * Returns
 *	number of errors
 *
 * NOTE: Does not free all dynamically allocated storage
 */
dbm_purge(file)
	char *file;			/* History DBM file */
{
	DBM	*hdb;		/* Database pointer */
	datum	hkey;		/* DBM lookup datum */
	int	count = 0,	/* Entry counter */
		deleted = 0,	/* Deletion counter */
		errors = 0;	/* Errors encountered */
	list_table	*history;/* History list */
	list_item	*hi;	/* List item */

	/*
	 * Open database
	 */
	if ((hdb = dbm_open(file, O_RDWR, 0)) == 0) {
		perror("History DBM open");
		if (logging)
			logerr("Cannot open DBM '%s' for purge", file);
		return(1);
	}

	/*
	 * Traverse the database, checking if the user is still in the
	 * password file and store the result
	 */
	if ((history = list_new()) == 0)
		(*xdie)("No memory for DBM purge list\n");

	for (hkey = dbm_firstkey(hdb); hkey.dptr != NULL; hkey = dbm_nextkey(hdb)) {
		char	tmp[DBLKSIZ];	/* String temp */

		dbm2str(tmp, hkey);
		if (getpwnam(tmp))
			list_insert(history, tmp, "U");	/* Update this entry */
		else
			list_insert(history, tmp, "D");	/* Delete this entry */
		count++;
	}

	/*
	 * Traverse the history list, cleaning and deleting entries as needed
	 */
	for (hi = list_first(history); hi; hi = list_next(history)) {
		datum	ukey;		/* Lookup temp */
		datum	udata;		/* Data temp */
		char	hdata[DBLKSIZ];	/* String temp */
		char	*ht;		/* String temp */

		str2dbm(ukey, hi->tag);
		if (*hi->data == 'D') {	/* Delete this entry */
			vprintf("Delete history for %s (not in passwd)\n",
				hi->tag);
			if (dbm_delete(hdb, ukey) < 0) {
				warn("DBM delete for %s failed", hi->tag);
				errors++;
			}
			deleted++;
			continue;
		}

		/*
		 * Fetch the history entry for cleaning
		 */
		udata = dbm_fetch(hdb, ukey);
		dbm2str(hdata, udata);
		ht = clean_history(hdata, HistoryDepth, HistoryAge, 0, 0);
		/*
		 * If the history is empty, delete the entry
		 */
		if (nullstr(ht)) {
			vprintf("Delete history for %s (empty)\n", hi->data);
			if (dbm_delete(hdb, ukey) < 0) {
				warn("DBM delete for %s failed", hi->tag);
				errors++;
			}
			deleted++;
			continue;
		}

		/*
		 * Store the cleaned history entry
		 */
		str2dbm(udata, ht);
		if (dbm_store(hdb, ukey, udata, DBM_REPLACE) < 0) {
			errors++;
			warn("DBM replace for %s failed", hi->tag);
			if (logging)
				logerr("DBM replace for %s failed", hi->tag);
		}
	}
	dbm_close(hdb);		/* Finished with database */

	if (logging)
		syslog(LOG_INFO,
			"History purge: %d records %d deletions %d errors",
			count, deleted, errors);
	vprintf("History purge: %d records %d deletions %d errors\n",
		count, deleted, errors);
	return(errors);
}

/* 
 * dbm_dump
 *	Dump DBM history database to stdout
 *
 * Returns
 *	0 on success
 *	1 on failure
 */
dbm_dump(file)
	char *file;		/* History DBM */
{
	DBM	*hdb;		/* Database pointer */
	datum	hkey;		/* DBM lookup datum */

	/*
	 * Open database
	 */
	if ((hdb = dbm_open(file, O_RDONLY, 0)) == 0) {
		if (logging)
			logerr("Cannot open DBM history database");
		return(1);
	}
	/*
	 * Step through the keys in the database and spew to stdout
	 */
	for (hkey = dbm_firstkey(hdb); hkey.dptr != NULL; hkey = dbm_nextkey(hdb)) {
		datum	hdata;
		char	name[DBLKSIZ],
			data[DBLKSIZ];

		hdata = dbm_fetch(hdb, hkey);
		dbm2str(name, hkey);
		dbm2str(data, hdata);
		printf("%s%c%s\n", name, ENTRY_SEP, data);
	}
	dbm_close(hdb);
	return(0);
}

/* 
 * dbm_load
 *	Build history database DBM from input
 *
 * Returns
 *	error count
 */
dbm_load(file, input)
	char	*file;		/* History DBM file */
	FILE	*input;		/* Input stream */
{
	DBM	*hdb;		/* Database pointer */
	char	*file_pag,	/* Database .pag name */
		*file_dir,	/* Database .dir name */
		*temp_pag,	/* Temp file .pag name */
		*temp_dir,	/* Temp file .dir name */
		*tempfile,	/* Temp file name */
		*save_dir = NULL,	/* Save file .dir name */
		*save_pag = NULL,	/* Save file .pag name */
		*savefile = NULL;	/* Save file name */
	char	inbuf[HISTORY_RECLEN];	/* Read buffer */
	int	errors = 0;		/* Error count */
	int	how_many = 0;		/* Count of records loaded */
	struct stat stb;		/* Stat buffer */

#define	db_files(_d_,_p_,_n_) \
	(void) sprintf(_d_, "%s.dir", _n_);\
	(void) sprintf(_p_, "%s.pag", _n_)

#define	fn_alloc(_d_,_f_,_p_) \
	if ((_d_ = malloc(strlen(_f_) + _p_)) == NULL) \
		(*xdie)("No memory for tempfile string\n")

	/*
	 * Make DB file names
	 */
	fn_alloc(file_dir, file, 8);
	fn_alloc(file_pag, file, 8);
	db_files(file_dir, file_pag, file);

	/*
	 * Make temp file names
	 */
	fn_alloc(tempfile, file, 8);
	(void) sprintf(tempfile, "%s.temp", file);
	fn_alloc(temp_dir, tempfile, 6);
	fn_alloc(temp_pag, tempfile, 6);
	db_files(temp_dir, temp_pag, tempfile);
	debug(DB_VERBOSE, "dbm_load: file '%s' temp '%s'\n", file, tempfile);

	/*
	 * Open database
	 */
	if ((hdb = dbm_open(tempfile, O_RDWR|O_CREAT, HISTORYDB_MODE)) == 0) {
		perror("DBM temp create");
		(*xdie)("Cannot create DBM '%s'\n", tempfile);
	}
	/*
	 * Read history lines from stdin and pack into the database
	 */
	while (fgets(inbuf, sizeof(inbuf), input)) {
		datum	hkey,		/* DBM key */
			hdata;		/* DBM data */
		char	*dptr,		/* History data start */
			*nptr,		/* New history data */
			*iptr;		/* Start of input line */

		chop_nl(inbuf);

		if ((iptr = filter_input(inbuf)) == 0)		/* Null input */
			continue;
		if ((dptr = strchr(iptr, ENTRY_SEP)) == 0)	/* Bad input */
			continue;
		*dptr++ = 0;

		nptr = clean_history(dptr, 0, 0, 0, 0);
		if (nullstr(nptr))
			continue;

		str2dbm(hkey, iptr);
		str2dbm(hdata, nptr);
		/*
		 * Store new data
		 */
		if (dbm_store(hdb, hkey, hdata, DBM_INSERT) < 0) {
			warn("DBM insert failed for '%s'\n", iptr);
			errors++;
		}
		how_many++;
	}
	dbm_close(hdb);

	if (stat(file_dir, &stb) == 0) {	/* Database exists */
		/*
		 * Make save file names
		 */
		fn_alloc(savefile, file, 8);
		(void) sprintf(savefile, "%s.old", file);
		fn_alloc(save_dir, savefile, 6);
		fn_alloc(save_pag, savefile, 6);
		db_files(save_dir, save_pag, savefile);
		debug(DB_VERBOSE, "dbm_load: file '%s' save '%s'\n",
			file, savefile);

		/*
		 * Copy mode and ownership from original
		 */
		errors += clone_file_stat(file_dir, temp_dir);
		errors += clone_file_stat(file_pag, temp_pag);
	}
	if (errors) {
		warn("History load errors - new database left as '%s'\n",
			tempfile);
		return(errors);
	}
	if (install_file(file_dir, temp_dir, save_dir)) {
		warn("Replace DBM '%s' failed\n", file_dir);
		return(1);
	}
	if (install_file(file_pag, temp_pag, save_pag)) {
		warn("Replace DBM '%s' failed\n", file_pag);
		return(1);
	}

	if (logging)
		syslog(LOG_INFO, "%d records loaded to history DBM '%s'",
			how_many, file);
	vprintf("%d records loaded to history DBM '%s'\n", how_many, file);
	return(0);
#undef	db_files
#undef	fn_alloc
}

/* 
 * dbm_merge
 *	Build history database DBM from stdin data
 *
 * Returns
 *	0 on success
 *	1 on failure
 */
dbm_merge(file, input)
	char	*file;		/* History DBM file */
	FILE	*input;		/* Input stream */
{
	DBM	*hdb;			/* Database pointer */
	char	inbuf[HISTORY_RECLEN];	/* Read buffer */
	int	errors = 0;		/* Error count */
	int	how_many = 0;		/* Count of records loaded */
	struct stat stb;		/* Stat buffer */

	if ((hdb = dbm_open(file, O_RDWR, HISTORYDB_MODE)) == 0) {
		perror("DBM merge open");
		(*xdie)("Cannot open DBM '%s' for merge\n", file);
	}
	/*
	 * Read history lines from stdin and pack into the database
	 */
	while (fgets(inbuf, sizeof(inbuf), input)) {
		datum	hkey,		/* Lookup key */
			hdata,		/* Store data */
			htemp;		/* Lookup data */
		char	*dptr,		/* Temp */
			*nptr,		/* Temp */
			*iptr;		/* Temp */

		chop_nl(inbuf);

		if ((iptr = filter_input(inbuf)) == NULL)
			continue;

		if ((dptr = strchr(iptr, ENTRY_SEP)) == NULL)
			continue;
		*dptr++ = 0;

		/*
		 * If the user is in the db, fetch entry and append input
		 */
		str2dbm(hkey, iptr);
		htemp = dbm_fetch(hdb, hkey);
		if (htemp.dptr) {
			char 	*nd = malloc(htemp.dsize + strlen(dptr) + 2);
			char	*td;

			if (nd == NULL)
				(*xdie)("No memory for DBM merge key extend\n");
			(void) strncpy(nd, htemp.dptr, htemp.dsize);
			nd[htemp.dsize] = 0;
			debug(DB_DETAIL, "dbm_merge: Append <%s> to <%s:%s>\n",
					dptr, iptr, nd);
			(void) strcat(nd, ENTRY_SEP_STR);
			(void) strcat(nd, dptr);

			td = clean_history(nd, 0, 0, 0, 0);
			if (nullstr(td)) {	/* "Shouldn't happen" */
				warn("Unexpected null history '%s'\n",iptr);
				free(nd);
				continue;
			}
			nptr = td;
		} else {
			debug(DB_DETAIL, "dbm_merge: Insert <%s:%s>\n", iptr, dptr);
			nptr = clean_history(dptr, 0, 0, 0, 0);
			if (nullstr(nptr))
				continue;
		}
		/*
		 * Store new data
		 */
		str2dbm(hdata, nptr);
		if (dbm_store(hdb, hkey, hdata, DBM_REPLACE) < 0) {
			warn("DBM replace for '%s' failed\n", iptr);
			errors++;
		}
		how_many++;
	}
	dbm_close(hdb);

	if (errors)
		warn("%s history merge errors\n", errors);
	if (logging)
		syslog(LOG_INFO, "Merged %d records to history DBM '%s', %d errors",
			how_many, file, errors);
	vprintf("Merged %d records to history DBM '%s'\n", how_many, file);
	return(errors);
}

#endif	/* I_NDBM */


/*
 * These routines impliment a simple linked list mechanism.
 * The keys are unordered; tags are not unique; searches are linear;
 * no routines exist to free lists or items.
 */

/*
 * list_insert
 *	Make a new item in a linked list
 *
 * Returns
 *	0 on failure
 *	1 on success
 */
list_insert(table, tag, data)
	list_table *table;		/* Target list */
	char	*tag,			/* Tag string */
		*data;			/* Data string */
{
	list_item	*nd;		/* Temp */
	char		*t;		/* Temp */

	if (table == 0)
		return(0);

	if ((nd = (list_item *)calloc(sizeof(list_item),1)) == 0)
		return(0);
	/*
	 * Do our own mallocs() so that space can be free()ed
	 * in list_item_update() and list_item_append()
	 */
	t = malloc(strlen(tag) + 2);
	(void) strcpy(t, tag);
	nd->tag = t;

	t = malloc(strlen(data) + 2);
	(void) strcpy(t, data);
	nd->data = t;
	nd->next = 0;

	if (table->head == 0)
		table->head = nd;

	if (table->tail)
		(table->tail)->next = nd;
	table->tail = nd;
	return(1);
}

/*
 * list_find
 *	Search linked list. The list in unordered, so we suck it up and do
 *	a brain-dead linear (order N) search.
 *
 * Returns
 *	Pointer to first list item found with matching tag
 *	NULL if not found
 */
list_item	*
list_find(table, tag)
	list_table	*table;		/* List to search */
	char		*tag;		/* What to search for */
{
	list_item	*dtp;		/* Temp */

	if (table == 0 || nullstr(tag))	/* Bad args */
		return(0);
	if ((dtp = table->head) == 0)	/* Empty list */
		return(0);
	while (dtp) {
		if (strcmp(tag, dtp->tag) == 0)
			return(dtp);
		dtp = dtp->next;
	}
	return(0);
}

/*
 * list_first
 *	Return the first item in a list
 */
list_item *
list_first(table)
	list_table	*table;		/* Table to traverse */
{
	if (table == 0 || table->head == 0)	/* Bad arg or empty list */
		return(0);
	table->curr = table->head;	/* Set traversal pointer */
	return(list_next(table));
}

/*
 * list_next
 *	Return next data item in list
 */
list_item *
list_next(table)
	list_table	*table;		/* Table to traverse */
{
	list_item	*rv;		/* Return value */

	if (table == 0 || table->head == 0)	/* Bad arg or empty list */
		return(0);
	if (table->curr) {
		rv = table->curr;
		table->curr = (table->curr)->next;
		return(rv);
	}
	return(0);
}

/*
 * list_item_update
 *	Update contents of a list item
 */
void
list_item_update(lp, ntag, ndata)
	list_item	*lp;		/* List item to update */
	char		*ntag,		/* New tag string */
			*ndata;		/* New data string */
{
	if (lp == 0)			/* Bad arg */
		return;
	if (ntag && *ntag) {		/* Change tag? */
		char	*t = malloc(strlen(ntag) + 2);

		(void) strcpy(t, ntag);
		free(lp->tag);
		lp->tag = t;
	}
	if (ndata && *ndata) {		/* Change data? */
		char	*t = malloc(strlen(ndata) + 2);

		(void) strcpy(t, ndata);
		free(lp->data);
		lp->data = t;
	}
}

/*
 * list_item_append
 *	Appends to contents of a list item
 */
void
list_item_append(lp, atag, adata)
	list_item	*lp;		/* List item */
	char		*atag,		/* Additional tag string */
			*adata;		/* Additional data string */
{
	if (lp == 0)			/* Bad arg */
		return;
	if (atag && *atag) {		/* Additional tag? */
		char	*t = malloc(strlen(lp->tag) + strlen(atag) + 4);

		(void) sprintf(t, "%s%s", lp->tag, atag);
		free(lp->tag);
		lp->tag = t;
	}
	if (adata && *adata) {		/* Additional data? */
		char	*t = malloc(strlen(lp->data) + strlen(adata) + 4);

		(void) sprintf(t, "%s%s", lp->data, adata);
		free(lp->data);
		lp->data = t;
	}
}

/* End history_admin.c */
