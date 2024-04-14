#include <iostream>
#include <stdexcept>
#include "../image/image.h"
#include "../filters/base_filter.h"
#include "../filters/crop.h"
#include "../filters/gray_scale.h"
#include "../filters/negative.h"
#include "../filters/sharpening.h"
#include "../filters/edge_detection.h"
#include "../filters/blur.h"
#include "../filters/my_filter.h"

void TestFilters() {
    try {
        Filter* filter = new Crop(-100, 100);  // NOLINT
        delete filter;
    } catch (const std::runtime_error& ex) {
        std::cerr << "CROP TEST: Caught expected exception: " << ex.what() << std::endl;
    }

    try {
        Filter* filter = new GrayScale();
        delete filter;
        std::cout << "GRAYSCALE TEST: PASSED" << std::endl;
    } catch (const std::runtime_error& ex) {
        std::cerr << "GRAYSCALE TEST: Caught unexpected exception: " << ex.what() << std::endl;
    }

    try {
        Filter* filter = new Negative();
        delete filter;
        std::cout << "NEGATIVE TEST: PASSED" << std::endl;
    } catch (const std::runtime_error& ex) {
        std::cerr << "NEGATIVE TEST: Caught unexpected exception: " << ex.what() << std::endl;
    }

    try {
        Filter* filter = new Sharpening();
        delete filter;
        std::cout << "SHARP TEST: PASSED" << std::endl;
    } catch (const std::runtime_error& ex) {
        std::cerr << "SHARP TEST: Caught unexpected exception: " << ex.what() << std::endl;
    }

    try {
        Filter* filter = new EdgeDetection(-100);  // NOLINT
        delete filter;
    } catch (const std::runtime_error& ex) {
        std::cerr << "EDGE TEST: Caught expected exception: " << ex.what() << std::endl;
    }

    try {
        Filter* filter = new GaussianBlur(-100);  // NOLINT
        delete filter;
    } catch (const std::runtime_error& ex) {
        std::cerr << "BLUR TEST: Caught expected exception: " << ex.what() << std::endl;
    }

    try {
        Filter* filter = new SickEye(-100, 10000);  // NOLINT
        delete filter;
    } catch (const std::runtime_error& ex) {
        std::cerr << "SICK TEST: Caught expected exception: " << ex.what() << std::endl;
    }
}
