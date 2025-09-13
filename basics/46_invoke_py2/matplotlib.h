#ifndef _FREDRIC_MATPLOT_LIB_H_
#define _FREDRIC_MATPLOT_LIB_H_

#include <pybind11/embed.h>
#include <map>
#include <set>
#include <vector>
#include <string>

namespace py = pybind11;
using namespace py::literals;

namespace matplotlibc {
    struct matplotlib_t {
        matplotlib_t() {
            py::initialize_interpreter();
            plt = py::module_::import("matplotlib.pyplot");
        }

        ~matplotlib_t() {
            plt.release();
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

        template<typename NumericX, typename NumericY>
        bool scatter(const std::vector<NumericX>& x,
            std::vector<NumericY> const& y,
            double const s=1.0, 
            std::map<std::string, std::string> const& keywords = {}) {
            
            py::list result_x;
            py::list result_y;
            
            to_py_list(x, &result_x);
            to_py_list(y, &result_y);
            
            py::object res;
            if(keywords.size() > 0) {
                py::kwargs kw_args;
                to_kw_args(keywords, {"linewidths"}, &kw_args);
                res = plt.attr("scatter")(result_x, result_y, s, **kw_args);
            } else {
                res = plt.attr("scatter")(result_x, result_y, s);
            }

            return !res.is_none();
        }

        void clf() {
            plt.attr("clf")();
        }

        void save(std::string const& file_name) {
            plt.attr("savefig")(file_name.c_str());
        }

    private:
        py::module_ plt;
    };
}
#endif