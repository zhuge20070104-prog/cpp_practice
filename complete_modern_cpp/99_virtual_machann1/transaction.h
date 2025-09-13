#ifndef _FREDRIC_TRANSACTION_H_
#define _FREDRIC_TRANSACTION_H_
#include "account.h"
#include <iostream>

void transact(Account* p_account) {
    std::cout << "Transaction started ..." << std::endl;
    std::cout << "Initial balance: " << p_account->get_balance() << std::endl;
    p_account->deposit(100);
    p_account->accumulate_interest();
    p_account->withdraw(170);
    std::cout << "Interest rate: " << p_account->get_interest_rate() << std::endl;
    std::cout << "Final balance: " << p_account->get_balance() << std::endl;
}
 
#endif 