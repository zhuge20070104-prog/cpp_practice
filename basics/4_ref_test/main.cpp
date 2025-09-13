#include <string>
#include <iostream>
#include <vector>

struct MyObject {
    int i{1};
};

struct MyRef {
    MyObject& obj;
    int& j ;
    bool& yes;
};


void pass_by_ref(MyRef& ref) {
    ref.obj.i = 50;
    ref.j = 20;
    ref.yes = true;
}



int main(int argc, char* argv[]) {
    int i = 100; 
    int j = 10;
    bool yes = true;
    MyObject obj{i};
    MyRef ref_{obj, j, yes};
    pass_by_ref(ref_);
    std::cout << std::boolalpha;
    std::cout << "In ref: " << ref_.obj.i << " ---> " << ref_.j << " --->" << ref_.yes << std::endl;
    std::cout << "Origin: " << obj.i << " --->" << j  << " ---> " << yes << std::endl;

    return EXIT_SUCCESS;
}