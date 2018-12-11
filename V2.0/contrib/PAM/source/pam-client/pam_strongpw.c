 /*
  * Copyright 1998-2001, Texas Instruments. All rights reserved.
  *
  * By using this software the USER indicates that he or she has read,
  * understood and will comply with the following:
  *
  * 1. the above copyright notice appears in all copies of the software
  *    and its documentation, or portions thereof, and
  * 2. a full copy of this notice is included with the software and its
  *    documentation, or portions thereof, and
  * 3. neither the software nor its documentation, nor portions thereof,
  *    is sold for profit. Any commercial sale or license of this software,
  *    copies of the software, its associated documentation and/or
  *    modifications of either is strictly prohibited without the prior
  *    consent of Texas Instruments.
  * 4. This software and any associated documentation are provided "as is,"
  *    and any issues, problems are yours to deal with. The USER takes
  *    full responsibility for the performance of this software.
  *
  *
  *   Check Passwords for strength by network communication
  *   to a strength checking daemon.
  *
  *
  *   Written by: Victor Burns
  *         Version: 0.5 First Release  Date:    Jan-2001
  *         Version: 0.2                Date: 06-Oct-2000
  *         Version: 0.1 test concept   Date: 07-Apr-1999
  *
  *   Solaris Setup: /etc/pam.conf
  *
  *     other password requisite /usr/lib/security/pam_strongpw.so.1
  *     other password required  /usr/lib/security/pam_unix.so.1     use_first_pass
  *     other password requisite /usr/lib/security/pam_strongpw.so.1 use_first_pass update_db
  *
  *   HP-UX   Setup: /etc/pam.conf
  *
  *     passwd   password required      /usr/lib/security/pam_strongpw.sl.1
  *     passwd   password required      /usr/lib/security/libpam_unix.1     use_first_pass
  *     passwd   password required      /usr/lib/security/pam_strongpw.sl.1 use_first_pass update_db
  *
  *   Suported Module Options:
  *
  *     debug		Print special debug messages. 
  *     verbose		Print generic messages.
  *     use_first_pass	Do not ask for passwd. Use existing passwd
  *     try_first_pass	Try first password.  Ask for password if needed
  *
  *   Syslog Setup  /etc/syslog.conf
  *
  *     user.info                   /var/log/sysinfo
  *     auth.info                   /var/log/sysinfo
  *
  */

#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <errno.h>
#include <shadow.h>
#include <syslog.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <security/pam_appl.h>
#include <security/pam_modules.h>

#include <udpchk.h>
#include <udp-client.h>
#include <itsspwd.h>

#ifndef getspnam_r
#define getspnam_r(a,b,c,d)	getspnam(a)
#endif

int	errno;

#define  MAXPAMBUFSZ	1024

void print2log(const char *, pam_handle_t *, int, int, const char **);

int pam_sm_chauthtok( pamh, flags, argc, argv )
    pam_handle_t	*pamh;
    int			flags;
    int			argc;
    const char		**argv;

{

   /*
    *   Variable Declarations
    */

    void	*item[1];	/* Pointer to data returned from pam_get_item      */
    char	Usr[9];		/* User Login name                                 */
    char	Epw[14];	/* Users Encryped Password (OLD)                   */
    char	AUTH_PW1[9];	/* New Password                                    */
    char	AUTH_PW2[9];	/* New Password (reentry)                          */
    char	*CryptPW;	/* Encrypted passwd (NEW)                          */
    int		st, j, k, l;	/* Status and other misc. ints                     */
    char	em[MAXMSGSIZE+1]; /* Service message buffer                        */

    int		debug;		/* flag (debug)  1+=DEBUG-ON   0=DEBUG-OFF         */
    int		root;		/* flag (root)   1 =USER-ROOT  0=NON-USER-ROOT     */
    int		sysadmin;	/* flag (admin)  1 =sysadmin   0=not-sysadmin      */
    int		use_first_pass;	/* flag (use_first_pass)  Use Existing Passwords   */
    int		try_first_pass;	/* flag (try_first_pass)  Try Existing Passwords   */
    int		update_db;	/* flag (update_db)       Update Password History  */

    struct pam_conv	*pass_conv;   /* Pam Message and response data             */
    struct pam_message	 pas_msg[5];
    struct pam_message	*pas_msgp;
    struct pam_response	*pas_res;

    struct spwd		 _pas_result;		/* Password-spwd entry information */
    struct spwd		*pwEntp = &_pas_result;	/* for account to be changed       */
    char		 shBuf[MAXPAMBUFSZ];

    struct passwd	 _pwu_result;		/* Password-pwd  entry information */
    struct passwd	*puEntp = &_pwu_result;	/* for account to be changed       */
    char		 puBuf[MAXPAMBUFSZ];

    struct passwd	 _pwd_result;		/* Password-pwd  entry information */
    struct passwd	*paEntp = &_pwd_result;	/* for Caller                      */
    char		 paBuf[MAXPAMBUFSZ];

    struct group	 _grp_result;		/* sysadmin group info             */
    struct group	*gpEntp = &_grp_result;
    char		 gpBuf[MAXPAMBUFSZ];


   /*
    *   Initial Variable Settings/Values
    */

    pas_msgp = pas_msg;

    debug          = 0;		/* Debug   Off    default */
    root           = 0;		/* Non root user  default */
    sysadmin       = 0;		/* Non sysadmin   default */
    update_db      = 0;		/* No Update      default */
    use_first_pass = 0;		/* No             default */
    try_first_pass = 0;		/* No             default */

   /*
    *   Detect module options
    */

    for(j=0;j<argc;j++)
    {
	if(strcmp("debug",          argv[j])==0) debug++;
	if(strcmp("update_db",      argv[j])==0) update_db=1;
	if(strcmp("use_first_pass", argv[j])==0) use_first_pass=1;
	if(strcmp("try_first_pass", argv[j])==0) try_first_pass=1;
    }

   /*
    *   SYSLOG Entry
    */

    if(debug)
    syslog(LOG_INFO,"Begin ->> pam_sm_chauthtok(%d)",flags);

   /*
    *   Debug messages
    */

    if(debug>=3) {
	
	syslog(LOG_INFO," (Begin)--------------------");

	syslog(LOG_INFO, " HANDLE          ->> %p", pamh );
	syslog(LOG_INFO, " FLAGS           ->> %04x", flags );

	if(PAM_SILENT & flags)
	syslog(LOG_INFO,"                     PAM_SILENT(%d)",PAM_SILENT);

	if(PAM_CHANGE_EXPIRED_AUTHTOK & flags)
	syslog(LOG_INFO,"                     PAM_CHANGE_EXPIRED_AUTHTOK(%d)",PAM_CHANGE_EXPIRED_AUTHTOK);

	if(PAM_PRELIM_CHECK & flags)
	syslog(LOG_INFO,"                     PAM_PRELIM_CHECK(%d)",PAM_PRELIM_CHECK);

	if(PAM_UPDATE_AUTHTOK & flags)
	syslog(LOG_INFO,"                     PAM_UPDATE_AUTHTOK(%d)",PAM_UPDATE_AUTHTOK);

	syslog(LOG_INFO," ARGC            ->> %d", argc  );
	for(j=0;j<argc;j++)
	{
		syslog(LOG_INFO,"   [ %s ]",argv[j]);
	}

	st = pam_get_item(pamh,PAM_SERVICE,item);
	syslog(LOG_INFO," PAM_SERVICE     ->> %s", *item);

	st = pam_get_item(pamh,PAM_USER,item);
	syslog(LOG_INFO," PAM_USER        ->> %s", *item);

	st = pam_get_item(pamh,PAM_AUTHTOK,item);
	if(*item) {
	    syslog(LOG_INFO," PAM_AUTHTOK     ->> %s", *item); } else {
	    syslog(LOG_INFO," PAM_AUTHTOK     ->> %d", st);    }

	st = pam_get_item(pamh,PAM_OLDAUTHTOK,item);
	if(*item) {
	    syslog(LOG_INFO," PAM_OLDAUTHTOK  ->> %s", *item); } else {
	    syslog(LOG_INFO," PAM_OLDAUTHTOK  ->> %d", st);    }

	st = pam_get_item(pamh,PAM_RHOST,item);
	if(*item) {
	    syslog(LOG_INFO," PAM_RHOST       ->> %s", *item); } else {
	    syslog(LOG_INFO," PAM_RHOST       ->> %d", st);    }

	st = pam_get_item(pamh,PAM_RUSER,item);
	if(*item) {
	    syslog(LOG_INFO," PAM_RUSER       ->> %s", *item); } else {
	    syslog(LOG_INFO," PAM_RUSER       ->> %d", st);    }

	st = pam_get_item(pamh,PAM_USER_PROMPT,item);
	if(*item) {
	    syslog(LOG_INFO," PAM_USER_PROMPT ->> %s", *item); } else {
	    syslog(LOG_INFO," PAM_USER_PROMPT ->> %d", st);    }

	syslog(LOG_INFO," (End)-------------------------");

    }; /* Debug */

   /*
    *   Who's password are we wanting to change?
    *   Is it Root's password?
    */

    st = pam_get_item(pamh,PAM_USER,item);
    if(strcmp("root",*item)==0) root = 1;

   /*
    *   Only "root" can Change "root" password
    *   Let pam_unix.so Handle "root" requests by non root users!
    *   in local password file.
    *
    *   This works by pretending that we are OK with it.
    *   The standard UNIX pam module will handle the error condition.
    *
    *   Return as OK, if we are not root trying to change root's password.
    */

    if(getuid() && root) return PAM_SUCCESS;

   /*
    *   Collect "PAM_USER" and passwd record
    *   Short user name interpreted as unknown?
    */

    if(*item != NULL) { strncpy(Usr,*item,8); Usr[8] = '\0'; } else { *Usr = '\0'; }
    if(strlen(Usr) < 1)		return PAM_USER_UNKNOWN;

    Epw[0] = '\0'; shBuf[0] = '\0';
    pwEntp = (struct spwd *)getspnam_r(Usr,pwEntp,shBuf,sizeof(shBuf));

    if(pwEntp != NULL)
    {
	if(strlen(pwEntp->sp_pwdp)==13) strcpy(Epw,pwEntp->sp_pwdp);
	syslog(LOG_INFO,"Using getspnam_r");
    }
    else
    {
#ifdef HPUX
	st     =                  getpwnam_r(Usr,puEntp,puBuf,sizeof(puBuf),&puEntp);
#else
	puEntp = (struct passwd *)getpwnam_r(Usr,puEntp,puBuf,sizeof(puBuf));
#endif

	if(puEntp != NULL)
	{
	    if(strlen(puEntp->pw_passwd)==13) strcpy(Epw,puEntp->pw_passwd);
	}
    }

    if(strlen(Epw)==0) strcpy(Epw,".............");

   /*
    *   Collect calling user[getuid()] infomation
    *   Get sysadmin group members.
    *   Is the caller a member of sysadmin(14)?
    */

#ifdef HPUX
    st     =                  getpwuid_r(getuid(),paEntp,paBuf,sizeof(paBuf),&paEntp);
#else
    paEntp = (struct passwd *)getpwuid_r(getuid(),paEntp,paBuf,sizeof(paBuf));
#endif

    if(paEntp == NULL) {
	syslog(LOG_INFO,"Failed - Caller Unknown");

	pas_msg[0].msg_style	= PAM_ERROR_MSG;
	pas_msg[0].msg		= "\nIntruder Alert! Could not determine who YOU are!\n";

	st = pam_get_item(pamh,PAM_CONV,item); pass_conv = (struct pam_conv *) *item;
	st = ((*pass_conv).conv)(1,&pas_msgp,&pas_res,(*pass_conv).appdata_ptr);
	return PAM_PERM_DENIED;
    }

    if((getegid() == 14)|(getgid() == 14))
    {
	sysadmin=1;
    }
    else
    {

#ifdef HPUX
	st     =                 getgrgid_r((gid_t)14,gpEntp,gpBuf,sizeof(gpBuf),&gpEntp);
#else
	gpEntp = (struct group *)getgrgid_r((gid_t)14,gpEntp,gpBuf,sizeof(gpBuf));
#endif
    }

    if(( gpEntp != NULL )&( ! sysadmin )) {
	/* OK we got a Group ID match */
	if(gpEntp->gr_mem != NULL)
	for(k=0;gpEntp->gr_mem[k]!=NULL;k++) {

	    if(debug>=4)
	    syslog(LOG_INFO,"   Member %8s%s",gpEntp->gr_mem[k],
		strcmp(paEntp->pw_name,gpEntp->gr_mem[k]) ? "" : "  (Match)" );

	    if(strcmp(paEntp->pw_name,gpEntp->gr_mem[k])==0) sysadmin=1;
	}
    }

   /*
    *  SYSLOG: users passwd record
    *          caller information
    *          options
    *          root?
    */

    if(debug>=2) {
	syslog(LOG_INFO," (Begin)-----------------------");
	if(pwEntp != NULL)
	{
	syslog(LOG_INFO,"          User %13s",  pwEntp->sp_namp);
	syslog(LOG_INFO,"     Encrypted %13s",  pwEntp->sp_pwdp);
	syslog(LOG_INFO,"     Last Chng %13ld", pwEntp->sp_lstchg);
	syslog(LOG_INFO,"      Min Days %13ld", pwEntp->sp_min);
	syslog(LOG_INFO,"      Max Days %13ld", pwEntp->sp_max);
	syslog(LOG_INFO,"       Warning %13ld", pwEntp->sp_warn);
	syslog(LOG_INFO,"  Max Inactive %13ld", pwEntp->sp_inact);
	syslog(LOG_INFO,"        Expire %13ld", pwEntp->sp_expire);
	}
	else
	syslog(LOG_INFO,"          User %13s", Usr);

	syslog(LOG_INFO,"");
	syslog(LOG_INFO,"Caller Info");
	syslog(LOG_INFO,"      Real uid %d [%s(%s)]", getuid(), paEntp->pw_name, paEntp->pw_passwd);
	syslog(LOG_INFO," Effective uid %d", geteuid());
	syslog(LOG_INFO,"");
	syslog(LOG_INFO," try_first_pass [ %d ]", try_first_pass);
	syslog(LOG_INFO," use_first_pass [ %d ]", use_first_pass);
	syslog(LOG_INFO,"           root [ %d ]", root);
	syslog(LOG_INFO," (End)-------------------------");
    }

   /*
    *   Check Strong Server Availability
    *   (Done during the first pass of this module)
    */

    if((PAM_PRELIM_CHECK & flags) && ! update_db && ! root) {
	if((st=udp_client((int)CMD_PING,Usr,"",em)) == PW_STAT_READY )
	{
	    /* Server ready */
	    pas_msg[0].msg_style	= PAM_TEXT_INFO;
	    pas_msg[0].msg		= "";
	    pas_msg[1].msg_style	= PAM_TEXT_INFO;
	    pas_msg[1].msg		= "  INFO: This server is equipped with a password strength enhancer and history\n"
					  "        manager. The server has been detected as \"UP\" and ready for service.";
	    pas_msg[2].msg_style	= PAM_TEXT_INFO;
	    pas_msg[2].msg		= "";

	    st = pam_get_item(pamh,PAM_CONV,item); pass_conv = (struct pam_conv *) *item;
	    st = ((*pass_conv).conv)(3,&pas_msgp,&pas_res,(*pass_conv).appdata_ptr);
	}
	else
	{
	    /* Server unavailable! */
	    pas_msg[0].msg_style	= PAM_TEXT_INFO;
	    pas_msg[0].msg		= "";
	    pas_msg[1].msg_style	= PAM_TEXT_INFO;
	    pas_msg[1].msg		= "  INFO: This server is equipped with a password strength enhancer and history\n"
					  "        manager. The server has been detected as \"DOWN\" and returned ...\n";
	    pas_msg[2].msg_style	= PAM_TEXT_INFO;
	    pas_msg[2].msg		= em;
	    pas_msg[3].msg_style	= PAM_TEXT_INFO;
	    pas_msg[3].msg		= "\n"
					  "        Please contact the UNIX team using the correct problem reporting system.\n";

	    st = pam_get_item(pamh,PAM_CONV,item); pass_conv = (struct pam_conv *) *item;
	    st = ((*pass_conv).conv)(4,&pas_msgp,&pas_res,(*pass_conv).appdata_ptr);

	    return PAM_SERVICE_ERR;
	}
    }

   /*
    *   Collect passwords
    */

    if(PAM_UPDATE_AUTHTOK & flags) {

       /*
	*  Ask User to enter current password on condition of?
	*
	*   1. USER not root
	*   2. No first password                      during option "try_first_pass"
	*   3. Exit with error if no first password   during option "use_first_pass"
	*/

	if( ! root )
	for(k=((use_first_pass*2) | !try_first_pass );k<2;k++) {

	    if(
		( ! use_first_pass && ! try_first_pass && k==0 ) ||
		( ! use_first_pass &&                     k    )
	      )
	    {

	       /*  Set Prompt (Current passwd & secure RPC passwd) */
		pas_msg[0].msg_style	= PAM_PROMPT_ECHO_OFF;
		pas_msg[0].msg		= "(Strong)Enter login(NIS+) password: ";

	       /*  Call calling programs prompt function */
		st = pam_get_item(pamh,PAM_CONV,item); pass_conv = (struct pam_conv *) *item;
		st = ((*pass_conv).conv)(1,&pas_msgp,&pas_res,(*pass_conv).appdata_ptr);

	       /*  Store Password if we got one          */
		if(pas_res[0].resp != NULL)
		    st = pam_set_item(pamh,PAM_OLDAUTHTOK,pas_res[0].resp);

	    } /* Get Old Password */

	   /*
	    *  Hummm does Entered passwd match
	    *      current login passwd?
	    */

	    /* if(debug) syslog(LOG_INFO,"  Current [ %s ]", pwEntp->sp_pwdp); */

	    if( pas_res != NULL )
	    {

		CryptPW = (char *)crypt(pas_res[0].resp,Epw);
		if(debug) syslog(LOG_INFO,"      New [ %s ]%s",
		   CryptPW, strcmp(Epw,CryptPW) ? "" : "  (Match)");

		/*
		 *  Force pam_unix.so to display this message
		 *  passwd(SYSTEM): Sorry, wrong passwd
		 *  when user enters wrong password and not in sysadmin group
		 *  or root!
		 */

		if(debug>=3) syslog(LOG_INFO,"  root[%d] sysadmin[%d]",root,sysadmin);

		if(   getuid()==0 &&   sysadmin && strcmp(pas_res[0].resp,"")==0 )
		    return PAM_SUCCESS;

		if( ! getuid()==0 && ! sysadmin && strcmp(Epw,CryptPW)!=0 )
		    return PAM_SUCCESS;
	    }
	    else
	    {       
		if(debug>=2) syslog(LOG_INFO,"Zero Length AUTH TOKENS SET");
		st = pam_set_item(pamh,PAM_OLDAUTHTOK,"");
		st = pam_set_item(pamh,PAM_AUTHTOK,"");
	    }

	} /* get Old Password and Check it? */

       /*
	*  Get New password
	*  Check passwd for strength as required
	*/

	if( ! use_first_pass && ! try_first_pass ) {

	  l = 1;
	  do { /* until password match OR 4 failures */

	   /*
	    *  Prompt for New Password
	    */

	    pas_msg[0].msg_style	= PAM_PROMPT_ECHO_OFF;
	    pas_msg[0].msg		= "(Strong)New password: ";

	    st = pam_get_item(pamh,PAM_CONV,item); pass_conv = (struct pam_conv *) *item;
	    st = ((*pass_conv).conv)(1,&pas_msgp,&pas_res,(*pass_conv).appdata_ptr);

	   /*
	    *  Copy first copy of password to AUTH_PW1
	    */

	    if(pas_res[0].resp != NULL) {
		strncpy(AUTH_PW1,pas_res[0].resp,8); AUTH_PW1[8] = '\0'; }
		else { *AUTH_PW1 = '\0'; }

	   /*
	    *  STRENGTH Check First new pasword entry
	    *
	    *  sysadmin group members and root do not conform (normal op)
	    */

	    if( ! getuid()==0 && ! sysadmin )
	    if((st=udp_client((int)CMD_PWCHK,Usr,AUTH_PW1,em)) != PW_STAT_PASS )
	    {
		pas_msg[0].msg_style	= PAM_TEXT_INFO;
		pas_msg[0].msg		= "";
		pas_msg[1].msg_style	= PAM_TEXT_INFO;
		pas_msg[1].msg		= em;
		pas_msg[2].msg_style	= PAM_TEXT_INFO;
		pas_msg[2].msg		= "";

		/*
		 *  Regular users cannot reuse a password in the
		 *  password history Period!
		 */

		if(strncasecmp(em," Password: is not old enough",20)==0) {
		    st = pam_get_item(pamh,PAM_CONV,item); pass_conv = (struct pam_conv *) *item;
		    st = ((*pass_conv).conv)(3,&pas_msgp,&pas_res,(*pass_conv).appdata_ptr);
		    l++;
		    continue;
		}

		/*
		 *  Display error and ask user to authorize IF
		 *  Password is their IMS/TSO password
		 */

		st = pam_get_item(pamh,PAM_CONV,item); pass_conv = (struct pam_conv *) *item;
		st = ((*pass_conv).conv)(3,&pas_msgp,&pas_res,(*pass_conv).appdata_ptr);

		continue;

/* The strength checker now includes this test
   I really need to test if the IMS passwd check is inabled and then
   use this code if it is not...

		pas_msg[2].msg_style	= PAM_TEXT_INFO;
		pas_msg[2].msg		= "\n"
					  "  The new password entered has failed the strength test. The reason has been\n"
					  "  given above. You are authorized to use this password if it is your current\n"
					  "  ITSS passsword. The normal UNIX password check cannot be overridden and will\n"
					  "  process your password after this first test is complete. If the systems\n"
					  "  built-in test should fail you must pick another password.\n";
		pas_msg[3].msg_style	= PAM_PROMPT_ECHO_ON;
		pas_msg[3].msg		= " Authorize this password for use? (y/[n]): ";
		pas_msg[4].msg_style	= PAM_TEXT_INFO;
		pas_msg[4].msg		= "";

		st = pam_get_item(pamh,PAM_CONV,item); pass_conv = (struct pam_conv *) *item;
		st = ((*pass_conv).conv)(5,&pas_msgp,&pas_res,(*pass_conv).appdata_ptr);

		if(pas_res[3].resp != NULL)
		{
		    if( strlen(pas_res[3].resp) != 1) continue;
		    if( *(pas_res[3].resp) != 'y' && *(pas_res[3].resp) != 'Y' ) continue;
		}
		else { continue; }
*/
	    }

	   /*
	    *  Prompt Re-enter new Password
	    *  The first copy was acceptable, we want to make sure you entered
	    *  it right the first time.
	    */

	    pas_msg[0].msg_style	= PAM_PROMPT_ECHO_OFF;
	    pas_msg[0].msg		= "(Strong)Re-enter new password: ";
	    pas_msg[1].msg_style	= PAM_TEXT_INFO;
	    pas_msg[1].msg		= "";

	    st = pam_get_item(pamh,PAM_CONV,item); pass_conv = (struct pam_conv *) *item;
	    st = ((*pass_conv).conv)(2,&pas_msgp,&pas_res,(*pass_conv).appdata_ptr);

	   /*
	    *  Copy second copy of password saved to AUTH_PW2
	    */

	    if(pas_res[0].resp != NULL) {
	    strncpy(AUTH_PW2,pas_res[0].resp,8); AUTH_PW2[8] = '\0'; }
	    else { *AUTH_PW2 = '\0'; }

	   /*
	    *  Tell user when passwords do not match?
	    */

	    if(strcmp(AUTH_PW1,AUTH_PW2)) {
		if(debug) syslog(LOG_INFO,"Passwords: They don't match");

		pas_msg[0].msg_style	= PAM_ERROR_MSG;
		pas_msg[0].msg		= "passwd(SYSTEM): They don't match; try again.\n";

		st = pam_get_item(pamh,PAM_CONV,item); pass_conv = (struct pam_conv *) *item;
		st = ((*pass_conv).conv)(1,&pas_msgp,&pas_res,(*pass_conv).appdata_ptr);
	    }

	    l++;
	  } while (( !strlen(AUTH_PW1) || strcmp(AUTH_PW1,AUTH_PW2)) && l<=4);

	 /*
	  *  Do New passwords Match!
	  */

	  if(strcmp(AUTH_PW1,AUTH_PW2)) return PAM_AUTHTOK_ERR;

	  if(debug) syslog(LOG_INFO,"Passwords Collected match.");

	 /*  Store Password if we got one          */
	  if(pas_res[0].resp != NULL)
	    st = pam_set_item(pamh,PAM_AUTHTOK,pas_res[0].resp);

	}

	/*
	 *  Assume this is the Second pass.
	 *  Save New OK'ed passwd into the DB
	 */

	if( use_first_pass && update_db ) {
	  st = pam_get_item(pamh,PAM_AUTHTOK,item);

	  if(!root)         /* No history for root account */
	  if(geteuid()==0)  /* Make sure no error so far   */
	  if(*item) {
	    if(debug>=2 && *item){syslog(LOG_INFO," PAM_AUTHTOK new ->> %s",*item);}
	    if((st=udp_client((int)CMD_PWPUTHIST,Usr,*item,em)) == PW_STAT_OK )
	    {
		pas_msg[0].msg_style	= PAM_TEXT_INFO;
		pas_msg[0].msg		= "\n(Strong)Password History Update. [ OK ]\n";

		st = pam_get_item(pamh,PAM_CONV,item); pass_conv = (struct pam_conv *) *item;
		st = ((*pass_conv).conv)(1,&pas_msgp,&pas_res,(*pass_conv).appdata_ptr);

		if(debug)
		syslog(LOG_INFO," History Update Msg\n%s", em);
	    }
	    else
	    {
		pas_msg[0].msg_style	= PAM_TEXT_INFO;
		pas_msg[0].msg		= "\n"
					  "(Strong)Password History Update. [ FAILED ]\n"
					  "  This can be ignored, however please notify a system's\n"
					  "  administrator as soon as possible.\n";
		pas_msg[1].msg_style	= PAM_TEXT_INFO;
		pas_msg[1].msg		= em;
		pas_msg[2].msg_style	= PAM_TEXT_INFO;
		pas_msg[2].msg		= "";

		st = pam_get_item(pamh,PAM_CONV,item); pass_conv = (struct pam_conv *) *item;
		st = ((*pass_conv).conv)(3,&pas_msgp,&pas_res,(*pass_conv).appdata_ptr);
	    }
	  }
	}

    } /* GET Password OR SAVE Password */

    if(debug) {
    syslog(LOG_INFO,"End   ->> pam_sm_chauthtok(%d)",flags);
    syslog(LOG_INFO,"");
    }

    return PAM_SUCCESS;
}

int pam_sm_authenticate( pamh, flags, argc, argv )
	pam_handle_t	*pamh;
	int		flags;
	int		argc;
	const char	**argv;
{ print2log("pam_sm_authenticate (called but not supported)",pamh,flags,argc,argv); return PAM_SUCCESS; }

int pam_sm_setcred( pamh, flags, argc, argv )
	pam_handle_t	*pamh;
	int		flags;
	int		argc;
	const char	**argv;
{ print2log("pam_sm_setcred      (called but not supported)",pamh,flags,argc,argv); return PAM_SUCCESS; }

int pam_sm_acct_mgmt( pamh, flags, argc, argv )
	pam_handle_t	*pamh;
	int		flags;
	int		argc;
	const char	**argv;
{ print2log("pam_sm_acct_mgmt    (called but not supported)",pamh,flags,argc,argv); return PAM_SUCCESS; }

int pam_sm_open_session( pamh, flags, argc, argv )
	pam_handle_t	*pamh;
	int		flags;
	int		argc;
	const char	**argv;
{ print2log("pam_sm_open_session (called but not supported)",pamh,flags,argc,argv); return PAM_SUCCESS; }

int pam_sm_close_session( pamh, flags, argc, argv )
	pam_handle_t	*pamh;
	int		flags;
	int		argc;
	const char	**argv;
{ print2log("pam_sm_close_session(called but not supported)",pamh,flags,argc,argv); return PAM_SUCCESS; }

void print2log( msg, pamh, flags, argc, argv )
	const char	*msg;
	pam_handle_t	*pamh;
	int		flags;
	int		argc;
	const char	**argv;
{
	int x;
	syslog(LOG_INFO,"%s[handle=%d,flags=%X,argc=%d]",msg,pamh,flags,argc);
	for(x=0;x<argc;x++) syslog(LOG_INFO," Option: %s", argv[x]);
}

/* END */
