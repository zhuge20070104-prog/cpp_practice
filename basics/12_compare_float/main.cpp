#include <string>
#include <iostream>
#include <map>


static bool floatCompare(float f1, float f2)
{
    static constexpr auto epsilon = 1.0e-05f;
    if (std::abs(f1 - f2) <= epsilon)
        return true;
    return std::abs(f1 - f2) <= epsilon * std::max(std::abs(f1), std::abs(f2));
}



int main(int argc, char* argv[]) {
    float  a = 23.039996085215762f;
    float b =  23.040111831054724f;

    if(floatCompare(a, b)) {
        std::cout << a << "==" << b << std::endl;
    } else {
        std::cout << a << "!=" << b << std::endl;
    }
}