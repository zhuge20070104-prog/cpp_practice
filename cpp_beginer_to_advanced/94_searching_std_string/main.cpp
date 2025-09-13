#include <iostream>
#include <string>

enum op_t {
    FIND_BASIC,
    INDICATE_STR_NPOS,
    FIND_SPECIFY_POS,
    FIND_C_STR
};

struct str_find_demo_t {
    void find_basic() {
        //Find(1)
        //std::string::find()
        //size_type find( const basic_string& str, size_type pos = 0 ) const
        //Finds the starting index where the str substring is found in
	    //the string where we call the method.
        std::string string1 {"Water was poured in the heater"};
        std::string search_for {"ter"};
        
        std::size_t found_pos = string1.find(search_for);
        std::cout << "find('ter'): index [" << found_pos << "]" << std::endl;

        //find red
        search_for = "red";
        found_pos = string1.find(search_for);
        std::cout << "find('red'): index [" << found_pos << "]" << std::endl;
        
        //Find something that isn't there
        search_for = "chicken";
        found_pos = string1.find(search_for);
        std::cout << "find('chicken'): index [" << found_pos << "]" << std::endl;

        // std::string::npos
        std::cout << "npos: " << std::string::npos << std::endl;
        std::size_t large = -1;
        std::cout << "large: " << large << std::endl;
    }

    void indicate_str_npos() {
        std::string string1 {"Water was poured in the heater"};
        std::string search_for {"red"};
        std::size_t found_pos = string1.find(search_for);
        if(found_pos == std::string::npos) {
            std::cout << "Could not find the string 'red'." << std::endl;
        } else {
            std::cout << "'red' found starting at position: " << found_pos << std::endl;
        }

        //Search for chicken and check result against std::string::npos
        search_for = "chicken";
        found_pos = string1.find(search_for);
        if(found_pos == std::string::npos) {
            std::cout << "Could not find the string 'chicken'." << std::endl;
        } else {
            std::cout << "'chicken' found starting at position: " << found_pos << std::endl;
        }
    }

    void find_specify_pos() {
        //Find(2)	
	    //Can specify the position where we want the search to start
        //using the second parameter of the method
        std::string string1{"Water was poured in the heater"};
        std::string search_for{"ter"};

        std::size_t found_pos = string1.find(search_for);
        std::cout << "ter found at position: " << found_pos << std::endl;

        found_pos = string1.find(search_for, 0);
        std::cout << "ter found at position: " << found_pos << std::endl;

        found_pos = string1.find(search_for, 10);
        std::cout << "ter found at position: " << found_pos << std::endl;
    }

    void find_c_str() {
        //Find(3)
        //size_type find( const CharT* s, size_type pos = 0 ) const;
        //Finds the first substring equal to the character string pointed to by s
        //pos : the position where we start searching in the std::string
        std::string string2 = "beer is packaged by her in beer cans around here.";
        char const* c_string2 {"her"};
        std::size_t found_pos = string2.find(c_string2, 2);
        if(found_pos != std::string::npos) {
            std::cout << c_string2 << " found at position: " << found_pos << std::endl;
        } else {
            std::cout << "Could not find the string: " << (c_string2) << std::endl;
        }
    }

    void operator()(op_t type_) {
        switch (type_) {
        case FIND_BASIC:
            find_basic();
            break;
        case INDICATE_STR_NPOS:
            indicate_str_npos();
            break;
        case FIND_SPECIFY_POS:
            find_specify_pos();
            break;
        case FIND_C_STR:
            find_c_str();
            break;
        default:
            break;
        }
    }
};

int main(int argc, char* argv[]) {
    str_find_demo_t sf_demo;
    sf_demo(op_t::FIND_BASIC);
    sf_demo(op_t::INDICATE_STR_NPOS);
    sf_demo(op_t::FIND_SPECIFY_POS);
    sf_demo(op_t::FIND_C_STR);

    return EXIT_SUCCESS;
}