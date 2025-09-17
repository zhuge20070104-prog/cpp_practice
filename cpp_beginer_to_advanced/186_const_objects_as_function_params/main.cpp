#include <iostream>
#include <string_view>

class Dog {

public:
    Dog() = default;
    Dog(std::string_view name, std::string_view breed, int age);
    Dog(const Dog& other);
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

Dog::Dog(const Dog& other) {
    m_name = other.m_name;
    m_breed = other.m_breed;
    m_p_age = new int(*(other.m_p_age));
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

void take_by_value(Dog d) {
    d.set_age(2);
    d.print_dog();
}

void take_by_ref(Dog& d) {
    d.set_name("hell");
    d.print_dog();
}

void take_by_const_ref(Dog const& d) {
    d.set_name("hell");
    d.print_dog();
}

int main(int argc, char* argv[]) {
    const Dog d1 {"Lenn", "Pitbull", 5};
    take_by_value(d1);
    // take_by_ref(d1);
    // take_by_const_ref(d1);
    return EXIT_SUCCESS;
}

