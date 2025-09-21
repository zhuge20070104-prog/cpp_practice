#include <iostream>

class InlineStatic {
public:
    inline static int s_member {0};
};


int main(int argc, char* argv[]) {
    std::cout << "InlineStatic::s_member: " << InlineStatic::s_member << '\n';

    return EXIT_SUCCESS;
}

