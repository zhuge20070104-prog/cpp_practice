#include "fixed_string.h"
#include "charbuf.h"
#include <iostream>


int test_fixed_string(int test_no, unsigned long multiplier) {
    bool rc = true;

    switch (test_no) {
    default: return -1;
    case 0: return 2;

    case 1: {
        basic_fixed_string<9> s0;
        basic_fixed_string<9> s1("xyzzy");
        rc &= (s0!=basic_fixed_string<9>("xyzzy"));
        rc &= (s0 == basic_fixed_string<9>());
        rc &= (s0 == basic_fixed_string<9>(""));
        rc &= (s1 == basic_fixed_string<9>("xyzzy"));
        rc &= (s1 != basic_fixed_string<9>());
    }
        break;
    
    case 2: {
        charbuf<> cb, cb2;
        rc &= (cb == cb);
        rc &= (cb == cb2);
        rc &= (cb == "");
        rc &= !(cb == "x");
        cb = "xyz";
        rc &= (cb == "xyz");
        rc &= !(cb == "abc");
        rc &= !(cb == cb2);
        cb2 = cb;
        rc &= (cb2 == "xyz");
        rc &= !(cb2 == "abc");
        rc &= !(cb2 == "");

        cb = "a";
        cb2 = "b";
        rc &= (cb < cb2);
        rc &= !(cb2 < cb);

        cb2 = "aa";
        rc &= (cb < cb2);
        rc &= !(cb2 < cb);

    }
        break;
    }

    return (rc) ? 1: 0;
}