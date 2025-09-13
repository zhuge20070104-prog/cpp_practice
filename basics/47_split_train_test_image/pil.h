#ifndef _FREDRIC_MATPLOT_LIB_H_
#define _FREDRIC_MATPLOT_LIB_H_

#include <pybind11/embed.h>
#include <map>
#include <set>
#include <vector>
#include <string>

namespace py = pybind11;
using namespace py::literals;

namespace pil{
    struct  pil_t{
        pil_t() {
            py::initialize_interpreter();
            pil_ = py::module_::import("PIL.Image");
        }

        ~pil_t() {
            pil_.release();
            py::finalize_interpreter();
        }
       
        template<typename NumericX>
        void to_py_list(const std::vector<NumericX>& x, py::list* result_x) {
            for (const auto &elem : x) {
                result_x->append(elem);
            }
        }

        void to_kw_args(std::map<std::string, std::string> const& keywords, std::set<std::string> const& real_keys,
        py::kwargs* kw_args)  {
            for (const auto& pair : keywords) {
                if(real_keys.find(pair.first) != real_keys.end()) {
                    (*kw_args)[py::str(pair.first)] = std::atof(pair.second.data());
                } else {
                    (*kw_args)[py::str(pair.first)] = pair.second;
                }    
            }
        }

        bool open(std::string const& img_name) {
            try {
                py::object res = pil_.attr("open")(img_name.c_str());
                if(res.is_none()) {
                    return false;
                }
                return true;
            }catch (const py::error_already_set &e) {
                // 处理异常
                PyErr_Print();
                return false;
            }
        }
            
        

    private:
        py::module_ pil_;
    };
}
#endif