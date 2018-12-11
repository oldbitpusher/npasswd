h48406
s 00051/00033/00019
d D 1.2 98/04/02 10:25:18 clyde 2 1
c Convert to cracklib 2.7 version
e
s 00053/00000/00000
d D 1.1 96/08/09 16:29:41 clyde 1 0
c date and time created 96/08/09 16:29:41 by clyde
e
u
U
f e 0
t
T
I 1
#!/usr/local/bin/perl
#
D 2
# %W% %G% (cc.utexas.edu 
E 2
I 2
# %W% %G% (cc.utexas.edu)
E 2
#
###
D 2
# This program is copyright Alec Muffett 1993. The author disclaims all
E 2
I 2
# This program is copyright Alec Muffett 1997. The author disclaims all
E 2
# responsibility or liability with respect to it's usage or its effect
# upon hardware or computer systems, and maintains copyright as set out
D 2
# in the "LICENCE" document which accompanies distributions of Crack v4.0
E 2
I 2
# in the "LICENCE" document which accompanies distributions of Crack v5.0
E 2
# and upwards.
###

D 2
sub ByLen {
	length($a) <=> length($b);
}
E 2
I 2
%perms = ();
E 2

D 2
@a1 = ('/$s$s', '/0s0o', '/1s1i', '/2s2a', '/3s3e', '/4s4h');
@a2 = ('/$s$s', '/0s0o', '/1s1l', '/2s2a', '/3s3e', '/4s4h');
@a3 = ('/$s$s', '/0s0o', '/1s1i', '/2s2a', '/3s3e', '/4s4a');
@a4 = ('/$s$s', '/0s0o', '/1s1l', '/2s2a', '/3s3e', '/4s4a');
E 2
I 2
sub Permute
{
    my $depth = shift;
    my $i;
E 2

D 2
sub Permute {
	local(@args) = @_;
	local($prefix);
E 2
I 2
    if ($depth == 0)
    {
	@stack = ();
    }
    for ($i = 0; $i <= $#set; $i++)
    {
	$stack[$depth] = $set[$i];
E 2

D 2
	while ($#args >= 0)
E 2
I 2
	if ($depth == $#set)
E 2
	{
D 2
		@foo = @args;
		$prefix = "";

		while ($#foo >= 0)
		{
			foreach (@foo)
			{
				$foo{"$prefix$_"}++;
			}
			$prefix .= shift(@foo);
		}

		shift(@args);
E 2
I 2
	    %output = ();
	    foreach (@stack) 
	    { 
		$output{$_}++; 
	    }
	    $perm = join(" ", sort(keys(%output)));
	    $perms{$perm}++;
E 2
	}
I 2
	else
	{
	    &Permute($depth + 1);
	}
    }
E 2
}

D 2
&Permute(@a1);
&Permute(@a2);
&Permute(@a3);
&Permute(@a4);
E 2
I 2
@maps = ([ '/$s$s', '/0s0o', '/2s2a', '/3s3e', '/5s5s', '/1s1i', '/4s4a' ],
	 [ '/$s$s', '/0s0o', '/2s2a', '/3s3e', '/5s5s', '/1s1i', '/4s4h' ],
	 [ '/$s$s', '/0s0o', '/2s2a', '/3s3e', '/5s5s', '/1s1l', '/4s4a' ],
	 [ '/$s$s', '/0s0o', '/2s2a', '/3s3e', '/5s5s', '/1s1l', '/4s4h' ]);
E 2

D 2
foreach $key (sort ByLen (keys(%foo)))
E 2
I 2
@set = (0 .. 5);

# why be elegant when you can use brute force?  moreover, it's easier
# to think brute-force at 1am in the morning, and leaves you with time
# for coffee...

&Permute(0);

foreach $perm (sort(keys(%perms)))
E 2
{
D 2
	print $key, "\n";
E 2
I 2
    foreach $aref (@maps)
    {
	foreach $i (split(" ", $perm))
	{
	    print ${$aref}[$i];
	}
	print "\n";
    }
E 2
}
I 2

exit 0;
E 2
E 1
