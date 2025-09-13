#ifndef _FREDRIC_TEST_DATA_GENERATOR_H_
#define _FREDRIC_TEST_DATA_GENERATOR_H_

#include <vector>
#include <iostream>
#include "beans/beans.h"


namespace tn {
namespace integration_test {

struct test_data_generator_t {
    test_data_generator_t(std::string const& case_type_,
        std::string const& sub_case_type_, int steps_ ): steps(steps_) {}
    // TODO: add read batch data code
    case_data_result_t next_batch() {
        case_data_result_t one_batch;
        return one_batch;
    }

    ~test_data_generator_t() {
        std::cout << "test_data_generator_t::cur_data_index"
            << test_data_generator_t::cur_data_index << std::endl;
        test_data_generator_t::cur_data_index = 0;
    }
    
    // 思考一下这个generator的设计, 生命周期的问题
    static int cur_data_index;
    int steps;
};

}
}
#endif