#ifndef _FREDRIC_NUMBER_H_
#define _FREDRIC_NUMBER_H_

#include "point.h"

class Number {
    friend std::ostream& operator<<(std::ostream& out, const Number& number); 
    // friend Number operator+(const Number& left, const Number& right);
    // friend Number operator-(const Number& left, const Number& right);
    friend Number operator*(const Number& left, const Number& right);
    friend Number operator/(const Number& left, const Number& right);
    friend Number operator%(const Number& left, const Number& right);

public:
    Number() = default;
    Number(int value);

    int get_wrappered_int() const {
        return m_wrappered_int;
    }

    ~Number() {}
    Number operator+(const Number& right) {
        return {m_wrappered_int + right.m_wrappered_int};
    }

    Number operator-(const Number& right) {
        return {m_wrappered_int - right.m_wrappered_int};
    }

    operator double() const {
        std::cout << "Using the member double() to convert\n";
        return static_cast<double>(m_wrappered_int);
    }

    operator Point() const {
        std::cout << "Using the member Point() to convert\n";
        return Point{static_cast<double>(m_wrappered_int),
             static_cast<double>(m_wrappered_int),
             m_wrappered_int};
    }
private:
    int m_wrappered_int{};
};

#endif