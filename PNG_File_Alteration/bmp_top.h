#ifndef __bmp_top_h
#define __bmp_top_h

#define MODE_ADD 0
#define MODE_SET 1
#define MODE_SUB 2

/**
 *Deals with the storing and managing of the bmp;
 **/

//Creates bmp with initial rgb values
ds_bmp create_bmp_ext(char const *name, unsigned long w, unsigned long h, unsigned char red, unsigned char green, unsigned char blue);

/*Accessor Functions*/
unsigned char pixel_get_red(ds_bmp map, unsigned long x, unsigned long y);
unsigned char pixel_get_green(ds_bmp map, unsigned long x, unsigned long y);
unsigned char pixel_get_blue(ds_bmp map, unsigned long x, unsigned long y);

//set_pixel sets rgb values
void set_pixel(ds_bmp map, unsigned long x, unsigned long y, unsigned char red, unsigned char green, unsigned char blue);

//add_pixel adds values red, blue, and green to pixel, just resetting if overflow
void add_pixel(ds_bmp map, unsigned long x, unsigned long y, unsigned char red, unsigned char green, unsigned char blue);

//sub_pixel just subtracts values from rgb channel
void sub_pixel(ds_bmp map, unsigned long x, unsigned long y, unsigned char red, unsigned char green, unsigned char blue);



/*General Drawing Functions*/
//Makes a simple gradient from left to right. mode is MODE_ADD/_SET/_SUB
void bmp_gradient(ds_bmp map, unsigned char red_start, unsigned char green_start, unsigned char blue_start, unsigned char red_end, unsigned char green_end, unsigned char blue_end, char mode);


#endif
