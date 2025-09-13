#ifndef _FREDRIC_INTEGER_H_
#define _FREDRIC_INTEGER_H_

#include <iostream>

class Integer {

public:
    Integer();
    Integer(int value);
    Integer(Integer const& obj);
    Integer& operator=(Integer const& obj);
    Integer(Integer&& obj);
    Integer& operator=(Integer&& obj);

    Integer operator+(Integer const& a) const;

    // 左加操作符重载，加在自己身上
    Integer& operator++();

    explicit operator int();

    // 右加操作符重载，返回一个临时值，是加之前的值
    Integer operator++(int);

    bool operator==(Integer const& other);

    int get_value() const;
    void set_value(int value);
    ~Integer();
private:
    int* m_pint;
};

#endif