#include <stdbool.h>
#include <stdio.h>
#define D_HANDSHAKE 1
#define SSLF_USERNAME_AS_COMMON_NAME 1
#define ENABLE_DEF_AUTH


typedef struct opts
{
	int ssl_flags;
} opts;
#ifdef ENABLE_DEF_AUTH
typedef struct auth_string
{
	char auth_deferred[20];
} auth_string;
#endif

typedef struct tls_session
{
	struct opts opt;
	char username[20];
} tls_session;

typedef struct user
{
	char username[20];
} user; 

void msg (int handshake, char msg[], char return_msg[], char username[], char type_set[])
{
	bool is_authenticated = handshake;	
#  ifdef ENABLE_DEF_AUTH
        is_authenticated = is_authenticated && return_msg != "deferred";
#	endif
#  ifdef PLUGIN_DEF_AUTH
        is_authenticated = is_authenticated && type_set != "[CN SET]";
#  endif
#  ifdef ENABLE_OCC
    is_authenticated = is_authenticated || (return_msg == "succeeded" && username.length > 0);
#  endif
    if (is_authenticated) 
	{
		printf("authentication succeeded");
	} else {
		printf("authentication failed");
	}
	
}
void set_common_name (struct tls_session *session, char username[]) 
{	
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

int main() {
opts session_opts = {0};
tls_session session = {session_opts, ""};
user up = {"joao"};
#ifdef ENABLE_DEF_AUTH
auth_string ks = {"succeeded"};
#endif
key_method_2_read(&session, up, ks);

return 0;
}