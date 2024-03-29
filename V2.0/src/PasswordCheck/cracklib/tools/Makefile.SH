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
CURRENT=src/PasswordCheck/cracklib/tools
DIR=`echo $CURRENT/ | sed -e 's/\.\///g'`
echo "Extracting ${DIR}Makefile (with variable substitutions)"

INSTALL=`echo $install | sed -e 's,\./i,\$(TOP)/i,'`
DATE=`date`

$spitshell >Makefile <<!GROK!THIS!
########################################################################
# Makefile generated from Makefile.SH on $DATE

SHELL = /bin/sh
JMAKE = jmake
TOP = ../../../../
CURRENT = $CURRENT
DIR = $DIR
INSTALL = $INSTALL

########################################################################
# Parameters set by Configure -- edit config.sh if changes are needed

CC = $cc
CTAGS = ctags
JCFLAGS = \$(CFLAGS) $optimize $ccflags $large
JLDFLAGS = \$(LDFLAGS) $optimize $ldflags
LIBS = $libs
LINT = lint
MAKE = make
MKDEP = $mkdep \$(DPFLAGS) --
MV = $mv
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
BIN =  $p_utildir
INCLUDE_PATH =  -I..
OBJECTS =  packer.o \${CRACKLIB} unpacker.o \${CRACKLIB} testnum.o \${CRACKLIB} teststr.o \${CRACKLIB} testlib.o \${CRACKLIB} testgecos.o \${CRACKLIB} testnpasswd.o \${CRACKLIB}
SOURCES =  packer.c unpacker.c testnum.c teststr.c testlib.c testgecos.c testnpasswd.c

########################################################################
# New suffixes and associated building rules -- edit with care

.c.o:
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
# @(#)Jmakefile	1.4 07/20/98 (cc.utexas.edu)
#
# ---------------------------------------------------------------
# Build Cracklib test programs
# ---------------------------------------------------------------

#
# This file is auto-generated from Makefile.SH - all persistent
# changes should be made there.
#
# Makefile.SH is itself generated from "Jmakefile" by jmake.
#
# Jmakefile is included in the developer kit.
# See the Npasswd Support Guide (Support.html).
#

CRACKLIB = ../libcrack.a

all:: packer

local_realclean::
	$(RM) packer

packer: packer.o ${CRACKLIB}
	$(RM) $@
	if test -f $@; then $(MV) $@ $@~; else exit 0; fi
	$(CC) -o $@ packer.o ${CRACKLIB} $(JLDFLAGS) $(LIBS)

all:: unpacker

local_realclean::
	$(RM) unpacker

unpacker: unpacker.o ${CRACKLIB}
	$(RM) $@
	if test -f $@; then $(MV) $@ $@~; else exit 0; fi
	$(CC) -o $@ unpacker.o ${CRACKLIB} $(JLDFLAGS) $(LIBS)

all:: testnum

local_realclean::
	$(RM) testnum

testnum: testnum.o ${CRACKLIB}
	$(RM) $@
	if test -f $@; then $(MV) $@ $@~; else exit 0; fi
	$(CC) -o $@ testnum.o ${CRACKLIB} $(JLDFLAGS) $(LIBS)

all:: teststr

local_realclean::
	$(RM) teststr

teststr: teststr.o ${CRACKLIB}
	$(RM) $@
	if test -f $@; then $(MV) $@ $@~; else exit 0; fi
	$(CC) -o $@ teststr.o ${CRACKLIB} $(JLDFLAGS) $(LIBS)

all:: testlib

local_realclean::
	$(RM) testlib

testlib: testlib.o ${CRACKLIB}
	$(RM) $@
	if test -f $@; then $(MV) $@ $@~; else exit 0; fi
	$(CC) -o $@ testlib.o ${CRACKLIB} $(JLDFLAGS) $(LIBS)

all:: testgecos

local_realclean::
	$(RM) testgecos

testgecos: testgecos.o ${CRACKLIB}
	$(RM) $@
	if test -f $@; then $(MV) $@ $@~; else exit 0; fi
	$(CC) -o $@ testgecos.o ${CRACKLIB} $(JLDFLAGS) $(LIBS)

all:: testnpasswd

local_realclean::
	$(RM) testnpasswd

testnpasswd: testnpasswd.o ${CRACKLIB}
	$(RM) $@
	if test -f $@; then $(MV) $@ $@~; else exit 0; fi
	$(CC) -o $@ testnpasswd.o ${CRACKLIB} $(JLDFLAGS) $(LIBS)


makedict: makedict.SH
	@$(RM) makedict
	@sh makedict.SH

makedict.SH:
	@exit 0;


install:: packer
	$(INSTALL) -c -s -m 555  packer  ${BIN}

deinstall::
	$(RM)  ${BIN}/packer

install:: unpacker
	$(INSTALL) -c -s -m 555  unpacker  ${BIN}

deinstall::
	$(RM)  ${BIN}/unpacker

install:: makedict
	$(INSTALL) -c -m 555  makedict  ${BIN}

deinstall::
	$(RM)  ${BIN}/makedict

.FORCE:

..//libcrack.a: .FORCE
	cd ../; $(MAKE) $(MFLAGS) libcrack.a

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
# The debug levels "files" and "system" are not applicable.
#
debug-files::
	@echo ""
	@echo WARNING: debug level \"files\" not effective in $(CURRENT)
	@echo ""

debug-system::
	@echo ""
	@echo WARNING: debug level \"system\" not effective in $(CURRENT)
	@echo ""

lint:
	$(LINT) $(LINTFLAGS) $(SOURCES) $(LINTLIBS)

depend:: ../../../..//mkdep

../../../..//mkdep:
	@echo "You have to run Configure in $(TOP) first."; exit 1

depend::
	($(SED) '/^# DO NOT DELETE/q' Makefile && \
	$(MKDEP) $(SOURCES) | \
	$(SED) -e 's/: \.\//: /; s/\/usr\/include[^ ]*//g' -e '/: *$$/d' \
	) > Makefile.new
	cp Makefile Makefile.bak
	cp Makefile.new Makefile
	$(RM) Makefile.new

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
!NO!SUBS!
chmod 644 Makefile
$eunicefix Makefile

