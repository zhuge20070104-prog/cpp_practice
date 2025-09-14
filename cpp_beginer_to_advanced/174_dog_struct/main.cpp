#include <iostream>
#include <string>


struct DogStruct {
public:
    DogStruct() = default;
    ~DogStruct() = default;

private:
    std::string m_name;
    std::string m_breed;
    int* p_age {nullptr};
};

class DogClass {
    DogClass() = default;
    ~DogClass() = default;

    std::string m_name;
    std::string m_breed;
    int* p_age {nullptr};
};


int main(int argc, char* argv[]) {
    // public members in the struct
    DogStruct d1;

    // constructor is private, so no object creation possible
    // DogClass d2;

    return EXIT_SUCCESS;
}

