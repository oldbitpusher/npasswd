h57219
s 00005/00003/00034
d D 1.4 98/07/16 09:12:49 clyde 4 3
c Update path tokens
e
s 00001/00001/00036
d D 1.3 98/07/09 08:43:49 clyde 3 2
c Change DICTS to DICT
e
s 00002/00001/00035
d D 1.2 98/07/08 16:46:05 clyde 2 1
c Working version 2
e
s 00036/00000/00000
d D 1.1 98/07/08 09:31:56 clyde 1 0
c date and time created 98/07/08 09:31:56 by clyde
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
echo "Extracting docfilter (with variable substitutions)"
$spitshell >docfilter <<!GROK!THIS!
$startsh
#
# docfilter - replace pathname tokens in documentation files
#
# %W% %G% (cc.utexas.edu)
#
D 4
sed 	-e "s!@NPASSWD-LIB@!$privlibexp!g" \\
D 3
	-e "s!@NPASSWD-DICTS@!$p_dictlib!g" \\
E 3
I 3
	-e "s!@NPASSWD-DICT@!$p_dictlib!g" \\
E 3
I 2
	-e "s!@NPASSWD-HIST@!$o_pwhDB!g" \\
E 4
I 4
sed 	-e "s!@NPASSWD-HOME@!$p_installdir!g" \\
	-e "s!@NPASSWD-DOCS@!$p_docdir!g" \\
	-e "s!@NPASSWD-DICT@!$p_dictionaries!g" \\
	-e "s!@NPASSWD-HIST@!$p_history!g" \\
E 4
E 2
	-e "s!@NPASSWD-XBIN@!$p_keepdir!g" \\
I 4
	-e "s!@NPASSWD-UTIL@!$p_utildir!g" \\
E 4
D 2
	-e "s!@NPASSWD-SRC@!$top_level!g" $*
E 2
I 2
	-e "s!@NPASSWD-SRC@!$top_level!g" \$*
E 2
exit 0
#
# End %M%
!GROK!THIS!
chmod 755 docfilter
$eunicefix docfilter
E 1
