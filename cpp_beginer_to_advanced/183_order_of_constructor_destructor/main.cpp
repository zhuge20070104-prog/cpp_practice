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

int main(int argc, char* argv[]) {
    Dog d1 {"Tom1", "Desi1", 2};
    Dog d2 {"Tom2", "Desi2", 4};
    Dog d3 {"Tom3", "Desi3", 8};
    Dog d4 {"Tom4", "Desi4", 16};
    return EXIT_SUCCESS;
}

