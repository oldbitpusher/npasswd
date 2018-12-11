: Makefile.SH generated from Jmake.tmpl and Jmakefile [jmake 3.0 PL70]
: $X-Id: Jmake.tmpl,v 3.0.1.3 1997/02/28 14:56:16 ram Exp $

case $CONFIG in
'')
	if test -f config.sh; then TOP=.;
	elif test -f ../config.sh; then TOP=..;
	elif test -f ../../config.sh; then TOP=../..;
	elif test -f ../../../config.sh; then TOP=../../..;
	elif test -f ../../../../config.sh; then TOP=../../../..;
	else
		echo "Can't find config.sh."; exit 1
	fi
	. $TOP/config.sh
	;;
esac
case "$0" in
*/*) cd `expr X$0 : 'X\(.*\)/'` ;;
esac
CURRENT=src/PasswordCheck
DIR=`echo $CURRENT/ | sed -e 's/\.\///g'`
echo "Extracting ${DIR}Makefile (with variable substitutions)"

INSTALL=`echo $install | sed -e 's,\./i,\$(TOP)/i,'`
DATE=`date`

$spitshell >Makefile <<!GROK!THIS!
########################################################################
# Makefile generated from Makefile.SH on $DATE

SHELL = /bin/sh
JMAKE = jmake
TOP = ../../
CURRENT = $CURRENT
DIR = $DIR
INSTALL = $INSTALL

########################################################################
# Parameters set by Configure -- edit config.sh if changes are needed

AR = ar rc
CC = $cc
CTAGS = ctags
JCFLAGS = \$(CFLAGS) $optimize $ccflags $large
JLDFLAGS = \$(LDFLAGS) $optimize $ldflags
LD = ld
LIBS = $libs
LINT = lint
MAKE = make
MKDEP = $mkdep \$(DPFLAGS) --
MV = $mv
RANLIB = $ranlib
RM = $rm -f
SED = $sed

########################################################################
# Automatically generated parameters -- do not edit

X_CCDEBUG =  $cc_dbflags
X_COPT =  $optimize
X_CFLAGS =  $ccflags $cc_osflags \$(INCLUDE_PATH)
X_LDFLAGS =  $ldflags
X_LOCAL_CFLAGS =
LOCAL_FLAGS =  Makefile.local
JCFLAGS =  \$(X_CFLAGS) \$(X_COPT) \$(X_LOCAL_CFLAGS)
JLDFLAGS =  \$(X_LDFLAGS) \$(X_LOCAL_CFLAGS)
LNS =  $lns
DPFLAGS =  \$(INCLUDE_PATH)
LINTFLAGS =  \$(X_CFLAGS) $ccflags
INCLUDE_PATH =  -I.. -I../.. -I../Common -Icracklib
LIB_DIR =  $p_installdir
SUBDIRS = cracklib
OBJECTS =   \$(PWCK_OBJ) \$(HIST_OBJ) \$(CRACK_OBJ)  pwck_all.o  checkpassword.o version.o \$(PUBLIC_A) history_admin.o \$(PRIVATE_A) \$(COMOBJ) test_pwck.o \$(PRIVATE_A) \$(COMOBJ) test_history.o \$(PRIVATE_A) \$(COMOBJ)
SOURCES =   \$(PWCK_SRC) \$(HIST_SRC)  \$(PWCK_SRC) \$(HIST_SRC)  checkpassword.c version.c history_admin.c test_pwck.c test_history.c

########################################################################
# New suffixes and associated building rules -- edit with care

.c.o:
	\$(RM) \$@
	\$(CC) -c \$(JCFLAGS) \$<

!GROK!THIS!
$spitshell >>Makefile <<'!NO!SUBS!'
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

# Put nothing here or make depend will gobble it up
.FORCE_DEPEND::
	@echo "You must run 'make depend' in $(TOP) first."; exit 1
!NO!SUBS!
chmod 644 Makefile
$eunicefix Makefile

