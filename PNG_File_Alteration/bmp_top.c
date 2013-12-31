#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp_header.h"
#include "bmp_top.h"
#include "bmpFileWrite.h"
#include <math.h>

struct ds_bmp_sentinel {
	unsigned long width, height; //how many pixels
	unsigned char ***pixel_list; //actual 3d array of pixels
	char *name; //name of the file to create
};

ds_bmp create_bmp(char const *filename, unsigned long w, unsigned long h) {
	ds_bmp my_bmp;
	unsigned long i,j;

	//make our sentinel and reserve (and copy in) our name
	my_bmp = malloc(sizeof(struct ds_bmp_sentinel));
	my_bmp->name = malloc(sizeof(char) * (1 + strlen(filename)));
	strncpy(my_bmp->name, filename, strlen(filename) + 1);
	*(my_bmp->name + strlen(filename)) = '\0';

	//set up width and height
	my_bmp->width = w;
	my_bmp->height = h;

	//create 3d array
	my_bmp->pixel_list = malloc(sizeof(char **) * w);
	for (i = 0; i < w; i++) {
		//for each column, we have a row we have to make
		my_bmp->pixel_list[i] = malloc(sizeof(char *) * h);
		for (j = 0; j < h; j++) {
			my_bmp->pixel_list[i][j] = malloc(sizeof(unsigned char) * 3);
			my_bmp->pixel_list[i][j][RED] = 0;
			my_bmp->pixel_list[i][j][GREEN] = 0;
			my_bmp->pixel_list[i][j][BLUE] = 0;
		}
	}

	return my_bmp;
}

ds_bmp create_bmp_ext(char const *filename, unsigned long w, unsigned long h, unsigned char red, unsigned char green, unsigned char blue) {
	ds_bmp my_bmp;
	unsigned long i,j;

	//make our sentinel and reserve (and copy in) our name
	my_bmp = malloc(sizeof(struct ds_bmp_sentinel));
	my_bmp->name = malloc(sizeof(char) * (1 + strlen(filename)));
	strncpy(my_bmp->name, filename, strlen(filename) + 1);
	*(my_bmp->name + strlen(filename)) = '\0';

	//set up width and height
	my_bmp->width = w;
	my_bmp->height = h;

	//create 3d array
	my_bmp->pixel_list = malloc(sizeof(char **) * w);
	for (i = 0; i < w; i++) {
		//for each column, we have a row we have to make
		my_bmp->pixel_list[i] = malloc(sizeof(char *) * h);
		for (j = 0; j < h; j++) {
			my_bmp->pixel_list[i][j] = malloc(sizeof(unsigned char) * 3);
			my_bmp->pixel_list[i][j][RED] = red;
			my_bmp->pixel_list[i][j][GREEN] = green;
			my_bmp->pixel_list[i][j][BLUE] = blue;
		}
	}

	return my_bmp;
}

void delete_bmp(ds_bmp my_bmp) {
	unsigned long i, j;
	for (i = 0; i < my_bmp->width; i++) {
		for (j = 0; j < my_bmp->height; j++) {
			free(my_bmp->pixel_list[i][j]);
		}
		free(my_bmp->pixel_list[i]);
	}
	free(my_bmp->pixel_list);
	//free(my_bmp->name);//willy frees in the ocean
	free(my_bmp); //:'(
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

unsigned char ***get_pixels(ds_bmp a) {
	return a->pixel_list;
}


void set_pixel(ds_bmp map, unsigned long x, unsigned long y, unsigned char red, unsigned char green, unsigned char blue) {
	map->pixel_list[x][y][RED] = red;
	map->pixel_list[x][y][GREEN] = green;
	map->pixel_list[x][y][BLUE] = blue;
}

void add_pixel(ds_bmp map, unsigned long x, unsigned long y, unsigned char red, unsigned char green, unsigned char blue) {
	map->pixel_list[x][y][RED] += red;
	map->pixel_list[x][y][GREEN] += green;
	map->pixel_list[x][y][BLUE] += blue;
}

void sub_pixel(ds_bmp map, unsigned long x, unsigned long y, unsigned char red, unsigned char green, unsigned char blue) {
	map->pixel_list[x][y][RED] -= red;
	map->pixel_list[x][y][GREEN] -= green;
	map->pixel_list[x][y][BLUE] -= blue;
}

unsigned char pixel_get_red(ds_bmp map, unsigned long x, unsigned long y) {
	return map->pixel_list[x][y][RED];
}

unsigned char pixel_get_green(ds_bmp map, unsigned long x, unsigned long y) {
	return map->pixel_list[x][y][GREEN];
}

unsigned char pixel_get_blue(ds_bmp map, unsigned long x, unsigned long y) {
	return map->pixel_list[x][y][BLUE];
}



void bmp_gradient(ds_bmp map, unsigned char red_start, unsigned char green_start, unsigned char blue_start, unsigned char red_end, unsigned char green_end, unsigned char blue_end, unsigned char mode) {
	double dr, dg, db;
	unsigned long i, j;
	dr = (double) (red_end - red_start);
	dg = (double) (green_end - green_start);
	db = (double) (blue_end - blue_start);

	dr = dr/(map->width - 1); //dr has how much each pixel should change in red value
	dg = dg/(map->width - 1);
	db = db/(map->width - 1);

	if (red_end != 0 && red_start == 0 && mode != MODE_ADD)
        printf("Warning! Setting the starting color to 0 and using either sub or set modes causes a tearing error!\n");
	if (green_end != 0 && green_start == 0 && mode != MODE_ADD)
        printf("Warning! Setting the starting color to 0 and using either sub or set modes causes a tearing error!\n");
	if (blue_end != 0 && blue_start == 0 && mode != MODE_ADD)
        printf("Warning! Setting the starting color to 0 and using either sub or set modes causes a tearing error!\n");


	for (i = 0; i < map->width; i++)
	for (j = 0; j < map->height; j++) {
		if (mode == MODE_ADD) {
			map->pixel_list[i][j][RED] += red_start + (i*dr);
			map->pixel_list[i][j][GREEN] += green_start + (i*dg);
			map->pixel_list[i][j][BLUE] += blue_start + (i*db);
		}
		else if (mode == MODE_SUB) {
			map->pixel_list[i][j][RED] -= red_start + (i*dr);
			map->pixel_list[i][j][GREEN] -= green_start + (i*dg);
			map->pixel_list[i][j][BLUE] -= blue_start + (i*db);
		}
		else { //assume set or mode is unrecognized
			(map->pixel_list[i][j][RED]) = (unsigned char) (red_start + (i*dr));
			(map->pixel_list[i][j][GREEN]) = (unsigned char) (green_start + (i*dg));
			(map->pixel_list[i][j][BLUE]) = (unsigned char) (blue_start + (i*db));
		}
	}
}

void bmp_draw_line(ds_bmp map, unsigned long start_x, unsigned long start_y, unsigned long end_x, unsigned long end_y, signed char red, signed char green, signed char blue) {
	/*
	gets slope of line. starts at start_x/y and goes to end_x/y. width of 3
	*/
	double dx, dy, y, ymax; //y has to be double because decimals :(
	unsigned long x;
	if (end_x < start_x) {
		x = end_x;
		end_x = start_x;
		start_x = x;
	}
	if (end_y < start_y) {
		y = (double) end_y;
		end_y = start_y;
		start_y = (unsigned long) y;
	}

	dx = end_x-start_x;
	dy = end_y-start_y;

	//we need one variable to be 0. we choose y
	dy = dy/max_ul(dx, 1);
	dx = 1; //dx/dx

	y = start_y;
	printf("Dx: %lf      Dy: %lf\n", dx, dy);
	for (x = start_x; x <= end_x; x++) {
		ymax = y+dy;
		if (x >= map->width || x == -1)
			continue;
		//printf("New Row\nymax = %lf\n", ymax);
		do {
			if (y == -1 || y >= map->height) {
				y = min_d(y+1, ymax);
				continue;
			}


			//middle pixel
			map->pixel_list[x][(unsigned long) y][RED] = red;
			map->pixel_list[x][(unsigned long) y][GREEN] = green;
			map->pixel_list[x][(unsigned long) y][BLUE] = blue;

			//top pixel
			if (y-1 >= 0) {
				map->pixel_list[x][(unsigned long) (y-1)][RED] = red;
				map->pixel_list[x][(unsigned long) (y-1)][GREEN] = green;
				map->pixel_list[x][(unsigned long) (y-1)][BLUE] = blue;
			}

			//bottom pixel
			if (y+1 < map->height) {
				map->pixel_list[x][(unsigned long) (y+1)][RED] = red;
				map->pixel_list[x][(unsigned long) (y+1)][GREEN] = green;
				map->pixel_list[x][(unsigned long) (y+1)][BLUE] = blue;
			}

			//left pixel
			if (x-1 >= 0) {
				map->pixel_list[x-1][(unsigned long) y][RED] = red;
				map->pixel_list[x-1][(unsigned long) y][GREEN] = green;
				map->pixel_list[x-1][(unsigned long) y][BLUE] = blue;
			}

			//right pixel
			if (x+1 < map->width) {
				map->pixel_list[x+1][(unsigned long) y][RED] = red;
				map->pixel_list[x+1][(unsigned long) y][GREEN] = green;
				map->pixel_list[x+1][(unsigned long) y][BLUE] = blue;
			}

			y = min_d(y+1, ymax);
		} while (y < ymax);
	}
}

void bmp_set_name(ds_bmp map, char const *filename) {
	free(map->name);
	map->name = malloc(sizeof(char) * (1 + strlen(filename)));
	strcpy(map->name, filename);
}

void bmp_write(ds_bmp map, unsigned char debug_switch) {
	FILE *result;

	result = bmpBottom(map, debug_switch);

	if (result==NULL)
		printf("There has been an error writing to the file!\nPlease make certain the file doesn't already exist, or\nyou have permission to overwrite it!\n");

	fclose(result);

}

void bmp_fill(ds_bmp map, unsigned char red, unsigned char green, unsigned char blue) {
	unsigned long w, h, i, j;
	w = map->width;
	h = map->height;
	for (i = 0; i < w; i++)
	for (j = 0; j < h; j++) {
		map->pixel_list[i][j][RED] = red;
		map->pixel_list[i][j][GREEN] = green;
		map->pixel_list[i][j][BLUE] = blue;
	}
}

void bmp_draw_rectangle(ds_bmp map, unsigned long start_x, unsigned long start_y, unsigned long end_x, unsigned long end_y, unsigned char red, unsigned char green, unsigned char blue) {
	unsigned long i, j;

	if (start_x > end_x) {
		i = start_x;
		start_x = end_x;
		end_x = i;
	}
	if (start_y > end_y) {
		i = start_y;
		start_y = end_y;
		end_y = i;
	}

	for (i = start_x; i <= end_x && i < map->width; i++)
	for (j = start_y; j <= end_y && j < map->height; j++) {
		map->pixel_list[i][j][RED] = red;
		map->pixel_list[i][j][GREEN] = green;
		map->pixel_list[i][j][BLUE] = blue;
	}
}

void bmp_draw_ellipse(ds_bmp map, unsigned long start_x, unsigned long start_y, unsigned long end_x, unsigned long end_y, unsigned char red, unsigned char green, unsigned char blue) {
	unsigned long i, w, h, r, cx, cy;
	signed long ymax, ymin, j;
	double x, y;

	if (start_x > end_x) {
		i = start_x;
		start_x = end_x;
		end_x = i;
	}
	if (start_y > end_y) {
		i = start_y;
		start_y = end_y;
		end_y = i;
	}

	if (end_x >= map->width)
		end_x = (map->width)-1;
	if (end_y >= map->height)
		end_y = (map->height)-1;

	w = end_x - start_x;
	h = end_y - start_y;
	cx = start_x + (w/2); //center x
	cy = start_y + (h/2); //center y
	if (w > h) {
		y = h/w;
		x = 1.0;
		r = h/2;
	}
	else {
		x = h/w;
		y=1.0;
		r = w/2;
	}
	printf("start_x=%lu   end_x=%lu\n", start_x, end_x);
	//r^2 = *x(x^2) + *y(y^2)
	for (i = start_x; i <= end_x; i++) {
		ymax = sqrt((pow(r, 2) - (x)*((i-cx) * (i-cx)))/y);
		//ymax = (r^2 - a(x^2))b
		//r^2 = ax^2+by^2
		ymin = -ymax;
		printf("r=%lu   ymax=%ld   ymin=%ld\n", r, ymax, ymin);
		for (j = ymin; j <= ymax; j++) {
			//j is y position without offset of center
			map->pixel_list[i][j+cy][RED] = red;
			map->pixel_list[i][j+cy][GREEN] = green;
			map->pixel_list[i][j+cy][BLUE] = blue;
		}
	}


}




double min_d(double a, double b) {
	if (a <= b)
		return a;
	return b;
}

unsigned long min_ul(unsigned long a, unsigned long b) {
	if (a <= b)
		return a;
	return b;
}

unsigned long max_ul(unsigned long a, unsigned long b) {
	if (a >= b)
		return a;
	return b;
}
