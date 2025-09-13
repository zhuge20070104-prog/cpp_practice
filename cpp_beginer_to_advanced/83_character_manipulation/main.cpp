#include <iostream>
#include <vector>

enum test_type_t{
    IS_ALPHANUM,
    IS_ALPHA,
    IS_BLANK,
    IS_LOWER_AND_UPPER,
    IS_DIGIT,
    TO_LOWER_AND_UPPER
};

struct char_demo_t {
    void is_alhpa_numeric() {
        std::cout << std::endl;
        std::cout << "std::isalnum: " << std::endl;
        std::cout << "C is alphanumeric: " << std::isalnum('C') << std::endl;
        std::cout << "^ is alphanumeric: " << std::isalnum('^') << std::endl;

        char input_char{'*'};
        if(std::isalnum(input_char)) {
            std::cout << input_char << " is alphanumeric" << std::endl;
        } else {
            std::cout << input_char << " is not alphanumeric" << std::endl;
        }
    }

    void is_alpha() {
        std::cout << std::endl;
        std::cout << "std::isalpha: " << std::endl;
        std::cout << "e is alphabetic: " << std::isalpha('e') << std::endl;
        std::cout << "^ is alphabetic: " << std::isalpha('^') << std::endl;
        std::cout << "7 is alphabetic: " << std::isalpha('7') << std::endl;

        if(std::isalpha('e')) {
            std::cout << "e is alphabetic" << std::endl;
        } else {
            std::cout << "e is not alphabetic" << std::endl;
        }
    }

    void is_blank() {
        std::cout << std::endl;
        std::cout << "std::is_blank: " << std::endl;
        char message[] {"Hello there. How are you doing? The sun is shining."};
        std::cout << "message: " << message << std::endl;
        // Find and print blank index
        std::size_t blank_count{};

        for(std::size_t i=0; i<std::size(message); ++i) {
            if(std::isblank(message[i])) {
                std::cout << "Found a blank character at index[" << i << "]" << std::endl;
                ++blank_count;
            }
        }

        std::cout << "In total we found " << blank_count << " blank characters" << std::endl; 
    }

    void is_lower_and_upper() {
        std::cout << std::endl;
        std::cout << "std::is_lower and std::is_upper: " << std::endl;
        char thought[] {"The C++ programming language is one of the most used on the planet"};
        std::size_t lowercase_count {};
        std::size_t uppercase_count {};
        std::cout << "Original string: " << thought << std::endl;
        for(auto character: thought) {
            if(std::islower(character)) {
                std::cout << " " << character;
                ++lowercase_count;
            }

            if(std::isupper(character)) {
                ++uppercase_count;
            }
        }

        std::cout << std::endl;
        std::cout << "Found " << lowercase_count << " lowercase characters and "
            << uppercase_count << " uppercase characters." << std::endl;
    }


    void is_digit() {
        std::cout << std::endl;
        std::cout << "std::isdigit: " << std::endl;

        char statement[] {"Mr Hamilton owns 221 cows. That's a lot of cows! The kid exclaimed."};
        std::cout << "statement: " << statement << std::endl;

        std::size_t digit_count{};
        for(auto character: statement) {
            if(std::isdigit(character)) {
                std::cout << "Found digit: " << character << std::endl;
                ++digit_count;
            }
        }

        std::cout << "Found " << digit_count << " digits in the statement string" << std::endl;
    } 

    void to_lower_and_upper() {
        std::cout << std::endl;
        std::cout << "std::tolower and std::toupper: " << std::endl;
        char original_str[] {"Home. The feeling of belonging"};
        char dest_str[std::size(original_str)];
        for(std::size_t i=0; i<std::size(original_str); ++i) {
            dest_str[i] = std::toupper(original_str[i]);
        }

        std::cout << "Original string: " << original_str << std::endl;
        std::cout << "Uppercase string: " << dest_str << std::endl;

        for(std::size_t i=0; i<std::size(original_str); ++i) {
            dest_str[i] = std::tolower(original_str[i]);
        }

        std::cout << "Original string: " << original_str << std::endl;
        std::cout << "Lowercase string: " << dest_str << std::endl;
    }


    void operator()(test_type_t type_) {
        switch (type_) {
        case IS_ALPHANUM:
            is_alhpa_numeric();    
            break;
        
        case IS_ALPHA:
            is_alpha();
            break;
        
        case IS_BLANK:
            is_blank();
            break;

        case IS_LOWER_AND_UPPER:
            is_lower_and_upper();
            break;
        
        case IS_DIGIT:
            is_digit();
            break;
        
        case TO_LOWER_AND_UPPER:
            to_lower_and_upper();
            break;
        default:
            break;
        }
    }
};

int main(int argc, char* argv[]) {
    char_demo_t char_demo;
    char_demo(test_type_t::IS_ALPHANUM);
    char_demo(test_type_t::IS_ALPHA);
    char_demo(test_type_t::IS_BLANK);
    char_demo(test_type_t::IS_LOWER_AND_UPPER);
    char_demo(test_type_t::IS_DIGIT);
    char_demo(test_type_t::TO_LOWER_AND_UPPER);
    return EXIT_SUCCESS;
}