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
echo "Extracting docfilter (with variable substitutions)"
$spitshell >docfilter <<!GROK!THIS!
$startsh
#
# docfilter - replace pathname tokens in documentation files
#
# @(#)docfilter.SH	1.4 07/16/98 (cc.utexas.edu)
#
sed 	-e "s!@NPASSWD-HOME@!$p_installdir!g" \\
	-e "s!@NPASSWD-DOCS@!$p_docdir!g" \\
	-e "s!@NPASSWD-DICT@!$p_dictionaries!g" \\
	-e "s!@NPASSWD-HIST@!$p_history!g" \\
	-e "s!@NPASSWD-XBIN@!$p_keepdir!g" \\
	-e "s!@NPASSWD-UTIL@!$p_utildir!g" \\
	-e "s!@NPASSWD-SRC@!$top_level!g" \$*
exit 0
#
# End docfilter.SH
!GROK!THIS!
chmod 755 docfilter
$eunicefix docfilter
