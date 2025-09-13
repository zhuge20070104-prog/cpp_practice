#include <vector>
#include <iostream>

struct Noisy {
    Noisy() {
        std::cout << "Constructed\n";
    }

    Noisy(Noisy const&) {
        std::cout << "Copied\n";
    }

    Noisy& operator=(Noisy const&) {
        std::cout << "Assigned\n";
        return *this;
    }

    ~Noisy() {
        std::cout << "Destroyed\n";
    }

    Noisy(Noisy&&) {
        std::cout << "moved\n";
    }
};

std::vector<Noisy> f() {
    std::vector<Noisy> v = std::vector<Noisy>(3); // Copy ellision from temporary to v
    return v; // RVO 
} 

Noisy g() {
    Noisy v;
    return v;
}

void fn_by_val(std::vector<Noisy> arg) {
    std::cout << "arg.size() = " << arg.size() << "\n";
}
 
int test_copy_elision(int test_no, unsigned long multiplier) {
    bool rc = true;
    switch (test_no) {
    default: return -1;
    case 0: return 2; // number of tests
    case 1: return 1; // no module test, return success
    case 2: {
        std::cout << "Copy ellision on return\n";
        Noisy x = g();
        std::cout << "No copy ellision on assign\n";
        x = g();

        std::cout << "Copy ellision on return\n";
        std::vector<Noisy> v = f();
        std::cout << "Copy ellision of unamed temporary\n";
        fn_by_val(f());

        std::cout << "Move on vector assignment\n";
        v = f();
        std::cout << std::flush;
    }
        break;
    }
    return (rc) ? 1: 0;
}