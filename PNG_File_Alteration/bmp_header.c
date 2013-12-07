#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp_header.h"

struct ds_bmp_sentinel {
	unsigned long width, height; //how many pixels
	char ***pixel_list; //actual 3d array of pixels
	char *name; //name of the file to create
};

ds_bmp create_bmp(char const *name, unsigned long w, unsigned long h) {
	ds_bmp my_bmp;
	unsigned i,j;
	
	//make our sentinel and reserve (and copy in) our name
	my_bmp = malloc(sizeof(struct ds_bmp_sentinel));
	my_bmp->name = malloc(sizeof(char) * (1 + strlen(name)));
	strncpy(my_bmp->name, name, strlen(name));
	*(my_bmp->name + strlen(name)) = '\0';
	
	//set up width and height
	my_bmp->width = w;
	my_bmp->height = h;
	
	//create 3d array
	my_bmp->pixel_list = malloc(sizeof(char **) * w);
	for (i = 0; i < w; i++) {
		//for each column, we have a row we have to make
		my_bmp->pixel_list[i] = malloc(sizeof(char *) * h);
		for (j = 0; j < h; j++) {
			my_bmp->pixel_list[i][j] = malloc(sizeof(char) * 3);
			my_bmp->pixel_list[i][j][RED] = 0;
			my_bmp->pixel_list[i][j][GREEN] = 0;
			my_bmp->pixel_list[i][j][BLUE] = 0; 
		}
	}
	
	return my_bmp;
}

unsigned long get_width(ds_bmp a) {
	return a->width;
}

unsigned long get_height(ds_bmp a) {
	return a->height;
}

char *get_name(ds_bmp a) {
	return a->name;
}

char ***get_pixels(ds_bmp a) {
	return a->pixel_list;
}
