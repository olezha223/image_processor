#pragma once
#include "base_filter.h"

class Negative : public Filter {
public:
    void Apply(Image &image) override;

    ~Negative() override;

    Negative &operator=(const Negative &neg);
};
