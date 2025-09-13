#ifndef _FREDRIC_GEOMETRY_HPP_
#define _FREDRIC_GEOMETRY_HPP_

#include <vector>
#include <iostream>
#include <map>
#include <boost/functional/hash.hpp>
#include "log.h"

struct Point {
    int x;
    int y;

    friend std::size_t hash_value(Point const& obj) {
        std::size_t seed = 0x725C686F;
        boost::hash_combine(seed, obj.x);
        boost::hash_combine(seed, obj.y);
        return seed;
    }
};

struct Line {
    Point start;
    Point end;
    friend std::size_t hash_value(Line const& obj) {
        std::size_t seed = 0x719E6B16;
        boost::hash_combine(seed, obj.start);
        boost::hash_combine(seed, obj.end);
        return seed;
    }
};

struct VectorObject {
    virtual std::vector<Line>::iterator begin() = 0;
    virtual std::vector<Line>::iterator end() = 0;
};


struct VectorRectangle: VectorObject {

    VectorRectangle(int x, int y, int width, int height) {
        lines.emplace_back(Line{Point{x, y}, Point{x+width, y}});
        lines.emplace_back(Line{Point{x+width, y}, Point{x+width, y+height}});
        lines.emplace_back(Line{Point{x, y}, Point{x, y+height}});
        lines.emplace_back(Line{Point{x, y+height}, Point{x+width, y+height}});
    }

    std::vector<Line>::iterator begin() override {
        return lines.begin();
    }

    std::vector<Line>::iterator end() override {
        return lines.end();
    }
private:
    std::vector<Line> lines;
};

using Points = std::vector<Point>;

struct LineToPointAdapter {
    LineToPointAdapter(Line& line) {
        static int count = 0;
        B_LOG(info) << ++count << ": Generating Points for line(no caching)\n";
        int left = std::min(line.start.x, line.end.x);
        int right = std::max(line.start.x, line.end.x);
        int top = std::min(line.start.y, line.end.y);
        int bottom = std::max(line.start.y, line.end.y);
        int dx = right - left;
        int dy = bottom - top;

        // only vertical or horizontal lines
        if (dx == 0){
            // vertical
            for (int y = top; y <= bottom; ++y){
                points.emplace_back(Point{ left,y });
            }
            // horizontal
        } else if (dy == 0) {
            for (int x = left; x <= right; ++x) {
                points.emplace_back(Point{ x, top });
            }
        }
    }


    Points::iterator begin() {
        return points.begin();
    }

    Points::iterator end() {
        return points.end();
    }
private:
    Points points;
};


struct LineToPointCacheAdapter {
    LineToPointCacheAdapter(Line& line) {
        boost::hash<Line> hash_;
        line_hash = hash_(line);
        // Find it, don't need to caculate it again
        if(cache.find(line_hash) != cache.end()) {
            return;
        }

        static int count = 0;
        B_LOG(info) << ++ count << ": Generating points for the line(caching)\n";

        Points points;
        // no interpolation
        int left = std::min(line.start.x, line.end.x);
        int right = std::max(line.start.x, line.end.x);
        int top = std::min(line.start.y, line.end.y);
        int bottom = std::max(line.start.y, line.end.y);
        int dx = right - left;
        int dy = bottom - top;

        // only vertical or horizontal lines
        if (dx == 0){
            // vertical
            for (int y = top; y <= bottom; ++y){
                points.emplace_back(Point{ left,y });
            }
            // horizontal
        } else if (dy == 0) {
            for (int x = left; x <= right; ++x) {
                points.emplace_back(Point{ x, top });
            }
        }

        // not find, cache it
        cache[line_hash] = points;
    }

    Points::iterator begin() {
        return cache[line_hash].begin();
    }

    Points::iterator end() {
        return cache[line_hash].end();
    }

private:
    std::size_t line_hash;
    static std::map<std::size_t, Points> cache;
};

std::map<std::size_t, Points> LineToPointCacheAdapter::cache {};

#endif