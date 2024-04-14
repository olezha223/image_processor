#include <cstring>
#include "parser.h"
#include <stdexcept>
#include "../image/image.h"
#include "../filters/base_filter.h"
#include "../filters/apply_matrix.h"
#include "../filters/crop.h"
#include "../filters/gray_scale.h"
#include "../filters/negative.h"
#include "../filters/sharpening.h"
#include "../filters/edge_detection.h"
#include "../filters/blur.h"
#include "../filters/my_filter.h"

void Parser(int argc, char** argv) {
    // чтение файла
    const char* input_path = argv[1];
    const char* output_path = argv[2];

    Image image = Image(input_path);

    // парсинг
    std::vector<Filter*> filters;
    for (int i = 3; i < argc; ++i) {
        if (strcmp(argv[i], "-crop") == 0) {
            if (i + 2 >= argc) {
                throw std::runtime_error("-crop requires 2 arguments");
            }
            char* width = argv[++i];
            char* height = argv[++i];
            if (!IsInt(width) || !IsInt(height)) {
                throw std::runtime_error("Arguments of -crop filter must be int");
            }
            filters.emplace_back(new Crop(atoi(width), atoi(height)));
        } else if (strcmp(argv[i], "-gs") == 0) {
            filters.emplace_back(new GrayScale());
        } else if (strcmp(argv[i], "-neg") == 0) {
            filters.emplace_back(new Negative());
        } else if (strcmp(argv[i], "-sharp") == 0) {
            filters.emplace_back(new Sharpening());
        } else if (strcmp(argv[i], "-edge") == 0) {
            if (i + 1 >= argc) {
                throw std::runtime_error("-edge requires 1 argument, 0 given");
            }
            char* threshold = argv[++i];
            if (!IsFloat(threshold)) {
                throw std::runtime_error("Argument of -edge filter must be float");
            }
            filters.emplace_back(new EdgeDetection(static_cast<float>(atof(threshold))));
        } else if (strcmp(argv[i], "-blur") == 0) {
            if (i + 1 >= argc) {
                throw std::runtime_error("-blur requires 1 argument, 0 given");
            }
            char* sigma = argv[++i];
            if (!IsFloat(sigma)) {
                throw std::runtime_error("Argument of -blur filter must be float");
            }
            filters.emplace_back(new GaussianBlur(static_cast<float>(atof(sigma))));
        } else if (strcmp(argv[i], "-sick") == 0) {
            if (i + 2 >= argc) {
                throw std::runtime_error("-sick requires 2 arguments");
            }
            char* vert = argv[++i];
            char* hor = argv[++i];
            if (!IsFloat(vert) || !IsFloat(hor)) {
                throw std::runtime_error("Arguments of -sick filter must be float");
            }
            filters.emplace_back(new SickEye(static_cast<float>(atof(vert)), static_cast<float>(atof(hor))));
        } else {
            throw std::runtime_error("Arguments passed incorrectly. Call the program without arguments to see help");
        }
    }
    // применение фильтров
    for (auto& filter : filters) {
        filter->Apply(image);
    }
    for (auto* filter : filters) {
        delete filter;
    }
    // сохранение файла
    SaveFile(output_path, image);
}
