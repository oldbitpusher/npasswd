########################################################################
# Makefile generated from Makefile.SH on Tue Apr 10 16:35:22 CDT 2001

SHELL = /bin/sh
JMAKE = jmake
TOP = ../../
CURRENT = src/PasswordCheck
DIR = src/PasswordCheck/
INSTALL = $(TOP)/install

########################################################################
# Parameters set by Configure -- edit config.sh if changes are needed

AR = ar rc
CC = cc
CTAGS = ctags
JCFLAGS = $(CFLAGS) -O +z 
JLDFLAGS = $(LDFLAGS) -O 
LD = ld
LIBS = -lnet -lnsl
LINT = lint
MAKE = make
MKDEP = /admin/pam_strong/source/npasswd-2.05-HPUX/mkdep $(DPFLAGS) --
MV = /usr/bin/mv
RANLIB = :
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
INCLUDE_PATH =  -I.. -I../.. -I../Common -Icracklib
LIB_DIR =  /usr/lib/passwd/lib
SUBDIRS = cracklib
OBJECTS =   $(PWCK_OBJ) $(HIST_OBJ) $(CRACK_OBJ)  pwck_all.o  checkpassword.o version.o $(PUBLIC_A) history_admin.o $(PRIVATE_A) $(COMOBJ) test_pwck.o $(PRIVATE_A) $(COMOBJ) test_history.o $(PRIVATE_A) $(COMOBJ)
SOURCES =   $(PWCK_SRC) $(HIST_SRC)  $(PWCK_SRC) $(HIST_SRC)  checkpassword.c version.c history_admin.c test_pwck.c test_history.c

########################################################################
# New suffixes and associated building rules -- edit with care

.c.o:
	$(RM) $@
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
# @(#)Jmakefile	1.25 07/20/98 (cc.utexas.edu)
#

#
# Makefile for password checker application & library
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

#
# CHECKPW_MODE
# 	Install mode for checkpassword (Variable)
#
## CHECKPW_MODE: 	Install mode for checkpassword (Variable)

#
# CHECKPW_FLAGS
# 	Additional install flags for checkpassword (Variable)
#
## CHECKPW_FLAGS: 	Additional install flags for checkpassword (Variable)
CHECKPW_MODE	= 0555
CHECKPW_FLAGS	=

COMOBJ = ../Common/libcomobj.a

PRIVATE	= pwcheck
PRIVATE_A = lib$(PRIVATE).a

PUBLIC	= checkpassword
PUBLIC_A =  lib$(PUBLIC).a

PWCK_SRC = \
	pwck_main.c \
	pwck_crack.c \
	pwck_history.c \
	pwck_lexical.c \
	pwck_local.c \
	pwck_passwd.c \
	pwck_vicb.c

HIST_SRC = \
	hist_file.c \
	hist_dbm.c \
	hist_nis.c \
	hist_osf.c

PWCK_OBJ = \
	pwck_main.o \
	pwck_crack.o \
	pwck_history.o \
	pwck_lexical.o \
	pwck_local.o \
	pwck_passwd.o \
	pwck_vicb.o

HIST_OBJ = \
	hist_file.o \
	hist_dbm.o \
	hist_nis.o \
	hist_osf.o 

#
# These Cracklib objects are included in the library
# This list needs to match that in cracklib/Makefile
#
CRACK_LIB = cracklib/libcrack.a

CRACK_SRC = \
	cracklib/fascist.c \
	cracklib/packlib.c \
	cracklib/rules.c \
	cracklib/stringlib.c

CRACK_OBJ = \
	cracklib/fascist.o \
	cracklib/packlib.o \
	cracklib/rules.o \
	cracklib/stringlib.o 

#
# Libraries that checkpassword depends upon.
# Make the dependancy upon the *library*, not the *object* files
# to avoid having to have dependancies for every cracklib object.
#

all:: $(CRACK_LIB)

local_realclean::
	$(RM) $(CRACK_LIB)


version.c: version.c.SH
	@$(RM) version.c
	@sh version.c.SH

version.c.SH:
	@exit 0;


#
# The private library - just password check routines
#

all:: lib$(PRIVATE).a

local_realclean::
	$(RM) lib$(PRIVATE).a

lib$(PRIVATE).a:  $(PWCK_OBJ) $(HIST_OBJ) $(CRACK_OBJ)
	$(RM) $@
	$(AR) $@  $(PWCK_OBJ) $(HIST_OBJ) $(CRACK_OBJ)
	$(RANLIB) $@

#
# The public library - including routines from common object lib
#

all:: lib$(PUBLIC).a

local_realclean::
	$(RM) lib$(PUBLIC).a

lib$(PUBLIC).a:  pwck_all.o
	$(RM) $@
	$(AR) $@  pwck_all.o
	$(RANLIB) $@

all:: pwck_all.o

local_realclean::
	$(RM) pwck_all.o

pwck_all.o:  $(PWCK_OBJ) $(HIST_OBJ) $(CRACK_OBJ) $(COMOBJ)
	$(RM) $@
	$(LD) $(JLKFLAGS) -r  $(PWCK_OBJ) $(HIST_OBJ) $(CRACK_OBJ) $(COMOBJ) -o $@

#
# install
#  Install public password check library
#
## install:  Install public password check library

install:: lib$(PUBLIC).a
	$(INSTALL) -c -m 444 lib$(PUBLIC).a  $(LIB_DIR)
	$(RANLIB)  $(LIB_DIR)/lib$(PUBLIC).a

deinstall::
	$(RM)  $(LIB_DIR)/lib$(PUBLIC).a

#
# Build checkpassword application
#

#
# checkpassword
#  Build the password check program
#
## checkpassword:  Build the password check program

all:: checkpassword

local_realclean::
	$(RM) checkpassword

checkpassword:  checkpassword.o version.o $(PUBLIC_A)
	$(RM) $@
	if test -f $@; then $(MV) $@ $@~; else exit 0; fi
	$(CC) -o $@  checkpassword.o version.o $(PUBLIC_A) $(JLDFLAGS) $(LIBS)

#
# install
#  	Install checkpassword application
#
## install:  	Install checkpassword application

install::	checkpassword-install

checkpassword-install:	checkpassword
	$(INSTALL) -c -s -m $(CHECKPW_MODE) $(CHECKPW_FLAGS) checkpassword $(LIB_DIR)

#
# Build history_admin application
#

#
# history_admin
#  Build the history administration program
#
## history_admin:  Build the history administration program

all:: history_admin

local_realclean::
	$(RM) history_admin

history_admin: history_admin.o $(PRIVATE_A) $(COMOBJ)
	$(RM) $@
	if test -f $@; then $(MV) $@ $@~; else exit 0; fi
	$(CC) -o $@ history_admin.o $(PRIVATE_A) $(COMOBJ) $(JLDFLAGS) $(LIBS)

#
# install
# 	Install history_admin application
#
## install: 	Install history_admin application

install:: history_admin
	$(INSTALL) -c -s -m 555  history_admin  $(LIB_DIR)

deinstall::
	$(RM)  $(LIB_DIR)/history_admin

#
# Build Cracklib
#

.FORCE:

cracklib/libcrack.a: .FORCE
	cd  cracklib; $(MAKE) $(MFLAGS) libcrack.a

../Common/libcomobj.a: .FORCE
	cd  ../Common; $(MAKE) $(MFLAGS) libcomobj.a

#
# Build test programs
#

all:: test_pwck

local_realclean::
	$(RM) test_pwck

test_pwck: test_pwck.o $(PRIVATE_A) $(COMOBJ)
	$(RM) $@
	if test -f $@; then $(MV) $@ $@~; else exit 0; fi
	$(CC) -o $@ test_pwck.o $(PRIVATE_A) $(COMOBJ) $(JLDFLAGS) $(LIBS)

all:: test_history

local_realclean::
	$(RM) test_history

test_history: test_history.o $(PRIVATE_A) $(COMOBJ)
	$(RM) $@
	if test -f $@; then $(MV) $@ $@~; else exit 0; fi
	$(CC) -o $@ test_history.o $(PRIVATE_A) $(COMOBJ) $(JLDFLAGS) $(LIBS)

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
# debug-none
##_ debug-none: Set debug level
#

debug-none::
	@$(MAKE) subdirs TARGET=debug-none VERB=debug-none FLAGS=
# debug-dbx
##_ debug-dbx: Set debug level
#

debug-dbx::
	@$(MAKE) subdirs TARGET=debug-dbx VERB=debug-dbx FLAGS=
# debug-files
##_ debug-files: Set debug level
#

debug-files::
	@$(MAKE) subdirs TARGET=debug-files VERB=debug-files FLAGS=
# debug-system
##_ debug-system: Set debug level
#

debug-system::
	@$(MAKE) subdirs TARGET=debug-system VERB=debug-system FLAGS=

depend:: ../..//mkdep

../..//mkdep:
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
	for i in $(SUBDIRS) ;\
	do \
	(cd $$i ; echo "Depending" "in $(DIR)$$i..."; \
	$(MAKE) $(MFLAGS)  depend); \
	done

#
# lint
#  Check C sources with lint
#
## lint:  Check C sources with lint

lint:
	$(LINT) $(LINTFLAGS) $(SOURCES) $(LINTLIBS)

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
pwck_main.o: ../Common/common.h
pwck_main.o: ../compatibility.h
pwck_main.o: ../config.h
pwck_main.o: ../constants.h
pwck_main.o: ../defines.h
pwck_main.o: checkpassword.h
pwck_main.o: cracklib/packer.h
pwck_main.o: pwck_defines.h
pwck_main.o: pwck_main.c
pwck_crack.o: ../Common/common.h
pwck_crack.o: ../compatibility.h
pwck_crack.o: ../config.h
pwck_crack.o: ../constants.h
pwck_crack.o: ../defines.h
pwck_crack.o: checkpassword.h
pwck_crack.o: cracklib/packer.h
pwck_crack.o: pwck_crack.c
pwck_crack.o: pwck_defines.h
pwck_history.o: ../Common/common.h
pwck_history.o: ../Common/pw_svc.h
pwck_history.o: ../compatibility.h
pwck_history.o: ../config.h
pwck_history.o: ../constants.h
pwck_history.o: ../defines.h
pwck_history.o: ../options.h
pwck_history.o: checkpassword.h
pwck_history.o: cracklib/packer.h
pwck_history.o: pwck_defines.h
pwck_history.o: pwck_history.c
pwck_history.o: pwck_history.h
pwck_lexical.o: ../Common/common.h
pwck_lexical.o: ../compatibility.h
pwck_lexical.o: ../config.h
pwck_lexical.o: ../constants.h
pwck_lexical.o: ../defines.h
pwck_lexical.o: checkpassword.h
pwck_lexical.o: cracklib/packer.h
pwck_lexical.o: pwck_defines.h
pwck_lexical.o: pwck_lexical.c
pwck_local.o: ../Common/common.h
pwck_local.o: ../compatibility.h
pwck_local.o: ../config.h
pwck_local.o: ../constants.h
pwck_local.o: ../defines.h
pwck_local.o: checkpassword.h
pwck_local.o: cracklib/packer.h
pwck_local.o: pwck_defines.h
pwck_local.o: pwck_local.c
pwck_passwd.o: ../Common/common.h
pwck_passwd.o: ../compatibility.h
pwck_passwd.o: ../config.h
pwck_passwd.o: ../constants.h
pwck_passwd.o: ../defines.h
pwck_passwd.o: checkpassword.h
pwck_passwd.o: cracklib/packer.h
pwck_passwd.o: pwck_defines.h
pwck_passwd.o: pwck_passwd.c
pwck_vicb.o: ../Common/common.h
pwck_vicb.o: ../compatibility.h
pwck_vicb.o: ../config.h
pwck_vicb.o: ../constants.h
pwck_vicb.o: ../defines.h
pwck_vicb.o: checkpassword.h
pwck_vicb.o: cracklib/packer.h
pwck_vicb.o: pwck_defines.h
pwck_vicb.o: pwck_vicb.c
hist_file.o: ../Common/common.h
hist_file.o: ../compatibility.h
hist_file.o: ../config.h
hist_file.o: ../constants.h
hist_file.o: ../defines.h
hist_file.o: ../options.h
hist_file.o: checkpassword.h
hist_file.o: cracklib/packer.h
hist_file.o: hist_file.c
hist_file.o: pwck_defines.h
hist_file.o: pwck_history.h
hist_dbm.o: ../Common/common.h
hist_dbm.o: ../compatibility.h
hist_dbm.o: ../config.h
hist_dbm.o: ../constants.h
hist_dbm.o: ../defines.h
hist_dbm.o: ../options.h
hist_dbm.o: checkpassword.h
hist_dbm.o: cracklib/packer.h
hist_dbm.o: hist_dbm.c
hist_dbm.o: pwck_defines.h
hist_dbm.o: pwck_history.h
hist_nis.o: ../Common/common.h
hist_nis.o: ../compatibility.h
hist_nis.o: ../config.h
hist_nis.o: ../constants.h
hist_nis.o: ../defines.h
hist_nis.o: ../options.h
hist_nis.o: checkpassword.h
hist_nis.o: cracklib/packer.h
hist_nis.o: hist_nis.c
hist_nis.o: pwck_defines.h
hist_nis.o: pwck_history.h
hist_osf.o: ../Common/common.h
hist_osf.o: ../compatibility.h
hist_osf.o: ../config.h
hist_osf.o: ../constants.h
hist_osf.o: ../defines.h
hist_osf.o: ../options.h
hist_osf.o: checkpassword.h
hist_osf.o: cracklib/packer.h
hist_osf.o: hist_osf.c
hist_osf.o: pwck_defines.h
hist_osf.o: pwck_history.h
pwck_main.o: ../Common/common.h
pwck_main.o: ../compatibility.h
pwck_main.o: ../config.h
pwck_main.o: ../constants.h
pwck_main.o: ../defines.h
pwck_main.o: checkpassword.h
pwck_main.o: cracklib/packer.h
pwck_main.o: pwck_defines.h
pwck_main.o: pwck_main.c
pwck_crack.o: ../Common/common.h
pwck_crack.o: ../compatibility.h
pwck_crack.o: ../config.h
pwck_crack.o: ../constants.h
pwck_crack.o: ../defines.h
pwck_crack.o: checkpassword.h
pwck_crack.o: cracklib/packer.h
pwck_crack.o: pwck_crack.c
pwck_crack.o: pwck_defines.h
pwck_history.o: ../Common/common.h
pwck_history.o: ../Common/pw_svc.h
pwck_history.o: ../compatibility.h
pwck_history.o: ../config.h
pwck_history.o: ../constants.h
pwck_history.o: ../defines.h
pwck_history.o: ../options.h
pwck_history.o: checkpassword.h
pwck_history.o: cracklib/packer.h
pwck_history.o: pwck_defines.h
pwck_history.o: pwck_history.c
pwck_history.o: pwck_history.h
pwck_lexical.o: ../Common/common.h
pwck_lexical.o: ../compatibility.h
pwck_lexical.o: ../config.h
pwck_lexical.o: ../constants.h
pwck_lexical.o: ../defines.h
pwck_lexical.o: checkpassword.h
pwck_lexical.o: cracklib/packer.h
pwck_lexical.o: pwck_defines.h
pwck_lexical.o: pwck_lexical.c
pwck_local.o: ../Common/common.h
pwck_local.o: ../compatibility.h
pwck_local.o: ../config.h
pwck_local.o: ../constants.h
pwck_local.o: ../defines.h
pwck_local.o: checkpassword.h
pwck_local.o: cracklib/packer.h
pwck_local.o: pwck_defines.h
pwck_local.o: pwck_local.c
pwck_passwd.o: ../Common/common.h
pwck_passwd.o: ../compatibility.h
pwck_passwd.o: ../config.h
pwck_passwd.o: ../constants.h
pwck_passwd.o: ../defines.h
pwck_passwd.o: checkpassword.h
pwck_passwd.o: cracklib/packer.h
pwck_passwd.o: pwck_defines.h
pwck_passwd.o: pwck_passwd.c
pwck_vicb.o: ../Common/common.h
pwck_vicb.o: ../compatibility.h
pwck_vicb.o: ../config.h
pwck_vicb.o: ../constants.h
pwck_vicb.o: ../defines.h
pwck_vicb.o: checkpassword.h
pwck_vicb.o: cracklib/packer.h
pwck_vicb.o: pwck_defines.h
pwck_vicb.o: pwck_vicb.c
hist_file.o: ../Common/common.h
hist_file.o: ../compatibility.h
hist_file.o: ../config.h
hist_file.o: ../constants.h
hist_file.o: ../defines.h
hist_file.o: ../options.h
hist_file.o: checkpassword.h
hist_file.o: cracklib/packer.h
hist_file.o: hist_file.c
hist_file.o: pwck_defines.h
hist_file.o: pwck_history.h
hist_dbm.o: ../Common/common.h
hist_dbm.o: ../compatibility.h
hist_dbm.o: ../config.h
hist_dbm.o: ../constants.h
hist_dbm.o: ../defines.h
hist_dbm.o: ../options.h
hist_dbm.o: checkpassword.h
hist_dbm.o: cracklib/packer.h
hist_dbm.o: hist_dbm.c
hist_dbm.o: pwck_defines.h
hist_dbm.o: pwck_history.h
hist_nis.o: ../Common/common.h
hist_nis.o: ../compatibility.h
hist_nis.o: ../config.h
hist_nis.o: ../constants.h
hist_nis.o: ../defines.h
hist_nis.o: ../options.h
hist_nis.o: checkpassword.h
hist_nis.o: cracklib/packer.h
hist_nis.o: hist_nis.c
hist_nis.o: pwck_defines.h
hist_nis.o: pwck_history.h
hist_osf.o: ../Common/common.h
hist_osf.o: ../compatibility.h
hist_osf.o: ../config.h
hist_osf.o: ../constants.h
hist_osf.o: ../defines.h
hist_osf.o: ../options.h
hist_osf.o: checkpassword.h
hist_osf.o: cracklib/packer.h
hist_osf.o: hist_osf.c
hist_osf.o: pwck_defines.h
hist_osf.o: pwck_history.h
checkpassword.o: ../Common/common.h
checkpassword.o: ../compatibility.h
checkpassword.o: ../config.h
checkpassword.o: ../defines.h
checkpassword.o: ../options.h
checkpassword.o: checkpassword.c
checkpassword.o: checkpassword.h
version.o: version.c
history_admin.o: ../Common/common.h
history_admin.o: ../compatibility.h
history_admin.o: ../config.h
history_admin.o: ../constants.h
history_admin.o: ../defines.h
history_admin.o: ../options.h
history_admin.o: checkpassword.h
history_admin.o: cracklib/packer.h
history_admin.o: history_admin.c
history_admin.o: pwck_defines.h
history_admin.o: pwck_history.h
test_pwck.o: ../Common/common.h
test_pwck.o: ../compatibility.h
test_pwck.o: ../config.h
test_pwck.o: ../constants.h
test_pwck.o: ../defines.h
test_pwck.o: ../options.h
test_pwck.o: checkpassword.h
test_pwck.o: cracklib/packer.h
test_pwck.o: pwck_defines.h
test_pwck.o: test_pwck.c
test_history.o: ../Common/common.h
test_history.o: ../compatibility.h
test_history.o: ../config.h
test_history.o: ../constants.h
test_history.o: ../defines.h
test_history.o: ../options.h
test_history.o: checkpassword.h
test_history.o: cracklib/packer.h
test_history.o: pwck_defines.h
test_history.o: pwck_history.h
test_history.o: test_history.c
