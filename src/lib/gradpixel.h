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
            void transform();
            void calculateSeams();
            void removal();
            void ptg();
            void ptp();
            void pts();
            void changeLines();
            void remove();

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
