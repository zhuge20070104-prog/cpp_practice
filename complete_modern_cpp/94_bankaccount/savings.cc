#include "savings.h"

Savings::Savings(std::string const& name, float balance, float rate):
    Account(name, balance), m_rate(rate) {

}

float Savings::get_interest_rate() const {
    return m_rate;
}

void Savings::accumulate_interest() {
    m_balance += (m_balance * m_rate);
}

Savings::~Savings() {

}