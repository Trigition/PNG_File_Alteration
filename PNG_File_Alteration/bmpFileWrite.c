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
    
    
    //Check for what variables need to be defaulted
    if(get_name(sentinel) == NULL)
    {
        fileName = defaultFileNameWrite();
        if (fileName == NULL) {
            printf("ERROR: Default filename creation failed\n");
        }
    }
    else
    {
        fileName = get_name(sentinel);
    }
    
    
    char *data = NULL;
    unsigned long estSize = get_width(sentinel) * get_height(sentinel);
    unsigned long i;
    
    newFile = fopen(fileName, "w");
    
    //Generate data array to write to file
    data = generateFileHeader(estSize, get_height(sentinel), get_width(sentinel), (char***)get_pixels(sentinel));
    
    //WRITE TO FILE
    for (i = 0; data[i] != '\n'; i++) {
        fprintf(newFile, "%c", data[i]);
    }
    
    //Free variables which have already been written to file
    free(fileName);
    free(data);
    
    //Return file pointer
    return newFile;
}

//Checks for header validity
//Determines if data is in correct order
//Returns 1 upon SUCCESS
//Returns 0 upon FAIL
int checkHeaderValidity(ds_bmp sentinel) {
    //int i;
    //char *header = get_name(sentinel);
    //unsigned long bmpHeight = get_height(sentinel);
    //unsigned long bmpWidth = get_width(sentinel);
    //unsigned long estSize = bmpHeight * bmpWidth * 3; //Height * Width * byte size per pixel
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


char *generateFileHeader(unsigned long arraySize, unsigned long height, unsigned long width, char ***pixels) {
    
    unsigned int i;
    char *header = NULL;
    unsigned long fileSize = 54 + pow(2, BPP/8) + arraySize*3;
    header = malloc(sizeof(char) * fileSize);
    
    // ===FILE HEADER===//
    
    //bmp signature
    header[0] = 'B';
    header[1] = 'M';
    
    //write filesize
    for (i = 2; i < 6; i++)
    {
        header[i] = fileSize / pow(255, 5 - i);
        fileSize = fileSize % (unsigned long)pow(255, 5 - i);
    }
    //Generate reserved space set to 0 by default
    for (; i < 10; i++)
    {
        header[i] = 0;
    }
    header[10] = 54;
    header[11] = 0;
    header[12] = 0;
    header[13] = 0;
    //===BITMAP HEADER===//
    //header size
    header[14] = 40; //DIB Header size
    header[15] = 0;
    header[16] = 0;
    header[17] = 0;
    //WIDTH
    for (i = 18; i < 22; i++)
    {
        header[i] = width / pow(255, 21 - i);
        width = width % (unsigned long)pow(255, 21 - i);
    }
    //HEIGHT
    for (; i < 26; i++)
    {
        header[i] = height / pow(255, 29 - i);
        height = height % (unsigned long)pow(255, 29 - i);
    }
    //RESERVED FIELD
    header[26] = 1;
    header[27] = 0;
    //Bits per pixel
    header[28] = BPP / 8;
    header[29] = 0;
    //Compression method (Set to 0 for no compression)
    for (i = 30; i < 34; i++)
    {
        header[i] = 0;
    }
    //Size of pixel data
    arraySize *= 3;
    for (; i < 38; i++)
    {
        header[i] = arraySize / pow(255, 37 - i);
        arraySize = arraySize % (unsigned long)pow(255, 37 -i);
    }
    //HORIZONTAL RESOLUTION 2,835 pixels per meter
    header[38] = 0x13;
    header[39] = 0x0B;
    header[40] = 0;
    header[41] = 0;
    //VERTICAL RESOLUTION 2,835 pixels per meter
    header[42] = 0x13;
    header[43] = 0x0B;
    header[44] = 0;
    header[45] = 0;
    // color pallette information
    for (i = 46; i < 50; i++)
    {
        header[i] = 0;
    }
    // # of important colors: 0 means all colors are important
    for (; i < 54; i++)
    {
        header[i] = 0;
    }
    //ENTER PIXEL DATA!!!
        for (int j = 0; j < width; j++)
        {
            for (int k = 0; k < height; k++)
            {
                //Writing color R G B
                for (int l = 0; l < 3; l++) {
                    header[i] = pixels[j][k][l];
                    i++;
                }
            }
        }
    
    header[i] = '\n';
    //RETURN header to copy
    return header;
}