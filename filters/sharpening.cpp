#include "apply_matrix.h"
#include "sharpening.h"

Sharpening::Sharpening() : matrix_({{0.0f, -1.0f, 0.0f}, {-1.0f, 5.0f, -1.0f}, {0.0f, -1.0f, 0.0f}}){};  // NOLINT

void Sharpening::Apply(Image &image) {
    ApplyMatrix(matrix_, image);
}

Sharpening::~Sharpening() = default;

Sharpening &Sharpening::operator=(const Sharpening &sharp) = default;
