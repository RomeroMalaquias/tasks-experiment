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

void set_common_name (struct tls_session *session, char username[]);