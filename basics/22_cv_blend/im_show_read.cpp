#include <iostream>
#include "opencv2/opencv.hpp"
#include <vector>

std::vector<std::vector<cv::Point>> getPolyPoints() {
    std::vector<std::vector<cv::Point>> ps_points;
    std::vector<cv::Point> ps_point;
    ps_point.push_back(cv::Point{1, 1});
    ps_point.push_back(cv::Point{100, 100});
    ps_points.push_back(ps_point);
    return ps_points;
}

void DrawPolygon(cv::Mat const& img,  cv::Scalar const& color , cv::Mat& dst, int line_width) {
    auto ps_points = getPolyPoints();
    dst = img.clone();
    cv::polylines(dst, ps_points, false, color, line_width);
}


void DrawPolygonOnSrc(cv::Mat& img,  cv::Scalar const& color , int line_width) {
    auto ps_points = getPolyPoints();
    cv::polylines(img, ps_points, false, color, line_width);
}



int main(int argc, char* argv[]) {

    // Read colored image
    auto img = cv::imread("../back.png");
    auto blend = img.clone();

    // Read image in grayscale mode
    // auto img = cv::imread("../lenna.png", cv::IMREAD_GRAYSCALE);
   
  
    // float alpha = 0.35f;
    // float alpha = 0.5f;
    // cv::Mat result;
    // cv::Mat dst1;
    // cv::Mat dst2;
    // DrawPolygon(img, cv::Scalar(0, 0, 255), dst1, 3);
    // DrawPolygon(img, cv::Scalar(0, 255, 255), dst2, 2);
    // cv::addWeighted(dst1, alpha, dst2, 1-alpha, 0.0f, result); 


    DrawPolygonOnSrc(img, cv::Scalar(0, 0, 255), 3);
    DrawPolygonOnSrc(img, cv::Scalar(0, 255, 255), 2);

    cv::imshow("Window",  img);
    cv::waitKey(0);
    cv::waitKey(0);
    return EXIT_SUCCESS;
}