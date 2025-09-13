#include <iostream>
#include <string>

enum op_t {
    STR_REPLACE_1,
    STR_REPLACE_2,
    STR_COPY,
    STR_RESIZE,
    STR_SWAP
};

struct str_op_demo_t {
    void str_replace_1() {
        //Replacing (1)
        //basic_string& replace( size_type pos, size_type count,const basic_string& str );
        //Replace the range [pos, pos + count] with str
        std::string str1 {"Finding Nemo"};
        std::string str1_2 {"Searching For"};
        std::cout << "str1: " << str1 << std::endl;

        std::cout << "Replacing..." << std::endl;
        str1.replace(0, 7, str1_2);
        std::cout << "str1: " << str1 << std::endl;
    }

    void str_replace_2() {
        //Replacing - (2)
        //basic_string& replace( size_type pos, size_type count,
        //const basic_string& str,
        //size_type pos2, size_type count2 = npos );

        //Replace in part of str, not its entirety
        std::string str2 {"Finding Nemo"};
        std::string str3 {"The Horse was Found in the Fields Searching For Food"};

        std::cout << "str2: " << str2 << std::endl;
        std::cout << "Replacing..." << std::endl;
        str2.replace(0, 7, str3, 34, 13);
        std::cout << "str2: " << str2 << std::endl;
    }

    void str_copy() {
        //Copying
        //size_type copy( CharT* dest,size_type count,size_type pos = 0)
        //Copy a subsection of *this string to dest. Dest is pre-allocated
        // The resulting character string is not null-terminated. Be careful
        std::string str4 {"Climbing Kirimanjaro"};
        char txt4[15] {}; //Initialized with zero equivalent for characters which is '\0'
        std::cout << "std::size(txt4): " << std::size(txt4) << std::endl;
        std::cout << "txt4: " << txt4 << std::endl;
        std::cout << "Copying..." << std::endl;
        str4.copy(txt4, 11, 9);
        //Safe to print because the char array was initialized with '\0' s.
        std::cout << "txt4: " << txt4 << std::endl;
    }

    void str_resize() {
        std::string str5 {"Hello"};
        std::cout << "null char: " << '\0' << std::endl;
        std::cout << "str5: " << str5 << std::endl;
        std::cout << "str5.size(): " << str5.size() << std::endl;
        std::cout << "str5.capacity(): " << str5.capacity() << std::endl;

        std::cout << "Resizing..." << std::endl;
        // This fills new char place holders with
        //null character by default, you can't print and see them
        str5.resize(8);
        std::cout << "str5: " << str5 << std::endl;
        std::cout << "str5.size(): " << str5.size() << std::endl;
        std::cout << "str5.capacity(): " << str5.capacity() << std::endl;

        // Prove that they are indeed null characters
        std::cout << "Printing through loop: " << std::endl;
        for(std::size_t i=0; i<str5.size(); ++i) {
            std::cout << i << ": " << str5[i] << std::endl;
        }    


        // Resize and specify autofill characters
        std::cout << "Resize and specify autofill characters: " << std::endl;
        str5.resize(10, '*');
        std::cout << "str5: " << str5 << std::endl;
        std::cout << "str5.size(): " << str5.size() << std::endl;
        std::cout << "str5.capacity(): " << str5.capacity() << std::endl;

        // Resize down
        std::cout << "Resize down: " << std::endl;
        str5.resize(5);
        std::cout << "str5: " << str5 << std::endl;
        std::cout << "str5.size(): " << str5.size() << std::endl;
        std::cout << "str5.capacity(): " << str5.capacity() << std::endl;
    }

    void str_swap() {
        std::string str_a {"This is a string stored in A"};
        std::string str_b {"This is a string stored in B and it's really great to be able to do that."};
        //Before swap
        std::cout << "str_a : " << str_a << std::endl;
        std::cout << "str_b : " << str_b << std::endl;
        std::cout << "str_a.size() :" << str_a.size() << std::endl;
        std::cout << "str_a.capaity() : " << str_a.capacity() << std::endl;
        std::cout << "str_b.size() :" << str_b.size() << std::endl;
        std::cout << "str_b.capaity() : " << str_b.capacity() << std::endl;

        std::cout << "Swapping..." << std::endl;
        str_a.swap(str_b);

        //After swap
        std::cout << "str_a : " << str_a << std::endl;
        std::cout << "str_b : " << str_b << std::endl;
        std::cout << "str_a.size() :" << str_a.size() << std::endl;
        std::cout << "str_a.capaity() : " << str_a.capacity() << std::endl;
        std::cout << "str_b.size() :" << str_b.size() << std::endl;
        std::cout << "str_b.capaity() : " << str_b.capacity() << std::endl;
    }

    void operator()(op_t type_) {
        switch (type_) {
        case STR_REPLACE_1:
            str_replace_1();
            break;
        case STR_REPLACE_2:
            str_replace_2();
            break;
        case STR_COPY:
            str_copy();
            break;
        case STR_RESIZE:
            str_resize();
            break;
        case STR_SWAP:
            str_swap();
            break;
        default:
            break;
        }
    }
};

int main(int argc, char* argv[]) {
    str_op_demo_t s_o_demo;
    s_o_demo(op_t::STR_REPLACE_1);
    s_o_demo(op_t::STR_REPLACE_2);
    s_o_demo(op_t::STR_COPY);
    s_o_demo(op_t::STR_RESIZE);
    s_o_demo(op_t::STR_SWAP);

    return EXIT_SUCCESS;
}