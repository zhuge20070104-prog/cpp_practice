#ifndef _FREDRIC_DRAWER_HPP_
#define _FREDRIC_DRAWER_HPP_
#include "geometry.hpp"
#include "opencv2/opencv.hpp"
#include <string>
#include <memory>

std::string const WindowName = "Draw Rectangle";
using DrawableObjects = std::vector<std::shared_ptr<VectorObject>>;
using Points = std::vector<Point>;
int const ExitKey = 27;

template<typename AdapterType>
struct Drawer {
    Drawer(DrawableObjects const& vector_objs_): vector_objs(vector_objs_) {
        cv::namedWindow(WindowName, cv::WINDOW_NORMAL);
        cv::resizeWindow(WindowName, 200, 150);
        img = cv::Mat::zeros(cv::Size(200, 150), CV_8UC1);
        img.setTo(cv::Scalar(255));
    }

    void wait_for_dispose() {
        while(ExitKey != cv::waitKey(1000)) {
        }
    }

    void draw() {
        for(auto& o: vector_objs) {
            for(auto& l: *o) {
                AdapterType lpa {l};
                draw_points(lpa.begin(), lpa.end());
            }
        }
        cv::imshow(WindowName, img);
       
    }

private:
    DrawableObjects vector_objs;
    cv::Mat img;
    
    void draw_points(Points::iterator start, Points::iterator end) {
        auto it = start;
        while(it!=end) {
            cv::circle(img, cv::Point(it->x, it->y), 3, cv::Scalar(0), cv::FILLED, cv::LINE_8);
            ++it;
        }
    }
};

using CacheDrawer = Drawer<LineToPointCacheAdapter>;
using NonCacheDrawer = Drawer<LineToPointAdapter>;
#endif