/*
#include <sys/socket.h>
#include <sys/un.h>

int
evutil_ersatz_socketpair_(int family, int type, int protocol)
{
	int test;
	test = (family != AF_INET);
#ifdef USE_AF_UNIX
	test = test && (family != AF_UNIX);
#endif
	if (protocol || test) {
			return -1;
	}

	return socket(family, type, protocol);
}
*/

#include <sys/socket.h>
#include <sys/un.h>

int
evutil_ersatz_socketpair_(int family, int type, int protocol)
{
	int test;
#ifdef USE_AF_INET
	test = (family != AF_INET);
#endif
#ifdef USE_AF_INET6
	test = (family != AF_INET6);
#endif
#ifdef USE_AF_IPX
	test = (family != AF_IPX);
#endif
#ifdef USE_AF_UNIX
	test = test && (family != AF_UNIX);
#endif
	if (protocol || test) {
			return -1;
	}

	return socket(family, type, protocol);
}
