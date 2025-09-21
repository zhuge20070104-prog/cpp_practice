#include <iostream>
#include <string>
#include <utility>

class Dog {

public:
    Dog(std::string name, unsigned int age):
    m_name{std::move(name)}, m_age{age} {}

    friend class Cat;    
private:
    std::string m_name;
    unsigned int m_age;
};


class Cat {

public:
    Cat(std::string name, unsigned int age):
    m_name{std::move(name)}, m_age{age} {}

    void show_dog_name_from_cat(Dog& dog) {
        dog.m_name = "Duffy";
        std::cout << dog.m_name << ", " << dog.m_age << '\n';
    }

private:
    std::string m_name;
    unsigned int m_age;
};



int main(int argc, char* argv[]) {
    Cat c1 {"Luna", 3};
    Dog d1 {"Fluffy", 4};
    
    // Cat can access and manipulate the dog - friendship
    c1.show_dog_name_from_cat(d1);

    return EXIT_SUCCESS;
}

