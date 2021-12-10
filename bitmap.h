#ifndef bitmap_h
#define bitmap_h

#include "FileInfo.h"


void generateBitmapImage (unsigned char* image, int height, int width, FileInfo fileInfo);

unsigned char* createBitmapFileHeader(int height, int stride, FileInfo fileInfo);

unsigned char* createBitmapInfoHeader(int height, int width, FileInfo fileInfo);


#endif