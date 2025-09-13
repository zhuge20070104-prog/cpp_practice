#include <iostream>
#include <string>
#include "gtest/gtest.h"
#include "products.hpp"


GTEST_TEST(OopTest, TestInheritance) {
    Product apple {"Apple", Color::green, Size::small};
    Product tree {"Tree", Color::green, Size::large};
    Product house {"House", Color::blue, Size::large};

    std::vector<Product*> items{&apple, &tree, &house};

    auto size_spec = SizeSpec(Size::large);
    auto color_spec = ColorSpec(Color::green);
    auto spec = color_spec && size_spec;
    
    // 这里不能这么写，写成右值往后面走的话，因为在AndSpec里面用了引用
    // 就会在某一时刻被析构掉，导致segment fault
    // 如果不用引用， Specification基类就没法使用纯虚函数接口
    // auto spec = ColorSpec(Color::green) && SizeSpec(Size::large);

    auto bf = BetterFilter();
    for(auto const& item: bf.filter(items, spec)) {
        std::cout << item->name << " is green and large\n";
    }
}

