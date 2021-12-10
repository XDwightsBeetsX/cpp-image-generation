#include <stdio.h>
#include <iostream>

#include "bitmap.h"
#include "FileInfo.h"

using namespace std;


int main () {
    cout << "running bitmap generator..." << endl;

    // .bmp params
    const int BYTES_PER_PIXEL = 3;
    const int FILE_HEADER_SIZE = 14;
    const int INFO_HEADER_SIZE = 40;

    // image params
    const int height = 361;
    const int width = 867;
    unsigned char image[height][width][BYTES_PER_PIXEL];

    // gets passed around carrying the .bmp params
    // useful for writing to the file and checking sizes
    FileInfo fileInfo = FileInfo((char*)"output.bmp", BYTES_PER_PIXEL, FILE_HEADER_SIZE, INFO_HEADER_SIZE);

    int i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            image[i][j][2] = (unsigned char) ( i * 255 / height );             ///red
            image[i][j][1] = (unsigned char) ( j * 255 / width );              ///green
            image[i][j][0] = (unsigned char) ( (i+j) * 255 / (height+width) ); ///blue
        }
    }

    generateBitmapImage((unsigned char*) image, height, width, fileInfo);
    cout << "done." << endl;
}
