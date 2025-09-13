#include "account.h"
#include <iostream>

int Account::s_ANgenerator = 1000;

Account::Account(std::string const& name, float balance): 
    m_name(name), m_balance(balance) {
    m_account_no = ++s_ANgenerator;
}   

Account::~Account() {

}

std::string const Account::get_name() const {
    return m_name;
}

float Account::get_balance() const { 
    return m_balance;
 }

int Account::get_account_no() const {
    return m_account_no;
}

void Account::accumulate_interest() {

}

void Account::withdraw(float amount) {
    if(amount < m_balance) {
        m_balance -= amount;
    } else {
        std::cout << "Insufficient balance" << std::endl;
    }
}

void Account::deposit(float amount) {
    m_balance += amount;
}

float Account::get_interest_rate() const {
    return 0.0f;
}