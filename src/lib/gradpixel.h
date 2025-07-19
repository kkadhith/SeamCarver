#pragma once


#include "bitmap.h"

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>


namespace grp {
    typedef std::vector<std::vector<float>> GradContainer;
    typedef std::vector<std::vector<Pixel>> PixelContainer;
    typedef std::vector<std::vector<float>> SeamContainer;

    class PixelTransformer {
        public:
            PixelTransformer();
            PixelTransformer(const PixelContainer &pc);
            void calculateGradients();
            void calculateSeams();
            void removeSingleSeam();
            void ptg();
            void viewPixelOutput();
            void pts();
            void changeLines();
            void deleteSeam();

            size_t getColumns();

            const PixelContainer& getPixelContainer();
        private:
            GradContainer grads;
            PixelContainer pixels;
            SeamContainer seams;
            std::unordered_map<int, int> seamCoords;

            size_t row;
            size_t column;
    };
}
