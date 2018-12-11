#	Makefile for checkpasswd (application & library)
BINDIR	= /usr/local
ADMDIR	= /usr/adm
DIR	= .

APPNAME	= checkpasswd
LIBNAME = checkpasswd.a
MAKEFNAME = MakeBlf

# Set VOWEL_STRIP to check vowel-stripped words ("mysterious" --> "mystrs")
# VOWEL_STRIP = -DVOWEL_STRIP
VOWEL_STRIP =

# Set LONG_REVERSE to check reversed words > 8 characters
#    ("mysterious" --> "suoirets")
# LONG_REVERSE = -DLONG_REVERSE
LONG_REVERSE =

# For debugging
DEBUG	= -g -DDEBUG
# DEBUG = 

FLAGS = $(DEBUG) $(LONG_REVERSE) $(VOWEL_STRIP)
CFLAGS	= $(FLAGS)
LDFLAGS	= $(FLAGS)

# Object files

OBJECTS = checkpasswd.o \
	pwck_lexical.o \
	pwck_local.o \
	pwck_passwd.o \
	pwck_finger.o \
	pwck_dict.o \
	util.o \
	Mycroft.o \
	CCStr.o \
	CFStr.o \
	Blf.o \
	BitArray.o \
	Hash.o \
	Queue.o \
	Util.o \
	Iter.o \
	CFText.o \
	Finger.o

APPMAIN = main.o
LIBMAIN	= libmain.o
MAKEFMAIN = MakeBlf.o

all:	$(APPNAME) $(LIBNAME) $(MAKEFNAME) 

$(APPNAME): $(APPMAIN) $(LIBNAME)
	cc -o $(APPNAME) $(LDFLAGS) $(APPMAIN) $(LIBNAME) -lm

$(LIBNAME): 	$(OBJECTS)
	-rm -f $(LIBNAME)
	ar cr $(LIBNAME) $(OBJECTS)
	ranlib $(LIBNAME)
    
$(MAKEFNAME): $(MAKEFMAIN) $(LIBNAME)
	cc -o $(MAKEFNAME) $(LDFLAGS) $(MAKEFMAIN) $(LIBNAME) -lm

clean:
	rm -f *.o a.out core $(APPNAME) $(MAKEFNAME) $(LIBNAME)

install:	checkpasswd checkpasswd.cf checkpasswd.filter
	install -s checkpasswd $(BINDIR)
	install -c -m 0644 checkpasswd.cf $(ADMDIR)
	install -c -m 0644 checkpasswd.filter $(ADMDIR)
 
# ------------------------------------------------------------------

# Source dependencies

checkpasswd.o: checkpasswd.c checkpasswd.h
main.o: main.c checkpasswd.h version.h
libmain.o: libmain.c checkpasswd.h
pwck_lexical.o: pwck_lexical.c checkpasswd.h
pwck_local.o: pwck_local.c checkpasswd.h
util.o: util.c checkpasswd.h

pwck_dict.o:	CCStr.h Blf.h Finger.h
main.o:		Blf.h Finger.h

MakeBlf.o:	Global.h MakeBlf.h CFStr.h Blf.h Iter.h
LookBlf.o:	Global.h Blf.h
Blf.o:		Global.h MakeBlf.h Blf.h BitArray.h Hash.h
BitArray.o:	Global.h BitArray.h
CCStr.o:	Global.h CCStr.h
CFStr.o:	Global.h CFStr.h Util.h
Util.o:		Util.h
Hash.o:		Hash.h
Iter.o:		Global.h Iter.h
Queue.o:	Global.h Queue.h
CFText.o:	Global.h CFStr.h CFText.h

# End Makefile
