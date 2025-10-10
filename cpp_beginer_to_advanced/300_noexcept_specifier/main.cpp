#include <iostream>

void somefunction() noexcept {
    try {
        throw 1;
    } catch(int ex) {
        std::cout << "int type exception handled\n";
        throw;
    }
}


class Item {
public:
    void do_something() const noexcept {
        try {
            throw 2;
        }catch(int ex) {
            std::cout << "Item handling an int exception\n";
            throw;
        }
    }
};
    

int main(int argc, char* argv[]) {
    // try {
    //     somefunction();
    // }catch(int ex) {
    //     std::cout << "main handling an int exception\n";
    // }

    Item item;
    item.do_something();
    return EXIT_SUCCESS;
}