#include "new_del.h"

#include <iostream>
#include <memory>
#include <string>



int string_allocator_test() {
    instrument_new(); 
    {
        puts("std::string s");
        std::string s;
        puts("try appending one char");
        s = s + 'x';
        puts("try appending 20 char C-style string");
        s = s + "12345678901234567890";
        puts("try appending s");
        s = s + s;
        puts("for");
        for(int i=0; i<30; ++i) {
            s = s + 'x';
        }  
        puts("delete s");
    }
    instrument_new(false);
    return 1;
}

int main(int argc, char* argv[]) {
    string_allocator_test();
    return EXIT_SUCCESS;
}