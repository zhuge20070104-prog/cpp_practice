#ifndef _FREDRIC_CONTACT_HPP_
#define _FREDRIC_CONTACT_HPP_

#include <iostream>
#include <string>
#include <memory>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/unique_ptr.hpp>
// 最后一个头文件必须加，支持std::unique_ptr serialization

struct Address {
    std::string street;
    std::string city;
    int suite;

    // 不增加默认构造，不支持serialization
    Address() {}

    Address(std::string const& street_, std::string const& city_, int suite_): street(street_), city(city_), suite(suite_) {
    }

    friend std::ostream& operator<<(std::ostream& os, Address const& address) {
        return os << " [street: " << address.street << " city: " << address.city << " suite: " << address.suite << "]";  
    }

private:
    friend class boost::serialization::access;

    template <class Ar>
    void serialize(Ar& ar, unsigned int const version) {
        ar & street;
        ar & city;
        ar & suite;
    }
};


struct Contact {
    std::string name;
    std::unique_ptr<Address> address;
    // 不加默认构造，不支持serialization
    Contact() {}

    // 构造的时候可以直接移动，Address被直接包含到了contact里面，移动后的Address只能和Contact绑定了
    Contact(std::string const& name_, std::unique_ptr<Address> address_): name(name_), address(std::move(address_)) {}

    // 拷贝的时候必须重新构建一个unique_ptr对象，不能移动，因为另外一个contact还需要使用的，注意着点
    Contact(Contact const& other): name(other.name), address(std::make_unique<Address>(*other.address)) {}

    friend std::ostream& operator<<(std::ostream& os, Contact const& contact) {
        return os << "name: [" << contact.name << "] address: " << *contact.address;
    }

private:
    friend class boost::serialization::access;
    template <class Ar>
    void serialize(Ar& ar, unsigned int const version) {
        ar & name;
        ar & address;
    }
};

auto clone_ = [](Contact const& c) {
    std::ostringstream oss;
    boost::archive::text_oarchive oa {oss};
    oa << c;

    std::istringstream iss {oss.str()};
    boost::archive::text_iarchive ia {iss};
    Contact result;
    ia >> result;
    return result;
};
#endif