#include <iostream>

// definition
auto max(int& a, int& b) {
    if(a > b) {
        return a;
    } else {
        return b;
    }
}


int main()
{
    int x{5};
    int y{9};
    int max_val = max(x, y);
    std::cout << "max_val: " << max_val << std::endl;
    return 0;
}
