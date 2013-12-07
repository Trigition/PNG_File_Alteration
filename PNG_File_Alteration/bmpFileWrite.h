//
//  bmpHeaderGen.h
//  PNG_File_Alteration
//
//  Created by William Fong on 12/6/13.
//  Copyright (c) 2013 William Fong. All rights reserved.
//

#ifndef PNG_File_Alteration_bmpHeaderGen_h
#define PNG_File_Alteration_bmpHeaderGen_h

#include "bmp_header.h"

FILE *bmpBottom(ds_png *sentinel); //Function dumps bmp char array to file

int checkHeaderValidity(char *header);

#endif
