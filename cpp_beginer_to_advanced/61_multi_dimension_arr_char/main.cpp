#include <iostream>


enum funcs {
    READ_2D_CHAR_ARRAY,
    READ_2D_CHAR_ARRAY_LOOP,
    USE_C_STRING_LITERAL,
    FORTUNE_TELLER_ARRAY
};

struct func_maker {
    


    void operator()(funcs func_) {
        switch (func_) {
        case READ_2D_CHAR_ARRAY:
            read_2d_char_array();
            break;
        case READ_2D_CHAR_ARRAY_LOOP:
            read_2d_char_array_loop();
            break;
        case USE_C_STRING_LITERAL:
            use_c_string_literal();
            break;
        case FORTUNE_TELLER_ARRAY:
            fortune_teller_array();
            break;
        default:
            break;
        }
    }

private:
    void read_2d_char_array() {
        std::cout << "Print of members: " << std::endl;

        for(std::size_t i{0}; i<std::size(members); ++i) {
            std::cout << members[i] << std::endl;
        }
    }


    void read_2d_char_array_loop() {
        std::cout << std::endl;
        std::cout << "Printing out character by character manually : " << std::endl;
        for(int i=0; i<std::size(members); ++i) {
            for(int j=0; j<std::size(members[i]) - 1; ++j) {
                std::cout << members[i][j];
            }
            std::cout << std::endl;
        }
    }

    void use_c_string_literal() {
        std::cout << "Printing out members1 (C-string literals) : " << std::endl;
        for(std::size_t i = 0; i < std::size(members1); ++i) {
            std::cout << members1[i] << std::endl;
        }
    }

    void fortune_teller_array() {
        std::cout << std::endl;
        std::cout << "Prediction : " << predictions[5] << std::endl;
    }
    
    char members[4][15]{
        {'J','o','h','n', '\0'},
        {'S','a','m','u','e','l', '\0'},
        {'R','a','s','h','i','d', '\0'},
        {'R','o','d','r','i','g','e','z', '\0'}
    };

    //Better : Using C-string litterals
	//Compared to initialization with charactes with in '', this
	// is even easier to type. The entire string is a single entity 
	//you can manage easily.
    char members1[4][15] {
        "John",
        "Samuel",
        "Rashid",
        "Rodriguez"
    };

    //Updating our prediction declaration in the fortune teller game
    char predictions [11] [90] {
        "a lot of kinds running in the backyard!",
        "a lot of empty beer bootles on your work table.",
        "you Partying too much with kids wearing weird clothes.",
        "you running away from something really scary",
        "clouds gathering in the sky and an army standing ready for war",
        "dogs running around in a deserted empty city",
        "a lot of cars stuck in a terrible traffic jam",
        "you sitting in the dark typing lots of lines of code on your dirty computer",
        "you yelling at your boss. And oh no! You get fired!",
        "you laughing your lungs out. I've never seen this before." ,
        "Uhm , I don't see anything!"
    };
};


int main(int argc, char* argv[]) {
    func_maker f_maker;
    f_maker(READ_2D_CHAR_ARRAY);
    f_maker(READ_2D_CHAR_ARRAY_LOOP);
    f_maker(USE_C_STRING_LITERAL);
    f_maker(FORTUNE_TELLER_ARRAY);
    return EXIT_SUCCESS;
}