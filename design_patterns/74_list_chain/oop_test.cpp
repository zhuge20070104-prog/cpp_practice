#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include "list_chain.hpp"
#include <utility>

#define BOOST_TEST_MODULE ListChain
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

BOOST_AUTO_TEST_CASE(TestListChainAll) {
    Creature goblin {"Goblin", 1, 1};
    CreatureModifierChain chain;
    DoubleAttackModifier r1 {goblin};
    DoubleAttackModifier r1_2 {goblin};
    IncreaseDefenseModifier r2 {goblin};
    chain.add(&r1);
    chain.add(&r1_2);
    chain.add(&r2);
    chain.handle();
    B_LOG(info) << goblin << "\n";
    BOOST_TEST(goblin.attack == 4, "Attack not correct!");
    BOOST_TEST(goblin.defense == 1, "Defense not correct!");
}

BOOST_AUTO_TEST_CASE(TestListChainBreakChain) {
    Creature goblin {"Goblin", 1, 1};
    CreatureModifierChain chain;
    NoBonusesModifier nm {goblin};
    DoubleAttackModifier r1 {goblin};
    DoubleAttackModifier r1_2 {goblin};
    IncreaseDefenseModifier r2 {goblin};
    chain.add(&nm);
    chain.add(&r1);
    chain.add(&r1_2);
    chain.add(&r2);
    chain.handle();
    B_LOG(info) << goblin << "\n"; 
    BOOST_TEST(goblin.attack == 1, "Attack not correct!");
    BOOST_TEST(goblin.defense == 1, "Defense not correct!");
}

BOOST_AUTO_TEST_SUITE_END()
