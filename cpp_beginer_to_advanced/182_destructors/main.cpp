#include <iostream>
#include <string_view>


class Dog {

public:
    Dog() = default;
    Dog(std::string_view name, std::string_view breed, int age);
    ~Dog();
private:
    std::string m_name;
    std::string m_breed;
    int* m_p_age {nullptr};
};

Dog::Dog(std::string_view name, std::string_view breed, int age) {
    m_name = name;
    m_breed = breed;
    m_p_age = new int(age);
}

Dog::~Dog() {
    delete m_p_age;
    std::cout << m_name << " has been killed!\n";
}

void dog_destroyed() {
    Dog test {"test", "test", 0};

    Dog* p_test {new Dog("p_test", "test", 0)};
    delete p_test;
}

int main(int argc, char* argv[]) {
   
    Dog d1 {"Tom", "Desi", 2};
    Dog d2 {"Tom2", "Desi2", 4};

    dog_destroyed();

    std::cout << "main() died!\n";
    return EXIT_SUCCESS;
}

