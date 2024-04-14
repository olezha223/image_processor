#include "crop.h"
#include <stdexcept>

Crop::Crop(int width, int height) {
    if (width < 0 || height < 0) {
        throw std::runtime_error("Arguments must be greater than 0");
    }
    width_ = width;
    height_ = height;
}

void Crop::Apply(Image &image) {
    image.ResizeImage(width_, height_);
}

Crop::~Crop() = default;

Crop &Crop::operator=(const Crop &crop) = default;
