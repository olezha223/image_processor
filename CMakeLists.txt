cmake_minimum_required(VERSION 3.27)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        image_processor
        image_processor.cpp
        filters/apply_matrix.cpp
        filters/base_filter.cpp
        filters/blur.cpp
        filters/crop.cpp
        filters/edge_detection.cpp
        filters/gray_scale.cpp
        filters/my_filter.cpp
        filters/negative.cpp
        filters/sharpening.cpp
        image/image.cpp
        image/open_save.cpp
        image/rgb.cpp
        tests/test_read_save.cpp
        parser/parser.cpp
        tests/test_filters.cpp
)
