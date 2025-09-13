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


void CVImageItem::drawArrowLine(cv::Mat const& srcMat, float startx, float starty, float thickness, float ratio) {
    setSource();
    int start_x = (int)startx;
    int start_y = (int)starty;
    cv::arrowedLine(m_mat, cv::Point(start_x, start_y), cv::Point(150, 150), cv::Scalar(0, 255, 255), thickness, cv::LINE_AA, 0, (double)ratio/10.0);
    update();
}

void CVImageItem::drawCircle(cv::Mat const& srcMat, float startx, float starty, float radius, float thickness, float shift) {
    setSource();
    int start_x = (int)startx;
    int start_y = (int)starty;
    cv::circle(m_mat, cv::Point(start_x, start_y), radius, cv::Scalar(0, 255, 255), thickness, cv::LINE_AA, shift);
    update();
}

void CVImageItem::drawLine(cv::Mat const& srcMat, float startx, float starty, float thickness) {
    setSource();
    int start_x = (int)startx;
    int start_y = (int)starty;
    cv::Point start_pt(start_x, start_y);
    cv::Point end_pt(500, 500);
    cv::line(m_mat, start_pt, end_pt, cv::Scalar(0, 255, 255), thickness, cv::LINE_AA);
    std::cout << cv::clipLine(cv::Size(500, 500), start_pt, end_pt) << std::endl; 
    update();
}
