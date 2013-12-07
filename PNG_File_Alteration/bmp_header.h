/**
 *Header for both the top and bottom layer of creation. This includes
 *structures used in both processes (such as the bridging ds_bmp structure)
 *as well as functions that can be utilized in both (like a shared library)
 **/

#ifndef __bmp_lib_global_head
#define __bmp_lib_global_head

//Remember that a variable of type ds_bmp is really a pointer to the structure
typedef struct ds_bmp_sentinel *ds_bmp;


/*Create and destroy*/
ds_bmp create_bmp(char const *name, unsigned long w, unsigned long h);
void delete_bmp();

/*Accessors*/
unsigned long get_size(ds_bmp);
char *get_name(ds_bmp);
char **get_pixels(ds_bmp);






#endif
