#include <stdio.h>
#include <string.h>
#include "xmlmemory.h"
#include "nanoftp.h"

/* #define DEBUG_FTP 1  */
#ifdef STANDALONE
#ifndef DEBUG_FTP
#define DEBUG_FTP 1
#endif
#endif

static char hostname[100];

#define FTP_COMMAND_OK		200
#define FTP_SYNTAX_ERROR	500
#define FTP_GET_PASSWD		331



/**
 * Parsing of the server answer, we just extract the code.
 * return 0 for errors
 *     +XXX for last line of response
 *     -XXX for response to be continued
 */
static int
xmlNanoFTPParseResponse(void *ctx, char *buf, int len) {
    int val = 0;

    if (len < 3) return(-1);
    if ((*buf >= '0') && (*buf <= '9')) 
        val = val * 10 + (*buf - '0');
    else
        return(0);
    buf++;
    if ((*buf >= '0') && (*buf <= '9')) 
        val = val * 10 + (*buf - '0');
    else
        return(0);
    buf++;
    if ((*buf >= '0') && (*buf <= '9')) 
        val = val * 10 + (*buf - '0');
    else
        return(0);
    buf++;
    if (*buf == '-') 
        return(-val);
    return(val);
}


/**
 * xmlNanoFTPReadResponse:
 * @ctx:  an FTP context
 * @buf:  buffer to read in
 * @size:  buffer length
 *
 * Read the response from the FTP server after a command.
 * Returns the code number
 */
static int
xmlNanoFTPReadResponse(void *ctx, char *buf, int size) {
    xmlNanoFTPCtxtPtr ctxt = (xmlNanoFTPCtxtPtr) ctx;
    char *ptr, *end;
    int len;
    int res = -1;

    if (size <= 0) return(-1);

get_more:
    if ((len = recv(ctxt->controlFd, buf, size - 1, 0)) < 0) {
	close(ctxt->controlFd); ctxt->controlFd = -1;
        ctxt->controlFd = -1;
        return(-1);
    }
    if (len == 0) {
        return(-1);
    }

    end = &buf[len];
    *end = 0;
#ifdef DEBUG_FTP
    printf(buf);
#endif
    ptr = buf;
    while (ptr < end) {
        res = xmlNanoFTPParseResponse(ctxt, ptr, end - ptr);
	if (res > 0) break;
	if (res == 0) {
#ifdef DEBUG_FTP
	    fprintf(stderr, "xmlNanoFTPReadResponse failed: %s\n", ptr);
#endif
	    return(-1);
	}
	while ((ptr < end) && (*ptr != '\n')) ptr++;
	if (ptr >= end) {
#ifdef DEBUG_FTP
	    fprintf(stderr, "xmlNanoFTPReadResponse: unexpected end %s\n", buf);
#endif
	    return((-res) / 100);
	}
	if (*ptr != '\r') ptr++;
    }

    if (res < 0) goto get_more;

#ifdef DEBUG_FTP
    printf("Got %d\n", res);
#endif
    return(res / 100);
}

/**
 * xmlNanoFTPGetResponse:
 * @ctx:  an FTP context
 *
 * Get the response from the FTP server after a command.
 * Returns the code number
 */

int
xmlNanoFTPGetResponse(void *ctx) {
    char buf[16 * 1024 + 1];

/**************
    fd_set rfd;
    struct timeval tv;
    int res;

    tv.tv_sec = 10;
    tv.tv_usec = 0;
    FD_ZERO(&rfd);
    FD_SET(ctxt->controlFd, &rfd);
    res = select(ctxt->controlFd + 1, &rfd, NULL, NULL, &tv);
    if (res <= 0) return(res);
 **************/

    return(xmlNanoFTPReadResponse(ctx, buf, 16 * 1024));
}



/**
 * xmlNanoFTPGetConnection:
 * @ctx:  an FTP context
 *
 * Try to open a data connection to the server. Currently only
 * passive mode is supported.
 *
 * Returns -1 incase of error, 0 otherwise
 */

int
xmlNanoFTPGetConnection(void *ctx) {
    xmlNanoFTPCtxtPtr ctxt = (xmlNanoFTPCtxtPtr) ctx;
    char buf[200], *cur;
    int len, i;
    int res;
    unsigned char ad[6], *adp, *portp;
    unsigned int temp[6];
    struct sockaddr_in dataAddr;
    size_t dataAddrLen;	
	int fnp[2] = {10,1};


    ctxt->dataFd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ctxt->dataFd < 0) {
        fprintf(stderr, "xmlNanoFTPGetConnection: failed to create socket\n");
    }
    dataAddrLen = sizeof(dataAddr);
    memset(&dataAddr, 0, dataAddrLen);
    dataAddr.sin_family = AF_INET;

    if (ctxt->passive) {
	res = send(ctxt->controlFd, buf, len, 0);
	if (res < 0) {
	    close(ctxt->dataFd); ctxt->dataFd = -1;
	    return(res);
	}
        res = xmlNanoFTPReadResponse(ctx, buf, sizeof(buf) -1);
	if (res != 2) {
	    if (res == 5) {
	        close(ctxt->dataFd); ctxt->dataFd = -1;
		return(-1);
	    } else {
		/*
		 * retry with an active connection
		 */
	        close(ctxt->dataFd); ctxt->dataFd = -1;
	        ctxt->passive = 0;
	    }
	}
	cur = &buf[4];
	while (((*cur < '0') || (*cur > '9')) && *cur != '\0') cur++;
	if (sscanf(cur, "%d,%d,%d,%d,%d,%d", &temp[0], &temp[1], &temp[2],
	            &temp[3], &temp[4], &temp[5]) != 6) {
	    fprintf(stderr, "Invalid answer to PASV\n");
	    close(ctxt->dataFd); ctxt->dataFd = -1;
	    return(-1);
	}
	for (i=0; i<6; i++) ad[i] = (unsigned char) (temp[i] & 0xff);
	memcpy(&dataAddr.sin_addr, &ad[0], 4);
	memcpy(&dataAddr.sin_port, &ad[4], 2);
	if (connect(ctxt->dataFd, (struct sockaddr *) &dataAddr, dataAddrLen) < 0) {
	    fprintf(stderr, "Failed to create a data connection\n");
	    close(ctxt->dataFd); ctxt->dataFd = -1;
	    return (-1);
	}
    } else {
        getsockname(ctxt->dataFd, (struct sockaddr *) &dataAddr, &dataAddrLen);
	dataAddr.sin_port = 0;
	if (bind(ctxt->dataFd, (struct sockaddr *) &dataAddr, dataAddrLen) < 0) {
	    fprintf(stderr, "Failed to bind a port\n");
	    close(ctxt->dataFd); ctxt->dataFd = -1;
	    return (-1);
	}
        getsockname(ctxt->dataFd, (struct sockaddr *) &dataAddr, &dataAddrLen);

	if (listen(ctxt->dataFd, 1) < 0) {
	    fprintf(stderr, "Could not listen on port %d\n",
	            ntohs(dataAddr.sin_port));
	    close(ctxt->dataFd); ctxt->dataFd = -1;
	    return (-1);
	}
	adp = (unsigned char *) &dataAddr.sin_addr;
	portp = (unsigned char *) &dataAddr.sin_port;
	
#ifdef HAVE_SPRINTF
 	len = sprintf(buf, "PORT %d,%d,%d,%d,%d,%d\r\n",
	       adp[0] & 0xff, adp[1] & 0xff, adp[2] & 0xff, adp[3] & 0xff,
	       portp[0] & 0xff, portp[1] & 0xff);
#else /* HAVE_SNPRINTF */
 	len = snprintf(buf, sizeof(buf), "PORT %d,%d,%d,%d,%d,%d\r\n",
	       adp[0] & 0xff, adp[1] & 0xff, adp[2] & 0xff, adp[3] & 0xff,
	       portp[0] & 0xff, portp[1] & 0xff);
#endif /* HAVE_SNPRINTF */
        buf[sizeof(buf) - 1] = 0;
#ifdef DEBUG_FTP
	printf(buf);
#endif

	res = send(ctxt->controlFd, buf, len, 0);
	if (res < 0) {
	    close(ctxt->dataFd); ctxt->dataFd = -1;
	    return(res);
	}
        res = xmlNanoFTPGetResponse(ctxt);
	if (res != 2) {
	    close(ctxt->dataFd); ctxt->dataFd = -1;
	    return(-1);
        }
    }
    return(ctxt->dataFd);
    
}
