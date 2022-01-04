#include <iostream>
#include <stdio.h>
#include <vector>

#include "./src/operations.h"
#include "./src/bitmap.h"


using namespace std;


int main () {
    cout << "[PROGRAM] - running..." << endl;

    // Image Parameters
    char* imageFileName = (char*) "output.bmp";
    const int height = 300;
    const int width = 700;
    unsigned char imgChar[height][width][BYTES_PER_PIXEL];  // [B, G, R]


    // Create a blank vector of same size to make operations easier
    vector<vector<vector<int>>> imgVect(height, vector<vector<int>>(width, vector<int>(BYTES_PER_PIXEL, 0)));
    
    
    // Perform img operations
    gradient(imgVect, height, width);
    // normalize(imgVect, height, width);


    // populate the imgChar with the imgVect
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            imgChar[row][col][0] = imgVect[row][col][0];
            imgChar[row][col][1] = imgVect[row][col][1];
            imgChar[row][col][2] = imgVect[row][col][2];
        }
    }
    
        
    // creates the file and info headers, then writes the image data
    generateBitmapImage((unsigned char*) imgChar, height, width, imageFileName);
    
    cout << "[PROGRAM] - image generated at ./" << imageFileName << endl;
}
