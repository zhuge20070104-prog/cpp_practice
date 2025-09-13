#include <iostream>
#include <exception>
#include "stopwatch11.h"
#include "test_driver.h"

inline unsigned my_round_1(double d) {
    return (unsigned)(d+0.5);
}

inline unsigned div0(unsigned n, unsigned d) {
    auto r = ldiv(n, d);
    return (r.rem > (d>>1))? r.quot + 1: r.quot;
}

inline unsigned div1(unsigned n, unsigned d) {
    unsigned q = n/d;
    unsigned r = n%d;
    return (r > (d>>1)) ? q + 1: q;
}

inline unsigned div2(unsigned n, unsigned d) {
    return (n+ (d>>1)) / d;
}

int test_fp(int test_no, unsigned long multiplier) {
    bool rc = true;
    switch (test_no) {
    default: 
        return -1;
    case 0: 
        return 2;
    
    case 1: {
        rc &= (div1(2, 5) == 0);
        rc &= (div2(2, 5) == 0);
        rc &= (div1(4, 7) == 1);
        rc &= (div2(4, 7) == 1); 
    }
        break;
    
    case 2: {
        unsigned iterations = 1000000 * multiplier;
        {
            StopWatch sw("floating round");
            for(unsigned long i=0; i<iterations; ++i) {
                rc &= (i >= (unsigned)my_round_1((double)i/3));
            }
        }

        {
            StopWatch sw("ldiv round");
            for(unsigned long i=0; i<iterations; ++i) {
                rc &= (i >= div0(i, 3));
            }
        }

        {
            StopWatch sw("div1 round");
            for(unsigned long i=0; i<iterations; ++i) {
                rc &= (i >= div1(i, 3));
            }
        }

        {
            StopWatch sw("div2 round");
            for(unsigned long i=0; i<iterations; ++i) {
                rc &= (i >= div2(i, 3));
            }
        }

    }
        break;
    }

    return (rc)? 1: 0;
}