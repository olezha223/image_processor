#pragma once
#include "base_filter.h"

std::pair<int, int> SetBoarders(int t, float sigma);

class GaussianBlur : public Filter {
private:
    float sigma_;

public:
    explicit GaussianBlur(float sigma);

    void Apply(Image &image) override;

    ~GaussianBlur() override;

    GaussianBlur &operator=(const GaussianBlur &blur);
};
