h46089
s 00001/00001/00068
d D 1.5 98/06/23 10:57:39 clyde 5 4
c Change compile-time debug include trigger
e
s 00001/00001/00068
d D 1.4 98/04/28 16:48:40 clyde 4 3
c Change LOCAL_FILES to DEBUG_LOCAL_FILES
e
s 00001/00001/00068
d D 1.3 96/08/14 17:20:41 clyde 3 2
c Change LOCAL_TEST_FILES to LOCAL_FILES
e
s 00002/00002/00067
d D 1.2 96/08/06 14:14:18 clyde 2 1
c beta 3 cycle 1 checkin
e
s 00069/00000/00000
d D 1.1 95/04/05 16:26:58 clyde 1 0
c date and time created 95/04/05 16:26:58 by clyde
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
echo "Extracting passwdtab.h (with variable substitutions)"

: In the following dollars and backticks do not need the extra backslash.
$spitshell >passwdtab.h <<'!NO!SUBS!'
/*
 * passwdtab.h - list of possible locations for the password file
 *	*** Do not modify this file directly - make changes to %M% ***
 * %W% %G% (cc.utexas.edu)
 */
struct passwd_files etc_passwd[] = {
/*	passwd		temp		old		lock	*/
D 2
#ifdef	DEBUG_FILES
E 2
I 2
D 3
#ifdef	LOCAL_TEST_FILES
E 3
I 3
D 4
#ifdef	LOCAL_FILES
E 4
I 4
D 5
#ifdef	DEBUG_LOCAL_FILES
E 5
I 5
#if	(CDEBUG >= CDEBUG_FILES)
E 5
E 4
E 3
E 2
	{ "./etc_passwd", "./etc_ptmp", "./etc_opasswd", "./passwd_lock" },
#endif
#ifdef	XPASSWD_FILE
	{ XPASSWD_FILE, XPASSWD_TEMP, XPASSWD_SAVE, XPASSWD_LOCK },
#endif
!NO!SUBS!

for pwf in $p_passwdfile; do
	pwfile=`basename $pwf`
	pwpath=`echo $pwf | sed 's@/'$pwfile'$@@'`
	case $pwpath in
		/etc)	TMP=/etc/ptmp
			# Need another lock file if this is SunOS 4
			case "$p_osName" in
			sunos_4*) LCK=/etc/${pwfile}.ptmp ;;
			esac
			OLD=/etc/o${pwfile}
			;;

		*)	TMP=${pwf}.tmp
			LCK=/etc/ptmp
			OLD=${pwpath}/o${pwfile}
			;;
	esac
	[ -n "$LCK" ] && LCK='"'$LCK'"'
	[ -z "$LCK" ] && LCK=0
	$spitshell >> passwdtab.h <<EOF

	/* Password file $pwf */
	{ "$pwf", "$TMP", "$OLD", $LCK },
EOF
done

$spitshell >> passwdtab.h <<"!NO!SUBS!"
	{ 0 }
};
/* End passwdtab.h */
!NO!SUBS!
D 2
exit 0
E 2
I 2
# exit 0
E 2
E 1
