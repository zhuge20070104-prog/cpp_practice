#include "boost/filesystem.hpp"
#include <iostream>
#include <thread>
#include <algorithm>
#include <boost/foreach.hpp>
#include <vector>
#include <string>
#include <cassert>
#include <future>
#include <chrono>
#include "asyc_out.hpp"
#include "clocker.hpp"

// 每个线程遍历完成之后返回的std::future数据
struct Result {
    std::vector<std::string> files;
    std::vector<boost::filesystem::path> dirs;

    Result() {}
    Result(Result&& r): files(std::move(r.files)), dirs(std::move(r.dirs)) {}
}; 


Result list_dir(boost::filesystem::path&& path_) {
    Result result;
    boost::filesystem::directory_iterator it(path_);
    for(auto& sub_path: it) {
        if(boost::filesystem::is_directory(sub_path)) {
            result.dirs.push_back(sub_path);
        } else {
            result.files.push_back(sub_path.path().filename().string());
        }
    } 
    return result;
}


int main(int argc, char* argv[]) {
    std::string root = "/home/fredric/code";
    std::vector<boost::filesystem::path> dirs_to_do;
    dirs_to_do.push_back(root);

    std::vector<std::string> files;
    aout << "Max threads count: " << std::thread::hardware_concurrency() << "\n";

    auto max_thread_size = std::thread::hardware_concurrency();
    {
        Clocker clocker;
          while(!dirs_to_do.empty()) {
            std::vector<std::future<Result>> futures;

            for(int i=0; i<max_thread_size && !dirs_to_do.empty(); ++i) {
                auto fut = std::async(std::launch::async, &list_dir, std::move(dirs_to_do.back()));
                dirs_to_do.pop_back();
                futures.push_back(std::move(fut));
            }

            try {
                while(!futures.empty()) {
                    auto ftr = std::move(futures.back());
                    futures.pop_back();
                    Result result = ftr.get();
                    std::copy(result.files.begin(), result.files.end(), std::back_inserter(files));
                    std::copy(result.dirs.begin(), result.dirs.end(), std::back_inserter(dirs_to_do));
                }
            } catch(boost::filesystem::filesystem_error& err) {
                aout << "File system error: " << err.code().message() << "\n";
            } catch(std::exception& ex) {
                aout << "Exception: " << ex.what() << "\n";
            } catch(...) {
                aout << "Unknown exception\n";
            }
        }
    }
    
    aout << "Total files count: " << files.size() << "\n";
    BOOST_FOREACH(std::string& file, files){
        aout << file << "\n";
    };

    aout << "Press enter\n";
    char c;
    std::cin.get(c);
    return EXIT_SUCCESS;
}