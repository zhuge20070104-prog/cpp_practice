#include <boost/filesystem.hpp>
#include <algorithm>
#include <iostream>
#include <numeric>


namespace fs = boost::filesystem;


std::vector<std::string> get_all_log_files() {
    fs::path log_root_path{"../logs"};

    fs::directory_iterator it(log_root_path);
    fs::directory_iterator end;
    std::vector<std::string> init_paths{};
    auto result = std::accumulate(it, end, init_paths, [](std::vector<std::string>& paths, 
        fs::directory_entry const& entry){
        if(fs::extension(entry.path()) == ".txt") {
            paths.emplace_back(std::move(entry.path().string()));
        }
        return paths;      
    });

    return result;
}

std::vector<std::string> get_all_log_files_2_step() {
    fs::path log_root_path{"../logs"};

    fs::directory_iterator it(log_root_path);
    fs::directory_iterator end;
    // 先filter[accumulate], 再map[transform] 
    std::vector<fs::directory_entry> init_entries{};

    auto result_entries = std::accumulate(it, end, init_entries, [](std::vector<fs::directory_entry>& paths, 
        fs::directory_entry const& entry){
        if(fs::extension(entry.path()) == ".txt") {
            paths.emplace_back(std::move(entry));
        }
        return paths;      
    });

    std::vector<std::string> result(result_entries.size());
    std::transform(result_entries.begin(), result_entries.end(), result.begin(), [](fs::directory_entry const& entry){
        return entry.path().string();
    });

    return result;
}

int main(int argc, char* argv[]) {
    // auto log_files = get_all_log_files();
    auto log_files = get_all_log_files_2_step();
    std::for_each(log_files.begin(), log_files.end(), [](std::string const& log_file) {
        std::cout << log_file << std::endl;
    });

    return EXIT_SUCCESS;
}