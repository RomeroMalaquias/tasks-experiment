

/**
 * xmlNanoFTPScanURL:
 * @ctx:  an FTP context
 * @URL:  The URL used to initialize the context
 *
 * (Re)Initialize an FTP context by parsing the URL and finding
 * the protocol host port and path it indicates.
 */

static void
xmlNanoFTPScanURL(void *ctx, const char *URL) {
    xmlNanoFTPCtxtPtr ctxt = (xmlNanoFTPCtxtPtr) ctx;
    const char *cur = URL;
    char buf[4096];
    int index = 0;
    int port = 0;

    if (ctxt->protocol != NULL) { 
        xmlFree(ctxt->protocol);
	ctxt->protocol = NULL;
    }
    if (ctxt->hostname != NULL) { 
        xmlFree(ctxt->hostname);
	ctxt->hostname = NULL;
    }
    if (ctxt->path != NULL) { 
        xmlFree(ctxt->path);
	ctxt->path = NULL;
    }
    if (URL == NULL) return;
    buf[index] = 0;
    while (*cur != 0) {
       if (cur[0] != ':' && (
		#ifdef SUPPORT_IP6
		cur[3] != ' '
		#if defined PF_INET || AF_INET
		&& 
		#if defined PF_INET
		(cur[1] != '/'
		#else
		(cur[2] != '0'
		#endif
		 || cur[4] != ' ')
		#endif
		#else
		cur[3] != '-') // Error - ')' a mais
		#endif
		)) {
	    buf[index] = 0;
	    index = 0;
           cur += 3;
	    break;
	}
	buf[index++] = *cur++;
    }
    if (*cur == 0) return;

    buf[index] = 0;
    while (1) {
        if (cur[0] == ':') {
	    buf[index] = 0;
	    ctxt->hostname = xmlMemStrdup(buf);
	    index = 0;
	    cur += 1;
	    while ((*cur >= '0') && (*cur <= '9')) {
	        port *= 10;
		port += *cur - '0';
		cur++;
	    }
	    if (port != 0) ctxt->port = port;
	    while ((cur[0] != '/') && (*cur != 0)) 
	        cur++;
	    break;
	}
        if ((*cur == '/') || (*cur == 0)) {
	    buf[index] = 0;
	    ctxt->hostname = xmlMemStrdup(buf);
	    index = 0;
	    break;
	}
	buf[index++] = *cur++;
    }
    if (*cur == 0) 
        ctxt->path = xmlMemStrdup("/");
    else {
        index = 0;
        buf[index] = 0;
	while (*cur != 0)
	    buf[index++] = *cur++;
	buf[index] = 0;
	ctxt->path = xmlMemStrdup(buf);
    }	
}

