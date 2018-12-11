#
# Variables needed from config.sh
#
if [ ! -f /config.sh ]; then
	echo Cannot find /config.sh
	exit 1
fi
. /config.sh

#
# Library of shell routines for npasswd method module validation driver script
#
# %W% %G% (cc.utexas.edu)
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
# End %M%
