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
