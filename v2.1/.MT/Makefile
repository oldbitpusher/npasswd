SHELL = /bin/sh
W = src d_bcopy d_bsd d_bzero d_const d_fchmod d_fchown d_gethname d_memcpy d_memset d_open3 d_pwage d_pwcomment d_pwquota d_readdir d_rename d_sigblock d_strccmp d_strchr d_strdup baserev c cc cc_dbflags cc_osflags ccflags cf_by cf_time direntrytype eunicefix gidtype install installdir large ldflags libs ln lns mkdep mv myhostname myuname n nroff optimize p_aixauth p_clnt_sperrno p_dbmpw p_dictionaries p_docdir p_fgetpwent p_getusershell p_history p_hpuxauth p_installdir p_keepdir p_kerberos p_lckpwdf p_nis p_nispasswd p_nisplus p_nsswitch p_osName p_osf1auth p_paranoid p_passwdfile p_putpwent p_replace p_secure_rpc p_shadow p_shadowfile p_sigposix p_svcconf p_sysinfo p_sysprogs p_ttyposix p_u4auth p_utildir p_utsname p_xdr_passwd package prototype ranlib rm sed signal_t spitshell startsh top_level tr trdown trup uidsigned uidtype voidflags i_dbm i_dirent i_memory i_ndbm i_sgtty i_stdlib i_string i_sysparam i_sysresrc i_systime i_termio i_termios i_unistd i_varhdr
All:Finish
Begin:Myinit Options package Extractall
	-pick add $@ Begin
Chk_MANI:Begin c n rsrc
	-pick wipe $@ Chk_MANI
Chk_whoami:d_uname i_whoami
	-pick add $@ Chk_whoami
Config_h:Id End Config_sh Obsol_h myuname cf_time cf_by package src
	-pick c_h_weed $@ Config_h
	-pick c_h_weed $@ ./Config_h
	-pick c_h_weed $@ ./Obsol_h
Config_sh:cf_time cf_by test spitshell startsh myuname Myread End Obsol_sh Loc d_portable package src
	-cond d_portable 
	-pick add.Config_sh $@ Config_sh
	-pick add $@ ./Obsol_sh
	-pick close.Config_sh $@ Config_sh
Configdir:package
	-pick add $@ Configdir
Cppsym:eunicefix Guess cppstdin awk cat tr sed sort grep rm startsh contains cppminus cc  test comm uniq echo n c Options
	-cond cc gccversion 
	-pick add $@ Cppsym
Csym:Options contains libc libs runnm cc ccflags ldflags rm
	-cond cc ccflags ldflags 
	-pick add $@ Csym
Extract:src
	-pick add $@ Extract
Extractall:Extract Options rsrc
	-pick wipe $@ Extractall
Filexp:startsh sed test expr eunicefix
	-pick add $@ Filexp
Findhdr:grep test tr rm usrinc awk cat startsh cppstdin cppminus cppflags
	-cond usrinc cppflags 
	-pick add $@ Findhdr
Finish:Chk_MANI Extract Myread Oldsym Magic_h cat rm contains
	-pick add $@ Finish
Getfile:d_portable contains startsh Myread Filexp
	-pick add $@ Getfile
Guess d_eunice d_xenix d_bsd:cat test echo n c contains rm Loc eunicefix
	-pick add $@ Guess
Head:
	-pick wipe $@ Head
Inhdr:test Findhdr Whoa
	-pick add $@ Inhdr
Init eunicefix:Null
	-pick add $@ Init
	-pick weed $@ ./Init
Inlibc:Csym Whoa Oldconfig
	-pick add $@ Inlibc
Instruct:Myread Configdir contains
	-pick wipe $@ Instruct
Loc Mcc awk ar bash bison byacc cat chgrp chmod chown comm compress cp cpio cpp csh date echo egrep emacs expr find flex gcc gzip grep inews ksh less line lint ln lp lpr ls mail mailx make mkdir more mv nroff perl pg pmake pr rm rmail sed sendmail shar sleep smail sort submit tail tar tbl test touch tr troff uname uniq uuname vi zcat zip:eunicefix n c Instruct Myread startsh
	-pick weed $@ Loc
full_sed:sed
	-pick add $@ Loc_sed
Magic_h:Id Config_h
	-pick cm_h_weed $@ Magic_h
	-pick cm_h_weed $@ ./Magic_h
MailAuthor mailpatches notifypatches usermail:test cat mailer package Myread patchlevel baserev rm rsrc Oldconfig Configdir
	-pick wipe $@ MailAuthor
MailList:cat mailer package Myread cf_name cf_email
	-pick wipe $@ MailList
Myread:Options startsh n c
	-pick add $@ Myread
Nothing:Head
Null:Head
	-pick add.Null $@ Null
Obsol_h:
	-pick prepend $@ ./Obsol_h
Obsol_sh:
	-pick prepend $@ ./Obsol_sh
Oldconfig hint myuname osname osvers:Instruct Myread uname sh awk sed test cat rm lns n c contains Loc Options Tr src
	-pick wipe $@ Oldconfig
Oldsym:Config_sh test hint src
	-pick add $@ Oldsym
Options:startsh
	-pick wipe $@ Options
Prefixit:prefix oldprefix
	-pick add $@ Prefixit
Prefixup:prefix prefixexp
	-pick add $@ Prefixup
Author Date Header Id Locker Log RCSfile Revision Source State:Oldconfig
	-pick weed $@ Rcs
Setvar:Whoa
	-pick add $@ Setvar
Signal:test tr rm awk cat grep startsh eunicefix sed sort uniq Findhdr cppstdin cppflags cppminus cc ccflags ldflags _o
	-cond cppflags cc ccflags ldflags 
	-pick add $@ Signal
Typedef:cppstdin cppminus cppflags rm contains Oldconfig
	-pick add $@ Typedef
Unix _exe _a _o firstmakefile archobjs:Oldconfig
	-pick add $@ Unix
Warn_v7EXT:package Guess
	-pick add $@ Warn_v7EXT
Warn_v7ND:package Guess
	-pick add $@ Warn_v7ND
Whoa:Myread startsh hint
	-pick add $@ Whoa
abortsig:Myread Oldconfig Guess cat cc ccflags rm
	-cond cc 
	-pick add $@ abortsig
active activeexp:newslib Oldconfig Getfile
	-pick add $@ active
afs:Nothing
	-pick add $@ afs
alignbytes:Myread cat cc ccflags rm
	-pick add $@ alignbytes
d_archlib archlib archlibexp installarchlib:archname afs spackage cat Getfile Loc Oldconfig prefixexp privlib test Prefixit Prefixup
	-pick add $@ archlib
archname myarchname:sed Loc Myread Oldconfig osname test rm
	-pick add $@ archname
baserev:Null
	-pick wipe $@ baserev
basicshell:Getfile Oldconfig bash csh ksh sh
	-pick add $@ basicshell
bin binexp installbin:Prefixit Getfile Oldconfig afs cat test
	-pick add $@ bin
bitpbyte:cat rm Myread cc ccflags
	-cond cc ccflags 
	-pick add $@ bitpbyte
byteorder:cat Myread Oldconfig Loc cc ccflags rm
	-cond cc ccflags 
	-pick add $@ byteorder
cc gccversion:cat contains sysman large cpp rm Mcc Myread Guess Options Oldconfig Loc
	-cond large 
	-pick add $@ cc
cf_email:cat cf_by myhostname mydomain Oldconfig Myread
	-pick add $@ cf_email
cf_name:cf_by passcat Filexp nametype cat test
	-pick add $@ cf_name
cf_time cf_by:date Oldconfig
	-pick add $@ cf_who
chorder_int chorder_short chorder_long:Myread cat cc ccflags rm
	-cond cc ccflags 
	-pick add $@ charorder
charsize:cat rm Myread cc ccflags
	-cond cc ccflags 
	-pick add $@ charsize
contains:Nothing
	-pick add $@ contains
cpp_stuff:cat contains cppstdin cppflags cppminus rm
	-pick add $@ cpp_stuff
cppfilecom cppstdinflags d_cppignhdrs d_cppcanstdin:contains package test Myread Oldconfig Loc Setvar cpp cc cat rm
	-pick add $@ cppfilecom
cppstdin cppminus cpprun cpplast:contains test Myread Oldconfig Loc cpp cc rm
	-cond cc 
	-pick add $@ cppstdin
nofile d_gettblsz tablesize:Myread Guess libc cat cc ccflags libs test rm Csym
	-cond cc ccflags libs 
	-pick add $@ d_NOFILE
d_news d_news0 d_newshome d_textcan:test rm Myread Getfile
	-pick add $@ d_NeWS
d_PORTAR:cat cc rm Setvar
	-cond cc 
	-pick add $@ d_PORTAR
d_SHM_MAC d_SHM_PRM d_SHM_SEG d_SHM_IMMU:cat d_shm test rm cc ccflags
	-cond cc ccflags 
	-pick add $@ d_SHM_MAC
d_access:test cc cat cppflags h_fcntl h_sysfile rm Inlibc Findhdr
	-cond cc cppflags 
	-pick add $@ d_access
d_alarm:Inlibc
	-pick add $@ d_alarm
d_attribut:Myread Oldconfig cat cc ccflags rm Setvar contains
	-pick add $@ d_attribut
d_bcmp:Inlibc
	-pick add $@ d_bcmp
d_bcopy:Inlibc
	-pick add $@ d_bcopy
d_brokstat:cat contains cppstdin cppminus cppflags rm Setvar
	-cond cppflags 
	-pick add $@ d_brokstat
d_bsdjmp:Guess Setvar cat cc libs rm
	-cond cc 
	-pick add $@ d_bsdjmp
d_byacc:byacc Setvar
	-pick add $@ d_byacc
d_bzero:Inlibc
	-pick add $@ d_bzero
d_casti32:cat cc ccflags rm intsize Setvar test signal_t
	-cond cc ccflags 
	-pick add $@ d_casti32
d_castneg castflags:cat cc ccflags rm Setvar signal_t
	-cond cc ccflags 
	-pick add $@ d_castneg
d_cbrt:Inlibc
	-pick add $@ d_cbrt
d_charsprf:cat rm cc Setvar
	-cond cc 
	-pick add $@ d_charsprf
d_chown:Inlibc
	-pick add $@ d_chown
d_chroot:Inlibc
	-pick add $@ d_chroot
d_chsize:Inlibc
	-pick add $@ d_chsize
d_ckeypad:cat cc termlib Setvar
	-pick add $@ d_ckeypad
d_closedir d_void_closedir:Inlibc i_dirent i_sysdir i_sysndir cc ccflags ldflags libs Setvar rm
	-pick add $@ d_closedir
d_const:cat cc ccflags Setvar
	-pick add $@ d_const
d_crypt cryptlib:Loc test xlibpth libpth Csym Setvar _a
	-pick add $@ d_crypt
d_csh full_csh:csh Setvar
	-pick add $@ d_csh
d_ctermid:Inlibc
	-pick add $@ d_ctermid
d_cuserid:Inlibc
	-pick add $@ d_cuserid
d_dbl_dig:Myread contains cat rm Setvar i_limits i_float cppstdin cppflags cppminus
	-pick add $@ d_dbl_dig
d_difftime:Inlibc
	-pick add $@ d_difftime
d_dlerror:Inlibc runnm
	-pick add $@ d_dlerror
d_dlopen:Inlibc runnm
	-pick add $@ d_dlopen
d_dosuid d_suidsafe:cat contains ls rm test Myread Setvar Oldconfig Guess package hint
	-pick add $@ d_dosuid
d_drem:Inlibc
	-pick add $@ d_drem
d_dup2:Inlibc
	-pick add $@ d_dup2
d_eofpipe:cat cc ccflags libs rm Oldconfig Guess echo n c
	-cond cc ccflags libs 
	-pick add $@ d_eofpipe
d_euc2jis:Inlibc
	-pick add $@ d_euc2jis
d_fchmod:Inlibc
	-pick add $@ d_fchmod
d_fchown:Inlibc
	-pick add $@ d_fchown
d_fcntl:Inlibc
	-pick add $@ d_fcntl
d_fd_set d_fd_macros d_fds_bits:cat cc ccflags rm Oldconfig d_socket i_systime i_sysselct
	-cond cc ccflags 
	-pick add $@ d_fd_set
d_ffs:Inlibc
	-pick add $@ d_ffs
d_fgetpos:Inlibc
	-pick add $@ d_fgetpos
d_flexfnam:cat rm test Setvar
	-pick add $@ d_flexfnam
d_flock:Inlibc
	-pick add $@ d_flock
d_fmod:Inlibc
	-pick add $@ d_fmod
d_fork:Inlibc
	-pick add $@ d_fork
d_fsetpos:Inlibc
	-pick add $@ d_fsetpos
d_ftime d_gettimeod:Inlibc Setvar
	-pick add $@ d_ftime
d_ftrncate:Inlibc
	-pick add $@ d_ftrncate
d_Gconvert:cat cc ccflags ldflags libs Inlibc rm _o
	-pick add $@ d_gconvert
d_getgrps:Inlibc
	-pick add $@ d_getgrps
d_gethbynm:Inlibc
	-pick add $@ d_gethbynm
d_gethent:Inlibc
	-pick add $@ d_gethent
d_gethid:Inlibc
	-pick add $@ d_gethid
d_gethname d_uname d_phostname aphostname:phostname cat myhostname package d_portable Loc libc echo n c  usrinc Myread Guess Oldconfig Csym
	-cond i_whoami usrinc 
	-pick add $@ d_gethname
d_getlogin:Inlibc
	-pick add $@ d_getlogin
d_getopt:Inlibc
	-pick add $@ d_getopt
d_getpagsz pagesize:Oldconfig Myread Inlibc cat contains cc ccflags libs rm Findhdr
	-cond cc ccflags 
	-pick add $@ d_getpagsz
d_getpgid:Inlibc
	-pick add $@ d_getpgid
d_getpgrp d_bsdgetpgrp:Guess Inlibc Setvar cat rm cc ccflags ldflags libs i_unistd
	-cond cc ccflags ldflags libs 
	-pick add $@ d_getpgrp
d_getpgrp2:Inlibc
	-pick add $@ d_getpgrp2
d_getppid:Inlibc
	-pick add $@ d_getppid
d_getprior:Inlibc
	-pick add $@ d_getprior
d_getpwent:Csym Setvar
	-pick add $@ d_getpwent
d_getwd:Csym Setvar
	-pick add $@ d_getwd
d_gnulibc:Myread Oldconfig Setvar contains rm cc ccflags ldflags libs
	-cond cc ccflags ldflags libs 
	-pick add $@ d_gnulibc
d_havetlib termlib:cat contains Myread Loc Filexp Oldconfig libpth test uname _a _o
	-pick add $@ d_havetlib
d_hidnet hiddennet:cat sed myhostname mydomain Myread Oldconfig
	-pick add $@ d_hidnet
d_htonl:Inlibc Setvar i_niin i_sysin cat rm contains cppstdin cppflags cppminus
	-pick add $@ d_htonl
d_inetaton:Inlibc
	-pick add $@ d_inetaton
d_inetd:cat test package Myread Setvar
	-pick add $@ d_inetd
d_internet:Myread Oldconfig Setvar
	-pick add $@ d_internet
d_isascii:cc cat ccflags ldflags rm libs Setvar
	-pick add $@ d_isascii
d_itimer:Inlibc
	-pick add $@ d_itimer
d_keepsig:cat cc ccflags rm Guess contains echo n c Setvar
	-cond cc ccflags 
	-pick add $@ d_keepsig
d_killpg:Inlibc
	-pick add $@ d_killpg
d_link:Inlibc
	-pick add $@ d_link
d_linuxstd:d_stdstdio cppstdin cppflags cppminus contains rm Setvar Findhdr
	-pick add $@ d_linuxstd
d_locconv:Inlibc
	-pick add $@ d_locconv
d_lockf:Inlibc
	-pick add $@ d_lockf
d_lstat:Inlibc
	-pick add $@ d_lstat
d_mblen:Inlibc
	-pick add $@ d_mblen
d_mbstowcs:Inlibc
	-pick add $@ d_mbstowcs
d_mbtowc:Inlibc
	-pick add $@ d_mbtowc
d_memccpy:Inlibc
	-pick add $@ d_memccpy
d_memchr:Inlibc
	-pick add $@ d_memchr
d_memcmp:Inlibc
	-pick add $@ d_memcmp
d_memcpy:Inlibc
	-pick add $@ d_memcpy
d_memmove:Inlibc
	-pick add $@ d_memmove
d_memset:Inlibc
	-pick add $@ d_memset
d_mkdir:Inlibc
	-pick add $@ d_mkdir
d_mkfifo:Inlibc
	-pick add $@ d_mkfifo
d_mktime:Inlibc
	-pick add $@ d_mktime
d_mmap:Inlibc
	-pick add $@ d_mmap
d_msg:test d_msgctl d_msgget d_msgsnd d_msgrcv Setvar Findhdr
	-pick add $@ d_msg
d_msgctl:Inlibc
	-pick add $@ d_msgctl
d_msgget:Inlibc
	-pick add $@ d_msgget
d_msgrcv:Inlibc
	-pick add $@ d_msgrcv
d_msgsnd:Inlibc
	-pick add $@ d_msgsnd
d_msync:Inlibc
	-pick add $@ d_msync
d_munmap:Inlibc
	-pick add $@ d_munmap
d_newsadm newsadmin:cat contains Guess Setvar Myread Oldconfig
	-pick add $@ d_newsadm
d_nice:Inlibc
	-pick add $@ d_nice
d_nolnbuf:test cc cat rm Setvar Myread
	-cond cc 
	-pick add $@ d_nolnbuf
d_normsig jobslib:test Setvar Guess _a
	-pick add $@ d_normsig
d_open3:test cc cat cppflags h_fcntl h_sysfile rm Setvar Findhdr
	-cond cc cppflags 
	-pick add $@ d_open3
d_pathconf d_fpathconf:Inlibc
	-pick add $@ d_pathconf
d_pause:Inlibc
	-pick add $@ d_pause
d_perror:Inlibc
	-pick add $@ d_perror
d_pidcheck:cat rm cc _o
	-cond cc 
	-pick add $@ d_pidcheck
d_pipe:Inlibc
	-pick add $@ d_pipe
d_poll:Inlibc
	-pick add $@ d_poll
d_popen:Inlibc
	-pick add $@ d_popen
d_portable:cat Loc Myread Oldconfig
	-pick add $@ d_portable
d_psignal:Inlibc
	-pick add $@ d_psignal
d_raster rasterlib:cat test Setvar Myread Oldconfig
	-pick add $@ d_raster
d_rdchk:Inlibc
	-pick add $@ d_rdchk
d_readdir d_seekdir d_telldir d_rewinddir:Inlibc
	-pick add $@ d_readdir
d_readlink:Inlibc
	-pick add $@ d_readlink
d_regcmp d_re_comp d_regcomp:Csym cat
	-pick add $@ d_regcmp
d_rename:Inlibc
	-pick add $@ d_rename
d_rmdir:Inlibc
	-pick add $@ d_rmdir
d_rusage:Inlibc
	-pick add $@ d_rusage
d_safebcpy:cat d_bcopy cc optimize ccflags ldflags libs rm d_memmove i_memory i_stdlib i_string i_unistd Oldconfig Setvar
	-cond cc optimize ccflags ldflags libs 
	-pick add $@ d_safebcpy
d_safemcpy:cat d_memcpy cc optimize ccflags libs ldflags rm d_memmove i_memory i_stdlib i_string i_unistd Oldconfig Setvar
	-cond cc optimize ccflags libs ldflags 
	-pick add $@ d_safemcpy
d_sanemcmp:cat d_memcmp cc optimize ccflags libs ldflags rm i_memory i_stdlib i_string i_unistd Oldconfig Setvar
	-cond cc optimize ccflags libs ldflags 
	-pick add $@ d_sanemcmp
d_sbrk:Inlibc
	-pick add $@ d_sbrk
d_scandir:Inlibc
	-pick add $@ d_scandir
d_scannl:cat cc ccflags rm Setvar
	-cond cc ccflags 
	-pick add $@ d_scannl
d_scorfl:cat Myread Oldconfig nametype Setvar
	-pick add $@ d_scorfl
d_select:Inlibc
	-pick add $@ d_select
d_sem:test d_semctl d_semget d_semop Setvar Findhdr
	-pick add $@ d_sem
d_semctl:Inlibc
	-pick add $@ d_semctl
d_semget:Inlibc
	-pick add $@ d_semget
d_semop:Inlibc
	-pick add $@ d_semop
d_setegid:Inlibc
	-pick add $@ d_setegid
d_seteuid:Inlibc
	-pick add $@ d_seteuid
d_setlinebuf:Inlibc
	-pick add $@ d_setlnbuf
d_setlocale:Inlibc
	-pick add $@ d_setlocale
d_setpgid:Inlibc
	-pick add $@ d_setpgid
d_setpgrp d_bsdsetpgrp:cat rm cc libs ccflags ldflags Inlibc Guess Setvar i_unistd
	-cond cc libs ccflags ldflags 
	-pick add $@ d_setpgrp
d_setpgrp2:Inlibc
	-pick add $@ d_setpgrp2
d_setprior:Inlibc
	-pick add $@ d_setprior
d_setregid d_setresgid:Inlibc
	-pick add $@ d_setregid
d_setreuid d_setresuid:Inlibc
	-pick add $@ d_setreuid
d_setrgid:Inlibc
	-pick add $@ d_setrgid
d_setruid:Inlibc
	-pick add $@ d_setruid
d_setsid:Inlibc
	-pick add $@ d_setsid
d_sgndchr:cat rm cc ccflags Setvar
	-cond cc ccflags 
	-pick add $@ d_sgndchr
d_shm:test d_shmctl d_shmget d_shmat d_shmdt Setvar Findhdr
	-pick add $@ d_shm
d_shmat shmattype d_shmatprototype:Inlibc cat cc ccflags rm cppstdin cppflags cppminus Findhdr Setvar contains
	-cond cc ccflags 
	-pick add $@ d_shmat
d_shmctl:Inlibc
	-pick add $@ d_shmctl
d_shmdt:Inlibc
	-pick add $@ d_shmdt
d_shmget:Inlibc
	-pick add $@ d_shmget
d_sigaction:Csym Setvar cat cc ccflags ldflags libs rm _o
	-pick add $@ d_sigaction
d_sigblock:Inlibc
	-pick add $@ d_sigblock
d_sighold:Inlibc
	-pick add $@ d_sighold
d_siglist:Csym Setvar
	-pick add $@ d_siglist
d_sigsetjmp:Setvar cat cc ccflags ldflags libs rm
	-cond cc ccflags ldflags 
	-pick add $@ d_sigsetjmp
d_sigsetmk:Csym Setvar
	-pick add $@ d_sigsetmk
d_sigvec d_sigvectr d_sigintrp:Csym Inlibc Setvar
	-pick add $@ d_sigvec
d_sjis2jis:Inlibc
	-pick add $@ d_sjis2jis
d_socket d_oldsock d_sockpair socketlib sockethdr:contains libc echo n c nm_opt nm_extract Inlibc Csym _a
	-pick add $@ d_socket
d_speedopt:Myread Cppsym Oldconfig cat models Setvar
	-pick add $@ d_speedopt
d_stat:Inlibc
	-pick add $@ d_stat
d_statblks:contains Setvar Findhdr
	-pick add $@ d_statblks
d_stdstdio d_stdiobase stdio_ptr stdio_cnt stdio_base stdio_bufsiz d_stdio_cnt_lval d_stdio_ptr_lval stdio_filbuf:cat cc ccflags contains ldflags libs rm Setvar Findhdr Oldconfig
	-cond cc ccflags ldflags libs 
	-pick add $@ d_stdstdio
d_strccmp:Inlibc
	-pick add $@ d_strccmp
d_strchr d_index:contains strings Setvar Myread Oldconfig Csym
	-pick add $@ d_strchr
d_strcoll:Inlibc
	-pick add $@ d_strcoll
d_strcspn:Inlibc
	-pick add $@ d_strcspn
d_strctcpy:cat rm cc Setvar
	-pick add $@ d_strctcpy
d_strdup:Inlibc
	-pick add $@ d_strdup
d_strerror d_syserrlst d_sysernlst d_strerrm:contains Csym Findhdr
	-pick add $@ d_strerror
d_strftime:Inlibc
	-pick add $@ d_strftime
d_strstr:Inlibc
	-pick add $@ d_strstr
d_strtod:Inlibc
	-pick add $@ d_strtod
d_strtok:Inlibc
	-pick add $@ d_strtok
d_strtol:Inlibc
	-pick add $@ d_strtol
d_strtoul:Inlibc
	-pick add $@ d_strtoul
d_strxfrm:Inlibc
	-pick add $@ d_strxfrm
d_su_chown:Csym Setvar
	-pick add $@ d_su_chown
d_symlink:Inlibc
	-pick add $@ d_symlink
d_syscall:Inlibc
	-pick add $@ d_syscall
d_sysconf:Inlibc
	-pick add $@ d_sysconf
d_syslog syslogc syslogo:test Csym Setvar Findhdr _o
	-pick add $@ d_syslog
d_system:Inlibc
	-pick add $@ d_system
d_table:Inlibc
	-pick add $@ d_table
d_tcgetpgrp:Inlibc
	-pick add $@ d_tcgtpgrp
d_tcsetpgrp:Inlibc
	-pick add $@ d_tcstpgrp
d_time timetype:Csym Setvar Findhdr Myread Typedef
	-pick add $@ d_time
d_times clocktype:Csym Myread Typedef i_systimes
	-pick add $@ d_times
d_tminsys:contains Setvar Findhdr
	-pick add $@ d_tminsys
d_truncate:Inlibc
	-pick add $@ d_truncate
d_tzmin:contains cppstdin cppminus timeincl rm Setvar Guess
	-pick add $@ d_tzmin
d_tzname:Csym Setvar
	-pick add $@ d_tzname
d_ulimit:Inlibc
	-pick add $@ d_ulimit
d_umask:Inlibc
	-pick add $@ d_umask
d_usendir i_ndir ndirc ndiro ndirlib:test Csym Findhdr _a _o
	-pick add $@ d_usendir
d_usleep:Inlibc
	-pick add $@ d_usleep
d_uwait d_uwait3:cat contains cppstdin cppminus cppflags rm Setvar Findhdr
	-cond cppflags 
	-pick add $@ d_uwait
d_vfork usevfork:Inlibc Myread Oldconfig Setvar
	-pick add $@ d_vfork
d_voidsig signal_t:rm contains cppstdin cppminus cppflags test Myread Oldconfig Setvar Findhdr
	-cond cppflags 
	-pick add $@ d_voidsig
d_volatile:cat cc ccflags rm Setvar
	-cond cc ccflags 
	-pick add $@ d_volatile
d_vprintf d_charvspr:Guess cat cc ccflags Csym Setvar
	-cond cc ccflags 
	-pick add $@ d_vprintf
d_wait3:Inlibc
	-pick add $@ d_wait3
d_wait4:Inlibc
	-pick add $@ d_wait4
d_waitpid:Inlibc
	-pick add $@ d_waitpid
d_wcstombs:Inlibc
	-pick add $@ d_wcstombs
d_wctomb:Inlibc
	-pick add $@ d_wctomb
d_wifstat:d_uwait cc ccflags ldflags libs Oldconfig cat rm
	-cond cc ccflags ldflags libs 
	-pick add $@ d_wifstat
d_xdrs:cat Csym Setvar
	-pick add $@ d_xdrs
defeditor:Getfile Oldconfig Loc vi
	-pick add $@ defeditor
doublesize:cat rm Myread cc ccflags
	-cond cc ccflags 
	-pick add $@ doublesize
errnolist errnolist_SH errnolist_a errnolist_c errnolist_o:cat cc ccflags libs  _a _o
	-cond cc ccflags libs d_sysernlst 
	-pick add $@ errnolist
etc etcexp:Getfile Loc Oldconfig
	-pick add $@ etc
filexp:privlib
	-pick add $@ filexp
floatsize:cat rm Myread cc ccflags
	-cond cc ccflags 
	-pick add $@ floatsize
fpostype:Myread Typedef
	-pick add $@ fpostype
fpu:test cat cc Myread
	-pick add $@ fpu
gidtype:Myread Typedef Findhdr
	-pick add $@ gidtype
groupstype:gidtype d_getgrps Myread Oldconfig Findhdr cat
	-pick add $@ groupstype
h_fcntl:Nothing
	-pick add $@ h_fcntl
h_sysfile:Nothing
	-pick add $@ h_sysfile
i_arpainet:Inhdr
	-pick add $@ i_arpainet
i_db db_hashtype db_prefixtype:Inhdr cc ccflags rm contains cat d_const
	-cond cc ccflags 
	-pick add $@ i_db
i_dbm i_rpcsvcdbm:Inhdr Inlibc Setvar
	-pick add $@ i_dbm
i_dirent d_dirnamlen direntrytype:test contains Setvar Myread Findhdr cppstdin cppflags cppminus rm
	-pick add $@ i_dirent
i_dld:Inhdr
	-pick add $@ i_dld
i_dlfcn:Inhdr
	-pick add $@ i_dlfcn
i_fcntl:h_fcntl h_sysfile  Inhdr Setvar
	-cond i_sysfile 
	-pick add $@ i_fcntl
i_float:Inhdr
	-pick add $@ i_float
i_gdbm:Inhdr Inlibc Setvar
	-pick add $@ i_gdbm
i_grp:Inhdr
	-pick add $@ i_grp
i_limits:Inhdr
	-pick add $@ i_limits
i_locale:Inhdr
	-pick add $@ i_locale
i_malloc:Inhdr
	-pick add $@ i_malloc
i_math:Inhdr
	-pick add $@ i_math
i_memory:Inhdr strings cppstdin cppflags cppminus contains rm Setvar
	-pick add $@ i_memory
i_ndbm:Inhdr Inlibc Setvar
	-pick add $@ i_ndbm
i_neterrno:Inhdr cc ccflags rm Setvar
	-cond cc ccflags 
	-pick add $@ i_neterrno
i_niin i_sysin:Inhdr
	-pick add $@ i_niin
i_pwd d_pwquota d_pwage d_pwchange d_pwclass d_pwexpire d_pwcomment:contains rm cppstdin cppflags cppminus Inhdr Findhdr Setvar
	-pick add $@ i_pwd
i_regex:Inhdr
	-pick add $@ i_regex
i_sfio:Inhdr Setvar
	-pick add $@ i_sfio
i_stddef:Inhdr
	-pick add $@ i_stddef
i_stdlib:Inhdr
	-pick add $@ i_stdlib
i_string strings:test Setvar Findhdr
	-pick add $@ i_string
i_sysdir:Inhdr
	-pick add $@ i_sysdir
i_sysfile:h_sysfile Inhdr Setvar
	-pick add $@ i_sysfile
i_sysioctl i_bsdioctl i_sysfilio i_syssockio d_voidtty:test contains cat i_termio i_termios i_sgtty Setvar Findhdr cc rm Inhdr
	-cond cc 
	-pick add $@ i_sysioctl
i_sysmman:Inhdr
	-pick add $@ i_sysmman
i_sysndir:Inhdr
	-pick add $@ i_sysndir
i_sysparam:Inhdr
	-pick add $@ i_sysparam
i_sysresrc:Inhdr
	-pick add $@ i_sysresrc
i_sysselct:Inhdr
	-pick add $@ i_sysselct
i_syssock:Inhdr
	-pick add $@ i_syssock
i_sysstat:Inhdr
	-pick add $@ i_sysstat
i_systable:Inhdr
	-pick add $@ i_systable
i_systimeb:test contains Loc Setvar Findhdr
	-pick add $@ i_systimeb
i_systimes:Inhdr
	-pick add $@ i_systimes
i_systwgcf:Inhdr
	-pick add $@ i_systwgcf
i_systypes:Inhdr
	-pick add $@ i_systypes
i_sysun:Inhdr
	-pick add $@ i_sysun
i_syswait:Inhdr
	-pick add $@ i_syswait
i_termio i_sgtty i_termios:test Inlibc Cppsym Guess Setvar Findhdr
	-pick add $@ i_termio
i_time i_systime i_systimek timeincl:cat cc ccflags contains rm echo n c  Findhdr
	-cond i_sysselct 
	-pick add $@ i_time
i_unistd:Inhdr
	-pick add $@ i_unistd
i_utime:Inhdr
	-pick add $@ i_utime
i_values:Inhdr
	-pick add $@ i_values
i_stdarg i_varargs i_varhdr:cat cc ccflags rm test Setvar Findhdr startsh _o
	-cond cc ccflags 
	-pick add $@ i_varhdr
i_vfork:Inhdr d_vfork
	-pick add $@ i_vfork
i_whoami:Inhdr
	-pick add $@ i_whoami
inc incexp:Loc Oldconfig Getfile usrinc
	-pick add $@ inc
install installdir:Loc Oldconfig Getfile cat test startsh rm cc eunicefix package contains mkdir echo n c
	-cond cc 
	-pick add $@ install
intsize longsize shortsize:Myread cat rm cc optimize ccflags ldflags libs
	-cond cc optimize ccflags ldflags libs 
	-pick add $@ intsize
ipc serve_shm serve_msg serve_inet_udp serve_inet_tcp serve_unix_udp serve_unix_tcp:test Myread Oldconfig d_socket d_msg d_shm d_sem
	-pick add $@ ipc
kernel:Getfile test
	-pick add $@ kernel
lex lexflags:Guess Myread Oldconfig flex test
	-pick add $@ lex
lib libexp:Getfile Loc Oldconfig Prefixit Prefixup prefixexp
	-pick add $@ lib
libc nm_extract:echo n c rm test grep Getfile Myread Oldconfig Loc sed libs incpath libpth runnm nm_opt nm_so_opt contains xlibpth so _a _o
	-pick add $@ libc
libdbm:test Loc libpth _a
	-pick add $@ libdbm
libflex:Loc lex libpth _a
	-pick add $@ libflex
libnlist:Loc libpth Guess usrinc mips _a
	-pick add $@ libnlist
libnm:test Loc libpth _a
	-pick add $@ libnm
libpth glibpth xlibpth plibpth loclibpth:usrinc mips incpath test cat Myread Oldconfig
	-pick add $@ libpth
libs:test cat Myread Oldconfig Loc libpth package xlibpth so _a
	-pick add $@ libs
libyacc:Loc yacc libpth _a
	-pick add $@ libyacc
lintlib lintlibexp:Getfile Loc Oldconfig
	-pick add $@ lintlib
lns:ln rm touch
	-pick add $@ lns
locdist orgdist citydist statedist multistatedist cntrydist contdist:test newslibexp cat Myread Oldconfig
	-pick add $@ locdist
lseektype:Myread Typedef
	-pick add $@ lseektype
maildir maildirexp:Getfile Loc Oldconfig
	-pick add $@ maildir
mailer:test cat rmail mail smail sendmail Getfile Oldconfig
	-pick add $@ mailer
mailfile:Myread Oldconfig Filexp Loc
	-pick add $@ mailfile
make_set_make:Loc rm sed make
	-pick add $@ make
mallocsrc mallocobj usemymalloc malloctype d_mymalloc freetype:Myread Oldconfig package Guess Setvar rm cat cc ccflags Findhdr i_malloc i_stdlib sed libs _o
	-cond cc ccflags 
	-pick add $@ mallocsrc
man1dir man1direxp man1ext installman1dir:afs cat nroff Loc Oldconfig spackage test Getfile Prefixit prefixexp Prefixup sysman Myread
	-pick add $@ man1dir
man3dir man3direxp man3ext installman3dir:afs cat nroff Loc Oldconfig sed man1dir spackage package Getfile prefix Prefixit Prefixup d_flexfnam privlib Myread
	-pick add $@ man3dir
manfmt manfmtexp installmanfmt:Getfile Loc Oldconfig cat manext spackage Prefixit prefixexp Prefixup afs test
	-pick add $@ manfmt
mansrc mansrcexp manext installmansrc:afs cat nroff Loc Oldconfig sysman spackage test Getfile Prefixit prefixexp Prefixup
	-pick add $@ mansrc
mboxchar:cat package shsharp Myread Oldconfig
	-pick add $@ mboxchar
mkdep:spitshell startsh cpp cppflags grep contains rm sed sort uniq Getfile Oldconfig eunicefix cat cc cppminus test _o
	-cond cppflags cc 
	-pick add $@ mkdep
models split small medium large huge:test cat Myread sysman Oldconfig Loc contains
	-pick add $@ models
modetype:Myread Typedef
	-pick add $@ modetype
myhostname phostname mydomain:contains sed test Myread Oldconfig Guess Loc awk echo sort uniq usrinc rm hostcat Tr
	-cond usrinc 
	-pick add $@ myhostname
n c:contains
	-pick add $@ n
nametype d_passnames d_berknames d_usgnames:Myread Guess Oldconfig cat
	-pick add $@ nametype
o_nonblock eagain rd_nodata d_eofnblk:cat rm cc ccflags ldflags d_open3 h_sysfile h_fcntl signal_t hint Oldconfig Setvar startsh
	-cond cc ccflags ldflags 
	-pick add $@ nblock_io
newslevel:cat contains test activeexp newslib Myread Oldconfig
	-pick add $@ newslevel
newslib newslibexp:test inews Oldconfig Getfile
	-pick add $@ newslib
newsspool newsspoolexp:Getfile Oldconfig
	-pick add $@ newsspool
passcat groupcat hostcat:Myread Oldconfig test contains
	-pick add $@ nis
nlist_pfx nlist_fnd:cat test Myread Oldconfig libnlist cc ccflags
	-cond cc ccflags 
	-pick add $@ nlist_pfx
orderlib ranlib:Loc ar cat test rm cc ccflags ldflags libs _a _o
	-cond cc ccflags ldflags libs 
	-pick add $@ orderlib
orgname:sed cat Myread Loc Oldconfig
	-pick add $@ orgname
packadmin:cf_email Oldconfig Myread cat spackage package
	-pick add $@ packadmin
package spackage:Null
	-pick wipe $@ package
pager:pg more less Getfile Oldconfig
	-pick add $@ pager
patchlevel:package baserev test rsrc
	-pick add $@ patchlevel
perlpath:Getfile Oldconfig Loc perl
	-pick add $@ perlpath
pidtype:Myread Typedef
	-pick add $@ pidtype
prefix prefixexp oldprefix:Getfile Loc Oldconfig cat package
	-pick add $@ prefix
prefshell:cat package Getfile Oldconfig ksh csh bash
	-pick add $@ prefshell
privlib privlibexp installprivlib:afs package cat Getfile Oldconfig Prefixit test
	-pick add $@ privlib
prototype:Myread Oldconfig cat cc ccflags rm Setvar
	-cond cc ccflags 
	-pick add $@ prototype
ptrsize:cat rm Myread cc ccflags
	-cond cc ccflags 
	-pick add $@ ptrsize
randbits:cat rm Myread cc i_unistd i_stdlib
	-pick add $@ randbits
randfunc mrand seedfunc nrandbits:cat cc rm test Myread Csym
	-cond cc 
	-pick add $@ randfunc
rcs_branch:Myread contains Loc
	-pick add $@ rcs_branch
registers reg1 reg2 reg3 reg4 reg5 reg6 reg7 reg8 reg9 reg10 reg11 reg12 reg13 reg14 reg15 reg16:awk rm Cppsym Myread Oldconfig
	-pick add $@ registers
rootid:sed
	-pick add $@ rootid
sbrksmart:cat d_sbrk cc ccflags libs rm
	-cond cc ccflags libs 
	-pick add $@ sbrksmart
sbrktype:Myread Oldconfig Loc contains Findhdr
	-pick add $@ sbrktype
scriptdir scriptdirexp installscript:afs cat test Getfile Loc Oldconfig  Prefixit prefixexp Prefixup
	-cond bin 
	-pick add $@ scriptdir
selecttype:cat cc ccflags rm Oldconfig Myread d_fd_set d_select d_socket i_systime i_sysselct
	-cond cc ccflags 
	-pick add $@ selecttype
sh:Head
	-pick wipe $@ sh
shm_for shm_att shm_lim:Cppsym Myread ipc uname
	-pick add $@ shm_for
sig_name sig_num:awk Signal Oldconfig rm
	-pick add $@ sig_name
sitearch sitearchexp installsitearch:afs cat Getfile Oldconfig Prefixit prefix test archname sitelib
	-pick add $@ sitearch
sitelib sitelibexp installsitelib:afs cat Getfile Oldconfig Prefixit test privlib package sed
	-pick add $@ sitelib
sizetype:Myread Typedef
	-pick add $@ sizetype
so:test libpth Loc Myread Oldconfig cat
	-pick add $@ so
d_keepalive:cat rm contains cc ccflags socketlib sockethdr d_oldsock libs Oldconfig Setvar Findhdr
	-cond cc ccflags 
	-pick add $@ sockopt
spitshell shsharp sharpbang:eunicefix sh
	-pick add $@ spitshell
src rsrc:Options Myread package contains
	-pick add $@ src
ssizetype:Myread Typedef sizetype cat rm cc optimize ccflags ldflags libs _o
	-cond cc optimize ccflags ldflags libs 
	-pick add $@ ssizetype
startperl:cat rm sharpbang perlpath d_portable Myread
	-pick add $@ startperl
startsh:sh sharpbang eunicefix
	-pick add $@ startsh
stdchar:contains Findhdr
	-pick add $@ stdchar
sunscanf:cat rm Myread cc ccflags test Setvar
	-cond cc ccflags 
	-pick add $@ sunscanf
sysman:test Loc Oldconfig
	-pick add $@ sysman
uidtype:Myread Typedef Findhdr
	-pick add $@ uidtype
usenm runnm nm_opt nm_so_opt:cat test Myread Oldconfig myuname grep d_gnulibc
	-pick add $@ usenm
usrinc mips incpath mips_type:test cat echo n c cc Getfile Guess Oldconfig eunicefix contains rm
	-cond cc 
	-pick add $@ usrinc
vaproto:prototype i_stdarg Setvar
	-pick add $@ vaproto
voidflags defvoidused:cat rm contains cc ccflags package Oldconfig Myread
	-cond cc ccflags 
	-pick add $@ voidflags
warnflags:cat cc contains Myread Guess Oldconfig Findhdr
	-pick add $@ warnflags
yacc yaccflags:Guess Myread Oldconfig byacc bison cat test
	-pick add $@ yacc
End:MyOptions $W
	-pick add $@ End
MyOptions p_installdir p_sysprogs p_keepdir p_dictionaries p_utildir p_docdir p_replace p_passwdfile p_shadowfile p_dbmpw p_history p_nis p_secure_rpc p_nisplus p_nispasswd p_hesiod p_kerberos p_svcconf p_nsswitch p_shadow p_u4auth p_osf1auth p_aixauth p_hpuxauth p_paranoid p_utsname top_level:cc_dbflags libexp more Getfile privlibexp myhostname Myread cat test Setvar package Inlibc Loc Findhdr orderlib p_osName p_osRev groupcat
	-pick add $@ MyOptions
Myinit p_osName p_osRev p_osMajor p_osMinor p_osMicro libswanted privlib lib:tr test Guess Loc Oldconfig osname osvers package Myread
	-pick add $@ Myinit
Tr trup trdown:startsh tr eunicefix
	-pick add $@ Tr
ccflags ldflags lkflags cppflags optimize cc_osflags cc_dbflags:p_osName p_osMajor p_osMinor p_osRev cc test cat Myread Guess Oldconfig  mips_type usrinc package contains rm cppstdin cppminus cpprun cpplast
	-cond gccversion usrinc 
	-pick add $@ ccflags
p_clnt_sperrno:Inlibc
	-pick add $@ p_clntsperrno
p_crypt:test Setvar Inlibc
	-pick add $@ p_crypt
p_fgetpwent:Inlibc
	-pick add $@ p_fgetpwent
p_fgetspent:Inlibc
	-pick add $@ p_fgetspent
p_getusershell:Inlibc
	-pick add $@ p_getusershell
p_lckpwdf:Inlibc
	-pick add $@ p_lckpwdf
p_putpwent:Inlibc
	-pick add $@ p_putpwent
p_xdr_passwd p_xdr_uid_t p_xencrypt p_rpclib:Loc test libpth Csym cc rm libs p_secure_rpc
	-pick add $@ p_rpcsvc
p_sigposix:Inlibc Setvar
	-pick add $@ p_sigposix
p_sysinfo:Inlibc
	-pick add $@ p_sysinfo
p_ttyposix:Inlibc Setvar
	-pick add $@ p_ttyposix
uidsigned:passcat awk
	-pick add $@ uidsigned
