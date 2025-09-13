#include <iostream>
#include <cstring>

enum op_t {
    STR_CONCAT,
    STR_CONCAT_MORE,
    STR_N_CAT,
    STR_COPY,
    STR_N_COPY
};

struct c_string_demo {

    void str_concat_demo() {
        std::cout << std::endl;
        std::cout << "std::strcat: " << std::endl;

        char dest[50] = "Hello ";
        char src[50] = "World!";
        std::strcat(dest, src);
        std::cout << "dest: " << dest << std::endl;
        std::strcat(dest, " Goodbye world!");
        std::cout << "dest: " << dest << std::endl;
    }

    void str_concat_more() {
        std::cout << std::endl;
        std::cout << "More std::strcat: " << std::endl;
        char* dest1 = new char[30]{'F','i','r','e','l','o','r','d','\0'};
        char* source1 = new char[30] {',','T','h','e',' ','P','h','e','n','i','x',' ','K','i','n','g','!','\0'};

        //NOTE TO SELF : 
        //Describe what's going to happen in std::strcat before you do the cat :
        //source is going to be appended to dest, and the process
        //will start by overriding the null character in dest

        std::cout << "std::strlen(dest1): " << std::strlen(dest1) << std::endl;
        std::cout << "std::strlen(source1): " << std::strlen(source1) << std::endl;

        std::cout << "Concatenating..." << std::endl;
        std::strcat(dest1, source1);

        std::cout << "std::strlen(dest1): " << std::strlen(dest1) << std::endl;
        std::cout << "dest1: " << dest1 << std::endl;
        delete [] dest1;
        delete [] source1;
    
    }

    void str_n_cat() {
        //std::strncat  : concatenates n characters from src to dest and
        //returns a pointer to the result string
        //signature : char *strncat( char *dest, const char *src, std::size_t count );
        std::cout << std::endl;
        std::cout << "std::strncat: " << std::endl;
        char dest2[50] {"Hello"};
        char source2[30] {"There is a bird on my window"};
        
        std::cout << std::strncat(dest2, source2, 6) << std::endl;

        std::strncat(dest2, source2, 6);
        std::cout << "The concatenated string is: " << dest2 << std::endl;
    }

    void str_copy() {
        //std::strcpy - signature : char* strcpy( char* dest, const char* src );
        std::cout << std::endl;
        std::cout << "std::strcpy: " << std::endl;
        char const* source3 = "C++ is a multipurpose programming language.";
        
        // +1 for the null character
        //Contains garbage data
        //Not initialized
        char* dest3 = new char[std::strlen(source3) + 1]; 
        std::strcpy(dest3, source3);
        std::cout << "sizeof(dest3): " << sizeof(dest3) << std::endl;
        std::cout << "std::strlen(dest3): " << std::strlen(dest3) << std::endl;
        std::cout << "dest3: " << dest3 << std::endl;
        delete [] dest3;
    }

    void str_n_copy() {
        //std::strncpy : Copy n characters from src to dest -
        //signature : char *strncpy( char *dest, const char *src, std::size_t count );
        std::cout << std::endl;
        std::cout << "std::strncpy: " << std::endl;
        char const* source4 = "Hello";
        
        // Have to put the terminating
        //null char if we want to print
        char dest4[] = {'a', 'b', 'c', 'd', 'e', 'f','\0'};  
        std::cout << "dest4: " << dest4 << std::endl;
        std::cout << "Copying..." << std::endl;
        std::strncpy(dest4, source4, 5);
        std::cout << "dest4: " << dest4 << std::endl;
    }

    void operator()(op_t type_) {
        switch (type_) {
        case STR_CONCAT:
            str_concat_demo();
            break;
        case STR_CONCAT_MORE:
            str_concat_more();
            break;
        case STR_N_CAT:
            str_n_cat();
            break;
        case STR_COPY:
            str_copy();
            break;
        case STR_N_COPY:
            str_n_copy();
            break;
        default:
            break;
        }
    }
};
int main(int argc, char* argv[]) {
    c_string_demo c_s_demo;
    c_s_demo(op_t::STR_CONCAT);
    c_s_demo(op_t::STR_CONCAT_MORE);
    c_s_demo(op_t::STR_N_CAT);
    c_s_demo(op_t::STR_COPY);
    c_s_demo(op_t::STR_N_COPY);
    return EXIT_SUCCESS;
}