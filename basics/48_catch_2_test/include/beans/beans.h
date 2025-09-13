#ifndef _FREDRIC_BEANS_H_
#define _FREDRIC_BEANS_H_

#include <vector>

namespace tn {
namespace integration_test {


struct case_data_t {

};

template <typename T>
struct result_t {
    bool ok;
    T obj;

    result_t(): ok(false), obj() {}

    result_t(bool ok_, T&& obj_):
        ok(ok_), obj(std::move(obj_))  {
    }
};

using case_data_result_t = result_t<std::vector<case_data_t>>;

}
}

#endif