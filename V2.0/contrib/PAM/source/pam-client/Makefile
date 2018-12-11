
INCLUDES=-I../../include

OBJS=udp-client.o pam_strongpw.o
 SRC=udp-client.c pam_strongpw.c

include Config.mk



all: $(TARGETS)


pwstrongchk: $(OBJX) pwstrongchk.c
	$(CC) $(LIBS) $(OBJX) -o $@ $@.c

lint: udp-client.c
	lint $(INCLUDES) -R./udp-client  udp-client.c
	lint $(INCLUDES) -R./pwstrongchk pwstrongchk.c
	lint -I../../include -R./pam_strongpw pam_strongpw.c
	@rm *.lnt

pam_strongpw.so.1: pam_strongpw.o
	ld -V -G -o pam_strongpw.so.1 pam_strongpw.o $(OBJX) -lc -lpam

pam_strongpw.sl.1: pam_strongpw.o
	ld -V -b -o pam_strongpw.sl.1 pam_strongpw.o $(OBJX) -lpam -lsec -lc

clean:
	/bin/rm -f $(OBJS) pam_strongpw.s[lo].1 pwstrongchk core *.o

save: all
	@./pam_strong_save

install: all
	@./pam_strong_save
#	@./pam_strong_install

install_pwstrongchk: all
	cp pwstrongchk ../../bin/pwstrongchk
	chmod 0755 ../../bin/pwstrongchk

config:
	@./Configure

#END
