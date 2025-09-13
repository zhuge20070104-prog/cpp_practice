#ifndef _FREDRIC_SHAPE_HPP_
#define _FREDRIC_SHAPE_HPP_

#include "log.h"
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <boost/functional/hash.hpp>



enum class ObjectType {
    TParkingLot,
    TMOD
};

struct PObject {
    int x;
    int y;

    ObjectType type;

    PObject(int x_, int y_, ObjectType type_): x(x_), y(y_), type(type_)  {

    }

    virtual std::string print() = 0; 

    virtual std::size_t hash()  = 0;
};

struct ParkingLot: PObject {

     ParkingLot(int x_, int y_, bool valid_): PObject(x_, y_, ObjectType::TParkingLot), valid(valid_) {}
     std::string print() override {
        std::stringstream ss;
        ss << "PLot: " << "x: " << x << ", y: " << y << std::boolalpha << ", valid: " << valid;
        return ss.str();
     } 

    std::size_t hash() override {
        std::size_t seed = 0x719E6B16;
        boost::hash_combine(seed, x);
        boost::hash_combine(seed, y);
        boost::hash_combine(seed, valid);
        return seed;
    }

     bool valid;
};

struct MOD: PObject {
    MOD(int x_, int y_, std::string const& classification_): PObject(x_, y_, ObjectType::TMOD), classification(classification_) {}
    std::string print() override {
        std::stringstream ss;
        ss << "MOD: " << "x: " << x << ", y: " << y << ", classification: " << classification;
        return ss.str();
     } 
    
     std::size_t hash() override {
        std::size_t seed = 0x719E6B16;
        boost::hash_combine(seed, x);
        boost::hash_combine(seed, y);
        boost::hash_combine(seed, classification);
        return seed;
     }

    std::string classification;
};

using PolyGroup = std::vector<std::shared_ptr<PObject>>; 


#endif