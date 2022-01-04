
#include "./src/Image.h"

using namespace std;

int main () {
    char* fname = (char*) "output.bmp";
    Image I = Image(400, 800, fname);
    I.gradient();
    I.writeToFile();
}
