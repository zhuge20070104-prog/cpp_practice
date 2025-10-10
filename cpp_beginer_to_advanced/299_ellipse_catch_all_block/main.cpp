#include <iostream>

void do_something(int i) {
    if(i==2) {
        throw 2;
    } 
    
    if(i==3) {
        throw "i is 3";
    }
    
    if(i==7) {
        throw std::string("i is 7");
    }
}

int main(int argc, char* argv[]) {
    try {
        for(std::size_t i{2}; i<10; ++i) {
            try {
                do_something(i);
            } catch(int ex) {
                std::cout << "int exception is handled: " << ex << std::endl;
            } catch(...) {
                std::cout << "(inner) - some exceptions have been caught\n";
                throw;
            }
        }
    } catch(const char* ex) {
        std::cout << "const char* exception is handled: " << ex << std::endl;
    } catch(...) {
        std::cout << "(outer) - all exceptions have been handled\n";
    }
    std::cout << "Run to here..." << std::endl;
    return EXIT_SUCCESS;
}