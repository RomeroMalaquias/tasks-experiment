#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "ssl-lib.h"
#include "ssl-D.h"


void msg (int handshake, char msg[], char return_msg[], char username[], char type_set[])
{
	bool is_authenticated = handshake;	
#ifdef ENABLE_DEF_AUTH
        is_authenticated = is_authenticated && return_msg != "deferred";
#endif
#ifdef PLUGIN_DEF_AUTH
        is_authenticated = is_authenticated && type_set != "[CN SET]";
#endif
#ifdef ENABLE_OCC
    is_authenticated = is_authenticated || (return_msg == "succeeded" && strlen(username) > 0);
#endif
    if (is_authenticated) 
	{
		printf("authentication succeeded");
	} else {
		printf("authentication failed");
	}
	
}

static bool key_method_2_read (struct tls_session *session, struct user up, struct auth_string ks)
{  	  
  if ((session->opt.ssl_flags & SSLF_USERNAME_AS_COMMON_NAME))
  	    set_common_name (session, up.username);
#ifdef ENABLE_DEF_AUTH
	  msg (D_HANDSHAKE, "TLS: Username/Password authentication %s for username '%s' %s",
  	       ks.auth_deferred ? "deferred" : "succeeded",
	       up.username,
	       (session->opt.ssl_flags & SSLF_USERNAME_AS_COMMON_NAME) ? "[CN SET]" : "");
#else
	  msg (D_HANDSHAKE, "TLS: Username/Password authentication %s for username '%s' %s","succeeded",
  	       up.username,
  	       (session->opt.ssl_flags & SSLF_USERNAME_AS_COMMON_NAME) ? "[CN SET]" : "");
#endif
return true;
}