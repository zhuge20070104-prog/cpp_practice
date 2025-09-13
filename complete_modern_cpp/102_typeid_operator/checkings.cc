#include "checkings.h"
#include <iostream>
  
Checkings::Checkings(std::string const& name, float balance, float min_balance): m_min_balance(min_balance), 
    Account(name, balance){

}

Checkings::~Checkings() {

}

void Checkings::withdraw(float amount) {
    if((m_balance - amount) > m_min_balance) {
        Account::withdraw(amount);
    } else {
        std::cout << "Invalid amount" << std::endl;
    }
}

float Checkings::get_min_balance() const {
    return m_min_balance;
}