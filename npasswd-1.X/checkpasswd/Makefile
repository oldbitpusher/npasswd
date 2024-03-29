
# --------------------------------------------------------------------  #
#                                                                       #
#                         Author: Clyde Hoover                          #
#                          Computation Center                           #
#                   The University of Texas at Austin                   #
#                          Austin, Texas 78712                          #
#                         clyde@emx.utexas.edu                          #
#                   uunet!cs.utexas.edu!ut-emx!clyde                    #
#                                                                       #
#This code may be distributed freely, provided this notice is retained. #
#                                                                       #
# --------------------------------------------------------------------  #
#
#	Makefile for checkpasswd (application & library)
#
#	@(#)Makefile	1.3 1/27/92 (cc.utexas.edu)
#
BINDIR	= /usr/local
ADMDIR	= /usr/adm
DIR	= .

APPNAME	= checkpasswd
LIBNAME = checkpasswd.a

DEBUG	= -g -DDEBUG
# Set the following two lines to $(DEBUG) for debugging
CFLAGS	= -O
LDFLAGS	= 

# If building with NDBM, use these lines 
ZLIB	=
DBM	= -DNDBM

#
# Source files
#
SOURCES = checkpasswd.h \
	checkpasswd.c \
	main.c \
	pwck_dict.c \
	pwck_passwd.c \
	pwck_lexical.c \
	pwck_local.c \
	util.c
#
# Object files
#
OBJECTS = checkpasswd.o \
	pwck_dict.o \
	pwck_passwd.o \
	pwck_lexical.o \
	pwck_local.o \
	util.o

APPMAIN = main.o
LIBMAIN	= libmain.o

all:	$(APPNAME) $(LIBNAME) dict

$(APPNAME): $(APPMAIN) $(OBJECTS)
	cc -o $(APPNAME) $(LDFLAGS) main.o $(OBJECTS)

$(LIBNAME): 	$(LIBMAIN) $(OBJECTS)
	-rm -f $(LIBNAME)
	ar cr $(LIBNAME) $(LIBMAIN) $(OBJECTS)
	ranlib $(LIBNAME)

#
# If not using NDBM from libc, link in $(ZLIB) here
#
pwck_dict.o: pwck_dict.c checkpasswd.h $(ZLIB)
	$(CC) $(CFLAGS) $(DBM) -c pwck_dict.c
	-@if [ -n "$(ZLIB)" ]; then\
		set -x;\
		$(LD) -r $*.o -o $*.x $(ZLIB);\
		mv $*.x $*.o;\
	fi

#
# Local library linked to this module to simplify rest of make procedure
# (UTEXAS CC only). 
#
UILIB	= /usr/local/lib/libuserinfo.a
pwck_passwd.o: pwck_passwd.c checkpasswd.h
	-@if [ -f $(UILIB) ]; then \
		set -e;\
		echo $(CC) $(CFLAGS) -DUTEXAS_CC -c $<;\
		$(CC) $(CFLAGS) -DUTEXAS_CC -c $<;\
		echo $(LD) -r $*.o -o $*.x $(UILIB);\
		$(LD) -r $*.o -o $*.x $(UILIB);\
		echo mv $*.x $*.o;\
		mv $*.x $*.o;\
	else \
		echo $(CC) $(CFLAGS) -c $<;\
		$(CC) $(CFLAGS) -c $<;\
	fi

clean:
	rm -f *.o a.out checkpasswd core makedict viewdict $(LIBNAME)

dict:	makedict viewdict

makedict:	makedict.c
	$(CC) $(CFLAGS) -o makedict makedict.c

viewdict:	viewdict.c
	$(CC) $(CFLAGS) -o viewdict viewdict.c

install:	checkpasswd
	install -s checkpasswd $(BINDIR)
	install -c -m 0644 checkpasswd.cf $(ADMDIR)
 
# ------------------------------------------------------------------
#
# Source dependancies
#
checkpasswd.o: checkpasswd.c checkpasswd.h
main.o: main.c checkpasswd.h version.h
libmain.o: libmain.c checkpasswd.h
pwck_lexical.o: pwck_lexical.c checkpasswd.h
pwck_local.o: pwck_local.c checkpasswd.h
util.o: util.c checkpasswd.h
#
# End Makefile
