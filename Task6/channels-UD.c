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


/** \brief open a session channel (suited for a shell. Not tcp Forwarding)
  * \param channel an allocated channel (see channel_new())
  * \return SSH_OK on success\n
  * SSH_ERROR on error
  * \see channel_open_forward()
  * \see channel_request_env()
  * \see channel_request_shell()
  * \see channel_request_exec()
  * \warning API changed from 0.11
  */
  static int channel_open(CHANNEL *channel, const char *type_c, int window,
     int maxpacket, BUFFER *payload) {
   return 1;
   }
 
  
  
  
 int channel_open_session(CHANNEL *channel){
 #ifdef HAVE_SSH1
     if(channel->session->version==2)
 #endif
         return channel_open(channel,"session",64000,32000,NULL);
  #ifdef HAVE_SSH1
     else
         return channel_open_session1(channel);
  #endif
  }


int main() {


return 0;
}
