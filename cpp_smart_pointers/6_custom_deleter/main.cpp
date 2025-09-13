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

// 函数做的delete
void deleter(strc* o) {
    printf("deleter: ");
    if(o) {
        printf("%s\n", o->value());
    } else {
        printf("[null]\n");
    }

    fflush(stdout);
    delete o;
    o = nullptr;
}

// 函数对象做deleter
class Deleter {
public:
    void operator()(strc* o) {
        printf("deleter: ");
        if(o) {
            printf("%s\n", o->value());
        } else {
            printf("[null]\n");
        }

        fflush(stdout);
        delete o;
        o = nullptr;
    }
};


int main(int argc, char* argv[]) {
    message("create shared_ptr");
    // std::shared_ptr<strc> a(new strc("thing"), &deleter);
    // std::shared_ptr<strc> a(new strc("thing"), Deleter());
    
    // 使用lambda 表达式构建deleter
    std::shared_ptr<strc> a(new strc("thing"), [](strc* o) {
        printf("deleter: ");
        if(o) {
            printf("%s\n", o->value());
        } else {
            printf("[null]\n");
        }

        fflush(stdout);
        delete o;
        o = nullptr;
    });

    disp(a);

    a.reset();
    disp(a);

    message("end of scope");
    return EXIT_SUCCESS;
}