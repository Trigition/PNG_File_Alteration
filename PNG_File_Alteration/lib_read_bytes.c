#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFLEN 2048

int main(int argc, char *argv[]) {
	
	char buffer, *filename = "My Map.bmp";
	
	if (argc > 1) {
		filename = argv[1];
	}
	else {
		printf("Defaulting to 'My Map.bmp'.\nIf you want to print out the contents of a different file,\nSupply the filename as a command line argument:\n./read_bytes.exe myfile.bmp");
	}
	
	FILE *f_in = fopen(filename, "r");
	if (f_in == NULL) {
		printf("Invalid file input. Please make sure it exists!\n");
		exit(1);
	}
	printf("\n");
	while ((buffer = fgetc(f_in)) != EOF) {
		printf("%u ", (unsigned) buffer);
	}
	printf("\n");
	
	fclose(f_in);
	
	return 0;
	
}
