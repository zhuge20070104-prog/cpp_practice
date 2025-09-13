#include <iostream>

struct test_st {
    test_st(uint8_t i_, float b_): i(i_),
        b(b_){}
    uint8_t i;
    float b;
    bool c{false};
};

int main()
{
    test_st st {0, 32.0f};
    std::cout << (int)st.i << ", " << st.b << ", "
              << std::boolalpha
              << st.c << std::endl;
    return 0;
}
