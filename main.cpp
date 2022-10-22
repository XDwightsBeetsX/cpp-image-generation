#include "./src/Image.h"

using namespace std;

int main () {
    const char* a = (const char*) "input/gradient_grid.bmp";
    const char* b = (const char*) "input/dog.bmp";

    Image I = Image::getImageFromFile(a);
    // I.showData();
}
