#include "./src/Image.h"

using namespace std;

int main () {
    char* fname = (char*) "output/gray.bmp";
    Image I = Image(400, 800, fname);
    I.gradient();
    I.toGrayscale();
    I.writeToFile();
}
