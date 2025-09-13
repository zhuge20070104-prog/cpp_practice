#ifndef _FREDRIC_SCANNER_H_
#define _FREDRIC_SCANNER_H_
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>


namespace scan {

template <typename T>
class array_scanner_t {
public:
  std::vector<T> scan(int size) {
    std::vector<T> data(size, 0);
    std::string line;
    std::getline(std::cin, line);
    std::istringstream iss(line);
    for (size_t i = 0; i < data.size(); ++i) {
      iss >> data[i];
    }
    return data;
  }
};


template <typename T>
class value_scanner_t {
public:
    T scan() {
        std::string value_str;
        std::getline(std::cin, value_str);
        std::stringstream ss(value_str);
        T value;
        ss >> value;
        return value;
    }
};
}


#endif