
OBJS=test_libhide.o libhide.o
 SRC=test_libhide.c libhide.c
  AR=ar

include Config.mk

all: $(TARGETS)

.SUFFIXES: .sl .so .a

.o.a:
	$(AR) $(ARFLAGS) $@ $< >/dev/null 2>&1

.o.so:
	$(LD) -V -G -i -o $@ $< >/dev/null 2>&1

.o.sl:
	$(LD) -V -b -o $@ $< >/dev/null 2>&1

clean:
	/bin/rm -f $(OBJS) test_libhide libhide.s[lo] libhide.a core

test_libhide: test_libhide.c libhide.h libhide.c
	$(CC) $(OBJS) -o $@

install: all
	@./install_ksh

config:
	@./Configure

#
