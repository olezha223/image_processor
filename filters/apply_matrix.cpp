#include "apply_matrix.h"
#include <cstdlib>

void ApplyMatrix(std::vector<std::vector<float>>& matrix, Image& image) {
    Image image_copy = image;
    for (int i = 0; i < image.Width(); ++i) {
        for (int j = 0; j < image.Height(); ++j) {
            // считаем взвешенную сумму для каждого цвета
            // в задании матрица свертки размера 3 * 3
            std::vector<int> numbers = {-1, 0, 1};
            float result_b = 0.0f;
            float result_g = 0.0f;
            float result_r = 0.0f;
            for (std::size_t m = 0; m < numbers.size(); ++m) {
                for (std::size_t t = 0; t < numbers.size(); ++t) {
                    result_b += matrix[m][t] * image.GetRgb(i - numbers[m], j - numbers[t]).b_;
                    result_g += matrix[m][t] * image.GetRgb(i - numbers[m], j - numbers[t]).g_;
                    result_r += matrix[m][t] * image.GetRgb(i - numbers[m], j - numbers[t]).r_;
                }
            }
            result_r = std::min(1.0f, std::max(0.0f, result_r));
            result_g = std::min(1.0f, std::max(0.0f, result_g));
            result_b = std::min(1.0f, std::max(0.0f, result_b));
            image_copy.ChangePixel(RGB(result_r, result_g, result_b), i, j);
        }
    }
    image.CopyImage(image_copy);
}

bool IsFloat(const char* str) {
    char* end_ptr = nullptr;
    std::strtof(str, &end_ptr);
    return (*str != '\0' && *end_ptr == '\0');
}

bool IsInt(const char* str) {
    char* end_ptr = nullptr;
    std::strtol(str, &end_ptr, 10);  // NOLINT
    return (*str != '\0' && *end_ptr == '\0');
}