#include "calling.h"

int C::f1(int arg) {
    x_ = arg;
    return arg;
}

int C::f0() {
    return x_;
}


int C1::f1(int arg) {
    int x = c_.f1(arg);
    return x + 1;
}

int C1::f0() {
    int x = c_.f0();
    return x - 1;
}


int C2::f1(int arg) {
    int x = c_.f1(arg);
    return x + 2;
}

int C2::f0() {
    int x = c_.f0();
    return x - 2;
}

int C3::f1(int arg) {
    int x = c_.f1(arg);
    return x + 3;
}

int C3::f0() {
    int x = c_.f0();
    return x - 3;
}


int C4::f1(int arg) {
    int x = c_.f1(arg);
    return x + 4;
}

int C4::f0() {
    int x = c_.f0();
    return x - 4;
}

int C5::f1(int arg) {
    int x = c_.f1(arg);
    return x + 5;
}

int C5::f0() {
    int x = c_.f0();
    return x - 5;
}







