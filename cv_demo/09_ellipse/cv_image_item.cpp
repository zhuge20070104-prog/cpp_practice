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


void CVImageItem::drawCircle(cv::Mat const& srcMat, float width, float height, float angle, float start_angle, float end_angle) {
    setSource();
    
    std::cout << "Parameters: " << " width: " << width << " height: " << height << " angle: " << angle 
        << " start_angle: " << start_angle << " end_angle: " << end_angle << std::endl;

    int width_ = (int)width;
    int height_ = (int)height;
    cv::ellipse(m_mat, cv::Point(200, 200), cv::Size(width, height), angle, start_angle, end_angle, cv::Scalar(0, 255, 255), 3);
    update();
}



void CVImageItem::drawCircle1(cv::Mat const& srcMat, float angle) {
    setSource();
    cv::ellipse(m_mat, cv::RotatedRect(cv::Point(85, 100), cv::Size(100, 180), angle), cv::Scalar(0, 255, 255), 3);
    update();
}

void CVImageItem::drawE2Polly(cv::Mat const& srcMat) {
    setSource();
    std::vector<cv::Point> vvv;
    cv::ellipse2Poly(cv::Point(85, 100), cv::Size(50, 50), 0, 0, 360, 1, vvv);
    for(std::size_t i=0; i<vvv.size(); ++i) {
        m_mat.at<cv::Vec3b>(vvv[i])[0] = 0;
        m_mat.at<cv::Vec3b>(vvv[i])[1] = 255;
        m_mat.at<cv::Vec3b>(vvv[i])[2] = 255;
    }

    update();
}