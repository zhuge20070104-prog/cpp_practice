#include <iostream>
#include <memory>
#include "derived.h"

/**
在我明白问题了！这是一个关于虚函数默认参数的重要概念：
关键点：虚函数的默认参数是静态绑定的，而函数本身是动态绑定的。
在您的代码中：
Base::add()的默认参数是x=5, y=5
Derived::add()的默认参数是x=10, y=10
当通过基类指针或引用调用虚函数时：
函数的实现是动态选择的（调用Derived::add()）
默认参数值是静态选择的（使用Base类中定义的x=5, y=5）
所以：
结果：
函数执行：Derived::add() → 输出"Derived::add() called"
参数使用：Base的默认值 x=5, y=5
返回值：5 + 5 = 10
这就是为什么看到"Derived::add() called"但返回值是10而不是20的原因。
如果您想看到20的结果，可以直接通过Derived对象调用：
Derived derived2;
derived2.add();  // 这会使用Derived的默认参数(10,10)，返回20
这是C++虚函数默认参数的一个经典陷阱！
*/

int main(int argc, char* argv[]) {
    std::unique_ptr<Base> base_ptr = std::make_unique<Derived>();

    std::cout << "base_ptr->add(): " << base_ptr->add() << std::endl;

    Derived derived1;
    Base& base_ref {derived1};

    std::cout << "base_ref.add(): " << base_ref.add() << std::endl;


    Base base1;
    std::cout << "base1.add(): " << base1.add() << std::endl;

    Derived derived2;
    std::cout << "derived2.add(): " << derived2.add() << std::endl;


    Base base2 {Derived{}};
    std::cout << "base2.add(): " << base2.add() << std::endl;

    return EXIT_SUCCESS;
}