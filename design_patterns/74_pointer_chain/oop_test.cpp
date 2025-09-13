#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include "pointer_chain.hpp"
#include <utility>

#define BOOST_TEST_MODULE ListChain
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

BOOST_AUTO_TEST_CASE(TestListChainAll) {
    Creature goblin {"Goblin", 1, 1};
    DoubleAttackModifier root {goblin};
    DoubleAttackModifier r1_2 {goblin};
    IncreaseDefenseModifier r2 {goblin};
    root.add(&r1_2);
    root.add(&r2);
    root.handle();
    B_LOG(info) << goblin << "\n";
    BOOST_TEST(goblin.attack == 4, "Attack not correct!");
    BOOST_TEST(goblin.defense == 1, "Defense not correct!");
}

BOOST_AUTO_TEST_CASE(TestListChainBreakChain) {
    Creature goblin {"Goblin", 1, 1};
    NoBonusesModifier root {goblin};
    DoubleAttackModifier r1 {goblin};
    DoubleAttackModifier r1_2 {goblin};
    IncreaseDefenseModifier r2 {goblin};
    root.add(&r1);
    root.add(&r1_2);
    root.add(&r2);
    root.handle();
    B_LOG(info) << goblin << "\n"; 
    BOOST_TEST(goblin.attack == 1, "Attack not correct!");
    BOOST_TEST(goblin.defense == 1, "Defense not correct!");
}

BOOST_AUTO_TEST_SUITE_END()
