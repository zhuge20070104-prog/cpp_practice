#ifndef _FREDRIC_ITEM_H_
#define _FREDRIC_ITEM_H_

#include <iostream>
#include <compare>
#include "integer.h"

class Item {
public:
    Item() = default;
    Item(int a, int b, int c): m_a{a}, m_b{b}, m_c{c} {}

    Item(int i): Item{i, i, i} {}

    std::strong_ordering operator<=>(const Item& other) const = default;

private:
    int m_a {};
    int m_b {};
    int m_c {};
    Integer m_i {};
};

#endif