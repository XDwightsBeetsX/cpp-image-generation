#include <string>
#include <cstring>
#include <cmath>

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

void Image::gradient() {
    cout << cProgram << "generating gradient..." << endl;
    for (int row = 0; row < Height; row++) {
        for (int col = 0; col < Width; col++) {
            Data[row][col][0] = (int) (255 * (double) (Width - col) / Width);
            Data[row][col][1] = (int) (255 * (double) (Height - row) / Height);
            Data[row][col][2] = (int) (255 * (double) (row + col) / (Width + Height));
        }
    }
}

void Image::toGrid(int nrows, int ncols) {
    int lineHeight = floor(0.05 * Height / (nrows - 1));
    int lineWidth = floor(0.05 * Width / (ncols - 1));

    int rowHeight = ceil(Height / nrows);
    int colWidth = ceil(Width / ncols);

    for (int row = 0; row < Height; row++) {
        for (int col = 0; col < Width; col++) {
            // is a horizontal gridline
            if (row % rowHeight < lineHeight) {
                setPixel(row, col, 0, 0, 0);
            }

            // is a vertical gridline
            if (col % colWidth < lineWidth) {
                setPixel(row, col, 0, 0, 0);
            }
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

    // Sobel masks in X and Y
    const int Mx[3][3] =    {{-1, 0, 1},
                             {-2, 0, 2},
                             {-1, 0, 1}};
    const int My[3][3] =    {{-1,-2,-1},
                             { 0, 0, 0},
                             { 1, 2, 1}};
    
    // Calculate the mask values for each pixel
    for (int row = 0; row < Height; row++) {
        for (int col = 0; col < Width; col++) {
            // Select current pixel and reset gradX and gradY
            int curr = Data[row][col][0];
            int gradX = 0;
            int gradY = 0;
            
            // top l/r, edge
            if (row == 0) {
                // left
                if (col == 0) {
                    int xTot =  Data[row  ][col  ][0] * 0.7 +
                                Data[row+1][col+1][0] * 0.3 -
                                curr;
                    int yTot =  Data[row+1][col  ][0] * 0.7 +
                                Data[row+1][col+1][0] * 0.3 -
                                curr;

                    if (T <= abs(xTot) || T <= abs(yTot))
                        invertPixel(row, col);
                }
                
                // right
                else if (col == Width-1) {
                    int xTot =  Data[row  ][col-1][0] * 0.7 +
                                Data[row+1][col  ][0] * 0.3 -
                                curr;
                    int yTot =  Data[row+1][col-1][0] * 0.7 +
                                Data[row+1][col  ][0] * 0.3 -
                                curr;

                    if (T <= abs(xTot) || T <= abs(yTot))
                        invertPixel(row, col);
                }

                // top edge
                else {
                    // Xs balance out
                    int xTot =  Data[row  ][col-1][0] * Mx[1][0] +
                                Data[row+1][col-1][0] * Mx[2][0] +
                                Data[row  ][col+1][0] * Mx[1][2] +
                                Data[row+1][col+1][0] * Mx[2][2];
                    
                    // Ys need adjustment
                    int yTot =  Data[row+1][col-1][0] * .25 +
                                Data[row+1][col  ][0] * .5  +
                                Data[row+1][col+1][0] * .25 -
                                curr;

                    if (T <= abs(xTot) || T <= abs(yTot))
                        invertPixel(row, col);
                }
            }

            // bottom l/r, edge
            else if (row == Height-1) {
                // left
                if (col == 0) {
                    int xTot =  Data[row-1][col+1][0] * 0.3 +
                                Data[row  ][col+1][0] * 0.7 -
                                curr;
                    int yTot =  Data[row-1][col  ][0] * 0.7 +
                                Data[row-1][col+1][0] * 0.3 -
                                curr;

                    if (T <= abs(xTot) || T <= abs(yTot))
                        invertPixel(row, col);
                }
                
                // right
                else if (col == Width-1) {
                    int xTot =  Data[row-1][col-1][0] * 0.3 +
                                Data[row  ][col-1][0] * 0.7 -
                                curr;
                    int yTot =  Data[row-1][col-1][0] * 0.3 +
                                Data[row  ][col-1][0] * 0.7 -
                                curr;

                    if (T <= abs(xTot) || T <= abs(yTot))
                        invertPixel(row, col);
                }

                // bottom edge
                else {
                    // Xs balance out
                    int xTot =  Data[row-1][col-1][0] * Mx[0][0] +
                                Data[row  ][col-1][0] * Mx[1][0] +
                                Data[row-1][col+1][0] * Mx[1][2] +
                                Data[row  ][col+1][0] * Mx[1][2];
                    
                    // Ys need adjustment
                    int yTot =  Data[row-1][col-1][0] * .25 +
                                Data[row-1][col  ][0] * .5  +
                                Data[row-1][col+1][0] * .25 -
                                curr;
                    
                    if (T <= abs(xTot) || T <= abs(yTot))
                        invertPixel(row, col);
                }
            }

            // left edge
            else if (col == 0) {
                // Xs need adjustment
                int xTot =  Data[row-1][col+1][0] * .25 +
                            Data[row  ][col+1][0] * .5  +
                            Data[row+1][col+1][0] * .25 -
                            curr;
                
                // Ys balance out
                int yTot =  Data[row-1][col  ][0] * Mx[0][1] +
                            Data[row-1][col+1][0] * Mx[0][2] +
                            Data[row+1][col  ][0] * Mx[2][1] +
                            Data[row+1][col+1][0] * Mx[2][2];

                if (T <= abs(xTot) || T <= abs(yTot))
                    invertPixel(row, col);
            }

            // right edge
            else if (col == Width - 1) {
                // Xs need adjustment
                int xTot =  Data[row-1][col-1][0] * .25 +
                            Data[row  ][col-1][0] * .5  +
                            Data[row+1][col-1][0] * .25 -
                            curr;
                
                // Ys balance out
                int yTot =  Data[row-1][col-1][0] * Mx[0][0] +
                            Data[row-1][col  ][0] * Mx[0][1] +
                            Data[row+1][col-1][0] * Mx[2][0] +
                            Data[row+1][col  ][0] * Mx[2][1];

                if (T <= abs(xTot) || T <= abs(yTot))
                    invertPixel(row, col);
            }

            // interior
            else {
                int xLeft =     Mx[0][0] * Data[row-1][col-1][0] +
                                Mx[1][0] * Data[row  ][col-1][0] +
                                Mx[2][0] * Data[row+1][col-1][0];
                int xRight =    Mx[0][2] * Data[row-1][col+1][0] +
                                Mx[1][2] * Data[row  ][col+1][0] +
                                Mx[2][2] * Data[row+1][col+1][0];
                int xTot = xLeft + xRight;

                int yTop =      My[0][0] * Data[row-1][col-1][0] +
                                My[0][1] * Data[row-1][col  ][0] +
                                My[0][2] * Data[row-1][col+1][0];
                int yBottom =   My[2][0] * Data[row+1][col-1][0] +
                                My[2][1] * Data[row+1][col  ][0] +
                                My[2][2] * Data[row+1][col+1][0];
                int yTot = yTop + yBottom;

                if (T <= xTot || T <= yTot) {
                    Data[row][col][0] = 255 - Data[row][col][0];
                }
            }
        }
    }
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
