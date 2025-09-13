#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include "broken_chain.hpp"
#include <utility>

#define BOOST_TEST_MODULE BrokenChain
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

BOOST_AUTO_TEST_CASE(TestBrokenChainAll) {
    Game game;
    Creature goblin(game, 1, 1, "Goblin");
    DoubleAttackModifier r1(game, goblin);
    B_LOG(info) << goblin << "\n";
    IncreaseDefenseModifier i1(game, goblin);
    B_LOG(info) << goblin << "\n";
    IncreaseDefenseModifier i2(game, goblin);
    B_LOG(info) << goblin << "\n";
    DoubleAttackModifier r2 {game, goblin};
    B_LOG(info) << goblin << "\n";
    IncreaseDefenseModifier i3(game, goblin);
    B_LOG(info) << goblin << "\n";
    BOOST_TEST(goblin.get_attack() == 4, "Attack not equal!");
    BOOST_TEST(goblin.get_defense() == 3, "Defense not equal!");
}

BOOST_AUTO_TEST_SUITE_END()
