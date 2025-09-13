#ifndef _FREDIRC_CHAT_ROOM_H_
#define _FREDIRC_CHAT_ROOM_H_

#include <string>
#include <iostream>
#include <vector>

struct Person;

struct ChatRoom {
    std::vector<Person*> people;

    void join(Person* p);
    void broadcast(std::string const& origin, std::string const& message);
    void message(std::string const& origin, std::string const& who, std::string const& message);
};


#endif