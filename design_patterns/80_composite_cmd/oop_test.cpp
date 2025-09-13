#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include "composite_cmd.hpp"
#include <utility>
#include <memory>

#define BOOST_TEST_MODULE CompositeCmd
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

BOOST_AUTO_TEST_CASE(TestCommandUndo) {
    BankAccount zhangsan;
    CompositeBankAccountCommand cmds {
        BankAccountCommand(zhangsan, BankAccountCommand::deposit, 100),
        BankAccountCommand(zhangsan, BankAccountCommand::withdraw, 700),
        BankAccountCommand(zhangsan, BankAccountCommand::deposit, 100),
        BankAccountCommand(zhangsan, BankAccountCommand::withdraw, 400)
    };

    cmds.call();
    B_LOG(info) << zhangsan << "\n";
    BOOST_TEST(zhangsan.balance == -200, "Balance not correct!");
    cmds.undo();
    BOOST_TEST(zhangsan.balance == 0, "Balance not correct!");
    B_LOG(info) << zhangsan << "\n";
}

BOOST_AUTO_TEST_CASE(TestMoneyTransferCommand) {
    BankAccount from;
    BankAccount to;
    CompositeBankAccountCommand cbc {
        BankAccountCommand(from, BankAccountCommand::deposit, 200),
        BankAccountCommand(to, BankAccountCommand::deposit, 200),
    };
    cbc.call();

    MoneyTransferCommand mtc (
        from, to, 100
    );

    mtc.call();
    B_LOG(info) << from << "\n";
    B_LOG(info) << to << "\n";
    BOOST_TEST(from.balance == 100, "Balance not correct!");
    BOOST_TEST(to.balance == 300, "Balance not correct!");
    mtc.undo();
    B_LOG(info) << from << "\n";
    B_LOG(info) << to << "\n";
    BOOST_TEST(from.balance == 200, "Balance not correct!");
    BOOST_TEST(to.balance == 200, "Balance not correct!");
}

BOOST_AUTO_TEST_SUITE_END()
