#include <iostream>
#include <string_view>
#include <string>
#include <cstring>

enum op_t {
    RAW_STR_COPY,
    USE_STR_VIEW,
    CONSTRUCT_STR_VIEW,
    CHANGE_ORIGIN_STR,
    CHANGE_THE_VIEW_NOT_AFFECT_STR,
    VIEW_SCOPE,
    VIEW_DATA,
    NOT_VIEW_DATA_ON_MODIFIED_VIEW,
    NOT_VIEW_ON_NON_NULL_TERM_STR,
    STD_STR_BEHAVIOR
};

struct string_view_demo_t {
    void raw_str_copy() {
        std::string str {"Hello"};
        std::string str1 {str};
        std::string str2 {str};

        std::cout << "address of string: " << &str << std::endl;
        std::cout << "address of string1: " << &str1 << std::endl;
        std::cout << "address of string2: " << &str2 << std::endl;
    }

    void use_str_view() {
        std::string_view sv {"Hellooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo"};
        std::string_view sv1 {sv}; // View viewing the hello literal
        std::string_view sv2 {sv1}; // Another view viewing hello 

        std::cout << "Size of string_view: " << sizeof(std::string_view) << std::endl;
        std::cout << "size of sv1: " << sizeof(sv1) << std::endl;

        std::cout << "sv: " << sv << std::endl;
        std::cout << "sv1: " << sv1 << std::endl;
        std::cout << "sv2: " << sv2 << std::endl;
    }

    void construct_str_view() {
        std::string string3 {"Regular std::string"};
        char const* c_string {"Regular C-String"};
        // Null terminated
        char const char_array[] {"Char array"};
        // Non null terminated char array
        char char_array2[] {'H', 'u', 'g', 'e'}; 

        std::string_view sv3 {"String literal"};
        std::string_view sv4 {string3};
        std::string_view sv5 {c_string};
        std::string_view sv6 {char_array};
        std::string_view sv7 {sv3};
        // Non null terminated char array
        // Need to pass in size info
        std::string_view sv8 {char_array2, std::size(char_array2)};
        std::cout << "sv3: " << sv3 << std::endl;
        std::cout << "sv4: " << sv4 << std::endl;
        std::cout << "sv5: " << sv5 << std::endl;
        std::cout << "sv6: " << sv6 << std::endl;
        std::cout << "sv7(construct from another string_view): " << sv7 << std::endl;
        std::cout << "Non null terminated string with std::string_view: " << sv8 << std::endl;
    }

    void change_origin_str() {
        char word[] = "Dog";
        std::string_view sv9 {word};
        std::cout << "word: " << sv9 << std::endl;
        std::cout << "Changing data... " << std::endl;
        word[2] = 't';
        std::cout << "word: " << sv9 << std::endl;
    }

    void change_the_view_not_affect_str() {
        char const* c_string1 {"The animals have left the region"};
        std::string_view sv10{c_string1};
        std::cout << "sv10: " << sv10 << std::endl;
        // Removes "The"
        sv10.remove_prefix(4);
        std::cout << "View with removed prefix(4): " << sv10 << std::endl;
        // Removes "the region"
        sv10.remove_suffix(10);
        std::cout << "View with removed suffix(10): " << sv10 << std::endl;
        //Changing the view doesn't change the viewed string
        std::cout << "Original sv10 viewed string: " << c_string1 << std::endl; 
    }

    void view_scope() {
        std::string_view sv11;
        {
            std::string string4 {"Hello there"};
            sv11 = string4;
            std::cout << "INSIDE --- sv11 is viewing: " << sv11 << std::endl;
        }
        std::cout << "OUTSIDE --- sv11 is viewing: " << sv11 << std::endl;
    }

    void view_data() {
        std::string_view sv13 {"Ticket"};
        std::cout << "sv13: " << sv13 << std::endl;
        std::cout << "std::strlen(sv13.data()): " << std::strlen(sv13.data()) << std::endl;
    }

    void not_view_data_on_modified_view() {
        std::string_view sv14 {"Ticket"};
        sv14.remove_prefix(2);
        sv14.remove_suffix(2);

        // Length info is lost when you modify the view
        std::cout << sv14 << " has " << std::strlen(sv14.data()) << " characters" << std::endl;
        std::cout << "sv14.data() is: " << sv14.data() << std::endl;
        std::cout << "sv14 is: " << sv14 << std::endl;
    }

    void not_view_on_non_null_term_str() {
        char char_array3[] {'H', 'e', 'l', 'l', 'o'};
        std::string_view sv15 {char_array3, std::size(char_array3)};
        std::cout << sv15 << " has " << std::strlen(sv15.data()) << " characters(s)" << std::endl;
        std::cout <<"sv15.data is  : " <<  sv15.data() << std::endl;
        std::cout << "sv15 is : " << sv15 << std::endl;
    }

    void std_str_behavior() {
        std::string_view sv16 {"There is a huge forest in that area"};
        std::cout << "sv16 is " << sv16.length() << " characters long" << std::endl;
        std::cout << "The front character is: " << sv16.front() << std::endl;
        std::cout << "The back character is: " << sv16.back() << std::endl;
        std::cout << "Substring: " << sv16.substr(0, 22) << std::endl;
    }
    
    void operator()(op_t type_) {
        switch (type_) {
        case RAW_STR_COPY:
            raw_str_copy();
            break;
        case USE_STR_VIEW:
            use_str_view();
            break;
        case CONSTRUCT_STR_VIEW:
            construct_str_view();
            break;
        case CHANGE_ORIGIN_STR:
            change_origin_str();
            break;
        case CHANGE_THE_VIEW_NOT_AFFECT_STR:
            change_the_view_not_affect_str();
            break;
        case VIEW_SCOPE:
            view_scope();
            break;
        case VIEW_DATA:
            view_data();
            break;
        case NOT_VIEW_DATA_ON_MODIFIED_VIEW:
            not_view_data_on_modified_view();
            break;
        case NOT_VIEW_ON_NON_NULL_TERM_STR:
            not_view_on_non_null_term_str();
            break;
        case STD_STR_BEHAVIOR:
            std_str_behavior();
            break;
        default:
            break;
        }
    }
};

int main(int argc, char* argv[]) {
    string_view_demo_t sv_demo;
    sv_demo(op_t::RAW_STR_COPY);
    sv_demo(op_t::USE_STR_VIEW);
    sv_demo(op_t::CONSTRUCT_STR_VIEW);
    sv_demo(op_t::CHANGE_ORIGIN_STR);
    sv_demo(op_t::CHANGE_THE_VIEW_NOT_AFFECT_STR);
    sv_demo(op_t::VIEW_SCOPE);
    sv_demo(op_t::VIEW_DATA);
    sv_demo(op_t::NOT_VIEW_DATA_ON_MODIFIED_VIEW);
    sv_demo(op_t::NOT_VIEW_ON_NON_NULL_TERM_STR);
    sv_demo(op_t::STD_STR_BEHAVIOR);

    return EXIT_SUCCESS;
}