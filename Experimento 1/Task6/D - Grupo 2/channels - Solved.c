#include <stdbool.h>
#include <stdio.h>

typedef struct BUFFER
{
	int buff;
} BUFFER;
typedef struct version
{
	int *version;
} version;
typedef struct session
{
	version *version;
} session;
typedef struct CHANNEL
{
	session session;
} CHANNEL;



  static int channel_open(CHANNEL *channel, const char *type_c, int window,
     int maxpacket, BUFFER *payload) {
   return 1;
   }
  
/**
  * @brief Open a session channel (suited for a shell, not TCP forwarding).
  *
  * @param channel       An allocated channel.
  *
  * @return SSH_OK on success\n
  *         SSH_ERROR on error.
  *
  * @see channel_open_forward()
  * @see channel_request_env()
  * @see channel_request_shell()
  * @see channel_request_exec()
   */
int channel_open_session(CHANNEL *channel) {

   return channel_open(channel,"session",64000,32000,NULL);
}


int main() {


return 0;
}
