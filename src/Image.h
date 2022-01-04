#ifndef Image_h
#define Image_h

#include <iostream>
#include <vector>


/**
 * @brief Stores 2D pixel data, 
 * where each pixel can be made up of a number of values in a form like (r, g, b).
 * Operations can be performed on the Image to modify the pixel data.
 */
class Image {
    std::string cProgram = "[PROGRAM] - ";
    std::string cFile = "[FILE] - ";

    const int FileHeaderSize = 14;
    const int InfoHeaderSize = 40;

    int Height;
    int Width;
    int BytesPerPixel;
    const char* Filename;

    std::vector<std::vector<std::vector<int>>> Data;

public:
    // =========================== constructors ===========================
    /**
     * Creates a [100 x 100] Image w/ filename="output.bmp" and pixels (r=0, g=0, b=0)
     */
    Image();


    /**
     * Creates a [height x width] Image w/ pixels (r=0, g=0, b=0)
     * @param height the height of the Image in pixels
     * @param width the width of the Image in pixels
     * @param filename optionally, choose a filename for the image. 'output.bmp' by default
     */
    Image(int height, int width, const char* filename=(char*)"output/output.bmp");


    // ============================ operations ============================
    /**
     * Fills the Image.Data with (r=255, g=255, b=255).
     */
    void toWhite();

    /**
     * Fills the Image.Data with (r=0, g=0, b=0).
     */
    void toBlack();


    // ============================== output ==============================
    /**
     * Prints out the Image.Data in matrix form where every pixel is given by (r, g, b).
     */
    void showData();

    /**
     * Writes the .bmp fileHeader, infoHeader, and the Image.Data to file.
     */
    void writeToFile();
};

#endif
