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
    std::vector<std::vector<Pixel>> bmp;
    image.open(filename);

    bool validBmp = image.isImage();

    if(validBmp == true) {
        bmp = image.toPixelMatrix();
        grp::PixelTransformer tm = grp::PixelTransformer(bmp); 
        tm.transform();
        tm.ptp();
        tm.ptg();
        image.fromPixelMatrix(bmp);
        // image.save("example1.bmp");
    }

    return 0;
}
