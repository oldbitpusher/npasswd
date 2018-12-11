#! /bin/sh
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
# IMPLIED, INCLUDING THOSE OF MERCHANTABILITY OR FIMinorESS FOR A PARTICULAR
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
# 78712, ATMinor: Technology Licensing Specialist.
#
# @(#)TestSuite.sh	1.1 06/04/98 (cc.utexas.edu)
#

#
# Test suite for password check library
#
# Usage: $0 
#
TEMP=/tmp/pwtest.$$
opt_S='-s'
SINK=/dev/null
verbose=false

while [ $# -gt 0 ]; do
	case "$1" in
	-v)	verbose=true
		SINK=/dev/tty
		[ -c /dev/stdout ] && SINK=/dev/stdout
		opt_S=''
		;;
	*)	break;;
	esac
	shift
done

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
	TestMajor=$1
	TestMinor=''
	TestMicro=''
}
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
	if [ -n "$TestMicro" ]; then
		TestMicro=`expr $TestMicro + 1`
	else
		TestMicro=1
	fi
}

incr()
{
	eval "_tt=\$$1"
	_t=`expr $_tt + 1`
	eval "$1=\$_t"
}

#
# MAIN
#
msg ""
msg This suite verifies the functionality of the
msg top-level password checking routines
msg ""
msg Test groups and the routines they verify are:
msg	lexical: pwck_lexical
msg	local: pwck_local
msg	history: pwck_history
msg ""
msg pwck_passwd is verified by the FascistGecos test suite in ./cracklib
msg pwck_crack is verified by the FascistNpasswd test suite in ./cracklib
msg ""

PROGS="./test_pwck ./test_history"
for what in $PROGS; do
	[ ! -f $what ] && die The executable $what is missing - run make
done

#
# Driver for running password checks
#
# $1 = password, $2 = prog, $3 = expected return, $* = config directives
#
test_password()
{
	pw="$1"; shift
	prog=$1; shift
	expect=$1; shift
	[ $# -gt 0 ] && args="-D \"$*\""
	eval ./test_pwck $opt_S -p $prog -P \"$pw\" $args > $TEMP
	status=$?
	if [ X$expect = "X-" ]; then	# Expect "-" means don't care
		spew $TEMP
		msg `get_test` DONE
	else 
		if [ $status -eq $expect ]; then
			spew $TEMP
			msg `get_test` OK
		else
			spew $TEMP
			msg `get_test` FAILED
			incr failures
		fi
	fi
	rm -f $TEMP
}

failures=0

#
# Test suite for "pwck_lexical"
#
trap "rm -f $TEMP; exit 1" 1 2 3 15
set_test lexical
if [ -z "$1" -o "$1" = $TestMajor ]; then
	echo ""
	ofailures=$failures
	msg `get_test` Start test group \"$TestMajor\" `date`
	
	#
	# Test for password too short
	#
	incr_minor
		msg `get_test` Reject too short
		test_password foo lexical 1 "minpassword 4"
	
	#
	# Test for password being all numbers
	#
	incr_minor
		msg `get_test` Reject all numbers
		test_password 012345689 lexical 1
	
	#
	# Test for password being all whitespace
	#
	incr_minor
		msg `get_test` Reject all whitespace
		# Too many levels of shell quoting in test_password - do not use
		./test_pwck $opt_S -p lexical \
			-P ' 	 	' -D "minpassword 3" > $TEMP
		if [ $? -eq 1 ]; then
			spew $TEMP
			msg `get_test` OK
		else
			spew $TEMP
			msg `get_test` FAILED
			incr failures
		fi
	
	#
	# Test for password being all alphas
	#
	incr_minor
		incr_micro
		msg `get_test` Reject all alpha
		test_password foobarabc lexical 1 "alphaonly no"
	
		incr_micro
		msg `get_test` Accept all alpha
		test_password foobarabc lexical 0 "alphaonly yes"
	
	#
	# Test for password having repeated characters
	#
	incr_minor
		msg `get_test` Reject repeated characters
		test_password 'aaabbbccc' lexical 1 "maxrepeat 2"
	
	#
	# Test for password fitting some patterns
	#
	incr_minor
		incr_micro
		msg `get_test` Reject telephone number lookalikes
		test_password '123-1234' lexical 1
	
		incr_micro
		msg `get_test` Reject US Social Security number lookalikes
		test_password '123-45-1234' lexical 1
	
	#
	# Test for password fitting some patterns
	#
	incr_minor
		msg `get_test` Reject single case
		incr_micro
		test_password 'absdcrs' lexical 1 "singlecase no; alphaonly yes"
	
		incr_micro
		test_password 'ABSDCRS' lexical 1 "singlecase no; alphaonly yes"
	
	#
	# Test for password being single case alpha
	#
	incr_minor
		incr_micro
		msg `get_test` Accept single case
		test_password 'absdcrs' lexical 0 "singlecase yes; alphaonly yes"
	
		incr_micro
		test_password 'ABSDCRS' lexical 0 "singlecase yes; alphaonly yes"
	
	#
	# Test for password having non-printable characters
	#
	incr_minor
		incr_micro
		msg `get_test` Reject non-printable characters
		test_password 'abcdfg' lexical 1 "printableonly yes"
	
		incr_micro
		msg `get_test` Allow non-printable characters
		test_password 'abcdfg' lexical 0 "printableonly no"
	
		incr_micro
		msg `get_test` Reject forbidden non-printable characters
		test_password 'abcdfg' lexical 1 "printableonly no"
	
	#
	# Test for password having a diversity of character classes
	#
	incr_minor
		msg `get_test` Test character class checks
		test_password 'a1b2c3d4e5' lexical 1 "charclasses 3"
	
	echo ""
	msg Test group \"$TestMajor\" done - `expr $failures - $ofailures` failures `date`
fi

set_test local
if [ -z "$1" -o "$1" = $TestMajor ]; then
	#
	# Test suite for the stock "pwck_local"
	# Add tests here if pwck_local.c has been customized
	#
	permute()
	{
		echo $1 | tr '[io]' '[10]'
		echo $1 | tr '[aeiou]' '[AEIOU]'
	}

	echo ""
	msg `get_test` Start test group \"$TestMajor\" `date`

	ofailures=$failures
	host=`hostname 2>/dev/null`
	[ -z "$host" ] && host=`uname -n`
	shost=`echo $host | sed 's/\..*//'`

	incr_minor
		msg `get_test` Test for full hostname 
		test_password $host local 1

	incr_minor
		msg `get_test` Test for short hostname 
		test_password $shost local 1

	incr_minor
		msg `get_test` Test of permuted hostname - some of these will fail
		for s in `permute $shost`; do
			incr_micro
			test_password $s local -
		done

	echo ""
	msg Test group \"$TestMajor\" done - `expr $failures - $ofailures` failures `date`
fi

#
# Test suite for the pasword history mechanism
#
set_test history
if [ -z "$1" -o "$1" = $TestMajor ]; then
	echo ""
	msg `get_test` Start test group \"$TestMajor\" `date`
	ofailures=$failures
	sh TestHistory.sh file || incr failures
	sh TestHistory.sh dbm || incr failures
	msg Test group \"$TestMajor\" done - `expr $failures - $ofailures` failures `date`
fi
msg End password check tests - $failures failures `date`
exit $failures
#
# End TestSuite.sh
