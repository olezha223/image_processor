#pragma once
#include "base_filter.h"

class Sharpening : public Filter {
public:
    explicit Sharpening();

    std::vector<std::vector<float>> matrix_;

    void Apply(Image &image) override;

    ~Sharpening() override;

    Sharpening &operator=(const Sharpening &sharp);
};
