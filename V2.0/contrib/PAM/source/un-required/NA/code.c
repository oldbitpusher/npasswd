

/* Examples */

sp = getservbyname("login", "tcp");if (sp == (struct servent *) NULL) {
  fprintf(stderr,"rlogin: tcp/login: unknown service");  exit(1);}


hp = gethostbyname(argv[1]);if (hp == (struct hostent *) NULL) {
  fprintf(stderr, "rlogin: %s: unknown host", argv[1]);  exit(2);}


main()
{
   ...
   sp = getservbyname("who", "udp");
   net = getnetbyname("localnet");
   sin.sin_addr = inet_makeaddr(net->n_net, INADDR_ANY);
   sin.sin_port = sp->s_port;
   ...
   s = socket(AF_INET, SOCK_DGRAM, 0);
   ...
   on = 1;
   if (setsockopt(s, SOL_SOCKET, SO_BROADCAST, &on, sizeof on)
         == -1) {
      syslog(LOG_ERR, "setsockopt SO_BROADCAST: %m");
      exit(1);
   }
   bind(s, (struct sockaddr *) &sin, sizeof sin);
   ...
   signal(SIGALRM, onalrm);
   onalrm();
   while(1) {
      struct whod wd;
       int cc, whod, len = sizeof from;
      cc = recvfrom(s, (char *) &wd, sizeof(struct whod), 0,
         (struct sockaddr *) &from, &len);
      if (cc <= 0) {
      if (cc == -1 && errno != EINTR)
         syslog(LOG_ERR, "rwhod: recv: %m");
      continue;
      }
      if (from.sin_port != sp->s_port) {
         syslog(LOG_ERR, "rwhod: %d: bad from port",
            ntohs(from.sin_port));
         continue;
      }
      ...
      if (!verify( wd.wd_hostname)) {
         syslog(LOG_ERR, "rwhod: bad host name from %x",
            ntohl(from.sin_addr.s_addr));
         continue;
      }
      (void) sprintf(path, "%s/whod.%s", RWHODIR, wd.wd_hostname);
      whod = open(path, O_WRONLY|O_CREAT|O_TRUNC, 0666);
      ...
      (void) time(&wd.wd_recvtime);
      (void) write(whod, (char *) &wd, cc);
      (void) close(whod);
   }
   exit(0);
}
