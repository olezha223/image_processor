#pragma once
#include "image.h"

static const int FILE_HEADER_SIZE = 14;
static const int INFO_HEADER_SIZE = 40;

void CreateFileHeader(unsigned char *file_header, const int file_size);

void CreateInfoHeader(unsigned char *info_header, const int file_size, int width, int height, int x_pixels,
                      int y_pixels);

void SaveFile(const char *path, Image &image);
