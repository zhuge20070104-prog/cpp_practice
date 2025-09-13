#ifndef _FREDRIC_SAVINGS_H_
#define _FREDRIC_SAVINGS_H_
#include "account.h"

class Savings: public Account {
    float m_rate;
public:
    Savings(std::string const& name, float balance, float rate);
    ~Savings();
    float get_interest_rate() const;
    void accumulate_interest();
};


#endif