#pragma once
#include "base_filter.h"

// задумка фильтра - создать эффект раздвоения картинки в глазах + добавить глюки
class SickEye : public Filter {
private:
    float vert_;
    float hor_;

public:
    SickEye(float vert, float hor);

    void Apply(Image &image) override;

    ~SickEye() override;

    SickEye &operator=(const SickEye &sick);
};