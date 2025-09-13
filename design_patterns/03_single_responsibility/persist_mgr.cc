#include "persisit_mgr.h"
#include <fstream>

void PersisitMgr::save(Journal const& j, std::string const& file_name) {
    std::ofstream ofs{file_name};
    ofs << j.title << std::endl;

    for(auto const& e: j.entries) {
        ofs << e << std::endl;
    }
}