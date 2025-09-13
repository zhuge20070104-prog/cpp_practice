#include "strc.h"
#include <memory>
#include <iostream>

void message(char const* s) {
    printf("\n%s\n", s);
    fflush(stdout);
}

void disp(std::shared_ptr<strc>& o) {
    if(o) printf("%s (%ld)\n", o->value(), o.use_count());
    else puts("null\n");
    fflush(stdout);
}

int main(int argc, char* argv[]) {
    message("create pointer with new");
    auto a = std::make_shared<strc>("new");

    message("reset a to one");
    a.reset(new strc("one"));
    disp(a);

    message("b = a");
    auto b = a;
    disp(a);
    disp(b);
    printf("a==b %s\n", a == b ? "true": "false");
    printf("*a==*b %s\n", *a == *b ? "true": "false");

    // reset 之后，a,b 指向了不同的对象
    message("reset a to two");
    a.reset(new strc("two"));
    disp(a);
    disp(b);
    printf("a==b %s\n", a == b ? "true": "false");
    printf("*a==*b %s\n", *a == *b ? "true": "false");

    message("b.swap(a)");
    b.swap(a);
    disp(a);
    disp(b);

    message("std::swap()");
    std::swap(*a, *b);

    // std::swap直接swap 指针不会有拷贝构造函数的调用
    // std::swap(a, b);
    
    disp(a);
    disp(b);

    message("end of scope");
    return EXIT_SUCCESS;
}