#ifndef __bmp_top_h
#define __bmp_top_h

#define MODE_ADD 0
#define MODE_SET 1
#define MODE_SUB 2

/**
 *Deals with the storing and managing of the bmp;
 **/

//Creates bmp with initial rgb values
ds_bmp create_bmp_ext(char const *filename, unsigned long w, unsigned long h, unsigned char red, unsigned char green, unsigned char blue);


/*Writing to file*/
//Writes bmp to file. Uses name passed with creation as filename
void bmp_write(ds_bmp map);

/*Accessor Functions*/
unsigned char pixel_get_red(ds_bmp map, unsigned long x, unsigned long y);
unsigned char pixel_get_green(ds_bmp map, unsigned long x, unsigned long y);
unsigned char pixel_get_blue(ds_bmp map, unsigned long x, unsigned long y);
unsigned long get_width(ds_bmp);
unsigned long get_height(ds_bmp);
void bmp_set_name(ds_bmp map, char const *filename);

//set_pixel sets rgb values
void set_pixel(ds_bmp map, unsigned long x, unsigned long y, unsigned char red, unsigned char green, unsigned char blue);

//add_pixel adds values red, blue, and green to pixel, just resetting if overflow
void add_pixel(ds_bmp map, unsigned long x, unsigned long y, unsigned char red, unsigned char green, unsigned char blue);

//sub_pixel just subtracts values from rgb channel
void sub_pixel(ds_bmp map, unsigned long x, unsigned long y, unsigned char red, unsigned char green, unsigned char blue);



/*General Drawing Functions*/
//Makes a simple gradient from left to right. mode is MODE_ADD/_SET/_SUB
void bmp_gradient(ds_bmp map, unsigned char red_start, unsigned char green_start, unsigned char blue_start, unsigned char red_end, unsigned char green_end, unsigned char blue_end, unsigned char mode);
void bmp_draw_line(ds_bmp map, unsigned long start_x, unsigned long start_y, unsigned long end_x, unsigned long end_y, signed char red, signed char green, signed char blue);
void bmp_draw_ellipse(ds_bmp map, unsigned long start_x, unsigned long start_y, unsigned long end_x, unsigned long end_y, unsigned char red, unsigned char green, unsigned char blue);
void bmp_draw_rectangle(ds_bmp map, unsigned long start_x, unsigned long start_y, unsigned long end_x, unsigned long end_y, unsigned char red, unsigned char green, unsigned char blue);
void bmp_fill(ds_bmp map, unsigned char red, unsigned char green, unsigned char blue);


/*Helper Functions*/
double min_d(double a, double b);
unsigned long min_ul(unsigned long a, unsigned long b);
unsigned long max_ul(unsigned long, unsigned long);

#endif
