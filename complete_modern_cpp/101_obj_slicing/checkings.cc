#include "checkings.h"
#include <iostream>
  

Checkings::~Checkings() {

}

void Checkings::withdraw(float amount) {
    if((m_balance - amount) > 50) {
        Account::withdraw(amount);
    } else {
        std::cout << "Invalid amount" << std::endl;
    }
}