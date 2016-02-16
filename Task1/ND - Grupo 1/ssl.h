#include <stdbool.h>
#include <stdio.h>


void msg (int handshake, char msg[], char return_msg[], char username[], char type_set[]);
static bool key_method_2_read (struct tls_session *session, struct user up, struct auth_string ks);