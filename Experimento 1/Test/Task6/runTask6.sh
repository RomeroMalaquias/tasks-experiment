sed '/#define/d' channels_.c > channels.c
gcc channels_functions.c channels_functions.h channels.h channels.c main.c -o task6 &>> gccResult.txt
./task6 &>> gccResult.txt
gcc channels_functions.c channels_functions.h channels.h channels.c main.c -o task6 -D HAVE_SSH1 &>> gccResult.txt
./task6 &>> gccResult.txt

