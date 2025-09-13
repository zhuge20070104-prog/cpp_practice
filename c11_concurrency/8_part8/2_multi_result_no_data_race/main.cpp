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

class MonitorResult {
    Result result;
    std::mutex mutex_;
public:
    MonitorResult(MonitorResult&& other): result(std::move(other.result)) {}
    MonitorResult() {}
    void put_file(std::string const& file) {
        std::lock_guard<std::mutex> lock(mutex_);
        result.files.emplace_back(std::move(file));
    }

    std::vector<std::string> get_files() {
        return result.files;
    }

    void put_dir(path_type const& path) {
        std::lock_guard<std::mutex> lock(mutex_);
        result.dirs.emplace_back(std::move(path));
    }

    // 去掉这两个方法中的锁
    std::vector<path_type> get_dirs(int n) {
        std::vector<path_type> dirs;
        // std::lock_guard<std::mutex> lock(mutex_);
        for(int i=0; i<n && !result.dirs.empty() ; ++i) {
            dirs.push_back(result.dirs.back());
            result.dirs.pop_back();
        }
        return dirs;
    }

    bool is_dirs_empty() {
        // std::lock_guard<std::mutex> lock(mutex_);
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


// 单线程运行时，1和2都是在单线程中运行
// 不需要加锁
// 只有到std::async部分起了新线程，才需要加锁
void list_tree(MonitorResult& result, int max_thread_size) {
     while(!result.is_dirs_empty()) {  // 1
            auto dirs_to_do = result.get_dirs(max_thread_size);  // 2
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

// 几个月之后，你的老板来找你，他说我们有那么多核，
// 我们想要在多线程中运行list_tree方法，并行运行
int main(int argc, char* argv[]) {

    std::string root = "/home/fredric/code";

    std::vector<MonitorResult> results;
    std::vector<std::future<void>> futures;
    boost::filesystem::directory_iterator it(root);
    for(auto& sub_path: it) {
        MonitorResult result;
        result.put_dir(sub_path.path());
        results.push_back(std::move(result));
    }

    int max_thread_size = std::thread::hardware_concurrency();

   {
        Clocker clocker;
        for(auto& result:  results) {
            std::future ftr = std::async(&list_tree, std::ref(result), max_thread_size);
            futures.push_back(std::move(ftr));
        }

        BOOST_FOREACH(std::future<void>& ftr_, futures) {
            ftr_.get();
        };
   }



    std::size_t total_file_size {0};
    for(auto& result: results) {
        total_file_size += result.get_files().size();
        // BOOST_FOREACH(std::string const& file, result.get_files()) {
        //     aout << file << "\n";
        // };
    }
    aout << "Total file size: " <<  total_file_size << "\n";

    aout << "Press enter\n";
    char c;
    std::cin.get(c);
    return EXIT_SUCCESS;
}