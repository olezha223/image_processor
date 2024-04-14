#include "image.h"

Image::Image() : width_(0), height_(0) {
}

Image::Image(int width, int height) : width_(width), height_(height), pixels_(height_, std::vector(width_, RGB())) {
}

int Image::Width() const {
    return width_;
}

int Image::Height() const {
    return height_;
}

int Image::GetXPixels() const {
    return x_pixels_per_m_;
}
int Image::GetYPixels() const {
    return y_pixels_per_m_;
}

RGB Image::GetRgb(int x, int y) const {
    // если мы на краю изображения, то используем самый близкий пиксель к краю
    if (x < 0) {
        x = 0;
    }
    if (y < 0) {
        y = 0;
    }
    if (x >= width_) {
        x = width_ - 1;
    }
    if (y >= height_) {
        y = height_ - 1;
    }
    return pixels_[y][x];
}

void Image::ChangePixel(const RGB& rgb, int x, int y) {
    pixels_[y][x] = rgb;
}

void Image::CopyImage(const Image& image_copy) {
    for (int i = 0; i < width_; ++i) {
        for (int j = 0; j < height_; ++j) {
            ChangePixel(image_copy.GetRgb(i, j), i, j);
        }
    }
}

void Image::ResizeImage(int width, int height) {
    width = std::min(width, width_);
    height = std::min(height, height_);
    Image cropped(width, height);
    for (int i = height_ - 1; i >= height_ - height; --i) {
        for (int j = 0; j < width; ++j) {
            cropped.ChangePixel(GetRgb(j, i), j, height - (height_ - i));
        }
    }

    width_ = width;
    height_ = height;
    CopyImage(cropped);
}

Image::~Image() = default;
