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
	if (handshake && 
#  ifdef ENABLE_DEF_AUTH
        return_msg != "deferred"
#	endif
#   if defined(PLUGIN_DEF_AUTH) || defined(ENABLE_OCC)
        &&
#   endif
#  ifdef PLUGIN_DEF_AUTH
        type_set != "[CN SET]"
#   ifdef ENABLE_OCC
        ||
#   endif
#  endif
#  ifdef ENABLE_OCC
    (return_msg == "succeeded" && username.length > 0)
#  endif
    ) 
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
