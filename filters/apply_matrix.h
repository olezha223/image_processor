#pragma once
#include "../image/image.h"
#include <vector>

void ApplyMatrix(std::vector<std::vector<float>>& matrix, Image& image);

bool IsFloat(const char* str);

bool IsInt(const char* str);