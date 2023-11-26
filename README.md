# npasswd
A relic from the 90's - a password change program which vetted the password and kept you from setting really dumb ones.

By one perspective, **npasswd** shoud never have existed.  Should never needed to exist.  But UNIX was very naive in the 1980s, still thinking it was running on computers where people were smart enough to create decent passwords and no one halfway across the world was trying to hammer their way in.

That changed with the [Morris Worm of November 1988|https://en.wikipedia.org/wiki/Morris_worm].  One of the ways the worm spread was password guessing.  Now guess for yourself how many people had passwords which were their login names backward, or replacing 'o' with '0', or something else algorithimcally determinable. 

When the "With Microscope and Tweezers: An Analysis of the Internet Virus of November 1988" http://www.mit.edu/people/eichin/virus/main.html came out, I read the description of how the password guessing was done and decided to write code to detect those kind of passwords.  With that in hand, we swept our own passwd files and were unpleasantly suprised at how many bad passwords were lurking, just waiting for a bot or someone with a lot of time on their hands.

We disabled those users, requiring them to appear at the Help Desk for the lecture and setting of a new, less vulnerable password.  Of course the problem going forward is that 'passwd' still didn't screen out bad passwords.  So I decided to write code to take care of that.  Orginally I pretty much swiped the passwd source code and starting stuffing 'features' into it for better password checking.  That happened a lot in the frontier days of UNIX, especially for source which had been pried out of the cold dead hands of AT&T - ok, their UNIX wasn't dead yet, but it didn't have that much longer to live.

There are several incarnations of **npasswd** stashed here, because once it went into the wild everyone started hacking on it, adding goodies and otherwise making it smell like whoever they were.

One of the adopters of **npasswd** v1 was the NASA Jet Propulsion Labratory - which is pretty much as close to space as I'll ever get.  That JPL was using my code was a thrill and a half, being a space geek since sitting at home with the measels watching the launch of Mercury-Atlas 6 taking John Glenn into orbit.  Thanks, guys.

Others ported **npasswd** to their specific flavors of UNIX (each vendor also rubbed their faces against UNIX to make it smell like them), and sent me their changes. 

A lot of those mods were useful and/or neat, and were working their way into version 2 which did see the light of day somewhat.  By then, our shop was not interested in running any more custom code than required, and we kept getting new systems running yet another flavor of UNIX and I did not have time to keep up.

Soon the [Pluggable Authenticaion Module|https://en.wikipedia.org/wiki/Pluggable_authentication_module] architecture came along, and a module version of [Crack|https://en.wikipedia.org/wiki/Crack_(password_software)] appeared which did pretty much everything **npasswd** did in the way of filtering out dumb passwords but was an easy drop in instead of build from source and hope for the best.

There was one quite good side-effect of **npasswd** - the technology commericialization office of the University of Texas licensed **npasswd** out to two companies who wanted better password integrity in their products - and I got half of the fee - somewhere around $12,000 in total (long gone to pay early childhood expenses for our nearly 21 year old offspring).

I spent a lot of time working on **npasswd** and remain proud of my work.  It made a difference for UNIX login security on our handful of systems and countless more in the wild.  But finally the UNIX world caught up with me and rendered the program which should never have been needed obsolete.  I did not weep because this meant that all UNIX systems (and their later Linux semi-descendants) would have more secure passwords - and that was all I wanted.

But what is remarkable is that **npasswd** is only around a 1000 lines of code - and that is with copious comments.  Of course when you are not taking into consideration building your program on a plethora of UNIX distributions, you don't need all those "#ifdef some-bloody-variant" blocks.  The ill-fated 2.0 was substantially more rotund because of multi-platform support.   

I am impressed at the level of C programming I did back then - and how simple and quaint it is in comparison to modern C.  The compilers of that time were much simpler (although the C preprocessor was the best macro engine available).  In fact, I'm pretty sure that GCC would spit my old code out with a plethora of warnings, deprecation notices and outright errors.  And the entire infrastructure beneath it has changed from "classic UNIX" to some variant of Linux - I doubt that most of the header files needed even exist anymore.

I could write an entire treatise about the "Old Days of UNIX" where every vendor had to take the baseline distribution and pee on it so it would smell like them.  Of course there often were real technology differences as vendors "fix" various problems and - of course once again - add more "features" which made their UNIX unique and a pain in the ass to make use of - and you had to do it their way in order to change user passwords.  So happy not to be doing this kind of work - and besides, if you write something that runs on one Linux distro, the source should compile without trouble and quite likely a foriegn binary would run just fine.

Writing software is akin to building sand castles on the beach - except you never know when the next high tide is, nor how high it will be - but you can be sure the tide will rise and your fine castle of silica grains will be swept away, leaving only a project archived on GitHub.

But you know - I spent 43 years building some damn fine sand castles.  Proud of every one of them.

