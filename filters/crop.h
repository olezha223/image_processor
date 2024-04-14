#pragma once
#include "base_filter.h"

class Crop : public Filter {
private:
    int width_;
    int height_;

public:
    explicit Crop(int width, int height);

    void Apply(Image &image) override;

    ~Crop() override;

    Crop &operator=(const Crop &crop);
};
