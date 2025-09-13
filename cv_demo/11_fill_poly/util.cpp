
#include "util.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QtCore/QTextCodec>
 
ColorSpace util::colorSpace = BGR;

util::util()
{
}
 
QPixmap util::matToPixmap(const QSize & size, const cv::Mat & mat)
{
    if(mat.empty())
        return QPixmap();
    
    if(colorSpace != RGB) {
        cv::cvtColor(mat,mat,cv::COLOR_BGR2RGB);
    }
    auto img = QImage((const unsigned char*)(mat.data),
                      mat.cols,
                      mat.rows,
                      mat.cols * mat.channels(),
                      QImage::Format_RGB888);
    return QPixmap::fromImage(img.scaled(size));
}
 
void util::readImage(const QString & filePath,cv::Mat & mat)
{
    mat = cv::imread(filePath.toStdString());
    cv::cvtColor(mat,mat,cv::COLOR_BGR2RGB);
    colorSpace = RGB;
}