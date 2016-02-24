/*
 * os_unix.h
 *
 *  Created on: Feb 23, 2016
 *      Author: lmac
 */

#ifndef OS_UNIX_H_
#define OS_UNIX_H_

int mzthreads_allowed();

int RealWaitForChar(int fd, int msec, int * check_for_gpm);

#endif /* OS_UNIX_H_ */
