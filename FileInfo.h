#ifndef FileInfo_h
#define FileInfo_h

#include <stdio.h>

using namespace std;

struct FileInfo {
    char* FileName;
    FILE* File;

    int BytesPerPixel;
    int FileHeaderSize;
    int InfoHeaderSize;

    FileInfo();
    FileInfo(char* fileName, int bytesPerPixe, int fileHeaderSize, int infoHeaderSize);
};


#endif