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

using string_vector = std::vector<std::string>;

string_vector list_directory(std::string&& dir) {
    string_vector listing;
    std::string dir_str("\n> ");
    dir_str += dir;
    dir_str += ":\n";
    listing.push_back(dir_str);

    std::vector<std::future<string_vector>> futures;
    boost::filesystem::directory_iterator it(dir);
    for(auto const& sub_path: it) {
        if(boost::filesystem::is_directory(sub_path)) {
            auto ftr = std::async(&list_directory, sub_path.path().string());      
            futures.push_back(std::move(ftr));
        } else {
            listing.push_back(sub_path.path().filename().string());
        }
    }


    BOOST_FOREACH(std::future<string_vector>& ftr, futures) {
        string_vector lst = ftr.get();
        std::copy(lst.begin(), lst.end(), std::back_inserter(listing));
    };

    return listing;
}


int main(int argc, char* argv[]) {
    std::string root = "/home/fredric/code";

    try {
        string_vector listing;
        {
            Clocker clocker;
            auto ftr = std::async(&list_directory, root);
            listing = ftr.get();
        }
        aout << "Files count: " << listing.size();

        BOOST_FOREACH(std::string const& file_name, listing) {
            aout << file_name << "\n";
        };
        
    } catch(std::exception& ex) {
        aout << ex.what() << "\n";
    } catch(...) {
        aout << "Unknown exception\n";
    }

    aout << "Press enter\n";
    char c;
    std::cin.get(c);
    return EXIT_SUCCESS;
}