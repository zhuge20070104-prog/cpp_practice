#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdio>
#include <sstream>
#include "gtest/gtest.h"
#include "log.hpp"
// 抽象类:
// 1. 至少有一个纯虚函数
// 2. 可以有其他成员，例如数据，非虚函数等
// 3. 不能被实例化，可以通过指针或引用来使用
// 4. 用来根客户建立一个合约
// 5. 被用来创建接口

// 纯虚函数
// 1. 使用=0标记的虚函数
// 2. 没有实现
// 3. 不能被调用，除非被子类实现了，使用子类的对象进行调用
// 4. 纯虚函数在抽象类的vtable里面没有，在子类的vtable里面有
// 5. 必须被子类实现才能使用

class Document {
public:
    virtual void serialize(float version) = 0;
};

class Text: public Document {
public:
    void serialize(float version) override final {
        std::cout << "Text::serialize\n";
    }
};

class RichText: public Text {
    // 不能override serialize，因为serialize是final的了
};

class XML: public Document {
public:
    void serialize(float version) override {
        std::cout << "XML::serialize()\n";
    }
};

void write(Document* p) {
    p->serialize(1.1f);
}

GTEST_TEST(OopTest, TypeidBasics) {
   XML xml;
   write(&xml);
}

