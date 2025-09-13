#include "boost/filesystem.hpp"
#include <iostream>
#include <regex>
#include <string>
#include <sstream>


struct Description {
    std::string date;
    std::string place;
    std::string car_type;
    std::string ps_type;
};

struct SplitDescription {
    Description description;
    std::string topic;
    std::string angle;
};

SplitDescription split_description(std::string const& desc, std::string const& topic_name, std::string const& car_name) {
    std::stringstream reg_ss;
    if(desc.find("_Angle_") != std::string::npos) {
        reg_ss << "(.*)_(" << topic_name << ")_(.*)_(" << car_name << ")_(.*)_(Angle.*?)";
    } else {
        reg_ss << "(.*)_(" << topic_name << ")_(.*)_(" << car_name << ")_(.*?)";
    }
    SplitDescription split_desc;
    std::string reg_s {reg_ss.str()};
    std::regex  re_angle(reg_s);
    std::smatch matches;
    if(std::regex_match(desc, matches, re_angle)) {
        split_desc.description.date = matches[1];
        split_desc.description.place = matches[3];
        split_desc.description.car_type = matches[4];
        split_desc.description.ps_type = matches[5];
        split_desc.topic = matches[2];
        if(matches.size() == 7) {
           split_desc.angle = matches[6];
        }
    } else {
        std::cout << "Match not found\n";
    }
    return split_desc;
}

std::ostream& operator<< (std::ostream& os, SplitDescription const& split_desc) {
    os << "Date: " << split_desc.description.date << "  Address: " << split_desc.description.place
        << " Car type: " << split_desc.description.car_type << " Parking space type: " << split_desc.description.ps_type
        << " Topic: " << split_desc.topic << " Angle: " << split_desc.angle;
    return os;
}

int main(int argc, char* argv[]) {
    std::string desc = "2023-01-12-11-00-02_StitchedImage_WuHuMengBo_CheryCV_X50_blue_under_ground_Angle_1";
    auto res = split_description(desc, "StitchedImage",  "CheryCV_X50_blue");

    std::cout << res << std::endl;
    desc = "2022-12-09-00-00-01_StitchedImage_JinHongQiao_CheryCV_X50_blue_underground_horizontal";
    res = split_description(desc, "StitchedImage", "CheryCV_X50_blue");
    std::cout << res << std::endl;
    return EXIT_SUCCESS;
}