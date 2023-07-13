#include <iostream>
#include <vector>
#include <string>

#include "lib/debugutil.hpp"
#include "lib/bitmap.h"

int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        signal_error("Need at least one image to carve.\n");
    }
    std::string filename = argv[1];
    Pixel rgb;
    Bitmap image;
    std::vector<std::vector<Pixel>> bmp;
    image.open(filename);
    bool validBmp = image.isImage();

    if(validBmp == true) {
        bmp = image.toPixelMatrix();

        for (int i = 0; i < 50; i++) {
            rgb = bmp[i][4];
            rgb.red = 0;
            rgb.green = 0;
            bmp[i][4] = rgb;
        }

        image.fromPixelMatrix(bmp);
        image.save("example1.bmp");
    }

    return 0;
}
