#pragma once


#include "bitmap.h"

#include <iostream>
#include <vector>
#include <string>


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
            bool removal();
            void ptg();
            void ptp();
        private:
            GradContainer grads;
            PixelContainer pixels;
            SeamContainer seams;
            size_t row;
            size_t column;
    };
}
