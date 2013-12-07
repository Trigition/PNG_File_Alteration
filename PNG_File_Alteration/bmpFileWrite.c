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

//Dumps generated bitmap into file
//Returns file pointer on SUCCESS
//Returns NULL on FAIL
FILE *bmpBottom(char *header) {
    FILE *newFile = NULL;
    int i;
    unsigned int expectFileSize;
    return newFile;
}

int checkHeaderValidity(char *header) {
    int i;
    if (header[0] != 'B' && header[1] != 'M')
    {
        return 0;
    }
    return 1;
}