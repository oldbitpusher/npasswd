########################################################################
# Makefile generated from Makefile.SH on Mon Feb  1 14:05:37 CST 1999

SHELL = /bin/sh
JMAKE = jmake
TOP = .
CURRENT = .
DIR = 
INSTALLDIR = mkdir -p

########################################################################
# Parameters set by Configure -- edit config.sh if changes are needed

CTAGS = ctags
MAKE = make
MV = mv
RM = rm -f

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
INSTALL_DIR =  
KEEP_DIR =  /usr/lib/passwd/xbin
DICT_DIR =  
UTIL_DIR =  
ECHO_C =  \c
ECHO_N =  
SUBDIRS = files src dict doc

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
# @(#)Jmakefile	1.12 07/20/98 (cc.utexas.edu)
#
# Main Makefile for npasswd
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

DIRS_NEEDED = $(INSTALL_DIR) $(DICT_DIR) $(KEEP_DIR) $(UTIL_DIR)

#
# all
#  Build everything everywhere
#
## all:  Build everything everywhere
# Force "all" to be the first target
all::

#
# "make help" will show useful targets
#
help::
	@echo Targets in Makefile
	-@sed -n 's/^##[ 	]/	/p' Makefile

#
# install
#  Install npasswd. This must be done as root
#
## install:  Install npasswd. This must be done as root
#
# Install section - lots of things to do
#
install::
	@foo=`(id || whoami) 2>/dev/null`;\
	  case "$$foo" in \
	  *root*) exit 0;;\
	  *) echo "make install should be done as root"; exit 1;;\
	         esac

#
# Make and set modes for the installation directories
#
install::
	@for dir in $(DIRS_NEEDED); do \
	case '${MFLAGS}' in *[i]*) set +e;; esac; \
	(set -x; test -d $$dir || $(INSTALLDIR) $$dir); \
	done
	chmod 0755 $(INSTALL_DIR) $(DICT_DIR) $(UTIL_DIR)
	chmod 0751 $(KEEP_DIR)

#
# deinstall
#  Remove npasswd and revert to vendor programs
#
## deinstall:  Remove npasswd and revert to vendor programs
deinstall:: backdown

#
# backdown
#  Revert to vendor programs
#
## backdown:  Revert to vendor programs
backdown::
	cd src; make $(MFLAGS) backdown

#
# nuke
#  Delete the entire install directory and contents
#
## nuke:  Delete the entire install directory and contents
nuke:
	@echo $(ECHO_N) Delete everything under $(INSTALL_DIR) '(y/n)? $(ECHO_C)'; \
	 read ans;\
	 case "$$ans" in\
	 y*|Y*) (set -x; $(RM) -r $(INSTALL_DIR)) ;;\
	esac

#
# depend
#  Update makefile dependancies
#
## depend:  Update makefile dependancies

depend::
	@case '${MFLAGS}' in *[ik]*) set +e;; esac; \
	for i in $(SUBDIRS) ;\
	do \
	(cd $$i ; echo "Depending" "in $(DIR)$$i..."; \
	$(MAKE) $(MFLAGS)  depend); \
	done

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

########################################################################
# Common rules for all Makefiles -- do not edit

emptyrule::

clean: sub_clean local_clean
realclean: sub_realclean local_realclean
clobber: sub_clobber local_clobber

local_clean::
	$(RM) core *~ *.o

local_realclean:: local_clean
	$(RM) -r UU

local_clobber:: local_realclean
	$(RM) config.sh config.h
	$(RM) -r .config
	$(RM) Makefile

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

