#include <cstring>
#include "fstream"
#include "open_save.h"

void CreateFileHeader(unsigned char *file_header, const int file_size) {
    file_header[0] = 'B';
    file_header[1] = 'M';
    file_header[2] = file_size;
    file_header[3] = file_size >> 8;   // NOLINT
    file_header[4] = file_size >> 16;  // NOLINT
    file_header[5] = file_size >> 24;  // NOLINT
    for (int i = 6; i < 14; ++i) {     // NOLINT
        if (i == 10) {                 // NOLINT
            file_header[i] = FILE_HEADER_SIZE + INFO_HEADER_SIZE;
            continue;
        }
        file_header[i] = 0;
    }
}

void CreateInfoHeader(unsigned char *info_header, const int file_size, int width, int height, int x_pixels,
                      int y_pixels) {
    info_header[0] = INFO_HEADER_SIZE;
    info_header[1] = 0;
    info_header[2] = 0;
    info_header[3] = 0;

    info_header[4] = width;
    info_header[5] = width >> 8;   // NOLINT
    info_header[6] = width >> 16;  // NOLINT
    info_header[7] = width >> 24;  // NOLINT

    info_header[8] = height;         // NOLINT
    info_header[9] = height >> 8;    // NOLINT
    info_header[10] = height >> 16;  // NOLINT
    info_header[11] = height >> 24;  // NOLINT

    info_header[12] = 1;  // NOLINT
    info_header[13] = 0;  // NOLINT

    info_header[14] = 24;            // NOLINT
    for (int i = 15; i < 21; ++i) {  // NOLINT
        info_header[i] = 0;
    }
    info_header[21] = file_size >> 8;   // NOLINT
    info_header[22] = file_size >> 16;  // NOLINT
    info_header[23] = file_size >> 24;  // NOLINT

    info_header[24] = x_pixels;        // NOLINT
    info_header[25] = x_pixels >> 8;   // NOLINT
    info_header[26] = x_pixels >> 16;  // NOLINT
    info_header[27] = x_pixels >> 24;  // NOLINT

    info_header[28] = y_pixels;                    // NOLINT
    info_header[29] = y_pixels >> 8;               // NOLINT
    info_header[30] = y_pixels >> 16;              // NOLINT
    info_header[31] = y_pixels >> 24;              // NOLINT
    for (int i = 32; i < INFO_HEADER_SIZE; ++i) {  // NOLINT
        info_header[i] = 0;
    }
}

void SaveFile(const char *path, Image &image) {
    const char *ending = "bmp";
    if (std::strncmp(path + std::strlen(path) - 3, ending, 3) != 0 || std::strlen(path) < 3) {
        throw std::runtime_error("Output file must be .bmp");
    }
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);
    if (!f.is_open()) {
        throw std::runtime_error("File can't be saved");
    }
    unsigned char padding[3] = {0, 0, 0};
    const int count_paddings = ((4 - (image.Width() * 3) % 4) % 4);
    const int file_size =
        FILE_HEADER_SIZE + INFO_HEADER_SIZE + image.Width() * image.Height() * 3 + count_paddings * image.Height();
    unsigned char file_header[FILE_HEADER_SIZE];
    unsigned char info_header[INFO_HEADER_SIZE];
    CreateFileHeader(file_header, file_size);
    CreateInfoHeader(info_header, file_size, image.Width(), image.Height(), image.GetXPixels(), image.GetYPixels());
    f.write(reinterpret_cast<char *>(file_header), FILE_HEADER_SIZE);
    f.write(reinterpret_cast<char *>(info_header), INFO_HEADER_SIZE);
    RGB temp;
    for (int y = 0; y < image.Height(); ++y) {
        for (int x = 0; x < image.Width(); ++x) {
            temp = image.GetRgb(x, y);
            auto pixel_r = static_cast<unsigned char>(temp.r_ * 255.0f);  // NOLINT
            auto pixel_g = static_cast<unsigned char>(temp.g_ * 255.0f);  // NOLINT
            auto pixel_b = static_cast<unsigned char>(temp.b_ * 255.0f);  // NOLINT

            unsigned char pixel_color[3] = {pixel_b, pixel_g, pixel_r};
            f.write(reinterpret_cast<char *>(pixel_color), 3);
        }
        f.write(reinterpret_cast<char *>(padding), count_paddings);
    }
    f.close();
}

void Image::Read(const char *path) {
    std::ifstream f;
    f.open(path, std::ios::in | std::ios::binary);
    if (!f.is_open()) {
        throw std::runtime_error("File can't be read");
    }
    unsigned char file_header[FILE_HEADER_SIZE];
    unsigned char info_header[INFO_HEADER_SIZE];
    f.read(reinterpret_cast<char *>(file_header), FILE_HEADER_SIZE);
    f.read(reinterpret_cast<char *>(info_header), INFO_HEADER_SIZE);
    if (file_header[0] != 'B' || file_header[1] != 'M') {
        throw std::runtime_error("Not a BMP file");
    }
    width_ = (info_header[4]) + (info_header[5] << 8) + (info_header[6] << 16)    // NOLINT
             + (info_header[7] << 24);                                            // NOLINT
    height_ = (info_header[8]) + (info_header[9] << 8) + (info_header[10] << 16)  // NOLINT
              + (info_header[11] << 24);                                          // NOLINT
    x_pixels_per_m_ =
        (info_header[24]) + (info_header[25] << 8) + (info_header[26] << 16) + (info_header[27] << 24);  // NOLINT
    y_pixels_per_m_ =
        (info_header[28]) + (info_header[29] << 8) + (info_header[30] << 16) + (info_header[31] << 24);  // NOLINT
    pixels_.resize(height_);
    for (auto &row : pixels_) {
        row.resize(width_);
    }
    const int count_paddings = ((4 - (width_ * 3) % 4) % 4);
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            unsigned char pixel_color[3];
            f.read(reinterpret_cast<char *>(pixel_color), 3);
            pixels_[y][x].r_ = static_cast<float>(pixel_color[2]) / 255.0f;  // NOLINT
            pixels_[y][x].g_ = static_cast<float>(pixel_color[1]) / 255.0f;  // NOLINT
            pixels_[y][x].b_ = static_cast<float>(pixel_color[0]) / 255.0f;  // NOLINT
        }
        f.ignore(count_paddings);
    }
    f.close();
}

Image::Image(const char *path) {
    Read(path);
}
