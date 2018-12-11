h64057
s 00043/00000/00082
d D 1.4 98/05/05 16:21:30 clyde 4 3
c Add copyright message
e
s 00003/00004/00079
d D 1.3 97/05/02 13:40:56 clyde 3 2
c Fix stupid typos
e
s 00045/00011/00038
d D 1.2 97/05/01 13:55:37 clyde 2 1
c 1. Convert to .SH self-extractor
c 2. Use "keepdir" if no directory given
e
s 00049/00000/00000
d D 1.1 97/04/28 14:39:26 clyde 1 0
c date and time created 97/04/28 14:39:26 by clyde
e
u
U
f e 0
t
T
I 1
D 2
#!/bin/sh
E 2
I 2
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
echo "Extracting restorefiles (with variable substitutions)"
: This section of the file will have variable substitutions done on it.
: Move anything that needs config subs from !NO!SUBS! section to !GROK!THIS!.
: Protect any dollar signs and backticks that you do not want interpreted
: by putting a backslash in front.  You may delete these comments.
$spitshell >restorefiles <<!GROK!THIS!
$startsh

DEFAULT="$p_keepdir"		# Default restore directory

!GROK!THIS!

: In the following dollars and backticks do not need the extra backslash.
$spitshell >>restorefiles <<'!NO!SUBS!'
E 2
#
I 4
#
# Copyright 1998, The University of Texas at Austin ("U. T. Austin").
# All rights reserved.
#
# By using this software the USER indicates that he or she has read,
# understood and will comply with the following:
#
# U. T. Austin hereby grants USER permission to use, copy, modify, and
# distribute this software and its documentation for any purpose and
# without fee, provided that:
#
# 1. the above copyright notice appears in all copies of the software
#    and its documentation, or portions thereof, and 
# 2. a full copy of this notice is included with the software and its
#    documentation, or portions thereof, and 
# 3. neither the software nor its documentation, nor portions thereof,
#    is sold for profit. Any commercial sale or license of this software,
#    copies of the software, its associated documentation and/or
#    modifications of either is strictly prohibited without the prior
#    consent of U. T. Austin. 
# 
# Title to copyright to this software and its associated documentation
# shall at all times remain with U. T. Austin. No right is granted to
# use in advertising, publicity or otherwise any trademark, service
# mark, or the name of U. T. Austin.
# 
# This software and any associated documentation are provided "as is,"
# and U. T. AUSTIN MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESSED OR
# IMPLIED, INCLUDING THOSE OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR
# PURPOSE, OR THAT USE OF THE SOFTWARE, MODIFICATIONS, OR ASSOCIATED
# DOCUMENTATION WILL NOT INFRINGE ANY PATENTS, COPYRIGHTS, TRADEMARKS OR
# OTHER INTELLECTUAL PROPERTY RIGHTS OF A THIRD PARTY. U. T. Austin, The
# University of Texas System, its Regents, officers, and employees shall
# not be liable under any circumstances for any direct, indirect, special,
# incidental, or consequential damages with respect to any claim by USER
# or any third party on account of or arising from the use, or inability
# to use, this software or its associated documentation, even if U. T.
# Austin has been advised of the possibility of those damages.
# 
# Submit commercialization requests to: Office of the Executive Vice
# President and Provost, U. T. Austin, 201 Main Bldg., Austin, Texas,
# 78712, ATTN: Technology Licensing Specialist.
#
E 4
# %W% %G% (cc.utexas.edu) %P%
#
# %M% -	Restore files preserved by savefiles
#
# Usage:
D 2
#	$0 [-n] save-dir
E 2
I 2
#	$0 [-n] [save-dir]
E 2
#
EXEC=''

#
D 2
# Main program
#
if [ -z "$1" ]; then
	echo "Usage: $0 [-n] save-dir"
	exit 1
fi
#
E 2
# Look for option "-n"
#
if [ X$1 = X-n ]; then
	EXEC=echo
	shift
fi

D 2
cd $1 || exit 1
E 2
I 2
if [ -z "$1" ]; then
	savedir=$DEFAULT
D 3
	exit 1
E 3
else
D 3
	DEFUALT=$1
E 3
I 3
	savedir=$1
E 3
fi

D 3
cd $DEFAULT || exit 1
E 3
I 3
cd $savedir || exit 1
E 3
E 2
for f in *.MARK; do
	master=""
	for sf in `cat $f`; do
		[ ! -f `basename "$sf"` ] && continue
		$EXEC rm -f $sf
		if [ -z "$master" ]; then
			src=`basename $f .MARK`
			[ -f $src ] || continue
			$EXEC mv $src $sf || $EXEC cp -p $src $sf
D 2
			echo Restored $sf from $1/$src
E 2
I 2
D 3
			echo Restored $sf from $DEFAULT/$src
E 3
I 3
			echo Restored $sf from $savedir/$src
E 3
E 2
			master=$sf
		else
			$EXEC ln $master $sf
			echo Restored link $master to $sf
		fi
	done
	$EXEC rm -f $f
	[ -z "$master" ] && $EXEC rm -f `basename $f .MARK`
done
exit 0
#
# End %M%
I 2
!NO!SUBS!
chmod 755 restorefiles
$eunicefix restorefiles
E 2
E 1
