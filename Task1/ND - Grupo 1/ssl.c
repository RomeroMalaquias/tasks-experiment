#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "ssl-lib.h"
#include "ssl-UD.h"



void msg (int handshake, char msg[], char return_msg[], char username[], char type_set[])
{
	if (handshake  
#ifdef ENABLE_DEF_AUTH
        && return_msg != "deferred"
#endif
#if defined(PLUGIN_DEF_AUTH) || defined(ENABLE_OCC)
        &&
#endif
#ifdef PLUGIN_DEF_AUTH
        type_set != "[CN SET]"
#ifdef ENABLE_OCC
        ||
#endif
#endif
#ifdef ENABLE_OCC
    (return_msg == "succeeded" && strlen(username) > 0)
#endif
    ) 
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
            msg (D_HANDSHAKE, "TLS: Username/Password authentication %s for username '%s' %s",
#ifdef ENABLE_DEF_AUTH
  	       ks.auth_deferred ? "deferred" : "succeeded",
#else
  	       "succeeded",
#endif
  	       up.username,
  	       (session->opt.ssl_flags & SSLF_USERNAME_AS_COMMON_NAME) ? "[CN SET]" : "");
return true;
}
