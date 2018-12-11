# npasswd
A relic from the 90's - a password change program which vetted the password and kept you from setting really dumb ones.

By one perspective, npasswd shoud never have existed.  Should never needed to exist.  But UNIX was very naive in the 1980s, still thinking it was running on computers where people were smart enough to create decent passwords and no one halfway across the world was trying to hammer their way in.

That changed with the Morris Worm of November 1988.  One of the ways the worm spread was password guessing.  Now guess for yourself how many people had passwords which were their login names backward, or replacing 'o' with '0', or something else algorithimcally determinable. 

When the "With Microscope and Tweezers: An Analysis of the Internet Virus of November 1988" http://www.mit.edu/people/eichin/virus/main.html came out, I read the description of how the password guessing was done and decided to write code to detect those kind of passwords.  With that in hand, we swept our own passwd files and were unpleasantly suprised at how many bad passwords were lurking, just waiting for a bot or someone with a lot of time on their hands.

We disabled those users, requiring them to appear at the Help Desk for the lecture and setting of a new, less vulnerable password.  Of course the problem going forward is that 'passwd' still didn't screen out bad passwords.  So I decided to write code to take care of that.  Orginally I pretty much swiped the passwd source code and starting stuffing 'features' into it for better password checking.  That happened a lot in the frontier days of UNIX, especially for source which had been pried out of the cold dead hands of AT&T - ok, their UNIX wasn't dead yet, but it didn't have that much longer to live.


There are several incarnations of npasswd stashed here, because once it went into the wild everyone started hacking on it, adding goodies and otherwise making it smell like whoever they were.

One of the adopters of npasswd v1 was NASA Jet Propulsion Labratory - pretty much as close to space as I'll ever get.

Others ported npasswd to their specific flavors of UNIX (each vendor also rubbed their faces against UNIX to make it smell like them), and sent me their changes. 

A lot of those mods were useful and/or neat, and were working their way into version 2 which did see the light of day somewhat.  By then, our shop was not interested in running any more custom code than required, and we kept getting new systems running yet another flavor of UNIX and I did not have time to keep up.

And finally, PAM came along and the Cracklib module appeared which did pretty much everything npasswd did in the way of filtering out dumb passwprd
