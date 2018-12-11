h46289
s 00010/00012/00246
d D 1.6 98/06/30 13:55:53 clyde 6 5
c Fix command line args
e
s 00045/00001/00213
d D 1.5 98/05/05 16:38:00 clyde 5 4
c 1. Add copyright notice
c 2. Use the 'mv' found by Configure
e
s 00000/00001/00214
d D 1.4 97/05/02 13:40:42 clyde 4 3
c Remove verbose crap
e
s 00047/00011/00168
d D 1.3 97/05/01 13:56:37 clyde 3 2
c 1. Change to .SH self-extractor
c 2. Change order of arguments (destination dir first)
c 3. Use "keepdir" if no destination given
e
s 00002/00001/00177
d D 1.2 97/04/29 16:00:12 clyde 2 1
c Make "df" use more general
e
s 00178/00000/00000
d D 1.1 97/04/28 14:39:27 clyde 1 0
c date and time created 97/04/28 14:39:27 by clyde
e
u
U
f e 0
t
T
I 1
D 3
#!/bin/sh
E 3
I 3
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
echo "Extracting savefiles (with variable substitutions)"
: This section of the file will have variable substitutions done on it.
: Move anything that needs config subs from !NO!SUBS! section to !GROK!THIS!.
: Protect any dollar signs and backticks that you do not want interpreted
: by putting a backslash in front.  You may delete these comments.
$spitshell >savefiles <<!GROK!THIS!
$startsh

DEFAULT="$p_keepdir"		# Where to stash things by default
MV=$mv

!GROK!THIS!

: In the following dollars and backticks do not need the extra backslash.
$spitshell >>savefiles <<'!NO!SUBS!'
E 3
#
I 5
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
E 5
# %W% %G% (cc.utexas.edu) %P%
#
D 3
# %M%
#	Move files, retaining hard links
E 3
I 3
# %M% Move files, retaining hard links
E 3
#
# Usage:
D 3
#	$0 [-n] source-file ... source-file destination-dir
E 3
I 3
#	$0 [-n] [destination] file ... file"
E 3
#
# Exits with the number of errors encountered
#
EXEC=''

#
# filetype
#	Sets 'type' to what kind of object $1 is
# Usage
#	filetype file
#
filetype()
{
	type=''
	[ -z "$1" ] && return
	type=`ls -dl $1 | sed 's/^\(.\)\(.*\)/\1/'`
	[ X"$type" = "X-" ] && type='f'
}

savelink()
{
	(
	umask 022
	_dx=$1
	shift
	echo $* >> $_dx.MARK
	)
}

#
# movefile
#	Move a file to directory $dest
#
# Usage
#	movefile source-file
#
movefile()
{
	_bn=`basename $1`
	if [ -f $dest/$_bn ]; then
		echo File \"$dest/$_bn\" already exists
		return			# File already exists at target
	fi
	filetype $1
	if [ $type = l ]; then
		target=`ls -l $1 | awk '{ print $NF }'`
		echo \"$1\" is a symbolic link to \"$target\" - not moved
		return
	fi
D 5
	if $EXEC mv $1 $dest; then
E 5
I 5
	if $EXEC $MV $1 $dest; then
E 5
		echo Moved \"$1\" to \"$dest/$_bn\"
		savelink $dest/$_bn $1
	else
		echo Failed to move \"$1\" to \"$dest/$_bn\"
		errors=`expr $errors + 1`
	fi
}

#
# install_links
#	Install file and make links
#
# Usage
#	install_links file link1 ... linkN
#
install_links()
{
	[ -z "$1" ] && return		# No arguments
	_first=$1
	shift
	movefile $_first
	_sx=`basename $_first`
	for _f in $*; do
		_t=`basename $_f`
I 2
		[ -f $dest/$_t ] && continue
E 2
		if $EXEC ln $dest/$_sx $dest/$_t; then
			echo Linked \"$dest/$_sx\" to \"$dest/$_t\"
			savelink $dest/$_sx $_f
			savelink $dest/$_t
			$EXEC rm -f $_f
		else
			errors=`expr $errors + 1`
		fi
	done
}

#
# Main program
#
if [ -z "$1" ]; then
D 3
	echo "Usage: $0 [-n] source-file ... source-file destination-dir"
E 3
I 3
D 6
	echo "Usage: $0 [-n] [destination] file ... file"
E 6
I 6
	echo "Usage: $0 [-n] [-d destination] file ... file"
E 6
E 3
	exit 1
fi
D 6
#
# Look for option "-n"
#
if [ X$1 = X-n ]; then
	EXEC=echo
E 6
I 6
while [ $# -gt 0 ]; do
	case "$1" in
	-n)	EXEC=echo ;;
	-d)	dest=$2; shift ;;
	*)	break ;;
	esac
E 6
	shift
D 6
fi
E 6
I 6
done
E 6
#
D 3
# The last argument is the destination directory
E 3
I 3
# The first argument is the destination directory
E 3
#
D 3
for f do
	src="$src $f"
	dest=$f
done
E 3
I 3
D 6
if [ -d $1 ]; then
	dest=$1
	shift
else
E 6
I 6
if [ -z "$dest" ]; then
E 6
	dest=$DEFAULT
D 4
	echo Will save files to \"$dest\"
E 4
fi
E 3
D 6
if [ ! -d "$dest" ]; then		# Last argument not a directory
E 6
I 6
if [ ! -d "$dest" ]; then
E 6
	echo No destination directory
	exit 1
fi
#
# Process files from command line
#
D 3
ls -id $src | sort -n | (
E 3
I 3
ls -id $* | sort -n | (
E 3
	errors=0		# Error count
	#
	# Input is ordered by inode number
	#
	while read inum file; do
		[ -d $file ] && continue
		links=`ls -l $file | awk '{ print $2 }'`
		#
		# File has one link - just move it
		#
		if [ $links -eq 1 ]; then
			movefile $file
			continue
		fi
		#
		# Files has multiple links - collect link information
I 5
		# (the output of df does not matter, as long as it
		# is related to the filesystem)
E 5
		#
D 2
		fs=`df $file | tail -1 | awk '{ print $NF }'`
E 2
I 2
		fs=`df $file | tail -1`
E 2
		if [ -z "$fs" ]; then
			echo Cannot determine filesystem for \"$file\"
			movefile $file
			continue
		fi
		#
		# Build link lists
		#  Name = "links_<basename of first file>"
		#   e.g. "links_passwd"
		#
		bn=`basename $file`
		if [ "$inum" = "$in_last" -a "$fs" = "$fs_last" ]; then
			# Same inode and filesystem
			[ -z "$bnlast" ] && bnlast=$bn
			ln=links_$bnlast		# Make list name
			eval "$ln=\"\$$ln \$file\""	# Add to list
		else
			ln=links_$bn		# Make list name
			eval "$ln=\"$file\""	# Init list
			lnx="$lnx $ln"		# Remember list name
			bnlast=$bn		# Save state hooks
			in_last=$inum
			fs_last=$fs
		fi
	done
	#
	# Traverse the list of link lists
	#
	for it in $lnx; do
		eval "tmp=\"\$$it\""
		install_links $tmp
	done
	exit $errors
)
exit		# Exit status will be that of the child process
#
# end %M%
I 3
!NO!SUBS!
chmod 755 savefiles
$eunicefix savefiles
E 3
E 1
