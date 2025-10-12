#include <exception>
#include <iostream>
#include <string>
#include <string_view>

class SomethingWrong {
public:
    SomethingWrong() = default;
    SomethingWrong(std::string_view message): m_message{message} {}
    ~SomethingWrong() = default;
    SomethingWrong(const SomethingWrong& src):
        m_message{src.m_message} {
        std::cout << "SomethingWrong copy constructor called\n";     
    }

    std::string what() const {
        return m_message;
    }
private:
    std::string m_message{};
};


void do_something(std::size_t i) {
    if(i == 5) {
        throw SomethingWrong("i is 5");
    }

    std::cout << "Iteration: " << i << '\n';
}


int main(int argc, char* argv[]) {
    for(std::size_t i{0}; i<10; ++i) {
        try {
            do_something(i);
        }catch(SomethingWrong& ex) {
            std::cout << "SomethingWrong exception is handled: " << ex.what() << '\n';
        }
    }
    return EXIT_SUCCESS;
}
