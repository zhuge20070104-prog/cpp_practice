#include  "cv_image_item.h"
#include "util.h"
#include <iostream>
#include <QtGui/QPainter>


CVImageItem::CVImageItem(QQuickItem* parent):
    QQuickPaintedItem(parent), m_mat(3, 3){
}

void CVImageItem::paint(QPainter* painter) {
    painter->setRenderHints(QPainter::Antialiasing, true);
    std::cout << "paint" << std::endl;
    QPoint top_left((int)x(), (int)y());
    QSize size(width(), height());
    QRect rect(top_left, size);
    std::cout << "x:" << x() << ",  y:" << y() << std::endl;
    std::cout << "w:" << width() << ", h:" << height() << std::endl;
    QFont font;
    font.setPointSize(20);
    painter->setFont(font);
    QString mat_s = matStr();
    std::cout << "mat Str: \n" << mat_s.toStdString() << std::endl;
    painter->drawText(top_left.x(), top_left.y(), size.width(), size.height(),  Qt::AlignCenter, mat_s);
}


void  CVImageItem::setSource(QString const&  srcMatStr) {
    
    auto lines = srcMatStr.split("\n");

    for(int i=0; i<lines.size(); ++i) {
        auto line = lines.at(i);
        auto ele_list = line.split(" ");
        for(int j=0; j<ele_list.size(); ++j) {
            auto ele = ele_list.at(j).toFloat();
            m_mat.at<float>(i,j) = ele;
        }
    }
    update();
}

cv::Mat_<float> CVImageItem::mat() const {
    return m_mat;
}


QString CVImageItem::matStr() {
    int h = m_mat.rows;
    int w = m_mat.cols;

    QString result;
    for(int i=0; i<h; ++i) {
        QStringList line;
        for(int j=0; j<w; ++j) {
            line << QString::number((int)m_mat.at<float>(i, j));
        }
        auto line_str = line.join(" ");
        result += line_str;
        result += "\n";
    }
    return result;
}

void CVImageItem::cnnMat(cv::Mat_<float> const& srcMat,  QString const& kernel) {
    std::cout << "Source Mat: " << srcMat << std::endl; 
    std::cout << "Original Kernel: " << kernel.toStdString() << std::endl;
    auto lines = kernel.split("\n");
    cv::Mat_<float> kernel_mat(2, 2);

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


