h33100
s 00001/00001/00065
d D 1.5 98/06/23 10:57:52 clyde 5 4
c Change compile-time debug include trigger
e
s 00001/00001/00065
d D 1.4 98/04/28 16:48:49 clyde 4 3
c Change LOCAL_FILES to DEBUG_LOCAL_FILES
e
s 00001/00001/00065
d D 1.3 96/08/14 17:20:40 clyde 3 2
c Change LOCAL_TEST_FILES to LOCAL_FILES
e
s 00001/00001/00065
d D 1.2 96/08/06 14:14:27 clyde 2 1
c beta 3 cycle 1 checkin
e
s 00066/00000/00000
d D 1.1 95/04/05 16:26:59 clyde 1 0
c date and time created 95/04/05 16:26:59 by clyde
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
echo "Extracting shadowtab.h (with variable substitutions)"

: In the following dollars and backticks do not need the extra backslash.
$spitshell >shadowtab.h <<'!NO!SUBS!'
/*
 * shadowtab.h - list of possible locations for the shadow file
 *	*** Do not modify this file directly - make changes to %M% ***
 * %W% %G% (cc.utexas.edu)
 */
struct passwd_files etc_shadow[] = {
/*	shadow		temp		old		lock	*/
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
	{ "./etc_shadow", "./etc_stmp", "./etc_oshadow", 0 },
#endif
#ifdef	XSHADOW_FILE
	{ XSHADOW_FILE, XSHADOW_TEMP, XSHADOW_SAVE, 0 },
#endif
!NO!SUBS!

for shf in $p_shadowfile; do
	shfile=`basename $shf`
	shpath=`echo $shf | sed 's@/'$shfile'$@@'`
	case $shpath in
		/etc)	TMP=$shpath/stmp
			OLD=$shpath/o${shfile}
			;;

		/etc/security)
			TMP=$shpath/ptmpa
			OLD=$shpath/o${shfile}
			;;

		*)	TMP=${shf}.tmp
			OLD=${shpath}/o${shfile}
			;;
	esac
	$spitshell >>shadowtab.h <<EOF

	/* Shadow file $shf */
	{ "$shf", "$TMP", "$OLD", 0 },
EOF
done

$spitshell >> shadowtab.h <<EOF
	{ 0 }
};
/* End shadowtab.h */
EOF
E 1
