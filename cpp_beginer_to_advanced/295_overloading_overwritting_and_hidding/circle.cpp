#include "circle.h"

Circle::Circle(double radius, std::string_view desc):
    Oval(radius, radius, desc) {}

Circle::~Circle() {}