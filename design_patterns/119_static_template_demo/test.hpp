#ifndef _FREDRIC_BOOST_TEST_HPP_
#define _FREDRIC_BOOST_TEST_HPP_
#include <boost/test/unit_test.hpp>
#include "log.h"
using namespace boost::unit_test;

struct SuiteSetUp {
    SuiteSetUp()  {
        init_log();
        unit_test_log.set_threshold_level(log_test_units);
     }
    ~SuiteSetUp() { }
};
#endif