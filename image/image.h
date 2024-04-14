#pragma once
#include "rgb.h"
#include <vector>

class Image {
private:
    int width_;
    int height_;
    int x_pixels_per_m_{};
    int y_pixels_per_m_{};
    std::vector<std::vector<RGB>> pixels_;

public:
    Image();

    explicit Image(const char* path);

    Image(int width, int height);

    RGB GetRgb(int x, int y) const;
    void ChangePixel(const RGB& rgb, int x, int y);

    int Width() const;
    int Height() const;
    int GetXPixels() const;
    int GetYPixels() const;

    void ResizeImage(int width, int height);

    friend void SaveFile(const char* path, Image& image);

    void Read(const char* path);

    void CopyImage(const Image& image_copy);

    ~Image();
};
