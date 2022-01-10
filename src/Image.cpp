#include <string>
#include <cstring>
#include <cmath>
#include <stdexcept>
#include <fstream>

#include "Image.h"


using namespace std;


// =========================== constructors ===========================
Image::Image() {
    Width = 100;
    Height = 100;
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

Image Image::getImageFromFile(const char* filename) {
    ifstream File(filename);

    if (File.is_open()) {
        char line;
        while (File >> line) {
            cout << line << endl;
        }

        File.close();
    }
    else {
        cerr << "[ERROR] - Encountered error reading the file at '" << filename << "'" << endl;
    }

    return Image();
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

void Image::toGradient() {
    cout << cProgram << "generating gradient..." << endl;
    for (int row = 0; row < Height; row++) {
        for (int col = 0; col < Width; col++) {
            Data[row][col][0] = (int) (255 * (double) (Width - col) / Width);
            Data[row][col][1] = (int) (255 * (double) (Height - row) / Height);
            Data[row][col][2] = (int) (255 * (double) (row + col) / (Width + Height));
        }
    }
}

void Image::toGrid(int nrows, int ncols, int lineThickness) {
    cout << cProgram << "generating " << nrows << "x" << ncols << " grid..." << endl;

    int rowHeight = floor((Height-(nrows-1)*lineThickness) / nrows);
    int colWidth = floor((Width-(ncols-1)*lineThickness) / ncols);

    // set rows
    for (int gridRow = 1; gridRow < nrows; gridRow++) {
        int h = gridRow * (rowHeight + lineThickness);
        for (int rowToSet = h-lineThickness; rowToSet < h; rowToSet++) {
            // set line pixels in rowToSet
            for (int col = 0; col < Width; col++)
                setPixel(rowToSet, col, 0, 0, 0);
        }
    }

    // set cols
    for (int gridCol = 1; gridCol < ncols; gridCol++) {
        int w = gridCol * (colWidth + lineThickness);
        for (int colToSet = w-lineThickness; colToSet < w; colToSet++) {
            // set line pixels in colToSet 
            for (int row = 0; row < Height; row++)
                setPixel(row, colToSet, 0, 0, 0);
        }
    }
}

void Image::setPixel(int row, int col, int r, int g, int b) {
    Data[row][col][2] = r;
    Data[row][col][1] = g;
    Data[row][col][0] = b;
}

void Image::invertPixel(int row, int col) {
    for (int i = 0; i < BytesPerPixel; i++) {
        Data[row][col][i] = abs(255 - Data[row][col][i]);
    }
}

void Image::invert() {
    cout << cProgram << "inverting colors..." << endl;
    for (int row = 0; row < Height; row++) {
        for (int col = 0; col < Width; col++) {
            invertPixel(row, col);
        }
    }
}

void Image::toGrayscale() {
    cout << cProgram << "calculating grayscale..." << endl;
    for (int row = 0; row < Height; row++) {
        for (int col = 0; col < Width; col++) {
            int avg = (Data[row][col][0] + Data[row][col][1] + Data[row][col][2]) / 3;
            setPixel(row, col, avg, avg, avg);
        }
    }
}

void Image::normalize() {
    cout << cProgram << "normalizing colors..." << endl;

    // preset min/maxs to be overridden
    int minB, maxB = Data[0][0][0];
    int minG, maxG = Data[0][0][1];
    int minR, maxR = Data[0][0][2];

    // find min/maxs
    for (int row = 0; row < Height; row++) {
        for (int col = 0; col < Width; col++) {
            int b = Data[row][col][0];
            int g = Data[row][col][1];
            int r = Data[row][col][2];

            if (b < minB)
                minB = b;
            if (maxB < b)
                maxB = b;
            if (g < minG)
                minG = g;
            if (maxG < g)
                maxG = g;
            if (r < minR)
                minR = r;
            if (maxR < r)
                maxR = r;
        }
    }

    // multiple vals by the spread (cast to ints)
    for (int row = 0; row < Height; row++) {
        for (int col = 0; col < Width; col++) {
            Data[row][col][0] = (int) (Data[row][col][0] * (double) ((maxB - minB) / 255));
            Data[row][col][1] = (int) (Data[row][col][1] * (double) ((maxG - minG) / 255));
            Data[row][col][2] = (int) (Data[row][col][2] * (double) ((maxR - minR) / 255));
        }
    }
}

void Image::sobel(int T) {
    cout << cProgram << "performing sobel edge detection..." << endl;
    sobelX(T);
    sobelY(T);
}

void Image::sobelX(int T) {
    const int Mx[3][3]= {{-1, 0, 1},
                         {-2, 0, 2},
                         {-1, 0, 1}};
    
    for (int row = 0; row < Height; row++) {
        for (int col = 0; col < Width; col++) {
            // gradient sum
            int sum = 0;

            // Left edge. Won't balance with typical masks.
            if (col == 0) {
                // Top left corner
                if (row == 0) {
                    sum = Data[row  ][col+1][0] * Mx[1][2] +
                          Data[row+1][col+1][0] * Mx[2][2] -
                          Data[row  ][col  ][0];
                }
                // Bottom left corner
                else if (row == Height-1) {
                    sum = Data[row-1][col+1][0] * Mx[0][2] +
                          Data[row  ][col+1][0] * Mx[1][2] -
                          Data[row  ][col  ][0];
                }
                // Left edge
                else {
                    sum = Data[row-1][col+1][0] * Mx[0][2] +
                          Data[row  ][col+1][0] * Mx[1][2] +
                          Data[row+1][col+1][0] * Mx[2][2] -
                          Data[row  ][col  ][0];
                }
            }
            // Right edge. Won't balance with typical masks.
            else if (col == Width-1) {
                // Top right corner
                if (row == 0) {
                    sum = Data[row  ][col-1][0] * Mx[1][0] +
                          Data[row+1][col-1][0] * Mx[2][0] -
                          Data[row  ][col  ][0];
                }
                // Bottom right corner
                else if (row == Height-1) {
                    sum = Data[row-1][col-1][0] * Mx[0][0] +
                          Data[row  ][col-1][0] * Mx[1][0] -
                          Data[row  ][col  ][0];
                }
                // Right edge
                else {
                    sum = Data[row-1][col-1][0] * Mx[0][0] +
                          Data[row  ][col-1][0] * Mx[1][0] +
                          Data[row-1][col-1][0] * Mx[2][0] -
                          Data[row  ][col  ][0];
                }
            }
            // Interior columns
            else {
                // Middle top
                if (row == 0) {
                    sum = Data[row  ][col-1][0] * Mx[1][0] +
                          Data[row+1][col-1][0] * Mx[2][0] -
                          Data[row  ][col+1][0] * Mx[0][2] -
                          Data[row+1][col+1][0] * Mx[0][2];
                }
                // Middle bottom
                else if (row == Height-1) {
                    sum = Data[row-1][col-1][0] * Mx[0][0] +
                          Data[row  ][col-1][0] * Mx[1][0] -
                          Data[row-1][col+1][0] * Mx[0][2] -
                          Data[row  ][col+1][0] * Mx[0][2];
                }
                // middle middle
                else {
                    sum = Data[row-1][col-1][0] * Mx[0][0] +
                          Data[row  ][col-1][0] * Mx[1][0] +
                          Data[row+1][col-1][0] * Mx[2][0] -
                          Data[row-1][col+1][0] * Mx[0][2] -
                          Data[row  ][col+1][0] * Mx[0][2] -
                          Data[row+1][col+1][0] * Mx[0][2];
                }
            }

            // check if gradient sum is beyond tolerance
            if (T < sum) {
                invertPixel(row, col);
            }
        }
    }
}

void Image::sobelY(int T) {
    const int My[3][3]= {{-1,-2,-1},
                         { 0, 0, 0},
                         { 1, 2, 1}};
}

// ============================== output ==============================
void Image::showData() {
    cout << cProgram << "image data:" << endl;
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
    cout << cProgram << cFile << "done." << endl;
}


// ============================= helpers ==============================
