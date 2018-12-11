#!/bin/ksh

cd /usr/lib/passwd/dictionaries || { print "ERROR: could not compile dictionaries"; exit -1; }

(
print Antworth
print CIS
print CRL-Words
print Congress
print Domains
print Dosref
print Ethnologue
print Family-Names
print Ftpsites
print Given-Names 
print Jargon 
print Koran 
print LCarrol 
print Movies 
print Muffet-Words
print Paradise-Lost
print Python 
print Roget-Words 
print Trek 
print Unabr-Dict 
print Unix-Dict 
print World-Factbook
print Zipcodes
) | \
while read dict
do
	/usr/lib/passwd/bin/makedict -o $dict $dict
done

##END
