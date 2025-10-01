#ifndef _FREDRIC_INTEGER_H_
#define _FREDRIC_INTEGER_H_

struct Integer {

    Integer() = default;
    Integer(int value): m_wrapped_int{value} {}

    int get() const { return m_wrapped_int; }
    bool operator==(const Integer& other) const { return m_wrapped_int == other.m_wrapped_int; }
    bool operator<(const Integer& other) const { return m_wrapped_int < other.m_wrapped_int; }
private: 
    int m_wrapped_int {};
};

#endif