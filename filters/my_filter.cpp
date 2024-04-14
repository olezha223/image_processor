#include "blur.h"
#include "my_filter.h"
#include <stdexcept>

SickEye::SickEye(float vert, float hor) {
    if (vert >= 100 || hor >= 100 || vert < 0 || hor < 0) {  // NOLINT
        throw std::runtime_error("Percent of offset must be from 0 to 100");
    }
    vert_ = vert;
    hor_ = hor;
}

void SickEye::Apply(Image& image) {
    // наш фильтр будет накладывать изображение на другое со смещением
    Image image_copy = image;
    int start_hor = static_cast<int>(static_cast<float>(image.Width()) * hor_ / 100);     // NOLINT
    int start_vert = static_cast<int>(static_cast<float>(image.Height()) * vert_ / 100);  // NOLINT
    for (int i = start_hor; i < image.Width(); ++i) {
        for (int j = start_vert; j < image.Height(); ++j) {
            RGB old_value = image.GetRgb(i - start_hor, j - start_vert);
            float result_r = 0.5f * (old_value.r_ + image_copy.GetRgb(i, j).r_);  // NOLINT
            float result_g = 0.5f * (old_value.g_ + image_copy.GetRgb(i, j).g_);  // NOLINT
            float result_b = 0.5f * (old_value.b_ + image_copy.GetRgb(i, j).b_);  // NOLINT
            image_copy.ChangePixel(RGB(result_r, result_g, result_b), i, j);
        }
    }
    image.CopyImage(image_copy);
    // сделаем цветовые глюки
    for (int i = 0; i < image.Width(); ++i) {
        for (int j = 0; j < image.Height(); ++j) {
            RGB old_value = image.GetRgb(i, j);
            float result_r = old_value.r_;
            float result_g = old_value.g_;
            float result_b = old_value.b_;
            float max_color = std::max(result_r, std::max(result_b, result_g));
            if (max_color == old_value.r_) {
                result_r *= 1.5f;   // NOLINT
                result_b *= 1.25f;  // NOLINT
            }
            if (max_color == old_value.g_) {
                result_g *= 0.75f;  // NOLINT
            }
            if (max_color == old_value.b_) {
                result_b *= 0.75f;  // NOLINT
            }
            image.ChangePixel(RGB(result_r, result_g, result_b), i, j);
        }
    }
    // сделаем легкое размытие
    Filter* blur = new GaussianBlur(1.5f);  // NOLINT
    blur->Apply(image);
    delete blur;
}

SickEye::~SickEye() = default;

SickEye& SickEye::operator=(const SickEye& sick) = default;
