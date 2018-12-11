*** ./config_h.SH	Wed Oct 29 15:03:30 1997
--- ../beta/config_h.SH	Fri Nov 14 16:32:47 1997
***************
*** 363,372 ****
  #$p_kerberos	USE_KERBEROS	/**/
  #$p_svcconf	HAS_SVCCONF	/**/
  #$p_nsswitch	HAS_NSSWITCH	/**/
  #$p_dbmpw 	DBM_PASSWD	/**/
! #$p_osf1auth OSF1_AUTH	/**/
  #$p_u4auth 	ULTRIX_AUTH	/**/
  #$p_aixauth 	AIX_AUTH	/**/
  #$o_paranoid	PARANOID 	/**/
  #$p_secure_rpc SECURE_RPC	/**/
  #define	PASSWD_UID $p_pwuid	/**/
--- 363,374 ----
  #$p_kerberos	USE_KERBEROS	/**/
  #$p_svcconf	HAS_SVCCONF	/**/
  #$p_nsswitch	HAS_NSSWITCH	/**/
+ #$p_tcbdflt 	HAS_TCBDFLT	/**/
  #$p_dbmpw 	DBM_PASSWD	/**/
! #$p_osf1auth 	OSF1_AUTH	/**/
  #$p_u4auth 	ULTRIX_AUTH	/**/
  #$p_aixauth 	AIX_AUTH	/**/
+ #$p_hpuxauth 	HPUX_AUTH	/**/
  #$o_paranoid	PARANOID 	/**/
  #$p_secure_rpc SECURE_RPC	/**/
  #define	PASSWD_UID $p_pwuid	/**/
