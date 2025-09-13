#ifndef _FREDRIC_SHAPE_HPP_
#define _FREDRIC_SHAPE_HPP_

#include "log.h"
#include <memory>
#include <string>
#include <vector>
#include <sstream>


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

    virtual bool equal(std::shared_ptr<PObject> other)  = 0;
};

struct ParkingLot: PObject {

     ParkingLot(int x_, int y_, bool valid_): PObject(x_, y_, ObjectType::TParkingLot), valid(valid_) {}
     std::string print() override {
        std::stringstream ss;
        ss << "PLot: " << "x: " << x << ", y: " << y << std::boolalpha << ", valid: " << valid;
        return ss.str();
     } 

    bool equal(std::shared_ptr<PObject> other) override {
        auto p_lot = dynamic_cast<ParkingLot*>(other.get());
        return x == p_lot->x && y == p_lot->y && valid == p_lot->valid;
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
    
    bool equal(std::shared_ptr<PObject> other) override {
        auto p_mod = dynamic_cast<MOD*>(other.get());
        return x == p_mod->x && y == p_mod->y && classification == p_mod->classification;
    }

    std::string classification;
};

using PolyGroup = std::vector<std::shared_ptr<PObject>>; 


#endif