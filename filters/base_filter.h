#pragma once
#include "../image/image.h"

class Filter {
public:
    Filter();

    virtual void Apply(Image &image){};

    virtual ~Filter();

    Filter &operator=(const Filter &filter);
};
