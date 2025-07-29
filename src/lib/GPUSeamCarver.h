#pragma once

#include "bitmap.h"
#include "GPUPixel.h"

#include <vector>

typedef std::vector<std::vector<Pixel>> PixelMatrix;

// TODO - add namespace later

class GPUSeamCarver {
    private:
        GPUPixel *pixels;
        float *gradients;
        float *seams;

        int* seamPath;

        // TODO - Using int for simplicity. Should this be size_t?
        // Note - width = column, height = row
        int width;
        int height; 

    public:
        GPUSeamCarver();
        GPUSeamCarver(const std::vector<std::vector<Pixel>> &pixelMatrix);
        ~GPUSeamCarver();

        void debugGradientMatrix();
        void debugSeamMatrix();
        void calculateGradients();
        void calculateSeams();
        void determineSeamToBeRemoved();
        void deleteSeam();
        const PixelMatrix& getPixelContainer();
};