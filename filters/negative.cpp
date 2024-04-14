#include "negative.h"

void Negative::Apply(Image &image) {
    for (int i = 0; i < image.Width(); ++i) {
        for (int j = 0; j < image.Height(); ++j) {
            RGB old_value = image.GetRgb(i, j);
            image.ChangePixel(RGB(1.0f - old_value.r_, 1.0f - old_value.g_, 1.0f - old_value.b_), i, j);
        }
    }
}

Negative::~Negative() = default;

Negative &Negative::operator=(const Negative &neg) = default;
