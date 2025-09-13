#include "mouse_memory.h"
#include <string>
#include <iostream>
#include <sstream>
#include <boost/filesystem.hpp>

std::string const out_file {"result.txt"};

MouseMemory::MouseMemory(QObject* parent): QObject(parent) {
    if(!boost::filesystem::exists(out_file)) {
        std::cout << "file not exist.." << std::endl;
        return;
    }
    std::fstream fs {out_file, std::ios::in};
    int x, y; 
    while(fs >> x >> y) {
        m_points.append(QVariant::fromValue(new Point(x, y)));
    }
}



QVariantList MouseMemory::points() {
    return m_points;
}

void MouseMemory::save() {
    std::fstream fs {out_file, std::ios::out};
    for(auto const& p: m_points) {
        auto pt=p.value<Point*>();
        fs << pt->x() << " " << pt->y() << " ";
    }
    fs.flush();
    fs.close();
}

void MouseMemory::clear() {
    m_points.clear();
}

void MouseMemory::add(int x, int y) {
    m_points.append(QVariant::fromValue(new Point(x, y)));
}

MouseMemory::~MouseMemory() {
    save();
}
