h05322
s 00046/00000/00000
d D 1.1 98/04/30 13:42:34 clyde 1 0
c date and time created 98/04/30 13:42:34 by clyde
e
u
U
f e 0
t
T
I 1
#! /bin/sh
#
# usage: BuildTree source-directory
#
# %W% %G% (cc.utexas.edu)
#
case "$1" in
	"")	echo Usage: $0 source-directory
		exit 1
		;;
	*)	DIRFROM=$1
		;;
esac

if [ ! -f $DIRFROM/MANIFEST ]; then
	echo No $DIRFROM/MANIFEST
	exit 1
fi

for file in `grep -v '^#' $DIRFROM/MANIFEST | awk '{ print $1 }'`; do
	xdir=`(dirname $file) 2>/dev/null`
	if [ -z "$xdir" ]; then		# dirname doesn't exist
		t=`basename $file`
		xdir=`echo $file | sed "s@/$t\\$@@"`
		[ "$xdir" = $file ] && xdir="."
	fi
	if [ -d $DIRFROM/$xdir -a ! -d "$xdir" ]; then
		echo mkdir $xdir
		mkdir -p $xdir
	fi
	if [ "$xdir" != "." ]; then
		(cd $xdir
		depth=`echo $xdir | tr -cd '/\012' | sed -e s@/@../@g`
		case "$DIRFROM" in
		     /*) ;;
		     *)  DIRFROM=../$depth/$DIRFROM ;;
		esac
		[ -f $DIRFROM/$file ] && ln -s $DIRFROM/$file .
		)
	else
	    [ -f $DIRFROM/$file ] && ln -s $DIRFROM/$file .
	fi
done
exit 0
#
# End %M%
E 1
