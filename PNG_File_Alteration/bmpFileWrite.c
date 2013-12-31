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
//ADDED debug_switch, WHICH TURNS ON AND OFF DEBUGGING MESSAGES (12/30/2013 8:48pm  - Sm)
FILE *bmpBottom(ds_bmp sentinel, unsigned char debug_switch) {
    FILE *newFile = NULL;
    char *fileName = NULL;


    //Check for what variables need to be defaulted
    if(get_name(sentinel) == NULL)
    {
        printf("ERROR (bmpBottom): No filename given. Defaulting to: ");
        fileName = defaultFileNameWrite();
        printf("%s\n", fileName);
        if (fileName == NULL) {
            printf("ERROR (bmpBottom): Default filename creation failed\n");
        }
    }
    else
    {
        fileName = get_name(sentinel);
        if (debug_switch == TRUE)
            printf("bmpBottom: Using filename: %s\n", fileName);
    }


    char *data = NULL;
    unsigned long estSize = get_width(sentinel) * get_height(sentinel);
    unsigned long fileSize = 54 + (get_height(sentinel) * get_width(sentinel) * 3) + get_height(sentinel)*(get_width(sentinel) % 4);
    unsigned long i;

    if (debug_switch == TRUE)
            printf("Writing file...\n");
    newFile = fopen(fileName, "w");
    if (newFile == NULL)
    {
        printf("ERROR (bmpBottom): 'fopen' failure\n");
    }
    else {
        if (debug_switch == TRUE)
            printf("bmpBottom: Created file pointer\n");
        }

    //Generate data array to write to file
    if (debug_switch == TRUE)
            printf("bmpBottom: Creating data...\n");
    data = generateFileHeader(estSize, get_height(sentinel), get_width(sentinel), (char***)get_pixels(sentinel), debug_switch);
    if (debug_switch == TRUE)
            printf("Successfully created data\n");

    //WRITE TO FILE
    if (debug_switch == TRUE)
            printf("bmpBottom: Writing data to file...\n");
    for (i = 0; i < fileSize; i++) {
        fprintf(newFile, "%c", data[i]);
    }

    if (debug_switch == TRUE)
            printf("bmpBottom: Wrote to file!\n");
    //Free variables which have already been written to file
    free(fileName);
    free(data);
    if (debug_switch == TRUE)
            printf("bmpBottom: Freed variables. Returning\n");
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


char *generateFileHeader(unsigned long arraySize, unsigned long height, unsigned long width, char ***pixels, unsigned char debug_switch) {

    unsigned int i;
    char *header = NULL;
    char tmp[4];
    unsigned long fileSize = 54 + (height * width * 3) + height*(width % 4);
    unsigned long pixelW = width;
    unsigned long pixelH = height;
    if (debug_switch == TRUE) {
        printf("File size: %lu\n", fileSize);
        printf("Width size: %lu\n", pixelW);
        printf("Height size: %lu\n", pixelH);
    }
    header = malloc(sizeof(char) * fileSize);

    // ===FILE HEADER=== //
    if (debug_switch == TRUE) {
            printf("generateFileHeader: Starting BITMAP HEADER\n");
    //bmp signature
    printf("generateFileHeader: Creating 'BM' header...\n");
    }
    header[0] = 'B';
    header[1] = 'M';
    if (debug_switch == TRUE)
            printf("generateFileHeader: Created 'BM' header\n");

    // ===FILE SIZE=== //
    if (debug_switch == TRUE)
            printf("generateFileHeader: Creating filesize\n");
    for (i = 2; i < 6; i++)
    {
        tmp[i - 2] = fileSize / pow(255, 5 - i);
        if (debug_switch == TRUE)
            printf("\tgenerateFileHeader: DEBUG; %u\n", tmp[i - 2]);
        fileSize = fileSize % (unsigned long)pow(255, 5 - i);
    }

    for (i = 2; i < 6; i++)
    {
        header[i] = tmp[5 - i];
        //printf("\tgenerateFileHeader: Placed %u\n", header[i]);
    }

    if (debug_switch == TRUE)
            printf("generateFileHeader: Created filesize\n");
    // ===RESERVED SPACE=== ///

    if (debug_switch == TRUE)
            printf("generateFileheader: Creating reserved space\n");
    for (i = 6; i < 10; i++)
    {
        header[i] = 0;
    }
    if (debug_switch == TRUE) {
            printf("generateFileHeader: Created reserved space\n");

            printf("generateFileHeader: Creating PIXEL DATA offset\n");
    }
    header[10] = 54;
    header[11] = 0;
    header[12] = 0;
    header[13] = 0;
    if (debug_switch == TRUE) {
        printf("generateFileHeader: Created PIXEL DATA offset\n");

        printf("generateFileHeader: Finished FILE HEADER\n");
    }
    //===BITMAP HEADER===//
    //header size
    if (debug_switch == TRUE) {
        printf("generateFileHeader: Starting BITMAP HEADER\n");

        printf("generateFileHeader: Creating DIB Header size\n");
    }
    header[14] = 40; //DIB Header size
    header[15] = 0;
    header[16] = 0;
    header[17] = 0;
    if (debug_switch == TRUE)
            printf("generateFileHeader: Created DIB Header size\n");

    //WIDTH
    if (debug_switch == TRUE)
            printf("generateFileHeader: Creating WIDTH\n");
    for (i = 18; i < 22; i++)
    {
        tmp[i - 18] = width / pow(255, 21 - i);
        width = width % (unsigned long)pow(255, 21 - i);
    }

    for (i = 18; i < 22; i++)
    {
        header[i] = tmp[21 - i];
        //printf("\tgenerateFileHeader: placed %u at header[%u]\n", header[i], i);
    }
    if (debug_switch == TRUE)
            printf("generateFileHeader: Created WIDTH\n");

    //HEIGHT
    if (debug_switch == TRUE)
            printf("generateFileHeader: Creating HEIGHT\n");
    for (i = 22; i < 26; i++)
    {
        tmp[i - 22] = height / pow(255, 25 - i);
        height = height % (unsigned long)pow(255, 25 - i);
    }

    for (i = 22; i < 26; i++)
    {
        header[i] = tmp[25 - i];
        //printf("generateFileHeader: placed %u at header %u\n", header[i], i);
    }
    if (debug_switch == TRUE)
            printf("generateFileHeader: Created HEIGHT\n");

    //RESERVED FIELD
    if (debug_switch == TRUE)
            printf("generateFileHeader: Creating Reserved field\n");
    header[26] = 1;
    header[27] = 0;
    if (debug_switch == TRUE)
            printf("generateFileHeader: Created Reserved field\n");
    //Bits per pixel
    if (debug_switch == TRUE)
            printf("generateFileHeader: Creating BPP\n");
    header[28] = BPP;
    header[29] = 0;
    if (debug_switch == TRUE)
            printf("generateFileHeader: Created BPP\n");

    //Compression method (Set to 0 for no compression)
    if (debug_switch == TRUE)
            printf("generateFileHeader: Creating compression method\n");
    for (i = 30; i < 34; i++)
    {
        header[i] = 0;
    }
    if (debug_switch == TRUE)
            printf("generateFileHeader: Created compression method\n");

    //Size of pixel data
    if (debug_switch == TRUE)
            printf("generateFileHeader: Creating array size\n");
    arraySize *= 3;
    for (i = 34; i < 38; i++)
    {
        tmp[i - 34] = arraySize / pow(255, 37 - i);
        arraySize = arraySize % (unsigned long)pow(255, 37 -i);
    }
    for (i = 34; i < 38; i++) {
        header[i] = tmp[37 - i];
        //printf("\tgenerateFileHeader: Placed %u\n", header[i]);
    }
    if (debug_switch == TRUE)
            printf("generateFileHeader: Created array size\n");

    //HORIZONTAL RESOLUTION 2,835 pixels per meter
    if (debug_switch == TRUE)
            printf("generateFileHeader: Creating HORIZ resolution\n");
    header[38] = 0x13;
    header[39] = 30;
    header[40] = 0;
    header[41] = 0;
    if (debug_switch == TRUE)
            printf("generateFileHeader: Creating HORIZ resolution\n");

    //VERTICAL RESOLUTION 2,835 pixels per meter
    if (debug_switch == TRUE)
            printf("generateFileHeader: Creating VERT resolution\n");
    header[42] = 0x13;
    header[43] = 30;
    header[44] = 0;
    header[45] = 0;
    if (debug_switch == TRUE)
            printf("generateFileHeader: Created VERT resolution\n");

    // color pallette information
    if (debug_switch == TRUE)
            printf("generateFileHeader: Creating color pallette info\n");
    for (i = 46; i < 50; i++)
    {
        header[i] = 0;
    }
    if (debug_switch == TRUE)
            printf("generateFileHeader: Created color pallette info\n");

    // # of important colors: 0 means all colors are important
    if (debug_switch == TRUE)
            printf("generateFileHeader: Creating 'important color field'. \n\tAll colors important, defaulting to 0\n");
    for (i = 50; i < 54; i++)
    {
        header[i] = 0;
    }
    if (debug_switch == TRUE)
            printf("generateFileHeader: Created 'important color field\n");

    //ENTER PIXEL DATA!!!
    if (debug_switch == TRUE)
            printf("generateFileHeader: Creating pixel data\n");
    i = 54;
    unsigned long j;
    unsigned long k;
    unsigned long l;
    for (j = 0; j < pixelH; j++)
        {
            for (k = 0; k < pixelW; k++)
                {
                        //Writing color R G B
                        for (l = 0; l < 3; l++)
                            {
                                //printf("\t\tAt index %d\n", i);
                                header[i] = pixels[k][j][l];
                                i++;
                            }
                }
            while ((i - 54) % 4 != 0)
                {
                    header[i] = i;
                    i++;
                }
        }
    if (debug_switch == TRUE)
            printf("generateFileHeader: Created pixel data\n");

    if (debug_switch == TRUE)
            printf("generateFileHeader: Creating end of buffer\n");
    //header[i] = 33;
    //RETURN header to copy
    if (debug_switch == TRUE)
            printf("generateFileHeader: Returning\n");
    return header;
}
