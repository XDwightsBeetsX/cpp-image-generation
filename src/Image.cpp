#include <string>
#include <cstring>

#include "Image.h"


using namespace std;


// =========================== constructors ===========================
Image::Image() {
    Width = 10;
    Height = 10;
    Filename = (char*) "output/output.bmp";
    
    int bpp = 3;
    BytesPerPixel = bpp;

    Data = vector<vector<vector<int>>>(Height, vector<vector<int>>(Width, vector<int>(bpp, 0)));
}

Image::Image(int height, int width, const char* filename) {
    Height = height;
    Width = width;
    Filename = filename;
    
    int bpp = 3;
    BytesPerPixel = bpp;

    Data = vector<vector<vector<int>>>(height, vector<vector<int>>(width, vector<int>(bpp, 0)));
}


// ============================ operations ============================
void Image::toWhite() {
    for (int row = 0; row < Height; row++) {
        for (int col = 0; col < Width; col++) {
            for (int i = 0; i < BytesPerPixel; i++) {
                Data[row][col][i] = 255;
            }
        }
    }
}

void Image::toBlack() {
    for (int row = 0; row < Height; row++) {
        for (int col = 0; col < Width; col++) {
            for (int i = 0; i < BytesPerPixel; i++) {
                Data[row][col][i] = 0;
            }
        }
    }
}


// ============================== output ==============================
void Image::showData() {
    for (int row = 0; row < Height; row++) {
        for (int col = 0; col < Width; col++) {
            cout << "(";
            for (int i = 0; i < BytesPerPixel; i++) {
                cout << Data[row][col][i];
                
                if (i != BytesPerPixel - 1)
                    cout << ",";
            }
            cout << ") ";
        }
        cout << endl;
    }
}

void Image::writeToFile() {
    // set vars
    int widthInBytes = Width * BytesPerPixel;
    unsigned char padding[3] = {0, 0, 0};
    int paddingSize = (4 - (widthInBytes) % 4) % 4;
    int stride = widthInBytes + paddingSize;
    int fileSize = FileHeaderSize + InfoHeaderSize + (stride * Height);

    // copy data to char array
    unsigned char dataChar[Height][Width][BytesPerPixel];  // [B, G, R] (little endian)
    for (int row = 0; row < Height; row++) {
        for (int col = 0; col < Width; col++) {
            for (int i = 0; i < BytesPerPixel; i++) {
                dataChar[row][col][i] = Data[row][col][i];
            }
        }
    }

    // FILE HEADER
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
    fileHeader[10] = (unsigned char)(FileHeaderSize + InfoHeaderSize);

    // INFO HEADER
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

    infoHeader[ 0] = (unsigned char)(InfoHeaderSize);
    infoHeader[ 4] = (unsigned char)(Width       );
    infoHeader[ 5] = (unsigned char)(Width  >>  8);
    infoHeader[ 6] = (unsigned char)(Width  >> 16);
    infoHeader[ 7] = (unsigned char)(Width  >> 24);
    infoHeader[ 8] = (unsigned char)(Height      );
    infoHeader[ 9] = (unsigned char)(Height >>  8);
    infoHeader[10] = (unsigned char)(Height >> 16);
    infoHeader[11] = (unsigned char)(Height >> 24);
    infoHeader[12] = (unsigned char)(1);
    infoHeader[14] = (unsigned char)(BytesPerPixel*8);

    // FILE WRITING
    cout << cProgram << cFile << "writing to file '" << Filename << "'..." << endl;
    FILE* file = fopen(Filename, "wb");

    cout << cProgram << cFile << "writing File Header..." << endl;
    fwrite(fileHeader, 1, FileHeaderSize, file);
    cout << cProgram << cFile << "writing Info Header..." << endl;
    fwrite(infoHeader, 1, InfoHeaderSize, file);
    cout << cProgram << cFile << "writing image data..." << endl;
    for (int i = 0; i < Height; i++) {
        fwrite((unsigned char*) dataChar + (i*widthInBytes), BytesPerPixel, Width, file);
        fwrite(padding, 1, paddingSize, file);
    }

    fclose(file);
    cout << "done." << endl;
}
