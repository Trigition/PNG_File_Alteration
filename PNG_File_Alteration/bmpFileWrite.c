//
//  bmpHeaderGen.c
//  PNG_File_Alteration
//
//  Created by William Fong on 12/6/13.
//  Copyright (c) 2013 William Fong. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bmpFileWrite.h"
#include "bmp_header.h"

//Dumps generated bitmap into file
//Returns file pointer on SUCCESS
//Returns NULL on FAIL
FILE *bmpBottom(ds_png *sentinel) {
    FILE *newFile = NULL;
    char *fileName = NULL;
    newFile = fopen(fileName, "w");
    return newFile;
}

//Checks for header validity
//Determines if data is in correct order
//Returns 1 upon SUCCESS
//Returns 0 upon FAIL
int checkHeaderValidity(ds_png *sentinel) {
    int i;
    char *header = sentinel->name;
    if (header[0] != 'B' && header[1] != 'M')
    {
        printf("Error: expected first 2 bytes to the 'B' and 'M' but got '%c' and '%c'instead\n", header[0], header[1]);
        return 0;
    }
    return 1;
}

//If no filename was given, generate systemtime and put in return string
char *defaultFileNameWrite() {
    time_t date;
    char *buf = NULL;
    time(&date);
    struct tm* tm_info = localtime(&date);
    buf = malloc(sizeof(char) *25);
    strftime(buf, 25, "%Y:%m:%d:%H:%m:%S", tm_info);
    puts(buf);
    return buf;
}