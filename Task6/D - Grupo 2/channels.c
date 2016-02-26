#include <stdbool.h>
#include <stdio.h>
#include "channels.h"
#define HAVE_SSH1

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
  #ifdef HAVE_SSH1
   if (channel->session->version == 1) {
     return channel_open_session1(channel);
   }
  #endif
 
   return channel_open(channel,"session",64000,32000,NULL);
}
