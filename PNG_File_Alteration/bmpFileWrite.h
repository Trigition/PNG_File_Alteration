//
//  bmpHeaderGen.h
//  PNG_File_Alteration
//
//  Created by William Fong on 12/6/13.
//  Copyright (c) 2013 William Fong. All rights reserved.
//

#ifndef PNG_File_Alteration_bmpHeaderGen_h
#define PNG_File_Alteration_bmpHeaderGen_h
#define BPP 24//Bits Per Pixel

#include "bmp_header.h"

FILE *bmpBottom(ds_bmp sentinel); //Function dumps bmp char array to file

int checkHeaderValidity(ds_bmp sentinel);  //Validates header COMMENTED OUT. KEEPING FUNCTION IN CASE TO READ IN FILE
char *defaultFileNameWrite();  //If no filename is given, generate one
char *generateFileHeader(unsigned long arraySize, unsigned long height, unsigned long width, char ***pixels);

#endif