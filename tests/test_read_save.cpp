#include <cassert>
#include <stdexcept>
#include <iostream>
#include "../image/image.h"
#include "../image/open_save.h"

void TestRead() {
    try {
        Image image = Image(R"(../image/image.h)");
        assert(false && "FIRST TEST: Expected exception not thrown!");
    } catch (const std::runtime_error& ex) {
        std::cerr << "FIRST TEST: Caught expected exception: " << ex.what() << std::endl;
    }
    try {
        Image image = Image(R"(../test_script/data/flag.bmp)");
        assert(true);
    } catch (const std::runtime_error& ex) {
        std::cerr << "SECOND TEST: Caught unexpected exception: " << ex.what() << std::endl;
    }
}

void TestSave() {
    Image image = Image(1, 1);
    try {
        SaveFile(R"(../image/image.h)", image);
        assert(false && "FIRST TEST: Expected exception not thrown!");
    } catch (const std::runtime_error& ex) {
        std::cerr << "FIRST TEST: Caught expected exception: " << ex.what() << std::endl;
    }
    try {
        SaveFile(R"(../test_script/data/flag.bmp)", image);
        assert(true);
    } catch (const std::runtime_error& ex) {
        std::cerr << "SECOND TEST: Caught unexpected exception: " << ex.what() << std::endl;
    }
}