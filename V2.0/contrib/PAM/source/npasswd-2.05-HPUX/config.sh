#!/bin/sh
#
# This file was produced by running the Configure script. It holds all the
# definitions figured out by Configure. Should you modify one of these values,
# do not forget to propagate your changes by running "Configure -der". You may
# instead choose to run each of the .SH files by yourself, or "Configure -S".
#

# Package name      : npasswd
# Source directory  : .
# Configuration time: Tue Apr 10 16:32:58 CDT 2001
# Configured by     : root
# Target system     : hp-ux daln4k b.11.00 u 9000800 639319323 unlimited-user license 

Author=''
Date=''
Header=''
Id=''
Locker=''
Log=''
Mcc='Mcc'
RCSfile=''
Revision=''
Source=''
State=''
afs='false'
aphostname=''
ar='/usr/bin/ar'
archobjs=''
awk='/usr/bin/awk'
baserev='2.0'
bash=''
bison=''
byacc=''
c='\c'
cat='/usr/bin/cat'
cc='cc'
cc_dbflags='-g'
cc_osflags='-DOS_HPUX -D_HPUX_SOURCE -DOS_NAME=hpux -DOS_MAJOR_VERSION=b -DOS_MINOR_VERSION=11'
ccflags='+z'
cf_by='root'
cf_time='Tue Apr 10 16:32:58 CDT 2001'
chgrp=''
chmod=''
chown=''
comm='/usr/bin/comm'
compress=''
contains='grep'
cp=''
cpio=''
cpp='/usr/lib/cpp'
cppflags='+z -DOS_HPUX -D_HPUX_SOURCE -DOS_NAME=hpux -DOS_MAJOR_VERSION=b -DOS_MINOR_VERSION=11'
cpplast='-'
cppminus='-'
cpprun='cc -E'
cppstdin='cc -E'
csh=''
d_bcopy='define'
d_bsd='define'
d_bzero='define'
d_const='undef'
d_dirnamlen=''
d_eunice='undef'
d_fchmod='define'
d_fchown='define'
d_gethname='define'
d_gnulibc='undef'
d_index='undef'
d_memcpy='define'
d_memset='define'
d_open3='define'
d_phostname='undef'
d_portable='undef'
d_pwage='define'
d_pwchange='undef'
d_pwclass='undef'
d_pwcomment='define'
d_pwexpire='undef'
d_pwquota='undef'
d_readdir='define'
d_rename='define'
d_rewinddir=''
d_seekdir=''
d_sigblock='define'
d_strccmp='define'
d_strchr='define'
d_strdup='define'
d_telldir=''
d_uname='undef'
d_voidsig='define'
d_xenix='undef'
date='/usr/bin/date'
defvoidused='15'
direntrytype='struct dirent'
echo='/usr/bin/echo'
egrep=''
emacs=''
eunicefix=':'
expr='/usr/bin/expr'
find=''
firstmakefile=''
flex=''
gcc=''
gccversion=''
gidtype='gid_t'
glibpth='/shlib /usr/shlib /lib/pa1.1 /usr/lib/large /lib /usr/lib /usr/lib/386 /lib/386 /lib/large /usr/lib/small /lib/small /usr/ccs/lib /usr/ucblib /usr/local/lib'
grep='/usr/bin/grep'
groupcat='cat /etc/group'
gzip=''
h_fcntl='false'
h_sysfile='true'
hint='previous'
hostcat='cat /etc/hosts'
huge=''
i_dbm='define'
i_dirent='define'
i_memory='undef'
i_ndbm='define'
i_pwd='define'
i_rpcsvcdbm='undef'
i_sgtty='undef'
i_stdarg='undef'
i_stdlib='define'
i_string='define'
i_sysparam='define'
i_sysresrc='define'
i_systime='define'
i_systimek='undef'
i_termio='undef'
i_termios='define'
i_time='undef'
i_unistd='define'
i_varargs='define'
i_varhdr='varargs.h'
incpath=''
inews=''
install='./install'
installdir='mkdir -p'
installprivlib='/usr/lib/passwd/lib'
ksh=''
large=''
ldflags=''
less=''
lib='/usr/lib/passwd/lib'
libc='/lib/libc.sl'
libexp='/usr/lib/passwd/lib'
libpth='/usr/local/lib /opt/local/lib /lib/pa1.1 /lib /usr/lib /usr/ccs/lib'
libs='-lnet -lnsl'
line=''
lint=''
lkflags=''
ln='/usr/bin/ln'
lns='/usr/bin/ln -s'
loclibpth='/usr/local/lib /opt/local/lib /usr/gnu/lib /opt/gnu/lib /usr/GNU/lib /opt/GNU/lib'
lp=''
lpr=''
ls=''
mail=''
mailx=''
make=''
medium=''
mips=''
mips_type=''
mkdep='/admin/pam_strong/source/npasswd-2.05-HPUX/mkdep'
mkdir='/usr/bin/mkdir'
models='none'
more='/usr/bin/more'
mv='/usr/bin/mv'
mydomain=''
myhostname='daln4k'
myuname='hp-ux daln4k b.11.00 u 9000800 639319323 unlimited-user license '
n=''
nm_opt='-p'
nm_so_opt=''
nroff='/usr/bin/nroff'
optimize='-O'
orderlib='false'
osname='hpux'
osvers='b.11.00'
p_aixauth='undef'
p_clnt_sperrno='define'
p_dbmpw='undef'
p_dictionaries='/usr/lib/passwd/dictionaries'
p_docdir='/usr/lib/passwd/lib/doc'
p_fgetpwent='define'
p_getusershell='define'
p_hesiod='undef'
p_history='/usr/lib/passwd/etc/history'
p_hpuxauth='define'
p_installdir='/usr/lib/passwd/lib'
p_keepdir='/usr/lib/passwd/lib/system'
p_kerberos='undef'
p_lckpwdf='define'
p_nis='undef'
p_nispasswd='undef'
p_nisplus='undef'
p_nsswitch='define'
p_osMajor='b'
p_osMicro='00'
p_osMinor='11'
p_osName='hpux'
p_osRev='b.11.00'
p_osf1auth='undef'
p_paranoid='undef'
p_passwdfile=' /etc/passwd'
p_putpwent='define'
p_replace='undef'
p_rpclib=''
p_secure_rpc='undef'
p_shadow='shm_hpux'
p_shadowfile=''
p_sigposix='define'
p_svcconf='undef'
p_sysinfo='define'
p_sysprogs='/sbin/passwd /usr/bin/chfn /usr/bin/chsh /usr/bin/nispasswd /usr/bin/passwd /usr/bin/yppasswd '
p_ttyposix='define'
p_u4auth='undef'
p_utildir='/usr/lib/passwd/lib/bin'
p_xdr_passwd='define'
p_xdr_uid_t=''
p_xencrypt='undef'
package='npasswd'
passcat='cat /etc/passwd'
perl=''
pg=''
phostname='hostname'
plibpth=''
pmake=''
pr=''
prefix='/usr/lib/passwd'
prefixexp='/usr/lib/passwd'
privlib='/usr/lib/passwd/lib'
privlibexp='/usr/lib/passwd/lib'
prototype='undef'
ranlib=':'
rm='/usr/bin/rm'
rmail=''
runnm='true'
sed='/usr/bin/sed'
sendmail=''
sh='/bin/sh'
shar=''
sharpbang='#!'
shsharp='true'
signal_t='void'
sleep=''
smail=''
small=''
so='sl'
sort='/usr/bin/sort'
spackage=''
spitshell='cat'
split=''
src='.'
startsh='#!/bin/sh'
strings='/usr/include/string.h'
submit=''
sysman='/usr/man/man1'
tail=''
tar=''
tbl=''
test='test'
timeincl='/usr/include/sys/time.h '
top_level='/admin/pam_strong/source/npasswd-2.05-HPUX'
touch='/usr/bin/touch'
tr='/usr/bin/tr'
trdown='[:lower:]'
troff=''
trup='[:upper:]'
uidsigned='define'
uidtype='uid_t'
uname='/usr/bin/uname'
uniq='/usr/bin/uniq'
usenm='true'
usrinc='/usr/include'
uuname=''
vi=''
voidflags='15'
xlibpth='/usr/lib/386 /lib/386'
zcat=''
zip=''
CONFIG=true
