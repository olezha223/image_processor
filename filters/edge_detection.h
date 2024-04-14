#pragma once
#include "base_filter.h"

class EdgeDetection : public Filter {
private:
    std::vector<std::vector<float>> matrix_;
    float threshold_;

public:
    explicit EdgeDetection(float threshold);

    void Apply(Image &image) override;

    ~EdgeDetection() override;

    EdgeDetection &operator=(const EdgeDetection &edge);
};
