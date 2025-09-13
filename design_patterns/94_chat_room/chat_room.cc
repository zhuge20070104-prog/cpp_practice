#include "chat_room.h"
#include "person.h"
#include <sstream>
#include <algorithm>

void ChatRoom::join(Person* p) {
    std::stringstream join_msg_ss;
    join_msg_ss << p->name << " joins the chat";
    broadcast("room", join_msg_ss.str());
    p->room = this;
    people.push_back(p);
}

void ChatRoom::broadcast(std::string const& origin, std::string const& message) {
    // 给除去自己以外的人广播这条消息
    for(auto&& p: people) {
        if(p->name != origin) {
            p->receive(origin, message);
        }
    }
}

// 从 origin给who发消息
void ChatRoom::message(std::string const& origin, std::string const& who, std::string const& message) {
    auto target = std::find_if(people.begin(), people.end(), [&](Person const* p) {
        return p->name == who;
    });
    
    if(target != people.end()) {
        (*target)->receive(origin, message);
    }
}