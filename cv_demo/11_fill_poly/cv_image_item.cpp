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

void CVImageItem::drawConvexPoly(cv::Mat const& srcMat) {
    setSource();   
    std::vector<cv::Point> points {cv::Point(100, 100), cv::Point(200, 100), cv::Point(300, 300), cv::Point(290, 390)}; 
    cv::fillConvexPoly(m_mat, points, cv::Scalar(0, 255, 255));
    update();
}

void CVImageItem::drawPoly(cv::Mat const& srcMat) {
    setSource();   
    std::vector<std::vector<cv::Point>> points { {cv::Point(100, 100), cv::Point(200, 100), cv::Point(300, 300), cv::Point(290, 390)},
            {cv::Point(400, 300), cv::Point(400, 400), cv::Point(450, 450)}}; 
    cv::fillPoly(m_mat, points, cv::Scalar(0, 255, 255));
    update();
}

void CVImageItem::drawPolyLines(cv::Mat const& srcMat, int is_closed) {
    setSource();   
    std::vector<std::vector<cv::Point>> points { {cv::Point(100, 100), cv::Point(200, 100), cv::Point(300, 300), cv::Point(290, 390)},
            {cv::Point(400, 300), cv::Point(400, 400), cv::Point(450, 450)}}; 
    cv::polylines(m_mat, points, is_closed, cv::Scalar(0, 255, 255), 5);
    update();
}
