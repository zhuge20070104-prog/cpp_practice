#include <iostream>
#include <optional>
#include <string>


enum option_type_t {
    option_with_value,
    option_without_value,
    option_has_value
};

struct option_test_t {
    void option_with_value() {
        std::optional<int> items {3};
        std::optional<std::string> name {"Fredric Zhu"};
        std::optional<double> weight {77.2};
        std::optional<char> character {'s'};

        //Read from an std::optional variable
        std::cout << "items: " << items.value() << std::endl;
        // Personaly find this confusing as
        // it's not a pointer, so this the
        // first and last time I use it in the
        // course
        std::cout << "items: " << *items << std::endl;
        std::cout << "name: " << name.value() << std::endl;
        std::cout << "weight: " << weight.value() << std::endl;
        std::cout << "character: " << character.value() << std::endl;
    }

    void option_without_value() {
        //Declare and empty initialize
        // Initializes to std::nullopt
        std::optional<std::string> dog_name {};
        std::optional<int> age {std::nullopt};
        std::optional<char> letter = std::nullopt;
        std::optional<double> height = {};

        dog_name = "Fluffy";
        age = 26;
        std::cout << std::endl;
        std::cout << "Writting data in..." << std::endl;
        std::cout << "dog name: " << dog_name.value() << std::endl;
        std::cout << "age: " << age.value() << std::endl;
    }

    void option_has_value() {
        //Declare and empty initialize
        // Initializes to std::nullopt
        std::optional<std::string> dog_name {};
        std::optional<int> age {std::nullopt};
        std::optional<char> letter = std::nullopt;
        std::optional<double> height = {};

        dog_name = "Fluffy";
        age = 26;

        std::cout << std::boolalpha;
        std::cout << "letter.has_value(): " << letter.has_value() << std::endl;
        std::cout << "height.has_value(): " << height.has_value() << std::endl;
        std::cout << "dog_name.has_value(): " << dog_name.has_value() << std::endl;

        // Do your checks before you read data
        std::cout << std::endl;
        std::cout << "conditional reading" << std::endl;

        if(letter.has_value()) {
            std::cout << "letter contains a userful value" << std::endl;
        } else {
            std::cout << "letter contains std::nullopt" << std::endl;
        }

        //Checking against std::nullopt
        if(letter != std::nullopt) {
            std::cout << "letter contains a userful value" << std::endl;
        } else {
            std::cout << "letter contains std::nullopt" << std::endl;
        }

        //Checking against std::nullop
        if(dog_name != std::nullopt) {
            std::cout << "dog_name contains a useful value: " << dog_name.value() << std::endl;
        } else {
            std::cout << "dog_name contains std::nullopt" << std::endl;
        }
    }

    void operator()(option_type_t type_) {
        switch(type_) {
        case option_type_t::option_with_value:
            option_with_value();
            break;
        case option_type_t::option_without_value:
            option_without_value();
            break;
        case option_type_t::option_has_value:
            option_has_value();
            break;
        }
    }
};

int main()
{
    option_test_t op_test;
    op_test(option_type_t::option_with_value);
    op_test(option_type_t::option_without_value);
    op_test(option_type_t::option_has_value);

    return 0;
}
