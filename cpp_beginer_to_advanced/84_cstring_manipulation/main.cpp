#include <iostream>
#include <cstring>

enum op_t {
    STR_LEN,
    STR_CMP,
    STR_N_CMP,
    STR_CHR,
    STR_RCHR
};


struct c_string_demo_t {
    void str_len_demo() {
        char const message1[] {"The sky is blue."};
        char const* message2 {"The sky is blue."};
        
        //strlen ignores null character
        std::cout << "strlen(message1): " << std::strlen(message1) << std::endl;
        // Includes the null character
        std::cout << "sizeof(message1): " << sizeof(message1) << std::endl;

        //strlen still works with decayed arrays
        std::cout << "strlen(message2): " << std::strlen(message2) << std::endl;
        //Prints size of pointer
        std::cout << "sizeof(message2): " << sizeof(message2) << std::endl;
    }

    void str_cmp_demo() {
        // std::strcmp - signature : int strcmp( const char *lhs, const char *rhs );
        //Returns negative value if lhs appears before rhs in lexicographical order,
        //Zero if lhs and rhs compare equal.
        //and Positive value if lhs appears after rhs in lexicographical order.

        std::cout << std::endl;
        std::cout << "std::strcmp: " << std::endl;
        char const* str_data1 {"Alabama"}; 
        char const* str_data2 {"Blabama"};

        char str_data3[] {"Alabama"};
        char str_data4[] {"Blabama"};

        std::cout << "std::strcmp(" << str_data1 << "," << str_data2 << "): "
            << std::strcmp(str_data1, str_data2) << std::endl;
        
        std::cout << "std::strcmp(" << str_data3 << "," << str_data4 << "): "
            << std::strcmp(str_data3, str_data4) << std::endl;

        str_data1 = "Alabama";
        str_data2 = "Alabamb";
        std::cout << "std::strcmp(" << str_data1 << "," << str_data2 << "): "
            << std::strcmp(str_data1, str_data2) << std::endl;
        
        str_data1 = "Alacama";
        str_data2 = "Alabama";
        std::cout << "std::strcmp(" << str_data1 << "," << str_data2 << "): "
            << std::strcmp(str_data1, str_data2) << std::endl;

        str_data1 = "India";
        str_data2 = "France";
        std::cout << "std::strcmp(" << str_data1 << "," << str_data2 << "): "
            << std::strcmp(str_data1, str_data2) << std::endl;

        str_data1 = "Kigali";
        str_data2 = "Kigali";
        std::cout << "std::strcmp(" << str_data1 << "," << str_data2 << "): "
            << std::strcmp(str_data1, str_data2) << std::endl;
    }

    void str_n_cmp_demo() {
        //std::strncmp : int strncmp( const char *lhs, const char *rhs, std::size_t count );
	    //Compares n characters in the strings
	    //Returns : Negative value if lhs appears before rhs in lexicographical order.
        //Zero if lhs and rhs compare equal, or if count is zero.
        //Positive value if lhs appears after rhs in lexicographical order. 
        //Print out the comparison

        char const* str_data1 {"Alabama"};
        char const* str_data2 {"Blabama"};
        std::size_t n{3};
        std::cout << std::endl;
        std::cout << "std::strncmp: " << std::endl;
        std::cout << "std::strncmp(" << str_data1 << "," << str_data2 << "," << n << "):"
            << std::strncmp(str_data1, str_data2, n) << std::endl;
        
        str_data1 = "aaaia";
        str_data2 = "aaance";
        std::cout << "std::strncmp(" << str_data1 << "," << str_data2 << "," << n << "):"
            << std::strncmp(str_data1, str_data2, n) << std::endl;

        n = 5;
        std::cout << "std::strncmp(" << str_data1 << "," << str_data2 << "," << n << "):"
            << std::strncmp(str_data1, str_data2, n) << std::endl;
        
        str_data1 = "aaaoa";
        str_data2 = "aaance";

        std::cout << "std::strncmp(" << str_data1 << "," << str_data2 << "," << n << "):"
            << std::strncmp(str_data1, str_data2, n) << std::endl;       

    }

    void str_chr_demo() {
        char const* const str {"Try not. Do, or do not. There is no try."};
        char target = 'T';
        char const* result = str;
        std::size_t iterations {};

        while((result = std::strchr(result, target)) != nullptr) {
            std::cout << "Found '" << target << "' starting at '" 
                << result << "'\n";
            // Increment result, otherwise we'll find target at the same location
            ++ result;
            ++ iterations;
        }
    }

    void str_rchr_demo() {
        std::cout << std::endl;
        std::cout << "std::strrchr: " << std::endl;

        char input[] = "/home/user/hello.cpp";
        char* output = std::strrchr(input, '/');
        if(output) {
            //+1 because we want to start printing past 
            // the character found by std::strrchr.
            std::cout << output + 1 << std::endl;
        }
    }

    void operator()(op_t op) {
        switch(op) {
        case STR_LEN: 
            str_len_demo();
            break;
        
        case STR_CMP:
            str_cmp_demo();
            break;
        
        case STR_N_CMP:
            str_n_cmp_demo();
            break;
        
        case STR_CHR:
            str_chr_demo();
            break;
        
        case STR_RCHR:
            str_rchr_demo();
            break;
        }
    }
};

int main(int argc, char* argv[]) {
    c_string_demo_t c_s_demo;
    c_s_demo(op_t::STR_LEN);
    c_s_demo(op_t::STR_CMP);
    c_s_demo(op_t::STR_N_CMP);
    c_s_demo(op_t::STR_CHR);
    c_s_demo(op_t::STR_RCHR);
    return EXIT_SUCCESS;
}