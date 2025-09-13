#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <sstream>
#include <functional>
#include <chrono>

class dns_entry {
    std::string host_name;

public:
    dns_entry(): host_name("localhost") {}
    dns_entry(std::string const& host_name_): host_name(host_name_) {}

    std::string get_host_name() {
        return host_name;
    }
};

class dns_cache {
    std::map<std::string, dns_entry> entries;
    std::shared_mutex entry_mutex;

public:
    dns_entry find_entry(std::string const& domain) {
        // 读取使用std::shared_lock，可以多个线程一起读取
        std::shared_lock<std::shared_mutex> lk(entry_mutex);
        std::map<std::string, dns_entry>::const_iterator const it = entries.find(domain);
        return (it==entries.end()) ? dns_entry(): it->second;
    }

    void update_or_add_entry(std::string const& domain, dns_entry const& dns_detail) {
        // 写入使用std::lock_guard，只能有一个线程写入，其他线程围观
        // 否则两个一起写会造成corruption data
        // 一读一写会读出未完成的数据，产生未定义行为
        std::lock_guard<std::shared_mutex> lk(entry_mutex);
        entries[domain] = dns_detail;
    }
};


int main(int argc, char* argv[]) {
    std::vector<std::thread> write_threads;
    std::vector<std::thread> read_threads;
   
    dns_cache dns_c;
    for(int i=0; i<5; ++i) {
        write_threads.push_back(std::thread([&, i](){
            std::stringstream domain_ss;
            std::stringstream entry_ss;
            domain_ss << "domain " << i;
            entry_ss << "entry " << i;
            dns_entry entry_(entry_ss.str());
            dns_c.update_or_add_entry(domain_ss.str(), entry_);
        }));

        read_threads.push_back(std::thread([&](){
            std::stringstream domain_ss_read;
            domain_ss_read << "domain 0";
            auto entry_ = dns_c.find_entry(domain_ss_read.str());
            std::cout << entry_.get_host_name() << std::endl;

            domain_ss_read.str("domain 1");
            entry_ = dns_c.find_entry(domain_ss_read.str());
            std::cout << entry_.get_host_name() << std::endl;
        }));
    }

    std::for_each(write_threads.begin(), write_threads.end(), std::mem_fn(&std::thread::join));
    std::for_each(read_threads.begin(), read_threads.end(), std::mem_fn(&std::thread::join));

    return EXIT_SUCCESS;
}