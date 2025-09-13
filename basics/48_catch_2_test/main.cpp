#define CATCH_CONFIG_RUNNER
#include "catch/catch.hpp"
#include "beans/beans.h"
#include "utils/config_parser.h"
#include "utils/test_data_generator.h"

namespace it = tn::integration_test;

std::shared_ptr<it::cfg_options_t> cfg_opts;

int main(int argc, char* argv[]) {
    Catch::Session session;
    char const* cfg_path = "./config/bifang_test.json";
    int sess_argc = argc;
    char** sess_argv = argv;

    if(argc>=2) {
        cfg_path = argv[1];
        sess_argc = argc - 1;
        sess_argv = &argv[1];
    } 
    

    it::config_parser_t cfg_parser(cfg_path);
    cfg_opts = cfg_parser.parse();
    return session.run(sess_argc, sess_argv);
}


class ParkingFusTestListener : public Catch::TestEventListenerBase {  
public:  
    ParkingFusTestListener(Catch::ReporterConfig const& config_):
        Catch::TestEventListenerBase(config_)  {}

    void testCaseStarting(Catch::TestCaseInfo const& testInfo) override {
        
        std::cout << "Test case Started..." << testInfo.name << "---" << cfg_opts->params2 << std::endl;
    }

    void testCaseEnded(Catch::TestCaseStats const& testStats) override {  
        std::cout << "Test case ended..." << cfg_opts->params1 << std::endl;
    }  
};  
  
CATCH_REGISTER_LISTENER(ParkingFusTestListener)



TEST_CASE("Test With config options", "[config]") {
    int param1 = cfg_opts->params1;
    std::string param2 = cfg_opts->params2;
    REQUIRE(param1 == 11);
    REQUIRE(param2 == "hello");
}

TEST_CASE("Test With config options1", "[config1]") {
    int param1 = cfg_opts->params1;
    std::string param2 = cfg_opts->params2;
    REQUIRE(param1 == 11);
    REQUIRE(param2 == "hello");
}

