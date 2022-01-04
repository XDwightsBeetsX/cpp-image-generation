#include "operations.h"

#include <vector>


using namespace std;


void black(vector<vector<vector<int>>>& img, int height, int width) {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            img[row][col][0] = 0;
            img[row][col][1] = 0;
            img[row][col][2] = 0;
        }
    }
}


void white(vector<vector<vector<int>>>& img, int height, int width) {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            img[row][col][0] = 255;
            img[row][col][1] = 255;
            img[row][col][2] = 255;
        }
    }
}


void invert(vector<vector<vector<int>>>& img, int height, int width) {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            img[row][col][0] = 255 - img[row][col][0];
            img[row][col][1] = 255 - img[row][col][1];
            img[row][col][2] = 255 - img[row][col][2];
        }
    }
}
