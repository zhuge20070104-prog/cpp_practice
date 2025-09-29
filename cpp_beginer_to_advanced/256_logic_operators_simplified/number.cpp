#include "number.h"

std::ostream& operator<<(std::ostream& os, const Number& number) {
    os << "Number: " << number.get_wrappered_int();
    return os;
}

Number::Number(int value): m_wrappered_int{value} {}