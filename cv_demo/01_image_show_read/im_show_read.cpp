#include <iostream>
#include <opencv2/highgui.hpp>

int main(int argc, char* argv[]) {

    // Read colored image
    auto img = cv::imread("../lenna.png");

    // Read image in grayscale mode
    // auto img = cv::imread("../lenna.png", cv::IMREAD_GRAYSCALE);
    cv::imshow("Window", img);
    cv::waitKey(0);
    return EXIT_SUCCESS;
}