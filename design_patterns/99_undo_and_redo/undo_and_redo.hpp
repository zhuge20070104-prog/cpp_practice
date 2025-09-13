#ifndef _FREDIRC_MOMENT_TO_HPP_
#define _FREDIRC_MOMENT_TO_HPP_

#include <string>
#include <iostream>
#include <memory>
#include <vector>

class BankAccount;

class MomentTo {
    int balance;

public:
    MomentTo(int balance_): balance(balance_) {}
    friend class BankAccount;
};


class BankAccount {
    int balance {0};
    std::vector<std::shared_ptr<MomentTo>> changes;
    int current;

public: 
    BankAccount(int balance_): balance(balance_) {
        changes.emplace_back(std::make_shared<MomentTo>(balance));
        current = 0;
    }

    std::shared_ptr<MomentTo> deposit(int amount) {
        balance += amount;
        auto m = std::make_shared<MomentTo>(balance);
        changes.emplace_back(m);
        ++ current;
        return m;
    }

    // restore相当于在最后加一步s
    void restore(std::shared_ptr<MomentTo> const& m) {
        if(m) {
            balance = m->balance;
            changes.emplace_back(m);
            current = changes.size() - 1;
        }
    }

    std::shared_ptr<MomentTo> undo() {
        if(current > 0) {
            -- current;
            auto m = changes[current];
            balance = m->balance;
            return m;
        }
        return {};
    }

    // redo 就是往后再走一步
    std::shared_ptr<MomentTo> redo() {
        if(current + 1 < changes.size() ) {
            ++ current;
            auto m = changes[current];
            balance = m->balance;
            return m;
        }
        return {};
    }

    friend std::ostream& operator<<(std::ostream& os, BankAccount const& account) {
        os << "balance: " << account.balance;
        return os;
    }
};

#endif