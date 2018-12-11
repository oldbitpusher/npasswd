h24581
s 00055/00058/00421
d D 1.5 98/10/13 13:59:43 clyde 5 4
c Major changes:
c 1. Add -v to history_admin if script run with -v
c 2. Add 2 tests for history_admin merge function
c 3. Change temp file usage
c 4. Build a bigger test database from /etc/passwd
e
s 00032/00006/00447
d D 1.4 98/10/01 10:39:06 clyde 4 3
c 1. Change 'append' to 'merge'
c 2. Add stanza to test merge with existing users
e
s 00082/00018/00371
d D 1.3 98/09/30 15:18:35 clyde 3 2
c 1. Use ./XXX for current directory executables
c 2. Test history_admin 'purge'
c 3. Test history_admin 'append'
e
s 00110/00101/00279
d D 1.2 98/06/23 10:47:34 clyde 2 1
c 1. Change parameters on test_history
c 2. Use history_admin to help testing
c 3. Add test stanza for history_admin
c 4. Fix inclusion of config.sh
c 5. Use and cleanup more temp files
e
s 00380/00000/00000
d D 1.1 98/06/04 08:42:44 clyde 1 0
c date and time created 98/06/04 08:42:44 by clyde
e
u
U
f e 0
t
T
I 1
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
# %W% %G% (cc.utexas.edu)
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
I 2

E 2
set_test()
{
	TestMajor=$1
	TestMinor=''
	TestMicro=''
}
I 2

E 2
get_test()
{
	r=$TestMajor
	[ -n "$TestMinor" ] && r="$r $TestMinor"
	[ -n "$TestMicro" ] && r="$r.$TestMicro"
	echo $r
}

I 2
set_minor()
{
	TestMinor=$1
	TestMicro=''
}

E 2
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
D 2
i_ndbm=define
E 2
I 2
# i_ndbm=define
if [ ../../config.sh ]; then
	.  ../../config.sh
else
	die Cannot find config.sh
fi
E 2
TEMP=/tmp/pwtest.$$
I 2
SAVE=/tmp/pwsave.$$
DBF=/tmp/histtemp,$$
rm -f $TEMP* $SAVE* $DBF*

E 2
opt_S='-s'
SINK=/dev/null
verbose=false
method=''
I 2
[ -z "$USER" ] && USER=nobody
E 2

while [ $# -gt 0 ]; do
	case "$1" in
	-v)	verbose=true
		SINK=/dev/tty
		[ -c /dev/stdout ] && SINK=/dev/stdout
		opt_S=''
I 5
		opt_V='-v'
E 5
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

D 2
PROGS="./test_history"
E 2
I 2
PROGS="./test_history ./history_admin"
E 2
for what in $PROGS; do
	[ ! -f $what ] && die The executable $what is missing - run make
done

D 2
#
# Test suite for the pasword history mechanism
#
if [ ../../config.sh ]; then
	.  ../../config.sh
else
	die Cannot find config.sh
fi
E 2

D 2
DBF=/tmp/histtemp,$$
E 2

D 2

E 2
set_test history-$method
#
# Testing history in flat password file
#
msg
msg Start history tests - database method \"$method\" `date`
msg
D 2
trap "rm -f ${DBF}* $TEMP; exit 1" 2 3 15
dbset="database $method $DBF;"
E 2
I 2
trap "rm -f ${DBF}* ${TEMP} ${SAVE}*; exit 1" 2 3 15
I 5
msg Test database = $DBF
E 5
E 2

D 2
incr_minor
E 2
I 2
set_minor 1
E 2
	failures=0
D 2
	t_depth=8
	t_age=0
E 2
I 2
	t_depth=0		# Disable history depth filter
	t_age=0			# Disable history age filter
E 2

	echo ""
	tn=`get_test`
	msg `get_test` Testing $method password history

	#
	# Test history database presence check
	#
	incr_micro
D 2
	rm -f ${DBF} ${DBF}.*
E 2
I 2
	rm -f ${DBF}*
E 2
	msg `get_test` Test should return '"No history database"'
D 2
	test_history $opt_S -c "$dbset" -A $t_age -D $t_depth \
		-u $USER -f put -p pass1 > $SINK
E 2
I 2
D 3
	test_history $opt_S -f $DBF -m $method -a $t_age -d $t_depth -u $USER \
E 3
I 3
	./test_history $opt_S -f $DBF -m $method -a $t_age -d $t_depth -u $USER \
E 3
		-p pass1 put > $SINK
E 2
	if [ $? -ne 2 ]; then
		die `get_test` FAILED
	else
		msg `get_test` OK
	fi
	#
	# Test of populating history database
	#
	incr_micro
D 2
	case $method in
	file)	cp /dev/null $DBF || exit 1
		;;
	dbm)	cp /dev/null ${DBF}.dir || exit 1
		cp /dev/null ${DBF}.pag || exit 1
		;;
	esac
E 2
I 2
	msg `get_test` Using history_admin to create empty history database 
	./history_admin -c /dev/null -m $method -f $DBF load < /dev/null
	if [ $? -ne 0 ]; then
		die `get_test` FAILED
	else
		msg `get_test` OK
	fi
E 2

I 2
	incr_micro
E 2
	msg `get_test` Populating history
D 2
	for T in 1 2 3; do
		sleep 1;
		test_history $opt_S -c "$dbset" -u $USER \
			-A $t_age -D $t_depth -f put -p pass$T \
				> $SINK || die `get_test` $T FAILED
E 2
I 2
	for T in 1 2 3 4; do
D 3
		test_history $opt_S -m $method -f $DBF -a $t_age -d $t_depth \
E 3
I 3
		./test_history $opt_S -m $method -f $DBF -a $t_age -d $t_depth \
E 3
			-p pass$T -u $USER put > $SINK || \
				die `get_test` $T FAILED
		sleep 2
E 2
	done
	msg `get_test` OK
	#
	# Fetch raw data from history database
	#
	incr_micro
	msg `get_test` Fetching history data
D 2
	test_history $opt_S -c "$dbset" -A $t_age -D $t_depth \
		-u $USER -f get > $SINK || die `get_test` FAILED
E 2
I 2
D 3
	test_history $opt_S -m $method -f $DBF -a $t_age -d $t_depth \
E 3
I 3
	./test_history $opt_S -m $method -f $DBF -a $t_age -d $t_depth \
E 3
		-u $USER get > $SINK || die `get_test` FAILED
E 2
	msg `get_test` OK
	#
	# Lookup passwords in history database
	#
	incr_micro
	msg `get_test` Looking for passwords in history
	ofailures=$failures
	for T in 1 2 3; do
D 2
		test_history $opt_S -c "$dbset" -A $t_age -D $t_depth\
			-u $USER -f find -p pass$T || error $T FAILED
E 2
I 2
D 3
		test_history $opt_S -m $method -f $DBF -a $t_age -d $t_depth \
E 3
I 3
		./test_history $opt_S -m $method -f $DBF -a $t_age -d $t_depth \
E 3
			-u $USER -p pass$T find || error $T FAILED
E 2
	done
D 2
	[ $failures = $ofailures ] && msg `get_test` OK
E 2
I 2
	#
	# Test dump/load function of history_admin
	#
	incr_micro
	msg `get_test` Testing history_admin dump and load

D 3
	history_admin -m $method -f $DBF   -d 0 -a 0 dump | sort > $DBF.0
	history_admin -m $method -f $DBF.1 -d 0 -a 0 load < $DBF.0
	history_admin -m $method -f $DBF.1 -d 0 -a 0 dump | sort > $DBF.2
E 3
I 3
	./history_admin -m $method -f $DBF   -d 0 -a 0 dump | sort > $DBF.0
D 5
	./history_admin -m $method -f $DBF.1 -d 0 -a 0 load < $DBF.0
E 5
I 5
	./history_admin -m $method -f $DBF.1 -d 0 -a 0 $opt_V load < $DBF.0
E 5
	./history_admin -m $method -f $DBF.1 -d 0 -a 0 dump | sort > $DBF.2
E 3
	if diff $DBF.0 $DBF.2 > $DBF.3 ; then
		msg `get_test` OK
	else
I 5
		spew $DBF.3
E 5
D 3
		spew
E 3
		error FAILED
	fi
	rm -f $DBF.0 $DBF.1 $DBF.2 $DBF.3
I 3

	incr_micro
D 4
	msg `get_test` Testing history_admin database append
E 4
I 4
D 5
	msg `get_test` Testing history_admin database merge 1
E 5
I 5

E 5
E 4
	#
I 4
D 5
	# Test 1 - merges with new usernames
E 5
I 5
	# Test 1 - merge which adds data to existing user
E 5
	#
E 4
D 5
	# Replicate each DB entry with a slightly munged username
	#
	./history_admin -c /dev/null -m $method -f $DBF -a 0 -d 0 dump | \
		 sort | tee $TEMP.1 | sed 's/^/U/' > $TEMP.2
D 4
	./history_admin -c /dev/null -m $method -f $DBF -a 0 -d 0 append < $TEMP.2
E 4
I 4
	./history_admin -c /dev/null -m $method -f $DBF -a 0 -d 0 merge < $TEMP.2
E 4
	rm -f $TEMP.2
	./history_admin -c /dev/null -m $method -f $DBF -a 0 -d 0 dump | \
		 sort > $TEMP.2
	#
	# TEMP2 should have 2x the lines of TEMP2, and the count of
	# different lines should equal line count of TEMP2
	# 
	td=`diff $TEMP.1 $TEMP.2 | grep -c '^> '`
	od=`cat $TEMP.1 | wc -l`
	if [ $od = $td ]; then
		msg `get_test` OK
	else
		error DB should have `expr $od \* 2` lines, has `wc -l $TEMP.2`
D 4
		msg `get_test` History append test FAILED
E 4
I 4
		msg `get_test` FAILED
E 4
	fi
I 4
	#
	# Test 2 - merges for existing users
	#
	msg `get_test` Testing history_admin database merge 2
E 5
I 5
	msg `get_test` "Testing history_admin merge (append to entry)"
E 5
	incr_micro
D 5
	one=`head -1 $TEMP.1`
	two=`expr "$one" : '.*:\(.*\)'`
	whom=`echo $one | sed 's/:.*//'`
E 5
E 4

I 5
	for u in `head -10 /etc/passwd | awk '{FS=":"} {print $1}'`; do
		./test_history $opt_S -m $method -f $DBF -a 0 -d 0 \
			-p pass$u -u $u put > $SINK || \
				die `get_test` Populate $u failed
	done

	./history_admin -c /dev/null -m $method -f $DBF -a 0 -d 0 dump | \
		 sort > $SAVE
	first=`head -1 $SAVE`			# Pick first user in history
	whom=`echo $first | sed 's/:.*//'`	# Peel off user name

E 5
I 4
	before="`./history_admin -c /dev/null -m $method \
		-f $DBF -a 0 -d 0 dump | grep \"^${whom}:\"`"

D 5
	echo $one:$two | ./history_admin -c /dev/null -m $method \
		-f $DBF -a 0 -d 0 merge
E 5
I 5
	echo "$first" | ./history_admin -c /dev/null -m $method \
			-f $DBF -a 0 -d 0 $opt_V merge
E 5
	
	after="`./history_admin -c /dev/null -m $method \
		-f $DBF -a 0 -d 0 dump | grep \"^${whom}:\"`"
I 5

E 5
	if [ "$before" = "$after" ]; then
		msg "before: $before"
		msg "after: $after"
		error FAILED
I 5
		exit 1
E 5
	else
		msg `get_test` OK
	fi

E 4
D 5
	incr_micro
	msg `get_test` Testing history_admin database purge
E 5
	#
D 5
	# Populate the database with multiple users from the real
	# password file
E 5
I 5
	# Test 2 - merge which adds new users
E 5
	#
D 5
	./history_admin -c /dev/null -m $method -f $DBF -a 0 -d 0 load < /dev/null
	for u in `head -10 /etc/passwd | awk '{FS=":"} {print $1}'`; do
		./test_history $opt_S -m $method -f $DBF -a 0 -d 0 \
			-p pass$u -u $u put > $SINK || \
				die `get_test` Populate $u failed
	done
E 5
I 5
	# Replicate each entry with a slightly munged username
	# Leave pristine copy of DB in $SAVE
	#
	msg `get_test` "Testing history_admin merge (adding entries)"
	./history_admin -c /dev/null -m $method -f $DBF -a 0 -d 0 \
		$opt_V load < $SAVE
E 5
	./history_admin -c /dev/null -m $method -f $DBF -a 0 -d 0 dump | \
D 5
		 sort > $TEMP.2
E 5
I 5
		sed 's/^/U/' > $TEMP.1
	./history_admin -c /dev/null -m $method -f $DBF -a 0 -d 0 \
		$opt_V merge < $TEMP.1
	./history_admin -c /dev/null -m $method -f $DBF -a 0 -d 0 dump | \
		sort > $TEMP.1
E 5
	#
D 5
	# Add dups of users with bogus login names
E 5
I 5
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
E 5
	#
D 5
	sed 's/^/Z/' $TEMP.2 | \
D 4
		./history_admin -c /dev/null -m $method -f $DBF -a 0 -d 0 append 
E 4
I 4
		./history_admin -c /dev/null -m $method -f $DBF -a 0 -d 0 merge 
E 5
I 5
	# The records entered in the last 'merge' should be removed
E 5
E 4
	#
D 5
	# The records entered above should be removed
	#
	./history_admin -c /dev/null -m $method -f $DBF -a 0 -d 0 purge 
E 5
I 5
	./history_admin -c /dev/null -m $method -f $DBF -a 0 -d 0 $opt_V purge 
E 5
	./history_admin -c /dev/null -m $method -f $DBF -a 0 -d 0 dump | \
D 5
		 sort > $TEMP.3
E 5
I 5
		 sort > $TEMP.1
E 5
	#
D 5
	# TEMP.2 and TEMP.3 should be identical
E 5
I 5
	# TEMP.1 and SAVE should be identical
E 5
	#
D 5
	if diff $TEMP.2 $TEMP.3 > $TEMP.4; then
E 5
I 5
	if diff $SAVE $TEMP.1 > $TEMP.2; then
E 5
		msg `get_test` OK
	else
D 5
		spew $TEMP.4
E 5
I 5
		spew $TEMP.2
E 5
D 4
		error History purge test FAILED
E 4
I 4
		error FAILED
E 4
	fi
D 5
	#
	# Put database back the way it was - the following tests need it
	#
	./history_admin -c /dev/null -m $method -f $DBF -a 0 -d 0 load < $TEMP.1
E 5
	rm -rf $TEMP.1 $TEMP.2 $TEMP.3 $TEMP.4

E 3
E 2
	[ $failures -gt 0 ] && die `get_test` Cannot continue
D 3
	msg $tn History put/get tests OK
E 3
I 3
D 4
	msg $tn History put/get/append/purge tests OK
E 4
I 4
	msg $tn History put/get/merge/purge tests OK
E 4
E 3

D 2
#
# Test aging of history database entries
#
if [ $method != file ]; then
	msg Tests for method \"$method\" done
	msg End pwck_history test - $failures failures `date`
	rm -f ${DBF}* $TEMP
	exit $failures
fi

echo ""
msg This section tests the method-independent history aging support
echo ""

incr_minor
	t_depth=8
E 2
I 2
set_minor 2
E 2
	t_age=30

	echo ""
	tn=`get_test`
D 2
	msg `get_test` Test history aging
E 2
I 2
	msg `get_test` Test culling of password history by age of entry
E 2
	#
D 2
	# Force all the history entries to be 31 days old
E 2
I 2
	# Force the existing history entries to be 31 days old by
	# dumping the database, manipulating the timestamp
	# and loading the changed entries back into the database
E 2
	#
D 2
	$verbose && msg `get_test` Making existing entries 31 old
E 2
I 2
	incr_micro
	msg `get_test` Making existing entries 31 old
E 2
	back=`expr 86400 \* 31`
D 2
	tail -1 $DBF | awk 'BEGIN { FS = ":" } {
E 2
I 2

D 5
	./history_admin -m $method -f $DBF -a 0 -d 0 dump | tee $SAVE | \
E 5
I 5
	./history_admin -m $method -f $DBF -a 0 -d 0 dump | \
E 5
		awk 'BEGIN { FS = ":" } {
E 2
		for (i = 1; i <= NF; i++) {
			c = index($i, ",");
			if (c) {
				pw = substr($i,1,c-1);
				tm = substr($i,c+1);
				tn = tm - '$back';
D 2
				printf("%s,%s:", pw,tn);
E 2
I 2
				printf("%s,%d:", pw,tn);
E 2
			} else {
				printf("%s:", $i);
			}
		 }
		print "";
	}' > $TEMP
D 2
	mv $TEMP $DBF
E 2
	#
I 2
	# Don't put this at the end of the pipe - 
	# the dump & load use the same database.
	#
	./history_admin -m $method -f $DBF -a 0 -d 0 load < $TEMP || \
		die `get_test` Could not repopuate history
	msg `get_test` Done
	#
E 2
	# Add a new entry
	#
D 2
	$verbose && msg `get_test` Adding fresh entry
	test_history $opt_S -c "$dbset" -A 0 -D 0 \
		-u $USER -f put -p pass999 > $SINK || \
E 2
I 2
	msg `get_test` Adding a fresh entry
D 3
	test_history $opt_S -m $method -f $DBF -a 0 -d 0 \
E 3
I 3
	./test_history $opt_S -m $method -f $DBF -a 0 -d 0 \
E 3
		-u $USER -p pass999 put > $SINK || \
E 2
			die `get_test` New password put failed
	#
D 2
	# Look for old passwords
E 2
I 2
	# Look for old passwords, which should not be found because
	# they are older than the threshold
E 2
	#
	incr_micro
D 2
	$verbose && msg `get_test` Looking for an old password
	msg `get_test` These passwords should not be found
E 2
I 2
	msg `get_test` These passwords should not be found "(too old)"
E 2
	ofailures=$failures
	for T in 1 2 3; do
D 2
		test_history $opt_S -c "$dbset" -A $t_age -D $t_depth \
			-u $USER -f find -p pass$T && \
E 2
I 2
D 3
		test_history $opt_S -m $method -f $DBF -a $t_age -d $t_depth \
E 3
I 3
		./test_history $opt_S -m $method -f $DBF -a $t_age -d $t_depth \
E 3
			-u $USER -p pass$T find && \
E 2
				error $T FAILED
	done
	#
D 2
	# Look for new passwords
E 2
I 2
	# Look for the new password just added -
	# should be found because it is young enough
E 2
	#
	incr_micro
D 2
	$verbose && msg `get_test` Looking for the recent password
	msg `get_test` This password should be found
	test_history $opt_S -c "$dbset" -A $t_age -D $t_depth \
		-u $USER -f find -p pass999 || error FAILED
E 2
I 2
	msg `get_test` This recent password should be found
D 3
	test_history $opt_S -m $method -f $DBF -a $t_age -d $t_depth \
E 3
I 3
	./test_history $opt_S -m $method -f $DBF -a $t_age -d $t_depth \
E 3
		-u $USER -p pass999 find || error FAILED
E 2

	msg $tn History age lookup tests OK
D 2
	#
	# Test history truncation by age
	#
E 2
I 2

E 2
	incr_micro
D 2
	msg `get_test` Testing history truncation by age
E 2
I 2
	msg `get_test` Testing auto-removal of stale entries
E 2

D 2
	$verbose && msg `get_test` Adding entry to trigger history age clean
	before=`test_history -s -c "$dbset" -A 0 -D 0 -u $USER -f get`
	test_history $opt_S -c "$dbset" -A $t_age -D 0 \
		-u $USER -f put -p pass998 > $SINK || \
E 2
I 2
D 3
	before=`history_admin -m $method -f $DBF -a 0 -d 0 dump | grep $USER`
	test_history $opt_S -m $method -f $DBF -a $t_age -d 0 \
E 3
I 3
	before=`./history_admin -m $method -f $DBF -a 0 -d 0 dump | grep $USER`
	./test_history $opt_S -m $method -f $DBF -a $t_age -d 0 \
E 3
		-u $USER -p pass998 put > $SINK || \
E 2
			die `get_test` New password put failed
D 2
	after=`test_history -s -c "$dbset" -A $t_age -D 0 -u $USER -f get`
E 2
I 2
D 3
	after=`history_admin -m $method -f $DBF -a $t_age -d 0 dump |grep $USER`
E 3
I 3
	after=`./history_admin -m $method -f $DBF -a $t_age -d 0 dump |grep $USER`
E 3
E 2

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
I 2
	msg $tn History aging tests OK
E 2

#
# Test depth management of history database entries
#
D 2
incr_minor
E 2
I 2
set_minor 3
	t_depth=2

E 2
	echo ""
	tn=`get_test`
D 2
	msg `get_test` Test history depth
E 2
I 2
	msg `get_test` Test history cull by depth
E 2

D 2
	t_depth=2

	incr_micro
	msg `get_test` Populating history
	cp /dev/null $DBF
	for T in 1 2 3 4; do
		sleep 1;
		test_history $opt_S -c "$dbset" -D 0 -u $USER \
			-f put -p pass$T > $SINK || die `get_test` $T FAILED
	done
	msg `get_test` OK

E 2
I 2
	./history_admin -m $method -f $DBF -a 0 -d 0 load < $SAVE || \
		die `get_test` Cannot repopulate history
E 2
	#
	# Look for passwords beyond the specifed depth
	#
	incr_micro
	ofailures=$failures
	msg `get_test` The next 2 passwords should not be found
	for T in 1 2; do
D 2
		test_history $opt_S -c "$dbset" -D $t_depth \
			-u $USER -f find -p pass$T && error FAILED
E 2
I 2
D 3
		test_history $opt_S -m $method -f $DBF -d $t_depth \
E 3
I 3
		./test_history $opt_S -m $method -f $DBF -d $t_depth \
E 3
			-u $USER -p pass$T find && error FAILED
E 2
	done
	[ $failures = $ofailures ] && msg `get_test` OK

	#
	# Look for passwords within the specifed depth
	#
	incr_micro
	ofailures=$failures
	msg `get_test` The next 2 passwords should be found
	for T in 3 4; do
D 2
		test_history $opt_S -c "$dbset" -D $t_depth \
			-u $USER -f find -p pass$T || error FAILED
E 2
I 2
D 3
		test_history $opt_S -m $method -f $DBF -d $t_depth \
E 3
I 3
		./test_history $opt_S -m $method -f $DBF -d $t_depth \
E 3
			-u $USER -p pass$T find || error FAILED
E 2
	done
	[ $failures = $ofailures ] && msg `get_test` OK
	[ $failures -gt 0 ] && die `get_test` Cannot continue
	msg $tn History depth tests OK

echo ""
D 2
msg End pwck_history test - $failures failures `date`
rm -f ${DBF}* $TEMP
E 2
I 2
msg End history tests - $failures failures `date`
D 3
rm -f ${DBF}* $TEMP $SAVE
E 3
I 3
rm -f ${DBF}* ${TEMP}* $SAVE
E 3
E 2
exit $failures
#
# End %M%
E 1
