########################################################################
# Makefile generated from Makefile.SH on Sat Feb 10 20:06:02 CST 2001

SHELL = /bin/sh
JMAKE = jmake
TOP = ../
CURRENT = files
DIR = files/
INSTALL = /usr/bin/install

########################################################################
# Parameters set by Configure -- edit config.sh if changes are needed

CTAGS = ctags
MAKE = make
MV = /bin/mv
RM = /bin/rm -f

########################################################################
# Automatically generated parameters -- do not edit

X_CCDEBUG =  -g3
X_COPT =  -O2
X_CFLAGS =   -DOS_NAME=linux -DOS_MAJOR_VERSION=2 -DOS_MINOR_VERSION=2 $(INCLUDE_PATH)
X_LDFLAGS =  
X_LOCAL_CFLAGS =
LOCAL_FLAGS =  Makefile.local
JCFLAGS =  $(X_CFLAGS) $(X_COPT) $(X_LOCAL_CFLAGS)
JLDFLAGS =  $(X_LDFLAGS) $(X_LOCAL_CFLAGS)
LNS =  /bin/ln -s
DPFLAGS =  $(INCLUDE_PATH)
LINTFLAGS =  $(X_CFLAGS) 
LIB =  /usr/lib/passwd

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
# Install npasswd ancillary files
#
# @(#)Jmakefile	1.4 08/17/98 (cc.utexas.edu)
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

HELP = \
	passwd.help \
	chfn.help \
	chsh.help

MOTD = \
	passwd.motd \
	chfn.motd \
	chsh.motd

CONF	= passwd.conf

#
# all
# 	Build everything
#
## all: 	Build everything

all:: passwd.conf

local_realclean::
	$(RM) passwd.conf

#
# passwd.conf
# 	Build example config file
#
## passwd.conf: 	Build example config file


passwd.conf: passwd.conf.SH
	@$(RM) passwd.conf
	@sh passwd.conf.SH

passwd.conf.SH:
	@exit 0;


#
# install
# 	Install help and motd files
#
## install: 	Install help and motd files

#
# deinstall
# 	Remove help and motd files
#
## deinstall: 	Remove help and motd files

install::
	@if [ ! -f $(LIB)/$(CONF) ]; then \
		$(INSTALL) -c -m 444 $(CONF) $(LIB);\
		echo $(INSTALL) -c -m 444 $(CONF) $(LIB);\
	fi
	@echo ""
	@echo See $(CURRENT)/README about customizing config, help and message files
	@echo ""

install::  $(HELP) $(MOTD)
	@case '${MFLAGS}' in *[i]*) set +e;; esac; \
	for i in  $(HELP) $(MOTD); do \
	(set -x; $(INSTALL) -c  -m 0444 $$i  $(LIB)); \
	done

deinstall::
	@case '${MFLAGS}' in *[i]*) set +e;; esac; \
	for i in  $(HELP) $(MOTD); do \
	(set -x; $(RM)  $(LIB)/$$i); \
	done

#
# install-config
# 	Install config file
#
## install-config: 	Install config file

#
# deinstall-config
# 	Remove config file
#
## deinstall-config: 	Remove config file

install-config::  $(CONF)
	@case '${MFLAGS}' in *[i]*) set +e;; esac; \
	for i in  $(CONF); do \
	(set -x; $(INSTALL) -c  -m 0444 $$i  $(LIB)); \
	done

deinstall-config::
	@case '${MFLAGS}' in *[i]*) set +e;; esac; \
	for i in  $(CONF); do \
	(set -x; $(RM)  $(LIB)/$$i); \
	done

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


lint:
	-@echo Nothing to lint in $(CURRENT)

depend:
	-@echo No dependancies in $(CURRENT)

#
# End Makefile

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

