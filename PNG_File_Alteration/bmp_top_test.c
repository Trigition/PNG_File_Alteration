#include <stdio.h>
#include "bmp_header.h"
#include "bmp_top.h"

void print_array(ds_bmp map);

int main() {
	
	ds_bmp my_map;
	my_map = create_bmp_ext("My Map.bmp", 10, 10, 0, 0, 0);
	print_array(my_map);
	printf("======\n");
	bmp_draw_line(my_map, 3, 3, 6, 6, 1, 0, 0);
	print_array(my_map);
	
	bmp_write(my_map);
	
	delete_bmp(my_map);
	
	return 0;
	
}

void print_array(ds_bmp map) {
	unsigned long w, h, i, j;
	w = get_width(map);
	h = get_height(map);
	
	//walk through, print out red values
	for (j = 0; j < w; j++) {
		for (i = 0; i < h; i++) {
			printf("%u ", pixel_get_red(map, i, j));
		}
	printf("\n");
	}
}
