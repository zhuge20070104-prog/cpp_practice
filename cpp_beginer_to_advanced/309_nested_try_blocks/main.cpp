#include <exception>
#include <iostream>
#include <string>

void exception_thrower() {
    throw 'z';
}

void some_func() {
    for(std::size_t i{0}; i<15; ++i) {
        std::cout << "ITERATION: " << i << '\n';
        try {
            if(i==2) {
                throw "Exception throw for int 2";
            }
            try {
                if(i==6) {
                    throw i;
                }

                if(i==8) {
                    throw '8';
                }

                if(i==10) {
                    exception_thrower();
                }

                if(i==13) {
                    throw std::string("std::string throw for int 13");
                }
            }catch(std::size_t ex) {
                std::cout << "Inner catch(std::size_t) handled the exception for: " << ex << '\n';
            } catch(char ex) {
                std::cout << "Inner catch(char) handled the exception for: " << ex << '\n';
            }
        }catch(const char* ex) {
            std::cout << "Outer catch(const char*) handled the exception for: " << ex << '\n';
        }
    }
}


int main(int argc, char* argv[]) {
    try {
        some_func();
    }catch(std::string& ex) {
        std::cout << "main catch(std::string) handled the exception for: " << ex << '\n';
    }

    std::cout << "Run to here..." << '\n';
    return EXIT_SUCCESS;
}
