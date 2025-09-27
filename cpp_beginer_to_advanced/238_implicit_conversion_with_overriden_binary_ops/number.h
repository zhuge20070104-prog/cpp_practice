#ifndef _FREDRIC_NUMBER_H_
#define _FREDRIC_NUMBER_H_


class Number {
    friend std::ostream& operator<<(std::ostream& out, const Number& number); 
    friend Number operator+(const Number& left, const Number& right);
    friend Number operator-(const Number& left, const Number& right);
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
   
private:
    int m_wrappered_int{};
};

#endif