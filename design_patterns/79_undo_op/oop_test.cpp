#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include "command_undo.hpp"
#include <utility>
#include <memory>

#define BOOST_TEST_MODULE CommandUndo
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

BOOST_AUTO_TEST_CASE(TestCommandUndo) {
    BankAccount ba;
    std::vector<std::shared_ptr<Command>> commands {
        std::make_shared<BankAccountCommand>(ba, BankAccountCommand::deposit, 100),
        std::make_shared<BankAccountCommand>(ba, BankAccountCommand::withdraw, 200)
    };
    std::cout << ba << "\n";
    BOOST_TEST(ba.balance == 0, "Balance is not correct!");
    for(auto const& cmd: commands) {
        cmd->call();
    }
    std::cout << ba << "\n";
    BOOST_TEST(ba.balance == -100, "Balance is not correct!");

    for(auto r_cmd = commands.rbegin(), r_end = commands.rend(); r_cmd != r_end; ++r_cmd) {
        (*r_cmd)->undo();
    }
    std::cout << ba << "\n";
    BOOST_TEST(ba.balance == 0, "Balance is not correct!");
}

BOOST_AUTO_TEST_SUITE_END()
