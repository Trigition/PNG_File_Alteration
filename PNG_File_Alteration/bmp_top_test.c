#include <stdio.h>
#include "bmp_header.h"
#include "bmp_top.h"

void print_array(ds_bmp map);
void create_animation();

int main() {
	create_animation();
	//ds_bmp my_map;
	//my_map = create_bmp_ext("My Map.bmp", 50, 50, 255, 255, 255);
	//print_array(my_map);
	//printf("======\n");
	//bmp_draw_line(my_map, 25, 25, 45, 30, 0, 0, 0);
	//bmp_gradient(my_map, 0, 0, 0, 0, 0, 255, MODE_SUB);
	//bmp_gradient(my_map, 0, 64, 0, 0, 255, 0, MODE_SUB);
	//print_array(my_map);
	
	//bmp_write(my_map);
	
	//delete_bmp(my_map);
	
	return 0;
	
}

void create_animation() {
    ds_bmp my_map;
    char main_name[100];
    unsigned long run = 0;
    for (;run < 1000; run++) {
        sprintf(main_name, "animation_%lu.bmp", run);
        my_map = create_bmp_ext(main_name, 100, 100, 0, 0, 0);
        bmp_draw_line(my_map, 1, 25, (run % 98) + 1, 26, 255 - run, 255, 255);
        bmp_write(my_map);
        delete_bmp(my_map);
    }
}

void print_array(ds_bmp map) {
	unsigned long w, h, i, j;
	w = get_width(map);
	h = get_height(map);
	
	//walk through, print out red values
	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			printf("%3.0u ", pixel_get_red(map, i, j));
		}
	printf("\n");
	}
}
