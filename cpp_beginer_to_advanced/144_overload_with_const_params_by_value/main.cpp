#include <iostream>


int max(int a, int b);
// int max(int const a, int const b);

int main()
{
    int a {6};
    int b {10};
    int max_val = max(a, b);
    std::cout << "max_val is: " << max_val << std::endl;
    return 0;
}

int max(int a, int b) {
    return a>b? a: b;
}

// int max(int const a, int const b) {
//     return a>b? a: b;
// }
