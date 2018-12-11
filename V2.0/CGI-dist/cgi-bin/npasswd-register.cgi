#!/usr/local/bin/perl
#
# %W% %G% %P%
#
# Npasswd request/registration/download CGI script.
#
# URL for running in home directory:
#	  http://<hostname>/cgi-bin/cgiwrap/<user>/npasswd-<func>.cgi[?stuff]
#
# Functions:
#	'request' submits a form for the user to fill out, providing
#		information for the registry.  The registration form
#		will be submitted to the 'register' CGI.
#
#	'register' processes the registration form.  If needed a new
#		registry id is created and a registry entry made.
#		If a new id was created, a browser cookie is sent which
#		will be recognized by the 'request', 'register' and 'download'
#		CGIs.  This form has links to the 'download' CGI.
#
#	'download' Generates redirect a URL to cause downloading of files.
#
#	'admin' is the administration interface to the registry.
#
use File::Basename;
use English;		# Plain words for special vars
use Fcntl;		# For O_XXXX symbols
use NDBM_File;		# To use registry database
use CGI;		# CGI stuff
use CGI::Carp;		# Logging stuff
use CGI::Carp qw(carpout);

require 'ctime.pl';

#
# Mailto URL for responsible person
#
$BigKahuna = '<A HREF="mailto:c.hoover@cc.utexas.edu">
		c.hoover@cc.utexas.edu</a>';
#
# Signature block for pages
#
$Signature = "
	Clyde Hoover<BR>
	Academic Computing &amp; Instructional Technology Services<BR>
	The University of Texas at Austin<BR>
	$BigKahuna
";

#
# Distribution stuff
#
$swName = 'npasswd';					# Product name
$swVersion = '2.0beta4';				# Product versin
$swCookie = "$swName-$swVersion";			# Browser cookie name
$swCookieExp = 'Tuesday, 1-Jul-97 06:00:00 GMT';	# Browser cookie expire
$swIndex = "$swName.index";		# Distribution file index

$swRegDB = "REGISTRY";			# Registry database
$swRegAccess = (O_RDWR|O_CREAT);	# Registry open mode
$swRegMode = 0600;			# Registry file mode
$swRegCounter = 'REQUEST-COUNT';	# Registry counter token

#
# Table of operating systems for user selection
#
%KnownSystems = (
	'sunos5' =>	'SunOS 5 (Solaris 2)',
	'sunos4' =>	'SunOS 4 (Solaris 1)',
	'decosf' =>	'Digital UNIX (OSF/1)',
	'decultrix' =>	'Digital Ultrix',
	'aix' =>	'IBM AIX',
	'hpux' =>	'HP/UX',
	'linux' =>	'Linux',
	'freebsd' =>	'FreeBSD',
	'bsdi' =>	'BSDI UNIX',
	'irix' =>	'SGI IRIX',
);

#
# Warnings to display about known problems on various UNIX systems
#
%Caveats = (
	'decosf' => 'Does not build under Digital UNIX 4.0 due to bugs
		 in the Korn Shell and system include files.',

	'aix' => 'Does not properly configure under AIX 4.X.',

	'decultrix' => "$swVersion has not been tested under ULTRIX 4,
		 though an earlier beta did work.",
);

#
# Hosts which are allowed to do administrative tasks
#
@AdminHosts = (
	'diana.cc.utexas.edu',
	'grapevine.cc.utexas.edu',
	'superfreak.cc.utexas.edu',
	'war.cc.utexas.edu',
);

########################################################################
#
# Main program
#
########################################################################
if (! -t STDERR) {
	#
	# Open log if not attached to a tty
	#
	warn "redirected to log\n";
	if (open(LOG, ">> $swName-cgi.log")) {
		carpout(\*LOG);
	}
}

$theQuery = new CGI;			# Fetch the query

$OrigHost = $theQuery->remote_host;	# Where query is from

&OpenRegistry;				# Open the registry

#
# The registration id can be sent either as a browser
# cookie or a "id=" parameter of the URL.
#
# RegistryID - set to registration id if found
# RegistryIDFrom - set to source of id ('url' | 'cookie')
#
if (($crumbs = $theQuery->cookie(-name=>$swCookie)) ne '') {
	$RegistryID = $crumbs;
	$RegistryIDFrom = 'cookie';
} else {
	$RegistryID = $theQuery->param('id');
	$RegistryIDFrom = 'url';
}
undef $crumbs;
carp "$RegistryID ($RegistryIDFrom)\n" if ($RegistryID);

#
# If the "state" parameter is set to 'new' then discard and registry ID found
#
if ($RegistryID && $theQuery->param('state') eq 'new') {
	undef $RegistryID;
	carp "'New' flag set - discarding registry\n";
}

#
# Lookup registry id and load the user data
#
if ($RegistryID) {
	my $dataFromRegistry = $Registry{$RegistryID};
	if ($dataFromRegistry ne '') {
		eval $dataFromRegistry;
		if ($EVAL_ERROR) {
			carp "Registry eval error <$EVAL_ERROR>";
			&ErrorPage('Internal error',
				"Internal error in registry database.<br>
				 Send mail to $BigKahuna");
			exit 0;
		}
	} else {
		undef $RegistryID, $RegistryIDFrom;
	}
	undef $dataFromRegistry;
}

#
# Decode function from program name
#
if ($0 =~ /request/io) {		# Make request form
	&DoRequest;
}

if ($0 =~ /register/io) {		# Process registration form
	&DoRegister;
}

if ($0 =~ /download/io) {		# Download software
	&DoDownload;
}

if ($0 =~ /admin/io) {			# Admininster registry
	&DoAdmin;
}
&CloseRegistry;
exit 0;

########################################################################
#
# Begin subroutines
#
########################################################################

#
# TextEntryRow - Make a table row in the form
#	Label	Text-entry-field
#
# Parameters are passed by name:
#	name - Name for text entry field
#	size - Size of text entry field
#	default - Default data in text entry field
#	label - Contents of label column
#
sub TextEntryRow {
	my %params = @_;
	my $foo;

	my $tmp = $params{'default'};
	if ($tmp ne '') {
		$foo = $theQuery->textfield(-name=>$params{'name'},
			-override => 1,
			-size=>$params{'size'}, -default=>$tmp);
	} else {
		$foo = $theQuery->textfield(-name=>$params{'name'},
			-override => 1,
			-size=>$params{'size'});
	}
	print &start_table_row,
		&start_table_data, $params{'label'}, &end_table_data,
		&start_table_data, $foo, &end_table_data,
	&end_table_row;
}

#
# DoRequest - Build and send the registration form
#
sub DoRequest {
	print $theQuery->header();
	print $theQuery->start_html(
		-title=>"Registration for $swName $swVersion");
	print $theQuery->h1(
		"<center>Registration for $swName $swVersion</center>");

	my $url = $theQuery->url;
	$url =~ s/request/register/;	# Change "request" to "register"

	print $theQuery->startform(-method=>'post', -action=>$url);
	print $theQuery->hr;

	#
	# If registry id is known, then tell the user that we know them.
	#
	if ($RegistryID) {
		my $xurl = "$url?id=$RegistryID&state=known";
		print "<P><P>
			You are already registered for the $swName $swVersion
			distribution. <P>
			Your registration id is <tt><B>$RegistryID</B></tt><P>
			If you want to <b>update</b> your registration,
			change this form and submit it.<P>
			If your registration is correct you can proceed to the 
			<A HREF=\"$xurl\">download page.</A><P>";

	} else {
		print "<P><P>
			Please fill out the registration form.
			This information will be used to keep you up-to-date
			with bug reports, patches and new releases.<P>\n";
		$User::Email = "\@$OrigHost";
	}
	#
	# Start the registration form table
	#
	print &start_table(
		cellpadding => 1, border => 1, caption => "Registration form");

	#
	# User name entry
	#
	&TextEntryRow (
		label => 'Name:', name => 'who_it_is',
		size => 30, default => $User::Name);
	#
	# Email address entry
	#
	&TextEntryRow (
		label => 'Email address:', name => 'email',
		size => 30, default => $User::Email);
	#
	# Operating system selector
	#
	print &start_table_row,
		&start_table_data,
		'Operating systems on which you want to use<br>
			npasswd under (select all that apply)',
		&end_table_data;

		print &start_table_data;
		print "<SELECT NAME=\"os_pick\" SIZE=\"5\" MULTIPLE>\n";
		foreach $os (sort keys %KnownSystems) {
			print "<OPTION VALUE=\"$os\"";
			print ' SELECTED'
				if (grep(/^$os$/, @User::OSlist));
			print '>'. $KnownSystems{$os} . "\n";
		}
		print "</SELECT><BR>\n";
			print $theQuery->textfield(-name=>'os_other',-size=>20),
			'Other',
			&end_table_data;
	print &end_table_row;
	#
	# Show download history if present
	#
	if (@User::Downloads) {
		print &start_table_row,
			&start_table_data,
				'What you have downloaded so far:',
			&end_table_data,
			&start_table_data;
				&PutDownloads;
			print &end_table_data,
		&end_table_row;
	}
	#
	# Add comments textarea
	#
	print &start_table_row,
		&start_table_data,
			"Comments:",
		&end_table_data,
		&start_table_data,
			$theQuery->textarea(
				-name => 'comments',
				-rows => 4,
				-columns => 50),
			&end_table_data,
		&end_table_row;
	#
	# Add submit & reset buttons
	#
	print &start_table_row,
		&start_table_data,
			$theQuery->submit(-value => 'Submit registration'),
			$theQuery->reset(-value => 'Reset form'),
			&end_table_data,
		&end_table_row;
	print &end_table;

	print $theQuery->endform;		# Finish form
	print "<P><HR><P>$Signature<P>";	# Add signature
	print $theQuery->end_html;
}

#
# PutDownloads - print file download history
#
sub PutDownloads {
	my $dl;
	local %xfiles = ();
	local %xdesc = ();

	&GetIndex($swIndex, *xfiles, *xdesc);
	print '<pre>';
	foreach $dl (@User::Downloads) {
		if ($dl =~ /(.*)@(.*)/) {
			my $pn = $xfiles{$1};
			printf '%-30s %s<br>', basename($pn), &ctime($2);
		}
	}
	print '</pre>';
}

#
# DoRegister - Process the registration form
#
# Form fields:
#	init - ignore contents of the registration form
#
sub DoRegister {
	my $cpath = $theQuery->url;
	my $newcookie;

	if ($RegistryID) {
		unless ($theQuery->param('state') eq 'known') {
			&ProcessRegistrationForm;
			&MakeRegistryEntry($RegistryID);
			carp "Updated registry $RegistryID\n";
		}
		print $theQuery->header;
	} else {
		#
		# No registry id - make a new one
		#
		&ProcessRegistrationForm;	# Get info from registry form
		my $RequestNo = $Registry{$swRegCounter};
		$RequestNo = '00' if ($RequestNo eq '');
		$RequestNo++;
		$Registry{$swRegCounter} = $RequestNo;

		my $now = time;
		$RegistryID = "$swName-$swVersion-$now$RequestNo";
		#
		# Make a browser cookie
		#
		$newcookie = $theQuery->cookie(
			-name=>$swCookie,
			-expires=>$swCookieExp,
			-value=>$RegistryID);
		print $theQuery->header(-cookie=>$newcookie);

		&MakeRegistryEntry($RegistryID, $newcookie);
		carp "New registry id \"$RegistryID\" for $User::Email\n";
	}
	#
	# Start building the download page
	#
	print $theQuery->start_html(-title=>
		"Download $swName $swVersion");
	print $theQuery->h1(
		"<center>Download $swName $swVersion</center>");

	print '<HR><P>', $theQuery->h2('Registration infomation'), "<PRE>
	Your name:		$User::Name
	Email address:		$User::Email
	Registration id:	<B>$RegistryID</B>
	Operating systems:	";

	foreach $tmp (@User::OSlist) {
		my $tmp2 = ($KnownSystems{$tmp} ? $KnownSystems{$tmp} : $tmp);
		print "$tmp2\n\t\t\t\t";
	}

	print " </pre> <P>
Your registration id allows you to obtain updates or patches.<P>
<UL>
	<LI>If your browser uses cookies you don't need to do anything.
	<LI>If you don't use cookies, then append the text in bold
	to the <I>request</I> or <I>registration</I> URLs:
	<TT>$cpath<B>?id=$RegistryID&state=known</B></TT>
</UL>
";
	#
	# Caveats about OS versions being used
	#
	my $warnhdr = 0;
	foreach $os (sort @User::OSlist) {
		$xwarn = $Caveats{$os};
		if ($xwarn ne '') {
			unless ($warnhdr) {
				print "<hr><p>
					<h2>Caveats</h2><P>
					Caveats about using $swName $swVersion
					on the operating
					systems you mentioned:\n<ul>";
				$warnhdr = 1;
			}
			print "<li>$xwarn</li>\n";
		}
	}
	print "</ul>" if ($warnhdr);
	#
	# URLs for getting the goodies
	#
	print "<HR><H2>Download URLs</H2><P>";
	local %xfiles = ();
	local %xdesc = ();
	if (&GetIndex($swIndex, *xfiles, *xdesc) == 0) {
		print "Sorry, the distribution manifest is not available.
			 Send mail to $BigKahuna<P>";
	} else {
		my $furl = $cpath;
		$furl =~ s/register/download/;
		$furl =~ s/$/?id=$RegistryID&/;

		print "<ul>";
		foreach $tag (sort keys %xfiles) {
			print "<li><A HREF=\"$furl&file=$tag\">",
				basename($xfiles{$tag}),
				"</a>&nbsp;&nbsp;($xdesc{$tag})</li>\n";
		}
		print "</ul>\n";
	}
	print "<P><HR><P>$Signature<P>";
	print $theQuery->end_html;
}

#
# DoDownload - Process download request.
#
# Form fields:
#	file - tag for desired file. 
#		This tag is mapped to a file path by consulting
#		the software index.
#
sub DoDownload {
	unless ($RegistryID) {			# User unknown
		my $url = $theQuery->url;
		$url =~ s/download/request/;

		&ErrorPage("$swName download error",
			"<P><B>You are not registered.</B>
			<P>Register at <A HREF=\"$url\">$url</A>\n");
		return;
	}

	$filetag = $theQuery->param('file');
	unless ($filetag) {
		&ErrorPage("$swName download error",
			"<P><B>No file specified.</B><P>
			Please use the download page.<P>"
		);
		return;
	}
	local %xfiles = ();
	local %xdesc = ();
	if (&GetIndex($swIndex, *xfiles, *xdesc) == 0) {
		carp "GetIndex failed\n";
		&ErrorPage("Download error",
			"Sorry, the distribution index is not available.
			 Send mail to $BigKahuna<P>");
		return;
	}
	#
	# Generate a redirection URL to download the real file,
	# letting the user's browser and our Web server do the transfer
	# (and determine the right MIME type).
	#
	$filename = $xfiles{$filetag};
	$newurl = "http://" . $theQuery->server_name . "/~" .
		(getpwuid($UID))[0] . "/$filename";
	print $theQuery->redirect($newurl);
	#
	# Record the download
	#
	my $now = time;
	push(@User::Downloads, "$filetag\@$now");
	MakeRegistryEntry($RegistryID);
	carp "Download \"$filename\" by $RegistryID\n";
}

#
# DoAdmin - Administer the registry
#
# Form fields:
#	id_pick - Registry id to manipulate (from select sub-form)
#	xid_pick - Registry id to manipulate (from update sub-form)
#	change - Trigger for updating of a registry entry
#		who_it_is - User name update field
#		email - Email address update field
#	show - Trigger for examination of a registry entry
#	delete - Trigger to delete a registry entry
#
sub DoAdmin {
	print $theQuery->header;
	print $theQuery->start_html(-title=>"Registry administration");

	#
	# Half-assed validation of caller
	#
	if (!grep(/^$OrigHost/, @AdminHosts)) {
		&AdminError("Not from authorized host");
		return;
	}

	my $url = $theQuery->url;
	my $id = $theQuery->param('id_pick');
	$id = $theQuery->param('xid_pick') if ($id eq '');

	print $theQuery->h1("Registry administration");
	print $theQuery->startform(-method=>'post', -action=>$url);

	#
	# Do administrative sub-commands
	#
	user_admin: {
	if ($id) {
		print "<hr>\n";
		if ($theQuery->param('show')) {		# Show entry
			&ShowUser($id);
			last user_admin;
		}
		if ($theQuery->param('change')) {	# Update entry
			my $doit = 0;
			my $tmp = $theQuery->param('who_it_is');
			if ($tmp ne $User::Name) {
				$User::Name = $tmp;
				$doit++;
			}
			$tmp = $theQuery->param('email');
			if ($tmp ne $User::Email) {
				$User::Email = $tmp;
				$doit++;
			}
			if ($doit) {
				&MakeRegistryEntry($id);
				print "<P>Updated registry for <B>$id</B><P>\n";
				carp "Updated registry for $id\n";
			} else {
				print "<P>No changes for <B>$id</B><P>\n";
			}
			&ShowUser($id);
			last user_admin;
		}
		if ($theQuery->param('delete')) {	# Delete entry
			undef $Registry{$id};
			print "<P>Deleted <B>$id</B> from registry<P>\n";
			carp "Delete registry $id\n" ;
			last user_admin;
		}
	}
	}
	#
	# Display the registry
	#
	print "<hr>\n";
	my $count = keys %Registry;
	my $disp = $count / 2;
	$disp = 12 if ($disp > 12);
	print $theQuery->h2("Registry entries ($count total)");
	print '<SELECT NAME="id_pick" SIZE="', $disp, '">';
	foreach $id (sort keys %Registry) {
		next if ($id eq $swRegCounter);
		eval $Registry{$id};
		if ($EVAL_ERROR) {
			print "<OPTION VALUE=\"$id\">$id **BAD ENTRY**\n";
			carp "Registry eval error <$EVAL_ERROR>";
		} else {
			print "<OPTION VALUE=\"$id\">$id $User::Email\n";
			$recipients{$User::Email} = $User::Email;
		}
	}
	print "</SELECT>\n";
	print $theQuery->submit(-name=>'show', -value=>'Examine');

	my $rl = join(',', (sort keys %recipients));
	print "<P><A HREF=\"mailto:$rl\">" ,
		"Send mail to <B>everyone</B> in the registry</A>\n";

	my $xurl = $theQuery->url;
	print "<P><A HREF=\"$url\">Registry adminitration home page</A>\n";

	print $theQuery->endform;
	print "<hr>\n";
	print $theQuery->end_html;
}

#
# ShowUser - Show registry entry
#
sub ShowUser {
	my ($id) = @_;			# Registry id
	my $idr = $Registry{$id};	# Registry entry

	if ($idr eq '' ) {
		&AdminError("No such id in registry - $id");
		return;
	}
	eval $idr;
	if ($EVAL_ERROR) {
		&AdminError("Bad registry entry.\n
			PERL eval error: $EVAL_ERROR\n
------
$idr
------
");
		return;
	}
	#
	# Build the display/update table
	#
	print $theQuery->hidden(-name => 'xid_pick', -default => $id), "\n";
	print &start_table(
		'cellpadding' => 1, 'border' => 1,
		'caption' => "Registration information for $id");

	print &start_table_row,
		&start_table_data(colspan=>2),
			"<pre>",
			"Product:     $User::Product<br>",
			"Version:     $User::Version<br>",
			"Created:     ", ctime($User::Created), '<br>',
			"Last update: ", ctime($User::LastUpdate), '<br>',
			"</pre>",
		&end_table_data,
		&end_table_row;

	#
	# This field can be changed (User name)
	#
	&TextEntryRow (
		label => 'Name:', name => 'who_it_is',
		size => 30, default => $User::Name);

	#
	# This field can be changed (Email address)
	#
	&TextEntryRow (
		label => 'Email address:', name => 'email',
		size => 30, default => $User::Email);

	print &start_table_row,
		&start_table_data, 'Operating systems:', &end_table_data;

		print &start_table_data, "<pre>";
		foreach $os (sort @User::OSlist) {
			print $KnownSystems{$os}, "\n";
		}
		print "</pre>", &end_table_data;
	print &end_table_row;

	if (@User::Downloads) {
		print &start_table_row,
			&start_table_data,
				'Download history:',
			&end_table_data,
			&start_table_data;
				&PutDownloads;
			print &end_table_data,
		&end_table_row;
	}

	if ($User::Comments) {
		print &start_table_row,
			&start_table_data, "Comments:",     &end_table_data,
			&start_table_data, "<pre>$User::Comments</pre>", &end_table_data,
		&end_table_row;
	}
	print &end_table;
	#
	# Put buttons
	#
	print $theQuery->submit(-name=>'change', -value => 'Change'),
		$theQuery->submit(-name=>'delete', -value => 'Delete');

}

#
# AdminError - Produce admin error message
#
sub AdminError {
	print '<h1>Registry administation error</h1>';
	print '<pre>';
	print @_;
	print '</pre>';
	carp @_;
}

#
# ErrorPage - Send a page with an error message
#
sub ErrorPage {
	my (	$title,			# Title for the document
		@message		# HTML text to send
	) = @_;

	print $theQuery->header,
		$theQuery->start_html(-title => $title),
		$theQuery->h1($title);
	print @message;
	print $theQuery->end_html;
}

#
# ProcessRegistrationForm - Validate and munch the form data
#
sub ProcessRegistrationForm {
	my $FormError = '';
	my $tmp;

	if (($tmp = $theQuery->param('who_it_is')) eq '') { 
		$FormError = 'Please enter your name';
	} else {
		$User::Name = $tmp;
	}

	if (($tmp = $theQuery->param('email')) eq '') { 
		$FormError = 'Please enter your email address';
	} else {
		$FormError = "Malformed email address: $tmp";
		if ($tmp =~ /(.+)@(.+)/) {
			my $ehost = $2;
			$FormError = ''
				if (gethostbyname($ehost) ||
				    &checkMX($ehost));
			$User::Email = $tmp;
		}
	}
	if ($FormError) {
		$tmp = $theQuery->url;
		$tmp =~ s/register/request/;

		&ErrorPage("$swName request form error",
			"<P>Error in filling out the registration form:<P>
			<B>$FormError</B>
			<P>Go back to the
			<A HREF=\"$tmp\">registration form</A> and try again</P>",
			$theQuery->end_html);
		exit 0;
	}
	@User::OSlist = $theQuery->param('os_pick');
	my $os = $theQuery->param('os_other');
	push (@User::OSlist, $os);

	$User::Comments = $theQuery->param('comments');
}

#
# checkMX - Quick & dirty way to check if a "hostname" is an MX record
#
sub checkMX {
	my $rc = system
	     "(nslookup -type=mx $_[0] | grep 'exchanger =') >/dev/null 2>&1";
	return int($rc == 0);
}

#
# OpenRegistry - Open the registry database and tie to hash array
#
sub OpenRegistry {
	unless (tie(%Registry, NDBM_File, $swRegDB, $swRegAccess, $swRegMode)) {
		carp "DBM tie of \"$swRegDB\" failed, error $ERRNO\n";
		&ErrorPage('Registry init error',
			"Error in opening registry database.<br>
			 Send mail to $BigKahuna");
		exit 0;
	}
}

#
# MakeRegistryEntry - Create a registry entry.
#	Dump various User::... variables into a form that can
#	be processed by eval().
#
sub MakeRegistryEntry {
	my $id = $_[0];			# Registry key
	my $now = time;
	my $tmp;
	my $value = "
\$User::Product = q($swName);
\$User::Version = q($swVersion);
\$User::Name = q($User::Name);
\$User::Email = q($User::Email);
\@User::Downloads = qw(@User::Downloads);
\@User::OSlist = qw(@User::OSlist);
\$User::LastUpdate = $now;
\$User::Comments = qq{$User::Comments};
";
	if ($User::Created == 0) {
		$User::Created = $now;
		$value .= "\$User::Created = $User::Created;"
	}
	$Registry{$id} = $value;
}

#
# CloseRegistry - Close registry database
#
sub CloseRegistry {
	untie %Registry;
	undef %Registry;
}

#
# GetIndex - Load the software index 
# Usage:
#	$ok = &GetIndex($indexFile, *filesXtags, *descXtags);
#		indexFile = Index file: tag<tab>file-path<tab>description
#		filesXtags = File name array (index by tag)
#		descXtags = File description array (index by tag)
#	Returns 1 on success, 0 on failure.
#
sub GetIndex {
	package GetIndex;
	local ($indexFile, *filesXtags, *descXtags) = @_;

	return 0 unless (open(SL, $indexFile));
	while (<SL>) {
		chomp;
		next if (/^#/ || /^$/);
		($tag, $file, $desc) = split(/\s+/,$_, 3);
		$desc = $file unless ($desc ne '');
		$filesXtags{$tag} = $file;
		$descXtags{$tag} = $desc;
	}
	close(SL);
	return 1;
}

#
# Functions to help build tables
#
sub start_table_row	{ return(&start_table_item('TR',@_)); }
sub end_table_row	{ return(&end_table_item('TR',@_)); }
sub start_table_data	{ return(&start_table_item('TD',@_)); }
sub end_table_data	{ return(&end_table_item('TD',@_)); }
sub start_table_hdr	{ return(&start_table_item('TH',@_)); }
sub end_table_hdr	{ return(&end_table_item('TH',@_)); }

#
# Build table item entries (TR, TD & TH)
#
sub start_table_item {
	my $str = "<$_[0] ";
	shift;
	my %params = @_;
	my $tmp;

	$str .= "VALIGN=\"$tmp\" " if ($tmp = $params{'valign'});
	$str .= "ALIGN=\"$tmp\" " if ($tmp = $params{'align'});
	$str .= "BGCOLOR=\"$tmp\" " if ($tmp = $params{'bgcolor'});
	$str .= "COLSPAN=\"$tmp\" " if ($tmp = $params{'colspan'});
	$str .= "ROWSPAN=\"$tmp\" " if ($tmp = $params{'rowspan'});
	$str .= "NOWRAP " if ($tmp = $params{'nowrap'});

	$str .= '>';
	return ($str);
}
sub end_table_item {
	return "</$_[0]>\n";
}

#
# start_table - Start HTML3 table
#
# Arguments are passed by name:
#	border - Width of border
#	cellpadding - Set cell padding
#	cellspacing - Set internal cell spacing
#	width - width of table (pixels of % of screen)
#	caption - Caption for table
#	caption_align - Alignment for table caption
#
sub start_table {
	my %params = @_;
	my $str = '<TABLE ';
	my $tmp;

	$str .= "BORDER=\"$tmp\" " if ($tmp = $params{'border'});
	$str .= "CELLPADDING=\"$tmp\" " if ($tmp = $params{'cellpadding'});
	$str .= "CELLSPACING=\"$tmp\" " if ($tmp = $params{'cellspacing'});
	$str .= "WIDTH=\"$tmp\" " if ($tmp = $params{'width'});
	$str .= '> ';
	if ($params{'caption'}) {
		$str .= '<CAPTION ';
		$str .= "ALIGN=\"$tmp\" " if ($tmp = $params{'caption_align'});
		$str .= '>';
		$str .= $params{'caption'};
		$str .= '</CAPTION> ';
	}
	return "$str\n";
}
#
# end_table - End table
#
sub end_table {
	return "</TABLE>\n";
}
#
# End %M%
