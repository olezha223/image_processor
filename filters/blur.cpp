#include "blur.h"
#include <cmath>
#include <stdexcept>

GaussianBlur::GaussianBlur(float sigma) {
    if (sigma < 0) {
        throw std::runtime_error("Argument must be greater than 0");
    }
    sigma_ = sigma;
}

GaussianBlur::~GaussianBlur() = default;

GaussianBlur &GaussianBlur::operator=(const GaussianBlur &blur) = default;

std::pair<int, int> SetBoarders(int t, float sigma) {
    int start = t - static_cast<int>(3 * sigma);
    int end = t + static_cast<int>(3 * sigma);
    return {start, end};
}

void GaussianBlur::Apply(Image &image) {
    Image image_copy = image;
    float my_exp = expf(-1.0f / (2.0f * sigma_ * sigma_));                               // NOLINT
    float denominator = 1.0f / sqrtf(2.0f * 3.14159265358979323846f * sigma_ * sigma_);  // NOLINT
    for (int i = 0; i < image.Width(); ++i) {
        for (int j = 0; j < image.Height(); ++j) {
            RGB old_value = image.GetRgb(i, j);
            float result_b = 0.0f;
            float result_g = 0.0f;
            float result_r = 0.0f;

            // первый проход
            for (int k = SetBoarders(i, sigma_).first; k < SetBoarders(i, sigma_).second; ++k) {
                RGB rgb = image.GetRgb(k, j);
                float p = denominator * powf(my_exp, static_cast<float>((i - k) * (i - k)));
                result_r += rgb.r_ * p;
                result_b += rgb.b_ * p;
                result_g += rgb.g_ * p;
            }
            image_copy.ChangePixel(RGB(result_r, result_g, result_b), i, j);
        }
    }
    image.CopyImage(image_copy);
    for (int i = 0; i < image.Width(); ++i) {
        for (int j = 0; j < image.Height(); ++j) {
            RGB old_value = image.GetRgb(i, j);
            float result_b = 0.0f;
            float result_g = 0.0f;
            float result_r = 0.0f;

            // второй проход
            for (int k = SetBoarders(j, sigma_).first; k < SetBoarders(j, sigma_).second; ++k) {
                RGB rgb = image.GetRgb(i, k);
                float p = denominator * powf(my_exp, static_cast<float>((j - k) * (j - k)));
                result_r += rgb.r_ * p;
                result_b += rgb.b_ * p;
                result_g += rgb.g_ * p;
            }
            image_copy.ChangePixel(RGB(result_r, result_g, result_b), i, j);
        }
    }
    image.CopyImage(image_copy);
}
