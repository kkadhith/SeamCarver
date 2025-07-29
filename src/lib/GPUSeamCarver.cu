#include "GPUPixel.h"
#include "bitmap.h"

#include <vector>
#include <iostream>


__global__ void calculateGradientsKernel(GPUPixel *pixels, float *gradients, int width, int height) {
    int j = blockDim.x * blockIdx.x + threadIdx.x;
    int i = blockDim.y * blockIdx.y + threadIdx.y;
    
    int trueIndex = i * width + j;

    if (j >= width || i >= height) {
        return;
    }

    GPUPixel currentPixel = pixels[trueIndex];

    GPUPixel left = (j == 0) ? currentPixel : pixels[trueIndex - 1];
    GPUPixel right = (j == width - 1) ? currentPixel : pixels[trueIndex + 1];
    GPUPixel up = (i == 0) ? currentPixel : pixels[trueIndex - width];
    GPUPixel down = (i == height - 1) ? currentPixel : pixels[trueIndex + width];

    int fx = (right.red - left.red) * (right.red - left.red) + 
    (right.green - left.green) * (right.green - left.green) + 
    (right.blue - left.blue) * (right.blue - left.blue);

    int fy = (down.red - up.red) * (down.red - up.red) + 
    (down.green - up.green) * (down.green - up.green) + 
    (down.blue - up.blue) * (down.blue - up.blue);

    gradients[trueIndex] = sqrtf(static_cast<float>(fx + fy));
}