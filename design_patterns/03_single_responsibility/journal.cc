#include "journal.h"
#include <sstream>

Journal::Journal(std::string const& title_): title(title_){

}

void Journal::add_entry(std::string const& entry) {
    int static count = 1;
    std::stringstream ss_entry;
    ss_entry << count++ << ":" + entry;
    entries.push_back(ss_entry.str());
}