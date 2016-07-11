#include <stdbool.h>
#include <stdio.h>
#include "channels.h"

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
  
  
 int channel_open_session(CHANNEL *channel){
 #ifdef HAVE_SSH1
     if(channel->session.version.version==2)
 #endif
         return channel_open(channel,"session",64000,32000,NULL);
  #ifdef HAVE_SSH1
     else
         return channel_open_session1(channel);
  #endif
  

}
