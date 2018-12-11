h32446
s 00001/00001/00090
d D 1.14 98/10/14 09:45:23 clyde 14 13
c Bump patchlevel
e
s 00001/00001/00090
d D 1.13 98/09/23 14:33:56 clyde 13 12
c Bump patchlevel
e
s 00001/00001/00090
d D 1.12 98/09/22 11:17:58 clyde 12 11
c Update patch level
e
s 00001/00001/00090
d D 1.11 98/09/18 11:43:53 clyde 11 10
c Bump the patch level
e
s 00001/00004/00090
d D 1.10 98/07/10 14:46:45 clyde 10 9
c Remove checkpassword version stamp
e
s 00004/00004/00090
d D 1.9 98/06/23 11:14:10 clyde 9 8
c Tweak datestamps
e
s 00048/00004/00046
d D 1.8 98/05/05 13:39:48 clyde 8 7
c 1. Add copyright message
c 2. Reset version dates and numbers
e
s 00002/00002/00048
d D 1.7 97/10/29 15:32:48 clyde 7 6
c Bump patch levels for npasswd and checkpasswd
e
s 00001/00001/00049
d D 1.6 97/08/26 13:03:36 clyde 6 5
c Increment npasswd patch level
e
s 00001/00001/00049
d D 1.5 97/06/18 14:49:13 clyde 5 4
c Bump npasswd patch level
e
s 00001/00001/00049
d D 1.4 97/05/27 09:50:07 clyde 4 3
c Update patch level for npasswd
e
s 00006/00010/00044
d D 1.3 97/05/05 10:33:15 clyde 3 2
c Use more tokens from config.sh
e
s 00000/00000/00054
d D 1.2 96/08/06 14:14:29 clyde 2 1
c beta 3 cycle 1 checkin
e
s 00054/00000/00000
d D 1.1 95/04/05 16:27:01 clyde 1 0
c date and time created 95/04/05 16:27:01 by clyde
e
u
U
f e 0
t
T
I 1
case $CONFIG in
'')
	if test -f config.sh; then TOP=.;
	elif test -f ../config.sh; then TOP=..;
	elif test -f ../../config.sh; then TOP=../..;
	elif test -f ../../../config.sh; then TOP=../../..;
	elif test -f ../../../../config.sh; then TOP=../../../..;
	else
		echo "Can't find config.sh."; exit 1
	fi
	. $TOP/config.sh
	;;
esac
: This forces SH files to create target in same directory as SH file.
: This is so that make depend always knows where to find SH derivatives.
case "$0" in
*/*) cd `expr X$0 : 'X\(.*\)/'` ;;
esac
echo "Extracting version.c (with variable substitutions)"
: This section of the file will have variable substitutions done on it.
: Move anything that needs config subs from !NO!SUBS! section to !GROK!THIS!.
: Protect any dollar signs and backticks that you do not want interpreted
: by putting a backslash in front.  You may delete these comments.
: In the following dollars and backticks do not need the extra backslash.

$spitshell >version.c <<'!NO!SUBS!'
/*
I 8
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
E 8
 *	npasswd version information
D 3
*	%W% %G% (cc.utexas.edu)
E 3
I 3
 *	%W% %G% (cc.utexas.edu)
E 3
 */
!NO!SUBS!
$spitshell >>version.c <<!GROK!THIS!

char	*build_info =
"Environment:	$myuname\n\
Configured by:	$cf_by@$myhostname $cf_time\n\
Build options:	$cc_osflags\n";

D 3
!GROK!THIS!
E 3
I 3
D 8
char	*npasswd_version = "$package $baserev (5/1/97)",
D 4
	*npasswd_patchlevel = "0 (5/1/97)";
E 4
I 4
D 5
	*npasswd_patchlevel = "1 (5/27/97)";
E 5
I 5
D 6
	*npasswd_patchlevel = "2 (6/18/97)";
E 6
I 6
D 7
	*npasswd_patchlevel = "3 (8/26/97)";
E 7
I 7
	*npasswd_patchlevel = "4 (10/29/97)";
E 8
I 8
D 9
char	*npasswd_version = "$package $baserev (05/01/1998)",
	*npasswd_patchlevel = "0 (05/01/1998)";
E 9
I 9
char	*npasswd_version = "$package $baserev (07/01/1998)",
D 10
	*npasswd_patchlevel = "0 (07/01/1998)";
E 10
I 10
D 11
	*npasswd_patchlevel = "00 (07/01/1998)";
E 11
I 11
D 12
	*npasswd_patchlevel = "01 (09/18/1998)";
E 12
I 12
D 13
	*npasswd_patchlevel = "02 (09/22/1998)";
E 13
I 13
D 14
	*npasswd_patchlevel = "03 (09/23/1998)";
E 14
I 14
	*npasswd_patchlevel = "04 (10/14/1998)";
E 14
E 13
E 12
E 11
E 10
E 9
E 8
E 7
E 6
E 5
E 4
E 3

D 3
$spitshell >>version.c <<'!NO!SUBS!'
E 3
I 3
D 8
char	*checkpasswd_version = "checkpasswd 2.0 (5/1/97)",
D 7
	*checkpasswd_patchlevel = "0 (5/1/97)";
E 7
I 7
	*checkpasswd_patchlevel = "1 (10/29/97)";
E 8
I 8
D 9
char	*checkpasswd_version = "checkpasswd 2.0 (05/01/1998)",
	*checkpasswd_patchlevel = "0 (05/01/1998)";
E 9
I 9
D 10
char	*checkpasswd_version = "checkpasswd 2.0 (07/01/1998)",
	*checkpasswd_patchlevel = "0 (07/01/1998)";
E 9
E 8
E 7
E 3

E 10
D 3
char	*npasswd_version = "npasswd 2.0b4 (3/1/94)",
	*npasswd_patchlevel = "0 (12/20/93)";

char	*checkpasswd_version = "checkpasswd 2.0 (1/7/94)",
	*checkpasswd_patchlevel = "0 (1/7/94)";

E 3
/*
 * End %M%
 */
D 3
!NO!SUBS!
E 3
I 3
!GROK!THIS!
E 3

chmod 0644 version.c
E 1
