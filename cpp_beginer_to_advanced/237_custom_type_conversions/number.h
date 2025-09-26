#ifndef _FREDRIC_NUMBER_H_
#define _FREDRIC_NUMBER_H_

#include "point.h"

class Number {
    friend std::ostream& operator<<(std::ostream& out, const Number& number); 
};

#endif