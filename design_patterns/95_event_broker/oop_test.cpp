#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include <utility>
#include <memory>
#include <cstring>
#include <vector>
#include <iterator>
#include "socker.hpp"

#define BOOST_TEST_MODULE  Socker
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

// 使用boost::signals2 库实现 教练向所有队员说话
// 其中game是中介者，被所有player持有，负责传递消息给coach
BOOST_AUTO_TEST_CASE(SockerTest) {
    Game game;
    Player player {"Sam", game};
    Player player1 {"Ming", game};
    Coach coach {game};

    player.score();
    player.score();
    player.score();
    player.score();

    player1.score();
    player1.score();
    player1.score();
}

BOOST_AUTO_TEST_SUITE_END()
