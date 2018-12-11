h16932
s 00001/00000/00321
d D 1.32 98/10/13 18:12:22 clyde 32 31
c Make passwd.MaxRepeat work
e
s 00001/00001/00320
d D 1.31 98/09/16 14:43:07 clyde 31 30
c Change PrintOnly to PrintableOnly
e
s 00001/00000/00320
d D 1.30 98/08/17 13:22:08 clyde 30 29
c Add passwd.WhiteSpace config directive
e
s 00001/00000/00319
d D 1.29 98/07/17 11:19:54 clyde 29 28
c Call checkpassword_probe() when dumping config data
e
s 00002/00002/00317
d D 1.28 98/07/09 14:18:48 clyde 28 27
c Use get_debug() instead of DebugLevel var
e
s 00003/00001/00316
d D 1.27 98/07/09 08:54:09 clyde 27 26
c Change usage of checkpassword_verify()
e
s 00011/00011/00306
d D 1.26 98/07/01 15:07:29 clyde 26 25
c Fix boo-boo in config table
e
s 00038/00022/00279
d D 1.25 98/07/01 15:04:41 clyde 25 24
c Impliment -Xc (config dump) switch
e
s 00001/00000/00300
d D 1.24 98/07/01 14:23:56 clyde 24 23
c Include checkpassword.h 
e
s 00001/00000/00299
d D 1.23 98/06/30 15:44:29 clyde 23 22
c Call checkpassword_verify() after config file processing
e
s 00001/00001/00298
d D 1.22 98/06/30 15:10:23 clyde 22 21
c Fix config file symlink check
e
s 00003/00003/00296
d D 1.21 98/06/26 13:33:13 clyde 21 20
c Fix call of checkpassword_configure() 
e
s 00066/00022/00233
d D 1.20 98/06/23 11:05:35 clyde 20 19
c 1. Add copyright notice
c 2. Change names of some config variables
c 3. Change compile-time debug include trigger
e
s 00036/00030/00219
d D 1.19 98/04/21 10:59:36 clyde 19 18
c 1. Update directive table
c 2. Be more fascist about checking the configuration file mode & ownership
e
s 00004/00000/00245
d D 1.18 98/03/26 11:18:11 clyde 18 17
c 1. Add passwd.MatchWait and passwd.MinCharClasses
e
s 00002/00001/00243
d D 1.17 97/10/29 14:39:58 clyde 17 16
c Add "alpha only" config switch for passwd
e
s 00002/00001/00242
d D 1.16 97/05/23 13:18:43 clyde 16 15
c Add config parameters for password history (oops)
e
s 00041/00023/00202
d D 1.15 96/08/15 11:33:30 clyde 15 14
c 1. Add comments 
c 2. Allow end-of-line comments 
c 3. Don't remove leading stuff from checkpasswd passthroughs
e
s 00002/00002/00223
d D 1.14 96/08/14 19:01:03 clyde 14 13
c Fix punctutation for die() messages
e
s 00017/00011/00208
d D 1.13 96/08/13 17:56:09 clyde 13 12
c Change name of configuration variables
e
s 00016/00018/00203
d D 1.12 96/08/09 16:16:12 clyde 12 11
c Beta 3 development checkin 2
e
s 00040/00175/00181
d D 1.11 96/08/06 14:14:21 clyde 11 10
c beta 3 cycle 1 checkin
e
s 00001/00001/00355
d D 1.10 96/03/29 11:22:38 clyde 10 9
c Change XBUFLEN to TMPBUFSIZ
e
s 00002/00003/00354
d D 1.9 96/03/27 17:20:59 clyde 9 8
c 1. Call checkpassword_init() before processing config file
c 2. Use debug() routine 
e
s 00001/00000/00356
d D 1.8 96/03/27 09:31:22 clyde 8 7
c Add 'dictionaries' directive
e
s 00003/00072/00353
d D 1.7 95/04/05 16:19:51 clyde 7 6
c Beta 3 development checkin
e
s 00005/00010/00420
d D 1.6 94/07/28 15:59:18 clyde 6 5
c Add chfn and chsh sstuff
e
s 00016/00021/00414
d D 1.5 94/06/20 13:48:32 clyde 5 4
c Cleanup debugging statements
e
s 00002/00001/00433
d D 1.4 94/03/31 17:38:36 clyde 4 3
c Fix error message
e
s 00001/00000/00433
d D 1.3 94/03/15 18:50:06 clyde 3 2
c Add passwd.history directive
e
s 00008/00003/00425
d D 1.2 94/03/15 11:07:45 clyde 2 1
c Fix configuration file checks
e
s 00428/00000/00000
d D 1.1 94/03/01 17:35:13 clyde 1 0
c date and time created 94/03/01 17:35:13 by clyde
e
u
U
t
T
I 1
/*
I 20
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
E 20
D 15
 * configure - Process the npasswd configuration file
E 15
I 15
 * configure
 *	Process the npasswd configuration file.
 *	Many of directives are passed to the pasword check library
 *	configuration routine.
 *
 * Exported routines
 *	configure()
 * Imported variables
 *	See below
E 15
 */

#ifndef lint
D 15
static char sccsid[] = "%W% %G% (cc.utexas.edu)";
E 15
I 15
static char sccsid[] = "%W% %G% (cc.utexas.edu) %P%";
E 15
#endif

#include "npasswd.h"
I 24
#include "checkpassword.h"
E 24

D 15
extern int	PasswdMatchTries;
D 11
extern char	PasswdHelpFile[];
extern char	PasswdMotdFile[];
E 11
I 11
extern char	*PasswdHelpFile;
extern char	*PasswdMotdFile;
E 15
I 15
D 20
extern int	PasswdMatchTries;	/* From passwd.c */
I 18
extern int	PasswdMatchWait;	/* From passwd.c */
E 18
extern char	*PasswdHelpFile;	/* From passwd.c */
extern char	*PasswdMotdFile;	/* From passwd.c */
E 20
I 20
extern char	*Passwd_Help;		/* From passwd.c */
extern char	*Passwd_Motd;		/* From passwd.c */
E 20
E 15
E 11

D 6
#if	0
/* Hooks for stuff that isn't attached yet */
E 6
D 11
extern char	chsh_shells[];
extern char	chsh_help[];
extern char	chsh_motd[];
extern char	chfn_help[];
extern char	chfn_motd[];
E 11
I 11
D 13
extern char	*chsh_shells;
extern char	*chsh_help;
extern char	*chsh_motd;
E 13
I 13
D 15
extern char	*ChshShellList;
extern char	*ChshHelpFile;
extern char	*ChshMotdFile;
E 15
I 15
D 20
extern char	*ChshShellList;		/* From chsh.c */
extern char	*ChshHelpFile;		/* From chsh.c */
extern char	*ChshMotdFile;		/* From chsh.c */
E 20
I 20
extern char	*Chsh_Help;		/* From chsh.c */
extern char	*Chsh_Motd;		/* From chsh.c */
extern char	*Chsh_Shells;		/* From chsh.c */
E 20
E 15
E 13
E 11
D 6
#endif
E 6

D 11
#define	PASSTHRU	'p'
E 11
I 11
D 13
extern char	*chfn_help;
extern char	*chfn_motd;
E 13
I 13
D 15
extern char	*ChfnHelpFile;
extern char	*ChfnMotdFile;
E 15
I 15
D 20
extern char	*ChfnHelpFile;		/* From chfn.c */
extern char	*ChfnMotdFile;		/* From chfn.c */
E 20
I 20
extern char	*Chfn_Help;		/* From chfn.c */
extern char	*Chfn_Motd;		/* From chfn.c */
E 20
E 15
E 13

I 20
extern int	PasswdMatchTries;	/* From getpass.c */
extern int	PasswdMatchWait;	/* From getpass.c */
E 20
I 13
D 15
extern int	PasswdTolerance;
extern int	ShadowTolerance;
E 15
I 15
extern int	PasswdTolerance;	/* From pwm_local.c */
extern int	ShadowTolerance;	/* From active shadow module */
E 15

I 18
D 25

E 25
E 18
E 13
D 15
#define	PWCHECK_PASSTHRU	'p'
E 15
I 15
#define	PWCHECK_PASSTHRU	'p'	/* Pass to checkpasswd_configure() */
E 15
E 11
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
D 15
 * The master configuration table.  This is pretty much a brute-force way
D 11
 * of doing configuration, but since the number of directives is small,
 * getting complicated won't by me anything.
E 11
I 11
 * of doing configuration, but the number of directives is small, so
 * simple is good.
E 15
I 15
 * The master configuration table.
 * I'm using a brute-force method for this, but since there are
 * few directives, so brutal-but-simple wins.
E 15
E 11
 */
private struct cftab cftab[] = {
I 13
	/* Global configuration */
D 15
	{ "PasswdTolerance",		0,	INT,	&PasswdTolerance },
	{ "ShadowTolerance",		0,	INT,	&ShadowTolerance },
E 15
I 15
D 19
	{ "PasswdTolerance",	0,	INT,	&PasswdTolerance },
	{ "ShadowTolerance",	0,	INT,	&ShadowTolerance },
E 19
I 19
	{ "PasswdTolerance",	0,	INT,	(void *)&PasswdTolerance },
	{ "ShadowTolerance",	0,	INT,	(void *)&ShadowTolerance },
I 20
	{ "MatchTries",		0,	INT,	(void *)&PasswdMatchTries },
	{ "MatchWait",		0,	INT,	(void *)&PasswdMatchWait },
E 20
E 19
E 15
E 13

	/* Configuration for checkpassword() */
I 15
D 25
	{ "passwd.Dictionaries",	PWCHECK_PASSTHRU,	NONE },
E 15
D 11
	{ "passwd.mandatory",	PASSTHRU,	NONE },
	{ "passwd.optional",	PASSTHRU,	NONE },
	{ "passwd.singlecase",	PASSTHRU,	NONE },
	{ "passwd.minlength",	PASSTHRU,	NONE },
	{ "passwd.maxlength",	PASSTHRU,	NONE },
	{ "passwd.printonly",	PASSTHRU,	NONE },
	{ "passwd.badchars",	PASSTHRU,	NONE },
	{ "passwd.checkorder",  PASSTHRU,	NONE },
I 3
	{ "passwd.history",	PASSTHRU,	NONE },
I 8
	{ "passwd.dictionaries", PASSTHRU,	NONE },
E 11
I 11
D 12
	{ "passwd.mandatory",	PWCHECK_PASSTHRU,	NONE },
	{ "passwd.optional",	PWCHECK_PASSTHRU,	NONE },
	{ "passwd.singlecase",	PWCHECK_PASSTHRU,	NONE },
	{ "passwd.minlength",	PWCHECK_PASSTHRU,	NONE },
	{ "passwd.maxlength",	PWCHECK_PASSTHRU,	NONE },
	{ "passwd.printonly",	PWCHECK_PASSTHRU,	NONE },
	{ "passwd.badchars",	PWCHECK_PASSTHRU,	NONE },
	{ "passwd.checkorder",  PWCHECK_PASSTHRU,	NONE },
	{ "passwd.history",	PWCHECK_PASSTHRU,	NONE },
	{ "passwd.dictionaries", PWCHECK_PASSTHRU,	NONE },
E 12
I 12
D 19
	{ "passwd.MonocaseOK",		PWCHECK_PASSTHRU,	NONE },
E 19
I 19
	{ "passwd.SingleCase",		PWCHECK_PASSTHRU,	NONE },
E 19
I 17
	{ "passwd.AlphaOnly",		PWCHECK_PASSTHRU,	NONE },
E 17
	{ "passwd.MinPassword",		PWCHECK_PASSTHRU,	NONE },
	{ "passwd.MaxPassword",		PWCHECK_PASSTHRU,	NONE },
D 19
	{ "passwd.PrintableOnly",	PWCHECK_PASSTHRU,	NONE },
E 19
I 19
	{ "passwd.LengthWarn",		PWCHECK_PASSTHRU,	NONE },
	{ "passwd.PrintOnly",		PWCHECK_PASSTHRU,	NONE },
E 19
	{ "passwd.DisallowedChars",	PWCHECK_PASSTHRU,	NONE },
I 19
	{ "passwd.CharClasses",		PWCHECK_PASSTHRU,	NONE },
E 19
	{ "passwd.PasswordChecks",	PWCHECK_PASSTHRU,	NONE },
I 18
D 19
	{ "passwd.MinCharClasses",	PWCHECK_PASSTHRU,	NONE },
E 18
	{ "passwd.HistoryDatabase",	PWCHECK_PASSTHRU,	NONE },
D 16
	{ "passwd.HistoryParams",	PWCHECK_PASSTHRU,	NONE },
E 16
I 16
	{ "passwd.HistoryAge",		PWCHECK_PASSTHRU,	NONE },
	{ "passwd.HistoryDepth",	PWCHECK_PASSTHRU,	NONE },
E 19
I 19
	{ "passwd.History",		PWCHECK_PASSTHRU,	NONE },
E 25
I 25
D 26
	{ "passwd.Dictionaries",	PWCHECK_PASSTHRU,	STRING },
	{ "passwd.SingleCase",		PWCHECK_PASSTHRU,	BOOLEAN },
	{ "passwd.AlphaOnly",		PWCHECK_PASSTHRU,	BOOLEAN },
	{ "passwd.MinPassword",		PWCHECK_PASSTHRU,	INT },
	{ "passwd.MaxPassword",		PWCHECK_PASSTHRU,	INT },
	{ "passwd.LengthWarn",		PWCHECK_PASSTHRU,	BOOLEAN },
	{ "passwd.PrintOnly",		PWCHECK_PASSTHRU,	BOOLEAN },
	{ "passwd.DisallowedChars",	PWCHECK_PASSTHRU,	STRING },
	{ "passwd.CharClasses",		PWCHECK_PASSTHRU,	INT },
	{ "passwd.PasswordChecks",	PWCHECK_PASSTHRU,	STRING },
	{ "passwd.History",		PWCHECK_PASSTHRU,	STRING },
E 26
I 26
	{ "passwd.Dictionaries",	PWCHECK_PASSTHRU,	NONE },
	{ "passwd.SingleCase",		PWCHECK_PASSTHRU,	NONE },
	{ "passwd.AlphaOnly",		PWCHECK_PASSTHRU,	NONE },
	{ "passwd.MinPassword",		PWCHECK_PASSTHRU,	NONE },
	{ "passwd.MaxPassword",		PWCHECK_PASSTHRU,	NONE },
I 32
	{ "passwd.MaxRepeat",		PWCHECK_PASSTHRU,	NONE },
E 32
	{ "passwd.LengthWarn",		PWCHECK_PASSTHRU,	NONE },
D 31
	{ "passwd.PrintOnly",		PWCHECK_PASSTHRU,	NONE },
E 31
I 31
	{ "passwd.PrintableOnly",	PWCHECK_PASSTHRU,	NONE },
E 31
I 30
	{ "passwd.WhiteSpace",		PWCHECK_PASSTHRU,	NONE },
E 30
	{ "passwd.DisallowedChars",	PWCHECK_PASSTHRU,	NONE },
	{ "passwd.CharClasses",		PWCHECK_PASSTHRU,	NONE },
	{ "passwd.PasswordChecks",	PWCHECK_PASSTHRU,	NONE },
	{ "passwd.History",		PWCHECK_PASSTHRU,	NONE },
E 26
E 25
E 19
E 16
E 12
E 11
E 8
E 3

	/* Configuration for 'passwd' module */
D 12
	{ "passwd.match",	0, INT,		(void *)&PasswdMatchTries },
D 11
	{ "passwd.help",  	0, PATH,	(void *)PasswdHelpFile },
	{ "passwd.motd",  	0, PATH,	(void *)PasswdMotdFile },
E 11
I 11
	{ "passwd.help",  	0, PATH,	(void *)&PasswdHelpFile },
	{ "passwd.motd",  	0, PATH,	(void *)&PasswdMotdFile },
E 12
I 12
D 20
	{ "passwd.MatchTries",	0, INT,		(void *)&PasswdMatchTries },
I 18
	{ "passwd.MatchWait",	0, INT,		(void *)&PasswdMatchWait },
E 18
D 19
	{ "passwd.HelpFile",  	0, PATH,	(void *)&PasswdHelpFile },
E 19
I 19
	{ "passwd.Help",  	0, PATH,	(void *)&PasswdHelpFile },
E 19
	{ "passwd.Message",  	0, PATH,	(void *)&PasswdMotdFile },
E 20
I 20
	{ "passwd.Help",  	0, PATH,	(void *)&Passwd_Help },
	{ "passwd.Message",  	0, PATH,	(void *)&Passwd_Motd },
E 20
E 12
E 11

D 6
#if	0
E 6
	/* Configurationf for 'chsh' module */
D 11
	{ "chsh.shells",	0, PATH,	(void *)chsh_shells },
D 6
	{ "chsh.help",  	0, PATH,	(void *)chsh_helpfile },
	{ "chsh.motd",  	0, PATH,	(void *)chsh_motdfile },
E 6
I 6
	{ "chsh.help",  	0, PATH,	(void *)chsh_help },
	{ "chsh.motd",  	0, PATH,	(void *)chsh_motd },
E 11
I 11
D 12
	{ "chsh.shells",	0, PATH,	(void *)&chsh_shells },
	{ "chsh.help",  	0, PATH,	(void *)&chsh_help },
	{ "chsh.motd",  	0, PATH,	(void *)&chsh_motd },
E 12
I 12
D 13
	{ "chsh.ShellList",	0, PATH,	(void *)&chsh_shells },
	{ "chsh.HelpFile",  	0, PATH,	(void *)&chsh_help },
	{ "chsh.Message",  	0, PATH,	(void *)&chsh_motd },
E 13
I 13
D 19
	{ "chsh.ShellList",	0, PATH,	(void *)&ChshShellList },
	{ "chsh.HelpFile",  	0, PATH,	(void *)&ChshHelpFile },
E 19
I 19
D 20
	{ "chsh.Shells",	0, PATH,	(void *)&ChshShellList },
	{ "chsh.Help",  	0, PATH,	(void *)&ChshHelpFile },
E 19
	{ "chsh.Message",  	0, PATH,	(void *)&ChshMotdFile },
E 20
I 20
	{ "chsh.Help",  	0, PATH,	(void *)&Chsh_Help },
	{ "chsh.Message",  	0, PATH,	(void *)&Chsh_Motd },
	{ "chsh.Shells",	0, PATH,	(void *)&Chsh_Shells },
E 20
E 13
E 12
E 11
E 6

D 6
	/* Configuration for 'chfn' module */
	{ "chfn.help",  	0, PATH,	(void *)chfn_helpfile },
	{ "chfn.help",  	0, PATH,	(void *)chfn_helpfile },
#endif
E 6
I 6
	/* Configurationf for 'chfn' module */
D 11
	{ "chfn.help",  	0, PATH,	(void *)chfn_help },
	{ "chfn.motd",  	0, PATH,	(void *)chfn_motd },
E 11
I 11
D 12
	{ "chfn.help",  	0, PATH,	(void *)&chfn_help },
	{ "chfn.motd",  	0, PATH,	(void *)&chfn_motd },
E 12
I 12
D 13
	{ "chfn.HelpFile",  	0, PATH,	(void *)&chfn_help },
	{ "chfn.Message",  	0, PATH,	(void *)&chfn_motd },
E 13
I 13
D 19
	{ "chfn.HelpFile",  	0, PATH,	(void *)&ChfnHelpFile },
E 19
I 19
D 20
	{ "chfn.Help",  	0, PATH,	(void *)&ChfnHelpFile },
E 19
	{ "chfn.Message",  	0, PATH,	(void *)&ChfnMotdFile },
E 20
I 20
	{ "chfn.Help",  	0, PATH,	(void *)&Chfn_Help },
	{ "chfn.Message",  	0, PATH,	(void *)&Chfn_Motd },
E 20
E 13
E 12
E 11
E 6
	{ 0 },
};

I 15
/*
 * dump_config
 *	Print confiuration table
 */
E 15
private void
D 25
dump_config()
E 25
I 25
dump_config(vflag)
	int vflag;		/* Verbose flag */
E 25
{
	struct cftab	*f;

	for (f = cftab; f->keyword; f++) {
D 25
		printf("%-20s code=%-5d type=%-5d ",
			f->keyword, f->code, f->datatype);
E 25
		switch(f->datatype) {
		case NONE:
I 25
			if (vflag == 0)
				break;
			printf("%-20s code=%-5d type=%-5d ",
				f->keyword, f->code, f->datatype);
E 25
D 11
			if (f->code == PASSTHRU)
E 11
I 11
			if (f->code == PWCHECK_PASSTHRU)
E 11
				printf("passthru ");
			if (f->where)
				printf("loc=%0x", f->where);
I 25
			printf("\n");
E 25
			break;
		case INT:
D 25
			printf("loc=%0x data=%0x",
				f->where, *((int *)f->where));
E 25
I 25
			if (vflag)
				printf("%-20s code=%-5d type=%d loc=%0x data=%0x\n",
					f->keyword, f->code, f->datatype,
					f->where, *((int *)f->where));
			else
				printf("%-20s %d\n", f->keyword,
					*((int *)f->where));
E 25
			break;

		case PATH:
D 25
			printf("loc=%0x data=<%s>",
D 13
				f->where, f->where);
E 13
I 13
				f->where, *((char **)f->where));
E 25
I 25
			if (vflag)
				printf("%-20s code=%-5d type=%d loc=%0x data=%0x\n",
					f->keyword, f->code, f->datatype,
					f->where, *((char **)f->where));
			else
				printf("%-20s %s\n", f->keyword,
					*((char **)f->where));
E 25
E 13
			break;
		}
D 25
		printf("\n");
E 25
	}
}

/*
D 11
 * split - Tokenize line
 */
public int
split(cbuf, vbuf)
D 5
char	*cbuf;
char	**vbuf;
E 5
I 5
	char	*cbuf;
	char	**vbuf;
E 5
{
	register char	*ts,	/* Start of token */
			*te;	/* End of token */
	int	nitems = 0;

	if (cbuf == 0)
		return(0);
	ts = te = cbuf;
	while (*ts) {
		while (*te && *te <= ' ')	/* Find start of next token */
			te++;
		if (!*te)
			break;
		ts = te;
		while (*te && *te > ' ') *te++; /* Find end of this token */
		if (*te)
			*te++ = '\0';
		*vbuf++ = ts;
		nitems++;
	}
	*vbuf = 0;
	return(nitems);
}

/*
 *	Is argument an octal digit?
 */
private int
octdigit(c)
D 5
char	c;
E 5
I 5
	char	c;
E 5
{
	return (c >= '0' && c <= '7');
}

/*
 *	Is argument a decimal digit?
 */
private int
decdigit(c)
D 5
char	c;
E 5
I 5
	char	c;
E 5
{
	return (c >= '0' && c <= '9');
}

/*
 *	Is argument a hexidecimal digit?
 */
private int
hexdigit(c)
D 5
char	c;
E 5
I 5
	char	c;
E 5
{
	return (decdigit(c) |
		(c >= 'a' &&  c <= 'f') |
		(c >= 'A' && c <= 'F'));
}

/*
 *	decode_boolean - decode a boolean value
 */
private int
decode_boolean(s)
D 5
char	*s;
E 5
I 5
	char	*s;
E 5
{
	return(*s == '1'
		| strcmp(s, "true") == 0
		| strcmp(s, "yes") == 0
		| strcmp(s, "on") == 0);
}

/*
 *	xatoi - Smart 'atoi' recognizes decimal, octal and hex constants
 */
private int
xatoi(ip, ipp, iv)
D 5
char	*ip,		/* Pointer to number string */
	**ipp;		/* Stash pointer to end of string */ /* RETURN VALUE */
int	*iv;		/* RETURN VALUE */
E 5
I 5
	char	*ip,	/* Pointer to number string */
		**ipp;	/* Stash pointer to end of string */ /* RETURN VALUE */
	int	*iv;	/* RETURN VALUE */
E 5
{
	int	(*func)() = decdigit,	/* Function to check char */
		base = 10;		/* Conversion base */
	int	t = 0,			/* Return value */
		mult = 1;		/* Sign of result */
	char	*fcc = ip;		/* First char position */

	if (*ip == '-') {		/* Negative number? */
		ip++;
		mult = -1;
	}
	if (*ip == '0') { 	/* Leading '0'? */
		ip++;
		if (*ip == 'x' || *ip == 'X') {	/* Hex */
			base = 16;
			func = hexdigit;
			ip++;			/* Skip 'x' */
		}
		else {
			base = 8;		/* Octal */
			func = octdigit;
		}
	}
	while (*ip && (*func)(*ip)) {
		t *= base;
		if (decdigit(*ip))
			t += (*ip - '0');
		else
			t += (*ip >= 'a' ? *ip - 0x57 : *ip - 0x37);
		ip++;
	}
	if (ip == fcc)		/* Nothing processed */
		return(0);
	if (ipp)		/* Stash new pointer location */
		*ipp = ip;
	*iv = (t * mult);
	return(1);
}

/*
 *	decode_int - decode an integer value
 */
private int
decode_int(s)
D 5
char	*s;		/* String to decode */
E 5
I 5
	char	*s;		/* String to decode */
E 5
{
	int	t;	/* Temp */

	if (xatoi(s, (char *)0, &t))
		return(t);
	fprintf(stderr, "Bad numeric value '%s'\n", s);
	return(-1);
}

D 7
#if	0
E 7
/*
E 11
D 7
 *	decode_string - Copy string, converting backslash escapes
 *	Can handle most of the C backslash escape sequences
 */
private void
decode_string(dst, src, len)
D 5
char	*dst,		/* Destination */
	*src;		/* Source */
int	len;
E 5
I 5
	char	*dst,		/* Destination */
		*src;		/* Source */
	int	len;
E 5
{
	int	t;		/* Temp */
	char	*dstx = dst;	/* Pointer to start of destination */
	char	quote = 0;	/* Quote character */

	if (*src == '"' || *src == '\'')
		quote = *src++;

#define	putxchar(P) *dst++ = (P)
	for (; *src && (dst - dstx) < len; ) {
		if (*src == '\\') {
			src++;
			switch(*src) {
			case 'a':	putxchar('\007'); src++; break;
			case 'b':	putxchar('\b'); src++; break;
			case 'f':	putxchar('\f'); src++; break;
			case 'n':	putxchar('\n'); src++; break;
			case 'r':	putxchar('\r'); src++; break;
			case 't':	putxchar('\t'); src++; break;
			case '\\':	putxchar('\\'); src++; break;
			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7':
			case 'x':
				if (xatoi(src, &src, &t))
					putxchar(t & 0xff);
				break;
			default:
				if (quote && *src == quote)
					*dst++ = *src++;
				break;
			}
			continue;
		}
		if (*src == '^') {	/* ^C = control-c */
			src++;
			if (isupper(*src))
				putxchar(*src - '@');
			else if (islower(*src))
				putxchar(*src - '`');
			else switch (*src) {
			     case '[':	putxchar('\033'); break;
			     case '\\':	putxchar('\034'); break;
			     case ']':	putxchar('\035'); break;
			     case '^':	putxchar('\036'); break;
			     case '-':	putxchar('\037'); break;
			}
			src++;
			continue;
		}
		if (quote && *src == quote)
			break;
		*dst++ = *src++;
	}
#undef	putxchar
	*dst = 0;
}
#endif


/*
E 7
D 15
 *	config - read validation configuration file and stash away
E 15
I 15
 * config
 *	Read validation configuration file and stash away.
 *
 * Usage
D 19
 *	configure(char *config-file-name);
E 19
I 19
 *	configure(char *config-file-name, int secure-check);
E 19
 * Error exits
 *	Syntax error or unknown directive encountered
E 15
D 11
 *		** Memory allocated by parse() is NOT freed **
E 11
 */
public void
D 19
configure(cfn)
D 5
char	*cfn;			/* Config file name */
E 5
I 5
	char	*cfn;			/* Config file name */
E 19
I 19
configure(cfn, secure)
	char	*cfn;		/* Config file name */
	int	secure;		/* Do security checks */	
E 19
E 5
{
D 7
	char	cfline[1024];	/* Input buffer */
E 7
I 7
D 10
	char	cfline[XBUFLEN]; /* Input buffer */
E 10
I 10
	char	cfline[TMPBUFSIZ]; /* Input buffer */
E 10
E 7
	FILE	*cf;		/* Config file pointer */
I 27
	char	*t;		/* Temp */
E 27
	int	lineno = 0;	/* Config file line number */
I 19
	struct stat cfstat;
E 19

D 19
	if ((cf = fopen(cfn, "r")) == NULL) {
		perror(cfn);
I 2
#ifdef	DEBUG
D 14
		warn("Cannot open configuration file \"%s\"", cfn);
E 14
I 14
		warn("Cannot open configuration file \"%s\"\n", cfn);
E 14
		return;
#else
E 2
D 14
		die("Cannot open configuration file \"%s\"", cfn);
E 14
I 14
		die("Cannot open configuration file \"%s\"\n", cfn);
E 14
I 2
#endif
E 2
	}
E 19
I 19
	if (lstat(cfn, &cfstat) < 0)
		die("Cannot find configuration file \"%s\"\n", cfn);
E 19
D 20
#ifndef	DEBUG
E 20
I 20
#if	(CDEBUG < CDEBUG_SYSTEM)
E 20
I 11
	/*
D 19
	 * Sanity check - require configuration file to be owned
	 * by the effective uid this program is running with
E 19
I 19
	 * Security checks:
	 *   File cannot be world-writable
	 *   File cannot be a symlink (too many race condition scenarios)
	 *   File must be owned by the effective uid
E 19
	 */
E 11
D 2
	fstat(fileno(cf), &stat);
E 2
D 19
	if (getuid() != geteuid()) {
E 19
I 19
	if (secure == 0) {
E 19
D 2
		struct stat stat;
E 2
D 7
		uid_t	euid = geteuid();
E 7
I 7
		Uid_t	euid = geteuid();
E 7
I 2
D 19
		struct stat cfstat;
E 19
E 2

D 2
		if (stat.st_uid != euid)
E 2
I 2
D 19
		fstat(fileno(cf), &cfstat);
E 19
		if (cfstat.st_uid != euid)
E 2
D 19
			die("Configuration file \"%s\" is not owned by user %d\n",
E 19
I 19
			die("Configuration file \"%s\" not owned by uid %d\n",
E 19
				cfn, euid);
I 19
#ifdef	S_IWOTH
		if (cfstat.st_mode & S_IWOTH)
#else
		if (cfstat.st_mode & 02)
#endif
			die("Configuration file \"%s\" is writable\n", cfn);
D 22
		if (cfstat.st_mode & S_IFLNK) 
E 22
I 22
		if ((cfstat.st_mode & S_IFLNK) == S_IFLNK) 
E 22
			die("Configuration file \"%s\" is a symlink\n", cfn);
E 19
	}
#endif
I 19
	if ((cf = fopen(cfn, "r")) == NULL) {
		perror(cfn);
		die("Cannot open configuration file \"%s\"\n", cfn);
	}
E 19
D 5
#ifdef	DEBUG_CONFIG
	if (DebugLevel > DEBUG_CONFIG) {
E 5
I 5
D 28
	if (DebugLevel >= DB_CONFIG) {
E 28
I 28
	if (get_debug() >= DB_CONFIG) {
E 28
E 5
		printf("\nBefore reading config file \"%s\"\n", cfn);
D 25
		dump_config();
E 25
I 25
		dump_config(1);
E 25
	}
I 9
	checkpassword_init();
E 9
D 5
#endif

E 5
	while (fgets(cfline, sizeof(cfline), cf)) {
		struct cftab *cfi;	/* Table lookup temp */
		int	ok,		/* Temp */
			itemp;		/* Temp */
D 11
		char	cftemp[1024],	/* Copy of cfline */
			*cfv[64];	/* Tokenized cftemp */
E 11
I 11
		char	**cfv;		/* Tokenized cfline */
E 11

		lineno++;
		if (cfline[0] == '#' || cfline[0] == '\n' || cfline[0] == '\0')
			continue;
D 11
		(void) strcpy(cftemp, cfline);
		if (split(cftemp, cfv) == 0)
E 11
I 11
		chop_nl(cfline);
D 15
		if ((cfv = split(cfline, '\0', 0, '\0')) == 0)
E 15
I 15
		if ((cfv = split(cfline, 0, 0, '#')) == 0)
E 15
E 11
			continue;
D 9
#ifdef	DEBUG
		printf ("[%d] %s", lineno, cfline);
#endif
E 9
I 9
D 15
		debug(DB_CONFIG, "[%d] %s", lineno, cfline);
E 15
I 15
		debug(DB_CONFIG, "[%d] %s\n", lineno, cfline);
E 15
E 9
		ok = 0;
		for (cfi = cftab; cfi->keyword; cfi++) {
D 17
			if (strcmp(cfv[0], cfi->keyword) == 0) {
E 17
I 17
			if (strcasecmp(cfv[0], cfi->keyword) == 0) {
E 17
				ok++;
				break;
			}
		}
		if (ok == 0) {
D 20
#ifdef	DEBUG
			warn("File %s line %d: Unrecognized directive\n",
E 20
I 20
#if	(DEBUG <= CDEBUG_SYSTEM)
			warn("File '%s' line %d: Unrecognized directive\n",
E 20
				cfn, lineno);
			continue;
#else
D 20
			die("File %s line %d: Unrecognized directive\n", cfn, lineno);
E 20
I 20
			die("File '%s' line %d: Unrecognized directive\n", cfn, lineno);
E 20
#endif
		}
		switch (cfi->datatype) {
		case NONE:
D 11
			if (cfi->code == PASSTHRU) {
D 7
				char	*x = INDEX(cfline, '.');
E 7
I 7
				char	*x = index(cfline, '.');
E 11
I 11
			if (cfi->code == PWCHECK_PASSTHRU) {
D 15
				char	*x = strchr(cfline, '.');
E 15
E 11
E 7
D 21
				char	cferr[128];
E 21
I 21
				char	*rc;
E 21

D 15
				if (!checkpassword_configure(++x, cferr))
E 15
I 15
D 21
				if (!checkpassword_configure(cfline, cferr))
E 15
					die("Line %d: Error %s\n",lineno,cferr);
E 21
I 21
				if (rc = checkpassword_configure(cfline, 1))
					die("Line %d: Error %s\n", lineno, rc);
E 21
I 4
				break;
E 4
			}
D 4
			die("Line %d: Internal error (NONE)\n", cfline);
E 4
I 4
			die("Line %d: Internal error (NONE)\n", lineno);
E 4
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
D 11
			(void) strncpy((char *)cfi->where, cfv[1], MAXPATHLEN);
E 11
I 11
			*((char **)cfi->where)= strdup(cfv[1]);
E 11
			break;

		case STRING:
			if (cfv[1])
D 11
				(void) strcpy((char *)cfi->where, cfv[1]);
E 11
I 11
				*((char **)cfi->where) = strdup(cfv[1]);
E 11
			else
				die("Line %d: Missing argument\n", lineno);
			break;

		default:
			warn("Line %d: Internal error (UNKNOWN)\n", cfline);
			break;
		}
	}
	(void) fclose(cf);
D 5
#ifdef	DEBUG_CONFIG
	if (DebugLevel > DEBUG_CONFIG) {
E 5
I 5
D 28
	if (DebugLevel >= DB_CONFIG) {
E 28
I 28
	if (get_debug() >= DB_CONFIG) {
E 28
E 5
		printf("\nAfter reading config file\n");
D 25
		dump_config();
E 25
I 25
		dump_config(1);
E 25
	}
I 23
D 27
	checkpassword_verify();
E 27
I 27
	if (t = checkpassword_verify())
		logdie(t);
E 27
I 25
	if (XSwitches[Xsw_ShowConfig]) {
		dump_config(0);
I 29
		checkpassword_probe("passwd.");
E 29
		exit(0);
	}
E 25
E 23
D 5
#endif
E 5
}
/* End %M% */
E 1
