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

    std::string get_name() const {
        return m_name;
    }

    std::string get_breed() const {
        return m_breed;
    }

    int get_age() const {
        return *(this->m_p_age);
    }

    void print_dog() const;

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

void Dog::print_dog() const {
   std::cout << "Dog: \n";
   std::cout << "Name: " << this->m_name << "\n";
   std::cout << "Breed: " << this->m_breed << "\n";
   std::cout << "Age: " << *(this->m_p_age) << "\n";
}



int main(int argc, char* argv[]) {
    const Dog d1 {"Lenn", "Pitbull", 5};
    std::cout << "Dog::age: " <<  d1.get_age() << std::endl;
    d1.print_dog();
    return EXIT_SUCCESS;
}

