#include <stdio.h>
#include "bmp_header.h"
#include "bmp_top.h"

void print_array(ds_bmp map);

int main() {

	ds_bmp my_map;
	my_map = create_from_pixel_data("My Code2.bmp", "Libraries.tar");
	//print_array(my_map);
	//printf("======\n");
	//bmp_draw_line(my_map, 5, 0, 45, 0, 0, 0, 0);
	//bmp_gradient(my_map, 0, 0, 0, 0, 0, 255, MODE_ADD);
	//bmp_gradient(my_map, 0, 0, 0, 255, 0, 0, MODE_SUB);
	//bmp_fill(my_map, 0, 255, 0);
	//bmp_draw_rectangle(my_map, 10, 20, 40, 30, 0, 255, 0);
	//bmp_draw_ellipse(my_map, 1, 25, 99, 30, 0, 0, 255);
	//print_array(my_map);

	bmp_write(my_map, TRUE);

	delete_bmp(my_map);

	return 0;

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
