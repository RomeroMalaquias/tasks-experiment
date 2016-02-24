sed '/#define/d' evutil_.c > evutil.c
gcc evutil.c main.c evutil.h -o evutil -D USE_AF_INET &>> gccResult.txt
./evutil &>> gccResult.txt
gcc evutil.c main.c evutil.h -o evutil -D USE_AF_INET -D USE_AF_UNIX &>> gccResult.txt
./evutil &>> gccResult.txt
gcc evutil.c main.c evutil.h -o evutil -D USE_AF_INET6 &>> gccResult.txt
./evutil &>> gccResult.txt
gcc evutil.c main.c evutil.h -o evutil -D USE_AF_INET6 -D USE_AF_UNIX &>> gccResult.txt
./evutil &>> gccResult.txt
gcc evutil.c main.c evutil.h -o evutil -D USE_AF_IPX &>> gccResult.txt
./evutil &>> gccResult.txt
gcc evutil.c main.c evutil.h -o evutil -D USE_AF_IPX -D USE_AF_UNIX &>> gccResult.txt
./evutil &>> gccResult.txt
rm -rf evutil

