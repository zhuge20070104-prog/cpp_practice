#include <iostream>
#include <memory>
#include "dog.h"


int main(int argc, char* argv[]) {
   
    // Shared ptr with foundamental types
    {
        std::shared_ptr<int> shared_int {new int{6}};

        // dereference possible
        // 打印解引用的shared_ptr值
        std::cout << "*shared_int: " << *shared_int << std::endl;

        ++(*shared_int);
        // 打印递增后的shared_ptr值
        std::cout << "*shared_int (after increment): " << *shared_int << std::endl;


        // reference count - total shared ptrs to the shared int
        // 打印引用计数（指向同一个对象的shared_ptr数量）
        std::cout << "shared_int.use_count(): " << shared_int.use_count() << '\n';

        // copy allowed
        std::shared_ptr<int> shared_int_copy {shared_int};
        // 打印复制后的shared_ptr解引用值
        std::cout << "*shared_int_copy: " << *shared_int_copy << '\n';

        // reference count is incremented on copying
        // 打印复制后原shared_ptr的引用计数
        std::cout << "shared_int.use_count() (after copy): " << shared_int.use_count() << '\n';
        // 打印复制后新shared_ptr的引用计数
        std::cout << "shared_int_copy.use_count(): " << shared_int_copy.use_count() << '\n';

        // both are accessing the same memory
        // 打印两个shared_ptr的原始指针地址（应该相同）
        std::cout << "shared_int: " << shared_int << " shared_int_copy: " << shared_int_copy << '\n';
    }


    {
        std::shared_ptr<int> shared_int {new int{99}};

        // initializing the shared_ptr to null
        std::shared_ptr<int> init_to_null;
        // 打印未初始化的shared_ptr（应该为nullptr）
        std::cout << "init_to_null (uninitialized): " << init_to_null << '\n';

        // 2 shared ptrs to an int data
        init_to_null = shared_int;
        // 打印赋值后init_to_null的引用计数
        std::cout << "init_to_null.use_count() (after assignment): " << init_to_null.use_count() << '\n';
        // 打印赋值后shared_int的引用计数
        std::cout << "shared_int.use_count() (after assignment): " << shared_int.use_count() << '\n';

        // explicit init to nullptr
        std::shared_ptr<int> init_to_null_again {nullptr};
        // 打印显式初始化为nullptr的shared_ptr
        std::cout << "init_to_null_again (explicit nullptr): " << init_to_null_again << '\n';

        init_to_null_again = init_to_null;

        ++(*init_to_null);

        // 打印递增后的init_to_null解引用值
        std::cout << "*init_to_null (after increment): " << *init_to_null << '\n';
        // 打印init_to_null_again的解引用值（应该与上面相同）
        std::cout << "*init_to_null_again: " << *init_to_null_again << '\n';

        // shared ptr to existing data
        // existing ptr will be not be released automatically

        int* existing_int {new int{82}};
        std::shared_ptr<int> shared_to_existing {existing_int};

        // necessary 
        existing_int = nullptr;

        // 打印指向已存在数据的shared_ptr解引用值
        std::cout << "*shared_to_existing: " << *shared_to_existing << '\n';
        // 打印指向已存在数据的shared_ptr引用计数
        std::cout << "shared_to_existing.use_count(): " << shared_to_existing.use_count() << '\n';

        // 打印原始指针（应该为nullptr）
        std::cout << "existing_int (after set to nullptr): " << existing_int << '\n';
        // 打印shared_ptr的原始指针地址
        std::cout << "shared_to_existing.get(): " << shared_to_existing.get() << '\n';
        // 再次打印shared_ptr的引用计数
        std::cout << "shared_to_existing.use_count() (again): " << shared_to_existing.use_count() << '\n';

        // reset will decrement the reference count
        shared_int.reset();
        // 打印reset后的shared_int原始指针（应该为nullptr）
        std::cout << "shared_int.get() (after reset): " << shared_int.get() << '\n';
        // 打印reset后的shared_int引用计数（应该为0）
        std::cout << "shared_int.use_count() (after reset): " << shared_int.use_count() << '\n';
        // 打印init_to_null的引用计数（应该减少1）
        std::cout << "init_to_null.use_count() (after shared_int reset): " << init_to_null.use_count() << '\n';
        // 打印init_to_null_again的引用计数（应该减少1）
        std::cout << "init_to_null_again.use_count() (after shared_int reset): " << init_to_null_again.use_count() << '\n';
        
    }


    // shared_ptr with custom type
    std::shared_ptr<Dog> shared_dog1 {new Dog {"shared_dog1"}};
    std::shared_ptr<Dog> shared_dog2 {shared_dog1};

    std::cout << "shared_dog1.use_count(): " << shared_dog1.use_count() << '\n';
    std::cout << "shared_dog2.use_count(): " << shared_dog2.use_count() << '\n';

    shared_dog2.reset();

    std::cout << "shared_dog1.use_count(): " << shared_dog1.use_count() << '\n';
    std::cout << "shared_dog2.use_count(): " << shared_dog2.use_count() << '\n';

    shared_dog2 = shared_dog1;

    std::shared_ptr<Dog> shared_dog3;
    std::cout << "shared_dog3.use_count(): " << shared_dog3.use_count() << '\n';

    shared_dog3 = shared_dog1;
    std::cout << "shared_dog3.use_count(): " << shared_dog3.use_count() << '\n';

    std::shared_ptr<Dog> shared_dog4 {nullptr};
    std::cout << "shared_dog4.use_count(): " << shared_dog4.use_count() << '\n';
    shared_dog4 = shared_dog3;

    std::cout << "shared_dog1.use_count(): " << shared_dog1.use_count() << '\n';
    std::cout << "shared_dog2.use_count(): " << shared_dog2.use_count() << '\n';
    std::cout << "shared_dog4.use_count(): " << shared_dog4.use_count() << '\n';
    std::cout << "shared_dog3.use_count(): " << shared_dog3.use_count() << '\n';

    Dog* raw_dog {new Dog{"raw_dog"}};

    std::shared_ptr<Dog> shared_to_raw_dog {raw_dog};
    // necessary
    raw_dog = nullptr;

    shared_to_raw_dog->print_dog();

    std::cout << "raw_dog: " << raw_dog << '\n';


    // use make_shared to avoid using new operator
    std::shared_ptr<Dog> make_shared_dog {std::make_shared<Dog>("make_shared_dog")};

    make_shared_dog->print_dog();

    std::cout << "make_shared_dog.use_count(): " << make_shared_dog.use_count() << '\n';

    std::shared_ptr<Dog> make_shared_dog_copy {nullptr};
    make_shared_dog_copy = make_shared_dog;

    std::cout << "make_shared_dog_copy.use_count(): " << make_shared_dog_copy.use_count() << '\n';
    std::cout << "make_shared_dog.use_cout(): " << make_shared_dog.use_count() << '\n';

    make_shared_dog.reset();

    std::cout << "make_shared_dog_copy.use_count(): " << make_shared_dog_copy.use_count() << '\n';


    
    
    

    
    return EXIT_SUCCESS;
}

