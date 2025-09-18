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
   
    void print_dog() const;

private:
    std::string m_name;
    std::string m_breed;
    unsigned int* m_p_age {nullptr};
    mutable std::size_t print_is_called {};
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


void Dog::print_dog() const{
    // modifiable in a const member function - specified as 
    ++print_is_called;
    std::cout << "Print is called: " << print_is_called << " times\n";
}



int main(int argc, char* argv[]) {
    Dog dog {"test", "test", 1};
    dog.print_dog();
    dog.print_dog();
    dog.print_dog();
    dog.print_dog();

    return EXIT_SUCCESS;
}

