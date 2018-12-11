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
 *	*** Do not modify this file directly - make changes to passwdtab.h.SH ***
 * @(#)passwdtab.h.SH	1.5 06/23/98 (cc.utexas.edu)
 */
struct passwd_files etc_passwd[] = {
/*	passwd		temp		old		lock	*/
#if	(CDEBUG >= CDEBUG_FILES)
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
# exit 0
