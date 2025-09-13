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


void  CVImageItem::setSource(QString const& filePath) {
    QString temp = filePath;
    sourcePath = temp.remove("file://");
    std::cout  << sourcePath.toStdString() << std::endl;
    util::readImage(sourcePath,m_mat);
    update();
}

cv::Mat CVImageItem::mat() const {
    return m_mat;
}

void CVImageItem::erodeMat(cv::Mat const& srcMat, int kernel_size) {
    std::cout <<"Erode Mat" << std::endl;
    cv::Mat temp = srcMat;
    auto elementKernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(kernel_size, kernel_size), cv::Point(-1, -1));
    cv::erode(temp, m_mat, elementKernel, cv::Point(-1, -1), 1);
    update();
}


void CVImageItem::dilateMat(cv::Mat const& srcMat, int kernel_size) {
    std::cout <<"Dilate Mat" << std::endl;
    cv::Mat temp = srcMat;
    auto elementKernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(kernel_size, kernel_size), cv::Point(-1, -1));
    cv::dilate(temp, m_mat, elementKernel, cv::Point(-1, -1), 1);
    update();
}

void CVImageItem::tidyMat(cv::Mat const& srcMat, int kernel_size) {
    std::cout <<"Tidy Mat" << std::endl;
    cv::Mat temp = srcMat;
    cv::Mat transMat = cv::Mat::zeros(cv::Size(temp.cols, temp.rows), CV_8UC3);
    auto elementKernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(kernel_size, kernel_size), cv::Point(-1, -1));
    cv::erode(temp, transMat, elementKernel, cv::Point(-1, -1), 1);
    cv::dilate(transMat, m_mat, elementKernel, cv::Point(-1, -1), 1);
    update();
}