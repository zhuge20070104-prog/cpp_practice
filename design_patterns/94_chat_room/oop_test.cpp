#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include <utility>
#include <memory>
#include <cstring>
#include <vector>
#include <iterator>
#include "chat_room.h"
#include "person.h"

#define BOOST_TEST_MODULE  ChatRoom
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

BOOST_AUTO_TEST_CASE(ChatRoomTest) {
    ChatRoom room;

    Person john {"John"};
    Person jane {"Jane"};
    room.join(&john);
    room.join(&jane);

    john.say("Hi room");
    jane.say("Oh, hey John");

    Person simon {"Simon"};
    room.join(&simon);
    simon.say("Hi everyone");

    jane.pm("Simon", "Glad you could join us, Simon");
}

BOOST_AUTO_TEST_SUITE_END()
