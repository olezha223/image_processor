#include <iostream>
#include "parser/parser.h"
#include <stdexcept>
#include <string_view>

int main(int argc, char** argv) {
    std::string_view help =
            "Welcome to my C++ project!\n"
            "The first command line argument is the path to the input file in .bmp format.\n"
            "The second command line argument is the path to the output file in .bmp format.\n"
            "Then you can apply filters.\n"
            "Options:\n"
            "-crop      requires 2 integer arguments. You can crop image using this filter.\n"
            "           The first argument sets width, the second sets height of output image.\n"
            "\n"
            "-gs        requires no arguments. You can convert colours to gray scale.\n"
            "\n"
            "-neg       requires no arguments. Applies negative filter.\n"
            "\n"
            "-sharp     requires no arguments. Makes image sharper.\n"
            "\n"
            "-edge      requires 1 float argument from 0 to 1. Detects edges.\n"
            "           The argument specifies the boundary after which the pixel is colored white.\n"
            "\n"
            "-blur      requires 1 float argument greater than 0. You can blur image using this filter.\n"
            "           The argument specifies the parameter of the standard deviation of the normal distribution.\n"
            "\n"
            "-sick      requires 2 float arguments from 0 to 100. An additional filter with which you can convert\n"
            "           the image to psychedelic colors and adjust the shear strength using the parameters.\n"
            "           The first argument sets vertical offset percent, the second sets horizontal offset percent\n";
    if (argc < 2) {
        // выведем справку
        std::cout << help;
        return 0;
    }
    if (argc == 2) {
        throw std::runtime_error("Add an output path");
    }

    Parser(argc, argv);
    return 0;
}
