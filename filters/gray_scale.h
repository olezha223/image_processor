#pragma once
#include "base_filter.h"

class GrayScale : public Filter {
public:
    void Apply(Image &image) override;

    ~GrayScale() override;

    GrayScale &operator=(const GrayScale &gs);
};
