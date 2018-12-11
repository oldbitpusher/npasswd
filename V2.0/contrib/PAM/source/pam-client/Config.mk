
OBJX=udp-client.o ../../lib/SunOS-sparc/libstrongconfig.a ../../lib/SunOS-sparc/libhide.a ../../lib/SunOS-sparc/libcomobj.a
TARGETS=$(OBJS) pam_strongpw.so.1 pwstrongchk
LIBS=-lsocket -lnsl
OPTS=
CC=cc $(INCLUDES) $(OPTS) -DSunOS -O
