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

void CVImageItem::medianMat(cv::Mat const& srcMat) {
    std::cout <<"median Mat" << std::endl;
    cv::Mat temp = srcMat;
    cv::medianBlur(temp, m_mat,  15);
    update();
}

void CVImageItem::gaussianMat(cv::Mat const& srcMat) {
    std::cout <<"gaussian Mat" << std::endl;
    cv::Mat temp = srcMat;
    cv::GaussianBlur(temp, m_mat,  cv::Size(15, 15), 0);
    update();
}

void CVImageItem::bilateralMat(cv::Mat const& srcMat) {
    std::cout <<"bilateral Mat" << std::endl;
    cv::Mat temp = srcMat;
    cv::bilateralFilter(temp, m_mat,  15, 95, 45);
    update();
}
