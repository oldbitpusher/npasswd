# With Microscope and Tweezers \- The story of Npasswd

In November of 1988 the infamous **Morris Worm** escaped its playpen and went on a rampage across the Internet, bringing UNIX systems to their knees and causing widespread trouble. Among the Worm's attacks was a password guesser which was fairly clever and unnervingly successful.

The UNIX public systems at The University of Texas at Austin Computation Center escaped being ravaged by the Worm because our main mail gateway at the time was neither a Digital Equipment Corporation VAX nor a Sun Microsystems computer, which ‘The Worm’ was crafted to hack.

The Worm attacked our mail server and the implanted executable code fell on its face so we were spared being subjected to the first wide scale hacking attack on UNIX systems.

Afterwards the Worm was dissected and papers released describing its anatomy (nearly amateurish in comparison to modern security hacks). From these documents I replicated its password cracker, ran it against our password files and got plenty of hits.  Quite a few of our users were “encouraged” to change their passwords to something the cracker could not guess.

I rewrote the cracker into a primitive password checker that I posted to the USENET group **comp.sources.misc** in 1989\.

The UNIX password encryption  function [*crypt(3)*](https://en.wikipedia.org/wiki/Crypt_\(C\)) was considered hard enough to crack, so it was deemed safe to have encrypted passwords visible to all. The Morris Worm invalidated this assumption.

The Worm approached password cracking from a "human engineering" perspective. People are likely to choose passwords which are easy to remember \- such as their login name or phone number. The Worm's password cracker encrypted various plaintext strings and compared them to the encrypted password. The plaintext came from other **/etc/passwd** fields and the UNIX spelling dictionary. This approach was frighteningly successful.

All the UNIX vendors of the time were shipping the primitive V7 *passwd* program which did no significant password validation. This meant the only way to have more secure passwords was to replace it with something smarter. 

Hence I wrote *npasswd,* using my  "worm" password checker as the core.  By late 1989 ***npass*****w*d*** had replaced **/bin/passwd** on all of our public UNIX systems. After a few sweeps with my password checker, some pointed email and other user-unfriendly actions, I and my colleagues breathed easier \- at least for a while.

Around 1991 Alec Muffet released **Crack** and the world changed. It did not attempt to reverse the password encryption, but used a brute force attack similar to that of the Worm. Anyone with a 386 box (the hot commodity system of the time), a C compiler and some patience could crack encrypted passwords at their leisure.

When I  took on integrating Crack into ***npasswd***. I found that it needed serious updating \- the UNIX environment was changing, and there had been plenty of porting problems. I had also learned a lot more about C programming, so I decided that *npasswd* needed an extensive rewrite. That work started in July of 1993, and version 2 was the result.

## The Tide Rolls In

Time rolled on and new UNIX systems came in and management was not keen on replacing supported vendor software with this sporadically supported homebrew program.  More importantly, the UNIX vendors / upstream source providers had started providing a *passwd* utility that was noticeably more picky about what was considered a valid password, and in some cases could be configured by the system administrators.

Another factor in the decline of *npasswd* was the proliferation of UNIX platforms was not possible to keep up with.  This was before the creation of GNU Project build utilities such as *autoconf*, so making one source build on a lot of different platforms became problematic.  My lack of access to development and testing platforms did not help the situation.

So my great creation faded into the land of lost bits (at least in binary form).  Npasswd's last hurrah was in the early 2000s, when the University of Texas Technology marketing office licensed it to a couple of companies for who knows what \- but I received $16,000 in royalties, which was sorely needed to pay the medical bills of our child's first week of life (the neonatal ICU is an awfully expensive daycare center).

Did it bother me that the product of much hard work (and expense of UT paying my salary) was obsolete?  Nope \- I wrote *npasswd* and gave it away because above all I wanted the UNIX community to be more secure, so the more people who used *npasswd* the better.  And when the vendors started supplying intelligent password change programs, all the better. My reaction was "About bloody time".

The advent of the Pluggable Authentication Module (PAM) meant that password policy could be implemented easier \- just write code to check and complain if the password didn't meet requirements.  Let someone else worry about updating the password data in files or NIS or LDAP or Hesiod or whatever the authentication backend is.

*Npasswd* 2.0 was not finished because UNIX vendors had made it obsolete.  It had done its job well and properly stood aside \- yet another beautiful sand castle swept away by the tides.

## Acknowledgments

A lot of people contributed their work to *npasswd* over the years. I received a lot of variants of *npasswd* version 1.3 done by lots of folks. Many of these people provided good ideas and code that went into version 2.0.

Here are some of the more outstanding contributions I can recall:

* Alec Muffet for providing a modular Crack program easily adapted and a copious collection of dictionary words.  
* Paul Leyland of Oxford University, UK provided support for Ultrix enhanced security \- which was also used for OSF/1 support.  
* Donnie Emeson for adding character class diversity requirements to the password lexical check code.  
* Mike Stute for HP-UX support and some improvements to the dictionary lookup password checking.  
* One of the most popular variants of npasswd version 1.3 was produced at NASA Jet Propulsion Laboratory in Pasadena, California. (This thrilled me half to death \- I have been a hardcore space geek since I watched the launch of John Glenn). The guys who did a lot of the JPL work were Dan Kegel, who added Crack password checking and Dave Hayes who added SunOS 4 adjunct password support (among other things).  
* Tomasz Surmacz, Institute of Cybernetics, Technical Technical University of Wroclaw, Poland, contributed password history code.  
* Charles Seeger, University of Florida CIS Department and Steve Swartz, University of Wisconsin for supplying code to include **chfn** and **chsh** functionality.  
* Victor Burns of Texas Instruments for converting the password check engine into a Pluggable Authentication Module. Thanks also to TI for letting him distribute his code.

 There were many more who made suggestions and provided code that wasn't used, but whose comments were appreciated.

## Bibliography

The original source for *npasswd*: [https://github.com/oldbitpusher/npasswd](https://github.com/oldbitpusher/npasswd)

Documents on the Morris Worm:   

* [With Microscope and Tweezers: An Analysis of the Internet Virus of November, 1988 Mark W. Eichin and Jon Rochlis, MIT.](http://www.mit.edu/people/eichin/virus/main.html)  
* [A Tour of the Worm, Donn Seeley, Department of Computer Science, University of Utah](http://www.cs.unc.edu/~jeffay/courses/nidsS05/attacks/seely-RTMworm-89.html).

   Documents on password security (ca 1990):

* Foiling the cracker: A Survey of, and Improvements to, Password Security. Daniel V. Klein, Software Engineering Institute, Carnegie Mellon University.  
* [Password Security: A Case History](http://www.cs.ucf.edu/courses/cop6614/fall2004/Password_Matthew.pdf). Robert Morris and Ken Thompson, AT\&T Bell Laboratories 1978\. Originally part of Volume 2A of the Seventh Edition UNIX Programmers Manual, dated January 1979 and included in the 4.3 BSD System Managers Manual.

[http://en.wikipedia.org/wiki/Crack\_%28password\_software%29](http://en.wikipedia.org/wiki/Crack_%28password_software%29)

## Finally

Npasswd is still out there \- at least in historical form \- ask [Google](https://www.google.com/search?q=npasswd).

   
