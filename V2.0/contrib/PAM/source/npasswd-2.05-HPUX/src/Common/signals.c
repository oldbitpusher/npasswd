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
 * Signal mangement routines
 *
 * Exported routines:
 *	block_signals
 *	unblock_signals
 */

#define	_signals_c
#include "npasswd.h"

#ifndef lint
static char sccsid[] = "@(#)signals.c	1.5 11/17/98 (cc.utexas.edu) /usr/share/src/private/ut/share/bin/passwd/V2.0/src/Common/SCCS/s.signals.c";
#endif

/*
 * block_signals
 *	Block a list of signals
 * Usage:
 *	block_signals(old_value_save, sig1, sig2, ... 0);
 *	Signal list ends with a 0
 */
public void
block_signals VA_DCL(struct sigblk *args)
{
	va_list	fargs;
	struct sigblk *sigblk;
	int	xsig;

	VA_START(fargs, args);
#ifdef	__STDC__
	sigblk = args;
#else
	sigblk = va_arg(fargs, struct sigblk *);
#endif

#if	(SIG_TYPE == SIG_TYPE_POSIX)
	/*
	 * POSIX signals - use sigprocmask()
	 */
	sigemptyset(&sigblk->savesigs);
	while (xsig = va_arg(fargs, int)) {
		sigaddset(&sigblk->savesigs, xsig);
	}
	sigprocmask(SIG_BLOCK, &sigblk->savesigs, &sigblk->sigvalues);
#endif

#if	(SIG_TYPE == SIG_TYPE_BSD)
	/*
	 * BSD type signals - use sigblock()
	 */
	sigblk->savesigs = 0;
	while (xsig = va_arg(fargs, int)) {
		sigblk->savesigs |= sigmask(xsig);
	}
	sigblk->sigvalues = sigblock(sigblk->savesigs);
#endif

#if	(SIG_TYPE == SIG_TYPE_UNIX)
	/*
	 * Classic UNIX signals - use signal(2)
	 */
	while (xsig = va_arg(fargs, int)) {
		sigblk->sigvalues[xsig] = signal(xsig, SIG_IGN);
	}
#endif
}

/*
 * unblock_signals
 *	Unblock a list of signals
 * Usage:
 *	unblock_signals(old_value_save);
 */
public void
unblock_signals(sigblk)
	struct sigblk *sigblk;		/* Saved signal status */
{
#if	(SIG_TYPE == SIG_TYPE_POSIX)
	sigprocmask(SIG_UNBLOCK, &sigblk->savesigs, (sigset_t *)0);
	return;
#endif
#if	(SIG_TYPE == SIG_TYPE_BSD)
	sigsetmask(&sigblk->sigvalues);
#endif
#if	(SIG_TYPE == SIG_TYPE_UNIX)
	int	i;
	
	for (i = 0; i <= NSIG; i++) {
		if (sigblk->sigvalues[i])
			(void) signal(i, sigblk->sigvalues[i]);
	}
#endif
}

/* End signals.c */
