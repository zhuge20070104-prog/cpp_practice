#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "bank_account.hpp"
#include <utility>

#define BOOST_TEST_MODULE SharedPointer
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

BOOST_AUTO_TEST_CASE(TestSharedPointer) {
    BankAccount* a = new CurrentAccount(123);
    a->deposit(321);
    std::cout << *dynamic_cast<CurrentAccount*>(a) << std::endl;
    delete a;

    auto b = std::make_shared<CurrentAccount>(123);
    b->deposit(321);
    std::cout << *b << std::endl;
 }

BOOST_AUTO_TEST_SUITE_END()
