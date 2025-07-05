#include <iostream>
#include <vector>
#include <string>

#include "lib/debugutil.hpp"
#include "lib/bitmap.h"
#include "lib/gradpixel.h"


int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        signal_error("Need at least one image to carve.\n");
    }

    std::string filename = argv[1];
    Bitmap image;
    std::vector<std::vector<Pixel>> originalImage;
    image.open(filename);

    bool validBmp = image.isImage();

    if(validBmp == true) {
        originalImage = image.toPixelMatrix();
        grp::PixelTransformer tm = grp::PixelTransformer(originalImage);

        // maybe make this part of argv
        int count = 400;
        for (int i = 0; i < count; i++) {
            tm.calculateGradients();
            tm.calculateSeams();
            tm.removeSingleSeam();
            tm.deleteSeam();
        }

        originalImage = tm.getPixelContainer();
        image.fromPixelMatrix(originalImage);
        image.save("carvedImage.bmp");
    }

    return 0;
}
