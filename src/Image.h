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
     * @brief Creates a [100 x 100] Image w/ filename="output.bmp" and pixels (r=0, g=0, b=0).
     * 
     */
    Image();

    /**
     * @brief Creates a [height x width] Image w/ pixels (r=0, g=0, b=0).
     * 
     * @param height the height of the Image in pixels
     * @param width the width of the Image in pixels
     * @param filename optionally, choose a filename for the image. 'output.bmp' by default
     */
    Image(int height, int width, const char* filename=(char*)"output/output.bmp");


    // ============================ operations ============================
    /**
     * @brief Fills the Image.Data with (r=255, g=255, b=255).
     */
    void toWhite();

    /**
     * @brief Fills the Image.Data with (r=0, g=0, b=0).
     */
    void toBlack();

    /**
     * @brief Generates equally spaced gridlines of 10% the row/col width.
     * 
     * @param nrows the number of table rows desired. 
     * @param ncols the number of table columns desired.
     */
    void toGrid(int nrows, int ncols);

    /**
     * @brief Generates an RGB gradient in the Image.Data.
     * NOTE Ensure Image.Data is in (R,G,B) form.
     */
    void gradient();

    /**
     * @brief Sets the pixel at Data[row][col] to the provided r, g, b values.
     * 
     * @param row pixel row
     * @param col pixel col
     * @param r pixel Red value
     * @param g pixel Green value
     * @param b pixel Blue value
     */
    void setPixel(int row, int col, int r, int g, int b);

    /**
     * @brief Performs abs(255 - Image.Data[row][col]) for each BytesPerPixel of the pixel.
     * 
     * @param row The pixel row to invert.
     * @param col The pixel column to invert.
     */
    void invertPixel(int row, int col);
    
    /**
     * @brief Inverts the Image.Data. Performs Image.invertPixel(row, col) for each pixel.
     */
    void invert();

    /**
     * @brief For each pixel, calculates the avg of the r,g,b vals and assigns it to all three values.
     */
    void toGrayscale();

    /**
     * @brief Normalizes all R,G,B values based on Min/Maxs.
     * 
     */
    void normalize();

    /**
     * @brief Determines Edges of an image using Sobel Edge detection. Requires grayscale image to work correctly.
     * 
     * @param T sets the threshold limit for edge detection. 225 by default.
     */
    void sobel(int T=225);


    // ============================== output ==============================
    /**
     * @brief Prints out the Image.Data in matrix form where every pixel is given by (r, g, b).
     * 
     */
    void showData();

    /**
     * @brief Writes the .bmp fileHeader, infoHeader, and the Image.Data to file.
     * 
     */
    void writeToFile();
};

#endif
