#include "number.h"

Number::Number(int value): m_wrappered_int{value} {}


std::ostream& operator<<(std::ostream& out, const Number& number) {
    out << "Number: " << number.m_wrappered_int;
    return out;
}


Number operator+(const Number& left, const Number& right) {
    return {left.m_wrappered_int + right.m_wrappered_int};
}

Number operator-(const Number& left, const Number& right) {
    return {left.m_wrappered_int - right.m_wrappered_int};
}

Number operator*(const Number& left, const Number& right) {
    return {left.m_wrappered_int * right.m_wrappered_int};
}

Number operator/(const Number& left, const Number& right) {
    return {left.m_wrappered_int / right.m_wrappered_int};
}

Number operator%(const Number& left, const Number& right) {
    return {left.m_wrappered_int % right.m_wrappered_int};
}

