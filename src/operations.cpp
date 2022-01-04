
#include <iostream>
#include <vector>

#include "operations.h"


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

void gradient(vector<vector<vector<int>>>& img, int height, int width) {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            img[row][col][0] = (int) (255 * (double) (width - col) / width);
            img[row][col][1] = (int) (255 * (double) (height - row) / height);
            img[row][col][2] = (int) (255 * (double) (row + col) / (width + height));
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


void normalize(vector<vector<vector<int>>>& img, int height, int width) {
    // preset min/maxs to be overridden
    int minB, maxB = img[0][0][0];
    int minG, maxG = img[0][0][1];
    int minR, maxR = img[0][0][2];

    // find min/maxs
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int b = img[row][col][0];
            int g = img[row][col][1];
            int r = img[row][col][2];

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
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            img[row][col][0] = (int) (img[row][col][0] * (double) ((maxB - minB) / 255));
            img[row][col][1] = (int) (img[row][col][1] * (double) ((maxG - minG) / 255));
            img[row][col][2] = (int) (img[row][col][2] * (double) ((maxR - minR) / 255));
        }
    }
}
