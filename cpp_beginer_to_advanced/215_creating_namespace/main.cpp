#include <iostream>

namespace no_adjustment {
    int add(int a, int b) {
        return a + b;
    }
}

// only declaration of add 
namespace adjustment {
    int add(int a, int b);
}

// definition of add - works
namespace adjustment {
    int add(int a, int b) {
        return a + b - 1;
    }
}

int main(int argc, char* argv[]) {
    std::cout << adjustment::add(2, 1) << '\n';
    
    return EXIT_SUCCESS;
}

