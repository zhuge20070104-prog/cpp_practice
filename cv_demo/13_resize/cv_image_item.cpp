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
    QSize size(m_mat.cols/draw_ratio, m_mat.rows/draw_ratio);
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
    draw_ratio = 1.5f;
    update();
}

cv::Mat CVImageItem::mat() const {
    return m_mat;
}


void CVImageItem::resizelMatWH(cv::Mat const& srcMat, int width, int height) {
    cv::Mat temp = srcMat.clone();
    cv::resize(temp, m_mat, cv::Size(width, height), 0, 0);
    draw_ratio = 1.0f;
    update();
}

void CVImageItem::resizelMatWHRatio(cv::Mat const& srcMat, int width_r, int height_r) {
    cv::Mat temp = srcMat.clone();
    cv::resize(temp, m_mat, cv::Size(), width_r, height_r);
    draw_ratio = 15.0f;
    update();
}


