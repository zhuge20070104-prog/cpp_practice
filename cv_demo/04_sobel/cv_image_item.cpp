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
    cv::cvtColor(m_mat, m_mat, cv::COLOR_RGB2GRAY);
    update();
}

cv::Mat CVImageItem::mat() const {
    return m_mat;
}

void CVImageItem::sobelMat(cv::Mat const& srcMat, int dx, int dy, int kernel_size, int scale_factor, int delta_value) {
    std::cout <<"sobel Mat" << std::endl;
    std::cout << "dx: " << dx << std::endl;
    std::cout << "dy: " << dy << std::endl; 
    cv::Mat temp = srcMat;
    cv::Sobel(temp, m_mat, CV_8UC1, dx, dy, kernel_size, scale_factor, delta_value);
    update();
}


