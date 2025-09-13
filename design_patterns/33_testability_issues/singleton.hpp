#ifndef _FREDRIC_SINGLETON_HPP_
#define _FREDRIC_SINGLETON_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <memory>


class SingletonDatabase {
    // 私有构造函数，不可外部构造
    SingletonDatabase() {
        std::cout << "Initializing database\n";
        std::ifstream ifs {"../data/capitals.txt"};
        std::string city, pop_s;
        while(std::getline(ifs, city)) {
            std::getline(ifs, pop_s);
            int pop = std::atoi(pop_s.data());
            capitals[city] = pop;
        }
    }

    std::map<std::string, int> capitals;

public:
    // 不允许拷贝构造和赋值
    SingletonDatabase(SingletonDatabase const&) = delete;
    SingletonDatabase& operator=(SingletonDatabase const&) = delete;

    static SingletonDatabase& get() {
        // C++ 11保证此处线程安全
        static SingletonDatabase db;
        return db;
    }

    int get_population(std::string const& name) {
        return capitals[name];
    }

};


struct SingletonRecordFilter {
    int total_population(std::vector<std::string> const& names){
        int result {0};
        for(auto& name: names) {
            result += SingletonDatabase::get().get_population(name);
        }
        return result;
    }
};
#endif