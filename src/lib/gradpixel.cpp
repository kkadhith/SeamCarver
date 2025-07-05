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

void PixelTransformer::calculateGradients() {
    for (size_t i = 0; i < row; i++) {
        for (size_t j = 0; j < column; j++) {
            // auto.red, auto.green, auto.blue
            auto left = (j == 0) ? pixels[i][j] : pixels[i][j-1];
            auto right = (j == column - 1) ? pixels[i][j] : pixels[i][j+1];
            auto up = (i == 0) ? pixels[i][j] : pixels[i-1][j];
            auto down = (i == row -1) ? pixels[i][j] : pixels[i+1][j];

            auto calculateOrientation = [](Pixel p1, Pixel p2) {
                return std::pow((p1.red - p2.red), 2) + std::pow((p1.green - p2.green), 2) + std::pow((p1.blue - p2.blue), 2); 
            };
            int fx = calculateOrientation(right, left);
            int fy = calculateOrientation(down, up);
            float grad = std::sqrt(fx + fy);
            
            grads[i][j] = grad;
        }
    }
}

void PixelTransformer::ptg() {
    for (auto &i : grads) {
        for (auto &j : i) {
            std::cout << j << " ";
        }
        std::cout << '\n';
    }
}

void PixelTransformer::viewPixelOutput() {
    for (auto &i : pixels) {
        for (auto &j : i) {
            std::cout << "(" << j.red << ", " << j.green << ", " << j.blue << ")  ";
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
    for (size_t i = 0; i < column; i++) {
        seams[0][i] = grads[0][i];
    }

    for (size_t i = 1; i < row; i++) {
        for (size_t j = 0; j < column; j++) {
            if (j == 0) {
                seams[i][j] = grads[i][j] + std::min(seams[i-1][j+1], seams[i-1][j]);
            }
            else if (j == column - 1) {
                seams[i][j] = grads[i][j] + std::min(seams[i-1][j-1], seams[i-1][j]);
            }
            else {
                seams[i][j] = grads[i][j] + std::min(seams[i-1][j-1], std::min(seams[i-1][j], seams[i-1][j+1]));
            }
        }
    }
}

void PixelTransformer::deleteSeam() {
    for (size_t i = 0; i < row; i++) {
        auto removeIdx = seamCoords[i];

        for (size_t j = removeIdx; j < column-1; j++) {
            pixels[i][j] = pixels[i][j+1];
        }
        pixels[i].pop_back();
    }

    column = column - 1;
    grads = std::vector<std::vector<float>>(row, std::vector<float>(column));
    seams = std::vector<std::vector<float>>(row, std::vector<float>(column));
}

void PixelTransformer::removeSingleSeam() {
    seamCoords.clear();
    size_t minIndex = 0;
    auto smallestSeamSum = FLT_MAX;
    for (size_t j = 0; j < column; j++) {
        if (seams[row-1][j] < smallestSeamSum) {
            minIndex = j;
            smallestSeamSum = seams[row-1][j];
        }
    }
    
    for (size_t rowIterator = row-1; rowIterator >= 1; rowIterator--) {
        pixels[rowIterator][minIndex].red = 255;
        pixels[rowIterator][minIndex].green = 0;
        pixels[rowIterator][minIndex].blue = 0;

        seamCoords[rowIterator] = minIndex;

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

    seamCoords[0] = minIndex;
}

const PixelContainer& PixelTransformer::getPixelContainer() {
    return pixels;
}