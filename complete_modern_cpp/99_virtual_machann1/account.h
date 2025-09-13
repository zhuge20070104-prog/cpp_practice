#ifndef _FREDRIC_ACCOUNT_H_
#define _FREDRIC_ACCOUNT_H_
#include <string>

class Account {
    std::string m_name;
    int m_account_no;
    int static s_ANgenerator;
protected:
    float m_balance;
public:
    Account(std::string const& name, float balance);
    virtual ~Account();
    std::string const get_name() const;
    float get_balance() const;
    int get_account_no() const;
    virtual void accumulate_interest();
    virtual void withdraw(float amount);
    void deposit(float amount);
    virtual float get_interest_rate() const;
};
#endif