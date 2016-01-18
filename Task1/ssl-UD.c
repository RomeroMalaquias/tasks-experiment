#include <stdbool.h>
#include <stdio.h>
#define D_HANDSHAKE 1
#define SSLF_USERNAME_AS_COMMON_NAME 1


struct opts
{
	int ssl_flags;
};

struct tls_session
{
	struct opts opt;
};

struct user
{
	char username[20];
};



void msg (int handshake, char msg[], char return_msg[], char username[], char type_set[])
{
	printf("olá");
}

void set_common_name (struct tls_session *session, char username[]) 
{
}

static bool key_method_2_read (struct tls_session *session)
{  
	struct user up = {"joao"};
	if ((session->opt.ssl_flags & SSLF_USERNAME_AS_COMMON_NAME))
  	    set_common_name (session, up.username);
            msg (D_HANDSHAKE, "TLS: Username/Password authentication %s for username '%s' %s",
#ifdef ENABLE_DEF_AUTH
  	       ks->auth_deferred ? "deferred" : "succeeded",
#else
  	       "succeeded",
#endif
  	       up.username,
  	       (session->opt.ssl_flags & SSLF_USERNAME_AS_COMMON_NAME) ? "[CN SET]" : "");
return true;
}

int main() {
struct opts session_opts = {0};
struct tls_session session = {session_opts};
key_method_2_read(&session);
return 1;
}
