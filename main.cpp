#include <iostream>
#include <stdio.h>

using namespace std;


int main() {
    cout << "running..." << endl << endl;

    // file paras
    char* filename = (char*) "output.bmp";
    const int height = 100;
    const int width = 100;

    // red, green, blue
    const int BYTES_PER_PIXEL = 3;

    const int FILE_HEADER_SIZE = 14;
    const int INFO_HEADER_SIZE = 40;

    const int rowWidthInBytes = BYTES_PER_PIXEL * width;

    unsigned char padding[3] = {0, 0, 0};
    const int paddingSize = (4 - (rowWidthInBytes) % 4) % 4;

    const int headerSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE;
    const int stride = rowWidthInBytes + paddingSize;
    const int dataSize = stride * height;
    const int fileSize = headerSize + dataSize;

    cout << "fname:     " << filename << endl;
    cout << "width:     " << width << endl;
    cout << "height:    " << height << endl;
    cout << "file size: " << fileSize << endl << endl;

    // fileHeader
    static unsigned char fileHeader[] = {
        0,0,        // signature must be 'BM'
        0,0,0,0,    // image file size in bytes
        0,0,0,0,    // reserved (all 0)
        0,0,0,0,    // start of pixel array
    };

    fileHeader[ 0] = (unsigned char)('B');
    fileHeader[ 1] = (unsigned char)('M');
    fileHeader[ 2] = (unsigned char)(fileSize);
    fileHeader[ 3] = (unsigned char)(fileSize >>  8);   
    fileHeader[ 4] = (unsigned char)(fileSize >> 16);
    fileHeader[ 5] = (unsigned char)(fileSize >> 24);
    fileHeader[10] = (unsigned char)(headerSize);
    

    // infoHeader
    static unsigned char infoHeader[] = {
        0,0,0,0, /// infoHeader size
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

    infoHeader[ 0] = (unsigned char)(INFO_HEADER_SIZE);
    infoHeader[ 4] = (unsigned char)(width       );
    infoHeader[ 5] = (unsigned char)(width  >>  8);
    infoHeader[ 6] = (unsigned char)(width  >> 16);
    infoHeader[ 7] = (unsigned char)(width  >> 24);
    infoHeader[ 8] = (unsigned char)(height      );
    infoHeader[ 9] = (unsigned char)(height >>  8);
    infoHeader[10] = (unsigned char)(height >> 16);
    infoHeader[11] = (unsigned char)(height >> 24);
    infoHeader[12] = (unsigned char)(1);
    infoHeader[14] = (unsigned char)(BYTES_PER_PIXEL*8);


    // write RGB data
    unsigned char image[height][width][BYTES_PER_PIXEL];    // [R, G, B]
    
    for (int row = 0; row < height; row++) {
        bool isBottom = row < (height / 2);

        for (int col = 0; col < width; col++) {    
            if (isBottom) {
                image[row][col][0] = (unsigned char) 0;
                image[row][col][1] = (unsigned char) 0;
                image[row][col][2] = (unsigned char) 255;
            }
            else {
                image[row][col][0] = (unsigned char) 0;
                image[row][col][1] = (unsigned char) 255;
                image[row][col][2] = (unsigned char) 0;
            }
        }
    }


    // write to file
    FILE* imageFile = fopen(filename, "wb");

    cout << "writing headers..." << endl;
    fwrite(fileHeader, 1, FILE_HEADER_SIZE, imageFile);
    fwrite(infoHeader, 1, INFO_HEADER_SIZE, imageFile);
    cout << "done." << endl;

    cout << "writing data..." << endl;
    for (int row = 0; row < height; row++) {
        cout << endl << "row " << row << endl;

        for (int col = 0; col < width; col++) {
            int r = (int) image[row][col][0];
            int g = (int) image[row][col][1];
            int b = (int) image[row][col][2];

            cout << "(" << r << "," << g << "," << b << ") ";
        }
        cout << endl;

        fwrite(image + (row * rowWidthInBytes), BYTES_PER_PIXEL, width, imageFile);
        fwrite(padding, 1, paddingSize, imageFile);
    }
    cout << "done." << endl;

    cout << "saving..." << endl;
    fclose(imageFile);
    cout << "done." << endl;
    
    cout << "image generated at ./" << filename << endl;
    return 0;
}
