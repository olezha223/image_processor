#include "rgb.h"

RGB::RGB() : r_(0), g_(0), b_(0) {
}

RGB::RGB(float r, float g, float b) : r_(r), g_(g), b_(b) {
}

RGB& RGB::operator=(const RGB& rgb) = default;

RGB::~RGB() {
}
