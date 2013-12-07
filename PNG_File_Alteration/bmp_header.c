#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp_header.h"

struct ds_bmp_sentinel {
	unsigned long size; //how many pixels
	char **pixel_list; //actual 3d array of pixels
	char *name; //name of the file to create
};

ds_bmp create_bmp(char const *name, unsigned long w, unsigned long h) {
	ds_bmp my_bmp;
	unsigned i;
	
	//make our sentinel and reserve (and copy in) our name
	my_bmp = malloc(sizeof(struct ds_bmp_sentinel));
	my_bmp->name = malloc(sizeof(char) * (1 + strlen(name)));
	strncpy(my_bmp->name, name, strlen(name));
	*(my_bmp->name + strlen(name)) = '\0';
	
	//create 3d array
	pixel_list = calloc(sizeof(char *) * w);
	for (i = 0; i < w; i++) {
		//for each 
	}
	
	return my_bmp;
}

unsigned long get_size(ds_bmp a) {
	return a->size;
}

char *get_name(ds_bmp a) {
	return a->name;
}

char **get_pixels(ds_bmp a) {
	return a->pixel_list;
}
