sed '/#define/d' os_unix.c > new_os_unix.c
gcc new_os_unix.c main.c new_os_unix.h -o os_unix -D TRUE=1 -D FALSE=0 -D FEAT_MZSCHEME -D HAVE_SYS_TIME_H -D HAVE_GETTIMEOFDAY -D USE_XSMP &> gccResult1.txt
gcc new_os_unix.c main.c new_os_unix.h -o os_unix -D TRUE=1 -D FALSE=0 -D FEAT_MZSCHEME -D HAVE_SYS_TIME_H -D HAVE_GETTIMEOFDAY &> gccResult2.txt
rm -rf os_unix
rm -rf new_os_unix.c

