
OBJS=itsspwd.o
 SRC=itsspwd.c
LIBS=
LIBS=
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

itsspwd:
	$(CC) -DTEST_ims_pw_chk -o $@ $<

clean:
	/bin/rm -f $(OBJS) itsspwd

install: all

config:
	@./Configure

#
