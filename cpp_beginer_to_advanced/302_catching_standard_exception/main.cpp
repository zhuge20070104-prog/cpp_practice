#include <iostream>
#include <string>
#include <string_view>
#include <exception>


class Animal {
public:
    Animal(std::string_view name): m_name{name} {}
    Animal() = default;
    virtual ~Animal() = default;
    virtual void breathe() const {
        std::cout << "Animal is breathing\n";
    }
protected:
    std::string m_name{};
};

class Feline: public Animal {
public:
    Feline(std::string_view name, int speed): Animal(name), m_speed{speed} {}
private:
    int m_speed{};
};

int main(int argc, char* argv[]) {
    Animal animal;

    try {
        Feline& feline {dynamic_cast<Feline&>(animal)};
    } catch(std::exception& ex) {
        std::cout << "Something is wrong: " << ex.what() << std::endl;
    }
    return EXIT_SUCCESS;
}