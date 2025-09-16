#include <iostream>
#include <string_view>

class Dog {

public:
    Dog() = default;
    Dog(std::string_view name, std::string_view breed, int age);
    ~Dog();

    Dog* set_name(std::string_view name) {
        this->m_name = name;
        return this;
    }

    Dog* set_breed(std::string_view breed) {
        this->m_breed = breed;
        return this;
    }

    Dog* set_age(int age) {
        *(this->m_p_age) = age;
        return this;
    }

    void print_dog();

private:
    std::string m_name;
    std::string m_breed;
    int* m_p_age {nullptr};
};


Dog::Dog(std::string_view name, std::string_view breed, int age) {
    m_name = name;
    m_breed = breed;
    m_p_age = new int(age);
    std::cout << this << " created\n";
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
    const Dog d1 {"John", "Titi", 3};
    const Dog* d_ptr {&d1};
    const Dog& d_ref {d1};

    // d1.print_dog();
    // d_ptr->print_dog();
    // d_ref.print_dog();

    return EXIT_SUCCESS;
}

