
/* --------------------------------------------------------------------  */
/*                                                                       */
/*                         Author: Clyde Hoover                          */
/*                          Computation Center                           */
/*                   The University of Texas at Austin                   */
/*                          Austin, Texas 78712                          */
/*                         clyde@emx.utexas.edu                          */
/*                   uunet!cs.utexas.edu!ut-emx!clyde                    */
/*                                                                       */
/*This code may be distributed freely, provided this notice is retained. */
/*                                                                       */
/* --------------------------------------------------------------------  */
/*
 *      npasswd defines
 *      @(#)npasswd.h   1.6 npasswd.h
 */

#define USERNAMESIZE 8
#define SALTSIZE 4
#define BUFMAX 128

#ifdef AUTH_SECURITY
# define PASSWORDSIZE MAX_PASSWORD_LENGTH
# define PBUFSIZE (CRYPT_PASSWORD_LENGTH+1)
#else
# define PASSWORDSIZE 8
# define PBUFSIZE 16
#endif


typedef struct passwd   passwd;
typedef struct passwd   *passwdp;

#ifdef AUTH_SECURITY
typedef AUTHORIZATION   *authp;
#endif

#define VERSION "npasswd 1.2 (03/19/90)"
#define PATCHLEVEL "2 (01/24/91)"

#define __ANSI__
#ifdef __STDC__

/* npasswd.c prototypes */
int main(int argc, char *argv[]);
void getpassword(char *pwd_crypt, char *pwd_plain, int pwlen);
void randomstring(char buf[], int len);
/* void quit(int logit, char *message, int *a1, int *a2, int *a3, int *a4, int *a5, int *a6, int *a7, int *a8, int *a9, int *a10); */
void motd(char *fn, char *complaint);
void checktty(void);
void catchit(void);
void savetty(void);
void fixtty(void);
char *getpass(char *prompt);
void putpwent(struct passwd *p, FILE *f);
struct passwd *fgetpwent(FILE *f);
#ifdef SYSV
int rename(char *src, char *dst);
#endif
void punt(char *prog);
void ChangePasswd(void);
void ChangeShell(void);
void ChangeFinger(void);
void getinput(char *Buf, int Size, char *Default);
int checkinput(char *InString);

/* pw_passwd.c prototypes */
int pw_initialize(void);
passwdp pw_getuserbyname(char *name, char *passwdb);
AUTHORIZATION *pw_getauth(int uid, char *passwdb);
int pw_permission(void);
int pw_compare(char *current, char *check);
int pw_check(char *newpw);
#ifdef AUTH_SECURITY
void pw_replace(char *newpwd, char *curpwd, passwdp pwinfo, AUTHORIZATION *authinfo, int WriteAuth);
#else
void pw_replace(char *newpwd, char *curpwd, passwdp pwinfo);
#endif
void pw_cleanup(int code);
char *_newstr(char *s);
static void _cppasswd(passwdp f, passwdp t);
void updatedbm(void);

/* these should be in an include file somewhere... */
char *crypt(char *key, char *salt);
char *crypt16(char *key, char *salt);

#else /* yukky k&r C */
char    *getpass(),
	*malloc(),
	*ttyname(),
	*getlogin();
char    *index();
int     catchit();              /* Signal catcher */
#endif

#ifdef  SYSV
#define index   strchr
#endif

/* End npasswd.h */
