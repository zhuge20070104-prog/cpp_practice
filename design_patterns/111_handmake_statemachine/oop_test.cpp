#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include <utility>
#include <memory>
#include <cstring>
#include <vector>
#include <iterator>
#include "handmake_statemachine.hpp"

#define BOOST_TEST_MODULE  HandmakeStatemachine
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(HandmakeStatemachineTest) {
     StateMachine sm;
     while(sm.next_state());
     std::cout << "We're done using the phone\n";
}

BOOST_AUTO_TEST_SUITE_END()
