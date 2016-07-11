#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "evutil.h"

int test() {
#ifndef USE_AF_INET
	if (evutil_ersatz_socketpair_(AF_INET, 1, 0) != -1) {
		return 0;
	}
#endif
#ifdef USE_AF_INET
	if (evutil_ersatz_socketpair_(AF_INET, 1, 0) == -1) {
		return 0;
	}
#endif

#ifndef USE_AF_INET6
	if (evutil_ersatz_socketpair_(AF_INET6, 1, 0) != -1) {
		return 0;
	}
#endif
#ifdef USE_AF_INET6
	if (evutil_ersatz_socketpair_(AF_INET6, 1, 0) == -1) {
		return 0;
	}
#endif

#ifndef USE_AF_IPX
	if (evutil_ersatz_socketpair_(AF_IPX, 1, 0) != -1) {
		return 0;
	}
#endif
#ifdef USE_AF_IPX
	if (evutil_ersatz_socketpair_(AF_IPX, 1, 0) == -1) {
		return 0;
	}
#endif

#ifndef USE_AF_UNIX
	if (evutil_ersatz_socketpair_(AF_UNIX, 1, 0) != -1) {
		return 0;
	}
#endif
#ifdef USE_AF_UNIX
	if (evutil_ersatz_socketpair_(AF_IPX, 1, 0) == -1) {
		return 0;
	}
#endif


	return 1;
}

int main() {
	if (!test()) {
		printf("Fail");
	} else {
		printf("Ok");
	}
	return 0;
}
