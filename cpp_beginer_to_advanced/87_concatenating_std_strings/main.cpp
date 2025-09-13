#include <iostream>
#include <string>

enum op_t {
    TWO_STRING,
    STR_LITERALS,
    STR_LITERALS_AROUND,
    NS_STR_LITERALS,
    STR_APPEND,
    CONCAT_STR_AND_CHAR,
    CONCAT_C_STR_AND_CHAR_ARRAY,
    CONCAT_NUMBER
};

struct std_string_concat_demo {
    void two_string() {
        std::cout << std::endl;
        std::cout << "Concatenating two strings: " << std::endl;
        std::string str1{"Hello"};
        std::string str2{"World"};
        std::string message = str1 + " my " + str2;
        std::cout << "message: " << message << std::endl;
    }

    void str_literals() {
        //Concatenating string literals : No, No - Compiler Error
	    //String literals are expanded into const char* arrays and C++ doesn't know
	    //how to add arrays with the + operator. Hence the compiler error.
        std::cout << std::endl;
        std::cout << "Concatenating string literals: No,No! Complier Error " << std::endl;
        
        // Compiler Error
        // invalid operands of types 'const char [6]' and 'const char [6]' to binary 'operator+'
        // std::string str3 {"Hello" + "World"};
        // std::string str4 = "Hello" + "World";
    }

    void str_literals_around() {
        std::cout << std::endl;
        std::cout << "A few ways around string literal concatenation" << std::endl;
        // Make the string one literal
        //in the first place
        std::string str5 {"Hello World"};
        // Put the literals side by side
        //without the + in between
        std::string str6 {"Hello" " World"};
        
        //Turn one or both into a std::string
        //object  and do the concatenation
        std::string str7 {std::string{"Hello"} + " World"};
        std::cout << str5 << std::endl;
        std::cout << str6 << std::endl;    
        std::cout << str7 << std::endl;
    }

    void ns_str_literals() {
        // necessary for the s suffix
		// This polutes the namespace in ns_str_literals
        using namespace std::string_literals;
        
        //Turn one or both into strings using the 
        //s suffix . the string_literals namespace has to be imported
        //for this to work
        std::string str8 {"Hello"s + " World"};
        std::cout << "str8: " << str8 << std::endl;

        //A better way to not polute the namespace
        std::string str9;
        {
            using namespace std::string_literals;
            str9 = "Hello"s + " World";
        }
        std::cout << "str9: " + str9 << std::endl;
    }

    void str_append() {
        //std::string is a compound type, it has properties and behaviors
        //one of the behaviors is append. We access the behaviors using
        //the . operator after the std::string variable name
        std::cout << std::endl;
        std::cout << "Using the append method: " << std::endl;
        std::string str10 {"Hello"};
        std::string str11 {" World"};
        std::string str12 = str10.append(str11);
        std::cout << "str12: " << str12 << std::endl;

        std::string str13 {std::string{"Hello"}.append(" World")};
        std::cout << "str13: " << str13 << std::endl;

        //Append can do more than the + operator
	    //The + operator is just a convenience for basic concatenation
        std::cout << std::endl;
        std::cout << "Append method can do more than + operator: " << std::endl;
        std::string str14 {"Hello "};
        // Appends 5 '?' characters
        std::string str15 {str14.append(5, '?')};
        std::cout << "str15: " << str15 << std::endl;
        
        std::string str16 {"The world is our shared home."};
        std::string str17 {"Hello "};
        // Append a sub-section of another string
        // starting from index 4 , 5 characters
        std::string str18 {str17.append(str16, 4, 5)};
        std::cout << "str18: " << str18 << std::endl;

        // Direct output
        std::string str19 {"Hello "};
        std::cout << "Direct output: " << str19.append(str16, 4, 5) << std::endl;
    }

    void concat_str_and_char() {
        std::cout << std::endl;
        std::cout << "Concatenating strings and characters: " << std::endl;
        std::string str20 {"Hello"};
        std::string str21 {"World"};
        // The space in between is a character
        std::string str22 {str20 + ' ' + str21};
        std::cout << "str22: " << str22 << std::endl;

        std::string str23 = "Hello";
        (str23 += ',') += ' ';
        std::cout << "str23: "  << str23 << std::endl;

        // Another solution
        std::string str24 {"Hello"};
        std::string str25 {"I am here to see you."};
        std::string str26 {str24 + ',' + ' ' + str25};
        std::cout << "str26: " << str26 << std::endl;
    }

    void concat_c_str_and_char_array() {
        std::cout << std::endl;
        std::cout << "Appending C-strings and char arrays: " << std::endl;
        char const message1[] {"World"};
        char const *message2 {"World"};
        
        std::cout << "+ char array: " << std::string{"Hello "} + message1 << std::endl;
        std::cout << "+ C-string: " << std::string{"Hello "} + message2 << std::endl;
        std::cout << "append char array: " << std::string{"Hello "}.append(message1) << std::endl;
        std::cout << "append C-string: " << std::string{"Hello "}.append(message2) << std::endl; 
    }

    void concat_number() {
        std::string str26{"Hello"};
        // Treats 67 as a character code
        // When using the += operator, C++ knows to treat the 
        //integer operand as a character code and append that to our
        //std::string. But what if we want the 67 appended to std::string
        //literally
        str26 += std::to_string(67.5f);
        std::cout << "str26: " << str26 << std::endl;
    }

    void operator()(op_t type_) {
        switch (type_) {
        case TWO_STRING:
            two_string();
            break;
        case STR_LITERALS:
            str_literals();
            break;
        case STR_LITERALS_AROUND:
            str_literals_around();
            break;
        case NS_STR_LITERALS:
            ns_str_literals();
            break;
        case STR_APPEND:
            str_append();
            break;
        case CONCAT_STR_AND_CHAR:
            concat_str_and_char();
            break;
        case CONCAT_C_STR_AND_CHAR_ARRAY:
            concat_c_str_and_char_array();
            break;
        case CONCAT_NUMBER:
            concat_number();
            break;
        default:
            break;
        }
    }
};


int main(int argc, char* argv[]) {
    std_string_concat_demo s_concat_demo;
    s_concat_demo(op_t::TWO_STRING);
    s_concat_demo(op_t::STR_LITERALS);
    s_concat_demo(op_t::STR_LITERALS_AROUND);
    s_concat_demo(op_t::NS_STR_LITERALS);
    s_concat_demo(op_t::STR_APPEND);
    s_concat_demo(op_t::CONCAT_STR_AND_CHAR);
    s_concat_demo(op_t::CONCAT_C_STR_AND_CHAR_ARRAY);
    s_concat_demo(op_t::CONCAT_NUMBER);
    
    return EXIT_SUCCESS;
}
