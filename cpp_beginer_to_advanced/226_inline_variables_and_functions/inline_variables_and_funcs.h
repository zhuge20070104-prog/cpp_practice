#ifndef _FREDRIC_INLINE_VARIABLES_AND_FUNCS_H_
#define _FREDRIC_INLINE_VARIABLES_AND_FUNCS_H_

#include <iostream>

// making the function inline - we can include it in multiple TUs without an error

inline void test_from_header() {
    std::cout << "Test from header\n";
}

#endif