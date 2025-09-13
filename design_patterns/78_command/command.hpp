#ifndef _FREDRIC_COMMAND_HPP_
#define _FREDRIC_COMMAND_HPP_
#include <string>
#include <iostream>
#include <memory>
#include <functional>
#include <vector>
#include <boost/signals2.hpp>

#include "log.h"

struct BankAccount {
    int balance {0};
    int overdraft_limit {-500};

    void deposit(int amount) {
        balance += amount;
        std::cout << "Deposited: " << amount << ", balance is now: " << balance << "\n";
    }

    void withdraw(int amount) {
        if(balance - amount >= overdraft_limit) {
            balance -= amount;
            std::cout << "Withdrew: " << amount << ", balance is now: " << balance << "\n";
        }
    }

    friend std::ostream& operator<<(std::ostream& os, BankAccount const& account) {
        os << "Balance: " << account.balance;
        return os;
    }
};

struct Command {
    virtual void call() = 0;
};

struct BankAccountCommand: Command {
    BankAccount& account;
    enum Action {deposit, withdraw} action;
    int amount;

    BankAccountCommand(BankAccount& account_, Action action_, int amount_):
        account(account_), action(action_), amount(amount_) {}
    
    void call() override {
        switch(action) {
            case deposit:
                account.deposit(amount);
                break;
            case withdraw:
                account.withdraw(amount);
                break;
        }
    }
};


#endif