
#include <stdio.h>

#include "bitmap.h"
#include "FileInfo.h"


void generateBitmapImage (unsigned char* image, int height, int width, FileInfo fileInfo)
{
    int widthInBytes = width * fileInfo.BytesPerPixel;

    unsigned char padding[3] = {0, 0, 0};
    int paddingSize = (4 - (widthInBytes) % 4) % 4;

    int stride = (widthInBytes) + paddingSize;

    unsigned char* fileHeader = createBitmapFileHeader(height, stride, fileInfo);
    fwrite(fileHeader, 1, fileInfo.FileHeaderSize, fileInfo.File);

    unsigned char* infoHeader = createBitmapInfoHeader(height, width, fileInfo);
    fwrite(infoHeader, 1, fileInfo.InfoHeaderSize, fileInfo.File);

    int i;
    for (i = 0; i < height; i++) {
        fwrite(image + (i*widthInBytes), fileInfo.BytesPerPixel, width, fileInfo.File);
        fwrite(padding, 1, paddingSize, fileInfo.File);
    }

    fclose(fileInfo.File);
}


unsigned char* createBitmapFileHeader (int height, int stride, FileInfo fileInfo)
{
    int fileSize = fileInfo.FileHeaderSize + fileInfo.InfoHeaderSize + (stride * height);

    static unsigned char fileHeader[] = {
        0,0,     /// signature
        0,0,0,0, /// image file size in bytes
        0,0,0,0, /// reserved
        0,0,0,0, /// start of pixel array
    };

    fileHeader[ 0] = (unsigned char)('B');
    fileHeader[ 1] = (unsigned char)('M');
    fileHeader[ 2] = (unsigned char)(fileSize      );
    fileHeader[ 3] = (unsigned char)(fileSize >>  8);
    fileHeader[ 4] = (unsigned char)(fileSize >> 16);
    fileHeader[ 5] = (unsigned char)(fileSize >> 24);
    fileHeader[10] = (unsigned char)(fileInfo.FileHeaderSize + fileInfo.InfoHeaderSize);

    return fileHeader;
}


unsigned char* createBitmapInfoHeader (int height, int width, FileInfo fileInfo)
{
    static unsigned char infoHeader[] = {
        0,0,0,0, /// header size
        0,0,0,0, /// image width
        0,0,0,0, /// image height
        0,0,     /// number of color planes
        0,0,     /// bits per pixel
        0,0,0,0, /// compression
        0,0,0,0, /// image size
        0,0,0,0, /// horizontal resolution
        0,0,0,0, /// vertical resolution
        0,0,0,0, /// colors in color table
        0,0,0,0, /// important color count
    };

    infoHeader[ 0] = (unsigned char)(fileInfo.FileHeaderSize);
    infoHeader[ 4] = (unsigned char)(width      );
    infoHeader[ 5] = (unsigned char)(width >>  8);
    infoHeader[ 6] = (unsigned char)(width >> 16);
    infoHeader[ 7] = (unsigned char)(width >> 24);
    infoHeader[ 8] = (unsigned char)(height      );
    infoHeader[ 9] = (unsigned char)(height >>  8);
    infoHeader[10] = (unsigned char)(height >> 16);
    infoHeader[11] = (unsigned char)(height >> 24);
    infoHeader[12] = (unsigned char)(1);
    infoHeader[14] = (unsigned char)(fileInfo.BytesPerPixel*8);

    return infoHeader;
}

