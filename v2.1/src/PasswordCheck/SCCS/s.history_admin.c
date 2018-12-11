h36687
s 00008/00009/01332
d D 1.12 98/10/13 14:40:24 clyde 12 11
c Make error message more consistent
e
s 00717/00461/00624
d D 1.11 98/10/13 14:11:21 clyde 11 10
c Major rework:
c 1. Use linked lists to keep stuff
c 2. Add -i and -XV command line options
c 3. Split merge function for DBM 
c 4. Split out file manipulation routines (clone modes, install temp)
c 5. Remove awk script frontends
c 6. Rewrite file_load() and file_purge()
c 7. Rewrite dbm_load() and dbm_purge()
c 8. Add debug() statements more places
c 9. Add convience #ifdefs
c 10. Cleanup comment and error message styles
e
s 00095/00066/00990
d D 1.10 98/10/01 14:36:52 clyde 10 9
c Rework file_load() merge code
e
s 00037/00021/01019
d D 1.9 98/10/01 10:37:15 clyde 9 8
c 1. Change 'append' function to 'merge'
c 2. Make DBM merge work properly (add to existing records)
e
s 00006/00005/01034
d D 1.8 98/09/30 15:41:02 clyde 8 7
c Fix dbm_load()
e
s 00224/00132/00815
d D 1.7 98/09/30 15:17:51 clyde 7 6
c 1. Add 'append' function
c 2. Fix dbm_purge()
c 3. Allow -m to affect default database
c 4. Make error messages consistent between file_xxx() and dbm_xxx()
c 5. Deal with possible null returns from clean_history()
e
s 00090/00085/00857
d D 1.6 98/07/17 09:44:48 clyde 6 5
c 1. Change behavior re file ownership and modes
c 2. Fix file load to issues messages properly
e
s 00014/00000/00928
d D 1.5 98/07/16 14:53:29 clyde 5 4
c Set new history files to group owner PASSWORD_HISTORY_GID (if defined)
e
s 00038/00008/00890
d D 1.4 98/07/09 14:28:35 clyde 4 3
c 1. Change debug table
c 2. Use set_debug_tag() and set_debug() instead of DebugLevel var
c 3. Add -Xh help option
c 4. Issue fuller help message if argument error
e
s 00000/00008/00898
d D 1.3 98/07/09 11:09:15 clyde 3 2
c  Remove pw_svc stuff
e
s 00012/00007/00894
d D 1.2 98/06/23 10:45:48 clyde 2 1
c 1. Fix new file build (method file)
c 2. Fix password history mechanism configure call
e
s 00901/00000/00000
d D 1.1 98/06/16 16:56:28 clyde 1 0
c date and time created 98/06/16 16:56:28 by clyde
e
u
U
f e 0
t
T
I 1
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
 * %M%
 *	Utility to administer the password history database.
 *
 *	This is an extension of the npasswd password history routines,
 *	and shares a lot of state internal to that code.
 */
#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu) %P%";
#endif

/*
 * System includes
 */
#include <stdio.h>
#include <ctype.h>
I 6
D 8
#include <grp.h>
E 8
I 8
D 11
/* #include <grp.h> */
E 11
E 8
E 6
D 2
#ifdef	I_NDBM
# include <ndbm.h>
#endif
E 2
/*
 * Npasswd includes
 */
#include "defines.h"
#include "compatibility.h"
#include "options.h"
D 3
#include "pw_svc.h"
E 3
#include "pwck_defines.h"
#include "pwck_history.h"

I 2
#ifdef	I_NDBM
# include <ndbm.h>
#endif

I 11
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
E 11
E 2
int	logging = 0;		/* Emit messages via syslog? */
int	verbose = 0;		/* User level verbose */
D 4
int	DebugLevel = 0;		/* Debug level for npasswd lib */
char	*ProgramName = "history_admin";	/* Program name for die() and warn() */
E 4
void	(*xdie)() = die;	/* Fatal error report routine */
				/* Either die() or logdie() in comobj.a */
I 6

E 6
I 4
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
E 4
D 3
struct pw_svc	svc;		/* Required by npasswd lib */
E 3

char *Usage = "Usage: %s\n\
	[-a N]		Set password retention age to N days\n\
	[-c file]	Alternate npasswd configuration file\n\
	[-d N]		Set password retention depth to N\n\
	[-f file]	Set database path\n\
I 11
	[-i file]	Input data file\n\
E 11
	[-l]		Log errors via syslog\n\
	[-m method]	Set database method\n\
	[-v]		Verbose mode\n\
D 4
	[-XDN]		Set internal debug level to N\n\
E 4
I 4
	[-XDN]		Set debug level\n\
	[-Xh]		Help\n\
E 4
	function	What to do:\n\
		load - build history database from stdin\n\
I 7
D 9
		append - append to history database from stdin\n\
E 9
I 9
		merge - merge into history database from stdin\n\
E 9
E 7
		dump - dump history database to stdout\n\
		purge - remove dead users and old passwords\n\
";

/*
 * Function prototypes
 */
char	*filter_input _((char *));
int	file_dump _((char *));
D 7
int	file_load _((char *, FILE *));
E 7
I 7
int	file_load _((char *, FILE *, int));
E 7
int	file_purge _((char *));
#ifdef	I_NDBM
int	dbm_dump _((char *));
D 7
int	dbm_load _((char *, FILE *));
E 7
I 7
D 11
int	dbm_load _((char *, FILE *, int));
E 11
I 11
int	dbm_load _((char *, FILE *));
int	dbm_merge _((char *, FILE *));
E 11
E 7
int	dbm_purge _((char *));
#endif

I 4
#define	ProgramName	"history_admin"
I 11
#define	vprintf		if (verbose) printf
#define	nullstr(_P_)	((_P_) == NULL || *(_P_) == 0)
E 11

E 4
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
I 11
	FILE	*input = stdin;		/* Data stream */
E 11
	extern char	*optarg;	/* From getopt() */
	extern int	optind;		/* From getopt() */

I 4
	set_debug_tag(ProgramName); /* Tag for die() and warn() */
E 4
	/*
	 * Process command line arguments
	 */
D 11
	while ((opt = getopt(argc, argv, "a:c:d:f:lm:vX:")) != EOF) {
E 11
I 11
	while ((opt = getopt(argc, argv, "a:c:d:f:i:lm:vX:")) != EOF) {
E 11
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
I 11
		case 'i':	/* -i input-file */
			if ((input = fopen(optarg, "r")) == NULL) {
				perror(optarg);
				die("Cannot open input file\n");
			}
			break;
E 11
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
D 4
			case 'D':	DebugLevel = atoi(++optarg);
					break;
E 4
I 4
			case 'D':
				set_debug(++optarg, admin_debug);
I 11
				verbose = 1;
E 11
				break;
			case 'h': {
				debug_table *dt = admin_debug;

				printf(Usage, argv[0]);
				printf("Debug levels (-XD...):\n");
				for (; dt->name; dt++)
					printf(" %s\t%s\n", dt->name, dt->help);
				return(0);
				}
I 11
			case 'V':
				printf("Version %s of %s\n", "%I%", "%G%");
				return(0);
E 11
E 4
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
D 4
	if (function == 0)
		(*xdie)(Usage, argv[0]);
E 4
I 4
	if (function == 0) {
		debug_table *dt = admin_debug;
E 4

I 4
		printf(Usage, argv[0]);
		printf("Debug levels (-XD...):\n");
		for (; dt->name; dt++)
			printf(" %s\t%s\n", dt->name, dt->help);
		return(1);
	}
D 11

E 11
E 4
	/*
D 3
	 * Get service order.  This program doesn't use the data, but
	 * library routines need for 'svc' to be reasonable
	 */
	(void) get_pwsvc(argc, argv, envp, &svc);      

	/*
E 3
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
D 7
	 * Database path set on command line?
E 7
I 7
	 * Database path or method set on command line?
E 7
	 */
D 7
	if (dbfile) {
E 7
I 7
	if (dbfile || strcmp(method, DEFAULT_METHOD)) {
E 7
D 2
		char	tmp[BUFSIZ];
E 2
I 2
		char	*tmp[4];
		char	*error;
E 2

D 2
		(void) sprintf(tmp, "database %s %s", method, dbfile);
E 2
I 2
		tmp[0] = "database";
		tmp[1] = method;
D 7
		tmp[2] = dbfile;
E 7
I 7
		tmp[2] = dbfile ? dbfile : HISTORYDB_DEFAULT;
E 7
		tmp[3] = 0;
E 2
		if (error = pwck_history_configure(tmp))
D 12
			(*xdie)(
			"Database error: file '%s' method '%s' error '%s'\n",
E 12
I 12
			(*xdie)("Database error: file '%s' method '%s' error '%s'\n",
E 12
				dbfile, method, error);
	}

D 4
	if (DebugLevel) {
E 4
I 4
	if (get_debug()) {
E 4
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
D 7
			return(file_load(HistoryDB, stdin));
E 7
I 7
D 11
			return(file_load(HistoryDB, stdin, 0));
E 11
I 11
			return(file_load(HistoryDB, input, 0));
E 11
E 7
#ifdef	I_NDBM
		if (Method_DBM)
D 7
			return(dbm_load(HistoryDB, stdin));
E 7
I 7
D 11
			return(dbm_load(HistoryDB, stdin, 0));
E 11
I 11
			return(dbm_load(HistoryDB, input));
E 11
E 7
#endif
		return(2);
	}
	/*
I 7
D 9
	 * Function 'append' - append to history from stdin data
E 9
I 9
	 * Function 'merge' - merge to history from stdin data
E 9
	 */
D 9
	if (instringcase(function, "append")) {
E 9
I 9
	if (instringcase(function, "merge")) {
E 9
		if (HistoryDB == 0)
			(*xdie)("No history database\n");
		if (Method_File)
D 11
			return(file_load(HistoryDB, stdin, 1));
E 11
I 11
			return(file_load(HistoryDB, input, 1));
E 11
#ifdef	I_NDBM
		if (Method_DBM)
D 11
			return(dbm_load(HistoryDB, stdin, 1));
E 11
I 11
			return(dbm_merge(HistoryDB, input));
E 11
#endif
		return(2);
	}
	/*
E 7
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
I 11
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
E 11
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
D 9
 * Awk scirpt to spew the last history line for each user
E 9
I 9
D 11
 * Awk script to spew the last history line for each user
E 11
I 11
 * file_read
 *	Read a history database and store in list
 *
 * There may be multiple records for a user, only the last of which is used.
 *
 * Returns
 *	List descriptor on success
 *	Aborts on error
E 11
E 9
 */
D 10
#define	FileIncantation \
E 10
I 10
D 11
#define	FileOutputCommand \
E 10
"/bin/awk 'BEGIN {FS = \":\"} {u[$1] = $0} END {for (f in u) {print u[f]}}'"
E 11
I 11
list_table	*
file_read(file)
	char	*file;			/* History file */
{
	FILE		*in;		/* Input file pointer */
	list_table	*nl;		/* List table pointer */
	char		buf[BUFSIZ];	/* Input buffer */
E 11

I 11
	if ((nl = list_new()) == NULL)
D 12
		(*xdie)("file_read: Cannot allocate list\n");
E 12
I 12
		(*xdie)("No memory for read list\n");
E 12

	if ((in = fopen(file, "r")) == NULL) {
		int xerrno = errno;

		perror(file);
D 12
		(*xdie)("file_read: Cannot open history file '%s', error %d\n",
E 12
I 12
		(*xdie)("Cannot open history file '%s', error %d\n",
E 12
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

E 11
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
D 11
	FILE	*file_in,		/* Input stream */
		*file_out;		/* Output stream */
	char	tempfile[MAXPATHLEN],	/* Temp history file */
		savefile[MAXPATHLEN],	/* Saved history file */
E 11
I 11
	FILE	*out;			/* Output stream */
	char	*tempfile,		/* Temp history file */
		*savefile,		/* Saved history file */
E 11
		buf[HISTORY_RECLEN];	/* Read buffer */
	int	errors = 0,		/* Error count */
		how_many = 0,		/* Record count */
		deleted = 0,		/* Deleted record count */
		t;			/* Temp */
D 11
	struct stat	stb;		/* History file stat */
E 11
I 11
	list_table	*history;	/* History list */
	list_item	*hi;		/* History list item */
E 11

	if (access(file, 0) < 0) {
		if (verbose)
			warn("No history file\n");
		return(1);
	}
I 11

E 11
	/*
D 11
	 * Invoke history file filter
	 */
D 10
	(void) sprintf(buf, "%s %s", FileIncantation, file);
E 10
I 10
	(void) sprintf(buf, "%s %s", FileOutputCommand, file);
E 10
	if ((file_in = popen(buf, "r")) == NULL) {
		if (verbose)
			warn("Filter popen failed\n");
		return(1);
	}
	/*
E 11
	 * Construct temporary and save file names
	 */
D 11
	(void) strcpy(tempfile, file);
	(void) strcat(tempfile, ".temp");
	(void) strcpy(savefile, file);
	(void) strcat(savefile, ".old");
E 11
I 11
	if ((tempfile = malloc(strlen(file) + 8)) == 0)
		(*xdie)("No memory for tempfile string\n");
	(void) sprintf(tempfile, "%s.temp", file);

	if ((savefile = malloc(strlen(file) + 8)) == 0)
		(*xdie)("No memory for savefile string\n");
	(void) sprintf(savefile, "%s.old", file);

E 11
	/*
	 * Create the temp file
	 */
	if ((t = MakeLockTemp(tempfile)) < 0) {
		(*xdie)("Cannot make temp file '%s', error %d\n",
			tempfile, errno);
	}
D 11
	file_out = fdopen(t, "w");		/* Get stdio pointer */

E 11
I 11
	out = fdopen(t, "w");		/* Get stdio pointer */
E 11
	debug(DB_VERBOSE, "purge_file: file '%s'\ntemp '%s'\nsave '%s'\n",
		file, tempfile, savefile);

	/*
D 11
 	 * Give temp file ownership and mode of the original
E 11
I 11
	 * Traverse the history, checking if the user is still in the
	 * password file and if so, clean their entry and put to temp file.
E 11
	 */
D 11
	(void) stat(file, &stb);
D 6
	if (stb.st_uid != getuid()) {
		if (chown(tempfile, stb.st_uid, stb.st_gid) < 0) {
			perror("History temp chown");
			errors++;
		}
E 6
I 6
	if (chown(tempfile, stb.st_uid, stb.st_gid) < 0) {
		perror("History temp chown");
		errors++;
E 6
	}
D 6
        if (chmod(tempfile, HISTORYDB_MODE) < 0) {
E 6
I 6
        if (chmod(tempfile, stb.st_mode) < 0) {
E 6
		perror("History temp chmod");
		errors++;
	}
E 11
I 11
	history = file_read(file);
	for (hi = list_first(history); hi; hi = list_next(history)) {
		char	*t;	/* Temp */
E 11

D 11
	while (fgets(buf, sizeof(buf), file_in)) {
		char	*c,		/* Temp */
			*t;		/* Temp */
		char	name[16];	/* User name temp */

E 11
		how_many++;
D 11
		c = strchr(buf, ENTRY_SEP);
		*c++ = 0;
		(void) strcpy(name, buf);
		/*
		 * What about alternate passwd maps/files?
		 */
		if (getpwnam(name) == 0) {
			if (verbose)
D 7
				printf("User '%s' removed\n", name);
E 7
I 7
				printf("Delete history for %s (not in passwd)\n", name);
E 11
I 11
		if (getpwnam(hi->tag) == 0) {
			vprintf("Delete history for %s (not in passwd)\n", hi->tag);
E 11
E 7
			deleted++;
			continue;
		}
D 7
		t = clean_history(c, HistoryDepth, HistoryAge, 0, 0);
E 7
I 7
D 11
		if ((t = clean_history(c, HistoryDepth, HistoryAge, 0, 0)) == NULL) {

			printf("Delete history for %s (null)\n", name);
E 11
I 11
		t = clean_history(hi->data, HistoryDepth, HistoryAge, 0, 0);
		if (nullstr(t)) {
			vprintf("Delete history for %s (null)\n", hi->tag);
E 11
			continue; 
		}
E 7
D 11
		debug(DB_VERBOSE, "Purge: new <%s%c%s>\n", name, ENTRY_SEP, t);
		(void) fprintf(file_out, "%s%c%s\n", name, ENTRY_SEP, t);
E 11
I 11
		debug(DB_DETAIL, "New purge entry <%s%c%s>\n",
			hi->tag, ENTRY_SEP, t);
		(void) fprintf(out, "%s%c%s\n", hi->tag, ENTRY_SEP, t);
E 11
	}
D 11
	(void) fclose(file_in);
	(void) fclose(file_out);
E 11
I 11
	(void) fclose(out);
E 11

	/*
	 * Install temp file as history file
	 */
D 11
	if (errors) {
E 11
I 11
	if (clone_file_stat(file, tempfile)) {
E 11
		warn("History purge errors - new database left in '%s'\n",
			tempfile);
		return(1);
	}
D 11
	(void) unlink(savefile);
	if (rename(file, savefile) < 0) {	/* Move current to save */
		int xerrno = errno;

		perror("History file save failure");
		if (logging)
			logerr("History file save failure %d", xerrno);
		(void) unlink(tempfile);
E 11
I 11
	if (install_file(file, tempfile, savefile)) {
		warn("History purge errors - new database left in '%s'\n",
			tempfile);
E 11
		return(1);
	}
D 11
	if (rename(tempfile, file) < 0) {	/* Move new to current */
		int xerrno = errno;
E 11

D 11
		perror("History file temp rename failure");
		if (logging)
			logerr("History file temp rename failure %d", xerrno);
		(void) unlink(tempfile);
		(void) unlink(file);
		if (rename(savefile, file) < 0) {
			int xerrno = errno;
		
			perror("Saved history file putback failure");
			if (logging)
				logerr("Saved history file putback failure %d",
					xerrno);
		}
		return(1);
	}
	/*
	 * Success - confirm and finish
 	 */
E 11
	if (logging)
		syslog(LOG_INFO,
			"Password history purge: %d records %d deletions",
			how_many, deleted);
D 11
	if (verbose)
		printf("Password history purge: %d records %d deletions\n",
			how_many, deleted);
E 11
I 11
	vprintf("Password history purge: %d records %d deletions\n",
		how_many, deleted);
E 11
	return(0);
}

/*
 * file_dump
 *	Dump a flat file history database to standard output
 *	Entries are not run through clean_history()
 *
 * Returns
 *	0 on success
D 11
 *	1 on failure
E 11
I 11
 *	1 if history file missing
E 11
 */
file_dump(file)
D 11
	char *file;		/* History file */
E 11
I 11
	char	*file;		/* History file */
E 11
{
D 10
	FILE	*in;		/* Input stream */
	char	buf[HISTORY_RECLEN]; /* Read buffer */
E 10
I 10
D 11
	char	buf[BUFSIZ]; 	/* Command build buffer */
E 11
I 11
	list_table	*hlist;	/* List pointer */
	list_item	*hitem;	/* List item */
E 11
E 10

	if (access(file, 0) < 0) {
		if (verbose)
			warn("No history file\n");
		return(1);
	}
D 10
	(void) sprintf(buf, "%s %s", FileIncantation, file);
	if ((in = popen(buf, "r")) == NULL) {
		if (verbose)
			warn("Filter popen failed\n");
		return(1);
	}
	while (fgets(buf, sizeof(buf), in)) {
I 7
		if (*buf == '\n')
			continue;
E 7
		printf("%s", buf);
	}
	(void) fclose(in);
E 10
I 10
D 11
	(void) sprintf(buf, "%s %s", FileOutputCommand, file);
	(void) system(buf);
E 11
I 11
	hlist = file_read(file);
	for (hitem = list_first(hlist); hitem; hitem = list_next(hlist)) {
		printf("%s%c%s\n", hitem->tag, ENTRY_SEP, hitem->data);
	}
E 11
E 10
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
I 10
D 11
#define	FileMergeCommand \
"/bin/awk 'BEGIN {FS = \":\"} { t = u[$1]; \
	if (t != \"\") { \
		for (i = 2; i<=NF; i++) t = t\":\"$i; \
		u[$1] = t; \
	} else { \
		u[$1] = $0; } \
	} \
	END {for (f in u) {print u[f]}}' | sed 's/::/:/g'"

E 11
E 10
D 7
file_load(file, input)
E 7
I 7
D 9
file_load(file, input, append)
E 9
I 9
file_load(file, input, merge)
E 9
E 7
	char	*file;			/* History file */
	FILE	*input;			/* Input stream */
I 7
D 9
	int	append;			/* Add to existing data? */
E 9
I 9
	int	merge;			/* Add to existing data? */
E 9
E 7
{
D 10
	FILE	*file_out;		/* Output stream */
E 10
I 10
D 11
	FILE	*file_out,		/* Output stream */
		*orig_in;		/* Original input stream */
E 10
	char	tempfile[MAXPATHLEN],	/* Temp history file */
		savefile[MAXPATHLEN],	/* Saved history file */
E 11
I 11
	FILE	*out;			/* Output stream */
	char	*tempfile,	/* Temp history file */
		*savefile,	/* Saved history file */
E 11
		buf[HISTORY_RECLEN];	/* Read buffer */
D 11
	int	errors = 0,		/* Error count */
		how_many = 0,		/* Record count */
		new_file = 0,		/* Making new history file? */
		t;			/* Temp */
	struct stat	stb;		/* History file stat */
E 11
I 11
	int	how_many = 0,		/* Record count */
		ofd;			/* Temp */
	list_table	*hlist;
	list_item	*hitem;
E 11

D 7
	/*
	 * Construct temporary file name
	 */
	(void) strcpy(tempfile, file);
E 7
I 7
D 11
	(void) strcpy(tempfile, file);	/* Construct temporary file name */
E 7
	(void) strcat(tempfile, ".temp");
E 11
I 11
	/*
	 * Construct temporary and save file names
	 */
	if ((tempfile = malloc(strlen(file) + 8)) == 0)
		(*xdie)("No memory for tempfile string\n");
	(void) sprintf(tempfile, "%s.temp", file);
E 11

D 7
	/*
 	 * Give temp file ownership of the original (if present)
	 */
E 7
D 10
	if (stat(file, &stb) < 0) {
E 10
I 10
D 11
	if (stat(file, &stb) < 0) {	/* Loading to new file */
E 10
		new_file = 1;
D 7
		(void) strcpy(tempfile, file);
E 7
I 7
D 10
	} else {
D 9
		if (append) new_file = 2;
E 9
I 9
		if (merge) new_file = 2;
E 10
I 10
		(void) strcpy(tempfile, file);
		if ((t = MakeLockTemp(tempfile)) < 0) {
			(*xdie)("Cannot make temp file '%s', error %d\n",
				tempfile, errno);
		}
	} else { 		/* Replacing existing file */
		if ((t = MakeLockTemp(tempfile)) < 0) {
			(*xdie)("Cannot make temp file '%s', error %d\n",
				tempfile, errno);
		}
		if (chown(tempfile, stb.st_uid, stb.st_gid) < 0) {
			perror("History temp chown");
			errors++;
		}
		if (chmod(tempfile, stb.st_mode) < 0) {
			perror("History temp chmod");
			errors++;
		}
E 11
I 11
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
E 11
E 10
E 9
E 7
D 6
	} else {
		if (stb.st_uid != getuid()) {
			if (chown(tempfile, stb.st_uid, stb.st_gid) < 0) {
				perror("History temp chown");
				errors++;
			}
		}
E 6
	}
I 7
D 10
	switch (new_file) {
		case 0:	/* Replacing existing file */
			if ((t = MakeLockTemp(tempfile)) < 0) {
				(*xdie)("Cannot make temp file '%s', error %d\n",
					tempfile, errno);
			}
			if (chown(tempfile, stb.st_uid, stb.st_gid) < 0) {
				perror("History temp chown");
				errors++;
			}
			if (chmod(tempfile, stb.st_mode) < 0) {
				perror("History temp chmod");
				errors++;
			}
			break;
E 10
I 10
D 11
	file_out = fdopen(t, "w");		/* Get stdio pointer */
E 11
I 11
	out = fdopen(ofd, "w");		/* Get stdio pointer */
E 11
E 10
E 7
D 6
	/*
	 * Create the temp file
	 */
E 6
I 6

E 6
D 7
	if ((t = MakeLockTemp(tempfile)) < 0) {
		(*xdie)("Cannot make temp file '%s', error %d\n",
			tempfile, errno);
	}
E 7
I 7
D 10
		case 1:	/* Loading to new file */
			(void) strcpy(tempfile, file);
			if ((t = MakeLockTemp(tempfile)) < 0) {
				(*xdie)("Cannot make temp file '%s', error %d\n",
					tempfile, errno);
			}
			break;
E 10
I 10
	/*
D 11
	 * Doing a merge properly is a lot easier using PERL
	 * associative arrays, but don't want to require the presence of
	 * PERL (if I were willing to do that, this program would be
	 * a PERL script).  But awk also has associative arrays, and what
	 * I need done is easy.
	 * 
	 * In merge mode, invoke awk scripts to dump the database
	 * (equivilant to the 'dump' function) and read the input stream
 	 * and feed to another awk script which does the merge dirty work.
	 *
	 * What makes below work is having sh(1) syntax to 
	 * redirect arbitrary file descriptors.
	 *
	 * The input stream had better be something which can be positioned
	 * with fseek().
E 11
I 11
	 * If merging read the database, else make new list
E 11
	 */
D 11
	orig_in = input;
	if (merge) {
		FILE	*pipe_in;
		char	buf[BUFSIZ];
E 11
I 11
	if (merge)
		hlist = file_read(file);
	else
		hlist = list_new();
E 11
E 10
E 7
D 6
	file_out = fdopen(t, "w");		/* Get stdio pointer */
E 6

D 6
	/*
	 * Fix temp file mode
	 */
        if (chmod(tempfile, HISTORYDB_MODE) < 0) {
		perror("History temp chmod");
		errors++;
E 6
I 6
D 7
	if (new_file == 0) {
		if (chown(tempfile, stb.st_uid, stb.st_gid) < 0) {
			perror("History temp chown");
			errors++;
		}
		if (chmod(tempfile, stb.st_mode) < 0) {
			perror("History temp chmod");
			errors++;
		}
E 7
I 7
D 10
		case 2:	/* Appending to existing file */
			if ((t = OpenWithLock(file)) < 0) {
				(*xdie)("Cannot open file '%s', error %d\n",
					file, errno);
			}
			break;
E 7
E 6
	}
I 7
	file_out = fdopen(t, "a");		/* Get stdio pointer */
E 10
I 10
D 11
		if (new_file == 0) {		/* Include current db */
			(void) sprintf(buf, "(%s %s; cat - <&%d) | %s",
				FileOutputCommand, file, fileno(input),
				FileMergeCommand);
		} else {			/* Just process merge data */
			(void) sprintf(buf, "cat - <&%d | %s",
				fileno(input), FileMergeCommand);
		}
		rewind(input);
E 10
E 7
I 5
D 6
#ifdef	PASSWD_HISTORY_GID
        if (chown(tempfile, -1, PASSWD_HISTORY_GID) < 0) {
		perror("History temp chown");
		errors++;
	}
#endif
E 6
E 5

I 10
		if ((pipe_in = popen(buf, "r")) == NULL) {
			if (verbose)
				warn("Filter popen failed\n");
			(void) fclose(file_out);
			if (new_file == 0)
				(void) unlink(tempfile);
			return(1);
		}
		input = pipe_in;
	}
E 11
E 10
I 6
D 7
	file_out = fdopen(t, "w");		/* Get stdio pointer */
E 7
E 6
	/*
D 10
	 * Read history lines from stdin and pack into the database
E 10
I 10
D 11
	 * Read history lines from <input> and pack into the database
E 11
I 11
	 * Read history lines from <input> and pack/merge into the database
E 11
E 10
	 */
	while (fgets(buf, sizeof(buf), input)) {
D 11
		char	*c,		/* Temp */
			*t;		/* Temp */
		char	name[16];	/* Temp */
E 11
I 11
		char	*iptr,
			*dptr;		/* Temp */
E 11

		chop_nl(buf);
D 11

		if ((t = filter_input(buf)) == 0)
E 11
I 11
		if ((iptr = filter_input(buf)) == 0)
E 11
			continue;
D 11
		if ((c = strchr(t, ENTRY_SEP)) == 0)
E 11
I 11
		if ((dptr = strchr(iptr, ENTRY_SEP)) == 0)
E 11
			continue;
D 11
		*c++ = 0;
		(void) strcpy(name, t);
D 7
		t = clean_history(c, 0, 0, 0, 0);
E 7
I 7
		if ((t = clean_history(c, 0, 0, 0, 0)) == NULL)
			continue;
E 7
		(void) fprintf(file_out, "%s%c%s\n", name, ENTRY_SEP, t);
E 11
I 11
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
E 11
		how_many++;
	}
D 11
	(void) fclose(file_out);
E 11

I 10
D 11
	if (input != orig_in)
		(void) fclose(input);
E 11
I 11
	/*
	 * Traverse the history list, clean the entries and put
	 * into the new history
	 */
	for (hitem = list_first(hlist); hitem; hitem = list_next(hlist)) {
		char	*t = clean_history(hitem->data, 0, 0, 0, 0);
E 11

E 10
D 11
	if (errors) {
D 7
		warn("History load errors - new database left as '%s'\n",
			tempfile);
E 7
I 7
D 9
		if (append)
			warn("History append errors on '%s'\n", file);
E 9
I 9
D 10
		if (merge)
			warn("History merge errors on '%s'\n", file);
E 9
		else
			warn("History load errors - new database left as '%s'\n",
				tempfile);
E 10
I 10
		warn("History %s errors - database left as '%s'\n",
			merge ? "merge" : "load", tempfile);
E 10
E 7
		return(1);
E 11
I 11
		if (nullstr(t))		/* "Shouldn't happen" */
			continue;
		(void) fprintf(out, "%s%c%s\n", hitem->tag, ENTRY_SEP, t);
E 11
	}
D 2
	if (new_file == 0)		/* Created from scratch? */
		return(0);		/* All done */
E 2
I 2
D 6
	if (new_file)		/* Created from scratch? */
		return(0);	/* All done */
E 2

	/*
	 * Install temp file as history file
	 */
	(void) strcpy(savefile, file);
	(void) strcat(savefile, ".old");

	(void) unlink(savefile);
	if (rename(file, savefile) < 0) {	/* Move current to save */
		int xerrno = errno;

		perror("History file save failure");
		if (logging)
			logerr("History file save failure %d", xerrno);
		(void) unlink(tempfile);
		return(1);
	}
	if (rename(tempfile, file) < 0) {	/* Move new to current */
		int xerrno = errno;

		perror("History file temp rename failure");
		if (logging)
			logerr("History file temp rename failure %d", xerrno);
		(void) unlink(tempfile);
		(void) unlink(file);
		if (rename(savefile, file) < 0) {
E 6
I 6
D 11
	if (new_file == 0) {
		/*
		 * Install temp file as history file
		 */
		(void) strcpy(savefile, file);
		(void) strcat(savefile, ".old");
	
		(void) unlink(savefile);
		if (rename(file, savefile) < 0) { /* Move current to save */
E 6
			int xerrno = errno;
D 6
		
			perror("Saved history file putback failure");
E 6
I 6
	
			perror("History file save failure");
E 6
			if (logging)
D 6
				logerr("Saved history file putback failure %d",
					xerrno);
E 6
I 6
				logerr("History file save failure %d", xerrno);
			(void) unlink(tempfile);
E 11
I 11
	(void) fclose(out);

	/*
	 * If the database file exists, copy the mode and ownership
	 */
	if (access(file, 0) == 0) {
		if (clone_file_stat(file, tempfile)) {
			warn("History load/merge errors - new database left in '%s'\n",
				tempfile);
E 11
			return(1);
E 6
		}
D 6
		return(1);
E 6
I 6
D 11
		if (rename(tempfile, file) < 0) { /* Move new to current */
			int xerrno = errno;
	
			perror("History file temp rename failure");
			if (logging)
				logerr("History file temp rename failure %d", xerrno);
			(void) unlink(tempfile);
			(void) unlink(file);
			if (rename(savefile, file) < 0) {
				int xerrno = errno;
			
				perror("Saved history file putback failure");
				if (logging)
					logerr("Saved history file putback failure %d",
						xerrno);
			}
			return(1);
		}
E 11
E 6
	}
	/*
D 11
	 * Success - confirm and finish
E 11
I 11
	 * Move temp file to database file
	 */
	if (install_file(file, tempfile, savefile)) {
		warn("History load/merge errors - new database left in '%s'\n",
			tempfile);
		return(1);
	}
	/*
	 * Confirm and finish
E 11
 	 */
	if (logging)
D 6
		syslog(LOG_INFO, "Password history load: %d records", how_many);
E 6
I 6
D 7
		syslog(LOG_INFO, "Load password history to file '%s': %d records",
			file, how_many);
E 7
I 7
D 10
		syslog(LOG_INFO, "%s %d records to history file '%s'",
D 9
			append ? "Add" : "Load", how_many, file);
E 9
I 9
			merge ? "Add" : "Load", how_many, file);
E 10
I 10
D 11
		syslog(LOG_INFO, "%d records added/merged to history file '%s'",
			how_many, file);
E 10
E 9
E 7
E 6
	if (verbose)
D 6
		printf("Password history load complete\n");
E 6
I 6
D 7
		printf("Loaded %d records to password history file '%s'\n",
			how_many, file);
E 7
I 7
D 10
		printf("%s %d records to password history file '%s'\n",
D 9
			append ? "Add" : "Load", how_many, file);
E 9
I 9
			merge ? "Add" : "Load", how_many, file);
E 10
I 10
		printf("%d records added/merged to password history file '%s'\n",
			how_many, file);
E 11
I 11
		syslog(LOG_INFO, "%d records %sed to history file '%s'",
			how_many, (merge ? "merg" : "add"), file);
	vprintf("%d records %sed to password history file '%s'\n",
		how_many,  (merge ? "merg" : "add"), file);
E 11
E 10
E 9
E 7
E 6
	return(0);
}
I 10
D 11
#undef	FileMergeCommand
#undef	FileOutputCommand
E 11
E 10

/*
 * Routines for manipulating DBM history databases
 */

#ifdef	I_NDBM
I 11
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
E 11
/* 
 * dbm_purge
 *	Cleanup DBM history database
 *
 * Returns
D 11
 *	0 on success
 *	1 on failure
E 11
I 11
 *	number of errors
E 11
I 7
 *
 * NOTE: Does not free all dynamically allocated storage
E 7
 */
dbm_purge(file)
	char *file;			/* History DBM file */
{
	DBM	*hdb;		/* Database pointer */
	datum	hkey;		/* DBM lookup datum */
D 11
	int	how_many = 0,	/* Entry counter */
E 11
I 11
	int	count = 0,	/* Entry counter */
E 11
D 7
		deleted = 0;	/* Deletion counter */
E 7
I 7
		deleted = 0,	/* Deletion counter */
		errors = 0;	/* Errors encountered */
D 11
	char	**purge_list,
		**purge_tail;
	char	**update_list,
		**update_tail;
E 11
I 11
	list_table	*history;/* History list */
	list_item	*hi;	/* List item */
E 11
E 7

	/*
	 * Open database
	 */
	if ((hdb = dbm_open(file, O_RDWR, 0)) == 0) {
D 11
		perror("Cannot open history DBM\n");
E 11
I 11
		perror("History DBM open");
E 11
		if (logging)
D 11
			logerr("Cannot open DBM history database");
E 11
I 11
			logerr("Cannot open DBM '%s' for purge", file);
E 11
		return(1);
	}
I 7

E 7
	/*
D 7
	 * Step through the keys in the database
E 7
I 7
D 11
	 * Count keys in database and allocate save space
E 11
I 11
	 * Traverse the database, checking if the user is still in the
	 * password file and store the result
E 11
E 7
	 */
D 11
	for (hkey = dbm_firstkey(hdb); hkey.dptr != NULL; hkey = dbm_nextkey(hdb)) {
D 7
		datum	hdata;		/* Data lookup temp */
		char    *new,		/* New entry temp */
			*key,		/* Key lookup temp */
			*data;		/* Data temp */

E 7
		how_many++;
D 7
		if ((key = malloc(hkey.dsize + 1)) == NULL)
E 7
I 7
	}
D 9
	purge_list = purge_tail = calloc(how_many + 1, sizeof (char *));
	update_list = update_tail = calloc(how_many + 1, sizeof (char *));
E 9
I 9
D 10
	purge_list = purge_tail = (char **)calloc(how_many + 1, sizeof (char *));
	update_list = update_tail = (char **)calloc(how_many + 1, sizeof (char *));
E 10
I 10
	purge_list = purge_tail = (char **)calloc(how_many + 32, sizeof (char *));
	update_list = update_tail = (char **)calloc(how_many + 32, sizeof (char *));
E 11
I 11
	if ((history = list_new()) == 0)
D 12
		(*xdie)("Cannot allocate DBM purge list\n");
E 12
I 12
		(*xdie)("No memory for DBM purge list\n");
E 12
E 11
E 10
E 9

D 11
	/*
	 * Step through the keys in the database, checking if the
	 * entry should be purged or cleaned.
	 */
E 11
	for (hkey = dbm_firstkey(hdb); hkey.dptr != NULL; hkey = dbm_nextkey(hdb)) {
D 11
		char	*tmp;
E 11
I 11
		char	tmp[DBLKSIZ];	/* String temp */
E 11

D 11
		if ((tmp = malloc(hkey.dsize + 1)) == NULL)
E 7
			(*xdie)("No memory for DBM key copy\n");
D 7
		(void) strncpy(key, hkey.dptr, hkey.dsize);
		key[hkey.dsize] = 0;
E 7
I 7
		(void) strncpy(tmp, hkey.dptr, hkey.dsize);
		tmp[hkey.dsize] = 0;
E 11
I 11
		dbm2str(tmp, hkey);
E 11
		if (getpwnam(tmp))
D 11
			*update_tail++ = tmp;
E 11
I 11
			list_insert(history, tmp, "U");	/* Update this entry */
E 11
		else
D 11
			*purge_tail++ = tmp;
E 11
I 11
			list_insert(history, tmp, "D");	/* Delete this entry */
		count++;
E 11
	}
E 7

D 7
		/*
		 * Is this user in the password file?
		 */
		if (getpwnam(key) == NULL) {
			if (verbose)
				printf("User %s not in passwd file\n", key);
			(void) dbm_delete(hdb, hkey);
			continue;
		}
E 7
I 7
	/*
D 11
	 * Delete entries for users no longer in passwd
E 11
I 11
	 * Traverse the history list, cleaning and deleting entries as needed
E 11
	 */
D 11
	for (purge_tail = purge_list; *purge_tail; purge_tail++) {
		datum	dkey;		/* Data delete temp */
E 11
I 11
	for (hi = list_first(history); hi; hi = list_next(history)) {
		datum	ukey;		/* Lookup temp */
		datum	udata;		/* Data temp */
		char	hdata[DBLKSIZ];	/* String temp */
		char	*ht;		/* String temp */
E 11
E 7

D 7
		hdata = dbm_fetch(hdb, hkey);
E 7
I 7
D 11
		dkey.dptr = *purge_tail;
		dkey.dsize = strlen(dkey.dptr);
		(void) dbm_delete(hdb, dkey);
		if (verbose)
			printf("Delete history for %s (not in passwd)\n",
				*purge_tail);
	}
E 11
I 11
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
E 11

D 11
	/*
	 * Clean and update entries for users in passwd
	 */
	for (update_tail = update_list; *update_tail; update_tail++) {
		datum	ukey;		/* Data update temp */
		datum	hdata;		/* Data lookup temp */
		char	*new,
			*data;

		ukey.dptr = *update_tail;
		ukey.dsize = strlen(ukey.dptr);

		hdata = dbm_fetch(hdb, ukey);
E 7
		if ((data = malloc(hdata.dsize + 1)) == NULL)
			(*xdie)("No memory for DBM key copy\n");
		(void) strncpy(data, hdata.dptr, hdata.dsize);
		data[hdata.dsize] = 0;

D 7
		new = clean_history(data, HistoryDepth, HistoryAge, 0, 0);
E 7
I 7
		if ((new = clean_history(data, HistoryDepth, HistoryAge, 0, 0)) == NULL) {
			(void) dbm_delete(hdb, ukey);
			if (verbose)
				printf("Delete history for %s (null)\n",
					*update_tail);
			free(data);
E 11
I 11
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
E 11
			continue;
		}
D 11
		free(data);
E 7
		hdata.dptr = new;
		hdata.dsize = strlen(new);
D 7
		if (dbm_store(hdb, hkey, hdata, DBM_REPLACE) < 0) {
			warn("DBM replace for '%s' failed", key);
E 7
I 7
		if (dbm_store(hdb, ukey, hdata, DBM_REPLACE) < 0) {
E 11
I 11

		/*
		 * Store the cleaned history entry
		 */
		str2dbm(udata, ht);
		if (dbm_store(hdb, ukey, udata, DBM_REPLACE) < 0) {
E 11
			errors++;
D 11
			warn("DBM replace for %s failed", *update_tail);
E 11
I 11
			warn("DBM replace for %s failed", hi->tag);
E 11
E 7
			if (logging)
D 7
				logerr("DBM replace for '%s' failed", key);
			dbm_close(hdb);
			return(1);
E 7
I 7
D 11
				logerr("DBM replace for %s failed", *update_tail);
E 11
I 11
				logerr("DBM replace for %s failed", hi->tag);
E 11
E 7
		}
D 7
		free(key);
		free(data);
E 7
	}
D 11
	dbm_close(hdb);
E 11
I 11
	dbm_close(hdb);		/* Finished with database */

E 11
I 7
	if (logging)
		syslog(LOG_INFO,
D 11
			"Password history purge: %d records %d deletions %d errors",
			how_many, deleted, errors);
	if (verbose)
		printf("Password history purge: %d records %d deletions %d errors\n",
			how_many, deleted, errors);
E 7
	return(0);
E 11
I 11
			"History purge: %d records %d deletions %d errors",
			count, deleted, errors);
	vprintf("History purge: %d records %d deletions %d errors\n",
		count, deleted, errors);
	return(errors);
E 11
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
D 11
	 * Step through the keys in the database
E 11
I 11
	 * Step through the keys in the database and spew to stdout
E 11
	 */
	for (hkey = dbm_firstkey(hdb); hkey.dptr != NULL; hkey = dbm_nextkey(hdb)) {
		datum	hdata;
D 11
		char	*name,
			*data;
E 11
I 11
		char	name[DBLKSIZ],
			data[DBLKSIZ];
E 11

		hdata = dbm_fetch(hdb, hkey);
D 11

		if ((name = malloc(hkey.dsize + 1)) == NULL)
			(*xdie)("No memory for DBM key copy\n");
		(void) strncpy(name, hkey.dptr, hkey.dsize);
		name[hkey.dsize] = 0;

		if ((data = malloc(hdata.dsize + 1)) == NULL)
			(*xdie)("No memory for DBM key copy\n");
		(void) strncpy(data, hdata.dptr, hdata.dsize);
		data[hdata.dsize] = 0;

E 11
I 11
		dbm2str(name, hkey);
		dbm2str(data, hdata);
E 11
		printf("%s%c%s\n", name, ENTRY_SEP, data);
D 11
		free(data);
		free(name);
E 11
	}
	dbm_close(hdb);
	return(0);
}

/* 
 * dbm_load
D 11
 *	Build history database DBM from stdin data
E 11
I 11
 *	Build history database DBM from input
E 11
 *
 * Returns
D 11
 *	0 on success
 *	1 on failure
E 11
I 11
 *	error count
E 11
 */
D 7
dbm_load(file, input)
E 7
I 7
D 9
dbm_load(file, input, append)
E 9
I 9
D 11
dbm_load(file, input, merge)
E 11
I 11
dbm_load(file, input)
E 11
E 9
E 7
	char	*file;		/* History DBM file */
	FILE	*input;		/* Input stream */
I 7
D 9
	int	append;		/* Add to existing data */
E 9
I 9
D 11
	int	merge;		/* Add to existing data */
E 11
E 9
E 7
{
D 11
	DBM	*hdb;			/* Database pointer */
	char	file_pag[MAXPATHLEN],	/* Database .pag file */
		file_dir[MAXPATHLEN],	/* Database .dir file */
		temp_pag[MAXPATHLEN],	/* Temp file .pag file */
		temp_dir[MAXPATHLEN],	/* Temp file .dir file */
D 7
		temp_file[MAXPATHLEN];	/* Temp file */
E 7
I 7
		tempfile[MAXPATHLEN];	/* Temp file */
E 11
I 11
	DBM	*hdb;		/* Database pointer */
	char	*file_pag,	/* Database .pag name */
		*file_dir,	/* Database .dir name */
		*temp_pag,	/* Temp file .pag name */
		*temp_dir,	/* Temp file .dir name */
		*tempfile,	/* Temp file name */
		*save_dir = NULL,	/* Save file .dir name */
		*save_pag = NULL,	/* Save file .pag name */
		*savefile = NULL;	/* Save file name */
E 11
E 7
	char	inbuf[HISTORY_RECLEN];	/* Read buffer */
D 11
	int	new_file = 0;		/* Making new file */
E 11
I 6
	int	errors = 0;		/* Error count */
	int	how_many = 0;		/* Count of records loaded */
I 7
D 11
	int	open_mode = O_RDWR|O_CREAT;
E 11
E 7
E 6
	struct stat stb;		/* Stat buffer */

#define	db_files(_d_,_p_,_n_) \
D 11
	(void) strcpy(_d_, _n_); (void) strcat(_d_, ".dir"); \
	(void) strcpy(_p_, _n_); (void) strcat(_p_, ".pag");
E 11
I 11
	(void) sprintf(_d_, "%s.dir", _n_);\
	(void) sprintf(_p_, "%s.pag", _n_)
E 11

D 8
	db_files(file_dir, file_pag, file);	/* Make history DB names */

E 8
D 7
	/*
D 6
	 * Making new DB?
E 6
I 6
	 * Database exists?
E 6
 	 */
E 7
I 7
D 11
	(void) strncpy(tempfile, file, MAXPATHLEN);
E 11
I 11
#define	fn_alloc(_d_,_f_,_p_) \
	if ((_d_ = malloc(strlen(_f_) + _p_)) == NULL) \
		(*xdie)("No memory for tempfile string\n")
E 11
D 8
	(void) strcat(tempfile, "-temp");		/* Make temp file */
E 8

I 8
D 11
	db_files(file_dir, file_pag, file);	/* Make history DB names */
E 11
I 11
	/*
	 * Make DB file names
	 */
	fn_alloc(file_dir, file, 8);
	fn_alloc(file_pag, file, 8);
	db_files(file_dir, file_pag, file);
E 11
E 8

E 7
D 11
	if (stat(file_dir, &stb) < 0) {
D 7
		(void) strcpy(temp_file, file);
E 7
		new_file = 1;
	} else {
D 7
		(void) strcpy(temp_file, file);
		(void) strcat(temp_file, "-temp");
E 7
I 7
D 9
		if (append) {
E 9
I 9
		if (merge) {
E 9
			new_file = 1;
			open_mode = O_RDWR;
			(void) strcpy(tempfile, file);
D 8
		}
E 8
I 8
		} else
			(void) strcat(tempfile, "-temp");
E 8
E 7
	}
D 7
	db_files(temp_dir, temp_pag, temp_file);	/* Make temp DB names */
E 7
I 7
	db_files(temp_dir, temp_pag, tempfile);	/* Make temp DB names */
E 11
I 11
	/*
	 * Make temp file names
	 */
	fn_alloc(tempfile, file, 8);
	(void) sprintf(tempfile, "%s.temp", file);
	fn_alloc(temp_dir, tempfile, 6);
	fn_alloc(temp_pag, tempfile, 6);
	db_files(temp_dir, temp_pag, tempfile);
	debug(DB_VERBOSE, "dbm_load: file '%s' temp '%s'\n", file, tempfile);
E 11
E 7

	/*
D 11
	 * Open database read-write
E 11
I 11
	 * Open database
E 11
	 */
D 7
	if ((hdb = dbm_open(temp_file, O_RDWR|O_CREAT, HISTORYDB_MODE)) == 0) {
E 7
I 7
D 11
	if ((hdb = dbm_open(tempfile, open_mode, HISTORYDB_MODE)) == 0) {
E 7
		perror("Cannot open DBM");
D 7
		(*xdie)("Cannot make DBM '%s'\n", temp_file);
E 7
I 7
		(*xdie)("Cannot open/make DBM '%s'\n", tempfile);
E 7
		return(1);
E 11
I 11
	if ((hdb = dbm_open(tempfile, O_RDWR|O_CREAT, HISTORYDB_MODE)) == 0) {
		perror("DBM temp create");
		(*xdie)("Cannot create DBM '%s'\n", tempfile);
E 11
	}
I 5
D 6
#ifdef	PASSWORD_HISTORY_GID
	if (chown(temp_dir, -1, PASSWORD_HISTORY_GID) < 0) {
		perror("Chown DBM dir");
E 6
I 6
D 11
	if (new_file == 0) {
		/*
		 * Give temp files same owner and mode as existing
		 */
		if (chown(temp_dir, stb.st_uid, stb.st_gid) < 0) {
D 7
			perror("Chown DBM dir");
E 7
I 7
			perror("Chown DBM temp dir");
E 7
			errors++;
		}
		if (chmod(temp_dir, stb.st_mode) < 0) {
D 7
			perror("Chmod DBM dir");
E 7
I 7
			perror("Chmod DBM temp dir");
E 7
			errors++;
		}
		if (chown(temp_pag, stb.st_uid, stb.st_gid) < 0) {
D 7
			perror("Chown DBM pag");
E 7
I 7
			perror("Chown DBM temp pag");
E 7
			errors++;
		}
		if (chmod(temp_pag, stb.st_mode) < 0) {
D 7
			perror("Chmod DBM pag");
E 7
I 7
			perror("Chmod DBM temp pag");
E 7
			errors++;
		}
E 6
	}
E 11
D 6
	if (chown(temp_pag, -1, PASSWORD_HISTORY_GID) < 0) {
		perror("Chown DBM pag");
	}
#endif
E 5

E 6
	/*
	 * Read history lines from stdin and pack into the database
	 */
	while (fgets(inbuf, sizeof(inbuf), input)) {
		datum	hkey,		/* DBM key */
			hdata;		/* DBM data */
D 6
		char	name[16];
		char	*c,
			*n,
			*t;
E 6
I 6
D 11
		char	name[16];	/* Temp */
		char	*c,		/* Temp */
			*n,		/* Temp */
			*t;		/* Temp */
E 11
I 11
		char	*dptr,		/* History data start */
			*nptr,		/* New history data */
			*iptr;		/* Start of input line */
E 11
E 6

		chop_nl(inbuf);

D 11
		if ((t = filter_input(inbuf)) == 0)
E 11
I 11
		if ((iptr = filter_input(inbuf)) == 0)		/* Null input */
E 11
			continue;
I 11
		if ((dptr = strchr(iptr, ENTRY_SEP)) == 0)	/* Bad input */
			continue;
		*dptr++ = 0;
E 11

D 11
		if ((c = strchr(t, ENTRY_SEP)) == 0)
E 11
I 11
		nptr = clean_history(dptr, 0, 0, 0, 0);
		if (nullstr(nptr))
E 11
			continue;
D 11
		*c++ = 0;
D 7
		n = clean_history(c, 0, 0, 0, 0);
E 7
I 7
		if ((n = clean_history(c, 0, 0, 0, 0)) == NULL)
			continue;
E 11
E 7

D 11
		hkey.dptr = t;
		hkey.dsize = strlen(t);

E 11
I 11
		str2dbm(hkey, iptr);
		str2dbm(hdata, nptr);
E 11
I 9
		/*
D 11
		 * Merge mode - fetch from db and append input
		 */
		if (merge) {
			datum tmp = dbm_fetch(hdb, hkey);

			if (tmp.dptr) {
				char *nd = malloc(tmp.dsize + strlen(n) + 2);

				(void) strncpy(nd, tmp.dptr, tmp.dsize);
				nd[tmp.dsize] = 0;
				(void) strcat(nd, ENTRY_SEP_STR);
				(void) strcat(nd, n);
				if ((n = clean_history(nd, 0, 0, 0, 0)) == NULL) {
					free(nd);
					continue;
				}
			}
		}
E 9
		hdata.dptr = n;
		hdata.dsize = strlen(n);
D 9

E 9
		/*
E 11
		 * Store new data
I 8
D 9
	 	 * Perhaps on 'append', the old entry should be fetched
		 * and the new data merged.
E 9
E 8
		 */
D 11
		if (dbm_store(hdb, hkey, hdata, DBM_REPLACE) < 0) {
D 7
				warn("DBM store failed\nHistory load errors - new database left as '%s'\n",
					temp_file);
				dbm_close(hdb);
				return(1);
			}
I 6
			how_many++;
E 7
I 7
			warn("DBM store failed\n");
E 11
I 11
		if (dbm_store(hdb, hkey, hdata, DBM_INSERT) < 0) {
D 12
			warn("DBM store failed for '%s'\n", iptr);
E 12
I 12
			warn("DBM insert failed for '%s'\n", iptr);
E 12
E 11
			errors++;
E 7
E 6
		}
D 7
		dbm_close(hdb);
E 7
I 7
		how_many++;
	}
	dbm_close(hdb);
I 11

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
E 11
	if (errors) {
D 11
		warn("DBM store errors - new database left as '%s'\n",
E 11
I 11
		warn("History load errors - new database left as '%s'\n",
E 11
			tempfile);
I 11
		return(errors);
	}
	if (install_file(file_dir, temp_dir, save_dir)) {
D 12
		warn("Replace '%s' failed\n", file_dir);
E 12
I 12
		warn("Replace DBM '%s' failed\n", file_dir);
E 12
E 11
		return(1);
	}
I 11
	if (install_file(file_pag, temp_pag, save_pag)) {
D 12
		warn("Replace '%s' failed\n", file_pag);
E 12
I 12
		warn("Replace DBM '%s' failed\n", file_pag);
E 12
		return(1);
	}
E 11
E 7

I 11
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
E 11
I 7
	/*
D 11
	 * Install temp file
E 11
I 11
	 * Read history lines from stdin and pack into the database
E 11
	 */
D 11
	if (new_file == 0) {
		char	save_dir[MAXPATHLEN],	/* Save .dir file */
			save_pag[MAXPATHLEN],	/* Save .pag file */
			save_file[MAXPATHLEN];	/* Save file */
E 11
I 11
	while (fgets(inbuf, sizeof(inbuf), input)) {
		datum	hkey,		/* Lookup key */
			hdata,		/* Store data */
			htemp;		/* Lookup data */
		char	*dptr,		/* Temp */
			*nptr,		/* Temp */
			*iptr;		/* Temp */
E 11

D 11
		(void) strcpy(save_file, file);
		(void) strcat(save_file, "-old");
		db_files(save_dir, save_pag, save_file);
E 11
I 11
		chop_nl(inbuf);
E 11

I 11
		if ((iptr = filter_input(inbuf)) == NULL)
			continue;

		if ((dptr = strchr(iptr, ENTRY_SEP)) == NULL)
			continue;
		*dptr++ = 0;

E 11
E 7
		/*
D 7
		 * Install temp file
E 7
I 7
D 11
		 * Save existing file
E 11
I 11
		 * If the user is in the db, fetch entry and append input
E 11
E 7
		 */
D 7
		if (new_file == 0) {
			char	save_dir[MAXPATHLEN],	/* Save .dir file */
				save_pag[MAXPATHLEN],	/* Save .pag file */
				save_file[MAXPATHLEN];	/* Save file */
E 7
I 7
D 11
		if (rename(file_dir, save_dir) < 0) {
			perror("Save .dir file failure");
			errors++;
		}
		if (rename(file_pag, save_pag) < 0) {
			perror("Save .pag file failure");
			errors++;
		}
E 11
I 11
		str2dbm(hkey, iptr);
		htemp = dbm_fetch(hdb, hkey);
		if (htemp.dptr) {
			char 	*nd = malloc(htemp.dsize + strlen(dptr) + 2);
			char	*td;
E 11
E 7
D 6
			int	errors = 0;		/* Error count */
E 6

I 11
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
E 11
D 6
			if (stb.st_uid != getuid()) {
				if (chown(temp_dir, stb.st_uid, stb.st_gid) < 0 ||
				    chown(temp_pag, stb.st_uid, stb.st_gid) < 0 ) {
					perror("History temp chown");
					errors++;
				}
			}
E 6
D 7
			(void) strcpy(save_file, file);
			(void) strcat(save_file, "-old");
			db_files(save_dir, save_pag, save_file);

			/*
			 * Save existing file
			 */
			if (rename(file_dir, save_dir) < 0) {
				perror("Save .dir file failure");
				errors++;
			}
			if (rename(file_pag, save_pag) < 0) {
				perror("Save .pag file failure");
				errors++;
			}

			/*
			 * Install temp file
			 */
			if (rename(temp_dir, file_dir) < 0) {
				perror("History .dir rename failure");
				errors++;
				if (rename(save_dir, file_dir) < 0)
					perror("Putback .dir failure");
			}
			if (rename(temp_pag, file_pag) < 0) {
				perror("History .pag rename failure");
				errors++;
				if (rename(save_pag, file_pag) < 0)
					perror("Putback .pag failure");
			}
			if (errors) {
				warn("History load errors - new database left as '%s'\n", temp_file);
E 7
I 7
		/*
D 11
		 * Install temp file
E 11
I 11
		 * Store new data
E 11
		 */
D 11
		if (rename(temp_dir, file_dir) < 0) {
			perror("History .dir rename failure");
E 11
I 11
		str2dbm(hdata, nptr);
		if (dbm_store(hdb, hkey, hdata, DBM_REPLACE) < 0) {
D 12
			warn("DBM merge store failed for '%s'\n", iptr);
E 12
I 12
			warn("DBM replace for '%s' failed\n", iptr);
E 12
E 11
			errors++;
D 11
			if (rename(save_dir, file_dir) < 0)
				perror("Putback .dir failure");
E 11
		}
D 11
		if (rename(temp_pag, file_pag) < 0) {
			perror("History .pag rename failure");
			errors++;
			if (rename(save_pag, file_pag) < 0)
				perror("Putback .pag failure");
		}
		if (errors) {
			warn("History load errors - new database left as '%s'\n", tempfile);
E 7
			return(1);
		}
E 11
I 11
		how_many++;
E 11
	}
I 6
D 11
	/*
	 * Success - confirm and finish
 	 */
E 11
I 11
	dbm_close(hdb);

	if (errors)
		warn("%s history merge errors\n", errors);
E 11
	if (logging)
D 7
		syslog(LOG_INFO, "Password history load to DBM '%s': %d records",
			file, how_many);
E 7
I 7
D 10
		syslog(LOG_INFO, "%s %d records to DBM history DBM '%s'",
D 9
			append ? "Add" : "Load", how_many, file);
E 9
I 9
			merge ? "Add" : "Load", how_many, file);
E 10
I 10
D 11
		syslog(LOG_INFO, "%d records %s to DBM history DBM '%s'",
			how_many, merge ? "merged" : "loaded", file);
E 10
E 9
E 7
	if (verbose)
D 7
		printf("Loaded %d records to password history DBM '%s'\n",
			how_many, file);
E 7
I 7
D 10
		printf("%s %d records to password history DBM '%s'\n",
D 9
			append ? "Added" : "Loaded", how_many, file);
E 9
I 9
			merge ? "Added" : "Loaded", how_many, file);
E 10
I 10
		printf("%d records %s to password history DBM '%s'\n",
			how_many, merge ? "merged" : "loaded", file);
E 10
E 9
E 7
E 6
	return(0);
#undef	db_files
E 11
I 11
		syslog(LOG_INFO, "Merged %d records to history DBM '%s', %d errors",
			how_many, file, errors);
	vprintf("Merged %d records to history DBM '%s'\n", how_many, file);
	return(errors);
E 11
}
I 11

E 11
#endif	/* I_NDBM */

I 11

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

E 11
/* End %M% */
E 1
