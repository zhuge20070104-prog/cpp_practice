#include <iostream>
#include <string>
#include <string_view>
#include <exception>
#include <memory>

class Item {
public:
    Item() {
        std::cout << "Item constructor called\n";
    }
    ~Item() {
        std::cout << "Item destructor called\n";
    }
};

class Incopyable {
public:
    Incopyable() = default;
    Incopyable(const Incopyable&) = delete;
};

int main(int argc, char* argv[]) {
    int a{9};
    int b{0};

    try {
        Item item;
        if(b == 0) {
            throw b;
        }
        std::cout << "Try block exited\n";
    } catch (int exception) {
        std::cout << "b can't be a " << exception << std::endl;
    }

    int c {0};

    try {
        int var {20};
        int* p_var {&var};
        if(!c) {
            throw p_var;
        }
    }catch(int* p_ex) {
        std::cout << "c can't be zero(pointer): " << *p_ex << std::endl;
    }

    try {
        std::shared_ptr<Item> p_item {std::make_shared<Item>()};
        if(c == 0) {
            throw 0;
        }
    }catch(int ex) {
        std::cout << "c can't be zero(shared_ptr): " << ex << std::endl;
    }

    // try {
    //     Incopyable i;
    //     throw i;
    // } catch(Incopyable& i) {
    //     std::cout << "Class is not copyable\n";
    // }
    return EXIT_SUCCESS;
}