#include "checkings.h"
#include <iostream>
  
Checkings::Checkings(std::string const& name, float balance): Account(name, balance) {

}

Checkings::~Checkings() {

}

void Checkings::withdraw(float amount) {
    if(m_balance < 50) {
        std::cout << "Balance not enough, at least 50 dollars" << std::endl;
    } else {
        Account::withdraw(amount);
    }
}