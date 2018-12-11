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
echo "Extracting installmany (with variable substitutions)"
: This section of the file will have variable substitutions done on it.
: Move anything that needs config subs from !NO!SUBS! section to !GROK!THIS!.
: Protect any dollar signs and backticks that you do not want interpreted
: by putting a backslash in front.  You may delete these comments.
$spitshell >installmany <<!GROK!THIS!
$startsh
# Get system programs
RM="$rm"
LN="$ln"
LNS="$lns"
!GROK!THIS!

: In the following dollars and backticks do not need the extra backslash.
$spitshell >>installmany <<'!NO!SUBS!'
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
# @(#)installmany.SH	1.2 07/14/98 (cc.utexas.edu)
#
# installmany.SH - Install links or copies of a file in multiple locations
#
#
EXEC=''
ecode=0
if [ -z "$1" ]; then
	echo Usage: $0 [-n] source dest ... dest
	exit 1
fi
if [ X$1 = "X-n" ]; then
	EXEC=echo
	shift
fi

source=$1
imode=`ls -l $source | awk '{ print $1 }' | \
	sed -e 's/.\(...\)\(...\)\(...\)/u=\1,g=\2,o=\3/' -e 's/-//g'`

shift
while [ $# -gt 0 ]; do
	dest=$1
	shift
	$EXEC $RM $dest
	if $EXEC $LN $source $dest; then		# Hard link first
		echo Linked \"$source\" to \"$dest\"
		# ls -l $dest
		continue
	fi
	if $EXEC $LNS $source $dest; then	# Symbolic link
		echo Symlinked \"$source\" to \"$dest\"
		# ls -l $dest
		continue
	fi
	if $EXEC cp $binary $dest; then		# Fall back to copy
		$EXEC chmod $imode $dest
		echo Copied \"$source\" to \"$dest\"
		# ls -l $dest
		continue
	fi
	echo Could not link or copy \"$source\" to \"$dest\"
	ecode=`expr $ecode + 1`
done
exit $ecode
#
# end installmany.SH
!NO!SUBS!
chmod 755 installmany
$eunicefix installmany
