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
#include <math.h>
#include "bmpFileWrite.h"
#include "bmp_header.h"

//Dumps generated bitmap into file
//Returns file pointer on SUCCESS
//Returns NULL on FAIL
FILE *bmpBottom(ds_bmp sentinel) {
    FILE *newFile = NULL;
    char *fileName = NULL;
    unsigned long estSize = get_width(sentinel) * get_height(sentinel);
    unsigned long i;
    newFile = fopen(fileName, "w");

    return newFile;
}

//Checks for header validity
//Determines if data is in correct order
//Returns 1 upon SUCCESS
//Returns 0 upon FAIL
int checkHeaderValidity(ds_bmp sentinel) {
    int i;
    char *header = get_name(sentinel);
    unsigned long bmpHeight = get_height(sentinel);
    unsigned long bmpWidth = get_width(sentinel);
    unsigned long estSize = bmpHeight * bmpWidth * 3; //Height * Width * byte size per pixel
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


char *generateFileHeader(unsigned long arraySize) {
    unsigned int i;
    char *header = NULL;
    unsigned long fileSize = 54 + pow(2, BPP) + arraySize*3;
    header = malloc(sizeof(char) * fileSize);
    
    // ===FILE HEADER===//
    
    //bmp signature
    header[0] = 'B';
    header[1] = 'M';
    
    //write filesize
    for (i = 2; i < 6; i++)
    {
        //Insert filesize write algorithm here
    }
    //Generate reserved space set to 0 by default
    for (; i < 10; i++)
    {
        header[i] = 0;
    }
    //===BITMAP HEADER===//
}