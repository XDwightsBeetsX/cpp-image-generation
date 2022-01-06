#include "./src/Image.h"

using namespace std;

int main () {
    char* fname = (char*) "output/grid.bmp";
    Image I = Image(20, 20, fname);
    I.gradient();
    I.toGrid(2, 2);
    I.toGrayscale();
    I.sobel(200);
    I.writeToFile();
}
