#include <iostream>
#include <string>
#include "gtest/gtest.h"

class Zip final {
public:
    Zip() {
        std::cout << "Zip::Zip()" << std::endl;
    }

    ~Zip() {
        std::cout << "Zip::~Zip()" << std::endl;
    }

    void compress(std::string const& file_name) {
        std::cout << "Zip compress: " << file_name << std::endl;
    }

    void decompress(std::string const& file_name) {
        std::cout << "Zip decompress: " << file_name << std::endl;
    }

    void print_statistics() {
        std::cout << "print zip statistics" << std::endl; 
    }
};

// final 类型zip 不能被继承
// class FastZip: public Zip {
// };


class Document {
public:
    virtual ~Document() {

    }

    virtual void serialize(float version) {
        std::cout << "Document::serialize" << std::endl;
    }
};

class Text: public Document {
public: 
    // 重写父类方法最好用override，让编译器做一个检查
    void serialize(float version) override {
        std::cout << "Text::serialize" << std::endl;
    }
};


GTEST_TEST(OopTest, TestFinal) {
    std::shared_ptr<Document> doc{new Text};
    doc->serialize(1.1f);
}

