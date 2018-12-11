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
 *	*** Do not modify this file directly - make changes to shadowtab.h.SH ***
 * @(#)shadowtab.h.SH	1.5 06/23/98 (cc.utexas.edu)
 */
struct passwd_files etc_shadow[] = {
/*	shadow		temp		old		lock	*/
#if	(CDEBUG >= CDEBUG_FILES)
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
