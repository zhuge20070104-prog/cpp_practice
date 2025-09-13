#include <iostream>
#include <string>

enum op_t {
    EMPTY_FUNC,
    SIZE_FUNC,
    LENGTH_FUNC,
    STR_MAX_SIZE,
    STR_CAPACITY,
    UPDATE_CAPACITY,
    SHRINK_TO_FIT
};

struct str_size_and_cap_demo_t {
    void empty_func() {
        std::string str1 {"Hello world"};
        std::string str2;
        std::string str3;

        std::cout << std::endl;
        std::cout << "std::string::empty(): " << std::endl;

        std::cout << "str1 is empty: " << std::boolalpha << str1.empty() << std::endl;
        std::cout << "str2 is empty: " << std::boolalpha << str2.empty() << std::endl;
        std::cout << "str3 is empty: " << std::boolalpha << str3.empty() << std::endl;
    }

    void size_func() {
        std::string str1 {"Hello world"};
        std::string str2;
        std::string str3;
        std::cout << std::endl;
        std::cout << "std::string::size(): " << std::endl;
        std::cout << "str1 contains: " << str1.size() << " characters" << std::endl;
        std::cout << "str2 contains: " << str2.size() << " characters" << std::endl;
        std::cout << "syt3 contains: " << str3.size() << " characters" << std::endl;
    }

    void length_func() {
        std::string str1 {"Hello world"};
        std::string str2;
        std::string str3;
        std::cout << std::endl;
        std::cout << "std::string::length(): " << std::endl;
        std::cout << "str1 contains: " << str1.length() << " characters" << std::endl;
        std::cout << "str2 contains: " << str2.length() << " characters" << std::endl;
        std::cout << "syt3 contains: " << str3.length() << " characters" << std::endl;
    }

    void str_max_size() {
        //max_size : max number of characters a string can have on the system
        std::string str1 {"Hello world"};
        std::cout << "std::string can hold: " << str1.max_size() << " characters" << std::endl;
    }

    void str_capacity() {
        std::string str1 {"Hello world"};
        std::string str2;
        std::cout << "str1 capacity: " << str1.capacity() << std::endl;
        std::cout << "str2 capacity: " << str2.capacity() << std::endl;

        str1 = "The sky is so blue, the grass is green. Kids are running all over the place";
        std::cout << "str1 size: " << str1.size() << std::endl;
        std::cout << "str1 capacity: " << str1.capacity() << std::endl;
    }

    void update_capacity() {
        std::string str1 {"Hello world"};
        std::cout << "str1 capacity: " << str1.capacity() << std::endl;
        std::cout << "str1 size: " << str1.size() << std::endl;

        str1.reserve(100);
        std::cout << "str1 after reserve: " << str1 << std::endl;
        std::cout << "str1 capacity: " << str1.capacity() << std::endl;
        std::cout << "str1 size: " << str1.size() << std::endl;
    }

    void shrink_to_fit_demo() {
        std::string str1 {"Hello world"};
        str1.reserve(100);

        std::cout << "str1 capacity: " << str1.capacity() << std::endl;
        std::cout << "str1 size: " << str1.size() << std::endl;

        str1.shrink_to_fit();
        std::cout << "str1 capacity: " << str1.capacity() << std::endl;
        std::cout << "str1 size: " << str1.size() << std::endl;
    }

    void operator()(op_t type_) {
        switch (type_) {
        case EMPTY_FUNC:
            empty_func();
            break;
        case SIZE_FUNC:
            size_func();
        break;    
        case LENGTH_FUNC:
            length_func();
        break;
        case STR_MAX_SIZE:
            str_max_size();
        break;
        case STR_CAPACITY:
            str_capacity();
        break;
        case UPDATE_CAPACITY:
            update_capacity();
        break;
        case SHRINK_TO_FIT:
            shrink_to_fit_demo();
        break;
        default:
            break;
        }
    }
};

int main(int argc, char* argv[]) {
    str_size_and_cap_demo_t s_c_demo;
    s_c_demo(op_t::EMPTY_FUNC);
    s_c_demo(op_t::SIZE_FUNC);
    s_c_demo(op_t::LENGTH_FUNC);
    s_c_demo(op_t::STR_MAX_SIZE);
    s_c_demo(op_t::STR_CAPACITY);
    s_c_demo(op_t::UPDATE_CAPACITY);
    s_c_demo(op_t::SHRINK_TO_FIT);

    return EXIT_SUCCESS;
}