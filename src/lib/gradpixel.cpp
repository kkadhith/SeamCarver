#include "gradpixel.h"

using namespace grp;

PixelTransformer::PixelTransformer() {}

PixelTransformer::PixelTransformer(const PixelContainer &pc) {
    this->pixels = pc;
    row = pc.size();
    column = pc[0].size();
    this->grads = std::vector<std::vector<float>>(row, std::vector<float>(column));
}

// void PixelTransformer::transform() {

// }
