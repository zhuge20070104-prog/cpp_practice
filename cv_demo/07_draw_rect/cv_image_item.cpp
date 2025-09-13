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

void  CVImageItem::drawRect(cv::Mat const& srcMat, float top_left, float bottom_right) {
    // 还原画布
    setSource();
    int top_left_int = (int)top_left;
    int bottom_right_int = (int)bottom_right;
    cv::rectangle(m_mat, cv::Point(top_left_int, top_left_int), cv::Point(bottom_right_int, bottom_right_int), 
        cv::Scalar(255, 0, 0), 3, cv::LINE_4);
    update();
}