
# --------------------------------------------------------------------  #
#                                                                       #
#                         Author: Clyde Hoover                          #
#                          Computation Center                           #
#                   The University of Texas at Austin                   #
#                          Austin, Texas 78712                          #
#                         clyde@emx.utexas.edu                          #
#                   uunet!cs.utexas.edu!ut-emx!clyde                    #
#                                                                       #
#This code may be distributed freely, provided this notice is retained. #
#                                                                       #
# --------------------------------------------------------------------  #
#
#	Makefile for npasswd
#
#	@(#)Makefile.dist	1.7 12/5/89 (cc.utexas.edu)
#
DEST	= /usr/local
BINDIR	= /bin
ADMDIR	= /lib/npasswd
MANDIR	= /usr/local/man/man1
IMODE	= 4511
PASSWD	= npasswd
DIR	= .
SUBDIRS = checkpasswd 
CHKLIB = checkpasswd/checkpasswd.a
DISTNAME = npasswd

# ---------------------------------------------------------------
#	Configuration parameters
# ---------------------------------------------------------------
# To use an alternate password file, set these defines
#
# PWF = /etc/passwd
# PWT = /etc/ptmp
# PWS = /etc/opasswd
#
# PWFD = -DPASSWD_FILE=\"$(PWF)\"
# PWTD = -DPASSWD_TEMP=\"$(PWT)\"
# PWSD = -DPASSWD_SAVE=\"$(PWS)\"

# The configuration file
CF = $(DEST)$(ADMDIR)/$(PASSWD).conf
CFD = -DCONFIG_FILE=\"$(CF)\"

# The help file
HF = $(DEST)$(ADMDIR)/$(PASSWD).help
HFD = -DHELP_FILE=\"$(HF)\"

# The message file
MF = $(DEST)$(ADMDIR)/$(PASSWD).motd
MFD = -DMOTD_FILE=\"$(MF)\"

# ---------------------------------------------------------------
#	Enable only ONE of the following options
#
# If running with 4.3BSD hashed password file
#BSD = -DBSD4_3 -DNBDM

HPUX = -DHPUX -DNDBM -Dindex=strchr #-llibstrings

# If running under System V
# SYS5 = -DSYSV -Dindex=strchr

# If running under SunOS 4.X (funky tty ioctls)
# SUNOS = -DSUNOS4


# ---------------------------------------------------------------
#	Any number of the following options can be enabled
#
# Use syslog(3) for recording password changes and errors
SYSLOG = -DSYSLOG 

# Use private version of getpass(3) which is better behaved than
# the version in libc (at least the 4.3BSD version).
GETPASS = -DXGETPASS

# -DXPUTPWENT provides putpwent() if not in libc.
PUTPWENT = -DXPUTPWENT

# ---------------------------------------------------------------

DEBUG	= -g -DDEBUG
# 'XFLAGS' are the configuration flags exported to sub-makes
# Change '-O' in XFLAGS to $(DEBUG) for debugging
XFLAGS	= -O $(BSD) $(SYS5) $(SUNOS) $(HPUX)

# 'CFLAGS' are the flags for npasswd only
CFLAGS	= $(XFLAGS) $(SYSLOG) $(GETPASS) $(PUTPWENT) \
	$(HFD) $(CFD) $(MFD) $(PWFD) $(PWTD) $(PWSD)

# Change the following line to $(DEBUG) for debugging
LDFLAGS	= 

# ---------------------------------------------------------------
all:	yp_$(PASSWD)		

first::
	@echo 'Edit this file to comment out all uneeded targets,'
	@echo 'and change the desired target name to "$(PASSWD)"'

# ---------------------------------------------------------------
#	Standard password file version
#OBJ_PW	= npasswd.o pw_passwd.o $(CHKLIB)

#pw_$(PASSWD):	$(OBJ_PW)
#	$(CC) -o $(PASSWD) $(LDFLAGS) $(OBJ_PW) 

# ---------------------------------------------------------------
#	Yellow Pages version
OBJ_YP	= npasswd.o pw_yp.o $(CHKLIB)

yp_$(PASSWD):	$(OBJ_YP)
	@ echo "yp"
	$(CC) -o $(PASSWD) $(LDFLAGS) $(OBJ_YP) -lrpcsvc 

# ---------------------------------------------------------------
#	UTEXAS CC database version
OBJ_UI	= npasswd.o pw_userinfo.o $(CHKLIB)

ui_$(PASSWD):	$(OBJ_UI)
	$(CC) -o $(PASSWD) $(LDFLAGS) $(OBJ_UI) -luserinfo 

# ---------------------------------------------------------------
#
#	Make password checker library
#
$(CHKLIB):
	(cd checkpasswd; make $(MFLAGS) "CFLAGS=$(XFLAGS)" checkpasswd.a)

# ---------------------------------------------------------------
clean::
	-rm -f *.o a.out n*passwd core
	-rm -f passwd passwd.dir passwd.pag opasswd
	-for f in $(SUBDIRS); do \
		(cd $$f; make clean); done

# ---------------------------------------------------------------
install:	yp_$(PASSWD)
	@if [ `whoami` != root ]; then\
		echo Must be super-user to install; \
		exit 1; \
	fi
	install -s -m $(IMODE) $(PASSWD) $(DEST)$(BINDIR)/$(PASSWD)
	@if [ ! -r $(CF) ]; then\
		install -c -m 0644 npasswd.conf $(CF);\
	else \
		echo $(CF) already exists.. edit to change; fi
	@if [ ! -r $(HF) ]; then\
		install -c -m 0644 npasswd.help $(HF);\
	else \
		echo $(HF) already exists.. edit to change; fi
	@echo Put site-specific information in $(MF)

install.man::
	@echo Customize a manual page
#	install -c -m 0444 npasswd.1 $(DEST)$(MANDIR)

# ---------------------------------------------------------------
#	Make copy of password file for testing
setup::
	-rm -f passwd passwd.dir passwd.pag passwd.old
	cp /etc/passwd passwd
	-if [ -f /etc/mkpasswd ]; then \
		/etc/mkpasswd passwd; fi

# ---------------------------------------------------------------
dist::
	@stuff/makedist $(DISTNAME)
 
# ---------------------------------------------------------------
#
# Source dependancies
#
pw_passwd.o:	pw_passwd.c
npasswd.o:	npasswd.c version.h
yp_passwd.o:	yp_passwd.c

