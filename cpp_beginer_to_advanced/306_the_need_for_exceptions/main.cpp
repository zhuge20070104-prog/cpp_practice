#include <exception>
#include <iostream>
#include <string>

class Animal {
public:
    Animal() = default;
    virtual void breathe() const {
        std::cout << "Animal is breathing\n";
    }
private:
    std::string m_description {};
};


class Dog: public Animal {
public:
    Dog() = default;
    virtual void breathe() const override {
        std::cout << "Dog is breathing\n";
    }

    void run() const {
        std::cout << "Dog is running\n";
    }
private:
    std::string m_fur_color {};
};

int silent_exception() {
    int a = 8;
    int b = 0;

    if(b == 0) {
        throw "Division by zero detected from silent_exception()\n";
    }

    return a / b;
}

int main(int argc, char* argv[]) {
    const int a {2};
    const int b {0};

    try {
        if(!b) {
            throw 0;
        }
        std::cout << a/b << '\n';
    } catch(int ex) {
        std::cout << "Division by " << ex << " detected" << '\n';
    }

    try {
        Animal animal;
        Dog& dog_ref = dynamic_cast<Dog&>(animal);
        dog_ref.run();
    }catch(std::exception& ex) {
        std::cout << "An exception was thrown: " << ex.what() << '\n';
    } 

    try {
        silent_exception();
    }catch(const char* ex) {
        std::cout << "An exception was thrown: " << ex << '\n';
    }


    std::cout << "Run to here...\n";
    return EXIT_SUCCESS;
}