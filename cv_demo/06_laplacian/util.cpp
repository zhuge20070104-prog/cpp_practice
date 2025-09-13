
#include "util.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QtCore/QTextCodec>
 
util::util()
{
}
 
QPixmap util::matToPixmap(const QSize & size, const cv::Mat & mat)
{
    if(mat.empty())
        return QPixmap();
 
    auto img = QImage((const unsigned char*)(mat.data),
                      mat.cols,
                      mat.rows,
                      mat.cols * mat.channels(),
                      QImage::Format_Grayscale8);
    return QPixmap::fromImage(img.scaled(size));
}
 
void util::readImage(const QString & filePath,cv::Mat & mat)
{
    mat = cv::imread(filePath.toStdString());
    cv::cvtColor(mat,mat,cv::COLOR_BGR2RGB);
}