#include <iostream>
#include <string_view>

class Dog {

public:
    Dog() = default;
    Dog(std::string_view name, std::string_view breed, int age);
    Dog(const Dog& other);
    ~Dog();

    std::string& name() {
        return m_name;
    }

    const std::string& name() const {
        return m_name;
    }

    std::string& breed() {
        return m_breed;
    }

    unsigned int& age() {
        return *(this->m_p_age);
    }

    void print_dog();

private:
    std::string m_name;
    std::string m_breed;
    unsigned int* m_p_age {nullptr};
};


Dog::Dog(std::string_view name, std::string_view breed, int age) {
    m_name = name;
    m_breed = breed;
    m_p_age = new unsigned int(age);
    std::cout << this << " created\n";
}

Dog::Dog(const Dog& other) {
    m_name = other.m_name;
    m_breed = other.m_breed;
    m_p_age = new unsigned int(*(other.m_p_age));
    std::cout << this << " created by copy\n";
}

Dog::~Dog() {
    delete m_p_age;
    std::cout << this << "  destroyed!\n";
}

void Dog::print_dog() {
   std::cout << "Dog: \n";
   std::cout << "Name: " << this->m_name << "\n";
   std::cout << "Breed: " << this->m_breed << "\n";
   std::cout << "Age: " << *(this->m_p_age) << "\n";
}



int main(int argc, char* argv[]) {
    Dog dog {"Tom", "Lebra", 3};
    dog.print_dog();

    dog.name() = "Gom";
    dog.breed() = "Debra";
    dog.age() = 2;

    dog.print_dog();

    const Dog d1 {"test", "tet", 22};
    std::cout << "d1.name(): " << d1.name() << std::endl;

    return EXIT_SUCCESS;
}

