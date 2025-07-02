#include "gradpixel.h"

#include <cmath>
#include <cfloat>
using namespace grp;

PixelTransformer::PixelTransformer() {}

PixelTransformer::PixelTransformer(const PixelContainer &pc) {
    pixels = pc;
    row = pc.size();
    column = pc[0].size();
    this->grads = std::vector<std::vector<float>>(row, std::vector<float>(column));
    this->seams = std::vector<std::vector<float>>(row, std::vector<float>(column));
}

void PixelTransformer::transform() {
    for (size_t i = 1; i < row-1; i++) {
        for (size_t j = 1; j < column-1; j++) {
            // auto.red, auto.green, auto.blue
            auto left = pixels[i][j-1];
            auto right = pixels[i][j+1];
            auto up = pixels[i-1][j];
            auto down = pixels[i+1][j];

            auto calculateOrientation = [](Pixel p1, Pixel p2) {
                return std::pow((p1.red - p2.red), 2) + std::pow((p1.green - p2.green), 2) + std::pow((p1.blue - p2.blue), 2); 
            };
            int fx = calculateOrientation(right, left);
            int fy = calculateOrientation(down, up);
            float grad = std::sqrt(fx + fy);
            
            grads[i][j] = grad;
        }
    }

    for (size_t i = 0; i < row; i++) {
        grads[i][0] = FLT_MAX;
        grads[i][column-1] = FLT_MAX;
    }

    for (size_t i = 0; i < column; i++) {
        grads[0][i] = FLT_MAX;
        grads[row-1][i] = FLT_MAX;
    }
    return;
}

void PixelTransformer::ptg() {
    for (auto &i : grads) {
        for (auto &j : i) {
            std::cout << j << " ";
        }
        std::cout << '\n';
    }
}

void PixelTransformer::ptp() {
    for (auto &i : pixels) {
        for (auto &j : i) {
            std::cout << j.red << " ";
        }
        std::cout << '\n';
    }
}

void PixelTransformer::pts() {
    for (auto &i : seams) {
        for (auto &j : i) {
            std::cout << j << " ";
        }
        std::cout << '\n';
    }
}

void PixelTransformer::calculateSeams() {
    for (size_t j = 1; j < column-1; j++) {
        float sum = 0;
        for (size_t i = 1; i < row-1; i++) {
            sum += grads[i][j];
            seams[i][j] = sum;
        }
    }
}

void PixelTransformer::removal() {
    size_t minIndex = 1;
    auto smallestSeamSum = FLT_MAX;
    for (size_t j = 1; j < column-1; j++) {
        if (seams[row-2][j] < smallestSeamSum) {
            minIndex = j;
            smallestSeamSum = seams[row-2][j];
        }
    }
    
    // In progress: seam identification
    // fix logic, visualize seam
    // clean up code
    for (size_t rowIterator = row-1; rowIterator >= 1; rowIterator--) {
        pixels[rowIterator][minIndex].red = 255;
        pixels[rowIterator][minIndex].green = 0;
        pixels[rowIterator][minIndex].blue = 0;

        if (minIndex == static_cast<size_t>(0)) {
            auto above = seams[rowIterator-1][minIndex];
            auto right = seams[rowIterator-1][minIndex+1];

            if (right < above) {
                smallestSeamSum = right;
                minIndex = minIndex + 1;
            }
            else {
                smallestSeamSum = above;
            }

        }
        else if (minIndex == static_cast<size_t>(column - 1)) {
            auto left = seams[rowIterator-1][minIndex-1];
            auto above = seams[rowIterator-1][minIndex];

            if (left < above) {
                smallestSeamSum = left;
                minIndex = minIndex - 1;
            }
            else {
                smallestSeamSum = above;
            }
        }
        else {
            auto left = seams[rowIterator-1][minIndex-1];
            auto above = seams[rowIterator-1][minIndex];
            auto right = seams[rowIterator-1][minIndex+1];

            if (left <= above && left <= right) {
                minIndex = minIndex - 1;
                smallestSeamSum = left;
            }
            else if (right <= above && right <= left) {
                minIndex = minIndex + 1;
                smallestSeamSum = right;
            }
            else {
                smallestSeamSum = above;
            }
        }
    }
}

const PixelContainer& PixelTransformer::getPixelContainer() {
    return pixels;
}