#include <stdbool.h>
#include <stdio.h>
#include "ssl-lib.h"
#define D_HANDSHAKE 1
#define SSLF_USERNAME_AS_COMMON_NAME 1
#define ENABLE_DEF_AUTH


#if defined(DISCIPLINED)
#include "ssl-D.h"
#else
#include "ssl-UD.h"	
#endif

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