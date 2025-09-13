#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include <utility>
#include <memory>
#include <cstring>
#include <vector>
#include <iterator>
#include "observer.hpp"

#define BOOST_TEST_MODULE  Observer
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(ObserverTest) {
    Person person {10};
    ConsolePersonObserver cpo;
    person.subscribe(cpo);

    person.set_age(11);
    person.set_age(12);

    // Ubsubscribe 之后应该就不接受消息了
    person.unsubscribe(cpo);
    person.set_age(13);
}

BOOST_AUTO_TEST_SUITE_END()
