#include <iostream>
#include <memory>
#include "dog.h"


std::unique_ptr<Dog> get_unique_ptr() {
    std::unique_ptr<Dog> unique_dog {std::make_unique<Dog>("Dog from function")};
    return unique_dog;  // return ptr can be used as shared or unique ptr
}

int main(int argc, char* argv[]) {
   
    std::unique_ptr<int> unique_int {std::make_unique<int>(2)};
    std::unique_ptr<Dog> unique_dog {std::make_unique<Dog>("Jacob")};
    
    std::cout << "unique_int: " << unique_int << '\n';
    std::cout << "unique_dog: " << unique_dog << '\n';

    std::shared_ptr<int> shared_int{std::move(unique_int)};
    std::shared_ptr<Dog> shared_dog{std::move(unique_dog)};

    std::cout << "shared_int.use_count(): " << shared_int.use_count() << '\n';
    std::cout << "shared_dog.use_count(): " << shared_dog.use_count() << '\n';

    std::cout << "shared_int: " << shared_int << '\n';
    std::cout << "shared_dog: " << shared_dog << '\n';

    std::cout << "unique_int: " << unique_int << '\n';
    std::cout << "unique_dog: " << unique_dog << '\n';


    std::shared_ptr<int> shared_int_copy {shared_int};
    std::shared_ptr<Dog> shared_dog_copy {shared_dog};

    std::cout << "shared_int_copy.use_count(): " << shared_int_copy.use_count() << '\n';
    std::cout << "shared_dog_copy.use_count(): " << shared_dog_copy.use_count() << '\n';


    std::shared_ptr<Dog> dog_from_function {get_unique_ptr()};
    std::cout << "dog_from_function.use_count(): " << dog_from_function.use_count() << '\n';

    std::unique_ptr<Dog> dog_from_function_another {get_unique_ptr()};
    std::cout << "dog_from_function_another->get_name(): " << dog_from_function_another->get_name() << '\n';

    return EXIT_SUCCESS;
}

