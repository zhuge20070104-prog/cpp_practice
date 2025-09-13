#ifndef _FREDRIC_CV_IMAGE_ITEM_H_
#define _FREDRIC_CV_IMAGE_ITEM_H_

#include <QtQuick/QQuickPaintedItem>
#include <QtGui/QPixmap>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class CVImageItem: public QQuickPaintedItem {
    Q_OBJECT 
    Q_PROPERTY(cv::Mat mat READ mat)
public:
    CVImageItem(QQuickItem* parent=0);
    void paint(QPainter* painter) override;
    Q_INVOKABLE void setSource(QString const& filePath);
    Q_INVOKABLE void cnnMat(cv::Mat const& srcMat,  QString const& kernel);
   
    cv::Mat mat() const;
private:
    cv::Mat m_mat;
    QString sourcePath;
};
#endif