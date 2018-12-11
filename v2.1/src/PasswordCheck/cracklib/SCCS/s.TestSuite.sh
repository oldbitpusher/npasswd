h13141
s 00092/00056/00222
d D 1.3 98/04/21 11:53:22 clyde 3 2
c Change test sequencing 
e
s 00047/00003/00231
d D 1.2 98/04/07 14:38:27 clyde 2 1
c Add test group 4 for FascistNpasswd()
e
s 00234/00000/00000
d D 1.1 98/04/03 10:55:48 clyde 1 0
c date and time created 98/04/03 10:55:48 by clyde
e
u
U
f e 0
t
T
I 1
#! /bin/sh
#
# Test suite for Cracklib dictionary building and password checking
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
# %W% %G% (cc.utexas.edu)
#
I 3
verbose=false
 
while [ $# -gt 0 ]; do
	case "$1" in
	-v)	verbose=true;;
	*)	break;;
	esac
	shift
done
 
E 3
msg()
{
	echo "***" $*
}
die()
{
	echo "***" $*; exit 1
}
spew()
{
	sed 's/^/	/' $*
}
set_test()
{
D 3
	TestNo=$1
	TestGroup=`echo $1 | sed 's/\..*//'`
E 3
I 3
	TestMajor=$1
	TestMinor=''
	TestMicro=''
E 3
}
I 3
get_test()
{
	r=$TestMajor
	[ -n "$TestMinor" ] && r="$r $TestMinor"
	[ -n "$TestMicro" ] && r="$r.$TestMicro"
	echo $r
}
incr_minor()
{
	[ -z "$TestMinor" ] && TestMinor=0
	TestMinor=`expr $TestMinor + 1`
	TestMicro='';
}
 
incr_micro()
{
	[ -z "$TestMicro" ] && TestMicro=0
	TestMicro=`expr $TestMicro + 1`
}

E 3
incr()
{
	eval "_tt=\$$1"
	_t=`expr $_tt + 1`
	eval "$1=\$_t"
}
#
# MAIN
# Usage: $0 [test-group] (1...N)
#
msg Test cracklib dictionary building and search

WORDS=/usr/dict/words
[ ! -f $WORDS ] && die No system dictionary in $WORDS

D 2
IN=/tmp/dtin$$
OUT=/tmp/dtout$$
DICT=/tmp/dtdict$$
E 2
I 2
IN=/tmp/dtAin$$
OUT=/tmp/dtAout$$
DICT=/tmp/dtAdict$$
E 2
DSIZE=5000
#
# Check if the executables needed are present
#
missing=''
for prog in packer unpacker testlib testgecos; do
	[ ! -f tools/$prog ] && missing="$missing $prog"
done
[ -n "$missing" ] && die Programs $missing missing in tools

trap "rm -f $IN $OUT $DICT.*; exit 1" 2 3 15
trap "rm -f $IN $OUT $DICT.*; exit 0" 0

I 3
msg Start tests of Cracklib `date`
E 3
#
D 3
# Always build the dictinaries - used by test groups 1 and 2
E 3
I 3
# Always build the dictionaries - used by test groups 1 and 2
E 3
#
D 3
set_test 1.0
E 3
I 3
set_test build
E 3
echo ""
D 3
msg $TestNo Building $DSIZE word test dictionary
E 3
I 3
msg `get_test` Building $DSIZE word test dictionary
E 3
head -$DSIZE $WORDS | sort | tee $IN | tools/packer $DICT
ndfiles=`ls $DICT.* | wc -l`
if [ $ndfiles -ne 3 ]; then
D 3
	msg $TestNo Hashed dictionary files incomplete:
E 3
I 3
	msg `get_test` Hashed dictionary files incomplete:
E 3
	ls -l $DICT.* | spew
else
D 3
	msg $TestNo OK
E 3
I 3
	msg `get_test` OK
E 3
fi

#
# The rest of test group 1 - can dict be unpacked to source
#
(
D 3
set_test 1.1
[ -n "$1" -a "$1" != $TestGroup ] && exit 0
E 3
I 3
set_test verify
[ -n "$1" -a "$1" != $TestMajor ] && exit 0
failures=0

E 3
echo ""
D 3
msg $TestNo Unpacking and comparing dictionary against source
E 3
I 3
incr_minor
msg `get_test` Unpacking and comparing dictionary against source
E 3
tools/unpacker $DICT | sort > $OUT
if diff $IN $OUT >/dev/null; then
D 3
	msg $TestNo OK
E 3
I 3
	msg `get_test` OK
E 3
else
D 3
	msg $TestNo $DICT unpack does not match input
	msg $TestNo Input = `wc -l $IN` lines\; `ls -l $IN | awk '{ print $4 }'` bytes
	msg $TestNo Output = `wc -l $OUT` lines\; `ls -l $OUT | awk '{ print $4 }'` bytes
E 3
I 3
	msg `get_test` $DICT unpack does not match input
	msg `get_test` Input = `wc -l $IN` lines\; `ls -l $IN | awk '{ print $4 }'` bytes
	msg `get_test` Output = `wc -l $OUT` lines\; `ls -l $OUT | awk '{ print $4 }'` bytes
	incr failures
E 3
fi

#
# Test that each word in the dictionary can be found. 
#
D 3
set_test 1.2
E 3
I 3
incr_minor
E 3
echo ""
D 3
msg $TestNo Searching for all $DSIZE words in dictionary
E 3
I 3
msg `get_test` Searching for all $DSIZE words in dictionary
E 3
cat $IN | tools/teststr | grep 'NOT FOUND' > $OUT
if [ -s $OUT ]; then
	missed=`grep -c 'NOT FOUND' $OUT`
D 3
	msg "$TestNo Missed $missed (of $DSIZE) words in test dictionary"
E 3
I 3
	msg "`get_test` Missed $missed (of $DSIZE) words in test dictionary"
E 3
	spew $OUT
I 3
	incr failures
E 3
else
D 3
	msg $TestNo OK
E 3
I 3
	msg `get_test` OK
E 3
fi
I 3
msg End tests of pwck_lexical - $failures failures `date`
exit $failures
E 3
)
I 3
[ $? -ne 0 ] && die Cannot continue
E 3

#
# Test group 2 - cracklib FascistCheck()
#
(
D 3
set_test 2.0
[ -n "$1" -a "$1" != $TestGroup ] && exit 0
E 3
I 3
set_test fcheck
[ -n "$1" -a "$1" != $TestMajor ] && exit 0
E 3
echo ""
D 3
msg $TestGroup Testing cracklib password checker
msg $TestGroup This test only verifies the basic functionality
E 3
I 3
msg `get_test` Testing basic functionality of Cracklib password checker
E 3

D 3
NW=20
E 3
I 3
NW=10
E 3
echo ""
D 3
msg $TestNo Trying $NW words from the dictionary 1>&2
E 3
I 3
incr_minor
msg `get_test` Trying $NW words from the dictionary 1>&2
E 3
#
# Generate a very psuedo-fake-random number
#
R1=`date | awk '{ print $4 }' | tr : ' ' | awk '{ print (($1+$2)*$2)+($3*$3) }'`
[ $R1 -gt $DSIZE ] && R1=`expr $R1 % $DSIZE`
#
# Pick words from the list and permute them
#
tail -$R1 $IN | head -$NW | (
	while read str; do
		echo 0$str				# Will be rejected
		echo $str | tr '[io]' '[10]'		# Should be rejected
		echo $str | tr '[aeiou]' '[AEIOU]'	# Might be rejected
		echo $str@$str				# Should pass
	done
) | tools/testlib $DICT
)	# End test group 2

#
# Test group 3 - cracklib FascistGecos()
#
(
which=0
D 3
set_test 3.$which
[ -n "$1" -a "$1" != $TestGroup ] && exit 0
E 3
I 3
set_test fgecos
[ -n "$1" -a "$1" != $TestMajor ] && exit 0
E 3
echo ""
D 3
msg $TestGroup Testing checking against passwd entry
msg $TestGroup This test only verifies the basic functionality
E 3
I 3
msg `get_test` Testing checking against passwd entry
E 3
u=$USER
[ -z "$n" ] && u=$LOGNAME
pwent=`grep "^${u}:" /etc/passwd`
(
	sleep 1
D 3
	incr which
	set_test $TestGroup.$which
E 3
I 3
	incr_minor
E 3
	echo ""
D 3
	msg $TestNo Trying username permutations - will be rejected 1>&2
E 3
I 3
	msg `get_test` Trying username permutations - will be rejected 1>&2
E 3
	name=`echo "$pwent" | awk 'BEGIN { FS=":" } { print $1 }'`
	echo $name
	echo $name$name
	echo ${name}0
	sleep 2

D 3
	incr which
	set_test $TestGroup.$which
E 3
I 3
	incr_minor
E 3
	echo ""
D 3
	msg $TestNo Trying username permutations - might be rejected 1>&2
E 3
I 3
	msg `get_test` Trying username permutations - might be rejected 1>&2
E 3
	echo $name | tr '[aeiou]' '[AEIOU]'
	echo $name | tr '[io]' '[10]'
	sleep 2

D 3
	incr which
	set_test $TestGroup.$which
E 3
I 3
	incr_minor
E 3
	echo ""
D 3
	msg $TestNo Trying username permutations - should be ok 1>&2
E 3
I 3
	msg `get_test` Trying username permutations - should be ok 1>&2
E 3
	echo ${name}"'s-password"
	echo $name@$name
	sleep 2

D 3
	incr which
	set_test $TestGroup.$which
E 3
I 3
	incr_minor
E 3
	echo ""
D 3
	msg $TestNo Trying GECOS data - should be rejected 1>&2
E 3
I 3
	msg `get_test` Trying GECOS data - should be rejected 1>&2
E 3
	IFS="${IFS},"
	for gc in `echo "$pwent" | awk 'BEGIN { FS=":" } { print $5 }'`; do
		for gw in $gc; do
			echo $gw
		done
	done
) | tools/testgecos
)	# End test group 3

I 2
D 3

#
# Always build the dictinaries - used by test groups 1 and 2
#
E 3
( 
D 3
set_test 4.0
[ -n "$1" -a "$1" != $TestGroup ] && exit 0
E 3
I 3
set_test fnpasswd
[ -n "$1" -a "$1" != $TestMajor ] && exit 0
failures=0

E 3
echo ""
D 3
msg $TestGroup Testing npasswd dictionary lookup
E 3
I 3
msg `get_test` Testing npasswd dictionary lookup
E 3

IN2=/tmp/dtBin$$
DICT2=/tmp/dtBdict$$

trap "rm -f $IN2 $DICT2.*; exit 1" 2 3 15
trap "rm -f $IN2 $DICT2.*; exit 0" 0

D 3
set_test 4.1
E 3
I 3
incr_minor
E 3
echo ""
D 3
msg $TestNo Building second test dictionary
E 3
I 3
msg `get_test` Building second test dictionary
E 3
dn=`expr $DSIZE \* 2`
head -$dn $WORDS | tail -$DSIZE | sort | tee $IN2 | tools/packer $DICT2
ndfiles=`ls $DICT2.* | wc -l`
if [ $ndfiles -ne 3 ]; then
D 3
	msg $TestNo Hashed dictionary files incomplete:
E 3
I 3
	msg `get_test` Hashed dictionary files incomplete:
E 3
	ls -l $DICT2.* | spew
I 3
	incr failures
E 3
else
D 3
	msg $TestNo OK
E 3
I 3
	msg `get_test` OK
E 3
fi

D 3
set_test 4.2
E 3
I 3
incr_minor
E 3
echo ""
D 3
msg $TestNo Testing npasswd dictionary lookup
msg $TestNo Two words and their variants should be ok, the rest rejected
E 3
I 3
msg `get_test` Testing npasswd dictionary lookup
msg `get_test` Two words and their variants should be ok, the rest rejected
E 3
	( tail -5 $IN; tail -5 $IN2) | (
		while read str; do
			echo 0$str			# Will be rejected
			echo $str | tr '[io]' '[10]'	# Should be rejected
			echo $str | tr '[aeiou]' '[AEIOU]' # Might be rejected
		done
	) | tools/testnpasswd $DICT $DICT2
D 3
exit
)	# End test group 4
E 3

I 3
msg `get_test` End dictionary lookup tests - $failures failures
exit $failures
)	# End test grou 

E 3
echo ""
E 2
msg All tests completed - examine the output for errors

exit
#
# End %M%
E 1
