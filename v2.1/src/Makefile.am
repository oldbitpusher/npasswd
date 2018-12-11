AC_INIT(npasswd, 2.1)
AM_INIT_AUTOMAKE(npasswd)
AM_CONFIG_HEADER(config.h)

AC_PROG_CC
AC_ISC_POSIX
AC_STDC_HEADERS

SUBDIRS		= Common PasswordCheck Methods

LIB_METHOD	= Methods/libmethod.a
LIB_PWCK	= PasswordCheck/libpwcheck.a
LIB_COMOBJ	= Common/libcomobj.a

bin_PROGRAMS	= npasswd

npasswd_SOURCES = \
	version.c \
	main.c \
	configure.c \
	passwd.c \
	chfn.c \
	chsh.c

npasswd_LDADD	= ${LIB_METHOD} \
		  ${LIB_PWCK} \
		  ${LIB_COMOBJ} \



