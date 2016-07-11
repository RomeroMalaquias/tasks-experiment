/**
 *
#include <sys/socket.h>
#include <sys/un.h>

int
evutil_ersatz_socketpair_(int family, int type, int protocol)
{
	if (protocol
		|| (
			family != AF_INET
	#ifdef USE_AF_UNIX
			&& family != AF_UNIX
	#endif
		)) {
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
	if (protocol
		|| (
	#ifdef USE_AF_INETs
			family != AF_INET
	#endif
	#ifdef USE_AF_INET6
			family != AF_INET6
	#endif
	#ifdef USE_AF_IPX
			family != AF_IPX
	#endif
	#ifdef USE_AF_UNIX
			&& family != AF_UNIX
	#endif
		)) {
			return -1;
	}

	return socket(family, type, protocol);
}
