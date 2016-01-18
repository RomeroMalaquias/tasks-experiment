  if ((session->opt->ssl_flags & SSLF_USERNAME_AS_COMMON_NAME))
  	    set_common_name (session, up->username);
#ifdef ENABLE_DEF_AUTH
	  msg (D_HANDSHAKE, "TLS: Username/Password authentication %s for username '%s' %s",
  	       ks->auth_deferred ? "deferred" : "succeeded",
	       up->username,
	       (session->opt->ssl_flags & SSLF_USERNAME_AS_COMMON_NAME) ? "[CN SET]" : "");
#else
	  msg (D_HANDSHAKE, "TLS: Username/Password authentication %s for username '%s' %s","succeeded",
  	       up->username,
  	       (session->opt->ssl_flags & SSLF_USERNAME_AS_COMMON_NAME) ? "[CN SET]" : "");
#endif
