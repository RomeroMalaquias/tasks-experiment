#include <stdio.h>
#include "nanoftp.h"

int main(void) {
#ifdef HAVE_FNPRINTF
    if(xmlNanoFTPGetConnection() != 10) {    
        printf("fail \n");
    }
#else
#ifndef HAVE_SNPRINTF
    if(xmlNanoFTPGetConnection() != 2) {    
        printf("fail \n");
    }

#else /* HAVE_SNPRINTF */
    if(xmlNanoFTPGetConnection() != 2) {    
        printf("fail \n");
    }

#endif
#endif    
    return 0;
}
