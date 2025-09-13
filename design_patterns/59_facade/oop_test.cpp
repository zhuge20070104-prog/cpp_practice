#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "facade.hpp"
#include <utility>

#define BOOST_TEST_MODULE Facade
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

BOOST_AUTO_TEST_CASE(TestFacade) {
    auto window = Console::instance().multi_buffers(3);
    for(int i=0; i<3; ++i) {
        for(int j=0; j<4; ++j) {
            cv::HersheyFonts font = cv::HersheyFonts::FONT_HERSHEY_DUPLEX;
            if(j%2 == 0) {
                font = cv::HersheyFonts::FONT_HERSHEY_TRIPLEX;
            }
            std::stringstream line;
            line << "This is line: " << i * 4 + j;
            window->buffers[i].add_string(line.str(), font);
        }
    }
    window->draw();
    window->wait_to_dispose();
}

BOOST_AUTO_TEST_SUITE_END()
