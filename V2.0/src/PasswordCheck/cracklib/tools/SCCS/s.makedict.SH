h49550
s 00002/00002/00146
d D 1.6 98/07/16 09:26:02 clyde 6 5
c Change config path vars
e
s 00019/00015/00129
d D 1.5 98/06/26 14:42:57 clyde 5 4
c Cleanup inexplicable mess
e
s 00006/00000/00138
d D 1.4 97/05/16 14:42:48 clyde 4 3
c Look for .Z and .gz names of dict files
e
s 00009/00001/00129
d D 1.3 97/05/16 14:33:15 clyde 3 2
c Handle compressed files (.Z & .gz)
e
s 00001/00001/00129
d D 1.2 96/12/03 15:37:55 clyde 2 1
c Fix typos
e
s 00130/00000/00000
d D 1.1 96/08/29 15:38:42 clyde 1 0
c date and time created 96/08/29 15:38:42 by clyde
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
echo "Extracting makedict (with variable substitutions)"
: This section of the file will have variable substitutions done on it.
: Move anything that needs config subs from !NO!SUBS! section to !GROK!THIS!.
: Protect any dollar signs and backticks that you do not want interpreted
: by putting a backslash in front.  You may delete these comments.
$spitshell >makedict <<!GROK!THIS!
$startsh
I 5

TR=$tr
TRUP="$trup"
TRDOWN="$trdown"
D 6
PACKER=$privlibexp/packer	# The program that packs the dictionary
UNPACKER=$privlibexp/unpacker	# The program that unpacks the dictionary
E 6
I 6
PACKER=$p_utildir/packer	# The program that packs the dictionary
UNPACKER=$p_utildir/unpacker	# The program that unpacks the dictionary
E 6

E 5
!GROK!THIS!

: In the following dollars and backticks do not need the extra backslash.
$spitshell >>makedict <<'!NO!SUBS!'
#
# %W% %G% (cc.utexas.edu)
#
###
# This program is copyright Alec Muffett 1993. The author disclaims all
# responsibility or liability with respect to it's usage or its effect
# upon hardware or computer systems, and maintains copyright as set out
# in the "LICENCE" document which accompanies distributions of Crack v4.0
# and upwards.
###
#
# This script is used to build the dictionary hash files
#
# Usage:
#	mkdict -o output-dict
D 5
#		[-T /tmp/dir (specify alternate tmp dir)]
E 5
I 5
#		[-T /tmp/dir (alternate tmp dir)]
E 5
#		[-m merge-with-dict]
#		dict-source1 dict-source2 ...
#
### In case of explosion, rerun with with "-T" option pointing to a lot
### of free space in a directory somewhere.

I 5
Usage="Usage: $0 -o output-dict [-m source-dict] [-T /tmp/dir] dict-source1 dict-source2 ..."
E 5
SORT="sort"

D 5
PACKER=$o_privlib/packer	# The program that packs the dictionary
UNPACKER=$o_privlib/unpacker	# The program that unpacks the dictionary

E 5
if [ $# -lt 1 ]; then
D 5
	echo "Usage: $0 -o output-dict [-m source-dict] [-T /tmp/dir] dict-source1 dict-source2 ..."
E 5
I 5
	echo $Usage
E 5
	exit 1
fi
while [ -n "$1" ]; do
	case $1 in
	-m*)	src_dict=`expr $1 : '-s\(.*\)'`
		if [ -z "$src_dict" ]; then
			shift
D 5
			src_dict=${1?"Missing option to -s"}
E 5
I 5
			src_dict=${1?"Missing option to -m"}
E 5
		fi
		;;

	-o*)	dest_dict=`expr $1 : '-o\(.*\)'`
		if [ -z "$dest_dict" ]; then
			shift
			dest_dict=${1?"Missing option to -o"}
		fi
		;;

	-T*)	tmp=`expr $1 : '-T\(.*\)'`
		if [ -z "$tmp" ]; then
			shift
			tmp=${1?"Missing option to -T"}
		fi
		;;

	*)	break
		;;
	esac
	shift
done
#
# Add the directory where this program lives to PATH
# so that 'packer' will be found (if needed)
#
if [ ! -f $PACKER ]; then
	bn=`basename $0`
	pn=`expr $0 : "\(.*\)/$bn"`
	PACKER="$pn/$PACKER"
	UNPACKER="$pn/$UNPACKER"
fi

if [ -z "$dest_dict" ]; then
	echo No output file given
I 5
	echo $Usage
E 5
	exit 1
fi
[ -n "$tmp" ] && SORT="$SORT -T $tmp"

OUT=${dest_dict}.TMP
(
	[ -n "$src_dict" ] && $UNPACKER $src_dict
D 3
	cat $* 			# Combine all source files
E 3
I 3
D 5
	(
E 5
	for f in $*; do
I 4
		for x in '' .Z .gz ''; do
			if [ -f "$f$x" ]; then
				f=$f$x
				break
			fi
		done
E 4
		case "$f" in
		*.Z)	zcat $f;;
		*.gz)	gunzip --stdout $f;;
		*)	cat $f;;
		esac
	done
D 5
	)
E 3
) |	grep -v '^#' | 		# Remove comments
	grep -v '^$' |		# Remove blank lines
	tr $trup $trlow | 	# Make lower case
	$SORT |			# Put in ASCII collating order
	uniq  |			# Pick out unique words
E 5
I 5
) |	grep -v '^#' | \
	grep -v '^$' | \
	$TR "$TRUP" "$TRDOWN" | \
	$SORT | \
	uniq | \
E 5
	$PACKER $OUT		# Build the dictionary

for t in hwm pwd pwi; do
D 2
	if [ if -s $OUT.$t [; then
E 2
I 2
	if [ -s $OUT.$t ]; then
E 2
		mv $OUT.$t $dest_dict.$t
	else
D 5
		echo ERROR: Empty hash file $OUT.t
E 5
I 5
		echo Empty or missing hash file $OUT.$t
E 5
	fi
done
D 5
echo Made dictionary '"'$dest_dict'"'.
E 5
I 5
echo Made dictionary $dest_dict
E 5
exit 0
#
# End %M%
!NO!SUBS!
chmod 755 makedict
$eunicefix makedict
E 1
