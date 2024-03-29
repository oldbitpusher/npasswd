########################################################################
# Makefile generated from Makefile.SH on Tue Apr 10 16:35:21 CDT 2001

SHELL = /bin/sh
JMAKE = jmake
TOP = ../
CURRENT = src
DIR = src/
INSTALL = $(TOP)/install

########################################################################
# Parameters set by Configure -- edit config.sh if changes are needed

CC = cc
CTAGS = ctags
JCFLAGS = $(CFLAGS) -O +z 
JLDFLAGS = $(LDFLAGS) -O 
LIBS = -lnet -lnsl
LINT = lint
MAKE = make
MKDEP = /admin/pam_strong/source/npasswd-2.05-HPUX/mkdep $(DPFLAGS) --
MV = /usr/bin/mv
RM = /usr/bin/rm -f
SED = /usr/bin/sed

########################################################################
# Automatically generated parameters -- do not edit

X_CCDEBUG =  -g
X_COPT =  -O
X_CFLAGS =  +z -DOS_HPUX -D_HPUX_SOURCE -DOS_NAME=hpux -DOS_MAJOR_VERSION=b -DOS_MINOR_VERSION=11 $(INCLUDE_PATH)
X_LDFLAGS =  
X_LOCAL_CFLAGS =
LOCAL_FLAGS =  Makefile.local
JCFLAGS =  $(X_CFLAGS) $(X_COPT) $(X_LOCAL_CFLAGS)
JLDFLAGS =  $(X_LDFLAGS) $(X_LOCAL_CFLAGS)
LNS =  /usr/bin/ln -s
DPFLAGS =  $(INCLUDE_PATH)
LINTFLAGS =  $(X_CFLAGS) +z
INCLUDE_PATH =  -I.. -ICommon -IPasswordCheck -IMethods
SYSTEM_PROGS =  /sbin/passwd /usr/bin/chfn /usr/bin/chsh /usr/bin/nispasswd /usr/bin/passwd /usr/bin/yppasswd 
NPASSWD_HOME =  /usr/lib/passwd/lib
REPLACE_SYSTEM_PROGS =  undef
SUBDIRS = Scripts
OBJECTS =   $(NPASSWD_OBJ) $(LIB_METHOD) $(LIB_PWCK) $(LIB_COMOBJ)
SOURCES =   $(NPASSWD_SRC)

########################################################################
# New suffixes and associated building rules -- edit with care

.c.o:
	$(CC) -c $(JCFLAGS) $<

########################################################################
# Jmake rules for building libraries, programs, scripts, and data files
# $X-Id: Jmake.rules,v 3.0.1.5 1995/09/25 09:07:19 ram Exp $

########################################################################
# Force 'make depend' to be performed first -- do not edit

.FORCE_DEPEND::

all:: .FORCE_DEPEND

########################################################################
# Start of Jmakefile
#
# Copyright 1998, The University of Texas at Austin ("U. T. Austin").
# All rights reserved.
#
# By using this software the USER indicates that he or she has read,
# understood and will comply with the following:
#
# U. T. Austin hereby grants USER permission to use, copy, modify, and
# distribute this software and its documentation for any purpose and
# without fee, provided that:
#
# 1. the above copyright notice appears in all copies of the software
#    and its documentation, or portions thereof, and
# 2. a full copy of this notice is included with the software and its
#    documentation, or portions thereof, and
# 3. neither the software nor its documentation, nor portions thereof,
#    is sold for profit. Any commercial sale or license of this software,
#    copies of the software, its associated documentation and/or
#    modifications of either is strictly prohibited without the prior
#    consent of U. T. Austin.
#
# Title to copyright to this software and its associated documentation
# shall at all times remain with U. T. Austin. No right is granted to
# use in advertising, publicity or otherwise any trademark, service
# mark, or the name of U. T. Austin.
#
# This software and any associated documentation are provided "as is,"
# and U. T. AUSTIN MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESSED OR
# IMPLIED, INCLUDING THOSE OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR
# PURPOSE, OR THAT USE OF THE SOFTWARE, MODIFICATIONS, OR ASSOCIATED
# DOCUMENTATION WILL NOT INFRINGE ANY PATENTS, COPYRIGHTS, TRADEMARKS OR
# OTHER INTELLECTUAL PROPERTY RIGHTS OF A THIRD PARTY. U. T. Austin, The
# University of Texas System, its Regents, officers, and employees shall
# not be liable under any circumstances for any direct, indirect, special,
# incidental, or consequential damages with respect to any claim by USER
# or any third party on account of or arising from the use, or inability
# to use, this software or its associated documentation, even if U. T.
# Austin has been advised of the possibility of those damages.
#
# Submit commercialization requests to: Office of the Executive Vice
# President and Provost, U. T. Austin, 201 Main Bldg., Austin, Texas,
# 78712, ATTN: Technology Licensing Specialist.
#
# @(#)Jmakefile	1.27 11/13/98 (cc.utexas.edu)
#

#
# This file is auto-generated from Makefile.SH - all persistent
# changes should be made there.
#
# Makefile.SH is itself generated from "Jmakefile" by jmake.
#
# Jmakefile is included in the developer kit.
# See the Npasswd Support Guide (Support.html).
#

X_SUBDIRS = Common PasswordCheck Methods
ALL_SUBDIRS = $(SUBDIRS) $(X_SUBDIRS)

#
# Sub directories & sub libraries
#
LIB_METHOD = Methods/libmethod.a
LIB_PWCK = PasswordCheck/libpwcheck.a
LIB_COMOBJ = Common/libcomobj.a

# Mode and ownership for npasswd binary
NPASSWD_MODE =	04111
NPASSWD_OWNER =	root

# The main source components of npasswd
NPASSWD_SRC = \
	version.c \
	main.c \
	configure.c \
	passwd.c \
	chfn.c \
	chsh.c

# The main object components of npasswd
NPASSWD_OBJ = \
	version.o \
	main.o \
	configure.o \
	passwd.o \
	chfn.o \
	chsh.o 

#
# all
#  Build everything here and in subdirectories
#
## all:  Build everything here and in subdirectories

#
# Link the master config file into this directory for convenience
#

#
# config.h
#  Link ../config.h to here
#
## config.h:  Link ../config.h to here

all:: config.h

local_realclean::
	$(RM) config.h

config.h: ../config.h
	$(RM) $@
	$(LNS) $? $@

#
# npasswd
#  Build npasswd
#
## npasswd:  Build npasswd

all:: npasswd

local_realclean::
	$(RM) npasswd

npasswd:  $(NPASSWD_OBJ) $(LIB_METHOD) $(LIB_PWCK) $(LIB_COMOBJ)
	$(RM) $@
	if test -f $@; then $(MV) $@ $@~; else exit 0; fi
	$(CC) -o $@  $(NPASSWD_OBJ) $(LIB_METHOD) $(LIB_PWCK) $(LIB_COMOBJ) $(JLDFLAGS) $(LIBS)

#
# install
# 	Install npasswd and installs in subdirectories
#
## install: 	Install npasswd and installs in subdirectories

#
# deinstall
# 	Remove npasswd and deinstall in subdirectories
#
## deinstall: 	Remove npasswd and deinstall in subdirectories

.FORCE:

install:: .FORCE
	cd PasswordCheck; $(MAKE) $(MFLAGS) install

deinstall:: .FORCE
	cd PasswordCheck; $(MAKE) $(MFLAGS) deinstall

#
# Put the binary into the npasswd install directory,
#
install:: install-npasswd install-links

#
# install-npasswd
#  Install npasswd binary only
#
## install-npasswd:  Install npasswd binary only
install-npasswd:	npasswd
	$(INSTALL) -c -o $(NPASSWD_OWNER) -m $(NPASSWD_MODE) \
		npasswd $(NPASSWD_HOME)

#
# install-links
#  Make npasswd links if replacing system programs
#
## install-links:  Make npasswd links if replacing system programs
#
#	Link/symlink/copy to the other places it needes to live.
#	The original versions of the system passwd/chfn/chsh
#	programs are saved if the "replace" option is set in config.sh.
#
install-links:	npasswd
	@if [ "$(REPLACE_SYSTEM_PROGS)" = define ]; then \
		echo Replacing system programs;\
		Scripts/savefiles $(SYSTEM_PROGS); \
		Scripts/installmany $(NPASSWD_HOME)/npasswd $(SYSTEM_PROGS); \
	 fi

#
# deinstall
#  Restore system passwd programs and remove npasswd
#
## deinstall:  Restore system passwd programs and remove npasswd
deinstall:: backdown
	$(RM) $(NPASSWD_HOME)/npasswd

#
# backdown
#  Restore system passwd programs if saved by install
#
## backdown:  Restore system passwd programs if saved by install
backdown::
	@if [ "$(REPLACE_SYSTEM_PROGS)" = define ]; then \
		echo Restoring system programs;\
		Scripts/restorefiles; \
	fi;\
	exit 0


version.c: version.c.SH
	@$(RM) version.c
	@sh version.c.SH

version.c.SH:
	@exit 0;



options.h: options.h.SH
	@$(RM) options.h
	@sh options.h.SH

options.h.SH:
	@exit 0;


#
# Dependancies on things in subdirectories
#

$(LIB_PWCK):: .FORCE
	cd PasswordCheck; $(MAKE) $(MFLAGS) all

Methods/libmethod.a: .FORCE
	cd Methods; $(MAKE) $(MFLAGS) libmethod.a

Common/libcomobj.a: .FORCE
	cd Common; $(MAKE) $(MFLAGS) libcomobj.a

# ---------------------------------------------------------------
# Set compile flags to build debug and test versions
# ---------------------------------------------------------------
include $(LOCAL_FLAGS)

#
# debug-none
# Set Makefile to build production binary
##_ debug-none: Set Makefile to build production binary
#
debug-none::
	@$(RM) -f $(LOCAL_FLAGS)
	@cp /dev/null $(LOCAL_FLAGS)
	@echo "Set flags in $(CURRENT) to build production binary (test off)"
	@echo "Do \"make realclean\" to remove old objects

#
# debug-dbx
#	Set Makefile to build debugger friendly binary)
##_ debug-dbx:	Set Makefile to build debugger friendly binary)
#
debug-dbx::
	@$(RM) -f $(LOCAL_FLAGS)
	@echo 'X_LOCAL_CFLAGS = ${X_CCDEBUG} -DCDEBUG=1' > ${LOCAL_FLAGS}
	@echo 'X_COPT='	>> ${LOCAL_FLAGS}
	@echo "Set flags in $(CURRENT) to build debugger friendly binary (test level 1)"
	@echo "Do \"make realclean\" to remove old objects

#
# debug-files
# Set Makefile to build binary which uses local files)
##_ debug-files: Set Makefile to build binary which uses local files
#
debug-files::
	@$(RM) -f $(LOCAL_FLAGS)
	@echo 'X_LOCAL_CFLAGS = ${X_CCDEBUG} -DCDEBUG=2' > $(LOCAL_FLAGS)
	@echo 'X_COPT=' >> $(LOCAL_FLAGS)
	@echo "Set flags in $(CURRENT) to build binary which uses local files (test level 2)"
	@echo "Do \"make realclean\" to remove old objects

#
# debug-system
#	Set Makefile to build non-production test binary
##_ debug-system:	Set Makefile to build non-production test binary
#
debug-system::
	@$(RM) -f $(LOCAL_FLAGS)
	@echo 'X_LOCAL_CFLAGS = ${X_CCDEBUG} -DCDEBUG=3' > $(LOCAL_FLAGS)
	@echo 'X_COPT='	>> $(LOCAL_FLAGS)
	@echo "Set flags in $(CURRENT) to build non-production test binary (test level 3)"
	@echo "Do \"make realclean\" to remove old objects

# Have "make depend" reset compile flags

depend::
	-@cp /dev/null $(LOCAL_FLAGS)

# ---------------------------------------------------------------
# Set debugging flags in sub-directories
# ---------------------------------------------------------------
debug-none::
	cd Scripts; $(MAKE) $(MFLAGS) debug-none

debug-dbx::
	cd Scripts; $(MAKE) $(MFLAGS) debug-dbx

debug-files::
	cd Scripts; $(MAKE) $(MFLAGS) debug-files

debug-system::
	cd Scripts; $(MAKE) $(MFLAGS) debug-system

debug-none::
	cd Common; $(MAKE) $(MFLAGS) debug-none

debug-dbx::
	cd Common; $(MAKE) $(MFLAGS) debug-dbx

debug-files::
	cd Common; $(MAKE) $(MFLAGS) debug-files

debug-system::
	cd Common; $(MAKE) $(MFLAGS) debug-system

debug-none::
	cd PasswordCheck; $(MAKE) $(MFLAGS) debug-none

debug-dbx::
	cd PasswordCheck; $(MAKE) $(MFLAGS) debug-dbx

debug-files::
	cd PasswordCheck; $(MAKE) $(MFLAGS) debug-files

debug-system::
	cd PasswordCheck; $(MAKE) $(MFLAGS) debug-system

debug-none::
	cd Methods; $(MAKE) $(MFLAGS) debug-none

debug-dbx::
	cd Methods; $(MAKE) $(MFLAGS) debug-dbx

debug-files::
	cd Methods; $(MAKE) $(MFLAGS) debug-files

debug-system::
	cd Methods; $(MAKE) $(MFLAGS) debug-system


#
# lint
#  Check C sources with lint
#
## lint:  Check C sources with lint

lint:
	$(LINT) $(LINTFLAGS) $(SOURCES) $(LINTLIBS)

xsubdirs::
	@case '${MFLAGS}' in *[ik]*) set +e;; esac; \
	for i in $(X_SUBDIRS) ;\
	do \
	(cd $$i ; echo $(VERB) "in $(DIR)$$i..."; \
	$(MAKE) $(MFLAGS) $(FLAGS) $(TARGET)); \
	done

depend:: ..//mkdep

..//mkdep:
	@echo "You have to run Configure in $(TOP) first."; exit 1

depend::
	($(SED) '/^# DO NOT DELETE/q' Makefile && \
	$(MKDEP) $(SOURCES) | \
	$(SED) -e 's/: \.\//: /; s/\/usr\/include[^ ]*//g' -e '/: *$$/d' \
	) > Makefile.new
	cp Makefile Makefile.bak
	cp Makefile.new Makefile
	$(RM) Makefile.new

depend::
	@case '${MFLAGS}' in *[ik]*) set +e;; esac; \
	for i in $(ALL_SUBDIRS) ;\
	do \
	(cd $$i ; echo "Depending" "in $(DIR)$$i..."; \
	$(MAKE) $(MFLAGS)  depend); \
	done

tags::
	$(CTAGS) -w *.[ch]
	$(CTAGS) -xw *.[ch] > tags

local_clobber::
	$(RM) tags


sub_clean::
	@$(MAKE) xsubdirs TARGET=clean VERB=clean FLAGS=$(FLAGS)

sub_realclean::
	@$(MAKE) xsubdirs TARGET=realclean VERB=realclean FLAGS=$(FLAGS)

sub_clobber::
	@$(MAKE) xsubdirs TARGET=clobber VERB=clobber FLAGS=$(FLAGS)

########################################################################
# Common rules for all Makefiles -- do not edit

emptyrule::

clean: sub_clean local_clean
realclean: sub_realclean local_realclean
clobber: sub_clobber local_clobber

local_clean::
	$(RM) core *~ *.o

local_realclean:: local_clean

local_clobber:: local_realclean
	$(RM) Makefile config.sh

Makefile.SH: Jmakefile
	-@if test -f $(TOP)/.package; then \
	if test -f Makefile.SH; then \
	echo "	$(RM) Makefile.SH~; $(MV) Makefile.SH Makefile.SH~"; \
	$(RM) Makefile.SH~; $(MV) Makefile.SH Makefile.SH~; \
	fi; \
	echo "	$(JMAKE) -DTOPDIR=$(TOP) -DCURDIR=$(CURRENT)" ; \
	$(JMAKE) -DTOPDIR=$(TOP) -DCURDIR=$(CURRENT) ; \
	else exit 0; fi

Makefile: Makefile.SH
	/bin/sh Makefile.SH

Jmakefile:

tags::
	$(CTAGS) -w *.[ch]
	$(CTAGS) -xw *.[ch] > tags

local_clobber::
	$(RM) tags

########################################################################
# Rules for building in sub-directories -- do not edit

subdirs:
	@case '${MFLAGS}' in *[ik]*) set +e;; esac; \
	for i in $(SUBDIRS) ;\
	do \
	(cd $$i ; echo $(VERB) "in $(DIR)$$i..."; \
	$(MAKE) $(MFLAGS) $(FLAGS) $(TARGET)); \
	done

install::
	@$(MAKE) subdirs TARGET=install VERB="Installing" FLAGS=

deinstall::
	@$(MAKE) subdirs TARGET=deinstall VERB="Deinstalling" FLAGS=

install.man::
	@$(MAKE) subdirs TARGET=install.man VERB="Installing man pages" FLAGS=

deinstall.man::
	@$(MAKE) subdirs TARGET=deinstall.man VERB="Deinstalling man pages" FLAGS=

sub_clean::
	@$(MAKE) subdirs TARGET=clean VERB="Cleaning" FLAGS=
	@echo "Back to $(CURRENT) for "clean...

sub_realclean::
	@$(MAKE) subdirs TARGET=realclean VERB="Real cleaning" FLAGS=
	@echo "Back to $(CURRENT) for "realclean...

sub_clobber::
	@$(MAKE) subdirs TARGET=clobber VERB="Clobbering" FLAGS=
	@echo "Back to $(CURRENT) for "clobber...

tag::
	@case '${MFLAGS}' in *[ik]*) set +e;; esac; \
	for i in $(SUBDIRS) ;\
	do \
	(cd $$i ; echo "Tagging" "in $(DIR)$$i..."; \
	$(MAKE) $(MFLAGS)  tag); \
	done

Makefiles::
	@case '${MFLAGS}' in *[ik]*) set +e;; esac; \
	for i in $(SUBDIRS);\
	do \
	echo "Making "Makefiles" in $(DIR)$$i..."; \
	(cd $$i || exit 1; \
	if test ! -f Makefile; then /bin/sh Makefile.SH; fi; \
	$(MAKE) $(MFLAGS) Makefiles) \
	done

Makefiles.SH:: Makefile.SH
	@case '${MFLAGS}' in *[ik]*) set +e;; esac; \
	for i in $(SUBDIRS);\
	do \
	case "$(DIR)$$i/" in \
	*/*/*/*/) newtop=../../../..;; \
	*/*/*/) newtop=../../..;; \
	*/*/) newtop=../..;; \
	*/) newtop=..;; \
	esac; \
	case "$(TOP)" in \
	/*) newtop="$(TOP)" ;; \
	esac; \
	echo "Making Makefiles.SH in $(DIR)$$i..."; \
	(cd $$i || exit 1; $(MAKE) $(MFLAGS) -f ../Makefile \
	Makefile TOP=$$newtop CURRENT=$(DIR)$$i;\
	$(MAKE) $(MFLAGS) Makefiles.SH) \
	done

all::
	@$(MAKE) subdirs TARGET=all VERB="Making all" FLAGS=

########################################################################
# Dependencies generated by make depend
# DO NOT DELETE THIS LINE -- make depend relies on it
version.o: version.c
main.o: Common/common.h
main.o: Common/pw_svc.h
main.o: compatibility.h
main.o: config.h
main.o: constants.h
main.o: defines.h
main.o: main.c
main.o: npasswd.h
main.o: options.h
configure.o: Common/common.h
configure.o: PasswordCheck/checkpassword.h
configure.o: compatibility.h
configure.o: config.h
configure.o: configure.c
configure.o: constants.h
configure.o: defines.h
configure.o: npasswd.h
configure.o: options.h
passwd.o: Common/common.h
passwd.o: Common/pw_svc.h
passwd.o: Methods/pwm_defs.h
passwd.o: PasswordCheck/checkpassword.h
passwd.o: compatibility.h
passwd.o: config.h
passwd.o: constants.h
passwd.o: defines.h
passwd.o: npasswd.h
passwd.o: options.h
passwd.o: passwd.c
chfn.o: Common/common.h
chfn.o: Common/pw_svc.h
chfn.o: Methods/pwm_defs.h
chfn.o: chfn.c
chfn.o: compatibility.h
chfn.o: config.h
chfn.o: constants.h
chfn.o: defines.h
chfn.o: npasswd.h
chfn.o: options.h
chsh.o: Common/common.h
chsh.o: Common/pw_svc.h
chsh.o: Methods/pwm_defs.h
chsh.o: chsh.c
chsh.o: compatibility.h
chsh.o: config.h
chsh.o: constants.h
chsh.o: defines.h
chsh.o: npasswd.h
chsh.o: options.h
