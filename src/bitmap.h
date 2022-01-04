#ifndef bitmap_h
#define bitmap_h

extern const int BYTES_PER_PIXEL;

extern void generateBitmapImage(unsigned char* image, int height, int width, char* imageFileName);
unsigned char* createBitmapFileHeader(int height, int stride);
unsigned char* createBitmapInfoHeader(int height, int width);

#endif
