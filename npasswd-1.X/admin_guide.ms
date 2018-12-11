'\"
'\" %W% %G% %P%
'\"
.PP
.TL
The system administrator's guide to npasswd
For version 1.3
.AU
Clyde Hoover
.AI
Computation Center
The University of Texas at Austin
.LP
Document version %I% of %G%.
.NH 1
Introduction.
.LP
.B Npasswd
is a pretty much plug-compatable replacement for
\fBpasswd\fP(1).  It incorporates checking to decrease the chance of
users choosing vunerable passwords.
.LP
It does exactly
.B one
thing \- change login passwords, though future releases will
change shells and finger information.
.LP
.B Npasswd
can be configured to run under a number of UNIX variants, both BSD and System 5
based. The systems that I know npasswd works on are: UMAX 4.3, Ultrix 3.X
and 4.X, SunOS 4.X, AIX 3.X and other System 5 variants.
.NH 1
Why this program.
.LP
The infamous Internet worm of November 1988 used among its attacks
a password guesser.  It is frightening how many passwords on how many UNIX
systems were guessed by this algorithim.  With the publication of various
papers about the internals of the worm, its' password cracking algorithims
came to light.
.LP
I replicated the worm password cracker from those papers, ran it
against my password file and got too many hits to be comfortable.
I decided that rigourous validity checking was needed for passwords,
so I took the ``worm'' algorithim and rewrote it into a password checker.
.LP
A simple version of that check package was posted to USENET at that time,
and still lurks on various FTP archives.  If you find this package, don't use
it \- there is better stuff included in this distribution.
.LP
Since 1988 programs such as ``Crack'' have been written
which are much better at password guessing.
Huge dictionaries of words and phrases from
many different languages and cultural areas have been compiled.
UNIX password cracking, once thought to be provice of only those
with access to supercomputers, is within easy reach of anyone with
a 386 box, a C compiler and patience.
.LP
.B Npasswd
lacks many of the features of vendor-supplied passwd programs
for the various platforms on which it will run.  Hence, the vendor passwd
program should be kept around for these purposes, such as setting password
expiration times.  On the other hand, no vendor-supplied passwd program
that I have seen performs any kind of intelligent password checking, or allows
the system administrator to configure that process.
.NH 1
How to make it go.
.LP
The process of configuring
.B npasswd
requires some thought on the part of the system administrator.
It's not a ``plug and play'' process.  There are configuration options
to select, and there is policy in the code that may not meet your needs.
.LP
The main decision that you need to make is
what kind of password database you use.  The supported methods are:
.IP \(bu
Flat password file with or without DBM lookup files.   This method is commonly
used by UNIX variants based upon 4.3 BSD.
.IP \(bu
The Network Information Service (\fBYellow Pages\fP).  This method is used
by most UNIX variants that offer Network File System (NFS), usually for
clusters of workstations.  The \fBNIS+\fP service of Solaris 2 is \fBnot\fP
supported.
Password aging is \fBnot\fP supported for SunOS systems.
.IP \(bu
Flat password file in Ultrix ``enhanced'' security mode.  This feature provides
for 16 character passwords and password aging.
.NH 2
Configuration options in the Makefile.
.IP \(bu
To select the desired password database method,  uncomment
the appropriate line of the group of "all" statements.
.IP \(bu
To choose the name of the configuration, help and message files,
change the lines "\fBCF =\fP", "\fBHF =\fP" and "\fBMF =\fP".
.IP \(bu
For running under SunOS 4.X system, uncomment the line "\fBSUNOS =\fP".
.IP \(bu
For running under System V R2 or R3, uncomment the line "\fBSYS5 =\fP".
.IP \(bu
To not use BSD-style system logging (\fIsyslog\fP), comment out the line
"\fBSYSLOG =\fP".
.IP \(bu
If you are on a BSD system without YP, uncomment the line "\fBBSD =\fP".
.IP \(bu
For DEC Ultrix 3.X and 4.X systems, uncomment the lines "\fBULTRIX =\fP"
and "\fBLIB_RPCSVC =\fP".
.IP \(bu
If you want to select a different location for the password file,
uncomment and change the lines "\fBPWF =\fP", "\fBPWT =\fP" and "\fBPWS =\fP",
and uncomment the lines below that define
.B PASSWD_FILE ,
.B PASSWD_TEMP
and
.B PASSWD_SAVE .
.IP \(bu
If you want to select ``paranoid'' caller authentication, uncomment the line
"\fBPARANOID = \fP".  This will cause 
.B npasswd
to abort if the uid obtained via
.I getpwnam(getlogin())
is not the same as the real uid and the real uid is not zero (the superuser).
.IP \(bu
If you want to use the Yellow Pages RPC interface to update passwords
even on the Yellow Pages master, uncomment the line "\fBFORCE_YP =\fP".
I do \fBnot\fP
recommend this because of buggy behavior that I have seen
in various versions of rpc.yppasswwdd, and I like the idea that if I change
a password on the Yellow Pages master, that it
.B will
happen and I will get immediate feedback to that effect.  I include this option
because it is one of the most popular added at other sites.
.NH 2
Editing ancillary files.
.LP
The file
.I npasswd.help
should be editted to reflect the preferences you have
chosen for the password checking and other local administrativa.
The file
.I npasswd.conf
should be editted to reflect your preferences.
See below for a detailed description of the configuration file.
The file
.I npasswd.motd
should be have local administrativa, such as notice of any update
latency (e.g. how often Yellow Pages maps are rebuilt).
.NH 2
The configuration file.
.LP
The parameters for password checking are provided by the configuration file.
There are defaults built into the 
.I checkpassword
routines, but the following configuration file directives
can be used to alter them.  Values in brackets '[\ ]' is the default.
.sp
.nf
dictionary	/path/to/dictionary
	See the dictionaries section below.

singlecase	yes | [no]
	Allow or disallow single case passwords.

minlength	N [6]
	Set the minimum password length.

maxlength	N [8]
	Specifies how many characters are effective in a password.
	Only the first N characters are used.

printonly	yes | [no]
	Allow non-printable (ASCII control) characters in passwords

badchars	"<string>"
	Set a list of characters disallowed in passwords.
	This form replaces the built-in illegal character list.
	Control characters may be specified by the '^X' convention.  

badchars	+"<string>"
	Set a list of characters disallowed in passwords.
	This form adds to the built-in illegal character list.
	Control characters may be specified by the '^X' convention.  
.fi
.NH 2
Making it so.
.LP
After the Makefile is configured and the ancillary files customized,
then you are ready to build stuff.  The Makefile has the following
entry points of interest:
.IP everything 15
This builds
.B npasswd
and the dictionary tools.  Run this after any change to the 
.B npasswd
configuration.
.IP all 15
This builds 
.B npasswd
only.
.IP dicttools 15
This builds the dictionary tools.
.IP dictionaries 15
This reminds you that you need to read this document for directions
about how to build dictionaries.
.IP install 15
This builds the and installs the program, the help and message files.
The configuration file and the password dictionaries specified therein 
are checked for consistency and the configuration file installed if ok.
.IP checkcf 15
This performs a consistency check on the configuration file.
.IP checkdicts 15
This performs a consistency check on the dictionaries specified in the
configuration file.
.IP clean 15
This cleans up the debris.
.LP
If you built
.B npasswd
with the syslog option on (which is the default)
modify
.B /etc/syslog.conf
to log messages for facility \fIlog.auth\fP and level
\fIlog.info\fP.  This gives you a record of password changes and failures.
.LP
You will probably want to customize the manual page.
.NH 1
Npasswd internals.
.LP
.B Npasswd
is divided into upper and lower levels.
The upper level is pretty abstract. It has no knowledge of how or
where passwords are stored.  It does command line processing,
permission checking and user interaction.  It relies upon
the lower (method) level routines to do the work.
.LP
The lower (method) level does data lookup and replacement.
The gritty work of updating files and databases is done in this section.
Both the upper and lower levels keep private state.
.LP
This approach allows a single user interface for a variety of
password storage methods.  To support another method, such as shadow
password files, a new set of method routines can be written and
linked in.
.LP
The upper and lower level communicate via the following interface:
.sp
\fBvoid pw_initalize(int argc, char **argv)\fP
.br
.RS
This initialized the method code.  The command line arguments are passed
for possible interpetation. 
.RE
.LP
\fBint pw_getuserbyname(char *username, *password)\fP
.br
.RS
Get user information for
.I username .
The encrypted password is copied into the buffer pointed to by the 
.I password
argument.  Returns 1 if the user was found, 0 if not.
That user now becomes the
.I current
user to the method routines.  That identity will be used for all
subseqent checks and updates.
.RE
\fBint pw_permission()\fP
.RS
Checks if the invoker of \fBnpasswd\fP has privlege to change the target's
password.  Returns 1 if permission granted, 0 if not.
.RE
\fBint pw_compare(char *current, *new)\fP
.RS
Compares passwords. The 
.I current
argument is the encrypted current password,
and
.I new
is a plaintext password.  The routine returns 1 if they match, 0 if not.
.RE
\fBint pw_check(char *password, *message)\fP
.RS
Check password for validity.  This routine usually calls the 
.I checkpassword
library to do the work.  The routine returns 1 if the
password is ok to use, 0 otherwise and the buffer pointed to by the
.I message
parameter contains information about why the password was rejected.
.RE
\fBvoid pw_replace(char *newpassword, *password)\fP
.RS
Replace the password for the current user.  The
.I newpassword
argument
is the plaintext of the new password, and the
.I password
argument is plaintext
of the current password.  The latter is needed for changing passwords via
the Yellow Pages RPC interface.  This routine has no return value, but
produces diagnostic messages and generally aborts upon update failure.
.RE
\fBvoid pw_cleanup(int code)\fP
.RS
Perform cleanup in preparation for program termination.  The
.I code
argument
denotes the circumstances.  A code of 0 indicates a normal exit, and non-zero
indicates an abort in progress.
.RE
.LP
The following method modules are provided with this distribution:
.LP
The module 
.B pw_passwd.c
deals with flat /etc/passwd file and can manage the hashed passwd database.
.LP
The module
.B pw_yp.c
also deals with flat /etc/passwd files and the Yellow Pages passwd service.
.LP
The module
.B pw_ultrix.c
deals with flat /etc/password files, hashed passwd
databases and additionally works with Ultrix ``enhanced'' security mode.
.LP
The module
.B pw_userinfo.c
supports a locally written user database.  This code illustrates how a totally
different database method can fit into the
.B npasswd
structure.
.NH 1
More about password checking.
.LP
The work of checking passwords is done by the
.I checkpassword
library.  Candidate password is subjected to the following challanges:
.IP 1.
Enforcement of a minimal length.
.IP 2.
Simple lexical checks to catch some dumb passwords, such as repeats
of the same letter (e.g. ``aaa'').  Strange characters are also checked for.
By default, the following control characters are not allowed in passwords:
.sp
.in +3
control-c control-d control-h control-j control-m
control-o control-r control-s control-q control-y
.in -3
.sp
These are typical tty ``special'' characters on UNIX systems.
A user could put these characters in their password by quoting them,
but there is no guarantee that the tty modes
used by \fIlogin\fP would allow them to be properly entered, so they
are best avoided.  This character list may be replaced or supplimented
by configuration directives.
.IP 3.
The candidate password is compared against host-specific information.
.IP 4.
The candidate password is checked against a number of permutations on
the users' current passwd information.
.IP 5.
The candidate password is checked against the user's finger information.
.IP 6.
The candidate password is checked against the Crack rules.
.LP
The checking process is table driven so that new routines can be added easily.
See the sources in the
.I checkpassword
directory.
.NH 1
About dictionaries.
.LP
Dictionaries are a vital part of password checking (and cracking).
The dictionaries used by npasswd must be in a special hashed form.
.LP
There are a number of dictionaries supplied, in various sizes and vintage.
The optimal setup would be to combine them all into one huge dictionary,
but you may prefer paritioning them into smaller ones.
.NH 2
How to set up dictionaries.
.IP 1.
Get your list for dictionary words together.
The format of the file is one token (word or short phrase) per line.  Blank
lines and lines starting with '#' will be ignored.
.IP 2.
Determine where you want the dictionary installed on the system.
The directory
.B /usr/dict
is where the standard spelling dictionary is
stored.  However, password checking dictionaries are not
always suitable for use by spelling checkers, so put the password dictionaries
where you have sufficent disk space.
.IP 3.
For each dictionary you want to use, do the following:
.in +2
mkdict dictfile1 dictfile2 ... -o /path/to/installed/dict
.in -2
.sp
.in +2
Then add the line
.in +3
dictionary	/path/to/installed/dict
.in -3
to the file \fInpasswd.conf\fP.
.in -2
.NH 1
So what's the catch?
.LP
.B Npasswd
does exactly
.B one
thing \- changes login passwords.  It doesn't anything more
and doesn't do that totally right for all UNIX environments.
The seperation between upper and lower levels leads to considerable
duplication of effort and state, and there is a couple of places where
holes have been punched through the layers in an ugly way.
Support for password aging is minimal at best, and the method varies
per vendor and operating system release.
.LP
Making 
.B npasswd
totally compatable with vendor
.B passwd
programs would involve either reverse engineering their work or swiping
their code.  Not having
.B npasswd
be totally compatible leads to loss of functionality. 
.NH 1
What's in the future?
.LP
Work is continuing on 
.B npasswd
and version 2.0 should be available in the fall of 1993.
.FS 1
Version 2.0 was supposed to be done in early 1992, so take this
schedule with a substantial grain of salt.
.FE
This version is expected to have the following features:
.IP \(bu
Support for changing login shell (chsh) and finger information (chfn).
.IP \(bu
Support for Solaris 2 and NIS+.
.IP \(bu
Support for the Netinfo database of NeXTSTEP.
.IP \(bu
Plug and play support for more UNIX variants and architectures.
.IP \(bu
A simplified configuration procedure.
.LP
Since it's almost impossible to replicate the
command line options of every version of
.B passwd
and since they increasingly
do more than just changing a pasword file, 
I'm exploring alternate ideas such as building a front-end for
the vendor-supplied programs.
It would use the
.I checkpassword
library to check passwords and then interact with the ``real''
.I passwd
program.
This will probably be written in
.I expect
(a variant of
.I tcl
) or 
.I perl .
.NH 1
Where do I get help?
.LP
The following electronic mail addresses exist for
.B npasswd
users:
.IP npasswd-bugs@emx.cc.utexas.edu
Is where to report bugs and send enhacements.
Bug reports will generally be acknowleged but not necessarily responded to.
I have at least two full-time ``jobs'' at my place of employment, and tend
to batch up
.B npasswd
problems and deal with them every few months.  It really
helps if bug reports are accompanied by source fixes, preferably in patch
diffs.  Enhancements will be dealt with in the same way.
.IP npasswd-users@emx.cc.utexas.edu
Is a mailing list of all registered users of npasswd.
.IP npasswd-users-request@emx.cc.utexas.edu
Is where to send requests to be added to or delete from the npasswd-users list.
.NH 1
Credit where credit is due.
.LP
.I Npasswd
and most of the ancillary routines were written by myself.
The code for Ultrix enhanced security support was written by
Paul Leyland (pcl@ox.ac.uk).
The ``Cracklib'' password checking code is copyright 1993 by
Alec Muffett (alec.muffett@uk.sun.com).
SunOS adjunct password support was done by Dave Hayes
(dave@jato.jpl.nasa.gov) and 
There are many others who supplied bug fixes and enhancements, some
of which are included in this distribution, some not, but all are
appreciated.
'\"
'\" End %M%
