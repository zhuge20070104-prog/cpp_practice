#include  "cv_image_item.h"
#include "util.h"
#include <iostream>
#include <QtGui/QPainter>

CVImageItem::CVImageItem(QQuickItem* parent):
    QQuickPaintedItem(parent){
}

void CVImageItem::paint(QPainter* painter) {
    painter->setRenderHints(QPainter::Antialiasing, true);
    std::cout << "paint" << std::endl;
    QPoint top_left((int)x(), (int)y());
    QSize size(width(), height());
    QRect rect(top_left, size);
    std::cout << "x:" << x() << ",  y:" << y() << std::endl;
    std::cout << "w:" << width() << ", h:" << height() << std::endl;
    painter->drawPixmap(rect, util::matToPixmap(size,m_mat));
}


void  CVImageItem::setSource() {
    std::cout << "set source width: " << width() << std::endl;
    std::cout << "set source height: " << height() << std::endl;
    m_mat = cv::Mat(width(),  height(), CV_8UC3, cv::Scalar(255, 255, 255));
    update();
}

cv::Mat CVImageItem::mat() const {
    return m_mat;
}

void CVImageItem::drawContour1(cv::Mat const& srcMat) {
    setSource();   
    std::vector<std::vector<cv::Point>> contours {{cv::Point(100, 100), cv::Point(100, 150), cv::Point(150, 150)},
        {cv::Point(300, 300), cv::Point(400, 400)},
        {cv::Point(100, 300), cv::Point(200, 400)}};
    for(std::size_t i=0; i<contours.size(); ++i) {
        cv::drawContours(m_mat, contours, i, cv::Scalar(0, 255, 255),  5);
    }
    update();
}

void CVImageItem::drawContour2(cv::Mat const& srcMat) {
    setSource();   
    // 放相同点，也可以拼回三角形
    std::vector<std::vector<cv::Point>> contours {{cv::Point(100, 100), cv::Point(100, 150), cv::Point(400, 150), cv::Point(100, 100)},
        {cv::Point(300, 300), cv::Point(400, 400)},
        {cv::Point(100, 300), cv::Point(200, 400)}};
    for(std::size_t i=0; i<contours.size(); ++i) {
        cv::drawContours(m_mat, contours, i, cv::Scalar(0, 255, 255),  5);
    }
    update();
}