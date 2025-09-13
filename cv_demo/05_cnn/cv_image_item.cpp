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

void CVImageItem::cnnMat(cv::Mat const& srcMat,  QString const& kernel) {
    std::cout << "Original Kernel: " << kernel.toStdString() << std::endl;
    auto lines = kernel.split("\n");
    cv::Mat_<float> kernel_mat(3, 3);

    for(int i=0; i<lines.size(); ++i) {
        auto line = lines.at(i);
        auto ele_list = line.split(" ");
        for(int j=0; j<ele_list.size(); ++j) {
            auto ele = ele_list.at(j).toFloat();
            kernel_mat.at<float>(i,j) = ele;
        }
    }
    
    std::cout << "Kernel Mat: " << std::endl;
    std::cout << kernel_mat << std::endl;
    auto temp = srcMat;
    cv::filter2D(temp, m_mat, -1, kernel_mat, cv::Point(-1, -1));
    update();
}


