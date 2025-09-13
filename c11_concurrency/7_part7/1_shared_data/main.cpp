#include "boost/filesystem.hpp"
#include <iostream>
#include <thread>
#include <algorithm>
#include <boost/foreach.hpp>
#include <vector>
#include <string>
#include <cassert>
#include <future>
#include <mutex>
#include <chrono>
#include "asyc_out.hpp"
#include "clocker.hpp"

using path_type = boost::filesystem::path;

// 每个线程遍历完成之后返回的std::future数据
struct Result {
    std::vector<std::string> files;
    std::vector<path_type> dirs;

    Result() {}
    Result(Result&& r): files(std::move(r.files)), dirs(std::move(r.dirs)) {}
}; 


Result list_dir(path_type&& path_) {
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


void test_move_data() {
    std::string root = "/home/fredric/code";
    std::vector<path_type> dirs_to_do;
    dirs_to_do.push_back(root);

    std::vector<std::string> files;
    aout << "Max threads count: " << std::thread::hardware_concurrency() << "\n";
    auto max_thread_size = std::thread::hardware_concurrency();
    {
          Clocker clocker;
          while(!dirs_to_do.empty()) {
            std::vector<std::future<Result>> futures;

            for(int i=0; i<max_thread_size && !dirs_to_do.empty(); ++i) {
                auto fut = std::async(&list_dir, std::move(dirs_to_do.back()));
                dirs_to_do.pop_back();
                futures.push_back(std::move(fut));
            }

            try {
                while(!futures.empty()) {
                    auto ftr = std::move(futures.back());
                    futures.pop_back();
                    Result result = ftr.get();
                    // 改用std::move 避免拷贝
                    std::move(result.files.begin(), result.files.end(), std::back_inserter(files));
                    std::move(result.dirs.begin(), result.dirs.end(), std::back_inserter(dirs_to_do));
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
}


class MonitorResult {
    Result result;
    std::mutex mutex_;

public:
    void put_file(std::string const& file) {
        std::lock_guard<std::mutex> lock(mutex_);
        result.files.emplace_back(std::move(file));
    }

    std::vector<std::string> get_files() {
        std::lock_guard<std::mutex> lock(mutex_);
        return result.files;
    }

    void put_dir(path_type const& path) {
        std::lock_guard<std::mutex> lock(mutex_);
        result.dirs.emplace_back(std::move(path));
    }

    std::vector<path_type> get_dirs(int n) {
        std::vector<path_type> dirs;
        std::lock_guard<std::mutex> lock(mutex_);
        for(int i=0; i<n && !result.dirs.empty() ; ++i) {
            dirs.push_back(result.dirs.back());
            result.dirs.pop_back();
        }
        return dirs;
    }

    bool is_dirs_empty() {
        std::lock_guard<std::mutex> lock(mutex_);
        return result.dirs.empty();
    }
};

void list_dir_shared(path_type&& dir, MonitorResult& result) {
    boost::filesystem::directory_iterator it(dir);
    for(auto& sub_dir: it) {
        if(boost::filesystem::is_directory(sub_dir)) {
            result.put_dir(sub_dir.path());
        } else {
            result.put_file(sub_dir.path().filename().string());
        }
    }
}

void test_share_data() {
    std::string root = "/home/fredric/code";
    MonitorResult result;
    result.put_dir(path_type(root));

    int max_thread_size = std::thread::hardware_concurrency();

    {
        Clocker clocker;
        while(!result.is_dirs_empty()) {
            auto dirs_to_do = result.get_dirs(max_thread_size);
            std::vector<std::future<void>> futures;
            while(!dirs_to_do.empty()) {
                auto ftr = std::async(&list_dir_shared, std::move(dirs_to_do.back()), std::ref(result));
                dirs_to_do.pop_back();
                futures.push_back(std::move(ftr));

                try{    
                    while(!futures.empty()) {
                        auto ftr = std::move(futures.back());
                        futures.pop_back();
                        ftr.wait();
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
    }

    aout << "Total file size: " << result.get_files().size() << "\n";
}

int main(int argc, char* argv[]) {

    for(int i=0; i<20; ++i) {
        aout << "Move data: ";
        test_move_data();
        aout << "\n";

        aout << "Shared data: ";
        test_share_data();
        aout << "\n";
    }
    
    aout << "Press enter\n";
    char c;
    std::cin.get(c);
    return EXIT_SUCCESS;
}