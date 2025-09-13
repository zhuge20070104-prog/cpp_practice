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
#include "observer_safety.hpp"

#define BOOST_TEST_MODULE  ObserverThreadSafe
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(ObserverThreadSafeTest) {
   Person p{10};
   TrafficAdministration ta;
   ConsolePersonObserver cpo;
   p.subscribe(ta);
   p.subscribe(cpo);

   std::thread t_1([&](){
        p.set_age(16);
   });

   std::thread t_2([&](){
        p.set_age(20);
   });

   t_1.join();
   t_2.join();
}

BOOST_AUTO_TEST_SUITE_END()
