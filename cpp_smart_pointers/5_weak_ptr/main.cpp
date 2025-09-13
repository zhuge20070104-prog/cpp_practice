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

void disp(std::weak_ptr<strc> const& o) {
    // Weak pointer use count
    std::size_t count = o.use_count();
    auto sp = o.lock();
    if(sp) {
        printf("%s (w: %ld s: %ld)\n", sp->value(), count, sp.use_count());
    }  else {
        puts("[null]");
    }

    fflush(stdout);
}

int main(int argc, char* argv[]) {
    message("create shared_ptr");
    auto a = std::make_shared<strc>("thing");

    message("make several copies");
    auto c1 = a;
    auto c2 = a;
    auto c3 = a;
    auto c4 = a;
    auto c5 = a;

    message("reference count is now 6");
    disp(a);

    message("create weak_ptr");
    auto w1 = std::weak_ptr<strc>(a);
    disp(w1);

    message("destroy copies");
    c1.reset();
    c2.reset();
    c3.reset();
    c4.reset();
    c5.reset();

    message("reference count should be 1");
    disp(a);

    message("check weak ptr");
    disp(w1);

    message("destroy a");
    a.reset();

    message("check weak ptr");
    disp(w1);
    
    message("end of scope");
    return EXIT_SUCCESS;
}