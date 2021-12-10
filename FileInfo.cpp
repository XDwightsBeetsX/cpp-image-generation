#include "FileInfo.h"

#include <iostream>


// =================================
// ======== constructors ===========
// =================================
FileInfo::FileInfo() {
    char* filename = (char*)"bitmap_image.bmp";
    
    FileName = filename;
    BytesPerPixel = 3;  // R, G, B
    FileHeaderSize = 1;
    InfoHeaderSize = 3;
    File = fopen(filename, "wb");
}


FileInfo::FileInfo(char* fileName=(char*)"", int bytesPerPixel=3, int fileHeaderSize=1, int infoHeaderSize=1) {
    FileName = fileName;
    BytesPerPixel = bytesPerPixel;
    FileHeaderSize = fileHeaderSize;
    InfoHeaderSize = infoHeaderSize;
    File = fopen(fileName, "wb");
}
