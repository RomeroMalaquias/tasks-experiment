#include <stdbool.h>
#include "etio.h"
#include "nanoftp.h"


int
xmlNanoFTPGetConnection()
{  
char buf[200];	
int adp[4] = {1,4,2,0};
int portp[2] = {20,4};
#ifdef HAVE_FNPRINTF
int fnp[2] = {10,1};
#endif
int len;

#ifndef HAVE_SNPRINTF
  	len = sprintf2(buf, "PORT %d,%d,%d,%d,%d,%d\r\n",
	       adp[0] & 0xff, adp[1] & 0xff, adp[2] & 0xff, adp[3] & 0xff,
	       portp[0] & 0xff, portp[1] & 0xff);
#else /* HAVE_SNPRINTF */
  	len = snprintf2(buf, sizeof(buf), "PORT %d,%d,%d,%d,%d,%d\r\n",
	       adp[0] & 0xff, adp[1] & 0xff, adp[2] & 0xff, adp[3] & 0xff,
	       portp[0] & 0xff, portp[1] & 0xff);
#endif /* HAVE_SNPRINTF */
return len;
}
