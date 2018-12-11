h37141
s 00001/00001/00134
d D 1.6 98/09/16 14:43:53 clyde 6 5
c Change PrintOnly to PrintableOnly
e
s 00014/00012/00121
d D 1.5 98/08/17 15:00:27 clyde 5 4
c 1. Add passwd.Whitespace, passwd.AlphaOnly
c 2. Sort passwd directives in alpha order
e
s 00040/00064/00093
d D 1.4 98/06/25 12:42:35 clyde 4 3
c Update and reformat
e
s 00004/00002/00153
d D 1.3 98/03/24 15:21:55 clyde 3 2
c Add passwd.MinCharClasses and passwd.MatchWait
e
s 00098/00078/00057
d D 1.2 97/04/29 15:58:34 clyde 2 1
c Rework with new stuff
e
s 00135/00000/00000
d D 1.1 96/08/30 14:42:02 clyde 1 0
c date and time created 96/08/30 14:42:02 by clyde
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

D 2
OUTFILE="npasswd_conf.proto"
E 2
I 2
D 4
OUTFILE="passwd.conf"
E 2
echo "Extracting $OUTFILE (with variable substitutions)"
E 4
I 4
echo "Extracting passwd.conf (with variable substitutions)"
E 4

D 4
$spitshell > $OUTFILE <<'!NO!SUBS!'
E 4
I 4
$spitshell > passwd.conf <<'!NO!SUBS!'
E 4
#
D 2
# Example npasswd configuration file
E 2
I 2
# Example npasswd configuration file.
E 2
#
D 2
# This file should NOT be used as your configuration file,
# but be used to base your configuration file on.
E 2
I 2
D 4
# See doc/Reference.html for details.
E 4
I 4
# See ../doc/Reference.html for details.
E 4
E 2
#
# %W% %G% (cc.utexas.edu)
#
D 2
#	 There may be multiple such entries.
E 2
I 2
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
D 4
#  Directive                 Value    Description
#                            type
E 4
I 4
# Directive		Value	Description
#			type
E 4
# 
D 4
#  PasswdTolerance           number   Tolerance between old and new passwd
#                                     files
# 
#  ShadowTolerance           number   Tolerance between old and new shadow
#                                     files
#  DeferOptions              string   Option to defer to vendor programs
E 4
I 4
# PasswdTolerance	number	Tolerance between old and new passwd files
# ShadowTolerance	number	Tolerance between old and new shadow files
# MatchTries		number	Chances to give user to correctly
#				enter a password
# MatchWait		number	Delay after the user enters an
#				incorrect password
E 4
E 2
#
D 2
# Configuration directives for 'passwd'
E 2
I 2
D 4
#               Directives for sub-program passwd
E 4
I 4
#	Directives for sub-program passwd
E 4
E 2
#
I 5
# passwd.AlphaOnly	boolean	Allow alpha-only passwords
# passwd.CharClasses	number	Minimum number of character classes required
E 5
D 2
# passwd.Dictionaries	/path/to/dirs
#		Specify the directory in which the check dictionaries
#		are localed.
E 2
I 2
D 4
#  passwd.Dictionaries       path     Password check dictionaries location
#  passwd.MonocaseOK         boolean  Allow single-case passwords
#  passwd.MinPassword        number   Minimum password length
#  passwd.MaxPassword        number   Maximum effective password length
# 
#  passwd.PrintableOnly      boolean  Deny non-printable characters in
#                                     passwords
D 3
# 
E 3
#  passwd.MaxRepeat          number   How many repeated characters allowed in
#                                     passwords
D 3
# 
E 3
I 3
#  passwd.MinCharClasses     number   Minimum number of character
#				      classes required
E 3
#  passwd.DisallowedChars    string   Change the list of non-allowed
#                                     characters
#  passwd.HistoryDatabase    string   Location of password history database
#  passwd.HistoryAge         number   Password history aging control
#  passwd.HistoryDepth       number   How many password to keep per user
#  passwd.PasswordChecks     string   Choose password check functions
#  passwd.HelpFile           path     Help file for passwd function
#  passwd.Message            path     Message of the day
#  passwd.MatchTries         number   How many password match tries
I 3
#  passwd.MatchWait          number   How long to wait after unsuccessful
#				      password match
E 4
I 4
# passwd.Dictionaries	path	Password check dictionaries location
D 5
# passwd.Singlecase	boolean	Allow single-case passwords
# passwd.MinPassword	number	Minimum password length
# passwd.MaxPassword	number	Maximum effective password length
# passwd.LengthWarn	boolean	Warn about passwords over MaxPassword length
# passwd.PrintOnly	boolean	Deny non-printable characters in passwords
# passwd.MaxRepeat	number	How many repeated characters allowed 
# passwd.MinCharClasses	number	Minimum number of character classes required
E 5
# passwd.DisallowedChars string	Change list of non-allowed characters
# passwd.Help 		path	Help file for passwd
D 5
# passwd.Message	path	Message of the day file for passwd
# passwd.PasswordChecks	string	Choose password check functions
# passwd.History none 		Disable password history
# passwd.History file	path 	Set path to history db (flat file)
# passwd.History dbm	path 	Set path to history db (DBM database)
E 5
# passwd.History age	number	Password history age
I 5
# passwd.History dbm	path 	Set path to history db (DBM database)
E 5
# passwd.History depth	number	How many password to keep per user
I 5
# passwd.History file	path 	Set path to history db (flat file)
# passwd.History none 		Disable password history
# passwd.LengthWarn	boolean	Warn about passwords over MaxPassword length
# passwd.MaxPassword	number	Maximum effective password length
# passwd.MaxRepeat	number	How many repeated characters allowed 
# passwd.Message	path	Message of the day file for passwd
# passwd.MinPassword	number	Minimum password length
# passwd.PasswordChecks	string	Choose password check functions
D 6
# passwd.PrintOnly	boolean	Deny non-printable characters in passwords
E 6
I 6
# passwd.PrintableOnly	boolean	Deny non-printable characters in passwords
E 6
# passwd.Singlecase	boolean	Allow single-case passwords
# passwd.WhiteSpace	boolean	Deny whitespace characters in passwords
E 5
E 4
E 3
E 2
#
D 2
# passwd.MonocaseOK	yes | [no]
#		Approve single-case passwords
E 2
I 2
D 4
#               Directives for sub-program chfn
E 4
I 4
#	Directives for sub-program chfn
E 4
E 2
#
D 2
# passwd.MinPassword	N [5]
#		Minimum password length (chars)
E 2
I 2
D 4
#  chfn.HelpFile             path     Help file for chfn
#  chfn.Message              path     Message of the day
E 4
I 4
# chfn.Help		path	Help file for chfn
# chfn.Message		path	Message of the day
E 4
E 2
#
D 2
# passwd.MaxPassword	N [8]
#		Maximum effective password length (for warning purposes only)
E 2
I 2
D 4
#               Directives for sub-program chsh
E 4
I 4
#	Directives for sub-program chsh
E 4
E 2
#
D 2
# passwd.PrintableOnly	yes | [no]
#		Deny non-printable characters in passwords
#
# passwd.MaxRepeat	N
#		XXXX
#
# passwd.DisallowedChars	"<string>"
#		Replace the list of characters not allowed in passwords
# passwd.DisallowedChars	+"<string>"
#		Append to the list of characters not allowed in passwords
#
# passwd.HistoryDatabase
#		/path/to/history/file |	nis mapname | nisplus table
#			Set location of password history file
#
# passwd.HistoryParams
#		keep=N		Retain the last N passwords per user
#		age=N		Retain passwords which are less than N days old
#
# passwd.PasswordChecks	function function ...
#		Specify the order of password checks.
#		The available check functions are:
#			lexical		Simple lexical checks
#			local		Local admin checks (shipped empty)
#			passwd		Check against passwd entry
#			crack		Check using Crack algorithims
#			history		Check password history
#
# passwd.MatchTries	N
#		How many chances to give users to match password
#
# passwd.HelpFile	/path/to/help/file
#		Specify the passwd help file
#
# passwd.Message	/path/to/message/file
#		Specify the passwd message-of-the-day file
#
# Configuration directives for 'chsh'
#
# chsh.HelpFile	/path/to/help/file
#		Specify the chsh help file
#
# chsh.Message	/path/to/message/file
#		Specify the chsh message-of-the-day file
#
# chsh.ShellList	/etc/shells
#		The list of blessed shells
#
# Configuration directives for 'chfn'
#
# chfn.HelpFile	/path/to/help/file
#		Specify the chfn help file
#
# chfn.Message	/path/to/message/file
#		Specify the chfn message-of-the-day file
#
E 2
I 2
D 4
#  chsh.Helpfile             path     Help file for chsh
#  chsh.Message              path     Message of the day
#  chsh.Shells               path     List of blessed shells
E 4
I 4
# chsh.Help		path	Help file for chsh
# chsh.Message		path	Message of the day
# chsh.Shells		path	List of blessed shells
E 4
# 
E 2
D 4
# ------------------------------------------------------------------
# Start settings from "Configure"
# ------------------------------------------------------------------
E 4
D 2
#
E 2
!NO!SUBS!
D 4
(
case "$o_pwhFile" in
	/*)			what="" ;;
	[nN][iI][sS]|[yY][pP])	what="nis ";;
	nisplus|NIS+)		what="nisplus ";
esac
	
	$spitshell <<!GROK!THIS!
E 4
I 4
$spitshell >> passwd.conf <<!GROK!THIS!
E 4
#
# Password check dictionaries
#
D 2
passwd.Dictionaries	$privlibexp/dictionaries
E 2
I 2
D 4
#passwd.Dictionaries	$privlibexp/dictionaries
E 4
I 4
# passwd.Dictionaries	$p_dictlib
E 4
E 2
#
D 4
# Password history parameters
#
D 2
passwd.HistoryParams	keep=$o_pwhSize age=$o_pwhTime
E 2
I 2
#passwd.HistoryDepth	$o_pwhSize
#passwd.HistoryAge	$o_pwhTime
#passwd.HistoryDataBase	$what $o_pwhDB
E 2
#
D 2
# Password history database
#
passwd.HistoryDataBase	$what $o_pwhFile

E 2
I 2
# End %M%
E 4
E 2
!GROK!THIS!

D 4
) >> $OUTFILE
chmod 644 $OUTFILE

E 4
I 4
chmod 644 passwd.conf
$eunicefix passwd.conf
E 4
E 1
