#include <stdbool.h>
#include <stdio.h>


int
xmlNanoFTPGetConnection()
{  
char buf[200];	
int adp[4] = {1,4,2};
int portp[2] = {20,4};
#ifdef HAVE_FNPRINTF
int fnp[2] = {10,1};
#endif
int len;

#ifndef HAVE_SNPRINTF
  	len = sprintf(buf, "PORT %d,%d,%d,%d,%d,%d\r\n",
#else /* HAVE_SNPRINTF */
  	len = snprintf(buf, sizeof(buf), "PORT %d,%d,%d,%d,%d,%d\r\n",
#endif /* HAVE_SNPRINTF */
               adp[0] & 0xff, adp[1] & 0xff, adp[2] & 0xff, adp[3] & 0xff,
 		       portp[0] & 0xff, portp[1] & 0xff);
return len;
}
