#include <stdio.h>
#include "bmp_header.h"
#include "bmp_top.h"

int main() {
	
	ds_bmp my_map;
	my_map = create_bmp("My Map", 10, 10);
	delete_bmp(my_map);
	
	return 0;
	
}
