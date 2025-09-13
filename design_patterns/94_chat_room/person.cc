#include "person.h"
#include "chat_room.h"
#include <sstream>

Person::Person(std::string const& name_): name(name_) {}

void Person::receive(std::string const& origin, std::string const& message) {
    std::stringstream origin_msg_ss;
    origin_msg_ss << origin << ":\"" << message << "\"";
    std::cout << "[" << name << "'s chat session]" << origin_msg_ss.str() << "\n";
    chat_log.emplace_back(std::move(origin_msg_ss.str()));
}

void Person::say(std::string const& message) const {
    room->broadcast(name, message);
}

void Person::pm(std::string const& who, std::string const& message) const {
    room->message(name, who, message);
}
