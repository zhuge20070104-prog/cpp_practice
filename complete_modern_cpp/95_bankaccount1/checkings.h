#ifndef _FREDRIC_CHECKINGS_H_
#define _FREDRIC_CHECKINGS_H_
#include "account.h"

class Checkings: public Account {

public:
    Checkings(std::string const& name, float balance);
    ~Checkings();
    void withdraw(float amount);
};

#endif