########################################################################
# Makefile generated from Makefile.SH on Mon Feb  1 14:06:34 CST 1999

SHELL = /bin/sh
JMAKE = jmake
TOP = ../../
CURRENT = src/Common
DIR = src/Common/

########################################################################
# Parameters set by Configure -- edit config.sh if changes are needed

AR = ar rc
CC = cc
CTAGS = ctags
JCFLAGS = $(CFLAGS) -O -D__LANGUAGE_C__ -D_NO_PROTO 
LINT = lint
MAKE = make
MKDEP = /tmp_mnt/usr/share/src/private/ut/share/bin/passwd/V2.0/mkdep $(DPFLAGS) --
MV = mv
RANLIB = :
RM = rm -f
SED = sed

########################################################################
# Automatically generated parameters -- do not edit

X_CCDEBUG =  -g2
X_COPT =  -O
X_CFLAGS =  -D__LANGUAGE_C__ -D_NO_PROTO -DOS_DEC_OSF1 -DOS_NAME=osf1 -DOS_MAJOR_VERSION=3 -DOS_MINOR_VERSION=2 -std $(INCLUDE_PATH)
X_LDFLAGS =  
X_LOCAL_CFLAGS =
LOCAL_FLAGS =  Makefile.local
JCFLAGS =  $(X_CFLAGS) $(X_COPT) $(X_LOCAL_CFLAGS)
JLDFLAGS =  $(X_LDFLAGS) $(X_LOCAL_CFLAGS)
LNS =  ln -s
DPFLAGS =  $(INCLUDE_PATH)
LINTFLAGS =  $(X_CFLAGS) -D__LANGUAGE_C__ -D_NO_PROTO
INCLUDE_PATH =  -I.. -I../..
OBJECTS =   $(OBJECTS)
SOURCES =   $(SOURCES)

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
# @(#)Jmakefile	1.11 11/17/98 (cc.utexas.edu)
#

#
# Makefile for npasswd commom object library
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

SOURCES = \
	chop_nl.c \
	compatibility.c \
	file_util.c \
	getpass.c \
	instring.c \
	messages.c \
	mpw_util.c \
	pager.c \
	pw_svc.c \
	pw_util.c \
	signals.c \
	split.c \
	term.c \
	pw_svc.c \
	xatoi.c \
	xdecode.c

OBJECTS = \
	chop_nl.o \
	compatibility.o \
	file_util.o \
	getpass.o \
	instring.o \
	messages.o \
	mpw_util.o \
	pager.o \
	pw_svc.o \
	pw_util.o \
	signals.o \
	split.o \
	term.o \
	pw_svc.o \
	xatoi.o \
	xdecode.o 

#
# libcomobj.a
#  Build npasswd common object library
#
## libcomobj.a:  Build npasswd common object library

all:: libcomobj.a

local_realclean::
	$(RM) libcomobj.a

libcomobj.a:  $(OBJECTS)
	$(RM) $@
	$(AR) $@  $(OBJECTS)
	$(RANLIB) $@

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

clean: local_clean
realclean: local_realclean
clobber: local_clobber

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
# Empty rules for directories with no sub-directories -- do not edit

install::
	@echo "install in $(CURRENT) done."

deinstall::
	@echo "deinstall in $(CURRENT) done."

install.man::
	@echo "install.man in $(CURRENT) done."

deinstall.man::
	@echo "deinstall.man in $(CURRENT) done."

Makefiles::

Makefiles.SH::

########################################################################
# Dependencies generated by make depend
# DO NOT DELETE THIS LINE -- make depend relies on it

# Put nothing here or make depend will gobble it up
.FORCE_DEPEND::
	@echo "You must run 'make depend' in $(TOP) first."; exit 1
