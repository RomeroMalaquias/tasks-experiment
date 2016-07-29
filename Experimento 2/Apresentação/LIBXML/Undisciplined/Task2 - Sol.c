/
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
	//Adição da função
#ifdef HAVE_FNPRINTF
 	len = fnprintf(buf, sizeof(buf), "PORT %d,%d,%d,%d,%d,%d\r\n",
#elif defined HAVE_SPRINTF
 	len = sprintf(buf, "PORT %d,%d,%d,%d,%d,%d\r\n",
#else /* HAVE_SNPRINTF */
 	len = snprintf(buf, sizeof(buf), "PORT %d,%d,%d,%d,%d,%d\r\n",
#endif /* HAVE_SNPRINTF */
              adp[0] & 0xff, adp[1] & 0xff,
			#ifdef HAVE_FNPRINTF
				fnp[0]
			#else
				adp[2]
			#endif
			& 0xff, adp[3] & 0xff,
		       portp[0] & 0xff, 
		   #ifdef HAVE_FNPRINTF
				fnp[1]
			#else
				portp[1] 
			#endif
			& 0xff);			   
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
