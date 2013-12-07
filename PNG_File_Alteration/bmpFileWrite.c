//
//  bmpHeaderGen.c
//  PNG_File_Alteration
//
//  Created by William Fong on 12/6/13.
//  Copyright (c) 2013 William Fong. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "bmpFileWrite.h"
#include "bmp_header.h"

//Dumps generated bitmap into file
//Returns file pointer on SUCCESS
//Returns NULL on FAIL
FILE *bmpBottom(ds_png *sentinel) {
    FILE *newFile = NULL;
    char *fileName = NULL;
    int i;
    unsigned int expectFileSize;
    newFile = fopen(fileName, "w");
    return newFile;
}

//Checks for header validity
//Determines if data is in correct order
//Returns 1 upon SUCCESS
//Returns 0 upon FAIL
int checkHeaderValidity(char *header) {
    int i;
    if (header[0] != 'B' && header[1] != 'M')
    {
        return 0;
    }
    return 1;
}