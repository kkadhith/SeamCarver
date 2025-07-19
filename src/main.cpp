#include <iostream>
#include <vector>
#include <string>

#include "lib/debugutil.hpp"
#include "lib/bitmap.h"
#include "lib/gradpixel.h"
#include "lib/timekeeper.h"


int main(int argc, char* argv[]) {
    
    if (argc < 3) {
        signal_error("Specify image and number of seams. Usage: ./compress <image> <seams>\n");
    }

    std::string filename = argv[1];
    int numberOfSeams = atoi(argv[2]);
    Bitmap image;
    std::vector<std::vector<Pixel>> originalImage;
    image.open(filename);

    bool validBmp = image.isImage();

    if(validBmp == true) {
        originalImage = image.toPixelMatrix();
        grp::PixelTransformer tm = grp::PixelTransformer(originalImage);

        if (tm.getColumns() < numberOfSeams) {
            signal_error("The number of seams to be removed is higher than the total seams in the image. Try a smaller number.\n");
        }

        timer t;
        for (int i = 0; i < numberOfSeams; i++) {
            tm.calculateGradients();
            tm.calculateSeams();
            tm.removeSingleSeam();
            tm.deleteSeam();
        }
        auto res = t.stop();

        std::cout << res << std::endl;

        originalImage = tm.getPixelContainer();
        image.fromPixelMatrix(originalImage);
        image.save("carvedImage.bmp");
    }

    return 0;
}
