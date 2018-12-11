########################################################################
# Makefile generated from Makefile.SH on Sat Feb 10 20:06:02 CST 2001

SHELL = /bin/sh
JMAKE = jmake
TOP = ../
CURRENT = doc
DIR = doc/
INSTALL = /usr/bin/install
INSTALLDIR = /usr/bin/install -d

########################################################################
# Parameters set by Configure -- edit config.sh if changes are needed

CC = cc
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
DOCS =  /usr/lib/passwd/doc
NROFF =  /usr/bin/nroff
HTCONVERT =  lynx -dump
HTFILTER =   sed -e s@file://localhost/home/motown/cc/ccbt/clyde/src/npasswd/V2.0/BUILD/redhat61/doc@file://localhost/.@

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
# @(#)Jmakefile	1.13 10/01/98 (cc.utexas.edu)
#
# Makefile for npasswd documentation (mostly HTML docs)
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
# NROFF
# 	Nroff command
#
## NROFF: 	Nroff command

#
# HTCONVERT
# 	Command to convert HTML to text (lynx -dump)
#
## HTCONVERT: 	Command to convert HTML to text (lynx -dump)

HTML	= \
	AdminGuide.html \
	BuildInstall.html \
	BugReport.html \
	Copyright.html \
	QNA.html \
	Main.html \
	ManPages.html \
	MiscNotes.html \
	Support.html \
	Reference.html \
	Reference_TOC.html \
	Reference_index.html \
	TOC_frame.html \
	TOC_std.html \
	index.html

HTML_TXT = \
	AdminGuide.txt \
	BuildInstall.txt \
	BugReport.txt \
	Copyright.txt \
	QNA.txt \
	Main.txt \
	ManPages.txt \
	MiscNotes.txt \
	Support.txt \
	Reference.txt \
	TOC_std.txt

PS	= \
	PasswordSecurity.ps \
	Worm-MIT.ps \
	Worm-Utah.ps

IMG	= \
	top.gif \
	home.gif

MAN	= \
	checkpassword.1 \
	checkpassword.3 \
	history_admin.1 \
	makedict.1 \
	npasswd.1

MAN_HTML = \
	checkpassword_1.html \
	checkpassword_3.html \
	history_admin_1.html \
	makedict_1.html \
	npasswd_1.html

MAN_CAT = \
	checkpassword.cat1 \
	checkpassword.cat3 \
	history_admin.cat1 \
	makedict.cat1 \
	npasswd.cat1

#
# all
# 	Make everything: nroff2html docfilter man-html man-txt hmtl-txt
#
## all: 	Make everything: nroff2html docfilter man-html man-txt hmtl-txt
all::	nroff2html docfilter man-html man-txt html-txt

#
# dist
# 	Prepare for distribution
#
## dist: 	Prepare for distribution
dist:	man-html man-txt html-txt

#
# install
# 	Install everything: install-html install-man install-txt
#
## install: 	Install everything: install-html install-man install-txt

#
# deinstall
# 	Remove everything: deinstall-html deinstall-man deinstall-txt
#
## deinstall: 	Remove everything: deinstall-html deinstall-man deinstall-txt

install::
	@for dir in $(DOCS); do \
	case '${MFLAGS}' in *[i]*) set +e;; esac; \
	(set -x; test -d $$dir || $(INSTALLDIR) $$dir); \
	done

deinstall::
	$(RM) -r $(DOCS)

#
# "make help" will show useful targets
#
help::
	@echo Targets in Makefile
	-@sed -n 's/^##[ 	]/	/p' Makefile

#
#  Program to "convert" nroff output to HTML
#

nroff2html: nroff2html.c
	$(CC) -o nroff2html nroff2html.c

docfilter: docfilter.SH
	$(RM) docfilter
	sh docfilter.SH

#
# Transform manual pages to HTML documents
#

#
# man-html
# 	Make HTML versions of man pages
#
## man-html: 	Make HTML versions of man pages
man-html:	$(MAN_HTML) docfilter nroff2html

checkpassword_1.html: checkpassword.1
	-@if [ -f $(NROFF) ]; then \
	$(RM) checkpassword_1.html; \
	$(NROFF) -man checkpassword.1 |./docfilter |./nroff2html > checkpassword_1.html ;\
	echo "checkpassword.1 -> checkpassword_1.html"; \
	else \
	echo "Cannot make checkpassword_1.html ($(NROFF) not found)"; \
	fi

checkpassword_3.html: checkpassword.3
	-@if [ -f $(NROFF) ]; then \
	$(RM) checkpassword_3.html; \
	$(NROFF) -man checkpassword.3 |./docfilter |./nroff2html > checkpassword_3.html ;\
	echo "checkpassword.3 -> checkpassword_3.html"; \
	else \
	echo "Cannot make checkpassword_3.html ($(NROFF) not found)"; \
	fi

history_admin_1.html: history_admin.1
	-@if [ -f $(NROFF) ]; then \
	$(RM) history_admin_1.html; \
	$(NROFF) -man history_admin.1 |./docfilter |./nroff2html > history_admin_1.html ;\
	echo "history_admin.1 -> history_admin_1.html"; \
	else \
	echo "Cannot make history_admin_1.html ($(NROFF) not found)"; \
	fi

makedict_1.html: makedict.1
	-@if [ -f $(NROFF) ]; then \
	$(RM) makedict_1.html; \
	$(NROFF) -man makedict.1 |./docfilter |./nroff2html > makedict_1.html ;\
	echo "makedict.1 -> makedict_1.html"; \
	else \
	echo "Cannot make makedict_1.html ($(NROFF) not found)"; \
	fi

npasswd_1.html: npasswd.1
	-@if [ -f $(NROFF) ]; then \
	$(RM) npasswd_1.html; \
	$(NROFF) -man npasswd.1 |./docfilter |./nroff2html > npasswd_1.html ;\
	echo "npasswd.1 -> npasswd_1.html"; \
	else \
	echo "Cannot make npasswd_1.html ($(NROFF) not found)"; \
	fi

#
# Transform manual pages to text documents
#

#
# man-txt
# 	Make text (cat) versions of man pages
#
## man-txt: 	Make text (cat) versions of man pages
man-txt:	$(MAN_CAT) docfilter

checkpassword.cat1: checkpassword.1
	-@if [ -f $(NROFF) ]; then \
	$(RM) checkpassword.cat1; \
	$(NROFF) -man checkpassword.1 | ./docfilter > checkpassword.cat1 ;\
	echo "checkpassword.1 -> checkpassword.cat1"; \
	else \
	echo "Cannot make checkpassword.cat1 ($(NROFF) not found)"; \
	fi

checkpassword.cat3: checkpassword.3
	-@if [ -f $(NROFF) ]; then \
	$(RM) checkpassword.cat3; \
	$(NROFF) -man checkpassword.3 | ./docfilter > checkpassword.cat3 ;\
	echo "checkpassword.3 -> checkpassword.cat3"; \
	else \
	echo "Cannot make checkpassword.cat3 ($(NROFF) not found)"; \
	fi

history_admin.cat1: history_admin.1
	-@if [ -f $(NROFF) ]; then \
	$(RM) history_admin.cat1; \
	$(NROFF) -man history_admin.1 | ./docfilter > history_admin.cat1 ;\
	echo "history_admin.1 -> history_admin.cat1"; \
	else \
	echo "Cannot make history_admin.cat1 ($(NROFF) not found)"; \
	fi

makedict.cat1: makedict.1
	-@if [ -f $(NROFF) ]; then \
	$(RM) makedict.cat1; \
	$(NROFF) -man makedict.1 | ./docfilter > makedict.cat1 ;\
	echo "makedict.1 -> makedict.cat1"; \
	else \
	echo "Cannot make makedict.cat1 ($(NROFF) not found)"; \
	fi

npasswd.cat1: npasswd.1
	-@if [ -f $(NROFF) ]; then \
	$(RM) npasswd.cat1; \
	$(NROFF) -man npasswd.1 | ./docfilter > npasswd.cat1 ;\
	echo "npasswd.1 -> npasswd.cat1"; \
	else \
	echo "Cannot make npasswd.cat1 ($(NROFF) not found)"; \
	fi

#
# Transform HTML documents to text
#

#
# html-txt
# 	Make text versions of HTML files
#
## html-txt: 	Make text versions of HTML files
html-txt:	$(HTML_TXT) docfilter


AdminGuide.txt: AdminGuide.html
	@test -f AdminGuide.html
	-@$(HTCONVERT) AdminGuide.html | ./docfilter | $(HTFILTER) >  AdminGuide.txt.tmp; \
	if [ -s  AdminGuide.txt.tmp ]; then \
	$(MV)  AdminGuide.txt.tmp  AdminGuide.txt; \
	echo "AdminGuide.html ->  AdminGuide.txt"; \
	else \
	echo "Cannot make  AdminGuide.txt ('$(HTCONVERT)' failed)"; \
	$(RM)  AdminGuide.txt.tmp; \
	fi


BuildInstall.txt: BuildInstall.html
	@test -f BuildInstall.html
	-@$(HTCONVERT) BuildInstall.html | ./docfilter | $(HTFILTER) >  BuildInstall.txt.tmp; \
	if [ -s  BuildInstall.txt.tmp ]; then \
	$(MV)  BuildInstall.txt.tmp  BuildInstall.txt; \
	echo "BuildInstall.html ->  BuildInstall.txt"; \
	else \
	echo "Cannot make  BuildInstall.txt ('$(HTCONVERT)' failed)"; \
	$(RM)  BuildInstall.txt.tmp; \
	fi


BugReport.txt: BugReport.html
	@test -f BugReport.html
	-@$(HTCONVERT) BugReport.html | ./docfilter | $(HTFILTER) >  BugReport.txt.tmp; \
	if [ -s  BugReport.txt.tmp ]; then \
	$(MV)  BugReport.txt.tmp  BugReport.txt; \
	echo "BugReport.html ->  BugReport.txt"; \
	else \
	echo "Cannot make  BugReport.txt ('$(HTCONVERT)' failed)"; \
	$(RM)  BugReport.txt.tmp; \
	fi


Copyright.txt: Copyright.html
	@test -f Copyright.html
	-@$(HTCONVERT) Copyright.html | ./docfilter | $(HTFILTER) >  Copyright.txt.tmp; \
	if [ -s  Copyright.txt.tmp ]; then \
	$(MV)  Copyright.txt.tmp  Copyright.txt; \
	echo "Copyright.html ->  Copyright.txt"; \
	else \
	echo "Cannot make  Copyright.txt ('$(HTCONVERT)' failed)"; \
	$(RM)  Copyright.txt.tmp; \
	fi


QNA.txt: QNA.html
	@test -f QNA.html
	-@$(HTCONVERT) QNA.html | ./docfilter | $(HTFILTER) >  QNA.txt.tmp; \
	if [ -s  QNA.txt.tmp ]; then \
	$(MV)  QNA.txt.tmp  QNA.txt; \
	echo "QNA.html ->  QNA.txt"; \
	else \
	echo "Cannot make  QNA.txt ('$(HTCONVERT)' failed)"; \
	$(RM)  QNA.txt.tmp; \
	fi


Main.txt: Main.html
	@test -f Main.html
	-@$(HTCONVERT) Main.html | ./docfilter | $(HTFILTER) >  Main.txt.tmp; \
	if [ -s  Main.txt.tmp ]; then \
	$(MV)  Main.txt.tmp  Main.txt; \
	echo "Main.html ->  Main.txt"; \
	else \
	echo "Cannot make  Main.txt ('$(HTCONVERT)' failed)"; \
	$(RM)  Main.txt.tmp; \
	fi


ManPages.txt: ManPages.html
	@test -f ManPages.html
	-@$(HTCONVERT) ManPages.html | ./docfilter | $(HTFILTER) >  ManPages.txt.tmp; \
	if [ -s  ManPages.txt.tmp ]; then \
	$(MV)  ManPages.txt.tmp  ManPages.txt; \
	echo "ManPages.html ->  ManPages.txt"; \
	else \
	echo "Cannot make  ManPages.txt ('$(HTCONVERT)' failed)"; \
	$(RM)  ManPages.txt.tmp; \
	fi


MiscNotes.txt: MiscNotes.html
	@test -f MiscNotes.html
	-@$(HTCONVERT) MiscNotes.html | ./docfilter | $(HTFILTER) >  MiscNotes.txt.tmp; \
	if [ -s  MiscNotes.txt.tmp ]; then \
	$(MV)  MiscNotes.txt.tmp  MiscNotes.txt; \
	echo "MiscNotes.html ->  MiscNotes.txt"; \
	else \
	echo "Cannot make  MiscNotes.txt ('$(HTCONVERT)' failed)"; \
	$(RM)  MiscNotes.txt.tmp; \
	fi


Support.txt: Support.html
	@test -f Support.html
	-@$(HTCONVERT) Support.html | ./docfilter | $(HTFILTER) >  Support.txt.tmp; \
	if [ -s  Support.txt.tmp ]; then \
	$(MV)  Support.txt.tmp  Support.txt; \
	echo "Support.html ->  Support.txt"; \
	else \
	echo "Cannot make  Support.txt ('$(HTCONVERT)' failed)"; \
	$(RM)  Support.txt.tmp; \
	fi


Reference.txt: Reference.html
	@test -f Reference.html
	-@$(HTCONVERT) Reference.html | ./docfilter | $(HTFILTER) >  Reference.txt.tmp; \
	if [ -s  Reference.txt.tmp ]; then \
	$(MV)  Reference.txt.tmp  Reference.txt; \
	echo "Reference.html ->  Reference.txt"; \
	else \
	echo "Cannot make  Reference.txt ('$(HTCONVERT)' failed)"; \
	$(RM)  Reference.txt.tmp; \
	fi


TOC_std.txt: TOC_std.html
	@test -f TOC_std.html
	-@$(HTCONVERT) TOC_std.html | ./docfilter | $(HTFILTER) >  TOC_std.txt.tmp; \
	if [ -s  TOC_std.txt.tmp ]; then \
	$(MV)  TOC_std.txt.tmp  TOC_std.txt; \
	echo "TOC_std.html ->  TOC_std.txt"; \
	else \
	echo "Cannot make  TOC_std.txt ('$(HTCONVERT)' failed)"; \
	$(RM)  TOC_std.txt.tmp; \
	fi


#
# Install targets
#
install::	install-html

deinstall::	deinstall-html

install::	install-man

deinstall::	deinstall-man

install::	install-txt

deinstall::	deinstall-txt


#
# install-html
# 	Install HTML documents
#
## install-html: 	Install HTML documents

#
# deinstall-html
# 	Remove HTML documents
#
## deinstall-html: 	Remove HTML documents

install-html:: $(PS) $(IMG)
	@case '${MFLAGS}' in *[i]*) set +e;; esac; \
	for i in $(PS) $(IMG); do \
	(set -x; $(INSTALL) -c  -m 0444 $$i  $(DOCS)); \
	done

deinstall-html::
	@case '${MFLAGS}' in *[i]*) set +e;; esac; \
	for i in $(PS) $(IMG); do \
	(set -x; $(RM)  $(DOCS)/$$i); \
	done

install-html::  $(HTML) docfilter
	@case '${MFLAGS}' in *[i]*) set +e;; esac; \
	for f in  $(HTML) ; do \
	$(RM) /tmp/$$f.temp; \
	./docfilter $$f > /tmp/$$f.temp; \
	(set -x; $(INSTALL) -m 444 /tmp/$$f.temp  $(DOCS)/$$f; ); \
	$(RM) /tmp/$$f.temp; \
	done

deinstall-html::
	@case '${MFLAGS}' in *[i]*) set +e;; esac; \
	for f in  $(HTML) ; do \
	$(RM) $(DOCS)/$$f; \
	done

#
# install-man
# 	Install man pages
#
## install-man: 	Install man pages

#
# deinstall-man
# 	Remove man pages
#
## deinstall-man: 	Remove man pages

install-man::  $(MAN_HTML) $(MAN_CAT)
	@case '${MFLAGS}' in *[i]*) set +e;; esac; \
	for i in  $(MAN_HTML) $(MAN_CAT); do \
	(set -x; $(INSTALL) -c  -m 0444 $$i  $(DOCS)); \
	done

deinstall-man::
	@case '${MFLAGS}' in *[i]*) set +e;; esac; \
	for i in  $(MAN_HTML) $(MAN_CAT); do \
	(set -x; $(RM)  $(DOCS)/$$i); \
	done

install-man::  $(MAN) docfilter
	@case '${MFLAGS}' in *[i]*) set +e;; esac; \
	for f in  $(MAN) ; do \
	$(RM) /tmp/$$f.temp; \
	./docfilter $$f > /tmp/$$f.temp; \
	(set -x; $(INSTALL) -m 444 /tmp/$$f.temp  $(DOCS)/$$f; ); \
	$(RM) /tmp/$$f.temp; \
	done

deinstall-man::
	@case '${MFLAGS}' in *[i]*) set +e;; esac; \
	for f in  $(MAN) ; do \
	$(RM) $(DOCS)/$$f; \
	done

#
# install-txt
# 	Install text versions of HTML documents
#
## install-txt: 	Install text versions of HTML documents

#
# deinstall-txt
# 	Remove text versions of HTML documents
#
## deinstall-txt: 	Remove text versions of HTML documents

install-txt::  $(HTML_TXT)
	@case '${MFLAGS}' in *[i]*) set +e;; esac; \
	for i in  $(HTML_TXT); do \
	(set -x; $(INSTALL) -c  -m 0444 $$i  $(DOCS)); \
	done

deinstall-txt::
	@case '${MFLAGS}' in *[i]*) set +e;; esac; \
	for i in  $(HTML_TXT); do \
	(set -x; $(RM)  $(DOCS)/$$i); \
	done

#
# Dependancies for HTML documents
#

AdminGuide.html:
	@exit 0;

BuildInstall.html:
	@exit 0;

BugReport.html:
	@exit 0;

Copyright.html:
	@exit 0;

QNA.html:
	@exit 0;

Main.html:
	@exit 0;

ManPages.html:
	@exit 0;

MiscNotes.html:
	@exit 0;

Support.html:
	@exit 0;

Reference.html:
	@exit 0;

Reference_TOC.html:
	@exit 0;

Reference_index.html:
	@exit 0;

TOC_frame.html:
	@exit 0;

TOC_std.html:
	@exit 0;

index.html:
	@exit 0;

PasswordSecurity.ps:
	@exit 0;

Worm-MIT.ps:
	@exit 0;

Worm-Utah.ps:
	@exit 0;

top.gif:
	@exit 0;

home.gif:
	@exit 0;


#
# Clean the HTML docs created from man pages
#
local_clobber::
	$(RM) $(MAN_HTML) $(HTML_TXT) nroff2html docfilter

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

