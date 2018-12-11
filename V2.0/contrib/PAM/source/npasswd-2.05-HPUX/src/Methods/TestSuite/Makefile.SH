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
CURRENT=src/Methods/TestSuite
DIR=`echo $CURRENT/ | sed -e 's/\.\///g'`
echo "Extracting ${DIR}Makefile (with variable substitutions)"

DATE=`date`

$spitshell >Makefile <<!GROK!THIS!
########################################################################
# Makefile generated from Makefile.SH on $DATE

SHELL = /bin/sh
JMAKE = jmake
TOP = ../../../
CURRENT = $CURRENT
DIR = $DIR

########################################################################
# Parameters set by Configure -- edit config.sh if changes are needed

CC = $cc
CTAGS = ctags
JCFLAGS = \$(CFLAGS) $optimize $ccflags $large
JLDFLAGS = \$(LDFLAGS) $optimize $ldflags
LIBS = $libs
MAKE = make
MV = $mv
RM = $rm -f

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
INCLUDE_PATH =  -I.. -I../.. -I../../.. -I../Common
SHADOW_M =  $p_shadow
OBJECTS =   \$(LIBS)
SOURCES =  \$(SHADOWM_SRC)  \$(MAIN) \$(SHADOW_M).o

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
# This Makefile builds debugging versions of password database access method
# modules and the selected shadow database access method module,
# and the validation test drivers & programs.
#
# @(#)Jmakefile	1.4 09/23/98 (cc.utexas.edu)
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
# Debugging is always on ../defines.h for the debug level explanation
#
X_LOCAL_CFLAGS = -DCDEBUG=3 $(X_CCDEBUG)
COMOBJ_LIB = ../../Common/libcomobj.a

#
# These must be the same as PASSWDM_SRC and SHADOWM_SRC in ../Makefile
#
PASSWDM_SRC = \
	pwm_main.c \
	pwm_local.c \
	pwm_nis.c

SHADOWM_SRC = \
	shm_adjunct.c \
	shm_aix.c \
	shm_shadow.c \
	shm_ultrix.c \
	shm_osf1.c \
	shm_hpux.c

#
# Test suite driver program
#
MAIN = pwm_test.c

METHOD_OBJ = \
	pwm_main.o \
	pwm_local.o \
	pwm_nis.o 

OBJS	= $(METHOD_OBJ) $(SHADOW_M).o $(COMOBJ_LIB) $(LIBS)

#
# all
#  Setup and build everthing
#
## all:  Setup and build everthing
all::	srclinks
	-@echo Run InitTestFiles.sh to setup dummy files

all::	getuser

#
# getuser
#  Build user lookup test program
#
## getuser:  Build user lookup test program

all:: getuser

local_realclean::
	$(RM) getuser

getuser:  $(LIBS)
	$(RM) $@
	if test -f $@; then $(MV) $@ $@~; else exit 0; fi
	$(CC) -o $@  $(LIBS) $(JLDFLAGS) $(LIBS)

getuser: $(MAIN) $(COMOBJ_LIB) $(METHOD_OBJ) $(SHADOW_M).o
	$(CC) -o getuser -DTEST_GETUSER $(JCFLAGS) $(MAIN) $(OBJS)

#
# putuser - build test user passwd update program
#
# all:: putuser
#

#
# putuser
#  Build user update test program
#
## putuser:  Build user update test program
#putuser: $(MAIN) $(COMOBJ_LIB) $(METHOD_OBJ) $(SHADOW_M).o
#	$(CC) -o putuser -DTEST_PUTUSER $(JCFLAGS) $(MAIN) $(OBJS)

depend::	srclinks

#
# srclinks
#  Link source modules from method directory
#
## srclinks:  Link source modules from method directory
srclinks:
	-@for f in $(PASSWDM_SRC) $(SHADOW_M).c; do \
		if [ ! -f $$f ]; then\
			 ln -s ../$$f $$f && echo $(LNS) ../$$f $$f;\
		fi;\
	done

#
# Local components to 'clobber' target
#
local_clobber::
	$(RM) $(PASSWDM_SRC) $(SHADOW_M).c
	$(RM) TestSuiteSetup.sh getuser putuser etc_*

#
# Dependancies for pieces of the test suite
#
all::	TestGetUser.sh TestSuiteSetup.sh InitTestFiles.sh

TestGetUser.sh:

InitTestFiles.sh:


TestSuiteSetup: TestSuiteSetup.SH
	@$(RM) TestSuiteSetup
	@sh TestSuiteSetup.SH

TestSuiteSetup.SH:
	@exit 0;


.FORCE:

../../Common/libcomobj.a: .FORCE
	cd ../../Common; $(MAKE) $(MFLAGS) libcomobj.a

# debug-none
##_ debug-none: Set debug level
#
debug-none:: debug-main

# debug-dbx
##_ debug-dbx: Set debug level
#
debug-dbx:: debug-main

# debug-files
##_ debug-files: Set debug level
#
debug-files:: debug-main

# debug-system
##_ debug-system: Set debug level
#
debug-system:: debug-main


debug-main:
	@echo Debugging in $(CURRENT) is always enabled

Coda()

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

!NO!SUBS!
chmod 644 Makefile
$eunicefix Makefile

