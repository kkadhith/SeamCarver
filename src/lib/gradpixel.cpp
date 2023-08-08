#include "gradpixel.h"

#include <cmath>
using namespace grp;

PixelTransformer::PixelTransformer() {}

PixelTransformer::PixelTransformer(const PixelContainer &pc) {
    pixels = pc;
    row = pc.size();
    column = pc[0].size();
    this->grads = std::vector<std::vector<float>>(row, std::vector<float>(column));
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

void PixelTransformer::calculateSeams() {
    for (size_t i = 1; i < row; i++) {
        for (size_t j = 1; j < column; j++) {

        }
    }
}