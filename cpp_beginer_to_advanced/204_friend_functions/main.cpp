#include <iostream>
#include <string>
#include <utility>

class Dog {

public:
    Dog(std::string name, unsigned int age):
    m_name{std::move(name)}, m_age{age} {}

    // declaring the outer function as friend of the class
    friend void dog_by_ref(const Dog& dog);
private:
    std::string m_name;
    unsigned int m_age;
};


void dog_by_ref(const Dog& dog) {
    // function can access the private members now
    std::cout << dog.m_name << ", " << dog.m_age << '\n';
}


int main(int argc, char* argv[]) {
   
    Dog d1 {"Jim", 2};
    dog_by_ref(d1);

    return EXIT_SUCCESS;
}

