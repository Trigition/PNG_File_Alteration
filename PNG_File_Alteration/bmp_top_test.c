#include <stdio.h>
#include "bmp_top.h"
#include "bmp_header.h"

void foo() {
	//n is our int we are storing
	unsigned int n = 650000; //we just give 650000 to prove it works
	char b1, b2, b3, b4;
	
	
	b1 = n / pow(255, 3);
	n = n % pow(255, 3);
	
	b2 = n / pow(255, 2);
	n = n % pow(255, 2);
	
	b3 = n / pow(255, 1);
	n = n % pow(255, 1);
	
	b4 = n;
	
}
