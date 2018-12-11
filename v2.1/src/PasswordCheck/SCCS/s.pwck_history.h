h06273
s 00001/00000/00103
d D 1.4 98/09/29 15:03:16 clyde 5 3
c Add HISTORYDB_DEFAULT define (for history configure)
e
s 00001/00001/00102
d R 1.4 98/07/16 09:44:50 clyde 4 3
c Change history db mode to 640
e
s 00002/00001/00101
d D 1.3 98/06/16 11:15:30 clyde 3 2
c Add ENTRY_SEP_STR define
e
s 00011/00012/00091
d D 1.2 98/06/08 14:09:15 clyde 2 1
c Change var names and clean_history proto
e
s 00103/00000/00000
d D 1.1 98/06/04 08:49:06 clyde 1 0
c date and time created 98/06/04 08:49:06 by clyde
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

/* %W% %G% (cc.utexas.edu) */

/*
 * Private include for npasswd password history routines
 */

public char *pwh_get_file _((char *));
D 2
public int   pwh_put_file _((char *, char *));
E 2
I 2
public int   pwh_put_file _((char *, char *, time_t));
E 2

#ifdef	USE_NIS_UNSUPPORTED
public char *pwh_get_nis _((char *));
D 2
public int   pwh_put_nis _((char *, char *));
E 2
I 2
public int   pwh_put_nis _((char *, char *, time_t));
E 2
#endif

#ifdef	USE_NISPLUS_UNSUPPORTED
public char *pwh_get_nisplus _((char *));
D 2
public int  *pwh_put_nisplus _((char *, char *));
E 2
I 2
public int  *pwh_put_nisplus _((char *, char *, time_t));
E 2
#endif

#ifdef	I_NDBM
/*
 * If NDBM is available, make it the default history database method
 */
public char *pwh_get_dbm _((char *));
D 2
public int   pwh_put_dbm _((char *, char *));
E 2
I 2
public int   pwh_put_dbm _((char *, char *, time_t));
E 2

#define	DEFAULT_PUT	pwh_put_dbm
#define	DEFAULT_GET	pwh_get_dbm
#define	DEFAULT_METHOD	"dbm"

#else
/*
 * Default history database method is flat file
 */
#define	DEFAULT_PUT	pwh_put_file
#define	DEFAULT_GET	pwh_get_file
#define	DEFAULT_METHOD	"file"

#endif

D 3
#define	ENTRY_SEP		':'	/* History entry seperator */
E 3
I 3
#define	ENTRY_SEP		':'	/* Entry seperator character */
#define	ENTRY_SEP_STR		":"	/* Entry seperator string */
E 3
#define	FIELD_SEP		','	/* History field seperator */
D 2

E 2
#define	MIN_HISTORY_DEPTH	1	/* The smallest depth allowed */
#define	MIN_HISTORY_TIMEOUT	30	/* The shortest timeout allowed */
I 2
#define HISTORYDB_MODE		0600	/* History database file mode */
#define	HISTORY_RECLEN		1024	/* How long a history entry can be */
I 5
#define	HISTORYDB_DEFAULT	"@"	/* Magic DB path token = use default */
E 5
E 2

D 2
#define HISTORYDB_MODE		0600
E 2
I 2
extern char	*HistoryDB,
		*HistoryMethod;
extern time_t	HistoryAge;
extern int	HistoryDepth;
E 2

D 2
extern char    *PasswordHistoryDB;
extern time_t  PasswordHistoryAge;
extern int     PasswordHistoryDepth;
extern char    *PasswordHistoryMethod;

E 2
/*
 * Function prototypes
 */
D 2
public char *clean_history _((char *));
E 2
I 2
public char *clean_history _((char *, int, time_t, time_t, size_t));
E 2

/* End %M% */
E 1
