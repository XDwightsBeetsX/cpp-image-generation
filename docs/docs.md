# Documentation

## Class *Image*

A data structure to store BMP image parameters such as `Height`, `Width`, and `BytesPerPixel`.
The *Image* class offers various constructors from different inputs.

| Constructor | Use |
| :-- | :-- |
| `Image I = Image();` | Makes a white image of size *100x100*. |
| `Image I = Image(height, width, filename);` | Makes a white image of size *HeightxWidth* with default filename of *output/output.bmp* if not provided. |

| Method | Description |
| :-- | :-- |
| `Image.toWhite()` | Overwrites all image pixels with white. |
| `Image.toBlack()` | Overwrites all image pixels with black. |
| `Image.toGrid(nrows, ncols, lineThickness)` | Overwrites a grid of *nrowsxncols* with default *lineThickness* of 1px if not provided. |
| `Image.toGradient()` | Generates an RGB gradient across the image. |
| `Image.setPixel(row, col, r, g, b)` | Overwrites the image pixel at location *Image[row][col]* with color values of *r, g, b*. |
| `Image.invertPixel(row, col)` | Inverts the image pixel colors at location *Image[row][col]* with `abs(255 - pixel)`. |
| `Image.invert()` | Inverts the whole image using `invertPixel`. |
| `Image.toGrayscale()` | Converts the current image pixel values to their r, g, b averages to create a grayscale image. |
| `Image.normalize` | Re-calculates image r, g, b values based on the range of each color present |
| `Image.sobel()` | ***(dev)*** Runs sobel edge detection in X and Y directions, highlighting transitions in pixel gradients. Requires image to be in grayscale format. |

| Output | Description |
| :-- | :-- |
| `Image.showData()` | Ouputs the current image pixel data to the console. |
| `Image.writeToFile()` | Writes the image BMP pixel data to *Image.Filename*. |
