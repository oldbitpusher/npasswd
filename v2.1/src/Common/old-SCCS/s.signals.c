h15771
s 00069/00005/00071
d D 1.5 98/11/17 16:47:56 clyde 6 5
c 1. Add copyright notice
c 2. Add more comments
e
s 00004/00002/00072
d D 1.4 98/04/30 16:31:21 clyde 5 4
c Add braces to make compilers happier
e
s 00004/00000/00070
d D 1.3 97/09/23 14:08:22 clyde 4 2
c Fix varargs usage in block_signals
e
s 00001/00001/00069
d R 1.3 97/09/23 13:43:03 clyde 3 2
c Fix varargs problem
e
s 00003/00001/00067
d D 1.2 97/09/23 12:30:06 clyde 2 1
c 1. Add define to fix problems with common.h and AIX
c 2. Add some {} to make compilers happy
e
s 00068/00000/00000
d D 1.1 96/08/07 15:19:38 clyde 1 0
c date and time created 96/08/07 15:19:38 by clyde
e
u
U
f e 0
t
T
I 1
/*
D 6
 * npasswd module %M%
E 6
I 6
 * Copyright 1998, The University of Texas at Austin ("U. T. Austin").
 * All rights reserved.
E 6
 *
D 6
 * Compliation: cc -c %M%
 * Includes: npasswd.h
E 6
I 6
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
E 6
 */

I 6
/*
 * Signal mangement routines
 *
 * Exported routines:
 *	block_signals
 *	unblock_signals
 */

E 6
I 2
#define	_signals_c
E 2
#include "npasswd.h"

#ifndef lint
static char sccsid[] = "%W% %G% (cc.utexas.edu) %P%";
#endif

/*
D 6
 * Signal block/unblock routines.
E 6
I 6
 * block_signals
 *	Block a list of signals
 * Usage:
 *	block_signals(old_value_save, sig1, sig2, ... 0);
 *	Signal list ends with a 0
E 6
 */
public void
block_signals VA_DCL(struct sigblk *args)
{
	va_list	fargs;
	struct sigblk *sigblk;
	int	xsig;

	VA_START(fargs, args);
I 4
#ifdef	__STDC__
	sigblk = args;
#else
E 4
	sigblk = va_arg(fargs, struct sigblk *);
I 4
#endif
E 4

#if	(SIG_TYPE == SIG_TYPE_POSIX)
I 6
	/*
	 * POSIX signals - use sigprocmask()
	 */
E 6
	sigemptyset(&sigblk->savesigs);
D 5
	while (xsig = va_arg(fargs, int))
E 5
I 5
	while (xsig = va_arg(fargs, int)) {
E 5
		sigaddset(&sigblk->savesigs, xsig);
I 5
	}
E 5
	sigprocmask(SIG_BLOCK, &sigblk->savesigs, &sigblk->sigvalues);
#endif

#if	(SIG_TYPE == SIG_TYPE_BSD)
I 6
	/*
	 * BSD type signals - use sigblock()
	 */
E 6
	sigblk->savesigs = 0;
D 5
	while (xsig = va_arg(fargs, int))
E 5
I 5
	while (xsig = va_arg(fargs, int)) {
E 5
		sigblk->savesigs |= sigmask(xsig);
I 5
	}
E 5
	sigblk->sigvalues = sigblock(sigblk->savesigs);
#endif

#if	(SIG_TYPE == SIG_TYPE_UNIX)
I 6
	/*
	 * Classic UNIX signals - use signal(2)
	 */
E 6
D 2
	while (xsig = va_arg(fargs, int))
E 2
I 2
	while (xsig = va_arg(fargs, int)) {
E 2
		sigblk->sigvalues[xsig] = signal(xsig, SIG_IGN);
I 2
	}
E 2
#endif
}

I 6
/*
 * unblock_signals
 *	Unblock a list of signals
 * Usage:
 *	unblock_signals(old_value_save);
 */
E 6
public void
unblock_signals(sigblk)
D 6
	struct sigblk *sigblk;
E 6
I 6
	struct sigblk *sigblk;		/* Saved signal status */
E 6
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

/* End %M% */
E 1
