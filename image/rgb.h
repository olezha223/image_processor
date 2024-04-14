#pragma once

struct RGB {
    float r_ = 0;
    float g_ = 0;
    float b_ = 0;

    ~RGB();
    RGB();
    RGB(float r, float g, float b);
    RGB &operator=(const RGB &rgb);
};
