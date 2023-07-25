#include "gradpixel.h"

using namespace grp;

PixelTransformer::PixelTransformer() {}

PixelTransformer::PixelTransformer(const PixelContainer &pc) {
    this->pixels = pc;
}

