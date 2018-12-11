/*
 *  substitute for /usr/etc/rpc.yppasswdd daemon
 *
 *      Written by Urs Zolliker, ETH, CH-8092 Zurich, Switzerland, May 1990
 *	Version 1.1, May 11, 1990
 *
 *      This program behaves as described in yppasswdd(8C).
 *      It supports both insecure systems and systems with adjunct
 *      password files.
 *      As extension you can supply a secure networks configuration file
 *      in order to control access by port checking (option: -s configfile).
 *      Any unauthorised queries are reported by syslog.
 *
 *      Called with no arguments, a short description is displayed and
 *      execution terminated.
 *
 *      This source program does NOT include any copyrighted parts
 *      from a source distribution. It's developed entirely from scratch.
 *      Any similarities originate from the Network Programming manual,
 *      the man pages yppasswdd(8C), intro(3R), rpc(3N), etc. and 
 *      some observations about the behavior of /usr/bin/yppasswd.
 *
 * NOTE, added May 14, '91:
 *
 *      How to install:
 *          cc -c rpc.yppasswdd.c
 *          cc -o /usr/etc/rpc.yppasswdd -s rpc.yppasswdd.o -lrpcsvc
 *
 *      Description:
 *          This program logs unauthorized attempts with authorization
 *          facility and info level.
 *
 *      Bugs: 
 *        - This program does not support chfn nor chsh.
 *        - If a user tries to change his passwort twice in a short
 *          period (e.g. 1 minute) yppasswdd will explicitely deny the
 *          second request, since it has not yet completed the first one.
 *          The end user will get the error message "Couldn't change
 *          password" or something like that.
 *
 *      Test report:
 *          This program has been installed for one year up to now
 *          on a system with 300 users and 50 machines.
 *          During this time there have been approx. 500 password changes
 *          by users. Only once it occured that a user wasn't able to login
 *          after changing his password.
 */

#include <sys/types.h>
#include <sys/label.h>
#include <sys/audit.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <stdio.h>
#include <pwd.h>
#include <pwdadj.h>
#include <fcntl.h>
#include <ctype.h>
#include <syslog.h>
#include <rpc/rpc.h>
#include <rpcsvc/yppasswd.h>

/*************** don't change anything above this line ******************/

    /* max length of yellow pages password file name */
#define LOCKLEN 100

    /* max length of adjunct password database entry */
#define ENTLEN 100

    /* max number of subnets */
#define MAXNETS 10

    /* max duration time for transaction in seconds */
#define LOCKDUR 20

    /* ignore adjunct password files? */
/* #define IGNORE_ADJ */

    /* default log file, used only if it exists already */
static char *defaultlog = "/var/yp/yppwdd.log";

/*************** don't change anything below this line ******************/

static char *docu[] = {

"Usage:  %s file [adjfile]  ...options...  [-m arg1 arg2 ...]\n\n",
"            file     :  password database                         \n",
"            adjfile  :  adjunct password database                 \n",
"                           (default: /etc/security/passwd.adjunct)\n",
"options:                                                          \n",
"         -i          :  ignore adjunct passwd file                \n",
"         -l logfile  :  name of logfile for debugging             \n",
"         -s netfile  :  pairs of netmasks and authorised subnets  \n",
"         -m arg?     :  arguments for make in directory /var/yp   \n\n",

NULL };

#define PWLEN      8
#define FPRINTF    (void)fprintf
#define PRINTF     (void)printf
#define FCLOSE     (void)fclose
#define FFLUSH     (void)fflush

extern struct passwd *fgetpwent();
extern struct passwd_adjunct *fgetpwaent();
extern char *crypt(), *sprintf(), *fgets(), *index(), *sys_errlist[], *optarg;
extern long ftell();
extern int errno, optind;
    
static char 
  lock[LOCKLEN], *prog, **command = NULL, 
  *pwdb = "/etc/security/passwd.adjunct", *pwfile,
  *lock_timeout = "Couldn't chage password since lock timed out!\n";
		
static struct yppasswd indata;
static int pid, end_of_nets, useadj, changed = 0, unchanged = 1;
static long masks[MAXNETS], subnets[MAXNETS], mylock;
static FILE *diag = stderr, *child_in_fp, *child_out_fp;

diagnostics(b) char *b;
{ FPRINTF(diag,"%s: %s\n",b,sys_errlist[errno]); FFLUSH(diag); return; }

#ifdef  IGNORE_ADJ
#define LEGITIM_PWA legitim_pw
#define MODIFY_PWA  modify_pw
#else
#define LEGITIM_PWA legitim_pwa
#define MODIFY_PWA  modify_pwa

static char entbuf[ENTLEN];
static struct ent { char *ent_name, *ent_passwd, 
		         *ent3, *ent4, *ent5, *ent6, *ent7; } pe;

struct ent *fgetent(f)
FILE *f;
{ char *p; 

  if (fgets(entbuf,ENTLEN,f) != entbuf) return(NULL);
  if (strlen(entbuf) >= ENTLEN - 1)
    { FPRINTF(diag,"adjunct entry buffer too small!\n"); 
      FFLUSH(diag); 
      return(NULL); }
  if (!(p = index(pe.ent_name = entbuf,':'))) return(NULL);
  *p++ = '\0';
  if (!(p = index(pe.ent_passwd = p,   ':'))) return(NULL);
  *p++ = '\0';
  if (!(p = index(pe.ent3 = p,     ':'))) return(NULL);
  *p++ = '\0';
  if (!(p = index(pe.ent4 = p,     ':'))) return(NULL);
  *p++ = '\0';
  if (!(p = index(pe.ent5 = p,     ':'))) return(NULL);
  *p++ = '\0';
  if (!(p = index(pe.ent6 = p,     ':'))) return(NULL);
  *p++ = '\0';
  *index(pe.ent7 = p++,'\n') = '\0';;
  return(index(p,':') ? NULL : &pe); }

fputent(e,f)
struct ent *e;
FILE *f;
{ return(fprintf(f,"%s:%s:%s:%s:%s:%s:%s\n",e->ent_name,e->ent_passwd,
		 e->ent3,e->ent4,e->ent5,e->ent6,e->ent7)); }

char *
legitim_pwa(h)
FILE *h;
{ struct passwd_adjunct *pa;
  long pos;

  while (1) 
    { while (pa = fgetpwaent(h)) 
	if (!strncmp(pa->pwa_name,indata.newpw.pw_name,9)) break;
      if (pa) return(pa->pwa_passwd);
      pos = ftell(h);
      if (fseek(h,0L,2) == EOF) { diagnostics(pwdb); break; }
      if (ftell(h) == pos) break;
      if (fseek(h,pos,0) == EOF) { diagnostics(pwdb); break; } }
  return(NULL); }
 
#endif

char *
legitim_pw(h)
FILE *h;
{ struct passwd *pa;
  long pos;

  while (1) 
    { while (pa = fgetpwent(h)) 
	if (!strncmp(pa->pw_name,indata.newpw.pw_name,9)) break;
      if (pa) return(pa->pw_passwd);
      pos = ftell(h);
      if (fseek(h,0L,2) == EOF) { diagnostics(pwfile); break; }
      if (ftell(h) == pos) break;
      if (fseek(h,pos,0) == EOF) { diagnostics(pwfile); break; } }
  return(NULL); }
	
legitim() 
  { char *p, *pas;
    FILE *h;

       /* check if new password code is wellformed */

    for (p=indata.newpw.pw_name; *p; p++)
      if (!isalnum(*p) && *p != '.' && *p != '/') 
	{ openlog(prog,LOG_NOWAIT,LOG_AUTH);
	  syslog(LOG_INFO,"bad change attempted: %s\n",indata.newpw.pw_name);
	  closelog();
	  return(2); }

       /* check user name and password */

    if (h = fopen(pwdb,"r"))
      { pas = (useadj) ? LEGITIM_PWA(h) : legitim_pw(h);
	FCLOSE(h); 
	if (!pas)
	  { FPRINTF(diag,"%s: no user %s in password database!\n",prog,
		    indata.newpw.pw_name);
	    FFLUSH(diag);
	    return(2); }
	if (strncmp(pas,crypt(indata.oldpass,pas),14))
	  { FPRINTF(diag,"bad password\n"); FFLUSH(diag); }
        else return(0); }
    else { FPRINTF(diag,"file %s not found\n",pwdb); FFLUSH(diag); }
    return(1); }
    
setlock()
{ long hislock;
  struct rusage ru;
  struct timeval tp;
  struct stat sta;
  union wait st;
  int d;

  if (pid) { if (!wait4(pid,&st,WNOHANG,&ru)) return(EOF); pid = 0; }
  (void)gettimeofday(&tp,(struct timezone *)NULL);
  mylock = tp.tv_sec + LOCKDUR;
  if ((d = open(lock,O_WRONLY|O_EXCL|O_CREAT,useadj ? 0600 : 0644)) != EOF)
    return(d);
  hislock = tp.tv_sec - 2 * LOCKDUR;

     /* It's safe to unlink a file of age 2 * LOCKDUR,
	since this main server only creates the lock,
	but not any forked children. */

  if (stat(lock,&sta) == EOF) { diagnostics(lock); return(EOF); }
  if (sta.st_mtime > hislock) return(EOF);
  if (unlink(lock)) diagnostics(lock);
  return(open(lock,O_WRONLY|O_EXCL|O_CREAT,0600)); }
		
movedb()
{ long pos;
  struct timeval tp;

  pos = ftell(child_in_fp);
  if (fseek(child_in_fp,0L,2) == EOF) 
    { syslog(LOG_DEBUG,"%s: %m",pwdb); return(EOF); }
  if (ftell(child_in_fp) == pos) 
    { FCLOSE(child_in_fp);
      if (fclose(child_out_fp) == EOF)
	{ syslog(LOG_DEBUG,"%s: %m",lock); return(1); }

      (void)gettimeofday(&tp,(struct timezone *)NULL);
		      
		       /* Don't touch a file older than LOCKDUR!
			  My file might have been unlinked.
			  There might be a new version with this path. */

      if (tp.tv_sec > mylock) 
	{ syslog(LOG_INFO,lock_timeout); return(1); }
      if (rename(lock,pwdb) == EOF) 
	{ syslog(LOG_INFO,"Can't move password file to target; update failed");
	  return(1); }
      if (!command) return(0);
      *(--command) = "make";
      if (chdir("/var/yp") != EOF) 
	execv("/usr/bin/make",command);
      syslog(LOG_DEBUG,"/var/yp: %m");
      return(1); }
  syslog(LOG_INFO,"bad entry in password database skipped!\n");
  if (fseek(child_in_fp,pos,0) == EOF) 
    { syslog(LOG_DEBUG,"%s: %m",pwdb); return(EOF); }
  return(EOF); }
	
modify_pw()
{ struct passwd *pent;
  int rc;

  while (1)
    { if (pent = fgetpwent(child_in_fp))
	{ if (!strncmp(pent->pw_name,indata.newpw.pw_name,PWLEN + 1)) 
	    pent->pw_passwd = indata.newpw.pw_passwd;
	  if (putpwent(pent,child_out_fp) == EOF) 
	    { syslog(LOG_DEBUG,"%s: %m",lock); break; } }
      else if ((rc = movedb()) >= EOF) return(rc); }
  return(EOF); }
	
#ifndef IGNORE_ADJ

modify_pwa()
{ struct ent *pent;
  int rc;

  while (1)
    { if (pent = fgetent(child_in_fp))
	{ if (!strncmp(pent->ent_name,indata.newpw.pw_name,PWLEN + 1)) 
	    pent->ent_passwd = indata.newpw.pw_passwd;
	  if (fputent(pent,child_out_fp) == EOF) 
	    { syslog(LOG_DEBUG,"%s: %m",lock); break; } }
      else if ((rc = movedb()) >= EOF) return(rc); }
  return(EOF); }

#endif

void modify(d) 
int d;
{ struct timeval tp;
  int rc = EOF;

  if (pid = fork()) { (void)close(d); return; }

  if (!freopen("/dev/null","a",stderr)) 
    { FPRINTF(diag,"can't reopen stderr\n"); FFLUSH(diag); }
  if (!freopen("/dev/null","a",stdout)) 
    { FPRINTF(diag,"can't reopen stdout\n"); FFLUSH(diag); }
  openlog(prog,LOG_NOWAIT,LOG_AUTH);
  if (child_in_fp = fopen(pwdb,"r"))
    { if (child_out_fp = fdopen(d,"w")) 
	{ if ((rc = (useadj) ? MODIFY_PWA() : modify_pw()) != EOF)
	    { closelog(); exit(rc); }
	  FCLOSE(child_out_fp); } 
      else 
	{ syslog(LOG_DEBUG,"%s: %m",pwdb);
	  if (close(d) == EOF) syslog(LOG_DEBUG,"%s: %m",lock); }
      FCLOSE(child_in_fp); }
  else
    { syslog(LOG_DEBUG,"file %s not found\n",pwdb); FFLUSH(diag); exit(1); }

  (void)gettimeofday(&tp,(struct timezone *)NULL);

		       /* Don't touch a file older than LOCKDUR!
			  My file might have been unlinked.
			  There might be a new version with this path. */

  if (tp.tv_sec < mylock) if (unlink(lock) == EOF) 
    syslog(LOG_DEBUG,"%s: %m",lock); 
  syslog(LOG_DEBUG,"password update failed!\n");
  closelog();
  exit(1); }

void modpw(rqstp, transp)
     struct svc_req *rqstp;
     SVCXPRT *transp;
     
{ int i;
  struct rusage ru;
  union wait st;

     /* RPC convention; always answer to null procedure */

  if (rqstp->rq_proc == NULLPROC)
    { if (!svc_sendreply(transp,xdr_void,(char *)0))
	  { FPRINTF(diag,"can't reply to RPC call\n"); FFLUSH(diag); }
	return; }

     /* check subnet of port */

  for (i = 0; i < end_of_nets; i++)
    if ((transp->xp_raddr.sin_addr.s_addr & masks[i]) == subnets[i]) break; 
  if (i == end_of_nets)
    { (void)svcerr_weakauth(transp);
      openlog(prog,LOG_NOWAIT,LOG_AUTH);
      syslog(LOG_INFO,"change attempted from bad host: %x\n",
	     transp->xp_raddr.sin_addr.s_addr);
      closelog();
      return; }
      
  switch (rqstp->rq_proc)
    { case YPPASSWDPROC_UPDATE:
	indata.oldpass = NULL;
	indata.newpw.pw_name = NULL;
	indata.newpw.pw_passwd = NULL;
	indata.newpw.pw_comment = NULL;
	indata.newpw.pw_gecos = NULL;
	indata.newpw.pw_dir = NULL;
	indata.newpw.pw_shell = NULL;
	if (!svc_getargs(transp,xdr_yppasswd,&indata))
	  { FPRINTF(diag,"can't decode arguments\n"); FFLUSH(diag); }
	switch (legitim()) 
	  { case 0: 
	      if ((i = setlock()) == EOF)
		{ svcerr_systemerr(transp); 
		  FPRINTF(diag,"passwd database busy.\n"); 
		  FFLUSH(diag);
		  if (pid) 
		    if (kill(pid,0)) 
		      { (void)wait4(pid,&st,0,&ru); pid = 0; } }
	      else
		{ (void)svc_sendreply(transp,xdr_int,(char *)&changed);
		  modify(i); }
	      break;
	    case 1: 
	      (void)svc_sendreply(transp,xdr_int,(char *)&unchanged);
	      break;
	    default: 
	      (void)svcerr_weakauth(transp); }
	if (!svc_freeargs(transp,xdr_yppasswd,&indata))
	  { FPRINTF(diag,"can't free arguments\n");
	    FFLUSH(diag); }
	break;
      default: 
        svcerr_noproc(transp); }
  return; }

init_nets(secnets)
char *secnets;
{ FILE *f;
  char line[80];
  int m0, m1, m2, m3, s0, s1, s2, s3;

  if (!secnets)
    { masks[0] = 0; subnets[0] = 0; end_of_nets = 1; return(0); }
  if (!(f = fopen(secnets,"r"))) 
    { FPRINTF(diag,"file %s not found\n",secnets);  FFLUSH(diag); return(1); }
  end_of_nets = 0;
  while (fgets(line,80,f))
    { if (sscanf(line,"%d.%d.%d.%d%d.%d.%d.%d",
		 &m0,&m1,&m2,&m3,&s0,&s1,&s2,&s3) != 8)
	{ FPRINTF(diag,"Syntax error in %s line:\n\t%s\n",secnets,line);
	  FFLUSH(diag);
	  return(1); }
      masks[end_of_nets]     = (((m0 * 256) + m1) * 256 + m2) * 256 + m3;
      subnets[end_of_nets++] = (((s0 * 256) + s1) * 256 + s2) * 256 + s3;
      if (end_of_nets == MAXNETS) 
        { FPRINTF(diag,"subnet table overvlow; recompile!\n"); 
	  FFLUSH(diag);
	  return(1); } } 
  FCLOSE(f);
  return(0); }

init(ac,av)
int ac;
char *av[];

{ char      **p, **optv = av + 1, *subnetf = NULL, *log = defaultlog;
  int       c, optc, forcelog = 0;

     /* usage */

  if (ac < 2)
    { FPRINTF(diag,*docu,av[0]); 
      for (p = docu + 1; *p; p++) FPRINTF(diag,*p);
      return(1); }

     /* parse options and arguments */

  prog   = av[0];
  pwfile = av[1];
  optc   = ac - 1;

  if (ac > 2)
    { if (*(av[2]) != '-') 
	{ optv++;
	  optc--;
	  pwdb = av[2];
#ifdef IGNORE_ADJ
	  FPRINTF(diag,"Sorry: %s has been compiled with IGNORE_ADJ option\n",
		  prog);
	  return(1);
#endif
	} }

#ifdef IGNORE_ADJ
  useadj = 0;
#else
  useadj = issecure();
#endif

  while ((c = getopt(optc,optv,"il:s:m")) != EOF)
    switch (c)
      { case 'i': useadj  = 0;	                  break;
	case 's': subnetf = optarg;               break;
	case 'l': log     = optarg; forcelog = 1; break;
	case 'm': command = optv + optind; }

     /* initialize configuration */

  if (!useadj) pwdb = pwfile;

  if (strlen(pwdb) + 6 > LOCKLEN)
    { FPRINTF(diag,"%s: filename too long; increase buffer length!\n",av[0]);
      FFLUSH(diag);
      return(1); }
  (void)sprintf(lock,"%s.lock",pwdb);

  if (init_nets(subnetf)) return(1);

  if (access(log,W_OK) && !forcelog) log = "/dev/null";

     /* set process into background and disconnect streams */

  FCLOSE(stdin);
  FFLUSH(stdout);
  if (!freopen(log,"a",stdout)) 
    { perror(log); FPRINTF(diag,"Can't reopen stdout\n"); FFLUSH(diag); }
  if (fclose(diag) == EOF) diagnostics("diag");
  diag = stdout;
  FCLOSE(stderr);
    
  if (fork()) { FCLOSE(stdout); FCLOSE(diag); exit(0); }
  return(0); }

main(argc,argv)
int argc;
char *argv[];

{ SVCXPRT *transp;
  
  if (init(argc,argv)) exit(1);

  transp = svcudp_create(RPC_ANYSOCK);
  if (transp == NULL) 
    { FPRINTF(diag,"can't create an RPC server\n"); FFLUSH(diag);
      exit(1); }
  (void)pmap_unset((u_long)YPPASSWDPROG,(u_long)YPPASSWDVERS);
  if (!svc_register(transp,(u_long)YPPASSWDPROG,(u_long)YPPASSWDVERS,
		    modpw,IPPROTO_UDP))
    { FPRINTF(diag,"can't register YPPASSWD service\n"); FFLUSH(diag);
      exit(1); }

  svc_run(); }
