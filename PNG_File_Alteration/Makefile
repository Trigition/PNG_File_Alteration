_Obj = bmp_header.o bmp_bottom.o bmpFileWrite.o

all: bmp_header bmp_top bmpFileWrite
#add bmp_bottom to all: and in _Obj

bmp_header: bmp_header.c
	gcc -g -Wall -c bmp_header.c

bmp_top: bmp_header bmp_top.c
	gcc -g -Wall -c bmp_top.c

bmpFileWrite: bmp_header bmpFileWrite.c
	gcc -g -Wall -c bmpFileWrite.c