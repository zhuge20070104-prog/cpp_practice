#ifndef _FREDRIC_NUMBER_H_
#define _FREDRIC_NUMBER_H_

#include <iostream>

class Number {
    friend std::ostream& operator<<(std::ostream& os, const Number& number);

public:
    Number() = delete;
    explicit Number(int value);

    ~Number() = default;

    int get_wrappered_int() const { return m_wrappered_int; }

    friend auto operator<=>(const Number& left, const Number& right);
    friend auto operator<=>(int left, const Number& right);

    friend bool operator==(const Number& left, const Number& right);
    friend bool operator==(int left, const Number& right);

private:
    int m_wrappered_int{0};
};

inline auto operator<=>(const Number& left, const Number& right) {
    return (left.get_wrappered_int() <=> right.get_wrappered_int());
}

inline auto operator<=>(int left, const Number& right) {
    return (left <=> right.get_wrappered_int());
}

inline bool operator==(const Number& left, const Number& right) {
    return (left.get_wrappered_int() == right.get_wrappered_int());
}

inline bool operator==(int left, const Number& right) {
    return (left == right.get_wrappered_int());
}

#endif