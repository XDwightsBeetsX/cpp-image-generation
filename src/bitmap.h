#ifndef bitmap_h
#define bitmap_h


extern void generateBitmapImage(unsigned char* image, int height, int width, const char* imageFileName="output.bmp", int bytesPerPixel=3);

unsigned char* createBitmapFileHeader(int height, int stride);

unsigned char* createBitmapInfoHeader(int height, int width, int bytesPerPixel=3);


#endif
