#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdio>
#include <sstream>
#include <fstream>
#include "gtest/gtest.h"
#include "log.hpp"

// 多重继承，钻石继承
// 1. C++ 允许同时从多个类继承
// 2. 这叫做多重继承
// 3. 允许一个子类从多个父类重用，重写行为
// 4. 多继承有可能导致钻石继承
// 5. 多个子类继承自一个公共的基类，形成钻石形状

class Stream {
private:
    std::string file_name;
    std::fstream fs;
protected:
    std::stringstream ss;

public:
    Stream(std::string const& file_name_): file_name(file_name_), fs(file_name_, std::ios::out){}
    std::string const& get_file_name() const {
        std::cout << "Stream(std::string const& file_name_)" << std::endl;
        return file_name;
    }

    // 对象析构时，将缓存写入文件
    ~Stream() {
        fs << ss.str();
        fs.flush();
        fs.close();
    }
};

// 虚继承保证子类中只有一个stream基类对象
class InputStream: virtual public Stream {
private:
    std::istream& in;
public:
    InputStream(std::istream& in_, std::string const& file_name_):  in(in_), Stream(file_name_) {
        std::cout << "InputStream(std::istream& in_, std::string const& file_name_)" << std::endl;
    }

    std::istream& operator>> (std::string& data) {
        in >> data;
        ss << data;
        return in;
    }

    ~InputStream() {
        std::cout << "~InputStream()" << std::endl;
    }
};

class OutputStream: virtual public Stream {
private:
    std::ostream& out;
public:
    OutputStream(std::ostream& out_, std::string const& file_name_):  out(out_), Stream(file_name_) {
        std::cout << "OutputStream(std::ostream& out_, std::string const& file_name_)" << std::endl;
    }

    std::ostream& operator<< (std::string const& data) {
        out << data;
        return out;
    }

    ~OutputStream() {
        std::cout << "~OutputStream()" << std::endl;
    }
};

class IOStream: public OutputStream, public InputStream {
public:
    IOStream(std::string const& file_name): OutputStream(std::cout, file_name), InputStream(std::cin, file_name), Stream(file_name) {
        std::cout << "IOStream(std::string const& file_name)" << std::endl;
    }    

    ~IOStream() {
        std::cout << "~IOStream()" << std::endl;
    }
};

// IOStream对象的构造过程
/**
 * 
 * 构造过程， 

        1、先调用IOStream类构造函数， 

        在IOStream构造函数中，先构造 基类Stream类， 

        Stream类构造完成之后 

        2、回到IOStream类构造函数，构造OutputStream类实例， 

        OutputStream类不会再构造 Stream类，因为它是虚继承自Stream类， 

        它把自己的vptr指向 Stream类，然后构造自己，返回 

        3、回到IOStream类构造函数中，构造InputStream类的示例， 

        InputStream类不会再构造Stream类，因为它是虚继承自Stream类， 

        它把自己的vptr指向Stream类，然后构造自己，返回 

        4、回到IOStream类构造函数中，构造IOStream，完毕 
*/
GTEST_TEST(OopTest, DiamondInheritance) {
    IOStream ss("result.txt");
    std::string data;
    ss << "请输入数据:" << std::endl;
    ss >> data;
    ss << data;
    ss << ss.get_file_name() << std::endl;
}

