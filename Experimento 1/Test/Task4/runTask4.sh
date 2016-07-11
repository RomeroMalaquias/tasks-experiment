sed '/#define/d' nanoftp_.c > nanoftp.c
gcc main.c nanoftp.c nanoftp.h etio.c etio.h -o task4 &>> gccResult.txt
./task4 &>> gccResult.txt
gcc main.c nanoftp.c nanoftp.h etio.c etio.h -o task4 -D HAVE_SNPRINTF &>> gccResult.txt
./task4 &>> gccResult.txt
gcc main.c nanoftp.c nanoftp.h etio.c etio.h -o task4 -D HAVE_FNPRINTF &>> gccResult.txt
./task4 &>> gccResult.txt

