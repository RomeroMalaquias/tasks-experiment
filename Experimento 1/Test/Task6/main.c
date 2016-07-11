#include <stdio.h>
#include "channels.h"

int main(void) {
    session session = {version: 1};
    CHANNEL channel = {session: session};
    if(channel_open_session(&channel) != 1) {
	printf("fail");
    }
    return 0;
}
