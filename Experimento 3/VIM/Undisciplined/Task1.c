#include <stdio.h>
#include "os_unixx.h"	    /* unix includes for os_unix.c only */

/*
 * Wait "msec" msec until a character is available from file descriptor "fd".
 * Time == -1 will block forever.
 * When a GUI is being used, this will not be used for input -- webb
 * Returns also, when a request from Sniff is waiting -- toni.
 * Or when a Linux GPM mouse event is waiting.
 */
/* ARGSUSED */
#if defined(__BEOS__)
    int
#else
    static  int
#endif
RealWaitForChar(fd, msec, check_for_gpm)
    int		fd;
    long	msec;
    int		*check_for_gpm;
{
    int		ret;
#if defined(FEAT_XCLIPBOARD) || defined(USE_XSMP) || defined(FEAT_MZSCHEME)
    static int	busy = FALSE;

    /* May retry getting characters after an event was handled. */
# define MAY_LOOP

# if defined(HAVE_GETTIMEOFDAY) && defined(HAVE_SYS_TIME_H)
    /* Remember at what time we started, so that we know how much longer we
     * should wait after being interrupted. */
#  define USE_START_TV
    struct timeval  start_tv;
	if (msec > 0 && (
#ifdef FEAT_XCLIPBOARD
       xterm_Shell != 0
#if defined(USE_XSMP) || defined(FEAT_MZSCHEME)
       ||
#endif
#endif
#ifdef USE_XSMP
       xsmp_icefd != -1
#ifdef FEAT_MZSCHEME
       ||
#endif
#endif
#ifdef FEAT_MZSCHEME
   ((mzthreads_allowed() && p_mzq > 0)
#endif
       ))
	gettimeofday(&start_tv, NULL);
# endif

    /* Handle being called recursively.  This may happen for the session
     * manager stuff, it may save the file, which does a breakcheck. */
    if (busy)
	return 0;
#endif
	struct pollfd   fds[5];
	int		nfd;
# ifdef FEAT_XCLIPBOARD
	int		xterm_idx = -1;
# endif
# ifdef FEAT_MOUSE_GPM
	int		gpm_idx = -1;
# endif
# ifdef USE_XSMP
	int		xsmp_idx = -1;
# endif
	int		towait = (int)msec;

# ifdef FEAT_MZSCHEME
	mzvim_check_threads();
	if (mzthreads_allowed() && p_mzq > 0 && (msec < 0 || msec > p_mzq))
	{
	    towait = (int)p_mzq;    /* don't wait longer than 'mzquantum' */
	    mzquantum_used = TRUE;
	}
# endif
	fds[0].fd = fd;
	fds[0].events = POLLIN;
	nfd = 1;

# ifdef FEAT_SNIFF
#  define SNIFF_IDX 1
	if (want_sniff_request)
	{
	    fds[SNIFF_IDX].fd = fd_from_sniff;
	    fds[SNIFF_IDX].events = POLLIN;
	    nfd++;
	}
# endif
    return (ret > 0);
}
