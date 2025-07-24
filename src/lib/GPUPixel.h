#pragma once


class GPUPixel {
    public:

        int red, green, blue;

        __host__ __device__ GPUPixel() : red(0), green(0), blue(0) {}

        __host__ __device__ GPUPixel(int r, int g, int b) : red(r), green(g), blue(b) {}
};