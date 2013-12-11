_Obj = bmp_bottom.o bmpFileWrite.o

all: bmp_top bmpFileWrite bmp_top_test lib_byte_read
#add bmp_bottom to all: and in _Obj


bmp_top: bmp_top.c
	gcc -g -Wall -c bmp_top.c

bmpFileWrite: bmpFileWrite.c
	gcc -g -Wall -c bmpFileWrite.c

bmp_top_test: bmp_top bmpFileWrite bmp_top_test.c
	gcc -g -Wall bmp_top_test.c bmp_top.o bmpFileWrite.o -lm -o test.exe

lib_byte_read: lib_read_bytes
	gcc -g -Wall lib_read_bytes.c -o read_bytes.exe
