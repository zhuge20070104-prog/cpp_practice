#ifndef _FREDRIC_TRANSACTION_H_
#define _FREDRIC_TRANSACTION_H_
#include "account.h"
#include <iostream>

void transact(Account* p_account) {
    std::cout << "Transaction started ..." << std::endl;
    std::cout << "Initial balance: " << p_account->get_balance() << std::endl;
    p_account->deposit(100);
    p_account->accumulate_interest();

    Checkings* p_checking = dynamic_cast<Checkings*>(p_account);
    if(p_checking) {
        std::cout << "Minimum balance of checking: " << p_checking->get_min_balance() << std::endl;
    }
    p_account->withdraw(170);
    std::cout << "Interest rate: " << p_account->get_interest_rate() << std::endl;
    std::cout << "Final balance: " << p_account->get_balance() << std::endl;
}

void transact(Account& p_account) {
    std::cout << "Transaction started ..." << std::endl;
    std::cout << "Initial balance: " << p_account.get_balance() << std::endl;
    p_account.deposit(100);
    p_account.accumulate_interest();

    // dyanmic_cast也可以用于处理引用，引用转换失败的时候会抛出一个std::bad_cast异常
    Checkings& checking = dynamic_cast<Checkings&>(p_account);
    std::cout << "Minimum balance of checking: " << checking.get_min_balance() << std::endl;
    
    p_account.withdraw(170);
    std::cout << "Interest rate: " << p_account.get_interest_rate() << std::endl;
    std::cout << "Final balance: " << p_account.get_balance() << std::endl;
}
 
#endif 