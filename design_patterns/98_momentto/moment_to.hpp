#ifndef _FREDIRC_MOMENT_TO_HPP_
#define _FREDIRC_MOMENT_TO_HPP_

#include <string>
#include <iostream>

class BankAccount;

class MomentTo {
    int balance;

public:
    MomentTo(int balance_): balance(balance_) {}
    friend class BankAccount;
};


class BankAccount {
    int balance {0};

public: 
    BankAccount(int balance_): balance(balance_) {}

    MomentTo deposit(int amount) {
        balance += amount;
        return {balance};
    }

    void restore(MomentTo const& m) {
        balance = m.balance;
    }

    friend std::ostream& operator<<(std::ostream& os, BankAccount const& account) {
        os << "balance: " << account.balance;
        return os;
    }
};

#endif