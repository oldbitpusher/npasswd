
INCLUDES=-I../../include
OBJS=libstrongconfig.o
 SRC=libstrongconfig.c

include Config.mk

xx=lint $(INCLUDES)
LIBS=-lsocket -lnsl


all: $(SRC) $(OBJS) $(TARGETS) libstrongconfig.a

.SUFFIXES: .sl .so .a

.o.a:
	$(AR) $(ARFLAGS) $@ $<    >/dev/null 2>&1

.o.so:
	$(LD) -V -G -i -o $@ $<   >/dev/null 2>&1

.o.sl:
	$(LD) -V -b -o $@ $<      >/dev/null 2>&1


lint: libstrongconfig.c
	lint $(INCLUDES) -R./libstrongconfig libstrongconfig.c
	@/bin/rm *.lnt *.ln

clean:
	/bin/rm -f $(OBJS) libstrongconfig.lnt libstrongconfig.ln *.s[ol] *.a core

install: all
	@./install_ksh

config:
	@./Configure


