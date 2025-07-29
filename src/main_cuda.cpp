#include <iostream>
#include <vector>

#include "lib/debugutil.hpp"
#include "lib/bitmap.h"
#include "lib/GPUSeamCarver.h"

int main(int argc, char* argv[]) {
    
    if (argc < 3) {
        signal_error("Specify image and number of seams. Usage: ./compress_cuda <image> <seams>\n");
    }

    std::string filename = argv[1];
    int numberOfSeams = atoi(argv[2]);
    Bitmap image;
    std::vector<std::vector<Pixel>> originalImage;
    image.open(filename);

    bool validBmp = image.isImage();

    if(validBmp == true) {
        originalImage = image.toPixelMatrix();
        GPUSeamCarver GPUSeamCarver(originalImage);

        if (GPUSeamCarver.getPixelContainer()[0].size() < numberOfSeams) {
            signal_error("The number of seams to be removed is higher than the total seams in the image. Try a smaller number.\n");
        }
        
        for (int i = 0; i < numberOfSeams; i++) {
            GPUSeamCarver.calculateGradients();
            GPUSeamCarver.calculateSeams();
            GPUSeamCarver.determineSeamToBeRemoved();
            GPUSeamCarver.deleteSeam();
        }

        originalImage = gpu_carver.getPixelContainer();
        image.fromPixelMatrix(originalImage);
        image.save("CUDACarvedImage.bmp");
    }
    
    return 0;
}