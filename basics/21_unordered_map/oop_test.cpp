#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "log.hpp"
#include <utility>
#include <memory>
#include <unordered_set>

#define BOOST_TEST_MODULE TimestampTest
#include "test.hpp"

enum ObjectType {
    TParkingLot,
    TMod
};

struct Point {
    float x;
    float y;

    friend std::ostream& operator<<(std::ostream& os, Point const& p) {
        os << "[" << p.x << "," << p.y << "]"; 
        return os;
    }
};

struct Polygon4 {
    Point p0;
    Point p1;
    Point p2;
    Point p3;
    friend std::ostream& operator<<(std::ostream& os, Polygon4 const& poly) {
        os << poly.p0 << ", " << poly.p1 << ", " << poly.p2 << ", " << poly.p3 << "\n";
        return os;
    }
};


struct PObject {
    PObject(Polygon4 const& poly_, ObjectType type_): poly(poly_), type(type_) {

    }

    virtual ~PObject() {}
    Polygon4 poly;
    ObjectType type;


};
struct PObjectEqual {
    // Reload operator == for std::unordered_set
    bool operator()(std::shared_ptr<PObject> const& left, std::shared_ptr<PObject> const& right) const {
        bool equal_rect = (left->poly.p0.x == right->poly.p0.x) && (left->poly.p0.y == right->poly.p0.y) &&
                          (left->poly.p1.x == right->poly.p1.x) && (left->poly.p1.y == right->poly.p1.y) &&
                          (left->poly.p2.x == right->poly.p2.x) && (left->poly.p2.y == right->poly.p2.y) &&
                          (left->poly.p3.x == right->poly.p3.x) && (left->poly.p3.y == right->poly.p3.y);
        return equal_rect;
    }
};
struct PObjectHash {
    std::size_t operator()(std::shared_ptr<PObject> const& pobject) const {
        auto p0_x = std::hash<float>()(pobject->poly.p0.x);
        auto p0_y = std::hash<float>()(pobject->poly.p0.y);
        auto p1_x = std::hash<float>()(pobject->poly.p1.x);
        auto p1_y = std::hash<float>()(pobject->poly.p1.y);
        auto p2_x = std::hash<float>()(pobject->poly.p2.x);
        auto p2_y = std::hash<float>()(pobject->poly.p2.y);
        auto p3_x = std::hash<float>()(pobject->poly.p3.x);
        auto p3_y = std::hash<float>()(pobject->poly.p3.y);
        return p0_x ^ p0_y ^ p1_x ^ p1_y ^ p2_x ^ p2_y ^ p3_x ^ p3_y;
    }
};

struct ParkingLot: PObject {

    ParkingLot(Polygon4 const& poly_, ObjectType type_, bool valid_, uint64_t timestamp_, bool mechanical_, bool handicap_): PObject(poly_, type_),
        valid(valid_), timestamp(timestamp_), mechanical(mechanical_), handicap(handicap_) {

    }
    bool valid;
    uint64_t timestamp;
    bool  mechanical;
    bool handicap;

    friend bool operator==(ParkingLot const& lhs, ParkingLot const& rhs) {
        return lhs.valid == rhs.valid && lhs.timestamp == rhs.timestamp && lhs.mechanical == rhs.mechanical && lhs.handicap == rhs.handicap;
    }
    
    friend std::ostream& operator<<(std::ostream& os,  ParkingLot const& parkLot) {
        os << "Poly: " << parkLot.poly.p0 << ", " <<  parkLot.poly.p1 << ", "  <<  parkLot.poly.p2 << ", " <<  parkLot.poly.p3;
        os << " timestamp: " << parkLot.timestamp << ", " << "valid: " << std::boolalpha << parkLot.valid << ", mechanical: " << parkLot.mechanical 
            << ", handicap: " << parkLot.handicap << "\n";
        return os;
    }
};


struct MOD: PObject {
    std::string classification;
    uint64_t timestamp;

    MOD(Polygon4 const& poly_, ObjectType type_, std::string const& classification_, uint64_t timestamp_):  PObject(poly_, type_), 
        classification(classification_), timestamp(timestamp_){

    } 

    friend bool operator==(MOD const& lhs, MOD const& rhs) {
        return lhs.classification == rhs.classification && lhs.timestamp == rhs.timestamp;
    }

    friend std::ostream& operator<<(std::ostream& os, MOD const& mod) {
        os << "Poly: " << mod.poly.p0 << ", " <<  mod.poly.p1 << ", "  <<  mod.poly.p2 << ", " <<  mod.poly.p3;
        os << " timestamp: " << mod.timestamp << ", classification: " << mod.classification << "\n"; 
        return os;
    }
};

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(TestTimestamp) {
    std::unordered_set<std::shared_ptr<PObject>, PObjectHash, PObjectEqual> pobjects{
         std::make_shared<MOD>(Polygon4{{1.1f, 1.2f}, {1.1f, 1.2f}, {1.3f, 1.4f}, {2.0f, 3.0f}}, TMod, "kCar", 111111),
         std::make_shared<MOD>(Polygon4{{1.1f, 1.2f}, {1.1f, 1.2f}, {1.3f, 1.4f}, {2.0f, 3.0f}}, TMod, "kCar", 111111),
         std::make_shared<MOD>(Polygon4{{1.1f, 1.3f}, {1.1f, 1.2f}, {1.3f, 1.4f}, {2.0f, 3.0f}}, TMod, "kCar", 111111),
         std::make_shared<MOD>(Polygon4{{1.1f, 1.4f}, {1.1f, 1.2f}, {1.3f, 1.4f}, {2.0f, 3.0f}}, TMod, "kCar", 111111)
         };


    for(auto const& mod: pobjects) {
        std::cout << mod->poly.p0.x << "," << mod->poly.p0.y << " ," << mod->poly.p1.x << "," << mod->poly.p1.y << " ,"
                << mod->poly.p2.x << "," << mod->poly.p2.y << " ," << mod->poly.p3.x << "," << mod->poly.p3.y << "\n";
    }
    std::cout << pobjects.size() << std::endl;
    BOOST_TEST(pobjects.size() == 3, "Pbject size not correct!");
}

BOOST_AUTO_TEST_SUITE_END()
