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
 *	npasswd version information
 *	$Id: version.c.SH,v 1.15 2002/10/02 15:56:04 clyde Exp $
 */
!NO!SUBS!
$spitshell >>version.c <<!GROK!THIS!

char	*build_info =
"Environment:	$myuname\n\
Configured by:	$cf_by@$myhostname $cf_time\n\
Build options:	$cc_osflags\n";

char	*npasswd_version = "$package $baserev (07/01/1998)",
	*npasswd_patchlevel = "04 (10/14/1998)";

/*
 * End $RCSfile: version.c.SH,v $
 */
!GROK!THIS!

chmod 0644 version.c
