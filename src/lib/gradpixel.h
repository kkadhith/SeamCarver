#pragma once


#include "bitmap.h"

#include <iostream>
#include <vector>
#include <string>


namespace grp {
    typedef std::vector<std::vector<float>> GradContainer;
    typedef std::vector<std::vector<Pixel>> PixelContainer;

    class PixelTransformer {
        public:
            PixelTransformer();
            //PixelTransformer(const PixelContainer &pc);
            void transform();
            bool removal(); 
        private:
            GradContainer grads;
            PixelContainer pixels;
    };
}
