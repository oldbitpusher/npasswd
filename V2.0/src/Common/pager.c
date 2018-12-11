/*
 * Copyright 1998, The University of Texas at Austin ("U. T. Austin").
 * All rights reserved.
 *
 * Original code by Peter Vernam (vernam@draper.com).
 *
 * Modifications by Clyde Hoover
 *	Academic Computing & Instructional Technologies Services
 *	The University of Texas at Austin
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

#include "npasswd.h"

#ifndef lint
static char sccsid[] = "@(#)pager.c	1.2 01/17/00 (cc.utexas.edu) /usr/share/src/private/ut/share/packages/npasswd/V2.0/src/Common/SCCS/s.pager.c";
#endif

#define	PROMPT_LINES 	2		/* Reserve 2 lines for prompt */

/*
 * pager
 * 	Simple and secure file pager
 * Usage:
 *	pager(stdio-stream);
 */
public void
pager(stream)
	FILE	*stream;		/* Input stream */
{
	int	lines_to_put,		/* Page length */
		lines_put = 0;		/* Line counter */
	int	totalbytes,		/* How much is in the stream */
		nbytes = 0;		/* How much output so far */
	int	bail = 0;		/* Presentation loop break flag */
	int	rows = 24;		/* Height of screen */
	char	buffer[128];		/* Input buffer */
	struct	stat stat_buf;		/* Stream stat buffer */

	/*
	 * Get the total size of the file so we can show percent done.
	 */
	(void) fstat(fileno(stream), &stat_buf);
	totalbytes = stat_buf.st_size;

#ifdef	TIOCGWINSZ
	{
	/*
	 * Get the size of the terminal screen.
	 */
	struct	winsize term_size;

	(void) ioctl(1, TIOCGWINSZ, &term_size);
	if (term_size.ws_row > 0)
		rows = term_size.ws_row;
	}
#endif
	term_echo(0);	/* Supress echo */
	term_raw(1);	/* Suppress processing */
	/*
	 * Read lines from the input stream and display them to the terminal.
	 */
	lines_to_put = rows - PROMPT_LINES;
	(void) fputs("\r\n", stdout);
	while (fgets(buffer, sizeof(buffer) - 2, stream)) {
		int	i;

		i = strlen(buffer);
		nbytes += i--;
		if (buffer[i] != '\n')
			buffer[++i] = '\n';
		buffer[++i] = '\r';		/* Map \n to \r\n */
		buffer[++i] = '\0';
		(void) fputs(buffer, stdout);
		if (++lines_put >= lines_to_put) {	/* Page break */
			char	c;		/* User input var */

			(void) printf("--More--(%d%%)",
				(nbytes * 100) / totalbytes);
			(void) fflush(stdout);
			(void) term_read(&c, 1);
			(void) fputs("\r              \r", stdout);

			switch (c) {
			case '1':		/* Show N lines */
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				lines_to_put = c - '0';
				break;
			case '0':
				lines_to_put = 10;
				break;
			case ' ':		/* Show next page */
				lines_to_put = rows - PROMPT_LINES;
				break;
			case 'Q':		/* Quit */
			case 'q':
				bail = 1;
				break;
			default:		/* Show next line */
				lines_to_put = 1;
				break;
			}
			lines_put = 0;
		}
		if (bail)
			break;
	}
	(void) fputs("\r\n", stdout);
	(void) fflush(stdout);

	term_raw(0);	/* Re-enable processing */
	term_echo(1);	/* Re-enable echo */
}
/* End pager.c */
