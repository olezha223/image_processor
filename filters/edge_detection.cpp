#include "apply_matrix.h"
#include "edge_detection.h"
#include <stdexcept>

EdgeDetection::EdgeDetection(const float threshold) {
    if (threshold < 0 || threshold > 1) {
        throw std::runtime_error("Argument must be greater than 0");
    }
    threshold_ = threshold;
    matrix_ = {{0.0f, -1.0f, 0.0f},
               {-1.0f, 4.0f, -1.0f},  // NOLINT
               {0.0f, -1.0f, 0.0f}};
}

void EdgeDetection::Apply(Image &image) {
    // переведем все в серые оттенки
    for (int i = 0; i < image.Width(); ++i) {
        for (int j = 0; j < image.Height(); ++j) {
            RGB old_value = image.GetRgb(i, j);
            float pixel = 0.299f * old_value.r_ + 0.587f * old_value.g_ + 0.114f * old_value.b_;  // NOLINT
            pixel = std::min(1.0f, std::max(0.0f, pixel));
            image.ChangePixel(RGB(pixel, pixel, pixel), i, j);
        }
    }
    // теперь применим матрицу
    ApplyMatrix(matrix_, image);
    // накинем threshold
    for (int i = 0; i < image.Width(); ++i) {
        for (int j = 0; j < image.Height(); ++j) {
            RGB old_value = image.GetRgb(i, j);
            float pixel = old_value.r_;
            if (pixel <= threshold_) {
                pixel = 0.0f;
            } else {
                pixel = 1.0f;
            }
            pixel = std::min(1.0f, std::max(0.0f, pixel));
            image.ChangePixel(RGB(pixel, pixel, pixel), i, j);
        }
    }
}

EdgeDetection::~EdgeDetection() = default;

EdgeDetection &EdgeDetection::operator=(const EdgeDetection &edge) = default;
