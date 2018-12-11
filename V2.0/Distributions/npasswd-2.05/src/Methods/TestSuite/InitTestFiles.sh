#!/bin/sh
#
# Script to setup local test files for method tests
#
# @(#)InitTestFiles.sh	1.1 03/31/98 (cc.utexas.edu)
#
. ./TestSuiteSetup.sh

case "$authmode" in
aix)
	sed 's/--/!/' files/etc_passwd.sys5 > $TestPasswd
	msg Made AIX passwd - shadow testing not available
	;;
sys5)
	rm -f $TestPasswd $TestShadow
	sed 's/--/x/' files/etc_passwd.sys5 > $TestPasswd
	cp files/etc_shadow.sys5 $TestShadow
	msg Made System5 passwd
	;;
sun4)
	rm -f $TestPasswd $TestShadow
	cp files/etc_passwd.sun4 $TestPasswd
	cp files/etc_shadow.sun4 $TestShadow
	msg Made SunOS4 adjunct passwd
	;;
osf)
	cp files/etc_passwd.v7 $TestPasswd
	msg Made OSF passwd
	;;
hpux)
	;;
*)
	cp files/etc_passwd.v7 etc_passwd
	msg Made classic passwd
	;;
esac
exit 0
#
# End InitTestFiles.sh

