########################################################################
# Makefile generated from Makefile.SH on Tue Mar 13 14:37:47 CDT 2007

SHELL = /bin/sh
JMAKE = jmake
TOP = ../../
CURRENT = src/Scripts
DIR = src/Scripts/
INSTALL = /usr/ucb/install

########################################################################
# Parameters set by Configure -- edit config.sh if changes are needed

CTAGS = ctags
MAKE = make
MV = /usr/bin/mv
RM = /usr/bin/rm -f

########################################################################
# Automatically generated parameters -- do not edit

X_CCDEBUG =  -g -xsb
X_COPT =  -O
X_CFLAGS =   -Xa -DOS_SUNOS_5 -DOS_NAME=sunos -DOS_MAJOR_VERSION=5 -DOS_MINOR_VERSION=10 $(INCLUDE_PATH)
X_LDFLAGS =  
X_LOCAL_CFLAGS =
LOCAL_FLAGS =  Makefile.local
JCFLAGS =  $(X_CFLAGS) $(X_COPT) $(X_LOCAL_CFLAGS)
JLDFLAGS =  $(X_LDFLAGS) $(X_LOCAL_CFLAGS)
LNS =  /usr/bin/ln -s
DPFLAGS =  $(INCLUDE_PATH)
LINTFLAGS =  $(X_CFLAGS) 
BIN =  /usr/lib/passwd/bin

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
# @(#)Jmakefile	1.7 07/16/98 (cc.utexas.edu)
#

#
# Makefile for npasswd utility scripts
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

ALL = savefiles restorefiles

#
# all
# 	Make npasswd utility scripts
#
## all: 	Make npasswd utility scripts

all:: installmany $(ALL)

local_realclean::
	$(RM) installmany $(ALL)


installmany: installmany.SH
	@$(RM) installmany
	@sh installmany.SH

installmany.SH:
	@exit 0;


savefiles: savefiles.SH
	@$(RM) savefiles
	@sh savefiles.SH

savefiles.SH:
	@exit 0;


restorefiles: restorefiles.SH
	@$(RM) restorefiles
	@sh restorefiles.SH

restorefiles.SH:
	@exit 0;


#
# install
# 	Install npasswd utility scripts
#
## install: 	Install npasswd utility scripts

#
# de-install
# 	Remove npasswd utility scripts
#
## de-install: 	Remove npasswd utility scripts


install:: savefiles
	$(INSTALL) -c -m 555  savefiles $(BIN)

deinstall::
	$(RM) $(BIN)/savefiles


install:: restorefiles
	$(INSTALL) -c -m 555  restorefiles $(BIN)

deinstall::
	$(RM) $(BIN)/restorefiles

#
# "make help" will show useful targets
#
help::
	@echo Targets in Makefile
	-@sed -n 's/^##[ 	]/	/p' Makefile

# ---------------------------------------------------------------
# Do-nothing debug targets
# ---------------------------------------------------------------
debug-none::
	@echo Nothing to debug in $(CURRENT)

debug-dbx::
	@echo Nothing to debug in $(CURRENT)

debug-files::
	@echo Nothing to debug in $(CURRENT)

debug-system::
	@echo Nothing to debug in $(CURRENT)


depend:
	-@echo No dependancies in $(CURRENT)

lint:
	-@echo Nothing to lint in $(CURRENT)

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

