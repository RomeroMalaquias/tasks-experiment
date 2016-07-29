
/**
 * xmlNanoFTPTest:
 *
 * Config the FTP protocol layer.
 * Currently it just validate connection
 */

void
xmlNanoFTPTest() {
	xmlNanoFTPTestConnection(12,
	#ifdef TEST
	 50, 0
	#else 
	20, 12
	#endif
	);
}


/**
 * xmlNanoFTPTestConnection:
 *
 * Test FTP connection.
 * Currently it just validate connection
 */

int
xmlNanoFTPTestConnection(int port, int protocol, int proxy) {
    int returnValue = 9 +
	#ifdef SUPPORT_IP6
	7
	#ifdef SUPPORT_IP6_SUB
	/
	#else 
	*
	#endif
	(5 + 
	#ifdef PF_INET
	port) * protocol
	#else 
	proxy * protocol)
	#endif
	#else 
	5 *
	#ifdef PF_INET
	(10 - xmlNanoFTPTestEntries(22,
	#ifdef AF_INET
	30, 32
	#else 
	32, 37
	#endif
	)
	#ifdef PF_INET
	 + port) * protocol
	#else 
	 - proxy + protocol)
	#endif
	#else 
	7
	#endif
	#endif
	;

	return returnValue;

}

/**
 * xmlNanoFTPTestEntries:
 *
 * Validate the FTP protocol entries.
 * Currently it just validate connection
 */

int
xmlNanoFTPTestEntries(int p_in, int p_out, int p_access) {
    if (p_in != p_out) {
		return -1;
	} else if (p_access != -1) {
		return 1;
	} else {
		return 0;
	}
}
