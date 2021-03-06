#include <stdbool.h>
#include <stdio.h>
#define FALSE 0
#define TRUE 1

#define FEAT_MZSCHEME
#define HAVE_SYS_TIME_H
#define HAVE_GETTIMEOFDAY

int 
mzthreads_allowed() 
{
	return 1;
};

int

RealWaitForChar(fd, msec, check_for_gpm)
    int     fd;
    long    msec;
    int     *check_for_gpm;
{
    int     ret;
#ifdef FEAT_NETBEANS_INTG
    int     nb_fd = netbeans_filedesc();
#endif
#if defined(FEAT_XCLIPBOARD) || defined(USE_XSMP) || defined(FEAT_MZSCHEME)
    static int  busy = FALSE;
	int p_mzq = TRUE;

    /* May retry getting characters after an event was handled. */
#define MAY_LOOP

#if defined(HAVE_GETTIMEOFDAY) && defined(HAVE_SYS_TIME_H)
    /* Remember at what time we started, so that we know how much longer we
     * should wait after being interrupted. */
#define USE_START_TV
    int start_tv = 0;
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
    (mzthreads_allowed() && p_mzq > 0) //Retirando ( a mais
#endif
        ))
    gettimeofday(&start_tv, NULL);
#endif

    /* Handle being called recursively.  This may happen for the session
     * manager stuff, it may save the file, which does a breakcheck. */
    if (busy)
		return 0;
#endif
	return 1;
}

int main() {


return 0;
}
