h60737
s 00180/00000/00000
d D 1.1 98/03/31 13:20:36 clyde 1 0
c date and time created 98/03/31 13:20:36 by clyde
e
u
U
f e 0
t
T
I 1
#!/bin/sh
#
# Test npasswd password database access methods
# This script tests the lookup functions
#
# %W% %G% (cc.utexas.edu)
#
# Usage: %M% [test group #]
#
. ./t_setup.sh

TEMP=/tmp/gutmp$$
trap "rm -f $TEMP; exit 1" 2 3
trap "rm -f $TEMP; exit 0" 0

PROG=getuser
[ ! -x $PROG ] && die Test program $PROG missing

#
# Test group 1: lookup in local password
#	1.1) user in test passwd
#	1.2) user in system passwd
#
(
failures=0
TestUser=joeblow
set_test "1.1"
[ -n "$1" -a "$1" != $TestGroup ] && exit 0
msg Test group $TestGroup: Lookups in local passwd files
msg Test $TestNo: Lookup username '"'$TestUser'"' in dummy passwd file
if $PROG -S local $TestUser > $TEMP; then
	msg Test $TestNo OK
else
	msg Test $TestNo FAILED
	spew $TEMP
	incr failures
fi
echo ""

test_user=`tail -5 /etc/passwd | head -1 | tr ':' ' ' | awk '{ print $1 }'`
user_pw=`grep "^$test_user" /etc/passwd | tr ':' ' ' | awk '{ print $2 }'`
pwlen=`expr "$user_pw" : '.*'`

#
# Test lookup of user in system password database
#
# The setup is elaborate becuase of the shadow databases.
# A user is selected at random from the password file.
# If that user appears to have a shadow password, expect that
# this test will fail unless run as root.
#
set_test "1.2"
msg Test $TestNo: Lookup of '"'$test_user'"' in system password/shadow file
fail_ok=''
shpw=''
uid=`id -u 2>/dev/null`
if [ $pwlen -lt 13 ]; then
	msg '"'$test_user'"' probably has a shadow password
	shpw=1
fi
case $authmode in
	sun4)	case $user_pw in
		\#\#*)	msg Cannot read adjunct file - This test should fail.
			fail_ok=1
			;;
		esac
		;;
	sys5)	if [ -n "$shpw" -a ! -r "$SysShadow" ]; then
			msg Cannot read shadow file - This test should fail.
			fail_ok=1
		fi
		;;
	aix)	if [ -n "$shpw" -a ! -r /etc/security/passwd ]; then
			msg Cannot read shadow file - This test should fail.
			fail_ok=1
		fi
		;;
	osf1)	if [ -d /tcb/files/auth ]; then
			msg Cannot read auth database - This test may fail.
			fail_ok=1
		fi
		;;
esac
$PROG $test_user >$TEMP
case $? in
	0)	if [ -n "$fail_ok" ]; then
			msg Test $TestNo unexpectedly OK!
			spew $TEMP
		else 
			msg Test $TestNo OK
		fi
		;;
	*)	if [ -n "$fail_ok" ]; then
			msg Test $TestNo failed as expected.
			msg Run as root to have the test succeed.
		else
			msg Test $TestNo FAILED
			spew $TEMP
			incr failures
		fi
		;;
esac
msg Test group $TestGroup: $failures failures
echo ""
rm -f $TEMP
)
#
# Test group 2: NIS tests
#	2.1.X) lookup user in NIS maps
#
(
failures=0
set_test 2.0
[ -n "$1" -a "$1" != $TestGroup ] && exit 0
msg Test group $TestGroup: Lookups via NIS/YP
if ypwhich -m passwd.byname >/dev/null 2>&1; then
	##if [ "$p_nis" != "$define" ]; then
 	##	die $TestGroup aborted - NIS support not configured
 	##fi
	test_users=`ypcat passwd.byname | tail -10 | head -5 |\
		 tr ':' ' ' | awk '{ print $1 }'`
	set_test 2.1
	xtest=1
	for u in $test_users; do
		msg Test $TestNo.$xtest: Lookup of '"'$u'"' in NIS
		if $PROG -S nis $u >$TEMP; then
			msg Test $TestNo.$xtest OK
		else
			msg Test $TestNo.$xtest FAILED
			spew $TEMP
			incr failures
		fi
		incr xtest
	done
else
	die NIS not active
fi
msg Test group $TestGroup: $failures failures
rm -f $TEMP
)

#
# Test group 3: NIS+ tests
#	3.1.X) lookup user in NIS+ maps
#
(
failures=0
set_test 3.0
[ -n "$1" -a "$1" != $TestGroup ] && exit 0
msg Test group $TestGroup: Lookups via NIS+
if nisls passwd.org_dir >/dev/null 2>&1 ; then
	##if [ "$p_nisplus" != "$define" ]; then
 	##	die $TestGroup aborted - NIS+ support not configured
 	##fi
	test_users=`niscat passwd.org_dir | tail -10 | head -5 |\
		 tr ':' ' ' | awk '{ print $1 }'`
	set_test 3.1
	xtest=1
	for u in $test_users; do
		msg Test $TestNo.$xtest: Lookup of user '"'$u'"' in NIS+
		if $PROG -S nisplus $u >$TEMP; then
			msg Test $TestNo.$xtest OK
		else
			msg Test $TestNo.$xtest FAILED
			spew $TEMP
			incr failures
		fi
		incr xtest
	done
else
	die NIS+ not active
fi
msg Test group $TestGroup: $failures failures
rm -f $TEMP
)
echo ""
msg All tests done
exit 0
#
# End %M%
E 1
