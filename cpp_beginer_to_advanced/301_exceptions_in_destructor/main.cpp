#include <iostream>

/*
 * class destructor have implicitly noexcept specifier attached to them
 *
 * noexcept(false) - to allow the class destructors to propagate the exception out of
 * them, not recommended
 */

class Item {
public:
    Item() = default;
    ~Item() {
        try {
            throw 1;
        } catch(int ex) {
            throw;
        }
    }
};
    

int main(int argc, char* argv[]) {
    try {
        Item item;
    } catch(int ex) {
        std::cout << "main:: int exception handled from destructor\n";
    }
    return EXIT_SUCCESS;
}