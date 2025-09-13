#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include <utility>
#include <memory>
#include <cstring>
#include <vector>
#include <iterator>
#include <thread>
#include "classic_state_impl.hpp"


#define BOOST_TEST_MODULE  ClassicStateImpl
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(ClassicStateImplTest) {
     LightSwitch ls;
     ls.on();
     ls.off();
     ls.off();
     ls.off();
     ls.off();
     ls.on();
     ls.on();
     ls.on();
}

BOOST_AUTO_TEST_SUITE_END()
