#include "strc.h"
#include <memory>
#include <iostream>

void message(char const* s) {
    printf("\n%s\n", s);
    fflush(stdout);
}

void disp(std::unique_ptr<strc>& o) {
    if(o) puts(o->value());
    else puts("null");
    fflush(stdout);
}

namespace nostd {
    template <typename T, typename P>
    std::unique_ptr<T> make_unique(P initializer) {
        return std::unique_ptr<T>(new T(initializer));
    }
};

int main(int argc, char* argv[]) {
    message("create unique pointer one");
    std::unique_ptr<strc> a(new strc("one"));
    disp(a);

    message("make_unique two");
    auto b = nostd::make_unique<strc>("two");
    disp(a);
    disp(b);

    message("reset a to threee");
    a.reset(new strc("three"));
    disp(a);
    disp(b);

    message("move b to c");
    auto c = std::move(b);
    disp(a);
    disp(b);
    disp(c);

    // reset 可以Destroy一个对象
    message("reset a");
    a.reset();
    disp(a);
    disp(b);
    disp(c);

    message("reset c");
    c.reset();
    disp(a);
    disp(b);
    disp(c);

    message("end of scope");
    return EXIT_SUCCESS;
}