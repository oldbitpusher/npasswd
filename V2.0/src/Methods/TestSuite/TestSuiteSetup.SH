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
echo "Extracting TestSuiteSetup.sh (with variable substitutions)"
: This section of the file will have variable substitutions done on it.
: Move anything that needs config subs from !NO!SUBS! section to !GROK!THIS!.
: Protect any dollar signs and backticks that you do not want interpreted
: by putting a backslash in front.  You may delete these comments.
$spitshell >TestSuiteSetup.sh <<!GROK!THIS!
#
# Variables needed from config.sh
#
if [ ! -f $TOP/config.sh ]; then
	echo Cannot find $TOP/config.sh
	exit 1
fi
. $TOP/config.sh

!GROK!THIS!

: In the following dollars and backticks do not need the extra backslash.
$spitshell >>TestSuiteSetup.sh <<'!NO!SUBS!'
#
# Library of shell routines for npasswd method module validation driver script
#
# @(#)TestSuiteSetup.SH	1.1 03/31/98 (cc.utexas.edu)
#
TestPasswd=etc_passwd

case "$p_shadow" in
	shm_shadow*)	authmode=sys5
			TestShadow=etc_shadow
			SysShadow=$p_shadowfile
			;;
	shm_adjunct*)	authmode=sun4
			TestShadow=etc_passwd.adjunct
			SysShadow=/etc/passwd.adjunct	## CONFIG
			;;
	shm_aix*)	authmode=aix
			TestShadow=etc_passwd.security
			SysShadow=/etc/security/passwd	## CONFIG
			;;
	shm_osf*)	authmode=osf ;;
	shm_hpux*)	authmode=hpux ;;
	*)		authmode=none ;;
esac

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
	sed 's/^/	/' $1
}

incr()
{
	eval "_tt=\$$1"
	_t=`expr $_tt + 1`
	eval "$1=\$_t"
}

set_test()
{
	TestNo=$1
	TestGroup=`echo $1 | sed 's/\..*//'`
}

#
# End TestSuiteSetup.SH
!NO!SUBS!
chmod 755 TestSuiteSetup.sh
$eunicefix TestSuiteSetup.sh
