#include "gray_scale.h"

void GrayScale::Apply(Image &image) {
    for (int i = 0; i < image.Width(); ++i) {
        for (int j = 0; j < image.Height(); ++j) {
            RGB old_value = image.GetRgb(i, j);
            float pixel = 0.299f * old_value.r_ + 0.587f * old_value.g_ + 0.114f * old_value.b_;  // NOLINT
            image.ChangePixel(RGB(pixel, pixel, pixel), i, j);
        }
    }
}

GrayScale::~GrayScale() = default;

GrayScale &GrayScale::operator=(const GrayScale &gs) = default;
