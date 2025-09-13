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


QVariantMap CVImageItem::putText(cv::Mat const& srcMat) {
    setSource();
    cv::putText(m_mat, "Hello", cv::Point(150, 80), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(255, 255, 0), 2);
    int bL;
    auto cv_size = cv::getTextSize("Hello", cv::FONT_HERSHEY_SIMPLEX, 1.0, 2, &bL);
    QVariantMap result;
    result.insert("width", QVariant::fromValue(cv_size.width));
    result.insert("height", QVariant::fromValue(cv_size.height));
    update();
    return result;
}