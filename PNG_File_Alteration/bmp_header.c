
struct ds_bmp_sentinel {
	unsigned long size; //how many pixels
	char *pixel_list; //actual 3d array of pixels
	char *name; //name of the file to create
};

unsigned long get_size(ds_bmp a) {
	return a->size;
}

char *get_name(ds_bmp a) {
	return a->name;
}

char *get_pixels(ds_bmp a) {
	return pixel_list;
}
