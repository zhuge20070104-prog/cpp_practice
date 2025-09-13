#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include <utility>
#include <memory>
#include <cstring>
#include <vector>
#include <iterator>
#include "multi_methods.hpp"


#define BOOST_TEST_MODULE  MultiMethods
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(MultiMethodsTest) {
     // 宇宙飞船
     Spaceship spaceship;
     // 小行星
     Asteroid asteroid;
     // 行星
     Planet planet;

     collide(planet, spaceship);
     collide(planet, asteroid);
     collide(spaceship, asteroid);
     collide(planet, planet);
}

BOOST_AUTO_TEST_SUITE_END()
