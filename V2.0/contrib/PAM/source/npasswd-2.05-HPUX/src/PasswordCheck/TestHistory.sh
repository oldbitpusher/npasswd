#! /bin/sh
#
# Test suite for password history
#
# Usage: $0 [test-group] (1...N)
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
# 78712, ATTN: Technology Licensing Specialist.
#
# @(#)TestHistory.sh	1.5 10/13/98 (cc.utexas.edu)
#
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

set_minor()
{
	TestMinor=$1
	TestMicro=''
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

error()
{
	msg `get_test` $*
	incr failures
}

#
# MAIN
#
# i_ndbm=define
if [ ../../config.sh ]; then
	.  ../../config.sh
else
	die Cannot find config.sh
fi
TEMP=/tmp/pwtest.$$
SAVE=/tmp/pwsave.$$
DBF=/tmp/histtemp,$$
rm -f $TEMP* $SAVE* $DBF*

opt_S='-s'
SINK=/dev/null
verbose=false
method=''
[ -z "$USER" ] && USER=nobody

while [ $# -gt 0 ]; do
	case "$1" in
	-v)	verbose=true
		SINK=/dev/tty
		[ -c /dev/stdout ] && SINK=/dev/stdout
		opt_S=''
		opt_V='-v'
		;;
	*)	[ -z "$method" ] && method=$1
		;;
	esac
	shift
done

case "$method" in
	"")	die Method not set
		;;
	d*)	if [ "$i_ndbm" != define ]; then
			msg DBM not enabled
			exit 0
		fi
		method=dbm
		;;
	f*)	method=file
		;;
esac

PROGS="./test_history ./history_admin"
for what in $PROGS; do
	[ ! -f $what ] && die The executable $what is missing - run make
done



set_test history-$method
#
# Testing history in flat password file
#
msg
msg Start history tests - database method \"$method\" `date`
msg
trap "rm -f ${DBF}* ${TEMP} ${SAVE}*; exit 1" 2 3 15
msg Test database = $DBF

set_minor 1
	failures=0
	t_depth=0		# Disable history depth filter
	t_age=0			# Disable history age filter

	echo ""
	tn=`get_test`
	msg `get_test` Testing $method password history

	#
	# Test history database presence check
	#
	incr_micro
	rm -f ${DBF}*
	msg `get_test` Test should return '"No history database"'
	./test_history $opt_S -f $DBF -m $method -a $t_age -d $t_depth -u $USER \
		-p pass1 put > $SINK
	if [ $? -ne 2 ]; then
		die `get_test` FAILED
	else
		msg `get_test` OK
	fi
	#
	# Test of populating history database
	#
	incr_micro
	msg `get_test` Using history_admin to create empty history database 
	./history_admin -c /dev/null -m $method -f $DBF load < /dev/null
	if [ $? -ne 0 ]; then
		die `get_test` FAILED
	else
		msg `get_test` OK
	fi

	incr_micro
	msg `get_test` Populating history
	for T in 1 2 3 4; do
		./test_history $opt_S -m $method -f $DBF -a $t_age -d $t_depth \
			-p pass$T -u $USER put > $SINK || \
				die `get_test` $T FAILED
		sleep 2
	done
	msg `get_test` OK
	#
	# Fetch raw data from history database
	#
	incr_micro
	msg `get_test` Fetching history data
	./test_history $opt_S -m $method -f $DBF -a $t_age -d $t_depth \
		-u $USER get > $SINK || die `get_test` FAILED
	msg `get_test` OK
	#
	# Lookup passwords in history database
	#
	incr_micro
	msg `get_test` Looking for passwords in history
	ofailures=$failures
	for T in 1 2 3; do
		./test_history $opt_S -m $method -f $DBF -a $t_age -d $t_depth \
			-u $USER -p pass$T find || error $T FAILED
	done
	#
	# Test dump/load function of history_admin
	#
	incr_micro
	msg `get_test` Testing history_admin dump and load

	./history_admin -m $method -f $DBF   -d 0 -a 0 dump | sort > $DBF.0
	./history_admin -m $method -f $DBF.1 -d 0 -a 0 $opt_V load < $DBF.0
	./history_admin -m $method -f $DBF.1 -d 0 -a 0 dump | sort > $DBF.2
	if diff $DBF.0 $DBF.2 > $DBF.3 ; then
		msg `get_test` OK
	else
		spew $DBF.3
		error FAILED
	fi
	rm -f $DBF.0 $DBF.1 $DBF.2 $DBF.3

	incr_micro

	#
	# Test 1 - merge which adds data to existing user
	#
	msg `get_test` "Testing history_admin merge (append to entry)"
	incr_micro

	for u in `head -10 /etc/passwd | awk '{FS=":"} {print $1}'`; do
		./test_history $opt_S -m $method -f $DBF -a 0 -d 0 \
			-p pass$u -u $u put > $SINK || \
				die `get_test` Populate $u failed
	done

	./history_admin -c /dev/null -m $method -f $DBF -a 0 -d 0 dump | \
		 sort > $SAVE
	first=`head -1 $SAVE`			# Pick first user in history
	whom=`echo $first | sed 's/:.*//'`	# Peel off user name

	before="`./history_admin -c /dev/null -m $method \
		-f $DBF -a 0 -d 0 dump | grep \"^${whom}:\"`"

	echo "$first" | ./history_admin -c /dev/null -m $method \
			-f $DBF -a 0 -d 0 $opt_V merge
	
	after="`./history_admin -c /dev/null -m $method \
		-f $DBF -a 0 -d 0 dump | grep \"^${whom}:\"`"

	if [ "$before" = "$after" ]; then
		msg "before: $before"
		msg "after: $after"
		error FAILED
		exit 1
	else
		msg `get_test` OK
	fi

	#
	# Test 2 - merge which adds new users
	#
	# Replicate each entry with a slightly munged username
	# Leave pristine copy of DB in $SAVE
	#
	msg `get_test` "Testing history_admin merge (adding entries)"
	./history_admin -c /dev/null -m $method -f $DBF -a 0 -d 0 \
		$opt_V load < $SAVE
	./history_admin -c /dev/null -m $method -f $DBF -a 0 -d 0 dump | \
		sed 's/^/U/' > $TEMP.1
	./history_admin -c /dev/null -m $method -f $DBF -a 0 -d 0 \
		$opt_V merge < $TEMP.1
	./history_admin -c /dev/null -m $method -f $DBF -a 0 -d 0 dump | \
		sort > $TEMP.1
	#
	# TEMP.1 should have 2x the lines of SAVE, and the count of
	# different lines should equal line count of SAVE
	# 
	td=`diff $SAVE $TEMP.1 | grep -c '^> '`
	od=`cat $SAVE | wc -l`
	if [ $od = $td ]; then
		msg `get_test` OK
	else
		error DB should have `expr $od \* 2` lines, has `wc -l $TEMP.1`
		msg `get_test` FAILED
	fi

	incr_micro
	msg `get_test` Testing history_admin database purge
	#
	# The records entered in the last 'merge' should be removed
	#
	./history_admin -c /dev/null -m $method -f $DBF -a 0 -d 0 $opt_V purge 
	./history_admin -c /dev/null -m $method -f $DBF -a 0 -d 0 dump | \
		 sort > $TEMP.1
	#
	# TEMP.1 and SAVE should be identical
	#
	if diff $SAVE $TEMP.1 > $TEMP.2; then
		msg `get_test` OK
	else
		spew $TEMP.2
		error FAILED
	fi
	rm -rf $TEMP.1 $TEMP.2 $TEMP.3 $TEMP.4

	[ $failures -gt 0 ] && die `get_test` Cannot continue
	msg $tn History put/get/merge/purge tests OK

set_minor 2
	t_age=30

	echo ""
	tn=`get_test`
	msg `get_test` Test culling of password history by age of entry
	#
	# Force the existing history entries to be 31 days old by
	# dumping the database, manipulating the timestamp
	# and loading the changed entries back into the database
	#
	incr_micro
	msg `get_test` Making existing entries 31 old
	back=`expr 86400 \* 31`

	./history_admin -m $method -f $DBF -a 0 -d 0 dump | \
		awk 'BEGIN { FS = ":" } {
		for (i = 1; i <= NF; i++) {
			c = index($i, ",");
			if (c) {
				pw = substr($i,1,c-1);
				tm = substr($i,c+1);
				tn = tm - '$back';
				printf("%s,%d:", pw,tn);
			} else {
				printf("%s:", $i);
			}
		 }
		print "";
	}' > $TEMP
	#
	# Don't put this at the end of the pipe - 
	# the dump & load use the same database.
	#
	./history_admin -m $method -f $DBF -a 0 -d 0 load < $TEMP || \
		die `get_test` Could not repopuate history
	msg `get_test` Done
	#
	# Add a new entry
	#
	msg `get_test` Adding a fresh entry
	./test_history $opt_S -m $method -f $DBF -a 0 -d 0 \
		-u $USER -p pass999 put > $SINK || \
			die `get_test` New password put failed
	#
	# Look for old passwords, which should not be found because
	# they are older than the threshold
	#
	incr_micro
	msg `get_test` These passwords should not be found "(too old)"
	ofailures=$failures
	for T in 1 2 3; do
		./test_history $opt_S -m $method -f $DBF -a $t_age -d $t_depth \
			-u $USER -p pass$T find && \
				error $T FAILED
	done
	#
	# Look for the new password just added -
	# should be found because it is young enough
	#
	incr_micro
	msg `get_test` This recent password should be found
	./test_history $opt_S -m $method -f $DBF -a $t_age -d $t_depth \
		-u $USER -p pass999 find || error FAILED

	msg $tn History age lookup tests OK

	incr_micro
	msg `get_test` Testing auto-removal of stale entries

	before=`./history_admin -m $method -f $DBF -a 0 -d 0 dump | grep $USER`
	./test_history $opt_S -m $method -f $DBF -a $t_age -d 0 \
		-u $USER -p pass998 put > $SINK || \
			die `get_test` New password put failed
	after=`./history_admin -m $method -f $DBF -a $t_age -d 0 dump |grep $USER`

	bcount=`echo "$before" | awk 'BEGIN {FS=":"} { print NF }'`
	acount=`echo "$after"  | awk 'BEGIN {FS=":"} { print NF }'`
	if $verbose; then
		echo before \"$before\" $bcount
		echo after \"$after\" $acount
	fi
	[ $bcount -le $acount ] && \
		error FAILED - after count "($acount)" not less than \
			before count "($bcount)"

	[ $failures = $ofailures ] && msg `get_test` OK
	[ $failures -gt 0 ] && die `get_test` Cannot continue
	msg $tn History aging tests OK

#
# Test depth management of history database entries
#
set_minor 3
	t_depth=1

	echo ""
	tn=`get_test`
	msg `get_test` Test history cull by depth

	./history_admin -m $method -f $DBF -a 0 -d 0 load < $SAVE || \
		die `get_test` Cannot repopulate history
	#
	# Look for passwords beyond the specifed depth
	#
	incr_micro
	ofailures=$failures
	msg `get_test` The next 2 passwords should not be found
#	echo '========================'
#	./history_admin -m $method -f $DBF   -d 0 -a 0 dump | sort
#	echo '========================'
	for T in 1 2; do
		./test_history $opt_S -m $method -f $DBF -d $t_depth \
			-u $USER -p pass$T find && error FAILED
		date
	done
	[ $failures = $ofailures ] && msg `get_test` OK

	#
	# Look for passwords within the specifed depth
	#
	incr_micro
	ofailures=$failures
	msg `get_test` The next 2 passwords should be found
	for T in 3 4; do
		./test_history $opt_S -m $method -f $DBF -d $t_depth \
			-u $USER -p pass$T find || error FAILED
	done
	[ $failures = $ofailures ] && msg `get_test` OK
	[ $failures -gt 0 ] && die `get_test` Cannot continue
	msg $tn History depth tests OK

echo ""
msg End history tests - $failures failures `date`
rm -f ${DBF}* ${TEMP}* $SAVE
exit $failures
#
# End TestHistory.sh
