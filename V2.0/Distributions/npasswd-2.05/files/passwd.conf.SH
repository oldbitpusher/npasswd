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

echo "Extracting passwd.conf (with variable substitutions)"

$spitshell > passwd.conf <<'!NO!SUBS!'
#
# Example npasswd configuration file.
#
# See ../doc/Reference.html for details.
#
# @(#)passwd.conf.SH	1.6 09/16/98 (cc.utexas.edu)
#
# Npasswd is a part of the system security infrastructure, and so will not
# accept an insecure or faulty master configuration file. This file must
# be owned by root (if npasswd does not run setuid root, then the
# configuration file must be owned by that uid), and *not* be world-writable.
# 
# Lines starting with "#" (such as this one) and blank lines are ignored.
# 
# Npasswd will abort if a syntax error is encountered in this file. 
# 
# The syntax of a configuration file can be testing by using the -XC option.
# 
# Npasswd is in essence three related programs: passwd, chfn and chsh. Each of
# these sub-programs have distinct functionality and separate configuration
# directives. There are also global directives.
# 
# Configuration directives are of the form
# 
#      sub-program.option<space>value
# 
#      sub-program.
#           Is one of passwd, chfn, chsh, or empty. A non-empty sub-program
#           name must be followed by a period.
#      option
#           Option name.
#      <space>
#           One or more whitespace characters.
#      value
#           Value for option.
# 
# There are the following data types for option values:
# 
#      number
#           May be decimal, octal (syntax 0NNN) or hex (syntax 0xNNNN), and
#           have a leading minus sign to indicate a negative value.
#      path
#           A UNIX pathname.
#      boolean
#           One of the strings "1", "true" "yes" or "on". Any other value is
#           interpreted as "false".
#      string
#           Strings can be optionally enclosed in single (') or double (")
#           quotes.
#           Non-printable ASCII characters can specified was follows:
#         * ^<caret>char" e.g. ^X for control-x.
#         * "\<backslash>char" for C special characters (\b \f \h \n \r \t
#           \\).
#         * "\0xNNN" where NNN is the character value in hex.
#         * "\0NNN" where NNN is the character value in octal.
# ----------------------------------------------------------------------------
# 
#  Configuration directives
# 
# Directive		Value	Description
#			type
# 
# PasswdTolerance	number	Tolerance between old and new passwd files
# ShadowTolerance	number	Tolerance between old and new shadow files
# MatchTries		number	Chances to give user to correctly
#				enter a password
# MatchWait		number	Delay after the user enters an
#				incorrect password
#
#	Directives for sub-program passwd
#
# passwd.AlphaOnly	boolean	Allow alpha-only passwords
# passwd.CharClasses	number	Minimum number of character classes required
# passwd.Dictionaries	path	Password check dictionaries location
# passwd.DisallowedChars string	Change list of non-allowed characters
# passwd.Help 		path	Help file for passwd
# passwd.History age	number	Password history age
# passwd.History dbm	path 	Set path to history db (DBM database)
# passwd.History depth	number	How many password to keep per user
# passwd.History file	path 	Set path to history db (flat file)
# passwd.History none 		Disable password history
# passwd.LengthWarn	boolean	Warn about passwords over MaxPassword length
# passwd.MaxPassword	number	Maximum effective password length
# passwd.MaxRepeat	number	How many repeated characters allowed 
# passwd.Message	path	Message of the day file for passwd
# passwd.MinPassword	number	Minimum password length
# passwd.PasswordChecks	string	Choose password check functions
# passwd.PrintableOnly	boolean	Deny non-printable characters in passwords
# passwd.Singlecase	boolean	Allow single-case passwords
# passwd.WhiteSpace	boolean	Deny whitespace characters in passwords
#
#	Directives for sub-program chfn
#
# chfn.Help		path	Help file for chfn
# chfn.Message		path	Message of the day
#
#	Directives for sub-program chsh
#
# chsh.Help		path	Help file for chsh
# chsh.Message		path	Message of the day
# chsh.Shells		path	List of blessed shells
# 
!NO!SUBS!
$spitshell >> passwd.conf <<!GROK!THIS!
#
# Password check dictionaries
#
# passwd.Dictionaries	$p_dictlib
#
!GROK!THIS!

chmod 644 passwd.conf
$eunicefix passwd.conf
