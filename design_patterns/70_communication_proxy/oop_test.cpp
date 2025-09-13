#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include "communication_proxy.hpp"
#include <utility>

#define BOOST_TEST_MODULE CommunicationProxy
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

BOOST_AUTO_TEST_CASE(TestCommunicationProxyPong) {
    Pong pp;
    for(int i=0; i<3; ++i) {
        try_it(pp);
    }
 }

BOOST_AUTO_TEST_CASE(TestCommunicationProxyRemotePong) {
    RemotePong pp;
    for(int i=0; i<3; ++i) {
        try_it(pp);
    }
 }
BOOST_AUTO_TEST_SUITE_END()
