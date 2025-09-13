#ifndef _FREDRIC_WINDOW_HPP_
#define _FREDRIC_WINDOW_HPP_

#include "log.h"
#include "opencv2/opencv.hpp"
#include <memory>
#include <string>
#include <array>
#include <numeric>
#include <iostream>
#include <sstream>
#include <memory>
#include <functional>

std::string const WindowName = "Draw Fonts";
int const ExitKey = 27;
int const line_distance = 5;
int const title_bar_height = 50;


struct Text {
    std::string text;
    cv::HersheyFonts font;
};

struct TextBuffer {
    std::vector<Text> texts;
    int max_width {0};
    int max_height {0};
    int total_height {0};

    void add_string(std::string const& text, cv::HersheyFonts const& font_style) {
        texts.emplace_back(Text{text, font_style});
        int base_line;
        auto size = cv::getTextSize(text, font_style, 1.0f, 1, &base_line);
        if(size.width > max_width) {
            max_width = size.width;
        }
        if(size.height > max_height) {
            max_height = size.height;
        }

        // 加的5是行间距
        total_height = texts.size() * (max_height + line_distance);
    }

    // 用于std::max_element，求最大行宽
    bool operator()(TextBuffer const& other) const {
        return max_width < other.max_width;
    }

    // 用于std::accumulate，求所有buffer的高度
    operator int() {
        return total_height;
    }
};


struct Window {
    Window() {
        cv::namedWindow(WindowName, cv::WINDOW_NORMAL);
    }

    void add_buffer(TextBuffer const& buffer) {
        buffers.emplace_back(std::move(buffer));
    }
    
    void draw() {
        width = get_width() + 18;
        height = get_height();
        cv::resizeWindow(WindowName, width, height + title_bar_height);
        img_ = cv::Mat::zeros(cv::Size(width, height + title_bar_height), CV_8UC1);
        img_.setTo(cv::Scalar(255));
        int current_y_pos = title_bar_height;

        for(auto const& buffer:  buffers) {
            for(auto const& text: buffer.texts) {
                cv::putText(img_, text.text, cv::Point(0, current_y_pos), text.font, 1.0, cv::Scalar(0), 1);
                current_y_pos += buffer.max_height + line_distance;
            }
        }

        cv::imshow(WindowName, img_);
    }

    void wait_to_dispose() {
        while(ExitKey != cv::waitKey(1000)) {
        }
    }

    std::vector<TextBuffer> buffers;

private:
    int width;
    int height;
    cv::Mat img_;

    int get_width() {
        auto buffer = *std::max_element(buffers.begin(), buffers.end());
        return buffer.max_width;
    }

    int get_height() {
        auto result = std::accumulate(buffers.begin(), buffers.end(), 0);
        return result;
    }
};

#endif